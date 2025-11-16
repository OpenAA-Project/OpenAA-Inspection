#ifndef POPUPMENUFORM_H
#define POPUPMENUFORM_H

#include <QWidget>
#include "XServiceForLayers.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
namespace Ui {
class PopupMenuForm;
}

class PopupMenuForm : public QWidget,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit PopupMenuForm(LayersBase *Base ,QWidget *parent = nullptr);
    ~PopupMenuForm();

private slots:
    void on_PushButtonMoveAll_clicked();
    void on_PushButtonChangeSize_clicked();
    void on_PushButtonClose_clicked();

private:
    Ui::PopupMenuForm *ui;
};

#endif // POPUPMENUFORM_H
