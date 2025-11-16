/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\CopyByControlPoints\CopyByControlPoints.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "CopyByControlPoints.h"
#include "XGeneralDialog.h"
#include "XGeneralFunc.h"
#include "XMacroFunction.h"
#include "SettingDialog.h"
#include "XDataInLayer.h"
#include "XAlgorithmBase.h"
#include "NList.h"
#include<QMessageBox>
#include "SelectAlgorithmDialog.h"
#include "XTransform.h"

const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"CopyByControlPoints";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to copy by ControlPoints");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdReqAlgoDataWithControlPoints	(Base,sRoot,sName);
	(*Base)=new GUICmdAckAlgoDataWithControlPoints	(Base,sRoot,sName);
	(*Base)=new GUICmdSetAlgoDataWithControlPoints	(Base,sRoot,sName);
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new CopyByControlPoints(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<5)
		return(-1);
	Data[0].Type				 =/**/"QString";
	Data[0].VariableNameWithRoute=/**/"Msg";
	Data[0].Pointer				 =&((CopyByControlPoints *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((CopyByControlPoints *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((CopyByControlPoints *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((CopyByControlPoints *)Instance)->CFont;
	Data[4].Type				 =/**/"QByteArray";
	Data[4].VariableNameWithRoute=/**/"FromToArray";
	Data[4].Pointer				 =&((CopyByControlPoints *)Instance)->FromToArray;
	Data[5].Type				 =/**/"QByteArray";
	Data[5].VariableNameWithRoute=/**/"AlgorithmRootName";
	Data[5].Pointer				 =&((CopyByControlPoints *)Instance)->AlgorithmRootName;
	
	return(6);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/CopyByControlPoints.png")));
}

//==================================================================================================
CopyByControlPoints::CopyByControlPoints(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.move(0,0);
	Button.setObjectName(/**/"CopyByControlPoints");
	Msg=/**/"Copy by ControlPoints";

	resize(60,25);
	connect(&Button,SIGNAL(clicked(bool))	, this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize())		, this ,SLOT(ResizeAction()));
}

CopyByControlPoints::~CopyByControlPoints(void)
{
}

void	CopyByControlPoints::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	CopyByControlPoints::ResizeAction()
{
	Button.resize(width(),height());
}
bool	CopyByControlPoints::ShowQByteArrayDialog(const QString &VariableName)
{
	if(VariableName==/**/"FromToArray"){
		{
			QBuffer	Buff(&FromToArray);
			Buff.open(QIODevice::ReadWrite);
			FromToInfo.Load(&Buff);
		}
		SettingDialog	D(GetLayersBase(),FromToInfo);
		if(D.exec()==(int)true){
			FromToInfo=D.InfoData;
			QBuffer	Buff;
			Buff.open(QIODevice::ReadWrite);
			FromToInfo.Save(&Buff);
			FromToArray=Buff.buffer();
		}
	}
	else
	if(VariableName==/**/"AlgorithmRootName"){
		QBuffer	Buff(&AlgorithmRootName);
		Buff.open(QIODevice::ReadWrite);
		RootNameListContainer	Selected;
		Selected.Load(&Buff);
		SelectAlgorithmDialog	D(GetLayersBase(),Selected);
		if(D.exec()==(int)true){
			QBuffer	Buff;
			Buff.open(QIODevice::ReadWrite);
			D.Selected.Save(&Buff);
			AlgorithmRootName=Buff.buffer();
		}
	}
	return true;
}

//==========================================================

void CopyByControlPoints::SlotClicked (bool checked)
{
	if(GetLayersBase()->GetShadowLevel()==0){
		CopyTopShadowLevel();
	}
	else{
		CopyShadowLevelFromTop();
	}
}

void CopyByControlPoints::CopyTopShadowLevel(void)
{
	QBuffer	Buff(&FromToArray);
	Buff.open(QIODevice::ReadWrite);
	if(FromToInfo.Load(&Buff)==false){
		QMessageBox::warning(NULL,"Warning"
							,"No setting data in FromToInfo field");
		return;
	}
	AlgoListInPageContainer	AlgoListInPageData;
	QBuffer	ABuff(&AlgorithmRootName);
	ABuff.open(QIODevice::ReadWrite);
	RootNameListContainer	AlgorithmList;
	AlgorithmList.Load(&ABuff);

	if(FromToInfo.SrcType==FromToClass::Info_AllPages){
		for(int page=0;page<GetParamGlobal()->PageNumb;page++){
			int	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),page);
			for(int phase=0;phase<GetPhaseNumb();phase++){
			    GUICmdReqAlgoDataWithControlPoints  RCmd(GetLayersBase(),sRoot,sName,globalPage);
				RCmd.Phase=phase;
				RCmd.ShadowLevel	=GetLayersBase()->GetShadowLevel();
				RCmd.ShadowNumber	=GetLayersBase()->GetShadowNumber();
				RCmd.AlgorithmList	=AlgorithmList;
			    GUICmdAckAlgoDataWithControlPoints  ACmd(GetLayersBase(),sRoot,sName,globalPage);
			    if(RCmd.Send(globalPage,0,ACmd)==true){
					AlgoListInPage	*a=new AlgoListInPage();
					a->Phase=phase;
					a->Page=page;
					a->ControlPointsForPages=ACmd.ControlPointsForPages;
					a->AlgoList	=ACmd.AlgoList;
					AlgoListInPageData.AppendList(a);
			    }
			}
		}
	}
	else
	if(FromToInfo.SrcType==FromToClass::Info_Shadow){
		LayersBase	*L=GetLayersBase()->GetShadowTree(FromToInfo.SrcShadowLevel ,FromToInfo.SrcShadowNumber);
		for(int page=0;page<L->GetParamGlobal()->PageNumb;page++){
			int	globalPage=L->GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),page);
			for(int phase=0;phase<L->GetPhaseNumb();phase++){
			    GUICmdReqAlgoDataWithControlPoints  RCmd(GetLayersBase(),sRoot,sName,globalPage);
				RCmd.Phase=phase;
				RCmd.ShadowLevel	=L->GetShadowLevel();
				RCmd.ShadowNumber	=L->GetShadowNumber();
				RCmd.AlgorithmList	=AlgorithmList;
			    GUICmdAckAlgoDataWithControlPoints  ACmd(GetLayersBase(),sRoot,sName,globalPage);
			    if(RCmd.Send(globalPage,0,ACmd)==true){
					AlgoListInPage	*a=new AlgoListInPage();
					a->Phase=phase;
					a->Page=page;
					a->ControlPointsForPages=ACmd.ControlPointsForPages;
					a->AlgoList	=ACmd.AlgoList;
					AlgoListInPageData.AppendList(a);
			    }
			}
		}
	}
	else
	if(FromToInfo.SrcType==FromToClass::Info_Page){
		for(IntClass *v=FromToInfo.SrcPage.GetFirst();v!=NULL;v=v->GetNext()){
			int	page=v->GetValue();	
			int	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),page);
			for(int phase=0;phase<GetPhaseNumb();phase++){
				GUICmdReqAlgoDataWithControlPoints  RCmd(GetLayersBase(),sRoot,sName,globalPage);
				RCmd.Phase=phase;
				RCmd.ShadowLevel	=GetLayersBase()->GetShadowLevel();
				RCmd.ShadowNumber	=GetLayersBase()->GetShadowNumber();
				RCmd.AlgorithmList	=AlgorithmList;
				GUICmdAckAlgoDataWithControlPoints  ACmd(GetLayersBase(),sRoot,sName,globalPage);
				if(RCmd.Send(globalPage,0,ACmd)==true){
					AlgoListInPage	*a=new AlgoListInPage();
					a->Phase=phase;
					a->Page=page;
					a->ControlPointsForPages=ACmd.ControlPointsForPages;
					a->AlgoList	=ACmd.AlgoList;
					AlgoListInPageData.AppendList(a);			        
				}
			}
		}
	}
	else
	if(FromToInfo.SrcType==FromToClass::Info_File){
		QDir::setCurrent(GetLayersBase()->GetUserPath());
		QFile	SrcFile(FromToInfo.SrcFileName);
		if(SrcFile.open(QIODevice::ReadOnly)==true){
			AlgoListInPageData.Load(&SrcFile);
		}
	}

	if(FromToInfo.DstType==FromToClass::Info_File){
		QDir::setCurrent(GetLayersBase()->GetUserPath());
		QFile	DstFile(FromToInfo.DstFileName);
		if(DstFile.open(QIODevice::WriteOnly)==true){
			AlgoListInPageData.Save(&DstFile);
		}
	}
	else
	if(FromToInfo.DstType==FromToClass::Info_AllPages){
		for(int page=0;page<GetParamGlobal()->PageNumb;page++){
			int	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),page);
			for(int phase=0;phase<GetPhaseNumb();phase++){
				AlgoListInPage *Point=NULL;
				for(AlgoListInPage *a=AlgoListInPageData.GetFirst();a!=NULL;a=a->GetNext()){
					if(a->Phase==phase && a->Page==page){
						Point=a;
						break;
					}
				}
				if(Point==NULL){
					for(AlgoListInPage *a=AlgoListInPageData.GetFirst();a!=NULL;a=a->GetNext()){
						if(a->Phase==phase){
							Point=a;
							break;
						}
					}
				}
				if(Point!=NULL){
					GUICmdSetAlgoDataWithControlPoints  RCmd(GetLayersBase(),sRoot,sName,globalPage);
					RCmd.Phase=phase;
					RCmd.ShadowLevel	=GetLayersBase()->GetShadowLevel();
					RCmd.ShadowNumber	=GetLayersBase()->GetShadowNumber();
					RCmd.ControlPointsForPages	=Point->ControlPointsForPages;
					RCmd.AlgoList		=Point->AlgoList;
					RCmd.Send(NULL,globalPage,0);
				}
			}
		}
	}
	else
	if(FromToInfo.DstType==FromToClass::Info_Shadow){
		for(int page=0;page<GetParamGlobal()->PageNumb;page++){
			int	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),page);
			for(int phase=0;phase<GetPhaseNumb();phase++){
				AlgoListInPage *Point=NULL;
				for(AlgoListInPage *a=AlgoListInPageData.GetFirst();a!=NULL;a=a->GetNext()){
					if(a->Phase==phase && a->Page==page){
						Point=a;
						break;
					}
				}
				if(Point==NULL){
					for(AlgoListInPage *a=AlgoListInPageData.GetFirst();a!=NULL;a=a->GetNext()){
						if(a->Phase==phase){
							Point=a;
							break;
						}
					}
				}
				if(Point!=NULL){
					GUICmdSetAlgoDataWithControlPoints  RCmd(GetLayersBase(),sRoot,sName,globalPage);
					RCmd.Phase=phase;
					RCmd.ShadowLevel	=FromToInfo.DstShadowLevel;
					RCmd.ShadowNumber	=FromToInfo.DstShadowNumber;
					RCmd.ControlPointsForPages	=Point->ControlPointsForPages;
					RCmd.AlgoList		=Point->AlgoList;
					RCmd.Send(NULL,globalPage,0);
				}
			}
		}
	}
	else
	if(FromToInfo.DstType==FromToClass::Info_Page){
		for(IntClass *v=FromToInfo.SrcPage.GetFirst();v!=NULL;v=v->GetNext()){
			int	page=v->GetValue();	
			int	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),page);
			for(int phase=0;phase<GetPhaseNumb();phase++){
				AlgoListInPage *Point=NULL;
				for(AlgoListInPage *a=AlgoListInPageData.GetFirst();a!=NULL;a=a->GetNext()){
					if(a->Phase==phase && a->Page==page){
						Point=a;
						break;
					}
				}
				if(Point==NULL){
					for(AlgoListInPage *a=AlgoListInPageData.GetFirst();a!=NULL;a=a->GetNext()){
						if(a->Phase==phase){
							Point=a;
							break;
						}
					}
				}
				if(Point!=NULL){
					GUICmdSetAlgoDataWithControlPoints  RCmd(GetLayersBase(),sRoot,sName,globalPage);
					RCmd.Phase=phase;
					RCmd.ShadowLevel	=FromToInfo.DstShadowLevel;
					RCmd.ShadowNumber	=FromToInfo.DstShadowNumber;
					RCmd.ControlPointsForPages	=Point->ControlPointsForPages;
					RCmd.AlgoList		=Point->AlgoList;
					RCmd.Send(NULL,globalPage,0);
				}
			}
		}
	}
}

