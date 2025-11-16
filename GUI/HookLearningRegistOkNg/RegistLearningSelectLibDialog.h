#ifndef REGISTLEARNINGSELECTLIBDIALOG_H
#define REGISTLEARNINGSELECTLIBDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
#include "XHookRegistCommon.h"

namespace Ui {
class RegistLearningSelectLibDialog;
}

class RegistLearningSelectLibDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    int		GlobalX1 ,GlobalY1;
	int		GlobalX2 ,GlobalY2;
	int		PointX,PointY;
    LibIDListWithResultContainer    LibContainer;

public:
    explicit RegistLearningSelectLibDialog(LayersBase *base ,int PointX,int PointY 
									,int GlobalX1 ,int GlobalY1 ,int GlobalX2 ,int GlobalY2
                                    ,LibIDListWithResultContainer &Container
                                    ,QWidget *parent = nullptr);
    ~RegistLearningSelectLibDialog();

    LibIDListWithResultContainer    SelectedLibContainer;

private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonNG_clicked();
    void on_horizontalSliderPriority_valueChanged(int value);
    void on_spinBoxPriority_valueChanged(int arg1);
    void on_pushButtonCancel_clicked();

private:
    Ui::RegistLearningSelectLibDialog *ui;
};

#endif // REGISTLEARNINGSELECTLIBDIALOG_H
