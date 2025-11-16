#pragma once

#include "shrinkedinspection_global.h"
#include "XShadowTree.h"
#include "XDataInLayer.h"
#include "XTransform.h"

class GUIFormBase;

class ShrinkedInspection : public LayersBase
{
	GUIFormBase	*MainForm;
public:
	int32	SkipDot;
	bool	HorizontalTile;
	bool	VerticalTile;
	bool	AddSystemMenu;
	TransformAffin	TransformData;

    ShrinkedInspection(int ShadowNumber ,LayersBase *base);

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
	virtual	bool	CopyShadowAlgorithmPage	(const AlgorithmInPageRoot &ParentAPage	, AlgorithmInPageRoot *ChildPage)		override;
	virtual	bool	CopyShadowAlgorithmLayer(const AlgorithmInLayerRoot &ParentALayer, AlgorithmInLayerRoot *ChildLayer)	override;
	virtual	bool	CopyShadowAlgorithmItem	(AlgorithmParentFromItem *ParentG	, const AlgorithmItemRoot &ParentItem)		override;

	void	SetSkipDot(int skipdot);

	virtual	TransformBase	&MakeTransformFromMain(void)	override;

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
	virtual	bool	ReallocXYPixelsShadowInChild(int NewDotPerLine ,int NewMaxLines)	override;
private:
	void	CopyFilterdCopy(ImageBuffer &DstImage ,ImageBuffer &SrcImage,int Skip);
};
