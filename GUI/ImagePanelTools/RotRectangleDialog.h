#ifndef ROTRECTANGLEDIALOG_H
#define ROTRECTANGLEDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
    class RotRectangleDialog;
}

class RotRectangleDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit RotRectangleDialog(LayersBase *base, QWidget *parent = 0);
    ~RotRectangleDialog();

	int		Cx,Cy;
	int		Width,Height;
	double	S;

private slots:
    void on_pushButtonOK_clicked();

    void on_pushButtonCancel_clicked();

private:
    Ui::RotRectangleDialog *ui;
};

#endif // ROTRECTANGLEDIALOG_H
