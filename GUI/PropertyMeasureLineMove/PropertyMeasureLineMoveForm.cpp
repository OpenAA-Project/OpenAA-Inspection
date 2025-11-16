/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyMeasureLineMove\PropertyMeasureLineMoveForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "PropertyMeasureLineMoveFormResource.h"
#include "PropertyMeasureLineMoveForm.h"
#include "XMeasureLineMove.h"
#include "XMeasureLineMovePacket.h"
#include "XCSV.h"
#include "swap.h"
#include "EditLibraryDialog.h"
#include "SelectLibraryDialog.h"
#include "XDisplayImage.h"
#include "XDisplayImagePacket.h"
#include "EditLineMoveDialog.h"
#include <QMessageBox>
#include "XGeneralDialog.h"
#include "XRememberer.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

PropertyMeasureLineMoveForm::PropertyMeasureLineMoveForm(LayersBase *Base ,QWidget *parent)
	: GUIFormBase(Base,parent)
{
	ui.setupUi(this);
	LangSolver.SetUI(this);

	LibFolderID =-1;
	LTable		=NULL;
	MeasureLineMoveBase	*BBase=GetMeasureLineMoveBase();
	LibType=-1;
	if(BBase!=NULL)	
		LibType=BBase->GetLibType();
	ui.tableWidgetLibList->setColumnWidth (0, 32);
	ui.tableWidgetLibList->setColumnWidth (1, 150);
	ui.tableWidgetLibList->setColumnWidth (2, 40);
	ui.tableWidgetLibList->setColumnWidth (3, 40);
	ui.tableWidgetLibList->setColumnWidth (4, 40);

	TempLib=NULL;
	if(BBase!=NULL){
		CmdCreateTempMeasureLineMoveLibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		TempLib=Packet.Point;
	}
	//ColorGenerator	.setParent(ui.frameColorCube);
	//ColorGenerator	.Fit(ui.frameColorCube);

	AlignmentPoint=0;
	AlignmentImage=true;

	ui.tableWidgetLineMoveList->setColumnWidth(0,48);
	ui.tableWidgetLineMoveList->setColumnWidth(1,48);
	ui.tableWidgetLineMoveList->setColumnWidth(2,140);
	ui.tableWidgetLineMoveList->setColumnWidth(3,48);
	
	int	LibFolderID=ControlRememberer::GetInt(objectName()+/**/"\\LibFolderID",-1);
	if(LibFolderID>=0){
		QString	FolderName=GetLayersBase()->GetLibFolderName(LibFolderID);
		SetLibFolder(LibFolderID,FolderName);
	}
}

PropertyMeasureLineMoveForm::~PropertyMeasureLineMoveForm()
{
	if(TempLib!=NULL)
		delete	TempLib;
	TempLib=NULL;

	if(LTable!=NULL)
		delete	[]LTable;
	LTable=NULL;
}
MeasureLineMoveBase	*PropertyMeasureLineMoveForm::GetMeasureLineMoveBase(void)
{
	return (MeasureLineMoveBase *)GetLayersBase()->GetAlgorithmBase(/**/"Measure",/**/"MeasureLineMove");
}

