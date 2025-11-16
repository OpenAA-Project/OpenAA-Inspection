#ifndef LONGCIRCLEDIALOG_H
#define LONGCIRCLEDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
class LongCircleDialog;
}

class LongCircleDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit LongCircleDialog(LayersBase *base, QWidget *parent = 0);
    ~LongCircleDialog();

	int		Cx1,Cy1;
	int		Cx2,Cy2;
	int		R;

private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::LongCircleDialog *ui;
};

#endif // LONGCIRCLEDIALOG_H
