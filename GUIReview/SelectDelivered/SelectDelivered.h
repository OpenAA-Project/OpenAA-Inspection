#ifndef SELECTDELIVERED_H
#define SELECTDELIVERED_H

#include "selectdelivered_global.h"
#include <QLabel>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include <QEvent>
#include "XGUIPacketForDLL.h"
#include "mtToolButtonColored.h"



class	SelectDelivered: public GUIFormBase
{
	Q_OBJECT

	mtToolButtonColored		*Buttons[256];
public:
	QStringList				AttrMessages;			
	int						ButtonCount;
	QColor	CharColor;
	QFont	CFont;


	SelectDelivered(LayersBase *Base ,QWidget *parent);
	~SelectDelivered();

	virtual void	Prepare(void)	override;
private:

private slots:
	void	SlotClicked ();
	void	ResizeAction();
};

#endif // SELECTDELIVERED_H
