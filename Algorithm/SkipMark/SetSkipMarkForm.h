#ifndef SETSKIPMARKFORM_H
#define SETSKIPMARKFORM_H

#include <QWidget>
#include "XServiceForLayers.h"

namespace Ui {
class SetSkipMarkForm;
}

class SetSkipMarkForm : public QWidget,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit SetSkipMarkForm(LayersBase *base, QWidget *parent = 0);
    ~SetSkipMarkForm();

private slots:
    void on_pushButtonModify_clicked();

    void on_pushButtonCancel_clicked();

    void on_pushButtonSelectArea_clicked();

private:
    Ui::SetSkipMarkForm *ui;
};

#endif // SETSKIPMARKFORM_H
