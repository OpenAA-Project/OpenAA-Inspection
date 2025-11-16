#ifndef DLLCHECKER_H
#define DLLCHECKER_H

#include <QMainWindow>
#include "ui_DLLChecker.h"
#include "XServiceForLayers.h"
#include "XGUI.h"

class DLLChecker : public QMainWindow,public ServiceForLayers
{
	Q_OBJECT

	GUIInstancePack	GUIPack;
public:
	DLLChecker(LayersBase *Base,QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~DLLChecker();

private:
	Ui::DLLCheckerClass ui;

private slots:
	void on_pushButtonClose_clicked();
	void on_pushButtonCheckDLL_clicked();
	void on_pushButtonEditAlgorithm_clicked();
        void on_pushButtonDLLVersionList_clicked();
};

#endif // DLLCHECKER_H
