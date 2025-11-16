#ifndef ROTELLIPSEDIALOG_H
#define ROTELLIPSEDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
    class RotEllipseDialog;
}

class RotEllipseDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit RotEllipseDialog(LayersBase *base, QWidget *parent = 0);
    ~RotEllipseDialog();

	int		Cx,Cy;
	int		Rx,Ry;
	double	S;

private slots:
    void on_pushButtonOK_clicked();

    void on_pushButtonCancel_clicked();

private:
    Ui::RotEllipseDialog *ui;
};

#endif // ROTELLIPSEDIALOG_H
