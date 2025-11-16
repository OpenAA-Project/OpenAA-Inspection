#pragma once

#include "buttonswitchphasesynchronize_global.h"
#include <QToolButton>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class ButtonSwitchPhaseSynchronize : public GUIFormBase
{
	Q_OBJECT

	QToolButton	Button;

public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;

public:
	ButtonSwitchPhaseSynchronize(LayersBase *Base ,QWidget *parent);
	~ButtonSwitchPhaseSynchronize();

	virtual void	Prepare		(void)	override;
	virtual void	ShowInEdit	(void)	override;
	virtual	void	GetMenuInfo(MenuInfoContainer &Info)	override;
	virtual	void	ExecuteMenu(int ID)	override;
private:

private slots:
	void SlotClicked (bool checked);
	void	ResizeAction();
};


class	GUICmdSwitchPhaseSynchronize: public GUICmdPacketBase
{
public:
	bool	SwitchPhaseSynchronize;

	GUICmdSwitchPhaseSynchronize(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};