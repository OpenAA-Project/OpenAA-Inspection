#pragma once

#include "controlmultispectralscanner_global.h"
#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include <QToolButton>
#include <QIODevice>
#include <QString>
#include <QColor>
#include <QFont>

class	SignalOperandInt;
class	SignalOperandBit;

class	ControlMultiSpectralScanner : public GUIFormBase
{
    Q_OBJECT

	QToolButton	Button;

	SignalOperandInt    *ioJDimL;
	SignalOperandInt    *ioJDimH;
	SignalOperandInt    *ioConstV;
    SignalOperandBit    *ioOK;

public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;

	ControlMultiSpectralScanner(LayersBase *Base ,QWidget *parent = 0);
	~ControlMultiSpectralScanner();

	virtual void	Prepare(void)	override;
private:

private slots:
	void SlotClicked (bool checked);
	void	ResizeAction();
};
