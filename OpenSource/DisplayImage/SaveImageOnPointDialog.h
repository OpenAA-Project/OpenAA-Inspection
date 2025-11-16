#ifndef SAVEIMAGEONPOINTDIALOG_H
#define SAVEIMAGEONPOINTDIALOG_H

#include <QDialog>
#include "XDataInLayer.h"
#include "XFileRegistry.h"
#include "XServiceForLayers.h"

class	DisplayImage;

namespace Ui {
class SaveImageOnPointDialog;
}

class SaveImageOnPointDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    DisplayImage	*ImageBase;

public:
    explicit SaveImageOnPointDialog(DisplayImage *Base,QWidget *parent = 0);
    ~SaveImageOnPointDialog();
    
private slots:
    void on_pushButtonOK_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::SaveImageOnPointDialog *ui;
};

#endif // SAVEIMAGEONPOINTDIALOG_H
