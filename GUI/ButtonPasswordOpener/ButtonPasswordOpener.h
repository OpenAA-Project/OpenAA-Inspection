#ifndef BUTTONPASSWORDOPENER_H
#define BUTTONPASSWORDOPENER_H

#include "buttonpasswordopener_global.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include<QString>
#include<QWidget>
#include<QColor>
#include<QFont>
#include<QPushButton>
#include "mtToolButtonColored.h"

class ButtonPasswordOpener : public GUIFormBase
{
	Q_OBJECT

	mtToolButtonColored	Button;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	int32	ExpiredTimeSec;
	QColor	LockedColor;
	QColor	UnlockedColor;

	ButtonPasswordOpener(LayersBase *Base ,QWidget *parent);
	~ButtonPasswordOpener(void);
	
	virtual void	Prepare(void)		override;
	virtual	void	GetMenuInfo(MenuInfoContainer &Info)	override;
	virtual	void	ExecuteMenu(int ID)	override;

protected:
	virtual	bool OnIdle(void)	override;
private slots:
	void SlotClicked (bool checked);
	void	ResizeAction();
};


#endif // BUTTONPASSWORDOPENER_H
