#ifndef BUTTONSHOWPLAYERINSIDE_H
#define BUTTONSHOWPLAYERINSIDE_H

#include "buttonshowplayerinside_global.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include <QPushButton>
#include <QString>
#include <QColor>
#include <QFont>

class	ButtonShowPlayerInside : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;

	ButtonShowPlayerInside(LayersBase *Base ,QWidget *parent);
	
	virtual void	Prepare(void)	override;

private:

private slots:
	void	SlotClicked (bool checked);
	void	ResizeAction();
};

#endif // BUTTONSHOWPLAYERINSIDE_H
