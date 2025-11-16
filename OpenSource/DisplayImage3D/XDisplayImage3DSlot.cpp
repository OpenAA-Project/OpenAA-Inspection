#include "XDisplayImage3D.h"
#include "XTypeDef.h"
#include "XGeneralDialog.h"
#include "XGeneralFunc.h"
#include "XCriticalFunc.h"
#include <omp.h>
#include <math.h>
#include <QMenu>
#include "XDataInLayer.h"
#include "XFileRegistry.h"
#include "XGeneralStocker.h"
#include "mtImageToolButtonWithBalloon.h"
#include "mtImageToolButtonColored.h"
#include "mtImageButtonWithBalloon.h"
#include "XImageStocker.h"
#include "swap.h"

void	DisplayImage3DAlgo::NoneButtonDown()
{
	if(MainCanvas!=NULL){
		MainCanvas->SetMode(mtFrameDraw::fdNone);
	}
	if((DrawingMode==_MeasureFirst)
	|| (DrawingMode==_MeasureSecond)
	|| (DrawingMode==_MeasureDone)){
		SetDrawingMode(_Normal);
	}
	GetLayersBase()->SetStatusModes(this,/**/"ImageNone");

	if(NoneBtn->isChecked()==true){
		emit	SignalButtonClicked(NoneBtn->objectName());
	}
}
void	DisplayImage3DAlgo::ZoomInButtonDown()
{
	if(MainCanvas!=NULL){
		MainCanvas->SetMode(mtFrameDraw::fdPoint);
	}
	AllUpToolButton();
	SetAlterSomething();

	if(ZoomInBtn->isChecked()==true){
		emit	SignalButtonClicked(ZoomInBtn->objectName());
	}
}
void	DisplayImage3DAlgo::ZoomRectButtonDown()
{
	AllUpToolButton();
	if(MainCanvas!=NULL){
		MainCanvas->SetMode(mtFrameDraw::fdRectangle);
		MainCanvas->SetFrameColor(FrameColor);
	}
	SetAlterSomething();
	GetLayersBase()->SetStatusModes(this,/**/"ImageZoomRect");

	if(ZoomRectBtn->isChecked()==true){
		emit	SignalButtonClicked(ZoomRectBtn->objectName());
	}
}

void	DisplayImage3DAlgo::MeasureButtonDown(bool checked)
{
	if(checked==true){
		if(MainCanvas!=NULL){
			MainCanvas->SetMode(mtFrameDraw::fdPoint);
		}
		AllUpToolButton();
		SetAlterSomething();
		if((MeasureBtn!=NULL) && (MeasureBtn->isChecked()==true)){
			SetDrawingMode(_MeasureFirst);
		}
		GetLayersBase()->SetStatusModes(this,/**/"ImageMeasure");
		SetCursor(_MeasureFirst);
	}

	if(MeasureBtn->isChecked()==true){
		emit	SignalButtonClicked(MeasureBtn->objectName());
	}
}

