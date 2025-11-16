#ifndef ITEMLISTFORM_H
#define ITEMLISTFORM_H

#include <QWidget>
#include <QResizeEvent>
#include <QCloseEvent>
#include <QModelIndex>
#include "XServiceForLayers.h"
#include "XPropertyDotColorMatchingPacket.h"
namespace Ui {
class ItemListForm;
}

class ItemListForm : public QWidget,public ServiceForLayers
{
    Q_OBJECT
    BlockListInfoContainer	BlockListInfoContainerData;
    int     SortType;   //0:ItemID, 1:AreaSearch    ,2:SelfSearch ,3:OKDot
    bool    Decendant;
public:
    explicit ItemListForm(LayersBase *Base ,QWidget *parent = nullptr);
    ~ItemListForm();

    void    Initial(void);

private slots:
    void on_tableWidget_clicked(const QModelIndex &index);
    void on_tableWidget_doubleClicked(const QModelIndex &index);
    void    SlotTableSectionClicked(int logicalIndex);
    void on_tableWidget_itemSelectionChanged();

private:
    Ui::ItemListForm *ui;
    void    ShowGrid(void);
    void    resizeEvent(QResizeEvent *)     override;
    void	closeEvent(QCloseEvent *event)  override;
};

#endif // ITEMLISTFORM_H
