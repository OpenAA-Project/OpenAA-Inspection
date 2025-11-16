#ifndef CONFIRMITEMLISTFORM_H
#define CONFIRMITEMLISTFORM_H

#include <QWidget>
#include "XServiceForLayers.h"
#include "XDataAlgorithmConfirm.h"
#include "NList.h"

namespace Ui {
class ConfirmItemListForm;
}
class ConfirmForm;
class ConfirmAlgorithm;

class ComfirmItemListPointer : public NPList<ComfirmItemListPointer>
{
public:
    ConfirmItemList     *CItem;
    ConfirmAlgorithm    *CAlgorithm;

    virtual	int	Compare(ComfirmItemListPointer &src)    override;
};


class ConfirmItemListForm : public QWidget,public ServiceForLayers
{
    Q_OBJECT

    friend  class ConfirmForm;

    ConfirmForm *Parent;
    NPListPack<ComfirmItemListPointer>  ComfirmItems;
public:
    explicit ConfirmItemListForm(LayersBase *Base,ConfirmForm *p,QWidget *parent = nullptr);
    ~ConfirmItemListForm();

    void    BuildShowItemList(void);
    
private slots:
    void on_tableWidgetCause_itemSelectionChanged();

    void on_tableWidgetCause_clicked(const QModelIndex &index);

private:
    Ui::ConfirmItemListForm *ui;

    virtual	void resizeEvent(QResizeEvent *event)	override;
};

#endif // CONFIRMITEMLISTFORM_H