void	DisplayImage3DAlgo::ToolMenuBtnDown()
{
	QMenu	Menu(this);
	//Menu.addAction (LangDISolver.GetString(XDisplayImage_LS,LID_193)/*"Undo"*/			, this, SLOT(UndoButtonDown()));
	//Menu.addAction (LangDISolver.GetString(XDisplayImage_LS,LID_194)/*"Redo"*/			, this, SLOT(RedoButtonDown()));
	//Menu.addSeparator ();
	//Menu.addAction (LangDISolver.GetString(XDisplayImage_LS,LID_20)/*"Move Image"*/				, this, SLOT(SlotMoveImage()));
	//Menu.addAction (LangDISolver.GetString(XDisplayImage_LS,LID_195)/*"Rotate Image"*/			, this, SLOT(SlotRotateImage()));
	//Menu.addAction (LangDISolver.GetString(XDisplayImage_LS,LID_196)/*"Mirror Image"*/			, this, SLOT(SlotMirrorImage()));
	//if(GetParamGlobal()->AllocateMasterBuff==true
	//&& GetParamGlobal()->AllocateTargetBuff==true){
	//	Menu.addAction (LangDISolver.GetString(XDisplayImage_LS,LID_21)/*"Swap Image"*/				, this, SLOT(SlotSwapImage()));
	//}
	//
	//Menu.addAction (LangDISolver.GetString(XDisplayImage_LS,LID_183)/*"Negative<-->Positive"*/	, this, SLOT(SlotNegPosImage()));
	//if(GetParamGlobal()->AllocateMasterBuff==true
	//&& GetParamGlobal()->AllocateTargetBuff==true){
	//	Menu.addAction (LangDISolver.GetString(XDisplayImage_LS,LID_22)/*"Copy Master -> Target"*/	, this, SLOT(SlotCopyImageToTarget()));
	//	Menu.addAction (LangDISolver.GetString(XDisplayImage_LS,LID_23)/*"Copy Target -> Master"*/	, this, SLOT(SlotCopyImageToMaster()));
	//}
	//if(GetParamGlobal()->AllocateTargetTRBuff==true)
	//	Menu.addAction (QString(LangDISolver.GetString(XDisplayImage_LS,LID_197)/*"Transposition Target -> TargetTR"*/), this, SLOT(SlotTranspositionTarget()));
	//if(GetCountOnlyMasterBuff()>1){
	//	Menu.addSeparator ();
	//	Menu.addAction (QString(LangDISolver.GetString(XDisplayImage_LS,LID_198)/*"Copy image Target -> MasterN"*/), this, SLOT(SlotCopyTargetToMasterBuffN()));
	//	Menu.addAction (QString(LangDISolver.GetString(XDisplayImage_LS,LID_199)/*"Copy image Master -> MasterN"*/), this, SLOT(SlotCopyMasterToMasterBuffN()));
	//	Menu.addAction (QString(LangDISolver.GetString(XDisplayImage_LS,LID_200)/*"Swap image Master <-> MasterN"*/),this, SLOT(SlotSwapMasterBuffN()));
	//}
	//
	//Menu.addSeparator ();
	//if(GetParamGlobal()->AllocateMasterBuff==true){
	//	Menu.addAction (LangDISolver.GetString(XDisplayImage_LS,LID_178)/*"Clear Master Image"*/	, this, SLOT(SlotClearMasterImage()));
	//}
	//if(GetParamGlobal()->AllocateTargetBuff==true){
	//	Menu.addAction (LangDISolver.GetString(XDisplayImage_LS,LID_179)/*"Clear Target Image"*/	, this, SLOT(SlotClearTargetImage()));
	//}
	//if(GetParamGlobal()->AllocBitBuffer==true){
	//	Menu.addAction (QString(LangDISolver.GetString(XDisplayImage_LS,LID_201)/*"Clear BitBuffer Image"*/)			, this, SLOT(SlotClearBitBuffer()));
	//}
	//Menu.addSeparator ();
	////Menu.addAction (LangDISolver.GetString(XDisplayImage_LS,LID_38)/*"Regulate brightness"*/,this,SLOT(SlotRegulateBrightness()));
	//if(GetParamGlobal()->AllocRawTargetBuffForNGImage==true){
	//	Menu.addAction (LangDISolver.GetString(XDisplayImage_LS,LID_184)/*"Copy Raw -> Target"*/, this, SLOT(SlotCopyRawToTarget()));
	//	Menu.addAction (LangDISolver.GetString(XDisplayImage_LS,LID_39)/*"Swap Raw -> Target"*/, this, SLOT(SlotSwapRawToTarget()));
	//}
	//if(GetPhaseNumb()>1){
	//	Menu.addAction (LangDISolver.GetString(XDisplayImage_LS,LID_202)/*"Copy Image between Phases"*/			, this, SLOT(SlotCopyImageInPhases()));
	//}
	//

	AddMenuToolMenuBtn(Menu);

	QPoint	Q=mapToGlobal(ToolMenuBtn->geometry().center());
	Menu.exec(Q);
}

