#include "DXFOperationResource.h"
#include "DXFOperation.h"
#include "XDXFOperation.h"
#include "XGeneralFunc.h"
#include "string.h"
#include "XFlexArea.h"
#include "swap.h"
#include "XDXFOperationPacket.h"
#include "XGeneralFunc.h"
#include "XDisplayBitImage.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include "XPickupPad.h"
#include "XUndo.h"
#include "XCrossObj.h"
#include <omp.h>
#include <float.h>
#include "XBitImageProcessor.h"
#include "XImageProcess.h"
#include "XAlgorithmDLL.h"

extern	QColor	NegaColor;


SectionClasses::SectionClasses(void)
{
	FunctionFlag.EnableDelete			=false;
	FunctionFlag.EnableTransform		=false;	
	FunctionFlag.EnableChangeColor		=false;
	FunctionFlag.EnableChangeLayer		=false;
	FunctionFlag.EnableChangeLineType	=false;
	FunctionFlag.EnableChangeScale		=false;
	FunctionFlag.EnableShow				=false;
	FunctionFlag.EnableClone			=false;
	FunctionFlag.EnableChangeLineWidth	=false;
	FunctionFlag.EnableChangePrintStyle	=false;
	FunctionFlag.IneffectiveWarningDialog=false;
	FunctionFlag.R13J					=false;

	CountInstance=0;
}
//======================================================================
DXFOperationThreshold::DXFOperationThreshold(DXFOperationItemBase *parent)
		:AlgorithmThreshold(parent)
{}


//======================================================================

DXFOperationInPage::DXFOperationInPage(AlgorithmBase *parent)
	:AlgorithmInPagePI(parent),DXFLayerList(this)
{
	ImagingBmp		=NULL;
	ImagingBmpXByte	=0;
	ImagingBmpYLen	=0;

	MoveMode		=false;
	RotateMode		=false;
	ExtendMode		=false;
	SlopeXMode		=false;
	SlopeYMode		=false;
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
}
DXFOperationInPage::~DXFOperationInPage(void)
{
	if(ImagingBmp!=NULL)
		DeleteMatrixBuff(ImagingBmp,ImagingBmpYLen);
	ImagingBmp=NULL;
	ImagingBmpXByte=0;
	ImagingBmpYLen=0;
}

void	DXFOperationInPage::CreateImagingBmpBuff(void)
{
	if(ImagingBmp!=NULL && ((ImagingBmpYLen!=GetMaxLines()) || (ImagingBmpXByte!=(GetDotPerLine()+7)/8))){
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
}

AlgorithmItemRoot		*DXFOperationInPage::CreateItem(int ItemClassType)
{
	DXFOperationItemBase	*a=NULL;
	switch(ItemClassType){
		case 1:
			a=new DXFOperationItemDot();
			break;
		case 2:
			a=new DXFOperationItemLine();
			break;
		case 3:
			a=new DXFOperationItemArc();
			break;
		case 4:
			a=new DXFOperationItemCircle();
			break;
		case 5:
			a=new DXFOperationItemLWPolyLine();
			break;
		case 6:
			a=new DXFOperationItemPolyLine();
			break;
		case 10:
			a=new DXFOperationItemFilledArea();
			break;
	}
	if(a!=NULL){
		a->SetParent(this);
	}
	return a;
}

bool	DXFOperationInPage::LoadDXF(const QByteArray &DXFData ,int FileNo)
{
	QTemporaryFile *F=new QTemporaryFile();
	F->setAutoRemove(false);
	if(F->open()==false){
		delete	F;
		return false;
	}
	F->write(DXFData);
	QString	TempFileName=F->fileName().replace(/**/"\\",/**/"/");
	delete	F;

	bool	Ret=false;
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
		int	ErrorLineNumber;
		QStringList SpecialGroupName;
		if(LoadDXF(file,ErrorLineNumber,SpecialGroupName,FileNo)==true){
			Ret=true;
		}
		fclose(file);
	}
#ifdef _MSC_VER
	::_wremove(tmpFileName);
	delete	[]tmpFileName;
#else
		::remove(tmpFileNameUTF8.data());
#endif
	return Ret;
}

