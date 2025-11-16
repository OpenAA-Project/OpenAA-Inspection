#if	!defined(XDISPLAYIMAGEPACKET_H)
#define	XDISPLAYIMAGEPACKET_H

#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
//#include "mtToolButtonWithBalloon.h"
//#include "mtPushButtonWithBalloon.h"
//#include "mtToolButtonColored.h"
#include "mtFrameDraw.h"
#include "XAlgorithmLibrary.h"
#include "XAlgorithmCommon.h"
#include "XDisplayImage.h"
#include "XGUIFormBase.h"
#include "swap.h"

class	AlgorithmLibraryListContainer;

class	GUICmdReqBmp : public GUICmdPacketBase	//画像表示用ビットマップ要求コマンド
{
public:
#pragma	pack(push)
#pragma	pack(1)
	struct	GUIReqBmpStruct
	{
		DisplayImage::DisplayType	DType;
		int32	Gx1;
		int32	Gy1;
		int32	Gx2;
		int32	Gy2;
		int32	Dx1;
		int32	Dy1;
		int32	Dx2;
		int32	Dy2;
		double	ZoomRate;
		double	Yz;		//Normal : 1.0
		int32	MovX;
		int32	MovY;
		int32	GlobalPage;
		bool	RedCircleMode;

		int32	ShowFixedPhase;	//-1: Any phase (current phase)
		int32	TransparentLevelInBitBuff;
		bool	ShowNGMarkInTarget;
		bool	RepaintContinuously;
		int32	MasterNo;

		GUIReqBmpStruct();
	}Data;
#pragma	pack(pop)

	IntList	LayerList;

