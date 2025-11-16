#if	!defined(XDXFOperation_H)
#define	XDXFOperation_H

#include <stdio.h>
#include "XTypeDef.h"
#include "XDXFOperation.h"
#include "XGeneralFunc.h"
#include "XGUIPacketForDLL.h"
#include "XAllocationLibByColor.h"
#include "XDXFOperation.h"

class	CmdLoadDXF: public GUIDirectMessage
{
public:
	QString		FileName;
	QByteArray	*pData;
	int			FileNo;
	int			ActivePage;
	bool		Ret;

	CmdLoadDXF(LayersBase *base):GUIDirectMessage(base){}
	CmdLoadDXF(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdReqDXFArea: public GUIDirectMessage
{
public:
	double	MinX,MinY,MaxX,MaxY;

	CmdReqDXFArea(LayersBase *base):GUIDirectMessage(base){}
	CmdReqDXFArea(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdReqLayerColor : public GUIDirectMessage
{
public:
	int		LayerNo;
	QColor	Color;

	CmdReqLayerColor(LayersBase *base):GUIDirectMessage(base){}
	CmdReqLayerColor(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdRegulateGerberArea: public GUIDirectMessage
{
public:
	double	MinX,MinY,MaxX,MaxY;

	CmdRegulateGerberArea(LayersBase *base):GUIDirectMessage(base){}
	CmdRegulateGerberArea(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdClearGerber: public GUIDirectMessage
{
public:
	CmdClearGerber(LayersBase *base):GUIDirectMessage(base){}
	CmdClearGerber(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdDXFMove: public GUIDirectMessage
{
public:
	double	XDir;
	double	YDir;
	bool	PixelMode;
	bool	OnlySelected;

	CmdDXFMove(LayersBase *base):GUIDirectMessage(base)		{	OnlySelected=true;	}
	CmdDXFMove(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){	OnlySelected=true;	}
};

class	CmdDXFRotate: public GUIDirectMessage
{
public:
	double	Angle;
	double	CenterX,CenterY;
	bool	OnlySelected;

	CmdDXFRotate(LayersBase *base):GUIDirectMessage(base)			{	OnlySelected=true;	}
	CmdDXFRotate(GUICmdPacketBase *gbase):GUIDirectMessage(gbase)	{	OnlySelected=true;	}
};

class	CmdDXFRotateInCenter: public GUIDirectMessage
{
public:
	double	Angle;
	bool	OnlySelected;
	int		ActivePage;

	CmdDXFRotateInCenter(LayersBase *base):GUIDirectMessage(base)			{	OnlySelected=true;	}
	CmdDXFRotateInCenter(GUICmdPacketBase *gbase):GUIDirectMessage(gbase)	{	OnlySelected=true;	}
};

class	CmdDXFZoom: public GUIDirectMessage
{
public:
	double	XZoomDir;
	double	YZoomDir;
	double	CenterX,CenterY;
	bool	OnlySelected;

	CmdDXFZoom(LayersBase *base):GUIDirectMessage(base)		{	OnlySelected=true;	}
	CmdDXFZoom(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){	OnlySelected=true;	}
};

class	CmdDXFZoomInCenter: public GUIDirectMessage
{
public:
	double	XZoomDir;
	double	YZoomDir;
	bool	OnlySelected;
	int		ActivePage;

	CmdDXFZoomInCenter(LayersBase *base):GUIDirectMessage(base)		{	OnlySelected=true;	}
	CmdDXFZoomInCenter(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){	OnlySelected=true;	}
};

class	CmdDXFShear: public GUIDirectMessage
{
public:
	bool	XMode;
	double	Shear;
	double	CenterX,CenterY;
	bool	OnlySelected;

	CmdDXFShear(LayersBase *base):GUIDirectMessage(base)			{	OnlySelected=true;	}
	CmdDXFShear(GUICmdPacketBase *gbase):GUIDirectMessage(gbase)	{	OnlySelected=true;	}
};

class	CmdDXFMirror: public GUIDirectMessage
{
public:
	bool	XMode;
	double	CenterX,CenterY;
	bool	OnlySelected;

	CmdDXFMirror(LayersBase *base):GUIDirectMessage(base)			{	OnlySelected=true;	}
	CmdDXFMirror(GUICmdPacketBase *gbase):GUIDirectMessage(gbase)	{	OnlySelected=true;	}
};

class	CmdDXFMirrorInCenter: public GUIDirectMessage
{
public:
	bool	XMode;
	bool	OnlySelected;
	int		ActivePage;

	CmdDXFMirrorInCenter(LayersBase *base):GUIDirectMessage(base)			{	OnlySelected=true;	}
	CmdDXFMirrorInCenter(GUICmdPacketBase *gbase):GUIDirectMessage(gbase)	{	OnlySelected=true;	}
};

class	CmdDXFCenterize: public GUIDirectMessage
{
public:
	double	MovX,MovY;
	double	ZoomRate;
	double	CenterX,CenterY;
	bool	OnlySelected;

	CmdDXFCenterize(LayersBase *base):GUIDirectMessage(base)			{	OnlySelected=true;	}
	CmdDXFCenterize(GUICmdPacketBase *gbase):GUIDirectMessage(gbase)	{	OnlySelected=true;	}
};

class	CmdDXFCenterizeOnly: public GUIDirectMessage
{
public:
	double	MovX,MovY;
	double	CenterX,CenterY;
	bool	OnlySelected;

	CmdDXFCenterizeOnly(LayersBase *base):GUIDirectMessage(base)			{	OnlySelected=true;	}
	CmdDXFCenterizeOnly(GUICmdPacketBase *gbase):GUIDirectMessage(gbase)	{	OnlySelected=true;	}
};

class	CmdSetLineWidth: public GUIDirectMessage
{
public:
	double	LineWidth;

	CmdSetLineWidth(LayersBase *base):GUIDirectMessage(base){}
	CmdSetLineWidth(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdMakeAlgo: public GUIDirectMessage
{
public:
	int	LibType;
	int	LibID;

	CmdMakeAlgo(LayersBase *base):GUIDirectMessage(base){}
	CmdMakeAlgo(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdMakeAlgoFillArea: public GUIDirectMessage
{
public:
	int	LibType;
	int	LibID;

	CmdMakeAlgoFillArea(LayersBase *base):GUIDirectMessage(base){}
	CmdMakeAlgoFillArea(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdMakeAlgoByColor: public GUIDirectMessage
{
public:
	IntList	ColorCode;
	QColor	Color;
	int	LibType;
	int	LibID;

	CmdMakeAlgoByColor(LayersBase *base):GUIDirectMessage(base){}
	CmdMakeAlgoByColor(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdMatchAutomatic: public GUIDirectMessage
{
public:

	CmdMatchAutomatic(LayersBase *base):GUIDirectMessage(base){}
	CmdMatchAutomatic(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdEnfatLine: public GUIDirectMessage
{
public:
	double	EnfatLineDot;

	CmdEnfatLine(LayersBase *base):GUIDirectMessage(base){}
	CmdEnfatLine(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdSelectInColor : public GUIDirectMessage
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


	CmdSelectInColor(LayersBase *base):GUIDirectMessage(base){}
	CmdSelectInColor(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdReqAllocationLibByColor: public GUIDirectMessage
{
public:
	int								ThresholdLevelID;
	AllocationLibByColorContainer	Container;

	CmdReqAllocationLibByColor(LayersBase *base)
		:GUIDirectMessage(base),Container(DXFCommonDataID){		ThresholdLevelID=0;	}
	CmdReqAllocationLibByColor(GUICmdPacketBase *gbase)
		:GUIDirectMessage(gbase),Container(DXFCommonDataID){	ThresholdLevelID=0;}
};
class	CmdSetAllocationLibByColor: public GUIDirectMessage
{
public:
	int								ThresholdLevelID;
	AllocationLibByColorContainer	Container;

	CmdSetAllocationLibByColor(LayersBase *base)
		:GUIDirectMessage(base),Container(DXFCommonDataID){		ThresholdLevelID=0;	}
	CmdSetAllocationLibByColor(GUICmdPacketBase *gbase)
		:GUIDirectMessage(gbase),Container(DXFCommonDataID){	ThresholdLevelID=0;	}
};

//----------------------------------------------------------------------------

class	CmdSaveAllocationLibByColor: public GUIDirectMessage
{
public:
	CmdSaveAllocationLibByColor(LayersBase *base):GUIDirectMessage(base){}
	CmdSaveAllocationLibByColor(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdLoadAllocationLibByColor: public GUIDirectMessage
{
public:
	CmdLoadAllocationLibByColor(LayersBase *base):GUIDirectMessage(base){}
	CmdLoadAllocationLibByColor(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdReqColorFromDXF: public GUIDirectMessage
{
public:
	AllocationLibByColorContainer	ColorList;

	CmdReqColorFromDXF(LayersBase *base):GUIDirectMessage(base),ColorList(DXFCommonDataID){}
	CmdReqColorFromDXF(GUICmdPacketBase *gbase):GUIDirectMessage(gbase),ColorList(DXFCommonDataID){}

};

class	CmdDelMaskByCAD: public GUIDirectMessage
{
public:
	CmdDelMaskByCAD(LayersBase *base):GUIDirectMessage(base){}
	CmdDelMaskByCAD(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdMakeDXFPaint : public GUIDirectMessage
{
public:
	int	LocalX, LocalY;
	int	FileNo;

	CmdMakeDXFPaint(LayersBase *base):GUIDirectMessage(base){}
	CmdMakeDXFPaint(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdSelectFileNo: public GUIDirectMessage
{
public:
	int	FileNo;

	CmdSelectFileNo(LayersBase *base):GUIDirectMessage(base){}
	CmdSelectFileNo(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdMakeEffectiveMask: public GUIDirectMessage
{
public:
	int		ShrinkDot;
	CmdMakeEffectiveMask(LayersBase *base):GUIDirectMessage(base){}
	CmdMakeEffectiveMask(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdSendEffectiveMask: public GUIDirectMessage
{
public:
	CmdSendEffectiveMask(LayersBase *base):GUIDirectMessage(base){}
	CmdSendEffectiveMask(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdSetDXFWithSelfTransform : public GUIDirectMessage
{
public:
	QByteArray	DXFData;
	bool		Result;

	CmdSetDXFWithSelfTransform(LayersBase *base):GUIDirectMessage(base){}
	CmdSetDXFWithSelfTransform(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdReqDXFTransformInfo : public GUIDirectMessage
{
public:
	QByteArray	TransformData;

	CmdReqDXFTransformInfo(LayersBase *base):GUIDirectMessage(base){}
	CmdReqDXFTransformInfo(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdSetDXFTransformInfo : public GUIDirectMessage
{
public:
	QByteArray	TransformData;

	CmdSetDXFTransformInfo(LayersBase *base):GUIDirectMessage(base){}
	CmdSetDXFTransformInfo(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

#endif