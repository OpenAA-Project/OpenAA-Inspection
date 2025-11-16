//#include "CopyMirroredTransferResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\CopyMirroredTransfer\CopyMirroredTransfer.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "CopyMirroredTransfer.h"
#include <QFile>
#include <QFileDialog>
#include "XGeneralFunc.h"
#include "XAlgorithmBase.h"
#include "XDataAlgorithm.h"

const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"CopyMirroredTransfer";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to transfer copied data with mirrored");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdReqBuild	(Base,sRoot,sName);
	(*Base)=new GUICmdAckBuild	(Base,sRoot,sName);
	(*Base)=new GUICmdSetBuild	(Base,sRoot,sName);
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new CopyMirroredTransfer(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<10)
		return(-1);
	Data[0].Type				 =/**/"QString";
	Data[0].VariableNameWithRoute=/**/"Msg";
	Data[0].Pointer				 =&((CopyMirroredTransfer *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((CopyMirroredTransfer *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((CopyMirroredTransfer *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((CopyMirroredTransfer *)Instance)->CFont;
	Data[4].Type				 =/**/"bool";
	Data[4].VariableNameWithRoute=/**/"InitializeAfterEdit";
	Data[4].Pointer				=&((CopyMirroredTransfer *)Instance)->InitializeAfterEdit;
	Data[5].Type				 =/**/"bool";
	Data[5].VariableNameWithRoute=/**/"MirrorX";
	Data[5].Pointer				=&((CopyMirroredTransfer *)Instance)->MirrorX;
	Data[6].Type				 =/**/"bool";
	Data[6].VariableNameWithRoute=/**/"MirrorY";
	Data[6].Pointer				=&((CopyMirroredTransfer *)Instance)->MirrorY;
	Data[7].Type				 =/**/"int32";
	Data[7].VariableNameWithRoute=/**/"CopySourcePhase";
	Data[7].Pointer				=&((CopyMirroredTransfer *)Instance)->CopySourcePhase;
	Data[8].Type				 =/**/"int32";
	Data[8].VariableNameWithRoute=/**/"CopyDestinationPhase";
	Data[8].Pointer				=&((CopyMirroredTransfer *)Instance)->CopyDestinationPhase;
	Data[9].Type				 =/**/"bool";
	Data[9].VariableNameWithRoute=/**/"CopyToSync";
	Data[9].Pointer				=&((CopyMirroredTransfer *)Instance)->CopyToSync;

	return(10);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/CopyMirroredTransfer.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}
//==================================================================================================
CopyMirroredTransfer::CopyMirroredTransfer(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.move(0,0);
	Button.setObjectName(/**/"CopyMirroredTransfer");
	Msg=/**/"Transfer mirror";
	InitializeAfterEdit	=true;
	MirrorX	=false;
	MirrorY	=false;
	CopySourcePhase	=-1;
	CopyDestinationPhase	=-1;
	CopyToSync	=false;
	CoppiedOffsetX	=0;
	CoppiedOffsetY	=0;

	resize(60,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));

	GetParamGUI()->SetParam(&CoppiedOffsetX, /**/"CopyMirroredTransfer",/**/"CoppiedOffsetX"	
												,"Offset-X in destination (copied)");
	GetParamGUI()->SetParam(&CoppiedOffsetY, /**/"CopyMirroredTransfer",/**/"CoppiedOffsetY"	
												,"Offset-Y in destination (copied)");
}

CopyMirroredTransfer::~CopyMirroredTransfer(void)
{
}

void	CopyMirroredTransfer::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	CopyMirroredTransfer::ResizeAction()
{
	Button.resize(width(),height());
}

void CopyMirroredTransfer::SlotClicked (bool checked)
{
	int		x1 ,y1 ,x2 ,y2;
	GetLayersBase()->GetArea(x1 ,y1 ,x2 ,y2);

	int	CenterX=(x1+x2)/2;
	int	CenterY=(y1+y2)/2;

	if(CopyToSync==true){
		for(int phase=0;phase<GetPhaseNumb();phase++){
			for(int page=0;page<GetPageNumb();page++){
				int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
				GUICmdReqBuild		CmdReq(GetLayersBase(),sRoot,sName,GlobalPage);
				CmdReq.phase	=phase;
				CmdReq.MirrorX	=MirrorX;
				CmdReq.MirrorY	=MirrorY;
				GUICmdAckBuild		CmdAck(GetLayersBase(),sRoot,sName,GlobalPage);
				if(CmdReq.Send(GlobalPage ,0,CmdAck)==true){
					QBuffer	Buff;
					Buff.open(QIODevice::ReadWrite);
					int32	Cmd=1;
					::Save(&Buff,Cmd);
					::Save(&Buff,phase);
					::Save(&Buff,GlobalPage);
					::Save(&Buff,MirrorX);
					::Save(&Buff,MirrorY);
					::Save(&Buff,CmdAck.Array);
					TxSync(Buff.buffer());
				}
			}
		}
		QBuffer	GBuff;
		GBuff.open(QIODevice::ReadWrite);
		int32	Cmd=2;
		GUIFormBase *GUIForm[10000];
		int	GUINumb=GetLayersBase()->EnumGUI(GUIForm ,10000);

		::Save(&GBuff,Cmd);
		::Save(&GBuff,GUINumb);

		for(int i=0;i<GUINumb;i++){
			QBuffer	GRBuff;
			GRBuff.open(QIODevice::ReadWrite);
			GUIForm[i]->SaveContent(&GRBuff);

			::Save(&GBuff,GUIForm[i]->GetDLLRoot());
			::Save(&GBuff,GUIForm[i]->GetDLLName());
			::Save(&GBuff,GUIForm[i]->GetName());
			::Save(&GBuff,GRBuff.buffer());
		}
		TxSync(GBuff.buffer());
	}
	else if(CopySourcePhase>=0 && CopyDestinationPhase>=0){
		for(int page=0;page<GetPageNumb();page++){
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdReqBuild		CmdReq(GetLayersBase(),sRoot,sName,GlobalPage);
			CmdReq.phase	=CopySourcePhase;
			CmdReq.MirrorX	=MirrorX;
			CmdReq.MirrorY	=MirrorY;
			GUICmdAckBuild		CmdAck(GetLayersBase(),sRoot,sName,GlobalPage);
			if(CmdReq.Send(GlobalPage ,0,CmdAck)==true){
				GUICmdSetBuild		CmdSet(GetLayersBase(),sRoot,sName,GlobalPage);
				CmdSet.phase	=CopyDestinationPhase;
				CmdSet.MirrorX	=MirrorX;
				CmdSet.MirrorY	=MirrorY;
				CmdSet.Array	=CmdAck.Array;
				CmdSet.CenterX	=CenterX;
				CmdSet.CenterY	=CenterY;
				CmdSet.SendOnly(GlobalPage ,0);
			}
		}
	}
}

void	CopyMirroredTransfer::RxSync(QByteArray &f)
{
	QBuffer	Buff(&f);
	Buff.open(QIODevice::ReadWrite);
	int32	Cmd;
	::Load(&Buff,Cmd);

	if(Cmd==1){
		int		x1 ,y1 ,x2 ,y2;
		GetLayersBase()->GetArea(x1 ,y1 ,x2 ,y2);

		int	CenterX=(x1+x2)/2;
		int	CenterY=(y1+y2)/2;

		int	phase;
		int	GlobalPage;
		bool	bMirrorX;
		bool	bMirrorY;
		QByteArray	Array;

		::Load(&Buff,phase);
		::Load(&Buff,GlobalPage);
		::Load(&Buff,bMirrorX);
		::Load(&Buff,bMirrorY);
		::Load(&Buff,Array);
		
		GUICmdSetBuild		CmdSet(GetLayersBase(),sRoot,sName,GlobalPage);
		CmdSet.phase	=phase;
		CmdSet.MirrorX	=bMirrorX;
		CmdSet.MirrorY	=bMirrorY;
		CmdSet.CenterX	=CenterX+CoppiedOffsetX;
		CmdSet.CenterY	=CenterY+CoppiedOffsetY;
		CmdSet.Array	=Array;
		CmdSet.SendOnly(GlobalPage ,0);
	}
	if(Cmd==2){
		int	GUINumb;
		::Load(&Buff,GUINumb);
		QString	DLLRoot,DLLName,InstName;
		for(int i=0;i<GUINumb;i++){
			::Load(&Buff,DLLRoot);
			::Load(&Buff,DLLName);
			::Load(&Buff,InstName);
			QByteArray	Array;
			::Load(&Buff,Array);

			GUIFormBase	*f=GetLayersBase()->FindByName(DLLRoot,DLLName,InstName);
			if(f!=NULL){
				QBuffer	RBuff(&Array);
				RBuff.open(QIODevice::ReadOnly);

				f->LoadContent(&RBuff);
			}
		}
	}
}
void	CopyMirroredTransfer::GetMenuInfo(MenuInfoContainer &Info)
{
	MenuInfoList	*p=new MenuInfoList(251,"Edit"
										,"Mirrored copy"
										,this);
	p->SetMenuNumber(2221);
	p->SetShowingAttributeAsSwicthInTab();
	Info.AppendList(p);
}
void	CopyMirroredTransfer::ExecuteMenu(int ID)
{
	if(ID==1){
		SlotClicked(true);
	}
}
//======================================================================================

GUICmdReqBuild::GUICmdReqBuild(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdReqBuild::Load(QIODevice *f)
{
	if(::Load(f,phase	)==false)
		return false;
	if(::Load(f,MirrorX)==false)
		return false;
	if(::Load(f,MirrorY)==false)
		return false;
	return true;
}
bool	GUICmdReqBuild::Save(QIODevice *f)
{
	if(::Save(f,phase	)==false)
		return false;
	if(::Save(f,MirrorX)==false)
		return false;
	if(::Save(f,MirrorY)==false)
		return false;
	return true;
}
void	GUICmdReqBuild::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckBuild	*SendBack=GetSendBack(GUICmdAckBuild,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);

	IntList LayerList;
	for(int layer=0;layer<GetLayerNumb(localPage);layer++){
		LayerList.Add(layer);
	}
	int	N=0;
	for(LogicDLL *L=GetLayersBase()->GetLogicDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
		AlgorithmBase	*A=L->GetInstance();
		if(A!=NULL){
			AlgorithmInPageInOnePhase	*Ph=A->GetPageDataPhase(phase);
			if(Ph!=NULL){
				N++;
			}
		}
	}

	::Save(&Buff,N);

	for(LogicDLL *L=GetLayersBase()->GetLogicDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
		AlgorithmBase	*A=L->GetInstance();
		if(A!=NULL){
			AlgorithmInPageInOnePhase	*Ph=A->GetPageDataPhase(phase);
			if(Ph!=NULL){
				AlgorithmInPageRoot		*P=Ph->GetPageData(localPage);
				P->SelectAll(LayerList);

				::Save(&Buff,L->GetDLLRoot());
				::Save(&Buff,L->GetDLLName());
				::Save(&Buff,phase);
				::Save(&Buff,localPage);

				QBuffer	MBuff;
				MBuff.open(QIODevice::WriteOnly);
				P->Save(&MBuff);
				::Save(&Buff,MBuff.buffer());
			}
		}
	}
	SendBack->Array=Buff.buffer();

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}


GUICmdAckBuild::GUICmdAckBuild(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdAckBuild::Load(QIODevice *f)
{
	if(::Load(f,Array)==false)
		return false;
	return true;
}
bool	GUICmdAckBuild::Save(QIODevice *f)
{
	if(::Save(f,Array)==false)
		return false;
	return true;
}


GUICmdSetBuild::GUICmdSetBuild(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSetBuild::Load(QIODevice *f)
{
	if(::Load(f,phase	)==false)
		return false;
	if(::Load(f,MirrorX)==false)
		return false;
	if(::Load(f,MirrorY)==false)
		return false;
	if(::Load(f,CenterX)==false)
		return false;
	if(::Load(f,CenterY)==false)
		return false;
	if(::Load(f,Array)==false)
		return false;
	return true;
}
bool	GUICmdSetBuild::Save(QIODevice *f)
{
	if(::Save(f,phase	)==false)
		return false;
	if(::Save(f,MirrorX)==false)
		return false;
	if(::Save(f,MirrorY)==false)
		return false;
	if(::Save(f,CenterX)==false)
		return false;
	if(::Save(f,CenterY)==false)
		return false;
	if(::Save(f,Array)==false)
		return false;
	return true;
}
void	GUICmdSetBuild::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	QBuffer	Buff(&Array);
	Buff.open(QIODevice::ReadOnly);

	int	N;
	::Load(&Buff,N);
	for(int i=0;i<N;i++){
		QString	DLLRoot,DLLName;
		int	sourcephase;
		int	sourcepage;
		::Load(&Buff,DLLRoot);
		::Load(&Buff,DLLName);
		::Load(&Buff,sourcephase);
		::Load(&Buff,sourcepage);

		QByteArray	MArray;	
		::Load(&Buff,MArray);

		LogicDLL *L=GetLayersBase()->GetLogicDLLBase()->Search(DLLRoot,DLLName);
		if(L!=NULL){
			AlgorithmBase	*A=L->GetInstance();
			AlgorithmInPageInOnePhase	*Ph=A->GetPageDataPhase(phase);
			if(Ph!=NULL){
				AlgorithmInPageRoot		*P=Ph->GetPageData(sourcepage);
				P->ReleaseAllSelectedItem();

				QBuffer	MBuff(&MArray);
				MBuff.open(QIODevice::ReadOnly);
		
				P->Load(&MBuff);
				if(MirrorX==true)
					P->MirrorItem(AlgorithmItemRoot::_XMirror,CenterX,CenterY);
				if(MirrorY==true)
					P->MirrorItem(AlgorithmItemRoot::_YMirror,CenterX,CenterY);
				P->ReleaseAllSelectedItem();
			}
		}
	}
	SendAck(localPage);
}

