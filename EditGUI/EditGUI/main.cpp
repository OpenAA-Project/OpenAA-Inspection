/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\EditGUI\EditGUI\main.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include <QApplication>
#include <QMessageBox>
#include <QGuiApplication>
#include "XGUI.h"
#include "XDataInExe.h"
#include "EditGui.h"
#include "XFileRegistry.h"
#include "XShowVersion.h"
#include "XStatusController.h"
#include "XIntegrationBase.h"
#include "XParamIntegrationMaster.h"
#include "itemlistwindow.h"
#include "propertylist.h"
#include "Regulus64System.h"

ItemListWindow	*MainItem;
PropertyList	*MainProperty;

const	char	*LayersBase::GetLanguageSolutionFileName(void)
{
	return "EditParameter.lng";
}

class	EntryPointForEditGUI : public EntryPointForGlobal
{
public:
	EntryPointForEditGUI(void){}

	virtual	void	GUISetProperty(GUIFormBase *Current,GUIFormBase *PutTop)	override;
};

void	EntryPointForEditGUI::GUISetProperty(GUIFormBase *CurrentForm,GUIFormBase *PutTop)
{
	if(CurrentForm!=NULL){
		GUIInitializer	*GD	=CurrentForm->GetLayersBase()->GetGuiInitializer();
		GUIItemInstance	*c=GD->GetGUIInstanceRoot()->Search(CurrentForm);
		if(c!=NULL && MainProperty!=NULL){
			MainProperty->DLLInst=c;
			MainProperty->PutTop=PutTop;
			if(c->DLLAccess!=NULL){
				MainProperty->ShowList(c->GetDLLRoot(),c->GetDLLName());
			}
			else{
				MainProperty->ClearList();
			}
		}
	}
	else{
		if(MainProperty!=NULL){
			MainProperty->DLLInst=NULL;
		}
	}
}


