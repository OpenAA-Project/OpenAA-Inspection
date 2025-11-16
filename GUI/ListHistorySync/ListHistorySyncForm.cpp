#include "ListHistorySyncResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ListHistorySync\ListHistorySyncForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

//#include "ListHistoryFormResource.h"
#include "ListHistorySyncForm.h"
#include "XDLLOnly.h"
#include "XDataInLayer.h"
#include "XResultDLLManager.h"
#include "XGeneralFunc.h"
#include "XDatabaseLoader.h"
#include "XSyncGUI.h"

#define		ListHistorySyncMode_Reset	1
#define		ListHistorySyncMode_ReqList	2
#define		ListHistorySyncMode_AckList	3


ResultsList::ResultsList(LayersBase *base)
:ServiceForLayers(base),List(base)
{
	MachineCode=-1;
}
void	ResultsList::Set(void)
{
	MachineCode=GetLayersBase()->GetMachineID();
	List=*GetLayersBase()->GetResultHistryData();
}
bool	ResultsList::Save(QIODevice *f)
{
	if(::Save(f,MachineCode)==false){
		return false;
	}
	if(List.Save(f)==false){
		return false;
	}
	return true;
}
bool	ResultsList::Load(QIODevice *f)
{
	if(::Load(f,MachineCode)==false){
		return false;
	}
	if(List.Load(f)==false){
		return false;
	}
	return true;
}
ResultsList	&ResultsList::operator=(ResultsList &src)
{
	MachineCode	=src.MachineCode;
	List		=src.List;
	return *this;
}


ListHistorySyncForm::ListHistorySyncForm(LayersBase *Base ,QWidget *parent)
	: GUIFormBase(Base,parent)
{
	ui.setupUi(this);
	//LangSolver.SetUI(this);
	
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
	ui.tableWidgetHistory->setSelectionMode(QAbstractItemView::SingleSelection);
	ui.tableWidgetHistory->setSelectionBehavior(QAbstractItemView::SelectRows);
}

ListHistorySyncForm::~ListHistorySyncForm()
{

}


void ListHistorySyncForm::on_ButtonReset_clicked()
{
	GetLayersBase()->GetResultHistryData()->Reset();
	if(GetLayersBase()->GetSyncGUIData()->GetConnectedCount()!=0){
		QBuffer	Buff;
		Buff.open(QIODevice::ReadWrite);
		int32	Mode=ListHistorySyncMode_Reset;
		::Save(&Buff,Mode);
		TxSync(Buff.buffer());
	}

	ShowInPlayer(-1);
}

void	ListHistorySyncForm::Prepare(void)
{
	ResizeAction();
}

void	ListHistorySyncForm::ResizeAction()
{
	ui.frame->move(0,height()-ui.frame->height());
	ui.frame->resize(width()-1,ui.frame->height());
	ui.tableWidgetHistory->move(0,0);
	ui.tableWidgetHistory->resize(width()-1,height()-ui.frame->height());
}

void	ListHistorySyncForm::RxSync(QByteArray &f)
{
	QBuffer	Buff(&f);
	Buff.open(QIODevice::ReadWrite);

	int32 Mode;
	::Load(&Buff,Mode);

	if(Mode==ListHistorySyncMode_Reset){
		GetLayersBase()->GetResultHistryData()->Reset();
	}
	if(Mode==ListHistorySyncMode_ReqList){
		ResultsList		R(GetLayersBase());
		R.Set();

		QBuffer	Buff;
		Buff.open(QIODevice::ReadWrite);
		int32	aMode=ListHistorySyncMode_AckList;
		::Save(&Buff,aMode);
		R.Save(&Buff);
		TxSync(Buff.buffer());
	}
	if(Mode==ListHistorySyncMode_AckList){
		ResultsList	*q=new ResultsList(GetLayersBase());
		if(q->Load(&Buff)==true){
			for(ResultsList *d=RList.GetFirst();d!=NULL;d=d->GetNext()){
				if(d->MachineCode==q->MachineCode){
					d->List	=q->List;
					delete	q;
					q=NULL;
					break;
				}
			}
			if(q!=NULL){
				RList.AppendList(q);
			}
		}
	}
}

int	SortTableFunc(const void *a ,const void *b)
{
	ResultsList	*fa=((ResultsList **)a)[0];
	ResultsList	*fb=((ResultsList **)b)[0];
	if(fa->MachineCode<fb->MachineCode){
		return -1;
	}
	if(fa->MachineCode>fb->MachineCode){
		return 1;
	}
	return 0;
}

class	HListLine : public NPList<HListLine>
{
public:
	int64	InspectionID;