	GUICmdReqBmp(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,DisplayImage::DisplayType dtype ,int globalPage=-1);
	GUICmdReqBmp(LayersBase *Base,QString className ,const QString &emitterRoot ,const QString &emitterName,DisplayImage::DisplayType dtype ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

inline	GUICmdReqBmp::GUIReqBmpStruct::GUIReqBmpStruct()
{
	DType	=DisplayImage::__NoImage;
	Gx1		=0;
	Gy1		=0;
	Gx2		=0;
	Gy2		=0;
	Dx1		=0;
	Dy1		=0;
	Dx2		=0;
	Dy2		=0;
	ZoomRate=0.0;
	Yz		=0;		//Normal : 1.0
	MovX	=0;
	MovY	=0;
	GlobalPage=0;
	RedCircleMode	=false;
	MasterNo	=0;

	ShowFixedPhase	=-1;	//-1: Any phase (current phase)
	TransparentLevelInBitBuff=0;
	ShowNGMarkInTarget	=false;
	RepaintContinuously	=false;
}

class	GUICmdSendBmp : public GUICmdPacketBase	//画像表示用ビットマップ送信コマンド
{
public:
	QImage		*IData;
	QImage		*NGData;
	QPainter	*PntFromIData;
	QPainter	*PntFromNGData;
	bool		ShowNGMarkInTarget;
	bool		RetNGData;
	int			MasterNo;

	GUICmdSendBmp(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);
	GUICmdSendBmp(LayersBase *Base,QString className ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);
	~GUICmdSendBmp(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}	

	bool	MakeImage(DisplayImage::DisplayType dtype 
					 ,int Gx1,int Gy1 ,int Gx2,int Gy2
					 ,int Dx1,int Dy1 ,int Dx2,int Dy2
					 ,int MovX,int MovY, double ZoomRate ,double Yz
					 ,int localPage
					 ,LayersBase &LocalLBase
					 ,int MasterNo
					 ,IntList &LayerList
					 ,bool RedCircleMode
					 ,int32 ShowFixedPhase
					 ,int32 TransparentLevelInBitBuff
					 ,bool ShowNGMarkInTarget
					 ,bool RepaintContinuously);
	bool	MakeImageOneLayer( DisplayImage::DisplayType dtype 
							 ,QImage *IData , DataInPage *P ,int Layer , QColor LColor
							 ,int MasterNo
							 ,int LGx,int LGy
							 ,int Dx1,int Dy1
							 ,int DotPerLine ,int MaxLines
							, double ZoomRate
							, double Yz);
	bool	MakeImageMultiLayer( DisplayImage::DisplayType dtype 
								,IntList &LayerList
								,QImage *IData , DataInPage *P ,QColor LColor
								,int MasterNo
								,int LGx,int LGy
								,int Dx1,int Dy1
								,int DotPerLine ,int MaxLines
								, double ZoomRate
								, double Yz);
	bool	MakeImageBitLayer(QImage *IData , DataInPage *P
								,int LGx,int LGy
								,int Dx1,int Dy1
								,int DotPerLine ,int MaxLines
								, double ZoomRate ,double Yz);
};


//============================================================================================
class	GUICmdSyncDrawingMode : public GUICmdPacketBase	//同期描画コマンド
{
public:
	DisplayImage::__DrawingMode	DMode;
	int		localX,localY;
	QString	InstName;

	GUICmdSyncDrawingMode(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//============================================================================================
class	GUICmdReqPixelColor : public GUICmdPacketBase	//ピクセル座標の色（輝度）要求コマンド
{
public:
	int		LocalX;
	int		LocalY;
	DisplayImage::DisplayType	DType;
	int		MasterNo;

	GUICmdReqPixelColor(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,DisplayImage::DisplayType dtype,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


class	GUICmdSendPixelColor : public GUICmdPacketBase	//ピクセル座標の色（輝度）送信コマンド
{
public:
	QColor	Col;

	GUICmdSendPixelColor(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);
	~GUICmdSendPixelColor(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


//============================================================================================
class	GUICmdDrawColor : public GUICmdPacketBase	//任意形状を描画（色塗り）するコマンド
{
public:
	QColor					Col;
	FlexArea				Area;
	//mtFrameDraw::_ShapeData	CShape;
	DisplayImage::DisplayType	DType;
	int							MasterNo;

	GUICmdDrawColor(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,DisplayImage::DisplayType dtype ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//============================================================================================
class	GUICmdDrawDot : public GUICmdPacketBase	//点を描画するコマンド
{
public:
	QColor					Col;
	int						LocalX,LocalY;
	//mtFrameDraw::_ShapeData	CShape;
	DisplayImage::DisplayType	DType;
	int							MasterNo;

	GUICmdDrawDot(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,DisplayImage::DisplayType dtype ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//============================================================================================
class	CmdDrawImageRectPacket : public GUIDirectMessage	//矩形描画コマンド
{
public:
	int	Ux1,Uy1,Ux2,Uy2;
	CmdDrawImageRectPacket(LayersBase *base ,int ux1, int uy1 ,int ux2 ,int uy2)
		:GUIDirectMessage(base),Ux1(ux1),Uy1(uy1),Ux2(ux2),Uy2(uy2){}
	CmdDrawImageRectPacket(GUICmdPacketBase *gbase ,int ux1, int uy1 ,int ux2 ,int uy2)
		:GUIDirectMessage(gbase),Ux1(ux1),Uy1(uy1),Ux2(ux2),Uy2(uy2){}
};

class	CmdDrawImageActivate : public GUIDirectMessage	//アイテムをアクティブにして描画させるコマンド
{
public:
	int	GlobalPage;
	int	Layer;
	int	ItemID;
	CmdDrawImageActivate(LayersBase *base ,int gpage ,int layer, int itemID)
		:GUIDirectMessage(base),GlobalPage(gpage),Layer(layer),ItemID(itemID){}
	CmdDrawImageActivate(GUICmdPacketBase *gbase ,int gpage ,int layer, int itemID)
		:GUIDirectMessage(gbase),GlobalPage(gpage),Layer(layer),ItemID(itemID){}
};
//============================================================================================

class	DisplayImageCopyStructureMemoryList : public NPList<DisplayImageCopyStructureMemoryList>	//画像コピーするためのクリップボードバッファリスト
{
public:
	int32	DataBytes;
	BYTE	*Data;

	DisplayImageCopyStructureMemoryList(void);
	~DisplayImageCopyStructureMemoryList(void);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};


class	DisplayImageCopyStructure : public NPList<DisplayImageCopyStructure>	//画像コピーのクリップボードリストコンテナ
{
public:
	int								GlobalPage;
	DisplayImage::DisplayType		DType;
	int								MasterNo;
	IntList							LayerList;
	NPListPack<FlexAreaImageList>	ImageWithAreas;

	DisplayImageCopyStructure(void)			{	GlobalPage=-1;	MasterNo=0;	}
	DisplayImageCopyStructure(int _MasterNo){	GlobalPage=-1;	MasterNo=_MasterNo;	}
	DisplayImageCopyStructure(const DisplayImageCopyStructure &src);

	void	Capture(FlexArea &area ,DataInPage *PageData ,DisplayImage::DisplayType &dtype);
	DisplayImageCopyStructure	&operator=(const DisplayImageCopyStructure &src);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	bool	SaveDefaultFile(void);
	bool	LoadDefaultFile(void);

	void	Draw(QImage &Img ,int dx ,int dy 
				,int movx ,int movy ,double zoomrate);
};

class	GUICmdCopyRectPacket : public GUICmdPacketBase	//画像の矩形コピーコマンド
{
public:
	DisplayImage::DisplayType	Source;
	FlexArea					Area;
	GUICmdCopyRectPacket(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendCopyRectPacket : public GUICmdPacketBase	//画像コピーのリストコンテナデータ送信コマンド
{
public:
	DisplayImageCopyStructure	ImageClipData;

	GUICmdSendCopyRectPacket(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReqPasteRectPacket : public GUICmdPacketBase	//画像コピーの貼り付け要求コマンド
{
public:
	int32		dx,dy;
	int			MasterNo;
	NPListPack<DisplayImageCopyStructure>	ImageClipData;

	GUICmdReqPasteRectPacket(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReqClippedImage : public GUICmdPacketBase	//任意形状での画像コピーのための画像要求コマンド
{
public:
	DisplayImage::DisplayType	Source;
	FlexArea	RealArea;
	IntList		LayerList;
	double		ZoomRate;
	int			MasterNo;

	GUICmdReqClippedImage(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendClippedImage : public GUICmdPacketBase	//任意形状での画像コピーのための画像送信コマンド
{
public:
	NPListPack<DisplayImageCopyStructureMemoryList>	BuffList;
	IntList		LayerList;
	FlexArea	ZoomedArea;

	GUICmdSendClippedImage(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	void	CreateImageData(LayersBase *Base,FlexArea &RealArea
							,double ZoomRate
							,DisplayImage::DisplayType DType
							,int MasterNo);
	void	Draw(QImage &Img ,int GlobalX ,int GlobalY
				,int movx ,int movy ,double ZoomRate);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReqClippedImageCopy : public GUICmdPacketBase	//クリップボードに入れた画像を貼り付ける要求コマンド
{
public:
	int	SourceGlobalPage;
	int	SourceCenterX,SourceCenterY;
	int	DestGlobalPage;
	int	DestCenterX,DestCenterY;

	GUICmdReqClippedImageCopy(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


//============================================================================================

class	GUICmdSelectItems : public GUICmdPacketBase	//アイテム選択要求コマンド
{
public:
	QString		AlgoRoot;
	QString		AlgoName;
	FlexArea	Area;
	IntList		LayerList;
	bool		MultiSelect;
	int			Phase;		//-1: Any phase (current phase)

	GUICmdSelectItems(AlgorithmBase	*base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSelectAll : public GUICmdPacketBase	//アイテム全選択要求コマンド
{
public:
	QString		AlgoRoot;
	QString		AlgoName;
	IntList		LayerList;

	GUICmdSelectAll(AlgorithmBase	*base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
class	GUICmdSelectLocked : public GUICmdPacketBase	//ロックされたアイテムを選択要求するコマンド
{
public:
	QString		AlgoRoot;
	QString		AlgoName;
	IntList		LayerList;

	GUICmdSelectLocked(AlgorithmBase	*base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdCutItems : public GUICmdPacketBase	//選択されたアイテム切り取り要求コマンド
{
public:
	QString		AlgoRoot;
	QString		AlgoName;
	FlexArea	Area;
	IntList		LayerList;
	bool		MultiSelect;
	int			Phase;

	GUICmdCutItems(AlgorithmBase *base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSeparateItems : public GUICmdPacketBase	//選択されたアイテム切り取り要求コマンド
{
public:
	QString		AlgoRoot;
	QString		AlgoName;
	FlexArea	Area;
	IntList		LayerList;
	int			Phase;

	GUICmdSeparateItems(AlgorithmBase *base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdRegistArea : public GUICmdPacketBase	//領域登録要求コマンド
{
public:
	QString		AlgoRoot;
	QString		AlgoName;
	FlexArea	Area;
	IntList		LayerList;

	GUICmdRegistArea(AlgorithmBase *base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdOperationDelete : public GUICmdPacketBase	//選択されたアイテムの削除要求コマンド
{
public:
	QString		AlgoRoot;
	QString		AlgoName;
	IntList		LayerList;
	int			Phase;

	GUICmdOperationDelete(AlgorithmBase *base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdOperationLock : public GUICmdPacketBase	//選択されたアイテムのロック要求コマンド
{
public:
	QString		AlgoRoot;
	QString		AlgoName;
	IntList		LayerList;

	GUICmdOperationLock(AlgorithmBase *base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdOperationUnlock : public GUICmdPacketBase	//選択されたアイテムのロック解除要求コマンド
{
public:
	QString		AlgoRoot;
	QString		AlgoName;
	IntList		LayerList;

	GUICmdOperationUnlock(AlgorithmBase *base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdOperationGroup : public GUICmdPacketBase	//グループ化要求コマンド
{
public:
	QString		AlgoRoot;
	QString		AlgoName;
	IntList		LayerList;

	GUICmdOperationGroup(AlgorithmBase *base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdOperationCopy : public GUICmdPacketBase	//アイテムコピー要求コマンド
{
public:
	QString		AlgoRoot;
	QString		AlgoName;
	XDateTime	CreatedTime;
	IntList		LayerList;
	bool		EnableDup;

	GUICmdOperationCopy(AlgorithmBase *base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdOperationPaste : public GUICmdPacketBase	//アイテムの貼り付け要求コマンド
{
public:
	QString		AlgoRoot;
	QString		AlgoName;

	GUICmdOperationPaste(AlgorithmBase *base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdOperationMoveFromOutside : public GUICmdPacketBase	//アイテム移動要求コマンド
{
public:
	int		GlobalDx;
	int		GlobalDy;
	QString		AlgoRoot;
	QString		AlgoName;
	IntList		PageListForOutside;
	int			Phase;

	GUICmdOperationMoveFromOutside(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdOperationMove : public GUICmdPacketBase	//アイテム移動要求コマンド
{
public:
	int		GlobalDx;
	int		GlobalDy;
	QString		AlgoRoot;
	QString		AlgoName;
	ListPageLayerIDPack		Items;
	int		Phase;

	GUICmdOperationMove(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReqMovedPage : public GUICmdPacketBase	//アイテム移動時にページを跨ぐときの移動を実現する移動要求コマンド
{
public:
	int		GlobalDx;
	int		GlobalDy;
	QString		AlgoRoot;
	QString		AlgoName;
	int		Phase;

	GUICmdReqMovedPage(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckMovedPage : public GUICmdPacketBase	//移動要求応答
{
public:
	IntList	PageList;
	ListPageLayerIDPack Items;

	GUICmdAckMovedPage(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdActivateOnItem : public GUICmdPacketBase	//
{
public:
	QString		AlgoRoot;
	QString		AlgoName;
	IntList		LayerList;
	int			PosX,PosY;

	GUICmdActivateOnItem(AlgorithmBase *base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendActivateOnItem : public GUICmdPacketBase	//指定した座標上のアイテムをアクティブにする要求コマンドに対してアイテムのＩＤを返すコマンド
{
public:
	QString				AlgoRoot;
	QString				AlgoName;
	IntList				LayerList;
	ListLayerAndIDPack	ItemList;

	GUICmdSendActivateOnItem(AlgorithmBase *base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdActivateOnItemDirect : public GUICmdPacketBase	//指定したアイテムをアクティブにする要求コマンド
{
public:
	QString		AlgoRoot;
	QString		AlgoName;
	int32		Layer;
	int64		ItemID;

	GUICmdActivateOnItemDirect(AlgorithmBase *base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReqClearTemporaryItems : public GUICmdPacketBase	//一時退避アイテムのクリア要求コマンド
{
public:
	QString		AlgoRoot;
	QString		AlgoName;

	GUICmdReqClearTemporaryItems(AlgorithmBase *base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReqTemporaryItems : public GUICmdPacketBase	//アイテムの一時退避要求コマンド
{
	DisplayImageWithAlgorithm	*Form;
	QString		AlgoRoot;
	QString		AlgoName;
public:
#pragma	pack(push)
#pragma	pack(1)
	struct	GUIReqBmpStruct
	{
		int32	Gx1;
		int32	Gy1;
		int32	Gx2;
		int32	Gy2;
		int32	Dx1;
		int32	Dy1;
		int32	Dx2;
		int32	Dy2;
		double	ZoomRate;
		int32	MovX;
		int32	MovY;
		int32	GlobalPage;
		int32	MoveGlobalDx;
		int32	MoveGlobalDy;
		DisplayImage::__DrawingMode	Mode;
		DisplayImage::DisplayType	DType;
	}Data;
#pragma	pack(pop)

	IntList	LayerList;
	//AlgorithmDrawAttr	*ModePoint;
	QString				InstName;

	GUICmdReqTemporaryItems(DisplayImageWithAlgorithm *Form,AlgorithmBase *base 
					, const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);
	~GUICmdReqTemporaryItems(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckTemporaryItems : public GUICmdPacketBase	//アイテムの一時退避要求への応答コマンド
{
public:

	GUICmdAckTemporaryItems(LayersBase *base 
					, const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f){	return true;	}
	virtual	bool	Save(QIODevice *f){	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

class	GUICmdReqItemsBmp : public GUICmdPacketBase		//アイテムの描画のための画像要求コマンド
{
	DisplayImageWithAlgorithm	*Form;
	QString		AlgoRoot;
	QString		AlgoName;
public:
#pragma	pack(push)
#pragma	pack(1)
	struct	GUIReqBmpStruct
	{
		int32	Gx1;
		int32	Gy1;
		int32	Gx2;
		int32	Gy2;
		int32	Dx1;
		int32	Dy1;
		int32	Dx2;
		int32	Dy2;
		double	ZoomRate;
		int32	MovX;
		int32	MovY;
		int32	GlobalPage;
		int32	MoveGlobalDx;
		int32	MoveGlobalDy;
		DisplayImage::__DrawingMode	Mode;
		DisplayImage::DisplayType	DType;
	}Data;
#pragma	pack(pop)

	IntList	LayerList;
	//AlgorithmDrawAttr	*ModePoint;
	QString				InstName;
	QByteArray			DAttrArray;

	GUICmdReqItemsBmp(DisplayImageWithAlgorithm *Form,AlgorithmBase *base 
					, const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);
	~GUICmdReqItemsBmp(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


class	GUICmdSendItemsBmp : public GUICmdPacketBase	//アイテムの描画のための画像要求応答コマンド
{
	QString		AlgoRoot;
	QString		AlgoName;
public:
	QImage		*IData;

	GUICmdSendItemsBmp(AlgorithmBase *base 
					,  const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);
	~GUICmdSendItemsBmp(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}

	void	MakeImage(AlgorithmDrawAttr	*ModePoint
					 ,IntList &LayerList					 
					 ,int Gx1,int Gy1 ,int Gx2,int Gy2
					 ,int Dx1,int Dy1 ,int Dx2,int Dy2
					 ,int MovX,int MovY, double ZoomRate
					 ,int localPage
					 ,DisplayImage::__DrawingMode	DMode
					 ,int MoveGlobalDx ,int MoveGlobalDy
					 ,DisplayImageWithAlgorithm	*A
					 ,DisplayImage::DisplayType	DType
					 ,LayersBase &LocalLBase
					 ,QString &EmitterRoot,QString &EmitterName);
};

class	SlaveCommReqPasteShape : public DirectCommPacketBase
{
public:
	int			DrawnGlobalPage;
	int			MoveGlobalDx,MoveGlobalDy;
	QString		InstName;
	int			Movx ,Movy;
	double		ZoomRate;
	QColor		Col;
	int			Gx1,Gy1;
	int			Gx2,Gy2;

	SlaveCommReqPasteShape(LayersBase *base 
					,  const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	SlaveCommAckPasteShape : public DirectCommPacketBase
{
public:
	QImage		Pnt;
	int			DrawnPosX,DrawnPosY;
	bool		Drawn;

	SlaveCommAckPasteShape(LayersBase *base 
					,  const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

class	SlaveCommSendTemporaryItems : public DirectCommPacketBase	//スレーブ間通信の一時退避アイテム送信コマンド
{
	QString		AlgoRoot;
	QString		AlgoName;
public:
	QByteArray	Data;

	SlaveCommSendTemporaryItems(AlgorithmBase *base 
					,  const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	void	SetData(ItemPointerListInPage *PageData);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	SlaveCommSendFixTemporaryItems : public DirectCommPacketBase	//スレーブ間通信による一時退避アイテムの固定化コマンド
{
	QString		AlgoRoot;
	QString		AlgoName;
public:
	QByteArray	Data;
	int			Phase;

	SlaveCommSendFixTemporaryItems(AlgorithmBase *base 
					,  const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	void	SetData(ItemPointerListInPage *PageData);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReqItemIndependentPack : public GUICmdPacketBase	//ItemIndependentPack要求コマンド
{
public:
	int		localX,localY;
	int		TargetPhase;	//-1:Any phase
	bool	SubResultMoving;

	GUICmdReqItemIndependentPack(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


class	GUICmdSendIndependentPack : public GUICmdPacketBase	//ItemIndependentPackデータ送信コマンド
{
public:
	AlgorithmItemIndependentPack		IData;

	GUICmdSendIndependentPack(LayersBase *base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReqItemIndependentsPack : public GUICmdPacketBase	//ItemIndependentPack要求コマンド
{
public:
	int		LibType;
	int		LibID;
	int		TargetPhase;	//-1:Any phase
	int		Layer;
	IntList	Items;

	GUICmdReqItemIndependentsPack(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReqSelectCopied : public GUICmdPacketBase	//コピーされたアイテムの操作要求コマンド
{
public:
	XDateTime	SelectTimeIndex;
	enum	_Mode{
		_PurePaste		=1
		,_ShapedPaste	=2
		,_PasteForImage	=3
		,_CutByShape	=4
	}Mode;
	QString InstName;
	int32	PastedLayer;
	QColor	Color;

	GUICmdReqSelectCopied(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReqCutByPasted : public GUICmdPacketBase	//コピーされたアイテムの操作要求コマンド
{
public:
	QString InstName;
	int	Dx,Dy;

	GUICmdReqCutByPasted(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdExecutePaste : public GUICmdPacketBase	//アイテムの貼り付け要求コマンド
{
public:
	enum	_Mode{
		_PurePaste		=1
		,_ShapedPaste	=2
	}Mode;	
	QString		InstName;
	QByteArray	Buff;
	QString OriginRoot;
	QString OriginName;
	int		Dx;
	int		Dy;
	int		ItemClass;
	bool	SamePage;

	GUICmdExecutePaste(LayersBase *Base,_Mode mode,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReqSelectedItemCount : public GUICmdPacketBase	//選択されたアイテムの個数要求コマンド
{
public:
	QString		AlgoRoot;
	QString		AlgoName;

	GUICmdReqSelectedItemCount(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendSelectedItemCount : public GUICmdPacketBase	//選択されたアイテムの個数送信コマンド
{
public:
	int		SelectedItemCount;

	GUICmdSendSelectedItemCount(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSetItemNameInSelected : public GUICmdPacketBase	//
{
public:
	QString		AlgoRoot;
	QString		AlgoName;
	QString		ItemName;

	GUICmdSetItemNameInSelected(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReqItemCountOnLocalPoint : public GUICmdPacketBase
{
public:
	QString		AlgoRoot;
	QString		AlgoName;
	int32		LocalX;
	int32		LocalY;
	IntList		LayerList;

	GUICmdReqItemCountOnLocalPoint(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendItemCountOnLocalPoint : public GUICmdPacketBase
{
public:
	ListLayerIDLibNamePack	ItemList;

	GUICmdSendItemCountOnLocalPoint(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSelectItemByID : public GUICmdPacketBase
{
public:
	QString		AlgoRoot;
	QString		AlgoName;
	ListLayerAndIDPack	SelectedItem;

	GUICmdSelectItemByID(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdMoveImage : public GUICmdPacketBase
{
public:
	bool	FlagMaster;
	bool	FlagTarget;

	int		XDir,YDir;
	GUICmdMoveImage(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdRotateImage : public GUICmdPacketBase
{
public:
	bool	FlagMaster;
	bool	FlagTarget;
	double	Angle;

	GUICmdRotateImage(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdMirrorXYImage : public GUICmdPacketBase
{
public:
	bool	FlagMaster;
	bool	FlagTarget;
	bool	MirrorX;
	bool	MirrorY;

	GUICmdMirrorXYImage(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdCopyImageInPhases : public GUICmdPacketBase
{
public:
	int		SrcPhase;
	int		DstPhase;
	bool	FlagMaster;
	bool	FlagTarget;

	GUICmdCopyImageInPhases(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSwapImage : public GUICmdPacketBase
{
public:
	GUICmdSwapImage(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f){	return true;	}
	virtual	bool	Save(QIODevice *f){	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdNegPosImage : public GUICmdPacketBase
{
public:
	bool	MasterBuff;
	bool	TargetBuff;

	GUICmdNegPosImage(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdCopyImageToTarget: public GUICmdPacketBase
{
public:
	GUICmdCopyImageToTarget(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f){	return true;	}
	virtual	bool	Save(QIODevice *f){	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdCopyImageToBackGround: public GUICmdPacketBase
{
public:
	GUICmdCopyImageToBackGround(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f){	return true;	}
	virtual	bool	Save(QIODevice *f){	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdCopyImageToMaster: public GUICmdPacketBase
{
public:
	GUICmdCopyImageToMaster(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f){	return true;	}
	virtual	bool	Save(QIODevice *f){	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdCopyImageToMasterBuffN: public GUICmdPacketBase
{
public:
	bool	SourceMaster;
	int		MasterNo;
	bool	SwapMode;

	GUICmdCopyImageToMasterBuffN(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdTranspositionTarget: public GUICmdPacketBase
{
public:
	GUICmdTranspositionTarget(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f){	return true;	}
	virtual	bool	Save(QIODevice *f){	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdClearImage: public GUICmdPacketBase
{
public:
	int		Mastered;	//0:Master , 1:Target , 2:BitBuffer
	int		TargetPhase;	//-1:Any phase
	QColor	Color;

	GUICmdClearImage(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);

private:
	void	ClearImage(PageDataInOnePhase *Ph,int32 localPage);
};


class	GUICmdReqSelectByOrigin: public GUICmdPacketBase
{
public:
	IntList		LayerList;	
	QString		AlgoRoot;
	QString		AlgoName;
	
	GUICmdReqSelectByOrigin(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckSelectByOrigin: public GUICmdPacketBase
{
public:
	NPListPack<OriginNames>	OriginNameList;

	GUICmdAckSelectByOrigin(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSelectByOrigin: public GUICmdPacketBase
{
public:
	OriginNames	Names;
	QString		OriginDLLRoot;
	QString		OriginDLLName;
	QString		AlgoRoot;
	QString		AlgoName;
	IntList		LayerList;	
	
	GUICmdSelectByOrigin(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdVisibleAll : public GUICmdPacketBase
{
public:
	QString		AlgoRoot;
	QString		AlgoName;
	IntList		LayerList;
	bool		Visible;

	GUICmdVisibleAll(AlgorithmBase	*base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdInvisibleSelected : public GUICmdPacketBase
{
public:
	QString		AlgoRoot;
	QString		AlgoName;
	IntList		LayerList;

	GUICmdInvisibleSelected(AlgorithmBase	*base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSelectManualCreature : public GUICmdPacketBase
{
public:
	QString		AlgoRoot;
	QString		AlgoName;
	IntList		LayerList;

	GUICmdSelectManualCreature(AlgorithmBase	*base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReqAllItemsForSelect: public GUICmdPacketBase
{
public:
	QString		AlgoRoot;
	QString		AlgoName;
	IntList		LayerList;

	GUICmdReqAllItemsForSelect(LayersBase *base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckAllItemsForSelect: public GUICmdPacketBase
{
public:
	ListPageLayerIDLibNamePack	ItemInfo;

	GUICmdAckAllItemsForSelect(LayersBase *base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

class	GUICmdReqExpandedPaste : public GUICmdPacketBase
{
public:
	QString		AlgoRoot;
	QString		AlgoName;
	enum	PasteMode{
		_SameAlgorithmPaste	=1
	}Mode;
	int32	Px1,Py1;
	int32	Px2,Py2;
	int32	Px3,Py3;
	int32	Px4,Py4;
	IntList	PastedLayer;
	int32	Dx,Dy;

	GUICmdReqExpandedPaste(LayersBase *base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReqSelectedItemListsForPaste : public GUICmdPacketBase
{
public:
	QString		AlgoRoot;
	QString		AlgoName;
	IntList		LayerList;

	GUICmdReqSelectedItemListsForPaste(LayersBase *base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendSelectedItemListsForPaste : public GUICmdPacketBase
{
public:
	QString		AlgoRoot;
	QString		AlgoName;
	ExpandedSelectedItemListContainer	Lists;

	GUICmdSendSelectedItemListsForPaste(LayersBase *base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReqDrawItemListsForPaste : public GUICmdPacketBase
{
public:
	QString		AlgoRoot;
	QString		AlgoName;
	/*
	int32		Layer;
	int32		ItemID;
	*/
	int			Width,Height;
	int			SourceCenterX,SourceCenterY;

	ExpandedSelectedItemListContainer		SelectedItemLists;
	DisplayImage::ExpandedItemPosContainer	ExpandedItems;

	double ZoomRate;
	int movx;
	int movy;

	GUICmdReqDrawItemListsForPaste(LayersBase *base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendDrawItemListsForPaste : public GUICmdPacketBase
{
public:
	QImage		*Image;
	int			Width,Height;

	GUICmdSendDrawItemListsForPaste(LayersBase *base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);
	~GUICmdSendDrawItemListsForPaste(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReqSavingImage : public GUICmdPacketBase
{
public:
	int			MinX,MinY,MaxX,MaxY;
	bool		Mastered;

	GUICmdReqSavingImage(LayersBase *base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckSavingImage : public GUICmdPacketBase
{
public:
	QImage	Img;

	GUICmdAckSavingImage(LayersBase *base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSelectItemsByOriginType : public GUICmdPacketBase
{
public:
	QString		AlgoRoot;
	QString		AlgoName;
	IntList		LayerList;
	struct	OriginTypeSelection SelectMode;
	bool		ExistOrigin;
	QString		OriginAlgoRoot;
	QString		OriginAlgoName;

	GUICmdSelectItemsByOriginType(LayersBase	*base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
//===============================================================================================

class	AvrVarListByLayer : public NPList<AvrVarListByLayer>
{
public:
	double	Average;
	double	Dispersion;
	int32	Layer;

	AvrVarListByLayer(void){	Average=0.0;	Dispersion=0.0;	Layer=0;	}

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	AvrVarListByLayerContainer : public NPListPack<AvrVarListByLayer>
{
public:
	AvrVarListByLayerContainer(void){}

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
	AvrVarListByLayerContainer	&operator=(AvrVarListByLayerContainer &src);
};

class	HistgramList : public NPList<HistgramList>
{
public:
	int		BrightList[256];
	int32	Layer;

	HistgramList(void){	Layer=0;	memset(BrightList,0,sizeof(BrightList));	}

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	HistgramListContainer : public NPListPack<HistgramList>
{
public:
	HistgramListContainer(void){}

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
	HistgramListContainer	&operator=(HistgramListContainer &src);
};

class	GUICmdRegulateBrightness : public GUICmdPacketBase
{
public:
	DisplayImage::DisplayType	ImageType;
	int							MasterNo;
	AvrVarListByLayerContainer	AvrDatas;
	int		BlockSize;
	FlexArea	Area;

	GUICmdRegulateBrightness(LayersBase *base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdGetAvrVar : public GUICmdPacketBase
{
public:
	DisplayImage::DisplayType	ImageType;
	int							MasterNo;
	IntList		LayerList;
	int		BlockSize;
	FlexArea	Area;

	GUICmdGetAvrVar(LayersBase *base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
class	GUICmdAckAvrVar : public GUICmdPacketBase
{
public:
	HistgramListContainer		HistDatas;
	AvrVarListByLayerContainer	AvrDatas;

	GUICmdAckAvrVar(LayersBase *base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
class	GUICmdSwapRawToTarget : public GUICmdPacketBase
{
public:
	GUICmdSwapRawToTarget(LayersBase *base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f){	return true;	}
	virtual	bool	Save(QIODevice *f){	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdCopyRawToTarget : public GUICmdPacketBase
{
public:
	GUICmdCopyRawToTarget(LayersBase *base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f){	return true;	}
	virtual	bool	Save(QIODevice *f){	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


class	GUICmdGetColorSample : public GUICmdPacketBase
{
public:
	DisplayImage::DisplayType	ImageType;
	int							MasterNo;
	FlexArea	Area;

	GUICmdGetColorSample(LayersBase *base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
class	GUICmdAckColorSample : public GUICmdPacketBase
{
public:
	RGBStock	ColorSample;

	GUICmdAckColorSample(LayersBase *base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);
	void	MakeData(ImagePointerContainer &Images,FlexArea &Area);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReqRatate : public GUICmdPacketBase
{
public:
	QString		AlgoRoot;
	QString		AlgoName;
	int	Angle;

	GUICmdReqRatate(AlgorithmBase *base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReqSelectedItems : public GUICmdPacketBase
{
public:
	QString		AlgoRoot;
	QString		AlgoName;

	GUICmdReqSelectedItems(LayersBase *base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckSelectedItems : public GUICmdPacketBase
{
public:
	QByteArray	BuffData;

	GUICmdAckSelectedItems(LayersBase *base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};


class	GUICmdReqMirror : public GUICmdPacketBase
{
public:
	QString		AlgoRoot;
	QString		AlgoName;
	QByteArray	*BuffData;
	int			PageNumb;
	AlgorithmItemRoot::_MirrorMode	MirrorMode;

	GUICmdReqMirror(AlgorithmBase *base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);
	~GUICmdReqMirror(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//===============================================================================================
class	CmdPanelGetButton : public GUIDirectMessage
{
public:
	mtFrameDraw::DrawingMode	Mode;
	CmdPanelGetButton(LayersBase *base):GUIDirectMessage(base){}
	CmdPanelGetButton(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdPanelSetButton : public GUIDirectMessage
{
public:
	mtFrameDraw::DrawingMode	Mode;
	CmdPanelSetButton(LayersBase *base):GUIDirectMessage(base){}
	CmdPanelSetButton(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetPickupColor : public GUIDirectMessage
{
public:
	QColor	PickupColor;

	CmdGetPickupColor(LayersBase *base):GUIDirectMessage(base){}
	CmdGetPickupColor(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdReqImageLayer : public GUIDirectMessage
{
public:
	DisplayImage::DisplayType DType;
	IntList		LayerList;

	CmdReqImageLayer(LayersBase *base ,int LayerNumb);
	CmdReqImageLayer(GUICmdPacketBase *gbase,int LayerNumb);
};

class	CmdCheckRegistered : public GUIDirectMessage
{
public:
	QString	InstName;
	bool	Ret;

	CmdCheckRegistered(LayersBase *base ):GUIDirectMessage(base){}
	CmdCheckRegistered(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCheckBitBuffMode : public GUIDirectMessage
{
public:
	bool3	BitBuffMode;

	CmdCheckBitBuffMode(LayersBase *base ):GUIDirectMessage(base){	BitBuffMode=none3;	}
	CmdCheckBitBuffMode(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){	BitBuffMode=none3;	}
};
class	CmdSetBitBuffMode : public GUIDirectMessage
{
public:
	bool	BitBuffMode;

	CmdSetBitBuffMode(LayersBase *base ):GUIDirectMessage(base){	BitBuffMode=false;	}
	CmdSetBitBuffMode(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){	BitBuffMode=false;	}
};

inline	CmdReqImageLayer::CmdReqImageLayer(LayersBase *base ,int LayerNumb)
	:GUIDirectMessage(base)
{	
	DType=DisplayImage::__Master;	
	for(int L=0;L<LayerNumb;L++){
		LayerList.Add(L);
	}
}
inline	CmdReqImageLayer::CmdReqImageLayer(GUICmdPacketBase *base ,int LayerNumb)
	:GUIDirectMessage(base)
{	
	DType=DisplayImage::__Master;	
	for(int L=0;L<LayerNumb;L++){
		LayerList.Add(L);
	}
}

class	CmdSetImageLayer : public GUIDirectMessage
{
public:
	IntList		LayerList;

	CmdSetImageLayer(LayersBase *base):GUIDirectMessage(base){}
	CmdSetImageLayer(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdSetDisplayType : public GUIDirectMessage
{
public:
	DisplayImage::DisplayType DType;
	int		MasterNo;

	CmdSetDisplayType(LayersBase *base):GUIDirectMessage(base){	MasterNo=0;	}
	CmdSetDisplayType(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){	MasterNo=0;	}
};



//===============================================================================================
class	SpecifiedBroadcasterDeletePasted : public SpecifiedBroadcaster
{
public:
	ClipboardAlgorithm	*DeletedPointer;
};

//===============================================================================================

class	SlaveCommReqPasteFromClipboard : public DirectCommPacketBase
{
public:
	XDateTime	CreatedTime;
	int			MoveGlobalDx,MoveGlobalDy;
	QString		InstName;

	SlaveCommReqPasteFromClipboard(LayersBase *base 
					,  const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	SlaveCommAckPasteFromClipboard : public DirectCommPacketBase
{
public:
	ClipboardAlgorithm		ClipboardDatas;

	SlaveCommAckPasteFromClipboard(LayersBase *base 
					,  const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//============================================================================================
class	GUICmdSetActivateItem : public GUICmdPacketBase	//アイテムをアクティブ表示にする
{
public:
	int		Layer;
	int		ItemID;
	QString		AlgoRoot;
	QString		AlgoName;

	GUICmdSetActivateItem(AlgorithmBase *base,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//============================================================================================
class	GUICmdClearActivateItem : public GUICmdPacketBase	//アイテムをアクティブ表示を解除
{
public:
	QString		AlgoRoot;
	QString		AlgoName;

	GUICmdClearActivateItem(AlgorithmBase *base,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//============================================================================================

class	GUICmdPasteMatrix: public GUICmdPacketBase
{
public:
	XDateTime					CreatedTime;
	QString						AlgoRoot;
	QString						AlgoName;
	PasteListMatrixContainer	MatrixData;
	
	GUICmdPasteMatrix(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//============================================================================================

class	GUICmdReqSelectItemByID : public GUICmdPacketBase
{
public:
	QString		AlgoRoot;
	QString		AlgoName;
	ListLayerAndIDPack	SelectedItem;
	bool		SelectMode;

	GUICmdReqSelectItemByID(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckSelectItemByID : public GUICmdPacketBase
{
public:
	int	MinX,MinY,MaxX,MaxY;

	GUICmdAckSelectItemByID(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}	
};


//============================================================================================

class	GUICmdMirrorImage : public GUICmdPacketBase
{
public:
	bool	XMode;
	bool	YMode;

	GUICmdMirrorImage(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//============================================================================================

class	GUICmdSetMultiSelectMode : public GUICmdPacketBase
{
public:
	QString	ItemName;
	bool	ModeMultiSelect;

	GUICmdSetMultiSelectMode(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//============================================================================================

class	GUICmdReqShrink : public GUICmdPacketBase
{
public:
	QString		AlgoRoot;
	QString		AlgoName;
	IntList		LayerList;
	int			ExpandPixels;
	bool		MaskForSameLib;

	GUICmdReqShrink(AlgorithmBase *base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
//============================================================================================
class	GUICmdPourImage : public GUICmdPacketBase	//
{
public:
	int		LocalX;
	int		LocalY;
	DisplayImage::DisplayType	DType;
	int		MasterNo; 
	int		BrightnessWidth;
	int		ExpandedDot;
	QColor	PickedColor;

	GUICmdPourImage(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
//============================================================================================
class	GUICmdReplaceColorImage : public GUICmdPacketBase	//
{
public:
	int		LocalX;
	int		LocalY;
	DisplayImage::DisplayType	DType;
	int		MasterNo; 
	int		BrightnessWidth;
	int		ExpandedDot;
	QColor	PickedColor;

	GUICmdReplaceColorImage(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//============================================================================================
class	GUICmdReqChangeLibItem : public GUICmdPacketBase	//
{
public:
	int	Phase	;
	int	LibType	;
	int	LibID	;

	GUICmdReqChangeLibItem(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//============================================================================================

class	GUICmdReqSelectedItemLibID : public GUICmdPacketBase
{
public:
	int	Phase	;
	int	LibType	;

	GUICmdReqSelectedItemLibID(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckSelectedItemLibID : public GUICmdPacketBase
{
public:
	IntList	LibList;

	GUICmdAckSelectedItemLibID(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}	
};

//============================================================================================

class	GUICmdReqSelectedItemIDInLibID : public GUICmdPacketBase
{
public:
	int	Phase	;
	int	LibType	;
	int	LibID	;
	int	Layer	;

	GUICmdReqSelectedItemIDInLibID(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckSelectedItemIDInLibID : public GUICmdPacketBase
{
public:
	IntList	ItemIDs;

	GUICmdAckSelectedItemIDInLibID(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}	
};

class	GUICmdMakeOutlineItem : public GUICmdPacketBase
{
public:
	int	LibType;
	int	Phase;
	int	OutlineWidth;

	GUICmdMakeOutlineItem(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};


#endif
