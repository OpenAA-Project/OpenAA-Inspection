#ifndef NEWMASTERDIALOG_H
#define NEWMASTERDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
#include <QLabel>
#include "XIntegrationBase.h"

namespace Ui {
class NewMasterDialog;
}

class	IntegrationNewMaster;

class NewMasterDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    IntegrationNewMaster    *Parent;
public:
	QString	ResultName	;
	QString	ResultRemark;
	QString	ResultNumber;
	IntegrationCommonData	CommonData;
	
	explicit NewMasterDialog(LayersBase *Base,IntegrationNewMaster *P,QWidget *parent = 0);
    ~NewMasterDialog();
    
private slots:
    void on_pushButtonInputPanelName_clicked();
    void on_pushButtonInputPanelRemark_clicked();
    void on_pushButtonInputPanelSizeX_clicked();
    void on_pushButtonInputPanelSizeY_clicked();
    void on_pushButtonSaveNew_clicked();
    void on_pushButtonCancel_clicked();

    void on_pushButtonInputPanelNumber_clicked();

private:
    Ui::NewMasterDialog *ui;
};

#endif // NEWMASTERDIALOG_H
