#ifndef SETTHRESHOLDDIALOG_H
#define SETTHRESHOLDDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
namespace Ui {
class SetThresholdDialog;
}
class	CartonMenuForm;


class SetThresholdDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
	CartonMenuForm	*Parent;
    
public:
	int		SlaveNo;

    explicit SetThresholdDialog(int _SlaveNo ,LayersBase *Base ,CartonMenuForm *p,QWidget *parent = 0);
    ~SetThresholdDialog();
    
private slots:
    void on_horizontalSliderLevelCharBright_valueChanged(int value);
    void on_horizontalSliderLevelCharSize_valueChanged(int value);
    void on_horizontalSliderLevelFlatBright_valueChanged(int value);
    void on_horizontalSliderLevelFlatSize_valueChanged(int value);
    void on_PushButtonClose_clicked();

private:
    Ui::SetThresholdDialog *ui;
};

#endif // SETTHRESHOLDDIALOG_H
