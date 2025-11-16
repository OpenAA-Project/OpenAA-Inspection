#include <QBuffer>
#include <QString>

#include "XRaster.h"
#include "XRasterLibrary.h"
#include "XPointer.h"
#include "XImageProcess.h"
#include "XGeneralDialog.h"
#include "XGeneralFunc.h"
#include "XMaskingFromGeneral.h"
#include "XRasterPacket.h"
#include "swap.h"

#include "XFlexArea.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include "XGUIRasterPacket.h"
#include "XUndo.h"
#include "XCrossObj.h"
#include <float.h>


int	DbgCounterInRaster;
int	DbgValueInRaster;

void	RasterInPage::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdLoadRaster	*CmdLoadRasterVar=dynamic_cast<CmdLoadRaster *>(packet);
	if(CmdLoadRasterVar!=NULL){
		RasterFileLayer	*f=FileLayerList.Find(CmdLoadRasterVar->FileLayerID);
		if(f==NULL){
			f=new RasterFileLayer(&FileLayerList);
			f->FileLayerID	=CmdLoadRasterVar->FileLayerID;
			f->FileName	=CmdLoadRasterVar->FileName;
			FileLayerList.AppendList(f);
		}
		QFileInfo	FInfo(CmdLoadRasterVar->FileName);
		if(FInfo.suffix().toLower()==/**/"pdf"){
			LoadPDF(f,*CmdLoadRasterVar->pData);
		}

		MakeXY();
		SetCurrentSize();
		bool	Error=false;
		BuildPointer(Error);
		return;
	}
	CmdSetPDFWithSelfTransform	*CmdSetPDFWithSelfTransformVar=dynamic_cast<CmdSetPDFWithSelfTransform *>(packet);
	if(CmdSetPDFWithSelfTransformVar!=NULL){
		RemoveAllDatas();
		RasterFileLayer	*f=FileLayerList.Find(0);
		if(f==NULL){
			f=new RasterFileLayer(&FileLayerList);
			f->FileLayerID	=0;
			f->FileName	=/**/"PDF file";
			FileLayerList.AppendList(f);
		}
		CmdSetPDFWithSelfTransformVar->Result=LoadPDF(f,CmdSetPDFWithSelfTransformVar->PDFData);
		//RasterBase	*ABase=(RasterBase	*)GetParentBase();
		//QDir::setCurrent(GetLayersBase()->GetUserPath());
		//QFile	File(ABase->DefaultTransformFileName);
		//if(File.open(QIODevice::ReadOnly)==true){
		//	LoadTransformParam(&File);
		//}
		MakeXY();
		SetCurrentSize();
		bool	Error=false;
		BuildPointer(Error);
		return;
	}
	CmdSetDrawAttr	*CmdSetDrawAttrVar=dynamic_cast<CmdSetDrawAttr *>(packet);
	if(CmdSetDrawAttrVar!=NULL){
		SetFileLayerVisible(CmdSetDrawAttrVar->ShownFileID);
		return;
	}
	CmdReqRasterArea	*CmdReqRasterAreaVar=dynamic_cast<CmdReqRasterArea *>(packet);
	if(CmdReqRasterAreaVar!=NULL){
		static	int	DbgIn=0;
		CmdReqRasterAreaVar->MinX=DBL_MAX;
		CmdReqRasterAreaVar->MinY=DBL_MAX;
		CmdReqRasterAreaVar->MaxX=-DBL_MAX;
		CmdReqRasterAreaVar->MaxY=-DBL_MAX;
		for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
			RasterItemAbstract	*item=dynamic_cast<RasterItemAbstract *>(a);
			if(item!=NULL){
				double	x1,y1,x2,y2;
				item->GetXY(x1,y1,x2,y2);
				if(-5<x1 && x1<0){
					item->MakeXY();
					DbgIn++;
				}
				CmdReqRasterAreaVar->MinX=min(CmdReqRasterAreaVar->MinX,x1);
				CmdReqRasterAreaVar->MinY=min(CmdReqRasterAreaVar->MinY,y1);
				CmdReqRasterAreaVar->MaxX=max(CmdReqRasterAreaVar->MaxX,x2);
				CmdReqRasterAreaVar->MaxY=max(CmdReqRasterAreaVar->MaxY,y2);
			}
		}
		return;
	}
	CmdClearRaster	*CmdClearRasterVar=dynamic_cast<CmdClearRaster *>(packet);
	if(CmdClearRasterVar!=NULL){
		FileLayerList		.RemoveAll();
		TriangleAreaData	.RemoveAll();
		RemoveAllDatas();
		return;
	}

	CmdRasterMove	*CmdMoveVar=dynamic_cast<CmdRasterMove *>(packet);
	if(CmdMoveVar!=NULL){
		UndoElement<RasterInPage>	*UPointer=new UndoElement<RasterInPage>(this,&RasterInPage::UndoMove);
		if(GetParamGlobal()->MaxUndoCount>0){
			int32	Numb=0;
			for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
				if(a->GetSelected()==true && a->GetEditLocked()==false  && a->GetVisible()==true){
					RasterItemAbstract	*item=dynamic_cast<RasterItemAbstract *>(a);
					if(item!=NULL){
						Numb++;
					}
				}
			}
			::Save(UPointer->GetWritePointer(),Numb);
		}
		bool	FlagUndoBuff=true;
		for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
			if(a->GetSelected()==true && a->GetEditLocked()==false  && a->GetVisible()==true){
				RasterItemAbstract	*item=dynamic_cast<RasterItemAbstract *>(a);
				if(item!=NULL){
					if(GetParamGlobal()->MaxUndoCount>0){
						if(FlagUndoBuff==true && ::Save(UPointer->GetWritePointer(),item->GetID())==false)
							FlagUndoBuff=false;
						if(FlagUndoBuff==true && item->SaveOnlyShape(UPointer->GetWritePointer())==false)
							FlagUndoBuff=false;
					}
					if(CmdMoveVar->PixelMode==true){
						item->MoveToFloat(CmdMoveVar->XDir ,CmdMoveVar->YDir);
					}
					else{
						item->MoveToFloat(CmdMoveVar->XDir ,CmdMoveVar->YDir);
					}
					item->MakeXY();
				}
			}
		}
		GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);
		SetCurrentSize();
		return;
	}
	CmdRasterRotate	*CmdRotateVar=dynamic_cast<CmdRasterRotate *>(packet);
	if(CmdRotateVar!=NULL){
		UndoElement<RasterInPage>	*UPointer=new UndoElement<RasterInPage>(this,&RasterInPage::UndoRotate);
		if(GetParamGlobal()->MaxUndoCount>0){
			int32	Numb=0;
			for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
				if(a->GetSelected()==true && a->GetEditLocked()==false  && a->GetVisible()==true){
					RasterItemAbstract	*item=dynamic_cast<RasterItemAbstract *>(a);
					if(item!=NULL){
						Numb++;
					}
				}
			}
			::Save(UPointer->GetWritePointer(),Numb);
		}
		bool	FlagUndoBuff=true;
		for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
			if(a->GetSelected()==true && a->GetEditLocked()==false  && a->GetVisible()==true){
				RasterItemAbstract	*item=dynamic_cast<RasterItemAbstract *>(a);
				if(item!=NULL){
					if(GetParamGlobal()->MaxUndoCount>0){
						if(FlagUndoBuff==true && ::Save(UPointer->GetWritePointer(),item->GetID())==false)
							FlagUndoBuff=false;
						if(FlagUndoBuff==true && item->SaveOnlyShape(UPointer->GetWritePointer())==false)
							FlagUndoBuff=false;
					}
					item->Rotate(2*M_PI*CmdRotateVar->Angle/360.0
								,CmdRotateVar->CenterX,CmdRotateVar->CenterY);
					item->MakeXY();
				}
			}
		}
		GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);
		SetCurrentSize();
		return;
	}
	CmdRasterZoom	*CmdZoomVar=dynamic_cast<CmdRasterZoom *>(packet);
	if(CmdZoomVar!=NULL){
		UndoElement<RasterInPage>	*UPointer=new UndoElement<RasterInPage>(this,&RasterInPage::UndoZoom);
		if(GetParamGlobal()->MaxUndoCount>0){
			int32	Numb=0;
			for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
				if(a->GetSelected()==true && a->GetEditLocked()==false  && a->GetVisible()==true){
					RasterItemAbstract	*item=dynamic_cast<RasterItemAbstract *>(a);
					if(item!=NULL){
						Numb++;
					}
				}
			}
			::Save(UPointer->GetWritePointer(),Numb);
		}
		bool	FlagUndoBuff=true;
		//DbgCounterInRaster=0;
		for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
			if(a->GetSelected()==true && a->GetEditLocked()==false  && a->GetVisible()==true){
				RasterItemAbstract	*item=dynamic_cast<RasterItemAbstract *>(a);
				if(item!=NULL){
					if(GetParamGlobal()->MaxUndoCount>0){
						if(FlagUndoBuff==true && ::Save(UPointer->GetWritePointer(),item->GetID())==false)
							FlagUndoBuff=false;
						if(FlagUndoBuff==true && item->SaveOnlyShape(UPointer->GetWritePointer())==false)
							FlagUndoBuff=false;
					}
					item->Zoom(CmdZoomVar->XZoomDir,CmdZoomVar->YZoomDir
							 , CmdZoomVar->CenterX,CmdZoomVar->CenterY);
					item->MakeXY();
				}
			}
		}
		GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);
		SetCurrentSize();
		return;
	}
	CmdRasterShear	*CmdShearVar=dynamic_cast<CmdRasterShear *>(packet);
	if(CmdShearVar!=NULL){
		UndoElement<RasterInPage>	*UPointer=new UndoElement<RasterInPage>(this,&RasterInPage::UndoShear);
		if(GetParamGlobal()->MaxUndoCount>0){
			int32	Numb=0;
			for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
				if(a->GetSelected()==true && a->GetEditLocked()==false  && a->GetVisible()==true){
					RasterItemAbstract	*item=dynamic_cast<RasterItemAbstract *>(a);
					if(item!=NULL){
						Numb++;
					}
				}
			}
			::Save(UPointer->GetWritePointer(),Numb);
		}
		bool	FlagUndoBuff=true;
		for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
			if(a->GetSelected()==true && a->GetEditLocked()==false  && a->GetVisible()==true){
				RasterItemAbstract	*item=dynamic_cast<RasterItemAbstract *>(a);
				if(item!=NULL){
					if(GetParamGlobal()->MaxUndoCount>0){
						if(FlagUndoBuff==true && ::Save(UPointer->GetWritePointer(),item->GetID())==false)
							FlagUndoBuff=false;
						if(FlagUndoBuff==true && item->SaveOnlyShape(UPointer->GetWritePointer())==false)
							FlagUndoBuff=false;
					}
					item->Shear(CmdShearVar->XMode,2*M_PI*CmdShearVar->Shear/360.0
							,   CmdShearVar->CenterX,CmdShearVar->CenterY);
					item->MakeXY();
				}
			}
		}
		GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);
		SetCurrentSize();
		return;
	}
	CmdRasterMirror	*CmdMirrorVar=dynamic_cast<CmdRasterMirror *>(packet);
	if(CmdMirrorVar!=NULL){
		UndoElement<RasterInPage>	*UPointer=new UndoElement<RasterInPage>(this,&RasterInPage::UndoMirror);
		if(GetParamGlobal()->MaxUndoCount>0){
			int32	Numb=0;
			for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
				if(a->GetSelected()==true && a->GetEditLocked()==false  && a->GetVisible()==true){
					RasterItemAbstract	*item=dynamic_cast<RasterItemAbstract *>(a);
					if(item!=NULL){
						Numb++;
					}
				}
			}
			::Save(UPointer->GetWritePointer(),Numb);
		}
		bool	FlagUndoBuff=true;
		for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
			if(a->GetSelected()==true && a->GetEditLocked()==false  && a->GetVisible()==true){
				RasterItemAbstract	*item=dynamic_cast<RasterItemAbstract *>(a);
				if(item!=NULL){
					if(GetParamGlobal()->MaxUndoCount>0){
						if(FlagUndoBuff==true && ::Save(UPointer->GetWritePointer(),item->GetID())==false)
							FlagUndoBuff=false;
						if(FlagUndoBuff==true && item->SaveOnlyShape(UPointer->GetWritePointer())==false)
							FlagUndoBuff=false;
					}
					item->Mirror(CmdMirrorVar->XMode
								,CmdMirrorVar->CenterX ,CmdMirrorVar->CenterY);
					item->MakeXY();
				}
			}
		}
		GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);
		SetCurrentSize();
		return;
	}
	CmdRasterCenterize	*CmdCenterizeVar=dynamic_cast<CmdRasterCenterize *>(packet);
	if(CmdCenterizeVar!=NULL){
		UndoElement<RasterInPage>	*UPointer=new UndoElement<RasterInPage>(this,&RasterInPage::UndoCenterize);
		if(GetParamGlobal()->MaxUndoCount>0){
			int32	Numb=0;

			for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
				if(a->GetSelected()==true && a->GetEditLocked()==false  && a->GetVisible()==true){
					RasterItemAbstract	*item=dynamic_cast<RasterItemAbstract *>(a);
					if(item!=NULL){
						Numb++;
					}
				}
			}
			::Save(UPointer->GetWritePointer(),Numb);
		}

		double	tMovX=GetDataInPage()->GetGlobalOutlineOffset()->x;
		double	tMovY=GetDataInPage()->GetGlobalOutlineOffset()->y;
		bool	FlagUndoBuff=true;

		for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
			if(a->GetSelected()==true && a->GetEditLocked()==false  && a->GetVisible()==true){
				RasterItemAbstract	*item=dynamic_cast<RasterItemAbstract *>(a);
				if(item!=NULL){
					if(GetParamGlobal()->MaxUndoCount>0){
						if(FlagUndoBuff==true && ::Save(UPointer->GetWritePointer(),item->GetID())==false)
							FlagUndoBuff=false;
						if(FlagUndoBuff==true && item->SaveOnlyShape(UPointer->GetWritePointer())==false)
							FlagUndoBuff=false;
					}
						
					item->MoveToFloat(-CmdCenterizeVar->CenterX+tMovX ,-CmdCenterizeVar->CenterY+tMovY);
					item->Zoom(CmdCenterizeVar->ZoomRate,CmdCenterizeVar->ZoomRate , 0,0);
					item->MoveToFloat(CmdCenterizeVar->MovX-tMovX ,CmdCenterizeVar->MovY-tMovY);
					item->MakeXY();
				}
			}
		}
		GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);
		SetCurrentSize();
		return;
	}
	CmdRasterCenterizeOnly	*CmdCenterizeOnlyVar=dynamic_cast<CmdRasterCenterizeOnly *>(packet);
	if(CmdCenterizeOnlyVar!=NULL){
		UndoElement<RasterInPage>	*UPointer=new UndoElement<RasterInPage>(this,&RasterInPage::UndoCenterizeOnly);
		if(GetParamGlobal()->MaxUndoCount>0){
			int32	Numb=0;

			for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
				if(a->GetSelected()==true && a->GetEditLocked()==false  && a->GetVisible()==true){
					RasterItemAbstract	*item=dynamic_cast<RasterItemAbstract *>(a);
					if(item!=NULL){
						Numb++;
					}
				}
			}
			::Save(UPointer->GetWritePointer(),Numb);
		}

		double	tMovX=GetDataInPage()->GetGlobalOutlineOffset()->x;
		double	tMovY=GetDataInPage()->GetGlobalOutlineOffset()->y;
		bool	FlagUndoBuff=true;

		for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
			if(a->GetSelected()==true && a->GetEditLocked()==false  && a->GetVisible()==true){
				RasterItemAbstract	*item=dynamic_cast<RasterItemAbstract *>(a);
				if(item!=NULL){
					if(GetParamGlobal()->MaxUndoCount>0){
						if(FlagUndoBuff==true && ::Save(UPointer->GetWritePointer(),item->GetID())==false)
							FlagUndoBuff=false;
						if(FlagUndoBuff==true && item->SaveOnlyShape(UPointer->GetWritePointer())==false)
							FlagUndoBuff=false;
					}					
					item->MoveToFloat(-CmdCenterizeOnlyVar->CenterX+tMovX ,-CmdCenterizeOnlyVar->CenterY+tMovY);
					item->MoveToFloat(CmdCenterizeOnlyVar->MovX-tMovX ,CmdCenterizeOnlyVar->MovY-tMovY);
					item->MakeXY();
				}
			}
		}
		GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);
		SetCurrentSize();
		return;
	}

	MsgRasterSelectAll	*MsgRasterSelectAllVar=dynamic_cast<MsgRasterSelectAll *>(packet);
	if(MsgRasterSelectAllVar!=NULL){
		IntList LayerList;
		SelectAll(LayerList);
		return;
	}
	GUICmdMakeImage	*GUICmdMakeImageVar=dynamic_cast<GUICmdMakeImage *>(packet);
	if(GUICmdMakeImageVar!=NULL){
		MakeXY();
		ReleaseAllSelectedItem();
		if(GUICmdMakeImageVar->MIMode==GUICmdMakeImage::_MIM_ToMaster){
			MakeImage(GUICmdMakeImageVar->ButtonsToOperateLayer
					, GUICmdMakeImageVar->LayerColor);
		}
		if(GUICmdMakeImageVar->MIMode==GUICmdMakeImage::_MIM_ToDispatchMaster){
			MakeImage();
		}
		else if(GUICmdMakeImageVar->MIMode==GUICmdMakeImage::_MIM_Standard){
			CreateImagingBmpBuff();
			int	LayerID=0;
			for(BoolClass *b=GUICmdMakeImageVar->ButtonsToOperateLayer.GetFirst();b!=NULL;b=b->GetNext(),LayerID++){
				if(b->GetValue()==true){
					MakeImage(ImagingBmp,LayerID);
				}
			}
		}
		else if(GUICmdMakeImageVar->MIMode==GUICmdMakeImage::_MIM_Enlarge){
			CreateImagingBmpBuff();
			int	LayerID=0;
			for(BoolClass *b=GUICmdMakeImageVar->ButtonsToOperateLayer.GetFirst();b!=NULL;b=b->GetNext(),LayerID++){
				if(b->GetValue()==true){
					MakeImageEnlarge(ImagingBmp,LayerID);
				}
			}
		}
		else if(GUICmdMakeImageVar->MIMode==GUICmdMakeImage::_MIM_Shrinked){
			CreateImagingBmpBuff();
			int	LayerID=0;
			for(BoolClass *b=GUICmdMakeImageVar->ButtonsToOperateLayer.GetFirst();b!=NULL;b=b->GetNext(),LayerID++){
				if(b->GetValue()==true){
					MakeImageShrinked(ImagingBmp,LayerID);
				}
			}
		}
		else if(GUICmdMakeImageVar->MIMode==GUICmdMakeImage::_MIM_Shiftable){
			CreateImagingBmpBuff();
			int	LayerID=0;
			for(BoolClass *b=GUICmdMakeImageVar->ButtonsToOperateLayer.GetFirst();b!=NULL;b=b->GetNext(),LayerID++){
				if(b->GetValue()==true){
					MakeImageShiftable(ImagingBmp,LayerID);
				}
			}
		}
		else if(GUICmdMakeImageVar->MIMode==GUICmdMakeImage::_MIM_Clear){
			CreateImagingBmpBuff();
			MatrixBuffClear	(ImagingBmp ,0,ImagingBmpXByte ,ImagingBmpYLen);
		}
		RasterBase	*GBase=(RasterBase *)GetParentBase();
		if(GBase->MasterNoForImaging<GetLayersBase()->GetParamGlobal()->AllocatedCountMasterBuff){
			GetLayersBase()->CopyShadowImageFromParent(true	,GBase->MasterNoForImaging
															,GetPhaseCode(),GetPage());
		}
		return;
	}

	CmdCopyImageToMaster	*CmdCopyImageToMasterVar=dynamic_cast<CmdCopyImageToMaster *>(packet);
	if(CmdCopyImageToMasterVar!=NULL){
		MakeXY();
		ReleaseAllSelectedItem();
	
		int	XLen=GetDotPerLine();
		int	YLen=GetMaxLines();

		RasterDrawAttr	Attr;
		Attr.DrawMode.ShowPDF=true;
		int	N=0;
		//RasterBase	*GBase=(RasterBase *)GetParentBase();
		//for(BoolClass *b=ButtonsToOperateLayer.GetFirst();b!=NULL;b=b->GetNext(),N++){
		//	if(b->GetValue()==true && FileLayerList[N]!=NULL){
		//		Attr.ShownFileID.Add(FileLayerList[N]->FileLayerID);
		//		Attr.LayerColor[N]=LayerColor[N];
		//	}
		//}
		QImage	TmpImage(XLen,YLen,QImage::Format_ARGB32);
		TmpImage.fill(0);

		for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
			RasterItemAbstract	*Item=dynamic_cast<RasterItemAbstract *>(a);
			if(Item!=NULL){
				a->Draw(TmpImage,0,0,1.0,&Attr);
			}
		}

		ImagePointerContainer	MasterImage;
		GetMasterImages(MasterImage);

		for(PureFlexAreaList *f=CmdCopyImageToMasterVar->ChangeableAreas.GetFirst();f!=NULL;f=f->GetNext()){
			for(int i=0;i<f->GetFLineLen();i++){
				int	y=f->GetFLineAbsY(i);
				QRgb	*s=(QRgb *)TmpImage.scanLine(y);
				BytePointerContainer	m=MasterImage.GetY(y);
				int	x1=f->GetFLineLeftX(i);
				int	numb=f->GetFLineNumb(i);
				for(int xn=0;xn<numb;xn++){
					int	x=x1+xn;
					m[x]=s[x];
				}
			}
		}
		return;
	}
	GUICmdMakeBitImage	*GUICmdMakeBitImageVar=dynamic_cast<GUICmdMakeBitImage *>(packet);
	if(GUICmdMakeBitImageVar!=NULL){
		MakeXY();
		ReleaseAllSelectedItem();
		MakeBitImage(GUICmdMakeBitImageVar->ButtonsToOperateLayer
					,GUICmdMakeBitImageVar->LayerColor			 );
	
		return;
	}
	CmdRasterExec3PointAlignment	*GExe3P=dynamic_cast<CmdRasterExec3PointAlignment *>(packet);
	if(GExe3P!=NULL){
		MakeXY();
		int	Numb=0;
		for(int i=0;i<MaxRasterPointNumb;i++){
			if(GExe3P->CadPoint[i].x==0.0 && GExe3P->CadPoint[i].y==0.0)
				break;
			Numb++;
		}
		int	CadImagePoints[MaxRasterPointNumb][4];
		int	MinN=min((int)min(MaxRasterPointNumb
							 ,Numb)
					,(int)min(sizeof(GExe3P->CadPoint) /sizeof(GExe3P->CadPoint[0])
							 ,sizeof(GExe3P->ImagePoint)/sizeof(GExe3P->ImagePoint[0])));
		for(int i=0;i<MinN;i++){
			CadImagePoints[i][0]=GExe3P->CadPoint[i].x;
			CadImagePoints[i][1]=GExe3P->CadPoint[i].y;
			CadImagePoints[i][2]=GExe3P->ImagePoint[i].x;
			CadImagePoints[i][3]=GExe3P->ImagePoint[i].y;
		}
		TriangleAreaData.BuildTriangle(CadImagePoints,Numb);
		UndoElement<RasterInPage>	*UPointer=new UndoElement<RasterInPage>(this,&RasterInPage::UndoMovePoints);
		if(GetParamGlobal()->MaxUndoCount>0){
			int32	UndoNumb=0;
			for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
				RasterItemAbstract	*item=dynamic_cast<RasterItemAbstract *>(a);
				if(item!=NULL && item->GetFileLayerID()==GExe3P->FileLayerID){
					UndoNumb++;
				}
			}
			::Save(UPointer->GetWritePointer(),UndoNumb);
		}
		bool	FlagUndoBuff=true;
		for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
			RasterItemAbstract	*item=dynamic_cast<RasterItemAbstract *>(a);
			if(item!=NULL && item->GetFileLayerID()==GExe3P->FileLayerID){
				double	cx,cy;
				item->GetCenter(cx,cy);
				RasterTriangleArea	*t=TriangleAreaData.GetClosedTriangle((int)cx,(int)cy);
				if(t!=NULL){
					if(GetParamGlobal()->MaxUndoCount>0){
						if(FlagUndoBuff==true && ::Save(UPointer->GetWritePointer(),item->GetID())==false)
							FlagUndoBuff=false;
						if(FlagUndoBuff==true && item->Save(UPointer->GetWritePointer())==false)
							FlagUndoBuff=false;
					}
					item->TransformByParam(t->m);
				}
			}
		}
		GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);
		SetCurrentSize();
		return;			
	}
	MsgRasterCenterize	*MsgRasterCenterizeVar=dynamic_cast<MsgRasterCenterize *>(packet);
	if(MsgRasterCenterizeVar!=NULL){
		MsgRasterCenterizeVar->Ret=false;
		for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
			RasterItemAbstract	*item=dynamic_cast<RasterItemAbstract *>(a);
			if(item!=NULL){
				FlexArea	A=MsgRasterCenterizeVar->Area;
				//XYData	*XP=GetGlobalOutlineOffset();
				//if(XP!=NULL){
					//A.MoveToNoClip(XP->x,XP->y);
					if(item->IsCrossed(&A)==true){
						double	mx1,my1,mx2,my2;
						item->GetXY(mx1,my1,mx2,my2);
						MsgRasterCenterizeVar->x	=(mx1+mx2)/2;
						MsgRasterCenterizeVar->y	=(my1+my2)/2;
						MsgRasterCenterizeVar->Ret=true;
						break;
					}
				//}
			}
		}
		return;
	}
	GetCenterPacket	*GCenter=dynamic_cast<GetCenterPacket *>(packet);
	if(GCenter!=NULL){
		ImageBuffer *ImageList[10];
		if(GetLayersBase()->GetParamGlobal()->AllocateMasterBuff==true)
			GetMasterBuffList(ImageList);
		else if(GetLayersBase()->GetParamGlobal()->AllocateTargetBuff==true)
			GetTargetBuffList(ImageList);
		double	MaxD=0;
		int		MaxLayer=0;
		for(int layer=0;layer<GetLayerNumb();layer++){
			double	DAvr;
			double D=GCenter->Area.GetVar(0,0,*ImageList[layer],DAvr);
			if(MaxD<D){
				MaxD=D;
				MaxLayer=layer;
			}
		}
		int BrList[256];
		memset(BrList,0,sizeof(BrList));
		GCenter->Area.MakeBrightList(BrList ,GetDotPerLine(),GetMaxLines(),*ImageList[MaxLayer]);
		FlexArea PadArea;
		//GetPadFromImage(*ImageList[MaxLayer] ,GCenter->Area ,PadArea);
		PadArea.GetCenter(GCenter->LocalX,GCenter->LocalY);
		return;
	}
	MsgSaveConstruct	*MsgSaveConstructVar=dynamic_cast<MsgSaveConstruct *>(packet);
	if(MsgSaveConstructVar!=NULL){
		QBuffer	Buff;
		Buff.open(QIODevice::WriteOnly);
		if(FileLayerList	.Save(&Buff)==false)
			return;
		MsgSaveConstructVar->Data=Buff.buffer();
		return;
	}
	MsgLoadConstruct	*MsgLoadConstructVar=dynamic_cast<MsgLoadConstruct *>(packet);
	if(MsgLoadConstructVar!=NULL){
		QBuffer	Buff(&MsgLoadConstructVar->Data);
		Buff.open(QIODevice::ReadOnly);
		if(FileLayerList	.Load(&Buff)==false)
			return;
		bool	Error;
		BuildPointer(Error);
		MakeXY();
		return;
	}
	GUICmdAlgoPipeOut	*GUICmdMakeAlgoVar=dynamic_cast<GUICmdAlgoPipeOut *>(packet);
	if(GUICmdMakeAlgoVar!=NULL){
		MakeXY();
		MakeAlgo();
		return;
	}
	CmdReqRasterInfo	*CmdReqRasterInfoVar=dynamic_cast<CmdReqRasterInfo *>(packet);
	if(CmdReqRasterInfoVar!=NULL){
		int	LayerNo=0;
		for(BoolClass *d=CmdReqRasterInfoVar->DrawingLayers.GetFirst();d!=NULL;d=d->GetNext(),LayerNo++){
			if(d->GetValue()==true){
				RasterFileLayer	*FL=FileLayerList[LayerNo];
				if(FL!=NULL){
					AlgorithmItemPointerListContainer	Found;
					PickupItem(CmdReqRasterInfoVar->GlobalX,CmdReqRasterInfoVar->GlobalY,Found);
					for(AlgorithmItemPointerList *a=Found.GetFirst();a!=NULL;a=a->GetNext()){
						RasterItemAbstract	*item=dynamic_cast<RasterItemAbstract *>(a->GetItem());
						if(item!=NULL && item->GetFileLayerID()==FL->GetFileLayerID()){
							RasterInfo	*g=new RasterInfo();
							g->ItemID	=item->GetID();
							g->FileLayerID	=item->GetFileLayerID();
							g->TypeStr		=item->GetTypeStr();
							g->Message		=item->GetMessage();
							CmdReqRasterInfoVar->Answer.AppendList(g);
						}
					}
				}
			}
		}
		//RasterBase	*ABase=(RasterBase *)GetParentBase();
		return;
	}
	CmdRasterDraw	*CmdRasterDrawVar=dynamic_cast<CmdRasterDraw *>(packet);
	if(CmdRasterDrawVar!=NULL){
		UndoElement<RasterInPage>	*UPointer=new UndoElement<RasterInPage>(this,&RasterInPage::UndoRasterDraw);
		for(int	N=0;N<MaxRasterLayer;N++){
			RasterFileLayer	*f=FileLayerList[N];
			if(f==NULL)
				break;
			AlgorithmItemPointerListContainer	ItemList;
			if(CmdRasterDrawVar->ButtonsToShowLayer.GetItem(N)->GetValue()==true
			&& CmdRasterDrawVar->ButtonsToOperateLayer[N]==true){
				for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
					RasterItemAbstract	*item=dynamic_cast<RasterItemAbstract *>(a);
					if(item!=NULL && item->GetFileLayerID()==f->GetFileLayerID()){
						ItemList.Add(item);
					}
				}
				AlgorithmItemPointerListContainer CreatedItems;
				bool	Ret=MakePaintArea(CmdRasterDrawVar->GlobalX,CmdRasterDrawVar->GlobalY,ItemList,CreatedItems);
				if(Ret==true){
					if(GetParamGlobal()->MaxUndoCount>0){
						for(AlgorithmItemPointerList *a=CreatedItems.GetFirst();a!=NULL;a=a->GetNext()){
							int32	id=a->GetItem()->GetID();
							::Save(UPointer->GetWritePointer(),id);
						}
					}
				}
			}
		}
		FastSearchIDItemStart();
		GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);
		SetCurrentSize();
		return;
	}
	CmdDrawAllSelected	*CmdDrawAllSelectedVar=dynamic_cast<CmdDrawAllSelected *>(packet);
	if(CmdDrawAllSelectedVar!=NULL){
		UndoElement<RasterInPage>	*UPointer=new UndoElement<RasterInPage>(this,&RasterInPage::UndoDrawAllSelected);
		for(int	N=0;N<MaxRasterLayer;N++){
			RasterFileLayer	*f=FileLayerList[N];
			if(f==NULL)
				break;
			if(CmdDrawAllSelectedVar->ButtonsToOperateLayer[N]==true){
				AlgorithmItemPointerListContainer AddedItems;
				MakeDraw(f->GetFileLayerID(),AddedItems);

				int32	Count=AddedItems.GetCount();
				::Save(UPointer->GetWritePointer(),Count);
				for(AlgorithmItemPointerList *a=AddedItems.GetFirst();a!=NULL;a=a->GetNext()){
					AppendItem(a->GetItem());
					int32	id=a->GetItem()->GetID();
					::Save(UPointer->GetWritePointer(),id);
				}
			}
		}

		FastSearchIDItemStart();
		
		GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);
		SetCurrentSize();
		return;
	}
	CmdSelectLine	*CmdSelectLineVar=dynamic_cast<CmdSelectLine *>(packet);
	if(CmdSelectLineVar!=NULL){
		RasterFileLayer	*FL=FileLayerList.Find(CmdSelectLineVar->FileLayerID);
		if(FL!=NULL){
			for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
				RasterItemAbstract	*item=dynamic_cast<RasterItemAbstract *>(a);
				if(item!=NULL){
					if(item->GetFileLayerID()==FL->GetFileLayerID()){
						item->SetSelected(true);
					}
					else{
						item->SetSelected(false);
					}
				}
			}
		}
		return;
	}
	CmdRemoveLine	*CmdRemoveLineVar=dynamic_cast<CmdRemoveLine *>(packet);
	if(CmdRemoveLineVar!=NULL){
		RasterFileLayer	*FL=FileLayerList.GetItem(CmdRemoveLineVar->LineNo);
		if(FL!=NULL){
			UndoElement<RasterInPage>	*UPointer=new UndoElement<RasterInPage>(this,&RasterInPage::UndoRemoveLine);
			::Save(UPointer->GetWritePointer(),CmdRemoveLineVar->LineNo);
			int32	Count=0;
			for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
				RasterItemAbstract	*item=dynamic_cast<RasterItemAbstract *>(a);
				if(item!=NULL){
					if(item->GetFileLayerID()==FL->GetFileLayerID()){
						Count++;
					}
				}
			}
			::Save(UPointer->GetWritePointer(),Count);

			for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;){
				AlgorithmItemPI	*NextA=a->GetNext();
				RasterItemAbstract	*item=dynamic_cast<RasterItemAbstract *>(a);
				if(item!=NULL){
					if(item->GetFileLayerID()==FL->GetFileLayerID()){
						::Save(UPointer->GetWritePointer(),item->GetItemClassType());
						item->Save(UPointer->GetWritePointer());
						RemoveItem(item);
						delete	item;
					}
				}
				a=NextA;
			}
			FL->Save(UPointer->GetWritePointer());
			FileLayerList.RemoveList(FL);
			delete	FL;

			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);
			SetCurrentSize();
		}
		return;
	}
	CmdSwapNext	*CmdSwapNextVar=dynamic_cast<CmdSwapNext *>(packet);
	if(CmdSwapNextVar!=NULL){
		RasterFileLayer	*FL1=FileLayerList.GetItem(CmdSwapNextVar->LineNo);
		RasterFileLayer	*FL2=FileLayerList.GetItem(CmdSwapNextVar->LineNo+1);
		if(FL1!=NULL && FL2!=NULL){
			UndoElement<RasterInPage>	*UPointer=new UndoElement<RasterInPage>(this,&RasterInPage::UndoSwapNext);
			::Save(UPointer->GetWritePointer(),CmdSwapNextVar->LineNo);

			FileLayerList.RemoveList(FL1);
			FileLayerList.InsertLater(FL2,FL1);

			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);
			SetCurrentSize();
		}
		return;
	}
	CmdDuplicateLine	*DuplicateLineVar=dynamic_cast<CmdDuplicateLine *>(packet);
	if(DuplicateLineVar!=NULL){
		RasterFileLayer	*FL=FileLayerList.GetItem(DuplicateLineVar->LineNo);
		if(FL!=NULL){
			UndoElement<RasterInPage>	*UPointer=new UndoElement<RasterInPage>(this,&RasterInPage::UndoDuplicateLine);
			::Save(UPointer->GetWritePointer(),DuplicateLineVar->LineNo);

			AlgorithmItemPointerListContainer	TmpItems;

			for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
				RasterItemAbstract	*item=dynamic_cast<RasterItemAbstract *>(a);
				if(item!=NULL){
					if(item->GetFileLayerID()==FL->GetFileLayerID()){
						AlgorithmItemRoot		*b=CreateItem(a->GetItemClassType());
						RasterItemAbstract	*Dest=dynamic_cast<RasterItemAbstract *>(b);
						if(Dest!=NULL){
							QBuffer	Buff;
							Buff.open(QIODevice::ReadWrite);
							if(a->Save(&Buff)==false){
								delete	b;
								continue;
							}
							Buff.seek(0);
							if(Dest->Load(&Buff,GetLayersBase())==false){
								delete	b;
								continue;
							}
							TmpItems.Add(b);
						}
					}
				}
			}
			RasterFileLayer	*FLDest=new RasterFileLayer(&FileLayerList);
			QBuffer	Buff;
			Buff.open(QIODevice::ReadWrite);
			if(FL->Save(&Buff)==false){
				delete	FLDest;
				return;
			}
			Buff.seek(0);
			if(FLDest->Load(&Buff)==false){
				delete	FLDest;
				return;
			}
			int	MaxID=FileLayerList.GetMaxFileLayerID();
			FileLayerList.InsertLater(FL,FLDest);
			FLDest->SetFileLayerID(MaxID+1);

			int32	Count=TmpItems.GetCount();
			::Save(UPointer->GetWritePointer(),Count);

			for(AlgorithmItemPointerList *d=TmpItems.GetFirst();d!=NULL;d=d->GetNext()){
				RasterItemAbstract	*item=dynamic_cast<RasterItemAbstract *>(d->GetItem());
				if(item!=NULL){
					item->SetFileLayer(FLDest);
					item->BuildPointer(FileLayerList);
					AppendItem(item);

					item->MakeXY();
					item->SetCurrentSize();
					::Save(UPointer->GetWritePointer(),item->GetID());
				}
			}
			DuplicateLineVar	->FileLayerID=MaxID+1;

			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);
			SetCurrentSize();
		}
		return;
	}
	CmdAddEmptyLayer	*CmdAddEmptyLayerVar=dynamic_cast<CmdAddEmptyLayer *>(packet);
	if(CmdAddEmptyLayerVar!=NULL){
		RasterFileLayer	*FL=FileLayerList.GetItem(CmdAddEmptyLayerVar->LineNo);
		if(FL!=NULL){
			UndoElement<RasterInPage>	*UPointer=new UndoElement<RasterInPage>(this,&RasterInPage::UndoAddEmptyLayer);
			::Save(UPointer->GetWritePointer() ,CmdAddEmptyLayerVar->LineNo);

			AlgorithmItemPointerListContainer	TmpItems;

			RasterFileLayer	*FLDest=new RasterFileLayer(&FileLayerList);
			QBuffer	Buff;
			Buff.open(QIODevice::ReadWrite);
			if(FL->Save(&Buff)==false){
				delete	FLDest;
				delete	UPointer;
				return;
			}
			Buff.seek(0);
			if(FLDest->Load(&Buff)==false){
				delete	FLDest;
				delete	UPointer;
				return;
			}
			FLDest->FileName=/**/"Added Layer";

			int	MaxID=FileLayerList.GetMaxFileLayerID();
			FileLayerList.InsertLater(FL,FLDest);
			FLDest->SetFileLayerID(MaxID+1);

			::Save(UPointer->GetWritePointer(),FLDest->GetFileLayerID());

			CmdAddEmptyLayerVar	->FileLayerID=FLDest->GetFileLayerID();

			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);
		}
		return;
	}

	CmdCopyPageAllFrom	*CmdCopyPageAllFromVar=dynamic_cast<CmdCopyPageAllFrom *>(packet);
	if(CmdCopyPageAllFromVar!=NULL){
		FileLayerList	= CmdCopyPageAllFromVar->SourcePage->FileLayerList;

		//PageInfoForPartsData;

		for(AlgorithmItemPI *s=CmdCopyPageAllFromVar->SourcePage->GetFirstData();s!=NULL;s=s->GetNext()){
			RasterItemAbstract	*d=(RasterItemAbstract *)CreateItem(s->GetItemClassType());
			d->CopyFrom(s);
			int	FileLayerID	=((RasterItemAbstract *)s)->GetFileLayerID();
			RasterFileLayer	*f=FileLayerList.Find(FileLayerID);
			d->SetFileLayer(f);
			AppendItem(d);
			d->SetID(s->GetID());
		}
		FastSearchIDItemStart();

		bool	Error=true;
		BuildPointer(Error);
		MakeXY();
		return;
	}
	CmdSelectItemsRaster	*CmdSelectItemsRasterVar=dynamic_cast<CmdSelectItemsRaster *>(packet);
	if(CmdSelectItemsRasterVar!=NULL){
		for(int	N=0;N<MaxRasterLayer;N++){
			RasterFileLayer	*f=FileLayerList[N];
			if(f==NULL)
				break;
			if(CmdSelectItemsRasterVar->ButtonsToOperateLayer[N]==true){
				for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
					RasterItemAbstract	*item=dynamic_cast<RasterItemAbstract *>(a);
					if(item!=NULL && item->GetFileLayerID()==f->GetFileLayerID()){
						if(item->GetVisible()==true){
							if(item->IsCrossed(&CmdSelectItemsRasterVar->Area)==true){
								item->SetSelected(true);
							}
							else if(item->GetVector()!=NULL){
								if(item->GetVector()->CheckOverlap(CmdSelectItemsRasterVar->Area)==true){
									item->SetSelected(true);
								}
							}
						}
					}
				}
			}
		}
		return;
	}
	CmdRasterPickupByColor	*CmdRasterPickupByColorVar=dynamic_cast<CmdRasterPickupByColor *>(packet);
	if(CmdRasterPickupByColorVar!=NULL){
		int	MaxElementID=0;
		for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
			RasterPDFItem	*item=dynamic_cast<RasterPDFItem *>(a);
			if(item!=NULL && item->GetFileLayerID()==CmdRasterPickupByColorVar->FileLayerID){
				MaxElementID=max(MaxElementID,item->GetMaxElementID());
			}
		}
		MaxElementID++;
		for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
			RasterPDFItem	*item=dynamic_cast<RasterPDFItem *>(a);
			if(item!=NULL && item->GetFileLayerID()==CmdRasterPickupByColorVar->FileLayerID){
				item->PickupAddElements(MaxElementID
							,LocalPickupArea
							,CmdRasterPickupByColorVar->LocalX,CmdRasterPickupByColorVar->LocalY
							,CmdRasterPickupByColorVar->ShrinkDot
							,CmdRasterPickupByColorVar->InsideEdgeWidth
							,CmdRasterPickupByColorVar->OutsideEdgeWidth
							,CmdRasterPickupByColorVar->AllocatedStaticLib
							,CmdRasterPickupByColorVar->AllocatedInsideEdgeLib
							,CmdRasterPickupByColorVar->AllocatedOutsideEdgeLib);

			}
		}
		return;
	}
	CmdRasterPickupByColorArea	*CmdRasterPickupByColorAreaVar=dynamic_cast<CmdRasterPickupByColorArea *>(packet);
	if(CmdRasterPickupByColorAreaVar!=NULL){
		int	MaxElementID=0;
		for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
			RasterPDFItem	*item=dynamic_cast<RasterPDFItem *>(a);
			if(item!=NULL && item->GetFileLayerID()==CmdRasterPickupByColorAreaVar->FileLayerID){
				MaxElementID=max(MaxElementID,item->GetMaxElementID());
			}
		}
		MaxElementID++;
		for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
			RasterPDFItem	*item=dynamic_cast<RasterPDFItem *>(a);
			if(item!=NULL && item->GetFileLayerID()==CmdRasterPickupByColorAreaVar->FileLayerID){
				item->PickupAddElements(MaxElementID
							,LocalPickupArea
							,CmdRasterPickupByColorAreaVar->LocalColorArea
							,CmdRasterPickupByColorAreaVar->ShrinkDot
							,CmdRasterPickupByColorAreaVar->InsideEdgeWidth
							,CmdRasterPickupByColorAreaVar->OutsideEdgeWidth
							,CmdRasterPickupByColorAreaVar->AllocatedStaticLib
							,CmdRasterPickupByColorAreaVar->AllocatedInsideEdgeLib
							,CmdRasterPickupByColorAreaVar->AllocatedOutsideEdgeLib);
			}
		}
		return;
	}
	ReqRasterElements	*ReqRasterElementsVar=dynamic_cast<ReqRasterElements *>(packet);
	if(ReqRasterElementsVar!=NULL){
		for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
			RasterItemAbstract	*item=dynamic_cast<RasterItemAbstract *>(a);
			if(item!=NULL && item->GetFileLayerID()==ReqRasterElementsVar->FileLayerID){
				item->MakeElementList(ReqRasterElementsVar->Elements);
			}
		}
		return;
	}
	CmdReqRasterElementData	*CmdReqRasterElementDataVar=dynamic_cast<CmdReqRasterElementData *>(packet);
	if(CmdReqRasterElementDataVar!=NULL){
		CmdReqRasterElementDataVar->Found=false;
		for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
			if(a->GetID()==CmdReqRasterElementDataVar->ItemID){
				RasterItemAbstract	*item=dynamic_cast<RasterItemAbstract *>(a);
				for(RasterAreaElement *e=item->Elements.GetFirst();e!=NULL;e=e->GetNext()){
					if(e->ElementID==CmdReqRasterElementDataVar->ElementID){
						CmdReqRasterElementDataVar->ShrinkDot				=e->ShrinkDot;
						CmdReqRasterElementDataVar->InsideEdgeWidth			=e->InsideEdgeWidth			;
						CmdReqRasterElementDataVar->OutsideEdgeWidth		=e->OutsideEdgeWidth		;
						CmdReqRasterElementDataVar->AllocatedStaticLib		=e->AllocatedStaticLib		;
						CmdReqRasterElementDataVar->AllocatedInsideEdgeLib	=e->AllocatedInsideEdgeLib	;
						CmdReqRasterElementDataVar->AllocatedOutsideEdgeLib	=e->AllocatedOutsideEdgeLib	;

						CmdReqRasterElementDataVar->Found=true;
						break;
					}
				}
				break;
			}
		}
		return;
	}
	CmdSetRasterElementData	*CmdSetRasterElementDataVar=dynamic_cast<CmdSetRasterElementData *>(packet);
	if(CmdSetRasterElementDataVar!=NULL){
		if(CmdSetRasterElementDataVar->DeleteMode==false){
			for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
				if(a->GetID()==CmdSetRasterElementDataVar->ItemID){
					RasterItemAbstract	*item=dynamic_cast<RasterItemAbstract *>(a);
					item->UpdateElement(CmdSetRasterElementDataVar->ElementID
										,CmdSetRasterElementDataVar->ShrinkDot 
										,CmdSetRasterElementDataVar->InsideEdgeWidth	 
										,CmdSetRasterElementDataVar->OutsideEdgeWidth 
										,CmdSetRasterElementDataVar->AllocatedStaticLib		
										,CmdSetRasterElementDataVar->AllocatedInsideEdgeLib	
										,CmdSetRasterElementDataVar->AllocatedOutsideEdgeLib);
				}
			}
		}
		else{
			for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
				if(a->GetID()==CmdSetRasterElementDataVar->ItemID){
					RasterItemAbstract	*item=dynamic_cast<RasterItemAbstract *>(a);
					for(RasterAreaElement *e=item->Elements.GetFirst();e!=NULL;){
						if(e->ElementID==CmdSetRasterElementDataVar->ElementID){
							RasterAreaElement *NextE=e->GetNext();
							item->Elements.RemoveList(e);
							delete	e;
							e=NextE;
						}
						else{
							e=e->GetNext();
						}
					}
				}
			}
		}
		return;
	}
	CmdReqRefreshLines	*CmdReqRefreshLinesVar=dynamic_cast<CmdReqRefreshLines *>(packet);
	if(CmdReqRefreshLinesVar!=NULL){
		RefreshFileLayerList();
		for(RasterFileLayer *R=FileLayerList.GetFirst();R!=NULL;R=R->GetNext()){
			RasterFileLayerList	*r=new RasterFileLayerList();
			r->FileName=R->FileName;
			r->FileLayerID	=R->FileLayerID;
			CmdReqRefreshLinesVar->FileLayerListContainer->AppendList(r);
		}
		return;
	}
	CmdPickRasterColor	*CmdPickRasterColorVar=dynamic_cast<CmdPickRasterColor *>(packet);
	if(CmdPickRasterColorVar!=NULL){
		for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
			RasterItemAbstract	*item=dynamic_cast<RasterItemAbstract *>(a);
			if(item->GetFileLayerID()==CmdPickRasterColorVar->FileLayerID){
				CmdPickRasterColorVar->Color=item->PickColor(CmdPickRasterColorVar->LocalX
															,CmdPickRasterColorVar->LocalY);
			}
		}
		return;
	}
	CmdRasterDrawArea	*CmdRasterDrawAreaVar=dynamic_cast<CmdRasterDrawArea *>(packet);
	if(CmdRasterDrawAreaVar!=NULL){
		for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
			RasterItemAbstract	*item=dynamic_cast<RasterItemAbstract *>(a);
			if(item->GetFileLayerID()==CmdRasterDrawAreaVar->FileLayerID){
				item->DrawShape(CmdRasterDrawAreaVar->Area,CmdRasterDrawAreaVar->Color);
			}
		}
		return;
	}
	CmdRasterMakeImage	*CmdRasterMakeImageVar=dynamic_cast<CmdRasterMakeImage *>(packet);
	if(CmdRasterMakeImageVar!=NULL){
		MakeImage	(CmdRasterMakeImageVar->DestBuff);
		return;
	}
	CmdMoveElement	*CmdMoveElementVar=dynamic_cast<CmdMoveElement *>(packet);
	if(CmdMoveElementVar!=NULL){
		for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
			//if(a->GetID()==CmdMoveElementVar->ItemID){
			RasterItemAbstract	*item=dynamic_cast<RasterItemAbstract *>(a);
			for(RasterAreaElement *e=item->Elements.GetFirst();e!=NULL;e=e->GetNext()){
				if(e->ElementID==CmdMoveElementVar->ElementID){
					e->Move(CmdMoveElementVar->MovX,CmdMoveElementVar->MovY);
				}
			}
		}
		return;
	}
	CmdPickRasterColorProfile	*CmdPickRasterColorProfileVar=dynamic_cast<CmdPickRasterColorProfile *>(packet);
	if(CmdPickRasterColorProfileVar!=NULL){
		ImagePointerContainer	Images;
		GetMasterImages(Images);
		int	MArea=2;
		QColor	ImageColor;
		if(MArea<=(CmdPickRasterColorProfileVar->LocalX) && CmdPickRasterColorProfileVar->LocalX<(GetDotPerLine()-MArea-1)
		&& MArea<=(CmdPickRasterColorProfileVar->LocalY) && CmdPickRasterColorProfileVar->LocalY<(GetMaxLines(  )-MArea-1)){
			int	tRed	=0;
			int	tGreen	=0;
			int tBlue	=0;	
			int	Numb=0;
			for(int y=-MArea;y<=MArea;y++){
				for(int x=-MArea;x<=MArea;x++){
					QColor	c=Images.GetColor(CmdPickRasterColorProfileVar->LocalX+x,CmdPickRasterColorProfileVar->LocalY+y);
					tRed	+=c.red();
					tGreen	+=c.green();
					tBlue	+=c.blue();
					Numb++;
				}
			}
			ImageColor=QColor(tRed/Numb,tGreen/Numb,tBlue/Numb);
		}
		QColor	RasterColor;
		for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
			//if(a->GetID()==CmdMoveElementVar->ItemID){
			RasterItemAbstract	*item=dynamic_cast<RasterItemAbstract *>(a);
			
			int	tRed	=0;
			int	tGreen	=0;
			int tBlue	=0;	
			int	Numb=0;
			for(int y=-MArea;y<=MArea;y++){
				for(int x=-MArea;x<=MArea;x++){
					QColor	c=item->PickColor(CmdPickRasterColorProfileVar->LocalX+x,CmdPickRasterColorProfileVar->LocalY+y);
					tRed	+=c.red();
					tGreen	+=c.green();
					tBlue	+=c.blue();
					Numb++;
				}
			}
			RasterColor=QColor(tRed/Numb,tGreen/Numb,tBlue/Numb);
			break;
		}
		RasterBase	*ABase=(RasterBase	*)GetParentBase();
		ColorProfile	*L1=ABase->ColorProfiles.GetClosedSrcColor(ImageColor);
		if(L1==NULL){
			ColorProfile	*C=new ColorProfile(ImageColor,RasterColor);
			ABase->ColorProfiles.AppendList(C);
			return;
		}
		//if(GetColorDistancce(L1->SrcColor,ImageColor)<3){
		//	return;
		//}
		ColorProfile	*L2=ABase->ColorProfiles.GetClosedDstColor(RasterColor);
		if(L2==NULL){
			ColorProfile	*C=new ColorProfile(ImageColor,RasterColor);
			ABase->ColorProfiles.AppendList(C);
			return;
		}
		if(GetColorDistancce(L2->DstColor,RasterColor)<3){
			return;
		}
		ColorProfile	*C=new ColorProfile(ImageColor,RasterColor);
		ABase->ColorProfiles.AppendList(C);
		return;
	}
	CmdConvertColorProfiles	*CmdConvertColorProfilesVar=dynamic_cast<CmdConvertColorProfiles *>(packet);
	if(CmdConvertColorProfilesVar!=NULL){
		//for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
		//	//if(a->GetID()==CmdMoveElementVar->ItemID){
		//	RasterItemAbstract	*Item=dynamic_cast<RasterItemAbstract *>(a);
		//	if(Item!=NULL){
		//		QImage	RImage(GetDotPerLine(),GetMaxLines(),QImage::Format_RGB32);
		//
		//		const QColor Color;
		//		Item->DrawBase	(0,0,RImage, 0,0 ,1.0,Color);
		//
		//		ImagePointerContainer	Images;
		//		GetMasterImages(Images);
		//		ConvertImageW(RImage ,Images,Item->RasterMaskList);
		//		break;
		//	}
		//}
		RasterBase	*ABase=(RasterBase	*)GetParentBase();
		for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
			//if(a->GetID()==CmdMoveElementVar->ItemID){
			RasterItemAbstract	*Item=dynamic_cast<RasterItemAbstract *>(a);
			if(Item!=NULL){
				QImage	RImage(GetDotPerLine(),GetMaxLines(),QImage::Format_RGB32);
				Item->MakeQImage(&RImage, 0,0);

				ImagePointerContainer	MasterImages;
				GetMasterImages(MasterImages);
				CopyRasterToImageByProfile(RImage
												,MasterImages 
												,ABase->ColorProfiles);
				MasterImages.SetChanged(true);
			}
		}
		GetLayersBase()->SetChangedMasterImage(0,GetPage(),0);
		return;
	}
	CmdSetPartialArea	*CmdSetPartialAreaVar=dynamic_cast<CmdSetPartialArea *>(packet);
	if(CmdSetPartialAreaVar!=NULL){
	}
	CmdAddRasterMaskArea	*CmdAddRasterMaskAreaVar=dynamic_cast<CmdAddRasterMaskArea *>(packet);
	if(CmdAddRasterMaskAreaVar!=NULL){
		for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
			//if(a->GetID()==CmdMoveElementVar->ItemID){
			RasterItemAbstract	*Item=dynamic_cast<RasterItemAbstract *>(a);
			if(Item!=NULL){
				if(Item->GetFileLayerID()==CmdAddRasterMaskAreaVar->FileLayerID){
					Item->AddMaskArea(CmdAddRasterMaskAreaVar->MaskArea);
				}
			}
		}
		return;
	}
	CmdDelRasterMaskArea	*CmdDelRasterMaskAreaVar=dynamic_cast<CmdDelRasterMaskArea *>(packet);
	if(CmdDelRasterMaskAreaVar!=NULL){
		for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
			//if(a->GetID()==CmdMoveElementVar->ItemID){
			RasterItemAbstract	*Item=dynamic_cast<RasterItemAbstract *>(a);
			if(Item!=NULL){
				if(Item->GetFileLayerID()==CmdDelRasterMaskAreaVar->FileLayerID){
					Item->DelMaskArea(CmdDelRasterMaskAreaVar->MaskID);
				}
			}
		}
		return;
	}
	CmdReqEnumMaskArea	*CmdReqEnumMaskAreaVar=dynamic_cast<CmdReqEnumMaskArea *>(packet);
	if(CmdReqEnumMaskAreaVar!=NULL){
		CmdReqEnumMaskAreaVar->MaskIDList.RemoveAll();
		for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
			//if(a->GetID()==CmdMoveElementVar->ItemID){
			RasterItemAbstract	*Item=dynamic_cast<RasterItemAbstract *>(a);
			if(Item!=NULL){
				if(Item->GetFileLayerID()==CmdReqEnumMaskAreaVar->FileLayerID){
					for(RasterMask *a=Item->RasterMaskList.GetFirst();a!=NULL;a=a->GetNext()){
						CmdReqEnumMaskAreaVar->MaskIDList.Add(a->MaskID);
					}
				}
			}
		}
		return;
	}
	CmdReqRasterTransformInfo	*CmdReqRasterTransformInfoVar=dynamic_cast<CmdReqRasterTransformInfo *>(packet);
	if(CmdReqRasterTransformInfoVar!=NULL){
		for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
			//if(a->GetID()==CmdMoveElementVar->ItemID){
			RasterItemAbstract	*Item=dynamic_cast<RasterItemAbstract *>(a);
			if(Item!=NULL){
				QBuffer	Buff;
				if(Buff.open(QIODevice::WriteOnly)==true){
					Item->SaveTransformParam(&Buff);
					CmdReqRasterTransformInfoVar->TransformData=Buff.buffer();
				}
				break;
			}
		}
		return;
	}
	CmdSetRasterTransformInfo	*CmdSetRasterTransformInfoVar=dynamic_cast<CmdSetRasterTransformInfo *>(packet);
	if(CmdSetRasterTransformInfoVar!=NULL){
		for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
			//if(a->GetID()==CmdMoveElementVar->ItemID){
			RasterItemAbstract	*Item=dynamic_cast<RasterItemAbstract *>(a);
			if(Item!=NULL){
				QBuffer	Buff(&CmdSetRasterTransformInfoVar->TransformData);
				if(Buff.open(QIODevice::ReadOnly)==true){
					Item->LoadTransformParam(&Buff);
				}
			}
		}
		MakeXY();
		SetCurrentSize();
		RasterBase	*ABase=(RasterBase	*)GetParentBase();
		for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
			//if(a->GetID()==CmdMoveElementVar->ItemID){
			RasterItemAbstract	*Item=dynamic_cast<RasterItemAbstract *>(a);
			if(Item!=NULL){
				QImage	RImage(GetDotPerLine(),GetMaxLines(),QImage::Format_RGB32);
				Item->MakeQImage(&RImage, 0,0);

				ImagePointerContainer	MasterImages;
				GetMasterImages(MasterImages);
				CopyRasterToImageByProfile(RImage
												,MasterImages 
												,ABase->ColorProfiles);
			}
		}
		GetLayersBase()->SetChangedMasterImage(0,GetPage(),0);
		return;
	}
	CmdReqRasterProfileValue	*CmdReqRasterProfileValueVar=dynamic_cast<CmdReqRasterProfileValue *>(packet);
	if(CmdReqRasterProfileValueVar!=NULL){
		RasterBase	*ABase=(RasterBase	*)GetParentBase();
		for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
			//if(a->GetID()==CmdMoveElementVar->ItemID){
			RasterItemAbstract	*Item=dynamic_cast<RasterItemAbstract *>(a);
			if(Item!=NULL){
				QColor	Col=Item->PickColor(CmdReqRasterProfileValueVar->LocalX,CmdReqRasterProfileValueVar->LocalY);
				if(Col!=Qt::black){
					CmdReqRasterProfileValueVar->PDFColor=Col;
					QColor	PCol=ABase->ColorProfiles.AssignToSrcBy4(Col);
					QRgb	CCol=ABase->ColorProfiles.GetColor(Col.rgb());
					CmdReqRasterProfileValueVar->ConvertedImageColor=QColor(CCol);
					break;
				}
			}
		}
		return;
	}
	CmdReqMakeProfileByImage	*CmdReqMakeProfileByImageVar=dynamic_cast<CmdReqMakeProfileByImage *>(packet);
	if(CmdReqMakeProfileByImageVar!=NULL){
		MakeProfileByImage(CmdReqMakeProfileByImageVar->Mastered);
		RasterBase	*ABase=(RasterBase	*)GetParentBase();
		ABase->ColorProfiles.MakeTable();
		return;
	}
	CmdMakeRasterReferenceItem	*CmdMakeRasterReferenceItemVar=dynamic_cast<CmdMakeRasterReferenceItem *>(packet);
	if(CmdMakeRasterReferenceItemVar!=NULL){
		RasterReferenceItem	*Item=new RasterReferenceItem();
		Item->SetArea(CmdMakeRasterReferenceItemVar->LocalArea);
		AppendItem(Item);
		return;
	}
	CmdReqRasterReference	*CmdReqRasterReferenceVar=dynamic_cast<CmdReqRasterReference *>(packet);
	if(CmdReqRasterReferenceVar!=NULL){
		//RasterBase	*ABase=(RasterBase	*)GetParentBase();
		for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
			RasterReferenceItem	*Item=dynamic_cast<RasterReferenceItem *>(a);
			if(Item!=NULL){
				QColor	PDFColor;
				QColor	ImgColor;
				if(Item->GetReferenceColor(PDFColor,ImgColor)==true){
					CmdReqRasterReferenceVar->ColorProfile.MergeBySource(PDFColor,ImgColor);
				}
			}
		}
		return;
	}
	CmdMakeAutoRasterReference	*CmdMakeAutoRasterReferenceVar=dynamic_cast<CmdMakeAutoRasterReference *>(packet);
	if(CmdMakeAutoRasterReferenceVar!=NULL){
		ConstMapBufferListContainer MaskBuff;
		if(GetReflectionMap(_Reflection_Mask,MaskBuff)==true){
			int	XByte	=(GetDotPerLine()+7)/8;
			int	YLen	=GetMaxLines();
			BYTE	**MaskMap=MakeMatrixBuff(XByte,YLen);
			ConstMapBuffer Map;
			MaskBuff.BindOr(Map);
			MatrixBuffCopy	(MaskMap,XByte,YLen
							,Map.GetBitMap() ,XByte,YLen);

			for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
				RasterReferenceItem	*Item=dynamic_cast<RasterReferenceItem *>(a);
				if(Item!=NULL){
					Item->GetArea().MakeNotBitData(MaskMap ,GetDotPerLine() ,YLen);
				}
			}

			for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
				RasterPDFItem	*Item=dynamic_cast<RasterPDFItem *>(a);
				if(Item!=NULL){
					Item->MakeAutoRasterReference(MaskMap,XByte,YLen
												,CmdMakeAutoRasterReferenceVar->ColorMergin 
												,CmdMakeAutoRasterReferenceVar->MinItemArea
												,CmdMakeAutoRasterReferenceVar->ShrinkSize);
				}
			}
			DeleteMatrixBuff(MaskMap,YLen);
		}
		return;
	}
}
