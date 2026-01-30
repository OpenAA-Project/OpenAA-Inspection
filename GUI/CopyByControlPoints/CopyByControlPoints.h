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

#pragma once

#include "copybycontrolpoints_global.h"
#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include <QToolButton>
#include <QIODevice>
#include <QString>
#include <QColor>
#include <QFont>
#include "XFromToInfo.h"

class	CopyByControlPoints : public GUIFormBase
{
    Q_OBJECT

	QToolButton	Button;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	bool	Mastered;
	QByteArray	FromToArray;
	QByteArray	AlgorithmRootName;
	FromToClass	FromToInfo;

	CopyByControlPoints(LayersBase *Base ,QWidget *parent = 0);
	~CopyByControlPoints();

	virtual void	Prepare(void)	override;

	void	CopyTopShadowLevel(void);
	void	CopyShadowLevelFromTop(void);

private:
	virtual	bool	ShowQByteArrayDialog(const QString &VariableName)	override;

private slots:
	void	SlotClicked (bool checked);
	void	ResizeAction();
};



//==================================================================

class	GUICmdReqAlgoDataWithControlPoints: public GUICmdPacketBase
{
public:
	int	Phase;
	int	ShadowLevel;
	int	ShadowNumber;
	RootNameListContainer	AlgorithmList;

	GUICmdReqAlgoDataWithControlPoints(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckAlgoDataWithControlPoints: public GUICmdPacketBase
{
public:
	XYPointContainerWithName	ControlPointsForPages;
	AlgoListArrayContainer	AlgoList;

	GUICmdAckAlgoDataWithControlPoints(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}	
};

class	GUICmdSetAlgoDataWithControlPoints: public GUICmdPacketBase
{
public:
	int	Phase;
	int	ShadowLevel;
	int	ShadowNumber;
	XYPointContainerWithName	ControlPointsForPages;
	AlgoListArrayContainer	AlgoList;

	GUICmdSetAlgoDataWithControlPoints(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};