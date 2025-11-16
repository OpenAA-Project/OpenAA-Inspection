#include "PropertyGerberFastFormResource.h"
#include "PropertyGerberFastForm.h"
#include "ui_PropertyGerberFastForm.h"
#include "XGerberFastPacket.h"
#include "XDataInLayer.h"
#include "XPropertyGerberFastPacket.h"
#include "EditMoveDialog.h"
#include "EditRotateDialog.h"
#include "EditShearDialog.h"
#include "EditZoomDialog.h"
#include "EditCompositeDefDialog.h"
#include "EditLayerTypeDialog.h"
#include "swap.h"
#include "GerberFastImagePanel.h"
#include "XDisplayImage.h"
#include "XDisplayImagePacket.h"
#include "MakeAlgorithmUpperDialog.h"
#include "XGerberImagePacket.h"
#include "MakeAlgorithmSimpleDialog.h"
#include "EditDCodeDialog.h"
#include "SelectStepInODBDialog.h"
#include "InputEchingFactorDialog.h"
#include "ConfirmLayersDialog.h"
#include "SelectLibraryDialog.h"
#include "XPropertyGerberFastCommon.h"
#include "SelectCompositeDefDialog.h"
#include "XDatabaseLoader.h"
#include <QMessageBox>

extern	const	char	*sRoot;
extern	const	char	*sName;

extern	const	char	*AlgoRoot;
extern	const	char	*AlgoName;

