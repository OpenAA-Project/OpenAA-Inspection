#include "ButtonLoadMasterDataWithoutMachineResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonLoadMasterDataWithoutMachine\LoadMasterDataWindow.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

//#include "ButtonLoadMasterDataResource.h"
#include "LoadMasterDataWindow.h"
#include "MasterCategoryForm.h"
#include "XDLLOnly.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include "ButtonSelectLot.h"
#include "ButtonSelectMachine.h"
#include "XGeneralFunc.h"
#include "ButtonLoadMasterDataWithoutMachine.h"
#include "XDatabaseLoader.h"
#include "SelectMachineDialog.h"
#include "XFileRegistry.h"
#include "ThreadSequence.h"
#include "XSequenceLocal.h"
#include "XExecuteInspectBase.h"
#include "ShowLoadedInfoForm.h"
#include "XGeneralDialog.h"
#include "ButtonAutoMode.h"
#include "XSyncGUI.h"
#include "XParamDatabase.h"
#include <QMessageBox>
#include "XEntryPoint.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

static	int	CategoryID;

QSqlLoadMasterModel::QSqlLoadMasterModel(QObject * parent, QSqlDatabase db)
:QSqlTableModel(parent, db)
{
	ParentWindow	=dynamic_cast<LoadMasterDataWindow *>(parent);
}
QString QSqlLoadMasterModel::selectStatement () const
{
	QString	ret;

	switch(ParentWindow->ListMode){
		case LoadMasterDataWindow::_IDNormal:
			if(CategoryID==-1){
				ret=QString(/**/"SELECT MASTERDATA.MASTERCODE")
					+QString(/**/",MACHINE.NAME")
					+QString(/**/",MASTERDATA.REGTIME")
					+QString(/**/",MASTERDATA.LASTEDITTIME")
					+QString(/**/",MASTERDATA.MASTERNAME")
					+QString(/**/",MASTERDATA.REMARK")
					+QString(/**/" FROM MASTERDATA,MACHINE WHERE MACHINE.MACHINEID=MASTERDATA.MACHINEID and MASTERDATA.MASTERCODE>=")
					+QString::number(ParentWindow->StartSearchID)
					+ParentWindow->GetAdditionalMachines()
					+QString(/**/" ORDER BY MASTERDATA.MASTERCODE;");
			}
			else{
				ret=QString(/**/"SELECT MASTERDATA.MASTERCODE")
					+QString(/**/",MACHINE.NAME")
					+QString(/**/",MASTERDATA.REGTIME")
					+QString(/**/",MASTERDATA.LASTEDITTIME")
					+QString(/**/",MASTERDATA.MASTERNAME")
					+QString(/**/",MASTERDATA.REMARK")
					+QString(/**/" FROM MASTERDATA,MACHINE WHERE MACHINE.MACHINEID=MASTERDATA.MACHINEID and MASTERDATA.MASTERCODE>=")
					+QString::number(ParentWindow->StartSearchID)
					+QString(/**/" AND MASTERDATA.CATEGORYID=")
					+QString::number(CategoryID)
					+ParentWindow->GetAdditionalMachines()
					+QString(/**/" ORDER BY MASTERDATA.MASTERCODE;");
			}
			break;
		case LoadMasterDataWindow::_IDReverse:
			if(ParentWindow->StartSearchID!=0){
				if(CategoryID==-1){
					ret=QString(/**/"SELECT MASTERDATA.MASTERCODE")
						+QString(/**/",MACHINE.NAME")
						+QString(/**/",MASTERDATA.REGTIME")
						+QString(/**/",MASTERDATA.LASTEDITTIME")
						+QString(/**/",MASTERDATA.MASTERNAME")
						+QString(/**/",MASTERDATA.REMARK")
						+QString(/**/" FROM MASTERDATA,MACHINE WHERE MACHINE.MACHINEID=MASTERDATA.MACHINEID and MASTERDATA.MASTERCODE<=")
						+QString::number(ParentWindow->StartSearchID)
						+ParentWindow->GetAdditionalMachines()
						+QString(/**/" ORDER BY MASTERDATA.MASTERCODE DESC;");
				}
				else{
					ret=QString(/**/"SELECT MASTERDATA.MASTERCODE")
						+QString(/**/",MACHINE.NAME")
						+QString(/**/",MASTERDATA.REGTIME")
						+QString(/**/",MASTERDATA.LASTEDITTIME")
						+QString(/**/",MASTERDATA.MASTERNAME")
						+QString(/**/",MASTERDATA.REMARK")
						+QString(/**/" FROM MASTERDATA,MACHINE WHERE MACHINE.MACHINEID=MASTERDATA.MACHINEID and MASTERDATA.MASTERCODE<=")
						+QString::number(ParentWindow->StartSearchID)
						+QString(/**/" AND MASTERDATA.CATEGORYID=")
						+QString::number(CategoryID)
						+ParentWindow->GetAdditionalMachines()
						+QString(/**/" ORDER BY MASTERDATA.MASTERCODE DESC;");
				}
			}
			else{
				if(CategoryID==-1){
					ret=QString(/**/"SELECT MASTERDATA.MASTERCODE")
						+QString(/**/",MACHINE.NAME")
						+QString(/**/",MASTERDATA.REGTIME")
						+QString(/**/",MASTERDATA.LASTEDITTIME")
						+QString(/**/",MASTERDATA.MASTERNAME")
						+QString(/**/",MASTERDATA.REMARK")
						+QString(/**/" FROM MASTERDATA,MACHINE WHERE MACHINE.MACHINEID=MASTERDATA.MACHINEID")
						+ParentWindow->GetAdditionalMachines()
						+QString(/**/" ORDER BY MASTERDATA.MASTERCODE DESC;");
				}
				else{
					ret=QString(/**/"SELECT MASTERDATA.MASTERCODE")
						+QString(/**/",MACHINE.NAME")
						+QString(/**/",MASTERDATA.REGTIME")
						+QString(/**/",MASTERDATA.LASTEDITTIME")
						+QString(/**/",MASTERDATA.MASTERNAME")
						+QString(/**/",MASTERDATA.REMARK")
						+QString(/**/" FROM MASTERDATA,MACHINE ")
						+QString(/**/" WHERE MACHINE.MACHINEID=MASTERDATA.MACHINEID and MASTERDATA.CATEGORYID=")
						+QString::number(CategoryID)
						+ParentWindow->GetAdditionalMachines()
						+QString(/**/" ORDER BY MASTERDATA.MASTERCODE DESC;");
				}
			}
			break;
		case LoadMasterDataWindow::_TimeNormal:
			if(CategoryID==-1){
				ret=QString(/**/"SELECT MASTERDATA.MASTERCODE")
					+QString(/**/",MACHINE.NAME")
					+QString(/**/",MASTERDATA.REGTIME")
					+QString(/**/",MASTERDATA.LASTEDITTIME")
					+QString(/**/",MASTERDATA.MASTERNAME")
					+QString(/**/",MASTERDATA.REMARK")
					+QString(/**/" FROM MASTERDATA,MACHINE WHERE MACHINE.MACHINEID=MASTERDATA.MACHINEID")
					+ParentWindow->GetAdditionalMachines()
					+QString(/**/" ORDER BY MASTERDATA.REGTIME;");
			}
			else{
				ret=QString(/**/"SELECT MASTERDATA.MASTERCODE")
					+QString(/**/",MACHINE.NAME")
					+QString(/**/",MASTERDATA.REGTIME")
					+QString(/**/",MASTERDATA.LASTEDITTIME")
					+QString(/**/",MASTERDATA.MASTERNAME")
					+QString(/**/",MASTERDATA.REMARK")
					+QString(/**/" FROM MASTERDATA,MACHINE WHERE MACHINE.MACHINEID=MASTERDATA.MACHINEID and MASTERDATA.CATEGORYID=")
					+QString::number(CategoryID)
					+ParentWindow->GetAdditionalMachines()
					+QString(/**/" ORDER BY MASTERDATA.REGTIME;");
			}
			break;
		case LoadMasterDataWindow::_TimeReverse:
			if(CategoryID==-1){
				ret=QString(/**/"SELECT MASTERDATA.MASTERCODE")
					+QString(/**/",MACHINE.NAME")
					+QString(/**/",MASTERDATA.REGTIME")
					+QString(/**/",MASTERDATA.LASTEDITTIME")
					+QString(/**/",MASTERDATA.MASTERNAME")
					+QString(/**/",MASTERDATA.REMARK")
					+QString(/**/" FROM MASTERDATA,MACHINE WHERE MACHINE.MACHINEID=MASTERDATA.MACHINEID")
					+ParentWindow->GetAdditionalMachines()
					+QString(/**/" ORDER BY MASTERDATA.REGTIME DESC;");
			}
			else{
				ret=QString(/**/"SELECT MASTERDATA.MASTERCODE")
					+QString(/**/",MACHINE.NAME")
					+QString(/**/",MASTERDATA.REGTIME")
					+QString(/**/",MASTERDATA.LASTEDITTIME")
					+QString(/**/",MASTERDATA.MASTERNAME")
					+QString(/**/",MASTERDATA.REMARK")
					+QString(/**/" FROM MASTERDATA,MACHINE WHERE MACHINE.MACHINEID=MASTERDATA.MACHINEID and MASTERDATA.CATEGORYID=")
					+ParentWindow->GetAdditionalMachines()
					+QString::number(CategoryID)
					+QString(/**/" ORDER BY MASTERDATA.REGTIME DESC;");
			}
			break;
		case LoadMasterDataWindow::_NameNormal:
			if(CategoryID==-1){
				ret=QString(/**/"SELECT MASTERDATA.MASTERCODE")
					+QString(/**/",MACHINE.NAME")
					+QString(/**/",MASTERDATA.REGTIME")
					+QString(/**/",MASTERDATA.LASTEDITTIME")
					+QString(/**/",MASTERDATA.MASTERNAME")
					+QString(/**/",MASTERDATA.REMARK")
					+QString(/**/" FROM MASTERDATA,MACHINE WHERE MACHINE.MACHINEID=MASTERDATA.MACHINEID and MASTERDATA.MASTERNAME>=")
					+QString(/**/"\'")+ParentWindow->StartSearchName+QString(/**/"\' ")
					+ParentWindow->GetAdditionalMachines()
					+QString(/**/" ORDER BY MASTERDATA.MASTERNAME;");
			}
			else{
				ret=QString(/**/"SELECT MASTERDATA.MASTERCODE")
					+QString(/**/",MACHINE.NAME")
					+QString(/**/",MASTERDATA.REGTIME")
					+QString(/**/",MASTERDATA.LASTEDITTIME")
					+QString(/**/",MASTERDATA.MASTERNAME")
					+QString(/**/",MASTERDATA.REMARK")
					+QString(/**/" FROM MASTERDATA,MACHINE WHERE MACHINE.MACHINEID=MASTERDATA.MACHINEID and MASTERDATA.CATEGORYID=")
					+QString::number(CategoryID)
					+QString(/**/" and MASTERDATA.MASTERNAME>=")+QString(/**/"\'")+ParentWindow->StartSearchName+QString(/**/"\' ")
					+ParentWindow->GetAdditionalMachines()
					+QString(/**/" ORDER BY MASTERDATA.MASTERNAME;");
			}
			break;
		case LoadMasterDataWindow::_NameReverse:
			if(CategoryID==-1){
				ret=QString(/**/"SELECT MASTERDATA.MASTERCODE")
					+QString(/**/",MACHINE.NAME")
					+QString(/**/",MASTERDATA.REGTIME")
					+QString(/**/",MASTERDATA.LASTEDITTIME")
					+QString(/**/",MASTERDATA.MASTERNAME")
					+QString(/**/",MASTERDATA.REMARK")
					+QString(/**/" FROM MASTERDATA,MACHINE WHERE MACHINE.MACHINEID=MASTERDATA.MACHINEID and MASTERDATA.MASTERNAME>=")
					+QString(/**/"\'")+ParentWindow->StartSearchName+QString(/**/"\' ")
					+ParentWindow->GetAdditionalMachines()
					+QString(/**/" ORDER BY MASTERDATA.MASTERNAME DESC;");
			}
			else{
				ret=QString(/**/"SELECT MASTERDATA.MASTERCODE")
					+QString(/**/",MACHINE.NAME")
					+QString(/**/",MASTERDATA.REGTIME")
					+QString(/**/",MASTERDATA.LASTEDITTIME")
					+QString(/**/",MASTERDATA.MASTERNAME")
					+QString(/**/",MASTERDATA.REMARK")
					+QString(/**/" FROM MASTERDATA,MACHINE WHERE MACHINE.MACHINEID=MASTERDATA.MACHINEID and MASTERDATA.CATEGORYID=")
					+QString::number(CategoryID)
					+QString(/**/" and MASTERDATA.MASTERNAME>=")+QString(/**/"\'")+ParentWindow->StartSearchName+QString(/**/"\' ")
					+ParentWindow->GetAdditionalMachines()
					+QString(/**/" ORDER BY MASTERDATA.MASTERNAME DESC;");
			}
			break;
		case LoadMasterDataWindow::_LastEditNormal:
			if(CategoryID==-1){
				ret=QString(/**/"SELECT MASTERDATA.MASTERCODE")
					+QString(/**/",MACHINE.NAME")
					+QString(/**/",MASTERDATA.REGTIME")
					+QString(/**/",MASTERDATA.LASTEDITTIME")
					+QString(/**/",MASTERDATA.MASTERNAME")
					+QString(/**/",MASTERDATA.REMARK")
					+QString(/**/" FROM MASTERDATA,MACHINE WHERE MACHINE.MACHINEID=MASTERDATA.MACHINEID")
					+ParentWindow->GetAdditionalMachines()
					+QString(/**/" ORDER BY MASTERDATA.LASTEDITTIME;");
			}
			else{
				ret=QString(/**/"SELECT MASTERDATA.MASTERCODE")
					+QString(/**/",MACHINE.NAME")
					+QString(/**/",MASTERDATA.REGTIME")
					+QString(/**/",MASTERDATA.LASTEDITTIME")
					+QString(/**/",MASTERDATA.MASTERNAME")
					+QString(/**/",MASTERDATA.REMARK")
					+QString(/**/" FROM MASTERDATA,MACHINE WHERE MACHINE.MACHINEID=MASTERDATA.MACHINEID and MASTERDATA.CATEGORYID=")
					+QString::number(CategoryID)
					+ParentWindow->GetAdditionalMachines()
					+QString(/**/" ORDER BY MASTERDATA.LASTEDITTIME;");
			}
			break;
		case LoadMasterDataWindow::_LastEditReverse:
			if(CategoryID==-1){
				ret=QString(/**/"SELECT MASTERDATA.MASTERCODE")
					+QString(/**/",MACHINE.NAME")
					+QString(/**/",MASTERDATA.REGTIME")
					+QString(/**/",MASTERDATA.LASTEDITTIME")
					+QString(/**/",MASTERDATA.MASTERNAME")
					+QString(/**/",MASTERDATA.REMARK")
					+QString(/**/" FROM MASTERDATA,MACHINE WHERE MACHINE.MACHINEID=MASTERDATA.MACHINEID")
					+ParentWindow->GetAdditionalMachines()
					+QString(/**/" ORDER BY MASTERDATA.LASTEDITTIME DESC;");
			}
			else{
				ret=QString(/**/"SELECT MASTERDATA.MASTERCODE")
					+QString(/**/",MACHINE.NAME")
					+QString(/**/",MASTERDATA.REGTIME")
					+QString(/**/",MASTERDATA.LASTEDITTIME")
					+QString(/**/",MASTERDATA.MASTERNAME")
					+QString(/**/",MASTERDATA.REMARK")
					+QString(/**/" FROM MASTERDATA,MACHINE WHERE MACHINE.MACHINEID=MASTERDATA.MACHINEID and MASTERDATA.CATEGORYID=")
					+QString::number(CategoryID)
					+ParentWindow->GetAdditionalMachines()
					+QString(/**/" ORDER BY MASTERDATA.LASTEDITTIME DESC;");
			}
			break;
	}
	return ret;
}
//=========================================================================================

