/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\XResult.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef XRESULTH
#define XRESULTH

#include <QMutex>
#include <QReadWriteLock>
#include "XTypeDef.h"
#include "NList.h"
#include "XParamGlobal.h"
#include "XYCross.h"
#include "XServiceForLayers.h"
#include "XFlexArea.h"
#include "XTreeLines.h"
#include "XDateTime.h"
#include "XBoolList.h"
#include "XDLLType.h"
#include "XGUIPacketForDLL.h"

#define		Version_NGImage	5

class	DataInLayer;
class	DataInPage;
class	AlgorithmItemRoot;
class	AlgorithmInPageRoot;
class	AlgorithmInLayerRoot;
class	AlgorithmInPageInOnePhase;
class	AlgorithmBase;
class	SmallPartsList;
class	ResultInspection;
class	NGImageContainerInPhase;
class	ResultPosList;
class	ResultBaseForAlgorithm;
class	ResultBaseForAlgorithmRoot;
class	ResultBasePhase;
class	ResultInPageRoot;
class	ResultInLayerRoot;
class	ResultInItemRoot;
class	LogicDLL;
class	LogicDLLBaseClass;
class	ResultDLLBaseRoot;
class	LayersBase;
class	ErrorGroupPack;
class	LearningImage;
class	FileThread;
class	ExecuteInitialAfterEditInfo;

class	AddedDataClass
{
public:
	AddedDataClass(void){}
	virtual	~AddedDataClass(void){}
	virtual	void	Clear(void){}
};

class		ResultVectorItem : public TreePointList
{
public:
	ResultVectorItem(void){}
	explicit    ResultVectorItem(int32 x, int32 y):TreePointList(x,y){}

	ResultVectorItem &operator=(const ResultVectorItem &src);
};

class	ResultVectorLine: public TreeLine
{
public:
	ResultVectorLine(void){}

	ResultVectorLine	&operator=(const TreeLine &src);
	void	Add(ResultVectorItem *t);
	void	Add(int32 x, int32 y){		AppendList(new ResultVectorItem(x,y));	}
};

class	TmpNGRectClass : public NPList<TmpNGRectClass>
{
public:
    int x1,y1,x2,y2;
    int attr;
	int	mx,my;
	int	Count;
	int32		ImportanceLevel;
	int32		PieceAreaNumber;	//å¬ï–î‘çÜ
	int32		NGSize;				//NGÇÃëÂÇ´Ç≥
	DWORD		result;				//0x10000ñ¢ñûÇ≈ÇnÇj

	QString				CauseStr;
	QString				ItemName;
	ResultInItemRoot	*RepresentativeItem[10];
	ResultPosList		*RepresentativeResultPosList[10];
	int					RepresentativeItemCount;
	TmpNGRectClass(void);

    TmpNGRectClass   &operator=(const TmpNGRectClass &src);

    bool    Save(QIODevice *f);
    bool    Load(QIODevice *f);
	bool	IsInclude(int x ,int y)		const;
	void	GetCenter(int &x,int &y)	const	{	x=(x1+x2)/2;	y=(y1+y2)/2;	}

	int	GetMx(void)	const	{	return (Count!=0)?mx/Count:0;	}
	int	GetMy(void)	const	{	return (Count!=0)?my/Count:0;	}

	virtual	int	Compare(TmpNGRectClass &src)	override;
};

class	TmpNGDim : public ServiceForLayers
{
public:
	NPListPack<TmpNGRectClass>	**Dim;
	int		XLen;
	int		YLen;
	int		XNumb;
	int		YNumb;

	TmpNGDim(void);
	virtual	~TmpNGDim(void);

	void	Set(LayersBase *Base);
	NPListPack<TmpNGRectClass>	*GetPoint(int X ,int Y);
};

class	ResultPosList : public NPList<ResultPosList>
{
public:
  #pragma	pack(push,1)

	DWORD		result;					//0x10000ñ¢ñûÇ≈ÇnÇj
	enum _ResultType{
		 _ResultDWORD	=0
		,_ResultDouble	=1
		,_ResultFloat	=2
	}ResultType;

private:
	union{
		struct	{
			DWORD		result1;
			DWORD		result2;				//åãâ ÉfÅ[É^
		};
		struct	{
			double		resultDouble;
		};
		struct	{
			float		resultFloat1;
			float		resultFloat2;
		};
	};
public:

	int32		Px;         //ÇmÇfÇÃÉ}ÉXÉ^Å[âÊëúÇ≈ÇÃäÓèÄç¿ïW
    int32		Py;

	short		Rx;
    short		Ry;			//ÇmÇfïîï™ÇÃÉAÉâÉCÉìÉÅÉìÉgï‚ê≥ÇµÇΩè„Ç≈ÇÃíTçıó 

	int32		NGTypeUniqueCode;
	int32		ImportanceLevel;	//èÍèäÇ…ÇÊÇÈèdóvìxÅ@ÇOÅFç≈èdóvÅ@í èÌÇPÇOÇO
	int32		PieceAreaNumber;	//å¬ï–î‘çÜ
	int32		NGSize;				//NGÇÃëÂÇ´Ç≥
  #pragma	pack(pop)

	QStringList	AreaNames;
	FlexArea	NGShape;	//GlobalParamÇ…ÇÊÇ¡Çƒê∂ê¨ÇµÇ»Ç¢èÍçáÇ™Ç†ÇÈ
	QString		Message;
	ResultVectorLine	Vector;

	ResultPosList(void);
	ResultPosList(const ResultPosList &src);
	explicit    ResultPosList(int px ,int py);
	explicit    ResultPosList(int px ,int py ,int rx ,int ry)
						:result(0),ResultType(_ResultDWORD),result1(0),result2(0)
						,Px(px),Py(py),Rx(rx),Ry(ry)
						,NGTypeUniqueCode(-1),ImportanceLevel(100),PieceAreaNumber(-1),NGSize(0){}
	virtual	~ResultPosList(void){}

	bool	IsOK(void)	const	{	return (result<0x10000)?true:false;	}
	virtual	bool    Load(QIODevice *f);
    virtual	bool    Save(QIODevice *f);
	void    Move(int dx ,int dy);
	ResultPosList	&operator=(const ResultPosList &src);
	int32	GetByte(void)	const;
	virtual	void	DrawResult(ResultInItemRoot *parent ,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate 
							,int MinimumRadius,QRgb Col,int CircleWidth,bool DrawBlueNGMark);
	virtual	void	DrawResultDetail(ResultInItemRoot *parent ,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate 
							,int MinimumRadius,QRgb Col,int CircleWidth,bool DrawBlueNGMark);

	void	GetPosInTarget(ResultInItemRoot *parent,int &X, int &Y)		const;
	void	GetDxyInTarget(ResultInItemRoot *parent,int &Dx, int &Dy)	const;
	bool	IsOverlap(const FlexArea &Area)			const;
	bool	GetXY(int &x1,int &y1,int &x2,int &y2)	const;

	void	SetResultCode	(DWORD _result)	{	result=_result;	}
	void	SetResult		(DWORD _result)	{	result=_result;	}

	void	SetResult1(DWORD _result1);
	void	SetResult2(DWORD _result2);
	void	SetResult(double result);
	void	SetResultFloat1(float result);
	void	SetResultFloat2(float result);

	DWORD	GetResult1(void)		const	{	return result1;	}	
	DWORD	GetResult2(void)		const	{	return result2;	}	
	double	GetResultDouble(void)	const	{	return resultDouble;	}
	float	GetResultFloat1(void)		const	{	return resultFloat1;	}	
	float	GetResultFloat2(void)		const	{	return resultFloat2;	}	
	virtual	void	GetExtraData(QByteArray &EData){}
};

class	ResultPosListContainer : public NPListPack<ResultPosList>
{
public:
	ResultPosListContainer(void){}
	ResultPosListContainer	&operator=(const ResultPosListContainer &src);
};


class	NGAreaList : public NPList<NGAreaList>
{
	QString	AreaName;
	int32	NGCount;

public:
	NGAreaList(void){	NGCount=0;	}
	NGAreaList(const NGAreaList &src);

	explicit    NGAreaList(const QString &areaName ,int32 ngCount):AreaName(areaName){	NGCount=ngCount;	}

	bool	Load(QIODevice *f);
	bool	Save(QIODevice *f);

	NGAreaList	&operator=(const NGAreaList &src);

	const QString	&GetAreaName(void)	const	{	return AreaName;	}
	int32	GetNGCount(void)			const	{	return NGCount;		}
	void	SetNGCount(int32 n)					{	NGCount=n;		}
};

class	NGAreaListContainer : public NPListPack<NGAreaList>
{
public:
	NGAreaListContainer(){}
	NGAreaListContainer(const NGAreaListContainer &src);

	bool	Load(QIODevice *f);
	bool	Save(QIODevice *f);

	NGAreaListContainer	&operator=(const NGAreaListContainer &src);
	NGAreaListContainer	&operator+=(const NGAreaListContainer &src);
	NGAreaList	*Search(const QString &areaname)	const;
};

