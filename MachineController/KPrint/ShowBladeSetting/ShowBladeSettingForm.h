#ifndef SHOWBLADESETTINGFORM_H
#define SHOWBLADESETTINGFORM_H

#include "XGUIFormBase.h"
#include "XIntegrationBase.h"
#include "XDataInLayer.h"
#include "IntegrationLib.h"
#include "XGUIPacketForDLL.h"
#include <QModelIndex>

namespace Ui {
class ShowBladeSettingForm;
}

class	EasyPropertyDentMeasureForm;

class ShowBladeSettingForm : public GUIFormBase
{
    Q_OBJECT
    EasyPropertyDentMeasureForm	*PropertyForm;

public:
    explicit ShowBladeSettingForm(LayersBase *Base ,QWidget *parent = 0);
    ~ShowBladeSettingForm();
	virtual void	BuildForShow(void)	override;
    virtual void	StartPage	(void)	override;
private slots:
    void on_tableWidgetBladeWidth_doubleClicked(const QModelIndex &index);
    void on_tableWidgetBladeY_doubleClicked(const QModelIndex &index);
    void on_tableWidgetBladeX_doubleClicked(const QModelIndex &index);
    void on_tableWidgetBladeR_doubleClicked(const QModelIndex &index);

	void	ResizeAction();

private:
    Ui::ShowBladeSettingForm *ui;

    EasyPropertyDentMeasureForm *GetEasyPropertyDentMeasureForm(void);
};

#endif // SHOWBLADESETTINGFORM_H
