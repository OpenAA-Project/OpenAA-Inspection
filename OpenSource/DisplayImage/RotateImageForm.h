#ifndef ROTATEIMAGEFORM_H
#define ROTATEIMAGEFORM_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
class RotateImageForm;
}
class	LayersBase;

class RotateImageForm : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    
public:
    explicit RotateImageForm(LayersBase *Base,QWidget *parent = 0);
    ~RotateImageForm();
    
	bool	FlagMaster;
	bool	FlagTarget;

	double	Angle;
	bool	RetMode;

private slots:
    void on_pushButtonGo_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::RotateImageForm *ui;
};

#endif // ROTATEIMAGEFORM_H
