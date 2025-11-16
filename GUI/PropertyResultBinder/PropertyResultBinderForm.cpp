#include "PropertyResultBinderFormResource.h"
#include "PropertyResultBinderForm.h"
#include "ui_PropertyResultBinderForm.h"
#include "RuleAlgorithmItemDialog.h"
#include "RuleAllItemsInLayerAlgorithmDialog.h"
#include "RuleAllItemsInPageAlgorithmDialog.h"
#include "RuleConditionalDialog.h"
#include "RuleOperationDialog.h"
#include "XRuleOfBinder.h"
#include "InputPageAndItemNameDialog.h"
#include "XDisplayImage.h"
#include <QMessageBox>

extern	const	char	*sRoot;
extern	const	char	*sName;

PropertyResultBinderForm::PropertyResultBinderForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::PropertyResultBinderForm)
{
    ui->setupUi(this);
	ResultBinderItemPage=-1;
	ResultBinderItemID	=-1;
}

PropertyResultBinderForm::~PropertyResultBinderForm()
{
    delete ui;
}

	
void	PropertyResultBinderForm::TransmitDirectly(GUIDirectMessage *packet)
{

	CmdCreateDrawAttrPacket	*CmdCreateDrawAttrPacketVar=dynamic_cast<CmdCreateDrawAttrPacket *>(packet);
	if(CmdCreateDrawAttrPacketVar!=NULL){
		AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ResultBinder");
		if(Ab!=NULL){
			ResultBinderBase	*M=(ResultBinderBase *)Ab;
			CmdCreateDrawAttrPacketVar->Attr=new ResultBinderDrawAttr(
									   M->ColorResultBinder	,M->TransparentLevel
									  ,M->ColorSelected		,M->TransparentLevel
									  ,M->ColorActive		,M->TransparentLevel
									  ,M->NegColorResultBinder
									  ,M->NegColorSelected);
			CmdCreateDrawAttrPacketVar->Attr->CurrentPage	=ResultBinderItemPage;
			CmdCreateDrawAttrPacketVar->Attr->CurrentItemID	=ResultBinderItemID;
		}
		return;
	}

	CmdCreateResultBinderManualPacket	*CmdCreateResultBinderManualPacketVar=dynamic_cast<CmdCreateResultBinderManualPacket *>(packet);
	if(CmdCreateResultBinderManualPacketVar!=NULL){
		if(ResultBinderItemID<0){
			QMessageBox::warning(NULL,LangSolver.GetString(PropertyResultBinderForm_LS,LID_0)/*"Alarm"*/,LangSolver.GetString(PropertyResultBinderForm_LS,LID_1)/*"Create item first"*/);
			return;
		}
		if(ui->toolButtonAlignmentItem->isChecked()==true){
			RuleAlgorithmItemDialog	D(GetLayersBase(),true);
			if(D.exec()==(int)true){
				GUICmdAddAreaManual	Cmd(GetLayersBase(),sRoot,sName,D.SelectedPage);
				Cmd.Area	=CmdCreateResultBinderManualPacketVar->Area;
				Cmd.RuleType	=ID_ChildOfRuleAlgorithmItem;

				Cmd.AlgoRoot	=D.SelectedDLLRoot;
				Cmd.AlgoName	=D.SelectedDLLName;
				Cmd.Phase		=GetLayersBase()->GetCurrentPhase();
				Cmd.Page		=D.SelectedPage;
				Cmd.Layer		=D.SelectedLayer;
				Cmd.ItemID		=D.SelectedItemID;
				Cmd.ItemName	=D.SelectedItemName;
				Cmd.RuleName	=D.RuleName;
				Cmd.RuleRemark	=D.RuleRemark;
				Cmd.ResultBinderItemID	=ResultBinderItemID;
				Cmd.Conclusion	=D.Conclusion;
				Cmd.Send(NULL,D.SelectedPage,0);
			}
		}
		else if(ui->toolButtonAllItemsInLayer->isChecked()==true){
			RuleAllItemsInLayerAlgorithmDialog	D(0,GetLayersBase(),true);
			if(D.exec()==true){
				GUICmdAddAreaManual	Cmd(GetLayersBase(),sRoot,sName,D.SelectedPage);
				Cmd.Area	=CmdCreateResultBinderManualPacketVar->Area;
				Cmd.RuleType	=ID_ChildOfRuleAllItemsInLayerAlgorithm;

				Cmd.AlgoRoot	=D.SelectedDLLRoot;
				Cmd.AlgoName	=D.SelectedDLLName;
				Cmd.Phase		=GetLayersBase()->GetCurrentPhase();
				Cmd.Page		=D.SelectedPage;
				Cmd.Layer		=D.SelectedLayer;

				Cmd.RuleName	=D.RuleName;
				Cmd.RuleRemark	=D.RuleRemark;
				Cmd.ResultBinderItemID	=ResultBinderItemID;
				Cmd.Conclusion	=D.Conclusion;
				Cmd.Send(NULL,D.SelectedPage,0);
			}
		}
		else if(ui->toolButtonAllItemsInPage->isChecked()==true){
			RuleAllItemsInPageAlgorithmDialog	D(GetLayersBase(),true);
			if(D.exec()==true){
				GUICmdAddAreaManual	Cmd(GetLayersBase(),sRoot,sName,D.SelectedPage);
				Cmd.Area	=CmdCreateResultBinderManualPacketVar->Area;
				Cmd.RuleType	=ID_ChildOfRuleAllItemsInPageAlgorithm;

				Cmd.AlgoRoot	=D.SelectedDLLRoot;
				Cmd.AlgoName	=D.SelectedDLLName;
				Cmd.Phase		=GetLayersBase()->GetCurrentPhase();
				Cmd.Page		=D.SelectedPage;

				Cmd.RuleName	=D.RuleName;
				Cmd.RuleRemark	=D.RuleRemark;
				Cmd.ResultBinderItemID	=ResultBinderItemID;
				Cmd.Conclusion	=D.Conclusion;
				Cmd.Send(NULL,D.SelectedPage,0);
			}
		}
		else if(ui->toolButtonOperationOR->isChecked()==true){
			RuleOperationDialog	D(GetLayersBase());
			if(ResultBinderItemPage>=0 && D.exec()==true){
				GUICmdAddAreaManual	Cmd(GetLayersBase(),sRoot,sName,ResultBinderItemPage);
				Cmd.Area	=CmdCreateResultBinderManualPacketVar->Area;
				Cmd.RuleType	=ID_ChildOfRuleOperationOR;

				Cmd.Phase		=GetLayersBase()->GetCurrentPhase();
				Cmd.Page		=ResultBinderItemPage;

				Cmd.RuleName	=D.RuleName;
				Cmd.RuleRemark	=D.RuleRemark;
				Cmd.ResultBinderItemID	=ResultBinderItemID;
				Cmd.Conclusion	=D.Conclusion;
				Cmd.Send(NULL,ResultBinderItemPage,0);
			}
		}
		else if(ui->toolButtonOperationAND->isChecked()==true){
			RuleOperationDialog	D(GetLayersBase());
			if(ResultBinderItemPage>=0 && D.exec()==true){
				GUICmdAddAreaManual	Cmd(GetLayersBase(),sRoot,sName,ResultBinderItemPage);
				Cmd.Area	=CmdCreateResultBinderManualPacketVar->Area;
				Cmd.RuleType	=ID_ChildOfRuleOperationAND;

				Cmd.Phase		=GetLayersBase()->GetCurrentPhase();
				Cmd.Page		=ResultBinderItemPage;

				Cmd.RuleName	=D.RuleName;
				Cmd.RuleRemark	=D.RuleRemark;
				Cmd.ResultBinderItemID	=ResultBinderItemID;
				Cmd.Conclusion	=D.Conclusion;
				Cmd.Send(NULL,ResultBinderItemPage,0);
			}		}
		else if(ui->toolButtonOperationXOR->isChecked()==true){
			RuleOperationDialog	D(GetLayersBase());
			if(ResultBinderItemPage>=0 && D.exec()==true){
				GUICmdAddAreaManual	Cmd(GetLayersBase(),sRoot,sName,ResultBinderItemPage);
				Cmd.Area	=CmdCreateResultBinderManualPacketVar->Area;
				Cmd.RuleType	=ID_ChildOfRuleOperationXOR;

				Cmd.Phase		=GetLayersBase()->GetCurrentPhase();
				Cmd.Page		=ResultBinderItemPage;

				Cmd.RuleName	=D.RuleName;
				Cmd.RuleRemark	=D.RuleRemark;
				Cmd.ResultBinderItemID	=ResultBinderItemID;
				Cmd.Conclusion	=D.Conclusion;
				Cmd.Send(NULL,ResultBinderItemPage,0);
			}		}
		else if(ui->toolButtonOperationNEG->isChecked()==true){
			RuleOperationDialog	D(GetLayersBase());
			if(ResultBinderItemPage>=0 && D.exec()==true){
				GUICmdAddAreaManual	Cmd(GetLayersBase(),sRoot,sName,ResultBinderItemPage);
				Cmd.Area	=CmdCreateResultBinderManualPacketVar->Area;
				Cmd.RuleType	=ID_ChildOfRuleOperationNEG;

				Cmd.Phase		=GetLayersBase()->GetCurrentPhase();
				Cmd.Page		=ResultBinderItemPage;

				Cmd.RuleName	=D.RuleName;
				Cmd.RuleRemark	=D.RuleRemark;
				Cmd.ResultBinderItemID	=ResultBinderItemID;
				Cmd.Conclusion	=D.Conclusion;
				Cmd.Send(NULL,ResultBinderItemPage,0);
			}		}
		else if(ui->toolButtonOperationConditional->isChecked()==true){
			RuleConditionalDialog	D(GetLayersBase(),0);
			if(ResultBinderItemPage>=0 && D.exec()==true){
				GUICmdAddAreaManual	Cmd(GetLayersBase(),sRoot,sName,ResultBinderItemPage);
				Cmd.Area	=CmdCreateResultBinderManualPacketVar->Area;
				Cmd.RuleType	=ID_ChildOfRuleOperationCond;

				Cmd.Phase			=GetLayersBase()->GetCurrentPhase();
				Cmd.Page			=ResultBinderItemPage;
				Cmd.ConditionData	=D.ConditionData;
				Cmd.RuleName		=D.RuleName;
				Cmd.RuleRemark		=D.RuleRemark;
				Cmd.ResultBinderItemID	=ResultBinderItemID;
				Cmd.Conclusion		=D.Conclusion;
				Cmd.Send(NULL,ResultBinderItemPage,0);
			}
		}
		else if(ui->toolButtonLinkArrow->isChecked()==true){
			if(CmdCreateResultBinderManualPacketVar->Vect!=NULL){
				int		RuleID1=-1;
				int		RuleID2=-1;
				GUICmdReqRuleOnXY	RCmd(GetLayersBase(),sRoot,sName,ResultBinderItemPage);
				GUICmdAckRuleOnXY	ACmd(GetLayersBase(),sRoot,sName,ResultBinderItemPage);
				VectorItemBase	*v1=CmdCreateResultBinderManualPacketVar->Vect->GetFirstItem();
				if(v1!=NULL){
					RCmd.PosX	=v1->GetXInt();
					RCmd.PosY	=v1->GetYInt();
					RCmd.ZoomRate=CmdCreateResultBinderManualPacketVar->ZoomRate;
					RCmd.ResultBinderItemID	=ResultBinderItemID;
					if(RCmd.Send(ResultBinderItemPage,0,ACmd)==true){
						RuleID1=ACmd.RuleID;
					}
					VectorItemBase	*v2=v1->GetNext();
					if(v2!=NULL){
						RCmd.PosX	=v2->GetXInt();
						RCmd.PosY	=v2->GetYInt();
						RCmd.ResultBinderItemID	=ResultBinderItemID;
						if(RCmd.Send(ResultBinderItemPage,0,ACmd)==true){
							RuleID2=ACmd.RuleID;
						}
						if(RuleID1>=0 && RuleID2>=0){
							GUICmdReqAddConnection	RAddCmd(GetLayersBase(),sRoot,sName,ResultBinderItemPage);
							RAddCmd.ParentRuleID		=RuleID2;
							RAddCmd.ChildRuleID			=RuleID1;
							RAddCmd.ResultBinderItemID	=ResultBinderItemID;
							RAddCmd.Send(NULL,ResultBinderItemPage,0);
						}
					}
				}
			}
		}
		return;
	}
	CmdDoubleClickedPacket	*CmdDoubleClickedPacketVar=dynamic_cast<CmdDoubleClickedPacket *>(packet);
	if(CmdDoubleClickedPacketVar!=NULL){
		if(ResultBinderItemPage>=0){
			GUICmdReqRuleOnXY	RCmd(GetLayersBase(),sRoot,sName,ResultBinderItemPage);
			GUICmdAckRuleOnXY	ACmd(GetLayersBase(),sRoot,sName,ResultBinderItemPage);
			RCmd.ZoomRate=CmdDoubleClickedPacketVar->ZoomRate;
			RCmd.PosX	=CmdDoubleClickedPacketVar->GlobalX;
			RCmd.PosY	=CmdDoubleClickedPacketVar->GlobalY;
			RCmd.ResultBinderItemID	=ResultBinderItemID;
			if(RCmd.Send(ResultBinderItemPage,0,ACmd)==true){
				if(ACmd.RuleType==ID_ChildOfRuleAlgorithmItem){
					ChildOfRuleAlgorithmItem	RuleItem(NULL);
					RuleItem.AlgoRoot	=ACmd.AlgoRoot;
					RuleItem.AlgoName	=ACmd.AlgoName;
					RuleItem.Phase		=ACmd.Phase;
					RuleItem.Page		=ACmd.Page;
					RuleItem.Layer		=ACmd.Layer;
					RuleItem.ItemID		=ACmd.ItemID;
					RuleItem.ItemName	=ACmd.ItemName;
					RuleItem.RuleID		=ACmd.RuleID;
					RuleItem.Name		=ACmd.RuleName;
					RuleItem.Remark		=ACmd.RuleRemark;
					RuleItem.Conclusion	=ACmd.Conclusion;
					RuleAlgorithmItemDialog	D(GetLayersBase(),false);
					D.Initial(&RuleItem);
					int	Ret=D.exec();
					if(Ret==(int)true){
						GUICmdChangeAreaManual	Cmd(GetLayersBase(),sRoot,sName,D.SelectedPage);
						Cmd.RuleType	=ID_ChildOfRuleAlgorithmItem;

						Cmd.AlgoRoot	=D.SelectedDLLRoot;
						Cmd.AlgoName	=D.SelectedDLLName;
						Cmd.Phase		=GetLayersBase()->GetCurrentPhase();
						Cmd.Page		=D.SelectedPage;
						Cmd.Layer		=D.SelectedLayer;
						Cmd.ItemID		=D.SelectedItemID;
						Cmd.ItemName	=D.SelectedItemName;
						Cmd.RuleName	=D.RuleName;
						Cmd.RuleRemark	=D.RuleRemark;
						Cmd.ResultBinderItemID	=ResultBinderItemID;
						Cmd.Conclusion	=D.Conclusion;
						Cmd.RuleID		=ACmd.RuleID;
						Cmd.DeleteMode	=false;
						Cmd.Send(NULL,D.SelectedPage,0);
					}
					else if(Ret==2){
						GUICmdChangeAreaManual	Cmd(GetLayersBase(),sRoot,sName,D.SelectedPage);
						Cmd.RuleType	=ID_ChildOfRuleAlgorithmItem;

						Cmd.AlgoRoot	=D.SelectedDLLRoot;
						Cmd.AlgoName	=D.SelectedDLLName;
						Cmd.Phase		=GetLayersBase()->GetCurrentPhase();
						Cmd.Page		=D.SelectedPage;
						Cmd.Layer		=D.SelectedLayer;
						Cmd.ItemID		=D.SelectedItemID;
						Cmd.ItemName	=D.SelectedItemName;
						Cmd.RuleName	=D.RuleName;
						Cmd.RuleRemark	=D.RuleRemark;
						Cmd.ResultBinderItemID	=ResultBinderItemID;
						Cmd.Conclusion	=D.Conclusion;
						Cmd.RuleID		=ACmd.RuleID;
						Cmd.DeleteMode	=true;
						Cmd.Send(NULL,D.SelectedPage,0);
					}
				}
				else if(ACmd.RuleType==ID_ChildOfRuleAllItemsInLayerAlgorithm){
					ChildOfRuleAllItemsInLayerAlgorithm	RuleItem(NULL);
					RuleItem.AlgoRoot	=ACmd.AlgoRoot;
					RuleItem.AlgoName	=ACmd.AlgoName;
					RuleItem.Phase		=ACmd.Phase;
					RuleItem.Page		=ACmd.Page;
					RuleItem.Layer		=ACmd.Layer;
					RuleItem.RuleID		=ACmd.RuleID;
					RuleItem.Name		=ACmd.RuleName;
					RuleItem.Remark		=ACmd.RuleRemark;
					RuleItem.Conclusion	=ACmd.Conclusion;
					RuleAllItemsInLayerAlgorithmDialog	D(ACmd.Page,GetLayersBase(),false);
					D.Initial(&RuleItem);
					int	Ret=D.exec();
					if(Ret==(int)true){
						GUICmdChangeAreaManual	Cmd(GetLayersBase(),sRoot,sName,D.SelectedPage);
						Cmd.RuleType	=ID_ChildOfRuleAllItemsInLayerAlgorithm;

						Cmd.AlgoRoot	=D.SelectedDLLRoot;
						Cmd.AlgoName	=D.SelectedDLLName;
						Cmd.Phase		=GetLayersBase()->GetCurrentPhase();
						Cmd.Page		=D.SelectedPage;
						Cmd.Layer		=D.SelectedLayer;

						Cmd.RuleName	=D.RuleName;
						Cmd.RuleRemark	=D.RuleRemark;
						Cmd.ResultBinderItemID	=ResultBinderItemID;
						Cmd.Conclusion	=D.Conclusion;
						Cmd.RuleID		=ACmd.RuleID;
						Cmd.DeleteMode	=false;
						Cmd.Send(NULL,D.SelectedPage,0);
					}
					else if(Ret==2){
						GUICmdChangeAreaManual	Cmd(GetLayersBase(),sRoot,sName,D.SelectedPage);
						Cmd.RuleType	=ID_ChildOfRuleAllItemsInLayerAlgorithm;

						Cmd.AlgoRoot	=D.SelectedDLLRoot;
						Cmd.AlgoName	=D.SelectedDLLName;
						Cmd.Phase		=GetLayersBase()->GetCurrentPhase();
						Cmd.Page		=D.SelectedPage;
						Cmd.Layer		=D.SelectedLayer;

						Cmd.RuleName	=D.RuleName;
						Cmd.RuleRemark	=D.RuleRemark;
						Cmd.ResultBinderItemID	=ResultBinderItemID;
						Cmd.Conclusion	=D.Conclusion;
						Cmd.RuleID		=ACmd.RuleID;
						Cmd.DeleteMode	=true;
						Cmd.Send(NULL,D.SelectedPage,0);
					}
				}
				else if(ACmd.RuleType==ID_ChildOfRuleAllItemsInPageAlgorithm){
					ChildOfRuleAllItemsInPageAlgorithm	RuleItem(NULL);
					RuleItem.AlgoRoot	=ACmd.AlgoRoot;
					RuleItem.AlgoName	=ACmd.AlgoName;
					RuleItem.Phase		=ACmd.Phase;
					RuleItem.Page		=ACmd.Page;
					RuleItem.RuleID		=ACmd.RuleID;
					RuleItem.Name		=ACmd.RuleName;
					RuleItem.Remark		=ACmd.RuleRemark;
					RuleItem.Conclusion	=ACmd.Conclusion;
					RuleAllItemsInPageAlgorithmDialog	D(GetLayersBase(),false);
					D.Initial(&RuleItem);
					int	Ret=D.exec();
					if(Ret==(int)true){
						GUICmdChangeAreaManual	Cmd(GetLayersBase(),sRoot,sName,D.SelectedPage);
						Cmd.RuleType	=ID_ChildOfRuleAllItemsInPageAlgorithm;

						Cmd.AlgoRoot	=D.SelectedDLLRoot;
						Cmd.AlgoName	=D.SelectedDLLName;
						Cmd.Phase		=GetLayersBase()->GetCurrentPhase();
						Cmd.Page		=D.SelectedPage;

						Cmd.RuleName	=D.RuleName;
						Cmd.RuleRemark	=D.RuleRemark;
						Cmd.ResultBinderItemID	=ResultBinderItemID;
						Cmd.Conclusion	=D.Conclusion;
						Cmd.RuleID		=ACmd.RuleID;
						Cmd.DeleteMode	=false;
						Cmd.Send(NULL,D.SelectedPage,0);
					}
					else if(Ret==2){
						GUICmdChangeAreaManual	Cmd(GetLayersBase(),sRoot,sName,D.SelectedPage);
						Cmd.RuleType	=ID_ChildOfRuleAllItemsInPageAlgorithm;

						Cmd.AlgoRoot	=D.SelectedDLLRoot;
						Cmd.AlgoName	=D.SelectedDLLName;
						Cmd.Phase		=GetLayersBase()->GetCurrentPhase();
						Cmd.Page		=D.SelectedPage;

						Cmd.RuleName	=D.RuleName;
						Cmd.RuleRemark	=D.RuleRemark;
						Cmd.ResultBinderItemID	=ResultBinderItemID;
						Cmd.Conclusion	=D.Conclusion;
						Cmd.RuleID		=ACmd.RuleID;
						Cmd.DeleteMode	=true;
						Cmd.Send(NULL,D.SelectedPage,0);
					}
				}
				else if(ACmd.RuleType==ID_ChildOfRuleOperationOR){
					ChildOfRuleOperationOR	RuleItem(NULL);
					RuleItem.RuleID		=ACmd.RuleID;
					RuleItem.Name		=ACmd.RuleName;
					RuleItem.Remark		=ACmd.RuleRemark;
					RuleItem.Conclusion	=ACmd.Conclusion;
					RuleOperationDialog	D(GetLayersBase());
					D.Initial(&RuleItem);
					if(D.exec()==(int)true){
						GUICmdChangeAreaManual	Cmd(GetLayersBase(),sRoot,sName,ResultBinderItemPage);
						Cmd.RuleType	=ID_ChildOfRuleOperationOR;
							
						Cmd.Phase		=GetLayersBase()->GetCurrentPhase();
						Cmd.Page		=ResultBinderItemPage;

						Cmd.RuleName	=D.RuleName;
						Cmd.RuleRemark	=D.RuleRemark;
						Cmd.ResultBinderItemID	=ResultBinderItemID;
						Cmd.Conclusion	=D.Conclusion;
						Cmd.RuleID		=ACmd.RuleID;
						Cmd.Send(NULL,ResultBinderItemPage,0);
					}
				}
				else if(ACmd.RuleType==ID_ChildOfRuleOperationAND){
					ChildOfRuleOperationAND	RuleItem(NULL);
					RuleItem.RuleID		=ACmd.RuleID;
					RuleItem.Name		=ACmd.RuleName;
					RuleItem.Remark		=ACmd.RuleRemark;
					RuleItem.Conclusion	=ACmd.Conclusion;
					RuleOperationDialog	D(GetLayersBase());
					D.Initial(&RuleItem);
					if(D.exec()==(int)true){
						GUICmdChangeAreaManual	Cmd(GetLayersBase(),sRoot,sName,ResultBinderItemPage);
						Cmd.RuleType	=ID_ChildOfRuleOperationAND;

						Cmd.Phase		=GetLayersBase()->GetCurrentPhase();
						Cmd.Page		=ResultBinderItemPage;

						Cmd.RuleName	=D.RuleName;
						Cmd.RuleRemark	=D.RuleRemark;
						Cmd.ResultBinderItemID	=ResultBinderItemID;
						Cmd.Conclusion	=D.Conclusion;
						Cmd.RuleID		=ACmd.RuleID;
						Cmd.Send(NULL,ResultBinderItemPage,0);
					}
				}
				else if(ACmd.RuleType==ID_ChildOfRuleOperationXOR){
					ChildOfRuleOperationXOR	RuleItem(NULL);
					RuleItem.RuleID		=ACmd.RuleID;
					RuleItem.Name		=ACmd.RuleName;
					RuleItem.Remark		=ACmd.RuleRemark;
					RuleItem.Conclusion	=ACmd.Conclusion;
					RuleOperationDialog	D(GetLayersBase());
					D.Initial(&RuleItem);
					if(D.exec()==(int)true){
						GUICmdChangeAreaManual	Cmd(GetLayersBase(),sRoot,sName,ResultBinderItemPage);
						Cmd.RuleType	=ID_ChildOfRuleOperationXOR;

						Cmd.Phase		=GetLayersBase()->GetCurrentPhase();
						Cmd.Page		=ResultBinderItemPage;

						Cmd.RuleName	=D.RuleName;
						Cmd.RuleRemark	=D.RuleRemark;
						Cmd.ResultBinderItemID	=ResultBinderItemID;
						Cmd.Conclusion	=D.Conclusion;
						Cmd.RuleID		=ACmd.RuleID;
						Cmd.Send(NULL,ResultBinderItemPage,0);
					}
				}
				else if(ACmd.RuleType==ID_ChildOfRuleOperationNEG){
					ChildOfRuleOperationNEG	RuleItem(NULL);
					RuleItem.RuleID		=ACmd.RuleID;
					RuleItem.Name		=ACmd.RuleName;
					RuleItem.Remark		=ACmd.RuleRemark;
					RuleItem.Conclusion	=ACmd.Conclusion;
					RuleOperationDialog	D(GetLayersBase());
					D.Initial(&RuleItem);
					if(D.exec()==(int)true){
						GUICmdChangeAreaManual	Cmd(GetLayersBase(),sRoot,sName,ResultBinderItemPage);
						Cmd.RuleType	=ID_ChildOfRuleOperationNEG;

						Cmd.Phase		=GetLayersBase()->GetCurrentPhase();
						Cmd.Page		=ResultBinderItemPage;

						Cmd.RuleName	=D.RuleName;
						Cmd.RuleRemark	=D.RuleRemark;
						Cmd.ResultBinderItemID	=ResultBinderItemID;
						Cmd.Conclusion	=D.Conclusion;
						Cmd.RuleID		=ACmd.RuleID;
						Cmd.Send(NULL,ResultBinderItemPage,0);
					}
				}
				else if(ACmd.RuleType==ID_ChildOfRuleOperationCond){
					ChildOfRuleOperationConditional	RuleItem(NULL);
					RuleItem.RuleID		=ACmd.RuleID;
					RuleItem.Name		=ACmd.RuleName;
					RuleItem.ConditionData	=ACmd.ConditionData;
					RuleItem.Remark		=ACmd.RuleRemark;
					RuleItem.NGOthers	=ACmd.NGOthers;
					RuleItem.Conclusion	=ACmd.Conclusion;
					RuleConditionalDialog	D(GetLayersBase(),ACmd.InputNumb);
					D.Initial(&RuleItem,ACmd.InputNumb);
					if(D.exec()==(int)true){
						GUICmdChangeAreaManual	Cmd(GetLayersBase(),sRoot,sName,ResultBinderItemPage);
						Cmd.RuleType	=ID_ChildOfRuleOperationCond;

						Cmd.Phase		=GetLayersBase()->GetCurrentPhase();
						Cmd.Page		=ResultBinderItemPage;
						Cmd.ConditionData	=D.ConditionData;
						Cmd.RuleName	=D.RuleName;
						Cmd.RuleRemark	=D.RuleRemark;
						Cmd.ResultBinderItemID	=ResultBinderItemID;
						Cmd.Conclusion	=D.Conclusion;
						Cmd.NGOthers	=D.NGOthers;
						Cmd.RuleID		=ACmd.RuleID;
						Cmd.Send(NULL,ResultBinderItemPage,0);
					}
				}
				else{
					GUICmdReqClosedConnectionOnXY	RConnectCmd(GetLayersBase(),sRoot,sName,ResultBinderItemPage);
					GUICmdAckClosedConnectionOnXY	AConnectCmd(GetLayersBase(),sRoot,sName,ResultBinderItemPage);
					RConnectCmd.ZoomRate=CmdDoubleClickedPacketVar->ZoomRate;
					RConnectCmd.PosX	=CmdDoubleClickedPacketVar->GlobalX;
					RConnectCmd.PosY	=CmdDoubleClickedPacketVar->GlobalY;
					RConnectCmd.ResultBinderItemID	=ResultBinderItemID;
					if(RConnectCmd.Send(ResultBinderItemPage,0,AConnectCmd)==true){
						if(AConnectCmd.ParentRuleID>=0 && AConnectCmd.ChildRuleID>=0){
							if(QMessageBox::question(NULL,LangSolver.GetString(PropertyResultBinderForm_LS,LID_2)/*"Delete"*/,LangSolver.GetString(PropertyResultBinderForm_LS,LID_3)/*"Delete this arrow?"*/,QMessageBox::Yes | QMessageBox::No)==QMessageBox::Yes){
								GUICmdDelConnection	DelConnectCmd(GetLayersBase(),sRoot,sName,ResultBinderItemPage);
								DelConnectCmd.ParentRuleID		=AConnectCmd.ParentRuleID;
								DelConnectCmd.ChildRuleID		=AConnectCmd.ChildRuleID;
								DelConnectCmd.ResultBinderItemID=ResultBinderItemID;
								DelConnectCmd.Send(NULL,ResultBinderItemPage,0);
							}
						}
					}
				}
			}
		}
		return;
	}
}
	
