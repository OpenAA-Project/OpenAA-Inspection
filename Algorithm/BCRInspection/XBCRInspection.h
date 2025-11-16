/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\BCRInspection\XBCRInspection.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#if	!defined(XBCRINSPECTION_H)
#define	XBCRINSPECTION_H


#include "XDataInLayer.h"
#include "XDataModelPageItem.h"
#include "XAlgorithmLibrary.h"
#include "XColorSpace.h"
#include "NListComp.h"
#include "XGeneralFunc.h"
#include "fftw3.h"
#include "XGeneralFunc.h"
#include "XBCRInspectionLibrary.h"

#define	BCRInspectionVersion	2
class	BCRInspectionItem;
struct	IBarcodeReader;

class	BCRGradeList : public NPListSaveLoad<BCRGradeList>
{
public:
	QString	Grade;
	double	Quality;

	BCRGradeList(void)	{	Quality=0;	}
	BCRGradeList(const BCRGradeList &src);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);

	bool	operator==(const BCRGradeList &src)	const ;
	BCRGradeList	&operator=(const BCRGradeList &src);
};

class	BCRGradeListContainer : public NPListPackSaveLoad<BCRGradeList>
{
public:
	BCRGradeListContainer(void){}
	BCRGradeListContainer(const BCRGradeListContainer &src);

	virtual	BCRGradeList	*Create(void){	return new BCRGradeList();	}

	bool	operator==(const BCRGradeListContainer &src)	const ;
	BCRGradeListContainer	&operator=(const BCRGradeListContainer &src);
};

inline	BCRGradeList::BCRGradeList(const BCRGradeList &src)
{
	Grade=src.Grade;
	Quality=src.Quality;
}
inline	BCRGradeList	&BCRGradeList::operator=(const BCRGradeList &src)
{
	Grade=src.Grade;
	Quality=src.Quality;
	return *this;
}

inline	BCRGradeListContainer::BCRGradeListContainer(const BCRGradeListContainer &src)
{
	for(BCRGradeList *L=src.GetFirst();L!=NULL;L=L->GetNext()){
		BCRGradeList	*d=new BCRGradeList(*L);
		AppendList(d);
	}
}
inline	BCRGradeListContainer	&BCRGradeListContainer::operator=(const BCRGradeListContainer &src)
{
	RemoveAll();
	for(BCRGradeList *L=src.GetFirst();L!=NULL;L=L->GetNext()){
		BCRGradeList	*d=new BCRGradeList(*L);
		AppendList(d);
	}
	return *this;
}

//-----------------------------------------------------------------------------------------------

class	BCRInspectionThreshold : public AlgorithmThreshold
{
public:
	int						CheckType;		//0:Read-2D	1:Quality Check	2:Read-1D
	double					QuilityGrade;
	BCRGradeListContainer	GradeList;
	BYTE					BarcodeOrientation;	//BarcodeOrientationEnum
	uint32					BarcodeType;		//BarcodeTypeEnum
	bool					BarcodeIsOnlyDigit;

	BCRInspectionThreshold(BCRInspectionItem *parent);

	virtual	void	CopyFrom(const AlgorithmThreshold &src)	override;
	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const override;
	virtual	bool	Save(QIODevice *f)					override;
	virtual	bool	Load(QIODevice *f)					override;
	virtual	int		GetSize(void)				const	override	{	return sizeof(this);	}

	virtual	void	MakeReportedTopics(ReportedTopicContainer &RetContainer)	const	override;
};


#define	SetIndependentItemDataCommand_OnlyOne	10
#define	SetIndependentItemDataCommand_All		12


class	BCRInspectionItem : public AlgorithmItemPI
{
public:
	AlignmentPacket2D	*AVector;
private:
	fftw_complex *FFT_in[4];
	fftw_complex *FFT_out[4];
	int			FFTLen[4];
	fftw_plan	FPlan[4];
public:
	int			BCRType;
	int			ResultMx,ResultMy;
	QString		Result;

