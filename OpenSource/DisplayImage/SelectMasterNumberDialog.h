#ifndef SELECTMASTERNUMBERDIALOG_H
#define SELECTMASTERNUMBERDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
class SelectMasterNumberDialog;
}

class SelectMasterNumberDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    
public:
    explicit SelectMasterNumberDialog(LayersBase *base,QWidget *parent = 0);
    ~SelectMasterNumberDialog();
    
	int	SelectedMasterNo;

private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::SelectMasterNumberDialog *ui;
};

#endif // SELECTMASTERNUMBERDIALOG_H
