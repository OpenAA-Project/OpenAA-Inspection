/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\RepairBase.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef REPAIRBASE_H
#define REPAIRBASE_H

#include <QWidget>
#include <QString>
#include <QTableWidget>
#include <QFile>
#include <QTreeWidgetItem>
#include <QThread>
#include <QComboBox>
#include <QTextStream>
#include "MTXMLLib.h"
#include "math.h"
//#include "XOutlineOffset.h"
#include "InspectionDataForm.h"
#include "mtQTableWidget.h"

class ClientMain;
class ImageDataUnit;
class ImageInPage;
class RepairBase;

//NG赤丸ブリンクスレッド
class NGBlinkThread : public QThread
{
	Q_OBJECT

public:
	NGBlinkThread();

	bool		StopFlag;
	bool		ChangeFlag;
	int			BlinkTime;
	bool		LocalNGPointVisible;
	void Stop()	{	StopFlag=true;	}

signals:
	void SignalRepaint(bool NGVisibled);

private slots:

protected:
	void run();

private:
};

//ウィンドウグラデーションスレッド
class WindowColorThread : public QThread
{
	Q_OBJECT

public:
	WindowColorThread();

	bool		ChangeFlag;
	int			BlinkTime;
	void SetColor	(int r,int g,int b,int a=255)	{	Red=r;	Green=r;	Blue=b;	Alpha=a;	}
	void SetColor	(QColor &color)					{	RGBColor=color;							}
	void Stop		()								{	StopFlag=true;							}
//	bool IsStop		()								{	return ChangeFlag;						}

signals:
//	void SignalRepaint(int r,int g,int b,int a=255);
	void SignalRepaint(QColor color);

protected:
	void run();

private:
	bool	StopFlag;
	int		Red,Green,Blue,Alpha;
	QColor	RGBColor;
};

//XMLデータ操作用スレッド
class XMLAppendThread : public QThread
{
	Q_OBJECT

public:
	XMLAppendThread();

//	ClientMain *Client;
	QString		XMLFile;
	QString		QNO;
	QString		XML;

//	void SetXMLClient	(ClientMain *pClient)	{	Client=pClient;		}
	void SetXMLFile		(QString *sXMLFile)		{	XMLFile=*sXMLFile;	}
	void SetXMLQNO		(QString *sQNO)			{	QNO=*sQNO;			}
	void SetXML			(QString *sXML)			{	XML=*sXML;			}

signals:
	void SignalClient_Update(QString strXML);
//	void SignalClient_Update();
//	void SignalOnCheck(Qt::CheckState *State);

protected:
	void run();

private:
};

//エラー送り監視スレッド
class ErrNextThread : public QThread
{
	Q_OBJECT

public:
	ErrNextThread();

	void Stop()		{	StopFlag=true;	}

signals:
	void SignalIsChanged();

protected:
	void run();

private:
	bool	StopFlag;
};

//個片コンボボックス
class PieceListEditor : public QComboBox
{
	Q_OBJECT

public:
//	PieceListEditor(QStringList &List,QWidget *widget=0);
	PieceListEditor(QStringList &List);
	~PieceListEditor();

public:
//	QString piece() const;
//	void setPiece(QString s);

private slots:
	void SlotCurIndexChanged(int Index);

private:
	void populateList();
};

//NGポイントデータ格納クラス
class NGPointList : public NPList<NGPointList>
{
public:
	NGPointList(int X,int Y,const QString &Str);
	~NGPointList();

	int x;
	int y;
	QString colorAlg;
};

//NGポイントデータBase格納クラス
class NGPointBaseList : public NPList<NGPointBaseList>
{
public:
	NGPointBaseList();
	~NGPointBaseList();

//	NGPointList	ChileNGPointList;
	NPListPack<NGPointList>	NGListForVRS;
};

//NGPタグデータ格納クラス
class NGPTagDataList
{
public:
	NGPTagDataList();
	NGPTagDataList(int X,int Y,QString RAL,int PG);
	~NGPTagDataList();

	int		x;
	int		y;
	QString	ral;
	int		pg;
	QString	ara;
//	bool	*Checked;
};

typedef	struct	_PieceInfoCoordinates
{
	int	X;
	int	Y;
	int	wY;

}PieceInfoCoordinates;

class PieceInfoData
{
public:
	PieceInfoData();
	~PieceInfoData();

	int		DataCount;
	PieceInfoCoordinates	*PieceCoordinates;

