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

#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_LinuxProjectModifier.h"
#include "NList.h"
#include <QString>

class ProjectList : public NPList<ProjectList>
{
public:
	QString	BaseName;
	QString	Path;

	ProjectList(void){}
	~ProjectList(void){}
};


class LinuxProjectModifier : public QMainWindow
{
    Q_OBJECT

	NPListPack<ProjectList>	ProjectListContainer;
	QString	PathQtLib;
	QString	PathQtInclude;
public:
    LinuxProjectModifier(QWidget *parent = Q_NULLPTR);

private slots:
    void on_pushButtonSelectFolder_clicked();
    void on_pushButtonExecute_clicked();
    void on_pushButtonSelectQtLib_clicked();
    void on_pushButtonSelectQtInclude_clicked();

private:
    Ui::LinuxProjectModifierClass ui;
	void SearchPathProj(const QString &FolderPath);
	bool LoadVCX(const QString &VCXProjectFileName
							,QStringList &DirList
							,QStringList &ModuleList
							,QStringList &AddedLib);
	bool SavePro(const QString &ProProjectFileName
								,const QStringList &DirList
								,const QString &tPathQtLib
								,const QString &tPathQtInclude
								,const QStringList &ModuleList
								,const QStringList &AddedLib);
};