void	PropertyMeasureLineMoveForm::BuildForShow(void)
{
	ShowListGrid();
}
void	PropertyMeasureLineMoveForm::TransmitDirectly(GUIDirectMessage *packet)
{
	MeasureLineMoveBase	*BBase=GetMeasureLineMoveBase();

	CmdMeasureLineMoveDrawModePacket	*DMode=dynamic_cast<CmdMeasureLineMoveDrawModePacket	*>(packet);
	if(DMode!=NULL){
		DMode->DrawAttr->NormalColor.setAlpha(BBase->TransparentLevel);
		DMode->DrawAttr->SelectedColor.setAlpha(BBase->TransparentLevel);
		DMode->DrawAttr->ActiveColor.setAlpha(BBase->TransparentLevel);

		int	Row=ui.tableWidgetLineMoveList->currentRow();
		if(Row>=0){
			LineMoveListForPacket *L=LTable[Row];
			DMode->DrawAttr->ShowingItemID=L->ItemID;
		}
		return;
	}
	CmdMeasureLineMoveDrawEnd	*BlockDEnd=dynamic_cast<CmdMeasureLineMoveDrawEnd *>(packet);
	if(BlockDEnd!=NULL){
		if(ui.toolButtonModeMark->isChecked()==true){
			SelectLibraryDialog	D(GetLayersBase(),NULL);
			if(D.exec()==(int)true){
				IntList PageList;
				GetLayersBase()->GetLocalPageFromArea(BlockDEnd->Area,PageList);
				for(IntClass *P=PageList.GetFirst();P!=NULL;P=P->GetNext()){
					int	page=P->GetValue();
					DataInPage	*pdata=GetLayersBase()->GetPageData(page);
					FlexArea	A=BlockDEnd->Area;
					pdata->ClipMoveAreaFromGlobal(A);
					if(A.GetPatternByte()>0){
						GUICmdSendAddManualMeasureLineMove	Cmd(GetLayersBase(),sRoot,sName,page);
						Cmd.ItemClass	=MeasureLineMove_ItemClass_Mark;
						Cmd.Area=A;

						int	n=ui.tableWidgetLibList->currentRow();
						int	SelectedID=-1;
						if(n>=0){
							SelectedID=LibList[n]->GetLibID();
						}
						if(SelectedID<0){
							SelectedID=D.SelectedID;
							Cmd.ItemName=D.ItemName;
						}
						Cmd.SelectedLibID=SelectedID;
						Cmd.Send(NULL,page,0);
					}
				}
			}
		}
		return;
	}
	AddLinePacket	*AddLinePacketVar=dynamic_cast<AddLinePacket *>(packet);
	if(AddLinePacketVar!=NULL){
		IntList PageList;
		GetLayersBase()->GetLocalPageFromVector(AddLinePacketVar->Vector,PageList);

		if(ui.toolButtonModeDistance->isChecked()==false){			
			for(IntClass *P=PageList.GetFirst();P!=NULL;P=P->GetNext()){
				int	page=P->GetValue();
				DataInPage	*pdata=GetLayersBase()->GetPageData(page);
				VectorLineBase	*v=AddLinePacketVar->Vector->CreateEmpty();
				*v=*AddLinePacketVar->Vector;
				pdata->ClipMoveVectorFromGlobal(v);

				GUICmdSendAddManualMeasureLineMove	Cmd(GetLayersBase(),sRoot,sName,page);
				Cmd.Vector=v->CreateDup();
				if(ui.toolButtonModeLine->isChecked()==true)
					Cmd.ItemClass	=MeasureLineMove_ItemClass_Line;
				if(ui.toolButtonModeRxLine->isChecked()==true)
					Cmd.ItemClass	=MeasureLineMove_ItemClass_RxLine;
				if(ui.toolButtonModeArc->isChecked()==true)
					Cmd.ItemClass	=MeasureLineMove_ItemClass_CornerR;
				if(ui.toolButtonModeDistance->isChecked()==true)
					Cmd.ItemClass	=MeasureLineMove_ItemClass_Distance;
				if(ui.toolButtonModeMark->isChecked()==true)
					Cmd.ItemClass	=MeasureLineMove_ItemClass_Mark;
						
				int	n=ui.tableWidgetLibList->currentRow();
				int	SelectedID=-1;
				if(n>=0){
					SelectedID=LibList[n]->GetLibID();
				}
				if(SelectedID<0){
					SelectLibraryDialog	DD(GetLayersBase());
					if(DD.exec()!=(int)true || DD.SelectedID<0){
						return;
					}
					SelectedID=DD.SelectedID;
					Cmd.ItemName=DD.ItemName;
				}
				Cmd.SelectedLibID=SelectedID;
				Cmd.Send(NULL,page,0);
			}
		}
		else{
			double	X1=AddLinePacketVar->Vector->GetFirstItem()->GetX();
			double	Y1=AddLinePacketVar->Vector->GetFirstItem()->GetY();
			double	X2=AddLinePacketVar->Vector->GetLastItem()->GetX();
			double	Y2=AddLinePacketVar->Vector->GetLastItem()->GetY();

			int	Page1=GetLayersBase()->GetLocalPageFromAreaFromDrawingTop(X1,Y1);
			int	Page2=GetLayersBase()->GetLocalPageFromAreaFromDrawingTop(X2,Y2);

			int		page=PageList.GetLast()->GetValue();

			DataInPage	*pdata=GetLayersBase()->GetPageData(page);
			VectorLineBase	*v=AddLinePacketVar->Vector->CreateEmpty();
			*v=*AddLinePacketVar->Vector;

			GUICmdSendAddManualMeasureLineMove	Cmd(GetLayersBase(),sRoot,sName,page);
			Cmd.ItemClass	=MeasureLineMove_ItemClass_Distance;
				
			int	n=ui.tableWidgetLibList->currentRow();
			int	SelectedID=-1;
			if(n>=0){
				SelectedID=LibList[n]->GetLibID();
			}
			if(SelectedID<0){
				SelectLibraryDialog	DD(GetLayersBase());
				if(DD.exec()!=(int)true || DD.SelectedID<0){
					return;
				}
				SelectedID=DD.SelectedID;
				Cmd.ItemName=DD.ItemName;
			}
			Cmd.SelectedLibID=SelectedID;

			if(Page1==Page2){
				pdata->ClipMoveVectorFromGlobal(v);
				Cmd.Vector=v->CreateDup();
				Cmd.Send(NULL,page,0);
			}
			else{
				Cmd.Vector=v->CreateDup();
				GUICmdReqMeasureLineMoveID	RCmd1(GetLayersBase(),sRoot,sName,Page1);
				GUICmdAckMeasureLineMoveID	ACmd1(GetLayersBase(),sRoot,sName,Page1);
				RCmd1.GlobalX	=X1;
				RCmd1.GlobalY	=Y1;
				if(RCmd1.Send(Page1,0,ACmd1)==false)
					return;
				GUICmdReqMeasureLineMoveID	RCmd2(GetLayersBase(),sRoot,sName,Page2);
				GUICmdAckMeasureLineMoveID	ACmd2(GetLayersBase(),sRoot,sName,Page2);
				RCmd2.GlobalX	=X2;
				RCmd2.GlobalY	=Y2;
				if(RCmd2.Send(Page2,0,ACmd2)==false)
					return;
				Cmd.NoCalc			=false;
				Cmd.GlobalPage1		=Page1;
				Cmd.ClosedItemID1	=ACmd1.ItemID;		
				Cmd.GlobalPage2		=Page2;
				Cmd.ClosedItemID2	=ACmd2.ItemID;
				Cmd.Send(NULL,page,0);

				int		pageHidden=PageList.GetFirst()->GetValue();
				GUICmdSendAddManualMeasureLineMove	CmdH(GetLayersBase(),sRoot,sName,pageHidden);
				CmdH.Vector			=v->CreateDup();
				CmdH.ItemClass		=MeasureLineMove_ItemClass_Distance;
				CmdH.SelectedLibID	=SelectedID;
				CmdH.NoCalc			=true;
				CmdH.GlobalPage1	=Page1;
				CmdH.ClosedItemID1	=ACmd1.ItemID;		
				CmdH.GlobalPage2	=Page2;
				CmdH.ClosedItemID2	=ACmd2.ItemID;
				CmdH.Send(NULL,pageHidden,0);
			}
		}
		ShowListGrid();
		return;
	}
	GUICmdMeasureLineMoveGetColorMap	*GUICmdMeasureLineMoveGetColorMapVar=dynamic_cast<GUICmdMeasureLineMoveGetColorMap *>(packet);
	if(GUICmdMeasureLineMoveGetColorMapVar!=NULL){
		IntList PageList;
		GetLayersBase()->GetLocalPageFromArea(GUICmdMeasureLineMoveGetColorMapVar->Area,PageList);
		for(IntClass *P=PageList.GetFirst();P!=NULL;P=P->GetNext()){
			int	page=P->GetValue();
			DataInPage	*pdata=GetLayersBase()->GetPageData(page);
			FlexArea	A=GUICmdMeasureLineMoveGetColorMapVar->Area;
			pdata->ClipMoveAreaFromGlobal(A);
			if(A.GetPatternByte()>0){
				CmdReqMeasureLineMoveColorMap	RCmd(GetLayersBase(),sRoot,sName,page);
				CmdAckMeasureLineMoveColorMap	ACmd(GetLayersBase(),sRoot,sName,page);
				RCmd.Area=A;
				RCmd.Send(page,0,ACmd);

				//ColorGenerator.Cube=ACmd.Color;
				//ColorGenerator.InitializedDoneCube();
				//ColorGenerator.Repaint();
			}
		}
		return;
	}
	CmdMeasureLineMoveLDown	*CmdMeasureLineMoveLDownVar=dynamic_cast<CmdMeasureLineMoveLDown *>(packet);
	if(CmdMeasureLineMoveLDownVar!=NULL){
		if(ui.tabWidget->currentIndex()==0){
			if(ui.checkBoxSelect1->isChecked()==true || ui.checkBoxSelect2->isChecked()==true){
				int	Row=ui.tableWidgetLineMoveList->currentRow();
				if(Row>=0){
					LineMoveListForPacket *L=LTable[Row];

					GUICmdReqChangeMeasureLineMoveEndPoint	RCmd(GetLayersBase(),sRoot,sName,L->Page);
					RCmd.Point1=ui.checkBoxSelect1->isChecked();
					RCmd.Point2=ui.checkBoxSelect2->isChecked();
					RCmd.ItemID=L->ItemID;
					int	localX ,localY;
					GetLayersBase()->GetLocalMatrixFromGlobal(CmdMeasureLineMoveLDownVar->GlobalX,CmdMeasureLineMoveLDownVar->GlobalY
															,localX ,localY);
					RCmd.LocalX =localX ;
					RCmd.LocalY	=localY;
					RCmd.Send(NULL,L->Page,0);
				}
			}
		}
		else if(ui.tabWidget->currentIndex()==1){
			if(AlignmentImage==true){
				ImagePoint[AlignmentPoint].SetXY(CmdMeasureLineMoveLDownVar->GlobalX,CmdMeasureLineMoveLDownVar->GlobalY);
				AlignmentImage=false;
			}
			else{
				ItemPoint[AlignmentPoint].SetXY(CmdMeasureLineMoveLDownVar->GlobalX,CmdMeasureLineMoveLDownVar->GlobalY);
				AlignmentImage=true;
				AlignmentPoint++;
				if(AlignmentPoint>=3)
					AlignmentPoint=0;
			}
		}
		return;
	}
	CmdGenerateMeasure	*CmdGenerateMeasureVar=dynamic_cast<CmdGenerateMeasure *>(packet);
	if(CmdGenerateMeasureVar!=NULL){
		for(int page=0;page<GetPageNumb();page++){
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdGenerateMeasure	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
			RCmd.BladePickupRL		=CmdGenerateMeasureVar->BladePickupRL;
			RCmd.BladePickupRH		=CmdGenerateMeasureVar->BladePickupRH;
			RCmd.BladePickupGL		=CmdGenerateMeasureVar->BladePickupGL;
			RCmd.BladePickupGH		=CmdGenerateMeasureVar->BladePickupGH;
			RCmd.BladePickupBL		=CmdGenerateMeasureVar->BladePickupBL;
			RCmd.BladePickupBH		=CmdGenerateMeasureVar->BladePickupBH;
			RCmd.BladeLeft			=CmdGenerateMeasureVar->BladeLeft ;
			RCmd.BladeRight			=CmdGenerateMeasureVar->BladeRight;
			RCmd.LineLib			=CmdGenerateMeasureVar->LineLib;
			RCmd.RxLineLib			=CmdGenerateMeasureVar->RxLineLib;
			RCmd.DistanceLib		=CmdGenerateMeasureVar->DistanceLib;
			RCmd.BladeMeasureData	=CmdGenerateMeasureVar->BladeMeasureData;
			RCmd.FilmMeasureData	=CmdGenerateMeasureVar->FilmMeasureData;
			RCmd.BladeHoleMinArea = CmdGenerateMeasureVar->BladeHoleMinArea;
			RCmd.BladeHoleErosionDot = CmdGenerateMeasureVar->BladeHoleErosionDot;
			RCmd.MaskLib			=CmdGenerateMeasureVar->MaskLib;
			RCmd.OnlyGenerateFilmLen=CmdGenerateMeasureVar->OnlyGenerateFilmLen;
			RCmd.SendOnly(GlobalPage,0);
		}
		return;
	}
	CmdReqCorrentValues	*CmdReqCorrentValuesVar=dynamic_cast<CmdReqCorrentValues *>(packet);
	if(CmdReqCorrentValuesVar!=NULL){
		for(int page=0;page<GetPageNumb();page++){
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdReqCorrentValues	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
			GUICmdAckCorrentValues	ACmd(GetLayersBase(),sRoot,sName,GlobalPage);
			RCmd.BladeMeasureData	=CmdReqCorrentValuesVar->BladeMeasureData;
			RCmd.Mastered	=CmdReqCorrentValuesVar->Mastered;
			if(RCmd.Send(GlobalPage,0,ACmd)==true){
				CmdReqCorrentValuesVar->BladeMeasureData=ACmd.BladeMeasureData;
			}
		}
		return;
	}
	CmdSetCorrectValues	*CmdSetCorrectValuesVar=dynamic_cast<CmdSetCorrectValues *>(packet);
	if(CmdSetCorrectValuesVar!=NULL){
		for(int page=0;page<GetPageNumb();page++){
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdSetCorrentValues	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
			RCmd.BladeMeasureData	=CmdSetCorrectValuesVar->BladeMeasureData;
			RCmd.LineLib			=CmdSetCorrectValuesVar->LineLib;
			RCmd.DistanceLib		=CmdSetCorrectValuesVar->DistanceLib;
			RCmd.BladePickupRL		=CmdSetCorrectValuesVar->BladePickupRL;
			RCmd.BladePickupRH		=CmdSetCorrectValuesVar->BladePickupRH;
			RCmd.BladePickupGL		=CmdSetCorrectValuesVar->BladePickupGL;
			RCmd.BladePickupGH		=CmdSetCorrectValuesVar->BladePickupGH;
			RCmd.BladePickupBL		=CmdSetCorrectValuesVar->BladePickupBL;
			RCmd.BladePickupBH		=CmdSetCorrectValuesVar->BladePickupBH;
			RCmd.BladeMeasureData	=CmdSetCorrectValuesVar->BladeMeasureData;
			RCmd.MaskLib			=CmdSetCorrectValuesVar->MaskLib;
			RCmd.Send(NULL,GlobalPage,0);
		}
		return;
	}
	CmdSetMeasureEndPoint	*CmdSetMeasureEndPointVar=dynamic_cast<CmdSetMeasureEndPoint *>(packet);
	if(CmdSetMeasureEndPointVar!=NULL){
		int	LocalX,LocalY;
		int	page=GetLayersBase()->GetLocalMatrixFromGlobal(CmdSetMeasureEndPointVar->X,CmdSetMeasureEndPointVar->Y
														,LocalX,LocalY);
		if(0<=page){
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdSetMeasureEndPoint	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
			RCmd.EndNo		=CmdSetMeasureEndPointVar->EndNo;
			RCmd.MeasureNo	=CmdSetMeasureEndPointVar->MeasureNo;
			RCmd.LocalX		=LocalX;
			RCmd.LocalY		=LocalY;
			RCmd.Send(NULL,GlobalPage,0);
		}
		return;

	}
	CmdSetOnlyBladeThreshold	*CmdSetOnlyBladeThresholdVar=dynamic_cast<CmdSetOnlyBladeThreshold *>(packet);
	if(CmdSetOnlyBladeThresholdVar!=NULL){
		for(int page=0;page<GetPageNumb();page++){
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdSetOnlyBladeThreshold	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
			RCmd.BladeMeasureData	=CmdSetOnlyBladeThresholdVar->BladeMeasureData;
			RCmd.FilmMeasureData	=CmdSetOnlyBladeThresholdVar->FilmMeasureData;
			RCmd.Send(NULL,GlobalPage,0);
		}
		return;
	}
	CmdReqDistancePacket	*CmdReqDistancePacketVar=dynamic_cast<CmdReqDistancePacket *>(packet);
	if(CmdReqDistancePacketVar!=NULL){
		CmdReqDistancePacketVar->DataList.RemoveAll();
		for(int page=0;page<GetPageNumb();page++){
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdReqListData	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
			GUICmdAckListData	ACmd(GetLayersBase(),sRoot,sName,GlobalPage);
			if(RCmd.Send(GlobalPage,0,ACmd)==true){
				for(MeasureDistanceItemInfo *L=ACmd.ListData.GetFirst();L!=NULL;L=L->GetNext()){
					L->Data.Page=GlobalPage;
				}
				CmdReqDistancePacketVar->DataList+=ACmd.ListData;
			}
		}
		return;
	}
	CmdSetDistanceCorrectValue	*CmdSetDistanceCorrectValueVar=dynamic_cast<CmdSetDistanceCorrectValue *>(packet);
	if(CmdSetDistanceCorrectValueVar!=NULL){
		int	GlobalPage=CmdSetDistanceCorrectValueVar->Page;
		if(0<=GlobalPage && GlobalPage<GetPageNumb()){
			GUICmdSetCorrectValue	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
			RCmd.Phase			=CmdSetDistanceCorrectValueVar->Phase		;
			RCmd.Page			=CmdSetDistanceCorrectValueVar->Page		;
			RCmd.ItemID			=CmdSetDistanceCorrectValueVar->ItemID		;
			RCmd.OKLengthLUnit	=CmdSetDistanceCorrectValueVar->OKLengthLUnit	;
			RCmd.OKLengthHUnit	=CmdSetDistanceCorrectValueVar->OKLengthHUnit	;	
			RCmd.Send(NULL,GlobalPage,0);
		}
		ShowListGrid();
		return;
	}
	CmdAddDistance	*CmdAddDistanceVar=dynamic_cast<CmdAddDistance *>(packet);
	if(CmdAddDistanceVar!=NULL){
		int	LocalX1,LocalY1;
		int	LocalX2,LocalY2;
		int	GlobalPage1=GetLayersBase()->GetLocalMatrixFromGlobal(CmdAddDistanceVar->X1,CmdAddDistanceVar->Y1,LocalX1,LocalY1);
		int	GlobalPage2=GetLayersBase()->GetLocalMatrixFromGlobal(CmdAddDistanceVar->X2,CmdAddDistanceVar->Y2,LocalX2,LocalY2);
		if(GlobalPage1==GlobalPage2){
			int	GlobalPage=GlobalPage1;
			if(0<=GlobalPage && GlobalPage<GetPageNumb()){
				GUICmdAddDistance	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);

				RCmd.LocalX1		=CmdAddDistanceVar->X1		;
				RCmd.LocalY1		=CmdAddDistanceVar->Y1		;
				RCmd.LocalX2		=CmdAddDistanceVar->X2		;
				RCmd.LocalY2		=CmdAddDistanceVar->Y2		;
				RCmd.LineLength		=CmdAddDistanceVar->LineLength		;
				RCmd.LineLibID1		=CmdAddDistanceVar->LineLibID1		;
				RCmd.LineLibID2		=CmdAddDistanceVar->LineLibID2		;
				RCmd.DistanceLibID	=CmdAddDistanceVar->DistanceLibID	;

				RCmd.Send(NULL,GlobalPage,0);
			}
		}
		ShowListGrid();
		return;			
	}
	CmdDeleteMeasureDistance	*CmdDeleteMeasureDistanceVar=dynamic_cast<CmdDeleteMeasureDistance *>(packet);
	if(CmdDeleteMeasureDistanceVar!=NULL){
		int	GlobalPage=CmdDeleteMeasureDistanceVar->Page;
		if(0<=GlobalPage && GlobalPage<GetPageNumb()){
			GUICmdDeleteMeasureDistance	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
			RCmd.Phase		=CmdDeleteMeasureDistanceVar->Phase		;
			RCmd.MeasureNo	=CmdDeleteMeasureDistanceVar->MeasureNo		;
			RCmd.Send(NULL,GlobalPage,0);
		}
		ShowListGrid();
		return;
	}
	CmdReqMeasureLineInfo	*CmdReqMeasureLineInfoVar=dynamic_cast<CmdReqMeasureLineInfo *>(packet);
	if(CmdReqMeasureLineInfoVar!=NULL){
		int	GlobalPage=CmdReqMeasureLineInfoVar->Page;
		if(0<=GlobalPage && GlobalPage<GetPageNumb()){
			GUICmdReqMeasureLineInfo	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
			RCmd.Phase			=CmdReqMeasureLineInfoVar->Phase		;
			RCmd.Page			=CmdReqMeasureLineInfoVar->Page		;
			RCmd.DistanceItemID	=CmdReqMeasureLineInfoVar->DistanceItemID		;
			RCmd.EndNo			=CmdReqMeasureLineInfoVar->EndNo	;
			RCmd.MeasureNo		=CmdReqMeasureLineInfoVar->MeasureNo	;
			GUICmdAckMeasureLineInfo	ACmd(GetLayersBase(),sRoot,sName,GlobalPage);
			RCmd.Send(GlobalPage,0,ACmd);
			CmdReqMeasureLineInfoVar->SearchDot=ACmd.SearchDot;
		}
		return;
	}
	CmdSetMeasureLineInfo	*CmdSetMeasureLineInfoVar=dynamic_cast<CmdSetMeasureLineInfo *>(packet);
	if(CmdSetMeasureLineInfoVar!=NULL){
		int	GlobalPage=CmdSetMeasureLineInfoVar->Page;
		if(0<=GlobalPage && GlobalPage<GetPageNumb()){
			GUICmdSetMeasureLineInfo	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
			RCmd.Phase			=CmdSetMeasureLineInfoVar->Phase		;
			RCmd.Page			=CmdSetMeasureLineInfoVar->Page		;
			RCmd.DistanceItemID	=CmdSetMeasureLineInfoVar->DistanceItemID		;
			RCmd.EndNo			=CmdSetMeasureLineInfoVar->EndNo	;
			RCmd.MeasureNo		=CmdSetMeasureLineInfoVar->MeasureNo	;
			RCmd.SearchDot		=CmdSetMeasureLineInfoVar->SearchDot;
			RCmd.Send(NULL,GlobalPage,0);
		}
		ShowListGrid();
		return;
	}
	CmdSetMeasureLineInfoAll	*CmdSetMeasureLineInfoAllVar=dynamic_cast<CmdSetMeasureLineInfoAll *>(packet);
	if(CmdSetMeasureLineInfoAllVar!=NULL){
		int	GlobalPage=CmdSetMeasureLineInfoAllVar->Page;
		if(0<=GlobalPage && GlobalPage<GetPageNumb()){
			GUICmdSetMeasureLineInfoAll	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
			RCmd.Phase			=CmdSetMeasureLineInfoAllVar->Phase		;
			RCmd.Page			=CmdSetMeasureLineInfoAllVar->Page		;
			RCmd.DistanceItemID	=CmdSetMeasureLineInfoAllVar->DistanceItemID		;
			RCmd.EndNo			=CmdSetMeasureLineInfoAllVar->EndNo	;
			RCmd.MeasureNo		=CmdSetMeasureLineInfoAllVar->MeasureNo	;
			RCmd.SearchDot		=CmdSetMeasureLineInfoAllVar->SearchDot;
			RCmd.Send(NULL,GlobalPage,0);
		}
		ShowListGrid();
		return;
	}
	CmdReqMeasureLinePosition	*CmdReqMeasureLinePositionVar=dynamic_cast<CmdReqMeasureLinePosition *>(packet);
	if(CmdReqMeasureLinePositionVar!=NULL){
		int	GlobalPage=CmdReqMeasureLinePositionVar->Page;
		if(0<=GlobalPage && GlobalPage<GetPageNumb()){
			GUICmdReqMeasureLineMovePosition	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
			GUICmdAckMeasureLineMovePosition	ACmd(GetLayersBase(),sRoot,sName,GlobalPage);
			RCmd.Phase	=CmdReqMeasureLinePositionVar->Phase;
			RCmd.ItemID	=CmdReqMeasureLinePositionVar->DistanceItemID;
			if(RCmd.Send(GlobalPage,0,ACmd)==true){
				CmdReqMeasureLinePositionVar->RetPos1X=ACmd.Point1X;
				CmdReqMeasureLinePositionVar->RetPos1Y=ACmd.Point1Y;
				CmdReqMeasureLinePositionVar->RetPos2X=ACmd.Point2X;
				CmdReqMeasureLinePositionVar->RetPos2Y=ACmd.Point2Y;
			}
		}
		return;
	}
}