	struct	StateInEachMachine
	{
		enum	StateResult{
				_OK				=1
				,_NG			=2
				,_TimeOver		=3
				,_MaxError		=4
				,_Nothing		=10
		}State;
		int32		MasterCode;
		int32		LotAutoCount;

		StateInEachMachine(void){	State=_Nothing;	}
		static	StateResult	GetState(ResultHistry &src);
		static	QString		GetStateString(HListLine::StateInEachMachine::StateResult state);
	};
		

	StateInEachMachine				EachMachine[100];
	StateInEachMachine::StateResult	Conclusion;

	void	MakeConclusion(int MacCount);
};

HListLine::StateInEachMachine::StateResult	HListLine::StateInEachMachine::GetState(ResultHistry &src)
{
	if(src.TimeOutBreak==true)
		return HListLine::StateInEachMachine::_TimeOver;
	if(src.MaxErrorBreak==true)
		return HListLine::StateInEachMachine::_MaxError;
	if(src.Result==1)
		return HListLine::StateInEachMachine::_OK;
	if(src.Result==0)
		return HListLine::StateInEachMachine::_Nothing;
	return HListLine::StateInEachMachine::_NG;
}

QString		HListLine::StateInEachMachine::GetStateString(HListLine::StateInEachMachine::StateResult state)
{
	switch(state){
		case HListLine::StateInEachMachine::_TimeOver:
			return /**/"TmOvr";
		case HListLine::StateInEachMachine::_MaxError:
			return /**/"MaxE";
		case HListLine::StateInEachMachine::_OK:
			return /**/"OK";
		case HListLine::StateInEachMachine::_NG:
			return /**/"NG";
		case HListLine::StateInEachMachine::_Nothing:
			return /**/"None";
	}
	return /**/"";
}

void	HListLine::MakeConclusion(int MacCount)
{
	for(int i=0;i<MacCount;i++){
		if(EachMachine[i].State==StateInEachMachine::_TimeOver){
			Conclusion=StateInEachMachine::_TimeOver;
			return;
		}
		if(EachMachine[i].State==StateInEachMachine::_MaxError){
			Conclusion=StateInEachMachine::_MaxError;
			return;
		}
	}
	bool	Flag=false;
	for(int i=0;i<MacCount;i++){
		if(EachMachine[i].State!=StateInEachMachine::_OK){
			Flag=true;
			break;
		}
	}
	if(Flag==false){
		Conclusion=StateInEachMachine::_OK;
		return;
	}
	Flag=false;
	for(int i=0;i<MacCount;i++){
		if(EachMachine[i].State!=StateInEachMachine::_NG && EachMachine[i].State!=StateInEachMachine::_OK){
			Flag=true;
			break;
		}
	}
	if(Flag==false){
		Conclusion=StateInEachMachine::_NG;
		return;
	}
	Conclusion=StateInEachMachine::_Nothing;
}

void	ListHistorySyncForm::BuildForShow(void)
{
	ShowInPlayer(-1);
}