class   NGImage final: public NPList<NGImage> , public ServiceForLayers
{
  #pragma	pack(push,1)
	BYTE		**SrcImage[3];
	int			SrcImageXLen;
	int			SrcImageYLen;
    uchar		*CompressedPtn;
    int32		PtnByte;

	int32		GlobalPage;
	int32		Number;		//ÇmÇfÉtÉ@ÉCÉãêÊì™ÇÇOÇ∆ÇµÇΩí Çµî‘çÜ
    int32		x1,y1,x2,y2;//åüç∏âÊëúè„ÇÃÉyÅ[ÉWì‡à íu
	int32		Mx,My;		//ïΩãœÉYÉåó 
	bool		SuccessCompress;
  #pragma	pack(pop)
public:

    NGImage(LayersBase *base);
    virtual	~NGImage(void);

	bool    Save(QIODevice  *file ,int offsetX=0, int offsetY=0);
	bool    Save(FileThread *file ,int offsetX=0, int offsetY=0);
    bool    Load(QIODevice  *file);

	bool    SaveJDT(QIODevice  *file,int offsetX=0, int offsetY=0);
	bool    SaveJDT(FileThread *file,int offsetX=0, int offsetY=0);
    bool    LoadJDT(QIODevice  *file);

	bool	SaveRawImage(QIODevice  *file,int offsetX=0, int offsetY=0);
	bool	SaveRawImage(FileThread *file,int offsetX=0, int offsetY=0);
	bool    LoadRawImage(QIODevice  *file);

	int     GetByte(void)	const;
    NGImage &operator=(const NGImage &src);

    int     GetWidth(void)	const	{	return(x2-x1);  }
    int     GetHeight(void)	const	{	return(y2-y1);  }

	bool	Expire(void);
	bool	AllocateBuffer(int LayerNumb);
	void	CopyImageFromTarget(DataInPage *PData);
	//void	CaptureRawImage(void);
	bool	CompressImage(DataInPage *PData,int quality);
	bool	IsOverlapped(const FlexArea &Area)	const;
	void	MoveTo(int dx,int dy);

	void	SetRectangle(int _x1,int _y1 ,int _x2 ,int _y2)			{	x1=_x1;	y1=_y1;	x2=_x2;	y2=_y2;	}
	bool	GetXY(int &qx1,int &qy1,int &qx2,int &qy2)		const	{	qx1=x1;	qy1=y1;	qx2=x2;	qy2=y2;	return true;	}
	int32	GetGlobalPage(void)			const	{	return GlobalPage;	}
	void	SetGlobalPage(int32 page)			{	GlobalPage=page;	}
	int32	GetNumber(void)				const	{	return Number;		}		//ÇmÇfÉtÉ@ÉCÉãêÊì™ÇÇOÇ∆ÇµÇΩí Çµî‘çÜ
	void	SetNumber(int32 n)					{	Number	=n;			}		//ÇmÇfÉtÉ@ÉCÉãêÊì™ÇÇOÇ∆ÇµÇΩí Çµî‘çÜ

	void	SetMxy(int _mx ,int _my)			{	Mx=_mx;	My=_my;	}
	int		GetMx(void)					const	{	return Mx;	}
	int		GetMy(void)					const	{	return My;	}
};

class  ResultInItemRoot
{
  #pragma	pack(push,1)
	short		Error;					//ÇmÇfÉåÉxÉã	Å|ÇPÅFñ¢åüç∏ÉGÉäÉA	ÇOÅFñ¢îªíË	ÇPÅFÇnÇj	ÇQÅ`ÇmÇf

	DWORD		result1;
	DWORD		result2;				//åãâ ÉfÅ[É^

public:

private:
	enum _ResultType	ResultType;

        union _ResultValue{
			double	ResultDouble;
			int64	ResultQInt;
			struct	ResultWord{
				WORD	ResultW[4];
			}ResultW;
			struct	ResultByte{
				BYTE	ResultB[8];
			}ResultB;
        } ResultValue;

	int32		ItemID;					//Number;
    int32		SmallPartsID;			//å¬ï–ID

	short		ItemSearchedX;			//Hx
    short		ItemSearchedY;			//Hy	å¬ï íTçıï‚ê≥ó 
	short		AlignedX;			//Mx
    short		AlignedY;			//My	ÉAÉâÉCÉìÉÅÉìÉgï‚ê≥ó 

	DWORD			AddedDataForRepairByte;
	DWORD			AddedDataForRepairType;
	AddedDataClass	*AddedDataForRepair;

	DWORD			AddedDataByte;
	DWORD			AddedDataType;
	AddedDataClass	*AddedData;
	AlgorithmItemRoot	*AlgorithmItemPointer;	//Set by every ExecuteProcessing
  #pragma	pack(pop)
	ResultPosListContainer	PosList;	//è⁄ç◊à íuèÓïÒ
	QString			Message;
	int				ErrorGroupID;
public:
	ResultInItemRoot(void);
    virtual	~ResultInItemRoot(void);

	virtual	ResultInItemRoot	*Clone(void)	=0;

	virtual	void	BuildNGImages(int ImageW ,int ImageH ,int Bevel ,NPListPack<TmpNGRectClass> &TmpRect,ErrorGroupPack &SpecializedGroup);
	virtual	void	BuildNGImages(int ImageW ,int ImageH ,int Bevel ,TmpNGDim &TmpRectDim,ErrorGroupPack &SpecializedGroup);
	bool    Load(QIODevice *f);
    bool    Save(QIODevice *f);

	AlgorithmItemRoot	*GetAlgorithmItem(void)			const	{	return AlgorithmItemPointer;	}
	void				SetAlgorithmItem(AlgorithmItemRoot *r)	{	AlgorithmItemPointer=r;	}

	void    Move(int dx ,int dy);
    ResultInItemRoot  &operator=(const ResultInItemRoot &src);
	void	InitialInspection(void);
	void	GetCenter(int &cx, int &cy)	const;
	void	BindNGAreaListContainer(NGAreaListContainer &List);

	QString	GetPosString(void)	const;

	bool	IsOk(void)		const	{	return (Error<2)?true:false;	}
	bool	IsDone(void)	const	{	return (Error==0)?false:true;	}
	virtual	LogicDLL			*GetLogicDLL(void)			const	=0;
	virtual	AlgorithmBase		*GetAlgorithmBase(void)		const	=0;
	virtual	ResultInspection	*GetResultInspection(void)	const	=0;
	virtual	int					GetPage(void)				const	=0;
	virtual	int					GetPhaseCode(void)			const	=0;
	virtual	int					GetLayer(void)				const	=0;
	virtual	AlgorithmItemRoot	*GetAlgorithmItemRoot(void)	const	=0;
	virtual	LayersBase			*GetLayersBase(void)		const	=0;
	virtual	int					GetDotPerLine(void)			const	=0;
	virtual	int					GetMaxLines(void)			const	=0;
	int		GetLayerNumb(void)	const;
	int		GetPageNumb(void)	const;

	QString	ResultItemToString(void);

	bool	IsNGNearXY(const FlexArea &area)	const;
	bool	IsOverlap (const FlexArea &Area)	const;

	void	GetTotalShifted(int &sx ,int &sy)	const	{	sx=AlignedX+ItemSearchedX;	sy=AlignedY+ItemSearchedY;	}
	int		GetTotalShiftedX(void)	const	{	return AlignedX+ItemSearchedX;	}
	int		GetTotalShiftedY(void)	const	{	return AlignedY+ItemSearchedY;	}
	int		GetItemID(void)			const	{	return ItemID;			}
	void	SetItemID(int32 id)				{	ItemID=id;			}
	int		GetSmallPartsID(void)	const	{	return SmallPartsID;	}
	int		GetAlignedX(void)		const	{	return AlignedX;		}
	int		GetAlignedY(void)		const	{	return AlignedY;		}
	int		GetItemSearchedX(void)	const	{	return ItemSearchedX;	}
	int		GetItemSearchedY(void)	const	{	return ItemSearchedY;	}

	void	SetAlignedXY	 (short dx,short dy)	{	AlignedX=dx;		AlignedY=dy;		}
	void	SetItemSearchedXY(short dx,short dy)	{	ItemSearchedX=dx;	ItemSearchedY=dy;	}
	bool	GetDistanceVector(int x ,int y,double &RetLength)	const;
	bool	GetDistanceArea(int x ,int y,double &RetLength)		const;

	virtual	ResultPosList	*CreateResultPosList(void)	{	return new ResultPosList();	}
	ResultPosListContainer	&GetPosList(void)			{	return PosList;				}
	ResultPosList	*GetPosListFirst(void)				{	return PosList.GetFirst();	}
	void	AddPosList		(ResultPosList *b)			{	PosList.AppendList(b);		}
	void	MovePosList		(ResultPosListContainer &b)	{	PosList.Move(b);			}
	void	AddMovePosList	(ResultPosListContainer &b)	{	PosList.AddMove(b);			}
	void	ClearPosList(void)							{	PosList.RemoveAll();		}

