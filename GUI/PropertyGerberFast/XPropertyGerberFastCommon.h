#if	!defined(XPropertyGerberFastCommon_H)
#define	XPropertyGerberFastCommon_H

//#include "XGUIDLL.h"
//#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "NListComp.h"
#include "XGeneralFunc.h"

//=========================================================================
class	CmdSearchLayerLibByDialog : public GUIDirectMessage
{
public:
	int		LibID;

	CmdSearchLayerLibByDialog(LayersBase *base):GUIDirectMessage(base)			{	LibID=-1;	}
	CmdSearchLayerLibByDialog(GUICmdPacketBase *gbase):GUIDirectMessage(gbase)	{	LibID=-1;	}
};

class	CmdSearcCompositeIDByDialog : public GUIDirectMessage
{
public:
	int		CompositeID;

	CmdSearcCompositeIDByDialog(LayersBase *base):GUIDirectMessage(base)			{	CompositeID=-1;	}
	CmdSearcCompositeIDByDialog(GUICmdPacketBase *gbase):GUIDirectMessage(gbase)	{	CompositeID=-1;	}
};

class	CmdGetCompositeName : public GUIDirectMessage
{
public:
	int		CompositeID;
	QString	CompositeName;

	CmdGetCompositeName(LayersBase *base):GUIDirectMessage(base)			{	CompositeID=-1;	}
	CmdGetCompositeName(GUICmdPacketBase *gbase):GUIDirectMessage(gbase)	{	CompositeID=-1;	}
};


class	GerberGenerationFileList : public NPListSaveLoad<GerberGenerationFileList>
{
public:
	QString		FileName;
	bool		Inverted;
	int			Shift;
	int			LayerLibID;
	int			LibID;

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

class	GerberGenerationFileContainer : public NPListPackSaveLoad<GerberGenerationFileList>
{
public:
	GerberGenerationFileContainer(void){}

	virtual	GerberGenerationFileList	*Create(void)	{	return new GerberGenerationFileList();	}
	GerberGenerationFileList	*SearchByFileName(const QString &FileName);
	GerberGenerationFileContainer	&operator=(GerberGenerationFileContainer &src);
};

inline	bool	GerberGenerationFileList::Save(QIODevice *f)
{
	if(::Save(f,FileName)==false)
		return false;
	if(::Save(f,Inverted)==false)
		return false;
	if(::Save(f,Shift)==false)
		return false;
	if(::Save(f,LayerLibID)==false)
		return false;
	if(::Save(f,LibID)==false)
		return false;
	return true;
}

inline	bool	GerberGenerationFileList::Load(QIODevice *f)
{
	if(::Load(f,FileName)==false)
		return false;
	if(::Load(f,Inverted)==false)
		return false;
	if(::Load(f,Shift)==false)
		return false;
	if(::Load(f,LayerLibID)==false)
		return false;
	if(::Load(f,LibID)==false)
		return false;
	return true;
}
inline	GerberGenerationFileContainer	&GerberGenerationFileContainer::operator=(GerberGenerationFileContainer &src)
{
	NPListPackSaveLoad<GerberGenerationFileList>::operator=(src);
	return *this;
}

inline	GerberGenerationFileList	*GerberGenerationFileContainer::SearchByFileName(const QString &FileName)
{
	for(GerberGenerationFileList *g=GetFirst();g!=NULL;g=g->GetNext()){
		if(g->FileName==FileName)
			return g;
	}
	return NULL;
}

class	GenerateBlocksFrom : public GUIDirectMessage
{
public:
	int	LayerOrComposite;	//0:Layer ,1:Composite;
	int	LayerCompositeID;
	int	GeneratedLibType;
	int	GeneratedLibID;
	int	OmitLayerOrComposite;	//0:Layer ,1:Composite;
	int	OmitLayerCompositeID;

	GerberGenerationFileContainer	GFileContainer;

	QByteArray	ThresholdData;

	GenerateBlocksFrom(LayersBase *base):GUIDirectMessage(base)			{		}
	GenerateBlocksFrom(GUICmdPacketBase *gbase):GUIDirectMessage(gbase)	{		}
};


class	CmdReqGerberLayerList : public GUIDirectMessage
{
public:
	GerberGenerationFileContainer	GFileContainer;

