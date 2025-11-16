#ifndef EASYLEVELALLOCATIONFORM_H
#define EASYLEVELALLOCATIONFORM_H

#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XIntegrationBase.h"


namespace Ui {
class EasyLevelAllocationForm;
}

class EasyLevelAllocationForm : public GUIFormBase
{
    Q_OBJECT
    
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	
	explicit EasyLevelAllocationForm(LayersBase *Base ,QWidget *parent = 0);
    ~EasyLevelAllocationForm();
    virtual	void	Prepare(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet) override;

private slots:
    void on_PushButtonOpen_clicked();
	void	ResizeAction();
private:
    Ui::EasyLevelAllocationForm *ui;
};

class	IntegrationShowLevelDialog : public GUIDirectMessage
{
public:
	IntegrationShowLevelDialog(LayersBase *base):GUIDirectMessage(base){}
	IntegrationShowLevelDialog(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

#endif // EASYLEVELALLOCATIONFORM_H
