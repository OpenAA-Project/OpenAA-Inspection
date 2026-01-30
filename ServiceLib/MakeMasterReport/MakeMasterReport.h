/*
 * Copyright (C) 2025
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

#ifndef MAKEMASTERREPORT_H
#define MAKEMASTERREPORT_H

#include <QMainWindow>
#include "ui_MakeMasterReport.h"
#include "MasterCategoryForm.h"
#include <QSqlTableModel>
#include <QTableView>
#include "XServiceForLayers.h"

class	MakeMasterReport;
class	QSqlLoadMasterModel;
class	ParamGlobal;

class MakeMasterReport : public QMainWindow,public ServiceForLayers
{
	Q_OBJECT
	friend class	QSqlLoadMasterModel;

public:
	MakeMasterReport(ParamGlobal *GlobalParam ,LayersBase *Base ,QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~MakeMasterReport();

	void	RefreshGrid(void);
private:
	MasterCategoryForm	*MasterCategory;
	QTableView *MListView;
	int		SelectedMasterCode;

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
	ParamGlobal *GlobalParam;

	void	ShowListHeader(void);
	void	SelectView(void);
	bool	LoadDataFromMaster(int masterCode);

private slots:
        void on_pushButtonOpenDatabase_clicked();
        void on_pushButtonStartSearchByID_clicked();
        void on_pushButtonStartSearchByName_clicked();
        void on_pushButtonClose_clicked();
	void	SlotClicked		(const QModelIndex &Index);
	void	SlotDoubleClicked(const QModelIndex &Index);
	void	SlotSelectCategory(int CategoryID ,QString FolderName ,QString Remark);
	
	void	MListSectionClicked ( int logicalIndex );
    void on_pushButtonSelect_clicked();

private:
	Ui::MakeMasterReportClass ui;
};

#endif // MAKEMASTERREPORT_H