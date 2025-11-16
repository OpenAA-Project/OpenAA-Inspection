#ifndef EDITITEMDIALOG_H
#define EDITITEMDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
namespace Ui {
class EditItemDialog;
}
class ColorShiftVThreshold;

class EditItemDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit EditItemDialog(LayersBase *Base ,QWidget *parent = nullptr);
    ~EditItemDialog();

    void    SetCurrentItem(const ColorShiftVThreshold *RThr);
    void    GetCurrentItem(ColorShiftVThreshold *WThr);
private:
    Ui::EditItemDialog *ui;
};

#endif // EDITITEMDIALOG_H
