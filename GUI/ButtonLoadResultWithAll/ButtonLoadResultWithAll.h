#ifndef BUTTONLOADRESULTWITHALL_H
#define BUTTONLOADRESULTWITHALL_H

#include "buttonloadresultwithall_global.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include <QPushButton>
#include <QString>
#include <QColor>
#include <QFont>

class	ButtonLoadResultWithAll : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	QString FileName;

	ButtonLoadResultWithAll(LayersBase *Base ,QWidget *parent);
	
	virtual void	Prepare(void)	override;

	bool	LoadRWA(QString LFileName);

private slots:
	void	SlotClicked (bool checked);
	void	ResizeAction();
};
#endif // BUTTONLOADRESULTWITHALL_H
