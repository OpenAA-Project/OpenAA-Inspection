#ifndef HLINEDIALOG_H
#define HLINEDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
    class HLineDialog;
}

class HLineDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit HLineDialog(LayersBase *base, QWidget *parent = 0);
    ~HLineDialog();

	int	x1,y1,Len;

private slots:
    void on_pushButtonOK_clicked();

    void on_pushButtonCancel_clicked();

private:
    Ui::HLineDialog *ui;
};

#endif // HLINEDIALOG_H
