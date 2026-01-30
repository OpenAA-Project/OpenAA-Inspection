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

#ifndef PROJECTPROPERTYMANAGER_H
#define PROJECTPROPERTYMANAGER_H

#include <QMainWindow>
#include "ui_ProjectPropertyManager.h"
#include "XPPManager.h"

class ProjectPropertyManager : public QMainWindow
{
	Q_OBJECT

	PropertyList	*CopiedProperty;
	CompileTypeList	*CopiedType;

public:
	ProjectPropertyManager(QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~ProjectPropertyManager();

private slots:
    void on_pushButtonSearchSolutionFile_clicked();
    void on_tableWidgetProjectList_clicked(const QModelIndex &index);
    void on_pushButtonLoadSolution_clicked();
    void on_tableWidgetType_clicked(const QModelIndex &index);
    void on_listWidgetTagFolder_clicked(const QModelIndex &index);
    void on_pushButtonCopyToAll_clicked();
    void on_pushButtonUpdateProject_clicked();
	void on_pushButtonCopy1_clicked();
    void on_pushButtonPaste1_clicked();

private:
	Ui::ProjectPropertyManagerClass ui;

	Solution	SolutionData;

	void ShowProjectList(void);
	void ShowTypeList(void);
	void ShowPropertyList(void);
};

#endif // PROJECTPROPERTYMANAGER_H