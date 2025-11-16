#ifndef SELECTMACHINEFORREVIEWDIALOG_H
#define SELECTMACHINEFORREVIEWDIALOG_H

#include <QDialog>
#include <QModelIndex>
#include "XServiceForLayers.h"
#include <QStringList>

namespace Ui {
class SelectMachineForReviewDialog;
}

class SelectMachineForReviewDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    
	QStringList	MFieldNames;
public:
    explicit SelectMachineForReviewDialog(LayersBase *base ,QWidget *parent = 0);
    ~SelectMachineForReviewDialog();
    
private:
private slots:
    void on_tableWidgetFrontSide_clicked(const QModelIndex &index);
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::SelectMachineForReviewDialog *ui;
};

#endif // SELECTMACHINEFORREVIEWDIALOG_H
