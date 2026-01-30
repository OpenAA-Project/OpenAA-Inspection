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


#ifndef AUTOALIGNMENTIMAGEPANEL_H
#define AUTOALIGNMENTIMAGEPANEL_H

#include "autoalignmentimagepanel_global.h"
#include "XDisplayImage.h"

#include <QToolButton>
#include <QToolBar>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonWithBalloon.h"
#include "XAutoAlignment.h"

class	AutoAlignmentImagePanel : public DisplayImageWithAlgorithm,public FunctionServerClass
{
	Q_OBJECT

public:
	int		ClickAreaSize;

	AutoAlignmentImagePanel(LayersBase *Base ,QWidget *parent);

	virtual void	Prepare(void)	override;
	virtual void	DrawEndAfterOperation(FlexArea &area)		override;
	virtual	AlgorithmDrawAttr	*CreateDrawAttrPointer(void)	override;
	virtual void	StartPage(void)	override;
	virtual void	ExecuteActiveOnItemXY(int globalX ,int globalY)	override;

	virtual	void	RequireHooks(GUIFormBase *mother)	override;
	void	ExecuteDrawEnd(FlexArea &Area);

private slots:
};

class	GUICmdReqAutoAlignmentInfoOnPoint : public GUICmdPacketBase
{
public:
	int	localX,localY;

	GUICmdReqAutoAlignmentInfoOnPoint(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendAutoAlignmentInfoOnPoint : public GUICmdPacketBase
{
public:
	int	ShiftXFromMaster,ShiftYFromMaster;
	int	ShiftXFromTarget,ShiftYFromTarget;
	int	ShiftRelativeXFromMaster,ShiftRelativeYFromMaster;
	int	ShiftRelativeXFromTarget,ShiftRelativeYFromTarget;

	GUICmdSendAutoAlignmentInfoOnPoint(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	void	MakeData(int localPage ,int localX,int localY);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


#endif // AUTOALIGNMENTIMAGEPANEL_H