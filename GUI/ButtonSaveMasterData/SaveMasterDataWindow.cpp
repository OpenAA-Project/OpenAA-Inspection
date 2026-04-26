/*
 * Copyright (C) 2023
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


#include "ButtonSaveMasterDataResource.h"
#include "SaveMasterDataWindow.h"
#include "MasterCategoryForm.h"
#include "XDLLOnly.h"
#include "XGeneralFunc.h"
#include "ButtonSaveMasterData.h"
#include "SelectMachineDialog.h"
#include "XFileRegistry.h"
#include "SelectImagePathDialog.h"
#include "XDataInLayer.h"
#include "XDatabaseLoader.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QMessageBox>
#include "XSyncGUI.h"
#include "SelectExecuteDialog.h"
#include "SelectMasterWithSameNameDialog.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

static	int	CategoryID;

QSqlSaveMasterModel::QSqlSaveMasterModel(QObject * parent, QSqlDatabase db)
:QSqlTableModel(parent, db)
{
}
QString QSqlSaveMasterModel::selectStatement () const
{
	QString	ret;
	if(CategoryID==-1){
		ret=QString(/**/"SELECT MASTERCODE,REGTIME,MASTERNAME,REMARK FROM MASTERDATA ORDER BY MASTERCODE;");
	}
	else{
		ret=QString(/**/"SELECT MASTERCODE,REGTIME,MASTERNAME,REMARK FROM MASTERDATA WHERE CATEGORYID=")
			+QString::number(CategoryID)
			+QString(/**/" ORDER BY MASTERCODE;");
	}
	return ret;
}


SaveMasterDataWindow::SaveMasterDataWindow(LayersBase *Base,const QString &emitterRoot,const QString &emitterName ,QWidget *parent)
	: QWidget(parent),ServiceForLayers(Base)
{
	ui.setupUi(this);
	LangSolver.SetUI(this);
	LogoInQWidget(Base,this,sRoot ,sName);
	ParentGUI=(ButtonSaveMasterData *)parent;

	if(GetLayersBase()->GetSyncGUIData()->GetConnectedCount()!=0){
		SyncCount=true;
	}
	else{
		SyncCount=false;
	}
	EmitterRoot	=emitterRoot;
	EmitterName =emitterName;
	CategoryID=-1;
	MasterCategory=new MasterCategoryForm(GetLayersBase(),ui.frameCategory);
	connect(MasterCategory,SIGNAL(SelectCategory(int,QString,QString)),this,SLOT(SlotSelectCategory(int,QString,QString)));

	QSqlSaveMasterModel *MModel = new QSqlSaveMasterModel(this,GetLayersBase()->GetDatabase());
	MModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
	MModel->select();
	MModel->removeColumn(0); // don't show the ID
	MModel->setHeaderData(0, Qt::Horizontal, LangSolver.GetString(SaveMasterDataWindow_LS,LID_3)/*"MasterCode"*/);
	MModel->setHeaderData(1, Qt::Horizontal, LangSolver.GetString(SaveMasterDataWindow_LS,LID_4)/*"RegTime"*/);
	MModel->setHeaderData(2, Qt::Horizontal, LangSolver.GetString(SaveMasterDataWindow_LS,LID_5)/*"Name"*/);
	MModel->setHeaderData(3, Qt::Horizontal, LangSolver.GetString(SaveMasterDataWindow_LS,LID_6)/*"Remark"*/);

	MListView = new QTableView(ui.frameGrid);
	MListView->setModel(MModel);
	MListView->move(0,0);
	MListView->resize(ui.frameGrid->width(),ui.frameGrid->height());
	MListView->setColumnWidth (0, 80);
	MListView->setColumnWidth (1, 160);
	MListView->setColumnWidth (2, 160);
	MListView->setColumnWidth (3, 160);
	MListView->setSelectionMode(QAbstractItemView::SingleSelection);
	MListView->setSelectionBehavior(QAbstractItemView::SelectRows);
	MListView->show();

	InstallOperationLog(this);
}

