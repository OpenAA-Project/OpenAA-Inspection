#ifndef SHOWSYSTEMVERSIONDIALOG_H
#define SHOWSYSTEMVERSIONDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
    class ShowSystemVersionDialog;
}

class	RunnerMap;

class ShowSystemVersionDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

	RunnerMap	*EVMap;
public:
    explicit ShowSystemVersionDialog(LayersBase *Base,QWidget *parent = 0);
    ~ShowSystemVersionDialog();

private slots:
    void on_pushButtonSaveCSV_clicked();

    void on_pushButtonClose_clicked();

private:
    Ui::ShowSystemVersionDialog *ui;
};

#endif // SHOWSYSTEMVERSIONDIALOG_H