	AddedDataClass	*GetAddedData(void)		const	{	return AddedData;		}
	DWORD			GetAddedDataType(void)	const	{	return AddedDataType;	}
	void			SetAddedData(AddedDataClass	*b,DWORD aType ,DWORD aByte=0)
						{	AddedData=b;	AddedDataType=aType;	AddedDataByte=aByte;	}

	virtual	int		GetNGPointCount(void)	const;
	virtual	int		GetTotalNGSize(void)	const;

	_ResultType	GetResultType(void)	const	{	return ResultType;	}

	short	GetError(void)		const	{	return Error;		}		//ÇmÇfÉåÉxÉã	Å|ÇPÅFñ¢åüç∏ÉGÉäÉA	ÇOÅFñ¢îªíË	ÇPÅFÇnÇj	ÇQÅ`ÇmÇf
	void	SetError(short s)			{	Error=s;			}
	DWORD	GetResult1(void)	const	{	return result1;		}
	void	SetResult1(DWORD d)			{	result1=d;	ResultType=_ResultDWORD;		}
	DWORD	GetResult2(void)	const	{	return result2;		}				//åãâ ÉfÅ[É^
	void	SetResult2(DWORD d)			{	result2=d;	ResultType=_ResultDWORD;		}				//åãâ ÉfÅ[É^
	double	GetResultDouble(void)	const	{	return ResultValue.ResultDouble;	}
	void	SetResultDouble(double d)		{	ResultValue.ResultDouble=d;		ResultType=_ResultDouble;	}

	BYTE	GetResultByte(int Index)	const;
	void	SetResultByte(int Index ,BYTE d);

	WORD	GetResultWord(int Index)	const;
	void	SetResultWord(int Index ,WORD d);

	void	ReviveResult(LearningImage *c);
	int		GetPointerListOfResultPosList(FlexArea &OverlapArea ,ResultPosList **RetDim ,int MaxCount);
	
	void	ClearResult(void);
	void	SetErrorGroupID(int d)			{	ErrorGroupID=d;			}
	int		GetErrorGroupID(void)	const	{	return ErrorGroupID;	}

	QString	GetResultMessage(void)	const		{	return Message;		}
	void	SetResultMessage(const QString &s)	{	Message=s;			}

private:
	int32	GetByte(void)	const;
};

class	ResultInItemRootPointerList : public NPList<ResultInItemRootPointerList>
{
public:
	ResultInItemRoot	*Pointer;

	explicit	ResultInItemRootPointerList(ResultInItemRoot *d):Pointer(d){}
};


class   ResultPosInfo : public NPList<ResultPosInfo>
{
public:
	ResultPosList		*RPos;
	ResultInItemRoot	*RItem;
	AlgorithmItemRoot	*AItem;

	ResultPosInfo(void)	{	RPos=NULL;	RItem=NULL;	AItem=NULL;	}
};


class   ErrorGroup : public NPList<ErrorGroup> , public ServiceForLayers
{
  #pragma	pack(push,1)
public:
	struct HPLIStruct
	{
		int32		LibType;
		int16		Phase;
		int16		Page;
		int16		Layer;
		int32		ItemID;
	};
private:
	struct{
		int32	ErrorGroupID;
		int32	x1,y1,x2,y2;
		int32	mx,my;
		int16	Page;
		DWORD	result;				//0x10000ñ¢ñûÇ≈ÇnÇj
		int16	ImportanceLevel;	//èÍèäÇ…ÇÊÇÈèdóvìxÅ@ÇOÅFç≈èdóvÅ@í èÌÇPÇOÇO
		int32	PieceAreaNumber;	//å¬ï–î‘çÜ
		int32	NGSize;				//NGÇÃëÂÇ´Ç≥
		struct HPLIStruct	RepresentativeItem;
	}CData;

  #pragma	pack(pop)
	QString	Name;
	QString	Cause;
	QString	Message;
	bool	SentCompressor;

public:
	ResultInItemRoot	*TmpRepresentativeItem[10];	//Not saved
	ResultPosList		*TmpRepresentativeResultPosList[10];
	int					TmpRepresentativeItemCount;

public:
	ResultInItemRoot	*RepresentativeItemPoint;
public:
	explicit	ErrorGroup(LayersBase *Base);

    ErrorGroup  &operator=(const ErrorGroup &src);
	void	SetMxy(int _mx ,int _my)	{	CData.mx=_mx;	CData.my=_my;	}
	int		GetMx(void)		const		{	return CData.mx;	}
	int		GetMy(void)		const		{	return CData.my;	}

	bool    Load(QIODevice *f);
    bool    Save(QIODevice *f);
	bool    Save(FileThread *f);

	void	GetCenter(int &Cx, int &Cy)	const	{	Cx=(CData.x1+CData.x2)/2;	Cy=(CData.y1+CData.y2)/2;	}
	void	SetRectangle(int _x1,int _y1 ,int _x2 ,int _y2)		{	CData.x1=_x1;	CData.y1=_y1;	CData.x2=_x2;	CData.y2=_y2;	}
	bool	GetXY(int &qx1,int &qy1,int &qx2,int &qy2)	const	{	qx1=CData.x1;	qy1=CData.y1;	qx2=CData.x2;	qy2=CData.y2;	return true;	}
	void	SetPage(int page)					{	CData.Page=page;		}
	int		GetPage(void)				const	{	return CData.Page;	}
	void	SetResult(DWORD _result)			{	CData.result=_result;	}
	DWORD	GetResult(void)				const	{	return CData.result;	}
	QString	GetName(void)				const;
	void	SetName(const QString &name);
	QString	GetCause(void)					const;
	void	SetCause(const QString &str)	;
	QString	GetMessageStr(void)				const;
	void	SetMessageStr(const QString &str)	;

	void	SetImportanceLevel(int n)	;
	int		GetImportanceLevel(void)	const;

	int32		GetPieceAreaNumber(void)	;
	void		SetPieceAreaNumber(int n)	;

	void	SetNGSize(int n)	;
	int32	GetNGSize(void)		const;
	int		GetWidth(void)		const;
	int		GetHeight(void)		const;

	bool	IsSentCompressor(void)		;
	void	SetSentCompressor(bool b)	;

	void	SetRepresentativeItem(ResultInItemRoot *r ,ResultPosList *p);
	const struct HPLIStruct	*GetRepresentativeItem(void)	{	return &CData.RepresentativeItem;	}
	bool	HasRepresentativeItem(void);

	void	SetErrorGroupID(int d)			{	CData.ErrorGroupID=d;		}
	int		GetErrorGroupID(void)	const	{	return CData.ErrorGroupID;	}
};

class	ErrorGroupPack : public NPListPack<ErrorGroup>
{
public:
	ErrorGroupPack(void){}

    ErrorGroupPack  &operator=(const ErrorGroupPack &src);
    ErrorGroupPack  &operator+=(const ErrorGroupPack &src);
	bool    Load(QIODevice *f,LayersBase *Base);
    bool    Save(QIODevice *f);	
	bool    Save(FileThread *f);	
};


//===============================================================================

class	ResultParentFromItem
{
protected:
	ResultInItemRoot	**ItemDimPointer;
	int					ItemDimPointerNumb;

public:
	ResultParentFromItem(void);
	~ResultParentFromItem(void);

	void	SortResultDimPointer(void);
protected:
	void	AllocateForFastSearch(int ItemCount);
	ResultInItemRoot	*FastSearchIDItemInside(int ItemID)	const;
};


class	ResultInLayerRoot : public ServiceForLayers ,public ResultParentFromItem
{
protected:
	int32							Layer;
	//DataInLayer					*PDataInLayer;

	AlgorithmInLayerRoot			*AlgoPointer;
	bool							CalcDone;		//Ç±ÇÍÇÕëSPhaseÇÃç≈èâÇ…falseÇ…Ç»ÇÈ
protected:
	void	SetDataInLayer(DataInLayer *L)	{	Layer=-1;	}	//PDataInLayer=L;	}	
public:

	explicit	ResultInLayerRoot(DataInLayer *pDataInLayer);
	virtual	~ResultInLayerRoot(void);

	virtual void	Initial(ResultBaseForAlgorithmRoot *parent)	=0;

	virtual	ResultInItemRoot	*CreateItem(void)				=0;
	virtual	ResultInItemRoot	*CreateItemDim(int count)		=0;
	virtual	ResultInItemRoot	*FastSearchIDItem(int ItemID)	const	=0;

	int		GetLayer(void)		const	{		return Layer;	}
	void	SetLayer(int layer)			{	Layer=layer;	}
	virtual	int		GetPage(void)		const;
	virtual	int		GetPhaseCode(void)	const;	

	virtual	bool    Save(QIODevice *file);
    virtual	bool    Load(QIODevice *file);

	virtual	void	MoveMerge(ResultInLayerRoot &dst)	=0;

	virtual	AlgorithmInLayerRoot		*GetAlgorithmInLayer(void)			const	=0;
	virtual	AlgorithmInPageRoot			*GetAlgorithmInPage(void)			const	=0;
	virtual	AlgorithmInPageInOnePhase	*GetAlgorithmInPageInOnePhase(void)	const	=0;
	virtual	AlgorithmBase				*GetAlgorithmBase(void)				const	=0;

