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
