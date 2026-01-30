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

#ifndef LANGUAGEMANAGER_H
#define LANGUAGEMANAGER_H

#include <QMainWindow>
#include "ui_LanguageManager.h"
#include "XLanguageManager.h"

class LanguageManager : public QMainWindow
{
	Q_OBJECT

public:
	LanguageManager(QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~LanguageManager();

	QString				SolutionFileName;
	SolutionLanguage	LSolution;
	LanguagePack		LanguageData;

private slots:
        void on_tableWidgetProject_doubleClicked(const QModelIndex &index);
        void on_tableWidgetExcelFiles_doubleClicked(const QModelIndex &index);
        void on_pushButtonLoadExcel_clicked();
        void on_pushButtonDeleteExcel_clicked();
        void on_pushButtonLNGFile_clicked();
        void on_pushButtonCompile_clicked();
        void on_pushButtonBuildAll_clicked();
        void on_actionLoad_solution_triggered();
        void on_actionLanguage_triggered();
        void on_actionDefault_triggered();
        void on_actionNew_Project_triggered();

        void on_tableWidgetProject_clicked(const QModelIndex &index);

        void on_actionSave_solution_triggered();

        void on_actionNew_solution_triggered();

        void on_actionClose_triggered();

        void on_actionOverwrite_solution_triggered();

        void on_lineEditLNGFile_textChanged(const QString &arg1);

        void on_pushButtonAddNewProject_clicked();

private:
	Ui::LanguageManagerClass ui;

	void	ShowProjectList();
	void	ShowDetail(ProjectLanguage *a);
};

#endif // LANGUAGEMANAGER_H