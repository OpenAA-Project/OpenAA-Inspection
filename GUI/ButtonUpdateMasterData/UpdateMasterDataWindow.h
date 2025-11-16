/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonUpdateMasterData\UpdateMasterDataWindow.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef UPDATEMASTERDATAWINDOW_H
#define UPDATEMASTERDATAWINDOW_H

#include <QWidget>
#include "ui_UpdateMasterDataWindow.h"
#include "MasterCategoryForm.h"
#include <QSqlTableModel>
#include <QTableView>
#include "XServiceForLayers.h"

class	QSqlUpdateMasterModel : public QSqlTableModel
{
public:
	QSqlUpdateMasterModel(QObject * parent, QSqlDatabase db);
	QString selectStatement () const;
};

class	ButtonUpdateMasterData;

class UpdateMasterDataWindow : public QWidget,public ServiceForLayers
{
	Q_OBJECT

	ButtonUpdateMasterData	*ParentGUI;
	bool	UpdateGeneralSetting;
public:
	UpdateMasterDataWindow(LayersBase *Base,const QString &emitterRoot,const QString &emitterName
							,bool UpdateGeneralSetting ,QWidget *parent = 0);
	~UpdateMasterDataWindow();

	bool	ExecuteUpdate		(QString &tMasterName ,QString &Remark);
	bool	ExecuteUpdateSilent	(QString &tMasterName ,QString &Remark ,QString &ErrorMessageOfFalse);
	QString EmitterRoot;
	QString EmitterName;

	bool	SyncCount;

private:
	Ui::UpdateMasterDataWindowClass ui;
	MasterCategoryForm	*MasterCategory;
	QTableView *MListView;
signals:
	void	SignalClose();

private slots:
	void on_ButtonCancel_clicked();
	void on_ButtonUpdate_clicked();
	void	SlotSelectCategory(int CategoryID ,QString FolderName ,QString Remark);
};

#endif // UPDATEMASTERDATAWINDOW_H
