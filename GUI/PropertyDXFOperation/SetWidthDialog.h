#ifndef SETWIDTHDIALOG_H
#define SETWIDTHDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
class SetWidthDialog;
}

class SetWidthDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    
public:
    explicit SetWidthDialog(LayersBase *base, QWidget *parent = 0);
    ~SetWidthDialog();
    
	int	Width;

private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::SetWidthDialog *ui;
};

#endif // SETWIDTHDIALOG_H
