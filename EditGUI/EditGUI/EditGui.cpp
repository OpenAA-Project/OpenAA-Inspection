/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\EditGUI\EditGUI\EditGui.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "EditGui.h"
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QGuiApplication>
#include "FormScanStrategy.h"
#include "FormCommSetting.h"
#include "XGeneralDialog.h"
#include "WEditParameterTab.h"
#include "EditOutlineOffset.h"
#include "EditFilterBank.h"
#include "EditSyncGUIForm.h"
#include "CommDialogForm.h"
#include "EditPhaseForm.h"
#include "UsageConponentListForm.h"
#include "FormDirectionOnEachPage.h"
#include "SearchDialog.h"
#include "itemlistwindow.h"
#include "propertylist.h"
#include "swap.h"
#include "CopyBATDialog.h"
#include "XStatusController.h"
#include "XGeneralFunc.h"
#include "MakeLanguageDialog.h"
#include "EditOrderDialog.h"

static	bool	EditMode=true;

extern	ItemListWindow	*MainItem;
extern	PropertyList	*MainProperty;

EditGUI::EditGUI(LayersBase *Base,QWidget *parent, Qt::WindowFlags flags)
    : QMainWindow(parent, flags),ServiceForLayers(Base)
{
	ui.setupUi(this);

	connect(ui.actionCreate_new				,SIGNAL(triggered ()),this,SLOT(CreateNewFunc())			);
	connect(ui.actionOpen_GUI_file			,SIGNAL(triggered ()),this,SLOT(OpenGUIFileFunc())			);
	connect(ui.actionSave_GUI_file			,SIGNAL(triggered ()),this,SLOT(SaveGUIFileFunc())			);
	connect(ui.actionSave_GUI_file_As		,SIGNAL(triggered ()),this,SLOT(SaveGUIFileAsFunc())		);
	connect(ui.actionTest					,SIGNAL(triggered ()),this,SLOT(TestGUIFunc())				);
	connect(ui.actionGlobal_Setting			,SIGNAL(triggered ()),this,SLOT(Global_SettingFunc())		);
	connect(ui.actionCommunication_Setting	,SIGNAL(triggered ()),this,SLOT(Communication_SettingFunc()));
	connect(ui.actionScanning_setting		,SIGNAL(triggered ()),this,SLOT(Scanning_settingFunc())		);
	connect(ui.actionSave_Setting			,SIGNAL(triggered ()),this,SLOT(Save_settingFunc())			);
	connect(ui.actionSave_Setting			,SIGNAL(triggered ()),this,SLOT(Save_settingFunc())			);
	connect(ui.actionOutlineOffset			,SIGNAL(triggered ()),this,SLOT(OutlineOffsetFunc())		);
	connect(ui.actionSave_Global_Param		,SIGNAL(triggered ()),this,SLOT(SaveGlobalParamFunc())		);
	connect(ui.actionEdit_Filter			,SIGNAL(triggered ()),this,SLOT(EditFilterFunc())			);
	connect(ui.action_Sync_GUI_File			,SIGNAL(triggered ()),this,SLOT(EditSyncGUIFileFunc())		);
	connect(ui.actionEditPhase				,SIGNAL(triggered ()),this,SLOT(EditPhaseFunc())			);
	connect(ui.actionUsage_component		,SIGNAL(triggered ()),this,SLOT(UsageConponentList())		);
	connect(ui.actionSearch					,SIGNAL(triggered ()),this,SLOT(SearchFunc())				);
	connect(ui.actionSnap_to_grid			,SIGNAL(triggered ()),this,SLOT(Snap_to_gridFunc())				);
	connect(ui.actionMake_BAT_file			,SIGNAL(triggered ()),this,SLOT(Make_BAT_fileFunc())				);

	connect(ui.actionExit					,SIGNAL(triggered ()),this,SLOT(ExitFunc())					);

	PathToOpenedFile = /**/"";

	LoadFileButton=new QToolButton();
	LoadFileButton->setObjectName(/**/"LoadFileButton");
	LoadFileButton->setToolTip("Load GUI file");
	LoadFileButton->setCheckable(false);
	LoadFileButton->setAutoRaise(true);
	ui.mainToolBar->addWidget(LoadFileButton);
	connect(LoadFileButton,SIGNAL(clicked()),this,SLOT(OpenGUIFileFunc()));
	LoadFileButton->setIcon(QIcon(/**/":Resources/LoadFileButton.png"));

	SaveNewButton=new QToolButton();
	SaveNewButton->setObjectName(/**/"SaveNewButton");
	SaveNewButton->setToolTip("Save new GUI file");
	SaveNewButton->setCheckable(false);
	SaveNewButton->setAutoRaise(true);
	ui.mainToolBar->addWidget(SaveNewButton);
	connect(SaveNewButton,SIGNAL(clicked()),this,SLOT(SaveGUIFileAsFunc()));
	SaveNewButton->setIcon(QIcon(/**/":Resources/SaveNewButton.png"));

	OverwriteButton=new QToolButton();
	OverwriteButton->setObjectName(/**/"OverwriteButton");
	OverwriteButton->setToolTip("Overwrite GUI file");
	OverwriteButton->setCheckable(false);
	OverwriteButton->setAutoRaise(true);
	ui.mainToolBar->addWidget(OverwriteButton);
	connect(OverwriteButton,SIGNAL(clicked()),this,SLOT(SaveGUIFileFunc()));
	OverwriteButton->setIcon(QIcon(/**/":Resources/OverwriteButton.png"));

	ui.mainToolBar->addSeparator ();

	SearchButton=new QToolButton();
	SearchButton->setObjectName(/**/"SearchButton");
	SearchButton->setToolTip("Search");
	SearchButton->setCheckable(false);
	SearchButton->setAutoRaise(true);
	ui.mainToolBar->addWidget(SearchButton);
	connect(SearchButton,SIGNAL(clicked()),this,SLOT(SearchFunc()));
	SearchButton->setIcon(QIcon(/**/":Resources/SearchButton.png"));

	Snap2GridButton=new QToolButton();
	Snap2GridButton->setObjectName(/**/"Snap2GridButton");
	Snap2GridButton->setToolTip("Snap to Grid");
	Snap2GridButton->setCheckable(true);
	Snap2GridButton->setAutoRaise(false);
	ui.mainToolBar->addWidget(Snap2GridButton);
	connect(Snap2GridButton,SIGNAL(clicked()),this,SLOT(Snap_to_gridFunc()));
	Snap2GridButton->setIcon(QIcon(/**/":Resources/Snap2GridButton.png"));

	ui.mainToolBar->addSeparator ();

	TestButton=new QToolButton();
	TestButton->setObjectName(/**/"TestButton");
	TestButton->setToolTip("Test GUI");
	TestButton->setCheckable(true);
	TestButton->setAutoRaise(false);
	ui.mainToolBar->addWidget(TestButton);
	connect(TestButton,SIGNAL(clicked()),this,SLOT(TestGUIFunc()));
	TestButton->setIcon(QIcon(/**/":Resources/TestButton.png"));

	UsageComponentButton=new QToolButton();
	UsageComponentButton->setObjectName(/**/"UsageComponentButton");
	UsageComponentButton->setToolTip("Usage component list");
	UsageComponentButton->setCheckable(true);
	UsageComponentButton->setAutoRaise(false);
	ui.mainToolBar->addWidget(UsageComponentButton);
	connect(UsageComponentButton,SIGNAL(clicked()),this,SLOT(UsageConponentList()));
	UsageComponentButton->setIcon(QIcon(/**/":Resources/UsageComponentButton.png"));

}