	void		SetPieceData(RepairBase *parent,const QByteArray *PieceData,QList<ImageInPage *> &ImageList);
//	void		SetPiecePageList(QList<int> *PageList)	{	PiecePageList=*PageList;		}
	QList<int>	GetPiecePageList()			{	return PiecePageList;			}
	int			GetFirstPiecePage()			{	return PiecePageList.first();	}
	int			GetLastPiecePage()			{	return (PiecePageList.count()==0)? -1 : PiecePageList.last();	}
	void		SetPieceName(QString Name)	{	PieceName	=Name;				}
	QString		GetPieceName()				{	return PieceName;				}
	void		SetPieceShape(char Shape);
	char		GetPieceShape()				{	return PieceShape;				}
	void		SetPolygon(int Page,QPolygon Polygon);
	QPolygon	GetPolygon(int Page);

	bool		isInside				(int X,int Y,int P);
	int			GetDistanceFromCenter	(int X,int Y,int OffsetX1,int OffsetY1,int OffsetX2,int OffsetY2);

private:
	QList<int>	PiecePageList;	//Piece Page List
	QString		PieceName;		//Piece Name
	char		PieceShape;		//Piece Shape

	QList<QPair<int,QPolygon> >	PolygonList;
};
/*
typedef	struct	_PieceInfoData
{
	QString	PieceName;		//Piece Name
	char	PieceShape;		//Piece Shape
	PieceInfoCoordinates	*PieceCoordinates;
	void	DrawPieceInfoData(QPainter &Pnt);

}PieceInfoData;
*/

//リペアステーションの親クラス
//class RepairBase : public QWidget
class RepairBase
{
//	Q_OBJECT

public:
//	RepairBase(QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	RepairBase();
	~RepairBase();

	//マスター画像裏表判断
	enum	SideType{
				 None	=-1		//デフォルト初期値用
				,Front	=0		//表
				,Back	=1		//裏
	};
	SideType	SType;

	enum	XYSortType{
				 TopToBottom	=0
				,BottomToTop	=1
				,LeftToRight	=2
				,RightToLeft	=3
	};
	XYSortType	XYSType;

	int MachineID[2];
	int Pagenumb;
//	OutlineOffsetInBlob	*OutlineOffsetWriter;

	QColor		twHistoryFrontColor;
	QColor		twHistoryBackColor;
	QColor		twHistoryBothColor;
	QColor		twNGListFrontColor;
	QColor		twNGListBackColor;
	QColor		twNGListCheckColor;
	QColor		NowFBColor;
	QList<QColor>		ColorFKey;
	NPListPack<NGPointList> *NGPList[2];
	NGPointBaseList *NGPBaseList;
//	NPListPack<NGPointBaseList> NoImageNGPList[2];
	NGPointBaseList *NGPBaseListForVRS;
	NPListPack<NGPointBaseList>	NGPListForVRS[2];
	int			PieceInfoDataCount[2];			//個片情報個数
	PieceInfoData *PieceInfoDataList[2];		//個片情報データ
	int			ClientNo[2];
	QByteArray	strQNO;
	QByteArray	strQNO1;
	QByteArray	strQNO2;
	int			MaxX,MinX,MaxY,MinY;
	int			iSide,iSideOld;
	int			SumFRowCnt,SumBRowCnt;
	int			SumFRowCntInImage,SumBRowCntInImage;
	int			ListFIndex,ListBIndex;
	bool		FirstXMLContact;
	int			NGShowW,NGShowH;

	QByteArray	strXML[2];

	ClientMain		*xmlCont[2];
	XMLElement		**NGPTagList[2];
	XMLAppendThread	tXMLAppend;

	int			PNumbForBase;		//カメラ数の保持

	NGBlinkThread		tNGBlink;
	WindowColorThread	tOKWindow;
	ImageDataUnit	*IDataUnit;
	int				Brightness[256];

	//NG個片コンボボックス
	PieceListEditor *cbPieceListEditor;

