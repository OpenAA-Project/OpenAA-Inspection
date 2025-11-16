#ifndef SELECTDISPATCHDIALOG_H
#define SELECTDISPATCHDIALOG_H

#include <QDialog>
#include "mtToolButtonColored.h"
#include "XServiceForLayers.h"
#include<QPushButton>

namespace Ui {
class SelectDispatchDialog;
}

class MasterButton : public QPushButton
{
    Q_OBJECT

    int ID;
public:
    MasterButton(int ID ,QWidget *obj=nullptr);

signals:
    void    SignalClicked(int ID);
private slots:
    void    SlotClicked();
};

class SelectDispatchDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

    MasterButton    **MasterButtonDim;
    int             CountMasterButton;
public:
    explicit SelectDispatchDialog(LayersBase *Base,QWidget *parent = nullptr);
    ~SelectDispatchDialog();

    int MasterNo;
private slots:
    void SlotMasterChanged(int ID);
private:
    Ui::SelectDispatchDialog *ui;
};

#endif // SELECTDISPATCHDIALOG_H