void	DXFOperationInPage::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdLoadDXF	*CmdLoadDXFVar=dynamic_cast<CmdLoadDXF *>(packet);
	if(CmdLoadDXFVar!=NULL){
		CmdLoadDXFVar->Ret=LoadDXF(*CmdLoadDXFVar->pData ,CmdLoadDXFVar->FileNo);
		return;
	}
	CmdSetDXFWithSelfTransform	*CmdSetDXFWithSelfTransformVar=dynamic_cast<CmdSetDXFWithSelfTransform *>(packet);
	if(CmdSetDXFWithSelfTransformVar!=NULL){
		CmdSetDXFWithSelfTransformVar->Result=LoadDXF(CmdSetDXFWithSelfTransformVar->DXFData ,0);
		return;
	}
	CmdDXFMove	*CmdMoveVar=dynamic_cast<CmdDXFMove *>(packet);
	if(CmdMoveVar!=NULL){
		//DXFOperationBase	*ABase=(DXFOperationBase *)GetParentBase();
		UndoElement<DXFOperationInPage>	*UPointer=new UndoElement<DXFOperationInPage>(this,&DXFOperationInPage::UndoMove);
		if(GetParamGlobal()->MaxUndoCount>0){
			int32	Numb=0;
			for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
				if(((a->GetSelected()==true && CmdMoveVar->OnlySelected==true) || CmdMoveVar->OnlySelected==false) && a->GetEditLocked()==false  && a->GetVisible()==true){
					DXFOperationItemBase	*item=static_cast<DXFOperationItemBase *>(a);
					if(item!=NULL){
						Numb++;
					}
				}
			}
			::Save(UPointer->GetWritePointer(),Numb);
		}
		bool	FlagUndoBuff=true;
		for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
			if(((a->GetSelected()==true && CmdMoveVar->OnlySelected==true) || CmdMoveVar->OnlySelected==false) && a->GetEditLocked()==false  && a->GetVisible()==true){
				DXFOperationItemBase	*item=static_cast<DXFOperationItemBase *>(a);
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
				}
			}
		}
		GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);
		return;
	}
	CmdDXFRotate	*CmdRotateVar=dynamic_cast<CmdDXFRotate *>(packet);
	if(CmdRotateVar!=NULL){
		UndoElement<DXFOperationInPage>	*UPointer=new UndoElement<DXFOperationInPage>(this,&DXFOperationInPage::UndoRotate);
		if(GetParamGlobal()->MaxUndoCount>0){
			int32	Numb=0;
			for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
				if(((a->GetSelected()==true && CmdRotateVar->OnlySelected==true) || CmdRotateVar->OnlySelected==false) && a->GetEditLocked()==false  && a->GetVisible()==true){
					DXFOperationItemBase	*item=static_cast<DXFOperationItemBase *>(a);
					if(item!=NULL){
						Numb++;
					}
				}
			}
			::Save(UPointer->GetWritePointer(),Numb);
		}
		bool	FlagUndoBuff=true;
		for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
			if(((a->GetSelected()==true && CmdRotateVar->OnlySelected==true) || CmdRotateVar->OnlySelected==false) && a->GetEditLocked()==false  && a->GetVisible()==true){
				DXFOperationItemBase	*item=static_cast<DXFOperationItemBase *>(a);
				if(item!=NULL){
					if(GetParamGlobal()->MaxUndoCount>0){
						if(FlagUndoBuff==true && ::Save(UPointer->GetWritePointer(),item->GetID())==false)
							FlagUndoBuff=false;
						if(FlagUndoBuff==true && item->SaveOnlyShape(UPointer->GetWritePointer())==false)
							FlagUndoBuff=false;
					}
					item->Rotate(2*M_PI*CmdRotateVar->Angle/360.0
								,CmdRotateVar->CenterX,CmdRotateVar->CenterY);
				}
			}
		}
		GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);
		return;
	}
	CmdDXFZoom	*CmdZoomVar=dynamic_cast<CmdDXFZoom *>(packet);
	if(CmdZoomVar!=NULL){
		UndoElement<DXFOperationInPage>	*UPointer=new UndoElement<DXFOperationInPage>(this,&DXFOperationInPage::UndoZoom);
		if(GetParamGlobal()->MaxUndoCount>0){
			int32	Numb=0;
			for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
				if(((a->GetSelected()==true && CmdZoomVar->OnlySelected==true) || CmdZoomVar->OnlySelected==false) && a->GetEditLocked()==false  && a->GetVisible()==true){
					DXFOperationItemBase	*item=static_cast<DXFOperationItemBase *>(a);
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
			if(((a->GetSelected()==true && CmdZoomVar->OnlySelected==true) || CmdZoomVar->OnlySelected==false) && a->GetEditLocked()==false  && a->GetVisible()==true){
				DXFOperationItemBase	*item=static_cast<DXFOperationItemBase *>(a);
				if(item!=NULL){
					if(GetParamGlobal()->MaxUndoCount>0){
						if(FlagUndoBuff==true && ::Save(UPointer->GetWritePointer(),item->GetID())==false)
							FlagUndoBuff=false;
						if(FlagUndoBuff==true && item->SaveOnlyShape(UPointer->GetWritePointer())==false)
							FlagUndoBuff=false;
					}
					item->Zoom(CmdZoomVar->XZoomDir,CmdZoomVar->YZoomDir
							 , CmdZoomVar->CenterX,CmdZoomVar->CenterY);
				}
			}
		}
		GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);
		return;
	}
	CmdDXFShear	*CmdShearVar=dynamic_cast<CmdDXFShear *>(packet);
	if(CmdShearVar!=NULL){
		UndoElement<DXFOperationInPage>	*UPointer=new UndoElement<DXFOperationInPage>(this,&DXFOperationInPage::UndoShear);
		if(GetParamGlobal()->MaxUndoCount>0){
			int32	Numb=0;
			for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
				if(((a->GetSelected()==true && CmdShearVar->OnlySelected==true) || CmdShearVar->OnlySelected==false) && a->GetEditLocked()==false  && a->GetVisible()==true){
					DXFOperationItemBase	*item=static_cast<DXFOperationItemBase *>(a);
					if(item!=NULL){
						Numb++;
					}
				}
			}
			::Save(UPointer->GetWritePointer(),Numb);
		}
		bool	FlagUndoBuff=true;
		for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
			if(((a->GetSelected()==true && CmdShearVar->OnlySelected==true) || CmdShearVar->OnlySelected==false) && a->GetEditLocked()==false  && a->GetVisible()==true){
				DXFOperationItemBase	*item=static_cast<DXFOperationItemBase *>(a);
				if(item!=NULL){
					if(GetParamGlobal()->MaxUndoCount>0){
						if(FlagUndoBuff==true && ::Save(UPointer->GetWritePointer(),item->GetID())==false)
							FlagUndoBuff=false;
						if(FlagUndoBuff==true && item->SaveOnlyShape(UPointer->GetWritePointer())==false)
							FlagUndoBuff=false;
					}
					item->Shear(CmdShearVar->XMode,2*M_PI*CmdShearVar->Shear/360.0
							,   CmdShearVar->CenterX,CmdShearVar->CenterY);
				}
			}
		}
		GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);
		return;
	}
	CmdDXFMirror	*CmdMirrorVar=dynamic_cast<CmdDXFMirror *>(packet);
	if(CmdMirrorVar!=NULL){
		UndoElement<DXFOperationInPage>	*UPointer=new UndoElement<DXFOperationInPage>(this,&DXFOperationInPage::UndoMirror);
		if(GetParamGlobal()->MaxUndoCount>0){
			int32	Numb=0;
			for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
				if(((a->GetSelected()==true && CmdMirrorVar->OnlySelected==true) || CmdMirrorVar->OnlySelected==false) && a->GetEditLocked()==false  && a->GetVisible()==true){
					DXFOperationItemBase	*item=dynamic_cast<DXFOperationItemBase *>(a);
					if(item!=NULL){
						Numb++;
					}
				}
			}
			::Save(UPointer->GetWritePointer(),Numb);
		}
		bool	FlagUndoBuff=true;
		for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
			if(((a->GetSelected()==true && CmdMirrorVar->OnlySelected==true) || CmdMirrorVar->OnlySelected==false) && a->GetEditLocked()==false  && a->GetVisible()==true){
				DXFOperationItemBase	*item=dynamic_cast<DXFOperationItemBase *>(a);
				if(item!=NULL){
					if(GetParamGlobal()->MaxUndoCount>0){
						if(FlagUndoBuff==true && ::Save(UPointer->GetWritePointer(),item->GetID())==false)
							FlagUndoBuff=false;
						if(FlagUndoBuff==true && item->SaveOnlyShape(UPointer->GetWritePointer())==false)
							FlagUndoBuff=false;
					}
					item->Mirror(CmdMirrorVar->XMode
								,CmdMirrorVar->CenterX ,CmdMirrorVar->CenterY);
				}
			}
		}
		GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);
		return;
	}
	CmdDXFCenterize	*CmdCenterizeVar=dynamic_cast<CmdDXFCenterize *>(packet);
	if(CmdCenterizeVar!=NULL){
		UndoElement<DXFOperationInPage>	*UPointer=new UndoElement<DXFOperationInPage>(this,&DXFOperationInPage::UndoCenterize);
		if(GetParamGlobal()->MaxUndoCount>0){
			int32	Numb=0;

			for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
				if(((a->GetSelected()==true && CmdCenterizeVar->OnlySelected==true) || CmdCenterizeVar->OnlySelected==false) && a->GetEditLocked()==false  && a->GetVisible()==true){
					DXFOperationItemBase	*item=dynamic_cast<DXFOperationItemBase *>(a);
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
			if(((a->GetSelected()==true && CmdCenterizeVar->OnlySelected==true) || CmdCenterizeVar->OnlySelected==false) && a->GetEditLocked()==false  && a->GetVisible()==true){
				DXFOperationItemBase	*item=dynamic_cast<DXFOperationItemBase *>(a);
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
				}
			}
		}
		GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);
		return;
	}
	CmdDXFCenterizeOnly	*CmdCenterizeOnlyVar=dynamic_cast<CmdDXFCenterizeOnly *>(packet);
	if(CmdCenterizeOnlyVar!=NULL){
		UndoElement<DXFOperationInPage>	*UPointer=new UndoElement<DXFOperationInPage>(this,&DXFOperationInPage::UndoCenterizeOnly);
		if(GetParamGlobal()->MaxUndoCount>0){
			int32	Numb=0;

			for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
				if(((a->GetSelected()==true && CmdCenterizeOnlyVar->OnlySelected==true) || CmdCenterizeOnlyVar->OnlySelected==false) && a->GetEditLocked()==false  && a->GetVisible()==true){
					DXFOperationItemBase	*item=dynamic_cast<DXFOperationItemBase *>(a);
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
			if(((a->GetSelected()==true && CmdCenterizeOnlyVar->OnlySelected==true) || CmdCenterizeOnlyVar->OnlySelected==false) && a->GetEditLocked()==false  && a->GetVisible()==true){
				DXFOperationItemBase	*item=dynamic_cast<DXFOperationItemBase *>(a);
				if(item!=NULL){
					if(GetParamGlobal()->MaxUndoCount>0){
						if(FlagUndoBuff==true && ::Save(UPointer->GetWritePointer(),item->GetID())==false)
							FlagUndoBuff=false;
						if(FlagUndoBuff==true && item->SaveOnlyShape(UPointer->GetWritePointer())==false)
							FlagUndoBuff=false;
					}
						
					item->MoveToFloat(-CmdCenterizeOnlyVar->CenterX+tMovX ,-CmdCenterizeOnlyVar->CenterY+tMovY);
					item->MoveToFloat(CmdCenterizeOnlyVar->MovX-tMovX ,CmdCenterizeOnlyVar->MovY-tMovY);
					item->SetCurrentSize();
				}
			}
		}
		GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);
		return;
	}
	CmdReqDXFArea	*CmdReqDXFAreaVar=dynamic_cast<CmdReqDXFArea *>(packet);
	if(CmdReqDXFAreaVar!=NULL){
		static	int	DbgIn=0;
		CmdReqDXFAreaVar->MinX=DBL_MAX;
		CmdReqDXFAreaVar->MinY=DBL_MAX;
		CmdReqDXFAreaVar->MaxX=-DBL_MAX;
		CmdReqDXFAreaVar->MaxY=-DBL_MAX;
		for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
			DXFOperationItemBase	*item=dynamic_cast<DXFOperationItemBase *>(a);
			if(item!=NULL && item->GetSelected()==true){
				double	x1,y1,x2,y2;
				item->GetXY(x1,y1,x2,y2);
				CmdReqDXFAreaVar->MinX=min(CmdReqDXFAreaVar->MinX,x1);
				CmdReqDXFAreaVar->MinY=min(CmdReqDXFAreaVar->MinY,y1);
				CmdReqDXFAreaVar->MaxX=max(CmdReqDXFAreaVar->MaxX,x2);
				CmdReqDXFAreaVar->MaxY=max(CmdReqDXFAreaVar->MaxY,y2);
			}
		}
		return;
	}
	CmdSetLineWidth	*CmdSetLineWidthVar=dynamic_cast<CmdSetLineWidth *>(packet);
	if(CmdSetLineWidthVar!=NULL){
		UndoElement<DXFOperationInPage>	*UPointer=new UndoElement<DXFOperationInPage>(this,&DXFOperationInPage::UndoSetLineWidth);
		if(GetParamGlobal()->MaxUndoCount>0){
			int32	Numb=0;

			for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
				if(a->GetSelected()==true && a->GetEditLocked()==false  && a->GetVisible()==true){
					DXFOperationItemBase	*item=dynamic_cast<DXFOperationItemBase *>(a);
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
				DXFOperationItemBase	*item=dynamic_cast<DXFOperationItemBase *>(a);
				if(item!=NULL){
					if(GetParamGlobal()->MaxUndoCount>0){
						if(FlagUndoBuff==true && ::Save(UPointer->GetWritePointer(),item->GetID())==false)
							FlagUndoBuff=false;
						if(FlagUndoBuff==true && ::Save(UPointer->GetWritePointer(),item->Width)==false)
							FlagUndoBuff=false;
					}
						
					item->Width=CmdSetLineWidthVar->LineWidth;
					item->SetCurrentSize();
				}
			}
		}
		GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);
		return;
	}
	CmdMakeAlgo	*CmdMakeAlgoVar=dynamic_cast<CmdMakeAlgo *>(packet);
	if(CmdMakeAlgoVar!=NULL){
		MakeAlgo(CmdMakeAlgoVar->LibType,CmdMakeAlgoVar->LibID);
		return;
	}
	CmdMakeAlgoFillArea	*CmdMakeAlgoFillAreaVar=dynamic_cast<CmdMakeAlgoFillArea *>(packet);
	if(CmdMakeAlgoFillAreaVar!=NULL){
		MakeAlgoFillArea(CmdMakeAlgoFillAreaVar->LibType,CmdMakeAlgoFillAreaVar->LibID);
		return;
	}
	CmdMakeAlgoByColor	*CmdMakeAlgoByColorVar=dynamic_cast<CmdMakeAlgoByColor *>(packet);
	if(CmdMakeAlgoByColorVar!=NULL){
		MakeAlgoByColor(CmdMakeAlgoByColorVar->ColorCode,CmdMakeAlgoByColorVar->Color
						,CmdMakeAlgoByColorVar->LibType,CmdMakeAlgoByColorVar->LibID);
		return;
	}
	CmdMatchAutomatic	*CmdMatchAutomaticVar=dynamic_cast<CmdMatchAutomatic *>(packet);
	if(CmdMatchAutomaticVar!=NULL){
		ImageBuffer *ImageList[100];
		GetMasterBuffList(ImageList);
		MatchAutomatic(ImageList);
		return;
	}
	CmdSelectInColor	*CmdSelectInColorVar=dynamic_cast<CmdSelectInColor *>(packet);
	if(CmdSelectInColorVar!=NULL){
		int	XLen=GetDotPerLine();
		int	XByte=(XLen+7)/8;
		int	YLen=GetMaxLines();
		BYTE	**BMap=MakeMatrixBuff(XByte,YLen);
		MatrixBuffClear	(BMap ,0 ,XByte,YLen);

		ColorBox	*CBox=new ColorBox;
		CBox->Set(CmdSelectInColorVar->PickupRL,CmdSelectInColorVar->PickupRH
				, CmdSelectInColorVar->PickupGL,CmdSelectInColorVar->PickupGH
				, CmdSelectInColorVar->PickupBL,CmdSelectInColorVar->PickupBH);
		ColorLogic	CLogic;
		CLogic.Add(CBox);
		ImagePointerContainer ImageList;
		GetMasterBuffList(ImageList);
		CLogic.MakeBitmap(ImageList,BMap,XLen,YLen);

		ClearBitInRect(BMap , XByte ,YLen
						 ,0, 0, XLen, CmdSelectInColorVar->AreaY1);
		ClearBitInRect(BMap , XByte ,YLen
						 ,0, CmdSelectInColorVar->AreaY1, CmdSelectInColorVar->AreaX1, CmdSelectInColorVar->AreaY2);
		ClearBitInRect(BMap , XByte ,YLen
						 ,CmdSelectInColorVar->AreaX2, CmdSelectInColorVar->AreaY1,XLen , CmdSelectInColorVar->AreaY2);
		ClearBitInRect(BMap , XByte ,YLen
						 ,0, CmdSelectInColorVar->AreaY2, XLen, YLen);

		PureFlexAreaListContainer FPack;
		PickupFlexArea(BMap ,XByte ,XLen,YLen ,FPack);

		FlexArea	TotalArea;
		for(PureFlexAreaList *f=FPack.GetFirst();f!=NULL;f=f->GetNext()){
			TotalArea+=*f;
		}

		for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
			//if(a->GetSelected()==true && a->GetEditLocked()==false  && a->GetVisible()==true){
			if(a->GetVisible()==true){
				DXFOperationItemBase	*item=dynamic_cast<DXFOperationItemBase *>(a);
				if(item!=NULL){
					if(item->IsCrossed(&TotalArea)==true){
						item->SetSelected(true);
					}
					else{
						item->SetSelected(false);
					}
				}
			}
		}
		DeleteMatrixBuff(BMap,YLen);
		return;
	}
	CmdReqColorFromDXF	*CmdReqColorFromDXFVar=dynamic_cast<CmdReqColorFromDXF *>(packet);
	if(CmdReqColorFromDXFVar!=NULL){
		for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
			DXFOperationItemBase	*item=dynamic_cast<DXFOperationItemBase *>(a);
			if(item!=NULL){
				QColor	Col=item->GetColor(NULL);
				if(CmdReqColorFromDXFVar->ColorList.IsExist(Col)==false){
					CmdReqColorFromDXFVar->ColorList.AppendList(new AllocationLibByColor(item->ColorCode,Col));
				}
				else{
					AllocationLibByColor	*v=CmdReqColorFromDXFVar->ColorList.Find(Col);
					if(v!=NULL){
						v->ColorCode.Merge(item->ColorCode);
					}
				}
			}
		}
		return;
	}
	CmdMakeDXFPaint	*CmdMakeDXFPaintVar=dynamic_cast<CmdMakeDXFPaint *>(packet);
	if(CmdMakeDXFPaintVar!=NULL){
		MakePaintArea(CmdMakeDXFPaintVar->FileNo,CmdMakeDXFPaintVar->LocalX,CmdMakeDXFPaintVar->LocalY);
		return;
	}
	CmdSelectFileNo	*CmdSelectFileNoVar=dynamic_cast<CmdSelectFileNo *>(packet);
	if(CmdSelectFileNoVar!=NULL){
		for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
			DXFOperationItemBase	*item=dynamic_cast<DXFOperationItemBase *>(a);
			if(item!=NULL){
				if(item->FileNo==CmdSelectFileNoVar->FileNo){
					item->SetSelected(true);
				}
				else{
					item->SetSelected(false);
				}
			}
		}
		return;
	}
	CmdMakeEffectiveMask *CmdMakeEffectiveMaskVar=dynamic_cast<CmdMakeEffectiveMask *>(packet);
	if(CmdMakeEffectiveMaskVar!=NULL){
		MakeFilledAllArea(CmdMakeEffectiveMaskVar->ShrinkDot);
		return;
	}
	CmdSendEffectiveMask *CmdSendEffectiveMaskVar=dynamic_cast<CmdSendEffectiveMask *>(packet);
	if(CmdSendEffectiveMaskVar!=NULL){
		PipeToSendEffectiveMask();
		return;
	}
	CmdReqDXFTransformInfo	*CmdReqDXFTransformInfoVar=dynamic_cast<CmdReqDXFTransformInfo *>(packet);
	if(CmdReqDXFTransformInfoVar!=NULL){
		for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
			//if(a->GetID()==CmdMoveElementVar->ItemID){
			DXFOperationItemBase	*Item=dynamic_cast<DXFOperationItemBase *>(a);
			if(Item!=NULL){
				QBuffer	Buff;
				if(Buff.open(QIODevice::WriteOnly)==true){
					Item->SaveTransformParam(&Buff);
					CmdReqDXFTransformInfoVar->TransformData=Buff.buffer();
				}
				break;
			}
		}
		return;
	}
	CmdSetDXFTransformInfo	*CmdSetDXFTransformInfoVar=dynamic_cast<CmdSetDXFTransformInfo *>(packet);
	if(CmdSetDXFTransformInfoVar!=NULL){
		for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
			//if(a->GetID()==CmdMoveElementVar->ItemID){
			DXFOperationItemBase	*Item=dynamic_cast<DXFOperationItemBase *>(a);
			if(Item!=NULL){
				QBuffer	Buff(&CmdSetDXFTransformInfoVar->TransformData);
				if(Buff.open(QIODevice::ReadOnly)==true){
					Item->LoadTransformParam(&Buff);
				}
			}
		}
		return;
	}
}