void	PropertyMeasureLineMoveForm::ShowLibList(void)
{
	ui.tableWidgetLibList->setRowCount(0);
	MeasureLineMoveBase	*BBase=GetMeasureLineMoveBase();
	if(BBase!=NULL){
		CmdGetMeasureLineMoveLibraryListPacket	Packet(GetLayersBase());
		Packet.LibFolderID=LibFolderID;
		BBase->TransmitDirectly(&Packet);
		LibList	=Packet.AList;
		int	row=0;
		ui.tableWidgetLibList->setRowCount(Packet.AList.GetNumber());
		for(AlgorithmLibraryList *a=Packet.AList.GetFirst();a!=NULL;a=a->GetNext(),row++){
			QTableWidgetItem *W;
			W=ui.tableWidgetLibList->item ( row, 0);
			if(W==NULL){
				W=new QTableWidgetItem();
				ui.tableWidgetLibList->setItem ( row, 0,W);
				W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);			
			}
			W->setText(QString::number(a->GetLibID()));

			W=ui.tableWidgetLibList->item ( row, 1);
			if(W==NULL){
				W=new QTableWidgetItem();
				ui.tableWidgetLibList->setItem ( row, 1,W);
				W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			}
			W->setText(a->GetLibName());

			W=ui.tableWidgetLibList->item ( row, 2);
			if(W==NULL){
				W=new QTableWidgetItem();
				ui.tableWidgetLibList->setItem ( row, 2,W);
				W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			}
			//W->setText(QString::number(a->MinDiameter));

			W=ui.tableWidgetLibList->item ( row, 3);
			if(W==NULL){
				W=new QTableWidgetItem();
				ui.tableWidgetLibList->setItem ( row, 3,W);
				W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			}
			//W->setText(QString::number(a->MaxDiameter));
		}
	}
}

