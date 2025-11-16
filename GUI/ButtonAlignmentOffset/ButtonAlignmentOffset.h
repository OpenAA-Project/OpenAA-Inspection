#pragma once

#include "buttonalignmentoffset_global.h"
#include <QPushButton>
#include <QTranslator>
#include "XGUIFormBase.h"
#include "XGUIPacketForDLL.h"

class	SetAlignmentOffsetForm;

class	ButtonAlignmentOffset : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;
public:
	SetAlignmentOffsetForm	*Window;

	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	int32	MaxOffsetXDot;
	int32	MaxOffsetYDot;

	ButtonAlignmentOffset(LayersBase *Base ,QWidget *parent);
	~ButtonAlignmentOffset(void);
	virtual void	Prepare(void)	override;

private:

private slots:
	void	SlotClicked();
	void	ResizeAction();
};
//---------------------------------------------------------------------------------------------

class	GUICmdReqAlignmentOffset : public GUICmdPacketBase
{
public:
	GUICmdReqAlignmentOffset(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
class	GUICmdAckAlignmentOffset : public GUICmdPacketBase
{
public:
	int		OffsetX;
	int		OffsetY;

	GUICmdAckAlignmentOffset(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}	
};
class	GUICmdSetAlignmentOffset : public GUICmdPacketBase
{
public:
	int		OffsetX;
	int		OffsetY;

	GUICmdSetAlignmentOffset(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