EditGUI::~EditGUI()
{
	QApplication::closeAllWindows ();
}

void EditGUI::UsageConponentList()
{
	UsageConponentListForm	*D=new UsageConponentListForm(this,GetLayersBase());
	D->show();
}

void EditGUI::CreateNewFunc()
{
	PathToOpenedFile = /**/"";
}

void EditGUI::OpenGUIFileFunc()
{
	QString	FileName=QFileDialog::getOpenFileName(NULL
												, QString(tr("Open GUI file"))
												, QString()
												, QString(/**/"GUI File (*.gui);;All files (*.*)"));
	if(FileName.isEmpty()==false){
		QFile	file(FileName);
		file.open(QIODevice::ReadOnly);
		GUIInitializer	*GD	=GetLayersBase()->GetGuiInitializer();
		GD->GetGUIInstanceRoot()->CloseAll();
		QString ErrorMsg;
		if(GD->GetGUIInstanceRoot()->LoadInstances(&file ,ErrorMsg)==false){
			QMessageBox::critical ( NULL
								, "Loading Error"
								, ErrorMsg, QMessageBox::Ok);
			return;
		}
		MainGUIFormBase	*MainForm=NULL;
		MainForm=(MainGUIFormBase *)GD->GetGUIInstanceRoot()->CreateMainForm(GetLayersBase(),GUIInstancePack::_None);
		GetLayersBase()->SetMainForm(MainForm);
		GUIFormPointerContainer AppendedInstance;
			
		GetLayersBase()->SetGUIInstancePack(GD->GetGUIInstanceRoot());
		GD->GetGUIInstanceRoot()->ShowAll(MainForm
														,GetLayersBase()
														,GetLayersBase()->GetParamGUI()
														,true);
		//GD->GetGUIInstanceRoot()->ShowAll(GetLayersBase(),GUIInstancePack::_None,true);
		if(GD!=NULL && GD->GetGUIInstanceRoot()!=NULL && MainForm!=NULL){
			GetLayersBase()->InitialAfterParamLoaded();
			GD->GetGUIInstanceRoot()->ReadyParam(MainForm);
			MainForm->ReflectSize();
		}
		QScreen	*Scr=qGuiApp->screens()[0];
		if(MainForm->geometry().right()<20 || MainForm->geometry().bottom()<20
		|| MainForm->geometry().top()>=(Scr->geometry().height()-20)
		|| MainForm->geometry().left()>=(Scr->geometry().width()-20)){
			SetWidgetCenter(MainForm);
		}
		PathToOpenedFile=FileName;
		setWindowTitle(FileName);
	}
}

