#ifndef REGISTLEARNINGDIALOG_H
#define REGISTLEARNINGDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
class RegistLearningDialog;
}

class RegistLearningDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    int		GlobalX1 ,GlobalY1;
	int		GlobalX2 ,GlobalY2;
	int		PointX,PointY;
    int     LibType,LibID;
public:

    explicit RegistLearningDialog(LayersBase *base ,int PointX,int PointY 
									,int GlobalX1 ,int GlobalY1 ,int GlobalX2 ,int GlobalY2
                                    ,int LibType,int LibID
                                    ,QWidget *parent = 0);
    ~RegistLearningDialog();
    
private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonNG_clicked();
    void on_pushButtonCancel_clicked();
    void on_horizontalSliderPriority_valueChanged(int value);
    void on_spinBoxPriority_valueChanged(int arg1);

private:
    Ui::RegistLearningDialog *ui;
};

#endif // REGISTLEARNINGDIALOG_H
