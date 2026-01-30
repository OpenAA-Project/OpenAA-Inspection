/*
 * Copyright (C) 2025
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

#include "shrinklowhigh_global.h"
#include "XShadowTree.h"
#include "XDataInLayer.h"

class GUIFormBase;

class  CalcMethod
{
public:
	enum __Method
	{
		_AdoptHigh		=0
		,_AdoptLow		=1
		,_AdoptAverage	=2
	}Method;

	CalcMethod(void){	Method=_AdoptHigh;	}

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class ShrinkLowHigh : public LayersBase
{
	GUIFormBase	*MainForm;
public:
	int32	SkipDot;
	bool	HorizontalTile;
	bool	VerticalTile;
	bool	AddSystemMenu;
	CalcMethod	*LayerMethod;
	int32		LayerMethodNumb;

    ShrinkLowHigh(int ShadowNumber ,LayersBase *base);

	virtual	bool	InitialInShadow(void)			override;
	virtual	void	ShowShadow(void)				override;
	virtual	void	ConvertToTop(int32 &x ,int32 &y)			override;
	virtual	void	ConvertToLocal(int32 &TopX ,int32 &TopY)	override;
	virtual	bool	SaveShadowParam(QIODevice *f)	override;
	virtual	bool	LoadShadowParam(QIODevice *f)	override;

	virtual	ExeResult	ExecuteInitialAfterEdit	(ExecuteInitialAfterEditInfo &EInfo,bool ProgressStep=true)	override;
	virtual	ExeResult	ExecuteCaptured(ListPhasePageLayerPack &CapturedList ,bool ProgressStep=true)	override;

	virtual	void	CopyShadowImageFromParentInChild(bool Mastered ,int MasterNo
													,DataInPage *SrcPg
													,int Phase ,int Page)	override;
	void	SetSkipDot(int skipdot);
protected:
	virtual	void	ChildCopyParamGlobalFromParent(ParamGlobal *ParentParam)	override;
	virtual	void	ShadeMakeImageNGCircleInChild(QImage *tNGDataInTop ,QPainter *tPntFromNGDataInTop
									,int dtype		//DisplayImage::DisplayType
									,int Gx1,int Gy1 ,int Gx2,int Gy2
									,int MovXInTop,int MovYInTop, double ZoomRateInTop
									,int localPage
									,bool RedCircleMode
									,bool ShowNGMarkInTarget
									,bool &RetNGData
									,int ShadowNumber)	override;
	virtual	bool	ReallocXYPixelsShadowInChild(int NewDotPerLine ,int NewMaxLines)		override;
	virtual	bool	ReallocateShadow(int newPhaseNumb , int newPageNumb ,int newLayerNumb)	override;
private:
	void	CopyFilterdCopyHigh		(ImageBuffer &DstImage ,ImageBuffer &SrcImage,int Skip);
	void	CopyFilterdCopyLow		(ImageBuffer &DstImage ,ImageBuffer &SrcImage,int Skip);
	void	CopyFilterdCopyAverage	(ImageBuffer &DstImage ,ImageBuffer &SrcImage,int Skip);
};