	BCRInspectionItem(void);
	~BCRInspectionItem(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new BCRInspectionItem();	}
	const	BCRInspectionThreshold	*GetThresholdR(LayersBase *base=NULL){	return (const BCRInspectionThreshold *)GetThresholdBaseReadable(base);	}
	BCRInspectionThreshold			*GetThresholdW(LayersBase *base=NULL){	return (BCRInspectionThreshold *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)	override{	return new BCRInspectionThreshold(this);	}

	virtual ExeResult	ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual	ExeResult	ExecuteProcessing		(int ExeID ,int ThreadNo,ResultInItemRoot *Res)	override;

	bool	Calc2D(ImagePointerContainer &ImageList);
	bool	Calc1D(ImagePointerContainer &ImageList);
	virtual	QString	OutputResult(ResultPosList *p)	override;

	//virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr);
	virtual	void	DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate ,bool OnlyNG)	override;
	bool	CheckQuality(ImagePointerContainer &ImageList,ResultInItemRoot *Res);
	BCRGradeList	*CheckQuality(ImagePointerContainer &ImageList,double &MaxV);

	virtual	void	SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer
								   ,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)	override;
	void	CopyThresholdOnly(BCRInspectionItem *src);
	virtual	void	MoveForAlignment(void)	override;
private:
	void	MakeImage (QImage &Img ,double ZoomRate ,int LayerNumb,int LNo,ImagePointerContainer &ImageList);
	void	RMakeImage(QImage &Img ,double ZoomRate ,int LayerNumb,int LNo,ImagePointerContainer &ImageList);

	double	CalcFFT(int n ,BYTE Data[]);
};


class   BCRInspectionInPage : public AlgorithmInPagePI
{
public:
	BCRInspectionInPage(AlgorithmBase *parent);

	virtual	AlgorithmItemRoot		*CreateItem(int ItemClassType=0)	override
	{	
		BCRInspectionItem	*a=new BCRInspectionItem();	
		a->SetParent(this);
		return a;
	}
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
};

class	BCRInspectionBase : public AlgorithmBase
{
	QLibrary	DTKLib;
	IBarcodeReader * barReader;

public:
	QColor	ColorBCR;
	QColor	ColorSelected;
	QColor	ColorActive;
	int32	TransparentLevel;
	QColor	NegColorBCR;
	QColor	NegColorSelected;
	int32	AdotpedLayer;
	int32	IdealSize;
	bool	TryAllFilter;

	bool	FixedMode;
	int		FixedValue;
	int		FixedValueMax;
	int		FixedValueMin;
	QString	LicenseKey;

	bool	BarcodeImageInvert;
	bool	BarcodeImageDespeckle;
	bool	BarcodeImageDilate;
	bool	BarcodeImageErode;
	bool	BarcodeImageSharp;


	BCRInspectionBase(LayersBase *Base);
	~BCRInspectionBase(void);

