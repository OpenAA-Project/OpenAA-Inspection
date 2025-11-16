#ifndef RWEDITOBJECTPROPERTYFORM_H
#define RWEDITOBJECTPROPERTYFORM_H

#include <QModelIndex>
#include "XGUIFormBase.h"

namespace Ui {
class RWEditObjectPropertyForm;
}

class RWEditObjectPropertyForm : public GUIFormBase
{
    Q_OBJECT

public:
    explicit RWEditObjectPropertyForm(LayersBase *Base,QWidget *parent = nullptr);
    ~RWEditObjectPropertyForm();

private slots:
    void on_pushButtonLoadStepFile_clicked();
    void on_pushButtonLoadFromServer_clicked();
    void on_listWidgetFileList_itemSelectionChanged();
    void on_listWidgetFileList_clicked(const QModelIndex &index);
    void on_listWidgetFileList_doubleClicked(const QModelIndex &index);
    void on_treeWidgetObject_itemSelectionChanged();
    void on_treeWidgetObject_clicked(const QModelIndex &index);
    void on_treeWidgetObject_doubleClicked(const QModelIndex &index);
    void on_pushButtonSave_clicked();
    void on_pushButtonLoad_clicked();
    void on_pushButtonToServer_clicked();

private:
    Ui::RWEditObjectPropertyForm *ui;
};

#endif // RWEDITOBJECTPROPERTYFORM_H
