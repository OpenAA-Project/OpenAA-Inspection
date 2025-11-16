#pragma once

#include <QColor>
#include <QByteArray>
#include "XDataInLayer.h"
#include "XDataModelPageItem.h"
#include "XAlgorithmLibrary.h"
#include "XFlexAreaImage.h"

#define	DefLibTypeAreaColorConverter	35
#define	AreaColorConverterVersion	1

class	AreaColorConverterItem;
class	RotatedXYBuffer;

class	AreaColorConverterLibrary : public AlgorithmLibrary , public ServiceForLayers
{
public:
	enum	_ConvertType{
		_CMYK			=1
		,_Monochrome	=2
	}ConvertType;

	AreaColorConverterLibrary(int LibType,LayersBase *Base);
	virtual	~AreaColorConverterLibrary(void);

	virtual	bool	SaveBlob(QIODevice *f)	override;
	virtual	bool	LoadBlob(QIODevice *f)	override;

	virtual	AreaColorConverterLibrary	&operator=(const AlgorithmLibrary &src)	override;
};


class	AreaColorConverterLibraryContainer : public AlgorithmLibraryContainer
{
public:
	AreaColorConverterLibraryContainer(LayersBase *base);
	virtual	~AreaColorConverterLibraryContainer(void);

	virtual	int	GetLibType(void)				override{	return DefLibTypeAreaColorConverter;	}
	virtual	const char	*GetLibTypeName(void)	override{	return "AreaColorConverter Library";	}
	virtual	AlgorithmLibrary	*CreateNew(void)override{	return new AreaColorConverterLibrary(GetLibType(),GetLayersBase());	}
};

//--------------------------------------------------------------------------------------------------------
class	AreaColorConverterItem;
class	AreaColorConverterThreshold : public AlgorithmThreshold
{
public:
	AreaColorConverterThreshold(AreaColorConverterItem *parent);

	virtual	void	CopyFrom(const AlgorithmThreshold &src)	override;
	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const	override;
	virtual	bool	Save(QIODevice *f)		override;
    virtual	bool	Load(QIODevice *f)		override;
    virtual	int		GetSize(void)			const	override;
};
//--------------------------------------------------------------------------------------------------------

class	AreaColorConverterItem : public AlgorithmItemPI
{
public:

	AreaColorConverterItem(void){}

	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new AreaColorConverterItem();	}
	const	AreaColorConverterThreshold	*GetThresholdR(LayersBase *base=NULL){	return (const AreaColorConverterThreshold *)GetThresholdBaseReadable(base);	}
	AreaColorConverterThreshold			*GetThresholdW(LayersBase *base=NULL){	return (AreaColorConverterThreshold *)GetThresholdBaseWritable(base);	}
	virtual	AreaColorConverterThreshold	*CreateThresholdInstance(void)	override{	return new AreaColorConverterThreshold(this);	}

	void	CopyThreshold(AreaColorConverterItem &src);
	void	CopyThresholdOnly(AreaColorConverterItem &src);
	virtual	ExeResult	ExecuteCaptured	(int ExeID,int ThreadNo,ResultInItemRoot *Res,ListPhasePageLayerPack &CapturedList)	override;

	virtual	void	SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)	override;
	virtual	bool    Save(QIODevice *f)					override{	return true;	}
    virtual	bool    Load(QIODevice *f,LayersBase *LBase)override{	return true;	}
};


//--------------------------------------------------------------------------------------------------------

class   AreaColorConverterInPage : public AlgorithmInPagePI
{
public:
	AreaColorConverterInPage(AlgorithmBase *parent):AlgorithmInPagePI(parent){}

	virtual	AlgorithmItemRoot		*CreateItem(int ItemClassType=0)	override{	return new AreaColorConverterItem();	}
	//void	AddMask(IntList &LayerList , MaskArea &mask);
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	void	UndoSetIndependentItemNameDataCommand(QIODevice *f);
};