bool EditGUI::SaveGUIFile(const QString &FilePath)
{
	QString FileName=FilePath;
	if( 0!=FileName.right(4).compare(/**/".gui",Qt::CaseInsensitive))
		FileName+=/**/".gui";
	QFile	file(FileName);
	if(file.exists()){
		QMessageBox ConfirmBox(QMessageBox::Question
							, QString(tr("Confirmation"))
							, QString(tr("Do you want to overwrite this file?\n")) + PathToOpenedFile
							, QMessageBox::Ok | QMessageBox::Cancel);
		if(ConfirmBox.exec() != QMessageBox::Ok){
			return false;
		}
	}
	if( ! file.open(QIODevice::WriteOnly) ){
		return false;
	}
	GUIInitializer	*GD	=GetLayersBase()->GetGuiInitializer();
	GD->GetGUIInstanceRoot()->SaveInstances(&file);
	return true;
}

void EditGUI::SaveGUIFileAsFunc()
{
	QString	Cap=tr("Save GUI file");
	QString	FileName=QFileDialog::getSaveFileName(NULL
								, Cap
								, QString()
								, QString(/**/"GUI File (*.gui);;All files (*.*)"));
	if(FileName.isEmpty()==false){
		SaveGUIFile(FileName);
	}
}


void EditGUI::SaveGUIFileFunc()
{
	if(PathToOpenedFile==/**/""){
		SaveGUIFileAsFunc();
		return;
	}

	SaveGUIFile(PathToOpenedFile);
}


void EditGUI::TestGUIFunc()
{
	EditMode = !EditMode;
	GUIInitializer	*GD	=GetLayersBase()->GetGuiInitializer();
	for(GUIItemInstance *p=GD->GetGUIInstanceRoot()->NPListPack<GUIItemInstance>::GetFirst();p!=NULL;p=p->GetNext()){
		p->Handle->EditMode=EditMode;
	}
}

void EditGUI::Global_SettingFunc()
{
	GeneralDialog	D(NULL,new WEditParameterTab(GetParamGlobal(),-1,NULL),NULL);
	D.exec();
}

void EditGUI::Communication_SettingFunc()
{
	//GeneralDialog	D(NULL,new FormCommSetting(GetLayersBase()),NULL);
	//D.exec();
	CommDialogForm	D(GetLayersBase(),NULL);
	D.exec();
}