LoadMasterDataWindow::LoadMasterDataWindow(LayersBase *Base,const QString &emitterRoot,const QString &emitterName,QWidget *parent)
	: QWidget(parent),ServiceForLayers(Base)
{
	ui.setupUi(this);
	//LangSolver.SetUI(this);
	LogoInQWidget(Base,this,sRoot ,sName);
	ParentGUI=dynamic_cast<ButtonLoadMasterDataWithoutMachine *>(parent);

	if(GetLayersBase()->GetSyncGUIData()->GetConnectedCount()!=0){
		SyncCount=true;
	}
	else{
		SyncCount=false;
	}
	RetMode	=false;

	MListView=NULL;
	ListMode=_NameNormal;
	StartSearchID=0;

	EmitterRoot	=emitterRoot;
	EmitterName =emitterName;
	CategoryID=-1;
	MasterCategory=new MasterCategoryForm(GetLayersBase(),ui.frameCategory);
	connect(MasterCategory,SIGNAL(SelectCategory(int,QString,QString)),this,SLOT(SlotSelectCategory(int,QString,QString)));

	QSqlLoadMasterModel *MModel = new QSqlLoadMasterModel(this,GetLayersBase()->GetDatabase());
	MModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
	MModel->select();
	MModel->removeColumn(0); // don't show the ID

	MListView = new QTableView(ui.frameGrid);
	MListView->setModel(MModel);
	MListView->setObjectName(/**/"MListView");
	MListView->move(0,0);
	MListView->resize(ui.frameGrid->width(),ui.frameGrid->height());
	MListView->setColumnWidth (0, 90);
	MListView->setColumnWidth (1, 100);
	MListView->setColumnWidth (2, 120);
	MListView->setColumnWidth (3, 120);
	MListView->setColumnWidth (4, 220);
	MListView->setColumnWidth (5, 160);
	MListView->setSelectionMode(QAbstractItemView::SingleSelection);
	MListView->setSelectionBehavior(QAbstractItemView::SelectRows);
	MListView->setObjectName(/**/"SelectMasterDataListView");
	MListView->show();
	connect(MListView ,SIGNAL(clicked(const QModelIndex &)),this,SLOT(SlotClicked(const QModelIndex &)));
	connect(MListView ,SIGNAL(doubleClicked(const QModelIndex &)),this,SLOT(SlotDoubleClicked(const QModelIndex &)));
	
	ShowListHeader();
	connect(MListView->horizontalHeader() ,SIGNAL(sectionClicked (int)),this,SLOT(MListSectionClicked (int)));

	ui.ButtonLoad->setEnabled(false);
	InstallOperationLog(this);
}

