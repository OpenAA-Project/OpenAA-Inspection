/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\ImageProcessor\XImageProcessor.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#if	!defined(XIMAGEPROCESSOR_H)
#define	XIMAGEPROCESSOR_H

#include "XDataInLayer.h"
#include "XDataModelPageItem.h"
#include "XAlgorithmLibrary.h"
#include "XGrouper.h"

class	ImageProcessItem;
#define	DefLibTypeImageProcessor		23

//=====================================================================================================================

class	ImageProcessorLibrary : public AlgorithmLibrary , public ServiceForLayers
{
public:
//¶¬ƒf[ƒ^
	FilterContainer			FilterList;

	ImageProcessorLibrary(int LibType,LayersBase *Base);
	virtual	~ImageProcessorLibrary(void);

	virtual	bool	SaveBlob(QIODevice *f)	override;
	virtual	bool	LoadBlob(QIODevice *f)	override;

	ImageProcessorLibrary	&operator=(const AlgorithmLibrary &src)	override;
};

class	ImageProcessorLibraryContainer : public AlgorithmLibraryContainer
{
public:
	ImageProcessorLibraryContainer(LayersBase *base);
	virtual	~ImageProcessorLibraryContainer(void);

	virtual	int	GetLibType(void)				override{	return DefLibTypeImageProcessor;	}
	virtual	const char	*GetLibTypeName(void)	override{	return "ImageProcessor";	}
	virtual	AlgorithmLibrary	*CreateNew(void)override{	return new ImageProcessorLibrary(GetLibType(),GetLayersBase());	}
};


//=====================================================================================================================


class	ImageProcessThreshold : public AlgorithmThreshold
{
public:

	ImageProcessThreshold(ImageProcessItem *parent);

	virtual	void	CopyFrom(const AlgorithmThreshold &src)	override;
	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const override{	return true;	}
	virtual	bool	Save(QIODevice *f)					override;
    virtual	bool	Load(QIODevice *f)					override;
    virtual	int		GetSize(void)	const override	{	return sizeof(this);	}
};

class	ImageProcessItem : public AlgorithmItemPI
{
public:
	ImageProcessItem(void){}
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new ImageProcessItem();	}
	const	ImageProcessThreshold	*GetThresholdR(LayersBase *base=NULL){	return (const ImageProcessThreshold *)GetThresholdBaseReadable(base);	}
	ImageProcessThreshold			*GetThresholdW(LayersBase *base=NULL){	return (ImageProcessThreshold *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold		*CreateThresholdInstance(void)	override	{	return new ImageProcessThreshold(this);	}

	virtual	AlgorithmItemPI	&operator=(const AlgorithmItemRoot &src)	override;
	virtual	bool    Save(QIODevice *f)						override;
    virtual	bool    Load(QIODevice *f,LayersBase *LBase)	override;
	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
};

class   ImageProcessInPage : public AlgorithmInPagePI
{
public:
	FlexAreaImageListContainer	LearnPattern;

	ImageProcessInPage(AlgorithmBase *parent):AlgorithmInPagePI(parent){}

	virtual	AlgorithmItemRoot		*CreateItem(int ItemClassType=0)	override
		{	
			ImageProcessItem	*a=new ImageProcessItem();	
			a->SetParent(this);
			return a;
		}
	virtual	void	RegistArea(FlexArea &localArea,const IntList &LayerList)	override;
};

class	ImageProcessBase : public AlgorithmBase
{
public:
	FilterContainer			GData;
	ProgramImages			Program;

	ImageProcessBase(LayersBase *Base);

	virtual	AlgorithmInPagePI	*NewChild(AlgorithmBase *parent)	override{	return new ImageProcessInPage(parent);		}
	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)				override;
	virtual	QString	GetDataText(void)	override{	return QString("ImageProcess");				}
	QString	GetDefaultFileName(void)	override{	return QString("ConfigImageProcess.dat");	}
	virtual	bool	ShowPasteCreateWithShape(QByteArray &templateData,int Layer)	override{	return false;	}
	virtual	void	Initial(LayersBase *Base)	override;

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	virtual	bool	SaveOnlyBase(QIODevice *f)	override;
	virtual	bool	LoadOnlyBase(QIODevice *f)	override;
};
//==================================================================================
class	ImageProcessorPaint : public GUIDirectMessage
{
public:
	QPainter	*Pnt;
	ImageProcessorPaint(LayersBase *base):GUIDirectMessage(base){	Pnt=NULL;	}
	ImageProcessorPaint(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){	Pnt=NULL;	}
};

class	ImageProcessorAddInstance : public GUIDirectMessage
{
public:
	FilterBase	*Base;
	QString		ParamTitle;
	int			x,y;