void	PropertyGerberFastForm::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdGetDrawAttr	*CmdGetDrawAttrVar=dynamic_cast<CmdGetDrawAttr *>(packet);
	if(CmdGetDrawAttrVar!=NULL){
		CmdGetDrawAttrVar->SimpleMode=ui->toolButtonSimpleMode->isChecked();
		for(int Line=0;Line<sizeof(child)/sizeof(child[0]);Line++){
			if(child[Line]->ButtonSelected.isChecked()==true){
				if(child[Line]->GetFileLayerNo()>=0){
					CmdGetDrawAttrVar->ShownFileID.Add(child[Line]->GetFileLayerNo());
				}
			}
			if(child[Line]->CheckBoxOperation.isChecked()==true){
				if(child[Line]->GetFileLayerNo()>=0){
					CmdGetDrawAttrVar->OperationalFileID.Add(child[Line]->GetFileLayerNo());
				}
			}
			CmdGetDrawAttrVar->LayerColor[Line]=child[Line]->GetColor();
			CmdGetDrawAttrVar->FileLayerIDTable[Line]=child[Line]->GetFileLayerNo();
		}
		for(int CLine=0;CLine<sizeof(CompChild)/sizeof(CompChild[0]);CLine++){
			int	Index	=CompChild[CLine]->ComboBComposite.currentIndex();
			if(Index>=0){
				QVariant	Q=CompChild[CLine]->ComboBComposite.itemData(Index);
				int	CompositeID=Q.toInt();
				if(CompChild[CLine]->ButtonSelected.isChecked()==true){
					CmdGetDrawAttrVar->ShownCompositeID.Add(CompositeID);
				}
				if(CompChild[CLine]->ButtonOperation.isChecked()==true){
					CmdGetDrawAttrVar->OperationalCompositeID.Add(CompositeID);
				}
			}
			CmdGetDrawAttrVar->CompColor[CLine]=CompChild[CLine]->GetColor();
		}
		CmdGetDrawAttrVar->DrawAutoMatchingArea	=ui->toolButtonShowAutoMatchArea->isChecked();
		CmdGetDrawAttrVar->DrawAutoMatchingImage=ui->toolButtonShowAutoMatchImage->isChecked();
		return;
	}
	GUICmdSetAutoMatchButtons	*GUICmdSetAutoMatchButtonsVar=dynamic_cast<GUICmdSetAutoMatchButtons *>(packet);
	if(GUICmdSetAutoMatchButtonsVar!=NULL){
		ui->toolButtonShowAutoMatchArea ->setChecked(GUICmdSetAutoMatchButtonsVar->DrawAutoMatchingArea);
		ui->toolButtonShowAutoMatchImage->setChecked(GUICmdSetAutoMatchButtonsVar->DrawAutoMatchingImage);
		return;
	}
	CmdGerberGetOperationModePacket	*GGMode=dynamic_cast<CmdGerberGetOperationModePacket *>(packet);
	if(GGMode!=NULL){
		GGMode->Mode=GetCurrentOperationMode();
		return;
	}
	CmdGerberLMouseDownIn3PAreaPacket	*GL3PArea=dynamic_cast<CmdGerberLMouseDownIn3PAreaPacket *>(packet);
	if(GL3PArea!=NULL){
		GerberFastBase	*Base=GetGerberFastBase();
		if(Base==NULL)
			return;
		if(ui->tabWidgetOperation->currentIndex()==1){
			if(GetInputTypeAlignment()==0){
				GL3PArea->Source->ImagePoint[GetInputNumberAlignment()].x=0;
				GL3PArea->Source->ImagePoint[GetInputNumberAlignment()].y=0;
				int	PointNumb=0;
				int	LocalPage=GetLayersBase()->GetLocalPageFromAreaFromDrawingTop(GL3PArea->Area);
				if(LocalPage<0){
					QMessageBox::warning(NULL
									, "Warning"
									, "Don't set this point outside");
					return;
				}
				int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(LocalPage);

				FlexArea	A=GL3PArea->Area;
				DataInPage	*P=GetLayersBase()->GetPageData(LocalPage);
				P->ClipMoveAreaFromGlobal(A);	
				for(IntClass *d=GL3PArea->LayerList.GetFirst();d!=NULL;d=d->GetNext()){
					int Layer=d->GetValue();
					GUICmdGerberReqPointFromArea	DReqMsg (GetLayersBase(),sRoot,sName,globalPage);
					GUICmdGerberSendPointFromArea	DSendMsg(GetLayersBase(),sRoot,sName,globalPage);
					DReqMsg.Area=A;
					DReqMsg.GlobalPage=globalPage;
					DReqMsg.Layer	  =Layer;
					if(DReqMsg.Send(globalPage,0,DSendMsg)==false){
						return;
					}
					GL3PArea->Source->ImagePoint[GetInputNumberAlignment()].x+=DSendMsg.LocalX+GetLayersBase()->GetGlobalOutlineOffset(LocalPage)->x-1;
					GL3PArea->Source->ImagePoint[GetInputNumberAlignment()].y+=DSendMsg.LocalY+GetLayersBase()->GetGlobalOutlineOffset(LocalPage)->y;
					PointNumb++;
				}			
				if(PointNumb!=0){
					GL3PArea->Source->ImagePoint[GetInputNumberAlignment()].x/=PointNumb;
					GL3PArea->Source->ImagePoint[GetInputNumberAlignment()].y/=PointNumb;
				}

				double	GPx=GL3PArea->Source->ImagePoint[GetInputNumberAlignment()].x;
				double	GPy=GL3PArea->Source->ImagePoint[GetInputNumberAlignment()].y;
				for(int page=0;page<GetPageNumb();page++){
					if(page==LocalPage)
						continue;
					int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
					GUICmdSendImagePointXY	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
					RCmd.Turn=GetInputNumberAlignment();

					RCmd.GPx=GPx;
					RCmd.GPy=GPy;
					RCmd.Send(NULL,GlobalPage,0);
				}

				UpdateAlignment();
				GoNextStepAlignment();
				return;
			}
			if(GetInputTypeAlignment()!=0 && Base!=NULL && Base->CenterizeByArea==true){
				int	LocalPage=GetLayersBase()->GetLocalPageFromAreaFromDrawingTop(GL3PArea->Area);
				if(LocalPage<0){
					QMessageBox::warning(NULL
									, "Warning"
									, "Don't set this point outside");
					return;
				}
				int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(LocalPage);
				GUICmdReqGerberCenterize	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
				GUICmdSendGerberCenterize	SCmd(GetLayersBase(),sRoot,sName,GlobalPage);

				//DataInPage	*pdata=GetLayersBase()->GetPageData(LocalPage);
				//FlexArea	Area=GL3PArea->Area;
				//pdata->ClipMoveAreaFromGlobal(Area);

				XYData	*XY=GetLayersBase()->GetGlobalOutlineOffset(GlobalPage);
				RCmd.Area	=GL3PArea->Area;
				RCmd.Area.MoveToNoClip(-XY->x,-XY->y);
				RCmd.XYArea	=GL3PArea->XYArea;

				int	SelectedNumb=0;
				int	SelectedLayer=0;
				for(int Line=0;Line<sizeof(child)/sizeof(child[0]);Line++){
					if(child[Line]->ButtonSelected.isChecked()==true){
						SelectedNumb++;
						SelectedLayer=Line+1;
					}
				}
				if(SelectedNumb!=1){
					QMessageBox::warning(NULL
										,"Warning"
										,"Show One layer of gerber");
					return;
				}
				RCmd.Layer=SelectedLayer;
				RCmd.Send(GlobalPage,0,SCmd);

				if(SCmd.Ret==true){
					GL3PArea->Source->CadPoint[GetInputNumberAlignment()].x=SCmd.x+XY->x;
					GL3PArea->Source->CadPoint[GetInputNumberAlignment()].y=SCmd.y+XY->y;
					UpdateAlignment();
					GoNextStepAlignment();
				}
			}
		}
		return;
	}
	CmdGerberLMouseDownIn3PAPacket	*CmdGerberLMouseDownIn3PAPacketVar=dynamic_cast<CmdGerberLMouseDownIn3PAPacket *>(packet);
	if(CmdGerberLMouseDownIn3PAPacketVar!=NULL){
		GerberFastBase	*Base=GetGerberFastBase();
		if(Base==NULL)
			return;
		if(ui->tabWidgetOperation->currentIndex()==3){
			GerberFastImagePanel	*Source=(GerberFastImagePanel *)GetImagePanel();
			int	GlobalPage=GetLayersBase()->GetGlobalPage(CmdGerberLMouseDownIn3PAPacketVar->GlobalX,CmdGerberLMouseDownIn3PAPacketVar->GlobalY);
			if(GlobalPage<0){
				QMessageBox::warning(NULL
								, "Warning"
								, "Don't set this point outside");
				return;
			}
			int	LocalPage=GetLayersBase()->GetLocalPageFromGlobal(GlobalPage);
			if(LocalPage<0){
				return;
			}
			int	LocalX, LocalY;
			if(GetLayersBase()->GetLocalMatrixFromGlobal(CmdGerberLMouseDownIn3PAPacketVar->GlobalX,CmdGerberLMouseDownIn3PAPacketVar->GlobalY
													, LocalX, LocalY)>=0){
				if(GetAMInputTypeAlignment()==0){
					DataInPage	*P=GetLayersBase()->GetPageData(LocalPage);

					Source->AMImagePoint[GetAMInputNumberAlignment()].x=LocalX+GetLayersBase()->GetGlobalOutlineOffset(LocalPage)->x;
					Source->AMImagePoint[GetAMInputNumberAlignment()].y=LocalY+GetLayersBase()->GetGlobalOutlineOffset(LocalPage)->y;

					GUICmdSendAMImagePointXY	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
					RCmd.Turn=GetAMInputNumberAlignment();

					RCmd.GPx=Source->AMImagePoint[GetAMInputNumberAlignment()].x;
					RCmd.GPy=Source->AMImagePoint[GetAMInputNumberAlignment()].y;
					RCmd.Send(NULL,GlobalPage,0);
					
					UpdateAMAlignment();
					GoNextStepAMAlignment();
					return;
				}
				else if(GetAMInputTypeAlignment()!=0 && Base!=NULL){

					Source->AMCadPoint[GetAMInputNumberAlignment()].x=LocalX;
					Source->AMCadPoint[GetAMInputNumberAlignment()].y=LocalY;
					UpdateAMAlignment();
					GoNextStepAMAlignment();
				}
			}
		}
		return;
	}
	GUICmdReqGerberInfo	*GUICmdReqGerberInfoVar=dynamic_cast<GUICmdReqGerberInfo *>(packet);
	if(GUICmdReqGerberInfoVar!=NULL){
		for(int Line=0;Line<sizeof(child)/sizeof(child[0]);Line++){
			if(child[Line]->ButtonSelected.isChecked()==true){
				GUICmdReqGerberInfoVar->DrawingLayers.Add(true);
			}
			else{
				GUICmdReqGerberInfoVar->DrawingLayers.Add(false);
			}
		}
		return;
	}
	GUICmdAckGerberInfo	*GUICmdAckGerberInfoVar=dynamic_cast<GUICmdAckGerberInfo *>(packet);
	if(GUICmdAckGerberInfoVar!=NULL){
		ui->tableWidgetGerberInfo->setRowCount(GUICmdAckGerberInfoVar->GInfo.GetCount());
		int	row=0;
		for(GerberInfo *g=GUICmdAckGerberInfoVar->GInfo.GetFirst();g!=NULL;g=g->GetNext(),row++){
			::SetDataToTable(ui->tableWidgetGerberInfo,0,row ,QString::number(g->FileLayerID));
			::SetDataToTable(ui->tableWidgetGerberInfo,1,row ,g->TypeStr);
			::SetDataToTable(ui->tableWidgetGerberInfo,2,row ,QString::number(g->DCode));
			::SetDataToTable(ui->tableWidgetGerberInfo,3,row ,QString(/**/"(")
															+ QString::number(g->ItemID)
															+ QString(/**/")")
															+g->Message);
		}
		return;
	}
	CmdGerberTabModePacket	*CmdGerberTabModePacketVar=dynamic_cast<CmdGerberTabModePacket *>(packet);
	if(CmdGerberTabModePacketVar!=NULL){
		if(ui->tabWidgetOperation->currentIndex()==0){
			CmdGerberTabModePacketVar->Mode=CmdGerberTabModePacket::_Loading;
		}
		else if(ui->tabWidgetOperation->currentIndex()==1){
			CmdGerberTabModePacketVar->Mode=CmdGerberTabModePacket::_Operation;
		}
		else if(ui->tabWidgetOperation->currentIndex()==2){
			CmdGerberTabModePacketVar->Mode=CmdGerberTabModePacket::_Imaging;
		}
		else if(ui->tabWidgetOperation->currentIndex()==3){
			CmdGerberTabModePacketVar->Mode=CmdGerberTabModePacket::_AutoMatching;
		}
		else if(ui->tabWidgetOperation->currentIndex()==4){
			CmdGerberTabModePacketVar->Mode=CmdGerberTabModePacket::_GenerateBlocks;
		}
		return;
	}
	CmdGerberRemoveAutoMatchingPoint	*CmdGerberRemoveAutoMatchingPointVar=dynamic_cast<CmdGerberRemoveAutoMatchingPoint *>(packet);
	if(CmdGerberRemoveAutoMatchingPointVar!=NULL){
		int	LocalX,LocalY;
		int	GlobalPage=GetLayersBase()->GetGlobalPage(CmdGerberRemoveAutoMatchingPointVar->GlobalX,CmdGerberRemoveAutoMatchingPointVar->GlobalY);
		if(GlobalPage>=0){
			GetLayersBase()->ShowProcessingForm("Remove Auto-match point");
			if(GetLayersBase()->GetLocalMatrixFromGlobal(CmdGerberRemoveAutoMatchingPointVar->GlobalX,CmdGerberRemoveAutoMatchingPointVar->GlobalY
													,LocalX,LocalY)>=0){

				GUICmdRemoveAutoMatchingPoint	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);

				RCmd.LocalX=LocalX;
				RCmd.LocalY=LocalY;
				RCmd.Send(NULL,GlobalPage,0);
				GetLayersBase()->CloseProcessingForm();
			}
		}
		return;
	}
	CmdGerberGetShowingState	*CmdGerberGetShowingStateVar=dynamic_cast<CmdGerberGetShowingState *>(packet);
	if(CmdGerberGetShowingStateVar!=NULL){
		SendShowingStateLayer(CmdGerberGetShowingStateVar->ButtonsToShowLayer ,CmdGerberGetShowingStateVar->ButtonsToOperateLayer);
		return;
	}
	GUICmdSetDrawAttr	*GUICmdSetDrawAttrVar=dynamic_cast<GUICmdSetDrawAttr *>(packet);
	if(GUICmdSetDrawAttrVar!=NULL){
		for(int i=0;i<MaxGerberLayer;i++){
			if(child[i]!=NULL){
				if(child[i]->GetFileLayerNo()>=0 && GUICmdSetDrawAttrVar->ShownFileID.IsInclude(child[i]->GetFileLayerNo())==true)
					child[i]->ButtonSelected   .setChecked(true);
				else
					child[i]->ButtonSelected   .setChecked(false);
				if(child[i]->GetFileLayerNo()>=0 && GUICmdSetDrawAttrVar->OperationalFileID.IsInclude(child[i]->GetFileLayerNo())==true)
					child[i]->CheckBoxOperation.setChecked(true);
				else
					child[i]->CheckBoxOperation.setChecked(false);
				child[i]->SetColor(GUICmdSetDrawAttrVar->LayerColor[i]);
			}
		}
		for(int i=0;i<MaxGerberLayer;i++){
			if(CompChild[i]!=NULL){
				if(GUICmdSetDrawAttrVar->ShownCompositeID.IsInclude(CompChild[i]->LayerNo)==true)
					CompChild[i]->ButtonSelected .setChecked(true);
				else
					CompChild[i]->ButtonSelected .setChecked(false);
				if(GUICmdSetDrawAttrVar->OperationalCompositeID.IsInclude(CompChild[i]->LayerNo)==true)
					CompChild[i]->ButtonOperation.setChecked(true);
				else
					CompChild[i]->ButtonOperation.setChecked(false);
				CompChild[i]->SetColor(GUICmdSetDrawAttrVar->CompColor[i]);
			}
		}
		return;
	}
	CmdAutoFileEntry	*CmdAutoFileEntryVar=dynamic_cast<CmdAutoFileEntry *>(packet);
	if(CmdAutoFileEntryVar!=NULL){
		GerberFastBase	*GBase=GetGerberFastBase();
		if(GBase!=NULL){
			GBase->TransmitDirectly(CmdAutoFileEntryVar);
			if(CmdAutoFileEntryVar->StepData.GetCount()>1){
				SelectStepInODBDialog	DStep(GetLayersBase(),CmdAutoFileEntryVar->StepData);
				int	r=DStep.exec();
				if(r==(int)true){
					CmdAutoFileEntryODB	ODBPacket(GetLayersBase());
					ODBPacket.LayerPathList	=CmdAutoFileEntryVar->FileNames;
					ODBPacket.StepData		=DStep.StepData;
					ODBPacket.MatrixLayers	=CmdAutoFileEntryVar->MatrixLayers;
					GBase->TransmitDirectly(&ODBPacket);
					for(int i=0;i<ODBPacket.FileNames.count() && i<MaxGerberLayer;i++){
						for(int	Row=0;Row<MaxGerberLayer;Row++){
							if(child[Row]->EditFileName.text().isEmpty()==true){
								QString	FileName=ODBPacket.FileNames[i];
								child[Row]->EditFileName.setText(FileName);
								break;
							}
						}
					}
				}	
			}
			else{
				for(int i=0;i<CmdAutoFileEntryVar->FileNames.count() && i<MaxGerberLayer;i++){
					for(int	Row=0;Row<MaxGerberLayer;Row++){
						if(child[Row]->EditFileName.text().isEmpty()==true){
							QString	FileName=CmdAutoFileEntryVar->FileNames[i];
							child[Row]->EditFileName.setText(FileName);
							break;
						}
					}
				}
			}
		}
		return;
	}
	GUICmdSendMatchAutoLikeManual	*GUICmdSendMatchAutoLikeManualVar=dynamic_cast<GUICmdSendMatchAutoLikeManual *>(packet);
	if(GUICmdSendMatchAutoLikeManualVar!=NULL){
		ShowAutoMatchInfo();
		return;
	}
	CmdAddMatchingAlignmentPoint	*CmdAddMatchingAlignmentPointVar=dynamic_cast<CmdAddMatchingAlignmentPoint *>(packet);
	if(CmdAddMatchingAlignmentPointVar!=NULL){
		GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Create Gerber automatching alignment");

		IntList PageList;
		GetLayersBase()->GetLocalPageFromArea(CmdAddMatchingAlignmentPointVar->Area,PageList);
		for(IntClass *P=PageList.GetFirst();P!=NULL;P=P->GetNext()){
			int	page=P->GetValue();
			DataInPage	*pdata=GetLayersBase()->GetPageData(page);
			FlexArea	A=CmdAddMatchingAlignmentPointVar->Area;
			pdata->ClipMoveAreaFromGlobal(A);
			if(A.GetPatternByte()>0){
				int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
				GUICmdAddMatchingAlignmentPoint	Cmd(GetLayersBase(),sRoot,sName,GlobalPage);
				Cmd.Area=A;
				Cmd.LayerList=CmdAddMatchingAlignmentPointVar->LayerList;
				if(ui->toolButtonAreaForParallel->isChecked()==true){
					Cmd.PointType=1;
				}
				else if(ui->toolButtonAreaForRotate->isChecked()==true){
					Cmd.PointType=2;
				}
				else if(ui->toolButtonAreaForZoom->isChecked()==true){
					Cmd.PointType=3;
				}
				Cmd.SendOnly(GlobalPage,0);
			}
		}
		return;
	}
	CmdAddGerberLine	*CmdAddGerberLineVar=dynamic_cast<CmdAddGerberLine *>(packet);
	if(CmdAddGerberLineVar!=NULL){
		int	LineNumb=0;
		for(int Line=0;Line<sizeof(child)/sizeof(child[0]);Line++){
			if(child[Line]->ButtonSelected.isChecked()==true){
				LineNumb++;
			}
		}
		if(LineNumb!=1){
			ConfirmLayersDialog		D(this,false);
			D.exec();
		}
		LineNumb=0;
		int	SelectedLine=0;
		for(int Line=0;Line<sizeof(child)/sizeof(child[0]);Line++){
			if(child[Line]->ButtonSelected.isChecked()==true){
				LineNumb++;
				SelectedLine=Line;
			}
		}
		if(LineNumb==1){
			int	FileLayerNo=child[SelectedLine]->GetFileLayerNo();
			GUICmdReqApertureInfo	RCmd(GetLayersBase(),sRoot,sName,0);
			GUICmdAckApertureInfo	ACmd(GetLayersBase(),sRoot,sName,0);
			RCmd.GerberLayer=child[SelectedLine]->GetFileLayerNo();
			if(RCmd.Send(0,0,ACmd)==true){
				EditDCodeDialog	*D=new EditDCodeDialog(FileLayerNo,GetLayersBase(),&ACmd.InfoList);
				if(D->exec()==(int)true && D->SelectedList.GetCount()==1){
					GUICmdChangeApertureInfo	CCmd(GetLayersBase(),sRoot,sName,0);
					CCmd.GerberLayer	=FileLayerNo;
					CCmd.InfoList		=ACmd.InfoList;
					CCmd.SelectedList	=D->SelectedList;
					for(int page=0;page<GetPageNumb();page++){
						int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
						CCmd.Send(NULL,GlobalPage,0);
					}
					int	L=0;
					int	DCode=-1;
					for(GerberApertureInfo	*a=ACmd.InfoList.GetFirst();a!=NULL;a=a->GetNext(),L++){
						if(D->SelectedList[L]==true){
							DCode=a->DCode;
							break;
						}
					}
					if(DCode>=0){
						GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Add Line in Gerber layer");

						for(int page=0;page<GetPageNumb();page++){
							int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
							GUICmdAddGerberLine		RCmd(GetLayersBase(),sRoot,sName,GlobalPage);

							RCmd.X1=CmdAddGerberLineVar->X1+GetLayersBase()->GetGlobalOutlineOffset(GlobalPage)->x;
							RCmd.Y1=CmdAddGerberLineVar->Y1+GetLayersBase()->GetGlobalOutlineOffset(GlobalPage)->x;
							RCmd.X2=CmdAddGerberLineVar->X2+GetLayersBase()->GetGlobalOutlineOffset(GlobalPage)->x;
							RCmd.Y2=CmdAddGerberLineVar->Y2+GetLayersBase()->GetGlobalOutlineOffset(GlobalPage)->x;
							RCmd.FileLayerNo=FileLayerNo;
							RCmd.DCode		=DCode;
							RCmd.Send(NULL,GlobalPage,0);
						}
					}
				}
			}
		}
		return;
	}
	CmdSearchLayerLibByDialog	*CmdSearchLayerLibByDialogVar=dynamic_cast<CmdSearchLayerLibByDialog *>(packet);
	if(CmdSearchLayerLibByDialogVar!=NULL){
		SelectLibraryDialog	D(GetLayersBase());
		if(D.exec()==QDialog::Accepted){
			CmdSearchLayerLibByDialogVar->LibID=D.SelectedLibID;
		}
		return;
	}
	CmdSearcCompositeIDByDialog	*CmdSearcCompositeIDByDialogVar=dynamic_cast<CmdSearcCompositeIDByDialog *>(packet);
	if(CmdSearcCompositeIDByDialogVar!=NULL){
		SelectCompositeDefDialog	D(GetLayersBase());
		if(D.exec()==QDialog::Accepted){
			CmdSearcCompositeIDByDialogVar->CompositeID=D.SelectedCompositeID;
		}
		return;
	}
	CmdGetCompositeName	*CmdGetCompositeNameVar=dynamic_cast<CmdGetCompositeName *>(packet);
	if(CmdGetCompositeNameVar!=NULL){
		GerberFastBase	*ABase=(GerberFastBase *)GetLayersBase()->GetAlgorithmBase(AlgoRoot ,AlgoName);
		GerberCompositeDefLayer *L=ABase->CompositeDef.Search(CmdGetCompositeNameVar->CompositeID);
		if(L!=NULL){
			CmdGetCompositeNameVar->CompositeName	=L->Name;
		}
		return;
	}
	GenerateBlocksFrom	*GenerateBlocksFromVar=dynamic_cast<GenerateBlocksFrom *>(packet);
	if(GenerateBlocksFromVar!=NULL){
		for(int page=0;page<GetPageNumb();page++){
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdGenerateBlockFrom	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
			RCmd.LayerOrComposite	=GenerateBlocksFromVar->LayerOrComposite	;
			if(GenerateBlocksFromVar->LayerOrComposite==0){
				for(int i=0;i<MaxGerberLayer;i++){
					if(child[i]->GetLibID()==GenerateBlocksFromVar->LayerCompositeID){
						RCmd.LayerCompositeID	=child[i]->GetFileLayerNo();
					}
				}
			}
			else{
				RCmd.LayerCompositeID	=GenerateBlocksFromVar->LayerCompositeID	;
			}
			RCmd.OmitLayerOrComposite	=GenerateBlocksFromVar->OmitLayerOrComposite	;
			if(GenerateBlocksFromVar->OmitLayerOrComposite==0){
				for(int i=0;i<MaxGerberLayer;i++){
					if(child[i]->GetLibID()==GenerateBlocksFromVar->OmitLayerCompositeID){
						RCmd.OmitLayerCompositeID	=child[i]->GetFileLayerNo();
					}
				}
			}
			else{
				RCmd.OmitLayerCompositeID	=GenerateBlocksFromVar->OmitLayerCompositeID	;
			}
			RCmd.GeneratedLibType	=GenerateBlocksFromVar->GeneratedLibType	;
			RCmd.GeneratedLibID		=GenerateBlocksFromVar->GeneratedLibID		;
			
			RCmd.ThresholdData		=GenerateBlocksFromVar->ThresholdData		;
			RCmd.GFileContainer		=GenerateBlocksFromVar->GFileContainer		;
			RCmd.Send(NULL,GlobalPage,0);
		}
		return;
	}
	CmdDeallocateLibInLine	*CmdDeallocateLibInLineVar=dynamic_cast<CmdDeallocateLibInLine *>(packet);
	if(CmdDeallocateLibInLineVar!=NULL){
		for(int Line=0;Line<sizeof(child)/sizeof(child[0]);Line++){
			if(child[Line]->EditFileName.text()==CmdDeallocateLibInLineVar->FileName){
				child[Line]->ClearLibID();
			}
		}
		return;
	}
	CmdSetCompositeLine	*CmdSetCompositeLineVar=dynamic_cast<CmdSetCompositeLine *>(packet);
	if(CmdSetCompositeLineVar!=NULL){
		GerberFastBase	*Base=GetGerberFastBase();
		if(Base==NULL)
			return;
		on_pushButtonClearDrawLayer_clicked();
		on_pushButtonClearCompositeDrawLayer_clicked();
		if(CmdSetCompositeLineVar->GerberType==0){
			for(int Line=0;Line<MaxGerberLayer;Line++){
				if(child[Line]->GetLibID()==CmdSetCompositeLineVar->GerberID){
					child[Line]->ButtonSelected.setChecked(true);
				}
			}
			SlotClickedSelected(-1);
		}
		else{
			int	Index=0;
			for(GerberCompositeDefLayer *L=Base->CompositeDef.GetFirst();L!=NULL;L=L->GetNext()){
				if(L->LibFolderID==GetLayersBase()->GetLibFolderID() || GetLayersBase()->GetLibFolderID()<0){
					if(L->CompositeID==CmdSetCompositeLineVar->GerberID){
						CompChild[1]->ComboBComposite.setCurrentIndex(Index+1);
						CompChild[1]->ButtonSelected.setChecked(true);
						CompClickedSelected(CompChild[1]->LayerNo);
					}
					Index++;
				}
			}
		}
		return;
	}
	CmdGerberSelectLayerNo	*CmdGerberSelectLayerNoVar=dynamic_cast<CmdGerberSelectLayerNo *>(packet);
	if(CmdGerberSelectLayerNoVar!=NULL){
		ConfirmLayersDialog	D(this,false);
		if(D.exec()==true){
			for(int i=0;i<MaxGerberLayer;i++){
				if(child[i]->IsValidLine()==false){
					break;
				}
				if(child[i]->IsOperational()==true){
					CmdGerberSelectLayerNoVar->GenGerberLayerNo=i;
					CmdGerberSelectLayerNoVar->GenGerberLib=child[i]->GetLibID();
					break;
				}
			}
		}
		return;
	}
	GUICmdSetGenerateAlgo	*GUICmdSetGenerateAlgoVar=dynamic_cast<GUICmdSetGenerateAlgo *>(packet);
	if(GUICmdSetGenerateAlgoVar!=NULL){
		if(GUICmdSetGenerateAlgoVar->GerberAlgoType==AlgoGenerationalLine::_GenFromShiftable)
			ui->checkBoxMakeAlgoShiftable	->setChecked(true);
		else
			ui->checkBoxMakeAlgoShiftable	->setChecked(false);

		if(GUICmdSetGenerateAlgoVar->GerberAlgoType==AlgoGenerationalLine::_GenFromStable)
			ui->checkBoxMakeAlgoSeparate	->setChecked(true);
		else
			ui->checkBoxMakeAlgoSeparate	->setChecked(false);

		if(GUICmdSetGenerateAlgoVar->GerberAlgoType==AlgoGenerationalLine::_GenFromEnlarge)
			ui->checkBoxMakeAlgoEnlarge	->setChecked(true);
		else
			ui->checkBoxMakeAlgoEnlarge	->setChecked(false);

		if(GUICmdSetGenerateAlgoVar->GerberAlgoType==AlgoGenerationalLine::_GenFromShrinked)
			ui->checkBoxMakeAlgoShrinked	->setChecked(true);
		else
			ui->checkBoxMakeAlgoShrinked	->setChecked(false);

		if(GUICmdSetGenerateAlgoVar->GerberAlgoType>=0){
			if(GUICmdSetGenerateAlgoVar->GenGerberLayerNo>=0 && child[GUICmdSetGenerateAlgoVar->GenGerberLayerNo]->IsValidLine()==true){
				child[GUICmdSetGenerateAlgoVar->GenGerberLayerNo]->SetLibID(GUICmdSetGenerateAlgoVar->GenGerberLib);
				on_pushButtonInitialAlgo_clicked();

				int	Row=0;
				for(AlgoGenerationalLine	*E=MakeAlgoAllList.GetFirst();E!=NULL;E=E->GetNext(),Row++){
					E->UpperLayers->ClearLibrary();
					if(E->BaseLayerID==GUICmdSetGenerateAlgoVar->GenGerberLayerNo){
						if(E->AutoGenType==GUICmdSetGenerateAlgoVar->GerberAlgoType){
							if(E->UpperLayers->GetCount()<=Row){
								int	L=1;
								for(AlgoGenerationalLine	*e=MakeAlgoAllList.GetFirst();e!=NULL;e=e->GetNext(),L++){
									AlgoGenerationalLine	*m=new AlgoGenerationalLine(0);
									m->AlgoGenID	=L;
									m->BaseLayerID=E->BaseLayerID;
									m->AutoGenType=e->AutoGenType;
									E->UpperLayers->AppendList(m);
								}
							}
							QString	LibName=GetLayersBase()->GetLibraryName( GUICmdSetGenerateAlgoVar->GenLibType
																			,GUICmdSetGenerateAlgoVar->GenLibID);
							AlgorithmLibraryList	*a=new AlgorithmLibraryList( GUICmdSetGenerateAlgoVar->GenLibType
																				,GUICmdSetGenerateAlgoVar->GenLibID
																				,LibName);
							E->UpperLayers->GetItem(Row)->Libraries.AppendList(a);
						}
					}
				}
			}
			else if(GUICmdSetGenerateAlgoVar->GenGerberLib>=0){
				on_pushButtonInitialAlgo_clicked();
				for(int i=0;i<MaxGerberLayer;i++){
					if(child[i]->IsValidLine()==false){
						break;
					}
					if(child[i]->GetLibID()==GUICmdSetGenerateAlgoVar->GenGerberLib){
						AlgoGenerationalLine	*E=MakeAlgoAllList[i];
						E->UpperLayers->ClearLibrary();
						if(E->AutoGenType==GUICmdSetGenerateAlgoVar->GerberAlgoType){
							if(E->UpperLayers->GetCount()<=i){
								int	L=1;
								for(AlgoGenerationalLine	*e=MakeAlgoAllList.GetFirst();e!=NULL;e=e->GetNext(),L++){
									AlgoGenerationalLine	*m=new AlgoGenerationalLine(0);
									m->AlgoGenID	=L;
									m->BaseLayerID=E->BaseLayerID;
									m->AutoGenType=e->AutoGenType;
									E->UpperLayers->AppendList(m);
								}
							}

							QString	LibName=GetLayersBase()->GetLibraryName( GUICmdSetGenerateAlgoVar->GenLibType
																			,GUICmdSetGenerateAlgoVar->GenLibID);
							AlgorithmLibraryList	*a=new AlgorithmLibraryList( GUICmdSetGenerateAlgoVar->GenLibType
																				,GUICmdSetGenerateAlgoVar->GenLibID
																				,LibName);
							E->UpperLayers->GetItem(i)->Libraries.AppendList(a);
						}
					}
				}
			}
		}
		ShowMakeAlgoAllList();
		return;
	}
	GUICmdGenerateAlgo	*GUICmdGenerateAlgoVar=dynamic_cast<GUICmdGenerateAlgo *>(packet);
	if(GUICmdGenerateAlgoVar!=NULL){
		on_pushButtonToAlgo_clicked();
		return;
	}
	CmdReqGerberLayerList	*CmdReqGerberLayerListVar=dynamic_cast<CmdReqGerberLayerList *>(packet);
	if(CmdReqGerberLayerListVar!=NULL){
		CmdReqGerberLayerListVar->GFileContainer.RemoveAll();
		for(int Line=0;Line<sizeof(child)/sizeof(child[0]);Line++){
			child[Line]->StoreFromWindow();
			QString	FileName=child[Line]->EditFileName.text();
			if(FileName.isEmpty()==false && child[Line]->GetLibID()>=0){
				GerberGenerationFileList	*g=new GerberGenerationFileList();
				g->FileName	 =FileName;
				g->LayerLibID=child[Line]->GetFileLayerNo();
				g->LibID	 =child[Line]->GetLibID();
				CmdReqGerberLayerListVar->GFileContainer.AppendList(g);
			}
		}
		return;
	}
}
