#if	!defined(XPropertyNickInspectionCommon_h)
#define	XPropertyNickInspectionCommon_h

#include "XGUIPacketForDLL.h"
#include "NListComp.h"
#include "XGeneralFunc.h"

class	CmdSelectNickInspectionLibraryDialog : public GUIDirectMessage
{
public:
	int		LibID;

	CmdSelectNickInspectionLibraryDialog(LayersBase *base):GUIDirectMessage(base)		{	LibID=-1;	}
	CmdSelectNickInspectionLibraryDialog(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){	LibID=-1;	}
};


class	ChangeNickInspectionsThresholdCommon : public GUIDirectMessage
{
public:
	int			LibID;
	QByteArray	InfosData;

	ChangeNickInspectionsThresholdCommon(LayersBase *base):GUIDirectMessage(base)		{}
	ChangeNickInspectionsThresholdCommon(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdRemoveAllOriginalNickInspectionItems : public GUIDirectMessage
{
public:
	int		GeneratedOrigin;

	CmdRemoveAllOriginalNickInspectionItems(LayersBase *base):GUIDirectMessage(base)			{	GeneratedOrigin=-1;	}
	CmdRemoveAllOriginalNickInspectionItems(GUICmdPacketBase *gbase):GUIDirectMessage(gbase)	{	GeneratedOrigin=-1;	}
};


class	SetThresholdNickInspectionInfo
{
public:
	int	Mergin;
	int	Shift;
	int	NGSize1;	//Broad
	int	NGSize2;	//Narrow

	int	CenterBright;
	int	AdjustL,AdjustH;
	int	BBrightL,BBrightH;
	int	NBrightL,NBrightH;

	SetThresholdNickInspectionInfo(void);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

inline	SetThresholdNickInspectionInfo::SetThresholdNickInspectionInfo(void)
{
	Mergin			=-1;
	Shift			=-1;
	NGSize1			=-1;
	NGSize2			=-1;

	CenterBright	=-1;
	AdjustL			=-1;
	AdjustH			=-1;
	BBrightL		=-1;
	BBrightH		=-1;
	NBrightL		=-1;
	NBrightH		=-1;
}

inline	bool	SetThresholdNickInspectionInfo::Save(QIODevice *f)
{
	if(::Save(f,Mergin)==false)
		return false;
	if(::Save(f,Shift)==false)
		return false;
	if(::Save(f,NGSize1)==false)
		return false;
	if(::Save(f,NGSize2)==false)
		return false;
	if(::Save(f,CenterBright)==false)
		return false;
	if(::Save(f,AdjustL)==false)
		return false;
	if(::Save(f,AdjustH)==false)
		return false;
	if(::Save(f,BBrightL)==false)
		return false;
	if(::Save(f,BBrightH)==false)
		return false;
	if(::Save(f,NBrightL)==false)
		return false;
	if(::Save(f,NBrightH)==false)
		return false;
	return true;
}
inline	bool	SetThresholdNickInspectionInfo::Load(QIODevice *f)
{
	if(::Load(f,Mergin)==false)
		return false;
	if(::Load(f,Shift)==false)
		return false;
	if(::Load(f,NGSize1)==false)
		return false;
	if(::Load(f,NGSize2)==false)
		return false;
	if(::Load(f,CenterBright)==false)
		return false;
	if(::Load(f,AdjustL)==false)
		return false;
	if(::Load(f,AdjustH)==false)
		return false;
	if(::Load(f,BBrightL)==false)
		return false;
	if(::Load(f,BBrightH)==false)
		return false;
	if(::Load(f,NBrightL)==false)
		return false;
	if(::Load(f,NBrightH)==false)
		return false;
	return true;
}
#endif