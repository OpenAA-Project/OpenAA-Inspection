#ifndef GENERALPANELFROMSEQ_H
#define GENERALPANELFROMSEQ_H

#include "generalpanelfromseq_global.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include <QThread>
#include "XServiceForLayers.h"
#include <QLabel>
#include <QColor>
#include <QTranslator>
#include <QString>
#include <QFont>
#include "XGUIFormBase.h"

class	SignalOperandString;

class	GeneralPanelFromSeq : public GUIFormBase
{
	Q_OBJECT

	QLabel	Label;
	QColor	PanelColor;
public:
	QTranslator Translator;
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	QString	AlignAttr;

	enum	CAlignment{
		AlignLeft
		,AlignCenter
	};
	SignalOperandString	*iMessageStr;
	SignalOperandString	*iColorStr;

	GeneralPanelFromSeq(LayersBase *Base ,QWidget *parent);
	~GeneralPanelFromSeq(void);

	virtual void	Prepare(void)	override;

protected:
	virtual	void	paintEvent ( QPaintEvent * event )	override;

private slots:
	void	ResizeAction();
	void	OperandChanged();
	void	OperandColorChanged();
};

#endif // GENERALPANELFROMSEQ_H
