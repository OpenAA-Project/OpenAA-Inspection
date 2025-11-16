#ifndef SHOWEXECUTINGDIALOG_H
#define SHOWEXECUTINGDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
#include "XReportStructure.h"

namespace Ui {
    class ShowExecutingDialog;
}

class ParamGlobal;

class ShowExecutingDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

	ThreadReport	RunningThread;
public:
    ParamGlobal     *GlobalParam;
public:
    explicit ShowExecutingDialog(int masterCode
                                ,ParamGlobal *GlobalParam
                                ,LayersBase *Base 
                                ,QWidget *parent = 0);
    ~ShowExecutingDialog();

private slots:
    void on_pushButtonSaveEXCEL_clicked();
    void on_pushButtonClose_clicked();

private:
    Ui::ShowExecutingDialog *ui;
private slots:
	void	SlotStep(QString Msg);
	void	SlotReqLibrary();
	void	SlotFinished();
};

#endif // SHOWEXECUTINGDIALOG_H