void EditGUI::Scanning_settingFunc()
{
	GeneralDialog	D(NULL,new FormScanStrategy(GetLayersBase()),NULL);
	D.exec();
}

void EditGUI::Save_settingFunc()
{
	QString	 fileName=QFileDialog::getSaveFileName ( NULL, GetParamComm()->GetDataText()
													, QString()
													, GetParamComm()->GetDefaultFileName()+QString(/**/";;dat(*.dat);;AllFile(*.*)"));
	if(fileName.isEmpty()==false){
		QFile	F(fileName);
		if(F.open(QIODevice::WriteOnly)==true){
			GetParamComm()->SaveParam(&F);
		}
	}
}
void EditGUI::OutlineOffsetFunc()
{
	GeneralDialog	D(NULL,new EditOutlineOffset(GetLayersBase(),NULL),NULL);
	D.exec();
}

void EditGUI::SaveGlobalParamFunc()
{
	QString	 fileName=QFileDialog::getSaveFileName ( NULL, GetParamGlobal()->GetDataText()
													, QString()
													, GetParamGlobal()->GetDefaultFileName()+QString(/**/";;dat(*.dat);;AllFile(*.*)"));
	if(fileName.isEmpty()==false){
		QFile	F(fileName);
		if(F.open(QIODevice::WriteOnly)==true){
			GetParamGlobal()->SaveParam(&F);
		}
	}
}

void EditGUI::closeEvent ( QCloseEvent * event )
{
	if(QMessageBox::warning ( NULL
							, "Confirmation"
							, "Do you really want to exit?"
							, QMessageBox::Yes, QMessageBox::No)==QMessageBox::Yes){
		event->accept();
		QCoreApplication::instance()->quit();
	}
	else{
		event->ignore();
	}
}
void EditGUI::EditFilterFunc()
{
	EditFilterBank	*Q=new EditFilterBank(GetLayersBase(),NULL);
	GeneralDialog	Dlg(NULL,Q,NULL);
	Dlg.exec();
}

void EditGUI::EditSyncGUIFileFunc()
{
	EditSyncGUIForm	*D=new EditSyncGUIForm(GetLayersBase());
	GeneralDialog	Dlg(NULL,D,NULL);
	Dlg.exec();
}

void EditGUI::SearchFunc()
{
	SearchDialog	*D=new SearchDialog(GetLayersBase());
	D->exec();
	delete	D;
}

void EditGUI::ExitFunc()
{
	close();
}

void EditGUI::Snap_to_gridFunc()
{
	GUIInitializer	*GD	=GetLayersBase()->GetGuiInitializer();
	if(GD->GetGridUnitForEditMode()>1){
		Snap2GridButton->setChecked(false);
		GD->SetGridUnitForEditMode(1);
	}
	else{
		Snap2GridButton->setChecked(true);
		GD->SetGridUnitForEditMode(8);
	}
}

void	EditGUI::EditPhaseFunc()
{
	EditPhaseForm	*Q=new EditPhaseForm(GetLayersBase(),NULL);
	GeneralDialog	Dlg(NULL,Q,NULL);
	Dlg.exec();
}


void EditGUI::on_actionImage_direction_on_each_page_triggered()
{
	FormDirectionOnEachPage	*Q=new FormDirectionOnEachPage(GetLayersBase(),NULL);
	GeneralDialog	Dlg(NULL,Q,NULL);
	Dlg.exec();
}
void EditGUI::on_actionCopy_triggered()
{
	QBuffer	Buff;

	Buff.open(QIODevice::WriteOnly);

	GUIInitializer	*GD	=GetLayersBase()->GetGuiInitializer();
	int32	N=0;
	for(GUIInstancePack *p=GD->GUIInstanceRoot.GetFirst();p!=NULL;p=p->GetNext()){
		for(GUIItemInstance *g=p->NPListPack<GUIItemInstance>::GetFirst();g!=NULL;g=g->GetNext()){
			if(g->Handle!=NULL && g->Handle->GetSelectedInEditMode()==true){
				N++;
			}
		}
	}
	::Save(&Buff,N);
	for(GUIInstancePack *p=GD->GUIInstanceRoot.GetFirst();p!=NULL;p=p->GetNext()){
		for(GUIItemInstance *g=p->NPListPack<GUIItemInstance>::GetFirst();g!=NULL;g=g->GetNext()){
			if(g->Handle!=NULL && g->Handle->GetSelectedInEditMode()==true){
				g->SaveInstance(&Buff);
			}
		}
	}
	ClipboardBuffer=Buff.buffer();
}