	virtual	XDateTime	&GetStartInspectionTime(void)		=0;

	virtual	void	InitialInspection(void)	=0;
	virtual	bool	GatherResult(bool3 &OK)	=0;
	virtual	bool	GatherResult(NPListPack<ResultPosInfo> &RContainer,bool3 &OK)	const	=0;

	virtual	void	BuildNGImages(int ImageW ,int ImageH ,int Bevel ,NPListPack<TmpNGRectClass> &TmpRect,ErrorGroupPack &SpecializedGroup)=0;
	virtual	void	BuildNGImages(int ImageW ,int ImageH ,int Bevel ,TmpNGDim &TmpRectDim,ErrorGroupPack &SpecializedGroup)				=0;
	virtual	void	BindNGAreaListContainer(NGAreaListContainer &List)	=0;

	ResultDLLBaseRoot	*GetResultDLLBase(void)	const;
	virtual	int			GetNGCount(void)		const	=0;
	virtual	int			GetNGPointCount(void)	const	=0;
	virtual	ResultInspection	*GetResultInspection(void)	const	=0;

	virtual	void	ExecuteInAllItems(void (*Func)(ResultInItemRoot *Item ,void *Something),void *Something)=0;

	virtual	void	GetNGItemList(NPListPack<ResultInItemRootPointerList> &Ret ,FlexArea &area)=0;
	virtual	void	ReviveResult(LearningImage *c)	=0;
	virtual	int		GetPointerListOfResultPosList(FlexArea &OverlapArea ,ResultPosList **RetDim ,int MaxCount)	=0;
	virtual	void	GetItemListByErrorGroupID(NPListPack<ResultInItemRootPointerList> &Ret ,int ErrorGroupID)=0;

	bool	IsCalced(void)	const	{	return CalcDone;	}
	virtual	void	SetCurentCalcDone(bool b)	=0;

	virtual	ExeResult	ExecuteInitialAfterEditPrev	(int ExeID)	=0;
	virtual	ExeResult	ExecuteInitialAfterEdit		(int ExeID)	=0;
	virtual	ExeResult	ExecuteInitialAfterEditPost	(int ExeID)	=0;
	virtual	ExeResult	ExecuteStartByInspection	(int ExeID)	=0;
	virtual	ExeResult	ExecuteCaptured				(int ExeID,ListPhasePageLayerPack &CapturedList)	=0;
	virtual	ExeResult	ExecutePreAlignment			(int ExeID)	=0;
	virtual	ExeResult	ExecuteAlignment			(int ExeID)	=0;
	virtual	ExeResult	ExecutePreProcessing		(int ExeID)	=0;
	virtual	ExeResult	ExecuteProcessing			(int ExeID)	=0;
	virtual	ExeResult	ExecuteProcessingRevived	(int ExeID)	=0;
	virtual	ExeResult	ExecutePostProcessing		(int ExeID)	=0;
	virtual	ExeResult	ExecutePreScanning			(int ExeID)	=0;
	virtual	ExeResult	ExecuteScanning				(int ExeID)	=0;
	virtual	ExeResult	ExecutePostScanning			(int ExeID)	=0;

	virtual	void	ClearResult(void)	=0;
};


#pragma	pack(push,1)

struct	ResultPositionInfomation
{
	short	Error;		//Same as ResultInItemRoot::Error
	DWORD	PosResult;	
	int32	X,Y;		//NG in Master position
	int32	MX,MY;		//Shift by Alignment
	int32	HX,HY;		//Shift by itself
	int32	LibType;
	int32	LibID;
	int32	NGTypeUniqueCode;
	//DWORD	Result1;
	//DWORD	Result2;
	DWORD		result1;
	DWORD		result2;				//åãâ ÉfÅ[É^
	_ResultType	ResultType;
    union _ResultValue{
		double	ResultDouble;
		int64	ResultQInt;
		struct	ResultWord{
			WORD	ResultW[4];
		}ResultW;
		struct	ResultByte{
			BYTE	ResultB[8];
		}ResultB;
       } ResultValue;

	int32	Layer;
	union{
		char	AreaName[32];
		BYTE	Something[32];
	};
	int32	UniqueID1;
	int32	UniqueID2;
	int32	ExtraDataByte;

	ResultPositionInfomation()	{	ExtraDataByte=0;	}
};

struct	ResultPositionInfomationVer2
{
	short	Error;		//Same as ResultInItemRoot::Error
	DWORD	PosResult;	
	int32	X,Y;		//NG in Master position
	int32	MX,MY;		//Shift by Alignment
	int32	HX,HY;		//Shift by itself
	int32	LibType;
	int32	LibID;
	int32	NGTypeUniqueCode;
	//DWORD	Result1;
	//DWORD	Result2;
	DWORD		result1;
	DWORD		result2;				//åãâ ÉfÅ[É^
	_ResultType	ResultType;
    union _ResultValue{
		double	ResultDouble;
		int64	ResultQInt;
		struct	ResultWord{
			WORD	ResultW[4];
		}ResultW;
		struct	ResultByte{
			BYTE	ResultB[8];
		}ResultB;
       } ResultValue;

	int32	Layer;
	union{
		char	AreaName[32];
		BYTE	Something[32];
	};
	int32	UniqueID1;
	int32	UniqueID2;
};

struct	ResultPositionInfomationOld2
{
	short	Error;		//Same as ResultInItemRoot::Error
	int32	X,Y;		//NG in Master position
	int32	MX,MY;		//Shift by Alignment
	int32	HX,HY;		//Shift by itself
	int32	LibType;
	int32	LibID;
	int32	NGTypeUniqueCode;
	//DWORD	Result1;
	//DWORD	Result2;
	DWORD		result1;
	DWORD		result2;				//åãâ ÉfÅ[É^
	_ResultType	ResultType;
        union _ResultValue{
		double	ResultDouble;
		int64	ResultQInt;
		struct	ResultWord{
			WORD	ResultW[4];
		}ResultW;
		struct	ResultByte{
			BYTE	ResultB[8];
		}ResultB;
        } ResultValue;;

	int32	Layer;
	union{
		char	AreaName[32];
		BYTE	Something[32];
	};
	int32	UniqueID1;
	int32	UniqueID2;
};

struct	ResultPositionInfomationOld
{
	short	Error;		//Same as ResultInItemRoot::Error
	int32	X,Y;		//NG in Master position
	int32	MX,MY;		//Shift by Alignment
	int32	HX,HY;		//Shift by itself
	int32	LibType;
	int32	LibID;
	int32	NGTypeUniqueCode;
	//DWORD	Result1;
	//DWORD	Result2;
	DWORD		result1;
	DWORD		result2;				//åãâ ÉfÅ[É^
        union _ResultValue{
		double	ResultDouble;
		int64	ResultQInt;
		struct	ResultWord{
			WORD	ResultW[4];
		}ResultW;
		struct	ResultByte{
			BYTE	ResultB[8];
		}ResultB;
        } ResultValue;

	int32	Layer;
	union{
		char	AreaName[32];
		BYTE	Something[32];
	};
	int32	UniqueID1;
	int32	UniqueID2;
};
#pragma	pack(pop)

class	ResultInPageRoot : public ServiceForLayers,public ResultParentFromItem
{
protected:
	int32				Page;
	DataInPage			*PDataInPage;
	ResultBasePhase		*PhaseParent;
	AlgorithmInPageRoot	*AlgoPointer;
	bool				CalcDone;		//Ç±ÇÍÇÕëSPhaseÇÃç≈èâÇ…falseÇ…Ç»ÇÈ
	bool				DoneBindImage;	//Ç±ÇÍÇÕëSPhaseÇÃç≈èâÇ…falseÇ…Ç»ÇÈ
protected:
	void	SetDataInPage(DataInPage *L)	{	PDataInPage=L;	}
public:
	explicit	ResultInPageRoot(ResultBasePhase *pPhaseParent,DataInPage *pPage);
	virtual	~ResultInPageRoot(void);

	virtual	ResultInItemRoot	*CreateItem(void)			=0;
	virtual	ResultInItemRoot	*CreateItemDim(int count)	=0;
	virtual	ResultInItemRoot	*FindResultInItem(int layer ,int ItemID)	const	=0;
	virtual	ResultInItemRoot	*FastSearchIDItem(int layer ,int ItemID)	const	=0;

	ResultBasePhase *GetPhaseParent(void)	const	{	return PhaseParent;		}

	int		GetPage(void)		const	{	return Page;	}
	void	SetPage(int page)			{	Page=page;	}
	int		GetPhaseCode(void)	const;	

	virtual	bool	Initial(ResultBaseForAlgorithmRoot *parent)	=0;
	virtual	void	Release(void)								=0;
	virtual	bool	Reallocate(int newLayerNumb)=0;

	virtual	bool    Save(QIODevice *file);
    virtual	bool    Load(QIODevice *file);
	virtual	void	MoveMerge(ResultInPageRoot &dst)	=0;

