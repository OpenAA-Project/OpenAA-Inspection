#if	!defined(XPropertyEulerRingL1Common_h)
#define	XPropertyEulerRingL1Common_h

#include "XGUIPacketForDLL.h"
#include "NListComp.h"
#include "XGeneralFunc.h"

class	CmdSelectEulerRingL1LibraryDialog : public GUIDirectMessage
{
public:
	int		LibID;

	CmdSelectEulerRingL1LibraryDialog(LayersBase *base):GUIDirectMessage(base)		{	LibID=-1;	}
	CmdSelectEulerRingL1LibraryDialog(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){	LibID=-1;	}
};


class	ChangeEulerRingL1sThresholdCommon : public GUIDirectMessage
{
public:
	int			BlockLibID;
	QByteArray	InfosData;

	ChangeEulerRingL1sThresholdCommon(LayersBase *base):GUIDirectMessage(base)		{}
	ChangeEulerRingL1sThresholdCommon(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdRemoveAllOriginalEulerRingL1Items : public GUIDirectMessage
{
public:
	int		GeneratedOrigin;

	CmdRemoveAllOriginalEulerRingL1Items(LayersBase *base):GUIDirectMessage(base)			{	GeneratedOrigin=-1;	}
	CmdRemoveAllOriginalEulerRingL1Items(GUICmdPacketBase *gbase):GUIDirectMessage(gbase)	{	GeneratedOrigin=-1;	}
};


class	SetThresholdEulerRingL1Info
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

	SetThresholdEulerRingL1Info(void);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

inline	SetThresholdEulerRingL1Info::SetThresholdEulerRingL1Info(void)
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

inline	bool	SetThresholdEulerRingL1Info::Save(QIODevice *f)
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
inline	bool	SetThresholdEulerRingL1Info::Load(QIODevice *f)
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