void	iSetDataToTable(QTableWidget *W ,int col ,int row ,const QVariant &value)
{
	W->model()->setData(W->model()->index(row,col),value);
}

static	int	SortFuncLTable(const void *a ,const void *b)
{
	LineMoveListForPacket	*ai=((LineMoveListForPacket **)a)[0];
	LineMoveListForPacket	*bi=((LineMoveListForPacket **)b)[0];

	bool	aok;
	double	An=ai->ItemName.toDouble(&aok);
	bool	bok;
	double	Bn=bi->ItemName.toDouble(&bok);
	if(aok==true && bok==true){
		if(An>Bn)
			return 1;
		if(An<Bn)
			return -1;
		return 0;
	}
	if(ai->ItemName>bi->ItemName)
		return 1;
	if(ai->ItemName<bi->ItemName)
		return -1;
	return 0;
}

void	PropertyMeasureLineMoveForm::ShowListGrid(void)
{
	static	volatile	bool	ReEntrant=false;

	if(ReEntrant==true)
		return;
	if(GetLayersBase()->IsValidData()==false)
		return;

	ReEntrant=true;
	QString	EmitterRoot=sRoot;
	QString	EmitterName=sName;
	GUICmdSendItemList	**BmpReceiver=new GUICmdSendItemList*[GetParamGlobal()->PageNumb];
	GUICmdReqItemList	**BmpRequester=new GUICmdReqItemList*[GetParamGlobal()->PageNumb];
	for(int page=0;page<GetParamGlobal()->PageNumb;page++){
		int	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),page);
		BmpReceiver[page]=new GUICmdSendItemList(GetLayersBase(),EmitterRoot,EmitterName,globalPage);
		BmpRequester[page]=new GUICmdReqItemList(GetLayersBase(),EmitterRoot,EmitterName,globalPage);
	}

	ListInfo.RemoveAll();
	for(int page=0;page<GetParamGlobal()->PageNumb;page++){
		if(BmpRequester[page]->Send(BmpRequester[page]->GetGlobalPage(),0,*BmpReceiver[page],60000)==true
		&& BmpReceiver[page]->IsReceived()==true){
			ListInfo+=BmpReceiver[page]->ListInfo;
		}
	}
	for(int page=0;page<GetParamGlobal()->PageNumb;page++){
		delete	BmpRequester[page];
		delete	BmpReceiver[page];
	}
	delete	[]BmpRequester;
	delete	[]BmpReceiver;

	int	N=0;
	int	Numb=ListInfo.GetNumber();
	ui.tableWidgetLineMoveList->setRowCount(Numb);
	if(LTable!=NULL){
		delete	[]LTable;
	}
	LTable=new LineMoveListForPacket*[Numb];
	for(LineMoveListForPacket *L=ListInfo.GetFirst();L!=NULL;L=L->GetNext(),N++){
		LTable[N]=L;
	}
	while(ListInfo.GetFirst()!=NULL){
		LineMoveListForPacket *M=ListInfo.GetFirst();
		ListInfo.RemoveList(M);
	}

	QSort(LTable,N,sizeof(LineMoveListForPacket *),SortFuncLTable);
	MeasureLineMoveBase	*ABase=GetMeasureLineMoveBase();
	AlgorithmLibraryContainer	*LibConatiner=ABase->GetLibraryContainer();

	ui.tableWidgetLineMoveList->setUpdatesEnabled(false);
	for(int i=0;i<N;i++){
		LineMoveListForPacket *L=LTable[i];
		ListInfo.AppendList(L);

		iSetDataToTable(ui.tableWidgetLineMoveList ,0,i ,QString::number(L->Page));
		iSetDataToTable(ui.tableWidgetLineMoveList ,1,i ,QString::number(L->ItemID));
		if(L->ItemName.isEmpty()==false) {
			iSetDataToTable(ui.tableWidgetLineMoveList, 2, i, L->ItemName);
		}
		else if(LibConatiner!=NULL && L->LibID>=0){
			QString	LibName=LibConatiner->GetLibraryName(L->LibID);
			iSetDataToTable(ui.tableWidgetLineMoveList, 2, i, LibName);
		}
		iSetDataToTable(ui.tableWidgetLineMoveList ,3,i ,QString::number(L->SearchDot));
		}
	ui.tableWidgetLineMoveList->setUpdatesEnabled(true);

	ReEntrant=false;
}