void	PropertyResultBinderForm::BuildForShow(void)
{
	ShowItems();
}

void PropertyResultBinderForm::on_tableWidgetItemList_itemSelectionChanged()
{
	int	R=ui->tableWidgetItemList->currentRow();
	int	Row=0;
	for(int page=0;page<GetPageNumb();page++){
		for(ItemIDNameList *a=ResultBinderItemList[page].GetFirst();a!=NULL;a=a->GetNext()){
			if(R==Row){
				ResultBinderItemPage	=page;
				ResultBinderItemID		=a->ItemID;
				return;
			}
			Row++;
		}
	}
}

void PropertyResultBinderForm::ShowItems(void)
{
	int	RowCount=0;
	for(int page=0;page<GetPageNumb();page++){
		GUICmdReqResultBinderItemEnum	DReq (GetLayersBase(),sRoot,sName,page);
		GUICmdAckResultBinderItemEnum	DAck(GetLayersBase(),sRoot,sName,page);

		if(DReq.Send(page,0,DAck)==true){
			ResultBinderItemList[page]=DAck.Items;
			RowCount+=DAck.Items.GetCount();
		}
	}

	ui->tableWidgetItemList->setRowCount(RowCount);
	int	Row=0;
	for(int page=0;page<GetPageNumb();page++){
		for(ItemIDNameList *a=ResultBinderItemList[page].GetFirst();a!=NULL;a=a->GetNext()){
			::SetDataToTable(ui->tableWidgetItemList ,0,Row ,QString::number(page));
			::SetDataToTable(ui->tableWidgetItemList ,1,Row ,a->ItemName);
			::SetDataToTable(ui->tableWidgetItemList ,2,Row ,QString::number(a->ItemID));
			if(ResultBinderItemPage==page && ResultBinderItemID==a->ItemID){
				ui->tableWidgetItemList->setCurrentCell(Row,0);
			}
			Row++;
		}
	}
}

