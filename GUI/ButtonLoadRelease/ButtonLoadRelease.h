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

#ifndef BUTTONLOADRELEASE_H
#define BUTTONLOADRELEASE_H

#include "buttonloadrelease_global.h"
#include <QToolButton>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XLoadRelease.h"

class ButtonLoadRelease : public GUIFormBase
{
	Q_OBJECT

	QToolButton	Button;

	QByteArray		SettingDataArray;
public:
	bool	AllocateMasterBuff;
	bool	AllocateTargetBuff;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	LoadReleaseAlgoContainer	SettingData;
	bool	SwapInOut;
	QString	SwapPath;

public:
	ButtonLoadRelease(LayersBase *Base ,QWidget *parent);
	~ButtonLoadRelease();

	virtual void	Prepare(void)		override;
	virtual void	ReadyParam(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	void	GetMenuInfo(MenuInfoContainer &Info)	override;
	virtual	void	ExecuteMenu(int ID)	override;

	virtual	void	RxSync(QByteArray &f)	override;
private:

private slots:
	void SlotClicked (bool checked);
	void	ResizeAction();
	void	SlotExecuteForByteArray(const QString &Category ,const QString &KeyName ,QByteArray &data);
};

class	GUICmdReqRelease: public GUICmdPacketBase
{
public:
	bool						SwapInOut;
	QString						SwapPath;
	LoadReleaseAlgoContainer	SettingData;

	GUICmdReqRelease(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	

private:
	bool	SwapOutMasterData(int localPage,int phase);
	bool	SwapOutAlgorithmData(int localPage,int phase,AlgorithmInPageRoot *Pg);
};

class	GUICmdReqLoad: public GUICmdPacketBase
{
public:
	bool						SwapInOut;
	QString						SwapPath;
	LoadReleaseAlgoContainer	SettingData;

	GUICmdReqLoad(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);

private:
	bool	SwapInMasterData(int localPage,int phase);
	bool	SwapInAlgorithmData(int localPage,int phase,AlgorithmInPageRoot *Pg);
};

#endif // BUTTONLOADRELEASE_H