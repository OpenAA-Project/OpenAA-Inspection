#ifndef PROPERTYREPEATCONTROLFORM_H
#define PROPERTYREPEATCONTROLFORM_H

#include <QModelIndex>
#include "XGUIFormBase.h"
#include "XPropertyRepeatControlPacket.h"

namespace Ui {
class PropertyRepeatControlForm;
}

class RepeatControlBase;

class PropertyRepeatControlForm : public GUIFormBase
{
    Q_OBJECT

    RepeatControlInfoListContainer  ItemList;
public:
    explicit PropertyRepeatControlForm(LayersBase *Base,QWidget *parent = nullptr);
    ~PropertyRepeatControlForm();

    virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override; 
	virtual void	BuildForShow(void)	override;
	virtual void	StartPage	(void)	override;

    void    CreateWhole(int RepeatCount);
private slots:
    void on_tableWidgetList_clicked(const QModelIndex &index);
    void on_tableWidgetList_doubleClicked(const QModelIndex &index);
    void on_pushButtonCreateWhole_clicked();

private:
    Ui::PropertyRepeatControlForm *ui;

    void	ShowList(void);
    RepeatControlBase	*GetRepeatControlBase(void);
};

#endif // PROPERTYREPEATCONTROLFORM_H
