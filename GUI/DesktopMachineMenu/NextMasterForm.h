#ifndef NEXTMASTERFORM_H
#define NEXTMASTERFORM_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
class NextMasterForm;
}

class NextMasterForm : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit NextMasterForm(LayersBase *base, QWidget *parent = nullptr);
    ~NextMasterForm();

private slots:
    void on_pushButtonStartNext_clicked();
    void on_pushButtonFinish_clicked();

private:
    Ui::NextMasterForm *ui;
};

#endif // NEXTMASTERFORM_H
