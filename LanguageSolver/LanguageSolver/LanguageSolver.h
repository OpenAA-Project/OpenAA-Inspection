/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\LanguageSolver\LanguageSolver\LanguageSolver.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#ifndef LANGUAGESOLVER_H
#define LANGUAGESOLVER_H

#include <QMainWindow>
#include "ui_LanguageSolver.h"


class	LSProjectItem;

class LanguageSolver : public QMainWindow
{
	Q_OBJECT

public:
	LanguageSolver(QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~LanguageSolver();

private:
	Ui::LanguageSolverClass ui;

	QString ProjectFileName;
	void	ShowProject();
	void	ShowProjectContents(LSProjectItem *CurrentProj);

private slots:
	void on_pushButtonSetXLSXFile_clicked();
	void on_pushButtonAutoXLSXNaming_clicked();
	void on_actionOverwrite_Project_triggered();
	void on_lineEditXLSXFolder_textChanged(const QString &);
	void on_pushButtonViewUI_clicked();
	void on_pushButtonViewString_clicked();
	void on_pushButtonExecuteOne_clicked();
	void on_lineEditVarName_textChanged(const QString &);
	void on_pushButtonAutoCSVNaming_clicked();
	void on_pushButtonAutoResourceNaming_clicked();
	void on_lineEditCSVFile_textChanged(const QString &);
	void on_lineEditResourceFile_textChanged(const QString &);
	void on_pushButtonFolderReference_clicked();
	void on_pushButtonExecute_clicked();
	void on_pushButtonSetCSVFile_clicked();
	void on_pushButtonSetResourceFile_clicked();
	void on_pushButtonDeleteUIFiles_clicked();
	void on_pushButtonAddUIFiles_clicked();
	void on_pushButtonDeleteCPPFiles_clicked();
	void on_pushButtonAddCPPFiles_clicked();
	void on_pushButtonDeleteProject_clicked();
	void on_pushButtonUpdateProject_clicked();
	void on_pushButtonAddProject_clicked();
	void on_listWidgetProject_clicked(const QModelIndex &);
	void on_actionSaveProject_triggered();
	void on_actionLoad_Project_triggered();
	void on_actionCodec_for_Languages_triggered();
	void on_actionLoad_UI_ui_triggered();
	void on_actionLoad_CSV_triggered();
	void on_actionSave_CSV_triggered();
	void on_actionLoad_resource_file_triggered();
	void on_actionSave_resource_files_triggered();
	void on_actionCodec_triggered();
	void on_actionReplace_CPP_triggered();
	void on_actionLoad_source_CPP_triggered();
};

#endif // LANGUAGESOLVER_H