	QByteArray	ThresholdData;

	CmdReqGerberLayerList(LayersBase *base):GUIDirectMessage(base)			{		}
	CmdReqGerberLayerList(GUICmdPacketBase *gbase):GUIDirectMessage(gbase)	{		}
};

class	CmdSetLayerLibID : public GUIDirectMessage
{
public:
	int		LibID;

	CmdSetLayerLibID(LayersBase *base):GUIDirectMessage(base)			{	LibID=-1;	}
	CmdSetLayerLibID(GUICmdPacketBase *gbase):GUIDirectMessage(gbase)	{	LibID=-1;	}
};

class	GerberInLayerBase : public QWidget
{
public:
	GerberInLayerBase(QWidget *obj)
		:QWidget(obj){}

	virtual	void	DragTransferDirently(GUIDirectMessage *packet)	=0;
};

class	CmdDeallocateLibInLine : public GUIDirectMessage
{
public:
	QString		FileName;

	CmdDeallocateLibInLine(LayersBase *base):GUIDirectMessage(base)			{	}
	CmdDeallocateLibInLine(GUICmdPacketBase *gbase):GUIDirectMessage(gbase)	{	}
};

class	LibIDAndInvertedList : public NPListSaveLoad<LibIDAndInvertedList>
{
public:
	bool	Inverted;
	int32	LayerLibID;

	LibIDAndInvertedList(void)	{	Inverted=false;	LayerLibID=-1;	}

	virtual	bool	Save(QIODevice *f)
	{
		if(::Save(f,Inverted)==false)
			return false;
		if(::Save(f,LayerLibID)==false)
			return false;
		return true;
	}
	virtual	bool	Load(QIODevice *f)
	{
		if(::Load(f,Inverted)==false)
			return false;
		if(::Load(f,LayerLibID)==false)
			return false;
		return true;
	}
};
class	LibIDAndInvertedContainer : public NPListPackSaveLoad<LibIDAndInvertedList>
{
public:
	virtual	LibIDAndInvertedList	*Create(void)	{	return new LibIDAndInvertedList();	}
};


class	CmdSetFileInvert : public GUIDirectMessage
{
public:
	LibIDAndInvertedContainer	*Container;

	CmdSetFileInvert(LayersBase *base):GUIDirectMessage(base)			{	}
	CmdSetFileInvert(GUICmdPacketBase *gbase):GUIDirectMessage(gbase)	{	}
};

class	CmdSetCompositeLine : public GUIDirectMessage
{
public:
	int32	GerberType;
	int32	GerberID;	//CompositeID or LayerID(LibID)

	CmdSetCompositeLine(LayersBase *base):GUIDirectMessage(base)			{	}
	CmdSetCompositeLine(GUICmdPacketBase *gbase):GUIDirectMessage(gbase)	{	}
};

class	CmdEnumCompositeChildren : public GUIDirectMessage
{
public:
	int		CompositeID;
	IntList	RetList;

	CmdEnumCompositeChildren(LayersBase *base):GUIDirectMessage(base)			{	CompositeID=-1;	}
	CmdEnumCompositeChildren(GUICmdPacketBase *gbase):GUIDirectMessage(gbase)	{	CompositeID=-1;	}
};

class	CmdGetCompositeFolderID : public GUIDirectMessage
{
public:
	int		CompositeID;
	int		RetFolderID;

	CmdGetCompositeFolderID(LayersBase *base):GUIDirectMessage(base)			{	CompositeID=-1;	RetFolderID=-1;	}
	CmdGetCompositeFolderID(GUICmdPacketBase *gbase):GUIDirectMessage(gbase)	{	CompositeID=-1;	RetFolderID=-1;	}
};

class	CmdDrawIntoBitBuffer : public GUIDirectMessage
{
public:
	BYTE	**BitImageBuffer;
	int		SDotPerLine;
	int		SMaxLines;
	BoolList	ButtonsToOperateLayer;
	IntList		OperateCompositeIDList;

	CmdDrawIntoBitBuffer(LayersBase *base):GUIDirectMessage(base)			{	BitImageBuffer=NULL;	}
	CmdDrawIntoBitBuffer(GUICmdPacketBase *gbase):GUIDirectMessage(gbase)	{	BitImageBuffer=NULL;	}
};

#endif