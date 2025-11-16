#ifndef MONONGTYPEDIALOG_H
#define MONONGTYPEDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
    class MonoNGTypeDialog;
}
class	OutlineInspectLibNGTypeItem;
class MonoNGTypeDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
	OutlineInspectLibNGTypeItem	*Item;

public:
    explicit MonoNGTypeDialog(LayersBase *base, OutlineInspectLibNGTypeItem *item ,QWidget *parent = 0);
    ~MonoNGTypeDialog();

private slots:
    void on_pushButtonOK_clicked();

private:
    Ui::MonoNGTypeDialog *ui;
};

#endif // MONONGTYPEDIALOG_H
