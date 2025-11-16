#pragma once

#include <stdio.h>
#include "XTypeDef.h"
#include "XRaster.h"
#include "XGeneralFunc.h"

class	RasterLibrary;

class	CmdRasterDrawAttr: public GUIDirectMessage
{
public:
	bool	DrawPickUpArea;
	int		CurrentElementID;

	CmdRasterDrawAttr(LayersBase *base):GUIDirectMessage(base){}
	CmdRasterDrawAttr(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};


class	CmdLoadRaster: public GUIDirectMessage
{
public:
	int			FileLayerID;
	QString		FileName;
	QByteArray	*pData;
	bool		Ret;

	CmdLoadRaster(LayersBase *base):GUIDirectMessage(base){}
	CmdLoadRaster(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdReqRasterArea: public GUIDirectMessage
{
public:
	double	MinX,MinY,MaxX,MaxY;

	CmdReqRasterArea(LayersBase *base):GUIDirectMessage(base){}
	CmdReqRasterArea(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdClearRaster: public GUIDirectMessage
{
public:
	CmdClearRaster(LayersBase *base):GUIDirectMessage(base){}
	CmdClearRaster(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdRasterMove: public GUIDirectMessage
{
public:
	double	XDir;
	double	YDir;
	bool	PixelMode;

	CmdRasterMove(LayersBase *base):GUIDirectMessage(base){}
	CmdRasterMove(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdRasterRotate: public GUIDirectMessage
{
public:
	double	Angle;
	double	CenterX,CenterY;

	CmdRasterRotate(LayersBase *base):GUIDirectMessage(base){}
	CmdRasterRotate(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdRasterZoom: public GUIDirectMessage
{
public:
	double	XZoomDir;
	double	YZoomDir;
	double	CenterX,CenterY;

	CmdRasterZoom(LayersBase *base):GUIDirectMessage(base){}
	CmdRasterZoom(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdRasterShear: public GUIDirectMessage
{
public:
	bool	XMode;
	double	Shear;
	double	CenterX,CenterY;

	CmdRasterShear(LayersBase *base):GUIDirectMessage(base){}
	CmdRasterShear(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdRasterMirror: public GUIDirectMessage
{
public:
	bool	XMode;
	double	CenterX,CenterY;

	CmdRasterMirror(LayersBase *base):GUIDirectMessage(base){}
	CmdRasterMirror(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdRasterCenterize: public GUIDirectMessage
{
public:
	double	MovX,MovY;
	double	ZoomRate;
	double	CenterX,CenterY;

	CmdRasterCenterize(LayersBase *base):GUIDirectMessage(base){}
	CmdRasterCenterize(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdRasterCenterizeOnly: public GUIDirectMessage
{
public:
	double	MovX,MovY;
	double	CenterX,CenterY;

	CmdRasterCenterizeOnly(LayersBase *base):GUIDirectMessage(base){}
	CmdRasterCenterizeOnly(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

//----------------------------------------------------------------------------

class	MsgGetRasterArea: public GUIDirectMessage
{
public:
	double pminx, pminy, pmaxx, pmaxy;
	MsgGetRasterArea(LayersBase *base):GUIDirectMessage(base){}
	MsgGetRasterArea(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};


class	MsgSaveRasterLayerList : public GUIDirectMessage
{
public:
	QString	FileName;
	MsgSaveRasterLayerList(LayersBase *base):GUIDirectMessage(base){}
	MsgSaveRasterLayerList(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	MsgLoadRasterLayerList : public GUIDirectMessage
{
public:
	QString	FileName;
	MsgLoadRasterLayerList(LayersBase *base):GUIDirectMessage(base){}
	MsgLoadRasterLayerList(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	MsgSaveConstruct : public GUIDirectMessage
{
public:
	QByteArray	Data;
	MsgSaveConstruct(LayersBase *base):GUIDirectMessage(base){}
	MsgSaveConstruct(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	MsgLoadConstruct : public GUIDirectMessage
{
public:
	QByteArray	Data;
	MsgLoadConstruct(LayersBase *base):GUIDirectMessage(base){}
	MsgLoadConstruct(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	MsgRasterDrawWithHBitmap : public GUIDirectMessage
{
public:
	QImage	*pBmp;
	QImage	*pSelectedBmp;
	double	ZoomRate;
	MsgRasterDrawWithHBitmap(LayersBase *base):GUIDirectMessage(base){}
	MsgRasterDrawWithHBitmap(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	MsgRasterDrawSelected : public GUIDirectMessage
{
public:
	QImage	SelectedImage;
	double	ZoomRate;
	MsgRasterDrawSelected(LayersBase *base):GUIDirectMessage(base){}
	MsgRasterDrawSelected(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	MsgRasterMoveTo : public GUIDirectMessage
{
public:
	int Dx,Dy;
	MsgRasterMoveTo(LayersBase *base):GUIDirectMessage(base){}
	MsgRasterMoveTo(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	MsgRasterRotate : public GUIDirectMessage
{
public:
	int Cx,Cy;
	double	Radian;
	MsgRasterRotate(LayersBase *base):GUIDirectMessage(base){}
	MsgRasterRotate(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	MsgRasterSlopeX : public GUIDirectMessage
{
public:
	int Cx,Cy;
	double	Radian;
	MsgRasterSlopeX(LayersBase *base):GUIDirectMessage(base){}
	MsgRasterSlopeX(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	MsgRasterSlopeY : public GUIDirectMessage
{
public:
	int Cx,Cy;
	double	Radian;
	MsgRasterSlopeY(LayersBase *base):GUIDirectMessage(base){}
	MsgRasterSlopeY(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	MsgRasterExtend : public GUIDirectMessage
{
public:
	int Cx,Cy;
	double	RateX,RateY;
	MsgRasterExtend(LayersBase *base):GUIDirectMessage(base){}
	MsgRasterExtend(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	MsgRasterXMirror : public GUIDirectMessage
{
public:
	MsgRasterXMirror(LayersBase *base):GUIDirectMessage(base){}
	MsgRasterXMirror(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	MsgRasterYMirror : public GUIDirectMessage
{
public:
	MsgRasterYMirror(LayersBase *base):GUIDirectMessage(base){}
	MsgRasterYMirror(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdRasterExec3PointAlignment : public GUIDirectMessage
{
public:
	int			FileLayerID;
	DoublePoint	ImagePoint[MaxRasterPointNumb];
	DoublePoint	CadPoint[MaxRasterPointNumb];	

	CmdRasterExec3PointAlignment(LayersBase *base):GUIDirectMessage(base){}
	CmdRasterExec3PointAlignment(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdRasterExecAddAlignmentPoint : public GUIDirectMessage
{
public:
	DoublePoint	ImagePoint[MaxRasterPointNumb];
	DoublePoint	CadPoint[MaxRasterPointNumb];	

	CmdRasterExecAddAlignmentPoint(LayersBase *base):GUIDirectMessage(base){}
	CmdRasterExecAddAlignmentPoint(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	MsgRasterUndo : public GUIDirectMessage
{
public:
	MsgRasterUndo(LayersBase *base):GUIDirectMessage(base){}
	MsgRasterUndo(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	MsgRasterRedo : public GUIDirectMessage
{
public:
	MsgRasterRedo(LayersBase *base):GUIDirectMessage(base){}
	MsgRasterRedo(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	MsgClearDrawModeInForm : public GUIDirectMessage
{
public:
	MsgClearDrawModeInForm(LayersBase *base):GUIDirectMessage(base){}
	MsgClearDrawModeInForm(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	MsgRasterClearItems : public GUIDirectMessage
{
public:
	MsgRasterClearItems(LayersBase *base):GUIDirectMessage(base){}
	MsgRasterClearItems(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	MsgRasterClearAll : public GUIDirectMessage
{
public:
	MsgRasterClearAll(LayersBase *base):GUIDirectMessage(base){}
	MsgRasterClearAll(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	MsgRasterSelectAll : public GUIDirectMessage
{
public:
	MsgRasterSelectAll(LayersBase *base):GUIDirectMessage(base){}
	MsgRasterSelectAll(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdRasterDraw: public GUIDirectMessage
{
public:
	int			GlobalX;
	int			GlobalY;
	BoolList	ButtonsToShowLayer;
	BoolList	ButtonsToOperateLayer;

	CmdRasterDraw(LayersBase *base):GUIDirectMessage(base){}
	CmdRasterDraw(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	GetCenterPacket : public GUIDirectMessage
{
public:
	FlexArea	Area;
	int			Layer;
	int			Page;
	double		LocalX,LocalY;
	double		DifBrightness;
	GetCenterPacket(LayersBase *base):GUIDirectMessage(base){	DifBrightness=0;	}
	GetCenterPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){	DifBrightness=0;	}
};

class	MsgRasterCenterize: public GUIDirectMessage
{
public:
	FlexArea	Area;
	XYClassCluster XYArea;
	double		x;
	double		y;
	int			GlobalPage;
	bool		Ret;

	MsgRasterCenterize(LayersBase *base):GUIDirectMessage(base){}
	MsgRasterCenterize(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	MsgDeleteRasterPacket : public GUIDirectMessage
{
public:
	MsgDeleteRasterPacket(LayersBase *base):GUIDirectMessage(base){}
	MsgDeleteRasterPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdRasterGetFileList : public GUIDirectMessage
{
public:
	QString		PathName;
	QStringList	FileNames;

	CmdRasterGetFileList(LayersBase *base):GUIDirectMessage(base){}
	CmdRasterGetFileList(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class MsgRasterCut : public GUIDirectMessage
{
public:
	MsgRasterCut(LayersBase *base):GUIDirectMessage(base){}
	MsgRasterCut(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	MsgRasterCopy : public GUIDirectMessage
{
public:
	MsgRasterCopy(LayersBase *base):GUIDirectMessage(base){}
	MsgRasterCopy(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	MsgRasterClearClipboard : public GUIDirectMessage
{
public:
	MsgRasterClearClipboard(LayersBase *base):GUIDirectMessage(base){}
	MsgRasterClearClipboard(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	MsgRasterPaste : public GUIDirectMessage
{
public:
	int index;	//íçà” PasteRasterFormÇ≈ÇÃcurrentRow();
	int	x,y;
	MsgRasterPaste(LayersBase *base):GUIDirectMessage(base){}
	MsgRasterPaste(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

struct RasterCopyInfo
{
	XDateTime DateTime;
	int64 ItemCount;
};

class CmdGetRasterCopyInfoList : public GUIDirectMessage
{
public:
	QList<RasterCopyInfo> List;
	CmdGetRasterCopyInfoList(LayersBase *base):GUIDirectMessage(base){}
	CmdGetRasterCopyInfoList(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class CmdSaveLayerTypeDef : public GUIDirectMessage
{
public:
	CmdSaveLayerTypeDef(LayersBase *base):GUIDirectMessage(base){}
	CmdSaveLayerTypeDef(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class CmdAutoPoints : public GUIDirectMessage
{
public:
	CmdAutoPoints(LayersBase *base):GUIDirectMessage(base){}
	CmdAutoPoints(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdRasterReflectLayerType: public GUIDirectMessage
{
public:
	CmdRasterReflectLayerType(LayersBase *base):GUIDirectMessage(base){}
	CmdRasterReflectLayerType(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdAutoMatch: public GUIDirectMessage
{
public:
	CmdAutoMatch(LayersBase *base):GUIDirectMessage(base){}
	CmdAutoMatch(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetRasterLibraryListPacket: public GUIDirectMessage
{
public:
	int			LibFolderID;
	AlgorithmLibraryListContainer	AList;
	CmdGetRasterLibraryListPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetRasterLibraryListPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};	

class	CmdGetRasterTemporaryLibraryPacket: public GUIDirectMessage
{
public:
	RasterLibrary	*TempLib;
	CmdGetRasterTemporaryLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetRasterTemporaryLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};	

class	CmdGetRasterLibraryNamesPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryListContainer	AList;
	CmdGetRasterLibraryNamesPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetRasterLibraryNamesPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetRasterLibraryNamePacket : public GUIDirectMessage
{
public:
	int		LibID;
	QString	LibName;
	CmdGetRasterLibraryNamePacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetRasterLibraryNamePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateTempRasterLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdCreateTempRasterLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateTempRasterLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdClearRasterLibraryPacket: public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdClearRasterLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdClearRasterLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdInsertRasterLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdInsertRasterLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdInsertRasterLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdUpdateRasterLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdUpdateRasterLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdUpdateRasterLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdLoadRasterLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	bool				Success;
	CmdLoadRasterLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdLoadRasterLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdDeleteRasterLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdDeleteRasterLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdDeleteRasterLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	RasterInfo : public NPListSaveLoad<RasterInfo>
{
public:
	QString	TypeStr;
	QString	Message;
	int32	FileLayerID;
	int		ItemID;

	RasterInfo(void):FileLayerID(-1){}
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

class	RasterInfoContainer : public NPListPackSaveLoad<RasterInfo>
{
public:
	RasterInfoContainer(void){}

	virtual	RasterInfo	*Create(void)	{	return new RasterInfo();	}
	RasterInfoContainer	&operator=(const RasterInfoContainer &src);
};

inline	bool	RasterInfo::Save(QIODevice *f)
{
	if(::Save(f,Message)==false)
		return false;
	if(::Save(f,FileLayerID)==false)
		return false;
	if(::Save(f,TypeStr)==false)
		return false;
	if(::Save(f,ItemID)==false)
		return false;
	return true;
}
inline	bool	RasterInfo::Load(QIODevice *f)
{
	if(::Load(f,Message)==false)
		return false;
	if(::Load(f,FileLayerID)==false)
		return false;
	if(::Load(f,TypeStr)==false)
		return false;
	if(::Load(f,ItemID)==false)
		return false;
	return true;
}

inline	RasterInfoContainer	&RasterInfoContainer::operator=(const RasterInfoContainer &src)
{
	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	((RasterInfoContainer *)&src)->Save(&Buff);
	Buff.seek(0);
	Load(&Buff);
	return *this;
}

class	CmdReqRasterInfo: public GUIDirectMessage
{
public:
	int						GlobalX ,GlobalY;
	BoolList				DrawingLayers;

	RasterInfoContainer		Answer;

	CmdReqRasterInfo(LayersBase *base):GUIDirectMessage(base){}
	CmdReqRasterInfo(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

//-------------------------------------------------------------------------------------

class	CmdDrawAllSelected: public GUIDirectMessage
{
public:
	BoolList	ButtonsToOperateLayer;	

	CmdDrawAllSelected(LayersBase *base):GUIDirectMessage(base){}
	CmdDrawAllSelected(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdSelectLine: public GUIDirectMessage
{
public:
	int		FileLayerID;

	CmdSelectLine(LayersBase *base):GUIDirectMessage(base){}
	CmdSelectLine(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdRemoveLine: public GUIDirectMessage
{
public:
	int		LineNo;

	CmdRemoveLine(LayersBase *base):GUIDirectMessage(base){}
	CmdRemoveLine(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdSwapNext: public GUIDirectMessage
{
public:
	int		LineNo;	

	CmdSwapNext(LayersBase *base):GUIDirectMessage(base){}
	CmdSwapNext(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdDuplicateLine: public GUIDirectMessage
{
public:
	int		LineNo;
	int		FileLayerID;

	CmdDuplicateLine(LayersBase *base):GUIDirectMessage(base){}
	CmdDuplicateLine(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdAddEmptyLayer: public GUIDirectMessage
{
public:
	int		LineNo;
	int		FileLayerID;

	CmdAddEmptyLayer(LayersBase *base):GUIDirectMessage(base){}
	CmdAddEmptyLayer(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdSetDrawAttr: public GUIDirectMessage
{
public:
	IntListFast		ShownFileID;
	int				FileLayerIDTable[MaxRasterLayer];
	CmdSetDrawAttr(LayersBase *base):GUIDirectMessage(base){}
	CmdSetDrawAttr(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCopyPageAllFrom: public GUIDirectMessage
{
public:
	RasterInPage	*SourcePage;

	CmdCopyPageAllFrom(LayersBase *base):GUIDirectMessage(base){}
	CmdCopyPageAllFrom(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdSelectItemsRaster : public GUIDirectMessage
{
public:
	FlexArea	Area;
	BoolList	ButtonsToOperateLayer;

	CmdSelectItemsRaster(LayersBase *base):GUIDirectMessage(base)		{}
	CmdSelectItemsRaster(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

//-------------------------------------------------------------------------------------
class	CmdRasterPickupByColor: public GUIDirectMessage
{
public:
	int			FileLayerID;
	int			LocalX,LocalY;
	int			ShrinkDot;
	int			InsideEdgeWidth;
	int			OutsideEdgeWidth;
	AlgorithmLibraryListContainer	AllocatedStaticLib;
	AlgorithmLibraryListContainer	AllocatedInsideEdgeLib;
	AlgorithmLibraryListContainer	AllocatedOutsideEdgeLib;

	CmdRasterPickupByColor(LayersBase *base):GUIDirectMessage(base)		{}
	CmdRasterPickupByColor(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdRasterPickupByColorArea: public GUIDirectMessage
{
public:
	int			FileLayerID;
	FlexArea	LocalColorArea;
	int			ShrinkDot;
	int			InsideEdgeWidth;
	int			OutsideEdgeWidth;
	AlgorithmLibraryListContainer	AllocatedStaticLib;
	AlgorithmLibraryListContainer	AllocatedInsideEdgeLib;
	AlgorithmLibraryListContainer	AllocatedOutsideEdgeLib;

	CmdRasterPickupByColorArea(LayersBase *base):GUIDirectMessage(base)		{}
	CmdRasterPickupByColorArea(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

//-------------------------------------------------------------------------------------
class RasterElementList : public NPListSaveLoad<RasterElementList>
{
public:
	int		Page;
	int		ItemID;
	int		ElementID;
	QColor	ReferenceColor;
	int		ShrinkDot;
	int		LibCount;

	RasterElementList(void);

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
};
class RasterElementListContainer : public NPListPackSaveLoad<RasterElementList>
{
public:
	RasterElementListContainer(void){}

	virtual	RasterElementList	*Create(void)	{	return new RasterElementList();	}
};

inline	RasterElementList::RasterElementList(void)
{
	Page		=0;
	ItemID		=-1;
	ElementID	=-1;
	ShrinkDot	=0;
	LibCount	=0;
}

inline	bool	RasterElementList::Save(QIODevice *f)
{
	if(::Save(f,Page			)==false)
		return false;
	if(::Save(f,ItemID			)==false)
		return false;
	if(::Save(f,ElementID		)==false)
		return false;
	if(::Save(f,ReferenceColor	)==false)
		return false;
	if(::Save(f,ShrinkDot		)==false)
		return false;
	if(::Save(f,LibCount		)==false)
		return false;
	return true;
}
inline	bool	RasterElementList::Load(QIODevice *f)
{
	if(::Load(f,Page			)==false)
		return false;
	if(::Load(f,ItemID			)==false)
		return false;
	if(::Load(f,ElementID		)==false)
		return false;
	if(::Load(f,ReferenceColor	)==false)
		return false;
	if(::Load(f,ShrinkDot		)==false)
		return false;
	if(::Load(f,LibCount		)==false)
		return false;
	return true;
}

class	ReqRasterElements: public GUIDirectMessage
{
public:
	int							FileLayerID;
	RasterElementListContainer	*Elements;

	ReqRasterElements(LayersBase *base):GUIDirectMessage(base)		{}
	ReqRasterElements(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdReqRasterElementData: public GUIDirectMessage
{
public:
	int	ItemID;
	int	ElementID;
	int	ShrinkDot;
	int			InsideEdgeWidth;
	int			OutsideEdgeWidth;
	AlgorithmLibraryListContainer	AllocatedStaticLib;
	AlgorithmLibraryListContainer	AllocatedInsideEdgeLib;
	AlgorithmLibraryListContainer	AllocatedOutsideEdgeLib;
	bool	Found;

	CmdReqRasterElementData(LayersBase *base):GUIDirectMessage(base)		{}
	CmdReqRasterElementData(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdSetRasterElementData: public GUIDirectMessage
{
public:
	int	ItemID;
	int	ElementID;
	int	ShrinkDot;
	int			InsideEdgeWidth;
	int			OutsideEdgeWidth;
	AlgorithmLibraryListContainer	AllocatedStaticLib;
	AlgorithmLibraryListContainer	AllocatedInsideEdgeLib;
	AlgorithmLibraryListContainer	AllocatedOutsideEdgeLib;
	bool	DeleteMode;

	CmdSetRasterElementData(LayersBase *base):GUIDirectMessage(base)		{}
	CmdSetRasterElementData(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

//-------------------------------------------------------------------------------------
class RasterFileLayerList: public NPListSaveLoad<RasterFileLayerList>
{
public:
	int32		FileLayerID;
	QString		FileName;

	RasterFileLayerList(void){}

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
};
class RasterFileLayerListContainer : public NPListPackSaveLoad<RasterFileLayerList>
{
public:
	RasterFileLayerListContainer(void){}

	virtual	RasterFileLayerList	*Create(void)	{	return new RasterFileLayerList();	}
};

inline	bool	RasterFileLayerList::Save(QIODevice *f)
{
	if(::Save(f,FileLayerID	)==false)
		return false;
	if(::Save(f,FileName	)==false)
		return false;
	return true;
}
inline	bool	RasterFileLayerList::Load(QIODevice *f)
{
	if(::Load(f,FileLayerID	)==false)
		return false;
	if(::Load(f,FileName	)==false)
		return false;
	return true;
}

class	CmdReqRefreshLines: public GUIDirectMessage
{
public:
	RasterFileLayerListContainer	*FileLayerListContainer;

	CmdReqRefreshLines(LayersBase *base):GUIDirectMessage(base)		{}
	CmdReqRefreshLines(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdRasterRotateInCenter: public GUIDirectMessage
{
public:
	double	Angle;

	CmdRasterRotateInCenter(LayersBase *base):GUIDirectMessage(base)			{}
	CmdRasterRotateInCenter(GUICmdPacketBase *gbase):GUIDirectMessage(gbase)	{}
};
class	CmdRasterZoomInCenter: public GUIDirectMessage
{
public:
	double	XZoomDir;
	double	YZoomDir;

	CmdRasterZoomInCenter(LayersBase *base):GUIDirectMessage(base)		{}
	CmdRasterZoomInCenter(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdRasterMirrorInCenter: public GUIDirectMessage
{
public:
	bool	XMode;

	CmdRasterMirrorInCenter(LayersBase *base):GUIDirectMessage(base)			{}
	CmdRasterMirrorInCenter(GUICmdPacketBase *gbase):GUIDirectMessage(gbase)	{}
};
class	CmdRasterDelMaskByCAD: public GUIDirectMessage
{
public:
	CmdRasterDelMaskByCAD(LayersBase *base):GUIDirectMessage(base){}
	CmdRasterDelMaskByCAD(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdPickRasterColor: public GUIDirectMessage
{
public:
	int	LocalX,LocalY;
	int	FileLayerID;
	QColor	Color;
	CmdPickRasterColor(LayersBase *base):GUIDirectMessage(base){}
	CmdPickRasterColor(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdRasterDrawArea: public GUIDirectMessage
{
public:
	int			FileLayerID;
	FlexArea	Area;
	QColor		Color;
	CmdRasterDrawArea(LayersBase *base):GUIDirectMessage(base){}
	CmdRasterDrawArea(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdRasterMakeImage: public GUIDirectMessage
{
public:
	ImagePointerContainer DestBuff;

	CmdRasterMakeImage(LayersBase *base):GUIDirectMessage(base){}
	CmdRasterMakeImage(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdMoveElement: public GUIDirectMessage
{
public:
	int	MovX,MovY;
	int	ElementID;

	CmdMoveElement(LayersBase *base):GUIDirectMessage(base){}
	CmdMoveElement(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdPickRasterColorProfile: public GUIDirectMessage
{
public:
	int	LocalX,LocalY;

	CmdPickRasterColorProfile(LayersBase *base):GUIDirectMessage(base){}
	CmdPickRasterColorProfile(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdConvertColorProfiles: public GUIDirectMessage
{
public:
	CmdConvertColorProfiles(LayersBase *base):GUIDirectMessage(base){}
	CmdConvertColorProfiles(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdSetPartialArea: public GUIDirectMessage
{
public:
	FlexArea	Area;
	CmdSetPartialArea(LayersBase *base):GUIDirectMessage(base){}
	CmdSetPartialArea(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdAddRasterMaskArea: public GUIDirectMessage
{
public:
	FlexArea	MaskArea;
	int			FileLayerID;

	CmdAddRasterMaskArea(LayersBase *base):GUIDirectMessage(base){}
	CmdAddRasterMaskArea(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdDelRasterMaskArea: public GUIDirectMessage
{
public:
	int		FileLayerID;
	int		MaskID;

	CmdDelRasterMaskArea(LayersBase *base):GUIDirectMessage(base){}
	CmdDelRasterMaskArea(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdReqEnumMaskArea: public GUIDirectMessage
{
public:
	int		FileLayerID;
	IntList	MaskIDList;

	CmdReqEnumMaskArea(LayersBase *base):GUIDirectMessage(base){}
	CmdReqEnumMaskArea(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdSetPDFWithSelfTransform : public GUIDirectMessage
{
public:
	QByteArray	PDFData;
	bool		Result;

	CmdSetPDFWithSelfTransform(LayersBase *base):GUIDirectMessage(base){}
	CmdSetPDFWithSelfTransform(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdReqRasterTransformInfo : public GUIDirectMessage
{
public:
	QByteArray	TransformData;

	CmdReqRasterTransformInfo(LayersBase *base):GUIDirectMessage(base){}
	CmdReqRasterTransformInfo(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdSetRasterTransformInfo : public GUIDirectMessage
{
public:
	QByteArray	TransformData;

	CmdSetRasterTransformInfo(LayersBase *base):GUIDirectMessage(base){}
	CmdSetRasterTransformInfo(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdReqRasterProfileValue : public GUIDirectMessage
{
public:
	int	Page;
	int	LocalX,LocalY;
	QColor	ConvertedImageColor;
	QColor	PDFColor;

	CmdReqRasterProfileValue(LayersBase *base):GUIDirectMessage(base){}
	CmdReqRasterProfileValue(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdReqMakeProfileByImage : public GUIDirectMessage
{
public:
	bool	Mastered;

	CmdReqMakeProfileByImage(LayersBase *base):GUIDirectMessage(base){}
	CmdReqMakeProfileByImage(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdMakeRasterReferenceItem : public GUIDirectMessage
{
public:
	FlexArea	LocalArea;

	CmdMakeRasterReferenceItem(LayersBase *base):GUIDirectMessage(base){}
	CmdMakeRasterReferenceItem(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdReqRasterReference : public GUIDirectMessage
{
public:
	ColorProfileContainer	ColorProfile;

	CmdReqRasterReference(LayersBase *base):GUIDirectMessage(base){}
	CmdReqRasterReference(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdMakeAutoRasterReference: public GUIDirectMessage
{
public:
	int ColorMergin;
	int MinItemArea;
	int	ShrinkSize;

	CmdMakeAutoRasterReference(LayersBase *base):GUIDirectMessage(base){}
	CmdMakeAutoRasterReference(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdSaveDefaultColorProfile: public GUIDirectMessage
{
public:
	ColorProfileContainer	ColorProfiler;

	CmdSaveDefaultColorProfile(LayersBase *base):GUIDirectMessage(base){}
	CmdSaveDefaultColorProfile(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
//=============================================================

class	CmdCopyImageToMaster : public GUIDirectMessage
{
public:
	PureFlexAreaListContainer	ChangeableAreas;

	CmdCopyImageToMaster(LayersBase *base):GUIDirectMessage(base){}
	CmdCopyImageToMaster(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
