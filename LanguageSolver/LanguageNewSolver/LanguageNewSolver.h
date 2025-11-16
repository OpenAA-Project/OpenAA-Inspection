#ifndef LANGUAGENEWSOLVER_H
#define LANGUAGENEWSOLVER_H

#include <QMainWindow>
#include "ui_LanguageNewSolver.h"
#include "XLSProjectNew.h"
#include <QModelIndex>
#include "XLanguageCodec.h"
#include "XLanguageNewSolver.h"


class LanguageNewSolver : public QMainWindow
{
	Q_OBJECT

	LanguageStocker		LSProjectData;
	LanguagePack		LanguageData;

public:
	LanguageNewSolver(QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~LanguageNewSolver();

private slots:
        void on_actionNew_solution_triggered();
        void on_actionLoad_solution_triggered();
        void on_actionOverwrite_solution_triggered();
        void on_actionSave_solution_triggered();
        void on_actionClose_triggered();
        void on_pushButtonAddProject_clicked();
        void on_listWidgetProject_clicked(const QModelIndex &index);
        void on_listWidgetProject_doubleClicked(const QModelIndex &index);
        void on_pushButtonFolderReference_clicked();
        void on_pushButtonAddCPPFiles_clicked();
        void on_pushButtonDeleteCPPFiles_clicked();
        void on_pushButtonAddUIFiles_clicked();
        void on_pushButtonDeleteUIFiles_clicked();
        void on_pushButtonAutoResourceNaming_clicked();
        void on_pushButtonSetResourceFile_clicked();
        void on_pushButtonAutoXLSXNaming_clicked();
        void on_pushButtonSetXLSXFile_clicked();
        void on_pushButtonExecuteOne_clicked();
        void on_pushButtonExecute_clicked();
        void on_actionLoad_Codec_file_triggered();
        void on_EditFolderReference_textChanged(const QString &arg1);
        void on_lineEditResourceFile_textChanged(const QString &arg1);
        void on_lineEditXLSXFile_textChanged(const QString &arg1);

        void on_pushButtonDeleteProject_clicked();

        void on_pushButtonSort_clicked();

private:
	Ui::LanguageNewSolverClass ui;

	void	ShowLanguageList(void);
	void	ShowProjectList(void);
	void	ShowDetail(LSProjectItem *a);
};

#endif // LANGUAGENEWSOLVER_H
