#ifndef HOOKLEARNINGREGISTOKNG_H
#define HOOKLEARNINGREGISTOKNG_H

#include "hooklearningregistokng_global.h"
#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XDisplayImageHook.h"
#include "XDisplayImage.h"
#include "NListComp.h"
#include "XHookRegistCommon.h"

class	HookLearningRegistOkNg: public GUIFormBase,public FunctionServerClass
{
	DisplayImage		*TargetPanel;

	int	GlobalX1,GlobalY1;
	int	GlobalX2,GlobalY2;
	int	MaxGlobalX1,MaxGlobalY1;
	int	MinGlobalX2,MinGlobalY2;
	int	PointX,PointY;

	int	GlobalX1BeforeMove,GlobalY1BeforeMove;
	int	GlobalX2BeforeMove,GlobalY2BeforeMove;

public:
	enum	CurrentState
	{
		_None
		,_WaitingOnFrame
		,PickingLeft
		,PickingTop
		,PickingRight
		,PickingBottom
		,PickingLeftTop
		,PickingRightTop
		,PickingLeftBottom
		,PickingRightBottom
	}CurrentState;

	QString	HookTargetInst;
	int		DefaultAreaSizeX;
	int		DefaultAreaSizeY;
	QColor	FrameColor;
	int		ControlPointSize;
	int32	LibType;
	int32	LibID;

	HookLearningRegistOkNg(LayersBase *Base ,QWidget *parent = 0);
	~HookLearningRegistOkNg();

	virtual void	ReadyParam(void)	override;
    void	MouseLClick		(int GlobalPosX,int GlobalPosY);
	void	MouseRClick		(int GlobalPosX,int GlobalPosY);
	void	MouseLDblClick	(int GlobalPosX,int GlobalPosY);
	void	MouseMove		(int GlobalPosX,int GlobalPosY);

	void	Draw(QPainter &pnt	,double ZoomRate,int movx ,int movy);
private:

};


//==================================================================================

class	GUICmdReqPointItemSize : public GUICmdPacketBase
{
public:
	int	GlobalX,GlobalY;
	IntList	LibType;

	GUICmdReqPointItemSize(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckPointItemSize : public GUICmdPacketBase
{
public:
	int	X1,Y1;
	int	X2,Y2;
	int	LibID;

	GUICmdAckPointItemSize(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};


//==================================================================================

class	GUICmdReqLibIDListWithResult : public GUICmdPacketBase
{
public:
	int	LocalX1,LocalY1;
	int	LocalX2,LocalY2;

	GUICmdReqLibIDListWithResult(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckLibIDListWithResult : public GUICmdPacketBase
{
public:
	LibIDListWithResultContainer	Container;

	GUICmdAckLibIDListWithResult(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};



#endif // HOOKLEARNINGREGISTOKNG_H
