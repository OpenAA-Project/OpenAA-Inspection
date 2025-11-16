#ifndef SELECTITEMSDIALOG_H
#define SELECTITEMSDIALOG_H

#include <QDialog>
#include <QModelIndex>
#include "XServiceForLayers.h"
#include "NListComp.h"
#include "XIntegrationSimpleImagePanelPacket.h"

namespace Ui {
class SelectItemsDialog;
}

class SelectedItemsInfo;


class SelectedItemsInfoPointer :public NPList<SelectedItemsInfoPointer>
{
public:
	SelectedItemsInfo	*Pointer;

    SelectedItemsInfoPointer(SelectedItemsInfo *p):Pointer(p){}

    bool    IsEqualForBind(SelectedItemsInfoPointer *src);
};

class	SelectedItemsInfoPointerContainer  : public NPListPack<SelectedItemsInfoPointer>
											,public NPList<SelectedItemsInfoPointerContainer>
{
public:
};

class	SelectedItemsInfoPointerContainerContainer : public NPListPack<SelectedItemsInfoPointerContainer>									
{
public:
};


class SelectItemsDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    SelectedItemsInfoContainer SelectedContainer;
    SelectedItemsInfoPointerContainerContainer  Binded;
public:
    explicit SelectItemsDialog(LayersBase *base,SelectedItemsInfoContainer &_SelectedContainer ,QWidget *parent = 0);
    ~SelectItemsDialog();
    
	SelectedItemsInfoContainer SelectedResult;

private slots:
    void on_pushButtonSelect_clicked();
    void on_tableWidget_doubleClicked(const QModelIndex &index);
    void on_pushButtonBind_clicked();
    void on_pushButtonSelectAll_clicked();
    void on_tableWidgetBinded_doubleClicked(const QModelIndex &index);
    void on_pushButtonCancel_clicked();
    void on_tableWidgetBinded_itemSelectionChanged();
    void on_tableWidget_itemSelectionChanged();

private:
    Ui::SelectItemsDialog *ui;

    void    MakeBind(void);
    void    ShowList(void);

protected:
	virtual	void resizeEvent ( QResizeEvent * event ) override;

signals:
	void	SignalTempSelectItem(const SelectedItemsInfoContainer &src);
    void	SignalTempSelectCancel();
};

#endif // SELECTITEMSDIALOG_H
