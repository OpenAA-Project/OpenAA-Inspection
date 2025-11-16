/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\Sequence\XSequenceFile.h
** Author : YYYYYYYYYY
****************************************************************************-**/


//---------------------------------------------------------------------------

#ifndef XSequenceFileH
#define XSequenceFileH
//---------------------------------------------------------------------------

//#include "XUniversalDefinition.h"
//#include <typeinfo.h>
#include <QDataStream>
#include <QColor>	
#include <QFont>	
#include "NList.h"
#include "XGeneralFunc.h"
#include "XSimulateTimingParameter.h"
#include "XTypeDef.h"

#define SeqTimingFileVersion


//============================================================
class   AddedVectorBase : public NPList<AddedVectorBase>
{
  public:
    AddedVectorBase(void){}
    virtual ~AddedVectorBase(void){}

    virtual BYTE    GetID(void)     const   =0;
    virtual bool    Read(QDataStream *is)   =0;
    virtual bool    Write(QDataStream *os)  =0;
    int     GetDataLength(void)     const;
//    virtual void    Draw(double ZoomRate ,VInt64 &topx, int topy, TCanvas *canvas)=0;

  protected:
//    void    DrawArrow(TCanvas *canvas ,int startx,int starty,int endx, int endy, int ArrowSize);
};

class   AddedVectorSingleArrow : public AddedVectorBase
{
  public:
    int64  StartX  ;
    int     StartY  ;
    int64  ArrowedX;
    int     ArrowedY;
    BYTE    LineWidth;
    QColor  LineColor;
    int     ArrowSize;

    AddedVectorSingleArrow(void);

    virtual BYTE GetID(void)    const   {   return(1);  }
    virtual bool    Read(QDataStream *is);
    virtual bool    Write(QDataStream *os);
///    virtual void    Draw(double ZoomRate ,VInt64 &topx, int topy, TCanvas *canvas);	//D-20051026
};

class   AddedVectorBothArrow : public AddedVectorBase
{
  public:
    int64  StartX;
    int     StartY;
    int64  EndX  ;
    int     EndY  ;
    int     LineWidth;
    QColor  LineColor;
    int     ArrowSize;

    AddedVectorBothArrow(void);
    virtual BYTE GetID(void)    const   {   return(2);  }
    virtual bool    Read(QDataStream *is);
    virtual bool    Write(QDataStream *os);
///    virtual void    Draw(double ZoomRate ,VInt64 &topx, int topy, TCanvas *canvas);	//D-20051026
};

class   AddedVectorFontChar : public AddedVectorBase
{
  public:
    int64      StartX  ;
    int         StartY  ;
    QString  Character;
    QColor      FontColor;
    QString  FontName;
    BYTE        FontCharSet;
    int         FontSize;
///    TFontStyles FontStyle;	//D-20051026
    float       Angle;

    AddedVectorFontChar(void);
    virtual BYTE GetID(void)    const   {   return(3);  }
    virtual bool    Read(QDataStream *is);
    virtual bool    Write(QDataStream *os);
///    virtual void    Draw(double ZoomRate ,VInt64 &topx, int topy, TCanvas *canvas);	//D-20051026
};

//============================================================










class   Operand;

/*  履歴フォーマット

ヘッダ
    １バイト    バージョン番号
    １バイト    シーケンス数
    ２バイト    命名オペランド数
    ４バイト    日時
    ８バイト    100msの間のクロック数

シーケンス
    １バイト    シーケンス種類
    １バイト    シーケンス番号
    １バイト    シーケンス名称バイト数（最後のヌルコードを含む）
    ｎバイト    名称

命名オペランド
    １バイト    オペランド種類
    １バイト    オペランド番号
    ８バイト    予備コード
    １バイト    名称バイト数（最後のヌルコードを含む）
    ｎバイト    名称


履歴データ
    ２バイト    データサイズ
    ８バイト    クロック時刻
    ４バイト    開始からの時間（ｍｓ）
    １バイト    シーケンス番号
    ２バイト    ライン番号
    １バイト    オペランド種類
    １バイト    オペランド番号
    １ビット    フラグ状態（１：ＯＮ、０：ＯＦＦ）
    ３ビット    変更要因
    ｎバイト    変更後のデータ

*/

struct  __TimingFileHeader
{
    BYTE    Ver;
    BYTE    SeqNumb;
    WORD    NamedOperandNumb;
    DWORD   CreatedTime;
    int64   ClockPerSec;        //100msでのクロック数
};

struct  __TimingSeqHeader
{
    BYTE    SType;
    BYTE    SCode;
    BYTE    NameLen;
};

enum    __TimingOperandKind
{
     __TOK_None
    ,__TOK_IO
    ,__TOK_Bit
    ,__TOK_Word
    ,__TOK_Float
    ,__TOK_String
    ,__TOK_Comm
    ,__TOK_Lanvar
    ,__TOK_Fifo
};

struct  __TimingOperandHeader
{
    BYTE    OType;              //200以降のとき、ユーザー定義オペランド
                                //201:Binary , 202:Word , 203:String
    BYTE    ONumber;            //ユーザー定義のときオペランドＩＤ
    union{
        struct{
            BYTE    BoardNumb;
            BYTE    PortNumb;
            BYTE    BitNumb;
            }ForIO;
        struct{
            BYTE    CommPort;
            int     BPS;
            BYTE    Parity;
            BYTE    Stopbit;
            BYTE    Character;
            }ForComm;
        };
    BYTE    NameLen;
    __TimingOperandKind Kind;   //ユーザー定義のオペランドのとき使う
    char    Explain[256];
    int     OpeExtendByte;      //拡張データバイト数

