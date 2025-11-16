#pragma once

#include "XTypeDef.h"
#include "NList.h"
#include "NListComp.h"
#include "XFlexArea.h"
#include "XVector.h"
#include <QByteArray>

class   AlgorithmBase;
class   AlgorithmParentFromItem;
class   ShadowTree;
class	TransformBase;

class	GeneralPipeInfo
{
public:
	enum{
		 _GI_Nothing							=-1
		,_GI_ReqFormat							=0
		,_GI_ReqFormatBmpMap					=1
		,_GI_ReqFormatArea						=2
		,_GI_ReqFormatOutlineVector				=3
		,_GI_ReqFormatSkeltonVector				=4
		,_GI_AckBmpMap							=1001
		,_GI_AckArea							=1002
		,_GI_AckOutlineVector					=1003
		,_GI_AckSkeltonVector					=1004
		,_GI_InitialBmpMap						=10000
		,_GI_SendBmpMap							=10001
		,_GI_SendArea							=10002
		,_GI_SendOutlineVector					=10003
		,_GI_SendSkentonVector					=10004
		,_GI_ReqToMoveByAlignment				=20000
		,_GI_CopyMoveByAlignmentFromOutside		=20001
		,_GI_ReqItemsToMoveByAlignmentOutside	=20002
	}Cmd;

	BYTE		**BmpMap;
	BYTE		**DriftMap;
	BYTE		**OmitMap;
	int			XByte;
	int			YLen;
	FlexArea	Area;
	VectorLineBase		*Vector;
	int			LibID;
	int			DestinationPage;
	QByteArray	Something;
	OriginType	OperationOrigin;
	AlgorithmBase	*Origin;

	explicit	GeneralPipeInfo(AlgorithmBase *OriginBase);
	virtual	~GeneralPipeInfo(void);

	virtual	bool	RequireAlignmentPosition(double X ,double Y ,double &AckX ,double &AckY){	return false;	}
};

enum EmitPipeDirection
{
	 _Pipe_AllAlgorithm		=0x01
	,_Pipe_SameAlgorithm	=0x02
	,_Pipe_AllShadowTree	=0x04
};


class PipeClass
{
	AlgorithmParentFromItem	*Own;
public:
	explicit	PipeClass(AlgorithmParentFromItem *own):Own(own){}
	virtual	~PipeClass(){}

	virtual	bool	PipeGeneration(GeneralPipeInfo &Info){	return false;	}

	virtual	bool	EmitPipeCreateArea	(EmitPipeDirection EDir ,FlexArea &Area, const QByteArray &Something=QByteArray());
	virtual	bool	EmitPipeMoveItem	(EmitPipeDirection EDir ,int dx ,int dy, const QByteArray &Something=QByteArray());
	virtual	bool	EmitPipeRemoveItem	(EmitPipeDirection EDir ,const QByteArray &Something=QByteArray());
	virtual	bool	EmitPipeSelectItem	(EmitPipeDirection EDir ,int px ,int py, const QByteArray &Something=QByteArray());
	virtual	bool	EmitPipeSelectItemByLibrary	(EmitPipeDirection EDir ,int LibType, int LibID ,const QByteArray &Something=QByteArray());
	virtual	bool	EmitPipeSelectItemByArea	(EmitPipeDirection EDir ,FlexArea &Area ,const QByteArray &Something=QByteArray());
	virtual	bool	EmitPipeRotateItems			(EmitPipeDirection EDir ,double Radian ,const QByteArray &Something=QByteArray());
	virtual	bool	EmitPipeMirrorItem			(EmitPipeDirection EDir ,bool XMirror ,bool YMirror ,const QByteArray &Something=QByteArray());
	virtual	bool	EmitPipeCopyImage			(EmitPipeDirection EDir ,int Source ,int Destination ,const QByteArray &Something=QByteArray());
};

class PipeAlgorithmBase
{
public:
	PipeAlgorithmBase(){}
	virtual	~PipeAlgorithmBase(){}

	virtual	bool	PipeOutAutoGenerationForLearning(QIODevice *f ,int LocalPage ,int localX1, int localY1, int localX2 ,int localY2)	{	return true;	}
	virtual	bool	PipeInAutoGenerationForLearning (QIODevice *f ,int LocalPage ,int localX1, int localY1, int localX2 ,int localY2)	{	return true;	}

};

class PipeShadowTree
{
	TransformBase	*TransformData;
protected:
	ShadowTree	*Own;
public:
	explicit	PipeShadowTree(ShadowTree *own);
	virtual	~PipeShadowTree();

	virtual	TransformBase	&MakeTransformFromMain(void);
	PipeShadowTree	&operator=(const PipeShadowTree &src);
};
