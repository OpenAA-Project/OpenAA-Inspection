#ifndef BUTTONCLEARSTOCKEDRESULT_H
#define BUTTONCLEARSTOCKEDRESULT_H

#include "buttonclearstockedresult_global.h"

#include <QLabel>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include <QPushButton>

class	ButtonClearStockedResult : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;
	bool	SyncMode;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;

	ButtonClearStockedResult(LayersBase *Base ,QWidget *parent);
	
	virtual void	Prepare(void)	override;
	virtual	void	GetMenuInfo(MenuInfoContainer &Info)	override;
	virtual	void	ExecuteMenu(int ID)	override;

	virtual	void	RxSync(QByteArray &f)	override;
private slots:
	void	SlotClicked (bool checked);
	void	ResizeAction();
};

class	GUICmdPushedClearStockedResult : public GUICmdPacketBase
{
public:

	GUICmdPushedClearStockedResult(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif // BUTTONCLEARSTOCKEDRESULT_H
