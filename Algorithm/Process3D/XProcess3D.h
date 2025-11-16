#if	!defined(XProcess3D_h)
#define	XProcess3D_h


#include "XFlexArea.h"
#include "XGeneralFunc.h"
#include "XMainSchemeMemory.h"
#include "XDataInLayer.h"
#include "XDataModelPageLayerItem.h"
#include "XAlgorithmLibrary.h"
#include "XYCross.h"
#include "XStandardCommand.h"

#define	Process3DVersion	1


class   AlignmentInLayer;
class	XAlignmentArea;
class	Process3DLibrary;
class	Process3DBase;
class	Process3DItem;
class	Process3DInLayer;
class	Process3DInPage;
class	SetThresholdProcess3DInfo;


class	Process3DThreshold : public AlgorithmThreshold
{
public:
	double	BaseCycleDot;
	double	HeightPerShift;
	int		VFilterLength;
	double	LargeTilt;
	double	LargeFlatness;
	double	SmallFlatness;
	int		SmallAreaSize;

	Process3DThreshold(Process3DItem *parent);

	virtual	void	CopyFrom(const AlgorithmThreshold &src)	override;
	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const override;
	virtual	bool	Save(QIODevice *f)					override;
    virtual	bool	Load(QIODevice *f)					override;
    virtual	int		GetSize(void)	const override	{	return sizeof(this);	}
    
	virtual	void	FromLibrary(AlgorithmLibrary *src)	override;
	virtual	void	ToLibrary(AlgorithmLibrary *Dest)	override;
	virtual	void	MakeReportedTopics(ReportedTopicContainer &RetContainer)	const	override;
};

class   Process3DItem : public AlgorithmItemPLITemplate<Process3DInLayer,Process3DInPage,Process3DBase>
{
	BYTE	**BmpMap;
	int		XLen;
	int		XByte;
	int		YLen;
	int		MapXPos,MapYPos;
	int		MasterCx,MasterCy;

	int		BaseCycleDot;
	BYTE	*MultTable;
	int		A,AA;

	class   XYLinesP3D : public NPListSaveLoad<XYLinesP3D> ,public NPListPack<XYClass>
	{
	public:
		int	MinX,MinY,MaxX,MaxY;
		double coss ,sins, C;
		double	Px1,Py1,Px2,Py2;

		XYLinesP3D(void);

		virtual	bool	Save(QIODevice *f);
		virtual	bool	Load(QIODevice *f);
        bool    IsInclude(int x ,int y,double AreaLength=5);
        void    Rotate(double angle ,int cx ,int cy);
        bool    IsOverlapLine(int x1, int y1 ,int x2 ,int y2);
        bool    IsOverlapRectangle(int x1, int y1 ,int x2 ,int y2);
        void    MoveTo(int dx ,int dy);
        bool    GetXY(int &minx ,int &miny ,int &maxx ,int &maxy);
        void    GetCenter(int &cx ,int &cy);
        void    ChangeXY(XYData *outlineOffset ,int MaxPage,int maxlines);
        bool    IsValid(void);
		void    Regulate(void);

		int		GetDotCount(void){	return NPListPack<XYClass>::GetNumber();	}
		XYClass	*GetFirstDot(void){	return NPListPack<XYClass>::GetFirst();		}

        XYLinesP3D &operator=(Process3DItem::XYLinesP3D &src);

		void	DrawLines(QPainter &pnt ,double ZoomRate ,int movx ,int movy);

		void	CreateOneLine(BYTE **BmpMap , int XLen ,int YLen
											,int x ,int y);
		void	GetMinY(int &x ,int &y);
		void	GetMaxY(int &x ,int &y);
		double	GetDistance(int x,int y);
		bool	CalcInterpolationLine(void);
	};

	class	XYLineP3DContainer : public NPListPackSaveLoad<XYLinesP3D>
	{
	public:
		XYLineP3DContainer(void){}

		virtual	XYLinesP3D	*Create(void){	return new XYLinesP3D();	}
		void	CreateLines(BYTE **BmpMap , int XByte ,int YLen ,int MapXPos ,int MapYPos);	//Clear BmpMap inside
		void	CalcInterpolationLine(void);
		bool    Save(QIODevice  *file);
		bool    Load(QIODevice  *file);

