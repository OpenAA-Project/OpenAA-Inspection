#ifndef SELECTPAGELAYER_H
#define SELECTPAGELAYER_H

#include <QDialog>
#include <QModelIndex>
#include "XServiceForLayers.h"

namespace Ui {
class SelectPageLayer;
}

class SelectPageLayer : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    
public:
    explicit SelectPageLayer(LayersBase *pbase ,QWidget *parent = 0);
    ~SelectPageLayer();

    int	Page;
    int	Layer;

private slots:
    void on_listWidgetPage_clicked(const QModelIndex &index);
    void on_listWidgetPage_doubleClicked(const QModelIndex &index);
    void on_listWidgetLayer_clicked(const QModelIndex &index);
    void on_listWidgetLayer_doubleClicked(const QModelIndex &index);
    void on_pushButtonSelect_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::SelectPageLayer *ui;

    void ShowLayerList(int page);
};

#endif // SELECTPAGELAYER_H
