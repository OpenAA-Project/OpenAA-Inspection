#ifndef ADDNEWPHASEDIALOG_H
#define ADDNEWPHASEDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
class AddNewPhaseDialog;
}

class AddNewPhaseDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    
public:
    explicit AddNewPhaseDialog(LayersBase *Base ,QWidget *parent = 0);
    ~AddNewPhaseDialog();
    
	QString	PhaseName;

private slots:
    void on_pushButtonOK_clicked();

    void on_pushButtonCancel_clicked();

private:
    Ui::AddNewPhaseDialog *ui;
};

#endif // ADDNEWPHASEDIALOG_H