	virtual	void	InitialInspection(void)				=0;
	virtual	void	BuildNGImages(int ImageW ,int ImageH ,int Bevel ,NPListPack<TmpNGRectClass> &TmpRect,ErrorGroupPack &SpecializedGroup)=0;
	virtual	void	BuildNGImages(int ImageW ,int ImageH ,int Bevel ,TmpNGDim &TmpRectDim,ErrorGroupPack &SpecializedGroup)				=0;
	virtual	void	BindNGAreaListContainer(NGAreaListContainer &List)	=0;

	virtual	ResultDLLBaseRoot	*GetResultDLLBase(void)	const	=0;

	virtual	AlgorithmInPageInOnePhase	*GetAlgorithmInPageInOnePhase(void)	const	=0;
	virtual	AlgorithmBase				*GetAlgorithmBase(void)				const	=0;

	DataInPage					*GetDataInPage(void)	const;
	virtual	LayersBase			*GetLayersBase(void)	const;

	virtual	int		GetNGCount(void)		const	=0;
	virtual	int		GetNGPointCount(void)	const	=0;
	virtual	bool	GatherResult(bool3 &OK)	const	=0;
	virtual	bool	GatherResult(NPListPack<ResultPosInfo> &RContainer,bool3 &OK)	const	=0;

	virtual	void	OutputResult(int globalPage ,LogicDLL *LogicDLLPoint ,QStringList &ResList)=0;
	virtual	void	OutputResult(int globalPage ,LogicDLL *LogicDLLPoint ,char *ResList)=0;
	virtual	bool	OutputResult(int globalPage ,LogicDLL *LogicDLLPoint ,QIODevice *f,int &WrittenNGCount)=0;
	virtual	bool	OutputResult(int globalPage ,LogicDLL *LogicDLLPoint ,FileThread *f,int &WrittenNGCount)=0;
	virtual	void	OutputResult(FlexArea &Area ,int OffsetX ,int OffsetY
								,int globalPage ,LogicDLL *LogicDLLPoint ,QStringList &ResList)=0;

	virtual	void	MakeResultDetailInNG(DetailResultInfoListContainerAll &List)	=0;

	virtual	ResultInspection	*GetResultInspection(void)	const	=0;

	virtual	void	ExecuteInAllItems(void (*Func)(ResultInItemRoot *Item ,void *Something),void *Something)=0;

	virtual	void	GetNGItemList(NPListPack<ResultInItemRootPointerList> &Ret ,FlexArea &area)	=0;
	virtual	void	GetItemListByErrorGroupID(NPListPack<ResultInItemRootPointerList> &Ret ,int ErrorGroupID)=0;

	virtual	void	ExecuteFuncInAllItems(void (*ItemFunc)(ResultInItemRoot *Item, void *_Something),void *Something)=0;
	virtual	void	ExecuteFuncInAllItemPos(void (*PosFunc)(ResultInItemRoot *Item, ResultPosList *RPos,void *_Something),void *Something)=0;

	virtual	void	SetResultMarkForLearning(void)	=0;
	virtual	void	ReviveResult(LearningImage *c)	=0;
	void	CalcNGCounterAgain(void);
	virtual	int		GetPointerListOfResultPosList(FlexArea &OverlapArea ,ResultPosList **RetDim ,int MaxCount)	=0;

	bool	IsCalced(void)			const		{	return CalcDone;		}
	virtual	void	SetCurentCalcDone(bool b)	=0;
	bool	IsDoneBindImage(void)	const		{	return DoneBindImage;	}
	virtual	void	SetDoneBindImage(bool b)	{	DoneBindImage=b;	}

	virtual	ExeResult	ExecuteInitialAfterEditPrev	(int ExeID)	=0;
	virtual	ExeResult	ExecuteInitialAfterEdit		(int ExeID)	=0;
	virtual	ExeResult	ExecuteInitialAfterEditPost	(int ExeID)	=0;
	virtual	ExeResult	ExecuteStartByInspection	(int ExeID)	=0;
	virtual	ExeResult	ExecuteCaptured				(int ExeID,ListPhasePageLayerPack &CapturedList)	=0;
	virtual	ExeResult	ExecutePreAlignment			(int ExeID)	=0;
	virtual	ExeResult	ExecuteAlignment			(int ExeID)	=0;
	virtual	ExeResult	ExecutePreProcessing		(int ExeID)	=0;
	virtual	ExeResult	ExecuteProcessing			(int ExeID)	=0;
	virtual	ExeResult	ExecuteProcessingRevived	(int ExeID)	=0;
	virtual	ExeResult	ExecutePostProcessing		(int ExeID)	=0;
	virtual	ExeResult	ExecutePreScanning			(int ExeID)	=0;
	virtual	ExeResult	ExecuteScanning				(int ExeID)	=0;
	virtual	ExeResult	ExecutePostScanning			(int ExeID)	=0;

	virtual	void	ClearResult(void)	=0;
};

class	ResultBasePhase
{
public:
	int32				AllocPageNumb;
	ResultInPageRoot	**PageData;
	ResultBaseForAlgorithmRoot	*Parent;
	AlgorithmInPageInOnePhase	*AlgoPointer;
	int32				PhaseCode;

	explicit	ResultBasePhase(int phaseCode ,ResultBaseForAlgorithmRoot *parent);
	virtual	~ResultBasePhase(void);

	bool	Initial(ResultBaseForAlgorithmRoot *p);
	void	Release(void);
	virtual	bool	Reallocate(int newPageNumb ,int newLayerNumb);
	virtual	bool	InsertPage(int IndexPage);	//Create page before Indexed page
	virtual	bool	RemovePage(int IndexPage);

	void	SetPhaseCode(int phase)			{	PhaseCode=phase;	}
	int32	GetPhaseCode(void)		const	{	return PhaseCode;	}

	void	InitialInspection(ResultBaseForAlgorithmRoot *p);
	bool	GatherResult(bool3 &OK,bool DependOnPageMode=false)	const;
	bool	GatherResult(int page ,bool3 &OK)	const;
	bool	GatherResult(int page ,NPListPack<ResultPosInfo> &RContainer,bool3 &OK)			const;
	void	MoveMerge(ResultBaseForAlgorithmRoot *p,ResultBasePhase &dst);
	void	BuildNGImages(int ImageW ,int ImageH ,int Bevel ,NPListPack<TmpNGRectClass> *TmpRect,ErrorGroupPack SpecializedGroup[]);
	void	BuildNGImages(int ImageW ,int ImageH ,int Bevel ,TmpNGDim TmpRectDim[],ErrorGroupPack SpecializedGroup[]);
	int		GetNGCount(void)		const;
	int		GetNGPointCount(void)	const;
	void	BindNGAreaListContainer(int localpage,NGAreaListContainer &List);
	ResultInPageRoot	*GetPageData(int page)	const{	return (PageData!=0)?PageData[page]:NULL;	}
	LayersBase	*GetLayersBase(void)	const;

	bool	Save(ResultBaseForAlgorithmRoot *p,QIODevice *file);
	bool	Load(ResultBaseForAlgorithmRoot *p,QIODevice *file);

	void	SetResultMarkForLearning(int page);
	void	ReviveResult(LearningImage *c);
	void	CalcNGCounterAgain(void);
	void	SetCurentCalcDone(bool b);
	void	ClearResult(void);

	ExeResult	ExecuteInitialAfterEditPrev	(int ExeID,AlgorithmBase *Base,ExecuteInitialAfterEditInfo &EInfo);
	ExeResult	ExecuteInitialAfterEdit		(int ExeID,AlgorithmBase *Base,ExecuteInitialAfterEditInfo &EInfo);
	ExeResult	ExecuteInitialAfterEditPost	(int ExeID,AlgorithmBase *Base,ExecuteInitialAfterEditInfo &EInfo);
	ExeResult	ExecuteStartByInspection	(int ExeID,AlgorithmBase *Base);
	ExeResult	ExecuteCaptured				(int ExeID,AlgorithmBase *Base,ListPhasePageLayerPack &CapturedList);
	ExeResult	ExecutePreAlignment			(int ExeID,AlgorithmBase *Base);
	ExeResult	ExecuteAlignment			(int ExeID,AlgorithmBase *Base);
	ExeResult	ExecutePreProcessing		(int ExeID,AlgorithmBase *Base);
	ExeResult	ExecuteProcessing			(int ExeID,AlgorithmBase *Base);
	ExeResult	ExecuteProcessingRevived	(int ExeID,AlgorithmBase *Base);
	ExeResult	ExecutePostProcessing		(int ExeID,AlgorithmBase *Base);
	ExeResult	ExecutePreScanning			(int ExeID,AlgorithmBase *Base);
	ExeResult	ExecuteScanning				(int ExeID,AlgorithmBase *Base);
	ExeResult	ExecutePostScanning			(int ExeID,AlgorithmBase *Base);

	int		GetPointerListOfResultPosList(FlexArea &OverlapArea ,ResultPosList **RetDim ,int MaxCount);
};


class	ResultBaseForAlgorithmRoot : public NPList<ResultBaseForAlgorithmRoot> , public ServiceForLayers
{
	LogicDLL			*LogicDLLPoint;
	ResultInspection	*Parent;
	ResultBasePhase		**PageDataPhase;
	int32				AllocPhaseNumb;
public:
	explicit	ResultBaseForAlgorithmRoot(LogicDLL *parent);
	virtual	~ResultBaseForAlgorithmRoot(void);

