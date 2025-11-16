#include <QIODevice>
#include <QMouseEvent>
#include <QColor>
#include "XTypeDef.h"
#include "NList.h"
#include "NListComp.h"
#include "XFlexArea.h"
#include "XParamGlobal.h"
#include "XDataInLayer.h"
#include "XVector.h"
#include "XParamBase.h"
#include "XServiceForLayers.h"
#include "XHistgramByParam.h"
#include "XAlgorithmCommon.h"
#include "XDataAlgorithmPipe.h"
#include "XDataAlgorithm.h"
#include "XTransform.h"

bool	PipeClass::EmitPipeCreateArea	(EmitPipeDirection EDir ,FlexArea &Area, const QByteArray &Something)
{
	return true;
}
bool	PipeClass::EmitPipeMoveItem	(EmitPipeDirection EDir ,int dx ,int dy, const QByteArray &Something)
{
	return true;
}
bool	PipeClass::EmitPipeRemoveItem	(EmitPipeDirection EDir ,const QByteArray &Something)
{
	return true;
}
bool	PipeClass::EmitPipeSelectItem	(EmitPipeDirection EDir ,int px ,int py, const QByteArray &Something)
{
	return true;
}
bool	PipeClass::EmitPipeSelectItemByLibrary(EmitPipeDirection EDir ,int LibType, int LibID ,const QByteArray &Something)
{
	return true;
}
bool	PipeClass::EmitPipeSelectItemByArea	(EmitPipeDirection EDir ,FlexArea &Area ,const QByteArray &Something)
{
	return true;
}
bool	PipeClass::EmitPipeRotateItems		(EmitPipeDirection EDir ,double Radian ,const QByteArray &Something)
{
	return true;
}
bool	PipeClass::EmitPipeMirrorItem			(EmitPipeDirection EDir ,bool XMirror ,bool YMirror ,const QByteArray &Something)
{
	return true;
}
bool	PipeClass::EmitPipeCopyImage			(EmitPipeDirection EDir ,int Source ,int Destination ,const QByteArray &Something)
{
	return true;
}


//=============================================================
PipeShadowTree::PipeShadowTree(ShadowTree *own)
	:Own(own)
{
	TransformData=new TransformAffin;
}
PipeShadowTree::~PipeShadowTree()
{
	delete	TransformData;
	TransformData=NULL;
}
TransformBase	&PipeShadowTree::MakeTransformFromMain(void)
{
	return *TransformData;
}

PipeShadowTree	&PipeShadowTree::operator=(const PipeShadowTree &src)
{
	if(this!=&src){
		*TransformData=*src.TransformData;
	}
	return *this;
}

