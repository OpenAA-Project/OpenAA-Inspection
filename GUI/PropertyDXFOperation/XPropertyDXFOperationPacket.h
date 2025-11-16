#if	!defined(XPropertyDXFOperationPacket_h)
#define	XPropertyDXFOperationPacket_h

#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XDXFOperation.h"
#include "XFlexAreaImageBuffer.h"
#include "NListComp.h"
#include "XBoolList.h"
#include "XDisplayImage.h"
#include "XDXFOperationPacket.h"


class	GUICmdLoadDXF : public GUICmdPacketBase
{
public:
	QString		FileName;
	QByteArray	Data;
	int32		FileNo;

	GUICmdLoadDXF(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//==============================================================

class	GUICmdMove : public GUICmdPacketBase
{
public:
	double	XDir;
	double	YDir;
	bool	PixelMode;
	bool	OnlySelected;

	GUICmdMove(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdRotate : public GUICmdPacketBase
{
public:
	double	Angle;
	double	CenterX,CenterY;
	bool	OnlySelected;

	GUICmdRotate(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdZoom : public GUICmdPacketBase
{
public:
	double	XZoomDir;
	double	YZoomDir;
	double	CenterX,CenterY;
	bool	OnlySelected;

	GUICmdZoom(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdShear : public GUICmdPacketBase
{
public:
	bool	XMode;
	double	Shear;
	double	CenterX,CenterY;
	bool	OnlySelected;

	GUICmdShear(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdMirror : public GUICmdPacketBase
{
public:
	bool	XMode;
	double	CenterX,CenterY;
	bool	OnlySelected;

	GUICmdMirror(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdCenterize: public GUICmdPacketBase
{
public:
	double	MovX,MovY;
	double	CenterX,CenterY;
	double	ZoomRate;
	bool	OnlySelected;

	GUICmdCenterize(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdCenterizeOnly: public GUICmdPacketBase
{
public:
	double	MovX,MovY;
	double	CenterX,CenterY;
	bool	OnlySelected;

	GUICmdCenterizeOnly(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

//==============================================================
class	GUICmdReqDXFArea : public GUICmdPacketBase
{
public:

	GUICmdReqDXFArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckDXFArea : public GUICmdPacketBase
{
public:
	double	MinX,MinY,MaxX,MaxY;

	GUICmdAckDXFArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

//==============================================================
class	GUICmdReqDXFLayerInfo : public GUICmdPacketBase
{
public:

	GUICmdReqDXFLayerInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckDXFLayerInfo : public GUICmdPacketBase
{
public:
	DXFLayerContainer	DXFLayerList;

	GUICmdAckDXFLayerInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};
//==============================================================
class	GUICmdSetLineWidth : public GUICmdPacketBase
{
public:
	double	LineWidth;

	GUICmdSetLineWidth(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//==============================================================

class	CmdDXFGetDrawAttr : public GUIDirectMessage
{
public:
	IntListFast		ShownDXFLayerID;
	bool			ShowFilledArea;
	IntList			ListFileNo;

	CmdDXFGetDrawAttr(LayersBase *base):GUIDirectMessage(base){}
	CmdDXFGetDrawAttr(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

//==============================================================

class	GUICmdDXFDrawMode : public GUICmdPacketBase
{
public:
	bool	MoveMode;
	bool	RotateMode;
	bool	SlopeXMode;
	bool	SlopeYMode;
	bool	ExtendMode;
	DisplayImage::__DrawingMode	Mode;
	int		LastPosX,LastPosY;
	int		MoveStartPosX,MoveStartPosY;
	int		RotateCenterXOnData	,RotateCenterYOnData;
	int		RotateFirstX		,RotateFirstY;
	double	RotateAngle;
	int		ExtendCenterXOnData	,ExtendCenterYOnData;
	int		ExtendFirstX		,ExtendFirstY;
	int		SlopeXCenterXOnData	,SlopeXCenterYOnData;
	int		SlopeXFirstX		,SlopeXFirstY;
	double	SlopeXAngle;
	int		SlopeYCenterXOnData	,SlopeYCenterYOnData;
	int		SlopeYFirstX		,SlopeYFirstY;
	double	SlopeYAngle;

	GUICmdDXFDrawMode(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	CmdDXFChangeOperationModePacket : public GUIDirectMessage
{
public:
	DXFOperationMode	Mode;
	CmdDXFChangeOperationModePacket(LayersBase *base):GUIDirectMessage(base){}
	CmdDXFChangeOperationModePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdDXFGetOperationModePacket : public GUIDirectMessage
{
public:
	DXFOperationMode	Mode;

	CmdDXFGetOperationModePacket(LayersBase *base):GUIDirectMessage(base){}
	CmdDXFGetOperationModePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};


class	GUICmdMakeAlgo: public GUICmdPacketBase
{
public:
	int	LibType;
	int	LibID;

	GUICmdMakeAlgo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdMakeAlgoFillArea: public GUICmdPacketBase
{
public:
	int	LibType;
	int	LibID;

	GUICmdMakeAlgoFillArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
class	GUICmdMakeAlgoByColor: public GUICmdPacketBase
{
public:
	IntList	ColorCode;
	QColor	Color;
	int	LibType;
	int	LibID;

	GUICmdMakeAlgoByColor(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


class	GUICmdMatchAutomatic: public GUICmdPacketBase
{
public:

	GUICmdMatchAutomatic(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSelectInColor : public GUICmdPacketBase
{
public:
	int32	PickupRL;
	int32	PickupRH;
	int32	PickupGL;
	int32	PickupGH;
	int32	PickupBL;
	int32	PickupBH;
	int32	AreaX1;
	int32	AreaY1;
	int32	AreaX2;
	int32	AreaY2;

	GUICmdSelectInColor(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	

};

//==============================================================

class	GUICmdReqColorFromDXF: public GUICmdPacketBase
{
public:

	GUICmdReqColorFromDXF(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckColorFromDXF: public GUICmdPacketBase
{
public:
	AllocationLibByColorContainer	ColorList;

	GUICmdAckColorFromDXF(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}	
};

class	CmdReqDXFColor : public GUIDirectMessage
{
public:
	ColorCodeListContainer	ColorList;

	CmdReqDXFColor(LayersBase *base):GUIDirectMessage(base){}
	CmdReqDXFColor(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};


//==============================================================

class	GUICmdDelMaskByCAD: public GUICmdPacketBase
{
public:

	GUICmdDelMaskByCAD(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
//==============================================================
class	CmdExecuteInitialMask : public GUIDirectMessage
{
public:
	CmdExecuteInitialMask(LayersBase *base):GUIDirectMessage(base){}
	CmdExecuteInitialMask(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	GUICmdExecuteInitialMask: public GUICmdPacketBase
{
public:

	GUICmdExecuteInitialMask(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
//==============================================================

class	CmdDXFPaint : public GUIDirectMessage
{
public:
	int	GlobalX, GlobalY;

	CmdDXFPaint(LayersBase *base):GUIDirectMessage(base){}
	CmdDXFPaint(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	GUICmdDXFDraw: public GUICmdPacketBase
{
public:
	int	LocalX, LocalY;
	int	FileNo;

	GUICmdDXFDraw(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//==============================================================

class	GUICmdSelectFileNo : public GUICmdPacketBase
{
public:
	int32	FileNo;

	GUICmdSelectFileNo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	

};

//========================================================================================================

class	GUICmdReqAllocationLibByColor: public GUICmdPacketBase
{
public:
	int		LevelID;
	GUICmdReqAllocationLibByColor(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int cmd ,QString &EmitterRoot,QString &EmitterName);	

private:

};

class	GUICmdAckAllocationLibByColor: public GUICmdPacketBase
{
public:
	AllocationLibByColorContainer	AllocationLibByColorContainerInst;

	GUICmdAckAllocationLibByColor(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int cmd ,QString &EmitterRoot,QString &EmitterName){}	

private:

};

class	GUICmdSetAllocationLibByColor: public GUICmdPacketBase
{
public:
	int		LevelID;
	AllocationLibByColorContainer	AllocationLibByColorContainerInst;

	GUICmdSetAllocationLibByColor(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int cmd ,QString &EmitterRoot,QString &EmitterName);

private:

};

//========================================================================================================

class	GUICmdMakeEffectiveMask: public GUICmdPacketBase
{
public:
	int		ShrinkDot;
	GUICmdMakeEffectiveMask(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendEffectiveMask: public GUICmdPacketBase
{
public:

	GUICmdSendEffectiveMask(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int cmd ,QString &EmitterRoot,QString &EmitterName);	
};
//==============================================================

class	GUICmdSetDXFWithSelfTransform: public GUICmdPacketBase
{
public:
	QByteArray	DXFData;

	GUICmdSetDXFWithSelfTransform(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//==============================================================
class	GUICmdReqDXFTransformInfo: public GUICmdPacketBase
{
public:
	GUICmdReqDXFTransformInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdAckDXFTransformInfo: public GUICmdPacketBase
{
public:
	QByteArray	TransformData;

	GUICmdAckDXFTransformInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

class	GUICmdSetDXFTransformInfo: public GUICmdPacketBase
{
public:
	QByteArray	TransformData;

	GUICmdSetDXFTransformInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};


#endif