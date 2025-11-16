#ifndef PROPERTYSKIPMARKFORM_H
#define PROPERTYSKIPMARKFORM_H

#include <QWidget>
#include <QDialog>
#include "XGUIFormBase.h"
#include "XGUIPacketForDLL.h"
#include"XPropertySkipMarkPacket.h"

namespace Ui {
class PropertySkipMarkForm;
}

class PropertySkipMarkForm : public GUIFormBase
{
    Q_OBJECT

	SkipMarkInfoContainer	GridList;
public:
    explicit PropertySkipMarkForm(LayersBase *Base ,QWidget *parent = 0);
    ~PropertySkipMarkForm();

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual void	BuildForShow(void)							override;

private slots:
    void on_tableWidgetList_clicked(const QModelIndex &index);
    void on_tableWidgetList_doubleClicked(const QModelIndex &index);

	void	AddDestination();
	void	AddSource();

private:
    Ui::PropertySkipMarkForm *ui;
	void	ShowItemGrid(void);
};

#endif // PROPERTYSKIPMARKFORM_H
