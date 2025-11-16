/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonUpdateMasterData\UpdateMasterDataWindow.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ButtonUpdateMasterDataResource.h"
#include "UpdateMasterDataWindow.h"
#include "MasterCategoryForm.h"
#include "XDLLOnly.h"
#include "ButtonUpdateMasterData.h"
#include "XGeneralFunc.h"
#include "SelectMachineDialog.h"
#include "XFileRegistry.h"
#include "SelectImagePathDialog.h"
#include <QMessageBox>
#include "XSyncGUI.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

static	int	CategoryID;

QSqlUpdateMasterModel::QSqlUpdateMasterModel(QObject * parent, QSqlDatabase db)
:QSqlTableModel(parent, db)
{
}
QString QSqlUpdateMasterModel::selectStatement () const
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

UpdateMasterDataWindow::UpdateMasterDataWindow(LayersBase *Base,const QString &emitterRoot,const QString &emitterName,bool _UpdateGeneralSetting ,QWidget *parent)
	: QWidget(parent),ServiceForLayers(Base)
{
	ui.setupUi(this);
	LangSolver.SetUI(this);
	LogoInQWidget(Base,this,sRoot ,sName);
	ParentGUI=(ButtonUpdateMasterData *)parent;
	UpdateGeneralSetting	=_UpdateGeneralSetting;

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

	ui.EditMasterCode->setText(QString::number(GetLayersBase()->GetMasterCode()));
	ui.EditMasterName->setText(GetLayersBase()->GetMasterName());
	ui.EditRemark	 ->setText(GetLayersBase()->GetRemark());

	QSqlUpdateMasterModel *MModel = new QSqlUpdateMasterModel(this,GetLayersBase()->GetDatabase());
	MModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
	MModel->select();
	MModel->removeColumn(0); // don't show the ID
	MModel->setHeaderData(0, Qt::Horizontal, LangSolver.GetString(UpdateMasterDataWindow_LS,LID_3)/*"MasterCode"*/);
	MModel->setHeaderData(1, Qt::Horizontal, LangSolver.GetString(UpdateMasterDataWindow_LS,LID_4)/*"RegTime"*/);
	MModel->setHeaderData(2, Qt::Horizontal, LangSolver.GetString(UpdateMasterDataWindow_LS,LID_5)/*"Name"*/);
	MModel->setHeaderData(3, Qt::Horizontal, LangSolver.GetString(UpdateMasterDataWindow_LS,LID_6)/*"Remark"*/);

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

UpdateMasterDataWindow::~UpdateMasterDataWindow()
{

}
void	UpdateMasterDataWindow::SlotSelectCategory(int _CategoryID ,QString FolderName ,QString Remark)
{
	::CategoryID=_CategoryID;

	QSqlUpdateMasterModel	*M=dynamic_cast<QSqlUpdateMasterModel *>(MListView->model());
	if(M!=NULL)
		M->select();
	
	//MListView->repaint();
}


void UpdateMasterDataWindow::on_ButtonUpdate_clicked()
{
	QString	tMasterName	=ui.EditMasterName->text();
	QString	tRemark		=ui.EditRemark->text();
	ExecuteUpdate(tMasterName,tRemark);
}

bool UpdateMasterDataWindow::ExecuteUpdate(QString &tMasterName ,QString &tRemark)
{
	if(GetLayersBase()->GetMasterCode()<0){
		QMessageBox::warning ( 0, LangSolver.GetString(UpdateMasterDataWindow_LS,LID_7)/*"Error"*/, LangSolver.GetString(UpdateMasterDataWindow_LS,LID_8)/*"?V?K?U?????d?s?A?A?-???3???"*/);
		return false;
	}
	if(SyncCount==true){
		if(QMessageBox::question(NULL,LangSolver.GetString(UpdateMasterDataWindow_LS,LID_11)/*"Synchronized"*/
									,LangSolver.GetString(UpdateMasterDataWindow_LS,LID_12)/*"‘¼•û‚à•Û‘¶‚µ‚Ü‚·‚©H"*/
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
	GetLayersBase()->SetCurrentPhase(0);
	bool	EditMaltipleMachine=GetLayersBase()->GetFRegistry()->LoadRegBool(/**/"EditMaltipleMachine",0);
	int	SelectedMachineID=GetLayersBase()->GetMachineID();
	if(EditMaltipleMachine==true){
		SelectedMachineID=GetLayersBase()->GetMachineIDFromMaster();
	}

	GetLayersBase()->SetMasterName(tMasterName);
	GetLayersBase()->SetRemark(tRemark);

	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm (LangSolver.GetString(UpdateMasterDataWindow_LS,LID_1)/*"Updating master data"*/);

	if(ParentGUI!=NULL){
		CreateUpdateMasterPreSpecifiedBroadcaster	SData;
		ParentGUI->BroadcastSpecifiedDirectly(&SData);
	}

	int		RelationCode=-1;
	if(SyncCount==true){
		if(GetLayersBase()->GetMasterCode()>=0){
				RelationCode=GetLayersBase()->SQLGetRelationCode(GetLayersBase()->GetMasterCode());
			if(RelationCode<0){
				int	ThresholdLevelID=GetLayersBase()->GetThresholdLevelID();
				RelationCode=GetLayersBase()->SQLCreateNewMasterRelation(/**/""
																		,GetLayersBase()->GetMasterName()
																		,GetLayersBase()->GetRemark()
																		,0
																		,ThresholdLevelID);
			}
		}

		QBuffer	Buff;
		Buff.open(QIODevice::ReadWrite);
		::Save(&Buff,RelationCode);
		::Save(&Buff,GetLayersBase()->GetMasterName());
		::Save(&Buff,GetLayersBase()->GetRemark());
		::Save(&Buff,ImagePath);
		ParentGUI->TxSync(Buff.buffer());
	}
	QString ErrorMessageOfFalse;
	if(GetLayersBase()->GetMasterCode()>=0){
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
			GetLayersBase()->SQLSetRelationOnMasterData(GetLayersBase()->GetMasterCode()
														,RelationCode ,GetLayersBase()->GetMachineID());
		}
		GetLayersBase()->CloseProcessingForm ();
		emit	SignalClose();
	}
	GetLayersBase()->SetEdited(false);
	return true;
}

bool UpdateMasterDataWindow::ExecuteUpdateSilent(QString &tMasterName ,QString &tRemark,QString &ErrorMessageOfFalse)
{		
	QStringList	ImagePathes=GetParamGlobal()->ImageFilePath.split(QChar(';'));
	QString		ImagePath;
	if(ImagePathes.count()>=1){
		ImagePath=ImagePathes[0];
	}
	else{
		ErrorMessageOfFalse="No image path";
		return false;
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
	GetLayersBase()->ShowProcessingForm (LangSolver.GetString(UpdateMasterDataWindow_LS,LID_1)/*"Updating master data"*/);

	if(ParentGUI!=NULL){
		CreateUpdateMasterPreSpecifiedBroadcaster	SData;
		ParentGUI->BroadcastSpecifiedDirectly(&SData);
	}

	//int		RelationCode=-1;

	if(GetLayersBase()->GetMasterCode()>=0){
		if(GetLayersBase()->SQLUpdateMasterData(SelectedMachineID,ImagePath,false
												,ErrorMessageOfFalse
												,UpdateGeneralSetting)==false){
			GetLayersBase()->CloseProcessingForm ();
			return false;
		}
		GetLayersBase()->WaitAllAcknowledged(60*10);
		
		if(ParentGUI!=NULL){
			CreateUpdateMasterSpecifiedBroadcaster	SData;
			ParentGUI->BroadcastSpecifiedDirectly(&SData);
		}
		GetLayersBase()->CloseProcessingForm ();
		emit	SignalClose();
	}
	GetLayersBase()->SetEdited(false);
	return true;
}
void UpdateMasterDataWindow::on_ButtonCancel_clicked()
{
	emit	SignalClose();
}