void EditGUI::on_actionPaste_triggered()
{
	GUIInitializer	*GD	=GetLayersBase()->GetGuiInitializer();
	GUIFormBase	*ParentInst=MainProperty->PutTop;
	if(ParentInst==NULL)
		return;
	NPListPack<GUIItemInstancePointer>	GUIItemInstancePointerContainer;
	QBuffer	Buff(&ClipboardBuffer);
	if(Buff.open(QIODevice::ReadOnly)==true){
		int32	N;
		if(::Load(&Buff,N)==false)
			return;
		QString	ErrorStr;
		DWORD	ErrorCode;
		for(int i=0;i<N;i++){
			GUIItemInstance	*k=new GUIItemInstance(GD->GetGUIInstanceRoot());
			if(k->LoadInstance(&Buff,ErrorStr)==false)
				return;
			k->Initial(GetLayersBase(),ParentInst,ErrorCode , k->DLLAccess);
			k->InitialInPaste(10,10);
			k->Handle->setParent(ParentInst);
			GUIItemInstancePointerContainer.AppendList(new GUIItemInstancePointer(k));
		}
	}
	ReleaseSelected();

	if(ParentInst!=NULL){
		for(GUIItemInstancePointer *k=GUIItemInstancePointerContainer.GetFirst();k!=NULL;k=k->GetNext()){
			GD->GetGUIInstanceRoot()->AppendList(k->Pointer);
			k->Pointer->Handle->SetSelectedInEditMode(true);
			k->Pointer->Handle->show();
			k->Pointer->Handle->update();
		}
	}
}

void EditGUI::ReleaseSelected(void)
{
	GUIInitializer	*GD	=GetLayersBase()->GetGuiInitializer();
	for(GUIInstancePack *p=GD->GUIInstanceRoot.GetFirst();p!=NULL;p=p->GetNext()){
		for(GUIItemInstance *g=p->NPListPack<GUIItemInstance>::GetFirst();g!=NULL;g=g->GetNext()){
			g->Handle->SetSelectedInEditMode(false);
		}
	}
}

void EditGUI::on_actionAlign_left_triggered()
{
	GUIInitializer	*GD	=GetLayersBase()->GetGuiInitializer();
	int	LeftPos=99999999;
	for(GUIInstancePack *p=GD->GUIInstanceRoot.GetFirst();p!=NULL;p=p->GetNext()){
		for(GUIItemInstance *g=p->NPListPack<GUIItemInstance>::GetFirst();g!=NULL;g=g->GetNext()){
			if(g->Handle!=NULL && g->Handle->GetSelectedInEditMode()==true){
				LeftPos=min(LeftPos,g->GUIPositionX1);
			}
		}
	}
	for(GUIInstancePack *p=GD->GUIInstanceRoot.GetFirst();p!=NULL;p=p->GetNext()){
		for(GUIItemInstance *g=p->NPListPack<GUIItemInstance>::GetFirst();g!=NULL;g=g->GetNext()){
			if(g->Handle!=NULL && g->Handle->GetSelectedInEditMode()==true){
				g->GUIPositionX1	= LeftPos;
				g->Handle->move(g->GUIPositionX1,g->GUIPositionY1);
			}
		}
	}
}