		void	DrawLines(QPainter &pnt ,double ZoomRate ,int movx ,int movy);
		void    Regulate(void);
	};


	XYLineP3DContainer	LineContainer;
public:
	AlignmentPacket2D	*AVector;

	double	ResultLargeTile		;
	double	ResultLargeFlatness	;
	double	ResultSmallFlatness	;
public:

	Process3DItem(void);
	Process3DItem(FlexArea &area);
	virtual	~Process3DItem(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new Process3DItem();	}
	const	Process3DThreshold	*GetThresholdR(LayersBase *base=NULL){	return (const Process3DThreshold *)GetThresholdBaseReadable(base);	}
	Process3DThreshold			*GetThresholdW(LayersBase *base=NULL){	return (Process3DThreshold *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)	override{	return new Process3DThreshold(this);	}
	virtual	void	SetRefereneFrom(AlgorithmItemRoot *src,int OffsetX ,int OffsetY)	override;

    Process3DItem &operator=(Process3DItem &src);
	void	CopyThreshold(Process3DItem &src);
	void	CopyThresholdOnly(Process3DItem &src);
	void	CopyArea(Process3DItem &src);
	virtual	void	SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)	override;
	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
	virtual	void	DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)	override;

    virtual	bool    Save(QIODevice *file)	override;
    virtual	bool    Load(QIODevice *file,LayersBase *LBase)	override;

	virtual	ExeResult	ExecuteStartByInspection(int ExeID ,int ThreadNo,ResultInItemRoot *Res)	override;
	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual	ExeResult	ExecutePreProcessing	(int ExeID ,int ThreadNo,ResultInItemRoot *Res)	override;

private:
	void	MakeBitVLine(ImageBuffer &IBuff ,int BaseCycleDot,int mx,int my);

};

class   Process3DInLayer : public AlgorithmInLayerPLITemplate<Process3DItem,Process3DInPage,Process3DBase>
{
	friend class	Process3DItem;

public:
	Process3DInLayer(AlgorithmInPageRoot *parent);
	~Process3DInLayer(void);

	virtual	AlgorithmItemRoot		*CreateItem(int ItemClassType=0)	override
		{	
			Process3DItem	*a=new Process3DItem();	
			a->SetParent(this);
			return a;
		}
	virtual	bool		AppendItem(AlgorithmItemRoot *item)					override;
	virtual	bool		AppendItem(int Layer ,AlgorithmItemRoot *item)		override;
	virtual	bool		AppendItemFromLoad(AlgorithmItemRoot *item)			override;
	virtual	bool		AppendItem(AlgorithmItemRoot *item ,int64 itemID)	override;

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)		override;

	void	UndoSetIndependentItemNameDataCommand(QIODevice *f);
	void	MoveFromPipe(GeneralPipeInfo &Info);
private:
	void	CreatePickupBmpBuff(void);
};

class   Process3DInPage : public AlgorithmInPagePLITemplate<Process3DItem,Process3DInLayer,Process3DBase>
{

public:
	Process3DInPage(AlgorithmBase *parent);
	~Process3DInPage(void);

	virtual	AlgorithmInLayerPLI	*NewChild(AlgorithmInPageRoot *parent)	override{	return new Process3DInLayer(parent);	}
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

private:

};
class	Process3DBase	: public AlgorithmBase
{
public:
	QColor		Process3DNormal	;
	QColor		Process3DSelected	;
	QColor		Process3DActive	;

	QColor		BlockColor0;
	QColor		BlockColor1;
	QColor		BlockColor2;
	QColor		BlockColor3;
	QColor		BlockColor4;
	QColor		BlockColor5;
	QColor		BlockColor6;
	QColor		BlockColor7;
	int			OmitZoneDot;

	Process3DBase(LayersBase *Base);

