#ifndef BUTTONSELECTDATABASE_H
#define BUTTONSELECTDATABASE_H

#include "buttonselectdatabase_global.h"
#include <QPushButton>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class	ButtonSelectDatabase : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;

public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;

	ButtonSelectDatabase(LayersBase *Base ,QWidget *parent);
	~ButtonSelectDatabase(void);
	
	virtual void	Prepare(void)		override;
	virtual	void	GetMenuInfo(MenuInfoContainer &Info)	override;
	virtual	void	ExecuteMenu(int ID)	override;

private slots:
	void SlotClicked (bool checked);
	void	ResizeAction();
};
#endif // BUTTONSELECTDATABASE_H