class	AreaColorConverterBase : public AlgorithmBase
{
public:
	QColor	AreaColor;
	QColor	NegAreaColor;
	QColor	NegAreaColorSelected;
	int32	TransparentLevel;

	AreaColorConverterBase(LayersBase *Base);

	virtual	AlgorithmInPagePI	*NewChild(AlgorithmBase *parent)	override		{	return new AreaColorConverterInPage(parent);		}
	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)				override;

	virtual	QString	GetDataText(void)			override	{	return QString("AreaColorConverter");				}
	virtual	QString	GetDefaultFileName(void)	override	{	return QString("ConfigAreaColorConverter.dat");		}
	virtual	bool	ShowPasteCreateWithShape(QByteArray &templateData,int Layer)	override;

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
};
//==================================================================================
//==================================================================================
#define	SetIndependentItemDataCommand_OnlyOne			1
#define	SetIndependentItemDataCommand_All				2
#define	AreaColorConverterReqChangeShiftCommand					9
#define	SetIndependentItemNameDataCommand_All			10
//==================================================================================
//===================================================================================

class	AreaColorConverterDrawAttr : public AlgorithmDrawAttr
{
public:
	QColor	AreaColor;
	QColor	NegAreaColor;
	QColor	NegAreaColorSelected;

	AreaColorConverterDrawAttr(void){}
	AreaColorConverterDrawAttr(QColor ncol ,QColor scol ,QColor acol):AlgorithmDrawAttr(ncol,scol,acol){}
	AreaColorConverterDrawAttr(  QColor ncol ,int ntranparentLevel
						,QColor scol ,int stranparentLevel
						,QColor acol ,int atranparentLevel)
		:AlgorithmDrawAttr(ncol,ntranparentLevel
						,  scol,stranparentLevel
						,  acol,atranparentLevel)
	{	
		AreaColor			=ncol;	
		NegAreaColor		=acol;	
		NegAreaColorSelected=scol;	
		AreaColor			.setAlpha(ntranparentLevel);
		NegAreaColor		.setAlpha(atranparentLevel);
		NegAreaColorSelected.setAlpha(stranparentLevel);
	}
};

//===================================================================================

class	CmdGetAreaColorConverterLibraryListPacket : public GUIDirectMessage
{
public:
	int			LibFolderID;
	AlgorithmLibraryListContainer	AList;
	CmdGetAreaColorConverterLibraryListPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetAreaColorConverterLibraryListPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetAreaColorConverterLibraryNamePacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryListContainer	AList;
	CmdGetAreaColorConverterLibraryNamePacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetAreaColorConverterLibraryNamePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateTempAreaColorConverterLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdCreateTempAreaColorConverterLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateTempAreaColorConverterLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdInsertAreaColorConverterLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdInsertAreaColorConverterLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdInsertAreaColorConverterLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdUpdateAreaColorConverterLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdUpdateAreaColorConverterLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdUpdateAreaColorConverterLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdLoadAreaColorConverterLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdLoadAreaColorConverterLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdLoadAreaColorConverterLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdDeleteAreaColorConverterLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdDeleteAreaColorConverterLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdDeleteAreaColorConverterLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdAreaColorConverterDrawModePacket : public GUIDirectMessage
{
public:

	CmdAreaColorConverterDrawModePacket(LayersBase *base):GUIDirectMessage(base){}
	CmdAreaColorConverterDrawModePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	AreaColorConverterImagePanel;
class	CmdAreaColorConverterDrawEnd : public GUIDirectMessage
{
public:
	FlexArea	Area;
	IntList		LayerList;
	AreaColorConverterImagePanel	*ImagePanelPoint;

	CmdAreaColorConverterDrawEnd(LayersBase *base):GUIDirectMessage(base){}
	CmdAreaColorConverterDrawEnd(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdAddAreaColorConverterItemPacket: public GUIDirectMessage
{
public:
	FlexArea	Area;
	int			SelectedLibID;
	int			LocalPage;
	IntList		LayerList;

	CmdAddAreaColorConverterItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdAddAreaColorConverterItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
