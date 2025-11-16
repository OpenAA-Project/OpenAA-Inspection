#ifndef MASTERPOSITIONDIALOG_H
#define MASTERPOSITIONDIALOG_H

#include <QDialog>
#include "XPalletize.h"

namespace Ui {
class MasterPositionDialog;
}

class MasterPositionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MasterPositionDialog(MasterPositionListContainer &_MasterPositions ,QWidget *parent = nullptr);
    ~MasterPositionDialog();

    MasterPositionListContainer	MasterPositions;
private slots:
    void on_pushButtonAdd_clicked();
    void on_pushButtonSub_clicked();
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::MasterPositionDialog *ui;
    void ShowGrid(void);
};

#endif // MASTERPOSITIONDIALOG_H
