#ifndef EDITTRANSFERHOSTDIALOG_H
#define EDITTRANSFERHOSTDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
class EditTransferHostDialog;
}

class EditTransferHostDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    
public:
    explicit EditTransferHostDialog(LayersBase *Base ,QWidget *parent = 0);
    ~EditTransferHostDialog();
    
private slots:
    void on_pushButtonTransferPlus_clicked();
    void on_pushButtonTransferMinus_clicked();
    void on_pushButtonOverWriteFileTransfer_clicked();

private:
    Ui::EditTransferHostDialog *ui;

	void	ShowTransfer(void);
	void	GetTransferFromWindow(void);
};

#endif // EDITTRANSFERHOSTDIALOG_H
