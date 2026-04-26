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

	bool	ExecuteSave			(QString &iMasterName,QString &tRemark);
	bool	ExecuteSaveSilent	(QString &iMasterName,QString &tRemark,QString &ErrorMessageOfFalse);
	int		ExecuteSearch		(QString &iMasterName);
	bool	ExecuteUpdate		(QString &tMasterName ,QString &tRemark);

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