LoadMasterDataWindow::~LoadMasterDataWindow()
{

}

void	LoadMasterDataWindow::RefreshGrid(void)
{
	if(MListView!=NULL){
		QSqlLoadMasterModel	*M=dynamic_cast<QSqlLoadMasterModel	 *>(MListView->model());
		if(M!=NULL){
			M->select();
		}
	}
}

void	LoadMasterDataWindow::ShowListHeader(void)
{
	//QSqlLoadMasterModel *MModel = new QSqlLoadMasterModel(this,GetLayersBase()->GetDatabase());
	QSqlLoadMasterModel *MModel = (QSqlLoadMasterModel*)(MListView->model());
	QString	MasterCodeStr	=LangSolver.GetString(LoadMasterDataWindow_LS,LID_8)/*"MasterCode"*/;
	QString	MachineNameStr	=LangSolver.GetString(LoadMasterDataWindow_LS,LID_9)/*"Machine"*/;
	QString	RegTimeStr		=LangSolver.GetString(LoadMasterDataWindow_LS,LID_10)/*"RegTime"*/;
	QString	LastEditStr		=LangSolver.GetString(LoadMasterDataWindow_LS,LID_11)/*"Last Edit"*/;
	QString	NameStr			=LangSolver.GetString(LoadMasterDataWindow_LS,LID_12)/*"Name"*/;
	QString	RemarkStr		=LangSolver.GetString(LoadMasterDataWindow_LS,LID_13)/*"Remark"*/;
	switch(ListMode){
		case  _IDNormal:
			MasterCodeStr=MasterCodeStr+LangSolver.GetString(LoadMasterDataWindow_LS,LID_14)/*"Up"*/;
			ui.lineEditState->setText(LangSolver.GetString(LoadMasterDataWindow_LS,LID_15)/*"MasterCode ->"*/);
			break;
		case  _IDReverse:
			MasterCodeStr=MasterCodeStr+LangSolver.GetString(LoadMasterDataWindow_LS,LID_16)/*"Down"*/;
			ui.lineEditState->setText(LangSolver.GetString(LoadMasterDataWindow_LS,LID_17)/*"MasterCode <-"*/);
			break;
		case  _TimeNormal:
			RegTimeStr	=RegTimeStr+LangSolver.GetString(LoadMasterDataWindow_LS,LID_18)/*"Up"*/;
			ui.lineEditState->setText(LangSolver.GetString(LoadMasterDataWindow_LS,LID_19)/*"RegTime ->"*/);
			break;
		case  _TimeReverse:
			RegTimeStr	=RegTimeStr+LangSolver.GetString(LoadMasterDataWindow_LS,LID_20)/*"Down"*/;
			ui.lineEditState->setText(LangSolver.GetString(LoadMasterDataWindow_LS,LID_21)/*"RegTime <-"*/);
			break;
		case  _NameNormal:
			NameStr		=NameStr+LangSolver.GetString(LoadMasterDataWindow_LS,LID_22)/*"Up"*/;
			ui.lineEditState->setText(LangSolver.GetString(LoadMasterDataWindow_LS,LID_23)/*"MasterName ->"*/);
			break;
		case  _NameReverse:
			NameStr		=NameStr+LangSolver.GetString(LoadMasterDataWindow_LS,LID_24)/*"Down"*/;
			ui.lineEditState->setText(LangSolver.GetString(LoadMasterDataWindow_LS,LID_25)/*"MasterName <-"*/);
			break;
		case  _LastEditNormal:
			LastEditStr	=LastEditStr+QString(/**/"Up");
			ui.lineEditState->setText(LangSolver.GetString(LoadMasterDataWindow_LS,LID_26)/*"LastEdit ->"*/);
			break;
		case  _LastEditReverse:
			LastEditStr	=LastEditStr+QString(/**/"Down");
			ui.lineEditState->setText(LangSolver.GetString(LoadMasterDataWindow_LS,LID_27)/*"LastEdit <-"*/);
			break;
	}
	MModel->setHeaderData(0, Qt::Horizontal, MasterCodeStr	,Qt::DisplayRole);
	MModel->setHeaderData(1, Qt::Horizontal, MachineNameStr	,Qt::DisplayRole);
	MModel->setHeaderData(2, Qt::Horizontal, RegTimeStr		,Qt::DisplayRole);
	MModel->setHeaderData(3, Qt::Horizontal, LastEditStr	,Qt::DisplayRole);
	MModel->setHeaderData(4, Qt::Horizontal, NameStr		,Qt::DisplayRole);
	MModel->setHeaderData(5, Qt::Horizontal, RemarkStr		,Qt::DisplayRole);
}


