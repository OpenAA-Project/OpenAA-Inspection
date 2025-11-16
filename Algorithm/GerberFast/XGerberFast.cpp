#include "XGerberFastResource.h"
#include "GerberFast.h"
#include "XGerberAperture.h"
#include "XGerberFast.h"
#include "XGeneralFunc.h"
#include "string.h"
#include "XFlexArea.h"
#include "swap.h"
#include "XGerberFastPacket.h"
#include "XGeneralFunc.h"
#include "XDisplayBitImage.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include "XGUIGerberPacket.h"
#include "XPickupPad.h"
#include "XUndo.h"
#include "XCrossObj.h"
#include <omp.h>
#include "XPropertyGerberFastCommon.h"
#include <float.h>
#include "XBitImageProcessor.h"

extern	QColor	NegaColor;

//======================================================================
GerberFastThreshold::GerberFastThreshold(GerberFastItemBase *parent)
		:AlgorithmThreshold(parent)
{}

void	GerberFastClusterItemContainer::BuildPointerInArea(void)
{
	for(int yn=0;yn<YDivClusterNumb;yn++){
		for(int xn=0;xn<XDivClusterNumb;xn++){
			PointerInArea[xn][yn].RemoveAll();
		}
	}

	XDivClusterLen	=(Parent->GetDotPerLine()+XDivClusterNumb-1)/XDivClusterNumb;
	YDivClusterLen	=(Parent->GetMaxLines  ()+YDivClusterNumb-1)/YDivClusterNumb;

	for(GerberFastClusterItemList *a=GetFirst();a!=NULL;a=a->GetNext()){
		int	kx1=max(a->Area.GetMinX()/XDivClusterLen,0);
		int	ky1=max(a->Area.GetMinY()/YDivClusterLen,0);
		int	kx2=ceil(((double)a->Area.GetMaxX())/XDivClusterLen);
		int	ky2=ceil(((double)a->Area.GetMaxY())/YDivClusterLen);
		for(int yn=ky1;yn<=ky2 && yn<YDivClusterNumb;yn++){
			for(int xn=kx1;xn<=kx2 && xn<XDivClusterNumb;xn++){
				PointerInArea[xn][yn].AppendList(new GerberFastClusterItemPointer(a));
			}
		}
	}
}

//======================================================================

GerberFastInPage::GerberFastInPage(AlgorithmBase *parent)
	:AlgorithmInPagePI(parent)
	,AutoInterpolation(this),FileLayerList(this)
	,AutoLikeManualData(this)
	,MatchAlignmentArea1(this)
	,MatchAlignmentArea2(this)
	,MatchAlignmentArea3(this)
	,ClusterItemContainer(this)
{
	ImagingBmp		=NULL;
	ImagingBmpXByte	=0;
	ImagingBmpYLen	=0;

	ABoxXNum=0;
	ABoxYNum=0;

	MoveMode		=false;
	RotateMode		=false;
	ExtendMode		=false;
	SlopeXMode		=false;
	SlopeYMode		=false;
	AlignmentMode	=false;
	AutoMatchingMode=false;
	Mode	=DisplayImage::_Normal;
	LastPosX=LastPosY							=0;
	MoveStartPosX		=MoveStartPosY			=0;
	RotateCenterXOnData	=RotateCenterYOnData	=0;
	RotateFirstX		=RotateFirstY			=0;
	RotateAngle									=0;
	ExtendCenterXOnData	=ExtendCenterYOnData	=0;
	ExtendFirstX		=ExtendFirstY			=0;
	SlopeXCenterXOnData	=SlopeXCenterYOnData	=0;
	SlopeXFirstX		=SlopeXFirstY			=0;
	SlopeXAngle									=0;
	SlopeYCenterXOnData	=SlopeYCenterYOnData	=0;
	SlopeYFirstX		=SlopeYFirstY			=0;
	SlopeYAngle									=0;

	AccessDimXLen	=0;
	AccessDimYLen	=0;
}
GerberFastInPage::~GerberFastInPage(void)
{
	if(ImagingBmp!=NULL)
		DeleteMatrixBuff(ImagingBmp,ImagingBmpYLen);
	ImagingBmp=NULL;
	ImagingBmpXByte=0;
	ImagingBmpYLen=0;

}

void	GerberFastInPage::CreateImagingBmpBuff(void)
{
	if(ImagingBmp!=NULL && (ImagingBmpYLen!=GetMaxLines()) && (ImagingBmpXByte!=(GetDotPerLine()+7)/8)){
		DeleteMatrixBuff(ImagingBmp,ImagingBmpYLen);
		ImagingBmp=NULL;
		ImagingBmpYLen=0;
	}
	if(ImagingBmp==NULL){
		ImagingBmpYLen=GetMaxLines();
		ImagingBmpXByte=(GetDotPerLine()+7)/8;
		ImagingBmp=MakeMatrixBuff(ImagingBmpXByte ,ImagingBmpYLen);
	}
	MatrixBuffClear(ImagingBmp ,0,ImagingBmpXByte ,ImagingBmpYLen);
	ClusterItemContainer.RemoveAll();
}

AlgorithmItemRoot		*GerberFastInPage::CreateItem(int ItemClassType)
{
	GerberFastItemBase	*a=NULL;
	switch(ItemClassType){
		case 1:
			a=new GerberFastItemFlash();
			break;
		case 2:
			a=new GerberFastItemLine();
			break;
		case 3:
			a=new GerberFastItemArc();
			break;
		case 4:
			a=new GerberFastItemPolygon();
			break;
		case 5:
			a=new GerberFastItemComposite();
			break;
	}
	if(a!=NULL){
		a->SetParent(this);
	}
	return a;
}

int	DbgCounterInGerber;
int	DbgValueInGerber;

