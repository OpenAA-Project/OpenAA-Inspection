/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\XAutoClassify\XAutoClassify.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#if	!defined(XAUTOCLASSIFY_H)
#define	XAUTOCLASSIFY_H


#include "XDataInLayer.h"
#include "XDataModelPageItem.h"
#include "XAlgorithmLibrary.h"
#include "XDirectComm.h"
#include "XColorSpace.h"
#include "XAutoClassifyCommon.h"
#include "XStandardCommand.h"

class	AutoClassifyItem;

#define	AutoClassifyVersion		1
#define	DefLibTypeAutoClassify			25

class	AutoClassifyLibrary : public AlgorithmLibrary , public ServiceForLayers
{
public:
	RGBStock	TeacherColor;

    int32		MinAreaSize;
    int32		MaxAreaSize;
    int32		MinAreaDots;
    int32		MaxAreaDots;
	int32		LimitAreaSize;

	WORD		NoiseSize;
    WORD		SpaceToOutline;
	WORD		Priority;

	enum		AlgorithmMethod{
				_Bayze		=1
				,_SVM		=2
	}AMethod;

public:

	AutoClassifyLibrary(int LibType,LayersBase *Base);

	virtual	bool	SaveBlob(QIODevice *f)	override;
	virtual	bool	LoadBlob(QIODevice *f)	override;
};

class	AutoClassifyLibraryContainer : public AlgorithmLibraryContainer
{
public:
	AutoClassifyLibraryContainer(LayersBase *base)
		:AlgorithmLibraryContainer(base){}

	virtual	int	GetLibType(void)				override{	return DefLibTypeAutoClassify;	}
	virtual	const char	*GetLibTypeName(void)	override{	return "AutoClassify Library";	}
	virtual	AlgorithmLibrary	*CreateNew(void)override{	return new AutoClassifyLibrary(GetLibType(),GetLayersBase());	}
};

//-------------------------------------------------------------------------

class	AutoClassifyThreshold : public AlgorithmThreshold
{
public:

	AutoClassifyThreshold(AutoClassifyItem *parent);

	virtual	void	CopyFrom(const AlgorithmThreshold &src)	override{}
	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const override{	return true;	}
	virtual	bool	Save(QIODevice *f)					override{	return true;	}
	virtual	bool	Load(QIODevice *f)					override{	return true;	}
	virtual	int		GetSize(void)	const override	{	return sizeof(this);	}
};

class	AutoClassifyItem : public AlgorithmItemPI
{
public:

	AutoClassifyItem(void){}
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new AutoClassifyItem();	}
	const	AutoClassifyThreshold	*GetThresholdR(LayersBase *base=NULL)	{	return (const AutoClassifyThreshold *)GetThresholdBaseReadable(base);	}
	AutoClassifyThreshold			*GetThresholdW(LayersBase *base=NULL)	{	return (AutoClassifyThreshold *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)	override	{	return new AutoClassifyThreshold(this);	}
};


class   AutoClassifyInPage : public AlgorithmInPagePI
{
	BYTE	*ColorTable;
public:
	AutoClassifyInPage(AlgorithmBase *parent);
	~AutoClassifyInPage(void);

	virtual	AlgorithmItemRoot		*CreateItem(int ItemClassType=0)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	void	SetColorIndex(int r ,int g ,int b ,int code);
	int		GetColorIndex(int r ,int g ,int b);

	void	PickupTest(AutoClassifyLibrary &LibData);
	void	GenerateAreas(AutoClassifyLibrary *LibDim[],int LibDimNumb);
};

inline	AlgorithmItemRoot		*AutoClassifyInPage::CreateItem(int ItemClassType)
{	
	AutoClassifyItem	*a=new AutoClassifyItem();	
	a->SetParent(this);
	return a;
}

inline	void	AutoClassifyInPage::SetColorIndex(int r ,int g ,int b ,int code)
{
	ColorTable[(r<<16)+(g<<8)+b]=(BYTE)code;
}
inline	int		AutoClassifyInPage::GetColorIndex(int r ,int g ,int b)
{
	return ColorTable[(r<<16)+(g<<8)+b];
}



