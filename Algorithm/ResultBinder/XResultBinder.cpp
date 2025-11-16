#include "XResultBinderResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XResultBinder.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XResultBinder.h"
#include "XResult.h"
#include "XResultDLLManager.h"
#include "swap.h"
#include "XAlgorithmDLL.h"
#include <ctype.h>


//=====================================================================================

ResultBinderThreshold::ResultBinderThreshold(ResultBinderItem *parent):AlgorithmThreshold(parent)
{
}

FlexArea	&ResultBinderItem::GetArea(void)
{
	if(AlgorithmItemRoot::GetArea().IsNull()==true){
		FlexArea	Area;
		Area.SetRectangle(0,0,GetDotPerLine(),GetMaxLines());
		SetArea(Area);
	}
	return AlgorithmItemRoot::GetArea();
}

bool    ResultBinderItem::Save(QIODevice *f)
{
	if(AlgorithmItemPI::Save(f)==false)
		return false;

	if(Rule.Save(f)==false)
		return false;
	return true;
}
bool    ResultBinderItem::Load(QIODevice *f,LayersBase *LBase)
{
	GetParentBase()->SetLoadedVersion(1);

	if(AlgorithmItemPI::Load(f,LBase)==false)
		return false;
	if(Rule.Load(f)==false)
		return false;
	return true;
}

void	ResultBinderItem::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	ResultBinderDrawAttr	*LAttr=dynamic_cast<ResultBinderDrawAttr *>(Attr);
	if(LAttr!=NULL){
		if(LAttr->CurrentPage==GetPage() && LAttr->CurrentItemID==GetID()){
			AlgorithmItemPI::Draw(pnt, movx ,movy ,ZoomRate ,Attr);
			Rule.DrawRule(pnt ,ZoomRate,movx ,movy);
		}
	}
}
void	ResultBinderItem::DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)
{
	QColor	c=Qt::red;
	c.setAlpha(100);

	RuleOfBinderBase *r=Rule.GetConclusionRule();
	if(r!=NULL){
		r->DrawRule(IData
					,ZoomRate ,MovX ,MovY);
	}
}

