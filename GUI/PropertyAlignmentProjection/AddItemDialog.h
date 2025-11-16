#ifndef ADDITEMDIALOG_H
#define ADDITEMDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
class AddItemDialog;
}

class AddItemDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    
public:
    explicit AddItemDialog(LayersBase *base ,QWidget *parent = 0);
    ~AddItemDialog();

	QString		ItemName;
	int			PeakCount;
	double		Angle;
	int			PeakIsolation;
	int			UsageLayer;
	double		AbandonRateL;
	double		AbandonRateH;

	void	SetInitial(QString &ItemName,int PeakCount,double Angle,int PeakIsolation ,int UsageLayer,double AbandonRateL ,double AbandonRateH);
    
private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::AddItemDialog *ui;
};

#endif // ADDITEMDIALOG_H