	ErrNextThread	tErrNext;
	bool			wErrNextBS;			//エラー送りボタンのOn／Off保持ワーク
	bool			wNGBS;				//NGボタンのOn／Off保持ワーク
	bool			wBackBS;			//戻りボタンのOn／Off保持ワーク
	bool			wUnloadDone;		//排出コメント表示要求信号ワーク
	bool			wMacEmergency;		//異常発生信号ワーク
	bool			wMacEmgRestart;		//異常発生信号（復旧可）ワーク
	bool			wReviewEnableFlag;	//レビュー再開フラグワーク
	bool			FirstUpdateFlag;	//初回Update時にボタン操作を有効にさせる
	QList<int>		PrevNGRow;			//直前のNGリストの行保持ワーク
	bool			(*DLL_GetName)					(QString &str);
	void			(*DLL_SetLogInfo)				(QString *Hinsh,QString *Lot,QString *Jouge,QStringList *HDNameList,QStringList *KohenNameList);
	void			(*DLL_AppendNGInfo)				(QString *KohenName,int NGNo,int PCNo,int TaiouKohenNumb,QString *X,QString *Y,QString HanteiKekka,QString *RealKohenName);
	int				(*DLL_OutputLog)				(QString *KibanNo,int NGNumb,QStringList &NGKohenNoList,QTextStream &FileStream);
	bool			(*DLL_IsOutputLog)				(void);
	void			(*DLL_SetIsOutputLog)			(bool IsOutputLog);
	void			(*DLL_RemoveNGInfo)				(QString *KohenName);
	int	 			(*DLL_AllCheckedFormShow)		(QStringList &NGKohenNoList,QString LotName,bool &IsMaxOver);
	void			(*DLL_AllCheckedFormClose)		(void);
	void			(*DLL_UnloadCommentFormShow)	(void);
	void			(*DLL_UnloadCommentFormClose)	(void);
//	bool			(*DLL_SaveNGImage)				(QByteArray *NGDataList,QString *KohenName,int NGNo,QString *strTime);
//	bool			(*DLL_SaveNGImage)				(QByteArray **NGDataList[],int *NGI,int *Side,int *IDX,int *Index,QString *KohenName,int NGCount,QString *strTime);
	bool			(*DLL_SaveNGImage)				(QByteArray **NGDataList[],int *NGI,int *Side,int *IDX,int *Index,QString *KohenName,int NGCount,QString *strTime,QString *RealKohenName);
	void			(*DLL_ClearNGInfoList)			(void);
	bool			(*DLL_PreNext)					(bool IsBack);
//	void			(*DLL_ErrorFormShow)			(void);		//D-20091106
	void			(*DLL_ErrorFormShow)			(int Code);	//A-20091106
	void			(*DLL_ErrorFormClose)			(void);
	void			(*DLL_OKCheckFormShow)			(void);
	void			(*DLL_OKCheckFormClose)			(void);
	QObject			*(*DLL_GetThreadInstance)		(void);
	bool			(*DLL_SaveLotNameFile)			(QString &LotName);
	bool			(*DLL_GetReviewEnable)			(void);
	void			(*DLL_SetReviewEnable)			(bool Enable);
	bool			(*DLL_IsAllCheckedFormShow)		(void);
	bool			(*DLL_IsUnloadCommentFormShow)	(void);
	bool			(*DLL_IsPreNext)				(void);
	bool			(*DLL_IsErrorFormShow)			(void);
	void			(*DLL_SetMessageFormLabel)		(QString &Message);
	void			(*DLL_SetMessageForm)			(QColor &TextColor,QColor &BackgroundColor);
	void			(*DLL_MessageFormShow)			(bool BlinkEnable);
	void			(*DLL_MessageFormClose)			(void);
	bool			(*DLL_SaveHistoryList)			(QTableWidget *W,QStringList &HeaderList,bool IsFirst);
	bool			(*DLL_GetShowPickupForm)		(void);
	bool			(*DLL_GetShowPickupEnable)		(void);
	void			(*DLL_SetShowPickupEnable)		(bool Enable);
	void			(*DLL_SetLogInfoHDNameList)		(QStringList *HDNameList);
	void			(*DLL_StartProcessCheckThread)	(bool Enable);
	QObject			*(*DLL_GetCheckThreadInstance)	(void);

	bool			(*DLL_SetMMCSettingList)		(QStringList &List);
	bool			(*DLL_GetShowOKMsg)				(void);
	bool			(*DLL_GetShowNGArea)			(void);
	int				(*DLL_GetPickupNGAreaNumbA)		(void);
	int				(*DLL_GetPickupNGAreaNumbB)		(void);
	int				(*DLL_GetPickupNGAreaNumbC)		(void);
	bool			(*DLL_GetNotShowEID)			(void);
	void			(*DLL_SetMMCParameter)			(QTableWidget *W,QStringList &HeaderList);
	bool			(*DLL_GetOKDoubleDone)			(void);
	bool			(*DLL_GetNGListControl)			(void);

	void			SetSaveFileName(QString FileName)			{	SaveFileName=FileName;			}
	QString			GetSaveFileName()							{	return SaveFileName;			}
	void			SetXmlConnectFileName(QString FileName)		{	XmlConnectFileName=FileName;	}
	QString			GetXmlConnectFileName()						{	return XmlConnectFileName;		}
	void			SetRepairSettingFileName(QString FileName)	{	RepairSettingFileName=FileName;	}
	QString			GetRepairSettingFileName()					{	return RepairSettingFileName;	}