void PropertyMeasureLineMoveForm::on_pushButtonEditLibFolder_clicked()
{
	MeasureLineMoveBase	*BBase=GetMeasureLineMoveBase();
	int		RetSelectedLibFolderID;
	QString RetSelectedFolderName;
	if(ExeSelectLibFolderDialog(BBase->GetLibType(),GetLayersBase(),this
								,RetSelectedLibFolderID
								,RetSelectedFolderName)==true){
		ControlRememberer::SetValue(objectName()+/**/"\\LibFolderID",RetSelectedLibFolderID);
		SetLibFolder(RetSelectedLibFolderID,RetSelectedFolderName);
	}
}

void	PropertyMeasureLineMoveForm::SetLibFolder(int _LibFolderID ,const QString &LinFolderName)
{
	ui.labelLibFolderName->setText(LinFolderName);
	LibFolderID=_LibFolderID;
	ShowLibList();
}

void PropertyMeasureLineMoveForm::on_pushButtonCreateNew_clicked()
{
	GetLibraryFromWindow(*TempLib);
	CmdInsertMeasureLineMoveLibraryPacket	Cmd(GetLayersBase());
	Cmd.Point=TempLib;
	TempLib->SetLibFolderID(LibFolderID);
	MeasureLineMoveBase	*BBase=GetMeasureLineMoveBase();
	if(BBase!=NULL){
		BBase->TransmitDirectly(&Cmd);
	}
	ShowLibList();
}

