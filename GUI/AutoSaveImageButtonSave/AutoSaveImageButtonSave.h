#ifndef AUTOSAVEIMAGEBUTTONSAVE_H
#define AUTOSAVEIMAGEBUTTONSAVE_H

#include "autosaveimagebuttonsave_global.h"
#include <QPushButton>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class	AutoSaveImageButtonSave : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;

public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	bool	MasterImage;

	AutoSaveImageButtonSave(LayersBase *Base ,QWidget *parent);
	~AutoSaveImageButtonSave(void);
	
	virtual void	Prepare(void)	override;
	virtual	void	GetMenuInfo(MenuInfoContainer &Info)	override;
	virtual	void	ExecuteMenu(int ID)	override;

private slots:
	void SlotClicked (bool checked);
	void	ResizeAction();
};

class	GUICmdSaveAutoSaveImage : public GUICmdPacketBase
{
public:
	bool	MasterImage;

	GUICmdSaveAutoSaveImage(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


#endif // AUTOSAVEIMAGEBUTTONSAVE_H
