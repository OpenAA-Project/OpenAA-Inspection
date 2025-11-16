#ifndef EDITPARAMINTEGRATIONMASTER_H
#define EDITPARAMINTEGRATIONMASTER_H

#include <QMainWindow>
#include "ui_EditParamIntegrationMaster.h"
#include "WEditParameterTab.h"
#include "WMultiGrid.h"
#include "XServiceForLayers.h"

class	ParamIntegrationMaster;

class EditParamIntegrationMaster : public QMainWindow,public ServiceForLayers
{
	Q_OBJECT

	QString	GlobalParamLoadedFileName;
	int	LastRowInSlave;
public:
	WEditParameterTab	*WTab;
	ParamIntegrationMaster *Param;

	EditParamIntegrationMaster(LayersBase *base,ParamIntegrationMaster *param,QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~EditParamIntegrationMaster();

private slots:
    void on_SaveButton_clicked();
    void on_UpdateDefaultButton_clicked();
    void on_LoadButton_clicked();
    void on_CancelButton_clicked();

    void on_listWidgetSlaveList_clicked(const QModelIndex &index);
    void on_pushButtonSlaveListPlus_clicked();
    void on_pushButtonSlaveListMinus_clicked();
    void on_pushButtonShooseSharedFolder_clicked();
    void on_pushButtonImagePathPlus_clicked();
    void on_pushButtonImagePathMinus_clicked();

private:
	Ui::EditParamIntegrationMasterClass ui;

	void	ShowSlaveList(void);
	void	ShowIntegrationSlave(int Row);
	void	GetIntegrationSlave(int Row);
	void	ClearIntegrationSlave(void);
};

#endif // EDITPARAMINTEGRATIONMASTER_H
