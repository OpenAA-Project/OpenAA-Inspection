#if	!defined(XPropertyLinePatternCommon_H)
#define	XPropertyLinePatternCommon_H

#include "XGUIPacketForDLL.h"
#include "NListComp.h"
#include "XGeneralFunc.h"

class	CmdSelectLinePatternLibraryDialog : public GUIDirectMessage
{
public:
	int		LibID;

	CmdSelectLinePatternLibraryDialog(LayersBase *base):GUIDirectMessage(base)		{	LibID=-1;	}
	CmdSelectLinePatternLibraryDialog(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){	LibID=-1;	}
};

class	SetThresholdLinePatternInfo
{
public:
	short	BrightWidthIL;
	short	BrightWidthIH;
	short	BrightWidthOL;
	short	BrightWidthOH;
	int32	NGSizeIL;
	int32	NGSizeIH;
	int32	NGSizeOL;
	int32	NGSizeOH;
	short	TransitDot;
	short	SearchDot;
	WORD	AdjustBrightIL;
	WORD	AdjustBrightIH;
	WORD	AdjustBrightOL;
	WORD	AdjustBrightOH;
	short	GlobalSearchDot;

	SetThresholdLinePatternInfo(void);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

inline	SetThresholdLinePatternInfo::SetThresholdLinePatternInfo(void)
{
	BrightWidthIL	=-1;
	BrightWidthIH	=-1;
	BrightWidthOL	=-1;
	BrightWidthOH	=-1;
	NGSizeIL		=-1;
	NGSizeIH		=-1;
	NGSizeOL		=-1;
	NGSizeOH		=-1;
	TransitDot		=-1;
	SearchDot		=-1;
	AdjustBrightIL	=-1;
	AdjustBrightIH	=-1;
	AdjustBrightOL	=-1;
	AdjustBrightOH	=-1;
	GlobalSearchDot	=-1;
}

inline	bool	SetThresholdLinePatternInfo::Save(QIODevice *f)
{
	if(::Save(f,BrightWidthIL)==false){
		return false;
	}
	if(::Save(f,BrightWidthIH)==false){
		return false;
	}
	if(::Save(f,BrightWidthOL)==false){
		return false;
	}
	if(::Save(f,BrightWidthOH)==false){
		return false;
	}
	if(::Save(f,NGSizeIL)==false){
		return false;
	}
	if(::Save(f,NGSizeIH)==false){
		return false;
	}
	if(::Save(f,NGSizeOL)==false){
		return false;
	}
	if(::Save(f,NGSizeOH)==false){
		return false;
	}
	if(::Save(f,TransitDot)==false){
		return false;
	}
	if(::Save(f,SearchDot)==false){
		return false;
	}
	if(::Save(f,AdjustBrightIL)==false){
		return false;
	}
	if(::Save(f,AdjustBrightIH)==false){
		return false;
	}
	if(::Save(f,AdjustBrightOL)==false){
		return false;
	}
	if(::Save(f,AdjustBrightOH)==false){
		return false;
	}
	if(::Save(f,GlobalSearchDot)==false){
		return false;
	}
	return true;
}
inline	bool	SetThresholdLinePatternInfo::Load(QIODevice *f)
{
	if(::Load(f,BrightWidthIL)==false){
		return false;
	}
	if(::Load(f,BrightWidthIH)==false){
		return false;
	}
	if(::Load(f,BrightWidthOL)==false){
		return false;
	}
	if(::Load(f,BrightWidthOH)==false){
		return false;
	}
	if(::Load(f,NGSizeIL)==false){
		return false;
	}
	if(::Load(f,NGSizeIH)==false){
		return false;
	}
	if(::Load(f,NGSizeOL)==false){
		return false;
	}
	if(::Load(f,NGSizeOH)==false){
		return false;
	}
	if(::Load(f,TransitDot)==false){
		return false;
	}
	if(::Load(f,SearchDot)==false){
		return false;
	}
	if(::Load(f,AdjustBrightIL)==false){
		return false;
	}
	if(::Load(f,AdjustBrightIH)==false){
		return false;
	}
	if(::Load(f,AdjustBrightOL)==false){
		return false;
	}
	if(::Load(f,AdjustBrightOH)==false){
		return false;
	}
	if(::Load(f,GlobalSearchDot)==false){
		return false;
	}
	return true;
}

class	LinePatternLibraryWithThresholdList : public NPListSaveLoad<LinePatternLibraryWithThresholdList>
{
public:
	int		LibID;
	SetThresholdLinePatternInfo	ThresholdInfo;

	LinePatternLibraryWithThresholdList(void)	{	LibID=-1;	}

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

class	LinePatternLibraryWithThresholdContainer : public NPListPackSaveLoad<LinePatternLibraryWithThresholdList>
{
public:
	virtual	LinePatternLibraryWithThresholdList	*Create(void)	{	return new LinePatternLibraryWithThresholdList();	}
};

inline	bool	LinePatternLibraryWithThresholdList::Save(QIODevice *f)
{
	if(::Save(f,LibID)==false)
		return false;
	if(ThresholdInfo.Save(f)==false)
		return false;
	return true;
}

inline	bool	LinePatternLibraryWithThresholdList::Load(QIODevice *f)
{
	if(::Load(f,LibID)==false)
		return false;
	if(ThresholdInfo.Load(f)==false)
		return false;
	return true;
}

//-----------------------------------------------------------------------------------------------
class	CmdRemoveAllOriginalLinePatternItems : public GUIDirectMessage
{
public:
	int		GeneratedOrigin;

	CmdRemoveAllOriginalLinePatternItems(LayersBase *base):GUIDirectMessage(base)			{	GeneratedOrigin=-1;	}
	CmdRemoveAllOriginalLinePatternItems(GUICmdPacketBase *gbase):GUIDirectMessage(gbase)	{	GeneratedOrigin=-1;	}
};

class	CmdUpdateLinePatternCommon : public GUIDirectMessage
{
public:
	int		LibID;
	SetThresholdLinePatternInfo	ThresholdInfo;

	CmdUpdateLinePatternCommon(LayersBase *base):GUIDirectMessage(base)		{	LibID=-1;	}
	CmdUpdateLinePatternCommon(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){	LibID=-1;	}
};

class	CmdGenerateLinePatternCommon : public GUIDirectMessage
{
public:
	LinePatternLibraryWithThresholdContainer	Infos;

	CmdGenerateLinePatternCommon(LayersBase *base):GUIDirectMessage(base)		{}
	CmdGenerateLinePatternCommon(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	UpdateLinePatternLibrary: public GUIDirectMessage
{
public:
	int	LibID;
	int	SpaceToOutline;		//-1:Ineffective

	UpdateLinePatternLibrary(LayersBase *base):GUIDirectMessage(base)			{		}
	UpdateLinePatternLibrary(GUICmdPacketBase *gbase):GUIDirectMessage(gbase)	{		}
};

class	ChangeLinePatternsThresholdCommon : public GUIDirectMessage
{
public:
	int			LinePatternLibID;
	QByteArray	InfosData;

	ChangeLinePatternsThresholdCommon(LayersBase *base):GUIDirectMessage(base)		{}
	ChangeLinePatternsThresholdCommon(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};


#endif