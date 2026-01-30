/*
 * Copyright (C) 2023
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


#ifndef BUTTONLOADALGORITHM_H
#define BUTTONLOADALGORITHM_H

#include "buttonloadalgorithm_global.h"
#include <QPushButton>
#include <QBuffer>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class	ButtonLoadAlgorithm : public GUIFormBase
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

	ButtonLoadAlgorithm(LayersBase *Base ,QWidget *parent);
	~ButtonLoadAlgorithm(void);
	
	virtual void	Prepare(void)	override;

	bool ExecuteLoad(QIODevice &F
				  ,QString _AlgorithmRoot ,QString _AlgorithmName);
				  
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	void	GetMenuInfo(MenuInfoContainer &Info)		override;
	virtual	void	ExecuteMenu(int ID)	override;

private slots:
	void SlotClicked (bool checked);
	void	ResizeAction();
};


//============================================================================================

class	GUICmdWriteAlgorithmData : public GUICmdPacketBase
{
public:
	QString	AlgorithmRoot;
	QString	AlgorithmName;
	QBuffer	Data;

	GUICmdWriteAlgorithmData(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
class	GUIAckWriteAlgorithmData : public GUICmdPacketBase
{
public:
	bool	Ok;
	QString	ErrorMsg;

	GUIAckWriteAlgorithmData(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	ExecuteLoadAlgorithm : public GUIDirectMessage
{
public:
	QString	AlgorithmRoot;
	QString	AlgorithmName;
	QString	FileName;

	ExecuteLoadAlgorithm(LayersBase *base):GUIDirectMessage(base){}
};

class	ExecuteLoadAlgorithmByData : public GUIDirectMessage
{
public:
	QString	AlgorithmRoot;
	QString	AlgorithmName;
	QByteArray	Data;

	ExecuteLoadAlgorithmByData(LayersBase *base):GUIDirectMessage(base){}
};

#endif // BUTTONLOADALGORITHM_H