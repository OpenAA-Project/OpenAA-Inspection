#ifndef SHAREMASTERDATAFORM_H
#define SHAREMASTERDATAFORM_H

#include <QWidget>
#include <QModelIndex>
#include "XServiceForLayers.h"

namespace Ui {
class ShareMasterDataForm;
}

class ShareMasterDataForm : public QWidget,public ServiceForLayers
{
    Q_OBJECT
    
	int	IndexNumber;
public:
    explicit ShareMasterDataForm(LayersBase *Base,QWidget *parent = 0);
    ~ShareMasterDataForm();
    
	void	ShowGrid(void);
	void	GetFromWindow(int machineID);

private slots:
    void on_tableWidget_doubleClicked(const QModelIndex &index);
    void on_pushButtonOK_clicked();
    void on_comboBoxMachineID_currentIndexChanged(int index);

    void on_pushButtonAddDestination_clicked();

    void on_pushButtonDelDestination_clicked();

private:
    Ui::ShareMasterDataForm *ui;
};

#endif // SHAREMASTERDATAFORM_H