	virtual	ResultInPageRoot	*CreatePage(int phase ,int page)=0;
	virtual	ResultBaseForAlgorithmRoot	*CreateResultBaseForAlgorithm(void)=0;

	virtual	bool	Initial(void);
	virtual	void	Release(void);
	virtual	bool	Reallocate(int newPhaseNumb , int newPageNumb ,int newLayerNumb);
	virtual	bool	Reallocate(int newPhaseNumb);
	virtual	bool	RemovePhase(int RemovedPhaseCode);
	virtual	bool	InsertPage(int IndexPage);	//Create page before Indexed page
	virtual	bool	RemovePage(int IndexPage);

	//virtual	ResultInPageRoot	*GetPageData(int page);
	virtual	void	GetAlgorithm(QString &DLLRoot,QString &DLLName);
    virtual	bool    Save(QIODevice *file);
    virtual	bool    Load(QIODevice *file);
    virtual	bool    SaveOnlyPage(QIODevice *file,int page);
    virtual	bool    LoadOnlyPage(QIODevice *file,int page);

	virtual	void	MoveMerge(ResultBaseForAlgorithmRoot &dst);
	virtual	void	InitialInspection(void);
	virtual	bool	DrawResult(int32 ShowFixedPhase
								,QPainter &PntFromIData ,QImage *IData 
								,int MovX ,int MovY ,double ZoomRate ,int localPage)=0;
	virtual	void	BuildNGImages(int ImageW ,int ImageH ,int Bevel ,NPListPack<TmpNGRectClass> **TmpRect,ErrorGroupPack SpecializedGroup[]);
	virtual	void	BuildNGImages(int ImageW ,int ImageH ,int Bevel ,TmpNGDim **TmpRectDim,ErrorGroupPack SpecializedGroup[]);
	virtual	void	BindNGAreaListContainer(int localpage,NGAreaListContainer &List);
	virtual	void	BindNGAreaListContainer(int phase ,int localpage,NGAreaListContainer &List);

	ResultDLLBaseRoot	*GetResultDLLBase(void)	const	;
	LogicDLL			*GetLogicDLL(void)	const	{	return LogicDLLPoint;	}
	int					GetLibType(void)	const;
	ResultInspection	*GetParent(void)	const	{	return Parent;	}
	void	SetParent(ResultInspection	*parent){	Parent=parent;	}
	ResultBasePhase		*GetPageDataPhase(int phase)const	{	return (0<=phase && phase<AllocPhaseNumb)?PageDataPhase[phase]:NULL;	}
	AlgorithmBase		*GetAlgorithm(void)			const;

	virtual	int		GetNGCount(void);
	virtual	int		GetNGPointCount(void);
	virtual	ResultInspection	*GetResultInspection(void)	const	{	return Parent;	}
	void	SetCurentCalcDone(bool b);

	virtual	ExeResult	ExecuteInitialAfterEditPrev	(int ExeID,AlgorithmBase *Base ,ExecuteInitialAfterEditInfo &EInfo);
	virtual	ExeResult	ExecuteInitialAfterEdit		(int ExeID,AlgorithmBase *Base ,ExecuteInitialAfterEditInfo &EInfo);
	virtual	ExeResult	ExecuteInitialAfterEditPost	(int ExeID,AlgorithmBase *Base ,ExecuteInitialAfterEditInfo &EInfo);
	virtual	ExeResult	ExecuteStartByInspection	(int ExeID,AlgorithmBase *Base);
	virtual	ExeResult	ExecuteCaptured				(int ExeID,AlgorithmBase *Base,ListPhasePageLayerPack &CapturedList);
	virtual	ExeResult	ExecutePreAlignment			(int ExeID,AlgorithmBase *Base);
	virtual	ExeResult	ExecuteAlignment			(int ExeID,AlgorithmBase *Base);
	virtual	ExeResult	ExecutePreProcessing		(int ExeID,AlgorithmBase *Base);
	virtual	ExeResult	ExecuteProcessing			(int ExeID,AlgorithmBase *Base);
	virtual	ExeResult	ExecuteProcessingRevived	(int ExeID,AlgorithmBase *Base);
	virtual	ExeResult	ExecutePostProcessing		(int ExeID,AlgorithmBase *Base);
	virtual	ExeResult	ExecutePreScanning			(int ExeID,AlgorithmBase *Base);
	virtual	ExeResult	ExecuteScanning				(int ExeID,AlgorithmBase *Base);
	virtual	ExeResult	ExecutePostScanning			(int ExeID,AlgorithmBase *Base);

	virtual	void	ExecuteInAllItems(void (*Func)(ResultInItemRoot *Item ,void *Something),void *Something)=0;
	virtual	void	ExecuteInAllItems(int phase ,void (*Func)(ResultInItemRoot *Item ,void *Something),void *Something)=0;

	void	SetResultMarkForLearning(int page);
	void	ReviveResult(LearningImage *c);
	void	CalcNGCounterAgain(void);
	int		GetPointerListOfResultPosList(FlexArea &OverlapArea ,ResultPosList **RetDim ,int MaxCount);

	bool	GatherResult(bool3 &OK,bool DependOnPhaseMode=true,bool DependOnPageMode=false)	const;
	bool	GatherResultInPhase(int phase,bool3 &OK)	const;
	bool	GatherResult(int page ,bool3 &OK)			const;
	bool	GatherResult(int page ,NPListPack<ResultPosInfo> &RContainer,bool3 &OK)	const;
	void	ClearResult(int phase);
};


class	NGImageContainerInPage final : public NPList<NGImageContainerInPage> , public ServiceForLayers
{
	NPListPack<NGImage>		NGImageData;
	ErrorGroupPack			ErrorGroupData;
	NPListPack<NGImage>		NGImageStockker;
	int		GlobalPage;
	bool	Compressed;
	NGImageContainerInPhase	*Parent;
public:
	QReadWriteLock	NGImageAccessor;
	QReadWriteLock	ErrorGroupAccessor;

public:
	explicit	NGImageContainerInPage(NGImageContainerInPhase *parent 
										,int globalPage,LayersBase *base)
							:ServiceForLayers(base),Parent(parent)
							{	GlobalPage=globalPage;	Compressed=false;	}
	NGImageContainerInPage(const NGImageContainerInPage &src);
	~NGImageContainerInPage(void);

	NGImageContainerInPage	&operator=(const NGImageContainerInPage &src);
	int		GetNGImageCount(void);
	int		GetGlobalPage(void)		const	{	return GlobalPage;	}
	void	SetGlobalPage(int page)			{	GlobalPage=page;	}

	virtual	bool    Save(QIODevice *file);
	virtual	bool    Save(FileThread *file);
    virtual	bool    Load(QIODevice *file,LayersBase *Base);

	void			AddNGImageData(NGImage *b);
	void			SetErrorGroupID(void);
	int				GetNGImageDataCount(void);
	NGImage			*GetNGImageDataFirst(void)	const;
	void			ClearNGImageData(void);
	void			CopyImageFromTarget(DataInPage *PData);
	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID);
	NGImageContainerInPhase	*GetParent(void)	const{	return Parent;	}

	int				GetErrorGroupDataCount(void)	const{	return ErrorGroupData.GetNumber();	}
	ErrorGroup		*GetErrorGroupDataFirst(void)	const{	return ErrorGroupData.GetFirst();	}
	ErrorGroupPack	&GetErrorGroupData(void)		{	return ErrorGroupData;				}
	void			AddErrorGroupData(ErrorGroup *a){	ErrorGroupData.AppendList(a);		}
	void			ClearErrorGroupData(void)		{	ErrorGroupData.RemoveAll();			}

	void			CompressImages(void);
	void			SetCompressedFlag(bool flag)			{	Compressed=flag;	}
	bool			IsDoneCompressed(void)			const	{	return Compressed;	}

	NGImage		*GetNGImageFromStockker(void);
};

class	NGImageContainerInPhase final : public NPList<NGImageContainerInPhase> , public ServiceForLayers
{
	int32	Phase;
	NPListPack<NGImageContainerInPage>	NGImageInPage;
	ResultInspection	*Parent;
public:
	explicit	NGImageContainerInPhase(ResultInspection *parent ,int phase ,LayersBase *base);
	NGImageContainerInPhase(const NGImageContainerInPhase &src);

	void	Initial(void);
	void	AppendListPageData(NGImageContainerInPage *a)	{	NGImageInPage.AppendList(a);	}
	int		GetNGImageCount(void)	const;
	int		GetPhaseCode(void)		const	{	return Phase;	}
	void	SetPhaseCode(int phase)			{	Phase=phase;	}
	NGImageContainerInPage	*GetNGImageInPage(int page);
	NGImageContainerInPhase	&operator=(const NGImageContainerInPhase &src);

	bool	InsertPage(int IndexPage);	//Create page before Indexed page
	bool	RemovePage(int IndexPage);

