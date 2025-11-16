#include "CopyBetweenPhaseDialogResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\CopyItemsBetweenPhase\CopyItemsBetweenPhase.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
//#include "ButtonLoadAlgorithmResource.h"
#include "CopyItemsBetweenPhase.h"
#include "CopyBetweenPhaseDialog.h"
#include <QFile>
#include <QFileDialog>
#include "XGeneralFunc.h"
#include "XAlgorithmBase.h"
#include "XDataInLayer.h"

static	const	char	*sRoot=/**/"Button";
static	const	char	*sName=/**/"CopyItemsBetweenPhase";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Copy Items between Phase");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}
DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdCopyData(Base,sRoot,sName);
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	

	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new CopyItemsBetweenPhase(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<6)
		return(-1);
	Data[0].Type				 =/**/"QString";
	Data[0].VariableNameWithRoute=/**/"Msg";
	Data[0].Pointer				 =&((CopyItemsBetweenPhase *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((CopyItemsBetweenPhase *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((CopyItemsBetweenPhase *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((CopyItemsBetweenPhase *)Instance)->CFont;
	Data[4].Type				 =/**/"QString";
	Data[4].VariableNameWithRoute=/**/"AlgorithmRoot";
	Data[4].Pointer				 =&((CopyItemsBetweenPhase *)Instance)->AlgorithmRoot;
	Data[5].Type				 =/**/"QString";
	Data[5].VariableNameWithRoute=/**/"AlgorithmName";
	Data[5].Pointer				 =&((CopyItemsBetweenPhase *)Instance)->AlgorithmName;
	Data[6].Type				 =/**/"int32";
	Data[6].VariableNameWithRoute=/**/"SourcePhase";
	Data[6].Pointer				 =&((CopyItemsBetweenPhase *)Instance)->SourcePhase;
	Data[7].Type				 =/**/"int32";
	Data[7].VariableNameWithRoute=/**/"DestinationPhase";
	Data[7].Pointer				 =&((CopyItemsBetweenPhase *)Instance)->DestinationPhase;
	Data[8].Type				 =/**/"bool";
	Data[8].VariableNameWithRoute=/**/"ModeCopyMasterImage";
	Data[8].Pointer				 =&((CopyItemsBetweenPhase *)Instance)->ModeCopyMasterImage;
	Data[9].Type				 =/**/"bool";
	Data[9].VariableNameWithRoute=/**/"ModeCopyTargetImage";
	Data[9].Pointer				 =&((CopyItemsBetweenPhase *)Instance)->ModeCopyTargetImage;
	Data[10].Type				 =/**/"bool";
	Data[10].VariableNameWithRoute=/**/"ModeCopyAlgorithm";
	Data[10].Pointer			 =&((CopyItemsBetweenPhase *)Instance)->ModeCopyAlgorithm;
	return(11);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/CopyItemsBetweenPhase.png")));
}

//==================================================================================================
CopyItemsBetweenPhase::CopyItemsBetweenPhase(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.move(0,0);
	Msg=/**/"Copy items in Phase";
	SourcePhase	=-1;
	DestinationPhase=-1;
	ModeCopyMasterImage	=true;
	ModeCopyTargetImage	=true;
	ModeCopyAlgorithm	=true;

	resize(60,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

CopyItemsBetweenPhase::~CopyItemsBetweenPhase(void)
{
}

void	CopyItemsBetweenPhase::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	CopyItemsBetweenPhase::ResizeAction()
{
	Button.resize(width(),height());
}

void CopyItemsBetweenPhase::SlotClicked (bool checked)
{
	int32	iSourcePhase		=SourcePhase;
	int32	iDestinationPhase	=DestinationPhase;
	bool	iModeCopyMasterImage=ModeCopyMasterImage;
	bool	iModeCopyTargetImage=ModeCopyTargetImage;
	bool	iModeCopyAlgorithm	=ModeCopyAlgorithm;

	if(SourcePhase==-1 || DestinationPhase==-1){
		CopyBetweenPhaseDialog	D(AlgorithmRoot,AlgorithmName
								,SourcePhase
								,DestinationPhase
								,ModeCopyMasterImage
								,ModeCopyTargetImage
								,ModeCopyAlgorithm
								,GetLayersBase(),this);
		if(D.exec()!=(int)true)
			return;
		iSourcePhase		=D.SourcePhase;
		iDestinationPhase	=D.DestinationPhase;
		iModeCopyMasterImage=D.ModeCopyMasterImage;
		iModeCopyTargetImage=D.ModeCopyTargetImage;
		iModeCopyAlgorithm	=D.ModeCopyAlgorithm;
	}
	if(iSourcePhase>=0 && iDestinationPhase>=0){
		for(int page=0;page<GetPageNumb();page++){
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdCopyData	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
			RCmd.SourcePhase		=iSourcePhase;
			RCmd.DestinationPhase	=iDestinationPhase;
			RCmd.ModeCopyMasterImage=iModeCopyMasterImage;
			RCmd.ModeCopyTargetImage=iModeCopyTargetImage;
			RCmd.ModeCopyAlgorithm	=iModeCopyAlgorithm;
			RCmd.AlgorithmRoot		=AlgorithmRoot;
			RCmd.AlgorithmName		=AlgorithmName;
			RCmd.Send(NULL,page,0);
		}
	}
}
void	CopyItemsBetweenPhase::TransmitDirectly(GUIDirectMessage *packet)
{
}

void	CopyItemsBetweenPhase::GetMenuInfo(MenuInfoContainer &Info)
{
	MenuInfoList	*p=new MenuInfoList(1
										,LangSolver.GetString(CopyItemsBetweenPhase_LS,LID_0)/*"Algorithm"*/
										,LangSolver.GetString(CopyItemsBetweenPhase_LS,LID_1)/*"Copy items between Phase"*/,this);
	p->SetMenuNumber(245);
	Info.AppendList(p);
}
void	CopyItemsBetweenPhase::ExecuteMenu(int ID)
{
	if(ID==1){
		SlotClicked(true);
	}
}

//==================================================================================================

GUICmdCopyData::GUICmdCopyData(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdCopyData::Load(QIODevice *f)
{
	if(::Load(f,AlgorithmRoot)==false)
		return false;
	if(::Load(f,AlgorithmName)==false)
		return false;
	if(::Load(f,SourcePhase)==false)
		return false;
	if(::Load(f,DestinationPhase)==false)
		return false;
	if(::Load(f,ModeCopyMasterImage)==false)
		return false;
	if(::Load(f,ModeCopyTargetImage)==false)
		return false;
	if(::Load(f,ModeCopyAlgorithm)==false)
		return false;
	return true;
}
bool	GUICmdCopyData::Save(QIODevice *f)
{
	if(::Save(f,AlgorithmRoot)==false)
		return false;
	if(::Save(f,AlgorithmName)==false)
		return false;
	if(::Save(f,SourcePhase)==false)
		return false;
	if(::Save(f,DestinationPhase)==false)
		return false;
	if(::Save(f,ModeCopyMasterImage)==false)
		return false;
	if(::Save(f,ModeCopyTargetImage)==false)
		return false;
	if(::Save(f,ModeCopyAlgorithm)==false)
		return false;
	return true;
}

void	GUICmdCopyData::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());

	DataInPage	*P=GetLayersBase()->GetPageData(localPage);

	int	LayerNumb=GetLayerNumb(localPage);
	if(0<=SourcePhase && SourcePhase<GetPhaseNumb() && 0<=DestinationPhase && DestinationPhase<GetPhaseNumb()){
		PageDataInOnePhase	*PhSrc=GetLayersBase()->GetPageDataPhase(SourcePhase);
		PageDataInOnePhase	*PhDst=GetLayersBase()->GetPageDataPhase(DestinationPhase);
		DataInPage *PageSrc=PhSrc->GetPageData(localPage);
		DataInPage *PageDst=PhDst->GetPageData(localPage);
		for(int Layer=0;Layer<GetLayerNumb(localPage);Layer++){
			DataInLayer	*LySrc=PageSrc->GetLayerData(Layer);
			DataInLayer	*LyDst=PageDst->GetLayerData(Layer);

			if(ModeCopyMasterImage==true){
				LyDst->GetMasterBuff()	=	LySrc->GetMasterBuff();
				LyDst->GetMasterBuff().SetChanged(true);
			}

			if(ModeCopyTargetImage==true){
				LyDst->GetTargetBuff()	=	LySrc->GetTargetBuff();
				LyDst->GetTargetBuff().SetChanged(true);
			}
			if(ModeCopyAlgorithm==true){
				if(AlgorithmRoot.isEmpty()==true || AlgorithmName.isEmpty()==true){
					for(LogicDLL *L=GetLayersBase()->GetLogicDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
						QBuffer		Buff;
						Buff.open(QIODevice::ReadWrite);
						L->GetInstance()->GetPageDataPhase(SourcePhase)->GetPageData(localPage)->Save(&Buff);
						Buff.seek(0);
						L->GetInstance()->GetPageDataPhase(DestinationPhase)->GetPageData(localPage)->Load(&Buff);
						L->GetInstance()->GetPageDataPhase(DestinationPhase)->GetPageData(localPage)->SetChanged(true);
					}
				}
				else{
					AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(AlgorithmRoot,AlgorithmName);
					if(Ab!=NULL){
						QBuffer		Buff;
						Buff.open(QIODevice::ReadWrite);
						Ab->GetPageDataPhase(SourcePhase)->GetPageData(localPage)->Save(&Buff);
						Buff.seek(0);
						Ab->GetPageDataPhase(DestinationPhase)->GetPageData(localPage)->Load(&Buff);
						Ab->GetPageDataPhase(DestinationPhase)->GetPageData(localPage)->SetChanged(true);
					}
				}
			}
		}
	}

	SendAck(localPage);
}
