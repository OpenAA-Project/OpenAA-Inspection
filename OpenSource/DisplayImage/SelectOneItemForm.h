#ifndef SELECTONEITEMFORM_H
#define SELECTONEITEMFORM_H

#include <QDialog>
#include <QModelIndex>
#include "XServiceForLayers.h"
#include "XIntClass.h"

namespace Ui {
class SelectOneItemForm;
}

class	AlgorithmBase;

class SelectOneItemForm : public QDialog,public ServiceForLayers
{
    Q_OBJECT

    ListLayerIDLibNamePack	ItemIDList;
    int GlobalPage;
public:
    explicit SelectOneItemForm(AlgorithmBase *Algo ,ListLayerIDLibNamePack &itemIDList ,QWidget *parent ,int _GlobalPage=-1);
    ~SelectOneItemForm();

    ListLayerAndID	SelectedItem;

private slots:
    void on_pushButtonOK_clicked();
    void on_tableWidgetItem_clicked(const QModelIndex &index);
    void on_tableWidgetItem_doubleClicked(const QModelIndex &index);

private:
    Ui::SelectOneItemForm *ui;
};

#endif // SELECTONEITEMFORM_H