void PropertyResultBinderForm::on_pushButtonAddItem_clicked()
{
	InputPageAndItemNameDialog	D(GetLayersBase());
	if(D.exec()==(int)true){
		GUICmdReqResultBinderItemAdd	DReq (GetLayersBase(),sRoot,sName,D.Page);
		GUICmdAckResultBinderItemAdd	DAck(GetLayersBase(),sRoot,sName,D.Page);
		DReq.GlobalPage	=D.Page;
		DReq.ItemName	=D.ItemName;
		if(DReq.Send(D.Page,0,DAck)==false){
			return;
		}
		ResultBinderItemPage=D.Page;
		ResultBinderItemID	=DAck.ItemID;

		ShowItems();
	}
}

void PropertyResultBinderForm::on_pushButtonModifyItem_clicked()
{
	int	R=ui->tableWidgetItemList->currentRow();
	int	Row=0;
	for(int page=0;page<GetPageNumb();page++){
		for(ItemIDNameList *a=ResultBinderItemList[page].GetFirst();a!=NULL;a=a->GetNext()){
			if(R==Row){
				ResultBinderItemPage	=page;
				ResultBinderItemID		=a->ItemID;
				ShowImagePanel();
			}
			Row++;
		}
	}

}

void PropertyResultBinderForm::on_pushButtonDeleteItem_clicked()
{
	int	R=ui->tableWidgetItemList->currentRow();
	int	Row=0;
	for(int page=0;page<GetPageNumb();page++){
		for(ItemIDNameList *a=ResultBinderItemList[page].GetFirst();a!=NULL;a=a->GetNext()){
			if(R==Row){
				GUICmdReqResultBinderItemDel	DReq (GetLayersBase(),sRoot,sName,page);
				DReq.ItemID	=a->ItemID;
				DReq.Send(NULL,page,0);
				ResultBinderItemPage	=-1;
				ResultBinderItemID		=-1;
				ShowImagePanel();
			}
			Row++;
		}
	}
	ShowItems();
}

