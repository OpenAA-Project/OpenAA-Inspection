#ifndef SHOWCOUNTFROMPIFORM_H
#define SHOWCOUNTFROMPIFORM_H

#include "XGUIFormBase.h"
#include "XIntegrationBase.h"
#include "XDataInLayer.h"
#include "IntegrationLib.h"
#include "XGUIPacketForDLL.h"
#include <QModelIndex>
#include <QTimer>
#include "XCommToTrigger.h"

namespace Ui {
class ShowCountFromPIForm;
}

class CartonMenuForm;
class WindowMismatchForm;

class ShowCountFromPIForm : public GUIFormBase
{
    Q_OBJECT

    QTimer  TM;
    CartonMenuForm	*CartonProp;
	WindowMismatchForm  *WindowMismatchFormInst;
public:
    explicit ShowCountFromPIForm(LayersBase *Base ,QWidget *parent = nullptr);
    ~ShowCountFromPIForm();

	virtual void	ReadyParam(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)  override;
	virtual	void	SpecifiedDirectly(SpecifiedBroadcaster *v)	override;

private slots:
	void	ResizeAction();
    void    SlotTimeOut();
private:
    Ui::ShowCountFromPIForm *ui;

    void    ShowMismatch(void);
};

#endif // SHOWCOUNTFROMPIFORM_H
