#ifndef SHOWSEQMESSAGE_H
#define SHOWSEQMESSAGE_H

#include "showseqmessage_global.h"
#include <QLabel>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"


class	SignalOperandString;


class	ShowSeqMessage : public GUIFormBase
{
	Q_OBJECT

	QLabel	Label;

	SignalOperandString	*ioString;
public:
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	QString	AlignAttr;
	int32	SystemRegisterNo;

	enum	CAlignment{
		AlignLeft
		,AlignCenter
	};

	ShowSeqMessage(LayersBase *Base ,QWidget *parent);
	~ShowSeqMessage(void);
	
	virtual void	Prepare(void)	override;

private slots:
	void	ResizeAction();
	void	OperandChanged();
};

#endif // SHOWSEQMESSAGE_H