    __TimingOperandHeader(void);
};

struct  __TimingOperandGroup
{
    BYTE    OType;
    BYTE    ONumber;
};

struct  __TimingOperandLanvar
{
    char    IP[32];
};


class   SSOperandClass : public NPList<SSOperandClass>
{
  public:
    struct  __TimingOperandHeader   Data;
    QString                         Name;

    struct  __TimingOperandGroup    *GroupDetail;
    struct  __TimingOperandLanvar   *LanvarDetail;
    int     DetailNumb;

    SSOperandClass(void);
    ~SSOperandClass(void);

    SSOperandClass  &operator=(Operand &src);

    QString  GetKindName(void);
    QString  GetName(void);
};


struct  __TimingDataHeader
{
    WORD    DataSize;
    int64   Clocks;         // 変更されたときのCPUクロック値
    DWORD   TickCount;		// 変更されたときのミリセカンド
    BYTE    SeqCode;
    WORD    MLine;			// 変更されたときのシーケンス行
    BYTE    OType;          //201：ユーザー定義のバイナリ信号、202：ユーザー定義のワード信号
    BYTE    ONumber;        //描画データのとき、描画種類
    int     Flag:2;
    int     Cause:4;
    int     DType:4;        //データの種類 1:int , 2:AnsiString , 3:BYTE block
                            //             4:パラメータ設定データ（データサイズ以外は無効）
                            //             5:描画データ  OType=描画種類
};

struct   __TimingSeq
{
    struct  __TimingSeqHeader   Header;
    QString                     Name;
};

struct  __TimingOperand
{
    __TimingOperandHeader       Header;
    QString                     Name;
};


class   LoadedTimingSlice : public NPList<LoadedTimingSlice>
{
  public:
    struct  __TimingDataHeader  TDHeader;
    union{
        struct{
            int     ByteLen;
            BYTE    *Data;
            };
        int D;
        };
    LoadedTimingSlice(void);
    ~LoadedTimingSlice(void);

    int GetInt(void){   return(D);  }
    QString  GetString(void);

    int     GetDataByte(void){  return(ByteLen);    }
    BYTE    *GetData(void){     return(Data);   }

    bool    Read(QDataStream *rfile);
    bool    Write(QDataStream *wfile);
};

class   SSTimingList : public NPList<SSTimingList>
{
  public:
    Operand         *Point;
    SSOperandClass  *UserOpe;   //どちらかがＮＵＬＬでない

    enum    DataKind{
         __STL_UnKnown
        ,__STL_Binary
        ,__STL_Word
        ,__STL_Float
        ,__STL_String
        }Kind;
    long double  MaxData;
    long double  MinData;
    NPListPack<LoadedTimingSlice>   TimingData;
    LoadedTimingSlice   **TimingPointer;
    int                 TimingNumb;
    int                 ItemLineWidth;
    QColor              ItemLineColor;

    SSTimingList(void);
    ~SSTimingList(void);

    LoadedTimingSlice   *GetTopSlice(int64 &startTime);
    LoadedTimingSlice   *GetPrevSlice(int64 &startTime);
    void    GetMinMaxRange(long double &MinData, long double &MaxData);
    void    BuildMinMaxRange(void);

    void    BuildTimingTable(void);
    LoadedTimingSlice   *GetTopSliceLess(int64 &startTime);
};

class   SSTimingFlowList : public NPList<SSTimingFlowList>
{
  public:
    SSTimingList        *List;
    LoadedTimingSlice   *Point;

    SSTimingFlowList(void)  {   List=NULL;  Point=NULL; }
    ~SSTimingFlowList(void) {   List=NULL;  Point=NULL; }
};


class   LoadedTimingFile
{
  public:
    struct  __TimingFileHeader      FileHeader;
    struct   __TimingSeq            *SeqData;
    NPListPack<SSOperandClass>      OpeData;
    NPListPack<SSTimingList>        LBase;
    NPListPack<SSTimingFlowList>    FlowList;   //順番を生成する

    NPListPack<AddedVectorBase> AddedVector;
    SeqTimingParameter  NowParam;

    LoadedTimingFile(void);
    ~LoadedTimingFile(void);

    int     Initial(void);
    bool    Read(QDataStream *rfile);
    bool    Write(QDataStream *wfile);

    bool    ReadParam(QDataStream *rfile);
    bool    WriteParam(QDataStream *rfile);

    bool    Write(QDataStream *wfile ,SeqTimingParameter &param);
    bool    Write(QDataStream *wfile ,AddedVectorBase *v);	//D-20051026

    SSTimingFlowList    *GetTopFlow(int64 &startTime);
    int     GetUserSignalNumb(void);
};

//============================================================

bool    WriteString(QString data , QDataStream *os);
bool    ReadString(QString &data , QDataStream *is);
bool    WriteStrings(QString *data , QDataStream *os);
bool    ReadStrings(QString *data, QDataStream *is);


#endif
