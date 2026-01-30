/*
 * Copyright (C) 2021
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

#ifndef SELECTMASTERFORM_H
#define SELECTMASTERFORM_H

#include <QWidget>
#include "ui_SelectMasterForm.h"
#include "MasterCategoryForm.h"
#include <QSqlTableModel>
#include <QTableView>
#include <QModelIndex>
#include <QSqlDatabase>
#include "XServiceForLayers.h"
#include "XTypeDef.h"
#include "XGUIPacketForDLL.h"

class SelectMasterForm;

class	QSqlSelectMasterModel : public QSqlTableModel
{
	SelectMasterForm	*ParentWindow;
public:
	QSqlSelectMasterModel(QObject * parent, QSqlDatabase db);
	QString selectStatement () const;
};

class SelectMasterForm : public QWidget ,public ServiceForLayers
{
	Q_OBJECT
	friend class	QSqlSelectMasterModel;

public:
	SelectMasterForm(LayersBase *Base ,const QString &emitterRoot,const QString &emitterName,QWidget *parent = 0);
	~SelectMasterForm();

	QString EmitterRoot;
	QString EmitterName;

private:
	Ui::SelectMasterFormClass ui;
	MasterCategoryForm	*MasterCategory;
	QTableView *MListView;

	enum	_ListMode{
		_IDNormal
		,_IDReverse
		,_TimeNormal
		,_TimeReverse
		,_NameNormal
		,_NameReverse
	}ListMode;
	QString	StartSearchName;
	int		StartSearchID;
	void	ShowListHeader(void);
	void	SelectView(void);

	QString	MasterName;
	QString	Remark;

signals:
	void	SignalClose();

private slots:
	void on_pushButtonStartSearchByName_clicked();
	void on_pushButtonStartSearchByID_clicked();
	void on_ButtonCancel_clicked();
	void on_ButtonLoad_clicked();
	void	SlotClicked		(const QModelIndex &Index);
	void	SlotSelectCategory(int CategoryID ,QString FolderName ,QString Remark);

	void	MListSectionClicked ( int logicalIndex );
};

class	GUICmdSelectMaster: public GUICmdPacketBase
{
public:
	int32		MasterCode;
	QString		MasterName;
	QString		Remark;

	GUICmdSelectMaster(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


#endif // SELECTMASTERFORM_H