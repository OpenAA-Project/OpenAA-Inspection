#ifndef EDITMOVEDIALOG_H
#define EDITMOVEDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
class EditMoveDialog;
}

class EditMoveDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit EditMoveDialog(LayersBase *base, QWidget *parent = 0);
    ~EditMoveDialog();

	double	XDir;
	double	YDir;
	bool	PixelMode;

private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::EditMoveDialog *ui;
};

#endif // EDITMOVEDIALOG_H