void	GerberFastInPage::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdLoadGerber	*CmdLoadGerberVar=dynamic_cast<CmdLoadGerber *>(packet);
	if(CmdLoadGerberVar!=NULL){
		GerberFileLayer	*f=FileLayerList.Find(CmdLoadGerberVar->FileLayerID);
		if(f==NULL){
			f=new GerberFileLayer(&FileLayerList);
			f->FileLayerID	=CmdLoadGerberVar->FileLayerID;
			f->FileName	=CmdLoadGerberVar->FileName;
			FileLayerList.AppendList(f);
		}

		QTemporaryFile *F=new QTemporaryFile();
		F->setAutoRemove(false);
		if(F->open()==false)
			return;
		F->write(*CmdLoadGerberVar->pData);
		QString	TempFileName=F->fileName().replace(/**/"\\",/**/"/");
		delete	F;

#ifdef _MSC_VER
		wchar_t	*tmpFileName=new wchar_t	[1000];
		memset(tmpFileName,0,sizeof(wchar_t)*1000);
		TempFileName.toWCharArray(tmpFileName);
		FILE	*file=_wfopen(tmpFileName,/**/L"rt");
#else
		QByteArray	tmpFileNameUTF8=TempFileName.toUtf8();
		FILE	*file=fopen(tmpFileNameUTF8.data(),/**/"rt");
#endif
		if(file!=NULL){
			int	LineNumber;
			GerberFastBase	*ABase=(GerberFastBase *)GetParentBase();
			if(f->LoadGerberData(ABase,file,false)==true){
				CmdLoadGerberVar->Ret=true;
			}
			else{
				fseek(file,0,SEEK_SET);
				if(f->LoadNCData(ABase,file,false)==true){
					CmdLoadGerberVar->Ret=true;
				}
				else{
					if(f->FileName.right(2)==QString(".Z")){
						QString	ZFileName=ABase->UnzipInTemp(TempFileName).replace(/**/"\\",/**/"/");

#ifdef _MSC_VER
						memset(tmpFileName,0,sizeof(wchar_t)*1000);
						ZFileName.toWCharArray(tmpFileName);
						FILE	*file=_wfopen(tmpFileName,/**/L"rt");
#else
						QByteArray	tmpFileNameUTF8=ZFileName.toUtf8();
						FILE	*file=fopen(tmpFileNameUTF8.data(),/**/"rt");
#endif
						if(file!=NULL){	
							if(f->LoadODBPP(ABase,file,LineNumber)==true){
								CmdLoadGerberVar->Ret=true;
							}
							else{
								CmdLoadGerberVar->Ret=false;
							}
							fclose(file);
#ifdef _MSC_VER
							::_wremove(tmpFileName);
#else
							::remove(tmpFileNameUTF8.data());
#endif

						}
						else{
							CmdLoadGerberVar->Ret=false;
						}
					}
					else{
						fseek(file,0,SEEK_SET);
						if(f->LoadODBPP(ABase,file,LineNumber)==true){
							CmdLoadGerberVar->Ret=true;
						}
						else{
							CmdLoadGerberVar->Ret=false;
						}
					}
				}
			}
			fclose(file);
		}
		MakeXY();
#ifdef _MSC_VER
		::_wremove(tmpFileName);
#else
		::remove(tmpFileNameUTF8.data());
#endif
		SetCurrentSize();
		bool	Error=false;
#ifdef _MSC_VER
		delete	[]tmpFileName;
#endif
		BuildPointer(Error);
		//BuildShapeToArea();
		return;
	}
	CmdSetDrawAttr	*CmdSetDrawAttrVar=dynamic_cast<CmdSetDrawAttr *>(packet);
	if(CmdSetDrawAttrVar!=NULL){
		SetFileLayerVisible(CmdSetDrawAttrVar->ShownFileID,CmdSetDrawAttrVar->ShownCompositeID);
		return;
	}
	CmdReqGerberArea	*CmdReqGerberAreaVar=dynamic_cast<CmdReqGerberArea *>(packet);
	if(CmdReqGerberAreaVar!=NULL){
		static	int	DbgIn=0;
		CmdReqGerberAreaVar->MinX=DBL_MAX;
		CmdReqGerberAreaVar->MinY=DBL_MAX;
		CmdReqGerberAreaVar->MaxX=-DBL_MAX;
		CmdReqGerberAreaVar->MaxY=-DBL_MAX;
		for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
			GerberFastItemBase	*item=dynamic_cast<GerberFastItemBase *>(a);
			if(item!=NULL){
				double	x1,y1,x2,y2;
				item->GetXY(x1,y1,x2,y2);
				if(-5<x1 && x1<0){
					item->MakeXY();
					DbgIn++;
				}
				CmdReqGerberAreaVar->MinX=min(CmdReqGerberAreaVar->MinX,x1);
				CmdReqGerberAreaVar->MinY=min(CmdReqGerberAreaVar->MinY,y1);
				CmdReqGerberAreaVar->MaxX=max(CmdReqGerberAreaVar->MaxX,x2);
				CmdReqGerberAreaVar->MaxY=max(CmdReqGerberAreaVar->MaxY,y2);
			}
		}
		return;
	}
	CmdRegulateGerberArea	*CmdRegulateGerberAreaVar=dynamic_cast<CmdRegulateGerberArea *>(packet);
	if(CmdRegulateGerberAreaVar!=NULL){
		for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
			GerberFastItemBase	*item=static_cast<GerberFastItemBase *>(a);
			if(item!=NULL){
				item->RegulatePos(CmdRegulateGerberAreaVar->MinX,CmdRegulateGerberAreaVar->MinY
								, CmdRegulateGerberAreaVar->MaxX,CmdRegulateGerberAreaVar->MaxY);
			}
		}
		SetCurrentSize();
		return;
	}
	CmdClearGerber	*CmdClearGerberVar=dynamic_cast<CmdClearGerber *>(packet);
	if(CmdClearGerberVar!=NULL){
		FileLayerList		.RemoveAll();
		TriangleAreaData	.RemoveAll();
		AutoInterpolation	.RemoveAll();
		AutoLikeManualData	.Clear();
		GerberFastItemPointerContainerContainerList.RemoveAll();
		MatchAlignmentArea1	.RemoveAll();
		MatchAlignmentArea2	.RemoveAll();
		MatchAlignmentArea3	.RemoveAll();
		RemoveAllDatas();
		for(int i=0;i<10;i++){
			for(int j=0;j<10;j++){
				ABox[i][j].Clear();
			}
		}
		for(int x=0;x<AccessDimNumbX;x++){
			for(int y=0;y<AccessDimNumbY;y++){
				AccessDim[x][y].RemoveAll();
			}
		}
		SparsContainerData	.RemoveAll();
		CenterLines			.RemoveAll();
		ClusterItemContainer.RemoveAll();
		RemoveAllDatas();	//Remove all items
		GerberFastBase	*ABase=(GerberFastBase *)GetParentBase();
		//ABase->FileLayerList.RemoveAll();
		return;
	}

	CmdMove	*CmdMoveVar=dynamic_cast<CmdMove *>(packet);
	if(CmdMoveVar!=NULL){
		UndoElement<GerberFastInPage>	*UPointer=new UndoElement<GerberFastInPage>(this,&GerberFastInPage::UndoMove);
		if(GetParamGlobal()->MaxUndoCount>0){
			int32	Numb=0;
			for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
				if(a->GetSelected()==true && a->GetEditLocked()==false  && a->GetVisible()==true){
					GerberFastItemBase	*item=static_cast<GerberFastItemBase *>(a);
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
				GerberFastItemBase	*item=static_cast<GerberFastItemBase *>(a);
				if(item!=NULL){
					if(GetParamGlobal()->MaxUndoCount>0){
						if(FlagUndoBuff==true && ::Save(UPointer->GetWritePointer(),item->GetID())==false)
							FlagUndoBuff=false;
						if(FlagUndoBuff==true && item->SaveOnlyShape(UPointer->GetWritePointer())==false)
							FlagUndoBuff=false;
					}
					if(item->GetID()==50890 || item->GetID()==51861)
						DbgValueInGerber++;
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
	CmdRotate	*CmdRotateVar=dynamic_cast<CmdRotate *>(packet);
	if(CmdRotateVar!=NULL){
		UndoElement<GerberFastInPage>	*UPointer=new UndoElement<GerberFastInPage>(this,&GerberFastInPage::UndoRotate);
		if(GetParamGlobal()->MaxUndoCount>0){
			int32	Numb=0;
			for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
				if(a->GetSelected()==true && a->GetEditLocked()==false  && a->GetVisible()==true){
					GerberFastItemBase	*item=static_cast<GerberFastItemBase *>(a);
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
				GerberFastItemBase	*item=static_cast<GerberFastItemBase *>(a);
				if(item!=NULL){
					if(GetParamGlobal()->MaxUndoCount>0){
						if(FlagUndoBuff==true && ::Save(UPointer->GetWritePointer(),item->GetID())==false)
							FlagUndoBuff=false;
						if(FlagUndoBuff==true && item->SaveOnlyShape(UPointer->GetWritePointer())==false)
							FlagUndoBuff=false;
					}
					if(item->GetID()==50890 || item->GetID()==51861)
						DbgValueInGerber++;
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
	CmdZoom	*CmdZoomVar=dynamic_cast<CmdZoom *>(packet);
	if(CmdZoomVar!=NULL){
		UndoElement<GerberFastInPage>	*UPointer=new UndoElement<GerberFastInPage>(this,&GerberFastInPage::UndoZoom);
		if(GetParamGlobal()->MaxUndoCount>0){
			int32	Numb=0;
			for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
				if(a->GetSelected()==true && a->GetEditLocked()==false  && a->GetVisible()==true){
					GerberFastItemBase	*item=static_cast<GerberFastItemBase *>(a);
					if(item!=NULL){
						Numb++;
					}
				}
			}
			::Save(UPointer->GetWritePointer(),Numb);
		}
		bool	FlagUndoBuff=true;
		//DbgCounterInGerber=0;
		for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
			if(a->GetSelected()==true && a->GetEditLocked()==false  && a->GetVisible()==true){
				GerberFastItemBase	*item=static_cast<GerberFastItemBase *>(a);
				if(item!=NULL){
					if(GetParamGlobal()->MaxUndoCount>0){
						if(FlagUndoBuff==true && ::Save(UPointer->GetWritePointer(),item->GetID())==false)
							FlagUndoBuff=false;
						if(FlagUndoBuff==true && item->SaveOnlyShape(UPointer->GetWritePointer())==false)
							FlagUndoBuff=false;
					}
					if(item->GetID()==4940)
						DbgValueInGerber++;
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
	CmdShear	*CmdShearVar=dynamic_cast<CmdShear *>(packet);
	if(CmdShearVar!=NULL){
		UndoElement<GerberFastInPage>	*UPointer=new UndoElement<GerberFastInPage>(this,&GerberFastInPage::UndoShear);
		if(GetParamGlobal()->MaxUndoCount>0){
			int32	Numb=0;
			for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
				if(a->GetSelected()==true && a->GetEditLocked()==false  && a->GetVisible()==true){
					GerberFastItemBase	*item=static_cast<GerberFastItemBase *>(a);
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
				GerberFastItemBase	*item=static_cast<GerberFastItemBase *>(a);
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
	CmdMirror	*CmdMirrorVar=dynamic_cast<CmdMirror *>(packet);
	if(CmdMirrorVar!=NULL){
		UndoElement<GerberFastInPage>	*UPointer=new UndoElement<GerberFastInPage>(this,&GerberFastInPage::UndoMirror);
		if(GetParamGlobal()->MaxUndoCount>0){
			int32	Numb=0;
			for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
				if(a->GetSelected()==true && a->GetEditLocked()==false  && a->GetVisible()==true){
					GerberFastItemBase	*item=dynamic_cast<GerberFastItemBase *>(a);
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
				GerberFastItemBase	*item=dynamic_cast<GerberFastItemBase *>(a);
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
	CmdCenterize	*CmdCenterizeVar=dynamic_cast<CmdCenterize *>(packet);
	if(CmdCenterizeVar!=NULL){
		UndoElement<GerberFastInPage>	*UPointer=new UndoElement<GerberFastInPage>(this,&GerberFastInPage::UndoCenterize);
		if(GetParamGlobal()->MaxUndoCount>0){
			int32	Numb=0;

			for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
				if(a->GetSelected()==true && a->GetEditLocked()==false  && a->GetVisible()==true){
					GerberFastItemBase	*item=dynamic_cast<GerberFastItemBase *>(a);
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
				GerberFastItemBase	*item=dynamic_cast<GerberFastItemBase *>(a);
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
	CmdCenterizeOnly	*CmdCenterizeOnlyVar=dynamic_cast<CmdCenterizeOnly *>(packet);
	if(CmdCenterizeOnlyVar!=NULL){
		UndoElement<GerberFastInPage>	*UPointer=new UndoElement<GerberFastInPage>(this,&GerberFastInPage::UndoCenterizeOnly);
		if(GetParamGlobal()->MaxUndoCount>0){
			int32	Numb=0;

			for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
				if(a->GetSelected()==true && a->GetEditLocked()==false  && a->GetVisible()==true){
					GerberFastItemBase	*item=dynamic_cast<GerberFastItemBase *>(a);
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
				GerberFastItemBase	*item=dynamic_cast<GerberFastItemBase *>(a);
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
	GUICmdSendApertureList	*GUICmdSendApertureListVar=dynamic_cast<GUICmdSendApertureList *>(packet);
	if(GUICmdSendApertureListVar!=NULL){
		GerberFileLayer	*GLayer=FileLayerList[GUICmdSendApertureListVar->Layer];
		if(GLayer!=NULL){
			GLayer->ReqApertureList(GUICmdSendApertureListVar->ApertureDim,GUICmdSendApertureListVar->Count);
		}
		SetCurrentSize();
		return;
	}
	GUICmdReqSetApertureList	*GUICmdReqSetApertureListVar=dynamic_cast<GUICmdReqSetApertureList *>(packet);
	if(GUICmdReqSetApertureListVar!=NULL){
		GerberFileLayer	*GLayer=FileLayerList[GUICmdReqSetApertureListVar->Layer];
		if(GLayer!=NULL){
			GLayer->SetApertureList(GUICmdReqSetApertureListVar->ApertureDim,GUICmdReqSetApertureListVar->Count);
		}
		SetCurrentSize();
		return;
	}
	MsgGerberSelectAll	*MsgGerberSelectAllVar=dynamic_cast<MsgGerberSelectAll *>(packet);
	if(MsgGerberSelectAllVar!=NULL){
		IntList LayerList;
		SelectAll(LayerList);
		return;
	}
	GUICmdMakeImage	*GUICmdMakeImageVar=dynamic_cast<GUICmdMakeImage *>(packet);
	if(GUICmdMakeImageVar!=NULL){
		MakeXY();
		ReleaseAllSelectedItem();
		if(GUICmdMakeImageVar->MIMode==GUICmdMakeImage::_MIM_ToMaster){
			MakeImage(GUICmdMakeImageVar->ButtonsToOperateLayer,GUICmdMakeImageVar->OperateCompositeIDList
					, GUICmdMakeImageVar->LayerColor ,GUICmdMakeImageVar->CompositeLayerColor);
		}
		else if(GUICmdMakeImageVar->MIMode==GUICmdMakeImage::_MIM_Standard){
			CreateImagingBmpBuff();
			int	LayerID=0;
			for(BoolClass *b=GUICmdMakeImageVar->ButtonsToOperateLayer.GetFirst();b!=NULL;b=b->GetNext(),LayerID++){
				if(b->GetValue()==true){
					MakeImage(ImagingBmp,LayerID,true);
				}
			}
			for(IntClass *b=GUICmdMakeImageVar->OperateCompositeIDList.GetFirst();b!=NULL;b=b->GetNext()){
				MakeImage(ImagingBmp,b->GetValue(),false);
			}
		}
		else if(GUICmdMakeImageVar->MIMode==GUICmdMakeImage::_MIM_Enlarge){
			CreateImagingBmpBuff();
			int	LayerID=0;
			for(BoolClass *b=GUICmdMakeImageVar->ButtonsToOperateLayer.GetFirst();b!=NULL;b=b->GetNext(),LayerID++){
				if(b->GetValue()==true){
					MakeImageEnlarge(ImagingBmp,LayerID,true);
				}
			}
			for(IntClass *b=GUICmdMakeImageVar->OperateCompositeIDList.GetFirst();b!=NULL;b=b->GetNext()){
				MakeImageEnlarge(ImagingBmp,b->GetValue(),false);
			}
		}
		else if(GUICmdMakeImageVar->MIMode==GUICmdMakeImage::_MIM_Shrinked){
			CreateImagingBmpBuff();
			int	LayerID=0;
			for(BoolClass *b=GUICmdMakeImageVar->ButtonsToOperateLayer.GetFirst();b!=NULL;b=b->GetNext(),LayerID++){
				if(b->GetValue()==true){
					MakeImageShrinked(ImagingBmp,LayerID,true);
				}
			}
			for(IntClass *b=GUICmdMakeImageVar->OperateCompositeIDList.GetFirst();b!=NULL;b=b->GetNext()){
				MakeImageShrinked(ImagingBmp,b->GetValue(),false);
			}
		}
		else if(GUICmdMakeImageVar->MIMode==GUICmdMakeImage::_MIM_Shiftable){
			CreateImagingBmpBuff();
			int	LayerID=0;
			for(BoolClass *b=GUICmdMakeImageVar->ButtonsToOperateLayer.GetFirst();b!=NULL;b=b->GetNext(),LayerID++){
				if(b->GetValue()==true){
					MakeImageShiftable(ImagingBmp,LayerID,true);
				}
			}
			for(IntClass *b=GUICmdMakeImageVar->OperateCompositeIDList.GetFirst();b!=NULL;b=b->GetNext()){
				MakeImageShiftable(ImagingBmp,b->GetValue(),false);
			}
		}
		else if(GUICmdMakeImageVar->MIMode==GUICmdMakeImage::_MIM_Unstable){
			CreateImagingBmpBuff();
			int	LayerID=0;
			for(BoolClass *b=GUICmdMakeImageVar->ButtonsToOperateLayer.GetFirst();b!=NULL;b=b->GetNext(),LayerID++){
				if(b->GetValue()==true){
					MakeImageUnstable(ImagingBmp,LayerID,true);
				}
			}
			for(IntClass *b=GUICmdMakeImageVar->OperateCompositeIDList.GetFirst();b!=NULL;b=b->GetNext()){
				MakeImageUnstable(ImagingBmp,b->GetValue(),false);
			}
		}
		else if(GUICmdMakeImageVar->MIMode==GUICmdMakeImage::_MIM_Stable){
			CreateImagingBmpBuff();
			int	LayerID=0;
			for(BoolClass *b=GUICmdMakeImageVar->ButtonsToOperateLayer.GetFirst();b!=NULL;b=b->GetNext(),LayerID++){
				if(b->GetValue()==true){
					MakeImageStable(ImagingBmp,LayerID,true);
				}
			}
			for(IntClass *b=GUICmdMakeImageVar->OperateCompositeIDList.GetFirst();b!=NULL;b=b->GetNext()){
				MakeImageStable(ImagingBmp,b->GetValue(),false);
			}
		}
		else if(GUICmdMakeImageVar->MIMode==GUICmdMakeImage::_MIM_Clear){
			CreateImagingBmpBuff();
			MatrixBuffClear	(ImagingBmp ,0,ImagingBmpXByte ,ImagingBmpYLen);
		}
		return;
	}
	GUICmdMakeBitImage	*GUICmdMakeBitImageVar=dynamic_cast<GUICmdMakeBitImage *>(packet);
	if(GUICmdMakeBitImageVar!=NULL){
		MakeXY();
		ReleaseAllSelectedItem();
		MakeBitImage(GUICmdMakeBitImageVar->ButtonsToOperateLayer,GUICmdMakeBitImageVar->OperateCompositeIDList
					,GUICmdMakeBitImageVar->LayerColor			 ,GUICmdMakeBitImageVar->CompositeLayerColor);
	
		return;
	}
	CmdGerberExec3PointAlignment	*GExe3P=dynamic_cast<CmdGerberExec3PointAlignment *>(packet);
	if(GExe3P!=NULL){
		MakeXY();
		int	Numb=0;
		for(int i=0;i<MaxGerberPointNumb;i++){
			if(GExe3P->CadPoint[i].x==0.0 && GExe3P->CadPoint[i].y==0.0)
				break;
			Numb++;
		}
		int	CadImagePoints[100][4];
		for(int i=0;i<100 && i<Numb;i++){
			CadImagePoints[i][0]=GExe3P->CadPoint[i].x;
			CadImagePoints[i][1]=GExe3P->CadPoint[i].y;
			CadImagePoints[i][2]=GExe3P->ImagePoint[i].x;
			CadImagePoints[i][3]=GExe3P->ImagePoint[i].y;
		}
		TriangleAreaData.BuildTriangle(CadImagePoints,Numb);
		UndoElement<GerberFastInPage>	*UPointer=new UndoElement<GerberFastInPage>(this,&GerberFastInPage::UndoMovePoints);
		if(GetParamGlobal()->MaxUndoCount>0){
			int32	UndoNumb=0;
			for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
				GerberFastItemBase	*item=dynamic_cast<GerberFastItemBase *>(a);
				if(item!=NULL){
					UndoNumb++;
				}
			}
			::Save(UPointer->GetWritePointer(),UndoNumb);
		}
		bool	FlagUndoBuff=true;
		for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
			GerberFastItemBase	*item=dynamic_cast<GerberFastItemBase *>(a);
			if(item!=NULL){
				double	cx,cy;
				item->GetCenter(cx,cy);
				TriangleArea	*t=TriangleAreaData.GetClosedTriangle((int)cx,(int)cy);
				if(t!=NULL){
					if(GetParamGlobal()->MaxUndoCount>0){
						if(FlagUndoBuff==true && ::Save(UPointer->GetWritePointer(),item->GetID())==false)
							FlagUndoBuff=false;
						if(FlagUndoBuff==true && item->Save(UPointer->GetWritePointer())==false)
							FlagUndoBuff=false;
					}
					item->TransformParam(t->m);
				}
			}
		}
		GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);
		SetCurrentSize();
		return;			
	}
	MsgGerberCenterize	*MsgGerberCenterizeVar=dynamic_cast<MsgGerberCenterize *>(packet);
	if(MsgGerberCenterizeVar!=NULL){
		MsgGerberCenterizeVar->Ret=false;
		for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
			GerberFastItemFlash	*item=dynamic_cast<GerberFastItemFlash *>(a);
			if(item!=NULL){
				FlexArea	A=MsgGerberCenterizeVar->Area;
				//XYData	*XP=GetGlobalOutlineOffset();
				//if(XP!=NULL){
					//A.MoveToNoClip(XP->x,XP->y);
					if(item->IsCrossed(&A)==true){
						double	mx1,my1,mx2,my2;
						item->GetXY(mx1,my1,mx2,my2);
						MsgGerberCenterizeVar->x	=(mx1+mx2)/2;
						MsgGerberCenterizeVar->y	=(my1+my2)/2;
						MsgGerberCenterizeVar->Ret=true;
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
		//int	Col=MakeColorCenter(BrList);
		FlexArea PadArea;
		GetPadFromImage(*ImageList[MaxLayer] ,GCenter->Area ,PadArea);
		PadArea.GetCenter(GCenter->LocalX,GCenter->LocalY);
		return;
	}
	CmdMakeAutoMatch	*CmdMakeAutoMatchVar=dynamic_cast<CmdMakeAutoMatch *>(packet);
	if(CmdMakeAutoMatchVar!=NULL){
		if(CmdMakeAutoMatchVar->UsageLayer==true){
			for(int i=0;i<MaxGerberLayer;i++){
				if(i==CmdMakeAutoMatchVar->UsageLayerID){
					AutoLikeManualData.AdpptedLayer=i;
				}
			}
		}
		else{
			AutoLikeManualData.AdpptedLayer=10000+CmdMakeAutoMatchVar->UsageLayerID;
		}
		AccessDimXLen=GetDotPerLine()/AccessDimNumbX+1;
		AccessDimYLen=GetMaxLines()  /AccessDimNumbY+1;
		MakeAccessDim();

		GerberFastBase	*ABase=(GerberFastBase *)GetParentBase();
		if(ABase->AutoMatchMethod==0){
			MakeAutoMatchingBox(CmdMakeAutoMatchVar->UsageLayer ,CmdMakeAutoMatchVar->UsageLayerID
								,CmdMakeAutoMatchVar->RemoveShiftable
								,CmdMakeAutoMatchVar->ShiftableLayer ,CmdMakeAutoMatchVar->ShiftableCompositeIDList
								,CmdMakeAutoMatchVar->MinDotsForAutoMatching
								,CmdMakeAutoMatchVar->ShrinkDotForAutoMatchingArea);
		}
		else if(ABase->AutoMatchMethod==1){
			AutoLikeManualData.CreateArea();
		}
		GetLayersBase()->StepProcessing(GetPage());
		if(ABase->CutLargeGetber==true){
			RestructTooBig(ABase->TooBigSizeForCut);
		}
		GetLayersBase()->StepProcessing(GetPage());
		MakeTransArea(CmdMakeAutoMatchVar->UsageLayer ,CmdMakeAutoMatchVar->UsageLayerID);

		SetCurrentSize();
		GetLayersBase()->StepProcessing(GetPage());
		return;
	}
	CmdClearAutoMatch	*CmdClearAutoMatchVar=dynamic_cast<CmdClearAutoMatch *>(packet);
	if(CmdClearAutoMatchVar!=NULL){
		ClearAutoMatchInfo();
		AutoLikeManualData.Clear();
		MatchAlignmentArea1.RemoveAll();
		MatchAlignmentArea2.RemoveAll();
		MatchAlignmentArea3.RemoveAll();
		return;
	}
	CmdExecAutoMatch	*CmdExecAutoMatchVar=dynamic_cast<CmdExecAutoMatch *>(packet);
	if(CmdExecAutoMatchVar!=NULL){
		MakeItemListInside();
		MakeXY();

		if(CmdExecAutoMatchVar->UsageLayer==true){
			AutoLikeManualData.AdpptedLayer=CmdExecAutoMatchVar->UsageLayerID;
		}
		else{
			AutoLikeManualData.AdpptedLayer=10000+CmdExecAutoMatchVar->UsageLayerID;
		}
		MakeEnabledAutomatchFlag();
		AccessDimXLen=GetDotPerLine()/AccessDimNumbX+1;
		AccessDimYLen=GetMaxLines()  /AccessDimNumbY+1;
		GerberFastBase	*ABase=(GerberFastBase *)GetParentBase();
		if(ABase->AutoMatchMethod==0){
			GetLayersBase()->StepProcessing(GetPage());
			PushCenter();
			GetLayersBase()->StepProcessing(GetPage());
			ExecuteMatching();
			GetLayersBase()->StepProcessing(GetPage());
		}
		else if(ABase->AutoMatchMethod==1){
			IntList	LayerListDummy;
			SelectAll(LayerListDummy);
			PushCenter();
			if(ABase->AutoMatchExecuteLargeArea==true){
				AutoLikeManualData.ExecuteMatchFirst();
			}
			
			GetLayersBase()->StepProcessing(GetPage());
			AutoLikeManualData.CreateDetail();
			
			GetLayersBase()->StepProcessing(GetPage());
			InitialTransArea(CmdExecAutoMatchVar->UsageLayer ,AutoLikeManualData.AdpptedLayer);
			
			MakeRelatedInOtherLayerItems(CmdExecAutoMatchVar->UsageLayer ,AutoLikeManualData.AdpptedLayer);

			GetLayersBase()->StepProcessing(GetPage());
			//AutoLikeManualData.ExecuteMatchDetail(CmdExecAutoMatchVar->BrighterInPattern);
			////AutoLikeManualData.ExecuteMatchDetail4(CmdExecAutoMatchVar->BrighterInPattern);
			ExecuteClusterMatchDetail(CmdExecAutoMatchVar->UsageLayer ,AutoLikeManualData.AdpptedLayer ,CmdExecAutoMatchVar->BrighterInPattern);
			MakeABox();
		}
		MakeXY();
		SetCurrentSize();
		GetLayersBase()->StepProcessing(GetPage());
		return;
	}
	MsgSaveConstruct	*MsgSaveConstructVar=dynamic_cast<MsgSaveConstruct *>(packet);
	if(MsgSaveConstructVar!=NULL){
		QBuffer	Buff;
		Buff.open(QIODevice::WriteOnly);
		if(FileLayerList	.Save(&Buff)==false)
			return;
		if(CompositeLayer	.Save(&Buff)==false)
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
		if(CompositeLayer	.Load(&Buff)==false)
			return;
		bool	Error;
		BuildPointer(Error);
		MakeXY();
		return;
	}
	GUICmdMakeAlgo	*GUICmdMakeAlgoVar=dynamic_cast<GUICmdMakeAlgo *>(packet);
	if(GUICmdMakeAlgoVar!=NULL){
		MakeXY();
		MakeAlgo(GUICmdMakeAlgoVar->MakeAlgoAllList,GUICmdMakeAlgoVar->ExecutedLine);
		return;
	}
	CmdReqGerberInfo	*CmdReqGerberInfoVar=dynamic_cast<CmdReqGerberInfo *>(packet);
	if(CmdReqGerberInfoVar!=NULL){
		int	LayerNo=0;
		for(BoolClass *d=CmdReqGerberInfoVar->DrawingLayers.GetFirst();d!=NULL;d=d->GetNext(),LayerNo++){
			if(d->GetValue()==true){
				GerberFileLayer	*FL=FileLayerList[LayerNo];
				if(FL!=NULL){
					AlgorithmItemPointerListContainer	Found;
					PickupItem(CmdReqGerberInfoVar->GlobalX,CmdReqGerberInfoVar->GlobalY,Found);
					for(AlgorithmItemPointerList *a=Found.GetFirst();a!=NULL;a=a->GetNext()){
						GerberFastItemBase	*item=static_cast<GerberFastItemBase *>(a->GetItem());
						if(item!=NULL && item->GetFileLayerID()==FL->GetFileLayerID()){
							GerberInfo	*g=new GerberInfo();
							g->DCode	=item->GetDCode();
							g->ItemID	=item->GetID();
							g->FileLayerID	=item->GetFileLayerID();
							g->TypeStr		=item->GetTypeStr();
							g->Message		=item->GetMessage();
							CmdReqGerberInfoVar->Answer.AppendList(g);
						}
					}
				}
			}
		}
		GerberFastBase	*ABase=(GerberFastBase *)GetParentBase();
		SparsContainerData.SetSelected(CmdReqGerberInfoVar->GlobalX,CmdReqGerberInfoVar->GlobalY,ABase->IsolationToSelect);
		return;
	}
	CmdRemoveAutoMatchPoint	*CmdRemoveAutoMatchPointVar=dynamic_cast<CmdRemoveAutoMatchPoint *>(packet);
	if(CmdRemoveAutoMatchPointVar!=NULL){
		GerberFastBase	*ABase=(GerberFastBase *)GetParentBase();
		if(ABase->AutoMatchMethod==0){
			for(int xn=0;xn<ABoxXNum;xn++){
				for(int yn=0;yn<ABoxYNum;yn++){
					if(ABox[yn][xn].IsInclude(CmdRemoveAutoMatchPointVar->LocalX,CmdRemoveAutoMatchPointVar->LocalY)==true){
						ABox[yn][xn].Adopted=false;
						ABox[yn][xn].DoneAutoMatch=false;
					}
				}
			}
			ExecuteAllocateMatching();
		}
		else{
			for(MatchAutoLikeManual *p=AutoLikeManualData.GetFirst();p!=NULL;p=p->GetNext()){
				p->RemoveArea(CmdRemoveAutoMatchPointVar->LocalX,CmdRemoveAutoMatchPointVar->LocalY);
			}
			MatchAlignmentArea1.RemoveArea(CmdRemoveAutoMatchPointVar->LocalX,CmdRemoveAutoMatchPointVar->LocalY);
			MatchAlignmentArea2.RemoveArea(CmdRemoveAutoMatchPointVar->LocalX,CmdRemoveAutoMatchPointVar->LocalY);
			MatchAlignmentArea3.RemoveArea(CmdRemoveAutoMatchPointVar->LocalX,CmdRemoveAutoMatchPointVar->LocalY);
		}	
		return;
	}
	CmdReflectOtherAlgorithm	*CmdReflectOtherAlgorithmVar=dynamic_cast<CmdReflectOtherAlgorithm *>(packet);
	if(CmdReflectOtherAlgorithmVar!=NULL){
		ExecuteAllocateForOthers();
		return;
	}
	CmdAllocateAutoMatching	*CmdAllocateAutoMatchingVar=dynamic_cast<CmdAllocateAutoMatching *>(packet);
	if(CmdAllocateAutoMatchingVar!=NULL){
		ExecuteAllocateMatching();
		return;
	}
	CmdReqAlgoGenMap	*CmdReqAlgoGenMapVar=dynamic_cast<CmdReqAlgoGenMap *>(packet);
	if(CmdReqAlgoGenMapVar!=NULL){
		GerberFastBase	*Base=(GerberFastBase *)GetParentBase();
		QBuffer	Buff;
		Buff.open(QIODevice::WriteOnly);
		AlgoGenEssenseContainer		AlgoGenEssenseContainerData;
		Base->MakeAlgoData.CreateEssense(this,AlgoGenEssenseContainerData);
		AlgoGenEssenseContainerData.Save(&Buff);
		*CmdReqAlgoGenMapVar->Pointer=Buff.buffer();
		return;
	}
	CmdSetAlgoGenMap	*CmdSetAlgoGenMapVar=dynamic_cast<CmdSetAlgoGenMap *>(packet);
	if(CmdSetAlgoGenMapVar!=NULL){
		GerberFastBase	*Base=(GerberFastBase *)GetParentBase();
		QBuffer	Buff(CmdSetAlgoGenMapVar->Pointer);
		Buff.open(QIODevice::ReadOnly);
		AlgoGenEssenseContainer		AlgoGenEssenseContainerData;
		AlgoGenEssenseContainerData.Load(&Buff);
		Base->MakeAlgoData.AllocateEssense	(this, AlgoGenEssenseContainerData);
		return;
	}
	CmdReqGerberAperture	*CmdReqGerberApertureVar=dynamic_cast<CmdReqGerberAperture *>(packet);
	if(CmdReqGerberApertureVar!=NULL){
		GerberFileLayer	*FL=FileLayerList[CmdReqGerberApertureVar->GerberLayer];
		if(FL!=NULL){
			for(GerberDCodeBase *a=FL->DCodeList.GetFirst();a!=NULL;a=a->GetNext()){
				GerberApertureInfo	*b=new GerberApertureInfo();
				b->DCode		=a->DCode;
				b->ShapeClass	=a->GetItemClassType();
				b->Width		=a->GetWidth();
				b->Height		=a->GetHeight();
				CmdReqGerberApertureVar->InfoList.AppendList(b);
			}
		}
		return;
	}
	CmdChangeGerberAperture	*CmdChangeGerberApertureVar=dynamic_cast<CmdChangeGerberAperture *>(packet);
	if(CmdChangeGerberApertureVar!=NULL){
		GerberFileLayer	*FL=FileLayerList[CmdChangeGerberApertureVar->GerberLayer];
		if(FL!=NULL){
			ReleaseAllSelectedItem();
			BoolClass	*SelectedBool=CmdChangeGerberApertureVar->SelectedList.GetFirst();
			for(GerberDCodeBase *a=FL->DCodeList.GetFirst();a!=NULL && SelectedBool!=NULL;a=a->GetNext(),SelectedBool=SelectedBool->GetNext()){
				for(GerberApertureInfo *b=CmdChangeGerberApertureVar->ApertureList->GetFirst();b!=NULL;b=b->GetNext()){
					if(b->DCode==a->DCode){
						a->SetWidth(b->Width);
						a->SetHeight(b->Height);
						GerberFastItemPointerContainer	*r=GerberFastItemPointerContainerContainerList[CmdChangeGerberApertureVar->GerberLayer];
						if(r!=NULL){
							for(GerberFastItemPointer *p=r->PointerList.GetFirst();p!=NULL;p=p->GetNext()){
								GerberFastItemBase	*Item=p->GetPoint();
								if(Item->GetDCode()==a->DCode){
									Item->SetSelected(SelectedBool->GetValue());
								}
							}
						}
						break;
					}
				}
			}
		}
		MakeXY();
		SetCurrentSize();
		return;
	}
	CmdGerberDraw	*CmdGerberDrawVar=dynamic_cast<CmdGerberDraw *>(packet);
	if(CmdGerberDrawVar!=NULL){
		UndoElement<GerberFastInPage>	*UPointer=new UndoElement<GerberFastInPage>(this,&GerberFastInPage::UndoGerberDraw);
		for(int	N=0;N<MaxGerberLayer;N++){
			GerberFileLayer	*f=FileLayerList[N];
			if(f==NULL)
				break;
			AlgorithmItemPointerListContainer	ItemList;
			if(CmdGerberDrawVar->ButtonsToShowLayer[N]==true
			&& CmdGerberDrawVar->ButtonsToOperateLayer[N]==true){
				for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
					GerberFastItemBase	*item=dynamic_cast<GerberFastItemBase *>(a);
					if(item!=NULL && item->GetFileLayerID()==f->GetFileLayerID()){
						ItemList.Add(item);
					}
				}
				AlgorithmItemPointerListContainer CreatedItems;
				bool	Ret=MakePaintArea(CmdGerberDrawVar->GlobalX,CmdGerberDrawVar->GlobalY,ItemList,CreatedItems);
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
	CmdMatchingRoughly	*CmdMatchingRoughlyVar=dynamic_cast<CmdMatchingRoughly *>(packet);
	if(CmdMatchingRoughlyVar!=NULL){
		MakeXY();
		bool	MirrorMode;
		double	MovX;
		double	MovY;
		double	ZoomX;
		double	ZoomY;
		double	Rotation;
		UndoElement<GerberFastInPage>	*UPointer=new UndoElement<GerberFastInPage>(this,&GerberFastInPage::UndoMatchingRoughly);
		if(GetParamGlobal()->MaxUndoCount>0){
			int32	Numb=0;
			for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
				GerberFastItemBase	*item=static_cast<GerberFastItemBase *>(a);
				if(item!=NULL){
					Numb++;
				}
			}
			::Save(UPointer->GetWritePointer(),Numb);
		}

		for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
			GerberFastItemBase	*item=static_cast<GerberFastItemBase *>(a);
			if(item!=NULL){
				if(GetParamGlobal()->MaxUndoCount>0){
					::Save(UPointer->GetWritePointer(),item->GetID());
					item->Save(UPointer->GetWritePointer());
				}
				item->Zoom(CmdMatchingRoughlyVar->ZoomX,CmdMatchingRoughlyVar->ZoomY 
						,  CmdMatchingRoughlyVar->ZoomStartX,CmdMatchingRoughlyVar->ZoomStartY);
				item->MoveToFloat(CmdMatchingRoughlyVar->Dx,CmdMatchingRoughlyVar->Dy);
			}
		}
		MatchRough(CmdMatchingRoughlyVar->ButtonsToShowLayer	,CmdMatchingRoughlyVar->OperateCompositeIDList
					,MirrorMode
					,MovX,MovY
					,ZoomX,ZoomY
					,Rotation);


		for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
			GerberFastItemBase	*item=static_cast<GerberFastItemBase *>(a);
			if(item!=NULL){
				item->MoveToFloat(MovX,MovY);
				item->Rotate(Rotation ,GetDotPerLine()/2,GetMaxLines()/2);
				item->Zoom(ZoomX,ZoomY , 0,0);
			}
		}
		GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);
		SetCurrentSize();
		return;
	}
	CmdFlushMatrix	*CmdFlushMatrixVar=dynamic_cast<CmdFlushMatrix *>(packet);
	if(CmdFlushMatrixVar!=NULL){
		for(int	N=0;N<MaxGerberLayer;N++){
			GerberFileLayer	*f=FileLayerList[N];
			if(f==NULL)
				break;
			AlgorithmItemPointerListContainer	ItemList;
			if(CmdFlushMatrixVar->ButtonsToShowLayer[N]==true
			&& CmdFlushMatrixVar->ButtonsToOperateLayer[N]==true){
				GerberFastItemPointerContainer *p=GerberFastItemPointerContainerContainerList.Search(f->GetFileLayerID());
				if(p!=NULL){
					for(GerberFastItemPointer *a=p->PointerList.GetFirst();a!=NULL;a=a->GetNext()){
						GerberFastItemBase	*item=a->GetPoint();
						if(item->GetSelected()==true){
							PasteListMatrix	*d=new PasteListMatrix();
							d->GlobalPage=GetPage();
							double	Cx,Cy;
							item->GetCenter(Cx,Cy);
							d->XPos	=Cx;
							d->YPos	=Cy;
							CmdFlushMatrixVar->MatrixData.AppendList(d);
						}
					}
				}
			}
		}
		return;
	}
	CmdReqGerberShrinked	*CmdReqGerberShrinkedVar=dynamic_cast<CmdReqGerberShrinked *>(packet);
	if(CmdReqGerberShrinkedVar!=NULL){
		MakeXY();
		MakeMatchShrinked(CmdReqGerberShrinkedVar->ButtonsToOperateLayer ,CmdReqGerberShrinkedVar->OperateCompositeIDList
									,CmdReqGerberShrinkedVar->ShrinkedRate
									,CmdReqGerberShrinkedVar->ImageData
									,CmdReqGerberShrinkedVar->GerberData);
		return;
	}
	CmdReqMatchAutoLikeManual	*CmdReqMatchAutoLikeManualVar=dynamic_cast<CmdReqMatchAutoLikeManual *>(packet);
	if(CmdReqMatchAutoLikeManualVar!=NULL){
		QBuffer	Buff;
		Buff.open(QIODevice::ReadWrite);
		AutoLikeManualData.SaveParam(&Buff);
		CmdReqMatchAutoLikeManualVar->MatchAutoLikeManualData=Buff.buffer();
		return;
	}
	CmdSetMatchAutoLikeManual	*CmdSetMatchAutoLikeManualVar=dynamic_cast<CmdSetMatchAutoLikeManual *>(packet);
	if(CmdSetMatchAutoLikeManualVar!=NULL){
		QBuffer	Buff(&CmdSetMatchAutoLikeManualVar->MatchAutoLikeManualData);
		Buff.open(QIODevice::ReadOnly);
		CmdSetMatchAutoLikeManualVar->Point->LoadParam(&Buff);
		return;
	}
	CmdSaveMatchAutoLikeManual	*CmdSaveMatchAutoLikeManualVar=dynamic_cast<CmdSaveMatchAutoLikeManual *>(packet);
	if(CmdSaveMatchAutoLikeManualVar!=NULL){
		QBuffer	Buff;
		Buff.open(QIODevice::WriteOnly);
		CmdSaveMatchAutoLikeManualVar->Point->SaveParam(&Buff);
		CmdSaveMatchAutoLikeManualVar->MatchAutoLikeManualData=Buff.buffer();
		return;
	}
	CmdLoadMatchAutoLikeManual	*CmdLoadMatchAutoLikeManualVar=dynamic_cast<CmdLoadMatchAutoLikeManual *>(packet);
	if(CmdLoadMatchAutoLikeManualVar!=NULL){
		QBuffer	Buff(&CmdLoadMatchAutoLikeManualVar->MatchAutoLikeManualData);
		Buff.open(QIODevice::ReadWrite);
		AutoLikeManualData.LoadParam(&Buff);
		return;
	}
	CmdGetMatchAutoLikeManual	*CmdGetMatchAutoLikeManualVar=dynamic_cast<CmdGetMatchAutoLikeManual *>(packet);
	if(CmdGetMatchAutoLikeManualVar!=NULL){
		QBuffer	Buff;
		Buff.open(QIODevice::ReadWrite);
		AutoLikeManualData.SaveParam(&Buff);
		Buff.seek(0);
		CmdGetMatchAutoLikeManualVar->Point->LoadParam(&Buff);
		return;
	}
	CmdAddMatchAutoLikeManualPoint	*CmdAddMatchAutoLikeManualPointVar=dynamic_cast<CmdAddMatchAutoLikeManualPoint *>(packet);
	if(CmdAddMatchAutoLikeManualPointVar!=NULL){

	}
	CmdAddMatchAutoLikeManualAlignment	*CmdAddMatchAutoLikeManualAlignmentVar=dynamic_cast<CmdAddMatchAutoLikeManualAlignment *>(packet);
	if(CmdAddMatchAutoLikeManualAlignmentVar!=NULL){
		MatchAlignmentArea	*a=new MatchAlignmentArea(this);
		a->Area			=CmdAddMatchAutoLikeManualAlignmentVar->Area;
		a->LayerList	=CmdAddMatchAutoLikeManualAlignmentVar->LayerList;
		a->PointType	=CmdAddMatchAutoLikeManualAlignmentVar->PointType;
		if(CmdAddMatchAutoLikeManualAlignmentVar->PointType==1)
			MatchAlignmentArea1.AppendList(a);
		else if(CmdAddMatchAutoLikeManualAlignmentVar->PointType==2)
			MatchAlignmentArea2.AppendList(a);
		else if(CmdAddMatchAutoLikeManualAlignmentVar->PointType==3)
			MatchAlignmentArea3.AppendList(a);
	
		return;
	}
	CmdReqGeneralPipeInfo	*CmdReqGeneralPipeInfoVar=dynamic_cast<CmdReqGeneralPipeInfo *>(packet);
	if(CmdReqGeneralPipeInfoVar!=NULL){
		CmdReqGeneralPipeInfoVar->Point=new AlignmentGeneralPipeInfo(this);
		return;
	}
	CmdGenerateOutline	*CmdGenerateOutlineVar=dynamic_cast<CmdGenerateOutline *>(packet);
	if(CmdGenerateOutlineVar!=NULL){
		MakeXY();
		MakeOutline(CmdGenerateOutlineVar->ButtonsToOperateLayer ,CmdGenerateOutlineVar->ButtonsToOperateComposite);
		return;
	}
	CmdCreateEchingFactor	*CmdCreateEchingFactorVar=dynamic_cast<CmdCreateEchingFactor *>(packet);
	if(CmdCreateEchingFactorVar!=NULL){
		MakeEchingFactor(CmdCreateEchingFactorVar->ButtonsToOperateLayer ,CmdCreateEchingFactorVar->ButtonsToOperateComposite
						,CmdCreateEchingFactorVar->CornerR);
		return;
	}
	CmdClearOutline	*CmdClearOutlineVar=dynamic_cast<CmdClearOutline *>(packet);
	if(CmdClearOutlineVar!=NULL){
		SparsContainerData.RemoveAll();
		return;
	}
	CmdDrawAllSelected	*CmdDrawAllSelectedVar=dynamic_cast<CmdDrawAllSelected *>(packet);
	if(CmdDrawAllSelectedVar!=NULL){
		UndoElement<GerberFastInPage>	*UPointer=new UndoElement<GerberFastInPage>(this,&GerberFastInPage::UndoDrawAllSelected);
		for(int	N=0;N<MaxGerberLayer;N++){
			GerberFileLayer	*f=FileLayerList[N];
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
		GerberFileLayer	*FL=FileLayerList.GetItem(CmdSelectLineVar->LineNo);
		if(FL!=NULL){
			for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
				GerberFastItemBase	*item=static_cast<GerberFastItemBase *>(a);
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
		GerberFileLayer	*FL=FileLayerList.GetItem(CmdRemoveLineVar->LineNo);
		if(FL!=NULL){
			UndoElement<GerberFastInPage>	*UPointer=new UndoElement<GerberFastInPage>(this,&GerberFastInPage::UndoRemoveLine);
			::Save(UPointer->GetWritePointer(),CmdRemoveLineVar->LineNo);
			int32	Count=0;
			for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
				GerberFastItemBase	*item=static_cast<GerberFastItemBase *>(a);
				if(item!=NULL){
					if(item->GetFileLayerID()==FL->GetFileLayerID()){
						Count++;
					}
				}
			}
			::Save(UPointer->GetWritePointer(),Count);

			for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;){
				AlgorithmItemPI	*NextA=a->GetNext();
				GerberFastItemBase	*item=static_cast<GerberFastItemBase *>(a);
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
		GerberFileLayer	*FL1=FileLayerList.GetItem(CmdSwapNextVar->LineNo);
		GerberFileLayer	*FL2=FileLayerList.GetItem(CmdSwapNextVar->LineNo+1);
		if(FL1!=NULL && FL2!=NULL){
			UndoElement<GerberFastInPage>	*UPointer=new UndoElement<GerberFastInPage>(this,&GerberFastInPage::UndoSwapNext);
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
		GerberFileLayer	*FL=FileLayerList.GetItem(DuplicateLineVar->LineNo);
		if(FL!=NULL){
			UndoElement<GerberFastInPage>	*UPointer=new UndoElement<GerberFastInPage>(this,&GerberFastInPage::UndoDuplicateLine);
			::Save(UPointer->GetWritePointer(),DuplicateLineVar->LineNo);

			AlgorithmItemPointerListContainer	TmpItems;

			for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
				GerberFastItemBase	*item=static_cast<GerberFastItemBase *>(a);
				if(item!=NULL){
					if(item->GetFileLayerID()==FL->GetFileLayerID()){
						AlgorithmItemRoot		*b=CreateItem(a->GetItemClassType());
						GerberFastItemBase	*Dest=static_cast<GerberFastItemBase *>(b);
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
			GerberFileLayer	*FLDest=new GerberFileLayer(&FileLayerList);
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
				GerberFastItemBase	*item=static_cast<GerberFastItemBase *>(d->GetItem());
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
		GerberFileLayer	*FL=FileLayerList.GetItem(CmdAddEmptyLayerVar->LineNo);
		if(FL!=NULL){
			UndoElement<GerberFastInPage>	*UPointer=new UndoElement<GerberFastInPage>(this,&GerberFastInPage::UndoAddEmptyLayer);
			::Save(UPointer->GetWritePointer() ,CmdAddEmptyLayerVar->LineNo);

			AlgorithmItemPointerListContainer	TmpItems;

			GerberFileLayer	*FLDest=new GerberFileLayer(&FileLayerList);
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
			FLDest->Remark	=/**/"Added by manual";

			int	MaxID=FileLayerList.GetMaxFileLayerID();
			FileLayerList.InsertLater(FL,FLDest);
			FLDest->SetFileLayerID(MaxID+1);

			::Save(UPointer->GetWritePointer(),FLDest->GetFileLayerID());

			CmdAddEmptyLayerVar	->FileLayerID=FLDest->GetFileLayerID();

			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);
		}
		return;
	}
	CmdAddGerberLineA	*CmdAddGerberLineAVar=dynamic_cast<CmdAddGerberLineA *>(packet);
	if(CmdAddGerberLineAVar!=NULL){
		GerberFastItemLine	*Item=new GerberFastItemLine();
		GerberFileLayer	*FL=FileLayerList.Find(CmdAddGerberLineAVar->FileLayerNo);
		if(FL==NULL)
			return;
		GerberDCodeBase	*DCode=FL->DCodeList.FindDCode(CmdAddGerberLineAVar->DCode);
		if(DCode==NULL)
			return;
		Item->SetDCode(DCode);
		Item->SetFileLayer(FL);
		Item->PosiImage	=true;
		Item->PosX1		=CmdAddGerberLineAVar->X1;
		Item->PosY1		=CmdAddGerberLineAVar->Y1;
		Item->OrgPosX1	=CmdAddGerberLineAVar->X1;
		Item->OrgPosY1	=CmdAddGerberLineAVar->Y1;
		Item->PosX2		=CmdAddGerberLineAVar->X2;
		Item->PosY2		=CmdAddGerberLineAVar->Y2;
		Item->OrgPosX2	=CmdAddGerberLineAVar->X2;
		Item->OrgPosY2	=CmdAddGerberLineAVar->Y2;
		AppendItem(Item);
		return;
	}
	CmdGenerateCenterize	*CmdGenerateCenterizeVar=dynamic_cast<CmdGenerateCenterize *>(packet);
	if(CmdGenerateCenterizeVar!=NULL){
		SparsContainerData.MakeCenterize(CmdGenerateCenterizeVar->MaxWidth,CenterLines);
		return;
	}
	GenerateBlocksFrom	*GenerateBlocksFromVar=dynamic_cast<GenerateBlocksFrom *>(packet);
	if(GenerateBlocksFromVar!=NULL){

		MakeXY();
		GenerateBlocks(GenerateBlocksFromVar->LayerOrComposite
					,  GenerateBlocksFromVar->LayerCompositeID
					,  GenerateBlocksFromVar->GeneratedLibType
					,  GenerateBlocksFromVar->GeneratedLibID
					,  GenerateBlocksFromVar->OmitLayerOrComposite
					,  GenerateBlocksFromVar->OmitLayerCompositeID
					,  GenerateBlocksFromVar->GFileContainer
					,  GenerateBlocksFromVar->ThresholdData);
		return;
	}
	CmdSetFileInvert	*CmdSetFileInvertVar=dynamic_cast<CmdSetFileInvert *>(packet);
	if(CmdSetFileInvertVar!=NULL){
		for(LibIDAndInvertedList *L=CmdSetFileInvertVar->Container->GetFirst();L!=NULL;L=L->GetNext()){
			GerberFileLayer	*f=FileLayerList.FindByLibID(L->LayerLibID);
			if(f!=NULL){
				f->ViewInvert=L->Inverted;
			}
		}
		return;
	}
	CmdMakeClusterItem	*CmdMakeClusterItemVar=dynamic_cast<CmdMakeClusterItem *>(packet);
	if(CmdMakeClusterItemVar!=NULL){
		MakeClusterContainer(CmdMakeClusterItemVar->ButtonsToOperateLayer ,CmdMakeClusterItemVar->OperateCompositeIDList);
		return;
	}
	CmdReqResult	*CmdReqResultVar=dynamic_cast<CmdReqResult *>(packet);
	if(CmdReqResultVar!=NULL){
		SetResultInCluster();
		for(GerberFastClusterItemList *a=ClusterItemContainer.GetFirst();a!=NULL;a=a->GetNext()){
			AlgorithmItemPointerList	*q=a->ItemPointer.GetFirst();
			if(q!=NULL){
				CmdReqResultVar->TotalHoles.Add(q->GetID());
				if(a->NG==true){
					CmdReqResultVar->NGHoles.Add(q->GetID());
				}
			}
		}
		CmdReqResultVar->PinholeCount	=ClusterItemContainer.PinholeCount;
		return;
	}
	CmdCopyPageAllFrom	*CmdCopyPageAllFromVar=dynamic_cast<CmdCopyPageAllFrom *>(packet);
	if(CmdCopyPageAllFromVar!=NULL){
		FileLayerList	= CmdCopyPageAllFromVar->SourcePage->FileLayerList;

		//PageInfoForPartsData;

		for(AlgorithmItemPI *s=CmdCopyPageAllFromVar->SourcePage->GetFirstData();s!=NULL;s=s->GetNext()){
			GerberFastItemBase	*d=(GerberFastItemBase *)CreateItem(s->GetItemClassType());
			d->CopyFrom(s);
			int	DCode		=((GerberFastItemBase *)s)->GetDCode();
			int	FileLayerID	=((GerberFastItemBase *)s)->GetFileLayerID();
			GerberFileLayer	*f=FileLayerList.Find(FileLayerID);
			d->SetFileLayer(f);
			GerberDCodeBase	*DC=f->FindDCode(DCode);
			if(DC!=NULL){
				d->SetDCode(DC);
			}
			AppendItem(d);
			d->SetID(s->GetID());
		}
		FastSearchIDItemStart();
		for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
			GerberFastItemBase	*Item=dynamic_cast<GerberFastItemBase *>(a);
			if(Item!=NULL){
				if(Item->RelationParentID>=0){
					Item->RelationParent=dynamic_cast<GerberFastItemBase *>(FastSearchIDItem(Item->RelationParentID));
				}
				else{
					Item->RelationParent=NULL;
				}
			}
		}
		bool	Error=true;
		BuildPointer(Error);
		MakeXY();
		MakeItemListInside();

		return;
	}
	CmdReqPatternResult	*CmdReqPatternResultVar=dynamic_cast<CmdReqPatternResult *>(packet);
	if(CmdReqPatternResultVar!=NULL){
		CmdReqPatternResultVar->Data.GerberArea=0;
		AlgorithmItemRoot	*a=FastSearchIDItem(CmdReqPatternResultVar->GerberItemID);
		if(a!=NULL){
			GerberFastItemBase	*Item=dynamic_cast<GerberFastItemBase *>(a);
			if(Item!=NULL){
				if(Item->GetDCodePointer()!=NULL)
					CmdReqPatternResultVar->Data.ApertureType	=Item->GetDCodePointer()->GetItemClassType();
				else
					CmdReqPatternResultVar->Data.ApertureType	=4;
				bool Clipped;
				CmdReqPatternResultVar->Data.GerberArea	=Item->GetAreaSize(true,Clipped);
				CmdReqPatternResultVar->Data.ClippedGerber	=Clipped;
				//CmdReqPatternResultVar->Data.GerberArea	=Item->GetAreaSize(false,Clipped);
				double	X1,Y1,X2,Y2;
				Item->GetXY(X1,Y1,X2,Y2);
				CmdReqPatternResultVar->Data.GerberPosX	=(X1+X2)/2.0;
				CmdReqPatternResultVar->Data.GerberPosY	=(Y1+Y2)/2.0;
				CmdReqPatternResultVar->Data.GerberXLen	=X2-X1;
				CmdReqPatternResultVar->Data.GerberYLen	=Y2-Y1;
			}
		}
		return;
	}
	CmdSelectItemsGerberFast	*CmdSelectItemsGerberFastVar=dynamic_cast<CmdSelectItemsGerberFast *>(packet);
	if(CmdSelectItemsGerberFastVar!=NULL){
		for(int	N=0;N<MaxGerberLayer;N++){
			GerberFileLayer	*f=FileLayerList[N];
			if(f==NULL)
				break;
			if(CmdSelectItemsGerberFastVar->ButtonsToOperateLayer[N]==true){
				for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
					GerberFastItemBase	*item=dynamic_cast<GerberFastItemBase *>(a);
					if(item!=NULL && item->GetFileLayerID()==f->GetFileLayerID()){
						if(item->GetVisible()==true){
							if(item->IsCrossed(&CmdSelectItemsGerberFastVar->Area)==true){
								item->SetSelected(true);
							}
							else if(item->GetVector()!=NULL){
								if(item->GetVector()->CheckOverlap(CmdSelectItemsGerberFastVar->Area)==true){
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
}

void	GerberFastInPage::MakeXY(void)
{
	AlgorithmItemPI	*a;
	#pragma omp parallel
	#pragma omp single private(a)
	for(a=GetFirstData();a!=NULL;a=a->GetNext()){
		#pragma omp task
		{
			GerberFastItemBase	*Item=static_cast<GerberFastItemBase *>(a);
			if(Item!=NULL && Item->GetItemClassType()!=5){	//No composite
				Item->MakeXY();
			}
		}
	}
	for(AlgorithmItemPI	*b=GetFirstData();b!=NULL;b=b->GetNext()){
		GerberFastItemBase	*Item=static_cast<GerberFastItemBase *>(b);
		if(Item->GetItemClassType()==5){	//Only composite
			Item->MakeXY();
		}
	}
}

ExeResult	GerberFastInPage::ExecuteInitialAfterEdit	(int ExeID 
														,ResultInPageRoot *Res
														,ExecuteInitialAfterEditInfo &EInfo)
{
	ExeResult	Ret=AlgorithmInPagePI::ExecuteInitialAfterEdit	(ExeID ,Res,EInfo);
	ClusterItemContainer.BuildPointerInArea();
	return Ret;
}

struct	ResultFuncClass
{
	int									Page;
	GerberFastClusterItemContainer		*ClusterItemContainer;
};


static	void SetResultFunc(ResultInItemRoot *Item ,void *Something)
{
	struct	ResultFuncClass	*PData=(struct	ResultFuncClass *)Something;
	if(PData->Page!=Item->GetPage())
		return;
	GerberFastClusterItemContainer		*ClusterItemContainer	=PData->ClusterItemContainer;
	if(Item->IsOk()==false){
		if(ClusterItemContainer->XDivClusterLen!=0 && ClusterItemContainer->YDivClusterLen!=0){
			for(ResultPosList *r=Item->GetPosListFirst();r!=NULL;r=r->GetNext()){
				bool	Found=false;
				int	kx=r->Px/ClusterItemContainer->XDivClusterLen;
				int	ky=r->Py/ClusterItemContainer->YDivClusterLen;
				if(0<=kx && kx<XDivClusterNumb && 0<=ky && ky<YDivClusterNumb){
					for(GerberFastClusterItemPointer *a=ClusterItemContainer->PointerInArea[kx][ky].GetFirst();a!=NULL;a=a->GetNext()){
						if(a->Pointer->Area.IsInclude(r->Px,r->Py)==true){
							a->Pointer->NG=true;
							Found=true;
							break;
						}
					}
				}
				if(Found==false){
					ClusterItemContainer->PinholeCount++;
				}
			}
		}
	}
}
void	GerberFastInPage::SetResultInCluster(void)
{
	ClusterItemContainer.PinholeCount	=0;
	for(GerberFastClusterItemList *a=ClusterItemContainer.GetFirst();a!=NULL;a=a->GetNext()){
		a->NG=false;
	}
	struct	ResultFuncClass		PData;
	PData.Page					=GetPage();
	PData.ClusterItemContainer	=&ClusterItemContainer;
	ResultInspection	*DRes=GetParentBase()->GetLayersBase()->GetCurrentResultForDraw();
	if(DRes!=NULL){
		DRes->ExecuteInAllItems(SetResultFunc,&PData);
	}
}

void	GerberFastInPage::UndoDrawAllSelected	(QIODevice *f)
{
	int32	Count;
	if(::Load(f,Count)==false)
		return;

	FastSearchIDItemStart();


	for(int i=0;i<Count;i++){
		int32	ID;
		if(::Load(f,ID)==false)
			return;
		AlgorithmItemRoot	*a=FastSearchIDItem(ID);
		if(a!=NULL){
			RemoveItem(a);
			delete	a;
		}
	}
	FastSearchIDItemStart();
	SetCurrentSize();
}
	
void	GerberFastInPage::UndoRemoveLine		(QIODevice *f)
{
	int32	LineNo;
	if(::Load(f,LineNo)==false)
		return;
	int32	Count;
	if(::Load(f,Count)==false)
		return;
	for(int i=0;i<Count;i++){
		int32	ItemClassType;
		if(::Load(f,ItemClassType)==false)
			return;
		AlgorithmItemRoot		*b=CreateItem(ItemClassType);
		if(b->Save(f)==false){
			delete	b;
			return;
		}
		AppendItem(b);
	}
	GerberFileLayer	*DestFL=new GerberFileLayer(&FileLayerList);
	if(DestFL->Load(f)==false){
		delete	DestFL;
		return;
	}
	GerberFileLayer	*FL=FileLayerList[LineNo];
	if(FL!=NULL){
		FileLayerList.InsertForward(FL,DestFL);
	}
	else{
		FileLayerList.AppendList(DestFL);
	}
}

void	GerberFastInPage::MakeItemListInside(void)
{
	ItemListInside.RemoveAll();
	int		Mergin=200;
	for(AlgorithmItemPI	*b=GetFirstData();b!=NULL;b=b->GetNext()){
		GerberFastItemBase	*BItem=dynamic_cast<GerberFastItemBase *>(b);
		if(BItem!=NULL){
			double	X1,Y1,X2,Y2;
			BItem->GetXY(X1,Y1,X2,Y2);
			X1-=Mergin;
			Y1-=Mergin;
			X2+=Mergin;
			Y2+=Mergin;
			if(CheckOverlapRectRect(X1,Y1,X2,Y2	,0.0,0.0,(double)GetDotPerLine(),(double)GetMaxLines())==true){
				ItemListInside.Add(BItem);
			}
		}
	}
}

void	GerberFastInPage::UndoSwapNext		(QIODevice *f)
{
	int32	LineNo;
	if(::Load(f,LineNo)==false)
		return;

	GerberFileLayer	*FL1=FileLayerList.GetItem(LineNo);
	GerberFileLayer	*FL2=FileLayerList.GetItem(LineNo+1);

	FileLayerList.RemoveList(FL1);
	FileLayerList.InsertLater(FL2,FL1);
}

void	GerberFastInPage::UndoDuplicateLine	(QIODevice *f)
{
	int32	LineNo;
	if(::Load(f,LineNo)==false)
		return;
	int32	Count;
	if(::Load(f,Count)==false)
		return;
	FastSearchIDItemStart();
	for(int i=0;i<Count;i++){
		int32	ID;
		if(::Load(f,ID)==false)
			return;
		AlgorithmItemRoot	*a=FastSearchIDItem(ID);
		if(a!=NULL){
			RemoveItem(a);
			delete	a;
		}
	}
	GerberFileLayer	*FL2=FileLayerList.GetItem(LineNo+1);
	FileLayerList.RemoveList(FL2);

	SetCurrentSize();
}
void	GerberFastInPage::UndoAddEmptyLayer	(QIODevice *f)
{
	int32	LineNo;
	if(::Load(f,LineNo)==false)
		return;

	GerberFileLayer	*FL2=FileLayerList.GetItem(LineNo+1);
	FileLayerList.RemoveList(FL2);

	SetCurrentSize();
}

bool	GerberFastInPage::Save(QIODevice *f)
{
	AlgorithmBase	*ABase=GetParentBase();
	if(ABase->GetModeLoadSaveInPlayer()==true || (ABase->GetModeLoadSaveInPlayer()==false && GetLayersBase()->GetModeInspectionPlayer()==false)){

		if(FileLayerList.Save(f)==false)
			return false;
		if(AutoInterpolation.Save(f)==false)
			return false;
		if(CompositeLayer.Save(f)==false)
			return false;

		if(TriangleAreaData.Save(f)==false)
			return false;
		if(::Save(f,MoveMode)==false)
			return false;
		if(::Save(f,RotateMode)==false)
			return false;
		if(::Save(f,ExtendMode)==false)
			return false;
		if(::Save(f,SlopeXMode)==false)
			return false;
		if(::Save(f,SlopeYMode)==false)
			return false;
		if(::Save(f,AlignmentMode)==false)
			return false;
		if(::Save(f,AutoMatchingMode)==false)
			return false;

		BYTE	d=(BYTE)Mode;
		if(::Save(f,d)==false)
			return false;

		if(::Save(f,LastPosX)==false)
			return false;
		if(::Save(f,LastPosY)==false)
			return false;
		if(::Save(f,MoveStartPosX)==false)
			return false;
		if(::Save(f,MoveStartPosY)==false)
			return false;
		if(::Save(f,RotateCenterXOnData)==false)
			return false;
		if(::Save(f,RotateCenterYOnData)==false)
			return false;
		if(::Save(f,RotateFirstX)==false)
			return false;
		if(::Save(f,RotateFirstY)==false)
			return false;
		if(::Save(f,RotateAngle)==false)
			return false;
		if(::Save(f,ExtendCenterXOnData)==false)
			return false;
		if(::Save(f,ExtendCenterYOnData)==false)
			return false;
		if(::Save(f,ExtendFirstX)==false)
			return false;
		if(::Save(f,ExtendFirstY)==false)
			return false;
		if(::Save(f,SlopeXCenterXOnData)==false)
			return false;
		if(::Save(f,SlopeXCenterYOnData)==false)
			return false;
		if(::Save(f,SlopeXFirstX)==false)
			return false;
		if(::Save(f,SlopeXFirstY)==false)
			return false;
		if(::Save(f,SlopeXAngle)==false)
			return false;
		if(::Save(f,SlopeYCenterXOnData)==false)
			return false;
		if(::Save(f,SlopeYCenterYOnData)==false)
			return false;
		if(::Save(f,SlopeYFirstX)==false)
			return false;
		if(::Save(f,SlopeYFirstY)==false)
			return false;
		if(::Save(f,SlopeYAngle)==false)
			return false;

		for(int i=0;i<MaxGerberPointNumb;i++){
			if(ImagePoint[i].Save(f)==false)
				return false;
			if(CadPoint[i].Save(f)==false)
				return false;
		}

		for(int i=0;i<10;i++){
			for(int j=0;j<10;j++){
				if(ABox[i][j].Save(f)==false)
					return false;
			}
		}
		if(::Save(f,ABoxXNum)==false)
			return false;
		if(::Save(f,ABoxYNum)==false)
			return false;
		for(int i=0;i<MaxGerberPointNumb;i++){
			if(AMImagePoint[i].Save(f)==false)
				return false;
			if(AMCadPoint[i].Save(f)==false)
				return false;
		}


		if(AlgorithmInPagePI::Save(f)==false)
			return false;

		if(AutoLikeManualData.Save(f)==false)
			return false;

		if(MatchAlignmentArea1.Save(f)==false)
			return false;
		if(MatchAlignmentArea2.Save(f)==false)
			return false;
		if(MatchAlignmentArea3.Save(f)==false)
			return false;

		if(::Save(f,AccessDimXLen)==false)
			return false;
		if(::Save(f,AccessDimYLen)==false)
			return false;

		for(int x=0;x<AccessDimNumbX;x++){
			for(int y=0;y<AccessDimNumbY;y++){
				AccessDim[x][y].Save(f);
			}
		}

		//if(GetPage()==0){
			if(((GerberFastBase *)GetParentBase())->SaveOnly(f)==false)
				return false;
		//}
	}
	return true;
}

bool	GerberFastInPage::Load(QIODevice *f)
{
	GerberFastItemPointerContainerContainerList.RemoveAll();

	if(FileLayerList.Load(f)==false)
		return false;
	if(AutoInterpolation.Load(f)==false)
		return false;
	if(CompositeLayer.Load(f)==false)
		return false;

	if(TriangleAreaData.Load(f)==false)
		return false;
	if(::Load(f,MoveMode)==false)
		return false;
	if(::Load(f,RotateMode)==false)
		return false;
	if(::Load(f,ExtendMode)==false)
		return false;
	if(::Load(f,SlopeXMode)==false)
		return false;
	if(::Load(f,SlopeYMode)==false)
		return false;
	if(::Load(f,AlignmentMode)==false)
		return false;
	if(::Load(f,AutoMatchingMode)==false)
		return false;

	BYTE	d=(BYTE)Mode;
	if(::Load(f,d)==false)
		return false;

	if(::Load(f,LastPosX)==false)
		return false;
	if(::Load(f,LastPosY)==false)
		return false;
	if(::Load(f,MoveStartPosX)==false)
		return false;
	if(::Load(f,MoveStartPosY)==false)
		return false;
	if(::Load(f,RotateCenterXOnData)==false)
		return false;
	if(::Load(f,RotateCenterYOnData)==false)
		return false;
	if(::Load(f,RotateFirstX)==false)
		return false;
	if(::Load(f,RotateFirstY)==false)
		return false;
	if(::Load(f,RotateAngle)==false)
		return false;
	if(::Load(f,ExtendCenterXOnData)==false)
		return false;
	if(::Load(f,ExtendCenterYOnData)==false)
		return false;
	if(::Load(f,ExtendFirstX)==false)
		return false;
	if(::Load(f,ExtendFirstY)==false)
		return false;
	if(::Load(f,SlopeXCenterXOnData)==false)
		return false;
	if(::Load(f,SlopeXCenterYOnData)==false)
		return false;
	if(::Load(f,SlopeXFirstX)==false)
		return false;
	if(::Load(f,SlopeXFirstY)==false)
		return false;
	if(::Load(f,SlopeXAngle)==false)
		return false;
	if(::Load(f,SlopeYCenterXOnData)==false)
		return false;
	if(::Load(f,SlopeYCenterYOnData)==false)
		return false;
	if(::Load(f,SlopeYFirstX)==false)
		return false;
	if(::Load(f,SlopeYFirstY)==false)
		return false;
	if(::Load(f,SlopeYAngle)==false)
		return false;

	for(int i=0;i<MaxGerberPointNumb;i++){
		if(ImagePoint[i].Load(f)==false)
			return false;
		if(CadPoint[i].Load(f)==false)
			return false;
	}

	for(int i=0;i<10;i++){
		for(int j=0;j<10;j++){
			if(ABox[i][j].Load(f)==false)
				return false;
		}
	}
	if(::Load(f,ABoxXNum)==false)
		return false;
	if(::Load(f,ABoxYNum)==false)
		return false;
	for(int i=0;i<MaxGerberPointNumb;i++){
		if(AMImagePoint[i].Load(f)==false)
			return false;
		if(AMCadPoint[i].Load(f)==false)
			return false;
	}

	if(AlgorithmInPagePI::Load(f)==false)
		return false;
	AlgorithmBase	*ABase=GetParentBase();
	if(ABase->GetModeLoadSaveInPlayer()==true || (ABase->GetModeLoadSaveInPlayer()==false && GetLayersBase()->GetModeInspectionPlayer()==false)){

		if(GetLoadedVersion()>=3){
			if(AutoLikeManualData.Load(f)==false)
				return false;
		}
		if(GetLoadedVersion()>=4){
			if(MatchAlignmentArea1.Load(f)==false)
				return false;
		}
		if(GetLoadedVersion()>=4){
			if(MatchAlignmentArea2.Load(f)==false)
				return false;
		}
		if(GetLoadedVersion()>=4){
			if(MatchAlignmentArea3.Load(f)==false)
				return false;
		}

		if(GetLoadedVersion()>=8){
			FastSearchIDItemStart();

			if(::Load(f,AccessDimXLen)==false)
				return false;
			if(::Load(f,AccessDimYLen)==false)
				return false;

			for(int x=0;x<AccessDimNumbX;x++){
				for(int y=0;y<AccessDimNumbY;y++){
					if(AccessDim[x][y].Load(f)==false)
						return false;
					for(AlgorithmItemPointerList *a=AccessDim[x][y].GetFirst();a!=NULL;){
						AlgorithmItemPointerList *NextP=a->GetNext();
						AlgorithmItemRoot	*ap=FastSearchIDItem(a->GetID());
						if(ap!=NULL){
							a->SetPointer(ap);
						}
						else{
							AccessDim[x][y].RemoveList(a);
							delete	a;
						}
						a=NextP;
					}
				}
			}
		}
		if(GetPage()==0){
			//if(((GerberFastBase *)GetParentBase())->LoadOnly(f)==false)
			//	return false;
			((GerberFastBase *)GetParentBase())->LoadOnly(f);
			//If Data is generated in EditPC and SlavePC(B,C,D-) load this data, this is executed and make fales.
		}

		if(GetLoadedVersion()>=8){
			for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
				GerberFastItemBase	*Item=dynamic_cast<GerberFastItemBase *>(a);
				if(Item!=NULL){
					if(Item->RelationParentID>=0){
						Item->RelationParent=dynamic_cast<GerberFastItemBase *>(FastSearchIDItem(Item->RelationParentID));
					}
					else{
						Item->RelationParent=NULL;
					}
				}
			}
		}
	}
	bool	Error=true;
	if(BuildPointer(Error)==false)
		return false;
	if(Error==false)
		return false;
	return true;
}

bool	GerberFastInPage::CheckValidity(void)
{
	for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
		GerberFastItemBase	*item=static_cast<GerberFastItemBase *>(a);
		if(item->CheckValidity()==false)
			return false;
	}
	return true;
}

void	GerberFastInPage::UndoMove		(QIODevice *f)
{
	int32	Numb;
	if(::Load(f,Numb)==false)
		return;
	FastSearchIDItemStart();
	for(int i=0;i<Numb;i++){
		int32	ItemID;
		if(::Load(f,ItemID)==false)
			return;
		AlgorithmItemRoot	*Item=FastSearchIDItem(ItemID);
		if(Item!=NULL){
			((GerberFastItemBase *)Item)->LoadOnlyShape(f);
			((GerberFastItemBase *)Item)->MakeXY();
		}
	}
	SetCurrentSize();
}

void	GerberFastInPage::UndoRotate	(QIODevice *f)
{
	int32	Numb;
	if(::Load(f,Numb)==false)
		return;
	FastSearchIDItemStart();
	for(int i=0;i<Numb;i++){
		int32	ItemID;
		if(::Load(f,ItemID)==false)
			return;
		AlgorithmItemRoot	*Item=FastSearchIDItem(ItemID);
		if(Item!=NULL){
			((GerberFastItemBase *)Item)->LoadOnlyShape(f);
			((GerberFastItemBase *)Item)->MakeXY();
		}
	}
	SetCurrentSize();
}

void	GerberFastInPage::UndoZoom		(QIODevice *f)
{
	int32	Numb;
	if(::Load(f,Numb)==false)
		return;
	FastSearchIDItemStart();
	for(int i=0;i<Numb;i++){
		int32	ItemID;
		if(::Load(f,ItemID)==false)
			return;
		AlgorithmItemRoot	*Item=FastSearchIDItem(ItemID);
		if(Item!=NULL){
			((GerberFastItemBase *)Item)->LoadOnlyShape(f);
			((GerberFastItemBase *)Item)->MakeXY();
		}
	}
	SetCurrentSize();
}

void	GerberFastInPage::UndoShear		(QIODevice *f)
{
	int32	Numb;
	if(::Load(f,Numb)==false)
		return;
	FastSearchIDItemStart();
	for(int i=0;i<Numb;i++){
		int32	ItemID;
		if(::Load(f,ItemID)==false)
			return;
		AlgorithmItemRoot	*Item=FastSearchIDItem(ItemID);
		if(Item!=NULL){
			((GerberFastItemBase *)Item)->LoadOnlyShape(f);
			((GerberFastItemBase *)Item)->MakeXY();
		}
	}
	SetCurrentSize();
}
void	GerberFastInPage::UndoMatchingRoughly(QIODevice *f)
{
	int32	Numb;
	if(::Load(f,Numb)==false)
		return;
	FastSearchIDItemStart();
	for(int i=0;i<Numb;i++){
		int32	ItemID;
		if(::Load(f,ItemID)==false)
			return;
		AlgorithmItemRoot	*Item=FastSearchIDItem(ItemID);
		if(Item!=NULL){
			Item->Load(f,GetLayersBase());
			((GerberFastItemBase *)Item)->MakeXY();
		}
	}
	SetCurrentSize();
}

void	GerberFastInPage::UndoMirror	(QIODevice *f)
{
	int32	Numb;
	if(::Load(f,Numb)==false)
		return;
	FastSearchIDItemStart();
	for(int i=0;i<Numb;i++){
		int32	ItemID;
		if(::Load(f,ItemID)==false)
			return;
		AlgorithmItemRoot	*Item=FastSearchIDItem(ItemID);
		if(Item!=NULL){
			((GerberFastItemBase *)Item)->LoadOnlyShape(f);
			((GerberFastItemBase *)Item)->MakeXY();
		}
	}
	SetCurrentSize();
}

void	GerberFastInPage::UndoCenterize	(QIODevice *f)
{
	int32	Numb;
	if(::Load(f,Numb)==false)
		return;
	FastSearchIDItemStart();
	for(int i=0;i<Numb;i++){
		int32	ItemID;
		if(::Load(f,ItemID)==false)
			return;
		AlgorithmItemRoot	*Item=FastSearchIDItem(ItemID);
		if(Item!=NULL){
			((GerberFastItemBase *)Item)->LoadOnlyShape(f);
			((GerberFastItemBase *)Item)->MakeXY();
		}
	}
	SetCurrentSize();
}

void	GerberFastInPage::UndoCenterizeOnly	(QIODevice *f)
{
	int32	Numb;
	if(::Load(f,Numb)==false)
		return;
	FastSearchIDItemStart();
	for(int i=0;i<Numb;i++){
		int32	ItemID;
		if(::Load(f,ItemID)==false)
			return;
		AlgorithmItemRoot	*Item=FastSearchIDItem(ItemID);
		if(Item!=NULL){
			((GerberFastItemBase *)Item)->LoadOnlyShape(f);
			((GerberFastItemBase *)Item)->MakeXY();
		}
	}
	SetCurrentSize();
}


void	GerberFastInPage::UndoMovePoints(QIODevice *f)
{
	int32	Numb;
	if(::Load(f,Numb)==false)
		return;
	FastSearchIDItemStart();
	for(int i=0;i<Numb;i++){
		int32	ItemID;
		if(::Load(f,ItemID)==false)
			return;
		AlgorithmItemRoot	*Item=FastSearchIDItem(ItemID);
		if(Item!=NULL){
			Item->Load(f,GetLayersBase());
			((GerberFastItemBase *)Item)->MakeXY();
		}
	}
	SetCurrentSize();
}

void	GerberFastInPage::UndoAutoMatch	(QIODevice *f)
{
	int32	Numb;
	if(::Load(f,Numb)==false)
		return;
	FastSearchIDItemStart();
	for(int i=0;i<Numb;i++){
		int32	ItemID;
		if(::Load(f,ItemID)==false)
			return;
		AlgorithmItemRoot	*Item=FastSearchIDItem(ItemID);
		if(Item!=NULL){
			Item->Load(f,GetLayersBase());
			((GerberFastItemBase *)Item)->MakeXY();
		}
	}
	SetCurrentSize();
}
void	GerberFastInPage::UndoGerberDraw(QIODevice *f)
{
	FastSearchIDItemStart();
	for(;;){
		int32	id;
		if(::Load(f,id)==false)
			break;
		AlgorithmItemRoot	*Item=FastSearchIDItem(id);
		if(Item!=NULL){
			RemoveItem(Item);
			delete	Item;
		}
	}
	FastSearchIDItemStart();
	SetCurrentSize();
}

bool	GerberFastInPage::BuildPointer(bool &Error)
{
	for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;){
		GerberFastItemBase	*item=static_cast<GerberFastItemBase *>(a);
		if(item->GetID()<0){
			AlgorithmItemPI	*NextItem=a->GetNext();
			RemoveItem(item);
			delete	item;
			a=NextItem;
		}
		else{
			if(item->BuildPointer(FileLayerList)==false){
				AlgorithmItemPI	*NextItem=a->GetNext();
				RemoveItem(item);
				delete	item;
				a=NextItem;
				Error=true;
			}
			else{
				a=a->GetNext();
			}
		}
	}
	return true;
}
void	GerberFastInPage::SetCurrentSize(void)
{
	AlgorithmItemPI	*a;
	#pragma omp parallel
	#pragma omp single private(a)
	for(a=GetFirstData();a!=NULL;a=a->GetNext()){
		#pragma omp task
		{
			GerberFastItemBase	*item=dynamic_cast<GerberFastItemBase *>(a);
			item->SetCurrentSize();
		}
	}
}

int		GerberFastInPage::GetOwnOrder(int FileLayerID)
{
	int	N=0;
	for(GerberFileLayer *f=FileLayerList.GetFirst();f!=NULL;f=f->GetNext()){
		if(f->FileLayerID==FileLayerID){
			return N;
		}
		N++;
	}
	return -1;
}

void	GerberFastInPage::BuildShapeToArea(void)
{
	AlgorithmItemPI	*a;
	#pragma omp parallel
	#pragma omp single private(a)
	for(a=GetFirstData();a!=NULL;a=a->GetNext()){
		#pragma omp task
		{
			GerberFastItemBase	*item=dynamic_cast<GerberFastItemBase *>(a);
			item->BuildPointer(FileLayerList);
			item->BuildShapeToArea();
		}
	}
}
void	GerberFastInPage::SetFileLayerVisible(IntListFast &ShownFileID,IntListFast &ShownCompositeID)
{
	for(GerberFileLayer *f=FileLayerList.GetFirst();f!=NULL;f=f->GetNext()){
		f->Visible=false;
	}

	for(IntClass *b=ShownFileID.GetFirst();b!=NULL;b=b->GetNext()){
		int	N=b->GetValue();
		if(FileLayerList[N]!=NULL){
			FileLayerList[N]->Visible=true;
		}
	}
	for(GerberCompositeLayer *k=CompositeLayer.GetFirst();k!=NULL;k=k->GetNext()){
		k->Visible=false;
	}
	for(IntClass *b=ShownCompositeID.GetFirst();b!=NULL;b=b->GetNext()){
		int	CompositeID=b->GetValue();
		GerberCompositeLayer	*CL=SearchCompositeLayer(CompositeID);
		if(CL!=NULL){
			CL->Visible=true;
		}
	}
	for(GerberFileLayer *g=FileLayerList.GetFirst();g!=NULL;g=g->GetNext()){
		g->ViewInvert=false;
	}
}

static	int	PriorityMapSortFunc(const void *a ,const void *b)
{
	if(((struct WPriorityMapClass *)a)->DrawingPriority>((struct WPriorityMapClass *)b)->DrawingPriority){
		return -1;
	}
	if(((struct WPriorityMapClass *)a)->DrawingPriority<((struct WPriorityMapClass *)b)->DrawingPriority){
		return 1;
	}
	return 0;
}
GerberFastItemPointerContainer::GerberFastItemPointerContainer(bool FileLayerMode ,int ID)
{	
	if(FileLayerMode==true){
		FileLayerID=ID;
		CompositeID=-1;
	}
	else{
		FileLayerID=-1;
		CompositeID=ID;
	}
	FastPointer=NULL;
}

GerberFastItemPointerContainer::~GerberFastItemPointerContainer(void)
{
	if(FastPointer!=NULL){
		delete	[]FastPointer;
		FastPointer=NULL;
	}
}

int	GerberFastItemPointerContainer::Draw(int page ,QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr,QImage &hpnt,struct WPriorityMapClass	*PriorityMap ,int KNumb)
{
	QColor	NormalColor	=GetColor(Attr);
	if((page&1)!=0){
		NormalColor.setRed	(NormalColor.red()*0.7);
		NormalColor.setGreen(NormalColor.green()*0.7);
		NormalColor.setBlue	(NormalColor.blue()*0.7);
	}
	int	ImageWidth	=pnt.width();
	int	ImageHeight	=pnt.height();

	GerberFastItemPointer *FirstOne=PointerList.GetFirst();
	if(FirstOne!=NULL){
		int		HNumb=FirstOne->GetPoint()->GetParent()->GetItemCount();
		GerberFastItemBase	**BasePointer=new GerberFastItemBase*[HNumb];

		bool	PosiImage;
		while(FirstOne!=NULL){
			int					BaseNumb=0;

			BasePointer[BaseNumb]=FirstOne->GetPoint();
			BaseNumb++;
			PriorityMap[KNumb].Point=FirstOne->GetPoint();
			KNumb++;

			PosiImage=FirstOne->GetPoint()->PosiImage;
			GerberFastItemPointer *t;
			for(t=FirstOne->GetNext();t!=NULL;t=t->GetNext()){
				if(t->GetPoint()->PosiImage!=PosiImage){
					break;
				}
				BasePointer[BaseNumb]=t->GetPoint();
				BaseNumb++;
				PriorityMap[KNumb].Point=t->GetPoint();
				KNumb++;
			}
			GerberFastItemPointer *EndOne=t;


			//#pragma omp parallel	num_threads(8)                           
			//{                                                
			//	#pragma omp for
				for(int i=0;i<BaseNumb;i++){
					GerberFastItemBase	*c=BasePointer[i];
					int	x1 ,y1 ,x2 ,y2;
					if(c->IsExist(ZoomRate ,movx ,movy ,ImageWidth ,ImageHeight ,x1 ,y1 ,x2 ,y2)==true){
						//if((x2-x1)*(y2-y1)<20 && (i&0x1f)!=0)
						//	continue;
						if(c->GetSelected()==true){
							Attr->NormalColor=Attr->SelectedColor;
						}
						else if(c->GetActive()==true){
							Attr->NormalColor=Attr->ActiveColor;
						}
						else{
							Attr->NormalColor=NormalColor;
						}
						if(c->GetVisible()==true){
							if(c->DrawSimple(pnt, x1 ,y1 ,x2 ,y2,ImageWidth ,ImageHeight,(c->PosiImage==true)?Attr->NormalColor.rgba():NegaColor.rgba())==false){
								c->Draw(pnt, movx ,movy ,ZoomRate ,Attr);
							}
							QColor	Col(Qt::red);
							c->TransDetail.Draw(0,0,hpnt ,movx ,movy ,ZoomRate , Col);
						}
					}
				}
			//}

			FirstOne=EndOne;
		}
		delete	[]BasePointer;
	}
	return KNumb;
}
void	GerberFastItemPointerContainer::DrawBase(int dx ,int dy,QImage &pnt, int movx ,int movy ,double ZoomRate , const QColor &Color,bool ThreadMode)
{
	bool	PosiImage;
	GerberFastItemPointer *FirstOne=PointerList.GetFirst();
	while(FirstOne!=NULL){
		PosiImage=FirstOne->GetPoint()->PosiImage;
		GerberFastItemPointer *t;
		for(t=FirstOne->GetNext();t!=NULL;t=t->GetNext()){
			if(t->GetPoint()->PosiImage!=PosiImage){
				break;
			}
		}
		GerberFastItemPointer *EndOne=t;

		if(ThreadMode==true){
			GerberFastItemPointer *a;
			#pragma omp parallel
			#pragma omp single private(a)
			for(a=FirstOne;a!=EndOne;a=a->GetNext()){
				#pragma omp task
				{
				a->GetPoint()->DrawBase(dx ,dy,pnt, movx ,movy ,ZoomRate ,(PosiImage==true)?Color:NegaColor);
				}
			}
		}
		else{
			for(GerberFastItemPointer *a=FirstOne;a!=EndOne;a=a->GetNext()){
				a->GetPoint()->DrawBase(dx ,dy,pnt, movx ,movy ,ZoomRate ,(PosiImage==true)?Color:NegaColor);
			}
		}
		FirstOne=EndOne;
	}
}
QColor	GerberFastItemPointerContainer::GetColor(AlgorithmDrawAttr *Attr)
{
	QColor	RetColor;
	int	Number=GetFileLayerID();
	if(Number>=0){
		GerberFastDrawAttr	*a=(GerberFastDrawAttr *)Attr;
		int	SCode=0;
		for(int i=0;i<MaxGerberLayer;i++){
			if(a->FileLayerIDTable[i]==Number){
				SCode=i;
				break;
			}
		}
		RetColor	=a->LayerColor[SCode%MaxGerberLayer];
		RetColor.setAlpha(160);
		return RetColor;
	}
	Number=GetCompositeID();
	if(Number>=0){
		GerberFastDrawAttr	*a=(GerberFastDrawAttr *)Attr;
		RetColor	=a->CompColor[Number%MaxGerberLayer];
		RetColor.setAlpha(160);
		return RetColor;
	}
	return Qt::darkGray;
}

GerberFileLayer	*GerberFastItemPointerContainer::GetFileLayer(GerberFastInPage &PageData)
{
	return PageData.FileLayerList.Find(FileLayerID);
}

void	GerberFastItemPointerContainer::AddItem(GerberFastItemBase *p)
{
	PointerList.AppendList(new GerberFastItemPointer(p));
}

bool	GerberFastItemPointerContainer::InsertBehind(GerberFastItemBase *Key , GerberFastItemBase *addItem)
{
	for(GerberFastItemPointer *a=PointerList.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetPoint()==Key){
			GerberFastItemPointer	*p=new GerberFastItemPointer(addItem);
			PointerList.InsertLater(a,p);
			return true;
		}
	}
	return false;
}
void	GerberFastItemPointerContainer::RemoveItem(GerberFastItemBase *p)
{
	for(GerberFastItemPointer *a=PointerList.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetPoint()==p){
			PointerList.RemoveList(a);
			delete	a;
			break;
		}
	}
}

static	int	SortFastPointerFunc(const void *a ,const void *b)
{
	struct	ItemBaseAndPointer *pa=((struct	ItemBaseAndPointer *)a);
	struct	ItemBaseAndPointer *pb=((struct	ItemBaseAndPointer *)b);
	uint64	ma=(uint64)pa->Item;
	uint64	mb=(uint64)pb->Item;
	if(ma>mb)
		return 1;
	else if(ma<mb)
		return -1;
	return 0;
}
void	GerberFastItemPointerContainer::BuildFastIndex(void)
{
	if(FastPointer!=NULL){
		delete	[]FastPointer;
	}
	FastPointer=new struct	ItemBaseAndPointer[PointerList.GetCount()];
	int	Index=0;
	for(GerberFastItemPointer *a=PointerList.GetFirst();a!=NULL;a=a->GetNext(),Index++){
		FastPointer[Index].Item	=a->GetPoint();
		FastPointer[Index].Pointer	=a;
	}
	QSort(FastPointer,Index,sizeof(FastPointer[0]),SortFastPointerFunc);
}

void	GerberFastItemPointerContainer::RemoveItemFast(GerberFastItemBase *p)
{
	struct	ItemBaseAndPointer	Key;
	Key.Item=p;
	Key.Pointer	=NULL;

	struct	ItemBaseAndPointer	*a=(struct	ItemBaseAndPointer	*)bsearch(&Key,FastPointer,PointerList.GetCount(),sizeof(FastPointer[0]),SortFastPointerFunc);
	if(a!=NULL){
		PointerList.RemoveList(a->Pointer);
		delete	a->Pointer;
	}
}

GerberFastItemBase	*GerberFastItemPointerContainer::GetFirst(void)
{
	GerberFastItemPointer *a=PointerList.GetFirst();
	if(a!=NULL)
		return a->GetPoint();
	return NULL;
}
void	GerberFastItemPointerContainer::MakeImage(BYTE **Image ,int dx ,int dy ,int XByte ,int YLen)
{
	bool	PosiImage;
	GerberFastItemPointer *FirstOne=PointerList.GetFirst();
	while(FirstOne!=NULL){
		PosiImage=FirstOne->GetPoint()->PosiImage;
		GerberFastItemPointer *t;
		for(t=FirstOne->GetNext();t!=NULL;t=t->GetNext()){
			if(t->GetPoint()->PosiImage!=PosiImage){
				break;
			}
		}
		GerberFastItemPointer *EndOne=t;

		GerberFastItemPointer *a;
		#pragma omp parallel
		#pragma omp single private(a)
		for(a=FirstOne;a!=EndOne;a=a->GetNext()){
			#pragma omp task
			{
				a->GetPoint()->MakeImage(Image ,dx ,dy ,XByte ,YLen);
			}
		}
		FirstOne=EndOne;
	}
}

GerberFastItemPointerContainer	*GerberFastItemPointerContainerContainer::Search(int	FileLayerID)
{
	for(GerberFastItemPointerContainer *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetFileLayerID()==FileLayerID){
			return a;
		}
	}
	return NULL;
}
GerberFastItemPointerContainer	*GerberFastItemPointerContainerContainer::SearchComposite(int CompositeID)
{
	for(GerberFastItemPointerContainer *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetCompositeID()==CompositeID){
			return a;
		}
	}
	return NULL;
}


bool	GerberFastInPage::AppendItem(AlgorithmItemRoot *item)
{
	if(AlgorithmInPagePI::AppendItem(item)==false)
		return false;
	GerberFastItemBase	*p=static_cast<GerberFastItemBase *>(item);
	if(p->GetItemClassType()==5){	//Composite mode
		GerberFastItemPointerContainer	*L=GerberFastItemPointerContainerContainerList.SearchComposite(p->GetCompositeID());
		if(L==NULL){
			L=new GerberFastItemPointerContainer(false,p->GetCompositeID());
			GerberFastItemPointerContainerContainerList.AppendList(L);
		}
		p->SetCurrentSize();
		L->AddItem(p);
	}
	else{
		GerberFastItemPointerContainer	*L=GerberFastItemPointerContainerContainerList.Search(p->GetFileLayerID());
		if(L==NULL){
			L=new GerberFastItemPointerContainer(true,p->GetFileLayerID());
			GerberFastItemPointerContainerContainerList.AppendList(L);
		}
		L->AddItem(p);
	}
	return true;
}

void	GerberFastInPage::AddAccessDim(GerberFastItemBase *p)
{
	int	x1,y1,x2,y2;
	p->GetXY(x1,y1,x2,y2);
	if(0<x2 && x1<GetDotPerLine() && 0<y2 && y1<GetMaxLines()){
		x1=Clipping(x1,0,GetDotPerLine());
		x2=Clipping(x2,0,GetDotPerLine());
		y1=Clipping(y1,0,GetMaxLines());
		y2=Clipping(y2,0,GetMaxLines());
		if(x1!=x2 && y1!=y2){
			int	px1=x1/AccessDimXLen;
			int	px2=x2/AccessDimXLen;
			int	py1=y1/AccessDimYLen;
			int	py2=y2/AccessDimYLen;
			for(int yn=py1;yn<=py2;yn++){
				for(int xn=px1;xn<=px2;xn++){
					AccessDim[xn][yn].Add(p);
				}
			}
		}
	}
}
void	GerberFastInPage::ClearAccessDim(void)
{
	for(int yn=0;yn<AccessDimNumbY;yn++){
		for(int xn=0;xn<AccessDimNumbX;xn++){
			AccessDim[xn][yn].RemoveAll();
		}
	}
}

bool	GerberFastInPage::AppendItem(int Layer ,AlgorithmItemRoot *item)
{
	if(AlgorithmInPagePI::AppendItem(Layer ,item)==false)
		return false;
	GerberFastItemBase	*p=static_cast<GerberFastItemBase *>(item);
	if(p->GetItemClassType()==5){	//Composite mode
		GerberFastItemPointerContainer	*L=GerberFastItemPointerContainerContainerList.SearchComposite(p->GetCompositeID());
		if(L==NULL){
			L=new GerberFastItemPointerContainer(false,p->GetCompositeID());
			GerberFastItemPointerContainerContainerList.AppendList(L);
		}
		L->AddItem(p);
	}
	else{
		GerberFastItemPointerContainer	*L=GerberFastItemPointerContainerContainerList.Search(p->GetFileLayerID());
		if(L==NULL){
			L=new GerberFastItemPointerContainer(true,p->GetFileLayerID());
			GerberFastItemPointerContainerContainerList.AppendList(L);
		}
		L->AddItem(p);
	}
	return true;
}

bool	GerberFastInPage::AppendItemFromLoad(AlgorithmItemRoot *item)
{
	if(AlgorithmInPagePI::AppendItemFromLoad(item)==false)
		return false;
	GerberFastItemBase	*p=static_cast<GerberFastItemBase *>(item);
	if(p->GetItemClassType()==5){	//Composite mode
		GerberFastItemPointerContainer	*L=GerberFastItemPointerContainerContainerList.SearchComposite(p->GetCompositeID());
		if(L==NULL){
			L=new GerberFastItemPointerContainer(false,p->GetCompositeID());
			GerberFastItemPointerContainerContainerList.AppendList(L);
		}
		L->AddItem(p);
	}
	else{
		GerberFastItemPointerContainer	*L=GerberFastItemPointerContainerContainerList.Search(p->GetLoadedFileLayerID());
		if(L==NULL){
			L=new GerberFastItemPointerContainer(true,p->GetLoadedFileLayerID());
			GerberFastItemPointerContainerContainerList.AppendList(L);
		}
		L->AddItem(p);
	}
	return true;
}

void	GerberFastInPage::RemoveItem(AlgorithmItemRoot *item)
{
	AlgorithmInPagePI::RemoveItem(item);
	GerberFastItemBase	*p=static_cast<GerberFastItemBase *>(item);
	if(p->GetItemClassType()==5){	//Composite mode
		GerberFastItemPointerContainer	*L=GerberFastItemPointerContainerContainerList.SearchComposite(p->GetCompositeID());
		if(L!=NULL){
			L->RemoveItem(p);
		}
	}
	else{
		GerberFastItemPointerContainer	*L=GerberFastItemPointerContainerContainerList.Search(p->GetFileLayerID());
		if(L!=NULL){
			L->RemoveItem(p);
		}
	}
}

bool	GerberFastInPage::AppendItem(AlgorithmItemRoot *item ,int64 itemID)
{
	if(AlgorithmInPagePI::AppendItem(item ,itemID)==false)
		return false;
	GerberFastItemBase	*p=static_cast<GerberFastItemBase *>(item);
	if(p->GetItemClassType()==5){	//Composite mode
		GerberFastItemPointerContainer	*L=GerberFastItemPointerContainerContainerList.SearchComposite(p->GetCompositeID());
		if(L==NULL){
			L=new GerberFastItemPointerContainer(false,p->GetCompositeID());
			GerberFastItemPointerContainerContainerList.AppendList(L);
		}
		L->AddItem(p);
	}
	else{
		GerberFastItemPointerContainer	*L=GerberFastItemPointerContainerContainerList.Search(p->GetFileLayerID());
		if(L==NULL){
			L=new GerberFastItemPointerContainer(true,p->GetFileLayerID());
			GerberFastItemPointerContainerContainerList.AppendList(L);
		}
		L->AddItem(p);
	}
	return true;
}
void	GerberFastInPage::InsertItem(AlgorithmItemRoot *item,AlgorithmItemRoot *Key)
{
	AlgorithmInPagePI::InsertItem(item,Key);
	GerberFastItemBase	*p=static_cast<GerberFastItemBase *>(item);
	if(p->GetItemClassType()==5){	//Composite mode
		GerberFastItemPointerContainer	*L=GerberFastItemPointerContainerContainerList.SearchComposite(p->GetCompositeID());
		if(L==NULL){
			L=new GerberFastItemPointerContainer(false,p->GetCompositeID());
			GerberFastItemPointerContainerContainerList.AppendList(L);
		}
		if(L->InsertBehind((GerberFastItemBase	*)Key,p)==false){
			L->AddItem(p);
		}
	}
	else{
		GerberFastItemPointerContainer	*L=GerberFastItemPointerContainerContainerList.Search(p->GetFileLayerID());
		if(L==NULL){
			L=new GerberFastItemPointerContainer(true,p->GetFileLayerID());
			GerberFastItemPointerContainerContainerList.AppendList(L);
		}
		if(L->InsertBehind((GerberFastItemBase	*)Key,p)==false){
			L->AddItem(p);
		}
	}
}


void	GerberFastInPage::RemoveAllDatas(void)
{
	AlgorithmInPagePI::RemoveAllDatas();
	GerberFastItemPointerContainerContainerList.RemoveAll();
}

void	GerberFastInPage::Draw(QImage &pnt, IntList &LayerList ,int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	GerberFastDrawAttr	*GAttr=(GerberFastDrawAttr *)Attr;
	GerberFastBase	*Base=(GerberFastBase *)GetParentBase();

	if(ImagingBmp!=NULL){
		DrawBitImage(pnt, (const BYTE **)ImagingBmp,ImagingBmpXByte*8,ImagingBmpXByte,ImagingBmpYLen
			,(movx<0)?movx:0 ,(movy<0)?movy:0,ZoomRate
				,0,0
				,Base->ColorImaging);
	}

	QColor	MCol1=Base->AutoMatchManualColorParallel;
	MCol1.setAlpha(145);
	for(MatchAlignmentArea *a=MatchAlignmentArea1.GetFirst();a!=NULL;a=a->GetNext()){
		a->Draw(pnt,movx,movy,ZoomRate,MCol1);
	}
	QColor	MCol2=Base->AutoMatchManualColorRotation;
	MCol2.setAlpha(145);
	for(MatchAlignmentArea *a=MatchAlignmentArea2.GetFirst();a!=NULL;a=a->GetNext()){
		a->Draw(pnt,movx,movy,ZoomRate,MCol2);
	}
	QColor	MCol3=Base->AutoMatchManualColorZooming;
	MCol3.setAlpha(145);
	for(MatchAlignmentArea *a=MatchAlignmentArea3.GetFirst();a!=NULL;a=a->GetNext()){
		a->Draw(pnt,movx,movy,ZoomRate,MCol3);
	}

	//??a???a?I?i?e?A?l?K??W?O?W?a?I?i?A?A?μ?U???I?A?A?f?t?H???g??a?d?g?p?μ?E?￠
	//AlgorithmInPagePI::Draw(pnt, LayerList ,movx ,movy ,ZoomRate ,Attr);

	//for(AlgorithmItemPI *c=Data.GetFirst();c!=NULL;c=c->GetNext()){
	//	c->Draw(pnt, movx ,movy ,ZoomRate ,Attr);
	//}
	QPainter	Pnt(&pnt);

	int	N=GetItemCount();
	struct	WPriorityMapClass	*PriorityMap=new struct	WPriorityMapClass[2*N];
	int	KNumb=0;

	QImage	*TmpImage	=new QImage(pnt.width(),pnt.height(),QImage::Format_ARGB32);
	for(GerberFastItemPointerContainer *a=GerberFastItemPointerContainerContainerList.GetFirst();a!=NULL;a=a->GetNext()){		
		if(GAttr->ShownFileID.IsInclude(a->GetFileLayerID())==true){
			TmpImage->fill(0);
			KNumb=a->Draw(GetPage(),*TmpImage, movx ,movy ,ZoomRate ,Attr,pnt,PriorityMap,KNumb);
			Pnt.drawImage(0,0,*TmpImage);
		}
		if(GAttr->ShownCompositeID.IsInclude(a->GetCompositeID())==true){
			TmpImage->fill(0);
			KNumb=a->Draw(GetPage(),*TmpImage, movx ,movy ,ZoomRate ,Attr,pnt,PriorityMap,KNumb);
			Pnt.drawImage(0,0,*TmpImage);
		}
	}
	delete	TmpImage;


	int	CanvasWidth=pnt.width();
	int	CanvasHeight=pnt.height();


	int	hx1=(movx					)*ZoomRate;
	int	hy1=(movy					)*ZoomRate;
	int	hx2=(movx+GetDotPerLine()	)*ZoomRate;
	int	hy2=(movy+GetMaxLines()		)*ZoomRate;
	
	if(hx2<0 || CanvasWidth<=hx1
	|| hy2<0 || CanvasHeight<=hy1){
		delete	[]PriorityMap;
		return;
	}
	hx1=max(hx1,0);
	hy1=max(hy1,0);
	hx2=min(hx2,CanvasWidth);
	hy2=min(hy2,CanvasHeight);

	XYData	*xy=GetLayersBase()->GetGlobalOutlineOffset(GetLayersBase()->GetGlobalPageFromLocal(GetPage()));
	
	DataInPage	*Dp=GetDataInPage();

	/*
	for(AlgorithmItemPI *c=Data.GetFirst();c!=NULL;c=c->GetNext()){
		if(c->GetVisible()==false)
			continue;
		if(c->GetSelected()==false)
			continue;
		PriorityMap[KNumb].Point=c;
		KNumb++;
	}
	*/

	#pragma omp parallel                             
	{                                                
		#pragma omp for
		for(int i=0;i<KNumb;i++){
			AlgorithmItemPI *c=PriorityMap[i].Point;
			PriorityMap[i].DrawingPriority=0x60000000 | c->GetDrawPriprity(movx ,movy ,ZoomRate ,Attr);
			if(c->GetSelected()==true){
				PriorityMap[i].DrawingPriority &= ~0x20000000;
			}
			if(c->GetActive()==true){
				PriorityMap[i].DrawingPriority &= ~0x40000000;
			}
		}
	}
	QSort(PriorityMap,KNumb,sizeof(struct WPriorityMapClass),PriorityMapSortFunc);

	if(GAttr->DrawAutoMatchingArea==true){
		for(int xn=0;xn<ABoxXNum;xn++){
			for(int yn=0;yn<ABoxYNum;yn++){
				ABox[yn][xn].Draw(Pnt,pnt ,movx ,movy ,ZoomRate ,Attr);
			}
		}
	}
	if(GAttr->DrawAutoMatchingArea==true){
		AutoLikeManualData.Draw(Pnt,pnt, movx ,movy ,ZoomRate ,Attr);
	}
	SparsContainerData.Draw(Pnt,movx,movy,ZoomRate,qRgb(255,128,9),pnt.width(),pnt.height());

	QRgb	ClusterCol=qRgba(192,0,192,128);
	for(GerberFastClusterItemList *a=ClusterItemContainer.GetFirst();a!=NULL;a=a->GetNext()){
		a->Area.DrawAlpha(0 ,0 ,&pnt ,ClusterCol
									,ZoomRate ,movx ,movy);
	}

	if(RotateMode==true){
		if(Mode==DisplayImage::_RotateMoveAngleStart || Mode==DisplayImage::_RotateMoveAngling){
			Pnt.setPen(Qt::red);
			int	x=(RotateCenterXOnData+movx)*ZoomRate;
			int	y=(RotateCenterYOnData+movy)*ZoomRate;
			Pnt.drawLine(x-15,y,x+15,y);
			Pnt.drawLine(x,y-15,x,y+15);
		
			if(Mode==DisplayImage::_RotateMoveAngling){
				int	gx1=-movx;
				int	gy1=-movy;
				int	gx2=gx1+CanvasWidth /ZoomRate;
				int	gy2=gy1+CanvasHeight/ZoomRate;
			
				int	Lx1=gx1;
				int	Ly1=gy1;
				int	Lx2=gx2;
				int	Ly2=gy1;
				int	Lx3=gx1;
				int	Ly3=gy2;
				int	Lx4=gx2;
				int	Ly4=gy2;
					
				Dp->GetGlobalMatrixFromLocalInMaster(gx1,gy1,Lx1,Ly1);
				Dp->GetGlobalMatrixFromLocalInMaster(gx2,gy1,Lx2,Ly2);
				Dp->GetGlobalMatrixFromLocalInMaster(gx1,gy2,Lx3,Ly3);
				Dp->GetGlobalMatrixFromLocalInMaster(gx2,gy2,Lx4,Ly4);

				//double	LCx=(gx1+gx2)/2.0;
				//double	LCy=(gy1+gy2)/2.0;
				double	LCx=(Lx1+Lx4)/2.0;
				double	LCy=(Ly1+Ly4)/2.0;
				double	s=-RotateAngle;
				double	coss=cos(s);
				double	sins=sin(s);
				//int	iRotateCenterXOnData;
				//int	iRotateCenterYOnData;
				//Dp->GetGlobalMatrixFromLocalInMaster(RotateCenterXOnData	,RotateCenterYOnData
				//									,iRotateCenterXOnData	,iRotateCenterYOnData);
				//double	MCx=(LCx-iRotateCenterXOnData)*coss - (LCy-iRotateCenterYOnData)*sins + iRotateCenterXOnData;
				//double	MCy=(LCx-iRotateCenterXOnData)*sins + (LCy-iRotateCenterYOnData)*coss + iRotateCenterYOnData;
				double	MCx=(LCx-RotateCenterXOnData)*coss - (LCy-RotateCenterYOnData)*sins + RotateCenterXOnData;
				double	MCy=(LCx-RotateCenterXOnData)*sins + (LCy-RotateCenterYOnData)*coss + RotateCenterYOnData;
				double	MLx1=(Lx1-LCx)*coss - (Ly1-LCy)*sins + MCx;
				double	MLy1=(Lx1-LCx)*sins + (Ly1-LCy)*coss + MCy;
				double	MLx2=(Lx2-LCx)*coss - (Ly2-LCy)*sins + MCx;
				double	MLy2=(Lx2-LCx)*sins + (Ly2-LCy)*coss + MCy;
				double	MLx3=(Lx3-LCx)*coss - (Ly3-LCy)*sins + MCx;
				double	MLy3=(Lx3-LCx)*sins + (Ly3-LCy)*coss + MCy;
				double	MLx4=(Lx4-LCx)*coss - (Ly4-LCy)*sins + MCx;
				double	MLy4=(Lx4-LCx)*sins + (Ly4-LCy)*coss + MCy;
	
				//int	MPx1=floor(min(min(MLx1,MLx2),min(MLx3,MLx4)));
				//int	MPy1=floor(min(min(MLy1,MLy2),min(MLy3,MLy4)));
				//int	MPx2=ceil (max(max(MLx1,MLx2),max(MLx3,MLx4)));
				//int	MPy2=ceil (max(max(MLy1,MLy2),max(MLy3,MLy4)));

				#pragma omp parallel                           
				{                                                
					#pragma omp for
					for(int i=0;i<KNumb;i++){
						GerberFastItemBase	*c=((GerberFastItemBase *)PriorityMap[i].Point);
						int	x1 ,y1 ,x2 ,y2;
						if(c->IsExistRotate(ZoomRate ,movx ,movy ,CanvasWidth ,CanvasHeight ,x1 ,y1 ,x2 ,y2
																		  ,-RotateAngle,RotateCenterXOnData	,RotateCenterYOnData)==true){
							if((x2-x1)*(y2-y1)>=20 || (i&0x1f)==0){
								if(c->DrawSimple(pnt, x1 ,y1 ,x2 ,y2,CanvasWidth ,CanvasHeight,(c->PosiImage==true)?Attr->NormalColor.rgba():NegaColor.rgba())==false){
									c->DrawRotate(pnt, movx ,movy ,ZoomRate ,Attr
																		  //,iRotateCenterXOnData	,iRotateCenterYOnData
																		  ,RotateCenterXOnData	,RotateCenterYOnData,-RotateAngle);
								}
							}
						}
					}
				}
				Pnt.setPen(Qt::red);
				int	cx=(RotateCenterXOnData+movx)*ZoomRate;
				int	cy=(RotateCenterYOnData+movy)*ZoomRate;
				int	x1=(RotateFirstX+movx)*ZoomRate;
				int	y1=(RotateFirstY+movy)*ZoomRate;
				int	x2=(LastPosX+movx)*ZoomRate;
				int	y2=(LastPosY+movy)*ZoomRate;
				Pnt.drawLine(cx,cy,x1,y1);
				Pnt.drawLine(cx,cy,x2,y2);
			}
		}
	}
	else if(ExtendMode==true){
		if(Mode==DisplayImage::_ExtendMoveStart || Mode==DisplayImage::_ExtendMoving){
			Pnt.setPen(Qt::red);
			int	x=(ExtendCenterXOnData+movx)*ZoomRate;
			int	y=(ExtendCenterYOnData+movy)*ZoomRate;
			Pnt.drawLine(x-15,y,x+15,y);
			Pnt.drawLine(x,y-15,x,y+15);
	
			if(Mode==DisplayImage::_ExtendMoving){
				//int	gExtendCenterXOnData,gExtendCenterYOnData;

				//Dp->GetGlobalMatrixFromLocalInMaster(ExtendCenterXOnData	,ExtendCenterYOnData
				//									,gExtendCenterXOnData	,gExtendCenterYOnData);

				Pnt.setPen(Qt::yellow);
				int	rx1=abs(ExtendFirstX-ExtendCenterXOnData);
				int	ry1=abs(ExtendFirstY-ExtendCenterYOnData);
				int	rx2=abs(LastPosX-ExtendCenterXOnData);
				int	ry2=abs(LastPosY-ExtendCenterYOnData);
				int	x11=(ExtendCenterXOnData-rx1+movx)*ZoomRate;
				int	y11=(ExtendCenterYOnData-ry1+movy)*ZoomRate;
				int	x12=(ExtendCenterXOnData+rx1+movx)*ZoomRate;
				int	y12=(ExtendCenterYOnData+ry1+movy)*ZoomRate;
				int	x21=(ExtendCenterXOnData-rx2+movx)*ZoomRate;
				int	y21=(ExtendCenterYOnData-ry2+movy)*ZoomRate;
				int	x22=(ExtendCenterXOnData+rx2+movx)*ZoomRate;
				int	y22=(ExtendCenterYOnData+ry2+movy)*ZoomRate;
				double	Zx=1.0;
				double	Zy=1.0;
				if(rx1!=0)
					Zx=(double)rx2/(double)rx1;
				if(ry1!=0)
					Zy=(double)ry2/(double)ry1;
				int	gx1=-movx;
				int	gy1=-movy;
				int	gx2=gx1+CanvasWidth /ZoomRate;
				int	gy2=gy1+CanvasHeight/ZoomRate;
				int	Lx1,Ly1;
				int	Lx2,Ly2;
				Dp->GetGlobalMatrixFromLocalInMaster(gx1,gy1,Lx1,Ly1);
				Dp->GetGlobalMatrixFromLocalInMaster(gx2,gy2,Lx2,Ly2);

				//int	ngx1=(Lx1-gExtendCenterXOnData)/Zx+gExtendCenterXOnData;
				//int	ngy1=(Ly1-gExtendCenterYOnData)/Zy+gExtendCenterYOnData;
				//int	ngx2=(Lx2-gExtendCenterXOnData)/Zx+gExtendCenterXOnData;
				//int	ngy2=(Ly2-gExtendCenterYOnData)/Zy+gExtendCenterYOnData;

				#pragma omp parallel                          
				{                                                
					#pragma omp for
					for(int i=0;i<KNumb;i++){
						GerberFastItemBase	*c=((GerberFastItemBase *)PriorityMap[i].Point);
						int	x1 ,y1 ,x2 ,y2;
						if(c->IsExistZoom(ZoomRate ,movx ,movy ,CanvasWidth ,CanvasHeight ,x1 ,y1 ,x2 ,y2
																		  ,Zx,Zy,ExtendCenterXOnData	,ExtendCenterYOnData)==true){
							if((x2-x1)*(y2-y1)>=20 || (i&0x1f)==0){
								if(c->DrawSimple(pnt, x1 ,y1 ,x2 ,y2,CanvasWidth ,CanvasHeight,(c->PosiImage==true)?Attr->NormalColor.rgba():NegaColor.rgba())==false){
									c->DrawZoom(pnt, movx ,movy ,ZoomRate ,Attr
																		  //,iRotateCenterXOnData	,iRotateCenterYOnData
																		 ,ExtendCenterXOnData	,ExtendCenterYOnData,Zx,Zy);
								}
							}
						}
					}
				}
				Pnt.drawLine(x11,y11,x12,y11);
				Pnt.drawLine(x12,y11,x12,y12);
				Pnt.drawLine(x12,y12,x11,y12);
				Pnt.drawLine(x11,y12,x11,y11);
				Pnt.setPen(Qt::red);
				Pnt.drawLine(x21,y21,x22,y21);
				Pnt.drawLine(x22,y21,x22,y22);
				Pnt.drawLine(x22,y22,x21,y22);
				Pnt.drawLine(x21,y22,x21,y21);
			}
		}
	}
	else if(SlopeXMode==true){
		if(Mode==DisplayImage::_SlopeXMoveAngleStart || Mode==DisplayImage::_SlopeXMoveAngling){
			Pnt.setPen(Qt::red);
			int	x=(SlopeXCenterXOnData+movx)*ZoomRate;
			int	y=(SlopeXCenterYOnData+movy)*ZoomRate;
			Pnt.drawLine(x-15,y,x+15,y);
			Pnt.drawLine(x,y-15,x,y+15);
		
			if(Mode==DisplayImage::_SlopeXMoveAngling){
				int	gx1=-movx;
				int	gy1=-movy;
				//int	gx1=0;
				//int	gy1=0;
				int	gx2=gx1+CanvasWidth /ZoomRate;
				int	gy2=gy1+CanvasHeight/ZoomRate;
			
				int	Lx1=gx1;
				int	Ly1=gy1;
				int	Lx2=gx2;
				int	Ly2=gy1;
				int	Lx3=gx1;
				int	Ly3=gy2;
				int	Lx4=gx2;
				int	Ly4=gy2;
					
				//Dp->GetGlobalMatrixFromLocalInMaster(gx1,gy1,Lx1,Ly1);
				//Dp->GetGlobalMatrixFromLocalInMaster(gx2,gy1,Lx2,Ly2);
				//Dp->GetGlobalMatrixFromLocalInMaster(gx1,gy2,Lx3,Ly3);
				//Dp->GetGlobalMatrixFromLocalInMaster(gx2,gy2,Lx4,Ly4);

				double	LCx=(Lx1+Lx4)/2.0;
				double	LCy=(Ly1+Ly4)/2.0;
				double	s=SlopeXAngle;
				double	coss=cos(s);
				double	sins=sin(s);
				//int	iSlopeXCenterXOnData;
				//int	iSlopeXCenterYOnData;
				//Dp->GetGlobalMatrixFromLocalInMaster(SlopeXCenterXOnData	,SlopeXCenterYOnData
				//									,iSlopeXCenterXOnData	,iSlopeXCenterYOnData);
				//double	MCx=(LCx-iSlopeXCenterXOnData)*coss - (LCy-iSlopeXCenterYOnData)*sins + iSlopeXCenterXOnData;
				//double	MCy=(LCx-iSlopeXCenterXOnData)*sins + (LCy-iSlopeXCenterYOnData)*coss + iSlopeXCenterYOnData;
				double	MCx=(LCx-SlopeXCenterXOnData)*coss - (LCy-SlopeXCenterYOnData)*sins + SlopeXCenterXOnData;
				double	MCy=(LCx-SlopeXCenterXOnData)*sins + (LCy-SlopeXCenterYOnData)*coss + SlopeXCenterYOnData;
				//double	MLx1=(Lx1-LCx)*coss - (Ly1-LCy)*sins + MCx;
				//double	MLy1=(Lx1-LCx)*sins + (Ly1-LCy)*coss + MCy;
				//double	MLx2=(Lx2-LCx)*coss - (Ly2-LCy)*sins + MCx;
				//double	MLy2=(Lx2-LCx)*sins + (Ly2-LCy)*coss + MCy;
				//double	MLx3=(Lx3-LCx)*coss - (Ly3-LCy)*sins + MCx;
				//double	MLy3=(Lx3-LCx)*sins + (Ly3-LCy)*coss + MCy;
				//double	MLx4=(Lx4-LCx)*coss - (Ly4-LCy)*sins + MCx;
				//double	MLy4=(Lx4-LCx)*sins + (Ly4-LCy)*coss + MCy;
	
				//int	MPx1=min(min(Lx1,Lx2),min(Lx3,Lx4));
				//int	MPy1=min(min(Ly1,Ly2),min(Ly3,Ly4));
				//int	MPx2=max(max(Lx1,Lx2),max(Lx3,Lx4));
				//int	MPy2=max(max(Ly1,Ly2),max(Ly3,Ly4));

				#pragma omp parallel                          
				{                                                
					#pragma omp for
					for(int i=0;i<KNumb;i++){
						GerberFastItemBase	*c=((GerberFastItemBase *)PriorityMap[i].Point);
						int	x1 ,y1 ,x2 ,y2;
						if(c->IsExistShear(ZoomRate ,movx ,movy ,CanvasWidth ,CanvasHeight ,x1 ,y1 ,x2 ,y2
																		  ,true,SlopeXAngle,SlopeXCenterXOnData	,SlopeXCenterYOnData )==true){
							if((x2-x1)*(y2-y1)>=20 || (i&0x1f)==0){
								if(c->DrawSimple(pnt, x1 ,y1 ,x2 ,y2,CanvasWidth ,CanvasHeight,(c->PosiImage==true)?Attr->NormalColor.rgba():NegaColor.rgba())==false){
									c->DrawShearX(pnt, movx ,movy ,ZoomRate ,Attr
																		  //,iRotateCenterXOnData	,iRotateCenterYOnData
																		 ,SlopeXCenterXOnData	,SlopeXCenterYOnData ,SlopeXAngle);
								}
							}
						}
					}
				}
				Pnt.setPen(Qt::red);
				int	cx=(SlopeXCenterXOnData+movx)*ZoomRate;
				int	cy=(SlopeXCenterYOnData+movy)*ZoomRate;
				int	x1=(SlopeXFirstX+movx)*ZoomRate;
				int	y1=(SlopeXFirstY+movy)*ZoomRate;
				int	x2=(LastPosX+movx)*ZoomRate;
				int	y2=(LastPosY+movy)*ZoomRate;
				Pnt.drawLine(cx,cy,x1,y1);
				Pnt.drawLine(cx,cy,x2,y2);
			}
		}
	}
	else if(SlopeYMode==true){
		if(Mode==DisplayImage::_SlopeYMoveAngleStart || Mode==DisplayImage::_SlopeYMoveAngling){
			Pnt.setPen(Qt::red);
			int	x=(SlopeYCenterXOnData+movx)*ZoomRate;
			int	y=(SlopeYCenterYOnData+movy)*ZoomRate;
			Pnt.drawLine(x-15,y,x+15,y);
			Pnt.drawLine(x,y-15,x,y+15);
		
			if(Mode==DisplayImage::_SlopeYMoveAngling){
				int	gx1=-movx;
				int	gy1=-movy;
				//int	gx1=0;
				//int	gy1=0;
				int	gx2=gx1+CanvasWidth /ZoomRate;
				int	gy2=gy1+CanvasHeight/ZoomRate;
			
				int	Lx1=gx1;
				int	Ly1=gy1;
				int	Lx2=gx2;
				int	Ly2=gy1;
				int	Lx3=gx1;
				int	Ly3=gy2;
				int	Lx4=gx2;
				int	Ly4=gy2;
					
				//Dp->GetGlobalMatrixFromLocalInMaster(gx1,gy1,Lx1,Ly1);
				//Dp->GetGlobalMatrixFromLocalInMaster(gx2,gy1,Lx2,Ly2);
				//Dp->GetGlobalMatrixFromLocalInMaster(gx1,gy2,Lx3,Ly3);
				//Dp->GetGlobalMatrixFromLocalInMaster(gx2,gy2,Lx4,Ly4);

				double	LCx=(Lx1+Lx4)/2.0;
				double	LCy=(Ly1+Ly4)/2.0;
				double	s=SlopeYAngle;
				double	coss=cos(s);
				double	sins=sin(s);
				//int	iSlopeYCenterXOnData;
				//int	iSlopeYCenterYOnData;
				//Dp->GetGlobalMatrixFromLocalInMaster(SlopeYCenterXOnData	,SlopeYCenterYOnData
				//									,iSlopeYCenterXOnData	,iSlopeYCenterYOnData);
				//double	MCx=(LCx-iSlopeYCenterXOnData)*coss - (LCy-iSlopeYCenterYOnData)*sins + iSlopeYCenterXOnData;
				//double	MCy=(LCx-iSlopeYCenterXOnData)*sins + (LCy-iSlopeYCenterYOnData)*coss + iSlopeYCenterYOnData;
				double	MCx=(LCx-SlopeYCenterXOnData)*coss - (LCy-SlopeYCenterYOnData)*sins + SlopeYCenterXOnData;
				double	MCy=(LCx-SlopeYCenterXOnData)*sins + (LCy-SlopeYCenterYOnData)*coss + SlopeYCenterYOnData;
				//double	MLx1=(Lx1-LCx)*coss - (Ly1-LCy)*sins + MCx;
				//double	MLy1=(Lx1-LCx)*sins + (Ly1-LCy)*coss + MCy;
				//double	MLx2=(Lx2-LCx)*coss - (Ly2-LCy)*sins + MCx;
				//double	MLy2=(Lx2-LCx)*sins + (Ly2-LCy)*coss + MCy;
				//double	MLx3=(Lx3-LCx)*coss - (Ly3-LCy)*sins + MCx;
				//double	MLy3=(Lx3-LCx)*sins + (Ly3-LCy)*coss + MCy;
				//double	MLx4=(Lx4-LCx)*coss - (Ly4-LCy)*sins + MCx;
				//double	MLy4=(Lx4-LCx)*sins + (Ly4-LCy)*coss + MCy;
				//
				//int	MPx1=min(min(Lx1,Lx2),min(Lx3,Lx4));
				//int	MPy1=min(min(Ly1,Ly2),min(Ly3,Ly4));
				//int	MPx2=max(max(Lx1,Lx2),max(Lx3,Lx4));
				//int	MPy2=max(max(Ly1,Ly2),max(Ly3,Ly4));

				#pragma omp parallel                            
				{                                                
					#pragma omp for
					for(int i=0;i<KNumb;i++){
						GerberFastItemBase	*c=((GerberFastItemBase *)PriorityMap[i].Point);
						int	x1 ,y1 ,x2 ,y2;
						if(c->IsExistShear(ZoomRate ,movx ,movy ,CanvasWidth ,CanvasHeight ,x1 ,y1 ,x2 ,y2
																		  ,false ,SlopeYAngle,SlopeYCenterXOnData	,SlopeYCenterYOnData)==true){
							if((x2-x1)*(y2-y1)>=20 || (i&0x1f)==0){
								if(c->DrawSimple(pnt, x1 ,y1 ,x2 ,y2,CanvasWidth ,CanvasHeight,(c->PosiImage==true)?Attr->NormalColor.rgba():NegaColor.rgba())==false){
									c->DrawShearY(pnt, movx ,movy ,ZoomRate ,Attr
																		 ,SlopeYCenterXOnData	,SlopeYCenterYOnData ,SlopeYAngle);
								}
							}
						}
					}
				}
				Pnt.setPen(Qt::red);
				int	cx=(SlopeYCenterXOnData+movx)*ZoomRate;
				int	cy=(SlopeYCenterYOnData+movy)*ZoomRate;
				int	x1=(SlopeYFirstX+movx)*ZoomRate;
				int	y1=(SlopeYFirstY+movy)*ZoomRate;
				int	x2=(LastPosX+movx)*ZoomRate;
				int	y2=(LastPosY+movy)*ZoomRate;
				Pnt.drawLine(cx,cy,x1,y1);
				Pnt.drawLine(cx,cy,x2,y2);
			}
		}
	}
	else if(AlignmentMode==true){
		Pnt.setPen(Qt::red);
		for(int i=0;i<sizeof(ImagePoint)/sizeof(ImagePoint[0]);i++){
			if(ImagePoint[i].x!=0 || ImagePoint[i].y!=0){
				int	x=(ImagePoint[i].x+movx-xy->x)*ZoomRate;
				int	y=(ImagePoint[i].y+movy-xy->y)*ZoomRate;
				Pnt.drawLine(x-15,y,x+15,y);
				Pnt.drawLine(x,y-15,x,y+15);
				Pnt.drawText(x+10,y+10,QString(/**/"Image:")+QString::number(i+1));
			}
		}
		Pnt.setPen(Qt::yellow);
		for(int i=0;i<sizeof(CadPoint)/sizeof(CadPoint[0]);i++){
			if(CadPoint[i].x!=0 || CadPoint[i].y!=0){
				int	x=(CadPoint[i].x+movx-xy->x)*ZoomRate;
				int	y=(CadPoint[i].y+movy-xy->y)*ZoomRate;
				Pnt.drawLine(x-15,y,x+15,y);
				Pnt.drawLine(x,y-15,x,y+15);
				Pnt.drawText(x+10,y-10,QString(/**/"CAD:")+QString::number(i+1));
			}
		}
	}
	else if(AutoMatchingMode==true){
		Pnt.setPen(Qt::red);
		for(int i=0;i<sizeof(AMImagePoint)/sizeof(AMImagePoint[0]);i++){
			if(AMImagePoint[i].x!=0 || AMImagePoint[i].y!=0){
				int	x=(AMImagePoint[i].x+movx-xy->x)*ZoomRate;
				int	y=(AMImagePoint[i].y+movy-xy->y)*ZoomRate;
				Pnt.drawLine(x-15,y,x+15,y);
				Pnt.drawLine(x,y-15,x,y+15);
				Pnt.drawText(x+10,y+10,QString(/**/"Image:")+QString::number(i+1));
			}
		}
		Pnt.setPen(Qt::yellow);
		for(int i=0;i<sizeof(AMCadPoint)/sizeof(AMCadPoint[0]);i++){
			if(AMCadPoint[i].x!=0 || AMCadPoint[i].y!=0){
				int	x=(AMCadPoint[i].x+movx-xy->x)*ZoomRate;
				int	y=(AMCadPoint[i].y+movy-xy->y)*ZoomRate;
				Pnt.drawLine(x-15,y,x+15,y);
				Pnt.drawLine(x,y-15,x,y+15);
				Pnt.drawText(x+10,y-10,QString(/**/"CAD:")+QString::number(i+1));
			}
		}
	}
	delete	[]PriorityMap;
}

GerberFastItemComposite	*GerberFastInPage::FindCompositeItem(int CompositeID)
{
	/*
	for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
		GerberFastItemBase	*t=static_cast<GerberFastItemBase *>(a);
		if(t->GetItemClassType()==5){
			GerberFastItemComposite	*item=dynamic_cast<GerberFastItemComposite *>(a);
			if(item!=NULL){
				if(item->GetCompositeID()==CompositeID){
					return item;
				}
			}
		}
	}
	return NULL;
	*/
	GerberFastItemPointerContainer	*a=GerberFastItemPointerContainerContainerList.SearchComposite(CompositeID);
	if(a!=NULL){
		return dynamic_cast<GerberFastItemComposite *>(a->GetFirst());
	}
	return NULL;
}
GerberFileLayer			*GerberFastInPage::FindFileLayer(int FileLayerID)
{
	for(GerberFileLayer *f=FileLayerList.GetFirst();f!=NULL;f=f->GetNext()){
		if(f->FileLayerID==FileLayerID){
			return f;
		}
	}
	return NULL;
}
GerberCompositeLayer	*GerberFastInPage::SearchCompositeLayer(int CompositeID)
{
	for(GerberCompositeLayer *L=CompositeLayer.GetFirst();L!=NULL;L=L->GetNext()){
		if(L->CompositeID==CompositeID)
			return L;
	}
	return NULL;
}

void	GerberFastInPage::PickupItem(int globalX,int globalY ,AlgorithmItemPointerListContainer &Found)
{
	for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
		if(a->IsInclude(globalX,globalY)==true){
			Found.AppendList(new AlgorithmItemPointerList(a));
		}
	}
}
bool	GerberFastInPage::ExecutePaste(int32 PastedLayer,ClipboardAlgorithmItem *item ,int globalDx, int globalDy,FlexArea &area,bool SelectModeAfterPaste)
{
	bool	Ret=false;
	if(item->ItemClassType!=5){
		AlgorithmItemRoot	*a=CreateItem(item->ItemClassType);
		QBuffer	Buff(&item->ItemData);
		Buff.open(QIODevice::ReadOnly);
		a->Load(&Buff,GetLayersBase());
		GerberFastItemBase	*AItem=(GerberFastItemBase *)a;
		GerberFileLayer		*FL=FileLayerList.Find(AItem->GetLoadedFileLayerID());
		AItem->SetFileLayer(FL);
		if(FL!=NULL){
			GerberDCodeBase	*dcode=FL->FindDCode(AItem->GetLoadedDCode());
			AItem->SetDCode(dcode);
		}
		if(SelectModeAfterPaste==true){
			a->SetSelected(true);
		}
		a->MoveTo(globalDx,globalDy);
		((GerberFastItemBase *)a)->BuildPointer(FileLayerList);
		AppendItem(a);
		UndoElement<AlgorithmInPagePI>	*UPointer	=new UndoElement<AlgorithmInPagePI>(this,&AlgorithmInPagePI::UndoExecutePaste);
		if(GetParamGlobal()->MaxUndoCount>0){
			::Save(UPointer->GetWritePointer(),a->GetID());
		}
		GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);

		Changed=true;
		CalcDone =false;
		Ret=true;
	}
	return Ret;
}

void	GerberFastInPage::ExecuteMove(int GlobalDx,int GlobalDy,bool AllItems)
{
	GerberFastBase	*ABase=(GerberFastBase *)GetParentBase();
	UndoElement<GerberFastInPage>	*UPointer=new UndoElement<GerberFastInPage>(this,&GerberFastInPage::UndoMove);
	if(GetParamGlobal()->MaxUndoCount>0){
		int32	Numb=0;
		for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
			if((a->GetSelected()==true || AllItems==true) && a->GetEditLocked()==false  && a->GetVisible()==true){
				GerberFastItemBase	*item=static_cast<GerberFastItemBase *>(a);
				if(item!=NULL){
					Numb++;
				}
			}
		}
		::Save(UPointer->GetWritePointer(),Numb);
	}
	bool	FlagUndoBuff=true;
	for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
		if((a->GetSelected()==true || AllItems==true) && a->GetEditLocked()==false  && a->GetVisible()==true){
			GerberFastItemBase	*item=static_cast<GerberFastItemBase *>(a);
			if(item!=NULL){
				if(GetParamGlobal()->MaxUndoCount>0){
					if(FlagUndoBuff==true && ::Save(UPointer->GetWritePointer(),item->GetID())==false)
						FlagUndoBuff=false;
					if(FlagUndoBuff==true && item->SaveOnlyShape(UPointer->GetWritePointer())==false)
						FlagUndoBuff=false;
				}
				item->MoveToFloat(GlobalDx,GlobalDy);
			}
		}
	}
	GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);
	SetCurrentSize();
}
void	GerberFastInPage::PushCenter(void)
{
	for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
		if(a->GetSelected()==true){
			GerberFastItemBase	*item=static_cast<GerberFastItemBase *>(a);
			double	Cx,Cy;
			item->GetCenter(Cx,Cy);
			item->CxBefore=Cx;
			item->CyBefore=Cy;
		}
	}
}

void	GerberFastInPage::InitializeFromParts(void)
{
	for(GerberFastItemPointerContainer *a=GerberFastItemPointerContainerContainerList.GetFirst();a!=NULL;a=a->GetNext()){		
		a->BuildFastIndex();
	}

	for(AlgorithmItemPI *Item=GetFirstData();Item!=NULL;){
		AlgorithmItemPI *NextItem=Item->GetNext();
		if(Item->GetPartsID()>=0){
			AlgorithmInPagePI::RemoveItem(Item);

			GerberFastItemBase	*p=static_cast<GerberFastItemBase *>(Item);
			if(p->GetItemClassType()==5){	//Composite mode
				GerberFastItemPointerContainer	*L=GerberFastItemPointerContainerContainerList.SearchComposite(p->GetCompositeID());
				if(L!=NULL){
					L->RemoveItemFast(p);
				}
			}
			else{
				GerberFastItemPointerContainer	*L=GerberFastItemPointerContainerContainerList.Search(p->GetFileLayerID());
				if(L!=NULL){
					L->RemoveItemFast(p);
				}
			}
			delete	Item;
			Changed=true;
		}
		Item=NextItem;
	}	
}

void	GerberFastInPage::CopyFrom(AlgorithmBase *DestParent
									,AlgorithmInPageRoot *src 
									,int OffsetX,int OffsetY
									,int PartsMaster ,int PartsID
									,bool ReferedThresholdMode)
{
	GerberFastItemPointerContainerContainerList.RemoveAll();
	RemoveAllDatas();
	return;
	/*
	PageInfoForParts *Found=NULL;
	GerberFastInPage	*s=dynamic_cast<GerberFastInPage *>(src);
	for(PageInfoForParts *a=PageInfoForPartsData.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->PartsMaster==PartsMaster){
			Found=a;
			break;
		}
	}
	if(Found==NULL){
		Found=new PageInfoForParts(this);
		Found->PartsMaster	=PartsMaster;
		Found->FileLayerList= s->FileLayerList;
		PageInfoForPartsData.AppendList(Found);
	}
	
	AlgorithmInPagePI::CopyFrom(DestParent
									,src 
									,OffsetX,OffsetY
									,PartsMaster ,PartsID
									,ReferedThresholdMode);
	*/
}
PageInfoForParts	*GerberFastInPage::GetPartsInfo(int PartsMaster)
{
	for(PageInfoForParts *a=PageInfoForPartsData.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->PartsMaster==PartsMaster)
			return a;
	}
	return NULL;
}

//==========================================================================================

GerberFastBase::GerberFastBase(LayersBase *Base)
:AlgorithmBase(Base)
{
	ColorNormal			=Qt::yellow;
	ColorSelected		=Qt::white;
	ColorActive			=Qt::red;
	ColorImaging		=Qt::magenta;
	TransparentLevel	=120;

	TileCopiedSize		=400;
	TileOverlapDot		=2;
	//CompositeDefFileName=/**/"GerberCompositeDef.dat";
	StartupZoomRateX	=10.0;
	StartupZoomRateY	=10.0;
	LayerTypeFileName	=/**/"LayerType.def";
	SearchAreaInMatching=50;
	CenterizeByArea		=true;

	DefaultMinDotsForAutoMatching	=400;
	AutoMatchingOutsideDot			=2;
	AutoMatchingInsideDot			=3;
	AutoMatchingMerginDot			=500;
	AutoMatchingEdgeOmitDot			=20;
	ThresholdSelfMatch				=0.95;
	AutoMatchMethod					=0;
	SwingDotInLastMatch				=3;
	CutLargeGetber					=true;
	TooBigSizeForCut				=10000;
	ExecuteFinalEachMatch			=true;
	AutoMatchMinWidthForPartial		=300;
	AutoMatchManualColorParallel	=QColor(100,0,80,180);
	AutoMatchManualColorRotation	=QColor(160,100,80,180);
	AutoMatchManualColorZooming		=QColor(160,0,180,180);
	MaxBindedAreaLength				=1000;
	OverlapPixelToCutBigArea		=50;

	NCUnitInchi		=true;
	NCIntegerNum	=4;
	NCSmallNum		=3;
	
	LoadedCenterization	=true;
	LoadedOffsetX		=0;
	LoadedOffsetY		=0;
	ODBArchiverExeFile	="C:\\Program Files\\7-Zip\\7z.exe";
	ODBArchiverParameter="e -o.\\ $GerberFile";
	HairlineIsolation	=20;
	HairlineLength		=20;
	HairlineCoeff		=20;
	AutoMatchMergin		=2;
	UseBrighterInPattern=false;
	IsolationToSelect	=5.0;
	UseMasterImage		=false;
	AutoMatchAreaSize	=3000;
	AutoMatchExecuteLargeArea	=true;

	ModeDeliverAllPhasesInLoadGerber	=true;
	SetModeLoadSaveInPlayer(true);
	EachSearchDot			=0;

	SetParam(&ColorNormal					, /**/"Color"	,/**/"ColorNormal"						,LangSolver.GetString(XGerberFast_LS,LID_0)/*"Color for normal Gerber item"*/);
	SetParam(&ColorSelected					, /**/"Color"	,/**/"ColorSelected"					,LangSolver.GetString(XGerberFast_LS,LID_1)/*"Color for Selected Gerber item"*/);
	SetParam(&ColorActive					, /**/"Color"	,/**/"ColorActive"						,LangSolver.GetString(XGerberFast_LS,LID_2)/*"Color for Active Gerber Item"*/);
	SetParam(&ColorActive					, /**/"Color"	,/**/"ColorActive"						,LangSolver.GetString(XGerberFast_LS,LID_3)/*"Color for Active Gerber Item"*/);
	SetParam(&ColorActive					, /**/"Color"	,/**/"ColorImaging"						,LangSolver.GetString(XGerberFast_LS,LID_4)/*"Color for Imaging area"*/);
	SetParam(&TransparentLevel				, /**/"Color"	,/**/"TransparentLevel"					,LangSolver.GetString(XGerberFast_LS,LID_16)/*"Transparent level 0-255"*/);
	SetParam(&AutoMatchManualColorParallel	, /**/"Color"	,/**/"AutoMatchManualColorParallel"		,LangSolver.GetString(XGerberFast_LS,LID_17)/*"AutoMatch Alignment color for Parallel"*/);
	SetParam(&AutoMatchManualColorRotation	, /**/"Color"	,/**/"AutoMatchManualColorRotation"		,LangSolver.GetString(XGerberFast_LS,LID_18)/*"AutoMatch Alignment color for Rotation"*/);
	SetParam(&AutoMatchManualColorZooming	, /**/"Color"	,/**/"AutoMatchManualColorZooming"		,LangSolver.GetString(XGerberFast_LS,LID_19)/*"AutoMatch Alignment color for Zooming"*/);

	SetParamFileName(&LayerTypeFileName		,/**/"FileName"	,/**/"LayerTypeFileName"				,LangSolver.GetString(XGerberFast_LS,LID_5)/*"LayerType file name with path"*/);
	
	SetParam(&TileCopiedSize				, /**/"Setting"	,/**/"TileCopiedSize"					,LangSolver.GetString(XGerberFast_LS,LID_6)/*"Copied size(dot) for tiling matrix"*/);
	SetParam(&TileOverlapDot				, /**/"Setting"	,/**/"TileOverlapDot"					,LangSolver.GetString(XGerberFast_LS,LID_7)/*"Overlap dot for tile boundary"*/);

	//SetParamFileName(&CompositeDefFileName	, /**/"FileName",/**/"CompositeDefFileName"				,LangSolver.GetString(XGerberFast_LS,LID_8)/*"Definition file of Gerber Composition"*/);
	SetParam(&StartupZoomRateX				, /**/"Setting"	,/**/"StartupZoomRateX"					,LangSolver.GetString(XGerberFast_LS,LID_9)/*"Default zoom rate when gerber data is loaded"*/);
	SetParam(&StartupZoomRateY				, /**/"Setting"	,/**/"StartupZoomRateY"					,LangSolver.GetString(XGerberFast_LS,LID_10)/*"Default Y-zoom rate when gerber data is loaded"*/);
	SetParam(&SearchAreaInMatching			, /**/"Setting"	,/**/"SearchAreaInMatching"				,LangSolver.GetString(XGerberFast_LS,LID_11)/*"SearchArea dot in Auto-Matching"*/);
	SetParam(&CenterizeByArea				, /**/"Setting"	,/**/"CenterizeByArea"					,LangSolver.GetString(XGerberFast_LS,LID_12)/*"Pick up CAD-center by area"*/);
	SetParam(&DefaultMinDotsForAutoMatching	, /**/"Setting"	,/**/"DefaultMinDotsForAutoMatching"	,LangSolver.GetString(XGerberFast_LS,LID_13)/*"Minimum pixels for AutoMatching (Default value)"*/);
	SetParam(&AutoMatchingOutsideDot		, /**/"Setting"	,/**/"AutoMatchingOutsideDot"			,LangSolver.GetString(XGerberFast_LS,LID_14)/*"Outside Dot for AutoMatching zone"*/);
	SetParam(&AutoMatchingInsideDot			, /**/"Setting"	,/**/"AutoMatchingInsideDot"			,LangSolver.GetString(XGerberFast_LS,LID_15)/*"Inside Dot for AutoMatching zone"*/);
	SetParam(&AutoMatchingMerginDot			, /**/"Setting"	,/**/"AutoMatchingMerginDot"			,LangSolver.GetString(XGerberFast_LS,LID_20)/*"Mergin dot which is outside of Page area"*/);
	SetParam(&ThresholdSelfMatch			, /**/"Setting"	,/**/"ThresholdSelfMatch"				,LangSolver.GetString(XGerberFast_LS,LID_21)/*"SelfMatch threshold. Enable Box in larger value"*/);
	SetParam(&AutoMatchMethod				, /**/"Setting"	,/**/"AutoMatchMethod"					,LangSolver.GetString(XGerberFast_LS,LID_22)/*"0:Standard automatch 1:Architectual match"*/);
	SetParam(&SwingDotInLastMatch			, /**/"Setting"	,/**/"SwingDotInLastMatch"				,LangSolver.GetString(XGerberFast_LS,LID_23)/*"Search-dot near location in last matching sequence."*/);
	SetParam(&IsolationToSelect				, /**/"Setting"	,/**/"IsolationToSelect"				,"Isolation to select");
	SetParam(&CutLargeGetber				, /**/"Gerber"	,/**/"CutLargeGetber"					,LangSolver.GetString(XGerberFast_LS,LID_24)/*"Cut mode for big gerber."*/);
	SetParam(&TooBigSizeForCut				, /**/"Gerber"	,/**/"TooBigSizeForCut"					,LangSolver.GetString(XGerberFast_LS,LID_25)/*"Size to cut too big gerber item"*/);
	SetParam(&NCUnitInchi					, /**/"NC-Data"	,/**/"NCUnitInchi"						,LangSolver.GetString(XGerberFast_LS,LID_26)/*"Data unit: Inchi/mm in NC Data"*/);
	SetParam(&NCIntegerNum					, /**/"NC-Data"	,/**/"NCIntegerNum"						,LangSolver.GetString(XGerberFast_LS,LID_27)/*"Number of figure for integer in NC Data"*/);
	SetParam(&NCSmallNum					, /**/"NC-Data"	,/**/"NCSmallNum"						,LangSolver.GetString(XGerberFast_LS,LID_28)/*"Number of figure for small number in NC Data"*/);
	SetParam(&ExecuteFinalEachMatch			, /**/"AutoMatch"	,/**/"ExecuteFinalEachMatch"		,LangSolver.GetString(XGerberFast_LS,LID_29)/*"Execute last matching of each gerber item"*/);
	SetParam(&AutoMatchMinWidthForPartial	, /**/"AutoMatch"	,/**/"AutoMatchMinWidthForPartial"	,LangSolver.GetString(XGerberFast_LS,LID_30)/*"Minimum width for partial detail in automatch"*/);
	SetParam(&MaxBindedAreaLength			, /**/"AutoMatch"	,/**/"MaxBindedAreaLength"			,LangSolver.GetString(XGerberFast_LS,LID_31)/*"Max length of Binded Area"*/);
	SetParam(&OverlapPixelToCutBigArea		, /**/"AutoMatch"	,/**/"OverlapPixelToCutBigArea"		,LangSolver.GetString(XGerberFast_LS,LID_32)/*"Overlapped Pixel length to cut too big gerber pattern"*/);
	SetParam(&HairlineIsolation				, /**/"AutoMatch"	,/**/"HairlineIsolation"			,"Hairline isolation");
	SetParam(&HairlineLength				, /**/"AutoMatch"	,/**/"HairlineLength"				,"Hairline length");
	SetParam(&HairlineCoeff					, /**/"AutoMatch"	,/**/"HairlineCoeff"				,"Coefficient for effective hairline");
	SetParam(&AutoMatchMergin				, /**/"AutoMatch"	,/**/"AutoMatchMergin"				,"AutoMatch Mergin in Page edge");
	SetParam(&UseBrighterInPattern			, /**/"AutoMatch"	,/**/"UseBrighterInPattern"			,"Use setting of BrighterInPattern");
	SetParam(&UseMasterImage				, /**/"AutoMatch"	,/**/"UseMasterImage"				,"Use master image in matching");
	SetParam(&AutoMatchAreaSize				, /**/"AutoMatch"	,/**/"AutoMatchAreaSize"			,"Automatic matching area size");
	SetParam(&AutoMatchingEdgeOmitDot		, /**/"AutoMatch"	,/**/"AutoMatchingEdgeOmitDot"		,"Omit edge pixels for automatic matching");
	SetParam(&AutoMatchExecuteLargeArea		, /**/"AutoMatch"	,/**/"AutoMatchExecuteLargeArea"	,"Enable large area for automatic matching");
	SetParam(&EachSearchDot					, /**/"AutoMatch2"	,/**/"EachSearchDot				"	,"Search dot by each item");

	SetParam(&LoadedCenterization				, /**/"Initial"	,/**/"LoadedCenterization"			,LangSolver.GetString(XGerberFast_LS,LID_33)/*"Centerization after loading"*/);
	SetParam(&LoadedOffsetX						, /**/"Initial"	,/**/"LoadedOffsetX"				,LangSolver.GetString(XGerberFast_LS,LID_34)/*"Offset X after loading"*/);
	SetParam(&LoadedOffsetY						, /**/"Initial"	,/**/"LoadedOffsetY"				,LangSolver.GetString(XGerberFast_LS,LID_35)/*"Offset Y after loading"*/);

	SetParam(&ODBArchiverExeFile				, /**/"Gerber"	,/**/"ODBArchiverExeFile"					,"(.Z) Archiver executable fullpath file name for ODB++");
	SetParam(&ODBArchiverParameter				, /**/"Gerber"	,/**/"ODBArchiverParameter"					,"Archiver parameter");
	SetParam(&ModeDeliverAllPhasesInLoadGerber	, /**/"Setting"	,/**/"ModeDeliverAllPhasesInLoadGerber"		,"Mode to deliver GerberData for all phases when it\'s loaded");
}

AlgorithmDrawAttr	*GerberFastBase::CreateDrawAttr(void)
{
	return new GerberFastDrawAttr();
}

void	GerberFastBase::InitialAfterParamLoaded(void)
{
	AlgorithmBase::InitialAfterParamLoaded();
	LoadCompositeDef();
}

bool	GerberFastBase::LoadCompositeDef(void)
{
	//QString	FileName=MakeCompositeDefFileName();
	//QFile	mfile(FileName);
	//
	//if(mfile.open(QIODevice::ReadOnly)==false)
	//	return false;
	//
	//if(CompositeDef.Load(&mfile)==false)
	//	return false;
	//mfile.close();

	CommonDataInLibType	CData;
	CData.CommonID		=CommonID_GerberCompositeDefinition;

	if(GetLibraryContainer()!=NULL){
		if(GetLibraryContainer()->LoadCommonDataInLibType(CData)==true){
			QBuffer	Buff(&CData.Data);
			if(Buff.open(QIODevice::ReadOnly)==true){
				if(CompositeDef.Load(&Buff)==true){
					return true;
				}
			}
		}
	}

	return false;
}
bool	GerberFastBase::SaveCompositeDef(void)
{
	CommonDataInLibType	CData;
	CData.CommonID		=CommonID_GerberCompositeDefinition;
	CData.LastUpdated	=QDateTime::currentDateTime();
	CData.Version		=1;
	CData.Name			=/**/"GerberCompositeDef";

	QBuffer	Buff;
	if(Buff.open(QIODevice::WriteOnly)==true){
		if(CompositeDef.Save(&Buff)==true){
			CData.Data=Buff.buffer();
			if(GetLibraryContainer()->UpdateCommonDataInLibType(CData)==true){
				CommonDataInLibType	tCData;
				tCData.CommonID		=CommonID_GerberCompositeDefinition;
				if(GetLibraryContainer()->LoadCommonDataInLibType(tCData)==true){
					return true;
				}
			}			
			if(GetLibraryContainer()->SaveNewCommonDataInLibType(CData)==true){
				return true;
			}
		}
	}
	return false;
							
	//QString	FileName=MakeCompositeDefFileName();
	//QFile	mfile(FileName);
	//
	//if(mfile.open(QIODevice::WriteOnly)==false)
	//	return false;
	//
	//if(CompositeDef.Save(&mfile)==false)
	//	return false;
	//mfile.close();
	//return true;
}

void	GerberFastBase::SetupLibFolder(int LibFolderID ,int originalLibFolder)
{
	LoadCompositeDef();
	if(originalLibFolder>0){
		CompositeDef.CopyCompositeIntoFolder(LibFolderID,originalLibFolder);
		SaveCompositeDef();
	}
}

//QString	GerberFastBase::MakeCompositeDefFileName(void)
//{
//	if(GetLayersBase()->GetLibFolderID()<0){
//		return CompositeDefFileName;
//	}
//	//QString	FileName=CompositeDefFileName+QString(/**/"-")+QString::number(GetLayersBase()->GetLibFolderID());
//	QFileInfo	FInfo(CompositeDefFileName);
//	QString	FileName;
//	if(FInfo.path().isEmpty()==true){
//		FileName=FInfo.baseName()
//				+QString(/**/"-")
//				+QString::number(GetLayersBase()->GetLibFolderID())
//				+QString(/**/".")
//				+FInfo.suffix();
//	}
//	else{
//		FileName=FInfo.path()
//				+GetSeparator()
//				+FInfo.baseName()
//				+QString(/**/"-")
//				+QString::number(GetLayersBase()->GetLibFolderID())
//				+QString(/**/".")
//				+FInfo.suffix();
//	}
//	if(QFile::exists(FileName)==false){
//		QFile::copy ( CompositeDefFileName,FileName );
//	}
//	return FileName;
//}

void	GerberFastBase::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdReqLayerColor	*CmdReqLayerColorVar=dynamic_cast<CmdReqLayerColor *>(packet);
	if(CmdReqLayerColorVar!=NULL){
		CmdReqLayerColorVar->Color=GetLayerColor(CmdReqLayerColorVar->LayerNo);
		return;
	}
	CmdAutoFileEntry	*CmdAutoFileEntryVar=dynamic_cast<CmdAutoFileEntry *>(packet);
	if(CmdAutoFileEntryVar!=NULL){
		QDir	GerberFiles(CmdAutoFileEntryVar->Path);
		QFileInfoList	List=GerberFiles.entryInfoList(QDir::Files);
		for(int i=0;i<List.count();i++){
			QString	FileName=CmdAutoFileEntryVar->Path+QString(/**/"\\")+List[i].fileName();
			GerberFileLayerContainer		TmpFileLayerList((GerberFastInPage *)GetPageData(0));
			GerberFileLayer	*TmpLayer=new GerberFileLayer(&TmpFileLayerList);

			QString	TempFileName=FileName.replace(/**/"\\",/**/"/");

#ifdef _MSC_VER
			wchar_t	tmpFileName[1000];
			memset(tmpFileName,0,sizeof(wchar_t)*1000);
			TempFileName.toWCharArray ( tmpFileName );
			FILE	*file=_wfopen(tmpFileName,/**/L"rt");
#else
			QByteArray	tmpFileNameUTF8=TempFileName.toUtf8();
			FILE	*file=fopen(tmpFileNameUTF8.data(),/**/"rt");
#endif
			if(file!=NULL){
				if(TmpLayer->LoadGerberData(this,file,true)==true){
					CmdAutoFileEntryVar->FileNames.append(FileName);
				}
				else{
					fseek(file,0,SEEK_SET);
					if(TmpLayer->LoadNCData(this,file,true)==true){
						CmdAutoFileEntryVar->FileNames.append(FileName);
					}
				}
				fclose(file);
			}
			delete	TmpLayer;
		}
		if(CmdAutoFileEntryVar->FileNames.count()==0){
			if(LoadODBPPDirectories(CmdAutoFileEntryVar->Path, true 
									,CmdAutoFileEntryVar->StepData
									,CmdAutoFileEntryVar->FileNames
									,CmdAutoFileEntryVar->MatrixLayers)==true){
			}
		}
		return;
	}
	CmdAutoFileEntryODB	*CmdAutoFileEntryODBVar=dynamic_cast<CmdAutoFileEntryODB *>(packet);
	if(CmdAutoFileEntryODBVar!=NULL){
		LoadODBFeatureDirectories(true
								, CmdAutoFileEntryODBVar->StepData
								, CmdAutoFileEntryODBVar->LayerPathList
								, CmdAutoFileEntryODBVar->FileNames
								, CmdAutoFileEntryODBVar->MatrixLayers);
		return;
	}
	GerberSaveCompositeDefPacket	*GerberSaveCompositeDefPacketVar=dynamic_cast<GerberSaveCompositeDefPacket *>(packet);
	if(GerberSaveCompositeDefPacketVar!=NULL){
		if(GerberSaveCompositeDefPacketVar->file==NULL)
			SaveCompositeDef();
		else{
			CompositeDef.Save(GerberSaveCompositeDefPacketVar->file);
		}
		return;
	}
	GerberLoadCompositeDefPacket	*GerberLoadCompositeDefPacketVar=dynamic_cast<GerberLoadCompositeDefPacket *>(packet);
	if(GerberLoadCompositeDefPacketVar!=NULL){
		if(GerberLoadCompositeDefPacketVar->file==NULL)
			LoadCompositeDef();
		else{
			CompositeDef.Load(GerberLoadCompositeDefPacketVar->file);
			SaveCompositeDef();
		}
		return;
	}
	GUICmdGerberSendShowingLayerInfo	*GInfo=dynamic_cast<GUICmdGerberSendShowingLayerInfo *>(packet);
	if(GInfo!=NULL){
		if(GetLibraryContainer()!=NULL){
			IntList PhaseList;
			if(GetParamGlobal()->CommonOperationInAllPhases==false){
				PhaseList.Add(GetLayersBase()->GetCurrentPhase());
			}
			else{
				for(int phase=0;phase<GetPhaseNumb();phase++){
					PhaseList.Add(phase);
				}
			}
			AlgorithmLibraryContainer	*Container=GetLibraryContainer();
			for(IntClass *v=PhaseList.GetFirst();v!=NULL;v=v->GetNext()){
				int phase=v->GetValue();
				AlgorithmInPageInOnePhase	*Ah=GetPageDataPhase(phase);

				for(int page=0;page<GetPageNumb();page++){
					GerberFastInPage	*GPage=(GerberFastInPage *)Ah->GetPageData(page);
					GerberFileLayer		*FL=GPage->FileLayerList.GetFirst();
					for(IntClass *d=GInfo->LayerTypes.GetFirst();d!=NULL && FL!=NULL;d=d->GetNext(),FL=FL->GetNext()){
						int	LibID=d->GetValue();
						AlgorithmLibraryLevelContainer	LLib(Container);
						if(Container->GetLibrary(LibID,LLib)==true){
							FL->LibID=LLib.GetLibID();
						}
						else{
							FL->LibID=-1;
						}
					}
					GPage->CompositeLayer	=GInfo->CompositeLayer;
				}

				for(int page=0;page<GetPageNumb();page++){
					GerberFastInPage	*GPage=(GerberFastInPage *)Ah->GetPageData(page);
					for(AlgorithmItemPI	*a=GPage->GetFirstData();a!=NULL;){
						AlgorithmItemPI	*ANext=a->GetNext();
						GerberFastItemBase	*Item=dynamic_cast<GerberFastItemBase *>(a);
						if(Item!=NULL && Item->GetItemClassType()==5){
							bool	Found=false;
							GerberFastItemComposite	*CItem=dynamic_cast<GerberFastItemComposite *>(Item);
							if(CItem!=NULL && CItem->CompositeLayer!=NULL){
								for(IntClass *d=GInfo->CompositeIDList.GetFirst();d!=NULL;d=d->GetNext()){
									int	CompositeID=d->GetValue();
									if(CItem->CompositeLayer->CompositeID==CompositeID){
										Found=true;
										break;
									}
								}
							}
							if(Found==false){
								GPage->RemoveItem(Item);
								GPage->SetChanged(true);
								delete	Item;
							}
						}
						a=ANext;
					}
				}

				for(IntClass *d=GInfo->CompositeIDList.GetFirst();d!=NULL;d=d->GetNext()){
					int	CompositeID=d->GetValue();
					if(CompositeID>=0){				
						GerberCompositeDefLayer	*GLayer=CompositeDef.Search(CompositeID);
						if(GLayer!=NULL){
							for(int page=0;page<GetPageNumb();page++){
								GerberFastInPage	*GPage=(GerberFastInPage *)Ah->GetPageData(page);
								GerberCompositeLayer	*CL=GPage->SearchCompositeLayer(CompositeID);
								if(CL!=NULL){
									CL->CompositeID=GLayer->CompositeID;
								}
								GerberFastItemComposite	*item=GPage->FindCompositeItem(CompositeID);
								if(item==NULL){
									item=new GerberFastItemComposite();
									item->CompositeLayer=GLayer;
									item->SetCompositeID(CompositeID);
									bool	Changed=GPage->IsChanged();
									GPage->AppendItem(item);
									GPage->SetChanged(Changed);
								}
								else{
									item->CompositeLayer=GLayer;
								}
							}
						}
					}
					else{
						for(int page=0;page<GetPageNumb();page++){
							GerberFastInPage	*GPage=(GerberFastInPage *)Ah->GetPageData(page);
							GerberCompositeLayer	*CL=GPage->SearchCompositeLayer(CompositeID);
							if(CL!=NULL){
								CL->CompositeID=-1;
							}
							GerberFastItemComposite	*item=GPage->FindCompositeItem(CompositeID);
							if(item!=NULL){
								bool	Changed=GPage->IsChanged();
								GPage->RemoveItem(item);
								GPage->SetChanged(Changed);
								delete	item;
							}
						}
					}
				}
			}
		}
		return;			
	}
	CmdGetGerberFastLibraryListPacket	*AListPacket=dynamic_cast<CmdGetGerberFastLibraryListPacket *>(packet);
	if(AListPacket!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->EnumLibrary(GetLibType(),AListPacket->LibFolderID 
				,AListPacket->AList);
		}
		return;
	}
	CmdGetGerberFastLibraryNamesPacket	*ANamesPacket=dynamic_cast<CmdGetGerberFastLibraryNamesPacket *>(packet);
	if(ANamesPacket!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->GetLibraryNames(ANamesPacket->AList);
		}
		return;
	}
	CmdGetGerberFastLibraryNamePacket	*ANamePacket=dynamic_cast<CmdGetGerberFastLibraryNamePacket *>(packet);
	if(ANamePacket!=NULL){
		if(GetLibraryContainer()!=NULL){
			ANamePacket->LibName=GetLibraryContainer()->GetLibraryName(ANamePacket->LibID);
		}
		return;
	}
	CmdGetGerberFastTemporaryLibraryPacket	*CmdGetGerberFastTemporaryLibraryPacketVar=dynamic_cast<CmdGetGerberFastTemporaryLibraryPacket *>(packet);
	if(CmdGetGerberFastTemporaryLibraryPacketVar!=NULL){
		if(GetLibraryContainer()!=NULL){
			CmdGetGerberFastTemporaryLibraryPacketVar->TempLib=(GerberFastLibrary *)GetLibraryContainer()->CreateNew();
		}
		return;
	}
	CmdInsertGerberFastLibraryPacket	*BInsLib=dynamic_cast<CmdInsertGerberFastLibraryPacket *>(packet);
	if(BInsLib!=NULL){
		BInsLib->Point->SetDataVersion(GerberFastVersion);
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->SaveNew(*BInsLib->Point);
		}
		return;
	}
	CmdUpdateGerberFastLibraryPacket	*BUpdLib=dynamic_cast<CmdUpdateGerberFastLibraryPacket *>(packet);
	if(BUpdLib!=NULL){
		BUpdLib->Point->SetDataVersion(GerberFastVersion);
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->Update(*BUpdLib->Point);
		}
		return;
	}
	CmdLoadGerberFastLibraryPacket	*BLoadLib=dynamic_cast<CmdLoadGerberFastLibraryPacket *>(packet);
	if(BLoadLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BLoadLib->Success=GetLibraryContainer()->Load(*BLoadLib->Point);
		}
		return;
	}
	CmdCreateTempGerberFastLibraryPacket	*BCreateLib=dynamic_cast<CmdCreateTempGerberFastLibraryPacket *>(packet);
	if(BCreateLib!=NULL){
		BCreateLib->Point=new AlgorithmLibraryLevelContainer(this);
		return;
	}
	CmdClearGerberFastLibraryPacket	*CmdClearGerberFastLibraryPacketVar=dynamic_cast<CmdClearGerberFastLibraryPacket *>(packet);
	if(CmdClearGerberFastLibraryPacketVar!=NULL){
		CmdClearGerberFastLibraryPacketVar->Point->Clear();
		return;
	}
	CmdDeleteGerberFastLibraryPacket	*BDeleteLib=dynamic_cast<CmdDeleteGerberFastLibraryPacket *>(packet);
	if(BDeleteLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->Delete(BDeleteLib->Point->GetLibID());
		}
		return;
	}
	MsgSaveConstruct	*MsgSaveConstructVar=dynamic_cast<MsgSaveConstruct *>(packet);
	if(MsgSaveConstructVar!=NULL){
		QBuffer	Buff;
		Buff.open(QIODevice::WriteOnly);
		if(MakeAlgoData.Save(&Buff)==false)
			return;
		int32	PhaseNumb=GetPhaseNumb();
		if(::Save(&Buff,PhaseNumb)==false)
			return;

		for(int phase=0;phase<PhaseNumb;phase++){
			AlgorithmInPageInOnePhase	*APhase=GetPageDataPhase(phase);
			for(int page=0;page<GetPageNumb();page++){
				MsgSaveConstruct	RCmd(GetLayersBase());
				APhase->GetPageData(page)->TransmitDirectly(&RCmd);
				if(::Save(&Buff,RCmd.Data)==false)
					return;
			}
		}
		MsgSaveConstructVar->Data=Buff.buffer();
		return;
	}
	MsgLoadConstruct	*MsgLoadConstructVar=dynamic_cast<MsgLoadConstruct *>(packet);
	if(MsgLoadConstructVar!=NULL){
		if(GetLoadedVersion()>=10){
			QBuffer	Buff(&MsgLoadConstructVar->Data);
			Buff.open(QIODevice::ReadOnly);
			if(MakeAlgoData.Load(&Buff)==false)
				return;
			int32	PhaseNumb;
			if(::Load(&Buff,PhaseNumb)==false)
				return;
			for(int phase=0;phase<PhaseNumb && phase<GetPhaseNumb();phase++){
				AlgorithmInPageInOnePhase	*APhase=GetPageDataPhase(phase);
				for(int page=0;page<GetPageNumb();page++){
					MsgLoadConstruct	RCmd(GetLayersBase());
					if(::Load(&Buff,RCmd.Data)==false)
						return;
					APhase->GetPageData(page)->TransmitDirectly(&RCmd);
				}
			}
		}
		else{
			QBuffer	Buff(&MsgLoadConstructVar->Data);
			Buff.open(QIODevice::ReadOnly);
			if(MakeAlgoData.Load(&Buff)==false)
				return;
			for(int page=0;page<GetPageNumb();page++){
				MsgLoadConstruct	RCmd(GetLayersBase());
				if(::Load(&Buff,RCmd.Data)==false)
					return;
				GetPageData(page)->TransmitDirectly(&RCmd);
			}
		}
		return;
	}
	CmdSetDefaultParam	*CmdSetDefaultParamVar=dynamic_cast<CmdSetDefaultParam *>(packet);
	if(CmdSetDefaultParamVar!=NULL){
		StartupZoomRateX	=CmdSetDefaultParamVar->StartupZoomRateX;
		StartupZoomRateY	=CmdSetDefaultParamVar->StartupZoomRateY;
		return;
	}
	CmdReqGerberMatchGlobal	*CmdReqGerberMatchGlobalVar=dynamic_cast<CmdReqGerberMatchGlobal *>(packet);
	if(CmdReqGerberMatchGlobalVar!=NULL){
		MatchGlobal(CmdReqGerberMatchGlobalVar->ShrinkedRate 
			,CmdReqGerberMatchGlobalVar->ImageData,CmdReqGerberMatchGlobalVar->GerberData
			,CmdReqGerberMatchGlobalVar->Dx,CmdReqGerberMatchGlobalVar->Dy
			,CmdReqGerberMatchGlobalVar->ZoomX,CmdReqGerberMatchGlobalVar->ZoomY);
		return;
	}
	CmdSetMatchAutoLikeManual	*CmdSetMatchAutoLikeManualVar=dynamic_cast<CmdSetMatchAutoLikeManual *>(packet);
	if(CmdSetMatchAutoLikeManualVar!=NULL){
		GetPageData(0)->TransmitDirectly(packet);
		return;
	}
	CmdSaveMatchAutoLikeManual	*CmdSaveMatchAutoLikeManualVar=dynamic_cast<CmdSaveMatchAutoLikeManual *>(packet);
	if(CmdSaveMatchAutoLikeManualVar!=NULL){
		GetPageData(0)->TransmitDirectly(packet);
		return;
	}
	CmdGetMatchAutoLikeManual	*CmdGetMatchAutoLikeManualVar=dynamic_cast<CmdGetMatchAutoLikeManual *>(packet);
	if(CmdGetMatchAutoLikeManualVar!=NULL){
		GetPageData(0)->TransmitDirectly(packet);
		return;
	}
	CmdLoadMatchAutoLikeManual	*CmdLoadMatchAutoLikeManualVar=dynamic_cast<CmdLoadMatchAutoLikeManual *>(packet);
	if(CmdLoadMatchAutoLikeManualVar!=NULL){
		GetPageData(0)->TransmitDirectly(packet);
		return;
	}
	CmdSaveMatchAutoLikeManualStream	*CmdSaveMatchAutoLikeManualStreamVar=dynamic_cast<CmdSaveMatchAutoLikeManualStream *>(packet);
	if(CmdSaveMatchAutoLikeManualStreamVar!=NULL){
		CmdSaveMatchAutoLikeManualStreamVar->Ret=CmdSaveMatchAutoLikeManualStreamVar->Point->Save(CmdSaveMatchAutoLikeManualStreamVar->f);
		return;
	}
	CmdLoadMatchAutoLikeManualStream	*CmdLoadMatchAutoLikeManualStreamVar=dynamic_cast<CmdLoadMatchAutoLikeManualStream *>(packet);
	if(CmdLoadMatchAutoLikeManualStreamVar!=NULL){
		CmdLoadMatchAutoLikeManualStreamVar->Ret=CmdLoadMatchAutoLikeManualStreamVar->Point->Load(CmdLoadMatchAutoLikeManualStreamVar->f);
		return;
	}
	CmdGetApertureName *CmdGetApertureNameVar=dynamic_cast<CmdGetApertureName *>(packet);
	if(CmdGetApertureNameVar!=NULL){
		CmdGetApertureNameVar->ApertureName=GerberDCodeContainer::GetApertureName(CmdGetApertureNameVar->ApertureClassID);
		return;
	}
	CmdEnumCompositeChildren	*CmdEnumCompositeChildrenVar=dynamic_cast<CmdEnumCompositeChildren *>(packet);
	if(CmdEnumCompositeChildrenVar!=NULL){
		CompositeDef.EnumChildren(CmdEnumCompositeChildrenVar->CompositeID ,CmdEnumCompositeChildrenVar->RetList);
		return;
	}
	CmdGetCompositeFolderID	*CmdGetCompositeFolderIDVar=dynamic_cast<CmdGetCompositeFolderID *>(packet);
	if(CmdGetCompositeFolderIDVar!=NULL){
		GerberCompositeDefLayer	*f=CompositeDef.Search(CmdGetCompositeFolderIDVar->CompositeID);
		if(f!=NULL){
			CmdGetCompositeFolderIDVar->RetFolderID=f->LibFolderID;
		}
		return;
	}
	CmdDrawIntoBitBuffer	*CmdDrawIntoBitBufferVar=dynamic_cast<CmdDrawIntoBitBuffer *>(packet);
	if(CmdDrawIntoBitBufferVar!=NULL){
		GerberFastInPage	*PData=(GerberFastInPage *)GetPageData(0);
		int	LayerID=0;
		for(BoolClass *b=CmdDrawIntoBitBufferVar->ButtonsToOperateLayer.GetFirst();b!=NULL;b=b->GetNext(),LayerID++){
			if(b->GetValue()==true){
				PData->MakeImage(CmdDrawIntoBitBufferVar->BitImageBuffer,LayerID,true);
			}
		}
		for(IntClass *b=CmdDrawIntoBitBufferVar->OperateCompositeIDList.GetFirst();b!=NULL;b=b->GetNext()){
			int	CompositeID=b->GetValue();
			PData->MakeImage(CmdDrawIntoBitBufferVar->BitImageBuffer,CompositeID,false);
		}
		return;
	}
	GerberSaveCompositeDefIntoFilePacket	*GerberSaveCompositeDefIntoFilePacketVar=dynamic_cast<GerberSaveCompositeDefIntoFilePacket *>(packet);
	if(GerberSaveCompositeDefIntoFilePacketVar!=NULL){
		QFile	File(GerberSaveCompositeDefIntoFilePacketVar->FileName);
		if(File.open(QIODevice::WriteOnly)==false){
			GerberSaveCompositeDefIntoFilePacketVar->RetSuccess=false;
			return;
		}
		GerberSaveCompositeDefIntoFilePacketVar->RetSuccess=CompositeDef.Save(&File);
		File.close();
		return;
	}
	GerberLoadCompositeDefIntoFilePacket	*GerberLoadCompositeDefIntoFilePacketVar=dynamic_cast<GerberLoadCompositeDefIntoFilePacket *>(packet);
	if(GerberLoadCompositeDefIntoFilePacketVar!=NULL){
		QFile	File(GerberLoadCompositeDefIntoFilePacketVar->FileName);
		if(File.open(QIODevice::ReadOnly)==false){
			GerberLoadCompositeDefIntoFilePacketVar->RetSuccess=false;
			return;
		}
		GerberLoadCompositeDefIntoFilePacketVar->RetSuccess=CompositeDef.Load(&File);
		File.close();
		return;
	}
	GerberAppendCompositeDefIntoFilePacket	*GerberAppendCompositeDefIntoFilePacketVar=dynamic_cast<GerberAppendCompositeDefIntoFilePacket *>(packet);
	if(GerberAppendCompositeDefIntoFilePacketVar!=NULL){
		QFile	File(GerberAppendCompositeDefIntoFilePacketVar->FileName);
		if(File.open(QIODevice::ReadOnly)==false){
			GerberAppendCompositeDefIntoFilePacketVar->RetSuccess=false;
			return;
		}
		GerberAppendCompositeDefIntoFilePacketVar->RetSuccess=CompositeDef.Append(&File);
		File.close();
		return;
	}
}

QColor	GerberFastBase::GetLayerColor(int layerNo)
{
	QColor	LColor;
	if(layerNo<0){
		return Qt::darkGray;
	}
	switch(layerNo%8){
		case 0:
			LColor=Qt::yellow;
			break;
		case 1:
			LColor=Qt::green;
			break;
		case 2:
			LColor=Qt::white;
			break;
		case 3:
			LColor=Qt::magenta;
			break;
		case 4:
			LColor=Qt::red;
			break;
		case 5:
			LColor=Qt::cyan;
			break;
		case 6:
			LColor=Qt::darkRed;
			break;
		case 7:
			LColor=Qt::darkYellow;
			break;
	}
	return LColor;
}


bool	GerberFastBase::ExecutePaste(int32 PastedLayer,ClipboardAlgorithmItem *item ,int globalDx, int globalDy,bool SelectModeAfterPaste)
{
	bool	Ret=true;
	AlgorithmInPageRoot	*Ap=GetPageData(item->Page);
	if(Ap!=NULL){
		FlexArea	area;
		if(Ap->ExecutePaste(PastedLayer,item ,globalDx, globalDy,area,SelectModeAfterPaste)==false){
			Ret=false;
		}
	}
	return Ret;
}

bool	GerberFastBase::SaveOnly(QIODevice *f)
{
	GerberFileLayerContainer		TmpFileLayerList((GerberFastInPage *)GetPageData(0));
	if(TmpFileLayerList.Save(f)==false)
		return false;
	if(MakeAlgoData.Save(f)==false)
		return false;
	return true;
}

bool	GerberFastBase::LoadOnly(QIODevice *f)
{
	GerberFileLayerContainer		TmpFileLayerList((GerberFastInPage *)GetPageData(0));
	if(TmpFileLayerList.Load(f)==false)
		return false;
	if(MakeAlgoData.Load(f)==false)
		return false;
	return true;
}