void PropertyMeasureLineMoveForm::on_pushButtonUpdate_clicked()
{
	GetLibraryFromWindow(*TempLib);
	CmdUpdateMeasureLineMoveLibraryPacket	Cmd(GetLayersBase());
	Cmd.Point=TempLib;
	TempLib->SetLibFolderID(LibFolderID);
	MeasureLineMoveBase	*BBase=GetMeasureLineMoveBase();
	if(BBase!=NULL){
		BBase->TransmitDirectly(&Cmd);
	}
	ShowLibList();

}

void PropertyMeasureLineMoveForm::on_tableWidgetLibList_clicked(const QModelIndex &Index)
{
	int	r=Index.row();
	AlgorithmLibraryList	*a=LibList.GetItem(r);
	if(a!=NULL){
		TempLib->SetLibID(a->GetLibID());

		CmdLoadMeasureLineMoveLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		MeasureLineMoveBase	*BBase=GetMeasureLineMoveBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			if(Packet.Success==true){
				ShowLibrary(*TempLib);
			}
			else{
				QMessageBox::critical(NULL, LangSolver.GetString(PropertyMeasureLineMoveForm_LS,LID_0)/*"Library error"*/, LangSolver.GetString(PropertyMeasureLineMoveForm_LS,LID_1)/*"Not loaded this library record"*/);
			}
		}
	}
}
void	PropertyMeasureLineMoveForm::ShowLibrary(AlgorithmLibraryLevelContainer &data)
{
	MeasureLineMoveLibrary	*d=dynamic_cast<MeasureLineMoveLibrary *>(data.GetLibrary());
	if(data.GetLibID()<0)
		ui.EditLibID->setText(/**/"");
	else
		ui.EditLibID->setText(QString::number(data.GetLibID()));
	ui.EditLibName	->setText(data.GetLibName());

	ui.doubleSpinBoxThresholdM	->setValue(d->ThresholdM);
	ui.doubleSpinBoxThresholdP	->setValue(d->ThresholdP);
	ui.EditSearchDot			->setValue(d->SearchDot);
	ui.EditEdgeWidth			->setValue(d->EdgeWidth);
}