int main(int argc, char *argv[])
{
	if(CheckExeVersion(argc, argv)==false)
		return 1;

	char	TBuff[256];
	strcpy(TBuff,"-platformpluginpath");
	argv[argc] = TBuff;
	argc++;

	char	CurrentBuff[256];
	strcpy(CurrentBuff,(char *)QDir::currentPath().toStdString().c_str());
	argv[argc] = CurrentBuff;	
	argc++;
	
	QCoreApplication::addLibraryPath(CurrentBuff);

	QApplication a(argc, argv);
	QString	AbsPath;
	bool	StopForDebug=false;

	for(int i=0;i<argc;i++){
		if(*argv[i]=='A' || *argv[i]=='a'){
			char	*fp=argv[i]+1;
			AbsPath	=fp;
			QDir::setCurrent(AbsPath);
		}
		else if(strnicmp(argv[i],"StopForDebug",12)==0){
			StopForDebug=true;
		}
	}
	if(StopForDebug==true){
		QMessageBox::information(NULL,"Stop","Please push OK button to go",QMessageBox::Ok);
	}

	if(AbsPath.isEmpty()==false){
		QCoreApplication::addLibraryPath (AbsPath);
	}
	else{
		QCoreApplication::addLibraryPath (QCoreApplication::applicationDirPath());
	}

	EntryPointBase	*E	=new EntryPointForEditGUI();
	E->GUISetEditMode(true);

	LayersBase	*Layers	=new LayersBase(E);
	E->SetLayersBase(Layers);
	GUIInitializer	*G=new GUIInitializer(Layers);
	Layers->SetGUIInitializer(G);

	EditGUI w(Layers);
    w.show();
    a.connect(&a, SIGNAL(lastWindowClosed()), &a, SLOT(quit()));


	Layers->SetCurrentPath(QDir::currentPath());
	Layers->GetParamGlobal()->LoadDefault(Layers->GetUserPath());
	Layers->GetParamComm()->LoadDefault(Layers->GetUserPath());
	QString	ErrorMsg;
	DWORD	ErrorCode=0;

	if(Layers->GetGuiInitializer()->Initial(Layers,ErrorCode ,ErrorMsg,true)==false || ErrorCode!=0){
		QString  msg=QString(/**/"GUI Error: ")
			+QString::number(ErrorCode);
		QMessageBox Q(msg
					, ErrorMsg, QMessageBox::Critical
					, QMessageBox::Ok , QMessageBox::NoButton, QMessageBox::NoButton);
		Q.exec();
		return(1);
	}
	if(Layers->GetStatusController()!=NULL){
		Layers->GetStatusController()->LoadDef();
	}
	Layers->GetParamGlobal()->DotPerLine=100;
	Layers->GetParamGlobal()->MaxLines	=100;
	Layers->GetParamGlobal()->PageNumb	=1;
	Layers->GetParamGlobal()->PhaseNumb	=1;

	QString Msg;
	if(Layers->GetGuiInitializer()->GetGUIInstanceRoot()->InitialLayers(Msg)==false){
		QMessageBox Q(/**/"Error"
					, Msg, QMessageBox::Critical
					, QMessageBox::Ok , QMessageBox::NoButton, QMessageBox::NoButton);
		Q.exec();
		return(1);
	}
	RootNameListContainer	AlgorithmRootNameList;
	QStringList	AlgorithmPathList;
	AlgorithmPathList<<DefAlgorithmPath;
	AlgorithmPathList<<DefRegulusWorldAlgorithmPath;
	Layers->InitialAlgorithm(AlgorithmRootNameList,AlgorithmPathList,true);
	int	LanguageCode=Layers->GetFRegistry()->LoadRegInt("Language",0);
	Layers->SetLanguageCode();
	Layers->GetGuiInitializer()->SetLanguageCode(LanguageCode);

	Layers->GetGuiInitializer()->InitialMultiComputer(Layers->GetGuiInitializer()->GetGUIInstanceRoot()->GetFirstForm());
	Layers->LoadAttrDefault();

	QScreen	*Scr=qGuiApp->screens()[0];
	int DesktopWidth	= Scr->geometry().width();
	int DesktopHeight	= Scr->geometry().height();

	MainItem=new ItemListWindow(Layers);
	MainItem->Initial();
	MainItem->ShowItems();
	MainItem->resize(DesktopWidth*0.2, DesktopHeight*0.8);
	MainItem->show();

	MainProperty=new PropertyList(Layers,NULL);
	MainProperty->show();

	GUIFormBase	*Pr=new GUIFormBase(Layers);
	Pr->show();
				
	GUIItemInstance	*Inst=new GUIItemInstance(Layers->GetGuiInitializer()->GetGUIInstanceRoot());
	Inst->Handle=Pr;
	Inst->InstanceID=Layers->GetGuiInitializer()->GetGUIInstanceRoot()->GetMaxInstanceID()+1;
	Layers->GetGuiInitializer()->GetGUIInstanceRoot()->AppendList(Inst);

	w.move(0,0);
	MainItem->move(0,w.height());
	MainProperty->move(MainItem->width(),w.height());
	Pr->move(MainItem->width()+MainProperty->width(),w.height());

	Layers->InitialFilterBank();
	Layers->InitialSyncGUI();
	Layers->LoadFilterDef();

	Layers->LoadShadowChildrenDLL();

	ParamIntegrationMaster	ParamIntegrationMasterData(Layers);
	ParamIntegrationMasterData.LoadDefault(Layers->GetUserPath());
	IntegrationBase	*IBase=new IntegrationBase(Layers,&ParamIntegrationMasterData);
	IBase->Initialize();
	Layers->SetIntegrationBase(IBase);

	Layers->CloseInformed();
	if(Layers->GetStatusController()!=NULL){
		Layers->GetStatusController()->InstallFilter();
	}
	return a.exec();
}