	void			ColorSetting(QList<QPair<QString, QString> > &citemList);
	bool			XMLConnection		(QString strXMLFile,int Side=0);
	bool			XMLRetryConnection	(int Side=0);
	bool			XMLClose			(int Side=0);
	bool			XMLLotGetClose		(int Side=0);
	void			SetXMLFile			(int Type,QString *FileName)			{	XMLFile[Type]=FileName->toAscii();		}
	void			SetXMLFile			(int Type,QByteArray *FileName)			{	XMLFile[Type]=*FileName;				}
	QByteArray		GetXMLFile			(int Type)								{	return(XMLFile[Type]);					}
	void			SetXMLQNO1			(QString *QueryNO)						{	XMLQNO1=*QueryNO;						}
	QString			GetXMLQNO1			()										{	return(XMLQNO1);						}
	void			SetXMLQNO2			(QString *QueryNO)						{	XMLQNO2=*QueryNO;						}
	QString			GetXMLQNO2			()										{	return(XMLQNO2);						}
	void			SetXML				(QString *QueryXML)						{	QXML=QueryXML->toAscii();				}
	QByteArray		GetXML				()										{	return(QXML);							}
	void			SetMasterID			(SideType Type,QString MID)				{	MasterIDInType[Type]=MID;				}
	QString			GetMasterID			(SideType Type)							{	return(MasterIDInType[Type]);			}
	void			SetMasterName		(SideType Type,QString MNM)				{	MasterNMInType[Type]=MNM;				}
	QString			GetMasterName		(SideType Type)							{	return(MasterNMInType[Type]);			}
	void			SetLotID			(SideType Type,QString LID)				{	LotIDInType[Type]=LID;					}
	QString			GetLotID			(SideType Type)							{	return(LotIDInType[Type]);				}
	void			SetLotName			(SideType Type,QString LNM)				{	LotNMInType[Type]=LNM;					}
	QString			GetLotName			(SideType Type)							{	return(LotNMInType[Type]);				}
	void			SetCategoryID		(SideType Type,QString CID)				{	CategoryIDInType[Type]=CID;				}
	QString			GetCategoryID		(SideType Type)							{	return(CategoryIDInType[Type]);			}
	void			SetNGSortXY			(char *XY)								{	NGSortXY=XY;							}
	char		   *GetNGSortXY			()										{	return(NGSortXY);						}
	void			SetNGSortOrder		(char *Order)							{	NGSortOrder=Order;						}
	char		   *GetNGSortOrder		()										{	return(NGSortOrder);					}
	void			SetRes				(QString Res)							{	ResStr=Res;								}
	QString			GetRes				()										{	return(ResStr);							}
	void			SetListIndex		(int LSide,int LIndex)					{	ListIndex[LSide]=LIndex;				}
	int				GetListIndex		(int LSide)								{	return(ListIndex[LSide]);				}

	void			SetMachineRemark	(SideType Type,QString *MAR)			{	MachineRemarkInType[Type]=*MAR;			}
	QString			*GetMachineRemark	(SideType Type)							{	return(&MachineRemarkInType[Type]);		}
	void			SetHDNameList		(SideType Type,QStringList *HDNList)	{	HDNameListInType[Type]=*HDNList;		}
	QStringList		*GetHDNameList		(SideType Type)							{	return(&HDNameListInType[Type]);		}
	void			SetKohenNameList	(SideType Type,QStringList *KNameList)	{	KohenNameListInType[Type]=*KNameList;	}
	QStringList		*GetKohenNameList	(SideType Type)							{	return(&KohenNameListInType[Type]);		}
	void			SetInspectionID		(SideType Type,QString *EID)			{	InspectionIDInType[Type]=*EID;			}
	QString			*GetInspectionID	(SideType Type)							{	return(&InspectionIDInType[Type]);		}
	void			SetNGKohenNumb		(SideType Type,int NGKNumb)				{	NGKohenNumbInType[Type]=NGKNumb;		}
	int				GetNGKohenNumb		(SideType Type)							{	return(NGKohenNumbInType[Type]);		}
	void			SetNGNumb			(SideType Type,int NGNumb)				{	NGNumbInType[Type]=NGNumb;				}
	int				GetNGNumb			(SideType Type)							{	return(NGNumbInType[Type]);				}
	void			SetKohenNo			(SideType Type,QString *KNo)			{	KohenNoInType[Type]=*KNo;				}
	QString			*GetKohenNo			(SideType Type)							{	return(&KohenNoInType[Type]);			}
	void			SetNGNo				(SideType Type,int NGNo)				{	NGNoInType[Type]=NGNo;					}
	int				GetNGNo				(SideType Type)							{	return(NGNoInType[Type]);				}
	void			SetPCNo				(SideType Type,int PCNo)				{	PCNoInType[Type]=PCNo;					}
	int 			GetPCNo				(SideType Type)							{	return(PCNoInType[Type]);				}
	void			SetTaiouKohenNumb	(SideType Type,int TKNumb)				{	TaiouKohenNumbInType[Type]=TKNumb;		}
	int				GetTaiouKohenNumb	(SideType Type)							{	return(TaiouKohenNumbInType[Type]);		}
	void			SetNGPointX			(SideType Type,QString *NGPX)			{	NGPointXInType[Type]=*NGPX;				}
	QString			*GetNGPointX		(SideType Type)							{	return(&NGPointXInType[Type]);			}
	void			SetNGPointY			(SideType Type,QString *NGPY)			{	NGPointYInType[Type]=*NGPY;				}
	QString			*GetNGPointY		(SideType Type)							{	return(&NGPointYInType[Type]);			}
	void			SetRealKohenNo		(SideType Type,QString *KNo)			{	RealKohenNoInType[Type]=*KNo;			}
	QString			*GetRealKohenNo		(SideType Type)							{	return(&RealKohenNoInType[Type]);		}

