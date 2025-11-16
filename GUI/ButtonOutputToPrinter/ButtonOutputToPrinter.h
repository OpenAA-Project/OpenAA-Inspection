#ifndef BUTTONOUTPUTTOPRINTER_H
#define BUTTONOUTPUTTOPRINTER_H

#include "buttonoutputtoprinter_global.h"
#include <QPushButton>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"


class	ButtonOutputToPrinter : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;

public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;

	ButtonOutputToPrinter(LayersBase *Base ,QWidget *parent);
	~ButtonOutputToPrinter(void);
	
	virtual void	Prepare(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	void	GetMenuInfo(MenuInfoContainer &Info)		override;
	virtual	void	ExecuteMenu(int ID)	override;

private:

private slots:
	void SlotClicked (bool checked);
	void	ResizeAction();
};

#endif // BUTTONOUTPUTTOPRINTER_H
