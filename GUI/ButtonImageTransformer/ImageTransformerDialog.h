#ifndef IMAGETRANSFORMERDIALOG_H
#define IMAGETRANSFORMERDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
#include "XIntClass.h"

namespace Ui {
    class ImageTransformerDialog;
}

class ImageTransformerDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit ImageTransformerDialog(LayersBase *Base,QWidget *parent = 0);
    ~ImageTransformerDialog();

	IntList		SelectedPages;
	bool		MasterImage;
	bool		TargetImage;

private slots:
    void on_pushButton_3_clicked();
    void on_pushButtonUpsideDown_clicked();
    void on_pushButtonLeftsideRight_clicked();

private:
    Ui::ImageTransformerDialog *ui;
};

#endif // IMAGETRANSFORMERDIALOG_H