	virtual	AlgorithmInPagePI	*NewChild(AlgorithmBase *parent)	override{	return new BCRInspectionInPage(parent);		}
	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)				override;
	virtual	QString	GetDataText(void)			override{	return QString("BCRInspection");				}
	virtual	QString	GetDefaultFileName(void)	override{	return QString("ConfigBCRInspection.dat");		}
	virtual	void	InitialAfterParamLoaded(void)	override;

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	bool	GetBCR2D(bool BarcodeIsOnlyDigit
					,const QString &FileName ,QString &Result);
	bool	GetBCR1D(BYTE BarcodeOrientation,uint32 BarcodeType,bool BarcodeIsOnlyDigit
					,const QString &FileName ,QString &Result);
	virtual	QString	GetNameByCurrentLanguage(void)	override;

	virtual	bool	GeneralDataRelease(int32 Command,void *data)			override;
	virtual	void	*GeneralDataCreate(int32 Command ,void *reqData)		override;
	virtual	bool	GeneralDataLoad(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataSave(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataReply(int32 Command,void *data)				override;
private:
	bool	GetBCR2D(QString &Result ,bool BarcodeIsOnlyDigit);
	bool	GetBCR1D(QString &Result ,bool BarcodeIsOnlyDigit);
	bool	GetBCR2DFilterVarious(QString &Result ,bool BarcodeIsOnlyDigit);
	bool	GetBCR1DFilterVarious(QString &Result ,bool BarcodeIsOnlyDigit);

};
//==================================================================================

class	BCRInspectionThresholdReq
{
public:
	int32	GlobalPage;
	int		ItemID;

	BCRInspectionThresholdReq(void);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	BCRInspectionThresholdSend
{
public:
	int32	GlobalPage;
	int		ItemID;

	int		                CheckType;		    //0:Read	1:Quality Check
	double	                QuilityGrade;
	BCRGradeListContainer	GradeList;
    BYTE					BarcodeOrientation;	//BarcodeOrientationEnum
	uint32					BarcodeType;		//BarcodeTypeEnum
    bool					BarcodeIsOnlyDigit;

	BCRInspectionThresholdSend(void);

	void	ConstructList(BCRInspectionThresholdReq *reqPacket,BCRInspectionBase *Base);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

//=================================================================================================
#define	SetIndependentItemDataCommand_OnlyOne		1
#define	SetIndependentItemDataCommand_All			2
#define	BCRInspectionHistogramListReqCommand		3
#define	BCRInspectionHistogramListSendCommand	4
#define	BCRInspectionReqThresholdReqCommand		5
#define	BCRInspectionReqThresholdSendCommand		6
#define	BCRInspectionReqTryThresholdCommand		7
#define	BCRInspectionSendTryThresholdCommand		8
#define	BCRInspectionReqChangeShiftCommand		9
#define	SetIndependentItemNameDataCommand_All		10
//===================================================================================
class	AddBCRInspectionAreaPacket : public GUIDirectMessage
{
public:
	FlexArea				Area;
	int						BCRType;
	int						CheckType;		//0:Read	1:Quality Check
	double					QuilityGrade;
	BCRGradeListContainer	GradeList;
	BYTE					BarcodeOrientation;	//BarcodeOrientationEnum
	uint32					BarcodeType;		//BarcodeTypeEnum
	bool					BarcodeIsOnlyDigit;

	AddBCRInspectionAreaPacket(LayersBase *base):GUIDirectMessage(base){}
	AddBCRInspectionAreaPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	BCRInspectionDrawAttr : public AlgorithmDrawAttr
{
public:
	QColor	NegColorBCR;
	QColor	NegColorSelected;

	BCRInspectionDrawAttr(void){}
	BCRInspectionDrawAttr(QColor ncol ,QColor scol ,QColor acol):AlgorithmDrawAttr(ncol,scol,acol){}
	BCRInspectionDrawAttr(QColor ncol ,int ntranparentLevel
						 ,QColor scol ,int stranparentLevel
						 ,QColor acol ,int atranparentLevel
						 ,QColor nncol
						 ,QColor nscol)
		:AlgorithmDrawAttr(ncol,ntranparentLevel
						,  scol,stranparentLevel
						,  acol,atranparentLevel)
	{	
		NegColorBCR	=nncol;	
		NegColorSelected=nscol;	
		NegColorBCR.setAlpha(ntranparentLevel);
		NegColorSelected.setAlpha(stranparentLevel);
	}
};

class	CmdBCRInspectionDrawPacket : public GUIDirectMessage
{
public:
	FlexArea	Area;


	CmdBCRInspectionDrawPacket(LayersBase *base)
		:GUIDirectMessage(base){}
};

//----------------------------------------------------------
class	BCRList : public NPListSaveLoad<BCRList>
{
public:
	int		LocalPage;
	int		ItemID;
	int		X1,Y1,X2,Y2;
	int		CheckType;		//0:Read	1:Quality Check
	int		BCRType;

	BCRList(void);
	BCRList(const BCRList &src);
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);

	BCRList	&operator=(const BCRList &src);
};

class	BCRContainer : public NPListPackSaveLoad<BCRList>
{
public:
	BCRContainer(void){}
	BCRContainer(const BCRContainer &src);

	virtual	BCRList	*Create(void);
	BCRContainer	&operator=(const BCRContainer &src);
};


inline	BCRList::BCRList(void)
{
	LocalPage=-1;
	ItemID=-1;
	X1=0;
	Y1=0;
	X2=0;
	Y2=0;
	CheckType	=0;
	BCRType		=-1;
}
inline	BCRList::BCRList(const BCRList &src)
{
	LocalPage	=src.LocalPage;
	ItemID		=src.ItemID	;
	X1			=src.X1		;
	Y1			=src.Y1		;
	X2			=src.X2		;
	Y2			=src.Y2		;
	CheckType	=src.CheckType;
	BCRType		=src.BCRType;
}
inline	BCRList	&BCRList::operator=(const BCRList &src)
{
	LocalPage	=src.LocalPage;
	ItemID		=src.ItemID	;
	X1			=src.X1		;
	Y1			=src.Y1		;
	X2			=src.X2		;
	Y2			=src.Y2		;
	CheckType	=src.CheckType;
	BCRType		=src.BCRType;
	return *this;
}

inline	bool	BCRList::Save(QIODevice *f)
{
	if(::Save(f,LocalPage)==false)
		return false;
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,X1)==false)
		return false;
	if(::Save(f,Y1)==false)
		return false;
	if(::Save(f,X2)==false)
		return false;
	if(::Save(f,Y2)==false)
		return false;
	if(::Save(f,CheckType)==false)
		return false;
	if(::Save(f,BCRType)==false)
		return false;
	return true;
}

inline	bool	BCRList::Load(QIODevice *f)
{
	if(::Load(f,LocalPage)==false)
		return false;
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,X1)==false)
		return false;
	if(::Load(f,Y1)==false)
		return false;
	if(::Load(f,X2)==false)
		return false;
	if(::Load(f,Y2)==false)
		return false;
	if(::Load(f,CheckType)==false)
		return false;
	if(::Load(f,BCRType)==false)
		return false;
	return true;
}

