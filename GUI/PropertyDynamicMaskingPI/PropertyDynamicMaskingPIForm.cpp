#include "AddManualItemFormResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyDynamicMaskingPI\PropertyDynamicMaskingPIForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "PropertyDynamicMaskingPIForm.h"
#include "AddManualItemForm.h"
#include "AddMonoManualItemForm.h"
#include "XPropertyDynamicMaskingPIPacket.h"
#include "XDataInLayer.h"
#include "XDisplayImage.h"
#include "XDisplayImagePacket.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

PropertyDynamicMaskingPIForm::PropertyDynamicMaskingPIForm(LayersBase *Base ,QWidget *parent)
	: GUIFormBase(Base,parent)
{
	ui.setupUi(this);
}

PropertyDynamicMaskingPIForm::~PropertyDynamicMaskingPIForm()
{
}
DynamicMaskingPIBase	*PropertyDynamicMaskingPIForm::GetDynamicMaskingPIBase(void)
{
	return (DynamicMaskingPIBase	*)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"DynamicMaskingPI");
}
void	PropertyDynamicMaskingPIForm::BuildForShow(void)
{
	ShowInEdit();
}
void	PropertyDynamicMaskingPIForm::TransmitDirectly(GUIDirectMessage *packet)
{
	AddDynamicMaskingPIAreaPacket *AddDynamicMaskingPIAreaPacketVar=dynamic_cast<AddDynamicMaskingPIAreaPacket *>(packet);
	if(AddDynamicMaskingPIAreaPacketVar!=NULL){
		//if(GetDynamicMaskingPIBase()->OnlyMakeMask==false){
		if(ui.radioButtonPickupMask->isChecked()==true){
			if(GetLayerNumb(0)==1){
				AddMonoManualItemForm	Q(GetLayersBase(),this);
				if(Q.exec()==(int)true){
					IntList PageList;
					GetLayersBase()->GetLocalPageFromArea(AddDynamicMaskingPIAreaPacketVar->MaskArea,PageList);
					for(IntClass *P=PageList.GetFirst();P!=NULL;P=P->GetNext()){
						int	page=P->GetValue();
						DataInPage	*pdata=GetLayersBase()->GetPageData(page);
						FlexArea	A=AddDynamicMaskingPIAreaPacketVar->MaskArea;
						pdata->ClipMoveAreaFromGlobal(A);
						if(A.GetPatternByte()>0){
							GUICmdAddDynamicMaskingPIArea	Cmd(GetLayersBase(),sRoot,sName,page);
							Cmd.MaskArea=A;
		
							Cmd.AbsLR=Q.AbsLR;
							Cmd.AbsHR=Q.AbsHR;
							Cmd.AbsLG=Q.AbsLG;
							Cmd.AbsHG=Q.AbsHG;
							Cmd.AbsLB=Q.AbsLB;
							Cmd.AbsHB=Q.AbsHB;
							Cmd.EnlargeDot	=Q.EnlargeDot;
							Cmd.EnsmallDot	=Q.EnsmallDot;
							Cmd.BlockWidth	=Q.BlockWidth;
							Cmd.BlockHeight	=Q.BlockHeight;
							Cmd.OpeType		=Q.OpeType;
							Cmd.DrawColR	=Q.DrawColR;
							Cmd.MinSize		=Q.MinSize;

							Cmd.AbsLR2=Q.AbsLR2;
							Cmd.AbsHR2=Q.AbsHR2;
							Cmd.EnlargeDot2	=Q.EnlargeDot2;
							Cmd.EnsmallDot2	=Q.EnsmallDot2;
							Cmd.DrawColR2	=Q.DrawColR2;
							Cmd.AdaptedPickupLayers	=Q.AdaptedPickupLayers;
							Cmd.SendOnly(page,0);
						}
					}
					ShowInfoList();
				}
			}
			else if(GetLayerNumb(0)>=3){
				GUIFormBase	*g=GetLayersBase()->FindByName(/**/"Inspection",/**/"DynamicMaskingPIImagePanel" ,/**/"");
				if(g!=NULL){
					DisplayImageWithAlgorithm	*V=dynamic_cast<DisplayImageWithAlgorithm *>(g);
					if(V!=NULL){
						IntList	LayerList;
						V->GetActiveLayerList(LayerList);
						if(LayerList.GetCount()==1){
							int	Layer=LayerList.GetFirst()->GetValue();
							AddMonoManualItemForm	Q(GetLayersBase(),this);
							if(Q.exec()==(int)true){
								IntList PageList;
								GetLayersBase()->GetLocalPageFromArea(AddDynamicMaskingPIAreaPacketVar->MaskArea,PageList);
								for(IntClass *P=PageList.GetFirst();P!=NULL;P=P->GetNext()){
									int	page=P->GetValue();
									DataInPage	*pdata=GetLayersBase()->GetPageData(page);
									FlexArea	A=AddDynamicMaskingPIAreaPacketVar->MaskArea;
									pdata->ClipMoveAreaFromGlobal(A);
									if(A.GetPatternByte()>0){
										GUICmdAddDynamicMaskingPIArea	Cmd(GetLayersBase(),sRoot,sName,page);
										Cmd.MaskArea=A;
										Cmd.Layer	=Layer;
										Cmd.AbsLR=Q.AbsLR;
										Cmd.AbsHR=Q.AbsHR;
										Cmd.AbsLG=Q.AbsLG;
										Cmd.AbsHG=Q.AbsHG;
										Cmd.AbsLB=Q.AbsLB;
										Cmd.AbsHB=Q.AbsHB;
										Cmd.EnlargeDot	=Q.EnlargeDot;
										Cmd.EnsmallDot	=Q.EnsmallDot;
										Cmd.BlockWidth	=Q.BlockWidth;
										Cmd.BlockHeight	=Q.BlockHeight;
										Cmd.OpeType		=Q.OpeType;
										Cmd.DrawColR	=Q.DrawColR;
										Cmd.MinSize		=Q.MinSize;

										Cmd.AbsLR2=Q.AbsLR2;
										Cmd.AbsHR2=Q.AbsHR2;
										Cmd.EnlargeDot2	=Q.EnlargeDot2;
										Cmd.EnsmallDot2	=Q.EnsmallDot2;
										Cmd.DrawColR2	=Q.DrawColR2;
										Cmd.AdaptedPickupLayers	=Q.AdaptedPickupLayers;
										Cmd.SendOnly(page,0);
									}
								}
								ShowInfoList();
							}
						}
						else{
							AddManualItemForm	Q(GetLayersBase(),this);
							Q.Initial();
							if(Q.exec()==(int)true){
								IntList PageList;
								GetLayersBase()->GetLocalPageFromArea(AddDynamicMaskingPIAreaPacketVar->MaskArea,PageList);
								for(IntClass *P=PageList.GetFirst();P!=NULL;P=P->GetNext()){
									int	page=P->GetValue();
									DataInPage	*pdata=GetLayersBase()->GetPageData(page);
									FlexArea	A=AddDynamicMaskingPIAreaPacketVar->MaskArea;
									pdata->ClipMoveAreaFromGlobal(A);
									if(A.GetPatternByte()>0){
										GUICmdAddDynamicMaskingPIArea	Cmd(GetLayersBase(),sRoot,sName,page);
										Cmd.AdaptedPickupLayers=LayerList;
										Cmd.Layer	=-1;
										Cmd.MaskArea=A;
										Cmd.Mergin		=Q.Mergin;
										Cmd.MaskingColor=Q.MaskingColor;
										Cmd.EnsmallDot	=Q.EnsmallDot;
										Cmd.EnlargeDot	=Q.EnlargeDot;
										Cmd.Send(NULL,page,0);
									}
								}
								ShowInfoList();
							}
						}
					}
				}
			}
		}
		else{
			int	R=ui.tableWidgetMaskingList->currentRow();
			if(R<0)
				return;
			IntList PageList;
			GetLayersBase()->GetLocalPageFromArea(AddDynamicMaskingPIAreaPacketVar->MaskArea,PageList);
			for(IntClass *P=PageList.GetFirst();P!=NULL;P=P->GetNext()){
				int	page=P->GetValue();
				DataInPage	*pdata=GetLayersBase()->GetPageData(page);
				FlexArea	A=AddDynamicMaskingPIAreaPacketVar->MaskArea;
				pdata->ClipMoveAreaFromGlobal(A);
				if(A.GetPatternByte()>0){
					GUICmdAddDynamicMaskingPIArea	Cmd(GetLayersBase(),sRoot,sName,page);
					Cmd.MaskArea=A;
					Cmd.ParentItemID	=List[R]->ID;
					Cmd.OpeType		=DynamicMaskingPIThreshold::_MakeDynamicMask;
					Cmd.SendOnly(page,0);
				}
			}
			ShowInfoList();
		}
	}
	CmdReqDMaskingPIMode	*CmdReqDMaskingPIModeVar=dynamic_cast<CmdReqDMaskingPIMode *>(packet);
	if(CmdReqDMaskingPIModeVar!=NULL){
		if(ui.radioButtonPickupMask->isChecked()==true)
			CmdReqDMaskingPIModeVar->Mode=DynamicMaskingPIDrawAttr::_PickupMode;
		else if(ui.radioButtonDrawMask->isChecked()==true)
			CmdReqDMaskingPIModeVar->Mode=DynamicMaskingPIDrawAttr::_MakingMode;
		int	R=ui.tableWidgetMaskingList->currentRow();
		if(R>=0){
			CmdReqDMaskingPIModeVar->SelectedItem.Page	=List[R]->GlobalPage;
			CmdReqDMaskingPIModeVar->SelectedItem.ID	=List[R]->ID;
		}
		else{
			CmdReqDMaskingPIModeVar->SelectedItem.Page	=-1;
			CmdReqDMaskingPIModeVar->SelectedItem.ID	=-1;
		}
		return;
	}
}

