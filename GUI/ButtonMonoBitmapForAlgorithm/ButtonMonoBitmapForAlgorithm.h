/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonMonoBitmapForAlgorithm\ButtonMonoBitmapForAlgorithm.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef BUTTONMONOBITMAPFORALGORITHM_H
#define BUTTONMONOBITMAPFORALGORITHM_H

#include "buttonmonobitmapforalgorithm_global.h"
#include <QPushButton>
#include <QBuffer>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"


class	ButtonMonoBitmapForAlgorithm : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;

public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	QString	AlgorithmRoot;
	QString	AlgorithmName;

	ButtonMonoBitmapForAlgorithm(LayersBase *Base ,QWidget *parent);
	~ButtonMonoBitmapForAlgorithm(void);
	
	virtual void	Prepare(void)	override;

private slots:
	void SlotClicked (bool checked);
	void	ResizeAction();
};

//============================================================================================

class	GUICmdReqMonoBitmapForAlgorithm : public GUICmdPacketBase
{
public:
	int		GlobalPage;
	QString	AlgorithmRoot;
	QString	AlgorithmName;
	int32	DotPerLine;
	int32	XByte;
	int32	MaxLines;

	GUICmdReqMonoBitmapForAlgorithm(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendMonoBitmapForAlgorithm : public GUICmdPacketBase
{
public:
	int		GlobalPage;
	QBuffer	Data;

	GUICmdSendMonoBitmapForAlgorithm(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif // BUTTONMONOBITMAPFORALGORITHM_H
