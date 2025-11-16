#ifndef RINGDIALOG_H
#define RINGDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
    class RingDialog;
}

class RingDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit RingDialog(LayersBase *base, QWidget *parent = 0);
    ~RingDialog();

	int		Cx,Cy;
	int		Rx1,Ry1;
	int		Rx2,Ry2;

private slots:
    void on_pushButtonOK_clicked();

    void on_pushButtonCancel_clicked();

private:
    Ui::RingDialog *ui;
};

#endif // RINGDIALOG_H