void	PropertyResultBinderForm::ShowImagePanel(void)
{
}


void PropertyResultBinderForm::on_toolButtonAlignmentItem_clicked()
{
	DisplayImage	*GProp=(DisplayImage *)GetLayersBase()->FindByName(/**/"Inspection" ,/**/"ResultBinderImagePanel" ,/**/"");
	if(GProp!=NULL){
		GProp->SetModeByOthers(mtFrameDraw::fdRectangle,Qt::red);
	}
}

void PropertyResultBinderForm::on_toolButtonAllItemsInLayer_clicked()
{
	DisplayImage	*GProp=(DisplayImage *)GetLayersBase()->FindByName(/**/"Inspection" ,/**/"ResultBinderImagePanel" ,/**/"");
	if(GProp!=NULL){
		GProp->SetModeByOthers(mtFrameDraw::fdRectangle,Qt::red);
	}
}

void PropertyResultBinderForm::on_toolButtonAllItemsInPage_clicked()
{
	DisplayImage	*GProp=(DisplayImage *)GetLayersBase()->FindByName(/**/"Inspection" ,/**/"ResultBinderImagePanel" ,/**/"");
	if(GProp!=NULL){
		GProp->SetModeByOthers(mtFrameDraw::fdRectangle,Qt::red);
	}
}