void	DXFOperationInPage::MakeAlgo(int LibType,int LibID)
{
	CreateImagingBmpBuff();

	int	MaxFileNo=0;
	for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
		if(a->GetEditLocked()==false  && a->GetVisible()==true){
			DXFOperationItemBase	*item=dynamic_cast<DXFOperationItemBase *>(a);
			if(item->FileNo>MaxFileNo){
				MaxFileNo=item->FileNo;
			}
		}
	}
	
	int	XByte	=(GetDotPerLine()+7)/8;
	int	YLen	=GetMaxLines();
	BYTE	**TmpMap=::MakeMatrixBuff(XByte ,YLen);

	for(int L=MaxFileNo;L>=0;L--){
		MatrixBuffClear	(TmpMap ,0 ,XByte ,YLen);
		for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
			if(a->GetEditLocked()==false  && a->GetVisible()==true){
				DXFOperationItemBase	*item=dynamic_cast<DXFOperationItemBase *>(a);
				if(item->GetItemClassType()==10 && item->FileNo==(L-1)){
					item->MakeImage(TmpMap ,0 ,0 ,ImagingBmpXByte ,ImagingBmpYLen);
				}
			}
		}

		for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
			if(a->GetEditLocked()==false  && a->GetVisible()==true){
				DXFOperationItemBase	*item=dynamic_cast<DXFOperationItemBase *>(a);
				if(item->GetItemClassType()!=10 && item->FileNo==L){
					item->MakeImage(ImagingBmp ,0 ,0 ,ImagingBmpXByte ,ImagingBmpYLen);
				}
			}
		}
		MatrixBuffNotAnd(ImagingBmp ,(const BYTE **)TmpMap ,XByte ,YLen);
	}

	DeleteMatrixBuff(TmpMap		,YLen);

	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(LibType);
	if(Ab!=NULL){
		AlgorithmInPageRoot	*Ap=Ab->GetPageData(GetPage());
		if(Ap!=NULL){
			GeneralPipeInfo	Info(GetParentBase());
			Info.Cmd	=GeneralPipeInfo::_GI_ReqFormatBmpMap;
			if(Ap->PipeGeneration(Info)==true){
				Info.Cmd		=GeneralPipeInfo::_GI_SendBmpMap;
				Info.BmpMap		=ImagingBmp;
				Info.DriftMap	=NULL;
				Info.OmitMap	=NULL;
				Info.XByte		=ImagingBmpXByte;
				Info.YLen		=ImagingBmpYLen;
				Info.LibID		=LibID;
				Info.OperationOrigin	=_OriginType_FromCAD;
				Ap->PipeGeneration(Info);
			}
		}
	}
	if(ImagingBmp!=NULL){
		MatrixBuffClear(ImagingBmp ,0,ImagingBmpXByte ,ImagingBmpYLen);
	}
}

