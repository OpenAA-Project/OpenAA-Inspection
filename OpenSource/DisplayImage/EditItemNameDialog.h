#ifndef EDITITEMNAMEDIALOG_H
#define EDITITEMNAMEDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
class EditItemNameDialog;
}

class EditItemNameDialog : public QDialog ,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit EditItemNameDialog(LayersBase *base ,const QString &itemname ,QWidget *parent = 0);
    ~EditItemNameDialog();

	QString ItemName;

private slots:
    void on_pushButtonChange_clicked();

    void on_pushButtonClose_clicked();

private:
    Ui::EditItemNameDialog *ui;
};

#endif // EDITITEMNAMEDIALOG_H
