#ifndef SHOWCURRENTTIME_H
#define SHOWCURRENTTIME_H

#include "showcurrenttime_global.h"
#include <QLabel>
#include <QColor>
#include <QFont>
#include "XGUIFormBase.h"
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class	ShowCurrentTime : public GUIFormBase
{
	Q_OBJECT

	QLabel	MessageTime;
	int		IdleCount;
public:
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;

	ShowCurrentTime(LayersBase *Base ,QWidget *parent);
	virtual void	Prepare(void)	override;

	void	ShowMessage(void);

	virtual	bool OnIdle(void)	override;
private slots:
	void	ResizeAction();

signals:
	void	SignalCycleTime(double FPS);
};
#endif // SHOWCURRENTTIME_H