ExeResult	ResultBinderItem::ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo
														,ResultInItemRoot *Res
														,ExecuteInitialAfterEditInfo &EInfo)
{
	Rule.ExecuteInitialAfterEdit(GetLayersBase(),EInfo);

	return _ER_true;
}
ExeResult	ResultBinderItem::ExecuteProcessing	(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
{
	RuleOfBinderBase *r=Rule.GetConclusionRule();
	if(r!=NULL){
		r->GetResult(Res);
	}
	return _ER_true;
}

void	ResultBinderItem::BindResult(ResultInItemRoot *Item,ResultPosList *RPos)
{
	ResultBinderBase	*ABase=(ResultBinderBase *)GetParentBase();

}

//bool	ResultBinderItem::IsInclude(int x ,int y)
//{
//	return Rule.IsInclude(x,y,1);
//}

void	ResultBinderItem::ReplaceOKInSource(void)
{
	Rule.ReplaceOKInSource();
}

//====================================================================

static	int	SortFuncDim(const void *a ,const void *b)
{
	AlgorithmItemPI	**ai=(AlgorithmItemPI **)a;
	AlgorithmItemPI	**bi=(AlgorithmItemPI **)b;
	int	x1=ai[0]->GetArea().GetMinX();
	int	x2=bi[0]->GetArea().GetMinX();
	return x1-x2;
}

void	ResultBinderInPage::TransmitDirectly(GUIDirectMessage *packet)
{
	AddRulePacket	*AddRulePacketVar=dynamic_cast<AddRulePacket *>(packet);
	if(AddRulePacketVar!=NULL){
		ResultBinderItem	*item=(ResultBinderItem *)SearchIDItem(AddRulePacketVar->ResultBinderItemID);
		int	cx=AddRulePacketVar->Area.GetMinX();
		int	cy=AddRulePacketVar->Area.GetMinY();
		if(item!=NULL){
			if(AddRulePacketVar->RuleType==ID_ChildOfRuleAlgorithmItem){
				ChildOfRuleAlgorithmItem	*a=new ChildOfRuleAlgorithmItem(&item->Rule);
				a->Location.setX(cx);
				a->Location.setY(cy);
				a->AlgoRoot	=AddRulePacketVar->AlgoRoot;
				a->AlgoName	=AddRulePacketVar->AlgoName;
				a->Phase	=AddRulePacketVar->Phase;
				a->Page		=AddRulePacketVar->Page;
				a->Layer	=AddRulePacketVar->Layer;
				a->ItemID	=AddRulePacketVar->ItemID;
				a->ItemName	=AddRulePacketVar->ItemName;
				a->Name		=AddRulePacketVar->RuleName;
				a->Remark	=AddRulePacketVar->RuleRemark;
				a->Conclusion=AddRulePacketVar->Conclusion;
				a->RuleID		=item->Rule.GetLastID()+1;
				a->ParentItem	=item;
				item->Rule.AppendList(a);
				item->SetEdited(true);
			}			
			else if(AddRulePacketVar->RuleType==ID_ChildOfRuleAllItemsInLayerAlgorithm){
				ChildOfRuleAllItemsInLayerAlgorithm	*a=new ChildOfRuleAllItemsInLayerAlgorithm(&item->Rule);
				a->Location.setX(cx);
				a->Location.setY(cy);
				a->AlgoRoot	=AddRulePacketVar->AlgoRoot;
				a->AlgoName	=AddRulePacketVar->AlgoName;
				a->Phase	=AddRulePacketVar->Phase;
				a->Page		=AddRulePacketVar->Page;
				a->Layer	=AddRulePacketVar->Layer;
				a->Name		=AddRulePacketVar->RuleName;
				a->Remark	=AddRulePacketVar->RuleRemark;
				a->Conclusion=AddRulePacketVar->Conclusion;
				a->RuleID		=item->Rule.GetLastID()+1;
				a->ParentItem	=item;
				item->Rule.AppendList(a);
				item->SetEdited(true);
			}			
			else if(AddRulePacketVar->RuleType==ID_ChildOfRuleAllItemsInPageAlgorithm){
				ChildOfRuleAllItemsInPageAlgorithm	*a=new ChildOfRuleAllItemsInPageAlgorithm(&item->Rule);
				a->Location.setX(cx);
				a->Location.setY(cy);
				a->AlgoRoot	=AddRulePacketVar->AlgoRoot;
				a->AlgoName	=AddRulePacketVar->AlgoName;
				a->Phase	=AddRulePacketVar->Phase;
				a->Page		=AddRulePacketVar->Page;
				a->Name		=AddRulePacketVar->RuleName;
				a->Remark	=AddRulePacketVar->RuleRemark;
				a->Conclusion=AddRulePacketVar->Conclusion;
				a->RuleID		=item->Rule.GetLastID()+1;
				a->ParentItem	=item;
				item->Rule.AppendList(a);
				item->SetEdited(true);
			}
			else if(AddRulePacketVar->RuleType==ID_ChildOfRuleOperationOR){
				ChildOfRuleOperationOR	*a=new ChildOfRuleOperationOR(&item->Rule);
				a->Location.setX(cx);
				a->Location.setY(cy);
				a->Name		=AddRulePacketVar->RuleName;
				a->Remark	=AddRulePacketVar->RuleRemark;
				a->Conclusion=AddRulePacketVar->Conclusion;
				a->RuleID		=item->Rule.GetLastID()+1;
				a->ParentItem	=item;
				item->Rule.AppendList(a);
				item->SetEdited(true);
			}
			else if(AddRulePacketVar->RuleType==ID_ChildOfRuleOperationAND){
				ChildOfRuleOperationAND	*a=new ChildOfRuleOperationAND(&item->Rule);
				a->Location.setX(cx);
				a->Location.setY(cy);
				a->Name		=AddRulePacketVar->RuleName;
				a->Remark	=AddRulePacketVar->RuleRemark;
				a->Conclusion=AddRulePacketVar->Conclusion;
				a->RuleID		=item->Rule.GetLastID()+1;
				a->ParentItem	=item;
				item->Rule.AppendList(a);
				item->SetEdited(true);
			}
			else if(AddRulePacketVar->RuleType==ID_ChildOfRuleOperationXOR){
				ChildOfRuleOperationXOR	*a=new ChildOfRuleOperationXOR(&item->Rule);
				a->Location.setX(cx);
				a->Location.setY(cy);
				a->Name		=AddRulePacketVar->RuleName;
				a->Remark	=AddRulePacketVar->RuleRemark;
				a->Conclusion=AddRulePacketVar->Conclusion;
				a->RuleID		=item->Rule.GetLastID()+1;
				a->ParentItem	=item;
				item->Rule.AppendList(a);
				item->SetEdited(true);
			}
			else if(AddRulePacketVar->RuleType==ID_ChildOfRuleOperationNEG){
				ChildOfRuleOperationNEG	*a=new ChildOfRuleOperationNEG(&item->Rule);
				a->Location.setX(cx);
				a->Location.setY(cy);
				a->Name		=AddRulePacketVar->RuleName;
				a->Remark	=AddRulePacketVar->RuleRemark;
				a->Conclusion=AddRulePacketVar->Conclusion;
				a->RuleID		=item->Rule.GetLastID()+1;
				a->ParentItem	=item;
				item->Rule.AppendList(a);
				item->SetEdited(true);
			}
			else if(AddRulePacketVar->RuleType==ID_ChildOfRuleOperationCond){
				ChildOfRuleOperationConditional	*a=new ChildOfRuleOperationConditional(&item->Rule);
				a->Location.setX(cx);
				a->Location.setY(cy);
				a->Name		=AddRulePacketVar->RuleName;
				a->Remark	=AddRulePacketVar->RuleRemark;
				a->Conclusion=AddRulePacketVar->Conclusion;
				a->ConditionData	=AddRulePacketVar->ConditionData;
				a->RuleID		=item->Rule.GetLastID()+1;
				a->ParentItem	=item;
				a->NGOthers	=AddRulePacketVar->NGOthers;
				item->Rule.AppendList(a);
				item->SetEdited(true);
			}
		}
		return;
	}
	CmdReqResultBinderItemAdd	*CmdReqResultBinderItemAddVar=dynamic_cast<CmdReqResultBinderItemAdd *>(packet);
	if(CmdReqResultBinderItemAddVar!=NULL){

		ResultBinderItem	*item=(ResultBinderItem *)CreateItem();
		item->SetItemName(CmdReqResultBinderItemAddVar->ResultBinderItemName);
		AppendItem(item);

		item->SetManualCreated(true);
		CmdReqResultBinderItemAddVar->ResultBinderItemID	=item->GetID();
		return;
	}
	CmdReqResultBinderItemEnum	*CmdReqResultBinderItemEnumVar=dynamic_cast<CmdReqResultBinderItemEnum *>(packet);
	if(CmdReqResultBinderItemEnumVar!=NULL){
		for(AlgorithmItemPI *Item=GetFirstData();Item!=NULL;Item=Item->GetNext()){
			ItemIDNameList	*a=new ItemIDNameList();
			a->ItemID	=Item->GetID();
			a->ItemName	=Item->GetItemName();
			CmdReqResultBinderItemEnumVar	->Items->AppendList(a);
		}
		return;
	}
	CmdReqResultBinderItemDel	*CmdReqResultBinderItemDelVar=dynamic_cast<CmdReqResultBinderItemDel *>(packet);
	if(CmdReqResultBinderItemDelVar!=NULL){
		ResultBinderItem	*item=(ResultBinderItem *)SearchIDItem(CmdReqResultBinderItemDelVar->ResultBinderItemID);
		if(item!=NULL){
			RemoveItem(item);
			delete	item;
		}
		SetChanged(true);
		return;
	}
	CmdReqRuleOnXY	*CmdReqRuleOnXYVar=dynamic_cast<CmdReqRuleOnXY *>(packet);
	if(CmdReqRuleOnXYVar!=NULL){
		ResultBinderItem	*item=(ResultBinderItem *)SearchIDItem(CmdReqRuleOnXYVar->ResultBinderItemID);
		if(item!=NULL){
			RuleOfBinderBase	*p=item->Rule.Find(CmdReqRuleOnXYVar->PosX ,CmdReqRuleOnXYVar->PosY,CmdReqRuleOnXYVar->ZoomRate);
			if(p!=NULL){
				CmdReqRuleOnXYVar	->RuleID	=p->RuleID;
				CmdReqRuleOnXYVar	->RuleName	=p->Name;
				CmdReqRuleOnXYVar	->RuleRemark=p->Remark;
				CmdReqRuleOnXYVar	->InputNumb	=p->Children.GetCount();
				CmdReqRuleOnXYVar	->RuleType	=p->GetClassID();
				CmdReqRuleOnXYVar	->Conclusion=p->Conclusion;
				
				ChildOfRuleAlgorithmItem	*ChildOfRuleAlgorithmItemVar=dynamic_cast<ChildOfRuleAlgorithmItem *>(p);
				if(ChildOfRuleAlgorithmItemVar!=NULL){
					CmdReqRuleOnXYVar->AlgoRoot	=ChildOfRuleAlgorithmItemVar->AlgoRoot;
					CmdReqRuleOnXYVar->AlgoName	=ChildOfRuleAlgorithmItemVar->AlgoName;
					CmdReqRuleOnXYVar->Phase	=ChildOfRuleAlgorithmItemVar->Phase;
					CmdReqRuleOnXYVar->Page		=ChildOfRuleAlgorithmItemVar->Page;
					CmdReqRuleOnXYVar->Layer	=ChildOfRuleAlgorithmItemVar->Layer;
					CmdReqRuleOnXYVar->ItemID	=ChildOfRuleAlgorithmItemVar->ItemID;
					CmdReqRuleOnXYVar->ItemName	=ChildOfRuleAlgorithmItemVar->ItemName;
				}
				ChildOfRuleAllItemsInLayerAlgorithm	*ChildOfRuleAllItemsInLayerAlgorithmVar=dynamic_cast<ChildOfRuleAllItemsInLayerAlgorithm *>(p);
				if(ChildOfRuleAllItemsInLayerAlgorithmVar!=NULL){
					CmdReqRuleOnXYVar->AlgoRoot	=ChildOfRuleAllItemsInLayerAlgorithmVar->AlgoRoot;
					CmdReqRuleOnXYVar->AlgoName	=ChildOfRuleAllItemsInLayerAlgorithmVar->AlgoName;
					CmdReqRuleOnXYVar->Phase	=ChildOfRuleAllItemsInLayerAlgorithmVar->Phase;
					CmdReqRuleOnXYVar->Page		=ChildOfRuleAllItemsInLayerAlgorithmVar->Page;
					CmdReqRuleOnXYVar->Layer	=ChildOfRuleAllItemsInLayerAlgorithmVar->Layer;
				}
				ChildOfRuleAllItemsInPageAlgorithm	*ChildOfRuleAllItemsInPageAlgorithmVar=dynamic_cast<ChildOfRuleAllItemsInPageAlgorithm *>(p);
				if(ChildOfRuleAllItemsInPageAlgorithmVar!=NULL){
					CmdReqRuleOnXYVar->AlgoRoot	=ChildOfRuleAllItemsInPageAlgorithmVar->AlgoRoot;
					CmdReqRuleOnXYVar->AlgoName	=ChildOfRuleAllItemsInPageAlgorithmVar->AlgoName;
					CmdReqRuleOnXYVar->Phase	=ChildOfRuleAllItemsInPageAlgorithmVar->Phase;
					CmdReqRuleOnXYVar->Page		=ChildOfRuleAllItemsInPageAlgorithmVar->Page;
				}
				ChildOfRuleOperationConditional	*ChildOfRuleOperationConditionalVar=dynamic_cast<ChildOfRuleOperationConditional *>(p);
				if(ChildOfRuleOperationConditionalVar!=NULL){
					CmdReqRuleOnXYVar->ConditionData	=ChildOfRuleOperationConditionalVar->ConditionData;
					CmdReqRuleOnXYVar->NGOthers			=ChildOfRuleOperationConditionalVar->NGOthers;
				}
			}
		}
		return;
	}
	CmdChangeRulePacket	*CmdChangeRulePacketVar=dynamic_cast<CmdChangeRulePacket *>(packet);
	if(CmdChangeRulePacketVar!=NULL){
		ResultBinderItem	*item=(ResultBinderItem *)SearchIDItem(CmdChangeRulePacketVar->ResultBinderItemID);
		if(item!=NULL){
			RuleOfBinderBase	*p=item->Rule.Find(CmdChangeRulePacketVar->RuleID);
			if(p!=NULL){
				p->Name			=CmdChangeRulePacketVar->RuleName;
				p->Remark		=CmdChangeRulePacketVar->RuleRemark;
				p->Conclusion	=CmdChangeRulePacketVar->Conclusion;
			}
			if(CmdChangeRulePacketVar->DeleteMode==false){
				if(CmdChangeRulePacketVar->RuleType==ID_ChildOfRuleAlgorithmItem){
					ChildOfRuleAlgorithmItem	*a=dynamic_cast<ChildOfRuleAlgorithmItem *>(p);
					if(a!=NULL){
						a->AlgoRoot	=CmdChangeRulePacketVar->AlgoRoot;
						a->AlgoName	=CmdChangeRulePacketVar->AlgoName;
						a->Phase	=CmdChangeRulePacketVar->Phase;
						a->Page		=CmdChangeRulePacketVar->Page;
						a->Layer	=CmdChangeRulePacketVar->Layer;
						a->ItemID	=CmdChangeRulePacketVar->ItemID;
						a->ItemName	=CmdChangeRulePacketVar->ItemName;
						item->SetEdited(true);
					}
				}			
				else if(CmdChangeRulePacketVar->RuleType==ID_ChildOfRuleAllItemsInLayerAlgorithm){
					ChildOfRuleAllItemsInLayerAlgorithm	*a=dynamic_cast<ChildOfRuleAllItemsInLayerAlgorithm *>(p);
					if(a!=NULL){
						a->AlgoRoot	=CmdChangeRulePacketVar->AlgoRoot;
						a->AlgoName	=CmdChangeRulePacketVar->AlgoName;
						a->Phase	=CmdChangeRulePacketVar->Phase;
						a->Page		=CmdChangeRulePacketVar->Page;
						a->Layer	=CmdChangeRulePacketVar->Layer;
						item->SetEdited(true);
					}
				}			
				else if(CmdChangeRulePacketVar->RuleType==ID_ChildOfRuleAllItemsInPageAlgorithm){
					ChildOfRuleAllItemsInPageAlgorithm	*a=dynamic_cast<ChildOfRuleAllItemsInPageAlgorithm *>(p);
					if(a!=NULL){
						a->AlgoRoot	=CmdChangeRulePacketVar->AlgoRoot;
						a->AlgoName	=CmdChangeRulePacketVar->AlgoName;
						a->Phase	=CmdChangeRulePacketVar->Phase;
						a->Page		=CmdChangeRulePacketVar->Page;
						item->SetEdited(true);
					}
				}
				else if(CmdChangeRulePacketVar->RuleType==ID_ChildOfRuleOperationOR){
					ChildOfRuleOperationOR	*a=dynamic_cast<ChildOfRuleOperationOR *>(p);
					if(a!=NULL){
						item->SetEdited(true);
					}
				}
				else if(CmdChangeRulePacketVar->RuleType==ID_ChildOfRuleOperationAND){
					ChildOfRuleOperationAND	*a=dynamic_cast<ChildOfRuleOperationAND *>(p);
					if(a!=NULL){
						item->SetEdited(true);
					}
				}
				else if(CmdChangeRulePacketVar->RuleType==ID_ChildOfRuleOperationXOR){
					ChildOfRuleOperationXOR	*a=dynamic_cast<ChildOfRuleOperationXOR *>(p);
					if(a!=NULL){
						item->SetEdited(true);
					}
				}
				else if(CmdChangeRulePacketVar->RuleType==ID_ChildOfRuleOperationNEG){
					ChildOfRuleOperationNEG	*a=dynamic_cast<ChildOfRuleOperationNEG *>(p);
					if(a!=NULL){
						item->SetEdited(true);
					}
				}
				else if(CmdChangeRulePacketVar->RuleType==ID_ChildOfRuleOperationCond){
					ChildOfRuleOperationConditional	*a=dynamic_cast<ChildOfRuleOperationConditional *>(p);
					if(a!=NULL){
						a->ConditionData=CmdChangeRulePacketVar->ConditionData;
						a->NGOthers		=CmdChangeRulePacketVar->NGOthers;
						item->SetEdited(true);
					}
				}
			}
			else{
				item->Rule.RemoveList(p);
				delete	p;
			}
		}
		return;
	}
	CmdReqAddConnection	*CmdReqAddConnectionVar=dynamic_cast<CmdReqAddConnection *>(packet);
	if(CmdReqAddConnectionVar!=NULL){
		ResultBinderItem	*item=(ResultBinderItem *)SearchIDItem(CmdReqAddConnectionVar->ResultBinderItemID);
		if(item!=NULL){
			RuleOfBinderBase	*ParentRule	=item->Rule.Find(CmdReqAddConnectionVar->ParentRuleID);
			RuleOfBinderBase	*ChildRule	=item->Rule.Find(CmdReqAddConnectionVar->ChildRuleID);
			if(ParentRule!=NULL && ChildRule!=NULL){
				RuleOfBinderPointer	*p=new RuleOfBinderPointer(ChildRule);
				ParentRule->Children.AppendList(p);
			}
		}
		return;
	}
	CmdAckClosedConnectionOnXY	*CmdAckClosedConnectionOnXYVar=dynamic_cast<CmdAckClosedConnectionOnXY *>(packet);
	if(CmdAckClosedConnectionOnXYVar!=NULL){
		ResultBinderItem	*item=(ResultBinderItem *)SearchIDItem(CmdAckClosedConnectionOnXYVar->ResultBinderItemID);
		if(item!=NULL){
			CmdAckClosedConnectionOnXYVar->ParentRuleID=-1;
			CmdAckClosedConnectionOnXYVar->ChildRuleID=-1;
			item->Rule.GetClosedConnection(  CmdAckClosedConnectionOnXYVar->PosX,CmdAckClosedConnectionOnXYVar->PosY
											,CmdAckClosedConnectionOnXYVar->ZoomRate
											,CmdAckClosedConnectionOnXYVar->ParentRuleID,CmdAckClosedConnectionOnXYVar->ChildRuleID);
		}
		return;
	}
	CmdDelConnection	*CmdDelConnectionVar=dynamic_cast<CmdDelConnection *>(packet);
	if(CmdDelConnectionVar!=NULL){
		ResultBinderItem	*item=(ResultBinderItem *)SearchIDItem(CmdDelConnectionVar->ResultBinderItemID);
		if(item!=NULL){
			item->Rule.RemoveConnection(CmdDelConnectionVar->ParentRuleID,CmdDelConnectionVar->ChildRuleID);
		}
		return;
	}
	CmdReqResultBinderItemInfo	*CmdReqResultBinderItemInfoVar=dynamic_cast<CmdReqResultBinderItemInfo *>(packet);
	if(CmdReqResultBinderItemInfoVar!=NULL){
		ResultBinderItem	*item=(ResultBinderItem *)SearchIDItem(CmdReqResultBinderItemInfoVar->ItemID);
		if(item!=NULL){
			CmdReqResultBinderItemInfoVar->ItemName	=item->GetItemName();
		}
		return;
	}
	CmdReqResultBinderItemMod	*CmdReqResultBinderItemModVar=dynamic_cast<CmdReqResultBinderItemMod *>(packet);
	if(CmdReqResultBinderItemModVar!=NULL){
		ResultBinderItem	*item=(ResultBinderItem *)SearchIDItem(CmdReqResultBinderItemModVar->ItemID);
		if(item!=NULL){
			item->SetItemName(CmdReqResultBinderItemModVar->ItemName);
		}
		return;
	}
}

ExeResult	ResultBinderInPage::ExecuteProcessing		(int ExeID ,ResultInPageRoot *Res)
{
	ExeResult	Ret=AlgorithmInPagePI::ExecuteProcessing	(ExeID ,Res);

	for(AlgorithmItemPI *c=GetFirstData();c!=NULL;c=c->GetNext()){
		ResultBinderItem	*Item=dynamic_cast<ResultBinderItem *>(c);
		if(Item!=NULL){
			Item->ReplaceOKInSource();
		}
	}
	return Ret;
}

//==================================================================

ResultBinderBase::ResultBinderBase(LayersBase *Base)
:AlgorithmBase(Base)
{
	ColorResultBinder		=Qt::green;
	ColorSelected			=Qt::yellow;
	ColorActive				=Qt::red;
	TransparentLevel		=120;
	NegColorResultBinder	=Qt::darkGreen;
	NegColorSelected		=Qt::darkYellow;

	SetParam(&ColorResultBinder		, /**/"Color" ,/**/"ColorResultBinder"		,LangSolver.GetString(XResultBinder_LS,LID_0)/*"Color for ResultBinder area"*/);
	SetParam(&ColorSelected			, /**/"Color" ,/**/"ColorSelected"			,LangSolver.GetString(XResultBinder_LS,LID_1)/*"Color for Selected Piece"*/);
	SetParam(&ColorActive			, /**/"Color" ,/**/"ColorActive"			,LangSolver.GetString(XResultBinder_LS,LID_2)/*"Color for Active Piece"*/);
	SetParam(&TransparentLevel		, /**/"Color" ,/**/"TransparentLevel"		,LangSolver.GetString(XResultBinder_LS,LID_3)/*"Color for Transparent display level"*/);
	SetParam(&NegColorResultBinder	, /**/"Color" ,/**/"NegColorResultBinder"	,LangSolver.GetString(XResultBinder_LS,LID_4)/*"Color for Negative ResultBinder area"*/);
	SetParam(&NegColorSelected	, /**/"Color" ,/**/"NegColorSelected"	,LangSolver.GetString(XResultBinder_LS,LID_5)/*"Color for Negative selected Naming"*/);

}

AlgorithmDrawAttr	*ResultBinderBase::CreateDrawAttr(void)
{
	return new ResultBinderDrawAttr(GetLayersBase());
}

void	ResultBinderBase::TransmitDirectly(GUIDirectMessage *packet)
{
}

/*
bool	ResultBinderBase::GeneralDataRelease(int32 Command,void *data)
{
	if(Command==NamingReqNameReqCommand){
		delete	data;
		return true;
	}
	else if(Command==NamingReqNameSendCommand){
		delete	data;
		return true;
	}
	else{
		return AlgorithmBase::GeneralDataRelease(Command,data);
	}
}
void	*ResultBinderBase::GeneralDataCreate(int32 Command ,void *reqData)
{
	if(Command==NamingReqNameReqCommand){
		return new NamingNameReq();
	}
	else if(Command==NamingReqNameSendCommand){
		NamingNameSend	*pSend=new NamingNameSend();
		if(reqData!=NULL){
			NamingNameReq	*req=(NamingNameReq *)reqData;
			pSend->ConstructList(req,this);
		}
		return pSend;
	}
	else{
		return AlgorithmBase::GeneralDataCreate(Command,reqData);
	}
	return NULL;
}
bool	ResultBinderBase::GeneralDataLoad(QIODevice *f,int32 Command,void *data)
{
	if(Command==NamingReqNameReqCommand){
		NamingNameReq	*p=(NamingNameReq *)data;
		return p->Load(f);
	}
	else if(Command==NamingReqNameSendCommand){
		NamingNameSend	*p=(NamingNameSend *)data;
		return p->Load(f);
	}
	else{
		return AlgorithmBase::GeneralDataLoad(f,Command,data);
	}
	return false;
}
bool	ResultBinderBase::GeneralDataSave(QIODevice *f,int32 Command,void *data)
{
	if(Command==NamingReqNameReqCommand){
		NamingNameReq	*p=(NamingNameReq *)data;
		return p->Save(f);
	}
	else if(Command==NamingReqNameSendCommand){
		NamingNameSend	*p=(NamingNameSend *)data;
		return p->Save(f);
	}
	else{
		return AlgorithmBase::GeneralDataSave(f,Command,data);
	}
	return false;
}
bool	ResultBinderBase::GeneralDataReply(int32 Command,void *data)
{
	if(Command==NamingReqNameReqCommand){
		NamingNameReq	*p=(NamingNameReq *)data;
		return true;
	}
	else if(Command==NamingReqNameSendCommand){
		NamingNameSend	*p=(NamingNameSend *)data;
		return true;
	}
	else{
		return AlgorithmBase::GeneralDataReply(Command,data);
	}
	return false;
}
*/