	void	ClearAll(void);
	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID);
	bool	IsResultOK(int page)			const;
	ResultInspection	*GetParent(void)	const	{	return Parent;	}

	bool	SaveNGImage(QIODevice *f ,int localPage);
	bool	SaveNGImage(const FlexArea &OverlappedArea
						,int offsetX ,int offsetY
						,QIODevice *f ,int localPage);
	bool	SaveOnlyPage(QIODevice *f,int page);
	bool	LoadOnlyPage(QIODevice *f,int page);

	bool	SaveNGImage(FileThread *f ,int localPage);
	bool	SaveNGImage(const FlexArea &OverlappedArea
						,int offsetX ,int offsetY
						,FileThread *f ,int localPage);
	bool	SaveOnlyPage(FileThread *f,int page);

	bool	IsDoneCompressed(void)	const;
	void	ClearAllErrorGroup(void);
};

struct	ReceivedResultCountsParam
{
	int32	Result;
	bool	TimeOutBreak;
	bool	MaxErrorBreak;
};

#pragma	pack(push,1)
class	ExecutedTime
{
public:
	DWORD	TM_ExecuteCaptured			;
	DWORD	TM_ExecutePreAlignment		;
	DWORD	TM_ExecuteAlignment			;
	DWORD	TM_ExecutePreProcessing		;
	DWORD	TM_ExecuteProcessing		;
	DWORD	TM_ExecuteProcessingRevived	;
	DWORD	TM_ExecutePostProcessing	;

	DWORD	TM_ExecutePreScanning		;
	DWORD	TM_ExecuteScanning			;
	DWORD	TM_ExecutePostScanning		;

	DWORD	TM_TotalProcessMilisec		;

	ExecutedTime(void);
	ExecutedTime(const ExecutedTime &src);

	ExecutedTime	&operator=(const ExecutedTime &src);
};
#pragma	pack(pop)

class	ResultInspectionPointerList : public NPList<class	ResultInspectionPointerList>
{
public:
	ResultInspection	*Pointer;

	ResultInspectionPointerList(void):Pointer(NULL){}

	void	SetPointer(ResultInspection *p)	{	Pointer=p;	}
};

class	ResultInspection : public ServiceForLayers
{
public:
	enum		CriticalErrorMode
	{
		_NoError				=0
		,_ErrorOverflowBuffer	=1
		,_ErrorOverrun			=2
		,_ErrorCantWrite		=3
	};

private:
	XDateTime	StartTimeForInspection;	//åüç∏äJénéûçè
	NPListPack<ResultBaseForAlgorithmRoot>	ResultBaseDim;
	QString		NGFileName;
	int32		IndexForNGFileName;
	DWORD		InspectionTimeMilisec;
	NPListPack<NGImageContainerInPhase>		NGImageInPhase;

	int64		InspectionID;
	int64		InspectionNumber;
	QString		IDStr;
	ReceivedResultCountsParam	*ReceivedResultCounts;
	int32						ReceivedResultCountsAllocated;
	bool		TimeOutBreak;
	bool		MaxErrorBreak;
	int32		OutputCode;		//êUï™êÊ	-1:ñ¢êUï™	1:ÇnÇj	2:ÇmÇf
	QString		DeliveredInfo;
	QString		InspectionBarcode;
	QByteArray	RemarkData;
	BoolList	CalcDoneByPhase;
	NPListPack<ResultInspectionPointerList>	ShadowChildren;
	ErrorGroupPack *SpecializedGroup;
	int				AllocatedSpecializedGroup;
	NPListPack<TmpNGRectClass>	**TmpRect;
	int				AllocatedTmpRect;

	CriticalErrorMode	CriticalError;
	volatile	int		PriorityCounter;
	bool		AliveTillPush;	//WriteResultThread::PutCurrentToStockÇ≈MoveResultÇ™é¿çsÇ≥ÇÍÇÈÇ‹Ç≈true
public:
	ExecutedTime			ExecTime;

	//THese are set in PutCurrentToStock function , Possible to change in ResultDLL
	QString					LotID;
	QString					LotName;
	int						MachineID;
	int						MasterCode;
	QString					MasterName;
	QString					Message;

public:
	explicit	ResultInspection(LayersBase *base);
	ResultInspection(const ResultInspection &src);
	virtual ~ResultInspection(void);

	bool	Initial(LogicDLLBaseClass *LBase);
	void	InitialForInspection(void);
	bool	Reallocate(int newPhaseNumb , int newPageNumb ,int newLayerNumb);
	bool	Reallocate(int newPhaseNumb);
	bool	RemovePhase(int RemovedPhaseCode);
	bool	InsertPage(int IndexPage);	//Create page before Indexed page
	bool	RemovePage(int IndexPage);

	void	Release(void);
	void	MoveResult(ResultInspection &CurrentRes);
	int		GetNGCount(void)		const;
	int		GetNGImageCount(void)	const;
	int		GetNGPointCount(void)	const;
	ResultBaseForAlgorithmRoot	*GetResultBaseForAlgorithm(AlgorithmBase *base)	const;
	ResultBaseForAlgorithmRoot	*GetResultBaseForAlgorithm(int LibType)			const;

	bool		IsFinished(void)	const;
	bool		BuildNGImages(void);
	//bool		BuildNGImages2(void);
	bool		SaveNGImage(QIODevice *f ,int localPage);
	bool		SaveNGImage(const FlexArea &OverlappedArea
							,int offsetX ,int offsetY
							,QIODevice *f ,int localPage);

	bool		SaveNGImage(FileThread *f ,int localPage);
	bool		SaveNGImage(const FlexArea &OverlappedArea
							,int offsetX ,int offsetY
							,FileThread *f ,int localPage);

	NGImageContainerInPhase	*GetNGImageInPhase(int phase);

	ResultDLLBaseRoot	*GetResultDLLBase(void)		const;

	void	SetResultReceivedFlag(int Page ,int64 resultCounts,bool TimeOutBreak,bool MaxErrorBreak);
	bool	IsResultOK(void)		const;
	bool	IsResultTimeOut(void)	const;
	bool	IsResultMaxError(void)	const;
	bool	GatherResult(bool3 &OK ,bool &MaxError , bool &TimeOver,bool DependOnPhaseMode,bool DependOnPageMode)	const;
	bool	GatherResultInPhase(int Phase,bool3 &OK ,bool &MaxError , bool &TimeOver)	const;
	bool	GatherResult(int page ,bool3 &OK ,bool &MaxError , bool &TimeOver)	const;
	bool	GatherResult(int page ,NPListPack<ResultPosInfo> &RContainer,bool3 &OK ,bool &MaxError , bool &TimeOver)	const;
	XDateTime	&GetStartTimeForInspection(void);
	void	SetStartTimeForInspect(const XDateTime &d);
	void	BindNGAreaListContainer(int localpage,NGAreaListContainer &List);
	void	BindNGAreaListContainer(int phase ,int localpage,NGAreaListContainer &List);
	bool	GetResultInPhases(IntList &PhaseCodes
							, bool &ResultOk)	const;

	void	ExecuteInAllItems(void (*Func)(ResultInItemRoot *Item ,void *Something),void *Something);
	void	ExecuteInAllItems(int phase,void (*Func)(ResultInItemRoot *Item ,void *Something),void *Something);

	bool	SaveWithoutPage(QIODevice *f);
	bool	LoadWithoutPage(QIODevice *f);
	bool	SaveOnlyPage(QIODevice *f,int page);
	bool	LoadOnlyPage(QIODevice *f,int page);

	virtual	ExeResult	ExecuteInitialAfterEdit		(int ExeID);
	virtual	ExeResult	StartByInspection(int ExeID);

	ResultBaseForAlgorithmRoot	*GetResultBaseDimFirst(void)	{	return ResultBaseDim.GetFirst();	}
	bool	GetAliveTillPush(void)		const	{	return AliveTillPush;	}
	void	SetAliveTillPush(bool b)			{	AliveTillPush=b;		}
	void	CopyInspectionAttr(LayersBase *Base);
	void	SetCurentCalcDone(bool b);

	void	SetPriorityCounter(int n)			{	PriorityCounter=n;		}
	int		GetPriorityCounter(void)	const	{	return PriorityCounter;	}

	void	ClearTimeOutBreak(void)				{	TimeOutBreak=false;		}
	bool	GetTimeOutBreak(void)		const	{	return TimeOutBreak;	}
	void	SetTimeOutBreak(bool b)				{	if(b==true)	{TimeOutBreak=b;	}	}
	bool	GetMaxErrorBreak(void)		const	{	return MaxErrorBreak;	}
	void	SetMaxErrorBreak(bool b)			{	MaxErrorBreak=b;		}
	int64	GetInspectionID(void)		const	{	return InspectionID;	}
	void	SetInspectionID(int64 n)			{	InspectionID=n;			}
	QString	GetIDStr(void)				const	{	return IDStr;			}
	void	SetIDStr(const QString &Str)		{	IDStr=Str;				}
	int64	GetInspectionNumber(void)	const	{	return InspectionNumber;	}
	void	SetInspectionNumber(int64 n)		{	InspectionNumber=n;		}
	const QByteArray	&GetRemarkData(void)	{	return RemarkData;		}