	bool			LoadFile			(QString strPath,QStringList &strList);
	bool			SaveFile			(QString strPath,QStringList *strList);
	void			WriteRepairSetting	();

	void			SetImageDataUnit	(ImageDataUnit *IDUnit)		{	IDataUnitInBase=IDUnit;		}
	ImageDataUnit	*GetImageDataUnit	()							{	return(IDataUnitInBase);	}
	int				CheckXMLDataList	(SideType Type,QList<QByteArray> *RetXMLData);
	int				CheckXMLData		(QByteArray &PreStrXML,const QByteArray &CurStrXML);
//	void			SetRetXMLDataList	(SideType Type,QList<QByteArray> *RetXMLData);
	void			SetRetXMLDataList	(int Type,QList<QByteArray> *RetXMLData);
	QList<QByteArray> *GetRetXMLDataList(SideType Type);
	void			SetRetPCEDataList	(SideType Type,QList<QByteArray> *RetPCEData);
	QList<QByteArray> *GetRetPCEDataList(SideType Type);
	bool			XMLTagSelect		(QString *strQueryXml,QList<QByteArray> *selList,int iParent=0,int Side=0);
	bool			XMLTagToTagSelect	(QList<QByteArray> *strQueryXmlList,QList<QByteArray> *selList,int Side=0);
	bool			XMLSelect			(QByteArray *strTag,QList<QByteArray> *selList,int Side=0);
	bool			XMLLotGet			(QString *MasterCode,QList<QByteArray> *selList,int Side=0);
	bool			XMLMasterStart		(QString *MasterCode,QString *LotID,int Side=0);
	void			SetDataToTable		(QTableWidget *W,int row,int col,QVariant value);
	void			SetDataToTable		(QTableWidget *W,int row,int col,QVariant value,QColor Color);
	void			SetBothDataToTable	(QTableWidget *W);
	void			SetXMLDataToTable	(QTableWidget *W,int Row,int Index,SideType Type,QColor FieldColor);
	void			SetColorToTable		(QTableWidget *W,int Row,QColor FieldColor);
	QString			GetString			(const QString		*value,QString FirstStr,QString EndStr,int Index=0);	//文字列から目的のデータを切り取る
	QByteArray		GetString			(const QByteArray	*value,QString FirstStr,QString EndStr,int Index=0);	//文字列から目的のデータを切り取る
	QByteArray		GetString			(const QByteArray	*value,QString FirstStr,int Count=0);					//文字列から目的のデータを指定文字数分切り取る
	int				GetStringCount		(const QString *value,QString strData);								//文字列から目的のデータがいくつあるか数える
	QString			SearchXMLData		(QList<QByteArray> *XMLDataList,QString SearchStr,int Side);
	void			SetWorkerID			(QString *WID);
	QString			GetWorkerID			()							{	return(WorkerID);	}
	void			SetWorkerName		(QString *Name);
	QString			GetWorkerName		()							{	return(WorkerName);	}
//	bool			GetNGImage			(QTableWidget *W,int Row,QStringList *HeaderLabels,QImage *Image,int &ImageX,int &ImageY,int &ImageW,int &ImageH);
	bool			GetNGImage			(QTableWidget *W,int Row,int Index,QStringList *HeaderLabels,QImage *Image,int &ImageX,int &ImageY,int &ImageW,int &ImageH);
	bool			GetByte				(QFile *f,int ByteCnt,int &iRet);
	bool			GetByteArray		(QFile *f,int ByteCnt,QImage *Img);
	bool			PassByteArray		(QFile *f,int ByteCnt);
	bool			GetBinary			(QFile *f,int ByteCnt,QByteArray &Buffer);
	NGPointBaseList	*SetMasterNGParam	(int Index,int Width,int Height,int &ImageX,int &ImageY,int &ImageW,int &ImageH);
	bool			CheckJDTFile		(QString strNGJ,int Side);
	void			ShowHistoryList		(QTableWidget *TableWidget,int MasterCount,QStringList &HeaderLabels,int InsDataDialogFlag=-1);
//	void			ShowNGList			(QTableWidget *TableWidget,int NGCount,int XMLIndex1,int XMLIndex2,QStringList *HeaderLabels,int W,int H,int BothSide=0);
	int				ShowNGList			(QTableWidget *TableWidget,int NGCount,int XMLIndex1,int XMLIndex2,QStringList *HeaderLabels,int W,int H,int BothSide=0);
//	void			ShowNGListForVRS	(QTableWidget *TableWidget,int NGCount,int XMLIndex,QStringList *HeaderLabels,int W,int H,int BothSide=0);
	void			ShowNGListForVRS	(QTableWidget *TableWidget,int NGCount,int XMLIndex1,int XMLIndex2,QStringList *HeaderLabels,int W,int H,int BothSide=0);
	bool			CheckInsideNGPoint	(int X,int Y,int W,int H,int wPG);
///	bool			isCheckedNGPoint	(int pNumb,int X,int Y,int Side);
	bool			isCheckedNGPoint	(int Side);
	QString			CreateFunctionStr(int FKey);
	bool			DeleteXMLStr(int Side, QString &str);
	bool			CheckedXML			(QString &strAppXML,QString &ErrMsg);
	bool			CheckedFunction		(int KeyNumber,bool FChecked,int DelFKey,QString *strDelTag,QString *strUpXML,int Side);
	bool			CheckFKey			(int &FK,int Side);
	QTreeWidgetItem *CheckTrMasterList	(QTreeWidgetItem *item,int col,int data);

