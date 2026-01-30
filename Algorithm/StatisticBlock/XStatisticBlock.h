/*
 * Copyright (C) 2023
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */



#if	!defined(XSTATISTICBLOCK_H)
#define	XSTATISTICBLOCK_H

#include "XFlexArea.h"
#include "XMainSchemeMemory.h"
#include "XDataInLayer.h"
#include "XPropertyStatisticBlockPacket.h"
#include "XStandardCommand.h"

#define	StatisticBlockVersion	3

class   AlignmentInLayer;
class	XAlignmentArea;
class	StatisticBlockLibrary;
class	StatisticBlockBase;
class	StatisticBlockItem;

class	StatisticBlockThreshold : public AlgorithmThreshold
{
public:
	double	BrightWidthL;	//�Ђɑ΂��Ă̈Ñ��{��
	double	BrightWidthH;	//�Ђɑ΂��Ă̖����{��
	DWORD	OKDotL;			//�Ñ��n�j�h�b�g��
	DWORD	OKDotH;			//�����n�j�h�b�g��
	WORD	OKLengthL;		//�Ñ��ŁA���̒����ȉ��̎��n�j
	WORD	OKLengthH;		//�����ŁA���̒����ȉ��̎��n�j

	struct{
		bool	ModeEnabled			:1;
		bool	ModeAbsoluteBright	:1;
		bool	ModeNGCluster		:1;
		bool    ModeWhiteMask		:1;
		bool    ModeBlackMask		:1;
	}PointMove;

	enum{
		_FromUnknown	=0
		,_FromLibrary	=1
		,_FromManual	=2
		,_FromParts		=3
		,_FromMPA		=4
		,_FromCAD		=5
	}GeneratedOriginOld;

    WORD	AdjustBlack;    //�P�x�␳�̉�����
    WORD	AdjustWhite;    //�P�x�␳�̏�����

	//�c���E���k
	bool	UseMorphology;		//�c���E���k�����邩�ǂ���
	bool	EliminateAcnode;	//�Ǘ��_�̏���
	WORD	DilationDotCount;	//�c�������h�b�g��
	WORD	ErosionDotCount;	//���k�����h�b�g��
	enum _MorphologyApplyTo{
		MAT_Both=0,
		MAT_DarkSideOnly=1,
		MAT_LightSideOnly=2
	}MorphologyApplyTo;

	StatisticBlockThreshold(StatisticBlockItem *parent);

	virtual	void	CopyFrom(const AlgorithmThreshold &src)	override;
	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const override;
	virtual	bool	Save(QIODevice *f)					override;
    virtual	bool	Load(QIODevice *f)					override;
    virtual	int		GetSize(void)	const override	{	return sizeof(this);	}

	virtual	void	FromLibrary(AlgorithmLibrary *src)	override;
	virtual	void	ToLibrary(AlgorithmLibrary *Dest)	override;
};

class   StatisticBlockItem : public AlgorithmItemPLI
{
public:
	AlignmentPacket2D	*AVector;

	double	Sigma;	//�v�Z���̒l
	double	Avr;	//�v�Z���̒l
	int		AreaDots;
	double	DegradeRate;

