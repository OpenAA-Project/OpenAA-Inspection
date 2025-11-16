#ifndef PROPERTYTREEMASTERFORM_H
#define PROPERTYTREEMASTERFORM_H

#include <QWidget>
#include "XGUIFormBase.h"
#include "XTreeMasterPacket.h"


namespace Ui {
    class PropertyTreeMasterForm;
}

class PropertyTreeMasterForm : public GUIFormBase
{
    Q_OBJECT

public:
    explicit PropertyTreeMasterForm(LayersBase *base,QWidget *parent = 0);
    ~PropertyTreeMasterForm();

	virtual	void	BuildForShow(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual void	ShowInEdit(void)	override;
	
	void ShowGridList(void);
private slots:
    void on_pushButtonAddNewCat_clicked();
    void on_tableWidgetCatList_clicked(const QModelIndex &index);
    void on_tableWidgetCatList_doubleClicked(const QModelIndex &index);
	void	SlotSelectLine(void);
	void	SlotRemoveLine(void);
	void	SlotViewLine(void);

private:
    Ui::PropertyTreeMasterForm *ui;
	TreeMasterBase	*GetTreeMasterBase(void);

	TreeMasterListForPacketPack	TreeMasterInfo;

};

//=================================================================================



#endif // PROPERTYTREEMASTERFORM_H