void EditGUI::on_actionAlign_top_triggered()
{
	GUIInitializer	*GD	=GetLayersBase()->GetGuiInitializer();
	int	TopPos=99999999;
	for(GUIInstancePack *p=GD->GUIInstanceRoot.GetFirst();p!=NULL;p=p->GetNext()){
		for(GUIItemInstance *g=p->NPListPack<GUIItemInstance>::GetFirst();g!=NULL;g=g->GetNext()){
			if(g->Handle!=NULL && g->Handle->GetSelectedInEditMode()==true){
				TopPos=min(TopPos,g->GUIPositionY1);
			}
		}
	}
	for(GUIInstancePack *p=GD->GUIInstanceRoot.GetFirst();p!=NULL;p=p->GetNext()){
		for(GUIItemInstance *g=p->NPListPack<GUIItemInstance>::GetFirst();g!=NULL;g=g->GetNext()){
			if(g->Handle!=NULL && g->Handle->GetSelectedInEditMode()==true){
				g->GUIPositionY1	= TopPos;
				g->Handle->move(g->GUIPositionX1,g->GUIPositionY1);
			}
		}
	}
}

void EditGUI::on_actionAlign_same_width_triggered()
{
	GUIInitializer	*GD	=GetLayersBase()->GetGuiInitializer();
	int	LeftPos	= 99999999;
	int	RightPos=-99999999;
	for(GUIInstancePack *p=GD->GUIInstanceRoot.GetFirst();p!=NULL;p=p->GetNext()){
		for(GUIItemInstance *g=p->NPListPack<GUIItemInstance>::GetFirst();g!=NULL;g=g->GetNext()){
			if(g->Handle!=NULL && g->Handle->GetSelectedInEditMode()==true){
				LeftPos=min(LeftPos,g->GUIPositionX1);
				RightPos=max(RightPos,g->GUIPositionX2);
			}
		}
	}
	for(GUIInstancePack *p=GD->GUIInstanceRoot.GetFirst();p!=NULL;p=p->GetNext()){
		for(GUIItemInstance *g=p->NPListPack<GUIItemInstance>::GetFirst();g!=NULL;g=g->GetNext()){
			if(g->Handle!=NULL && g->Handle->GetSelectedInEditMode()==true){
				g->GUIPositionX2	=RightPos;
				g->GUIPositionX1	=LeftPos;
				g->Handle->move  (g->GUIPositionX1,g->GUIPositionY1);
				g->Handle->resize(g->GUIPositionX2-g->GUIPositionX1+1 ,g->GUIPositionY2-g->GUIPositionY1+1);
			}
		}
	}
}

void EditGUI::on_actionAlign_same_height_triggered()
{
	GUIInitializer	*GD	=GetLayersBase()->GetGuiInitializer();
	int	TopPos		= 99999999;
	int	BottomPos	=-99999999;
	for(GUIInstancePack *p=GD->GUIInstanceRoot.GetFirst();p!=NULL;p=p->GetNext()){
		for(GUIItemInstance *g=p->NPListPack<GUIItemInstance>::GetFirst();g!=NULL;g=g->GetNext()){
			if(g->Handle!=NULL && g->Handle->GetSelectedInEditMode()==true){
				TopPos		=min(TopPos		,g->GUIPositionY1);
				BottomPos	=max(BottomPos	,g->GUIPositionY2);
			}
		}
	}
	for(GUIInstancePack *p=GD->GUIInstanceRoot.GetFirst();p!=NULL;p=p->GetNext()){
		for(GUIItemInstance *g=p->NPListPack<GUIItemInstance>::GetFirst();g!=NULL;g=g->GetNext()){
			if(g->Handle!=NULL && g->Handle->GetSelectedInEditMode()==true){
				g->GUIPositionY2	=BottomPos;
				g->GUIPositionY1	=TopPos;
				g->Handle->move  (g->GUIPositionX1,g->GUIPositionY1);
				g->Handle->resize(g->GUIPositionX2-g->GUIPositionX1+1 ,g->GUIPositionY2-g->GUIPositionY1+1);
			}
		}
	}
}

void EditGUI::on_actionAlign_right_triggered()
{
	GUIInitializer	*GD	=GetLayersBase()->GetGuiInitializer();
	int	RightPos=-99999999;
	for(GUIInstancePack *p=GD->GUIInstanceRoot.GetFirst();p!=NULL;p=p->GetNext()){
		for(GUIItemInstance *g=p->NPListPack<GUIItemInstance>::GetFirst();g!=NULL;g=g->GetNext()){
			if(g->Handle!=NULL && g->Handle->GetSelectedInEditMode()==true){
				RightPos=max(RightPos,g->GUIPositionX2);
			}
		}
	}
	for(GUIInstancePack *p=GD->GUIInstanceRoot.GetFirst();p!=NULL;p=p->GetNext()){
		for(GUIItemInstance *g=p->NPListPack<GUIItemInstance>::GetFirst();g!=NULL;g=g->GetNext()){
			if(g->Handle!=NULL && g->Handle->GetSelectedInEditMode()==true){
				int	dx=RightPos-g->GUIPositionX2;
				g->GUIPositionX2	= RightPos;
				g->GUIPositionX1	+=dx;
				g->Handle->move(g->GUIPositionX1,g->GUIPositionY1);
			}
		}
	}
}

