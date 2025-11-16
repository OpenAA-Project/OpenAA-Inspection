/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\TreeMaster\XTreeMaster.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#if	!defined(XTREEMASTER_H)
#define	XTREEMASTER_H


#include "XDataInLayer.h"
#include "XDataModelPageItem.h"
#include "XAlgorithmLibrary.h"
#include "XDirectComm.h"
#include "NListComp.h"
#include "XColorSpace.h"
#include "XTreeMasterCommon.h"
#include "XFlexAreaImage.h"

class	TreeMasterItem;
class	TreeMasterInPage;
class	TreeMasterBase;

#define	TreeMasterVersion		1
#define	DefLibTypeTreeMaster			60

class TreeMasterDrawAttr : public AlgorithmDrawAttr{
public:
	int		ShowingMasterCode;
	TreeMasterDrawAttr(void){	ShowingMasterCode=-1;	};
	TreeMasterDrawAttr(QColor ncol,int ntrans,QColor scol,int strans,QColor acol,int atrans) : AlgorithmDrawAttr(ncol,ntrans,scol,strans,acol,atrans){	ShowingMasterCode=-1;	};
};

//==================================================
class	TreeMasterLibrary : public AlgorithmLibrary , public ServiceForLayers
{
public:

	TreeMasterLibrary(int LibType,LayersBase *Base);

	virtual	bool	SaveBlob(QIODevice *f)	override{	return true;	}
	virtual	bool	LoadBlob(QIODevice *f)	override{	return true;	}
};

class	TreeMasterLibraryContainer : public AlgorithmLibraryContainer
{
public:
	TreeMasterLibraryContainer(LayersBase *base)
		:AlgorithmLibraryContainer(base){}

	virtual	int	GetLibType(void)				override{	return DefLibTypeTreeMaster;	}
	virtual	const char	*GetLibTypeName(void)	override{	return "TreeMaster Library";	}
	virtual	AlgorithmLibrary	*CreateNew(void)override{	return new TreeMasterLibrary(GetLibType(),GetLayersBase());	}
};

//-------------------------------------------------------------------------

class	TreeMasterThreshold : public AlgorithmThreshold
{
public:
	double		ThreShape;
	double		ThreColor;
	int			SearchDot;

	TreeMasterThreshold(TreeMasterItem *parent);

	virtual	void	CopyFrom(const AlgorithmThreshold &src)	override;
	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const override;
	virtual	bool	Save(QIODevice *f)					override;
	virtual	bool	Load(QIODevice *f)					override;
	virtual	int		GetSize(void)	const override	{	return sizeof(this);	}
};


class	TreeMasterItem : public AlgorithmItemPITemplate<TreeMasterInPage,TreeMasterBase>
{
public:
	int								TMItemID;
	AreaWithColorContainer			MatchingArea;
	FlexAreaImageListCoeffContainer	ShapeList;
	FlexArea						ShapeMask;

	int		MasterCode;
	QString MasterName;
	QString	CatName;
	bool	AlertMark;

	double	ResultE;
	double	ResultColor;
	double	ResultShape;
	int		ResultDx,ResultDy;
	bool	ResultOk;

	TreeMasterItem(void);
	~TreeMasterItem(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new TreeMasterItem();	}
	virtual	bool    Save(QIODevice *f)						override;
    virtual	bool    Load(QIODevice *f,LayersBase *LBase)	override;

	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;

	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual	ExeResult	ExecutePreProcessing	(int ExeID ,int ThreadNo,ResultInItemRoot *Res)	override;

	const	TreeMasterThreshold	*GetThresholdR(LayersBase *base=NULL)		{	return (const TreeMasterThreshold *)GetThresholdBaseReadable(base);	}
	TreeMasterThreshold			*GetThresholdW(LayersBase *base=NULL)		{	return (TreeMasterThreshold *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)	override	{	return new TreeMasterThreshold(this);	}

	virtual	void	ExecuteMove(int GlobalDx,int GlobalDy,bool AllItems=false)	override;
	void	RemoveArea(void);

	double	GetColorLength(AreaWithColor &s,int mx ,int my);
	QString	GetShapeCode(void);

	ExeResult	ExecutePreProcessingColor	(int dx ,int dy);

};


class   TreeMasterInPage : public AlgorithmInPagePITemplate<TreeMasterItem,AlgorithmBase>
{
public:
	TreeMasterInPage(AlgorithmBase *parent);
	~TreeMasterInPage(void);