class	AutoClassifyBase : public AlgorithmBase
{
public:
	QColor	ColorMask;
	QColor	ColorSelected;
	QColor	ColorActive;
	QColor	PickupColor;
	int32	TransparentLevel;
	QColor	NegColorMask;
	QColor	NegColorSelected;
	QColor		AreaColor0;
	QColor		AreaColor1;
	QColor		AreaColor2;
	QColor		AreaColor3;
	QColor		AreaColor4;
	QColor		AreaColor5;
	QColor		AreaColor6;
	QColor		AreaColor7;

	AutoClassifyBase(LayersBase *Base);

	virtual	AlgorithmInPagePI	*NewChild(AlgorithmBase *parent)	override{	return new AutoClassifyInPage(parent);		}
	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)				override;
	virtual	QString	GetDataText(void)			override{	return QString("AutoClassify");				}
	virtual	QString	GetDefaultFileName(void)	override{	return QString("ConfigAutoClassify.dat");	}

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
};
//==================================================================================
class	CmdGetAutoClassifyLibraryListPacket : public GUIDirectMessage
{
public:
	int			LibFolderID;
	AlgorithmLibraryListContainer	AList;
	CmdGetAutoClassifyLibraryListPacket(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdGetAutoClassifyLibraryNamePacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryListContainer	AList;
	CmdGetAutoClassifyLibraryNamePacket(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdCreateTempAutoClassifyLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdCreateTempAutoClassifyLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdClearAutoClassifyLibraryPacket: public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdClearAutoClassifyLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
};
class	CmdInsertAutoClassifyLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdInsertAutoClassifyLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdUpdateAutoClassifyLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdUpdateAutoClassifyLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdLoadAutoClassifyLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	bool				Success;
	CmdLoadAutoClassifyLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdDeleteAutoClassifyLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdDeleteAutoClassifyLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdPickupTestAutoClassifyPacket : public GUIDirectMessage
{
public:
	//AutoClassifyLibrary	*LibPoint;
	AlgorithmLibraryLevelContainer	*LibPoint;
	IntList			LayerList;
	int				Page;

	CmdPickupTestAutoClassifyPacket(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdGenerateAutoClassifyPacket : public GUIDirectMessage
{
public:
	IntList		LibList;
	int			Page;
	CmdGenerateAutoClassifyPacket(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdCreateTempAutoClassifyItemPacket : public GUIDirectMessage
{
public:
	AutoClassifyItem	*Point;
	CmdCreateTempAutoClassifyItemPacket(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdCreateByteArrayFromAutoClassifyItemPacket : public GUIDirectMessage
{
public:
	AutoClassifyItem	*Point;
	QByteArray	Buff;
	CmdCreateByteArrayFromAutoClassifyItemPacket(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdAddByteAutoClassifyItemPacket : public GUIDirectMessage
{
public:
	QByteArray	Buff;
	FlexArea	Area;
	int			LocalPage;
	CmdAddByteAutoClassifyItemPacket(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdLoadAutoClassifyItemPacketFromByteArray : public GUIDirectMessage
{
public:
	AutoClassifyItem	*BItemPoint;
	QByteArray	Buff;
	CmdLoadAutoClassifyItemPacketFromByteArray(LayersBase *base):GUIDirectMessage(base){}
};
class	CmdModifySelectedAutoClassifyFromByteArray : public GUIDirectMessage
{
public:
	QByteArray	Buff;
	int			LocalPage;
	CmdModifySelectedAutoClassifyFromByteArray(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdGetOneSelectedItem : public GUIDirectMessage
{
public:
	QByteArray	Buff;
	bool		ExistSelected;
	CmdGetOneSelectedItem(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdClearTestAutoClassifyPacket: public GUIDirectMessage
{
public:
	CmdClearTestAutoClassifyPacket(LayersBase *base):GUIDirectMessage(base){}
};



class	CmdAreaInfoListPacket: public GUIDirectMessage
{
public:
	int		LocalPage;
	NPListPack<AreaInfoList>	*AreaInfos;

	CmdAreaInfoListPacket(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdGetAutoClassifyFromList: public GUIDirectMessage
{
public:
	ListLayerAndID	CurrentItem;
	int				LocalPage;
	AutoClassifyItem	*AutoClassifyInfoOnMouse;

	CmdGetAutoClassifyFromList(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdCreateAutoClassifyItem: public GUIDirectMessage
{
public:
	AutoClassifyItem	*Area;

	CmdCreateAutoClassifyItem(LayersBase *base):GUIDirectMessage(base){	Area=NULL;	}
};

#endif
