#ifndef BUTTONGENERALSTOCKER_H
#define BUTTONGENERALSTOCKER_H

#include "buttongeneralstocker_global.h"
#include <QPushButton>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XGUIFormBase.h"
#include "XGUIPacketForDLL.h"

class	ButtonGeneralStocker : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;

public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	QString	Keyword;

	ButtonGeneralStocker(LayersBase *Base ,QWidget *parent);
	~ButtonGeneralStocker(void);
	
	virtual void	Prepare(void)	override;
	virtual	void	GetMenuInfo(MenuInfoContainer &Info)	override;
	virtual	void	ExecuteMenu(int ID)	override;
	void	CommandTransfer(void);
private slots:
	void SlotClicked (bool checked);
	void	ResizeAction();
};

class	GUICmdSendGeneralStockerData : public GUICmdPacketBase
{
public:
	QByteArray	Data;

	GUICmdSendGeneralStockerData(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif // BUTTONGENERALSTOCKER_H