void	LoadMasterDataWindow::SlotSelectCategory(int _CategoryID ,QString FolderName ,QString Remark)
{
	::CategoryID=_CategoryID;

	QSqlLoadMasterModel	*M=dynamic_cast<QSqlLoadMasterModel	 *>(MListView->model());
	ListMode=_IDNormal;
	ShowListHeader();
	if(M!=NULL)
		M->select();
}

QString	LoadMasterDataWindow::GetAdditionalMachines(void)
{
	int	N=0;
	for(int i=0;i<ParentGUI->IncludedMachines.count();i++){
		if(ParentGUI->IncludedMachines[i].isEmpty()==false){
			N++;
		}
	}
	if(N>0){
		QString	Str=/**/" And (";
		int	k=0;
		for(int i=0;i<ParentGUI->IncludedMachines.count();i++){
			if(ParentGUI->IncludedMachines[i].isEmpty()==false){
				if(k!=0){
					Str+=QString(/**/" or ");
				}
				Str+=QString(/**/"MASTERDATA.MACHINEID=") + ParentGUI->IncludedMachines[i];
				k++;
			}
			Str+=/**/" ";
		}
		Str+=/**/") ";
		return Str;
	}
	return /**/"";
}

void LoadMasterDataWindow::on_ButtonLoad_clicked()
{
	bool	ok;

	SelectView();

	if(SyncCount==true){
		if(QMessageBox::question(NULL,LangSolver.GetString(LoadMasterDataWindow_LS,LID_28)/*"Synchronized"*/
									,LangSolver.GetString(LoadMasterDataWindow_LS,LID_29)/*"Load others?"*/
									,QMessageBox::Yes,QMessageBox::No)==QMessageBox::No){
			SyncCount=false;
		}
	}
	int	RelationCode=-1;
	RelationMasterList MasterListDim[100];
	int	MasterListDimCount=0;

	bool	ModeLoadMasterImage=true;
	int		DotPerLine	=GetLayersBase()->GetDotPerLine(-1);
	int		MaxLines	=GetLayersBase()->GetMaxLines(-1);
	int		PageNumb	=GetLayersBase()->GetPageNumb();
	int		MasterCode=ui.EditMasterCode->text().toInt(&ok);
	if(ParentGUI->iOnLoading!=NULL){
		ParentGUI->iOnLoading->Set(true);
	}
	if(ok==true){
		if(ParentGUI->ShowSelectToLoadImage==true){
			if(QMessageBox::question(NULL,LangSolver.GetString(LoadMasterDataWindow_LS,LID_30)/*"Select"*/
										,LangSolver.GetString(LoadMasterDataWindow_LS,LID_31)/*"Do you load master image?"*/
										,QMessageBox::Yes
										,QMessageBox::No)==QMessageBox::No){
				ModeLoadMasterImage=false;
			}
		}

		GetLayersBase()->SetCurrentPhase(0);
		GetLayersBase()->WaitAllAcknowledged(1);
		GetLayersBase()->ClearAllAckFlag(1);
		GetLayersBase()->ShowProcessingForm (LangSolver.GetString(LoadMasterDataWindow_LS,LID_32)/*"Loading master data"*/);

		bool	EditMaltipleMachine=GetLayersBase()->GetFRegistry()->LoadRegBool(/**/"EditMaltipleMachine",0);
		int	SelectedMachineID=-1;
		if(EditMaltipleMachine==false){
			IntList MachineList;
			GetLayersBase()->GetDulicatedData(MasterCode ,MachineList);
			if(MachineList.GetCount()>1){
				GetLayersBase()->TmpHideProcessingForm();
				SelectMachineDialog	SelectMac(GetLayersBase(),MachineList,this);
				if(SelectMac.exec()==(int)false){
					GetLayersBase()->TmpRercoverProcessingForm();
					if(ParentGUI->iOnLoading!=NULL){
						ParentGUI->iOnLoading->Set(false);
					}
					return;
				}
				GetLayersBase()->TmpRercoverProcessingForm();
				SelectedMachineID=SelectMac.SelectedMachineID;
			}
		}

		if(SyncCount==true){
			RelationCode=GetLayersBase()->SQLGetRelationCode(MasterCode);
			if(RelationCode!=-1){
				MasterListDimCount=GetLayersBase()->SQLSearchMasterCode(RelationCode ,MasterListDim ,100);
			}
			QBuffer	Buff;
			Buff.open(QIODevice::ReadWrite);
			int	N=0;
			for(int i=0;i<MasterListDimCount;i++){
				if(MasterListDim[i].MasterCode!=MasterCode){
					N++;
				}
			}
			::Save(&Buff,N);
			for(int i=0;i<MasterListDimCount;i++){
				if(MasterListDim[i].MasterCode!=MasterCode){
					::Save(&Buff,MasterListDim[i].MasterCode);
					::Save(&Buff,MasterListDim[i].MachineID);
				}
			}
			::Save(&Buff,ModeLoadMasterImage);
			ParentGUI->TxSync(Buff.buffer());
		}

		if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL){
			SeqControlParam	*Param=(SeqControlParam *)GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetSeqParam();
			if(Param!=NULL){
				Param->LoadedMasterData=true;
			}
		}
		bool CriticalErrorOccured=false;
		QString ErrorMessageOfFalse;
		GetLayersBase()->ClearAllAckFlag(1);
		if(GetLayersBase()->SQLLoadMasterData(MasterCode,SelectedMachineID,ModeLoadMasterImage
											,CriticalErrorOccured
											,ErrorMessageOfFalse)==false){
			if(CriticalErrorOccured==true){
				GetLayersBase()->CloseProcessingForm ();
				GetLayersBase()->WriteAllSettingFiles();
				GetLayersBase()->SendSettingsToSlave();
				QMessageBox::critical ( NULL, LangSolver.GetString(LoadMasterDataWindow_LS,LID_33)/*"Reboot"*/
											, LangSolver.GetString(LoadMasterDataWindow_LS,LID_34)/*"Reboot software to change critical items"*/
											, QMessageBox::Ok);
				GetLayersBase()->CloseAll();
				QCoreApplication::quit();	
				if(ParentGUI->iOnLoading!=NULL){
					ParentGUI->iOnLoading->Set(false);
				}
				return;
			}
			QMessageBox::critical(NULL,"Save Error",ErrorMessageOfFalse);
		}
		//_CrtCheckMemory();
	}
	else{
		if(ParentGUI->iOnLoading!=NULL){
			ParentGUI->iOnLoading->Set(false);
		}
		return;
	}
	GetLayersBase()->WaitAllAcknowledged(60*100);
	if(ParentGUI->InitializeAfterEdit==true){
		ExecuteInitialAfterEditInfo EInfo;
		EInfo.CalledInLoadMaster=true;
		GetLayersBase()->ExecuteInitialAfterEdit(EInfo);
	}
	GetLayersBase()->CloseProcessingForm ();
	QApplication::processEvents();
	
	if(GetLayersBase()->GetParamComm()->ConnectedPCNumb!=0){
		if(DotPerLine	!=GetLayersBase()->GetDotPerLine(-1)
		|| MaxLines		!=GetLayersBase()->GetMaxLines(-1)
		|| PageNumb		!=GetLayersBase()->GetPageNumb()){
			GetLayersBase()->WriteAllSettingFiles();
			GetLayersBase()->SendSettingsToSlave();
			QMessageBox::critical ( NULL, LangSolver.GetString(LoadMasterDataWindow_LS,LID_35)/*"Reboot"*/
										, LangSolver.GetString(LoadMasterDataWindow_LS,LID_36)/*"Reboot software to change critical items"*/
										, QMessageBox::Ok);
			GetLayersBase()->CloseAll();
			QCoreApplication::quit();	
			if(ParentGUI->iOnLoading!=NULL){
				ParentGUI->iOnLoading->Set(false);
			}
			return;
		}
	}

	if(ParentGUI!=NULL){
		if(ParentGUI->ReleaseAutoMode==true){
			GUIFormBase	*AGProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"AutoMode",/**/"");
			if(AGProp!=NULL){
				CmdSetStateOnAutoMode	AmCmd(GetLayersBase());
				AmCmd.AutoModeOn=false;
				AGProp->TransmitDirectly(&AmCmd);
			}
		}
		if(ParentGUI->ShowLoadedInfo==true){
			ShowLoadedInfoForm	*ShowLoadedInfo=new ShowLoadedInfoForm(GetLayersBase());
			//ShowLoadedInfo->show();
			//ShowLoadedInfo->update();
			//ShowLoadedInfo->activateWindow();
			GeneralDialog	*D=new GeneralDialog(GetLayersBase(),ShowLoadedInfo,GetLayersBase()->GetMainWidget());
			GetLayersBase()->CenterizeDialog(D);
			D->exec();
		}
	}
	//GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"SelectLot" ,/**/"");
	GUIFormBase	*GProp=GetLayersBase()->FindByName(ParentGUI->SelectLotSRoot ,ParentGUI->SelectLotSName ,/**/"");
	if(GProp!=NULL){
		CmdSelectLot	Cmd(GetLayersBase());
		GProp->TransmitDirectly(&Cmd);
	}
	GetLayersBase()->LoadOutlineOffsetForDatabase();
	GetLayersBase()->BroadcastMachineID();
	GetLayersBase()->DeliverOutlineOffset();

	GetLayersBase()->CloseInformed();

	if(ParentGUI!=NULL){
		LoadMasterSpecifiedBroadcaster	SData;
		ParentGUI->BroadcastSpecifiedDirectly(&SData);
	}

	if(ParentGUI!=NULL){
		if(ParentGUI->ReleaseAutoMode==false){
			GSleep(1000);
			GUIFormBase	*AGProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"AutoMode",/**/"");
			if(AGProp!=NULL){
				CmdSetStateOnAutoMode	AmCmd(GetLayersBase());
				AmCmd.AutoModeOn=true;
				AGProp->TransmitDirectly(&AmCmd);
			}
		}
	}
	RetMode	=true;
	emit	SignalClose();

	if(ParentGUI->iOnLoading!=NULL){
		ParentGUI->iOnLoading->Set(false);
	}
}