void EditGUI::on_actionAlign_bottom_triggered()
{
	GUIInitializer	*GD	=GetLayersBase()->GetGuiInitializer();
	int	BottomPos=-99999999;
	for(GUIInstancePack *p=GD->GUIInstanceRoot.GetFirst();p!=NULL;p=p->GetNext()){
		for(GUIItemInstance *g=p->NPListPack<GUIItemInstance>::GetFirst();g!=NULL;g=g->GetNext()){
			if(g->Handle!=NULL && g->Handle->GetSelectedInEditMode()==true){
				BottomPos=max(BottomPos,g->GUIPositionY2);
			}
		}
	}
	for(GUIInstancePack *p=GD->GUIInstanceRoot.GetFirst();p!=NULL;p=p->GetNext()){
		for(GUIItemInstance *g=p->NPListPack<GUIItemInstance>::GetFirst();g!=NULL;g=g->GetNext()){
			if(g->Handle!=NULL && g->Handle->GetSelectedInEditMode()==true){
				int	dy=BottomPos-g->GUIPositionY1;
				g->GUIPositionY2	= BottomPos;
				g->GUIPositionY1	+=dy;
				g->Handle->move(g->GUIPositionX1,g->GUIPositionY1);
			}
		}
	}
}


static	int	SortByX(const void *a ,const void *b)
{
	GUIItemInstancePointer	*pa=((GUIItemInstancePointer **)a)[0];
	GUIItemInstancePointer	*pb=((GUIItemInstancePointer **)b)[0];
	return pa->Pointer->GUIPositionX1 - pb->Pointer->GUIPositionX1;
}

static	int	SortByY(const void *a ,const void *b)
{
	GUIItemInstancePointer	*pa=((GUIItemInstancePointer **)a)[0];
	GUIItemInstancePointer	*pb=((GUIItemInstancePointer **)b)[0];
	return pa->Pointer->GUIPositionY1 - pb->Pointer->GUIPositionY1;
}


void EditGUI::on_actionAlign_horizontal_same_gap_triggered()
{
	GUIInitializer	*GD	=GetLayersBase()->GetGuiInitializer();
	int	LeftPos	= 99999999;
	int	RightPos=-99999999;
	int	N=0;
	NPListPack<GUIItemInstancePointer>	GUIItemInstancePointerContainer;
	int	GapTotal=0;
	for(GUIInstancePack *p=GD->GUIInstanceRoot.GetFirst();p!=NULL;p=p->GetNext()){
		for(GUIItemInstance *g=p->NPListPack<GUIItemInstance>::GetFirst();g!=NULL;g=g->GetNext()){
			if(g->Handle!=NULL && g->Handle->GetSelectedInEditMode()==true){
				LeftPos=min(LeftPos,g->GUIPositionX1);
				RightPos=max(RightPos,g->GUIPositionX2);
				GapTotal	+=g->GUIPositionX2-g->GUIPositionX1+1;
				GUIItemInstancePointerContainer.AppendList(new GUIItemInstancePointer(g));
				N++;
			}
		}
	}
	if(N<=1)
		return;
	int	Gap=(RightPos-LeftPos+1-GapTotal)/(N-1);
	GUIItemInstancePointerContainer.Sort(SortByX);
	int	X=GUIItemInstancePointerContainer.GetFirst()->Pointer->GUIPositionX1;
	for(GUIItemInstancePointer *k=GUIItemInstancePointerContainer.GetFirst();k!=NULL;k=k->GetNext()){
		int	dx=X-k->Pointer->GUIPositionX1;
		k->Pointer->GUIPositionX1+=dx;
		k->Pointer->GUIPositionX2+=dx;
		k->Pointer->Handle->move(k->Pointer->GUIPositionX1,k->Pointer->GUIPositionY1);
		X+=k->Pointer->GUIPositionX2 - k->Pointer->GUIPositionX1+1+Gap;
	}
}