void	PropertyDynamicMaskingPIForm::ShowInEdit(void)
{
	GUICmdReqDMaskingPIAreaInfoList	**RCmd=new GUICmdReqDMaskingPIAreaInfoList*[GetPageNumb()];
	GUICmdAckDMaskingPIAreaInfoList	**ACmd=new GUICmdAckDMaskingPIAreaInfoList*[GetPageNumb()];
	List.RemoveAll();
	for(int page=0;page<GetPageNumb();page++){
		RCmd[page]=new GUICmdReqDMaskingPIAreaInfoList(GetLayersBase(),sRoot,sName,page);
		ACmd[page]=new GUICmdAckDMaskingPIAreaInfoList(GetLayersBase(),sRoot,sName,page);

		RCmd[page]->Send(page,0,*ACmd[page]);
		for(DynamicMaskingPIInfoList *c=ACmd[page]->Data.GetFirst();c!=NULL;c=c->GetNext()){
			c->Page=page;
		}
		List+=ACmd[page]->Data;
	}

	ui.tableWidgetMaskingList->setRowCount(List.GetNumber());
	int	R=0;
	for(DynamicMaskingPIInfoList *c=List.GetFirst();c!=NULL;c=c->GetNext(), R++){
		QTableWidgetItem *w;
		w=ui.tableWidgetMaskingList->item (R, 0);
		if(w==NULL){
			ui.tableWidgetMaskingList->setItem(R,0,(w=new QTableWidgetItem()));
			w->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		}
		w->setText(QString::number(c->Page));

		if(c->OpeType==DynamicMaskingPIThreshold::_PickupMask){
			w=ui.tableWidgetMaskingList->item (R, 1);
			if(w==NULL){
				ui.tableWidgetMaskingList->setItem(R,1,(w=new QTableWidgetItem()));
				w->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			}
			w->setText(LangSolver.GetString(PropertyDynamicMaskingPIForm_LS,LID_0)/*"Pickup Mask"*/);

			w=ui.tableWidgetMaskingList->item (R, 2);
			if(w==NULL){
				ui.tableWidgetMaskingList->setItem(R,2,(w=new QTableWidgetItem()));
				w->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			}
			w->setText(QString::number(c->EnsmallDot));
	
			w=ui.tableWidgetMaskingList->item (R, 3);
			if(w==NULL){
				ui.tableWidgetMaskingList->setItem(R,3,(w=new QTableWidgetItem()));
				w->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			}
			w->setText(QString::number(c->EnlargeDot));

			w=ui.tableWidgetMaskingList->item (R, 4);
			if(w==NULL){
				ui.tableWidgetMaskingList->setItem(R,4,(w=new QTableWidgetItem()));
				w->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			}
			w->setText(QString::number(c->Cx)+QString(/**/",")+QString::number(c->Cy));
		}
		else if(c->OpeType==DynamicMaskingPIThreshold::_DrawMask){
			w=ui.tableWidgetMaskingList->item (R, 1);
			if(w==NULL){
				ui.tableWidgetMaskingList->setItem(R,1,(w=new QTableWidgetItem()));
				w->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			}
			w->setText(LangSolver.GetString(PropertyDynamicMaskingPIForm_LS,LID_1)/*"Draw mask"*/);

			w=ui.tableWidgetMaskingList->item (R, 2);
			if(w==NULL){
				ui.tableWidgetMaskingList->setItem(R,2,(w=new QTableWidgetItem()));
				w->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			}
			w->setText(LangSolver.GetString(PropertyDynamicMaskingPIForm_LS,LID_2)/*"Bright"*/+QString::number((int)(c->DrawColR)));
	
			w=ui.tableWidgetMaskingList->item (R, 3);
			if(w==NULL){
				ui.tableWidgetMaskingList->setItem(R,3,(w=new QTableWidgetItem()));
				w->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			}
			w->setText(/**/"");

			w=ui.tableWidgetMaskingList->item (R, 4);
			if(w==NULL){
				ui.tableWidgetMaskingList->setItem(R,4,(w=new QTableWidgetItem()));
				w->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			}
			w->setText(/**/"");
		}
		else if(c->OpeType==DynamicMaskingPIThreshold::_MakeDynamicMask){
			w=ui.tableWidgetMaskingList->item (R, 1);
			if(w==NULL){
				ui.tableWidgetMaskingList->setItem(R,1,(w=new QTableWidgetItem()));
				w->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			}
			w->setText(LangSolver.GetString(PropertyDynamicMaskingPIForm_LS,LID_3)/*"Making Mask"*/);
		}
	}
	for(int page=0;page<GetPageNumb();page++){
		delete	RCmd[page];
		delete	ACmd[page];
	}
	delete	[]RCmd;
	delete	[]ACmd;

	// setcolumnwidth
	ui.tableWidgetMaskingList->setColumnWidth(0, 40);
	ui.tableWidgetMaskingList->setColumnWidth(1, 90);
	ui.tableWidgetMaskingList->setColumnWidth(2, 60);
	ui.tableWidgetMaskingList->setColumnWidth(3, 60);
	ui.tableWidgetMaskingList->setColumnWidth(4, 60);
}

