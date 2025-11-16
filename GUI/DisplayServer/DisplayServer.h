#ifndef DISPLAYSERVER_H
#define DISPLAYSERVER_H

#include "displayserver_global.h"
#include <QLabel>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class	DisplayServer :public GUIFormBase
{
    Q_OBJECT
	QLabel	HLabel;
public:
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;

	DisplayServer(LayersBase *Base ,QWidget *parent);
	
	virtual	void	Prepare(void)		override;
	virtual	void	BuildForShow(void)	override;

private slots:
	void	ResizeAction();
};
#endif // DISPLAYSERVER_H
