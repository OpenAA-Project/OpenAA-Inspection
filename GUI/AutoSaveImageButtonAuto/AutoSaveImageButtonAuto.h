#ifndef AUTOSAVEIMAGEBUTTONAUTO_H
#define AUTOSAVEIMAGEBUTTONAUTO_H

#include "autosaveimagebuttonauto_global.h"
#include <QPushButton>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include <QToolButton>

class	AutoSaveImageButtonAuto : public GUIFormBase
{
	Q_OBJECT

	QToolButton	Button;

public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	bool	NormallyON;

	AutoSaveImageButtonAuto(LayersBase *Base ,QWidget *parent);
	~AutoSaveImageButtonAuto(void);
	
	virtual void	Prepare(void)	override;

	virtual	void	GetMenuInfo(MenuInfoContainer &Info)	override;
	virtual	void	ExecuteMenu(int ID)	override;

private slots:
	void SlotClicked (bool checked);
	void	ResizeAction();
};

class	GUICmdSaveAutoSaveMode : public GUICmdPacketBase
{
public:
	bool	AutoSaveON;

	GUICmdSaveAutoSaveMode(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif // AUTOSAVEIMAGEBUTTONAUTO_H
