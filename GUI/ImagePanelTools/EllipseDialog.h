#ifndef ELLIPSEDIALOG_H
#define ELLIPSEDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
    class EllipseDialog;
}

class EllipseDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit EllipseDialog(LayersBase *base, QWidget *parent = 0);
    ~EllipseDialog();

	int		Cx,Cy;
	int		Rx,Ry;

private slots:
    void on_pushButtonOK_clicked();

    void on_pushButtonCancel_clicked();

private:
    Ui::EllipseDialog *ui;
};

#endif // ELLIPSEDIALOG_H
