#ifndef RECTANGLEDIALOG_H
#define RECTANGLEDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
    class RectangleDialog;
}

class RectangleDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit RectangleDialog(LayersBase *base, QWidget *parent = 0);
    ~RectangleDialog();

	int	x1,y1,x2,y2;

private slots:
    void on_pushButtonOK_clicked();

    void on_pushButtonCancel_clicked();

private:
    Ui::RectangleDialog *ui;
};

#endif // RECTANGLEDIALOG_H