SaveMasterDataWindow::~SaveMasterDataWindow()
{
}

void	SaveMasterDataWindow::SlotSelectCategory(int _CategoryID ,QString FolderName ,QString Remark)
{
	::CategoryID=_CategoryID;

	QSqlSaveMasterModel	*M=dynamic_cast<QSqlSaveMasterModel	 *>(MListView->model());
	if(M!=NULL)
		M->select();
	
	//MListView->repaint();
}

bool	SaveMasterDataWindow::CheckDupName(QString iMasterName)
{
	IntList		RetMasterCodes;
	GetLayersBase()->GetDatabaseLoader()->G_SQLCheckMasterName(GetLayersBase()->GetDatabase()
		,  GetLayersBase()->GetMachineID()
		,iMasterName
		,RetMasterCodes);
	if(RetMasterCodes.IsEmpty()==true)
		return false;
	return true;
}

void SaveMasterDataWindow::on_ButtonSaveNew_clicked()
{
	QString	iMasterName	=ui.EditMasterName->text();
	QString	iRemark		=ui.EditRemark->text();
	ExecuteSave(iMasterName,iRemark);

	emit	SignalClose();
}

int		SaveMasterDataWindow::ExecuteSearch(QString &iMasterName)
{
	QString	str=QString(/**/"SELECT MASTERCODE FROM MASTERDATA where MASTERNAME=\'")
				+iMasterName
				+QString("\'");
	
	QSqlQuery query(str,*GetLayersBase()->GetDataBase());
	if(query.next ()==false){
		return -1;
	}

	int	MasterID	=query.value(query.record().indexOf("MASTERCODE")).toInt();
	return MasterID;
}

bool SaveMasterDataWindow::ExecuteSave(QString &iMasterName,QString &iRemark)
{
	if(ParentGUI->ModeCheckDupName==true && CheckDupName(iMasterName)==true){

		SelectExecuteDialog	D(GetLayersBase());
		D.exec();
		if(D.ResultCode==1){
		}
		else
		if(D.ResultCode==2){
			ExecuteUpdate(iMasterName,iRemark);
			GetLayersBase()->SetMasterCodeInTree(GetLayersBase()->GetMasterCode());
			GetLayersBase()->CloseProcessingForm();
			GetLayersBase()->SetEdited(false);
			return true;
		}
		else{
			//QMessageBox::question(NULL,LangSolver.GetString(SaveMasterDataWindow_LS,LID_12)/*"Duplicated"*/
			//							,LangSolver.GetString(SaveMasterDataWindow_LS,LID_13)/*"名前が重複しています"*/
			//							,QMessageBox::Ok);
			return false;
		}
	}

	int	RelationCode;
	if(SyncCount==true){
		if(QMessageBox::question(NULL,LangSolver.GetString(SaveMasterDataWindow_LS,LID_9)/*"Synchronized"*/
									,LangSolver.GetString(SaveMasterDataWindow_LS,LID_10)/*"他方も保存しますか？"*/
									,QMessageBox::Yes,QMessageBox::No)==QMessageBox::No){
			SyncCount=false;
		}
	}
	QStringList	ImagePathes=GetParamGlobal()->ImageFilePath.split(QChar(';'));
	QString		ImagePath;
	if(ImagePathes.count()==1)
		ImagePath=ImagePathes[0];
	else{
		SelectImagePathDialog	SelectImagePathD(ImagePathes);
		if(SelectImagePathD.exec()!=(int)true){
			return false;
		}
		ImagePath=SelectImagePathD.SelectedPath;
	}

	if(SyncCount==true){
		int32 ThresholdLevelID=GetLayersBase()->GetThresholdLevelID();
		RelationCode=GetLayersBase()->SQLCreateNewMasterRelation(/**/"",iMasterName,iRemark ,0,ThresholdLevelID);
	}

	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm(LangSolver.GetString(SaveMasterDataWindow_LS,LID_1)/*"Save-new master data"*/);
	GetLayersBase()->SetCurrentPhase(0);

	if(ParentGUI!=NULL){
		CreateNewMasterPreSpecifiedBroadcaster	SData;
		ParentGUI->BroadcastSpecifiedDirectly(&SData);
	}

	if(SyncCount==true){
		QBuffer	Buff;
		Buff.open(QIODevice::ReadWrite);
		::Save(&Buff,RelationCode);
		::Save(&Buff,iMasterName);
		::Save(&Buff,iRemark);
		::Save(&Buff,MasterCategory->SelectedCategoryID);
		::Save(&Buff,ImagePath);
		ParentGUI->TxSync(Buff.buffer());
	}
	GetLayersBase()->SetEdited(true);
	QString ErrorMessageOfFalse;
	if(GetLayersBase()->SQLSaveNewMasterData(iMasterName,iRemark
										//ui.EditMasterName->text()
										// ,ui.EditRemark->text() 
										 ,MasterCategory->SelectedCategoryID
										 ,ImagePath
										,ErrorMessageOfFalse)==false){
		GetLayersBase()->CloseProcessingForm();
		QMessageBox::critical(NULL,"Save Error",ErrorMessageOfFalse);
		return false;
	}

	GetLayersBase()->WaitAllAcknowledged(60*10);
	if(ParentGUI!=NULL){
		CreateNewMasterSpecifiedBroadcaster	SData;
		ParentGUI->BroadcastSpecifiedDirectly(&SData);
	}

	if(SyncCount==true){
		if(GetLayersBase()->SQLSetRelationOnMasterData(GetLayersBase()->GetMasterCode()
													,RelationCode ,GetLayersBase()->GetMachineID())==false){
			GetLayersBase()->CloseProcessingForm();
			QMessageBox::critical(NULL,"Save Error","SetRelationOnMasterData");
			return false;
		}
	}
	GetLayersBase()->SetMasterCodeInTree(GetLayersBase()->GetMasterCode());
	GetLayersBase()->CloseProcessingForm();
	GetLayersBase()->SetEdited(false);
	return true;
}


