#if	!defined(XPropertyBlockCommon_H)
#define	XPropertyBlockCommon_H

#include "XGUIPacketForDLL.h"
#include "NListComp.h"
#include "XGeneralFunc.h"

class	CmdSelectBlockLibraryDialog : public GUIDirectMessage
{
public:
	int		LibID;

	CmdSelectBlockLibraryDialog(LayersBase *base):GUIDirectMessage(base)		{	LibID=-1;	}
	CmdSelectBlockLibraryDialog(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){	LibID=-1;	}
};

class	SetThresholdBlockInfo
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

	SetThresholdBlockInfo(void);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

inline	SetThresholdBlockInfo::SetThresholdBlockInfo(void)
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

inline	bool	SetThresholdBlockInfo::Save(QIODevice *f)
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
inline	bool	SetThresholdBlockInfo::Load(QIODevice *f)
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

class	BlockLibraryWithThresholdList : public NPListSaveLoad<BlockLibraryWithThresholdList>
{
public:
	int		LibID;
	SetThresholdBlockInfo	ThresholdInfo;

	BlockLibraryWithThresholdList(void)	{	LibID=-1;	}

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

class	BlockLibraryWithThresholdContainer : public NPListPackSaveLoad<BlockLibraryWithThresholdList>
{
public:
	virtual	BlockLibraryWithThresholdList	*Create(void)	{	return new BlockLibraryWithThresholdList();	}
};

inline	bool	BlockLibraryWithThresholdList::Save(QIODevice *f)
{
	if(::Save(f,LibID)==false)
		return false;
	if(ThresholdInfo.Save(f)==false)
		return false;
	return true;
}

inline	bool	BlockLibraryWithThresholdList::Load(QIODevice *f)
{
	if(::Load(f,LibID)==false)
		return false;
	if(ThresholdInfo.Load(f)==false)
		return false;
	return true;
}

//-----------------------------------------------------------------------------------------------
class	CmdRemoveAllOriginalBlockItems : public GUIDirectMessage
{
public:
	int		GeneratedOrigin;

	CmdRemoveAllOriginalBlockItems(LayersBase *base):GUIDirectMessage(base)			{	GeneratedOrigin=-1;	}
	CmdRemoveAllOriginalBlockItems(GUICmdPacketBase *gbase):GUIDirectMessage(gbase)	{	GeneratedOrigin=-1;	}
};

class	CmdUpdateBlockCommon : public GUIDirectMessage
{
public:
	int		LibID;
	SetThresholdBlockInfo	ThresholdInfo;

	CmdUpdateBlockCommon(LayersBase *base):GUIDirectMessage(base)		{	LibID=-1;	}
	CmdUpdateBlockCommon(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){	LibID=-1;	}
};

class	CmdGenerateBlockCommon : public GUIDirectMessage
{
public:
	BlockLibraryWithThresholdContainer	Infos;

	CmdGenerateBlockCommon(LayersBase *base):GUIDirectMessage(base)		{}
	CmdGenerateBlockCommon(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	UpdateBlockLibrary: public GUIDirectMessage
{
public:
	int	LibID;
	int	SpaceToOutline;		//-1:Ineffective

	UpdateBlockLibrary(LayersBase *base):GUIDirectMessage(base)			{		}
	UpdateBlockLibrary(GUICmdPacketBase *gbase):GUIDirectMessage(gbase)	{		}
};

class	ChangeBlocksThresholdCommon : public GUIDirectMessage
{
public:
	int			BlockLibID;
	QByteArray	InfosData;

	ChangeBlocksThresholdCommon(LayersBase *base):GUIDirectMessage(base)		{}
	ChangeBlocksThresholdCommon(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};


#endif