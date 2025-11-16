#if	!defined(XPropertyAlignmentLargeCommon_H)
#define	XPropertyAlignmentLargeCommon_H

//#include "XGUIDLL.h"
//#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "NListComp.h"
#include "XGeneralFunc.h"
#include "XAlgorithmLibrary.h"
#include "XAlignmentLarge.h"

//=========================================================================

class	CmdSelectAlignmentLargeLibraryDialog : public GUIDirectMessage
{
public:
	int		LibID;

	CmdSelectAlignmentLargeLibraryDialog(LayersBase *base):GUIDirectMessage(base)		{	LibID=-1;	}
	CmdSelectAlignmentLargeLibraryDialog(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){	LibID=-1;	}
};


class	AlignmentLargeAreaList : public NPList<AlignmentLargeAreaList>
{
public:
	int		Number;
	int		AreaID;
	QString	AreaName;
	int		MasterNo;
	int		Layer;
	int		GlobalPage;
	int		XSize;
	int		YSize;
	AlgorithmLibraryListContainer		LimitedLib;
	XAlignmentLargeArea::_EnumPriority	Priority;
	
	AlignmentLargeAreaList(void){}

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	AlignmentLargeAreaList	&operator=(AlignmentLargeAreaList &src);
};

class	AlignmentLargeAreaListPack : public NPListPack<AlignmentLargeAreaList>
{
public:
	AlignmentLargeAreaListPack(void){}

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	AlignmentLargeAreaListPack	&operator=(AlignmentLargeAreaListPack &src);
	AlignmentLargeAreaListPack	&operator+=(AlignmentLargeAreaListPack &src);
};

class	CmdReqAlignmentLargeAreaListPack : public GUIDirectMessage
{
public:
	int							Layer;
	AlignmentLargeAreaListPack	*Area;

	CmdReqAlignmentLargeAreaListPack(LayersBase *base):GUIDirectMessage(base)			{}
	CmdReqAlignmentLargeAreaListPack(GUICmdPacketBase *gbase):GUIDirectMessage(gbase)	{}
};
class	CmdSetAlignmentLargeAreaListPackToSlave : public GUIDirectMessage
{
public:
	int							Layer;
	CmdSetAlignmentLargeAreaListPackToSlave(LayersBase *base):GUIDirectMessage(base)			{}
	CmdSetAlignmentLargeAreaListPackToSlave(GUICmdPacketBase *gbase):GUIDirectMessage(gbase)	{}
};

//==============================================================

class	CmdReqAddAlignmentArea : public GUIDirectMessage
{
public:
    FlexArea        Area;
	QString			AreaName;
	XAlignmentLargeArea::_EnumPriority	Priority;
	AlgorithmLibraryListContainer	LimitedLib;

	int32           GeneratedAreaID;

	CmdReqAddAlignmentArea(LayersBase *base):GUIDirectMessage(base)			{}
	CmdReqAddAlignmentArea(GUICmdPacketBase *gbase):GUIDirectMessage(gbase)	{}
};

class	CmdReqAddAlignmentPoint : public GUIDirectMessage
{
public:
	int32           AreaID;
    FlexArea        Area;
	int				MoveDotX,MoveDotY;

	CmdReqAddAlignmentPoint(LayersBase *base):GUIDirectMessage(base)			{}
	CmdReqAddAlignmentPoint(GUICmdPacketBase *gbase):GUIDirectMessage(gbase)	{}
};



#endif