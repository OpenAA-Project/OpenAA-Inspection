#ifndef WIZARDMASTERMENUFORM_H
#define WIZARDMASTERMENUFORM_H

#include "XGUIFormBase.h"
#include <QPushButton>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XIntegrationBase.h"
#include "XDataInLayer.h"
#include "IntegrationLib.h"
#include "XIntegrationPacketComm.h"


namespace Ui {
class WizardMasterMenuForm;
}

class	WizardMenuForm;

class WizardMasterMenuForm : public GUIFormBase,public IntegratorRelation
{
    Q_OBJECT
    
	WizardMenuForm	*Window;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	
	explicit WizardMasterMenuForm(LayersBase *Base ,QWidget *parent = 0);
    ~WizardMasterMenuForm();
    virtual void	Prepare(void)	override;
	virtual void	ReadyParam(void)override;

	virtual	void	SpecifiedDirectly(SpecifiedBroadcaster *v)	override;
	void	ExecuteSwitchImage(void);
private slots:
    void on_PushButtonMasterData_clicked();
	void	ResizeAction();
	void	SlotBusy();
	void	SlotIdle();
private:
    Ui::WizardMasterMenuForm *ui;
};

#endif // WIZARDMASTERMENUFORM_H