void	DXFOperationInPage::MakeFilledAllArea(int ShrinkDot)
{
	CreateImagingBmpBuff();

	IntList	LineWidthList;
	const	int		LineWidthForImage=5;
	for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
		if(a->GetVisible()==true){
			DXFOperationItemBase	*item=dynamic_cast<DXFOperationItemBase *>(a);
			if(item!=NULL){
				LineWidthList.Add(item->Width);
				item->Width=LineWidthForImage;
				item->SetCurrentSize();
			}
		}
	}
	int	XByte	=(GetDotPerLine()+7)/8;
	int	YLen	=GetMaxLines();

	MatrixBuffClear	(ImagingBmp ,0 ,ImagingBmpXByte ,ImagingBmpYLen);
	for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
		if(a->GetVisible()==true){
			DXFOperationItemBase	*item=dynamic_cast<DXFOperationItemBase *>(a);
			item->MakeImage(ImagingBmp ,0 ,0 ,ImagingBmpXByte ,ImagingBmpYLen);
		}
	}
	MatrixBuffNot	(ImagingBmp ,ImagingBmpXByte ,ImagingBmpYLen);
	MakeInsideArea();

	//if(ImagingBmp!=NULL){
	//	MatrixBuffClear(ImagingBmp ,0,ImagingBmpXByte ,ImagingBmpYLen);
	//}
	IntClass	*WidthList=LineWidthList.GetFirst();
	for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
		if(a->GetVisible()==true){
			DXFOperationItemBase	*item=dynamic_cast<DXFOperationItemBase *>(a);
			if(item!=NULL){
				item->Width=WidthList->GetValue();
				item->SetCurrentSize();
				WidthList=WidthList->GetNext();
			}
		}
	}

	BYTE	**TmpMap=::MakeMatrixBuff(ImagingBmpXByte ,ImagingBmpYLen);

	if(ShrinkDot>0){
		GetLayersBase()->ThinAreaN(ImagingBmp,TmpMap,ImagingBmpXByte,ImagingBmpYLen,ShrinkDot);
	}
	else if(ShrinkDot<0){
		GetLayersBase()->FatAreaN(ImagingBmp,TmpMap,ImagingBmpXByte,ImagingBmpYLen,ShrinkDot);
	}
	DeleteMatrixBuff(TmpMap	,ImagingBmpYLen);
}
void	DXFOperationInPage::PipeToSendEffectiveMask(void)
{
	AlgorithmBasePointerContainer ABases;
	GetLayersBase()->GetAlgorithmByType(ABases,AlgorithmBit_TypeMasking);
	for(AlgorithmBasePointerList *a=ABases.GetFirst();a!=NULL;a=a->GetNext()){
		AlgorithmBase		*Ab=a->GetAlgorithmBase();
		AlgorithmInPageRoot	*Ap=Ab->GetPageData(GetPage());
		if(Ap!=NULL){
			GeneralPipeInfo	Info(GetParentBase());
			Info.Cmd	=GeneralPipeInfo::_GI_ReqFormatBmpMap;
			if(Ap->PipeGeneration(Info)==true){
				Info.Cmd		=GeneralPipeInfo::_GI_SendBmpMap;
				Info.BmpMap		=ImagingBmp;
				Info.DriftMap	=NULL;
				Info.OmitMap	=NULL;
				Info.XByte		=ImagingBmpXByte;
				Info.YLen		=ImagingBmpYLen;
				Info.LibID		=-1;
				Info.OperationOrigin	=_OriginType_FromCAD;
				Ap->PipeGeneration(Info);
			}
		}
	}
}