void LoadMasterDataWindow::on_ButtonCancel_clicked()
{
	emit	SignalClose();
}

void	LoadMasterDataWindow::SlotClicked(const QModelIndex &)
{
	SelectView();
	ui.ButtonLoad->setEnabled(true);
}
void	LoadMasterDataWindow::SlotDoubleClicked	(const QModelIndex &Index)
{
	on_ButtonLoad_clicked();
}
void	LoadMasterDataWindow::SelectView(void)
{
	QModelIndex Index=MListView->currentIndex();

	QSqlLoadMasterModel	*M=dynamic_cast<QSqlLoadMasterModel	 *>(MListView->model());
	if(M!=NULL){
		QModelIndex RIndex=Index.sibling ( Index.row(), 0);
		int	MasterCode=M->data(RIndex).toInt();
		ui.EditMasterCode->setText(QString::number(MasterCode));
		QString	S=QString(/**/"SELECT MASTERNAME,REMARK,TOPVIEW FROM MASTERDATA WHERE MASTERCODE=")
			+QString::number(MasterCode);
		QSqlQuery query(S ,GetLayersBase()->GetDatabase());
		if(query.next ()==false)
			return;

		QString	MasterName	=query.value(query.record().indexOf(/**/"MASTERNAME")).toString();
		QString	Remark		=query.value(query.record().indexOf(/**/"REMARK"	)).toString();
		QByteArray	TopVArray=query.value(query.record().indexOf(/**/"TOPVIEW"	)).toByteArray();
		ui.EditMasterName->setText(MasterName);
		ui.EditRemark	 ->setText(Remark);
		QPixmap		TopView;
		TopView.loadFromData(TopVArray,/**/"PNG");
		ui.labelTopView->setPixmap(TopView);
	}
}