void PropertyDynamicMaskingPIForm::on_tableWidgetMaskingList_clicked(const QModelIndex &)
{
	int	R=ui.tableWidgetMaskingList->currentRow();
	if(R<0)
		return;
	DynamicMaskingPIInfoList *c=List.GetItem(R);
	if(c!=NULL){
		if(c->OpeType==DynamicMaskingPIThreshold::_PickupMask){
			ui.stackedWidget->setCurrentIndex(0);
		}
		else if(c->OpeType==DynamicMaskingPIThreshold::_DrawMask){
			ui.stackedWidget->setCurrentIndex(1);
		}
		ui.spinBoxDark		->setValue(c->AbsLR);
		ui.spinBoxLight		->setValue(c->AbsHR);
		ui.spinBoxEnsmall	->setValue(c->EnsmallDot);
		ui.spinBoxEnlarge	->setValue(c->EnlargeDot);
		ui.spinBoxBlockWidth->setValue(c->BlockWidth);
		ui.spinBoxBlockHeight->setValue(c->BlockHeight);
		ui.spinBoxMinSize	->setValue(c->MinSize);

		if(c->OpeType==DynamicMaskingPIThreshold::_PickupMask)
			ui.radioButtonPickupMask->setChecked(true);
		if(c->OpeType==DynamicMaskingPIThreshold::_DrawMask)
			ui.radioButtonDrawMask	->setChecked(true);
		ui.spinBoxDrawCol->setValue(c->DrawColR);
		if(c->Layer>=0){
			IntList LayerList;
			LayerList.Add(c->Layer);
			SetLayersFromLib(LayerList);
		}
		else{
			IntList LayerList;
			LayerList=c->AdaptedPickupLayers;
			SetLayersFromLib(LayerList);
		}

		DataInPage	*P=GetLayersBase()->GetPageData(c->GlobalPage);
		if(P!=NULL){
			CmdDrawImageRectPacket	Cmd( GetLayersBase()
										,c->x1+P->GetOutlineOffset()->x,c->y1+P->GetOutlineOffset()->y
										,c->x2+P->GetOutlineOffset()->x,c->y2+P->GetOutlineOffset()->y);
			GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"DynamicMaskingPIImagePanel" ,/**/"");
			if(GProp!=NULL)
				GProp->TransmitDirectly(&Cmd);
			CmdDrawImageActivate	ACmd(GetLayersBase(),c->Page,c->Layer,c->ID);
			if(GProp!=NULL)
				GProp->TransmitDirectly(&ACmd);
		}
	}
}

