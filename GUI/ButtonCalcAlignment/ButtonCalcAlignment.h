#ifndef BUTTONCALCALIGNMENT_H
#define BUTTONCALCALIGNMENT_H

#include "buttoncalcalignment_global.h"
#include <QLabel>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include <QPushButton>
#include <QString>
#include <QColor>
#include <QFont>

class	ButtonCalcAlignment : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;
	bool	SyncMode;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;

	ButtonCalcAlignment(LayersBase *Base ,QWidget *parent);
	
	virtual void	Prepare(void)	override;
	virtual	void	GetMenuInfo(MenuInfoContainer &Info)	override;
	virtual	void	ExecuteMenu(int ID)	override;

	virtual	void	RxSync(QByteArray &f)	override;
private slots:
	void	SlotClicked (bool checked);
	void	ResizeAction();
};

class	GUICmdPushedAlignment : public GUICmdPacketBase
{
public:

	GUICmdPushedAlignment(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
#endif // BUTTONCALCALIGNMENT_H