	virtual	Process3DInPage	*NewChild(AlgorithmBase *parent)	override{	return(new Process3DInPage(parent));	}
	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)			override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	QString	GetDataText(void)			override{	return QString("Process3D");			}
	virtual	QString	GetDefaultFileName(void)	override{	return QString("ConfigProcess3D.dat");	}

	virtual	bool	GeneralDataRelease(int32 Command,void *data)			override;
	virtual	void	*GeneralDataCreate(int32 Command,void *reqData)			override;
	virtual	bool	GeneralDataLoad(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataSave(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataReply(int32 Command,void *data)				override;

	//virtual	bool	ShowPasteCreateWithShape(QByteArray &templateData)	override;

	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,ResultBaseForAlgorithmRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
};

//==================================================================================
#define	SetIndependentItemDataCommand_OnlyOne			1
#define	SetIndependentItemDataCommand_All				2
#define	Process3DHistogramListReqCommand				3
#define	Process3DHistogramListSendCommand				4
#define	Process3DReqThresholdReqCommand					5
#define	Process3DReqThresholdSendCommand				6
#define	Process3DReqTryThresholdCommand					7
#define	Process3DSendTryThresholdCommand				8
#define	Process3DReqChangeShiftCommand					9
#define	SetIndependentItemNameDataCommand_All			10
//==================================================================================

class	Process3DDrawAttr : public AlgorithmDrawAttr , public ServiceForLayers
{
public:
	QColor		BlockColor0;
	QColor		BlockColor1;
	QColor		BlockColor2;
	QColor		BlockColor3;
	QColor		BlockColor4;
	QColor		BlockColor5;
	QColor		BlockColor6;
	QColor		BlockColor7;

	Process3DDrawAttr(void):ServiceForLayers(NULL){}
	Process3DDrawAttr(LayersBase *Base,QColor ncol,QColor scol ,QColor acol);
	Process3DDrawAttr(LayersBase *Base
				, QColor ncol ,int ntranparentLevel
				, QColor scol ,int stranparentLevel
				, QColor acol ,int atranparentLevel
				, int ptranparentLevel
				, QColor &blockColor0
				, QColor &blockColor1
				, QColor &blockColor2
				, QColor &blockColor3
				, QColor &blockColor4
				, QColor &blockColor5
				, QColor &blockColor6
				, QColor &blockColor7);

	void	Initial(void);

	Process3DDrawAttr	&operator=(Process3DDrawAttr &src);
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

inline	Process3DDrawAttr	&Process3DDrawAttr::operator=(Process3DDrawAttr &src)
{
	AlgorithmDrawAttr::operator=(*((AlgorithmDrawAttr *)&src));
	ServiceForLayers::Copy(this);

	BlockColor0	=src.BlockColor0;
	BlockColor1	=src.BlockColor1;
	BlockColor2	=src.BlockColor2;
	BlockColor3	=src.BlockColor3;
	BlockColor4	=src.BlockColor4;
	BlockColor5	=src.BlockColor5;
	BlockColor6	=src.BlockColor6;
	BlockColor7	=src.BlockColor7;
	return *this;
}
inline	bool	Process3DDrawAttr::Save(QIODevice *f)
{
	return true;
}
inline	bool	Process3DDrawAttr::Load(QIODevice *f)
{
	return true;
}


//==========================================================================
class	Process3DInfoList : public NPList<Process3DInfoList>
{
public:
	int		LibID;
	int		GlobalPage;
	int		Layer;
	int		ItemID;
	int		x1,y1,x2,y2;
	QString	ItemName;

	int		GetLibID(void){		return LibID;	}
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

inline	bool	Process3DInfoList::Save(QIODevice *f)
{
	if(::Save(f,LibID)==false)
		return false;
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,x1)==false)
		return false;
	if(::Save(f,y1)==false)
		return false;
	if(::Save(f,x2)==false)
		return false;
	if(::Save(f,y2)==false)
		return false;
	if(::Save(f,ItemName)==false)
		return false;

	return true;
}
inline	bool	Process3DInfoList::Load(QIODevice *f)
{
	if(::Load(f,LibID)==false)
		return false;
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,x1)==false)
		return false;
	if(::Load(f,y1)==false)
		return false;
	if(::Load(f,x2)==false)
		return false;
	if(::Load(f,y2)==false)
		return false;
	if(::Load(f,ItemName)==false)
		return false;

	return true;
}


//==================================================================================

class	Process3DThresholdReq
{
public:
	int32	GlobalPage;
	int32	Layer;
	int		BlockItemID;
	bool	Mastered;
	int32	Dx,Dy;

