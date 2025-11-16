/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonLoadMasterData\ButtonLoadMasterData.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef BUTTONLOADMASTERDATA_H
#define BUTTONLOADMASTERDATA_H

#include "buttonloadmasterdata_global.h"
#include <QPushButton>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class	SignalOperandInt;
class	SignalOperandBit;
class LoadMasterDataWindow;

class	ButtonLoadMasterData : public GUIFormBase
{
	Q_OBJECT

	friend class LoadMasterDataWindow;

	QPushButton	Button;
	SignalOperandInt	*iExeLoadMasterData;
	SignalOperandBit	*iOnLoading;

public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	bool	ShowLoadedInfo;
	bool	EnableManyTimes;
	QString	SelectLotSRoot;
	QString	SelectLotSName;
	QString	SelectMachineSRoot;
	QString	SelectMachineSName;
	bool	InitializeAfterEdit;
	bool	ShowSelectToLoadImage;
	bool	ReleaseAutoMode;

	ButtonLoadMasterData(LayersBase *Base ,QWidget *parent);
	~ButtonLoadMasterData(void);
	
	virtual void	Prepare(void)		override;

	virtual	void	GetMenuInfo(MenuInfoContainer &Info)	override;
	virtual	void	ExecuteMenu(int ID)	override;

	virtual	void	RxSync(QByteArray &f)	override;
	void	CommandLoadMaster(int MasterCode,bool	ModeLoadMasterImage,bool SilentMode);

public slots:
	void SlotClicked (bool checked);
	void	OperandExeLoadMAsterData();
private slots:
	void	ResizeAction();
	void	SlotShowInfo(void);
signals:
	void	SignalShowInfo(void);

};


class	GUICmdSendInitialXYPixelsData : public GUICmdPacketBase
{
public:
	int		DotPerLine;
	int		MaxLines;

	GUICmdSendInitialXYPixelsData(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


#endif // BUTTONLOADMASTERDATA_H
