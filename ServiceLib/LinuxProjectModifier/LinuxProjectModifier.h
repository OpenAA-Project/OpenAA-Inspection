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
