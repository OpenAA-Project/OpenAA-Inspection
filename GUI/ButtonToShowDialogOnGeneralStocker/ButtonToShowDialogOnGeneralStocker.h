#ifndef BUTTONTOSHOWDIALOGONGENERALSTOCKER_H
#define BUTTONTOSHOWDIALOGONGENERALSTOCKER_H

#include "buttontoshowdialogongeneralstocker_global.h"
#include <QPushButton>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class	ButtonToShowDialogOnGeneralStocker : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;
	bool	LoadLastID;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	QString	Keyword;

	ButtonToShowDialogOnGeneralStocker(LayersBase *Base ,QWidget *parent);

	virtual void	Prepare(void)	override;

private slots:
	void SlotClicked (bool checked);
	void	ResizeAction();

private:
	int		GeneralStockerShowDialog(const QString& Keyword);
};

#endif // BUTTONTOSHOWDIALOGONGENERALSTOCKER_H
