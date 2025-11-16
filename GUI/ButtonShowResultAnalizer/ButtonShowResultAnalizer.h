#ifndef BUTTONSHOWRESULTANALIZER_H
#define BUTTONSHOWRESULTANALIZER_H

#include "buttonshowresultanalizer_global.h"
#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include <QToolButton>
#include <QString>
#include <QColor>
#include <QFont>

class  ButtonShowResultAnalizer : public GUIFormBase
{
    Q_OBJECT

	QToolButton	Button;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;

	ButtonShowResultAnalizer(LayersBase *Base ,QWidget *parent = 0);
	~ButtonShowResultAnalizer();

	virtual void	Prepare(void)	override;
private:

private slots:
	void SlotClicked (bool checked);
	void	ResizeAction();
};

#endif // BUTTONSHOWRESULTANALIZER_H