	StatisticBlockItem(void);
	StatisticBlockItem(FlexArea &area);
    virtual	~StatisticBlockItem(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new StatisticBlockItem();	}
    virtual	void	MoveTo(int dx ,int dy)	override;
	const	StatisticBlockThreshold	*GetThresholdR(LayersBase *base=NULL){	return (const StatisticBlockThreshold *)GetThresholdBaseReadable(base);	}
	StatisticBlockThreshold			*GetThresholdW(LayersBase *base=NULL){	return (StatisticBlockThreshold *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)	override{	return new StatisticBlockThreshold(this);	}
	virtual	void	SetRefereneFrom(AlgorithmItemRoot *src,int OffsetX ,int OffsetY)	override;

	virtual	AlgorithmItemPLI	&operator=(const AlgorithmItemRoot &src)	override;
    StatisticBlockItem &operator=(StatisticBlockItem &src);
	void	CopyThreshold(StatisticBlockItem &src);
	void	CopyThresholdOnly(StatisticBlockItem &src);

	virtual	void	SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)	override;
	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
	virtual	void	DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)	override;

    virtual	bool    Save(QIODevice *file)					override;
    virtual	bool    Load(QIODevice *file,LayersBase *LBase)	override;

	virtual	int		GetDrawPriprity(int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;	
	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual	ExeResult	ExecuteProcessing		(int ExeID ,int ThreadNo,ResultInItemRoot *Res)	override;
	void	CalcAvrSigma(int mx, int my
						,BYTE **DynamicMaskMap,int DynamicMaskMapXByte,int DynamicMaskMapYLen);

  private:

	bool    ExecuteProcessingInner(int ThreadNo,ResultInItemRoot *Res 
						  ,int mx ,int my
						  ,double BrightWidthL ,double BrightWidthH
						  ,int OKDotL ,int OKDotH
						  ,WORD	OKLengthL ,WORD	OKLengthH
						  ,BYTE **DynamicMaskMap,int DynamicMaskMapXByte,int DynamicMaskMapYLen);

	bool	CheckOnNG(int mx,int my
				, double BrightWidthL ,double BrightWidthH
				, int OKDotL ,int OKDotH
				,int &SumL,int &SumH
				,NPListPack<ResultPosList> &PosList
				,WORD	OKLengthL
				,WORD	OKLengthH
				,short &Error
				,BYTE **DynamicMaskMap,int DynamicMaskMapXByte,int DynamicMaskMapYLen);

	void	CheckOnNGInner1(int dx ,int dy
							,int LLevel ,int HLevel
							,BYTE *pMapL ,BYTE *pMapH
							,int Lx ,int Ly ,int LByte,int starty
							,int &LSum ,int &HSum
							,BYTE **DynamicMaskMap,int DynamicMaskMapXByte,int DynamicMaskMapYLen);

	int  AnalyzeNGHole(int dx ,int dy,int x ,int y
							, BYTE *NGBmp ,int NGBmpX ,int NGBmpY
							,int &Cx ,int &Cy
							,int OKDot,int &Sum
							,int &NGLen);
	static	void  SearchAnalyzeNGHole(struct AnalyzeNGHoleClass *LData,int x ,int y ,BYTE *B);
	static	void  SearchAnalyzeNGHole2(struct AnalyzeNGHoleClass *LData,int x ,int y ,BYTE *B);

	WORD	CalcCenterBright(ImageBuffer &IBuff ,int mx ,int my);

	void	DilateAndErode(BYTE *pMap, BYTE **pTempMap2D1, BYTE **pTempMap2D2, int Lx, int Ly);
};

class	StatisticBlockLimitedMask : public AlgorithmItemPLI
{
public:
	StatisticBlockLimitedMask(void){}
	
    virtual	bool    Save(QIODevice *file)					override;
    virtual	bool    Load(QIODevice *file,LayersBase *LBase)	override;
	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
};

class   StatisticBlockInLayer : public AlgorithmInLayerPLI
{
	friend class	StatisticBlockItem;

	BYTE	**PickupBmp;
	int		PickupBmpXByte;
	int		PickupBmpYLen;
	IntList	CommonMoveIDList;
	BYTE	**DynamicMaskMap;
	int		DynamicMaskMapXByte;
	int		DynamicMaskMapYLen;

  public:
	StatisticBlockInLayer(AlgorithmInPageRoot *parent);
	~StatisticBlockInLayer(void);

	virtual	AlgorithmItemRoot		*CreateItem(int ItemClassType)	override
		{	
			StatisticBlockItem	*a=new StatisticBlockItem();	
			a->SetParent(this);
			return a;
		}
    virtual	bool			Save(QIODevice *f)	override;
    virtual	bool			Load(QIODevice *f)	override;

	//const BYTE	**GetMaskBitmap(StatisticBlockLibrary &LibData);

	virtual	ExeResult	ExecuteProcessing		(int ExeID ,ResultInLayerRoot *Res)	override;

	void	PickupTest(StatisticBlockLibrary &LibData);
	void	GenerateStatisticBlocks(StatisticBlockLibrary *LibDim[],int LibDimNumb);
	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
private:
	void	CreatePickupBmpBuff(void);
};

class   StatisticBlockInPage : public AlgorithmInPagePLI
{
public:
	StatisticBlockInPage(AlgorithmBase *parent):AlgorithmInPagePLI(parent){}
	virtual	StatisticBlockInLayer	*NewChild(AlgorithmInPageRoot *parent)	override	{	return(new StatisticBlockInLayer(parent));	}
	void	PickupTest(IntList &LayerList ,StatisticBlockLibrary &LibData);
	void	GenerateStatisticBlocks(IntList &LayerList, StatisticBlockLibrary *LibDim[],int LibDimNumb);
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
};