void CopyByControlPoints::CopyShadowLevelFromTop(void)
{
	QBuffer	Buff(&FromToArray);
	Buff.open(QIODevice::ReadWrite);
	if(FromToInfo.Load(&Buff)==false){
		QMessageBox::warning(NULL,"Warning"
							,"No setting data in FromToInfo field");
		return;
	}
	AlgoListInPageContainer	AlgoListInPageData;
	QBuffer	ABuff(&AlgorithmRootName);
	ABuff.open(QIODevice::ReadWrite);
	RootNameListContainer	AlgorithmList;
	AlgorithmList.Load(&ABuff);

	if(FromToInfo.SrcType==FromToClass::Info_File){
		QDir::setCurrent(GetLayersBase()->GetUserPath());
		QFile	SrcFile(FromToInfo.SrcFileName);
		if(SrcFile.open(QIODevice::ReadOnly)==true){
			AlgoListInPageData.Load(&SrcFile);
		}
	}
	else{
		for(int page=0;page<GetParamGlobal()->PageNumb;page++){
			int	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),page);
			for(int phase=0;phase<GetPhaseNumb();phase++){
			    GUICmdReqAlgoDataWithControlPoints  RCmd(GetLayersBase(),sRoot,sName,globalPage);
				RCmd.Phase=phase;
				RCmd.ShadowLevel	=0;
				RCmd.ShadowNumber	=-1;
				RCmd.AlgorithmList	=AlgorithmList;
			    GUICmdAckAlgoDataWithControlPoints  ACmd(GetLayersBase(),sRoot,sName,globalPage);
			    if(RCmd.Send(globalPage,0,ACmd)==true){
					AlgoListInPage	*a=new AlgoListInPage();
					a->Phase=phase;
					a->Page=page;
					a->ControlPointsForPages=ACmd.ControlPointsForPages;
					a->AlgoList	=ACmd.AlgoList;
					AlgoListInPageData.AppendList(a);
			    }
			}
		}
	}

	for(int page=0;page<GetParamGlobal()->PageNumb;page++){
		int	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),page);
		for(int phase=0;phase<GetPhaseNumb();phase++){
			AlgoListInPage *Point=NULL;
			for(AlgoListInPage *a=AlgoListInPageData.GetFirst();a!=NULL;a=a->GetNext()){
				if(a->Phase==phase && a->Page==page){
					Point=a;
					break;
				}
			}
			if(Point==NULL){
				for(AlgoListInPage *a=AlgoListInPageData.GetFirst();a!=NULL;a=a->GetNext()){
					if(a->Phase==phase){
						Point=a;
						break;
					}
				}
			}
			if(Point!=NULL){
				GUICmdSetAlgoDataWithControlPoints  RCmd(GetLayersBase(),sRoot,sName,globalPage);
				RCmd.Phase=phase;
				RCmd.ShadowLevel	=GetLayersBase()->GetShadowLevel();
				RCmd.ShadowNumber	=GetLayersBase()->GetShadowNumber();
				RCmd.ControlPointsForPages	=Point->ControlPointsForPages;
				RCmd.AlgoList		=Point->AlgoList;
				RCmd.Send(NULL,globalPage,0);
			}
		}
	}
}
//==================================================================
GUICmdReqAlgoDataWithControlPoints::GUICmdReqAlgoDataWithControlPoints(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdReqAlgoDataWithControlPoints::Load(QIODevice *f)
{
	if(::Load(f,ShadowLevel	)==false)	return false;
	if(::Load(f,ShadowNumber)==false)	return false;
	if(::Load(f,Phase		)==false)	return false;
	if(AlgorithmList.Load(f)==false)	return false;
	return true;
}
bool	GUICmdReqAlgoDataWithControlPoints::Save(QIODevice *f)
{
	if(::Save(f,ShadowLevel	)==false)	return false;
	if(::Save(f,ShadowNumber)==false)	return false;
	if(::Save(f,Phase		)==false)	return false;
	if(AlgorithmList.Save(f)==false)	return false;
	return true;
}
void	GUICmdReqAlgoDataWithControlPoints::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckAlgoDataWithControlPoints	*SendBack=GetSendBack(GUICmdAckAlgoDataWithControlPoints,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	LayersBase	*L=GetLayersBase()->GetShadowTree(ShadowLevel ,ShadowNumber);
	SendBack->ControlPointsForPages=L->GetControlPointsForPages(Phase,localPage);
	for(LogicDLL *DLL=L->GetLogicDLLBase()->GetFirst();DLL!=NULL;DLL=DLL->GetNext()){
		if(AlgorithmList.GetCount()==0
		|| AlgorithmList.Exists(DLL->GetDLLRoot(),DLL->GetDLLName())==true){
			AlgorithmBase	*ABase=DLL->GetInstance();
			AlgorithmInPageInOnePhase	*Ah=ABase->GetPageDataPhase(Phase);
			if(Ah!=NULL){
				AlgorithmInPageRoot		*Ap=Ah->GetPageData(localPage);
				QBuffer	Buff;
				Buff.open(QIODevice::ReadWrite);
				Ap->Save(&Buff);
				AlgoListArray	*a=new AlgoListArray();
				a->DLLRoot=DLL->GetDLLRoot();
				a->DLLName=DLL->GetDLLName();
				a->Array	=Buff.buffer();
				SendBack->AlgoList.AppendList(a);
			}
		}
	}

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckAlgoDataWithControlPoints::GUICmdAckAlgoDataWithControlPoints(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdAckAlgoDataWithControlPoints::Load(QIODevice *f)
{
	if(ControlPointsForPages.Load(f)==false)
		return false;
	if(AlgoList.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdAckAlgoDataWithControlPoints::Save(QIODevice *f)
{
	if(ControlPointsForPages.Save(f)==false)
		return false;
	if(AlgoList.Save(f)==false)
		return false;
	return true;
}

GUICmdSetAlgoDataWithControlPoints::GUICmdSetAlgoDataWithControlPoints(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSetAlgoDataWithControlPoints::Load(QIODevice *f)
{
	if(::Load(f,ShadowLevel	)==false)	return false;
	if(::Load(f,ShadowNumber)==false)	return false;
	if(::Load(f,Phase		)==false)	return false;
	if(ControlPointsForPages.Load(f)==false)
		return false;
	if(AlgoList.Load(f)==false)
		return false;

	return true;
}
bool	GUICmdSetAlgoDataWithControlPoints::Save(QIODevice *f)
{
	if(::Save(f,ShadowLevel	)==false)	return false;
	if(::Save(f,ShadowNumber)==false)	return false;
	if(::Save(f,Phase		)==false)	return false;
	if(ControlPointsForPages.Save(f)==false)
		return false;
	if(AlgoList.Save(f)==false)
		return false;

	return true;
}

void	GUICmdSetAlgoDataWithControlPoints::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	LayersBase	*L=GetLayersBase()->GetShadowTree(ShadowLevel ,ShadowNumber);
	TransformBase	*Param=TransformBase::MakeTransformParamControlPoints(L->GetControlPointsForPages(Phase,localPage) ,ControlPointsForPages);

	if(Param!=NULL){
		for(LogicDLL *DLL=L->GetLogicDLLBase()->GetFirst();DLL!=NULL;DLL=DLL->GetNext()){
			for(AlgoListArray *a=AlgoList.GetFirst();a!=NULL;a=a->GetNext()){
				if(a->DLLRoot==DLL->GetDLLRoot() && a->DLLName==DLL->GetDLLName()){
					AlgorithmBase	*ABase=DLL->GetInstance();
					AlgorithmInPageInOnePhase	*Ah=ABase->GetPageDataPhase(Phase);
					if(Ah!=NULL){
						AlgorithmInPageRoot		*Ap=Ah->GetPageData(localPage);
						QBuffer	Buff(&a->Array);
						Buff.open(QIODevice::ReadWrite);

						TransformBase	*Pb=L->MakeTransformFromMain().clone();
						*Pb*=(*Param);
						Ap->LoadByTransform(&Buff,*Pb);
						delete	Pb;
					}
				}
			}
		}
		delete	Param;
	}
}
