/*
 * Copyright (C) 2024
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


#ifndef BUTTONSAVEALGORITHM_H
#define BUTTONSAVEALGORITHM_H

#include "buttonsavealgorithm_global.h"
#include <QPushButton>
#include <QBuffer>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class	ButtonSaveAlgorithm : public GUIFormBase
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
	int32	WaitingMilisec;

	ButtonSaveAlgorithm(LayersBase *Base ,QWidget *parent);
	~ButtonSaveAlgorithm(void);
	
	virtual void	Prepare(void)		override;
	virtual	void	GetMenuInfo(MenuInfoContainer &Info)	override;
	virtual	void	ExecuteMenu(int ID)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override; 

	bool	SaveAlgo(const QString &AlgoRoot ,const QString &AlgoName
					,QIODevice *Buff);

private slots:
	void SlotClicked (bool checked);
	void	ResizeAction();
};

//============================================================================================

class	GUICmdReqAlgorithmData : public GUICmdPacketBase
{
public:
	QString	AlgorithmRoot;
	QString	AlgorithmName;


	GUICmdReqAlgorithmData(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendAlgorithmData : public GUICmdPacketBase
{
public:
	QBuffer	Data;

	GUICmdSendAlgorithmData(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class CmdReqAlgorithmData: public GUIDirectMessage
{
public:
	QString	AlgorithmRoot;
	QString	AlgorithmName;
	QIODevice	*Data;
	bool	RetSuccessful;

	CmdReqAlgorithmData(LayersBase *base):GUIDirectMessage(base)			{}
	CmdReqAlgorithmData(GUICmdPacketBase *gbase):GUIDirectMessage(gbase)	{}
};


#endif // BUTTONSAVEALGORITHM_H