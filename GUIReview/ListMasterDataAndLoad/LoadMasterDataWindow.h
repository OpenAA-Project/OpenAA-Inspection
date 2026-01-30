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


#ifndef LOADMASTERDATAWINDOW_H
#define LOADMASTERDATAWINDOW_H

#include <QWidget>
#include "ui_LoadMasterDataWindow.h"
#include "MasterCategoryForm.h"
#include <QSqlTableModel>
#include <QTableView>
#include "XServiceForLayers.h"
#include "NList.h"
#include <QToolButton>

class LoadMasterDataWindow;
class	QSqlLoadMasterModel : public QSqlTableModel
{
	LoadMasterDataWindow	*ParentWindow;
public:
	QSqlLoadMasterModel(QObject * parent, QSqlDatabase db);
	QString selectStatement () const;
};

class	MachineButton : public QToolButton ,public NPList<MachineButton>
{
    Q_OBJECT
public:
	int MachineID;
	LoadMasterDataWindow	*ParentWindow;

	MachineButton(int _MachineID ,LoadMasterDataWindow *ParentWindow ,QWidget *parent);

private slots:
	void	ToggleButton(bool mode);
};


class	MachineList : public NPList<MachineList>
{
public:
	int		MachineID;
	QString	NetID;
	QString	Version;
	QString	Name;
	QString	Remark;
};

class	ButtonLoadMasterData;

class LoadMasterDataWindow : public QWidget ,public ServiceForLayers
{
	Q_OBJECT
	friend class	QSqlLoadMasterModel;

	ButtonLoadMasterData	*ParentGUI;
	QFrame					ScrollFrame;
public:
	LoadMasterDataWindow(LayersBase *Base ,const QString &emitterRoot,const QString &emitterName,QWidget *parent = 0);
	~LoadMasterDataWindow();

	QString EmitterRoot;
	QString EmitterName;
	int		SelectedMasterCode;

	NPListPack<MachineList>		MachineContainer;
	NPListPack<MachineButton>	MachineButtonContainer;

	void	RefreshGrid(void);
	QString	MakeMachineSQL(void);
	bool	isAccepted(){ return accept; };
	int		currentMachineID();

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
	bool	accept;
	void	ShowListHeader(void);
	void	SelectView(void);
	void	LoadMachineList(void);

signals:
	void	SignalClose();

private slots:
	void on_pushButtonStartSearchByID_clicked();
	void on_pushButtonStartSearchByName_clicked();
	void on_ButtonCancel_clicked();
	void on_ButtonLoad_clicked();
	void	SlotClicked		(const QModelIndex &Index);
	void	SlotSelectCategory(int CategoryID ,QString FolderName ,QString Remark);
	
	void	MListSectionClicked ( int logicalIndex );
};

#endif // LOADMASTERDATAWINDOW_H