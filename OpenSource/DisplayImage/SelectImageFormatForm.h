#ifndef SELECTIMAGEFORMATFORM_H
#define SELECTIMAGEFORMATFORM_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
class SelectImageFormatForm;
}
class	DisplayImage;

class SelectImageFormatForm : public QDialog,public ServiceForLayers
{
    Q_OBJECT

    DisplayImage	*ImageBase;
public:
    explicit SelectImageFormatForm(DisplayImage *Base,QWidget *parent = 0);
    ~SelectImageFormatForm();
    
private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::SelectImageFormatForm *ui;
};

#endif // SELECTIMAGEFORMATFORM_H
