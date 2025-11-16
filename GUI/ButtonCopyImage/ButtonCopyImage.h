#ifndef BUTTONCOPYIMAGE_H
#define BUTTONCOPYIMAGE_H

#include "buttoncopyimage_global.h"
#include <QLabel>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include <QPushButton>

class	ButtonCopyImage : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;
	bool	SyncMode;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	QString	CopyMode;

	ButtonCopyImage(LayersBase *Base ,QWidget *parent);
	
	virtual void	Prepare(void)	override;
	virtual	void	GetMenuInfo(MenuInfoContainer &Info)	override;
	virtual	void	ExecuteMenu(int ID)	override;

	virtual	void	RxSync(QByteArray &f)	override;
public slots:
	void	SlotClicked (bool checked);
private slots:
	void	ResizeAction();
};

class	GUICmdReqButtonCopyImage : public GUICmdPacketBase
{
public:
	QString	CopyMode;

	GUICmdReqButtonCopyImage(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif // BUTTONCOPYIMAGE_H
