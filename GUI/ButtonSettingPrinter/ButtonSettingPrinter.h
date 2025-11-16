#ifndef BUTTONSETTINGPRINTER_H
#define BUTTONSETTINGPRINTER_H

#include "buttonsettingprinter_global.h"
#include <QPushButton>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"


class	ButtonSettingPrinter : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;

public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;

	ButtonSettingPrinter(LayersBase *Base ,QWidget *parent);
	~ButtonSettingPrinter(void);
	
	virtual void	Prepare(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	void	GetMenuInfo(MenuInfoContainer &Info)	override;
	virtual	void	ExecuteMenu(int ID)	override;

private:

private slots:
	void SlotClicked (bool checked);
	void	ResizeAction();
};

#endif // BUTTONSETTINGPRINTER_H
