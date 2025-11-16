#if	!defined(XGerberFast_H)
#define	XGerberFast_H

#include <stdio.h>
#include "XTypeDef.h"
#include "XGerberFast.h"
#include "XGeneralFunc.h"
#include "XGerberFastLibrary.h"

class	CmdReqLayerColor : public GUIDirectMessage
{
public:
	int		LayerNo;
	QColor	Color;

	CmdReqLayerColor(LayersBase *base):GUIDirectMessage(base){}
	CmdReqLayerColor(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdAutoFileEntry : public GUIDirectMessage
{
public:
	QString		Path;
	QStringList	FileNames;
	ODBStepContainer	StepData;
	ODBLayerContainer	MatrixLayers;

	CmdAutoFileEntry(LayersBase *base):GUIDirectMessage(base){}
	CmdAutoFileEntry(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdAutoFileEntryODB : public GUIDirectMessage
{
public:
	QStringList LayerPathList;
	QStringList	FileNames;
	ODBStepContainer	StepData;
	ODBLayerContainer	MatrixLayers;

	CmdAutoFileEntryODB(LayersBase *base):GUIDirectMessage(base){}
	CmdAutoFileEntryODB(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdLoadGerber: public GUIDirectMessage
{
public:
	int			FileLayerID;
	QString		FileName;
	QByteArray	*pData;
	bool		Ret;

	CmdLoadGerber(LayersBase *base):GUIDirectMessage(base){}
	CmdLoadGerber(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	GerberSaveCompositeDefPacket: public GUIDirectMessage
{
public:
	QIODevice	*file;

	GerberSaveCompositeDefPacket(LayersBase *base):GUIDirectMessage(base){	file=NULL;	}
	GerberSaveCompositeDefPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){	file=NULL;	}
};

class	GerberLoadCompositeDefPacket: public GUIDirectMessage
{
public:
	QIODevice	*file;

	GerberLoadCompositeDefPacket(LayersBase *base):GUIDirectMessage(base){	file=NULL;	}
	GerberLoadCompositeDefPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){	file=NULL;	}
};

class	CmdReqGerberArea: public GUIDirectMessage
{
public:
	double	MinX,MinY,MaxX,MaxY;

	CmdReqGerberArea(LayersBase *base):GUIDirectMessage(base){}
	CmdReqGerberArea(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
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

class	CmdMove: public GUIDirectMessage
{
public:
	double	XDir;
	double	YDir;
	bool	PixelMode;

	CmdMove(LayersBase *base):GUIDirectMessage(base){}
	CmdMove(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdRotate: public GUIDirectMessage
{
public:
	double	Angle;
	double	CenterX,CenterY;

	CmdRotate(LayersBase *base):GUIDirectMessage(base){}
	CmdRotate(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdZoom: public GUIDirectMessage
{
public:
	double	XZoomDir;
	double	YZoomDir;
	double	CenterX,CenterY;

	CmdZoom(LayersBase *base):GUIDirectMessage(base){}
	CmdZoom(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdShear: public GUIDirectMessage
{
public:
	bool	XMode;
	double	Shear;
	double	CenterX,CenterY;

	CmdShear(LayersBase *base):GUIDirectMessage(base){}
	CmdShear(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdMirror: public GUIDirectMessage
{
public:
	bool	XMode;
	double	CenterX,CenterY;

	CmdMirror(LayersBase *base):GUIDirectMessage(base){}
	CmdMirror(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCenterize: public GUIDirectMessage
{
public:
	double	MovX,MovY;
	double	ZoomRate;
	double	CenterX,CenterY;

	CmdCenterize(LayersBase *base):GUIDirectMessage(base){}
	CmdCenterize(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCenterizeOnly: public GUIDirectMessage
{
public:
	double	MovX,MovY;
	double	CenterX,CenterY;

	CmdCenterizeOnly(LayersBase *base):GUIDirectMessage(base){}
	CmdCenterizeOnly(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdMatchingRoughly: public GUIDirectMessage
{
public:
	BoolList	ButtonsToShowLayer;
	IntList		OperateCompositeIDList;
	int	Dx,Dy;
	double	ZoomX,ZoomY;
	int		ZoomStartX,ZoomStartY;

	CmdMatchingRoughly(LayersBase *base):GUIDirectMessage(base){}
	CmdMatchingRoughly(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

//----------------------------------------------------------------------------

class	MsgGetGerberArea: public GUIDirectMessage
{
public:
	double pminx, pminy, pmaxx, pmaxy;
	MsgGetGerberArea(LayersBase *base):GUIDirectMessage(base){}
	MsgGetGerberArea(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};


class	MsgSaveGerberLayerList : public GUIDirectMessage
{
public:
	QString	FileName;
	MsgSaveGerberLayerList(LayersBase *base):GUIDirectMessage(base){}
	MsgSaveGerberLayerList(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	MsgLoadGerberLayerList : public GUIDirectMessage
{
public:
	QString	FileName;
	MsgLoadGerberLayerList(LayersBase *base):GUIDirectMessage(base){}
	MsgLoadGerberLayerList(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
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

class	MsgGerberDrawWithHBitmap : public GUIDirectMessage
{
public:
	QImage	*pBmp;
	QImage	*pSelectedBmp;
	double	ZoomRate;
	MsgGerberDrawWithHBitmap(LayersBase *base):GUIDirectMessage(base){}
	MsgGerberDrawWithHBitmap(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	MsgGerberDrawSelected : public GUIDirectMessage
{
public:
	QImage	SelectedImage;
	double	ZoomRate;
	MsgGerberDrawSelected(LayersBase *base):GUIDirectMessage(base){}
	MsgGerberDrawSelected(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	MsgGerberMoveTo : public GUIDirectMessage
{
public:
	int Dx,Dy;
	MsgGerberMoveTo(LayersBase *base):GUIDirectMessage(base){}
	MsgGerberMoveTo(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	MsgGerberRotate : public GUIDirectMessage
{
public:
	int Cx,Cy;
	double	Radian;
	MsgGerberRotate(LayersBase *base):GUIDirectMessage(base){}
	MsgGerberRotate(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	MsgGerberSlopeX : public GUIDirectMessage
{
public:
	int Cx,Cy;
	double	Radian;
	MsgGerberSlopeX(LayersBase *base):GUIDirectMessage(base){}
	MsgGerberSlopeX(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	MsgGerberSlopeY : public GUIDirectMessage
{
public:
	int Cx,Cy;
	double	Radian;
	MsgGerberSlopeY(LayersBase *base):GUIDirectMessage(base){}
	MsgGerberSlopeY(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	MsgGerberExtend : public GUIDirectMessage
{
public:
	int Cx,Cy;
	double	RateX,RateY;
	MsgGerberExtend(LayersBase *base):GUIDirectMessage(base){}
	MsgGerberExtend(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	MsgGerberXMirror : public GUIDirectMessage
{
public:
	MsgGerberXMirror(LayersBase *base):GUIDirectMessage(base){}
	MsgGerberXMirror(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	MsgGerberYMirror : public GUIDirectMessage
{
public:
	MsgGerberYMirror(LayersBase *base):GUIDirectMessage(base){}
	MsgGerberYMirror(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
/*
class	MsgGerberGetPickInfo : public GUIDirectMessage
{
public:
	double	GlobalX,GlobalY;
	//AXGR_PICKDATA	*PData;
	int				PDataNumb;

	MsgGerberGetPickInfo(LayersBase *base):GUIDirectMessage(base){	PData=NULL;	}
	MsgGerberGetPickInfo(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){	PData=NULL;	}
	~MsgGerberGetPickInfo(void);
};

inline	MsgGerberGetPickInfo::~MsgGerberGetPickInfo(void)
{	
	if(PData!=0){
		delete []PData;
		PData=NULL;	
	}
}
*/

class	CmdGerberExec3PointAlignment : public GUIDirectMessage
{
public:
	DoublePoint	ImagePoint[MaxGerberPointNumb];
	DoublePoint	CadPoint[MaxGerberPointNumb];	

	CmdGerberExec3PointAlignment(LayersBase *base):GUIDirectMessage(base){}
	CmdGerberExec3PointAlignment(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGerberExecAddAlignmentPoint : public GUIDirectMessage
{
public:
	DoublePoint	ImagePoint[MaxGerberPointNumb];
	DoublePoint	CadPoint[MaxGerberPointNumb];	

	CmdGerberExecAddAlignmentPoint(LayersBase *base):GUIDirectMessage(base){}
	CmdGerberExecAddAlignmentPoint(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	MsgGerberUndo : public GUIDirectMessage
{
public:
	MsgGerberUndo(LayersBase *base):GUIDirectMessage(base){}
	MsgGerberUndo(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	MsgGerberRedo : public GUIDirectMessage
{
public:
	MsgGerberRedo(LayersBase *base):GUIDirectMessage(base){}
	MsgGerberRedo(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	MsgClearDrawModeInForm : public GUIDirectMessage
{
public:
	MsgClearDrawModeInForm(LayersBase *base):GUIDirectMessage(base){}
	MsgClearDrawModeInForm(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	MsgGerberClearItems : public GUIDirectMessage
{
public:
	MsgGerberClearItems(LayersBase *base):GUIDirectMessage(base){}
	MsgGerberClearItems(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	MsgGerberClearAll : public GUIDirectMessage
{
public:
	MsgGerberClearAll(LayersBase *base):GUIDirectMessage(base){}
	MsgGerberClearAll(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	MsgGerberSelectAll : public GUIDirectMessage
{
public:
	MsgGerberSelectAll(LayersBase *base):GUIDirectMessage(base){}
	MsgGerberSelectAll(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGerberDraw: public GUIDirectMessage
{
public:
	int			GlobalX;
	int			GlobalY;
	BoolList	ButtonsToShowLayer;
	BoolList	ButtonsToOperateLayer;

	CmdGerberDraw(LayersBase *base):GUIDirectMessage(base){}
	CmdGerberDraw(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
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

class	MsgGerberCenterize: public GUIDirectMessage
{
public:
	FlexArea	Area;
	XYClassCluster XYArea;
	double		x;
	double		y;
	int			Layer;
	int			GlobalPage;
	bool		Ret;

	MsgGerberCenterize(LayersBase *base):GUIDirectMessage(base){}
	MsgGerberCenterize(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	MsgDeleteGerberPacket : public GUIDirectMessage
{
public:
	MsgDeleteGerberPacket(LayersBase *base):GUIDirectMessage(base){}
	MsgDeleteGerberPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGerberGetFileList : public GUIDirectMessage
{
public:
	QString		PathName;
	QStringList	FileNames;

	CmdGerberGetFileList(LayersBase *base):GUIDirectMessage(base){}
	CmdGerberGetFileList(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class MsgGerberCut : public GUIDirectMessage
{
public:
	MsgGerberCut(LayersBase *base):GUIDirectMessage(base){}
	MsgGerberCut(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	MsgGerberCopy : public GUIDirectMessage
{
public:
	MsgGerberCopy(LayersBase *base):GUIDirectMessage(base){}
	MsgGerberCopy(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	MsgGerberClearClipboard : public GUIDirectMessage
{
public:
	MsgGerberClearClipboard(LayersBase *base):GUIDirectMessage(base){}
	MsgGerberClearClipboard(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	MsgGerberPaste : public GUIDirectMessage
{
public:
	int index;	//íçà” PasteGerberFormÇ≈ÇÃcurrentRow();
	int	x,y;
	MsgGerberPaste(LayersBase *base):GUIDirectMessage(base){}
	MsgGerberPaste(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

struct GerberCopyInfo
{
	XDateTime DateTime;
	int64 ItemCount;
};

class CmdGetGerberCopyInfoList : public GUIDirectMessage
{
public:
	QList<GerberCopyInfo> List;
	CmdGetGerberCopyInfoList(LayersBase *base):GUIDirectMessage(base){}
	CmdGetGerberCopyInfoList(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
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

class	CmdGetGerberCompositeDefPack: public GUIDirectMessage
{
public:
	GerberCompositeDefPack	CompData;

	CmdGetGerberCompositeDefPack(LayersBase *base):GUIDirectMessage(base){}
	CmdGetGerberCompositeDefPack(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdSetGerberCompositeDefPack: public GUIDirectMessage
{
public:
	GerberCompositeDefPack	CompData;

	CmdSetGerberCompositeDefPack(LayersBase *base):GUIDirectMessage(base){}
	CmdSetGerberCompositeDefPack(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGerberReflectCompositeDef: public GUIDirectMessage
{
public:
	CmdGerberReflectCompositeDef(LayersBase *base):GUIDirectMessage(base){}
	CmdGerberReflectCompositeDef(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGerberReflectLayerType: public GUIDirectMessage
{
public:
	CmdGerberReflectLayerType(LayersBase *base):GUIDirectMessage(base){}
	CmdGerberReflectLayerType(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdAutoMatch: public GUIDirectMessage
{
public:
	CmdAutoMatch(LayersBase *base):GUIDirectMessage(base){}
	CmdAutoMatch(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

/*
class	CmdGerberCommandGetPointer : public GUIDirectMessage
{
public:
	GerberCommandStocker	*Stocker;

	CmdGerberCommandGetPointer(LayersBase *base):GUIDirectMessage(base){	Stocker=NULL;	}
	CmdGerberCommandGetPointer(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){	Stocker=NULL;	}
};

class	CmdGerberCommandClear : public GUIDirectMessage
{
public:
	CmdGerberCommandClear(LayersBase *base):GUIDirectMessage(base){}
	CmdGerberCommandClear(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGerberCommandSave : public GUIDirectMessage
{
public:
	QString	FileName;
	bool	Result;

	CmdGerberCommandSave(LayersBase *base):GUIDirectMessage(base){}
	CmdGerberCommandSave(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGerberCommandLoad : public GUIDirectMessage
{
public:
	QString	FileName;

	CmdGerberCommandLoad(LayersBase *base):GUIDirectMessage(base){}
	CmdGerberCommandLoad(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGerberCommandExecute : public GUIDirectMessage
{
public:
	bool	Result;
	CmdGerberCommandExecute(LayersBase *base):GUIDirectMessage(base){}
	CmdGerberCommandExecute(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
*/

class	CmdMakeAutoMatch: public GUIDirectMessage
{
public:
	bool	UsageLayer;
	int		UsageLayerID;	//	LayerID/CompositeID
	bool		RemoveShiftable;
	BoolList	ShiftableLayer;
	IntList		ShiftableCompositeIDList;
	int32		MinDotsForAutoMatching;
	int32		ShrinkDotForAutoMatchingArea;

	CmdMakeAutoMatch(LayersBase *base):GUIDirectMessage(base){}
	CmdMakeAutoMatch(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdClearAutoMatch: public GUIDirectMessage
{
public:

	CmdClearAutoMatch(LayersBase *base):GUIDirectMessage(base){}
	CmdClearAutoMatch(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdExecAutoMatch: public GUIDirectMessage
{
public:
	bool	UsageLayer;
	int		UsageLayerID;
	bool	RemoveShiftable;
	BoolList	ShiftableLayer;
	BoolList	ShiftableComposite;
	bool		BrighterInPattern;

	CmdExecAutoMatch(LayersBase *base):GUIDirectMessage(base){}
	CmdExecAutoMatch(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};	

class	CmdReflectOtherAlgorithm: public GUIDirectMessage
{
public:

	CmdReflectOtherAlgorithm(LayersBase *base):GUIDirectMessage(base){}
	CmdReflectOtherAlgorithm(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};	

class	CmdGetGerberFastLibraryListPacket: public GUIDirectMessage
{
public:
	int			LibFolderID;
	AlgorithmLibraryListContainer	AList;
	CmdGetGerberFastLibraryListPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetGerberFastLibraryListPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};	

class	CmdGetGerberFastTemporaryLibraryPacket: public GUIDirectMessage
{
public:
	GerberFastLibrary	*TempLib;
	CmdGetGerberFastTemporaryLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetGerberFastTemporaryLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};	

class	CmdGetGerberFastLibraryNamesPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryListContainer	AList;
	CmdGetGerberFastLibraryNamesPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetGerberFastLibraryNamesPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetGerberFastLibraryNamePacket : public GUIDirectMessage
{
public:
	int		LibID;
	QString	LibName;
	CmdGetGerberFastLibraryNamePacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetGerberFastLibraryNamePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateTempGerberFastLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdCreateTempGerberFastLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateTempGerberFastLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdClearGerberFastLibraryPacket: public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdClearGerberFastLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdClearGerberFastLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdInsertGerberFastLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdInsertGerberFastLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdInsertGerberFastLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdUpdateGerberFastLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdUpdateGerberFastLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdUpdateGerberFastLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdLoadGerberFastLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	bool				Success;
	CmdLoadGerberFastLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdLoadGerberFastLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdDeleteGerberFastLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdDeleteGerberFastLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdDeleteGerberFastLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	GerberInfo : public NPListSaveLoad<GerberInfo>
{
public:
	int		DCode;
	QString	TypeStr;
	QString	Message;
	int32	FileLayerID;
	int		ItemID;

	GerberInfo(void):DCode(-1),FileLayerID(-1){}
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

class	GerberInfoContainer : public NPListPackSaveLoad<GerberInfo>
{
public:
	GerberInfoContainer(void){}

	virtual	GerberInfo	*Create(void)	{	return new GerberInfo();	}
	GerberInfoContainer	&operator=(const GerberInfoContainer &src);
};
inline	GerberInfoContainer	&GerberInfoContainer::operator=(const GerberInfoContainer &src)
{
	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	((GerberInfoContainer *)&src)->Save(&Buff);
	Buff.seek(0);
	Load(&Buff);
	return *this;
}
inline	bool	GerberInfo::Save(QIODevice *f)
{
	if(::Save(f,DCode)==false)
		return false;
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
inline	bool	GerberInfo::Load(QIODevice *f)
{
	if(::Load(f,DCode)==false)
		return false;
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

class	CmdReqGerberInfo: public GUIDirectMessage
{
public:
	int						GlobalX ,GlobalY;
	BoolList				DrawingLayers;

	GerberInfoContainer		Answer;

	CmdReqGerberInfo(LayersBase *base):GUIDirectMessage(base){}
	CmdReqGerberInfo(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdRemoveAutoMatchPoint: public GUIDirectMessage
{
public:
	int		LocalX,LocalY;

	CmdRemoveAutoMatchPoint(LayersBase *base):GUIDirectMessage(base){}
	CmdRemoveAutoMatchPoint(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdAllocateAutoMatching: public GUIDirectMessage
{
public:
	CmdAllocateAutoMatching(LayersBase *base):GUIDirectMessage(base){}
	CmdAllocateAutoMatching(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdReqAlgoGenMap : public GUIDirectMessage
{
public:
	QByteArray	*Pointer;

	CmdReqAlgoGenMap(LayersBase *base):GUIDirectMessage(base){}
	CmdReqAlgoGenMap(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdSetAlgoGenMap : public GUIDirectMessage
{
public:
	QByteArray	*Pointer;

	CmdSetAlgoGenMap(LayersBase *base):GUIDirectMessage(base){}
	CmdSetAlgoGenMap(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

//-------------------------------------------------------------------------------------

class	GerberApertureInfo : public NPListSaveLoad<GerberApertureInfo>
{
public:
	int32		DCode;
	int32		ShapeClass;
	double		Width;
	double		Height;

	GerberApertureInfo(void);
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

inline	GerberApertureInfo::GerberApertureInfo(void)
{
	DCode	=-1;
	ShapeClass	=0;
	Width		=0;
	Height		=0;
}

inline	bool	GerberApertureInfo::Save(QIODevice *f)
{
	if(::Save(f,DCode)==false)
		return false;
	if(::Save(f,ShapeClass)==false)
		return false;
	if(::Save(f,Width)==false)
		return false;
	if(::Save(f,Height)==false)
		return false;
	return true;
}
inline	bool	GerberApertureInfo::Load(QIODevice *f)
{
	if(::Load(f,DCode)==false)
		return false;
	if(::Load(f,ShapeClass)==false)
		return false;
	if(::Load(f,Width)==false)
		return false;
	if(::Load(f,Height)==false)
		return false;
	return true;
}

class	GerberApertureInfoContainer : public NPListPackSaveLoad<GerberApertureInfo>
{
public:
	GerberApertureInfoContainer(void){}

	virtual	GerberApertureInfo	*Create(void)	{	return new GerberApertureInfo();	}
};

class	CmdReqGerberAperture : public GUIDirectMessage
{
public:
	int		GerberLayer;
	GerberApertureInfoContainer	InfoList;

	CmdReqGerberAperture(LayersBase *base):GUIDirectMessage(base){}
	CmdReqGerberAperture(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdChangeGerberAperture : public GUIDirectMessage
{
public:
	int		GerberLayer;
	GerberApertureInfoContainer	*ApertureList;
	BoolList	SelectedList;
	CmdChangeGerberAperture(LayersBase *base):GUIDirectMessage(base)		{	ApertureList=NULL;	}
	CmdChangeGerberAperture(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){	ApertureList=NULL;	}
};

class	CmdFlushMatrix : public GUIDirectMessage
{
public:
	BoolList	ButtonsToShowLayer;
	BoolList	ButtonsToOperateLayer;	
	PasteListMatrixContainer	MatrixData;

	CmdFlushMatrix(LayersBase *base):GUIDirectMessage(base)		{}
	CmdFlushMatrix(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdSetDefaultParam : public GUIDirectMessage
{
public:
	double	StartupZoomRateX;
	double	StartupZoomRateY;

	CmdSetDefaultParam(LayersBase *base):GUIDirectMessage(base)		{}
	CmdSetDefaultParam(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdReqGerberShrinked : public GUIDirectMessage
{
public:
	BoolList	ButtonsToOperateLayer;
	IntList		OperateCompositeIDList;	
	double		ShrinkedRate;
	QByteArray	ImageData;
	QByteArray	GerberData;

	CmdReqGerberShrinked(LayersBase *base):GUIDirectMessage(base)		{}
	CmdReqGerberShrinked(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdReqGerberMatchGlobal : public GUIDirectMessage
{
public:
	double ShrinkedRate;
	QByteArray	ImageData[100];
	QByteArray	GerberData[100];
	int		Dx,Dy;
	double	ZoomX,ZoomY;

	CmdReqGerberMatchGlobal(LayersBase *base):GUIDirectMessage(base)		{}
	CmdReqGerberMatchGlobal(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdReqMatchAutoLikeManual : public GUIDirectMessage
{
public:
	QByteArray	MatchAutoLikeManualData;

	CmdReqMatchAutoLikeManual(LayersBase *base):GUIDirectMessage(base)		{}
	CmdReqMatchAutoLikeManual(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdSetMatchAutoLikeManual : public GUIDirectMessage
{
public:
	QByteArray	MatchAutoLikeManualData;
	MatchAutoLikeManualContainer	*Point;

	CmdSetMatchAutoLikeManual(LayersBase *base):GUIDirectMessage(base)		{}
	CmdSetMatchAutoLikeManual(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdSaveMatchAutoLikeManual: public GUIDirectMessage
{
public:
	QByteArray	MatchAutoLikeManualData;
	MatchAutoLikeManualContainer	*Point;

	CmdSaveMatchAutoLikeManual(LayersBase *base):GUIDirectMessage(base)		{}
	CmdSaveMatchAutoLikeManual(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdLoadMatchAutoLikeManual: public GUIDirectMessage
{
public:
	QByteArray	MatchAutoLikeManualData;

	CmdLoadMatchAutoLikeManual(LayersBase *base):GUIDirectMessage(base)		{}
	CmdLoadMatchAutoLikeManual(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetMatchAutoLikeManual: public GUIDirectMessage
{
public:
	MatchAutoLikeManualContainer	*Point;

	CmdGetMatchAutoLikeManual(LayersBase *base):GUIDirectMessage(base)		{}
	CmdGetMatchAutoLikeManual(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdAddMatchAutoLikeManualPoint: public GUIDirectMessage
{
public:
	int32	PointType;

	CmdAddMatchAutoLikeManualPoint(LayersBase *base):GUIDirectMessage(base)		{}
	CmdAddMatchAutoLikeManualPoint(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdAddMatchAutoLikeManualAlignment: public GUIDirectMessage
{
public:
	int32	PointType;
	FlexArea	Area;
	IntList		LayerList;

	CmdAddMatchAutoLikeManualAlignment(LayersBase *base):GUIDirectMessage(base)		{}
	CmdAddMatchAutoLikeManualAlignment(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdSaveMatchAutoLikeManualStream: public GUIDirectMessage
{
public:
	MatchAutoLikeManualContainer	*Point;
	QIODevice						*f;
	bool							Ret;

	CmdSaveMatchAutoLikeManualStream(LayersBase *base):GUIDirectMessage(base)		{}
	CmdSaveMatchAutoLikeManualStream(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdLoadMatchAutoLikeManualStream: public GUIDirectMessage
{
public:
	MatchAutoLikeManualContainer	*Point;
	QIODevice						*f;
	bool							Ret;

	CmdLoadMatchAutoLikeManualStream(LayersBase *base):GUIDirectMessage(base)		{}
	CmdLoadMatchAutoLikeManualStream(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdReqGeneralPipeInfo: public GUIDirectMessage
{
public:
	GeneralPipeInfo	*Point;

	CmdReqGeneralPipeInfo(LayersBase *base):GUIDirectMessage(base)			{	Point=NULL;	}
	CmdReqGeneralPipeInfo(GUICmdPacketBase *gbase):GUIDirectMessage(gbase)	{	Point=NULL;	}

	~CmdReqGeneralPipeInfo(void){	delete	Point;	Point=NULL;	}
};

class	CmdGenerateOutline : public GUIDirectMessage
{
public:
	BoolList	ButtonsToOperateLayer;
	BoolList	ButtonsToOperateComposite;

	CmdGenerateOutline(LayersBase *base):GUIDirectMessage(base)		{}
	CmdGenerateOutline(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateEchingFactor : public GUIDirectMessage
{
public:
	BoolList	ButtonsToOperateLayer;
	BoolList	ButtonsToOperateComposite;
	double		CornerR;

	CmdCreateEchingFactor(LayersBase *base):GUIDirectMessage(base)		{}
	CmdCreateEchingFactor(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdClearOutline : public GUIDirectMessage
{
public:

	CmdClearOutline(LayersBase *base):GUIDirectMessage(base)		{}
	CmdClearOutline(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

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
	int		LineNo;

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

class	CmdAddGerberLineA: public GUIDirectMessage
{
public:
	int		FileLayerNo;
	int		DCode;
	double	X1,Y1,X2,Y2;

	CmdAddGerberLineA(LayersBase *base):GUIDirectMessage(base){}
	CmdAddGerberLineA(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGenerateCenterize: public GUIDirectMessage
{
public:
	double MaxWidth;
	CmdGenerateCenterize(LayersBase *base):GUIDirectMessage(base){}
	CmdGenerateCenterize(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdSetDrawAttr: public GUIDirectMessage
{
public:
	IntListFast		ShownFileID;
	IntListFast		ShownCompositeID;
	int				FileLayerIDTable[MaxGerberLayer];
	CmdSetDrawAttr(LayersBase *base):GUIDirectMessage(base){}
	CmdSetDrawAttr(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdMakeClusterItem: public GUIDirectMessage
{
public:
	BoolList	ButtonsToOperateLayer;
	IntList		OperateCompositeIDList;

	CmdMakeClusterItem(LayersBase *base):GUIDirectMessage(base){}
	CmdMakeClusterItem(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdReqResult: public GUIDirectMessage
{
public:
	IntList	TotalHoles;
	IntList	NGHoles;
	int32	PinholeCount;

	CmdReqResult(LayersBase *base):GUIDirectMessage(base){}
	CmdReqResult(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCopyPageAllFrom: public GUIDirectMessage
{
public:
	GerberFastInPage	*SourcePage;

	CmdCopyPageAllFrom(LayersBase *base):GUIDirectMessage(base){}
	CmdCopyPageAllFrom(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdReqPatternResult :  public GUIDirectMessage
{
public:
	int						ImageLayer;
	bool					FileLayerMode;
	int						GerberLayerID;
	int						GerberItemID;

	PatternList				Data;

	CmdReqPatternResult(LayersBase *base):GUIDirectMessage(base){}
	CmdReqPatternResult(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetApertureName: public GUIDirectMessage
{
public:
	int		ApertureClassID;
	QString	ApertureName;

	CmdGetApertureName(LayersBase *base):GUIDirectMessage(base){}
	CmdGetApertureName(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};


class	GerberSaveCompositeDefIntoFilePacket: public GUIDirectMessage
{
public:
	QString	FileName;
	bool	RetSuccess;
	GerberSaveCompositeDefIntoFilePacket(LayersBase *base):GUIDirectMessage(base)			{	RetSuccess=false;	}
	GerberSaveCompositeDefIntoFilePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase)	{	RetSuccess=false;	}
};

class	GerberLoadCompositeDefIntoFilePacket: public GUIDirectMessage
{
public:
	QString	FileName;
	bool	RetSuccess;
	GerberLoadCompositeDefIntoFilePacket(LayersBase *base):GUIDirectMessage(base)			{	RetSuccess=false;	}
	GerberLoadCompositeDefIntoFilePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase)	{	RetSuccess=false;	}
};

class	GerberAppendCompositeDefIntoFilePacket: public GUIDirectMessage
{
public:
	QString	FileName;
	bool	RetSuccess;
	GerberAppendCompositeDefIntoFilePacket(LayersBase *base):GUIDirectMessage(base)			{	RetSuccess=false;	}
	GerberAppendCompositeDefIntoFilePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase)	{	RetSuccess=false;	}
};

class	CmdSelectItemsGerberFast : public GUIDirectMessage
{
public:
	FlexArea	Area;
	BoolList	ButtonsToOperateLayer;

	CmdSelectItemsGerberFast(LayersBase *base):GUIDirectMessage(base)		{}
	CmdSelectItemsGerberFast(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

#endif