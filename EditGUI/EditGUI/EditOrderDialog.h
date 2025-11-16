#ifndef EDITORDERDIALOG_H
#define EDITORDERDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
namespace Ui {
class EditOrderDialog;
}

class GUIFormBase;

class EditOrderDialog : public QDialog, public ServiceForLayers
{
    Q_OBJECT

    GUIFormBase **GDim;
    int         GDimCount;
public:
    explicit EditOrderDialog(LayersBase *base,QWidget *parent = nullptr);
    ~EditOrderDialog();

private slots:
    void on_pushButtonUp_clicked();
    void on_pushButtonDown_clicked();
    void on_pushButtonOK_clicked();

private:
    Ui::EditOrderDialog *ui;

    void    ShowDim(void);

};

#endif // EDITORDERDIALOG_H