	CriticalErrorMode	GetCriticalError(void)	{	return CriticalError;	}
	void				SetCriticalError(CriticalErrorMode b){	CriticalError=b;	}

	int32	GetOutputCode(void)		const	{	return OutputCode;		}
	void	SetOutputCode(int32 c)			{	OutputCode=c;			}
	bool	IsDoneCompressed(void)	const;

	void	SetResultMarkForLearning(int page);
	void	ReviveResult(LearningImage *c);
	void	CalcNGCounterAgain(void);

	void	ResetCalcDone(void);
	void	SetCalcDone(int phase);
	bool	IsCalcDone(int phase)	const;
	bool	IsAllCalcDone(void)		const;

	int		GetPointerListOfResultPosList(FlexArea &OverlapArea ,ResultPosList **RetDim ,int MaxCount);
	void	SetDeliveredInfo(const QString &Info)	{		DeliveredInfo=Info;		}
	QString	GetDeliveredInfo(void)			const	{		return DeliveredInfo;	}

	void	SetInspectionBarcode(const QString &Info)	{		InspectionBarcode=Info;		}
	QString	GetInspectionBarcode(void)			const	{		return InspectionBarcode;	}

	QString		GetLotID(void)					const	{	return LotID;		}
	void		SetLotID(const QString &lotID)			{	LotID=lotID;		}
	QString		GetLotName(void)				const	{	return LotName;		}
	void		SetLotName(const QString &lotName)		{	LotName=lotName;	}

	void	ClearAllErrorGroup(void);
	void	ClearResult(int phase);

	void	AddRemark(const QString &Str);
	void	AddRemark(int N);
	void	ClearRemarkData(void);
	int		GetRemarkStr(BYTE Buff[],int MaxBuffLen);

	void	SetShadowResult(ResultInspection *child,int shadownumber);
	ResultInspection	*GetShadowResult(int shadownumber)	const;
};

class	ResultInspectionPointer : public NPList<ResultInspectionPointer>
{
public:
	ResultInspection *Res;
};
class	ResultInspectionPointerStock : public NPListPack<ResultInspectionPointer>
{
	QMutex	StockMutex;
public:
	void	AddPoint(ResultInspection *p);
	ResultInspection	*PopPointer(void);
};

class	GUIDirectMessage;

class	ResultDLLBaseRoot :  public ParamBaseForAlgorithm 
							,public IdentifiedClass
							,public ServiceForLayers
{
public:
	int		NGImageWidth;
	int		NGImageHeight;
	int		NGImageBevel;
	int		NGImageQuality;
	QString	PathNGImage;
	bool	NotSaved;

	explicit	ResultDLLBaseRoot(LayersBase *Base);

	QString	CreateNGFileNameForCommon(ResultInspection *Res);
	QString	CreateNGFileNameForSlaveWithDrive(int localPage,ResultInspection *Res);
	QString	CreateNGFileNameForSlaveMilisecWithDrive(int localPage,ResultInspection *Res ,int &Milisec);

	virtual void	Prepare(void){}

	virtual	void	TransmitDirectly(GUIDirectMessage *packet){}
	virtual	bool	OutputResultDirectly(int mode ,ResultInspection &Res,GUIDirectMessage *packet)	{	return true;	}

	void	CommandSaveToSlave(LayersBase *base ,ResultInspection *Res);

	virtual	bool		MakeExecuteInitialAfterEditInfo	(int ExeID ,ResultInspection *Res,ExecuteInitialAfterEditInfo &EInfo)	{	return true;	}
	virtual	ExeResult	ExecuteInitialAfterEditPrev	(int ExeID,ResultInspection *Res)	{	return _ER_true;	}
	virtual	ExeResult	ExecuteInitialAfterEdit		(int ExeID,ResultInspection *Res)	{	return _ER_true;	}
	virtual	ExeResult	ExecuteInitialAfterEditPost	(int ExeID,ResultInspection *Res)	{	return _ER_true;	}
	virtual	ExeResult	ExecuteStartByInspection	(int ExeID,ResultInspection *Res)	{	return _ER_true;	}
	virtual	ExeResult	ExecuteCaptured				(int ExeID,ResultInspection *Res,ListPhasePageLayerPack &CapturedList)	{	return _ER_true;	}
	virtual	ExeResult	ExecutePreAlignment			(int ExeID,ResultInspection *Res)	{	return _ER_true;	}
	virtual	ExeResult	ExecuteAlignment			(int ExeID,ResultInspection *Res)	{	return _ER_true;	}
	virtual	ExeResult	ExecutePreProcessing		(int ExeID,ResultInspection *Res)	{	return _ER_true;	}
	virtual	ExeResult	ExecuteProcessing			(int ExeID,ResultInspection *Res)	{	return _ER_true;	}
	virtual	ExeResult	ExecuteProcessingRevived	(int ExeID,ResultInspection *Res)	{	return _ER_true;	}
	virtual	ExeResult	ExecutePostProcessing		(int ExeID,ResultInspection *Res)	{	return _ER_true;	}
	virtual	ExeResult	ExecutePreScanning			(int ExeID,ResultInspection *Res)	{	return _ER_true;	}
	virtual	ExeResult	ExecuteScanning				(int ExeID,ResultInspection *Res)	{	return _ER_true;	}
	virtual	ExeResult	ExecutePostScanning			(int ExeID,ResultInspection *Res)	{	return _ER_true;	}
	virtual	ExeResult	ExecuteManageResult			(int ExeID,ResultInspection *Res)	{	return _ER_true;	}
};

class	ResultPkNgPacket : public GUIDirectMessage
{
public:
	bool3	Ok;
	bool	TimeOver;
	bool	MaxError;

	explicit	ResultPkNgPacket(LayersBase *base);
	explicit	ResultPkNgPacket(GUICmdPacketBase *base);

	ResultPkNgPacket	&operator=(const ResultPkNgPacket &src);
};
//=================================================================================================================
class	ResultHistry : public NPList<ResultHistry>
{
public:
	int32		MasterCode;
	int32		ClusterID;
	int32		Result;
	XDateTime	ResultTime;
	int64		InspectionID;
	QString		IDStr;
	bool		TimeOutBreak;
	bool		MaxErrorBreak;	
	bool		Written;
	int32		ProcessMilisec;

	ResultHistry(void);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
	ResultHistry	&operator=(const ResultHistry &src);
};

class	ResultCounterList : public NPList<ResultCounterList>
{
public:
	int32	Result;
	int		Count;

	ResultCounterList(void){	Result=0;	Count=0;	}
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
	ResultCounterList	&operator=(const ResultCounterList &src);
};

class	ResultHistryContainer : public NPListPack<ResultHistry>,public ServiceForLayers
{
	QReadWriteLock	lock;
	NPListPack<ResultCounterList>	ResultCounter;
public:
	explicit	ResultHistryContainer(LayersBase *_Base);

	int		GetCount(int32 result);
	int		GetAllCount(void)	;
	void	SetMaxCount(int count);

	void	AddHistry(int32 result 
					,const XDateTime &ResTime 
					,int64 inspectionID
					,const QString &IDStr
					,bool TimeOutBreak
					,bool MaxErrorBreak
					,int32 ProcessMilisec);
	void	SetWritten(const XDateTime &ResTime ,int64 inspectionID);
	bool	RemoveResult(const XDateTime &ResTime);

	ResultHistry *SetWritten(const XDateTime &ResTime);

	void	Reset(void);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
	ResultHistryContainer	&operator=(const ResultHistryContainer &src);
};


//=================================================================================================================

inline	void	ResultPosList::GetPosInTarget(ResultInItemRoot *parent,int &X, int &Y)	const
{
	if(parent!=NULL){
		X=Px+parent->GetAlignedX()+Rx;
		Y=Py+parent->GetAlignedY()+Ry;
	}
}
inline	void	ResultPosList::GetDxyInTarget(ResultInItemRoot *parent,int &Dx, int &Dy)	const
{
	if(parent!=NULL){
		Dx=parent->GetAlignedX()+Rx;
		Dy=parent->GetAlignedY()+Ry;
	}
}
class	CmdChangeResultLotInfo : public GUIDirectMessage
{
public:
	int		DeliveryNo;
	QString	LotID;
	QString	LotName;
	QString	Remark;

	explicit	CmdChangeResultLotInfo(LayersBase *base):GUIDirectMessage(base){	DeliveryNo=0;	}
};

//=================================================================================================================
#pragma	pack(push,1)
struct	ResultHeader
{
	int32	InspectionID;
	BYTE	Year;
	BYTE	Month;
	BYTE	Day;
	BYTE	Hour;
	BYTE	Minute;
	BYTE	Second;
	BYTE	MachineID;
	int32	MasterCode;
	int32	LotAutoCount;
	BYTE	PhaseNumb;
	BYTE	PageNumb;
	BYTE	Result;
	BYTE	RemarkData[256];
	int32	RemarkByte;
};

struct	NGIInfo
{
	int32	X,Y,W,H;
	int32	MX,MY;
	int32	IDX;
	int32	Index;
};

#pragma	pack(pop)

#endif