void LoadMasterDataWindow::on_pushButtonStartSearchByName_clicked()
{
	StartSearchName=ui.lineEditSearchName->text();
	ListMode=_NameNormal;

	ShowListHeader();
	QSqlLoadMasterModel	*M=dynamic_cast<QSqlLoadMasterModel	 *>(MListView->model());
	if(M!=NULL)
		M->select();
}
void	LoadMasterDataWindow::MListSectionClicked ( int logicalIndex )
{
	switch(logicalIndex){
		case 0:
			if(ListMode==_IDNormal)
				ListMode=_IDReverse;
			else if(ListMode==_IDReverse)
				ListMode=_IDNormal;
			else
				ListMode=_IDNormal;
			break;
		case 2:
			if(ListMode==_TimeNormal)
				ListMode=_TimeReverse;
			else if(ListMode==_TimeReverse)
				ListMode=_TimeNormal;
			else
				ListMode=_TimeNormal;
			break;
		case 3:
			if(ListMode==_LastEditNormal)
				ListMode=_LastEditReverse;
			else if(ListMode==_LastEditReverse)
				ListMode=_LastEditNormal;
			else
				ListMode=_LastEditNormal;
			break;
		case 4:
			if(ListMode==_NameNormal)
				ListMode=_NameReverse;
			else if(ListMode==_NameReverse)
				ListMode=_NameNormal;
			else
				ListMode=_NameNormal;
			break;
	}
	ShowListHeader();
	QSqlLoadMasterModel	*M=dynamic_cast<QSqlLoadMasterModel	 *>(MListView->model());
	if(M!=NULL)
		M->select();
}


void LoadMasterDataWindow::on_pushButtonStartSearchByID_clicked()
{
	StartSearchID=ui.spinBoxSearchID->value();
	ListMode=_IDNormal;

	ShowListHeader();
	QSqlLoadMasterModel	*M=dynamic_cast<QSqlLoadMasterModel	 *>(MListView->model());
	if(M!=NULL)
		M->select();

}