inline	BCRContainer::BCRContainer(const BCRContainer &src)
{
	for(BCRList *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		BCRList	*d=new BCRList(*s);
		AppendList(d);
	}
}
inline	BCRList	*BCRContainer::Create(void)
{	
	return new BCRList();	
}
inline	BCRContainer	&BCRContainer::operator=(const BCRContainer &src)
{
	RemoveAll();
	for(BCRList *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		BCRList	*d=new BCRList(*s);
		AppendList(d);
	}
	return *this;
}
//----------------------------------------------------------

class	CmdReqBCodeList : public GUIDirectMessage
{
public:
	BCRContainer	*Container;

	CmdReqBCodeList(LayersBase *base)
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


//==================================================================================

inline	bool	BCRGradeList::Save(QIODevice *f)
{
	if(::Save(f,Grade	)==false)	return false;
	if(::Save(f,Quality	)==false)	return false;
	return true;
}
inline	bool	BCRGradeList::Load(QIODevice *f)
{
	if(::Load(f,Grade	)==false)	return false;
	if(::Load(f,Quality	)==false)	return false;
	return true;
}
inline	bool	BCRGradeList::operator==(const BCRGradeList &src)	const 
{
	if(Grade==src.Grade && Quality==src.Quality)
		return true;
	return false;
}

inline	bool	BCRGradeListContainer::operator==(const BCRGradeListContainer &src)	const 
{
	for(BCRGradeList *a=GetFirst();a!=NULL;a=a->GetNext()){
		bool	Found=false;
		for(BCRGradeList *b=src.GetFirst();b!=NULL;b=b->GetNext()){
			if(*a==*b){
				Found=true;
				break;
			}
		}
		if(Found==false){
			return false;
		}
	}
	for(BCRGradeList *a=src.GetFirst();a!=NULL;a=a->GetNext()){
		bool	Found=false;
		for(BCRGradeList *b=GetFirst();b!=NULL;b=b->GetNext()){
			if(*a==*b){
				Found=true;
				break;
			}
		}
		if(Found==false){
			return false;
		}
	}
	return true;
}

class	CmdReqBCodeInfoByItem : public GUIDirectMessage
{
public:
	int						Page;
	int						ItemID;

