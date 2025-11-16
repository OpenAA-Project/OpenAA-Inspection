#ifndef SETZFORM_H
#define SETZFORM_H

#include "XGUIFormBase.h"
#include "ui_SetZForm.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class SetZForm : public GUIFormBase
{
	Q_OBJECT

public:
	int	ZHeight;
	int32	LimitMax;

	SetZForm(LayersBase *Base ,QWidget *parent = 0);
	~SetZForm();
	
	virtual void	Prepare(void)		override;
	virtual void	BuildForShow(void)	override;
	virtual	void	SpecifiedDirectly(SpecifiedBroadcaster *v)	override;
private:
	Ui::SetZFormClass ui;

private slots:
	void on_pushButtonOK_clicked();
};

#endif // SETZFORM_H
