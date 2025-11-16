#ifndef CREATEMANUALLIGHTDIALOG_H
#define CREATEMANUALLIGHTDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
class CreateManualLightDialog;
}

class CreateManualLightDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    
public:
    explicit CreateManualLightDialog(LayersBase *base, QWidget *parent = 0);
    ~CreateManualLightDialog();
    
	QString	ItemName;
	int	BrightnessLow;
	int	BrightnessHigh;
	void	Reflect(void);
private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::CreateManualLightDialog *ui;
};

#endif // CREATEMANUALLIGHTDIALOG_H
