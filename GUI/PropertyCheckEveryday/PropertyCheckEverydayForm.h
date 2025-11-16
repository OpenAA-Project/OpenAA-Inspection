#ifndef PROPERTYCHECKEVERYDAYFORM_H
#define PROPERTYCHECKEVERYDAYFORM_H

#include <QDialog>
#include "XCheckEveryday.h"
#include "XStandardPropertyForm.h"
#include "XGUIFormBase.h"
#include "XCheckEverydayGUIPacket.h"
#include "XCheckEverydayCommon.h"

namespace Ui {
class PropertyCheckEverydayForm;
}

class PropertyCheckEverydayForm : public GUIFormBase
{
    Q_OBJECT
    
public:
    explicit PropertyCheckEverydayForm(LayersBase *Base ,QWidget *parent = 0);
    ~PropertyCheckEverydayForm();

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	//virtual void	StartPage	(void)	override;

	CheckEverydayLightInfoContainer	InfoLight;
	CheckEverydayFocusInfoContainer	InfoFocus;
    
	virtual	void showEvent ( QShowEvent * event )	override;
	virtual void	BuildForShow(void)	override;
	CheckEverydayBase	*GetCheckEverydayBase(void);
	void ShowGrid(void);

private slots:
    void on_toolButtonLight_clicked();
    void on_toolButtonFocus_clicked();
    void on_pushButtonSave_clicked();

    void on_tableWidgetLight_clicked(const QModelIndex &index);
    void on_tableWidgetLight_doubleClicked(const QModelIndex &index);
    void on_tableWidgetFocus_clicked(const QModelIndex &index);
    void on_tableWidgetFocus_doubleClicked(const QModelIndex &index);

private:
    Ui::PropertyCheckEverydayForm *ui;
};

#endif // PROPERTYCHECKEVERYDAYFORM_H