	bool testLoad(QIODevice *f);
	TreeMasterItem *getItemFromMasterCode(int MasterCode);
	void copyMatchingArea(TreeMasterItem *srcItem);

	void decreaseItemID(int removedID);
	virtual	void	RemoveItem(AlgorithmItemRoot *item)				override;
	virtual	void	DeleteSelectedItems(const IntList &LayerList)	override;

	virtual	AlgorithmItemRoot		*CreateItem(int ItemClassType=0)	override
		{	
			TreeMasterItem	*a=new TreeMasterItem();	
			a->SetParent(this);
			return a;
		}
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
};


class	TreeMasterBase : public AlgorithmBase
{
public:
	QColor		ColorArea;
	QColor		ColorSelected;
	QColor		ColorActive;
	int32		TransparentLevel;
	QColor		NegColorArea;
	QColor		NegColorSelected;

	QColor		AreaColor0;
	QColor		AreaColor1;
	QColor		AreaColor2;
	QColor		AreaColor3;
	QColor		AreaColor4;
	QColor		AreaColor5;
	QColor		AreaColor6;
	QColor		AreaColor7;

	QString		MatchedNameOfResult;
	int			PickedMasterCode;
	TreeMasterItem	*PosibilityItem;

	TreeMasterBase(LayersBase *Base);

	virtual	AlgorithmInPagePI	*NewChild(AlgorithmBase *parent)	override{	return new TreeMasterInPage(parent);	}
	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)				override;
	virtual	QString	GetDataText(void)			override{	return QString("TreeMaster");				}
	virtual	QString	GetDefaultFileName(void)	override{	return QString("ConfigTreeMaster.dat");		}

	virtual ExeResult ExecutePreProcessing(int ExeID ,ResultBaseForAlgorithmRoot* Res)	override;
	
	void copyItem(int MasterSrc,int MasterDst);
	bool testLoad(QIODevice *f);

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	TreeMasterItem	*FoundTheMost(void);
};
//==================================================================================


class	CmdAddTreeMasterItemPacket : public GUIDirectMessage
{
public:
	int		TMItemID;
	QString	CatName;
	int		MasterCode;
	QString MasterName;

	CmdAddTreeMasterItemPacket(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdReqMaxTMItemIDPacket : public GUIDirectMessage
{
public:
	int		MaxTMItemID;

	CmdReqMaxTMItemIDPacket(LayersBase *base):GUIDirectMessage(base){	MaxTMItemID=0;	}
};

class	CmdAddItemAreaPacket	: public GUIDirectMessage
{
public:
	int			TMItemID;
	int			MasterCode;
	QString		CatName;
	QString		MasterName;
	FlexArea	Area;
	QColor		TreeMasterColor;
	int			Selection;
	double		ThreShape;
	double		ThreColor;
	int			SearchDot;

	CmdAddItemAreaPacket(LayersBase *base):GUIDirectMessage(base){}
};

class CmdCopyTreeMasterItemPacket : public GUIDirectMessage
{
public:
	int MasterSrc;
	int MasterDst;

	CmdCopyTreeMasterItemPacket(LayersBase *base):GUIDirectMessage(base){}
};

class CmdSetCategoryNamePacket : public GUIDirectMessage
{
public:
	QString CatName;
	int MasterCode;

	CmdSetCategoryNamePacket(LayersBase *base):GUIDirectMessage(base){}
};

class CmdRemoveItemPacket : public GUIDirectMessage
{
public:
	int MasterCode;

	CmdRemoveItemPacket(LayersBase *base):GUIDirectMessage(base){}
};
class CmdSelectItemPacket : public GUIDirectMessage
{
public:
	int MasterCode;

	CmdSelectItemPacket(LayersBase *base):GUIDirectMessage(base){}
};

class CmdFoundTheMost : public GUIDirectMessage
{
public:
	TreeMasterItem	*Item;

	CmdFoundTheMost(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdSetAlertTreeMaster : public GUIDirectMessage
{
public:
	int		TMItemID;
	int		MasterCode;
	bool	AlertMark;

	CmdSetAlertTreeMaster(LayersBase *base):GUIDirectMessage(base){}
};

class CmdSetPickedMaser : public GUIDirectMessage
{
public:
	QString	MasterName;
	bool	AlertMark;
	int		PickedMasterCode;

	CmdSetPickedMaser(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdReqTotalResult : public GUIDirectMessage
{
public:
	double	ResultE;
	double	ResultColor;
	double	ResultShape;
	bool	ResultOk;

	QString	Posibility;

	CmdReqTotalResult(LayersBase *base):GUIDirectMessage(base){}
};

#endif