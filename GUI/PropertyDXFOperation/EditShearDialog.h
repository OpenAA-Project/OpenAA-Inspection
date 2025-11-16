#ifndef EDITSHEARDIALOG_H
#define EDITSHEARDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
class EditShearDialog;
}

class EditShearDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit EditShearDialog(LayersBase *base, QWidget *parent = 0);
    ~EditShearDialog();

	bool	XMode;
	double	Shear;

private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::EditShearDialog *ui;
};

#endif // EDITSHEARDIALOG_H
