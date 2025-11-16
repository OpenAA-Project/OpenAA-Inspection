#ifndef LISTSELECTFIXEDPAGEFORM_H
#define LISTSELECTFIXEDPAGEFORM_H

#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include <QModelIndex>


namespace Ui {
class ListSelectFixedPageForm;
}

class ListSelectFixedPageForm : public GUIFormBase
{
    Q_OBJECT

public:
    QStringList DisplayImageInst;

    explicit ListSelectFixedPageForm(LayersBase *Base ,QWidget *parent = nullptr);
    ~ListSelectFixedPageForm();

    virtual void	BuildForShow(void);
    virtual bool	Reallocate(int newPhaseNumb , int newPageNumb ,int newLayerNumb)    override;
	virtual	bool	InsertPage(int IndexPage);	//Create page before Indexed page
	virtual	bool	RemovePage(int IndexPage);

    virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
private slots:
    void on_listWidgetPage_itemSelectionChanged();
    void on_listWidgetPage_clicked(const QModelIndex &index);

private:
    Ui::ListSelectFixedPageForm *ui;

    void    ShowPageList(void);
private slots:
	void	ResizeAction();
};

#endif // LISTSELECTFIXEDPAGEFORM_H