	QByteArray      MAC;
	void			xmlMacGet(QByteArray Info, QByteArray &MAC);

	void			SetPieceInfoData	(SideType Type);

	int GetX();
	int GetY();
	int GetWidth();
	int GetHeight();

	static	bool	HaspCheck			(QString strKey);

	void SetSigmoid(double Volume,int Bright,int BrightArray[]);

	virtual void SetCheckEditEnable	(bool Check){};
	virtual void SetWaitTime		(int Time)	{};
	virtual void LoadLocation				()	{};
	virtual void SaveLocation				()	{};
	virtual void WindowDefault				()	{};
	virtual void MainFrameDefault			()	{};
	virtual void dwCameraImageDefault		()	{};
	virtual void dwMasterImage1Default		()	{};
	virtual void dwMasterImage2Default		()	{};
	virtual void dwNGMasterPixDefault		()	{};
	virtual void dwNGInspectionPixDefault	()	{};
	virtual void dwHistoryListDefault		()	{};
	virtual void dwNGListDefault			()	{};

	bool	GetOutlineOffset(int MacID,QList<int> *DataX,QList<int> *DataY);

	NPListPack<NGPointList> *GetNGPListForVRS(int Side,int ListCount);

	//NG画像の保存
	bool	SaveNGImage(QString InsID);
	bool	SaveNGImage(int Both,int Page,int Cnt,QString InsID);
	bool	SaveNGImage(QTableWidget *W,QStringList *HeaderLabels);

