#ifndef SELECTBYBindedLIMITEDDIALOG_H
#define SELECTBYBindedLIMITEDDIALOG_H

#include <QDialog>
#include "XMasking.h"
#include "XServiceForLayers.h"
#include "XPropertyMaskingPacket.h"

namespace Ui {
class SelectByBindedLimitedDialog;
}

class LineItemPointer : public NPList<LineItemPointer>
{
public:
	MaskingBindedList::BindedInPage::BindedInLayer	*Pointer;

	LineItemPointer(MaskingBindedList::BindedInPage::BindedInLayer *s){	Pointer=s;	}
};

class LineInfoBinded : public NPList<LineInfoBinded>
{
public:
	NPListPack<LineItemPointer>	PointerInst;
	AlgorithmLibraryListContainer	*LibPointer;
	bool	Selected;

	LineInfoBinded(void):Selected(false){}
};



class SelectByBindedLimitedDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
public:
    MaskingBindedListContainer	InstList;
	NPListPack<LineInfoBinded>	LineInfoInst;

	explicit SelectByBindedLimitedDialog(LayersBase *,QWidget *parent = 0);
    ~SelectByBindedLimitedDialog();
    
private slots:
    void on_toolButtonPage_clicked();
    void on_toolButtonLayer_clicked();
    void on_tableWidgetBinded_itemSelectionChanged();
    void on_pushButtonSelect_clicked();
    void on_pushButtonEdit_clicked();
    void on_pushButtonClose_clicked();
    void on_tableWidgetBinded_doubleClicked(const QModelIndex &index);

private:
    Ui::SelectByBindedLimitedDialog *ui;

	void ShowBindedList(void);
};

#endif // SELECTBYBindedLIMITEDDIALOG_H
