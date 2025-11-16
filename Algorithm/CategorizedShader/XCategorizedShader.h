/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\XCategorizedShader\XCategorizedShader.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#if	!defined(XCategorizedShader_H)
#define	XCategorizedShader_H


#include "XDataInLayer.h"
#include "XDataModelPageItem.h"
#include "XAlgorithmLibrary.h"
#include "XDirectComm.h"
#include "XColorSpace.h"
//#include "XCategorizedShaderCommon.h"
#include "XStandardCommand.h"

class	CategorizedShaderItem;

#define	CategorizedShaderVersion		1
#define	DefLibTypeCategorizedShader		26

class	CategorizedShaderLibrary : public AlgorithmLibrary , public ServiceForLayers
{
public:

	CategorizedShaderLibrary(int LibType,LayersBase *Base);

	virtual	bool	SaveBlob(QIODevice *f)	override;
	virtual	bool	LoadBlob(QIODevice *f)	override;
};

class	CategorizedShaderLibraryContainer : public AlgorithmLibraryContainer
{
public:
	CategorizedShaderLibraryContainer(LayersBase *base)
		:AlgorithmLibraryContainer(base){}

	virtual	int	GetLibType(void)				override{	return DefLibTypeCategorizedShader;	}
	virtual	const char	*GetLibTypeName(void)	override{	return "CategorizedShader Library";	}
	virtual	AlgorithmLibrary	*CreateNew(void)override{	return new CategorizedShaderLibrary(GetLibType(),GetLayersBase());	}
};

//-------------------------------------------------------------------------

class	CategorizedShaderThreshold : public AlgorithmThreshold
{
public:
	double	Strength;	//0 - 1.0

	CategorizedShaderThreshold(CategorizedShaderItem *parent);
	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const override;
	virtual	bool	Save(QIODevice *f)					override;
	virtual	bool	Load(QIODevice *f)					override;
	virtual	int		GetSize(void)	const override	{	return sizeof(this);	}
};

class	CategorizedShaderItem : public AlgorithmItemPI
{
public:

	CategorizedShaderItem(void){}
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new CategorizedShaderItem();	}
	const	CategorizedShaderThreshold	*GetThresholdR(LayersBase *base=NULL){	return (const CategorizedShaderThreshold *)GetThresholdBaseReadable(base);	}
	CategorizedShaderThreshold			*GetThresholdW(LayersBase *base=NULL){	return (CategorizedShaderThreshold *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)	override	{	return new CategorizedShaderThreshold(this);	}
};


class   CategorizedShaderInPage : public AlgorithmInPagePI
{
	BYTE	**UncoveredMap;
	int		XByte;
	int		YLen;
public:
	CategorizedShaderInPage(AlgorithmBase *parent);
	~CategorizedShaderInPage(void);

	virtual	AlgorithmItemRoot		*CreateItem(int ItemClassType=0)	override
		{	
			CategorizedShaderItem	*a=new CategorizedShaderItem();
			a->SetParent(this);
			return a;
		}
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,ResultInPageRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual	ExeResult	ExecutePreProcessing	(int ExeID ,ResultInPageRoot *Res)	override;
};


class	CategorizedShaderBase : public AlgorithmBase
{
public:
	QColor	ColorItem;
	QColor	ColorSelected;
	QColor	ColorActive;
	int32	TransparentLevel;
	QColor	NegColorItem;
	QColor	NegColorSelected;
	double	DefaultStrength;
	int		MeshSize;

	CategorizedShaderBase(LayersBase *Base);

	virtual	AlgorithmInPagePI	*NewChild(AlgorithmBase *parent)	override{	return new CategorizedShaderInPage(parent);		}
	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)				override;
	virtual	QString	GetDataText(void)			override{	return QString("CategorizedShader");				}
	virtual	QString	GetDefaultFileName(void)	override{	return QString("ConfigCategorizedShader.dat");		}

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
};
//==================================================================================
class	CmdGetCategorizedShaderLibraryListPacket : public GUIDirectMessage
{
public:
	int			LibFolderID;
	AlgorithmLibraryListContainer	AList;
	CmdGetCategorizedShaderLibraryListPacket(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdGetCategorizedShaderLibraryNamePacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryListContainer	AList;
	CmdGetCategorizedShaderLibraryNamePacket(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdCreateTempCategorizedShaderLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdCreateTempCategorizedShaderLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdClearCategorizedShaderLibraryPacket: public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdClearCategorizedShaderLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
};
class	CmdInsertCategorizedShaderLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdInsertCategorizedShaderLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdUpdateCategorizedShaderLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdUpdateCategorizedShaderLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdLoadCategorizedShaderLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	bool				Success;
	CmdLoadCategorizedShaderLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdDeleteCategorizedShaderLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdDeleteCategorizedShaderLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdCreateTempCategorizedShaderItemPacket : public GUIDirectMessage
{
public:
	CategorizedShaderItem	*Point;
	CmdCreateTempCategorizedShaderItemPacket(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdCreateByteArrayFromCategorizedShaderItemPacket : public GUIDirectMessage
{
public:
	CategorizedShaderItem	*Point;
	QByteArray	Buff;
	CmdCreateByteArrayFromCategorizedShaderItemPacket(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdAddByteCategorizedShaderItemPacket : public GUIDirectMessage
{
public:
	QByteArray	Buff;
	FlexArea	Area;
	int			LocalPage;
	CmdAddByteCategorizedShaderItemPacket(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdLoadCategorizedShaderItemPacketFromByteArray : public GUIDirectMessage
{
public:
	CategorizedShaderItem	*BItemPoint;
	QByteArray	Buff;
	CmdLoadCategorizedShaderItemPacketFromByteArray(LayersBase *base):GUIDirectMessage(base){}
};
class	CmdModifySelectedCategorizedShaderFromByteArray : public GUIDirectMessage
{
public:
	QByteArray	Buff;
	int			LocalPage;
	CmdModifySelectedCategorizedShaderFromByteArray(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdGetOneSelectedItem : public GUIDirectMessage
{
public:
	QByteArray	Buff;
	bool		ExistSelected;
	CmdGetOneSelectedItem(LayersBase *base):GUIDirectMessage(base){}
};


/*
class	CmdAreaInfoListPacket: public GUIDirectMessage
{
public:
	int		LocalPage;
	NPListPack<AreaInfoList>	*AreaInfos;
	CmdAreaInfoListPacket(LayersBase *base):GUIDirectMessage(base){}
};
*/

class	CmdGetCategorizedShaderFromList: public GUIDirectMessage
{
public:
	ListLayerAndID	CurrentItem;
	int				LocalPage;
	CategorizedShaderItem	*CategorizedShaderInfoOnMouse;

	CmdGetCategorizedShaderFromList(LayersBase *base):GUIDirectMessage(base){}
};
class	CmdCreateCategorizedShaderItem: public GUIDirectMessage
{
public:
	CategorizedShaderItem	*Area;

	CmdCreateCategorizedShaderItem(LayersBase *base):GUIDirectMessage(base){	Area=NULL;	}
};

#endif