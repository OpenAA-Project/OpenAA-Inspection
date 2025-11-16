#include "ListboxAlgorithmCountResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ListboxAlgorithmCount\ListboxAlgorithmCount.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ListboxAlgorithmCount.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "XAlgorithmBase.h"
#include "XDataAlgorithm.h"

const	char	*sRoot=/**/"Inspection";
const	char	*sName=/**/"ListboxAlgorithmCount";



DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Listbox to view Algorithm Item count");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdReqAlgorithmItemCount	(Base,sRoot,sName,-1);
	(*Base)=new GUICmdSendAlgorithmItemCount(Base,sRoot,sName,-1);
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ListboxAlgorithmCount(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	return(0);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ListboxAlgorithmCount.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

//====================================================================================

ListboxAlgorithmCount::ListboxAlgorithmCount(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
	resize(400,250);
}
ListboxAlgorithmCount::~ListboxAlgorithmCount(void)
{
}
void	ListboxAlgorithmCount::Prepare(void)
{
	MainList.setParent(this);
	MainList.move(0,0);
	MainList.resize(width(),height());
	MainList.setColumnCount(4);
	MainList.setHorizontalHeaderItem ( 0, new QTableWidgetItem(LangSolver.GetString(ListboxAlgorithmCount_LS,LID_0)/*"Algorithm"*/) );
	MainList.setHorizontalHeaderItem ( 1, new QTableWidgetItem(LangSolver.GetString(ListboxAlgorithmCount_LS,LID_1)/*"Page"*/) );
	MainList.setHorizontalHeaderItem ( 2, new QTableWidgetItem(LangSolver.GetString(ListboxAlgorithmCount_LS,LID_2)/*"Layer"*/) );
	MainList.setHorizontalHeaderItem ( 3, new QTableWidgetItem(LangSolver.GetString(ListboxAlgorithmCount_LS,LID_3)/*"Count"*/) );
	MainList.setColumnWidth ( 0, 140);
	MainList.setColumnWidth ( 1, 40);
	MainList.setColumnWidth ( 2, 40);
	MainList.setColumnWidth ( 3, 60);

}
void	ListboxAlgorithmCount::BuildForShow(void)
{
	ShowInEdit();
}
void	ListboxAlgorithmCount::ShowInEdit(void)
{
	NPListPack<AlgorithmItemCountInBase>	CountInBases;
	for(int page=0;page<GetPageNumb();page++){
		GUICmdReqAlgorithmItemCount		CmdReq(GetLayersBase(),sRoot,sName,page);
		GUICmdSendAlgorithmItemCount	CmdAck(GetLayersBase(),sRoot,sName,page);
		if(CmdReq.Send(page,0,CmdAck)==false)
			return;
		AlgorithmItemCountInBase	*p;
		while((p=CmdAck.CountInBases.GetFirst())!=NULL){
			CmdAck.CountInBases.RemoveList(p);
			for(AlgorithmItemCountInBase *d=CountInBases.GetFirst();d!=NULL;d=d->GetNext()){
				if(d->AlgoRoot==p->AlgoRoot && d->AlgoName==p->AlgoName){
					AlgorithmItemCountInPage	*Ps;
					while((Ps=p->CountInPage.GetFirst())!=NULL){
						p->CountInPage.RemoveList(Ps);
						d->CountInPage.AppendList(Ps);
					}
					break;
				}
			}
			if(p->CountInPage.GetNumber()!=0){
				CountInBases.AppendList(p);
			}
			else
				delete	p;
		}
	}
	MainList.setRowCount(CountInBases.GetNumber()*GetPageNumb()*GetLayerNumb(0));
	int	NLine=0;
	for(AlgorithmItemCountInBase *B=CountInBases.GetFirst();B!=NULL;B=B->GetNext()){
		int	PageNumb=0;
		for(AlgorithmItemCountInPage *P=B->CountInPage.GetFirst();P!=NULL;P=P->GetNext(),PageNumb++){
			int	LayerNumb=0;
			for(IntClass *L=P->CountInLayer.GetFirst();L!=NULL;L=L->GetNext(),LayerNumb++){
				QTableWidgetItem	*W;
				W=MainList.item (NLine, 0);
				if(W==NULL){
					W=new QTableWidgetItem(B->AlgoName);
					MainList.setItem(NLine,	0,W);
				}
				else
					W->setText(B->AlgoName);
				W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

				W=MainList.item (NLine, 1);
				if(W==NULL){
					W=new QTableWidgetItem(QString::number(PageNumb));
					MainList.setItem(NLine,	1,W);
				}
				else
					W->setText(QString::number(PageNumb));
				W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

				W=MainList.item (NLine, 2);
				if(W==NULL){
					W=new QTableWidgetItem(QString::number(LayerNumb));
					MainList.setItem(NLine,	2,W);
				}
				else
					W->setText(QString::number(LayerNumb));
				W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

				W=MainList.item (NLine, 3);
				if(W==NULL){
					W=new QTableWidgetItem(QString::number(L->GetValue()));
					MainList.setItem(NLine,	3,W);
				}
				else
					W->setText(QString::number(L->GetValue()));
				W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
				NLine++;
			}
		}
	}
}

void	ListboxAlgorithmCount::ResizeAction()
{
	MainList.resize(width(),height());
}

//====================================================================================


GUICmdReqAlgorithmItemCount::GUICmdReqAlgorithmItemCount(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqAlgorithmItemCount::Load(QIODevice *f)
{
	return true;
}
bool	GUICmdReqAlgorithmItemCount::Save(QIODevice *f)
{
	return true;
}

void	GUICmdReqAlgorithmItemCount::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendAlgorithmItemCount	*SendBack=GetSendBack(GUICmdSendAlgorithmItemCount,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	SendBack->MakeLists(localPage,GetLayersBase());
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendAlgorithmItemCount::GUICmdSendAlgorithmItemCount(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdSendAlgorithmItemCount::MakeLists(int localPage ,LayersBase *Base)
{
	CountInBases.RemoveAll();
	for(LogicDLL *L=Base->GetLogicDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
		AlgorithmBase	*Ab=L->GetInstance();
		AlgorithmItemCountInBase	*CBase=new AlgorithmItemCountInBase();
		CountInBases.AppendList(CBase);
		CBase->AlgoRoot=L->GetDLLRoot();
		CBase->AlgoName=L->GetDLLName();

		AlgorithmInPageRoot *Ap=Ab->GetPageData(localPage);
		AlgorithmItemCountInPage	*CPage=new AlgorithmItemCountInPage();
		Ap->GenerateAlgorithmItemCount(*CPage);
		CBase->CountInPage.AppendList(CPage);
	}
}
bool	GUICmdSendAlgorithmItemCount::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false)
		return false;
	CountInBases.RemoveAll();
	for(int i=0;i<N;i++){
		AlgorithmItemCountInBase *p=new AlgorithmItemCountInBase();
		if(p->Load(f)==false)
			return false;
		CountInBases.AppendList(p);
	}
	return true;
}
bool	GUICmdSendAlgorithmItemCount::Save(QIODevice *f)
{
	int32	N=CountInBases.GetNumber();
	if(::Save(f,N)==false)
		return false;
	for(AlgorithmItemCountInBase *p=CountInBases.GetFirst();p!=NULL;p=p->GetNext()){
		if(p->Save(f)==false)
			return false;
	}
	return true;
}

void	GUICmdSendAlgorithmItemCount::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{

}

