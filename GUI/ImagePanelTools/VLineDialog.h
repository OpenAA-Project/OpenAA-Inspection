#ifndef VLINEDIALOG_H
#define VLINEDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
    class VLineDialog;
}

class VLineDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit VLineDialog(LayersBase *base, QWidget *parent = 0);
    ~VLineDialog();
	
	int	x1,y1,Len;

private slots:
    void on_pushButtonOK_clicked();

    void on_pushButtonCancel_clicked();

private:
    Ui::VLineDialog *ui;
};

#endif // VLINEDIALOG_H