void PropertyResultBinderForm::on_toolButtonOperationOR_clicked()
{
	DisplayImage	*GProp=(DisplayImage *)GetLayersBase()->FindByName(/**/"Inspection" ,/**/"ResultBinderImagePanel" ,/**/"");
	if(GProp!=NULL){
		GProp->SetModeByOthers(mtFrameDraw::fdRectangle,Qt::red);
	}

}

void PropertyResultBinderForm::on_toolButtonOperationAND_clicked()
{
	DisplayImage	*GProp=(DisplayImage *)GetLayersBase()->FindByName(/**/"Inspection" ,/**/"ResultBinderImagePanel" ,/**/"");
	if(GProp!=NULL){
		GProp->SetModeByOthers(mtFrameDraw::fdRectangle,Qt::red);
	}
}

void PropertyResultBinderForm::on_toolButtonOperationXOR_clicked()
{
	DisplayImage	*GProp=(DisplayImage *)GetLayersBase()->FindByName(/**/"Inspection" ,/**/"ResultBinderImagePanel" ,/**/"");
	if(GProp!=NULL){
		GProp->SetModeByOthers(mtFrameDraw::fdRectangle,Qt::red);
	}
}

void PropertyResultBinderForm::on_toolButtonOperationNEG_clicked()
{
	DisplayImage	*GProp=(DisplayImage *)GetLayersBase()->FindByName(/**/"Inspection" ,/**/"ResultBinderImagePanel" ,/**/"");
	if(GProp!=NULL){
		GProp->SetModeByOthers(mtFrameDraw::fdRectangle,Qt::red);
	}
}

