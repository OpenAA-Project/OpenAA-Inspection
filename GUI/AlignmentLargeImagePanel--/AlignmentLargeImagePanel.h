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



#ifndef AlignmentLargeIMAGEPANEL_H
#define AlignmentLargeIMAGEPANEL_H

//#include "AlignmentLargeimagepanel_global.h"
#include "XDisplayImage.h"

#include <QToolButton>
#include <QToolBar>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonWithBalloon.h"
#include "XAlignmentLarge.h"



class	AlignmentLargeImagePanel : public DisplayImageWithAlgorithm
{
	bool	HasBitbuffData;
public:
	AlignmentLargeImagePanel(LayersBase *Base ,QWidget *parent);
	~AlignmentLargeImagePanel(void);

	virtual void	Prepare(void)	override;
	virtual	void	DrawEndAfterOperation(FlexArea &area)	override;
	virtual	AlgorithmDrawAttr	*CreateDrawAttrPointer(void)	override;
	virtual	void	ButtonExecuteDeleteSelected(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	virtual void	StartPage	(void)	override;

private:
	virtual	void	CanvasSlotOnPaint(QPainter &pnt)	override;
	virtual	void	MultiSelectBtnDown()	override;

	virtual	void	SelectArea(IntList &LayerList, FlexArea &Area)	override;
	virtual	void	ExeCutItems(FlexArea &Area)	override;

};

//=========================================================

class	GUICmdReqAlignmentLargeCheckBitBuff: public GUICmdPacketBase
{
public:
	GUICmdReqAlignmentLargeCheckBitBuff(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckAlignmentLargeCheckBitBuff : public GUICmdPacketBase
{
public:
	bool	HasData;

	GUICmdAckAlignmentLargeCheckBitBuff(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};
//===========================================================================
class	GUICmdSelectItemsAlignmentLarge : public GUICmdPacketBase	//アイテム選択要求コマンド
{
public:
	FlexArea	Area;
	bool		MultiSelect;
	IntList		AreaIDList;

	GUICmdSelectItemsAlignmentLarge(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
class	GUICmdCutItemsAlignmentLarge : public GUICmdPacketBase	//選択されたアイテム切り取り要求コマンド
{
public:
	FlexArea	Area;
	IntList		AreaIDList;
	bool		MultiSelect;

	GUICmdCutItemsAlignmentLarge(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
#endif // AlignmentLargeIMAGEPANEL_H