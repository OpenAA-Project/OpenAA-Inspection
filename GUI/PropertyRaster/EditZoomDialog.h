#ifndef EDITZOOMDIALOG_H
#define EDITZOOMDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
class EditZoomDialog;
}

class EditZoomDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit EditZoomDialog(LayersBase *base, QWidget *parent = 0);
    ~EditZoomDialog();

	double	XZoomDir;
	double	YZoomDir;

private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::EditZoomDialog *ui;
};

#endif // EDITZOOMDIALOG_H