	int						BCRType;
	int						CheckType;		//0:Read	1:Quality Check
	double					QuilityGrade;
	BCRGradeListContainer	GradeList;
	BYTE					BarcodeOrientation;	//BarcodeOrientationEnum
	uint32					BarcodeType;		//BarcodeTypeEnum
	bool					BarcodeIsOnlyDigit;

	CmdReqBCodeInfoByItem(LayersBase *base):GUIDirectMessage(base){}
	CmdReqBCodeInfoByItem(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdSetBCodeInfoByItem : public GUIDirectMessage
{
public:
	int						Page;
	int						ItemID;

	int						BCRType;
	int						CheckType;		//0:Read	1:Quality Check
	double					QuilityGrade;
	BCRGradeListContainer	GradeList;
	BYTE					BarcodeOrientation;	//BarcodeOrientationEnum
	uint32					BarcodeType;		//BarcodeTypeEnum
	bool					BarcodeIsOnlyDigit;

	CmdSetBCodeInfoByItem(LayersBase *base):GUIDirectMessage(base){}
	CmdSetBCodeInfoByItem(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};



class	CmdCreateBCRInspectionThreshold : public GUIDirectMessage
{
public:
	BCRInspectionItem		*Item;		//Should be deleted
	BCRInspectionThreshold	*Threshold;	//Should be deleted

	CmdCreateBCRInspectionThreshold(LayersBase *base):GUIDirectMessage(base){	Item=NULL;	Threshold=NULL;	}
	CmdCreateBCRInspectionThreshold(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
	~CmdCreateBCRInspectionThreshold(void){	delete	Item;	delete	Threshold;	}
};


class	BCRInspectionReqTryThreshold
{
public:
	int32	GlobalPage;
	int		BCRInspectionItemID;	
	BCRInspectionItem	Threshold;

	struct BCRInspectionReqTryThresholdStruct
	{
		int32	GlobalPage		;
		int		ItemID			;	
		int		                CheckType;		    //0:Read	1:Quality Check
		double	                QuilityGrade;
		BCRGradeListContainer	GradeList;
		BYTE					BarcodeOrientation;	//BarcodeOrientationEnum
		uint32					BarcodeType;		//BarcodeTypeEnum
		bool					BarcodeIsOnlyDigit;
	}Data;

	BCRInspectionReqTryThreshold(void);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f,LayersBase *LBase);
};

class	BCRInspectionSendTryThreshold : public AddedDataClass
{
public:
	ResultInItemRoot	*Result;
	QString	ResultStr;
	double	ResultQuality;

	BCRInspectionSendTryThreshold(void);
	~BCRInspectionSendTryThreshold(void);

	void	ConstructList(BCRInspectionReqTryThreshold *reqPacket,BCRInspectionBase *Base);
	void	ConstructList2(BCRInspectionReqTryThreshold *reqPacket,BCRInspectionBase *Base);
	void	Calc(BCRInspectionItem *Target
				,BCRInspectionItem *Src
				,BCRInspectionBase *Base
				,BCRInspectionReqTryThreshold *Req);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	CmdBCRInspectionSendTryThreshold : public GUIDirectMessage
{
public:
	BCRInspectionSendTryThreshold	*PTry;
	BCRInspectionItem				*Src;
	BCRInspectionItem				*Target;
	QByteArray						ThresholdDataForTarget;

	CmdBCRInspectionSendTryThreshold(LayersBase *base):GUIDirectMessage(base){	PTry=NULL;	Target=NULL;	Src=NULL;	}
	CmdBCRInspectionSendTryThreshold(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}

	~CmdBCRInspectionSendTryThreshold(void){	delete	PTry;	delete	Target;	}
};

int	GetBarcodeTypeTableCount(void);
int	GetBarcodeTypeTable(int n,QString &TypeName);
int	GetBarcodeOrientationTableCount(void);
int	GetBarcodeOrientationTable(int n,QString &TypeName);

#endif