void	DisplayImage3DAlgo::WholeButtonDown()
{
	if(MainCanvas!=NULL){
		SetAreaSize();
		MainCanvas->ZoomDrawWhole();
		emit	SignalChangedDrawingPosition();
	}
	BroadcastDraw();
	SetAlterSomething();

	emit	SignalButtonClicked(ZoomWholeBtn->objectName());
}

void	DisplayImage3DAlgo::FitButtonDown()
{
	if(MainCanvas!=NULL){
		SetAreaSize();
		MainCanvas->ZoomDrawFit();
		emit	SignalChangedDrawingPosition();
	}
	BroadcastDraw();
	SetAlterSomething();
}

void	DisplayImage3DAlgo::ResizeAction()
{
	GetLayersBase()->SetOnChanging(true);
	if(MainCanvas!=NULL){
		int	W=width();
		int	H=height();
		MainCanvas->resize(W,H-ClientTop);
		SetAlterSomething();
	}
	GetLayersBase()->SetOnChanging(false);
}

void	DisplayImage3DAlgo::SlotMouseMove(int globalX,int globalY)
{
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		if(GetLayersBase()->GetSendingData(globalPage)==true){
			return;
		}
	}

	if(HookedExecuteMouseMove(globalX,globalY)==false)
		return;

	int	GlobalPage=GetLayersBase()->GetGlobalPage(globalX,globalY);
	if(GlobalPage>=0){
		int	LocalPage=GetLayersBase()->GetLocalPageFromGlobal(GlobalPage);
		QColor Ret;
		if(DynamicPickupColor(globalX,globalY ,Ret)==true){
			if(XPosLabel!=NULL){
				XPosLabel->setText(QString::number(globalX));
			}
			if(YPosLabel!=NULL){
				YPosLabel->setText(QString::number(globalY));
			}

			if(LabelColorMessage!=NULL){
				QString	msg;
				int	LayerNumb=GetLayersBase()->GetLayerNumb(LocalPage);
				if(LayerNumb>3){
					msg= QString::number(Ret.red()) + QString(/**/",")
						+QString::number(Ret.green()) + QString(/**/",")
						+QString::number(Ret.blue())
						+QString(/**/"...");
				}
				else
				if(LayerNumb==3){
					msg= QString::number(Ret.red()) + QString(/**/",")
						+QString::number(Ret.green()) + QString(/**/",")
						+QString::number(Ret.blue());
				}
				else
				if(LayerNumb==2){
					msg= QString::number(Ret.red()) + QString(/**/",")
						+QString::number(Ret.green());
				}
				else
				if(LayerNumb==1){
					msg=QString::number(Ret.red());
				}
				LabelColorMessage->setText(msg);
			}
			int		MeterX ,MeterY;
			GetMeterMatrix(globalX ,globalY ,MeterX ,MeterY);
			emit	SignalPointColor(MeterX ,MeterY ,Ret);
		}
	}

	if((MeasureBtn!=NULL) && (MeasureBtn->isChecked()==true)){
		if(DrawingMode==_MeasureSecond){
			MeasureCurrentGlobalX	=globalX;
			MeasureCurrentGlobalY	=globalY;
			if(MainCanvas!=NULL){
				MainCanvas->Repaint();
			}
		}
	}
}

void	DisplayImage3DAlgo::UndoButtonDown()
{
	if(GetLayersBase()->ExecuteUndoInMaster()==false){
		SetError(Error_Comm , /**/"Send error : GUICmdReqUndo",ErrorCodeList::_Alart);
	}
	BroadcastBuildForShow();
}

void	DisplayImage3DAlgo::RedoButtonDown()
{
	if(GetLayersBase()->ExecuteRedoInMaster()==false){
		SetError(Error_Comm , /**/"Send error : GUICmdReqRedo",ErrorCodeList::_Alart);
	}
	BroadcastBuildForShow();
}