void	DXFOperationInPage::MakeAlgoFillArea(int LibType,int LibID)
{
	CreateImagingBmpBuff();

	for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
		if(a->GetEditLocked()==false  && a->GetVisible()==true){
			DXFOperationItemBase	*item=dynamic_cast<DXFOperationItemBase *>(a);
			if(item->GetItemClassType()==10){
				item->MakeImage(ImagingBmp ,0 ,0 ,ImagingBmpXByte ,ImagingBmpYLen);
			}
		}
	}

	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(LibType);
	if(Ab!=NULL){
		AlgorithmInPageRoot	*Ap=Ab->GetPageData(GetPage());
		if(Ap!=NULL){
			GeneralPipeInfo	Info(GetParentBase());
			Info.Cmd	=GeneralPipeInfo::_GI_ReqFormatBmpMap;
			if(Ap->PipeGeneration(Info)==true){
				Info.Cmd		=GeneralPipeInfo::_GI_SendBmpMap;
				Info.BmpMap		=ImagingBmp;
				Info.DriftMap	=NULL;
				Info.OmitMap	=NULL;
				Info.XByte		=ImagingBmpXByte;
				Info.YLen		=ImagingBmpYLen;
				Info.LibID		=LibID;
				Info.OperationOrigin	=_OriginType_FromCAD;
				Ap->PipeGeneration(Info);
			}
		}
	}
	if(ImagingBmp!=NULL){
		MatrixBuffClear(ImagingBmp ,0,ImagingBmpXByte ,ImagingBmpYLen);
	}
}
void	DXFOperationInPage::MakeAlgoByColor(IntList &ColorCode ,QColor &Color ,int LibType,int LibID)
{
	CreateImagingBmpBuff();
	
	int	N=0;
	for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
		if(a->GetEditLocked()==false  && a->GetVisible()==true){
			DXFOperationItemBase	*item=dynamic_cast<DXFOperationItemBase *>(a);
			if(ColorCode.IsInclude(item->ColorCode)==true){
				item->MakeImage(ImagingBmp ,0 ,0 ,ImagingBmpXByte ,ImagingBmpYLen);
				N++;
			}
		}
	}

	if(N>0){
		AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(LibType);
		if(Ab!=NULL){
			AlgorithmInPageRoot	*Ap=Ab->GetPageData(GetPage());
			if(Ap!=NULL){
				GeneralPipeInfo	Info(GetParentBase());
				Info.Cmd	=GeneralPipeInfo::_GI_ReqFormatBmpMap;
				if(Ap->PipeGeneration(Info)==true){
					Info.Cmd		=GeneralPipeInfo::_GI_SendBmpMap;
					Info.BmpMap		=ImagingBmp;
					Info.DriftMap	=NULL;
					Info.OmitMap	=NULL;
					Info.XByte		=ImagingBmpXByte;
					Info.YLen		=ImagingBmpYLen;
					Info.LibID		=LibID;
					Info.OperationOrigin	=_OriginType_FromCAD;
					Ap->PipeGeneration(Info);
				}
			}
		}
		if(ImagingBmp!=NULL){
			MatrixBuffClear(ImagingBmp ,0,ImagingBmpXByte ,ImagingBmpYLen);
		}
	}
	else{
		MakeAlgo(LibType,LibID);
	}
}

void	DXFOperationInPage::MatchAutomatic(ImageBuffer *IBuff[])
{
	for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
		if(a->GetSelected()==true && a->GetEditLocked()==false  && a->GetVisible()==true){
			DXFOperationItemBase	*Item=dynamic_cast<DXFOperationItemBase *>(a);
			Item->ExecuteMatch(IBuff[Item->MatchingLayer],((DXFOperationBase *)GetParentBase())->SearchDot);
		}
	}
}

ExeResult	DXFOperationInPage::ExecuteInitialAfterEdit	(int ExeID 
														,ResultInPageRoot *Res
														,ExecuteInitialAfterEditInfo &EInfo)
{
	ExeResult	Ret=AlgorithmInPagePI::ExecuteInitialAfterEdit	(ExeID ,Res,EInfo);
	return Ret;
}

bool	DXFOperationInPage::Save(QIODevice *f)
{
	AlgorithmBase	*ABase=GetParentBase();
	if(ABase->GetModeLoadSaveInPlayer()==true || (ABase->GetModeLoadSaveInPlayer()==false && GetLayersBase()->GetModeInspectionPlayer()==false)){

		if(DXFLayerList.Save(f)==false)
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

		if(AlgorithmInPagePI::Save(f)==false)
			return false;
	}
	return true;
}

bool	DXFOperationInPage::Load(QIODevice *f)
{

	if(DXFLayerList.Load(f)==false)
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

	if(AlgorithmInPagePI::Load(f)==false)
		return false;
	for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
		DXFOperationItemBase	*item=static_cast<DXFOperationItemBase *>(a);
		item->SetDXFLayer(DXFLayerList.Find(item->LoadedFileID));
	}

	return true;
}

bool	DXFOperationInPage::CheckValidity(void)
{
	for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
		DXFOperationItemBase	*item=static_cast<DXFOperationItemBase *>(a);
		//if(item->CheckValidity()==false)
		//	return false;
	}
	return true;
}

void	DXFOperationInPage::UndoMove		(QIODevice *f)
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
			((DXFOperationItemBase *)Item)->LoadOnlyShape(f);
		}
	}
}

void	DXFOperationInPage::UndoRotate	(QIODevice *f)
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
			((DXFOperationItemBase *)Item)->LoadOnlyShape(f);
		}
	}
}

void	DXFOperationInPage::UndoZoom		(QIODevice *f)
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
			((DXFOperationItemBase *)Item)->LoadOnlyShape(f);
		}
	}
}

void	DXFOperationInPage::UndoShear		(QIODevice *f)
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
			((DXFOperationItemBase *)Item)->LoadOnlyShape(f);
		}
	}
}

void	DXFOperationInPage::UndoMirror	(QIODevice *f)
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
			((DXFOperationItemBase *)Item)->LoadOnlyShape(f);
		}
	}
}

void	DXFOperationInPage::UndoCenterize	(QIODevice *f)
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
			((DXFOperationItemBase *)Item)->LoadOnlyShape(f);
		}
	}
}

void	DXFOperationInPage::UndoCenterizeOnly	(QIODevice *f)
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
			((DXFOperationItemBase *)Item)->LoadOnlyShape(f);
		}
	}
}

