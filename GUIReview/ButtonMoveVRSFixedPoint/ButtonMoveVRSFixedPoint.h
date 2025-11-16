#ifndef BUTTONMOVEVRSFIXEDPOINT_H
#define BUTTONMOVEVRSFIXEDPOINT_H

#include "buttonmovevrsfixedpoint_global.h"
#include <QLabel>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include <QEvent>
#include "XGUIPacketForDLL.h"
#include "mtToolButtonColored.h"

class	SignalOperandBit;
class	SignalOperandInt;

class	KeyedColorButton : public mtToolButtonColored
{
public:
	KeyedColorButton(bool ColorDialogOnLClick ,QWidget *parent = 0);
	KeyedColorButton(bool ColorDialogOnLClick ,const QColor &col ,QWidget *parent = 0);

	virtual	void leaveEvent ( QEvent * e )	override;
};

class	ButtonMoveVRSFixedPoint : public GUIFormBase
{
	Q_OBJECT

	KeyedColorButton	Button;

	SignalOperandBit	*oPushedOperand;
	SignalOperandInt	*iFixedXPos;
	SignalOperandInt	*iFixedYPos;

	int		LastX;
	int		LastY;
	DWORD	LastKeyTime;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	int32	XPos,YPos;
	bool	AbsoluteMode;
	bool	ToggleMode;
	int32	SysBitNumber;
	int32	SysRegisterXPos;
	int32	SysRegisterYPos;
	bool	ReleaseButtonOnOtherOperation;
	int32	ShortcutKey;

	ButtonMoveVRSFixedPoint(LayersBase *Base ,QWidget *parent);
	
	virtual void	Prepare(void)	override;
	virtual	void	SpecifiedDirectly(SpecifiedBroadcaster *v)	override;
private slots:
	void	SlotClicked (bool checked);
	void	ResizeAction();
private:
	virtual	void	keyPressEvent ( QKeyEvent * event )	override;
};

#endif // BUTTONMOVEVRSFIXEDPOINT_H
