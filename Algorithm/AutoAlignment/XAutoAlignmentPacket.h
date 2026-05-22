#pragma once

#include "XMainSchemeMemory.h"
#include "XDataInLayer.h"
#include "XColorSpace.h"
#include "XServiceForLayers.h"
#include "XDataModelPageItem.h"
#include "XDoubleClass.h"
#include "XFlexAreaImage.h"
#include "XAlgorithmLibrary.h"
#include "XGeneralFunc.h"
#include "XDataAlgorithm.h"
#include "XAutoAlignmentCommon.h"
#include "XStandardCommand.h"


//==================================================================================
class	CmdCreateTempAutoAlignmentLibraryPacket: public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdCreateTempAutoAlignmentLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateTempAutoAlignmentLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetAutoAlignmentLibraryListPacket : public GUIDirectMessage
{
public:
	int			LibFolderID;
	AlgorithmLibraryListContainer	AList;
	CmdGetAutoAlignmentLibraryListPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetAutoAlignmentLibraryListPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdLoadAutoAlignmentLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	bool				Success;
	CmdLoadAutoAlignmentLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdLoadAutoAlignmentLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdClearAutoAlignmentLibraryPacket: public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdClearAutoAlignmentLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdClearAutoAlignmentLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdDeleteAutoAlignmentLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdDeleteAutoAlignmentLibraryPacket (LayersBase *base):GUIDirectMessage(base){}
	CmdDeleteAutoAlignmentLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdInsertAutoAlignmentLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdInsertAutoAlignmentLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdInsertAutoAlignmentLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdUpdateAutoAlignmentLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdUpdateAutoAlignmentLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdUpdateAutoAlignmentLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetAutoAlignmentLibraryNamePacket : public GUIDirectMessage
{
public:
	int					LibID;
	QString				LibName;
	bool				Success;
	CmdGetAutoAlignmentLibraryNamePacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetAutoAlignmentLibraryNamePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};


class	CmdCreateAutoAlignmentSheetPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryListContainer	SelectedLibList;
	int								LocalPage;

	CmdCreateAutoAlignmentSheetPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateAutoAlignmentSheetPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdGetSheetLevel: public GUIDirectMessage
{
public:
	IntList	SheetLevels;
	int		LocalPage;
	CmdGetSheetLevel(LayersBase *base):GUIDirectMessage(base){}
	CmdGetSheetLevel(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	GUICmdReqAutoAlignmentDrawMode: public GUIDirectMessage
{
public:
	int		DrawSheetMode;
	bool	DrawMono;
	int		MonoLevel;
	int		DrawPico;
	AAListAttrContainer	SelectedLDList;

	GUICmdReqAutoAlignmentDrawMode(LayersBase *base):GUIDirectMessage(base){}
	GUICmdReqAutoAlignmentDrawMode(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetAutoAlignmentSheetPacket : public GUIDirectMessage
{
public:
	AASheetInfos	*Point;

	CmdGetAutoAlignmentSheetPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetAutoAlignmentSheetPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetAutoAlignmentResult : public GUIDirectMessage
{
public:
	int	LocalX,LocalY;
	int	ShiftXFromMaster,ShiftYFromMaster;
	int	ShiftXFromTarget,ShiftYFromTarget;
	int	ShiftRelativeXFromMaster,ShiftRelativeYFromMaster;
	int	ShiftRelativeXFromTarget,ShiftRelativeYFromTarget;

	CmdGetAutoAlignmentResult(LayersBase *base):GUIDirectMessage(base){}
	CmdGetAutoAlignmentResult(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdAutoAlignmentNoAdjustPacket : public GUIDirectMessage
{
public:

	CmdAutoAlignmentNoAdjustPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdAutoAlignmentNoAdjustPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdSetAutoAlignmentLibColor : public GUIDirectMessage
{
public:
	FlexArea	LocalArea;
	int			LibID;

	CmdSetAutoAlignmentLibColor(LayersBase *base):GUIDirectMessage(base){}
	CmdSetAutoAlignmentLibColor(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdAddAutoAlignmentSheet : public GUIDirectMessage
{
public:
	FlexArea	LocalArea;
	int			LibID;

	CmdAddAutoAlignmentSheet(LayersBase *base):GUIDirectMessage(base){}
	CmdAddAutoAlignmentSheet(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

//=========================================================================
class	CmdReqAutoAlignmentEnumLibs: public GUIDirectMessage
//	StartupExecute=true�̃��C�u������LibID���X�g�R���e�i���O�����珊������
{
public:
	IntList	LibIDList;
	CmdReqAutoAlignmentEnumLibs(LayersBase *base):GUIDirectMessage(base){}
	CmdReqAutoAlignmentEnumLibs(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

//=========================================================================
class	CmdPickupTestAutoAlignmentPacket : public GUIDirectMessage
{
public:
///	int						LibID;
///	AutoAlignmentLibrary	*LibPoint;
	int				PhaseNumb;
	int				Page;

	CmdPickupTestAutoAlignmentPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdPickupTestAutoAlignmentPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