bool SaveMasterDataWindow::ExecuteUpdate(QString &tMasterName ,QString &tRemark)
{
	int	MachineID=GetLayersBase()->GetMachineID();
	IntList		RetMasterCodes;
	bool	Ret=GetLayersBase()->GetDatabaseLoader()->G_SQLCheckMasterName(GetLayersBase()->GetDatabase()
							,MachineID
							,tMasterName
							,RetMasterCodes);
	if(RetMasterCodes.GetCount()==0){
		return false;
	}
	int	MasterCode=RetMasterCodes[0];

	if(RetMasterCodes.GetCount()>1){
		SelectMasterWithSameNameDialog	D(RetMasterCodes ,GetLayersBase());
		int	Ret=D.exec();
		if(Ret==true){
			MasterCode=D.SelectedMasterCode;
		}
		else{
			return false;
		}
	}
		
	QStringList	ImagePathes=GetParamGlobal()->ImageFilePath.split(QChar(';'));
	QString		ImagePath;
	if(ImagePathes.count()==1)
		ImagePath=ImagePathes[0];
	else{
		SelectImagePathDialog	SelectImagePathD(ImagePathes);
		if(SelectImagePathD.exec()!=(int)true){
			return false;
		}
		ImagePath=SelectImagePathD.SelectedPath;
	}
	GetLayersBase()->SetCurrentPhase(0);
	bool	EditMaltipleMachine=GetLayersBase()->GetFRegistry()->LoadRegBool(/**/"EditMaltipleMachine",0);
	int	SelectedMachineID=GetLayersBase()->GetMachineID();
	if(EditMaltipleMachine==true){
		SelectedMachineID=GetLayersBase()->GetMachineIDFromMaster();
	}

	GetLayersBase()->SetMasterName(tMasterName);
	GetLayersBase()->SetRemark(tRemark);

	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm ("Updating master data");

	if(ParentGUI!=NULL){
		CreateUpdateMasterPreSpecifiedBroadcaster	SData;
		ParentGUI->BroadcastSpecifiedDirectly(&SData);
	}

	int		RelationCode=-1;
	if(SyncCount==true){
		if(MasterCode>=0){
			RelationCode=GetLayersBase()->SQLGetRelationCode(MasterCode);
			if(RelationCode<0){
				int	ThresholdLevelID=GetLayersBase()->GetThresholdLevelID();
				RelationCode=GetLayersBase()->SQLCreateNewMasterRelation(/**/""
																		,tMasterName
																		,tRemark
																		,0
																		,ThresholdLevelID);
			}
		}

		QBuffer	Buff;
		Buff.open(QIODevice::ReadWrite);
		::Save(&Buff,RelationCode);
		::Save(&Buff,tMasterName);
		::Save(&Buff,tRemark);
		::Save(&Buff,ImagePath);
		ParentGUI->TxSync(Buff.buffer());
	}
	QString ErrorMessageOfFalse;
	if(MasterCode>=0){
		bool	UpdateGeneralSetting=true;
		if(GetLayersBase()->SQLUpdateMasterData(SelectedMachineID,ImagePath,false
												,ErrorMessageOfFalse
												,UpdateGeneralSetting)==false){
			GetLayersBase()->CloseProcessingForm ();
			QMessageBox::critical(NULL,"Update Error",ErrorMessageOfFalse);
		}
		GetLayersBase()->WaitAllAcknowledged(60*10);
		
		if(ParentGUI!=NULL){
			CreateUpdateMasterSpecifiedBroadcaster	SData;
			ParentGUI->BroadcastSpecifiedDirectly(&SData);
		}
		if(SyncCount==true){
			GetLayersBase()->SQLSetRelationOnMasterData(MasterCode
														,RelationCode ,GetLayersBase()->GetMachineID());
		}
		GetLayersBase()->CloseProcessingForm ();
		emit	SignalClose();
	}
	GetLayersBase()->SetEdited(false);
	return true;
}

