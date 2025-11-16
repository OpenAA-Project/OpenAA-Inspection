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