void	PropertyMeasureLineMoveForm::GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data)
{
	MeasureLineMoveLibrary	*d=dynamic_cast<MeasureLineMoveLibrary *>(data.GetLibrary());
	data.SetLibName(ui.EditLibName	->text());

	d->SearchDot	=ui.EditSearchDot			->value();
	d->ThresholdM	=ui.doubleSpinBoxThresholdM	->value();
	d->ThresholdP	=ui.doubleSpinBoxThresholdP	->value();
	d->EdgeWidth	=ui.EditEdgeWidth			->value();
}


void PropertyMeasureLineMoveForm::on_pushButtonLoadCSV_clicked()
{
	VectorLineDouble	V;
	struct	LineStruct{
		double	X1;
		double	Y1;
		double	X2;
		double	Y2;
	};
	struct	LineStruct	*LData=NULL;
	int		LDataNumb;

	QString CSVFileName=GetLayersBase()->LGetOpenFileName (0, LangSolver.GetString(PropertyMeasureLineMoveForm_LS,LID_2)/*"Load CSV"*/
														, /**/"", /**/"*.csv");
	if(CSVFileName.isEmpty()==false){
		QStringListListCSV	CSVData;
		if(CSVData.LoadFromCSVFile(CSVFileName)==true){
			int	RNumb=CSVData.GetRowCount();
			MeasureLineMoveBase	*BBase=GetMeasureLineMoveBase();

			LData=new struct	LineStruct[RNumb];
			LDataNumb=0;

			for(int r=0;r<RNumb;r++){
				QString	SX1=CSVData.Get(0,r);
				QString	SY1=CSVData.Get(1,r);
				QString	SX2=CSVData.Get(2,r);
				QString	SY2=CSVData.Get(3,r);
				bool	ok;
				double	x1=SX1.toDouble(&ok);
				if(ok==false)
					continue;
				double	y1=SY1.toDouble(&ok);
				if(ok==false)
					continue;
				double	x2=SX2.toDouble(&ok);
				if(ok==false)
					continue;
				double	y2=SY2.toDouble(&ok);
				if(ok==false)
					continue;
				LData[LDataNumb].X1=x1;
				LData[LDataNumb].Y1=-y1;
				LData[LDataNumb].X2=x2;
				LData[LDataNumb].Y2=-y2;
				LDataNumb++;
			}
			if(LDataNumb>0){
				double	MinX=LData[0].X1;
				double	MinY=LData[0].Y1;
				double	MaxX=LData[0].X1;
				double	MaxY=LData[0].Y1;
				for(int i=0;i<LDataNumb;i++){
					if(MinX>LData[i].X1)
						MinX=LData[i].X1;
					if(MinY>LData[i].Y1)
						MinY=LData[i].Y1;
					if(MinX>LData[i].X2)
						MinX=LData[i].X2;
					if(MinY>LData[i].Y2)
						MinY=LData[i].Y2;
					if(MaxX<LData[i].X1)
						MaxX=LData[i].X1;
					if(MaxY<LData[i].Y1)
						MaxY=LData[i].Y1;
					if(MaxX<LData[i].X2)
						MaxX=LData[i].X2;
					if(MaxY<LData[i].Y2)
						MaxY=LData[i].Y2;
				}
				double	Lx=MaxX-MinX;
				double	Ly=MaxY-MinY;
				double	L=max(Lx,Ly);
				double	Z=min(GetDotPerLine(0),GetMaxLines(0))/L;

				for(int i=0;i<LDataNumb;i++){
					LData[i].X1=(LData[i].X1-MinX)*Z;
					LData[i].Y1=(LData[i].Y1-MinY)*Z;
					LData[i].X2=(LData[i].X2-MinX)*Z;
					LData[i].Y2=(LData[i].Y2-MinY)*Z;

					V.Clear();
					V.AppendItemBase(new VectorItemDouble(LData[i].X1,LData[i].Y1));
					V.AppendItemBase(new VectorItemDouble(LData[i].X2,LData[i].Y2));

					IntList PageList;
					GetLayersBase()->GetLocalPageFromVector(&V,PageList);
					for(IntClass *P=PageList.GetFirst();P!=NULL;P=P->GetNext()){
						int	page=P->GetValue();
						VectorLineDouble	VTmp;
						VTmp=V;
						DataInPage	*pdata=GetLayersBase()->GetPageData(page);
						pdata->ClipMoveVectorFromGlobal(&VTmp);
						if(VTmp.IsNull()==false){
							GUICmdSendAddCSVMeasureLineMove	Cmd(GetLayersBase(),sRoot,sName,page);
							Cmd.Vector=VTmp.CreateDup();
							//CmdCreateByteArrayFromMeasureLineMoveItemPacket	BCmd;
							//BCmd.Point=D.BItem;
							//BBase->TransmitDirectly(&BCmd);
							//Cmd.BItem=BCmd.Buff;
							Cmd.Send(NULL,page,0);
						}
					}
				}
				delete	[]LData;
			}
		}
	}
}