void	ListHistorySyncForm::ShowInPlayer(int64 shownInspectionID)
{
	if(GetLayersBase()->GetSyncGUIData()->GetConnectedCount()!=0){
		QBuffer	Buff;
		Buff.open(QIODevice::ReadWrite);
		int32	Mode=ListHistorySyncMode_ReqList;
		::Save(&Buff,Mode);
		TxSync(Buff.buffer());
	}
	ResultsList	ThisList(GetLayersBase());
	ThisList.MachineCode	=GetLayersBase()->GetMachineID();
	ThisList.Set();

	ResultsList	*SortTable[100];
	int	MacCount=0;
	SortTable[0]=&ThisList;
	MacCount++;
	for(ResultsList *d=RList.GetFirst();d!=NULL;d=d->GetNext()){
		SortTable[MacCount]=d;
		MacCount++;
		if(MacCount>=100){
			break;
		}
	}
	QSort(SortTable,MacCount,sizeof(SortTable[0]),SortTableFunc);

	NPListPack<HListLine>	HList;
	for(ResultHistry *a=SortTable[0]->List.GetLast();a!=NULL;a=a->GetPrev()){
		HListLine	*c=new HListLine();
		c->InspectionID	=a->InspectionID;
		c->EachMachine[0].MasterCode	=a->MasterCode;
		c->EachMachine[0].LotAutoCount	=a->LotAutoCount;
		c->EachMachine[0].State			=HListLine::StateInEachMachine::GetState(*a);
		HList.AppendList(c);
	}

	for(int Mac=1;Mac<MacCount;Mac++){
		ResultHistry *b=SortTable[Mac]->List.GetLast();
		HListLine	*L=HList.GetFirst();
		for(;b!=NULL;b=b->GetPrev()){
			if(L==NULL || L->InspectionID<b->InspectionID){
				HListLine	*c=new HListLine();
				c->InspectionID	=b->InspectionID;
				c->EachMachine[Mac].MasterCode	=b->MasterCode;
				c->EachMachine[Mac].LotAutoCount=b->LotAutoCount;
				c->EachMachine[Mac].State		=HListLine::StateInEachMachine::GetState(*b);
				HList.InsertForward(L,c);
			}
			else{
				break;
			}
		}
		while(L!=NULL){
			if(L->InspectionID>b->InspectionID){
				L=L->GetNext();
			}
			else{
				break;
			}
		}
		while(L!=NULL && b!=NULL){
			if(L->InspectionID==b->InspectionID){
				L->EachMachine[Mac].MasterCode	=b->MasterCode;
				L->EachMachine[Mac].LotAutoCount=b->LotAutoCount;
				L->EachMachine[Mac].State		=HListLine::StateInEachMachine::GetState(*b);
				L=L->GetNext();
				b=b->GetPrev();
			}
			else if(L->InspectionID<b->InspectionID){
				HListLine	*c=new HListLine();
				c->InspectionID	=b->InspectionID;
				c->EachMachine[Mac].MasterCode	=b->MasterCode;
				c->EachMachine[Mac].LotAutoCount=b->LotAutoCount;
				c->EachMachine[Mac].State		=HListLine::StateInEachMachine::GetState(*b);
				HList.InsertForward(L,c);
				b=b->GetPrev();
			}
			else{
				L=L->GetNext();
			}
		}
		if(L==NULL){
			for(;b!=NULL;b=b->GetPrev()){
				HListLine	*c=new HListLine();
				c->InspectionID	=b->InspectionID;
				c->EachMachine[Mac].MasterCode	=b->MasterCode;
				c->EachMachine[Mac].LotAutoCount=b->LotAutoCount;
				c->EachMachine[Mac].State		=HListLine::StateInEachMachine::GetState(*b);
				HList.AppendList(c);
			}
		}
	}

	for(HListLine *k=HList.GetFirst();k!=NULL;k=k->GetNext()){
		k->MakeConclusion(MacCount);
	}

	ui.tableWidgetHistory->setColumnCount(2+MacCount);
	ui.tableWidgetHistory->setColumnWidth (0,40);
	ui.tableWidgetHistory->horizontalHeaderItem(0)->setText(LangSolver.GetString(ListHistorySyncForm_LS,LID_0)/*"ID"*/);
	for(int m=0;m<MacCount;m++){
		ui.tableWidgetHistory->setColumnWidth (1+m,50);
		int	MachineCode=SortTable[m]->MachineCode;
		QString NetID;
		QString MacName;
		QString Version;
		QString Remark;
		if(GetLayersBase()->GetDatabaseLoader()->G_GetMachineInfo(*GetLayersBase()->GetDataBase(),MachineCode
								,NetID
								,MacName
								,Version
								,Remark)==true){
			ui.tableWidgetHistory->horizontalHeaderItem(1+m)->setText(MacName);
		}
	}
	ui.tableWidgetHistory->setColumnWidth (1+MacCount,50);
	ui.tableWidgetHistory->horizontalHeaderItem(1+MacCount)->setText(LangSolver.GetString(ListHistorySyncForm_LS,LID_1)/*"Total"*/);

	int	row=0;
	ui.tableWidgetHistory->setRowCount(HList.GetNumber());
	for(HListLine *a=HList.GetFirst();a!=NULL;a=a->GetNext(),row++){
		SetDataToTable(ui.tableWidgetHistory ,0 ,row ,a->InspectionID);
		for(int m=0;m<MacCount;m++){
			SetDataToTable(ui.tableWidgetHistory ,1+m ,row ,HListLine::StateInEachMachine::GetStateString(a->EachMachine[m].State));
		}
		SetDataToTable(ui.tableWidgetHistory ,1+MacCount ,row ,HListLine::StateInEachMachine::GetStateString(a->Conclusion));
	}

	int		CountOK=0;
	int		CountNG=0;

	for(HListLine *a=HList.GetFirst();a!=NULL;a=a->GetNext(),row++){
		if(a->Conclusion==HListLine::StateInEachMachine::_OK){
			CountOK++;
		}
		else{
			CountNG++;
		}
	}

	ui.labelOK ->setText(QString::number(CountOK));
	ui.labelNG ->setText(QString::number(CountNG));
	ui.labelSUM->setText(QString::number(CountOK+CountNG));
}
