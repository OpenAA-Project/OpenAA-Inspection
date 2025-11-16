/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\IntegrationButtonSaveAlgorithm\IntegrationButtonSaveAlgorithm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "IntegrationButtonSaveAlgorithm.h"
#include "XGeneralFunc.h"
#include <QFileDialog>
#include "XMacroFunction.h"
#include "XIntegrationBase.h"
#include "XDataInLayer.h"
#include <QMessageBox>
#include <QIcon>
#include <QPixmap>
#include "ButtonSaveAlgorithm.h"

const	char	*sRoot=/**/"Integration";
const	char	*sName=/**/"ButtonSaveAlgorithm";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to load algorithm");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)	=new IntegrationCmdReqSaveAlgorithm(Base,sRoot,sName,-1);
	(*Base)	=new IntegrationCmdAckSaveAlgorithm(Base,sRoot,sName,-1);
	return true;
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}
DEFFUNCEX	void	DLL_Close(void)
{
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new IntegrationButtonSaveAlgorithm(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<7)
		return(-1);
	Data[0].Type				 =/**/"QString";
	Data[0].VariableNameWithRoute=/**/"Msg";
	Data[0].Pointer				 =&((IntegrationButtonSaveAlgorithm *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((IntegrationButtonSaveAlgorithm *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((IntegrationButtonSaveAlgorithm *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((IntegrationButtonSaveAlgorithm *)Instance)->CFont;
	Data[4].Type				 =/**/"int32";
	Data[4].VariableNameWithRoute=/**/"SlaveNo";
	Data[4].Pointer				 =&((IntegrationButtonSaveAlgorithm *)Instance)->SlaveNo;
	Data[5].Type				 =/**/"QString";
	Data[5].VariableNameWithRoute=/**/"AlgoRoot";
	Data[5].Pointer				 =&((IntegrationButtonSaveAlgorithm *)Instance)->AlgoRoot;
	Data[6].Type				 =/**/"QString";
	Data[6].VariableNameWithRoute=/**/"AlgoName";
	Data[6].Pointer				 =&((IntegrationButtonSaveAlgorithm *)Instance)->AlgoName;

	return(7);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/IntegrationButtonSaveAlgorithm.png")));
}

DEFFUNCEX	void	DLL_AssociateComponent(LayersBase *Base,ComponentListContainer &List)
{
	List.Add(GUILIB_ID,/**/"Button" ,/**/"SaveAlgorithm");
}

//==================================================================================================
IntegrationButtonSaveAlgorithm::IntegrationButtonSaveAlgorithm(LayersBase *Base ,QWidget *parent)
	:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.setObjectName(/**/"IntegrationButtonSaveAlgorithmBtn");
	Button.move(0,0);
	Msg=/**/"Save algorithm";
	SlaveNo=0;

	resize(200,25);
	Button.setStyleSheet(/**/"QToolButton {"
						 /**/"	border-style: outset;"
						 /**/"	border-width: 1px;"
						 /**/"	border-radius: 25px;"
						 /**/"	border-color: gray;"
						 /**/"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));"
						 /**/"}"
						 /**/"QToolButton:pressed { 	"
						 /**/"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));"
						 /**/"}"
						);
	connect(&Button,SIGNAL(clicked()), this ,SLOT(SlotClicked()));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

void	IntegrationButtonSaveAlgorithm::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	IntegrationButtonSaveAlgorithm::ResizeAction()
{
	Button.setGeometry(0,0,width(),height());
}

void	IntegrationButtonSaveAlgorithm::SlotClicked ()
{
	QString FileName=QFileDialog::getSaveFileName(nullptr, "Save algorithm file"
												, QString()
												, /**/"Algo file(*.alg);;All files(*.*)");
	if(FileName.isEmpty()==false){
		QFile	File(FileName);
		if(File.open(QIODevice::WriteOnly)==true){
			IntegrationCmdReqSaveAlgorithm	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
			IntegrationCmdAckSaveAlgorithm	ACmd(GetLayersBase(),sRoot,sName,SlaveNo);
			RCmd.AlgoRoot=AlgoRoot;
			RCmd.AlgoName=AlgoName;
			if(RCmd.Send(SlaveNo,0,ACmd)==true){
				int64	DataLen=ACmd.Data.length();
				if(File.write(ACmd.Data)==false){
					QMessageBox::critical(NULL
										,"エラー"
										,"書き込めません");
				}
			}
		}
	}
}

//======================================================================================

IntegrationCmdReqSaveAlgorithm::IntegrationCmdReqSaveAlgorithm(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationCmdReqSaveAlgorithm::Load(QIODevice *f)
{
	if(::Load(f,AlgoRoot)==false)
		return false;
	if(::Load(f,AlgoName)==false)
		return false;
	return true;
}
bool	IntegrationCmdReqSaveAlgorithm::Save(QIODevice *f)
{
	if(::Save(f,AlgoRoot)==false)
		return false;
	if(::Save(f,AlgoName)==false)
		return false;
	return true;
}

void	IntegrationCmdReqSaveAlgorithm::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	IntegrationCmdAckSaveAlgorithm	*SendBack=GetSendBackIntegration(IntegrationCmdAckSaveAlgorithm,GetLayersBase(),EmitterRoot,EmitterName ,slaveNo);

	GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Button" ,/**/"SaveAlgorithm",/**/"");
	if(f!=NULL){
		CmdReqAlgorithmData	Cmd(GetLayersBase());
		Cmd.AlgorithmRoot=AlgoRoot;
		Cmd.AlgorithmName=AlgoName;
		QBuffer	Buff;
		Buff.open(QIODevice::ReadWrite);
		Cmd.Data=&Buff;
		f->TransmitDirectly(&Cmd);
		if(Cmd.RetSuccessful==true){
			SendBack->Data=Buff.buffer();
		}
	}
	SendBack->Send(this ,slaveNo,0);
	CloseSendBackIntegration(SendBack);
}

IntegrationCmdAckSaveAlgorithm::IntegrationCmdAckSaveAlgorithm(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationCmdAckSaveAlgorithm::Load(QIODevice *f)
{
	if(::Load(f,Data)==false)
		return false;
	return true;
}
bool	IntegrationCmdAckSaveAlgorithm::Save(QIODevice *f)
{
	if(::Save(f,Data)==false)
		return false;
	return true;
}
