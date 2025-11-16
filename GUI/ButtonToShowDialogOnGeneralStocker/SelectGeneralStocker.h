#ifndef SELECTGENERALSTOCKER_H
#define SELECTGENERALSTOCKER_H

#include <QDialog>
#include <QModelIndex>
#include "NList.h"
#include "XServiceForLayers.h"

namespace Ui {
class SelectGeneralStocker;
}
class	GeneralStocker;
class	GeneralStockerPointerList;

class SelectGeneralStocker : public QDialog,public ServiceForLayers
{
    Q_OBJECT

    NPListPack<GeneralStockerPointerList>	Dim;

public:
    explicit SelectGeneralStocker(LayersBase *base,NPListPack<GeneralStockerPointerList> &Dim,QWidget *parent = 0);
    ~SelectGeneralStocker();

    GeneralStocker	*Selected;

private slots:
    void on_pushButtonSelect_clicked();
    void on_tableWidgetGeneralStocker_doubleClicked(const QModelIndex &index);

private:
    Ui::SelectGeneralStocker *ui;
};

#endif // SELECTGENERALSTOCKER_H
