/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\SavePartialImage\XSavePartialImage.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#if	!defined(XSavePartialImage_h)
#define	XSavePartialImage_h

#define	SavePartialImageVersion	1

#include <QString>
#include <QIODevice>
#include <QImage>
#include <QColor>
#include "XFlexArea.h"
#include "XMainSchemeMemory.h"
#include "XDataInLayer.h"
#include "XTypeDef.h"
#include "XAlgorithmLibrary.h"
#include "XDataModelPageItem.h"
#include "XServiceForLayers.h"

class	SavePartialImageItem;
class	SavePartialImageInLayer;
class	SavePartialImageBase;
class	FileEntryListContainer;
class   SaveImageFileListContainer;
class   CmdImageFileList;

class	SavePartialImageThreshold : public AlgorithmThreshold
{
public:

	SavePartialImageThreshold(SavePartialImageItem *parent);

	virtual	void	CopyFrom(const AlgorithmThreshold &src)	override;
	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const override;
	virtual	bool	Save(QIODevice *f)					override;
    virtual	bool	Load(QIODevice *f)					override;
    virtual	int		GetSize(void)	const override	{	return sizeof(this);	}
};

class	SavePartialImageItem : public AlgorithmItemPI
{
public:
	QString							AreaName;
	ImageBufferListContainer		MasterImages;

	SavePartialImageItem(void){}
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new SavePartialImageItem();	}
	const	SavePartialImageThreshold	*GetThresholdR(LayersBase *base=NULL){	return (const SavePartialImageThreshold *)GetThresholdBaseReadable(base);	}
	SavePartialImageThreshold			*GetThresholdW(LayersBase *base=NULL){	return (SavePartialImageThreshold *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)	override{	return new SavePartialImageThreshold(this);	}

	virtual	AlgorithmItemPI	&operator=(const AlgorithmItemRoot &src)	override;
	virtual	bool    Save(QIODevice *f)						override;
    virtual	bool    Load(QIODevice *f,LayersBase *LBase)	override;

	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
};

class   SavePartialImageInPage : public AlgorithmInPagePI
{
public:
	SavePartialImageInPage(AlgorithmBase *parent):AlgorithmInPagePI(parent){}

	virtual	AlgorithmItemRoot	*CreateItem(int ItemClassType)	override
		{	
			SavePartialImageItem	*a=new SavePartialImageItem();
			a->SetParent(this);
			return a;
		}
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
};

class	SavePartialImageBase : public AlgorithmBase
{
public:

	SavePartialImageBase(LayersBase *Base);

	virtual	AlgorithmInPagePI	*NewChild(AlgorithmBase *parent)	override{	return new SavePartialImageInPage(parent);		}
	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)				override;
	virtual	QString	GetDataText(void)			override{	return QString("SavePartialImage");				}
	virtual	QString	GetDefaultFileName(void)	override{	return QString("ConfigSavePartialImage.dat");	}
	virtual	bool	ShowPasteCreateWithShape(QByteArray &templateData,int Layer)	override;

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	void	GetSavePartialImageList(CmdImageFileList *cmd);
	bool	MakeSavePartialImageList(QString strDir, SaveImageFileListContainer &lstSaveImageFile);
	bool	NextFolder(void);
};

//==================================================================================

class	SavePartialImageDrawAttr : public AlgorithmDrawAttr
{
public:
	enum	SPI_DrawMode
	{
		_SPI_None
		,_SPI_Image
		,_SPI_Area
	};
	SPI_DrawMode	DrawMode;

	SavePartialImageDrawAttr(void):DrawMode(_SPI_None){}
	SavePartialImageDrawAttr(QColor ncol ,QColor scol ,QColor acol):AlgorithmDrawAttr(ncol,scol,acol),DrawMode(_SPI_None){}
};
//==================================================================================
class	CmdAddAreaManual : public GUIDirectMessage
{
public:
	QString		ItemName;
	FlexArea	Area;

	CmdAddAreaManual(LayersBase *Base):GUIDirectMessage(Base){}
};

class	SavePartialImageInfoContainer;

class	CmdReqSavePartialImageInfo : public GUIDirectMessage
{
public:
	SavePartialImageInfoContainer	*Info;

	CmdReqSavePartialImageInfo(LayersBase *Base):GUIDirectMessage(Base){}
};

class	CmdReqItemInfo : public GUIDirectMessage
{
public:
	int			ItemID;

	CmdReqItemInfo(LayersBase *Base):GUIDirectMessage(Base){}
};

//===================================================================================

class	SavePartialImageInfo : public NPListSaveLoad<SavePartialImageInfo>
{
public:
	int		ItemID;
	int		Cx,Cy;
	int		x1,y1,x2,y2;

	SavePartialImageInfo(void){}

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);
};

class	SavePartialImageInfoContainer : public NPListPackSaveLoad<SavePartialImageInfo>
{
public:
	SavePartialImageInfoContainer(void){}
	virtual	SavePartialImageInfo	*Create(void);
	void	SetPage(int page);
};


inline	bool	SavePartialImageInfo::Load(QIODevice *f)
{
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,Cx)==false)
		return false;
	if(::Load(f,Cy)==false)
		return false;
	if(::Load(f,x1)==false)
		return false;
	if(::Load(f,x2)==false)
		return false;
	if(::Load(f,y1)==false)
		return false;
	if(::Load(f,y2)==false)
		return false;
	return true;
}
inline	bool	SavePartialImageInfo::Save(QIODevice *f)
{
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,Cx)==false)
		return false;
	if(::Save(f,Cy)==false)
		return false;
	if(::Save(f,x1)==false)
		return false;
	if(::Save(f,x2)==false)
		return false;
	if(::Save(f,y1)==false)
		return false;
	if(::Save(f,y2)==false)
		return false;
	return true;
}
#endif