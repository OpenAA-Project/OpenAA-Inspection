#pragma once

#include "buttonloadshiftmark_global.h"
#include <QPushButton>
#include <QBuffer>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class	ButtonLoadShiftMark : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;

public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;

	ButtonLoadShiftMark(LayersBase *Base ,QWidget *parent);
	~ButtonLoadShiftMark(void);
	
	virtual void	Prepare(void)	override;

	bool ExecuteLoad(QIODevice &F);
				  
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	void	GetMenuInfo(MenuInfoContainer &Info)		override;
	virtual	void	ExecuteMenu(int ID)	override;

private slots:
	void SlotClicked (bool checked);
	void	ResizeAction();
};


//============================================================================================

class	GUICmdLoadShiftMarkData : public GUICmdPacketBase
{
public:
	QBuffer	Data;

	GUICmdLoadShiftMarkData(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUIAckLoadShiftMarkData : public GUICmdPacketBase
{
public:
	bool	LoadingSuccessful;
	QString	ErrorMsg;

	GUIAckLoadShiftMarkData(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

class	ExecuteLoadShiftMarkByData : public GUIDirectMessage
{
public:
	QByteArray	Data;

	ExecuteLoadShiftMarkByData(LayersBase *base):GUIDirectMessage(base){}
};
