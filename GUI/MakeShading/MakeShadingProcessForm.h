#ifndef MAKESHADINGPROCESSFORM_H
#define MAKESHADINGPROCESSFORM_H

#include <QWidget>
#include <QPainter>
#include "XServiceForLayers.h"
#include "XDisplayImage.h"

namespace Ui {
class MakeShadingProcessForm;
}
class MakeShading;

class MakeShadingProcessForm : public QWidget ,public ServiceForLayers
{
    Q_OBJECT
    
    MakeShading *Parent;
    DisplayImage   ImagePanel;
    FlexArea        ShadingArea;

public:
    explicit MakeShadingProcessForm(LayersBase *base,MakeShading *p,QWidget *parent = 0);
    ~MakeShadingProcessForm();
    
private slots:
    void on_pushButtonRegist_clicked();
    void	SlotDrawEndAfterOperation(FlexArea &area);
    void	SlotDrawFunc(QPainter &pnt ,QImage &PntImage ,const IntList &_LayerList);
    void on_pushButtonStartCapture_clicked();
    void on_toolButtonDown_clicked();
    void on_toolButtonUp_clicked();
    void on_spinBoxMinX_valueChanged(int arg1);
    void on_spinBoxMaxX_valueChanged(int arg1);
    void on_comboBoxCurrentPage_currentIndexChanged(int index);

private:
    Ui::MakeShadingProcessForm *ui;

    virtual	void showEvent(QShowEvent *event)       override;
	virtual	void resizeEvent(QResizeEvent *event)   override;
    virtual	void closeEvent(QCloseEvent *event)     override;
};

#endif // MAKESHADINGPROCESSFORM_H