	//GeneralSetting内で使用
	QStringList	GetRepairSettingList()					{	return RepairSettingList;	}
	void		SetRepairSettingList(QStringList List)	{	RepairSettingList=List;		}
	QString		GetMasterDir()						{	return MasterDir;				}
	void		SetMasterDir(QString Dir)			{	MasterDir	=Dir;				}
	bool		GetNGBlink()						{	return bNGBlink;				}
	void		SetNGBlink(bool NGBlink)			{	bNGBlink	=NGBlink;			}
	int			GetCheckedNumb()					{	return CheckedNumb;				}
	void		SetCheckedNumb(int Numb)			{	CheckedNumb	=Numb;				}
	bool		GetShowOK()							{	return bShowOK;					}
	void		SetShowOK(bool ShowOK)				{	bShowOK		=ShowOK;			}
	int			GetImgRate()						{	return ImgRate;					}
	void		SetImgRate(int Rate)				{	ImgRate		=Rate;				}
	int			GetNGWaitTime()						{	return NGWaitTime;				}
	void		SetNGWaitTime(int WaitTime)			{	NGWaitTime	=WaitTime;			}
	double		GetSigVolume()						{	return SigVolume;				}
	void		SetSigVolume(double	Volume)			{	SigVolume=Volume;				}
	int			GetSigBright()						{	return SigBright;				}
	void		SetSigBright(int Bright)			{	SigBright	=Bright;			}
	bool		GetEachPieces()						{	return bEachPieces;				}
	void		SetEachPieces(bool Enable)			{	bEachPieces=Enable;				}
	int			GetMImageSplitter()					{	return MImageSplitter;			}
	void		SetMImageSplitter(int Splitter)		{	MImageSplitter=Splitter;		}
	QString		GetPieceColorString()				{	return PieceColorString;		}
	void		SetPieceColorString(QString Str)	{	PieceColorString=Str;			}
	bool		GetEnableNGPieceChange()			{	return bEnableNGPieceChange;	}
	void		SetEnableNGPieceChange(bool Enable)	{	bEnableNGPieceChange=Enable;	}
	QString		GetSaveDirNGImage()					{	return SaveDirNGImage;			}
	void		SetSaveDirNGImage(QString Dir)		{	SaveDirNGImage	=Dir;			}
	bool		GetOutputDebugLog()					{	return bOutputDebugLog;			}
	void		SetOutputDebugLog(bool Enable)		{	bOutputDebugLog=Enable;			}
	bool		GetOutputXMLData()					{	return bOutputXMLData;			}
	void		SetOutputXMLData(bool Enable)		{	bOutputXMLData=Enable;			}
	bool		GetShowInsDataMsg()					{	return bShowInsDataMsg;			}
	void		SetShowInsDataMsg(bool Enable)		{	bShowInsDataMsg=Enable;			}
	int			GetListScrollRowCnt()				{	return ListScrollRowCnt;		}
	void		SetListScrollRowCnt(int Row)		{	ListScrollRowCnt=Row;			}
	QString		GetOnlyFColor()						{	return OnlyFColor;				}
	void		SetOnlyFColor(QString strColor)		{	OnlyFColor=strColor;			}
	QString		GetOnlyBColor()						{	return OnlyBColor;				}
	void		SetOnlyBColor(QString strColor)		{	OnlyBColor=strColor;			}
	QString		GetFBColor()						{	return FBColor;					}
	void		SetFBColor(QString strColor)		{	FBColor=strColor;				}
	int			GetNGImageOffset()					{	return NGImageOffset;			}
	void		SetNGImageOffset(int Value)			{	NGImageOffset=Value;			}
	int			GetPlusRed()						{	return PlusRed;					}
	void		SetPlusRed(int Value)				{	PlusRed=Value;					}
	int			GetPlusGreen()						{	return PlusGreen;				}
	void		SetPlusGreen(int Value)				{	PlusGreen=Value;				}
	int			GetPlusBlue()						{	return PlusBlue;				}
	void		SetPlusBlue(int Value)				{	PlusBlue=Value;					}

	//メイン画面内の設定項目
	bool		GetReverseOrderDisplay()			{	return bReverseOrderDisplay;	}
	void		SetReverseOrderDisplay(bool Enable)	{	bReverseOrderDisplay=Enable;	}
	bool		GetNextCheck()						{	return bNextCheck;				}
	void		SetNextCheck(bool Enable)			{	bNextCheck=Enable;				}
	bool		GetEnterCheck()						{	return bEnterCheck;				}
	void		SetEnterCheck(bool Enable)			{	bEnterCheck=Enable;				}
	bool		GetNotShowHaltFlag()				{	return NotShowHaltFlag;			}
	void		SetNotShowHaltFlag(bool Enable)		{	NotShowHaltFlag=Enable;			}
	bool		GetNotShowHalt()					{	return bNotShowHalt;			}
	void		SetNotShowHalt(bool Enable)			{	bNotShowHalt=Enable;			}

	int			GetPreINM()	{	return PreINM;	}
	int			GetCurINM()	{	return CurINM;	}

	QString		GetEmptyARA	(int X,int Y);

	//デバッグログ出力
	bool	OpenDebugLogFile	(QString OutputDir,QString OutputFileName);
	void	WriteDebugLogFile	(const QString &WriteMsg);
	QFile		&GetDebugLogFile()			{	return DebugLogFile;		}
	QTextStream &GetDebugLogFileStream()	{	return DebugLogFileStream;	}

	//数値リストの中の数値をすべてビットにして返す
	int		GetListNumbers(const QStringList &List);

