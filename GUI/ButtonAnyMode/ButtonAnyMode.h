#ifndef BUTTONANYMODE_H
#define BUTTONANYMODE_H

#include "buttonanymode_global.h"
#include <QPushButton>
#include <QTranslator>
#include "XGUIFormBase.h"
#include "XGUIPacketForDLL.h"
#include <QToolButton>
#include <QString>
#include <QColor>
#include <QFont>

class	SignalOperandBit;

class	ButtonAnyMode : public GUIFormBase
{
	Q_OBJECT

	QToolButton	Button;
	DWORD	LastKeyTime;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	bool	DefaultPushed;
	int32	SystemRegisterNo;
	int32	ShortcutKey;

	ButtonAnyMode(LayersBase *Base ,QWidget *parent);
	~ButtonAnyMode(void);
	
	virtual void	Prepare(void)	override;

private:
	SignalOperandBit	*ioMode;
	virtual	void	keyPressEvent ( QKeyEvent * event )	override;
private slots:
	void	SlotToggled ( bool checked );
	void	ResizeAction();
};
#endif // BUTTONANYMODE_H
