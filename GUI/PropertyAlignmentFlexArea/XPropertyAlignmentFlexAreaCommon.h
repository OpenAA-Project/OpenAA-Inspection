#if	!defined(XPropertyAlignmentFlexAreaCommon_H)
#define	XPropertyAlignmentFlexAreaCommon_H

//#include "XGUIDLL.h"
//#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "NListComp.h"
#include "XGeneralFunc.h"

//=========================================================================


class	CmdSelectAlignmentFlexAreaLibraryDialog : public GUIDirectMessage
{
public:
	int		LibID;

	CmdSelectAlignmentFlexAreaLibraryDialog(LayersBase *base):GUIDirectMessage(base)		{	LibID=-1;	}
	CmdSelectAlignmentFlexAreaLibraryDialog(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){	LibID=-1;	}
};


class	SetThresholdAlignmentFlexAreaInfo
{
public:
	int32		GlobalSearchDot;
	int32		SearchDot;

	SetThresholdAlignmentFlexAreaInfo(void);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

inline	SetThresholdAlignmentFlexAreaInfo::SetThresholdAlignmentFlexAreaInfo(void)
{
	SearchDot		=-1;
	GlobalSearchDot	=-1;
}

inline	bool	SetThresholdAlignmentFlexAreaInfo::Save(QIODevice *f)
{
	if(::Save(f,SearchDot)==false){
		return false;
	}
	if(::Save(f,GlobalSearchDot)==false){
		return false;
	}
	return true;
}
inline	bool	SetThresholdAlignmentFlexAreaInfo::Load(QIODevice *f)
{
	if(::Load(f,SearchDot)==false){
		return false;
	}
	if(::Load(f,GlobalSearchDot)==false){
		return false;
	}
	return true;
}

class	ChangeAlignmentFlexAreaThresholdCommon : public GUIDirectMessage
{
public:
	int			LibID;
	QByteArray	InfosData;

	ChangeAlignmentFlexAreaThresholdCommon(LayersBase *base):GUIDirectMessage(base)		{}
	ChangeAlignmentFlexAreaThresholdCommon(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdRemoveAllOriginalAlignmentFlexAreaItems : public GUIDirectMessage
{
public:
	int		GeneratedOrigin;

	CmdRemoveAllOriginalAlignmentFlexAreaItems(LayersBase *base):GUIDirectMessage(base)			{	GeneratedOrigin=-1;	}
	CmdRemoveAllOriginalAlignmentFlexAreaItems(GUICmdPacketBase *gbase):GUIDirectMessage(gbase)	{	GeneratedOrigin=-1;	}
};


class	CmdCreateBaseMatchBuffer : public GUIDirectMessage
{
public:
	BYTE	**BitImageBuffer;
	int		SDotPerLine;
	int		SMaxLines;
	double	ZoomRate;

	CmdCreateBaseMatchBuffer(LayersBase *base):GUIDirectMessage(base)			{	BitImageBuffer=NULL;	}
	CmdCreateBaseMatchBuffer(GUICmdPacketBase *gbase):GUIDirectMessage(gbase)	{	BitImageBuffer=NULL;	}
};
class	CmdGenerateBaseMatchGUI : public GUIDirectMessage
{
public:
	CmdGenerateBaseMatchGUI(LayersBase *base):GUIDirectMessage(base)			{	}
	CmdGenerateBaseMatchGUI(GUICmdPacketBase *gbase):GUIDirectMessage(gbase)	{	}
};
class	CmdExecBaseMatchResult : public GUIDirectMessage
{
public:
	int		ResultDx;
	int		ResultDy;
	double	Angle;

	CmdExecBaseMatchResult(LayersBase *base):GUIDirectMessage(base)			{	ResultDx=ResultDy=0;	Angle=0;	}
	CmdExecBaseMatchResult(GUICmdPacketBase *gbase):GUIDirectMessage(gbase)	{	ResultDx=ResultDy=0;	Angle=0;	}
};

#endif