#ifndef BUTTONEXECUTEMACRO_H
#define BUTTONEXECUTEMACRO_H

#include "buttonexecutemacro_global.h"
#include <QLabel>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XMacroExecuter.h"
#include "XExecuteBatch.h"
#include <QPushButton>
#include <QString>
#include <QColor>
#include <QFont>

class	ButtonExecuteMacro : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;
	//MacroSentenseContainer	SContainer;
	BatchContainer			BatchData;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	QString	MacroFileName;
	QString	MacroFileNameByEditGUI;

	ButtonExecuteMacro(LayersBase *Base ,QWidget *parent);
	
	virtual void	Prepare(void)	override;
	virtual	void	GetMenuInfo(MenuInfoContainer &Info)	override;
	virtual	void	ExecuteMenu(int ID)	override;

public slots:
	void	SlotClicked (bool checked);
private slots:
	void	ResizeAction();
};

#endif // BUTTONEXECUTEMACRO_H
