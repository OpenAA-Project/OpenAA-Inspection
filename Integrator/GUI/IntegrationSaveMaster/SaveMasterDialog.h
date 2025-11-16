#ifndef SAVEMASTERDIALOG_H
#define SAVEMASTERDIALOG_H

#include <QDialog>
#include <QSqlTableModel>
#include <QTableView>
#include "XServiceForLayers.h"
#include <QLabel>
#include "XIntegrationBase.h"

namespace Ui {
class SaveMasterDialog;
}
class	SaveMasterDialog;
class	IntegrationSaveMaster;

class	QSqlSaveMasterModel : public QSqlTableModel
{
	SaveMasterDialog	*ParentWindow;
public:
	QSqlSaveMasterModel(QObject * parent, QSqlDatabase db);
	QString selectStatement () const;   
private slots:
};

class SaveMasterDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
     
	IntegrationSaveMaster	*ParentGUI;
	QLabel	*TopViewDim; 
	int		AllocatedViewCount;
public:
	QString	ResultNumber	;
	QString	ResultName	;
	QString	ResultRemark;
	IntegrationCommonData	CommonData;

	explicit SaveMasterDialog(LayersBase *Base
                            , IntegrationSaveMaster *P
                            , bool ModeNew=true ,bool ModeUpdate=true
                            , QWidget *parent = 0);
    ~SaveMasterDialog();
    
	QString	GetSearchString(void);
	void	SelectView(void);
    
private slots:
    void on_pushButtonInputPanelName_clicked();
    void on_pushButtonInputPanelRemark_clicked();
    void on_pushButtonSaveNew_clicked();
    void on_pushButtonUpdate_clicked();
    void on_pushButtonCancel_clicked();
    void on_pushButtonInputPanel_clicked();
    void on_tableView_clicked(const QModelIndex &index);
    void on_pushButtonInputPanelSizeX_clicked();
    void on_pushButtonInputPanelSizeY_clicked();
    void on_pushButtonInputPanelNumber_clicked();

private:
    Ui::SaveMasterDialog *ui;
};

#endif // SAVEMASTERDIALOG_H
