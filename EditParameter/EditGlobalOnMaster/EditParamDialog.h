#ifndef EDITPARAMDIALOG_H
#define EDITPARAMDIALOG_H

#include <QDialog>
#include <QModelIndex>
#include "XServiceForLayers.h"
#include "WEditParameterTab.h"
#include "FormCommSetting.h"

namespace Ui {
    class EditParamDialog;
}

class	FormScanStrategy;

class EditParamDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

	int MasterCode;
	WEditParameterTab	*WTab;
	FormScanStrategy	*WStrategy;
	FormCommSetting		*WCommSetting;

	ParamGlobal	MasterParam;
	ParamComm	MasterCommParam;
	int			LPageNumb;
	ParamGlobal	**SlaveParam;
	ParamComm	**SlaveCommParam;
	int			LastRow;

public:
    explicit EditParamDialog(int MasterCode ,LayersBase *base,QWidget *parent = 0);
    ~EditParamDialog();

private:
	bool LoadDataFromMaster(int masterCode);

private slots:
    void on_pushButtonSelectMachine_clicked();

    void on_pushButtonSelectWorker_clicked();

    void on_listWidgetPage_clicked(const QModelIndex &index);

    void on_pushButtonUpdate_clicked();

    void on_pushButtonCancel_clicked();

private:
    Ui::EditParamDialog *ui;
};

#endif // EDITPARAMDIALOG_H
