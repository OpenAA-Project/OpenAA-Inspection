/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonSaveMasterData\SaveMasterDataWindow.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef SAVEMASTERDATAWINDOW_H
#define SAVEMASTERDATAWINDOW_H

#include <QWidget>
#include "ui_SaveMasterDataWindow.h"
#include "MasterCategoryForm.h"
#include <QSqlTableModel>
#include <QTableView>
#include "XServiceForLayers.h"

class	ButtonSaveMasterData;

class	QSqlSaveMasterModel : public QSqlTableModel
{
public:
	QSqlSaveMasterModel(QObject * parent, QSqlDatabase db);
	QString selectStatement () const;
};


class SaveMasterDataWindow : public QWidget ,public ServiceForLayers
{
	Q_OBJECT

	ButtonSaveMasterData	*ParentGUI;
public:
	SaveMasterDataWindow(LayersBase *Base ,const QString &emitterRoot,const QString &emitterName,QWidget *parent = 0);
	~SaveMasterDataWindow();

	bool	ExecuteSave		 (QString &iMasterName,QString &tRemark);
	bool	ExecuteSaveSilent(QString &iMasterName,QString &tRemark,QString &ErrorMessageOfFalse);
	int		ExecuteSearch(QString &iMasterName);

	QString EmitterRoot;
	QString EmitterName;
	bool	SyncCount;

private:
	Ui::SaveMasterDataWindowClass ui;
	MasterCategoryForm	*MasterCategory;
	QTableView *MListView;

	bool	CheckDupName(QString iMasterName);
signals:
	void	SignalClose();

private slots:
	void on_ButtonCancel_clicked();
	void on_ButtonSaveNew_clicked();
	void	SlotSelectCategory(int CategoryID ,QString FolderName ,QString Remark);

};

#endif // SAVEMASTERDATAWINDOW_H
