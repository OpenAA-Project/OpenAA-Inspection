#ifndef BUTTONPASSWORDENABLER_H
#define BUTTONPASSWORDENABLER_H

#include "buttonpasswordenabler_global.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include<QString>
#include<QWidget>
#include<QColor>
#include<QFont>
#include<QPushButton>

class ButtonPasswordEnabler : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;

	ButtonPasswordEnabler(LayersBase *Base ,QWidget *parent);
	~ButtonPasswordEnabler(void);
	
	virtual void	Prepare(void)		override;
	virtual	void	GetMenuInfo(MenuInfoContainer &Info)	override;
	virtual	void	ExecuteMenu(int ID)	override;


private slots:
	void SlotClicked (bool checked);
	void	ResizeAction();
};


#endif // BUTTONPASSWORDENABLER_H
