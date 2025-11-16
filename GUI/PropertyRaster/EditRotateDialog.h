#ifndef EDITROTATEDIALOG_H
#define EDITROTATEDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
class EditRotateDialog;
}

class EditRotateDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit EditRotateDialog(LayersBase *base, QWidget *parent = 0);
    ~EditRotateDialog();

	double	Angle;

private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();
    void on_pushButton90_clicked();
    void on_pushButton180_clicked();
    void on_pushButton270_clicked();

private:
    Ui::EditRotateDialog *ui;
};

#endif // EDITROTATEDIALOG_H