bool SaveMasterDataWindow::ExecuteSaveSilent(QString &iMasterName,QString &iRemark,QString &ErrorMessageOfFalse)
{
	if(ParentGUI->ModeCheckDupName==true && CheckDupName(iMasterName)==true){
		ErrorMessageOfFalse="Duplicate master name";
		return false;
	}

	//int	RelationCode=-1;
	QStringList	ImagePathes=GetParamGlobal()->ImageFilePath.split(QChar(';'));
	QString		ImagePath;
	if(ImagePathes.count()>0){
		ImagePath=ImagePathes[0];
	}
	else{
		ErrorMessageOfFalse="No image path";
		return false;
	}

	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm(LangSolver.GetString(SaveMasterDataWindow_LS,LID_1)/*"Save-new master data"*/);
	GetLayersBase()->SetCurrentPhase(0);

	if(ParentGUI!=NULL){
		CreateNewMasterPreSpecifiedBroadcaster	SData;
		ParentGUI->BroadcastSpecifiedDirectly(&SData);
	}
	GetLayersBase()->SetEdited(true);
	if(GetLayersBase()->SQLSaveNewMasterData(iMasterName,iRemark
										//ui.EditMasterName->text()
										// ,ui.EditRemark->text() 
										 ,MasterCategory->SelectedCategoryID
										 ,ImagePath
										,ErrorMessageOfFalse)==false){
		GetLayersBase()->CloseProcessingForm();
		return false;
	}

	GetLayersBase()->WaitAllAcknowledged(60*10);
	if(ParentGUI!=NULL){
		CreateNewMasterSpecifiedBroadcaster	SData;
		ParentGUI->BroadcastSpecifiedDirectly(&SData);
	}

	GetLayersBase()->CloseProcessingForm();
	GetLayersBase()->SetEdited(false);
	return true;
}
void SaveMasterDataWindow::on_ButtonCancel_clicked()
{
	emit	SignalClose();
	//close();
}