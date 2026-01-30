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

#ifndef LANGUAGEMERGEXLSX_H
#define LANGUAGEMERGEXLSX_H

#include <QMainWindow>
#include "ui_LanguageMergeXLSX.h"
#include <QModelIndex>
#include "XLanguageCodec.h"
#include <QListWidget>
#include <QTableWidget>
#include "XMergeXLSX.h"

class LanguageMergeXLSX : public QMainWindow
{
	Q_OBJECT

	LanguagePack		LanguageData;
	QFileInfoList	DestXLSXFiles;
	QFileInfoList	SourceXLSXFiles;

	NPListPack<CombinedXLSX>	CombinedXLSXContainer;

public:
	LanguageMergeXLSX(QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~LanguageMergeXLSX();

private slots:
        void on_pushButtonDestFolder_clicked();
        void on_pushButtonSourceFolder_clicked();
        void on_listWidgetDestFiles_doubleClicked(const QModelIndex &index);
        void on_listWidgetSourceFiles_doubleClicked(const QModelIndex &index);
        void on_pushButtonConbine_clicked();
        void on_pushButtonStartMerge_clicked();
        void on_pushButtonAddDest_clicked();
        void on_pushButtonAddSource_clicked();

private:
	Ui::LanguageMergeXLSXClass ui;

	void	ShowLanguageList(void);
};

#endif // LANGUAGEMERGEXLSX_H