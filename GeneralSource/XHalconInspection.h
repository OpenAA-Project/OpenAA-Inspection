/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XHalconInspection.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef XHalconInspection
#define XHalconInspection

#define	HalconInspectionVersion	1

#include "XFlexArea.h"
#include "XMainSchemeMemory.h"
#include "XDataInLayer.h"
#include "XTypeDef.h"
#include "XAlgorithmLibrary.h"
#include "XDataModelPageItem.h"
#include "XServiceForLayers.h"
#include "XHalcon.h"

class	HalconInspectionItem;
#define	HalconInspectionLibType		12

#define	ResultHalconInspectionOnItemType	7

enum	ArgType{
			 Region=0
			,Tuple
};

//extern QString	HalconFuncString[100];
//extern int		FuncListCount;

class HalconSampleList;

class	HalconFuncListBase : public NPList<HalconFuncListBase>
{
public:
	HalconFuncListBase(XHalcon *XHalIns,HalconSampleList *List)	{	HalIns=XHalIns;	}

//	void (*pFunc)();
	virtual void ExecHalconFunc()=0;

//	void	SetXHalcon(XHalcon *XHalIns)	{	HalIns=XHalIns;	}
	XHalcon *GetXHalcon()					{	return HalIns;	}

private:
	XHalcon *HalIns;
};

//area_center
class	Farea_center : public HalconFuncListBase
{
public:
	Farea_center(XHalcon *XHalIns,HalconSampleList *List,QStringList *RegionList,QStringList *TupleList);
	virtual void ExecHalconFunc();

private:
	int RIndex,AreaIndex,RowIndex,ColIndex;
};

//closing_circle
class	Fclosing_circle : public HalconFuncListBase
{
public:
	Fclosing_circle(XHalcon *XHalIns,HalconSampleList *List,QStringList *RegionList,QStringList *TupleList);
	virtual void ExecHalconFunc();

private:
	int RIndex,RCIndex;
	double Radius;
	bool IsRadiusNumb;
};

//concat_obj
class	Fconcat_obj : public HalconFuncListBase
{
public:
	Fconcat_obj(XHalcon *XHalIns,HalconSampleList *List,QStringList *RegionList,QStringList *TupleList);
	virtual void ExecHalconFunc();

private:
	int Index1,Index2,CIndex;
};

//connection
class	Fconnection : public HalconFuncListBase
{
public:
	Fconnection(XHalcon *XHalIns,HalconSampleList *List,QStringList *RegionList,QStringList *TupleList);
	virtual void ExecHalconFunc();

private:
	int RIndex,CRIndex;
};

//count_obj
class	Fcount_obj : public HalconFuncListBase
{
public:
	Fcount_obj(XHalcon *XHalIns,HalconSampleList *List,QStringList *RegionList,QStringList *TupleList);
	virtual void ExecHalconFunc();

private:
	int Index,Number;
};

//difference
class	Fdifference : public HalconFuncListBase
{
public:
	Fdifference(XHalcon *XHalIns,HalconSampleList *List,QStringList *RegionList,QStringList *TupleList);
	virtual void ExecHalconFunc();

private:
	int RIndex,SIndex,RDIndex;
};

//emphasize
class	Femphasize : public HalconFuncListBase
{
public:
	Femphasize(XHalcon *XHalIns,HalconSampleList *List,QStringList *RegionList,QStringList *TupleList);
	virtual void ExecHalconFunc();

private:
	int IIndex,IEIndex,MaskWidth,MaskHeight,Factor;
};

//gen_image1
class	Fgen_image1 : public HalconFuncListBase
{
public:
	Fgen_image1(XHalcon *XHalIns,HalconSampleList *List,QStringList *RegionList,QStringList *TupleList);
	virtual void ExecHalconFunc();

private:
	int Index;
};

//Hgen_image3
class	Fgen_image3 : public HalconFuncListBase
{
public:
	Fgen_image3(XHalcon *XHalIns,HalconSampleList *List,QStringList *RegionList,QStringList *TupleList);
	virtual void ExecHalconFunc();

private:
	int Index;
};

//get_region_points
class	Fget_region_points : public HalconFuncListBase
{
public:
	Fget_region_points(XHalcon *XHalIns,HalconSampleList *List,QStringList *RegionList,QStringList *TupleList);
	virtual void ExecHalconFunc();

private:
	int Index,RowIndex,ColIndex;
};

//invert_image
class	Finvert_image : public HalconFuncListBase
{
public:
	Finvert_image(XHalcon *XHalIns,HalconSampleList *List,QStringList *RegionList,QStringList *TupleList);
	virtual void ExecHalconFunc();

private:
	int IIndex,IIIndex;
};

//mean_image
class	Fmean_image : public HalconFuncListBase
{
public:
	Fmean_image(XHalcon *XHalIns,HalconSampleList *List,QStringList *RegionList,QStringList *TupleList);
	virtual void ExecHalconFunc();

private:
	int IIndex,IMIndex,MaskWidth,MaskHeight;
};

