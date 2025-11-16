/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\IntegrationButtonLoadAlgorithm\IntegrationButtonLoadAlgorithm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "IntegrationButtonLoadAlgorithm.h"
#include "XGeneralFunc.h"
#include <QFileDialog>
#include "XMacroFunction.h"
#include "XIntegrationBase.h"
#include "XDataInLayer.h"
#include <QMessageBox>
#include <QIcon>
#include <QPixmap>
#include <QMessageBox>
#include "ButtonLoadAlgorithm.h"

const	char	*sRoot=/**/"Integration";
const	char	*sName=/**/"ButtonLoadAlgorithm";

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
	(*Base)	=new IntegrationCmdLoadAlgorithm(Base,sRoot,sName,-1);

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
	return(new IntegrationButtonLoadAlgorithm(Base,parent));
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
	Data[0].Pointer				 =&((IntegrationButtonLoadAlgorithm *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((IntegrationButtonLoadAlgorithm *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((IntegrationButtonLoadAlgorithm *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((IntegrationButtonLoadAlgorithm *)Instance)->CFont;
	Data[4].Type				 =/**/"int32";
	Data[4].VariableNameWithRoute=/**/"SlaveNo";
	Data[4].Pointer				 =&((IntegrationButtonLoadAlgorithm *)Instance)->SlaveNo;
	Data[5].Type				 =/**/"QString";
	Data[5].VariableNameWithRoute=/**/"AlgoRoot";
	Data[5].Pointer				 =&((IntegrationButtonLoadAlgorithm *)Instance)->AlgoRoot;
	Data[6].Type				 =/**/"QString";
	Data[6].VariableNameWithRoute=/**/"AlgoName";
	Data[6].Pointer				 =&((IntegrationButtonLoadAlgorithm *)Instance)->AlgoName;

	return(7);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/IntegrationButtonLoadAlgorithm.png")));
}

DEFFUNCEX	void	DLL_AssociateComponent(LayersBase *Base,ComponentListContainer &List)
{
	List.Add(GUILIB_ID,/**/"Button" ,/**/"LoadAlgorithm");
}

//==================================================================================================
IntegrationButtonLoadAlgorithm::IntegrationButtonLoadAlgorithm(LayersBase *Base ,QWidget *parent)
	:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.setObjectName(/**/"IntegrationButtonLoadAlgorithmBtn");
	Button.move(0,0);
	Msg=/**/"Load algorithm";
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

void	IntegrationButtonLoadAlgorithm::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	IntegrationButtonLoadAlgorithm::ResizeAction()
{
	Button.setGeometry(0,0,width(),height());
}

void	IntegrationButtonLoadAlgorithm::SlotClicked ()
{
	QString FileName=QFileDialog::getOpenFileName(nullptr, "Load algorithm file"
												, QString()
												, /**/"Algo file(*.alg);;All files(*.*)");
	if(FileName.isEmpty()==false){
		QFile	File(FileName);
		if(File.open(QIODevice::ReadOnly)==true){
			QByteArray	Data=File.readAll();
			IntegrationCmdLoadAlgorithm	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
			RCmd.AlgoRoot=AlgoRoot;
			RCmd.AlgoName=AlgoName;
			RCmd.Data	 =Data;
			RCmd.Send(NULL,SlaveNo,0);
		}
	}
}

IntegrationCmdLoadAlgorithm::IntegrationCmdLoadAlgorithm(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationCmdLoadAlgorithm::Load(QIODevice *f)
{
	if(::Load(f,AlgoRoot)==false)
		return false;
	if(::Load(f,AlgoName)==false)
		return false;
	if(::Load(f,Data)==false)
		return false;
	return true;
}
bool	IntegrationCmdLoadAlgorithm::Save(QIODevice *f)
{
	if(::Save(f,AlgoRoot)==false)
		return false;
	if(::Save(f,AlgoName)==false)
		return false;
	if(::Save(f,Data)==false)
		return false;
	return true;
}

void	IntegrationCmdLoadAlgorithm::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Button" ,/**/"LoadAlgorithm",/**/"");
	if(f!=NULL){
		ExecuteLoadAlgorithmByData	Cmd(GetLayersBase());
		Cmd.AlgorithmRoot=AlgoRoot;
		Cmd.AlgorithmName=AlgoName;
		Cmd.Data		=Data;
		f->TransmitDirectly(&Cmd);
	}
}

