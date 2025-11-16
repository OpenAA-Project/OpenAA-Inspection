#ifndef SELECTPAGEITEMDIALOG_H
#define SELECTPAGEITEMDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
#include "XIntClass.h"
#include <QModelIndex>

namespace Ui {
class SelectPageItemDialog;
}
class	AlgorithmBase;

class SelectPageItemDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    
	ListPageLayerIDLibNamePack	ItemIDList;
public:
    explicit SelectPageItemDialog(AlgorithmBase *Algo ,ListPageLayerIDLibNamePack &itemIDList ,QWidget *parent = 0);
    ~SelectPageItemDialog();
    
	ListPageLayerIDPack	SelectedItems;
private slots:
    void on_tableWidgetItem_clicked(const QModelIndex &index);
    void on_tableWidgetItem_doubleClicked(const QModelIndex &index);
    void on_ButtonOK_clicked();

private:
    Ui::SelectPageItemDialog *ui;
};

#endif // SELECTPAGEITEMDIALOG_H