void PropertyResultBinderForm::on_toolButtonOperationConditional_clicked()
{
	DisplayImage	*GProp=(DisplayImage *)GetLayersBase()->FindByName(/**/"Inspection" ,/**/"ResultBinderImagePanel" ,/**/"");
	if(GProp!=NULL){
		GProp->SetModeByOthers(mtFrameDraw::fdRectangle,Qt::red);
	}
}

void PropertyResultBinderForm::on_toolButtonNothing_clicked()
{
	DisplayImage	*GProp=(DisplayImage *)GetLayersBase()->FindByName(/**/"Inspection" ,/**/"ResultBinderImagePanel" ,/**/"");
	if(GProp!=NULL){
		GProp->SetModeByOthers(mtFrameDraw::fdNone,Qt::red);
	}
}

void PropertyResultBinderForm::on_toolButtonLinkArrow_clicked()
{
	DisplayImage	*GProp=(DisplayImage *)GetLayersBase()->FindByName(/**/"Inspection" ,/**/"ResultBinderImagePanel" ,/**/"");
	if(GProp!=NULL){
		GProp->SetModeByOthers(mtFrameDraw::fdSingleArrow,Qt::red);
	}
}

void PropertyResultBinderForm::on_tableWidgetItemList_doubleClicked(const QModelIndex &index)
{
	int	R=ui->tableWidgetItemList->currentRow();
	int	Row=0;
	int	GlobalPage=-1;
	int	SelectedItemID;
	for(int page=0;page<GetPageNumb();page++){
		for(ItemIDNameList *a=ResultBinderItemList[page].GetFirst();a!=NULL;a=a->GetNext()){
			if(R==Row){
				GlobalPage=page;
				SelectedItemID	=a->ItemID;
				goto	PNext;
			}
			Row++;
		}
	}
	PNext:;
	if(GlobalPage==-1)
		return;
	GUICmdReqResultBinderItemInfo	DReq (GetLayersBase(),sRoot,sName,GlobalPage);
	GUICmdSendResultBinderItemInfo	DAck(GetLayersBase(),sRoot,sName,GlobalPage);
	DReq.ItemID	=SelectedItemID;
	if(DReq.Send(GlobalPage,0,DAck)==false){
		return;
	}

	InputPageAndItemNameDialog	D(GetLayersBase());
	D.Initial(DAck.ItemName);
	if(D.exec()==(int)true){
		GUICmdReqResultBinderItemMod	ModReq (GetLayersBase(),sRoot,sName,D.Page);
		ModReq.ItemID	=SelectedItemID;
		ModReq.ItemName	=D.ItemName;
		if(ModReq.Send(NULL,GlobalPage,0)==false){
			return;
		}

		ShowItems();
	}
}