class	StatisticBlockBase	: public AlgorithmBase
{
public:
	QColor		ColorPickup;
	QColor		ColorBlockNormal	;
	QColor		ColorBlockSelected	;
	QColor		ColorBlockActive	;

	QColor		BlockColor0;
	QColor		BlockColor1;
	QColor		BlockColor2;
	QColor		BlockColor3;
	QColor		BlockColor4;
	QColor		BlockColor5;
	QColor		BlockColor6;
	QColor		BlockColor7;
	int			OmitZoneDot;
	double		MinDotRate;
	double		SideDegradeRate;
	int			ExcludedL;
	int			ExcludedH;

	StatisticBlockBase(LayersBase *Base);

	virtual	StatisticBlockInPage	*NewChild(AlgorithmBase *parent)override{	return(new StatisticBlockInPage(parent));	}
	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)				override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)		override;
	virtual	QString	GetDataText(void)			override{	return QString("StatisticBlock");				}
	virtual	QString	GetDefaultFileName(void)	override{	return QString("ConfigStatisticBlock.dat");		}

	virtual	bool	GeneralDataRelease(int32 Command,void *data)			override;
	virtual	void	*GeneralDataCreate(int32 Command,void *reqData)			override;
	virtual	bool	GeneralDataLoad(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataSave(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataReply(int32 Command,void *data)				override;

	virtual	bool	ShowPasteCreateWithShape(QByteArray &templateData,int Layer)	override;
};

//==================================================================================
class	StatisticBlockHistogramListReq
{
public:
	int32	GlobalPage;
	int32	Layer;
	int		StatisticBlockItemID;
	bool	Mastered;
	int32	Dx,Dy;

	StatisticBlockHistogramListReq(void);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	StatisticBlockHistogramListSend
{
public:
	int32	GlobalPage;
	int32	Layer;
	int		StatisticBlockItemID;
	bool	Mastered;
	int32	Dx,Dy;
	int		ListMaster[256];
	int		ListTarget[256];

	StatisticBlockHistogramListSend(void);

	void	ConstructList(StatisticBlockHistogramListReq *reqPacket,StatisticBlockBase *Base);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	StatisticBlockThresholdReq
{
public:
	int32	GlobalPage;
	int32	Layer;
	int		StatisticBlockItemID;
	bool	Mastered;
	int32	Dx,Dy;

	StatisticBlockThresholdReq(void);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	StatisticBlockThresholdSend
{
public:
	int32	GlobalPage;
	int32	Layer;
	int		StatisticBlockItemID;
	bool	Mastered;
	int32	Dx,Dy;
	double	Avr;
	double	Sigma;
	double	BrightWidthL;		//�����̈Ñ��P�x��
	double	BrightWidthH;		//�����̖����P�x��


	StatisticBlockThresholdSend(void);

	void	ConstructList(StatisticBlockThresholdReq *reqPacket,StatisticBlockBase *Base);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};


class	StatisticBlockReqTryThreshold
{
public:
	int32	GlobalPage;
	int32	Layer;
	int		StatisticBlockItemID;	
	StatisticBlockItem	Threshold;

	StatisticBlockReqTryThreshold(void);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f,LayersBase *LBase);
};

class	StatisticBlockSendTryThreshold : public AddedDataClass
{
public:
	int		NGDotInDark;
	int		NGDotInBright;
	int		ResultMoveDx;
	int		ResultMoveDy;

	StatisticBlockSendTryThreshold(void);

	void	ConstructList(StatisticBlockReqTryThreshold *reqPacket,StatisticBlockBase *Base);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	StatisticBlockChangeShift
{
public:
	int32	GlobalPage;
	int32	Layer;
	int		StatisticBlockItemID;
	int32	Dx,Dy;

	StatisticBlockChangeShift(void){}

	void	Reflect(StatisticBlockBase *Base);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};


#define	SetIndependentItemDataCommand_OnlyOne	1
#define	SetIndependentItemDataCommand_All		2
#define	StatisticBlockHistogramListReqCommand	3
#define	StatisticBlockHistogramListSendCommand	4
#define	StatisticBlockReqThresholdReqCommand	5
#define	StatisticBlockReqThresholdSendCommand	6
#define	StatisticBlockReqTryThresholdCommand	7
#define	StatisticBlockSendTryThresholdCommand	8
#define	StatisticBlockReqChangeShiftCommand		9

//===================================================================================

class	CmdGetStatisticBlockLibraryListPacket : public GUIDirectMessage
{
public:
	int			LibFolderID;
	AlgorithmLibraryListContainer	AList;
	CmdGetStatisticBlockLibraryListPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetStatisticBlockLibraryListPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetStatisticBlockLibraryNamePacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryListContainer	AList;
	CmdGetStatisticBlockLibraryNamePacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetStatisticBlockLibraryNamePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateTempStatisticBlockLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdCreateTempStatisticBlockLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateTempStatisticBlockLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdInsertStatisticBlockLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdInsertStatisticBlockLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdInsertStatisticBlockLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdUpdateStatisticBlockLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdUpdateStatisticBlockLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdUpdateStatisticBlockLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdLoadStatisticBlockLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdLoadStatisticBlockLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdLoadStatisticBlockLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdDeleteStatisticBlockLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdDeleteStatisticBlockLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdDeleteStatisticBlockLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdPickupTestStatisticBlockPacket : public GUIDirectMessage
{
public:
	//StatisticBlockLibrary	*LibPoint;
	AlgorithmLibraryLevelContainer	*LibPoint;
	IntList			LayerList;
	int				Page;

	CmdPickupTestStatisticBlockPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdPickupTestStatisticBlockPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGenerateStatisticBlockPacket : public GUIDirectMessage
{
public:
	IntList		LibList;
	IntList		LayerList;
	int			Page;
	CmdGenerateStatisticBlockPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGenerateStatisticBlockPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateTempStatisticBlockItemPacket : public GUIDirectMessage
{
public:
	StatisticBlockItem	*Point;
	CmdCreateTempStatisticBlockItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateTempStatisticBlockItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateByteArrayFromStatisticBlockItemPacket : public GUIDirectMessage
{
public:
	StatisticBlockItem	*Point;
	QByteArray	Buff;
	CmdCreateByteArrayFromStatisticBlockItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateByteArrayFromStatisticBlockItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdAddByteStatisticBlockItemPacket : public GUIDirectMessage
{
public:
	QByteArray	Buff;
	FlexArea	Area;
	IntList		LayerList;
	int			LocalPage;
	CmdAddByteStatisticBlockItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdAddByteStatisticBlockItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdLoadStatisticBlockItemPacketFromByteArray : public GUIDirectMessage
{
public:
	StatisticBlockItem	*BItemPoint;
	QByteArray	Buff;
	CmdLoadStatisticBlockItemPacketFromByteArray(LayersBase *base):GUIDirectMessage(base){}
	CmdLoadStatisticBlockItemPacketFromByteArray(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdModifySelectedStatisticBlockFromByteArray : public GUIDirectMessage
{
public:
	QByteArray	Buff;
	IntList		LayerList;
	int			LocalPage;
	CmdModifySelectedStatisticBlockFromByteArray(LayersBase *base):GUIDirectMessage(base){}
	CmdModifySelectedStatisticBlockFromByteArray(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetOneSelectedItem : public GUIDirectMessage
{
public:
	QByteArray	Buff;
	bool		ExistSelected;
	CmdGetOneSelectedItem(LayersBase *base):GUIDirectMessage(base){}
	CmdGetOneSelectedItem(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdClearTestStatisticBlockPacket: public GUIDirectMessage
{
public:
	CmdClearTestStatisticBlockPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdClearTestStatisticBlockPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};



class	CmdStatisticBlockInfoListPacket: public GUIDirectMessage
{
public:
	int		LocalPage;
	NPListPack<StatisticBlockInfoList>	*StatisticBlockInfos;

	CmdStatisticBlockInfoListPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdStatisticBlockInfoListPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetStatisticBlockFromList: public GUIDirectMessage
{
public:
	ListLayerAndID	CurrentItem;
	int				LocalPage;
	StatisticBlockItem	*StatisticBlockInfoOnMouse;
		
	CmdGetStatisticBlockFromList(LayersBase *base):GUIDirectMessage(base){}
	CmdGetStatisticBlockFromList(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdCreateStatisticBlockItem: public GUIDirectMessage
{
public:
	StatisticBlockItem	*StatisticBlock;
	CmdCreateStatisticBlockItem(LayersBase *base):GUIDirectMessage(base){	StatisticBlock=NULL;	}
	CmdCreateStatisticBlockItem(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){	StatisticBlock=NULL;	}
};


#endif