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