	ImageProcessorAddInstance(LayersBase *base):GUIDirectMessage(base){}
	ImageProcessorAddInstance(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	ImageProcessorAddProgram : public GUIDirectMessage
{
public:
	QString	ProgName;
	ImageProcessorAddProgram(LayersBase *base):GUIDirectMessage(base){}
	ImageProcessorAddProgram(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	ImageProcessorEnumProgram : public GUIDirectMessage
{
public:
	QStringList	ProgNameList;
	ImageProcessorEnumProgram(LayersBase *base):GUIDirectMessage(base){}
	ImageProcessorEnumProgram(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	ImageProcessorEnumImages : public GUIDirectMessage
{
public:
	int	Row;
	QStringList	FileNameList;
	ImageProcessorEnumImages(LayersBase *base):GUIDirectMessage(base){}
	ImageProcessorEnumImages(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	ImageProcessorDelProgram : public GUIDirectMessage
{
public:
	int	Row;
	ImageProcessorDelProgram(LayersBase *base):GUIDirectMessage(base){}
	ImageProcessorDelProgram(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	ImageProcessorAddFiles : public GUIDirectMessage
{
public:
	int	ProgRow;
	QStringList	FileNames;
	ImageProcessorAddFiles(LayersBase *base):GUIDirectMessage(base){}
	ImageProcessorAddFiles(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	ImageProcessorDelFile : public GUIDirectMessage
{
public:
	int	ProgRow;
	int	FileRow;
	ImageProcessorDelFile(LayersBase *base):GUIDirectMessage(base){}
	ImageProcessorDelFile(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	ImageProcessorSelectItem: public GUIDirectMessage
{
public:
	int	x,y;
	FilterBase	*Item;
	ImageProcessorSelectItem(LayersBase *base):GUIDirectMessage(base){}
	ImageProcessorSelectItem(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	ImageProcessorDeleteItem : public GUIDirectMessage
{
public:
	FilterBase	*Item;
	ImageProcessorDeleteItem(LayersBase *base):GUIDirectMessage(base){}
	ImageProcessorDeleteItem(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	ImageProcessorMoveItem : public GUIDirectMessage
{
public:
	int	x,y;
	FilterBase	*Item;
	ImageProcessorMoveItem(LayersBase *base):GUIDirectMessage(base){}
	ImageProcessorMoveItem(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	ImageProcessorDeleteAllTargetInItem : public GUIDirectMessage
{
public:
	FilterBase	*Item;
	ImageProcessorDeleteAllTargetInItem(LayersBase *base):GUIDirectMessage(base){}
	ImageProcessorDeleteAllTargetInItem(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	ImageProcessorAddTargetFromSource : public GUIDirectMessage
{
public:
	int	x,y;
	FilterBase	*CurrentItem;
	ImageProcessorAddTargetFromSource(LayersBase *base):GUIDirectMessage(base){}
	ImageProcessorAddTargetFromSource(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	ImageProcessorGetParam : public GUIDirectMessage
{
public:
	int			ItemID;
	int			ParamCount;
	double		Param[100];
	QStringList	ParamName;
	ImageProcessorGetParam(LayersBase *base):GUIDirectMessage(base){}
	ImageProcessorGetParam(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	ImageProcessorSetParam : public GUIDirectMessage
{
public:
	int			ItemID;
	double		Param[100];
	ImageProcessorSetParam(LayersBase *base):GUIDirectMessage(base){}
	ImageProcessorSetParam(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	ImageProcessorUpperFile : public GUIDirectMessage
{
public:
	int		ProgRow;
	int		FileRow;
	ImageProcessorUpperFile(LayersBase *base):GUIDirectMessage(base){}
	ImageProcessorUpperFile(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	ImageProcessorLowerFile : public GUIDirectMessage
{
public:
	int		ProgRow;
	int		FileRow;
	ImageProcessorLowerFile(LayersBase *base):GUIDirectMessage(base){}
	ImageProcessorLowerFile(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	ImageProcessorExecuteOne : public GUIDirectMessage
{
public:
	int		ProgRow;
	ImageProcessorExecuteOne(LayersBase *base):GUIDirectMessage(base){}
	ImageProcessorExecuteOne(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	ImageProcessorExecuteAll : public GUIDirectMessage
{
public:
	ImageProcessorExecuteAll(LayersBase *base):GUIDirectMessage(base){}
	ImageProcessorExecuteAll(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	ImageProcessorGetMinMaxArea : public GUIDirectMessage
{
public:
	int	MinX,MinY;
	int	MaxX,MaxY;
	ImageProcessorGetMinMaxArea(LayersBase *base):GUIDirectMessage(base){}
	ImageProcessorGetMinMaxArea(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	ImageProcessorRegistLearnArea: public GUIDirectMessage
{
public:
	FlexArea	Area;
	FilterBase	*CurrentItem;
	ImageProcessorRegistLearnArea(LayersBase *base):GUIDirectMessage(base){}
	ImageProcessorRegistLearnArea(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	ImageProcessorPaintPanel: public GUIDirectMessage
{
public:
	QImage		*Img;
	double		ZoomRate;
	int			MovX;
	int			MovY;
	FilterBase	*Item;
	ImageProcessorPaintPanel(LayersBase *base):GUIDirectMessage(base){}
	ImageProcessorPaintPanel(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	ImageProcessorLoadDefFile: public GUIDirectMessage
{
public:
	QString	DefFileName;
	ImageProcessorLoadDefFile(LayersBase *base):GUIDirectMessage(base){}
	ImageProcessorLoadDefFile(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	ImageProcessorDelAllProgram: public GUIDirectMessage
{
public:
	ImageProcessorDelAllProgram(LayersBase *base):GUIDirectMessage(base){}
	ImageProcessorDelAllProgram(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

//===================================================================================

#endif
