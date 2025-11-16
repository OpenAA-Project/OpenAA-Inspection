#ifndef BUTTONSETMACHINE_H
#define BUTTONSETMACHINE_H

#include "buttonsetmachine_global.h"
#include <QLabel>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonColored.h"

class	ButtonSetMachine : public GUIFormBase
{
	Q_OBJECT

	mtToolButtonColored	Button;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	int32	MachineID;

	ButtonSetMachine(LayersBase *Base ,QWidget *parent);
	
	virtual void	Prepare(void)		override;
	bool			SetMachineID(int ID);
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

private slots:
	void	SlotClicked (bool checked);
	void	ResizeAction();
};

class	CmdButtonUp	:public GUIDirectMessage
{
public:
	CmdButtonUp(LayersBase *base):GUIDirectMessage(base){}
};

#endif // BUTTONSETMACHINE_H