//min_max_gray
class	Fmin_max_gray : public HalconFuncListBase
{
public:
	Fmin_max_gray(XHalcon *XHalIns,HalconSampleList *List,QStringList *RegionList,QStringList *TupleList);
	virtual void ExecHalconFunc();

private:
	int RIndex,IIndex,Percent,Min,Max,Range;
};

//select_obj
class	Fselect_obj : public HalconFuncListBase
{
public:
	Fselect_obj(XHalcon *XHalIns,HalconSampleList *List,QStringList *RegionList,QStringList *TupleList);
	virtual void ExecHalconFunc();

private:
	int Index,SIndex,Idx;
};

//select_shape
class	Fselect_shape : public HalconFuncListBase
{
public:
	Fselect_shape(XHalcon *XHalIns,HalconSampleList *List,QStringList *RegionList,QStringList *TupleList);
	virtual void ExecHalconFunc();

private:
	int RIndex,SRIndex,Features,Operation;
	double Min,Max;
	bool IsMinNumb,IsMaxNumb;
};

//threshold
class	Fthreshold : public HalconFuncListBase
{
public:
	Fthreshold(XHalcon *XHalIns,HalconSampleList *List,QStringList *RegionList,QStringList *TupleList);
	virtual void ExecHalconFunc();

private:
	int IIndex,RIndex,MinGray,MaxGray;
};

//tuple_max
class	Ftuple_max : public HalconFuncListBase
{
public:
	Ftuple_max(XHalcon *XHalIns,HalconSampleList *List,QStringList *RegionList,QStringList *TupleList);
	virtual void ExecHalconFunc();

private:
	int TIndex,Max;
};

//tuple_sum
class	Ftuple_sum : public HalconFuncListBase
{
public:
	Ftuple_sum(XHalcon *XHalIns,HalconSampleList *List,QStringList *RegionList,QStringList *TupleList);
	virtual void ExecHalconFunc();

private:
	int Index,Sum;
};

class	HalconFuncContainer : public NPListPack<HalconFuncListBase>
{
public:
	HalconFuncContainer(void){}
};

class	HalconArg : public NPList<HalconArg>
{
public:
	HalconArg(const char *A)			{	strcpy(Arg,A);				}
//	HalconArg(const char *A,int Len)	{	memcpy(Arg,A,Len);			}
	char	Arg[32];
	ArgType	AType;

	static	HalconArg	*GetNew(char *A);
};

inline	HalconArg	*HalconArg::GetNew(char *A)
{
	return new HalconArg(A);
}

class	HalconSampleList : public NPList<HalconSampleList>
{
public:
	QString			FuncName;
	NPListPack<HalconArg>	ArgList;

	HalconSampleList(void){}