void PropertyMeasureLineMoveForm::on_pushButtonExecuteAlign_clicked()
{
	MeasureLineMoveBase	*BBase=GetMeasureLineMoveBase();
	CmdExecuteAlignMeasureLineMove	Packet(GetLayersBase());
	Packet.ImagePoint[0]=ImagePoint[0];
	Packet.ImagePoint[1]=ImagePoint[1];
	Packet.ImagePoint[2]=ImagePoint[2];
	Packet.ItemPoint[0]=ItemPoint[0];
	Packet.ItemPoint[1]=ItemPoint[1];
	Packet.ItemPoint[2]=ItemPoint[2];
	BBase->TransmitDirectly(&Packet);
}
void PropertyMeasureLineMoveForm::on_pushButtonEditLibrary_clicked()
{
	EditLibraryDialog	D(GetLayersBase());
	D.exec();
}

void PropertyMeasureLineMoveForm::on_toolButtonModeLine_clicked()
{
	BroadcastShowInEdit();
}

void PropertyMeasureLineMoveForm::on_toolButtonModeArc_clicked()
{
	BroadcastShowInEdit();
}

void PropertyMeasureLineMoveForm::on_toolButtonModeDistance_clicked()
{
	BroadcastShowInEdit();
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Measure" ,/**/"MeasureLineMoveImagePanel" ,/**/"");
	if(GProp!=NULL){
		DisplayImageWithAlgorithm	*g=dynamic_cast<DisplayImageWithAlgorithm *>(GProp);
		if(g!=NULL){
			g->SetModeByOthers(mtFrameDraw::fdDualArrow,Qt::yellow);
		}
	}
}

void PropertyMeasureLineMoveForm::on_tableWidgetLineMoveList_clicked(const QModelIndex &MIndex)
{
	if(LTable!=NULL){
		LineMoveListForPacket *L=LTable[MIndex.row()];
		if(L==NULL)
			return;

		DataInPage	*P=GetLayersBase()->GetPageData(GetLayersBase()->GetLocalPageFromGlobal(L->Page));
		if(P!=NULL){
			CmdDrawImageRectPacket	Cmd( GetLayersBase()
										,L->x1+P->GetOutlineOffset()->x,L->y1+P->GetOutlineOffset()->y
										,L->x2+P->GetOutlineOffset()->x,L->y2+P->GetOutlineOffset()->y);
			GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Measure" ,/**/"MeasureLineMoveImagePanel" ,/**/"");
			if(GProp!=NULL)
				GProp->TransmitDirectly(&Cmd);
			CmdDrawImageActivate	ACmd(GetLayersBase(),L->Page,0,L->ItemID);
			if(GProp!=NULL)
				GProp->TransmitDirectly(&ACmd);
		}
	}
}

void PropertyMeasureLineMoveForm::on_tableWidgetLineMoveList_doubleClicked(const QModelIndex &index)
{
	QModelIndex	RIndex=ui.tableWidgetLineMoveList->currentIndex();
	if(RIndex.isValid()==false)
		return;
	int	R=RIndex.row();
	if(LTable!=NULL){
		LineMoveListForPacket *L=LTable[R];
		if(L==NULL)
			return;

		GUICmdReqItemThreshold	RCmd(GetLayersBase(),sRoot,sName,L->Page);
		GUICmdSendItemThreshold	SCmd(GetLayersBase(),sRoot,sName,L->Page);
		RCmd.ItemID=L->ItemID;
		if(RCmd.Send(RCmd.GetGlobalPage(),0,SCmd,60000)==true
		&& SCmd.IsReceived()==true){
			EditLineMoveDialog	DForm(GetLayersBase(),SCmd.ItemName ,SCmd.Thre);
			if(DForm.exec()==true){

				GUICmdSetItemThreshold	rCmd(GetLayersBase(),sRoot,sName,L->Page);
				rCmd.ItemID		=L->ItemID;
				rCmd.ItemName	=DForm.ItemName;
				MeasureLineMoveBase	*BBase=GetMeasureLineMoveBase();
				if(BBase==NULL)
					return;
				//CmdCreateThresholdPacket	PCmd(GetLayersBase());
				//BBase->TransmitDirectly(&PCmd);
				//rCmd.Thre		=PCmd.Thre;
				rCmd.Thre		=DForm.ThreData;
				DForm.ThreData=NULL;
				rCmd.Send(NULL,L->Page,0);
				rCmd.Thre=NULL;
			}
		}
		ShowListGrid();
	}
}

void PropertyMeasureLineMoveForm::on_toolButtonModeMark_clicked()
{
	BroadcastShowInEdit();
}

void PropertyMeasureLineMoveForm::on_checkBoxSelect1_clicked()
{
	if(ui.checkBoxSelect1->isChecked()==true){
		ui.checkBoxSelect2->setChecked(false);
	}
}


void PropertyMeasureLineMoveForm::on_checkBoxSelect2_clicked()
{
	if(ui.checkBoxSelect2->isChecked()==true){
		ui.checkBoxSelect1->setChecked(false);
	}
}