void	DXFOperationInPage::UndoSetLineWidth	(QIODevice *f)
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
			double	LineWidth;
			if(::Load(f,LineWidth)==false)
				return;
			DXFOperationItemBase *AItem=(DXFOperationItemBase *)Item;
			AItem->Width=LineWidth;
		}
	}
}
void	DXFOperationInPage::Draw(QImage &pnt, IntList &LayerList ,int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	AlgorithmInPagePI::Draw(pnt, LayerList ,movx ,movy ,ZoomRate ,Attr);
	DXFOperationBase	*Base=(DXFOperationBase *)GetParentBase();

	QPainter	Pnt(&pnt);
	Pnt.setPen(Base->ColorVLine);
	for(AlgorithmItemPI	*item=GetFirstData();item!=NULL;item=item->GetNext()){
		DXFOperationItemBase	*Item=(DXFOperationItemBase *)item;
		for(VLineOnDXF *v=Item->VLineContainer.GetFirst();v!=NULL;v=v->GetNext()){
			v->Draw(0,0,Pnt,movx,movy,ZoomRate);
		}
	}
					
	DXFOperationDrawAttr	*GAttr=(DXFOperationDrawAttr *)Attr;
	if(ImagingBmp!=NULL){
		DrawBitImageOr(pnt, (const BYTE **)ImagingBmp,ImagingBmpXByte*8,ImagingBmpXByte,ImagingBmpYLen
			,(movx<0)?movx:0 ,(movy<0)?movy:0,ZoomRate
				,0,0
				,Base->ColorImaging);
	}

	int	CanvasWidth=pnt.width();
	int	CanvasHeight=pnt.height();

	int	hx1=(movx					)*ZoomRate;
	int	hy1=(movy					)*ZoomRate;
	int	hx2=(movx+GetDotPerLine()	)*ZoomRate;
	int	hy2=(movy+GetMaxLines()		)*ZoomRate;
	
	if(hx2<0 || CanvasWidth<=hx1
	|| hy2<0 || CanvasHeight<=hy1){
		return;
	}
	hx1=max(hx1,0);
	hy1=max(hy1,0);
	hx2=min(hx2,CanvasWidth);
	hy2=min(hy2,CanvasHeight);

	XYData	*xy=GetLayersBase()->GetGlobalOutlineOffset(GetLayersBase()->GetGlobalPageFromLocal(GetPage()));
	
	DataInPage	*Dp=GetDataInPage();

	if(RotateMode==true){
		if(Mode==DisplayImage::_RotateMoveAngleStart || Mode==DisplayImage::_RotateMoveAngling){
			Pnt.setPen(Qt::red);
			int	x=(RotateCenterXOnData+movx)*ZoomRate;
			int	y=(RotateCenterYOnData+movy)*ZoomRate;
			Pnt.drawLine(x-15,y,x+15,y);
			Pnt.drawLine(x,y-15,x,y+15);
		
			if(Mode==DisplayImage::_RotateMoveAngling){
				//int	gx1=-movx;
				//int	gy1=-movy;
				//int	gx2=gx1+CanvasWidth /ZoomRate;
				//int	gy2=gy1+CanvasHeight/ZoomRate;
				//
				//int	Lx1=gx1;
				//int	Ly1=gy1;
				//int	Lx2=gx2;
				//int	Ly2=gy1;
				//int	Lx3=gx1;
				//int	Ly3=gy2;
				//int	Lx4=gx2;
				//int	Ly4=gy2;
				//	
				//Dp->GetGlobalMatrixFromLocalInMaster(gx1,gy1,Lx1,Ly1);
				//Dp->GetGlobalMatrixFromLocalInMaster(gx2,gy1,Lx2,Ly2);
				//Dp->GetGlobalMatrixFromLocalInMaster(gx1,gy2,Lx3,Ly3);
				//Dp->GetGlobalMatrixFromLocalInMaster(gx2,gy2,Lx4,Ly4);

				//double	LCx=(Lx1+Lx4)/2.0;
				//double	LCy=(Ly1+Ly4)/2.0;
				//double	s=-RotateAngle;
				//double	coss=cos(s);
				//double	sins=sin(s);
				//
				//double	MCx=(LCx-RotateCenterXOnData)*coss - (LCy-RotateCenterYOnData)*sins + RotateCenterXOnData;
				//double	MCy=(LCx-RotateCenterXOnData)*sins + (LCy-RotateCenterYOnData)*coss + RotateCenterYOnData;
				//double	MLx1=(Lx1-LCx)*coss - (Ly1-LCy)*sins + MCx;
				//double	MLy1=(Lx1-LCx)*sins + (Ly1-LCy)*coss + MCy;
				//double	MLx2=(Lx2-LCx)*coss - (Ly2-LCy)*sins + MCx;
				//double	MLy2=(Lx2-LCx)*sins + (Ly2-LCy)*coss + MCy;
				//double	MLx3=(Lx3-LCx)*coss - (Ly3-LCy)*sins + MCx;
				//double	MLy3=(Lx3-LCx)*sins + (Ly3-LCy)*coss + MCy;
				//double	MLx4=(Lx4-LCx)*coss - (Ly4-LCy)*sins + MCx;
				//double	MLy4=(Lx4-LCx)*sins + (Ly4-LCy)*coss + MCy;
				//
				//int	MPx1=floor(min(min(MLx1,MLx2),min(MLx3,MLx4)));
				//int	MPy1=floor(min(min(MLy1,MLy2),min(MLy3,MLy4)));
				//int	MPx2=ceil (max(max(MLx1,MLx2),max(MLx3,MLx4)));
				//int	MPy2=ceil (max(max(MLy1,MLy2),max(MLy3,MLy4)));

				for(AlgorithmItemPI	*item=GetFirstData();item!=NULL;item=item->GetNext()){
					DXFOperationItemBase	*c=(DXFOperationItemBase *)item;
					int	x1 ,y1 ,x2 ,y2;
					if(c->IsExistRotate(ZoomRate ,movx ,movy ,CanvasWidth ,CanvasHeight ,x1 ,y1 ,x2 ,y2
																	  ,-RotateAngle,RotateCenterXOnData	,RotateCenterYOnData)==true){
						c->DrawRotate(pnt, movx ,movy ,ZoomRate ,Attr
																,RotateCenterXOnData	,RotateCenterYOnData,-RotateAngle);
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
				//int	gx1=-movx;
				//int	gy1=-movy;
				//int	gx2=gx1+CanvasWidth /ZoomRate;
				//int	gy2=gy1+CanvasHeight/ZoomRate;
				//int	Lx1,Ly1;
				//int	Lx2,Ly2;
				//Dp->GetGlobalMatrixFromLocalInMaster(gx1,gy1,Lx1,Ly1);
				//Dp->GetGlobalMatrixFromLocalInMaster(gx2,gy2,Lx2,Ly2);

				for(AlgorithmItemPI	*item=GetFirstData();item!=NULL;item=item->GetNext()){
					DXFOperationItemBase	*c=(DXFOperationItemBase *)item;
					int	x1 ,y1 ,x2 ,y2;
					if(c->IsExistZoom(ZoomRate ,movx ,movy ,CanvasWidth ,CanvasHeight ,x1 ,y1 ,x2 ,y2
																	  ,Zx,Zy,ExtendCenterXOnData	,ExtendCenterYOnData)==true){
						c->DrawZoom(pnt, movx ,movy ,ZoomRate ,Attr
														 ,ExtendCenterXOnData	,ExtendCenterYOnData,Zx,Zy);
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
				//int	gx1=-movx;
				//int	gy1=-movy;
				//int	gx2=gx1+CanvasWidth /ZoomRate;
				//int	gy2=gy1+CanvasHeight/ZoomRate;
				//
				//int	Lx1=gx1;
				//int	Ly1=gy1;
				//int	Lx2=gx2;
				//int	Ly2=gy1;
				//int	Lx3=gx1;
				//int	Ly3=gy2;
				//int	Lx4=gx2;
				//int	Ly4=gy2;
				//
				//double	LCx=(Lx1+Lx4)/2.0;
				//double	LCy=(Ly1+Ly4)/2.0;
				//double	s=SlopeXAngle;
				//double	coss=cos(s);
				//double	sins=sin(s);
				//
				//double	MCx=(LCx-SlopeXCenterXOnData)*coss - (LCy-SlopeXCenterYOnData)*sins + SlopeXCenterXOnData;
				//double	MCy=(LCx-SlopeXCenterXOnData)*sins + (LCy-SlopeXCenterYOnData)*coss + SlopeXCenterYOnData;
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

				for(AlgorithmItemPI	*item=GetFirstData();item!=NULL;item=item->GetNext()){
					DXFOperationItemBase	*c=(DXFOperationItemBase *)item;
					int	x1 ,y1 ,x2 ,y2;
					if(c->IsExistShear(ZoomRate ,movx ,movy ,CanvasWidth ,CanvasHeight ,x1 ,y1 ,x2 ,y2
																	  ,true,SlopeXAngle,SlopeXCenterXOnData	,SlopeXCenterYOnData )==true){
						c->DrawShearX(pnt, movx ,movy ,ZoomRate ,Attr
																 //,iRotateCenterXOnData	,iRotateCenterYOnData
																 ,SlopeXCenterXOnData	,SlopeXCenterYOnData ,SlopeXAngle);
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
				//int	gx1=-movx;
				//int	gy1=-movy;
				//int	gx2=gx1+CanvasWidth /ZoomRate;
				//int	gy2=gy1+CanvasHeight/ZoomRate;
				//
				//int	Lx1=gx1;
				//int	Ly1=gy1;
				//int	Lx2=gx2;
				//int	Ly2=gy1;
				//int	Lx3=gx1;
				//int	Ly3=gy2;
				//int	Lx4=gx2;
				//int	Ly4=gy2;
				//
				//double	LCx=(Lx1+Lx4)/2.0;
				//double	LCy=(Ly1+Ly4)/2.0;
				//double	s=SlopeYAngle;
				//double	coss=cos(s);
				//double	sins=sin(s);
				//
				//double	MCx=(LCx-SlopeYCenterXOnData)*coss - (LCy-SlopeYCenterYOnData)*sins + SlopeYCenterXOnData;
				//double	MCy=(LCx-SlopeYCenterXOnData)*sins + (LCy-SlopeYCenterYOnData)*coss + SlopeYCenterYOnData;
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

				for(AlgorithmItemPI	*item=GetFirstData();item!=NULL;item=item->GetNext()){
					DXFOperationItemBase	*c=(DXFOperationItemBase *)item;
					int	x1 ,y1 ,x2 ,y2;
					if(c->IsExistShear(ZoomRate ,movx ,movy ,CanvasWidth ,CanvasHeight ,x1 ,y1 ,x2 ,y2
																		  ,false ,SlopeYAngle,SlopeYCenterXOnData	,SlopeYCenterYOnData)==true){
						c->DrawShearY(pnt, movx ,movy ,ZoomRate ,Attr
																 ,SlopeYCenterXOnData	,SlopeYCenterYOnData ,SlopeYAngle);
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
}

void	DXFOperationInPage::PickupItem(int globalX,int globalY ,AlgorithmItemPointerListContainer &Found)
{
	for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
		if(a->IsInclude(globalX,globalY)==true){
			Found.AppendList(new AlgorithmItemPointerList(a));
		}
	}
}

void	DXFOperationInPage::ExecuteMove(int GlobalDx,int GlobalDy,bool AllItems)
{
	DXFOperationBase	*ABase=(DXFOperationBase *)GetParentBase();
	UndoElement<DXFOperationInPage>	*UPointer=new UndoElement<DXFOperationInPage>(this,&DXFOperationInPage::UndoMove);
	if(GetParamGlobal()->MaxUndoCount>0){
		int32	Numb=0;
		for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
			if((a->GetSelected()==true || AllItems==true) && a->GetEditLocked()==false  && a->GetVisible()==true){
				DXFOperationItemBase	*item=static_cast<DXFOperationItemBase *>(a);
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
			DXFOperationItemBase	*item=static_cast<DXFOperationItemBase *>(a);
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
}


//==========================================================================================

DXFOperationBase::DXFOperationBase(LayersBase *Base)
:AlgorithmBase(Base)
	//:FileLayerList(NULL)
{
	ColorNormal			=Qt::yellow;
	ColorSelected		=Qt::white;
	ColorActive			=Qt::red;
	ColorImaging		=Qt::magenta;
	TransparentLevel	=120;

	TileCopiedSize		=400;
	TileOverlapDot		=2;
	StartupZoomRateX	=10.0;
	StartupZoomRateY	=10.0;
	SearchAreaInMatching=50;
	CenterizeByArea		=true;

	DefaultMinDotsForAutoMatching	=400;
	ThresholdSelfMatch				=0.95;
	SwingDotInLastMatch				=3;
	
	LoadedCenterization	=true;
	LoadedOffsetX		=0;
	LoadedOffsetY		=0;

	ColorVLine			=Qt::red;
	VLineLength			=10;
	VLineIsolation		=40;
	SearchDot			=50;
	//AllocationLibByColorContainerInst.CommonID= DXFCommonDataID;

	SetModeLoadSaveInPlayer(true);

	SetParam(&ColorNormal					, /**/"Color"	,/**/"ColorNormal"					,LangSolver.GetString(XDXFOperation_LS,LID_0)/*"Color for normal DXF item"*/);
	SetParam(&ColorSelected					, /**/"Color"	,/**/"ColorSelected"				,LangSolver.GetString(XDXFOperation_LS,LID_1)/*"Color for Selected DXF item"*/);
	SetParam(&ColorActive					, /**/"Color"	,/**/"ColorActive"					,LangSolver.GetString(XDXFOperation_LS,LID_2)/*"Color for Active DXF Item"*/);
	SetParam(&ColorActive					, /**/"Color"	,/**/"ColorActive"					,LangSolver.GetString(XDXFOperation_LS,LID_3)/*"Color for Active DXF Item"*/);
	SetParam(&ColorActive					, /**/"Color"	,/**/"ColorImaging"					,LangSolver.GetString(XDXFOperation_LS,LID_4)/*"Color for Imaging area"*/);
	SetParam(&TransparentLevel				, /**/"Color"	,/**/"TransparentLevel"				,LangSolver.GetString(XDXFOperation_LS,LID_5)/*"Transparent level 0-255"*/);
	
	SetParam(&TileCopiedSize				, /**/"Setting"	,/**/"TileCopiedSize"				,LangSolver.GetString(XDXFOperation_LS,LID_6)/*"Copied size(dot) for tiling matrix"*/);
	SetParam(&TileOverlapDot				, /**/"Setting"	,/**/"TileOverlapDot"				,LangSolver.GetString(XDXFOperation_LS,LID_7)/*"Overlap dot for tile boundary"*/);

	SetParam(&StartupZoomRateX				, /**/"Setting"	,/**/"StartupZoomRateX"				,LangSolver.GetString(XDXFOperation_LS,LID_8)/*"Default zoom rate when DXF data is loaded"*/);
	SetParam(&StartupZoomRateY				, /**/"Setting"	,/**/"StartupZoomRateY"				,LangSolver.GetString(XDXFOperation_LS,LID_9)/*"Default Y-zoom rate when DXF data is loaded"*/);
	SetParam(&SearchAreaInMatching			, /**/"Setting"	,/**/"SearchAreaInMatching"			,LangSolver.GetString(XDXFOperation_LS,LID_10)/*"SearchArea dot in Auto-Matching"*/);
	SetParam(&CenterizeByArea				, /**/"Setting"	,/**/"CenterizeByArea"				,LangSolver.GetString(XDXFOperation_LS,LID_11)/*"Pick up CAD-center by area"*/);
	SetParam(&DefaultMinDotsForAutoMatching	, /**/"Setting"	,/**/"DefaultMinDotsForAutoMatching",LangSolver.GetString(XDXFOperation_LS,LID_12)/*"Minimum pixels for AutoMatching (Default value)"*/);
	SetParam(&ThresholdSelfMatch			, /**/"Setting"	,/**/"ThresholdSelfMatch"			,LangSolver.GetString(XDXFOperation_LS,LID_13)/*"SelfMatch threshold. Enable Box in larger value"*/);
	SetParam(&SwingDotInLastMatch			, /**/"Setting"	,/**/"SwingDotInLastMatch"			,LangSolver.GetString(XDXFOperation_LS,LID_14)/*"Search-dot near location in last matching sequence."*/);

	SetParam(&LoadedCenterization			, /**/"Initial"	,/**/"LoadedCenterization"			,LangSolver.GetString(XDXFOperation_LS,LID_15)/*"Centerization after loading"*/);
	SetParam(&LoadedOffsetX					, /**/"Initial"	,/**/"LoadedOffsetX"				,LangSolver.GetString(XDXFOperation_LS,LID_16)/*"Offset X after loading"*/);
	SetParam(&LoadedOffsetY					, /**/"Initial"	,/**/"LoadedOffsetY"				,LangSolver.GetString(XDXFOperation_LS,LID_17)/*"Offset Y after loading"*/);

	SetParam(&ColorVLine					, /**/"Matching",/**/"ColorVLine"					,LangSolver.GetString(XDXFOperation_LS,LID_18)/*"Vector color for auto-matching "*/);
	SetParam(&VLineLength					, /**/"Matching",/**/"VLineLength"					,LangSolver.GetString(XDXFOperation_LS,LID_19)/*"Vector length for auto matching"*/);
	SetParam(&VLineIsolation				, /**/"Matching",/**/"VLineIsolation"				,LangSolver.GetString(XDXFOperation_LS,LID_20)/*"Vector isolation for auto matching"*/);
	SetParam(&SearchDot						, /**/"Matching",/**/"SearchDot"					,LangSolver.GetString(XDXFOperation_LS,LID_21)/*"Search dot for auto matching"*/);
}

AlgorithmDrawAttr	*DXFOperationBase::CreateDrawAttr(void)
{
	return new DXFOperationDrawAttr();
}

bool	DXFOperationBase::SaveOnlyBase(QIODevice *f)
{
	if(AlgorithmBase::SaveOnlyBase(f)==false){
		return false;
	}

	QBuffer	File;
	if(File.open(QIODevice::WriteOnly)==true){
		if(AllocationLibByColorPackInst.Save(&File)==false){
			return false;
		}
	}
	CommonDataInLibType	CommonData;
	CommonData.CommonID	=DXFCommonDataID;
	CommonData.Version	=DXFOperationVersion;
	CommonData.Data		=File.buffer();
	CommonData.Name		=/**/"AllocationLibByColor";

	if(GetLibraryContainer()->UpdateCommonDataInLibType(CommonData)==false){
		GetLibraryContainer()->SaveNewCommonDataInLibType(CommonData);
	}

	return true;
}
bool	DXFOperationBase::LoadOnlyBase(QIODevice *f,QString &ErrorMsg)
{
	bool	Ret=AlgorithmBase::LoadOnlyBase(f,ErrorMsg);

	CommonDataInLibType	CommonData;
	CommonData.CommonID=DXFCommonDataID;
	if(GetLibraryContainer()->LoadCommonDataInLibType(CommonData)==true){
		QBuffer	File(&CommonData.Data);
		if(File.open(QIODevice::ReadOnly)==true){
			if(AllocationLibByColorPackInst.Load(&File)==false){
				Ret=false;
			}
		}
	}
	return Ret;
}
bool	DXFOperationBase::LoadOnlyBase(QIODevice *f)
{
	bool	Ret=AlgorithmBase::LoadOnlyBase(f);

	CommonDataInLibType	CommonData;
	CommonData.CommonID=DXFCommonDataID;
	if(GetLibraryContainer()->LoadCommonDataInLibType(CommonData)==true){
		QBuffer	File(&CommonData.Data);
		if(File.open(QIODevice::ReadOnly)==true){
			if(AllocationLibByColorPackInst.Load(&File)==false){
				Ret=false;
			}
		}
	}

	return Ret;
}

void	DXFOperationBase::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdReqLayerColor	*CmdReqLayerColorVar=dynamic_cast<CmdReqLayerColor *>(packet);
	if(CmdReqLayerColorVar!=NULL){
		CmdReqLayerColorVar->Color=GetLayerColor(CmdReqLayerColorVar->LayerNo);
		return;
	}
	CmdSaveAllocationLibByColor	*CmdSaveAllocationLibByColorVar=dynamic_cast<CmdSaveAllocationLibByColor *>(packet);
	if(CmdSaveAllocationLibByColorVar!=NULL){
		QBuffer	File;
		if(File.open(QIODevice::WriteOnly)==true){
			if(AllocationLibByColorPackInst.Save(&File)==false){
				return;
			}
		}
		CommonDataInLibType	CommonData;
		CommonData.CommonID	=DXFCommonDataID;
		CommonData.Version	=DXFOperationVersion;
		CommonData.Data		=File.buffer();
		CommonData.Name		=/**/"AllocationLibByColor";
		if(GetLibraryContainer()->UpdateCommonDataInLibType(CommonData)==false){
			GetLibraryContainer()->SaveNewCommonDataInLibType(CommonData);
		}
		return;
	}
	CmdLoadAllocationLibByColor	*CmdLoadAllocationLibByColorVar=dynamic_cast<CmdLoadAllocationLibByColor *>(packet);
	if(CmdLoadAllocationLibByColorVar!=NULL){
		CommonDataInLibType	CommonData;
		CommonData.CommonID=DXFCommonDataID;
		if(GetLibraryContainer()!=NULL){
			if(GetLibraryContainer()->LoadCommonDataInLibType(CommonData)==true){
				QBuffer	File(&CommonData.Data);
				if(File.open(QIODevice::ReadOnly)==true){
					if(AllocationLibByColorPackInst.Load(&File)==false){
						return;
					}
				}
			}
		}
		return;
	}
	CmdReqAllocationLibByColor	*CmdReqAllocationLibByColorVar=dynamic_cast<CmdReqAllocationLibByColor *>(packet);
	if(CmdReqAllocationLibByColorVar!=NULL){
		AllocationLibByColorContainer	*a=FindAllocationLibByColor(CmdReqAllocationLibByColorVar->ThresholdLevelID);
		if(a==NULL){
			AllocationLibByColorContainerByLevel	*b=new AllocationLibByColorContainerByLevel();
			AllocationLibByColorContainerByLevel	*s=AllocationLibByColorPackInst.GetFirst();
			if(s!=NULL){
				*b=*s;
			}
			b->ThresholdLevelID=CmdReqAllocationLibByColorVar->ThresholdLevelID;
			AllocationLibByColorPackInst.AppendList(b);
			a=&b->AllocationLibByColorContainerInst;
		}
		CmdReqAllocationLibByColorVar->Container=*a;
		return;
	}
	CmdSetAllocationLibByColor	*CmdSetAllocationLibByColorVar=dynamic_cast<CmdSetAllocationLibByColor *>(packet);
	if(CmdSetAllocationLibByColorVar!=NULL){
		AllocationLibByColorContainer	*a=FindAllocationLibByColor(CmdSetAllocationLibByColorVar->ThresholdLevelID);
		if(a==NULL){
			AllocationLibByColorContainerByLevel	*b=new AllocationLibByColorContainerByLevel();
			b->ThresholdLevelID=CmdSetAllocationLibByColorVar->ThresholdLevelID;
			b->AllocationLibByColorContainerInst=CmdSetAllocationLibByColorVar->Container;
			AllocationLibByColorPackInst.AppendList(b);
		}
		else{
			*a=CmdSetAllocationLibByColorVar->Container;
		}
		return;
	}
}

QColor	DXFOperationBase::GetLayerColor(int layerNo)
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


bool	DXFOperationBase::ExecutePaste(int32 PastedLayer,ClipboardAlgorithmItem *item ,int globalDx, int globalDy,bool SelectModeAfterPaste)
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
QString	DXFOperationBase::GetNameByCurrentLanguage(void)
{
	return LangSolver.GetString(XDXFOperation_LS,LID_22)/*"DXF陷�ｽｦ騾�ｿｽ*/;
}

AllocationLibByColorContainer	*DXFOperationBase::FindAllocationLibByColor(int LevelID)
{
	if(LevelID<0){
		LevelID=GetLayersBase()->GetThresholdLevelID();
	}
	for(AllocationLibByColorContainerByLevel *f=AllocationLibByColorPackInst.GetFirst();f!=NULL;f=f->GetNext()){
		if(f->ThresholdLevelID==LevelID){
			return &f->AllocationLibByColorContainerInst;
		}
	}
	return NULL;
}

AllocationLibByColorContainerByLevel	&AllocationLibByColorContainerByLevel::operator=(const AllocationLibByColorContainerByLevel &src)
{
	ThresholdLevelID=src.ThresholdLevelID;
	AllocationLibByColorContainerInst	=src.AllocationLibByColorContainerInst;
	return *this;
}

bool	AllocationLibByColorContainerByLevel::Save(QIODevice *f)
{
	if(::Save(f,ThresholdLevelID)==false)
		return false;
	if(AllocationLibByColorContainerInst.Save(f)==false)
		return false;
	return true;
}
bool	AllocationLibByColorContainerByLevel::Load(QIODevice *f)
{
	if(::Load(f,ThresholdLevelID)==false)
		return false;
	if(AllocationLibByColorContainerInst.Load(f)==false)
		return false;
	return true;
}

AllocationLibByColorContainerByLevel	*AllocationLibByColorContainerByLevelContainer::Create(void)
{
	return new AllocationLibByColorContainerByLevel();
}