void PropertyDynamicMaskingPIForm::SetLayersFromLib(IntList &LayerList)
{
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"DynamicMaskingPIImagePanel" ,/**/"");
	if(GProp!=NULL){
		DisplayImage	*di=dynamic_cast<DisplayImage *>(GProp);
		if(di!=NULL){
			di->SetActiveLayerList(LayerList);
		}
	}
}
void PropertyDynamicMaskingPIForm::ShowInfoList(void)
{
	ShowInEdit();
}


void PropertyDynamicMaskingPIForm::on_tableWidgetMaskingList_doubleClicked(QModelIndex)
{
	on_pushButtonSet_clicked();
}
void PropertyDynamicMaskingPIForm::on_pushButtonSet_clicked()
{
	int	Row=ui.tableWidgetMaskingList->currentRow();
	if(GetLayerNumb(0)==1){
		DynamicMaskingPIInfoList	*p=List.GetItem(Row);
		AddMonoManualItemForm	Q(GetLayersBase(),this);
		Q.AbsLR			=p->AbsLR;
		Q.AbsHR			=p->AbsHR;
		Q.AbsLG			=p->AbsLG;
		Q.AbsHG			=p->AbsHG;
		Q.AbsLB			=p->AbsLB;
		Q.AbsHB			=p->AbsHB;
		Q.EnlargeDot	=p->EnlargeDot;
		Q.EnsmallDot	=p->EnsmallDot;
		Q.BlockWidth	=p->BlockWidth;
		Q.BlockHeight	=p->BlockHeight;
		Q.OpeType		=p->OpeType;
		Q.DrawColR		=p->DrawColR;
		Q.MinSize		=p->MinSize;

		Q.AbsLR2		=p->AbsLR2;
		Q.AbsHR2		=p->AbsHR2;
		Q.EnlargeDot2	=p->EnlargeDot2;
		Q.EnsmallDot2	=p->EnsmallDot2;
		Q.DrawColR2		=p->DrawColR2;
		Q.AdaptedPickupLayers	=p->AdaptedPickupLayers;
		Q.SetInitial();
		if(Q.exec()==(int)true){
			int	page=p->GlobalPage;
			GUICmdModDynamicMaskingPIArea	Cmd(GetLayersBase(),sRoot,sName,page);
			Cmd.ID		=p->ID;
			Cmd.AbsLR	=Q.AbsLR;
			Cmd.AbsHR	=Q.AbsHR;
			Cmd.AbsLG	=Q.AbsLG;
			Cmd.AbsHG	=Q.AbsHG;
			Cmd.AbsLB	=Q.AbsLB;
			Cmd.AbsHB	=Q.AbsHB;
			Cmd.EnlargeDot	=Q.EnlargeDot;
			Cmd.EnsmallDot	=Q.EnsmallDot;
			Cmd.BlockWidth	=Q.BlockWidth;
			Cmd.BlockHeight	=Q.BlockHeight;
			Cmd.OpeType		=Q.OpeType;
			Cmd.DrawColR	=Q.DrawColR;
			Cmd.MinSize		=Q.MinSize;

			Cmd.AbsLR2=Q.AbsLR2;
			Cmd.AbsHR2=Q.AbsHR2;
			Cmd.EnlargeDot2	=Q.EnlargeDot2;
			Cmd.EnsmallDot2	=Q.EnsmallDot2;
			Cmd.DrawColR2	=Q.DrawColR2;
			Cmd.AdaptedPickupLayers	=Q.AdaptedPickupLayers;

			Cmd.SendOnly(page,0);
		}
		ShowInfoList();
	}	
	else if(GetLayerNumb(0)>=3){
		GUIFormBase	*g=GetLayersBase()->FindByName(/**/"Inspection",/**/"DynamicMaskingPIImagePanel" ,/**/"");
		if(g!=NULL){
			DisplayImageWithAlgorithm	*V=dynamic_cast<DisplayImageWithAlgorithm *>(g);
			if(V!=NULL){
				IntList	LayerList;
				V->GetActiveLayerList(LayerList);
				if(LayerList.GetCount()==1){
					int	Layer=LayerList.GetFirst()->GetValue();
					DynamicMaskingPIInfoList	*p=List.GetItem(Row);
					AddMonoManualItemForm	Q(GetLayersBase(),this);
					Q.AbsLR			=p->AbsLR;
					Q.AbsHR			=p->AbsHR;
					Q.AbsLG			=p->AbsLG;
					Q.AbsHG			=p->AbsHG;
					Q.AbsLB			=p->AbsLB;
					Q.AbsHB			=p->AbsHB;
					Q.EnlargeDot	=p->EnlargeDot;
					Q.EnsmallDot	=p->EnsmallDot;
					Q.BlockWidth	=p->BlockWidth;
					Q.BlockHeight	=p->BlockHeight;
					Q.OpeType		=p->OpeType;
					Q.DrawColR		=p->DrawColR;
					Q.MinSize		=p->MinSize;

					Q.AbsLR2		=p->AbsLR2;
					Q.AbsHR2		=p->AbsHR2;
					Q.EnlargeDot2	=p->EnlargeDot2;
					Q.EnsmallDot2	=p->EnsmallDot2;
					Q.DrawColR2		=p->DrawColR2;
					Q.AdaptedPickupLayers	=p->AdaptedPickupLayers;
					Q.SetInitial();
					if(Q.exec()==(int)true){
						int	page=p->GlobalPage;
						GUICmdModDynamicMaskingPIArea	Cmd(GetLayersBase(),sRoot,sName,page);
						Cmd.ID		=p->ID;
						Cmd.Layer	=Layer;
						Cmd.AbsLR=Q.AbsLR;
						Cmd.AbsHR=Q.AbsHR;
						Cmd.AbsLG=Q.AbsLG;
						Cmd.AbsHG=Q.AbsHG;
						Cmd.AbsLB=Q.AbsLB;
						Cmd.AbsHB=Q.AbsHB;
						Cmd.EnlargeDot	=Q.EnlargeDot;
						Cmd.EnsmallDot	=Q.EnsmallDot;
						Cmd.BlockWidth	=Q.BlockWidth;
						Cmd.BlockHeight	=Q.BlockHeight;
						Cmd.OpeType		=Q.OpeType;
						Cmd.DrawColR	=Q.DrawColR;
						Cmd.MinSize		=Q.MinSize;

						Cmd.AbsLR2=Q.AbsLR2;
						Cmd.AbsHR2=Q.AbsHR2;
						Cmd.EnlargeDot2	=Q.EnlargeDot2;
						Cmd.EnsmallDot2	=Q.EnsmallDot2;
						Cmd.DrawColR2	=Q.DrawColR2;
						Cmd.AdaptedPickupLayers	=Q.AdaptedPickupLayers;

						Cmd.SendOnly(page,0);
					}
				}
				else{
					DynamicMaskingPIInfoList	*p=List.GetItem(Row);
					AddManualItemForm	Q(GetLayersBase(),this);
					Q.MaskingColor	=p->MaskingColor;
					Q.Mergin		=p->Mergin;
					Q.EnsmallDot	=p->EnsmallDot;
					Q.EnlargeDot	=p->EnlargeDot;
					Q.Initial();
					if(Q.exec()==(int)true){
						int	page=p->GlobalPage;
						GUICmdModDynamicMaskingPIArea	Cmd(GetLayersBase(),sRoot,sName,page);
						Cmd.ID=p->ID;
						Cmd.AdaptedPickupLayers	=p->AdaptedPickupLayers;
						Cmd.MaskingColor		=Q.MaskingColor;
						Cmd.Mergin				=Q.Mergin;
						Cmd.EnlargeDot			=Q.EnlargeDot;
						Cmd.EnsmallDot			=Q.EnsmallDot;
						Cmd.Layer	=-1;

						Cmd.SendOnly(page,0);
					}
				}
			}
		}
	}
	ShowInEdit();
}

void PropertyDynamicMaskingPIForm::on_radioButtonPickupMask_clicked()
{

}

void PropertyDynamicMaskingPIForm::on_radioButtonDrawMask_clicked()
{

}
