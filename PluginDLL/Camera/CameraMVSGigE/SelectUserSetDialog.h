#ifndef SELECTUSERSETDIALOG_H
#define SELECTUSERSETDIALOG_H

#include <QDialog>
#include <QByteArray>
#include "CameraMVSGigE.h"

namespace Ui {
class SelectUserSetDialog;
}
class  CameraMVSGigE;


class SelectUserSetDialog : public QDialog
{
    Q_OBJECT

    CameraMVSGigE   *Parent;
    int         EnumUserSetSelectorData[64];
public:
    explicit SelectUserSetDialog(CameraMVSGigE *P,const QByteArray &CamData ,QWidget *parent = nullptr);
    ~SelectUserSetDialog();

    QByteArray  RetCamData;

private slots:
    void on_pushButtonSelect_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::SelectUserSetDialog *ui;
};

#endif // SELECTUSERSETDIALOG_H