	mtQTableWidget *GetNGList		()								{	return twNGListInBase;				}
	void			SetNGList		(mtQTableWidget *twNGList)		{	twNGListInBase=twNGList;			}
	QTableWidget   *GetHistoryList	()								{	return twHistoryListInBase;			}
	void			SetHistoryList	(QTableWidget *twHistoryList)	{	twHistoryListInBase=twHistoryList;	}
	QStringList		GetHFieldNames	()								{	return HFieldNamesInBase;			}
	void			SetHFieldNames	(QStringList HFieldNames)		{	HFieldNamesInBase=HFieldNames;		}

protected:
	void	SetPG		(int Page)	{	PG=Page;	}
	int		GetPG		()			{	return PG;	}

//private slots:

private:
	int					PG;
	ImageDataUnit		*IDataUnitInBase;
	QString				HostName;
	QString				port;
	QString				XMLFilePath;
	QString				XMLFileDir;
	QByteArray			XMLFile[2];
	QString				XMLQNO1;
	QString				XMLQNO2;
	QByteArray			QXML;
	QList<QByteArray>	RetXMLFDataList;
	QList<QByteArray>	RetXMLBDataList;
	QList<QByteArray>	RetPCEFDataList;
	QList<QByteArray>	RetPCEBDataList;
	QByteArray			Msg;
	QString				WorkerID;
	QString				WorkerName;
	QFile				NGFile;
	int					iIDX;
	int					iIndex;
	QList<QList<int> >	IDXJDT;
	QString				MasterIDInType[2];
	QString				MasterNMInType[2];
	QString				LotIDInType[2];
	QString				LotNMInType[2];
	QString				CategoryIDInType[2];
	char			   *NGSortXY;
	char			   *NGSortOrder;
	QString				ResStr;
	int					ListIndex[2];

	QString				MachineRemarkInType[2];
	QStringList			HDNameListInType[2];
	QStringList			KohenNameListInType[2];
	QString				InspectionIDInType[2];
	int					NGKohenNumbInType[2];
	int					NGNumbInType[2];
	QString				KohenNoInType[2];
	int					NGNoInType[2];
	int 				PCNoInType[2];
	int					TaiouKohenNumbInType[2];
	QString				NGPointXInType[2];
	QString				NGPointYInType[2];
	QString				RealKohenNoInType[2];

	XMLElement			*ISTElement[2];
	int					**BuffPG;
	int					*ImgCnt;

	int					RAreaX,RAreaY;
	int					NGIX1,NGIY1,NGIX2,NGIY2;

	//GeneralSetting内で使用
	QStringList		RepairSettingList;
	QString			MasterDir;
	bool			bNGBlink;
	int				CheckedNumb;
	bool			bShowOK;
	int				ImgRate;
	int				NGWaitTime;
	double			SigVolume;
	int				SigBright;
	bool			bEachPieces;
	int				MImageSplitter;
	QString			PieceColorString;
	bool			bEnableNGPieceChange;
	QString			SaveDirNGImage;
	bool			bOutputDebugLog;
	bool			bOutputXMLData;
	bool			bShowInsDataMsg;
	int				ListScrollRowCnt;
	QString			OnlyFColor;
	QString			OnlyBColor;
	QString			FBColor;
	int				NGImageOffset;
	int				PlusRed;
	int				PlusGreen;
	int				PlusBlue;
	//メイン画面内の設定項目
	bool			bReverseOrderDisplay;
	bool			bNextCheck;
	bool			bEnterCheck;
	bool			NotShowHaltFlag;
	bool			bNotShowHalt;

	int				PreINM,CurINM;

	InspectionDataForm InsDataDialog;	//検査データのSelect結果を表示するダイアログ

	//NGPデータ判断
	enum	NGPCompair{
				 NotMatch	=-1
				,Less		=0
				,Match		=1
				,Large		=2
	};

	XMLElement			**NGITagList[2];
	QByteArray			**JDTDataList[2];
	int					wjdtCount;
	int					JDTDataListCountPage[2];
	int					JDTDataListCountJpg[2][10];

	void				ComSortNGP		(int m_dcnt, XMLElement **m_data,int T);
	void				ComSortNGI		(int m_dcnt, XMLElement **m_data,int T);
	int					GetSortValueNGP	(XMLElement *Src,int T);
	int					GetSortValueNGP	(int XY,int P,int T);
	int					GetSortValueNGI	(XMLElement *Src,int T);
	int					GetSortValue	(XMLElement *Src,QString strAttr);
	NGPCompair			CompairSortValue(int X,int Y,int P,int T);

	void				ComSortXML		(int m_dcnt, QList<QByteArray> &XMLData);
	int					GetSortValueEID	(QByteArray *Src)	{	return GetString(Src,"EID=\"","\"").toInt();	}

	QStringList			GetPieceNMList	(int X,int Y,int W,int H,int Page,int Type);

	//NG画像保存ワーク
	int		*vNGI;
	int		*vSide;
	QString *vARA;
	int		*vIDX;
	int		*vIndex;
	QString *vRealARA;

	//デバッグログ出力
	QFile	DebugLogFile;
	QTextStream DebugLogFileStream;

	//子クラスのインスタンス保持用
	mtQTableWidget	*twNGListInBase;
	QTableWidget	*twHistoryListInBase;
	QStringList		HFieldNamesInBase;

	QString		SaveFileName;			//"save.dat"
	QString		XmlConnectFileName;		//"XmlConnect.dat"
	QString		RepairSettingFileName;	//"RepairSetting.dat"
};

#endif // REPAIRBASE_H

