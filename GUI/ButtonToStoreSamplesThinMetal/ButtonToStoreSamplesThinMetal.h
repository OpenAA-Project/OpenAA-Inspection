#ifndef BUTTONTOSTORESAMPLESTHINMETAL_H
#define BUTTONTOSTORESAMPLESTHINMETAL_H

#include "buttontostoresamplesthinmetal_global.h"
#include <QPushButton>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XYCross.h"

class	ButtonToStoreSamplesThinMetal : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;

public:

	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	bool	Additional;

	ButtonToStoreSamplesThinMetal(LayersBase *Base ,QWidget *parent);
	~ButtonToStoreSamplesThinMetal(void);
	
	virtual void	Prepare(void)		override;

	virtual	void	GetMenuInfo(MenuInfoContainer &Info)	override;
	virtual	void	ExecuteMenu(int ID)	override;

private slots:
	void SlotClicked (bool checked);
	void	ResizeAction();
};


class	GUICmdStoreSamplesThinMetalStart: public GUICmdPacketBase
{
public:

	GUICmdStoreSamplesThinMetalStart(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdStoreSamplesThinMetal: public GUICmdPacketBase
{
public:
	int		Judgement;
	QString	JudgeStr;
	QString	TargetFolder;
	QString	TargetFileName;

	GUICmdStoreSamplesThinMetal(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdStoreSamplesThinMetalEnd: public GUICmdPacketBase
{
public:

	GUICmdStoreSamplesThinMetalEnd(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif // BUTTONTOSTORESAMPLESTHINMETAL_H
