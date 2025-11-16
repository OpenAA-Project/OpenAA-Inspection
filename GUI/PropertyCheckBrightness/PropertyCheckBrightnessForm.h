#ifndef PROPERTYCHECKBRIGHTNESSFORM_H
#define PROPERTYCHECKBRIGHTNESSFORM_H

#include <QWidget>
#include <QDialog>
#include "XGUIFormBase.h"
#include "XGUIPacketForDLL.h"
#include"XPropertyCheckBrightnessPacket.h"

namespace Ui {
class PropertyCheckBrightnessForm;
}

class PropertyCheckBrightnessForm : public GUIFormBase
{
    Q_OBJECT
    CheckBrightnessInfoContainer	GridList;

public:
    explicit PropertyCheckBrightnessForm(LayersBase *Base ,QWidget *parent = 0);
    ~PropertyCheckBrightnessForm();
    
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual void	BuildForShow(void)		override;
private slots:
    void on_tableWidget_clicked(const QModelIndex &index);
    void on_tableWidget_doubleClicked(const QModelIndex &index);

private:
    Ui::PropertyCheckBrightnessForm *ui;

	void	ShowItemGrid(void);
};

#endif // PROPERTYCHECKBRIGHTNESSFORM_H
