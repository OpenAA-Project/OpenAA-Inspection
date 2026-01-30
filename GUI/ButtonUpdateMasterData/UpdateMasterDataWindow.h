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