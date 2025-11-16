#ifndef NGTYPEDIALOG_H
#define NGTYPEDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
    class NGTypeDialog;
}
class	ColorBlockLibNGTypeItem;

class NGTypeDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

	ColorBlockLibNGTypeItem *Item;
public:
    explicit NGTypeDialog(LayersBase *base, ColorBlockLibNGTypeItem *item ,QWidget *parent = 0);
    ~NGTypeDialog();

private slots:
    void on_pushButtonOK_clicked();

private:
    Ui::NGTypeDialog *ui;
};

#endif // NGTYPEDIALOG_H
