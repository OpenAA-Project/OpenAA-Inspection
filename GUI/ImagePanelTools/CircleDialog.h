#ifndef CIRCLEDIALOG_H
#define CIRCLEDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
    class CircleDialog;
}

class CircleDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit CircleDialog(LayersBase *base, QWidget *parent = 0);
    ~CircleDialog();

	int		Cx,Cy;
	int		R;

private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::CircleDialog *ui;
};

#endif // CIRCLEDIALOG_H
