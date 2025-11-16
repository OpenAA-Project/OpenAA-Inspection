/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\OCRInspection\XOCRInspection.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#if	!defined(XOCRINSPECTION_H)
#define	XOCRINSPECTION_H


#include "XDataInLayer.h"
#include "XDataModelPageItem.h"
#include "XAlgorithmLibrary.h"
#include "XColorSpace.h"
#include "NListComp.h"

class	OCRInspectionItem;

class	OCRInspectionThreshold : public AlgorithmThreshold
{
public:
	int32		AbsLR, AbsHR;
	int32		AbsLG, AbsHG;
	int32		AbsLB, AbsHB;
	int32		EnsmallDot;
	int32		EnlargeDot;
	int32		BlockWidth;
	int32		BlockHeight;
	int32		MinSize;
	int32		Mergin;
	ColorLogic	MaskingColor;
	bool		UseColorLogic;
	double		Rotation;

	int				RegNumber;
	bool			InspectMatching;
	bool			SaveIntoResult;
	bool			OKByFailingRecognition;
	QStringList		CorrectList;

	OCRInspectionThreshold(OCRInspectionItem *parent);

	virtual	void	CopyFrom(const AlgorithmThreshold &src)	override;
	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const override;
	virtual	bool	Save(QIODevice *f)					override;
	virtual	bool	Load(QIODevice *f)					override;
	virtual	int		GetSize(void)	const override	{	return sizeof(this);	}
};

class	OCRInspectionItem : public AlgorithmItemPI
{
	BYTE	**MaskingMap;
	BYTE	**TmpBuff;
	int		XByte;
	int		YLen;
public:
	AlignmentPacket2D	*AVector;
	int			Mx,My;
	QString		Result;

	OCRInspectionItem(void);
	~OCRInspectionItem(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new OCRInspectionItem();	}
	const	OCRInspectionThreshold	*GetThresholdR(LayersBase *base=NULL){	return (const OCRInspectionThreshold *)GetThresholdBaseReadable(base);	}
	OCRInspectionThreshold			*GetThresholdW(LayersBase *base=NULL){	return (OCRInspectionThreshold *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)	override{	return new OCRInspectionThreshold(this);	}

	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual	ExeResult	ExecuteProcessing		(int ExeID,int ThreadNo,ResultInItemRoot *Res)	override;

	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
	virtual	void	DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)	override;

	bool	Calc(ImagePointerContainer &ImageList);
	bool	Match(QString &_Result);
	virtual	QString	OutputResult(ResultPosList *p)	override;
private:
	void	MakeImage (int mx,int my,ImagePointerContainer &ImageList);
};

class   OCRInspectionInPage : public AlgorithmInPagePI
{
public:
	OCRInspectionInPage(AlgorithmBase *parent):AlgorithmInPagePI(parent){}

	virtual	AlgorithmItemRoot		*CreateItem(int ItemClassType=0)	override
	{	
		OCRInspectionItem	*a=new OCRInspectionItem();	
		a->SetParent(this);
		return a;
	}
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
};

class	OCRInspectionBase : public AlgorithmBase
{
public:
	QColor	ColorOCR;
	QColor	ColorSelected;
	QColor	ColorActive;
	int32	TransparentLevel;
	QColor	NegColorOCR;
	QColor	NegColorSelected;
	int32	AdotpedLayer;

	OCRInspectionBase(LayersBase *Base);
	virtual	~OCRInspectionBase(void);

	virtual	AlgorithmInPagePI	*NewChild(AlgorithmBase *parent)	override{	return new OCRInspectionInPage(parent);		}
	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)				override;
	virtual	QString	GetDataText(void)			override{	return QString("OCRInspection");				}
	virtual	QString	GetDefaultFileName(void)	override{	return QString("ConfigOCRInspection.dat");		}
	virtual	void	InitialAfterParamLoaded(void)	override;

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	bool	GetOCR(const QString &FileName ,QString &Result);

private:

};
//==================================================================================
//===================================================================================
class	AddOCRInspectionAreaPacket : public GUIDirectMessage
{
public:
	int32		AbsLR, AbsHR;
	int32		AbsLG, AbsHG;
	int32		AbsLB, AbsHB;
	int32		EnsmallDot;
	int32		EnlargeDot;
	int32		BlockWidth;
	int32		BlockHeight;
	int32		MinSize;
	int32		Mergin;
	ColorLogic	MaskingColor;
	bool		UseColorLogic;
	double		Rotation;

