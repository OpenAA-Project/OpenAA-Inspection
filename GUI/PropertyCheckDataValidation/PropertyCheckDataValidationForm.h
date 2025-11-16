#ifndef PROPERTYCHECKDATAVALIDATIONFORM_H
#define PROPERTYCHECKDATAVALIDATIONFORM_H

#include <QWidget>
#include <QModelIndex>
#include "XGUIFormBase.h"
#include "XCheckDataValidation.h"
#include "XPropertyCheckDataValidationPacket.h"

namespace Ui {
class PropertyCheckDataValidationForm;
}

class ShowNGMessageForm;

class PropertyCheckDataValidationForm : public GUIFormBase
{
    Q_OBJECT

    CheckDataValidationGridListContainer    GridList;
    bool    ModeShowNGMessage;
public:
    explicit PropertyCheckDataValidationForm(LayersBase *Base ,QWidget *parent = nullptr);
    ~PropertyCheckDataValidationForm();

    virtual void	ReadyParam(void)    override;
 	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual void	ShowInEdit(void)	override;
	virtual void	BuildForShow(void)	override;
	virtual void	StartPage	(void)	override;

private slots:
    void on_toolButtonExistItemArea_clicked();
    void on_toolButtonExistItemVector_clicked();
    void on_toolButtonMinMax_clicked();
    void on_toolButtonProhibiteItem_clicked();
    void on_tableWidget_clicked(const QModelIndex &index);
    void on_tableWidget_doubleClicked(const QModelIndex &index);
    void    SlotShowNGMessage(int phase ,int page);
private:
    Ui::PropertyCheckDataValidationForm *ui;
    ShowNGMessageForm   *NGMessageWindow;

    CheckDataValidationBase	*GetCheckDataValidationBase(void);

    void ShowList(void);
    void ReDrawImage(void);
};

#endif // PROPERTYCHECKDATAVALIDATIONFORM_H
