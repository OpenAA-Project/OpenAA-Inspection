/*
 * Copyright (C) 2025
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */



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
#include "XOpenAA.h"

ItemListWindow	*MainItem;
PropertyList	*MainProperty;

/*
	Arguments:
		A[path]	: Set current path to [path]
		Q[path]	: Set user path to [path] for data 
		StopForDebug : Stop for debug
*/
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
	QString	AddedLibPath = QString(CurrentBuff)+QString("/plugins");
	QCoreApplication::addLibraryPath(AddedLibPath);

	QApplication a(argc, argv);
	QString	UserPath;
	QString	AbsPath;
	bool	StopForDebug=false;

	for(int i=1;i<argc;i++){
		if(*argv[i]=='A' || *argv[i]=='a'){
			char	*fp=argv[i]+1;
			AbsPath	=fp;
			QDir::setCurrent(AbsPath);
		}
		else if((*argv[i]=='Q' || *argv[i]=='q') && *(argv[i]+1)!=':'){
			char	*fp=argv[i]+1;
			UserPath	=fp;
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

	LayersBase	*Layers	=new LayersBase(E,::GetUserPath(UserPath));
	E->SetLayersBase(Layers);
	Layers->SetUserPath(UserPath);

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