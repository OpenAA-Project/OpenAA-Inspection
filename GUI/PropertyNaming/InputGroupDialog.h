#ifndef INPUTGROUPDIALOG_H
#define INPUTGROUPDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
class InputGroupDialog;
}

class InputGroupDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    
public:
    explicit InputGroupDialog(LayersBase *base, QWidget *parent = 0);
    ~InputGroupDialog();
    
	QString		GroupString;

private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::InputGroupDialog *ui;
};

#endif // INPUTGROUPDIALOG_H
