#if	!defined(XGerberFastComposite_h)
#define	XGerberFastComposite_h

#include "XGeneralFunc.h"
#include "XMainSchemeMemory.h"
#include "XDataInLayer.h"
#include "NListComp.h"

#define	CommonID_GerberCompositeDefinition	2100


class	GerberCompositeDefLayerItem : public NPListSaveLoad<GerberCompositeDefLayerItem>
{
public:
	enum	_Operation{
		_Or			=0
		,_And		=2
		,_NotAnd	=1
		,_NotOr		=3
	}Operation;
	int32	LayerTypeLibID;
	int32	DotSpr;
	bool	NegMode;

	GerberCompositeDefLayerItem(void){	Operation=_Or;	LayerTypeLibID=0;	LayerTypeLibID=0;	DotSpr=0;	NegMode=false;	}

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
	GerberCompositeDefLayerItem	&operator=(GerberCompositeDefLayerItem &src);
};

class	GerberCompositeDefLayerItemContainer : public NPListPackSaveLoad<GerberCompositeDefLayerItem>
{
public:
	virtual	GerberCompositeDefLayerItem	*Create(void){	return new GerberCompositeDefLayerItem();	}

	GerberCompositeDefLayerItemContainer	&operator=(GerberCompositeDefLayerItemContainer &src);
};

class	GerberCompositeDefLayer : public NPList<GerberCompositeDefLayer>
{
public:
	QString	Name;
	int		LibFolderID;
	int32	CompositeID;
	int		LibID;
	bool	NegMode;
	int		SourceCompositeID;

	GerberCompositeDefLayerItemContainer	Combination;

	GerberCompositeDefLayer(void){	LibFolderID=-1;	Name="Example 1";	NegMode=false;	LibID=-1;	CompositeID=-1;	SourceCompositeID=-1;	}
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
	GerberCompositeDefLayer	&operator=(GerberCompositeDefLayer &src);
};

class	GerberCompositeDefPack : public NPListPack<GerberCompositeDefLayer>
{
public:
	GerberCompositeDefPack(void){}

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
	bool	Append(QIODevice *f);
	GerberCompositeDefPack	&operator=(GerberCompositeDefPack &src);
	int32	GetMaxID(void);
	GerberCompositeDefLayer	*Search(int compositeDefID);
	bool	CopyCompositeIntoFolder(int NewLibFolderID , int OriginalLibFolderID);

	void	EnumChildren(int CompositeID ,IntList &RetID);
};

class	GerberLayerBase
{
public:
	GerberLayerBase(void){}

};

class	GerberCompositeLayer : public GerberLayerBase,public NPList<GerberCompositeLayer>
{
public:
	int32	CompositeID;
	QColor	LayerColor;
	QString	Remark;
	bool	Visible;
	bool	Operational;

	GerberCompositeLayer(int compsiteIndex);
	GerberCompositeLayer	&operator=(GerberCompositeLayer &src);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

};

inline	GerberCompositeLayer::GerberCompositeLayer(int compsiteid)
{	
	CompositeID=compsiteid;
	Visible=false;	
	Operational=true;
	LayerColor	=Qt::cyan;
}

class	GerberCompositeLayerContainer : public NPListPack<GerberCompositeLayer>
{
public:
	GerberCompositeLayerContainer(void);

	GerberCompositeLayerContainer	&operator=(GerberCompositeLayerContainer &src);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

//========================================================================================


#endif