	FlexArea		Area;
	QString			ItemName;
	int				RegNumber;
	bool			InspectMatching;
	bool			SaveIntoResult;
	bool			OKByFailingRecognition;
	QStringList		CorrectList;

	AddOCRInspectionAreaPacket(LayersBase *base):GUIDirectMessage(base){}
	AddOCRInspectionAreaPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	UpdateOCRInspectionAreaPacket : public GUIDirectMessage
{
public:
	int32		AbsLR, AbsHR;
	int32		AbsLG, AbsHG;
	int32		AbsLB, AbsHB;
	int32		EnsmallDot;
	int32		EnlargeDot;
	int32		BlockWidth;
	int32		BlockHeight;
	int32		MinSize;
	int32		Mergin;
	ColorLogic	MaskingColor;
	bool		UseColorLogic;
	double		Rotation;

	int				ItemID;
	QString			ItemName;
	int				RegNumber;
	bool			InspectMatching;
	bool			SaveIntoResult;
	bool			OKByFailingRecognition;
	QStringList		CorrectList;

	UpdateOCRInspectionAreaPacket(LayersBase *base):GUIDirectMessage(base){}
	UpdateOCRInspectionAreaPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	DeleteOCRInspectionAreaPacket : public GUIDirectMessage
{
public:
	int				ItemID;

	DeleteOCRInspectionAreaPacket(LayersBase *base):GUIDirectMessage(base){}
	DeleteOCRInspectionAreaPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	ReqOCRItemPacket : public GUIDirectMessage
{
public:
	int				ItemID;
	FlexArea		Area;

	ReqOCRItemPacket(LayersBase *base):GUIDirectMessage(base){}
	ReqOCRItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdReqOCRTest : public GUIDirectMessage
{
public:
	int				ItemID;
	bool			Mastered;

	QString			Result;
	bool			Matched;

	CmdReqOCRTest(LayersBase *base):GUIDirectMessage(base){}
	CmdReqOCRTest(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	OCRInspectionDrawAttr : public AlgorithmDrawAttr
{
public:
	QColor	NegColorOCR;
	QColor	NegColorSelected;

	OCRInspectionDrawAttr(void){}
	OCRInspectionDrawAttr(QColor ncol ,QColor scol ,QColor acol):AlgorithmDrawAttr(ncol,scol,acol){}
	OCRInspectionDrawAttr( QColor ncol ,int ntranparentLevel
					,QColor scol ,int stranparentLevel
					,QColor acol ,int atranparentLevel
					,QColor nncol
					,QColor nscol)
		:AlgorithmDrawAttr(ncol,ntranparentLevel
						,  scol,stranparentLevel
						,  acol,atranparentLevel)
	{	
		NegColorOCR	=nncol;	
		NegColorSelected=nscol;	
		NegColorOCR.setAlpha(ntranparentLevel);
		NegColorSelected.setAlpha(stranparentLevel);
	}
};

class	CmdOCRInspectionDrawPacket : public GUIDirectMessage
{
public:
	FlexArea	Area;

	CmdOCRInspectionDrawPacket(LayersBase *base)
		:GUIDirectMessage(base){}
};

//----------------------------------------------------------
class	OCRList : public NPListSaveLoad<OCRList>
{
public:
	int			GlobalPage;
	int			ItemID;
	QString		ItemName;

	int32		AbsLR, AbsHR;
	int32		AbsLG, AbsHG;
	int32		AbsLB, AbsHB;
	int32		EnsmallDot;
	int32		EnlargeDot;
	int32		BlockWidth;
	int32		BlockHeight;
	int32		MinSize;
	int32		Mergin;
	ColorLogic	MaskingColor;
	bool		UseColorLogic;
	double		Rotation;

	int			RegNumber;
	bool		InspectMatching;
	bool		SaveIntoResult;
	bool		OKByFailingRecognition;
	QStringList	CorrectList;
	int			x1,y1,x2,y2;

	OCRList(void);
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

class	OCRContainer : public NPListPackSaveLoad<OCRList>
{
public:
	OCRContainer(void){}

	virtual	OCRList	*Create(void);
};


inline	OCRList::OCRList(void)
{
	GlobalPage	=-1;
	ItemID=-1;

	AbsLR=AbsHR=0;
	AbsLG=AbsHG=0;
	AbsLB=AbsHB=0;

	EnlargeDot	=0;
	EnsmallDot	=0;
	MinSize		=0;

	BlockWidth=BlockHeight	=100;
	Mergin					=0;
	UseColorLogic			=false;
	Rotation				=0;
}
inline	bool	OCRList::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,ItemName)==false)
		return false;

	if(::Save(f,AbsLR)==false)
		return false;
	if(::Save(f,AbsHR)==false)
		return false;
	if(::Save(f,AbsLG)==false)
		return false;
	if(::Save(f,AbsHG)==false)
		return false;
	if(::Save(f,AbsLB)==false)
		return false;
	if(::Save(f,AbsHB)==false)
		return false;
	if(::Save(f,EnlargeDot)==false)
		return false;
	if(::Save(f,EnsmallDot)==false)
		return false;
	if(::Save(f,BlockWidth)==false)
		return false;
	if(::Save(f,BlockHeight)==false)
		return false;

	if(::Save(f,Mergin)==false)
		return false;
	if(MaskingColor.Save(f)==false)
		return false;
	if(::Save(f,MinSize)==false)
		return false;
	if(::Save(f,UseColorLogic)==false)
		return false;
	if(::Save(f,Rotation)==false)
		return false;

	if(::Save(f,RegNumber)==false)
		return false;
	if(::Save(f,InspectMatching)==false)
		return false;
	if(::Save(f,SaveIntoResult)==false)
		return false;
	if(::Save(f,OKByFailingRecognition)==false)
		return false;
	if(::Save(f,CorrectList)==false)
		return false;

	if(::Save(f,x1)==false)
		return false;
	if(::Save(f,y1)==false)
		return false;
	if(::Save(f,x2)==false)
		return false;
	if(::Save(f,y2)==false)
		return false;

	return true;
}

inline	bool	OCRList::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,ItemName)==false)
		return false;

	if(::Load(f,AbsLR)==false)
		return false;
	if(::Load(f,AbsHR)==false)
		return false;
	if(::Load(f,AbsLG)==false)
		return false;
	if(::Load(f,AbsHG)==false)
		return false;
	if(::Load(f,AbsLB)==false)
		return false;
	if(::Load(f,AbsHB)==false)
		return false;
	if(::Load(f,EnlargeDot)==false)
		return false;
	if(::Load(f,EnsmallDot)==false)
		return false;
	if(::Load(f,BlockWidth)==false)
		return false;
	if(::Load(f,BlockHeight)==false)
		return false;

	if(::Load(f,Mergin)==false)
		return false;
	if(MaskingColor.Load(f)==false)
		return false;
	if(::Load(f,MinSize)==false)
		return false;
	if(::Load(f,UseColorLogic)==false)
		return false;
	if(::Load(f,Rotation)==false)
		return false;

	if(::Load(f,RegNumber)==false)
		return false;
	if(::Load(f,InspectMatching)==false)
		return false;
	if(::Load(f,SaveIntoResult)==false)
		return false;
	if(::Load(f,OKByFailingRecognition)==false)
		return false;
	if(::Load(f,CorrectList)==false)
		return false;

	if(::Load(f,x1)==false)
		return false;
	if(::Load(f,y1)==false)
		return false;
	if(::Load(f,x2)==false)
		return false;
	if(::Load(f,y2)==false)
		return false;

	return true;
}

inline	OCRList	*OCRContainer::Create(void)
{	
	return new OCRList;	
}
//----------------------------------------------------------

class	CmdReqOCRList : public GUIDirectMessage
{
public:
	OCRContainer	*Container;

	CmdReqOCRList(LayersBase *base)
		:GUIDirectMessage(base){}
};

class	CmdReqBCodeTest : public GUIDirectMessage
{
public:
	int		ItemID;
	bool	Mastered;
	QString	Result;

	CmdReqBCodeTest(LayersBase *base)
		:GUIDirectMessage(base){}
};

class	CmdReqBCodeResults : public GUIDirectMessage
{
public:
	QStringList	ResultBarcode;

	CmdReqBCodeResults(LayersBase *base)
		:GUIDirectMessage(base){}
};

class	CmdSetBCodeResults: public GUIDirectMessage
{
public:
	QString		ResultBarcode;
	bool		OK;

	CmdSetBCodeResults(LayersBase *base)
		:GUIDirectMessage(base){	OK=false;	}
};

#endif