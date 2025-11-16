#ifndef EDITRWDEVICEPARAMFORM_H
#define EDITRWDEVICEPARAMFORM_H

#include <QWidget>
#include "XServiceForLayers.h"
namespace Ui {
class EditRWDeviceParamForm;
}

class EditRWDeviceParamForm : public QWidget,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit EditRWDeviceParamForm(LayersBase *base,QWidget *parent = nullptr);
    ~EditRWDeviceParamForm();

    void	Show(void);
    void	LoadFromWindow(void);

private slots:
    void on_tableWidgetDeviceList_itemSelectionChanged();
    void on_tableWidgetDeviceList_clicked(const QModelIndex &index);
    void on_pushButtonAddLine_clicked();
    void on_pushButtonDelLine_clicked();
    void on_pushButtonSelectFile_clicked();

    void on_pushButtonSet_clicked();

private:
    Ui::EditRWDeviceParamForm *ui;
};

#endif // EDITRWDEVICEPARAMFORM_H
