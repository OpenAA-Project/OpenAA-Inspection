#ifndef BUTTONEXECUTECOMMAND_H
#define BUTTONEXECUTECOMMAND_H

#include "buttonexecutecommand_global.h"
#include <QPushButton>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class	ButtonExecuteCommand : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;

public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;

	QString		ExecutableProgram;
	QStringList	ArgumentParam;
	QString		WorkingPath;

	ButtonExecuteCommand(LayersBase *Base ,QWidget *parent);
	~ButtonExecuteCommand(void);
	virtual void	Prepare(void)	override;

	void	Execute(void);
	virtual void	TransmitDirectly(GUIDirectMessage *packet)	override;
public slots:
	void SlotClicked (bool checked);

private slots:
	void	ResizeAction();
};

#endif // BUTTONEXECUTECOMMAND_H
