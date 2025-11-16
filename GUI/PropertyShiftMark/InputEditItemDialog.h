#ifndef INPUTEDITITEMDIALOG_H
#define INPUTEDITITEMDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
class InputEditItemDialog;
}

class InputEditItemDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

    int Phase;
    int GlobalPage;
    int ItemID;

public:
    explicit InputEditItemDialog(LayersBase *base 
                                ,int Page ,int ItemID ,QWidget *parent = nullptr);
    ~InputEditItemDialog();

private slots:
    void on_pushButtonChangeVert_clicked();
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::InputEditItemDialog *ui;
};

#endif // INPUTEDITITEMDIALOG_H
