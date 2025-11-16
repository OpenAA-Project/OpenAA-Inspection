#ifndef ARCDIALOG_H
#define ARCDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
    class ArcDialog;
}

class ArcDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit ArcDialog(LayersBase *base, QWidget *parent = 0);
    ~ArcDialog();

	int		Cx,Cy;
	int		Rx,Ry;
	double	StartS,EndS;

private slots:
    void on_pushButtonOK_clicked();

    void on_pushButtonCancel_clicked();

private:
    Ui::ArcDialog *ui;
};

#endif // ARCDIALOG_H
