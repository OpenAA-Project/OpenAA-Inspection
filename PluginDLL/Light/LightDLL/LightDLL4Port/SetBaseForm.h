#ifndef SETBASEFORM_H
#define SETBASEFORM_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
    class SetBaseForm;
}

class SetBaseForm : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit SetBaseForm(LayersBase *base, int BasePort[],QWidget *parent = 0);
    ~SetBaseForm();

private slots:
    void on_pushButtonOK_clicked();

private:
    Ui::SetBaseForm *ui;
};

#endif // SETBASEFORM_H
