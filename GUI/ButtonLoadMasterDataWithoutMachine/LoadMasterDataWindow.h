/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonLoadMasterData\LoadMasterDataWindow.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef LOADMASTERDATAWINDOW_H
#define LOADMASTERDATAWINDOW_H

#include <QWidget>
#include "ui_LoadMasterDataWindow.h"
#include "MasterCategoryForm.h"
#include <QSqlTableModel>
#include <QTableView>
#include "XServiceForLayers.h"
#include "NList.h"

class LoadMasterDataWindow;
class	QSqlLoadMasterModel : public QSqlTableModel
{
	LoadMasterDataWindow	*ParentWindow;
public:
	QSqlLoadMasterModel(QObject * parent, QSqlDatabase db);
	QString selectStatement () const;
};


class	ButtonLoadMasterDataWithoutMachine;

class LoadMasterDataWindow : public QWidget ,public ServiceForLayers
{
	Q_OBJECT
	friend class	QSqlLoadMasterModel;

	ButtonLoadMasterDataWithoutMachine	*ParentGUI;
	QFrame					ScrollFrame;
public:
	LoadMasterDataWindow(LayersBase *Base ,const QString &emitterRoot,const QString &emitterName,QWidget *parent = 0);
	~LoadMasterDataWindow();

	QString EmitterRoot;
	QString EmitterName;
	bool	SyncCount;
	bool	RetMode;

	void	RefreshGrid(void);
	QString	GetAdditionalMachines(void);

private:
	Ui::LoadMasterDataWindowClass ui;
	MasterCategoryForm	*MasterCategory;
	QTableView *MListView;

	enum	_ListMode{
		_IDNormal
		,_IDReverse
		,_TimeNormal
		,_TimeReverse
		,_NameNormal
		,_NameReverse
		,_LastEditNormal
		,_LastEditReverse
	}ListMode;
	QString	StartSearchName;
	int		StartSearchID;
	void	ShowListHeader(void);
	void	SelectView(void);

signals:
	void	SignalClose();

private slots:
	void on_pushButtonStartSearchByID_clicked();
	void on_pushButtonStartSearchByName_clicked();
	void on_ButtonCancel_clicked();
	void on_ButtonLoad_clicked();
	void	SlotClicked		(const QModelIndex &Index);
	void	SlotDoubleClicked	(const QModelIndex &Index);
	void	SlotSelectCategory(int CategoryID ,QString FolderName ,QString Remark);
	
	void	MListSectionClicked ( int logicalIndex );
};

#endif // LOADMASTERDATAWINDOW_H