	Process3DThresholdReq(void);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	Process3DThresholdSend
{
public:
	int32	GlobalPage;
	int32	Layer;
	int		BlockItemID;
	bool	Mastered;
	int32	Dx,Dy;

	double	BaseCycleDot;
	double	HeightPerShift;
	double	LargeTilt;
	double	LargeFlatness;
	double	SmallFlatness;
	int		SmallAreaSize;

	Process3DThresholdSend(void);

	void	ConstructList(Process3DThresholdReq *reqPacket,Process3DBase *Base);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	Process3DReqTryThreshold
{
public:
	int32	GlobalPage;
	int32	Layer;
	int		BlockItemID;	
	Process3DItem	Threshold;

	Process3DReqTryThreshold(void);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f,LayersBase *LBase);
};

class	Process3DSendTryThreshold : public AddedDataClass
{
public:
	ResultInItemRoot	*Result;
	double	ResultLargeTile		;
	double	ResultLargeFlatness	;
	double	ResultSmallFlatness	;

	Process3DSendTryThreshold(void);
	~Process3DSendTryThreshold(void);

	void	ConstructList(Process3DReqTryThreshold *reqPacket,Process3DBase *Base);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};


class	CmdGetProcess3DLibraryListPacket : public GUIDirectMessage
{
public:
	int			LibFolderID;
	AlgorithmLibraryListContainer	AList;
	CmdGetProcess3DLibraryListPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetProcess3DLibraryListPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetProcess3DLibraryNamePacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryListContainer	AList;
	CmdGetProcess3DLibraryNamePacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetProcess3DLibraryNamePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateTempProcess3DLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdCreateTempProcess3DLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateTempProcess3DLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdClearProcess3DLibraryPacket: public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdClearProcess3DLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdClearProcess3DLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdInsertProcess3DLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdInsertProcess3DLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdInsertProcess3DLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdUpdateProcess3DLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdUpdateProcess3DLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdUpdateProcess3DLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdLoadProcess3DLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	bool				Success;
	CmdLoadProcess3DLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdLoadProcess3DLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdDeleteProcess3DLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdDeleteProcess3DLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdDeleteProcess3DLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateTempProcess3DItemPacket : public GUIDirectMessage
{
public:
	Process3DItem	*Point;
	CmdCreateTempProcess3DItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateTempProcess3DItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateByteArrayFromProcess3DItemPacket : public GUIDirectMessage
{
public:
	Process3DItem	*Point;
	QByteArray	Buff;
	CmdCreateByteArrayFromProcess3DItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateByteArrayFromProcess3DItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdAddProcess3DItemPacket : public GUIDirectMessage
{
public:
	FlexArea	Area;
	int			Layer;
	QString		ItemName;
	int			LibID;

	CmdAddProcess3DItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdAddProcess3DItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdLoadProcess3DItemPacketFromByteArray : public GUIDirectMessage
{
public:
	Process3DItem	*BItemPoint;
	QByteArray	Buff;
	CmdLoadProcess3DItemPacketFromByteArray(LayersBase *base):GUIDirectMessage(base){}
	CmdLoadProcess3DItemPacketFromByteArray(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdModifySelectedProcess3DFromByteArray : public GUIDirectMessage
{
public:
	QByteArray	Buff;
	int			LocalPage;
	CmdModifySelectedProcess3DFromByteArray(LayersBase *base):GUIDirectMessage(base){}
	CmdModifySelectedProcess3DFromByteArray(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetOneSelectedItem : public GUIDirectMessage
{
public:
	QByteArray	Buff;
	bool		ExistSelected;
	CmdGetOneSelectedItem(LayersBase *base):GUIDirectMessage(base){}
	CmdGetOneSelectedItem(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdProcess3DInfoListPacket: public GUIDirectMessage
{
public:
	NPListPack<Process3DInfoList>	*Process3DInfos;
	CmdProcess3DInfoListPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdProcess3DInfoListPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetProcess3DFromList: public GUIDirectMessage
{
public:
	ListLayerAndID	CurrentItem;
	Process3DItem	*Process3DInfoOnMouse;

	CmdGetProcess3DFromList(LayersBase *base):GUIDirectMessage(base){}
	CmdGetProcess3DFromList(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdCreateProcess3DItem: public GUIDirectMessage
{
public:
	Process3DItem	*Process3D;
	CmdCreateProcess3DItem(LayersBase *base):GUIDirectMessage(base){	Process3D=NULL;	}
	CmdCreateProcess3DItem(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
//==========================================================================




#endif