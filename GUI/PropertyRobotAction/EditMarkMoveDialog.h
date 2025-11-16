#ifndef EDITMARKMOVEDIALOG_H
#define EDITMARKMOVEDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
class EditMarkMoveDialog;
}

class ActionMarkBase;

class EditMarkMoveDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit EditMarkMoveDialog(LayersBase *base,QWidget *parent = nullptr);
    ~EditMarkMoveDialog();

    void    Initial(ActionMarkBase *src);
    float   Speed;

private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::EditMarkMoveDialog *ui;
};

#endif // EDITMARKMOVEDIALOG_H
