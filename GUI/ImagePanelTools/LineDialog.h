#ifndef LINEDIALOG_H
#define LINEDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
    class LineDialog;
}

class LineDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit LineDialog(LayersBase *base, QWidget *parent = 0);
    ~LineDialog();

	int	x1,y1,x2,y2;

private slots:
    void on_pushButtonOK_clicked();

    void on_pushButtonCancel_clicked();

private:
    Ui::LineDialog *ui;
};

#endif // LINEDIALOG_H