	HalconSampleList	&operator=(HalconSampleList &src);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	HalconSampleContainer : public NPListPack<HalconSampleList>
{
public:
	HalconSampleContainer(void){}

	HalconSampleContainer	&operator=(HalconSampleContainer &src);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	HalconInspectionLibrary : public AlgorithmLibrary , public ServiceForLayers
{
public:
	HalconSampleContainer	SampleLists;

	QString HalconFuncString[100];
	int		FuncListCount;
	char	*FeaturesList[62];
	char	*OperationList[2];
	char	*NormList[1];
	char	*DirectionList[4];
	char	*FeatureList[5];
	char	*ShapeList[3];

	HalconInspectionLibrary(int LibType,LayersBase *Base);
	virtual	~HalconInspectionLibrary(void);

	virtual	bool	SaveBlob(QIODevice *f);
	virtual	bool	LoadBlob(QIODevice *f);

	virtual	HalconInspectionLibrary	&operator=(AlgorithmLibrary &src);
};

class	HalconInspectionLibraryContainer : public AlgorithmLibraryContainer
{
public:
	HalconInspectionLibraryContainer(LayersBase *base);
	virtual	~HalconInspectionLibraryContainer(void);

	virtual	int	GetLibType(void){	return 6;	}
	virtual	const char	*GetLibTypeName(void){	return "Halcon Inspection Library";	}
	virtual	AlgorithmLibrary	*CreateNew(void){	return new HalconInspectionLibrary(GetLibType(),GetLayersBase());	}
};

//=======================================================================================================
class	HalconInspectionThreshold : public AlgorithmThreshold
{
public:

	HalconInspectionThreshold(HalconInspectionItem *parent);

	virtual	void	CopyFrom(AlgorithmThreshold &src);
	virtual	bool	Save(QIODevice *f)				;
    virtual	bool	Load(QIODevice *f)				;
    virtual	int		GetSize(void)	override	{	return sizeof(this);	}
};

//=======================================================================================================
class	ResultClusterOnItem : public AddedDataClass
{
public:
	PureFlexAreaListContainer	List;
	ResultClusterOnItem(void){}

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	Clear(void){	List.RemoveAll();	}
};

class	HalconInspectionItem : public AlgorithmItemPI
{
public:
	BYTE	**NGBitmap;
	int		XByte;
	int		YLen;

	HalconInspectionItem(void);
	~HalconInspectionItem(void);

	const	HalconInspectionThreshold	*GetThresholdR(LayersBase *base=NULL){	return (const HalconInspectionThreshold *)GetThresholdBaseReadable(base);	}
	HalconInspectionThreshold			*GetThresholdW(LayersBase *base=NULL){	return (HalconInspectionThreshold *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)	override	{	return new HalconInspectionThreshold(this);	}

	virtual	AlgorithmItemPI	&operator=(AlgorithmItemRoot &src);
	virtual	bool    Save(QIODevice *f)						override;
    virtual	bool    Load(QIODevice *f,LayersBase *LBase)	override;
	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
	virtual	void	DrawResult    (ResultInItemRoot &Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate)	override;

	virtual	bool	ExecuteInitialAfterEdit	(int ThreadNo,ResultInItemRoot *Res ,EntryPointBase *pInspectionData);
	virtual	bool	ExecutePreProcessing	(int ThreadNo,ResultInItemRoot *Res ,EntryPointBase *pInspectionData);
	virtual	bool	ExecuteProcessing		(int ThreadNo,ResultInItemRoot *Res ,EntryPointBase *pInspectionData);

private:
	bool	GetHalconInspectionLibrary(GUIDirectMessage *CmdPacket);
	void	ImageBufferToHalcon(ImageBuffer *Buff[]);
	void	MakeExecuteProcess(void);
	void	CreateHalconFunc(HalconSampleList *List);
	bool	IsNumb(char Arg[]);
	void	SetStringList(HalconInspectionLibrary *p);

	XHalcon	XHal;
	HalconFuncContainer	HalconFuncList;
	QStringList	ArgRegionList;
	QStringList	ArgTupleList;
};

class   HalconInspectionInPage : public AlgorithmInPagePI
{
	friend	class	HalconInspectionItem;

public:
	HalconInspectionInPage(AlgorithmBase *parent);
	~HalconInspectionInPage(void);

	virtual	AlgorithmItemRoot	*CreateItem(int layer=-1 ,int ItemClassType=0){	return new HalconInspectionItem();	}
	virtual	void	TransmitDirectly(GUIDirectMessage *packet);
	virtual	void	Initial(LayersBase *Base);
};

class	HalconInspectionBase : public AlgorithmBase
{
public:
	QColor	ColorSelected;
	QColor	ColorActive;
	int32	TransparentLevel;
	QColor	NegColorMask;
	QColor	NegColorSelected;
	QColor	ColorNG;

//	QColor	ColorEffective;
//	QColor	ColorEffectiveLimited;
//	QColor	ColorIneffective;
//	QColor	ColorIneffectiveLimited;
	int		DefaultLibraryID;

	HalconInspectionBase(void);

	virtual	AlgorithmInPagePI	*NewChild(AlgorithmBase *parent){	return new HalconInspectionInPage(parent);	}
	virtual	QString	GetDataText(void)	{	return QString("HalconInspection");				}
	QString	GetDefaultFileName(void)	{	return QString("ConfigHalconInspection.dat");	}

	void	TransmitDirectly(GUIDirectMessage *packet);

	virtual	bool	SaveOnlyBase(QIODevice *f);
	virtual	bool	LoadOnlyBase(QIODevice *f);
};

//============================================================================================================================

class	HalconNGDataList : public NPList<HalconNGDataList>
{
public:
	int32	Page;
	int32	LibID;
	int32	CenterX,CenterY;
	int32	Area;	//ñ êœ

	HalconNGDataList(void){}
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	HalconNGDataListContainer : public NPListPack<HalconNGDataList>
{
public:
	HalconNGDataListContainer(void){}

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	CmdCreateNGListPacket : public GUIDirectMessage
{
public:
	HalconNGDataListContainer	*Point;
	ResultInspection			*Res;
	CmdCreateNGListPacket(void){}
};

class	CmdGetHalconInspectionLibraryListPacket : public GUIDirectMessage
{
public:
	int			LibFolderID;
	AlgorithmLibraryListContainer	AList;
	CmdGetHalconInspectionLibraryListPacket(void){}
};

class	CmdCreateTempHalconInspectionLibraryPacket : public GUIDirectMessage
{
public:
	HalconInspectionLibrary	*Point;
	CmdCreateTempHalconInspectionLibraryPacket(void){}
};

class	CmdInsertHalconInspectionLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibrary	*Point;
	CmdInsertHalconInspectionLibraryPacket(void){}
};

class	CmdUpdateHalconInspectionLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibrary	*Point;
	CmdUpdateHalconInspectionLibraryPacket(void){}
};

class	CmdLoadHalconInspectionLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibrary	*Point;
	CmdLoadHalconInspectionLibraryPacket(void){}
};

class	CmdDeleteHalconInspectionLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibrary	*Point;
	CmdDeleteHalconInspectionLibraryPacket(void){}
};

#endif