void EditGUI::on_actionAlign_vertical_same_gap_triggered()
{
	GUIInitializer	*GD	=GetLayersBase()->GetGuiInitializer();
	int	TopPos	= 99999999;
	int	BottomPos=-99999999;
	int	GapTotal=0;
	int	N=0;
	NPListPack<GUIItemInstancePointer>	GUIItemInstancePointerContainer;

	for(GUIInstancePack *p=GD->GUIInstanceRoot.GetFirst();p!=NULL;p=p->GetNext()){
		for(GUIItemInstance *g=p->NPListPack<GUIItemInstance>::GetFirst();g!=NULL;g=g->GetNext()){
			if(g->Handle!=NULL && g->Handle->GetSelectedInEditMode()==true){
				TopPos		=min(TopPos		,g->GUIPositionY1);
				BottomPos	=max(BottomPos	,g->GUIPositionY2);
				GapTotal	+=g->GUIPositionY2-g->GUIPositionY1+1;
				GUIItemInstancePointerContainer.AppendList(new GUIItemInstancePointer(g));
				N++;
			}
		}
	}
	if(N<=1)
		return;
	int	Gap=(BottomPos - TopPos+1-GapTotal)/(N-1);
	GUIItemInstancePointerContainer.Sort(SortByY);
	int	Y=GUIItemInstancePointerContainer.GetFirst()->Pointer->GUIPositionY1;
	for(GUIItemInstancePointer *k=GUIItemInstancePointerContainer.GetFirst();k!=NULL;k=k->GetNext()){
		int	dy=Y-k->Pointer->GUIPositionY1;
		k->Pointer->GUIPositionY1+=dy;
		k->Pointer->GUIPositionY2+=dy;
		k->Pointer->Handle->move(k->Pointer->GUIPositionX1,k->Pointer->GUIPositionY1);
		Y+=k->Pointer->GUIPositionY2 - k->Pointer->GUIPositionY1+1+Gap;
	}
}

void EditGUI::on_actionDelete_Selected_components_triggered()
{
	GUIInitializer	*GD	=GetLayersBase()->GetGuiInitializer();
	NPListPack<GUIItemInstancePointer>	GUIItemInstancePointerContainer;
	for(GUIInstancePack *p=GD->GUIInstanceRoot.GetFirst();p!=NULL;p=p->GetNext()){
		for(GUIItemInstance *g=p->NPListPack<GUIItemInstance>::GetFirst();g!=NULL;g=g->GetNext()){
			if(g->Handle!=NULL && g->Handle->GetSelectedInEditMode()==true){
				GUIItemInstancePointerContainer.AppendList(new GUIItemInstancePointer(g));
			}
		}
	}
	for(GUIItemInstancePointer *k=GUIItemInstancePointerContainer.GetFirst();k!=NULL;k=k->GetNext()){
		for(GUIInstancePack *p=GD->GUIInstanceRoot.GetFirst();p!=NULL;p=p->GetNext()){
			p->NPListPack<GUIItemInstance>::RemoveList(k->Pointer);
		}
		delete	k->Pointer;
	}
}

void EditGUI::Make_BAT_fileFunc()
{
	CopyBATDialog	D(this,GetLayersBase(), NULL);
	D.exec();

}
void EditGUI::on_actionMake_status_Def_fike_triggered()
{
	QString FileName=QFileDialog::getSaveFileName ( 0, QString("Save Comment file")
												,"CommentDef.dat"
												,/**/"Opinion (*.dat);;All files (*.*)");
	if(FileName.isNull()==false){
		GetLayersBase()->GetStatusController()->SaveDef(FileName);
	}
}

void EditGUI::on_actionMake_GUILanguage_file_triggered()
{
	MakeLanguageDialog	D(GetLayersBase());
	D.exec();
}


void EditGUI::on_actionEdit_order_triggered()
{
	EditOrderDialog	D(GetLayersBase());
	D.exec();
}

