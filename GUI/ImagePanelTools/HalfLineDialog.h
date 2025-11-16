#ifndef HALFLINEDIALOG_H
#define HALFLINEDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
    class HalfLineDialog;
}

class HalfLineDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit HalfLineDialog(LayersBase *base, QWidget *parent = 0);
    ~HalfLineDialog();
	
	int		x,y;
	double	S;
	double	Length;

private slots:
    void on_pushButtonOK_clicked();

    void on_pushButtonCancel_clicked();

private:
    Ui::HalfLineDialog *ui;
};

#endif // HALFLINEDIALOG_H
