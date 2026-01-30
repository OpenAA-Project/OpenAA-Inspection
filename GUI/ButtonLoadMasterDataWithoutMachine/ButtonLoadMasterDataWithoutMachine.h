/*
 * Copyright (C) 2022
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef BUTTONLOADMASTERDATAWITHOUTMACHINE_H
#define BUTTONLOADMASTERDATAWITHOUTMACHINE_H

#include "buttonloadmasterdatawithoutmachine_global.h"
#include <QPushButton>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class	SignalOperandInt;
class	SignalOperandBit;
class LoadMasterDataWindow;

class	ButtonLoadMasterDataWithoutMachine : public GUIFormBase
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
	bool	InitializeAfterEdit;
	bool	ShowSelectToLoadImage;
	QStringList	IncludedMachines;
	bool	ReleaseAutoMode;

	ButtonLoadMasterDataWithoutMachine(LayersBase *Base ,QWidget *parent);
	~ButtonLoadMasterDataWithoutMachine(void);
	
	virtual void	Prepare(void)		override;

	virtual	void	GetMenuInfo(MenuInfoContainer &Info)	override;
	virtual	void	ExecuteMenu(int ID)	override;

	virtual	void	RxSync(QByteArray &f)	override;
	void	CommandLoadMaster(int MasterCode,bool	ModeLoadMasterImage);

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


#endif // BUTTONLOADMASTERDATAWITHOUTMACHINE_H