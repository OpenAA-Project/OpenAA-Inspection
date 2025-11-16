#ifndef SHOWPARTIALIMAGINGLISTFORM_H
#define SHOWPARTIALIMAGINGLISTFORM_H

#include <QWidget>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XGUIFormBase.h"
#include "XPartialImaging.h"

namespace Ui {
class ShowPartialImagingListForm;
}

class	WriteBufferPointer
{
public:
	WriteBufferInItem	*Point;
	int					GlobalPage;
};


class ShowPartialImagingListForm : public GUIFormBase
{
    Q_OBJECT

	WriteBufferInPage	*PageData;
	int					AllocatedPageNumb;
	WriteBufferPointer	*WList;
	int					WListNumb;

public:
    explicit ShowPartialImagingListForm(LayersBase *Base ,QWidget *parent = 0);
    ~ShowPartialImagingListForm();

	virtual void	BuildForShow(void)	override;
	virtual void	StartLot	(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

private slots:
    void on_tableWidgetList_clicked(const QModelIndex &index);
    void on_tableWidgetList_doubleClicked(const QModelIndex &index);

    void on_pushButtonUpdate_clicked();

private:
    Ui::ShowPartialImagingListForm *ui;

	PartialImagingBase	*GetPartialImagingBase(void);
	void	ShowGrid(void);
	void	Release(void);
};

#endif // SHOWPARTIALIMAGINGLISTFORM_H
