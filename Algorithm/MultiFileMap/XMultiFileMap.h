#if	!defined(XMultiFileMap_H)
#define	XMultiFileMap_H

#include "XDataInLayer.h"
#include "XDataModelPageItem.h"
#include "XAlgorithmLibrary.h"
#include "XDirectComm.h"
#include "XAlgorithmLibrary.h"
#include "NListComp.h"

#define	MultiFileMapVersion			1
#define	DefLibTypeMultiFileMap		43
class	MultiFileMapItem;



class MultiFileMapLibrary : public AlgorithmLibrary , public ServiceForLayers
{
public:
	int	XNumb;
	int	YNumb;


	MultiFileMapLibrary(int LibType,LayersBase *Base);
	virtual	~MultiFileMapLibrary(void);

	virtual	bool	SaveBlob(QIODevice *f)	override;
	virtual	bool	LoadBlob(QIODevice *f)	override;

	virtual	MultiFileMapLibrary	&operator=(const AlgorithmLibrary &src)	override;
};

class	MultiFileMapLibraryContainer : public AlgorithmLibraryContainer
{
public:
	MultiFileMapLibraryContainer(LayersBase *base):AlgorithmLibraryContainer(base){}
	virtual	~MultiFileMapLibraryContainer(void){}

	virtual	int	GetLibType(void)				override{	return DefLibTypeMultiFileMap;	}
	virtual	const char	*GetLibTypeName(void)	override{	return "MultiFileMap Library";	}
	virtual	AlgorithmLibrary	*CreateNew(void)override{	return new MultiFileMapLibrary(GetLibType(),GetLayersBase());	}
};



//=========================================================================================================

class	MultiFileMapThreshold : public AlgorithmThreshold
{
public:

	MultiFileMapThreshold(MultiFileMapItem *parent);

	virtual	void	CopyFrom(const AlgorithmThreshold &src)	override;
	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const override{	return true;	}
	virtual	bool	Save(QIODevice *f)					override;
    virtual	bool	Load(QIODevice *f)					override;
    virtual	int		GetSize(void)	const override	{	return sizeof(this);	}
};

class	MultiFileMapItem : public AlgorithmItemPI
{
public:
	QString	FileName;
	int32	PosX;
	int32	PosY;

	MultiFileMapItem(void){}
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new MultiFileMapItem();	}
	const	MultiFileMapThreshold	*GetThresholdR(LayersBase *base=NULL){	return (const MultiFileMapThreshold *)GetThresholdBaseReadable(base);	}
	MultiFileMapThreshold			*GetThresholdW(LayersBase *base=NULL){	return (MultiFileMapThreshold *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)	override{	return new MultiFileMapThreshold(this);	}

	virtual	AlgorithmItemPI	&operator=(const AlgorithmItemRoot &src)	override;
	virtual	bool    Save(QIODevice *f)						override;
    virtual	bool    Load(QIODevice *f,LayersBase *LBase)	override;

	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
};


class   MultiFileMapInPage : public AlgorithmInPagePI
{
public:
	MultiFileMapInPage(AlgorithmBase *parent):AlgorithmInPagePI(parent){}

	virtual	AlgorithmItemRoot		*CreateItem(int ItemClassType=0)	override{	return new MultiFileMapItem();	}
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
};

class	MultiFileMapBase : public AlgorithmBase
{
public:
	QColor	ColorArea;
	QColor	ColorSelected;
	QColor	ColorActive;
	int32	TransparentLevel;
	QColor	NegColorArea;
	QColor	NegColorSelected;
	QString	SourcePath;

	MultiFileMapBase(LayersBase *Base);

	virtual	AlgorithmInPagePI	*NewChild(AlgorithmBase *parent)	override{	return new MultiFileMapInPage(parent);		}
	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)				override;
	virtual	QString	GetDataText(void)			override{	return QString("MultiFileMap");				}
	virtual	QString	GetDefaultFileName(void)	override{	return QString("ConfigMultiFileMap.dat");	}
	virtual	bool	ShowPasteCreateWithShape(QByteArray &templateData,int Layer)	override;

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
};
//==================================================================================
//===================================================================================
class	AddMultiFileMapAreaPacket : public GUIDirectMessage
{
public:
	QString		FileName;
	int			PosX;
	int			PosY;
	FlexArea	Area;

	AddMultiFileMapAreaPacket(LayersBase *base):GUIDirectMessage(base){}
	AddMultiFileMapAreaPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	ClearMultiFileMapAllPacket : public GUIDirectMessage
{
public:

	ClearMultiFileMapAllPacket(LayersBase *base):GUIDirectMessage(base){}
	ClearMultiFileMapAllPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	MultiFileMapDrawAttr : public AlgorithmDrawAttr
{
public:
	QColor	NegColorMask;
	QColor	NegColorSelected;


	MultiFileMapDrawAttr(void){}
	MultiFileMapDrawAttr(QColor ncol ,QColor scol ,QColor acol):AlgorithmDrawAttr(ncol,scol,acol){}
	MultiFileMapDrawAttr( QColor ncol ,int ntranparentLevel
					,QColor scol ,int stranparentLevel
					,QColor acol ,int atranparentLevel
					,QColor nncol
					,QColor nscol)
		:AlgorithmDrawAttr(ncol,ntranparentLevel
						,  scol,stranparentLevel
						,  acol,atranparentLevel)
	{	
		NegColorMask	=nncol;	
		NegColorSelected=nscol;	
		NegColorMask.setAlpha(ntranparentLevel);
		NegColorSelected.setAlpha(stranparentLevel);
	}
};

class	CmdMultiFileMapDrawPacket : public GUIDirectMessage
{
public:
	int		movx;
	int		movy;
	double	ZoomRate;
	QImage	*Canvas;
	IntList	LayerList;
//	CmdBlockDrawModePacket::DrawMode	Mode;

	CmdMultiFileMapDrawPacket(LayersBase *base,int _movx ,int _movy ,double zoomrate
		,QImage *canvas ,IntList &layerList)
		:GUIDirectMessage(base)
		,movx(_movx),movy(_movy),ZoomRate(zoomrate),Canvas(canvas),LayerList(layerList){}
};

class	CmdReqMultiFileMapInfo : public GUIDirectMessage
{
public:
	int GlobalX ,GlobalY;
	int	PosX,PosY;
	QString	FileName;

	CmdReqMultiFileMapInfo(LayersBase *base):GUIDirectMessage(base)			{	PosX=PosY=-1;	}
	CmdReqMultiFileMapInfo(GUICmdPacketBase *gbase):GUIDirectMessage(gbase)	{	PosX=PosY=-1;	}
};

#endif