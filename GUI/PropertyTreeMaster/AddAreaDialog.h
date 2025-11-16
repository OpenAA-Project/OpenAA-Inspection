#ifndef ADDAREADIALOG_H
#define ADDAREADIALOG_H

#include <QDialog>
#include <QColor>
#include "XServiceForLayers.h"
#include "mtColorFrame.h"

namespace Ui {
    class AddAreaDialog;
}

class AddAreaDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit AddAreaDialog(LayersBase *Base,QWidget *parent = 0);
	AddAreaDialog(QColor Color, LayersBase *Base, QWidget *parent = 0);
    ~AddAreaDialog();

	QColor	Color;
	QColor	PickupColor;

private slots:
    void on_spinBoxR_valueChanged(int arg1);
    void on_spinBoxG_valueChanged(int arg1);
    void on_spinBoxB_valueChanged(int arg1);
    void on_pushButtonAddPickupColor_clicked();
    void on_pushButtonSubPickupColor_clicked();
    void on_pushButtonOk_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::AddAreaDialog *ui;

	mtColorFrame	PickupColorFrame;
	mtColorFrame	ColorFrame;

	void ShowPanel(void);
};

#endif // ADDAREADIALOG_H
