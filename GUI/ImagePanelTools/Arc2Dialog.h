#ifndef ARC2DIALOG_H
#define ARC2DIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
    class Arc2Dialog;
}

class Arc2Dialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit Arc2Dialog(LayersBase *base, QWidget *parent = 0);
    ~Arc2Dialog();

	int		Cx,Cy;
	int		Rx,Ry;
	double	StartS,EndS;

private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::Arc2Dialog *ui;
};

#endif // ARC2DIALOG_H
