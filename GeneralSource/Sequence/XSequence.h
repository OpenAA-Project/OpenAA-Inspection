/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\Sequence\XSequence.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#ifndef XSequenceH
#define XSequenceH

#include <QtSerialPort/QSerialPort>
#include <QLibrary>
#include <QMutex>
#include"NList.h"
#include "XSequenceFile.h"
#include "XFifoClass.h"
#include <time.h>
#include "XTypeDef.h"	

#include "XServiceForLayers.h"

#define MaxCommBuffSize 256
#define MaxMomoryRegisterSize   256

class	QApplication;
class	PIOClass;
class	DLLVarInterface;
class	OutSequenceYesNo	;
class	OutSequenceShowYesNo;
class	OutSequenceShow		;
class	OutSequenceShowOK	;
class	OutSequenceMessage	;
class	OutSequenceInput	;


#define KindCodeIO          1
#define KindCodeComm        2
#define KindCodeBit         3
#define KindCodeWord        4
#define KindCodeString      5
#define KindCodeSpecial     6
#define KindCodeSpeicalBit  7
#define KindCodeSpeicalString	19
#define KindCodeSpeicalFloat	20
#define KindCodeNumber      8
#define KindCodeCharacter   9
#define KindCodeGroup       10
#define KindCodeLanvar      11
#define KindCodeFifo        12
#define KindCodeDLLVar      13
#define KindCodeFloat       14
#define KindCodeLocalBit    15
#define KindCodeLocalWord   16
#define KindCodeLocalString 17
#define KindCodeLocalFloat  18

class   LocalReg;
class   SequenceStock;
class   Sequence;
class   Operand ;
class   FlagExecuted;
class	QextSerialPort;
class	SeqControl;
class	SeqLocalParam;
class	ThreadSequence;
class	LayersBase;

///typedef unsigned short WORD;	//A-20051026

//====================================================================

class   OpeChangeListBase
{
  public:
    int64		Clocks;					// 変更されたときのCPUクロック値
    DWORD       TickCount;				// 変更されたときのミリセカンド
    Sequence    *Parent;				// 変更されたときのシーケンスページ
    int         MLine;					// 変更されたときのシーケンス行
    Operand     *Ope;                   // 変更されたオペランド
    enum    ForceChange{
         _FromSequence      =1
        ,_FromInputDevice   =2
        ,_FromInputManual   =3
        }Cause;             //変更の要因
    bool    WriteMode;

	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    OpeChangeListBase(void){    Ope=NULL;	Clocks=0;   TickCount=0;	Parent=NULL;	MLine=0;	Cause=_FromSequence;	WriteMode=false;    }

    virtual void       SetData(int d       ,Sequence *parent ,ForceChange c ,bool writemode)=0;
    virtual void       SetData(const QString &d,Sequence *parent ,ForceChange c ,bool writemode)=0;
    virtual void       GetListData(int        &d)=0;
    virtual void       GetListData(QString &d)=0;
};


const   int MaxOCLISTNUMB=1000;

enum    ExeHistAttr
{
     EHA_OnlyExec
    ,EHA_AllPIO
    ,EHA_Never
};

bool    WriteString(QString data , FILE *os);
bool    ReadString(QString &data , FILE *is);
class	GUIDirectMessage;

/*----------------------------------------------------------------------------*/
//  1.日本語名
//
//  2.概要
//
//  3.機能説明
//
//  4.備考
//
/*----------------------------------------------------------------------------*/
class   Operand
{
  public:
    QString    Name;
    int     ID;
    QString  Comment;
	SeqControl	*BaseParent;

	Operand(SeqControl *baseParent);
    virtual ~Operand(void);

    virtual QString  GetComment(void){   return(Comment);    }
    virtual void        SetComment(const QString &comment);
    void    SetName(QString &name);
    void    SetID(int id);
    virtual QString    GetName(void)=0;
    virtual const char    *GetKindName(void)=0;
    virtual int     GetKindCode(void)=0;
	SeqControl		*GetSeqControl(void){	return BaseParent;	}
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    int     GetID(void){    return(ID); }
    virtual bool    Load(char buff[])=0;
    virtual int       GetNumeric(bool SrcReconstruct=false)=0;
    virtual int       GetStringCount(void)=0;
    virtual QByteArray   GetString(bool ThreadMode=true)=0;
	virtual QByteArray   GetBufferingString(void){	return GetString();	}
    virtual void      SetData(int d)=0;
	virtual void      SetFloat(double d){	SetData((int)d);	}
    virtual void      SetData(const QByteArray &d)=0;
	void      SetData(const QString &d);
    virtual bool      IsGetEnabled(void)=0;
    virtual void      FlushSource(void){}
    virtual double     GetFloat(bool SrcReconstruct=false)=0;
    virtual Operand     *MakeDup(LocalReg *DestLReg)=0;
    void       Copy(Operand *dest);
    virtual ExeHistAttr    GetHistAttr(void)=0;
    virtual int     GetPreDataBitSize(void)=0;
    virtual bool    SaveBinHeader(FILE *file);
    virtual bool    LoadBinHeader(FILE *file);

    virtual bool       LetSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)=0;
    virtual bool       LetBSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)=0;
    virtual bool       AddSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)=0;
    virtual bool       SubSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)=0;
    virtual bool       AndSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)=0;
    virtual bool       OrSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)=0;
    virtual bool       XorSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)=0;
    virtual bool       NotSeq(Sequence *parent,bool FlagConnectedMode )=0;
    virtual bool       FlushSeq(Sequence *parent,bool FlagConnectedMode)=0;
    virtual bool       AllocSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)=0;
    virtual bool       IndSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)=0;
    virtual bool       BitloadSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src1 ,Operand *src2 ,Operand *src3)=0;
    virtual bool       FlagSeq(Sequence *parent,bool FlagConnectedMode)=0;
    virtual bool       CAndSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)=0;
    virtual bool       COrSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)=0;
    virtual bool       CXorSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)=0;
    virtual bool       EqualSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)=0;
    virtual bool       ZoneSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src1,Operand *src2)=0;
    virtual bool       PartEqSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)=0;
    virtual bool       UnequalSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)=0;
    virtual bool       GreaterSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)=0;
    virtual bool       LargeSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)=0;
    virtual bool       LessSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)=0;
    virtual bool       SmallSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)=0;
    virtual bool       MultSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)=0;
    virtual bool       DivSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)=0;
    virtual bool       ModSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)=0;
    virtual bool       StrMoveSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src1 ,Operand *src2)=0;
    virtual bool       LowerSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)=0;
    virtual bool       UpperSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)=0;
    virtual bool       StateSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)=0;
    virtual bool       TWSetSeq(Sequence *parent,bool FlagConnectedMode)=0;
    virtual bool       FSetSeq(Sequence *parent,bool FlagConnectedMode)=0;
    virtual bool       FResetSeq(Sequence *parent,bool FlagConnectedMode)=0;
    virtual bool       RxTimeoutSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src1 ,Operand *src2)=0;
    virtual bool       StrLenSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)=0;

    virtual bool       AddFileSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)=0;
    virtual bool       OpenLFileSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)=0;
    virtual bool       LoadFileSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)=0;
    virtual bool       CloseFileSeq(Sequence *parent,bool FlagConnectedMode)=0;
    virtual bool       DeleteFileSeq(Sequence *parent,bool FlagConnectedMode)=0;
    virtual bool       BPrintSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)=0;
    virtual bool       BScanSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)=0;
    virtual bool       InputFromString(Sequence *parent,QString &Src)=0;
    virtual bool       FloatNumSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)=0;

	virtual	void		TransmitDirectly(GUIDirectMessage *packet){}
};

/*----------------------------------------------------------------------------*/
//  1.日本語名
//
//  2.概要
//
//  3.機能説明
//
//  4.備考
//
/*----------------------------------------------------------------------------*/
class   IOOperand   : public Operand ,public NPList<IOOperand>
{
    WORD    hPIO_DRV;
    int     OutData;    //-1:未設定     0,1:出力済み
  public:
    int     BoardNumber;
    int     PortNumber;
    int     BitNumber;
    bool    InMode;

	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
	IOOperand(SeqControl *BaseParent);
    QString    GetName(void)	override;
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    virtual QString  GetComment(void)				override;
    virtual const	char    *GetKindName(void)		override	{ return("I/O");  }
    virtual int     GetKindCode(void)				override	{  return(KindCodeIO);     }
    bool    Load(char buff[])						override;
    int    GetNumeric(bool SrcReconstruct=false)	override;
    int    GetStringCount(void)						override;
    QByteArray   GetString(bool ThreadMode=true)	override;
    double     GetFloat(bool SrcReconstruct=false)	override	{    return(GetNumeric(SrcReconstruct)); }
    void      SetData(int d)						override;
    void      SetData(const QByteArray &d)			override;
    virtual Operand     *MakeDup(LocalReg *)		override	{     return(NULL);   }

    int       GetOutData(void)						{    return(OutData);    }
    bool      IsGetEnabled(void)					override{  return(true);   }
    ExeHistAttr    GetHistAttr(void)				override{      return(EHA_AllPIO);     }
    int     GetPreDataBitSize(void)					override{    return(1);      }
    bool    SaveBinHeader(FILE *file)				override;
    bool    LoadBinHeader(FILE *file)				override;

    bool       LetSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       LetBSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       AddSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       SubSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       AndSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       OrSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)		override;
    bool       XorSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       NotSeq(Sequence *parent,bool FlagConnectedMode)					override;
    bool       FlushSeq(Sequence *parent,bool FlagConnectedMode)				override;
    bool       AllocSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       IndSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       BitloadSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src1 ,Operand *src2 ,Operand *src3)	override;
    bool       FlagSeq(Sequence *parent,bool FlagConnectedMode)					override;
    bool       CAndSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       COrSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       CXorSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       EqualSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       ZoneSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src1,Operand *src2)		override;
    bool       PartEqSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       UnequalSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)override;
    bool       GreaterSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)override;
    bool       LargeSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       LessSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       SmallSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       MultSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       DivSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       ModSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       StrMoveSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src1 ,Operand *src2)	override;
    bool       LowerSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       UpperSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       StateSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       TWSetSeq(Sequence *parent,bool FlagConnectedMode)				override;
    bool       FSetSeq(Sequence *parent,bool FlagConnectedMode)					override;
    bool       FResetSeq(Sequence *parent,bool FlagConnectedMode)				override;
    bool       RxTimeoutSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src1 ,Operand *src2)	override;
    bool       StrLenSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       AddFileSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)override;
    bool       OpenLFileSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       LoadFileSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       CloseFileSeq(Sequence *parent,bool FlagConnectedMode)			override;
    bool       DeleteFileSeq(Sequence *parent,bool FlagConnectedMode)			override;
    bool       BPrintSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       BScanSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       InputFromString(Sequence *parent,QString &Src)					override;
    bool       FloatNumSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)override;

  private:
    void    Initial(void);
};

/*----------------------------------------------------------------------------*/
//  1.日本語名
//
//  2.概要
//
//  3.機能説明
//
//  4.備考
//
/*----------------------------------------------------------------------------*/
#define CommCharNumb    16

class   CommOperand : public QObject ,public Operand,public NPList<CommOperand>
{
	Q_OBJECT

	QSerialPort	*sio;
  public:
    int CommPort;
    int BPS;
    int Parity;
    int Stopbit;
    int Character;
    char	*TermChar[CommCharNumb];
    int     TermNumb;
    char	*IgnoreChar[CommCharNumb];
    int     IgnoreNumb;
    int     NoTermRxByte;
    char    RxBuff[MaxCommBuffSize+1];
    int     RxTop;
    int     RxTimeoutAddress;
    int     RxTimeoutMilisec;
    DWORD   IntoTime;
    bool    RsCs;

	bool	IsOpened(void);
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    CommOperand(SeqControl *BaseParent);
    ~CommOperand(void);

    void	Initial(void);
    QString    GetName(void)	override;
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    virtual const	char    *GetKindName(void)	override{ return("Comm");  }
    virtual int     GetKindCode(void)			override{  return(KindCodeComm);   }
    bool    Load(char buff[])					override;
    int   GetNumeric(bool SrcReconstruct=false)	override;
    int   GetStringCount(void)					override;
    QByteArray   GetString(bool ThreadMode=true)override;
	QByteArray   GetBufferingString(void)		override;
    void      SetData(int d)					override;
    void      SetData(const QByteArray &d)		override;
    bool      IsGetEnabled(void)				override{  return(true);   }
    double     GetFloat(bool SrcReconstruct=false)	override{    return(GetNumeric(SrcReconstruct)); }
    virtual Operand     *MakeDup(LocalReg *)	override{     return(NULL);   }
    ExeHistAttr    GetHistAttr(void)			override{      return(EHA_OnlyExec);   }
    int     GetPreDataBitSize(void)				override{    return(-1);      }
    bool    SaveBinHeader(FILE *file)			override;
    bool    LoadBinHeader(FILE *file)			override;

    bool       LetSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       LetBSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       AddSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       SubSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       AndSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       OrSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)		override;
    bool       XorSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       NotSeq(Sequence *parent,bool FlagConnectedMode)					override;
    bool       FlushSeq(Sequence *parent,bool FlagConnectedMode)				override;
    bool       AllocSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       IndSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       BitloadSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src1 ,Operand *src2 ,Operand *src3)	override;
    bool       FlagSeq(Sequence *parent,bool FlagConnectedMode)					override;
    bool       CAndSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       COrSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       CXorSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       EqualSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       ZoneSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src1,Operand *src2)	override;
    bool       PartEqSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       UnequalSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)override;
    bool       GreaterSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)override;
    bool       LargeSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       LessSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       SmallSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       MultSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       DivSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       ModSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       StrMoveSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src1 ,Operand *src2)	override;
    bool       LowerSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       UpperSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       StateSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       TWSetSeq(Sequence *parent,bool FlagConnectedMode)				override;
    bool       FSetSeq(Sequence *parent,bool FlagConnectedMode)					override;
    bool       FResetSeq(Sequence *parent,bool FlagConnectedMode)				override;
    bool       RxTimeoutSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src1 ,Operand *src2)	override;
    bool       StrLenSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       AddFileSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)override;
    bool       OpenLFileSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)override;
    bool       LoadFileSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)override;
    bool       CloseFileSeq(Sequence *parent,bool FlagConnectedMode)			override;
    bool       DeleteFileSeq(Sequence *parent,bool FlagConnectedMode)			override;
    bool       BPrintSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       BScanSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       InputFromString(Sequence *parent,QString &Src)					override;
    bool       FloatNumSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)override;

    bool       ReceiveLoop(void);
    int        ReceiveWaitTillTimeout(void);

private:
	void	SendStr(char Buff[] ,int Len);
	void	SendStr(const QByteArray &s);
	void	SendStr(const QString &s);

signals:
	void	SignalTx(const QByteArray &str);
	void	SignalRx(const QByteArray &str);
};

#define MaxBitOperand   256

/*----------------------------------------------------------------------------*/
//  1.日本語名
//
//  2.概要
//
//  3.機能説明
//
//  4.備考
//
/*----------------------------------------------------------------------------*/
class   BitBaseOperand : public Operand
{
  public:
    BYTE    Data;

	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    BitBaseOperand(SeqControl *BaseParent);
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    bool    Load(char buff[])						override;
    int    GetNumeric(bool SrcReconstruct=false)	override;
    int    GetStringCount(void)						override;
    QByteArray   GetString(bool ThreadMode=true)	override;
    double     GetFloat(bool SrcReconstruct=false)	override{    return(GetNumeric(SrcReconstruct)); }
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//    d
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    void       SetData(int d)					override{	Data=(BYTE)(d&1);   }
    void      SetData(const QByteArray &d)		override;
    bool      IsGetEnabled(void)				override{	return(true);		}
    ExeHistAttr    GetHistAttr(void)			override{	return(EHA_OnlyExec);   }
    int     GetPreDataBitSize(void)				override{   return(1);			}

	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//    parent
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    bool       LetSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       LetBSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       AddSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       SubSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       AndSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       OrSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)		override;
    bool       XorSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       NotSeq(Sequence *parent,bool FlagConnectedMode)					override;
    bool       FlushSeq(Sequence *parent,bool FlagConnectedMode)				override;
    bool       AllocSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       IndSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       BitloadSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src1 ,Operand *src2 ,Operand *src3)	override;
    bool       FlagSeq(Sequence *parent,bool FlagConnectedMode)					override;
    bool       CAndSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       COrSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       CXorSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       EqualSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       ZoneSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src1,Operand *src2)	override;
    bool       PartEqSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       UnequalSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)override;
    bool       GreaterSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)override;
    bool       LargeSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       LessSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       SmallSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       MultSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       DivSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       ModSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       StrMoveSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src1 ,Operand *src2)	override;
    bool       LowerSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       UpperSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       StateSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       TWSetSeq(Sequence *parent,bool FlagConnectedMode)				override;
    bool       FSetSeq(Sequence *parent,bool FlagConnectedMode)					override;
    bool       FResetSeq(Sequence *parent,bool FlagConnectedMode)				override;
    bool       RxTimeoutSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src1 ,Operand *src2)	override;
    bool       StrLenSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       AddFileSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       OpenLFileSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       LoadFileSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       CloseFileSeq(Sequence *parent,bool FlagConnectedMode)			override;
    bool       DeleteFileSeq(Sequence *parent,bool FlagConnectedMode)			override;
    bool       BPrintSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       BScanSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       InputFromString(Sequence *parent,QString &Src)					override;
    bool       FloatNumSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)override;

};

class   BitOperand : public BitBaseOperand,public NPList<BitOperand>
{
  public:
	BitOperand(SeqControl *baseParent):BitBaseOperand(baseParent){}

    QString    GetName(void)	override;
    virtual const	char    *GetKindName(void)	override{ return("Bit");  }
    virtual int     GetKindCode(void)			override{  return(KindCodeBit);  }
    virtual Operand     *MakeDup(LocalReg *)	override{     return(NULL);   }
};

class   LocalBitOperand : public BitBaseOperand,public NPList<LocalBitOperand>
{
  public:
	  LocalBitOperand(SeqControl *baseParent):BitBaseOperand(baseParent){}

    QString    GetName(void)	override;
    virtual const	char    *GetKindName(void)	override{ return("LocalBit");  }
    virtual int     GetKindCode(void)			override{  return(KindCodeLocalBit);  }
    virtual Operand     *MakeDup(LocalReg *DestLReg)	override;
};

#define MaxWordOperand   256

/*----------------------------------------------------------------------------*/
//  1.日本語名
//
//  2.概要
//
//  3.機能説明
//
//  4.備考
//
/*----------------------------------------------------------------------------*/
class   WordBaseOperand : public Operand
{
  public:
    int Data;

	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    WordBaseOperand(SeqControl *BaseParent);
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    bool    Load(char buff[])						override;
    int    GetNumeric(bool SrcReconstruct=false)	override;
    int    GetStringCount(void)						override;
    QByteArray GetString(bool ThreadMode=true)		override;
    double     GetFloat(bool SrcReconstruct=false)	override{    return(GetNumeric(SrcReconstruct)); }
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//    d
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    void       SetData(int d)						override{ Data=d; }
    void      SetData(const QByteArray &d)			override;
    bool      IsGetEnabled(void)					override{  return(true);   }
    ExeHistAttr    GetHistAttr(void)				override{      return(EHA_OnlyExec);   }
    int     GetPreDataBitSize(void)					override{    return(sizeof(Data));      }

	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//    parent
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    bool       LetSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       LetBSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       AddSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       SubSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       AndSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       OrSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)		override;
    bool       XorSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       NotSeq(Sequence *parent,bool FlagConnectedMode)					override;
    bool       FlushSeq(Sequence *parent,bool FlagConnectedMode)				override;
    bool       AllocSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       IndSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       BitloadSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src1 ,Operand *src2 ,Operand *src3)	override;
    bool       FlagSeq(Sequence *parent,bool FlagConnectedMode)					override;
    bool       CAndSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       COrSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       CXorSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       EqualSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       ZoneSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src1,Operand *src2)	override;
    bool       PartEqSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       UnequalSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)override;
    bool       GreaterSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)override;
    bool       LargeSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       LessSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       SmallSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       MultSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       DivSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       ModSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       StrMoveSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src1 ,Operand *src2)	override;
    bool       LowerSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       UpperSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       StateSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       TWSetSeq(Sequence *parent,bool FlagConnectedMode)				override;
    bool       FSetSeq(Sequence *parent,bool FlagConnectedMode)					override;
    bool       FResetSeq(Sequence *parent,bool FlagConnectedMode)				override;
    bool       RxTimeoutSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src1 ,Operand *src2)	override;
    bool       StrLenSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       AddFileSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)override;
    bool       OpenLFileSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       LoadFileSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       CloseFileSeq(Sequence *parent,bool FlagConnectedMode)			override;
    bool       DeleteFileSeq(Sequence *parent,bool FlagConnectedMode)			override;
    bool       BPrintSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       BScanSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       InputFromString(Sequence *parent,QString &Src)					override;
    bool       FloatNumSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;

};

class   WordOperand : public WordBaseOperand,public NPList<WordOperand>
{
  public:
	  WordOperand(SeqControl *BaseParent):WordBaseOperand(BaseParent){}
    ~WordOperand(void){}
    QString    GetName(void)					override;
    virtual const	char    *GetKindName(void)	override{ return("Word");  }
    virtual int     GetKindCode(void)			override{  return(KindCodeWord);  }
    virtual Operand     *MakeDup(LocalReg *)	override{     return(NULL);   }
};

class   LocalWordOperand : public WordBaseOperand,public NPList<LocalWordOperand>
{
  public:
	  LocalWordOperand(SeqControl *BaseParent):WordBaseOperand(BaseParent){}
    ~LocalWordOperand(void){}
    QString    GetName(void)					override;
    virtual const	char    *GetKindName(void)	override{ return("LocalWord");  }
    virtual int     GetKindCode(void)			override{  return(KindCodeLocalWord);  }
    virtual Operand     *MakeDup(LocalReg *DestLReg) override;
};


#define MaxFloatOperand   256

/*----------------------------------------------------------------------------*/
//  1.日本語名
//
//  2.概要
//
//  3.機能説明
//
//  4.備考
//
/*----------------------------------------------------------------------------*/
class   FloatBaseOperand : public Operand
{
  public:
    double  Data;
    BYTE    Num;    //少数の桁数    0xFFのとき、桁数制限無し
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    FloatBaseOperand(SeqControl *BaseParent);
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    bool    Load(char buff[])						override;
    int    GetNumeric(bool SrcReconstruct=false)	override;
    int    GetStringCount(void)						override;
    QByteArray    GetString(bool ThreadMode=true)	override;
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//    d
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    double     GetFloat(bool SrcReconstruct=false)	override;
    void       SetData(int d)						override{	Data=d; }
    void       SetFloat(double d)					override{	Data=d; }
    void       SetData(const QByteArray &d)			override;
    bool       IsGetEnabled(void)					override{	return(true);			}
    ExeHistAttr    GetHistAttr(void)				override{	return(EHA_OnlyExec);   }
    int     GetPreDataBitSize(void)					override{	return(sizeof(Data));	}

	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//    parent
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    bool       LetSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       LetBSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       AddSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       SubSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       AndSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       OrSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)		override;
    bool       XorSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       NotSeq(Sequence *parent,bool FlagConnectedMode)					override;
    bool       FlushSeq(Sequence *parent,bool FlagConnectedMode)				override;
    bool       AllocSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       IndSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       BitloadSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src1 ,Operand *src2 ,Operand *src3)	override;
    bool       FlagSeq(Sequence *parent,bool FlagConnectedMode)					override;
    bool       CAndSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       COrSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       CXorSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       EqualSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       ZoneSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src1,Operand *src2)	override;
    bool       PartEqSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       UnequalSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)override;
    bool       GreaterSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)override;
    bool       LargeSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       LessSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       SmallSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       MultSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       DivSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       ModSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       StrMoveSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src1 ,Operand *src2)	override;
    bool       LowerSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       UpperSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       StateSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       TWSetSeq(Sequence *parent,bool FlagConnectedMode)				override;
    bool       FSetSeq(Sequence *parent,bool FlagConnectedMode)					override;
    bool       FResetSeq(Sequence *parent,bool FlagConnectedMode)				override;
    bool       RxTimeoutSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src1 ,Operand *src2)	override;
    bool       StrLenSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)		override;
    bool       AddFileSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       OpenLFileSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       LoadFileSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       CloseFileSeq(Sequence *parent,bool FlagConnectedMode)			override;
    bool       DeleteFileSeq(Sequence *parent,bool FlagConnectedMode)			override;
    bool       BPrintSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       BScanSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       InputFromString(Sequence *parent,QString &Src)					override;
    bool       FloatNumSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;

};

class   FloatOperand : public FloatBaseOperand,public NPList<FloatOperand>
{
  public:
	  FloatOperand(SeqControl *BaseParent):FloatBaseOperand(BaseParent){}
    ~FloatOperand(void){}

    QString    GetName(void)					override;
    virtual const	char    *GetKindName(void)	override{	return("Float");		}
    virtual int     GetKindCode(void)			override{	return(KindCodeFloat);  }
    virtual Operand     *MakeDup(LocalReg *)	override{	return(NULL);			}
};

class   LocalFloatOperand : public FloatBaseOperand,public NPList<LocalFloatOperand>
{
  public:
    LocalFloatOperand(SeqControl *BaseParent):FloatBaseOperand(BaseParent){}
    ~LocalFloatOperand(void){}

    QString    GetName(void)					override;
    virtual const	char    *GetKindName(void)	override{	return("LocalFloat");		}
    virtual int     GetKindCode(void)			override{	return(KindCodeLocalFloat);	}
    virtual Operand     *MakeDup(LocalReg *DestLReg) override;
};

#define MaxStringOperand   256

/*----------------------------------------------------------------------------*/
//  1.日本語名
//
//  2.概要
//
//  3.機能説明
//
//  4.備考
//
/*----------------------------------------------------------------------------*/
class   StringBaseOperand : public Operand
{
  public:
    QByteArray    Data;

	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考	//
	/*----------------------------------------------------------------------------*/
    StringBaseOperand(SeqControl *BaseParent);
    ~StringBaseOperand(void);
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    bool    Load(char buff[])				override;
///    void    SetData(QString &data)		override;
    void      SetData(const QByteArray &d)	override;
	void      SetData(const QString &d);
    bool      IsGetEnabled(void)			override{  return(true);   }
    void      SetData(int d)				override;
    int			GetNumeric(bool SrcReconstruct=false)	override;
    int			GetStringCount(void)					override;
    QByteArray  GetString(bool ThreadMode=true)			override;
    double		GetFloat(bool SrcReconstruct=false)		override;
    ExeHistAttr    GetHistAttr(void)					override{	return(EHA_OnlyExec);   }
    int     GetPreDataBitSize(void)						override{	return(-1);				}

	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//    parent
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    bool       LetSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       LetBSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       AddSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       SubSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       AndSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       OrSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)		override;
    bool       XorSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       NotSeq(Sequence *parent,bool FlagConnectedMode)					override;
    bool       FlushSeq(Sequence *parent,bool FlagConnectedMode)				override;
    bool       AllocSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       IndSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       BitloadSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src1 ,Operand *src2 ,Operand *src3)	override;
    bool       FlagSeq(Sequence *parent,bool FlagConnectedMode)					override;
    bool       CAndSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       COrSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       CXorSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       EqualSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       ZoneSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src1,Operand *src2)	override;
    bool       PartEqSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       UnequalSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)override;
    bool       GreaterSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)override;
    bool       LargeSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       LessSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       SmallSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       MultSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       DivSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       ModSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       StrMoveSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src1 ,Operand *src2)	override;
    bool       LowerSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       UpperSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       StateSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       TWSetSeq(Sequence *parent,bool FlagConnectedMode)				override;
    bool       FSetSeq(Sequence *parent,bool FlagConnectedMode)					override;
    bool       FResetSeq(Sequence *parent,bool FlagConnectedMode)				override;
    bool       RxTimeoutSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src1 ,Operand *src2)	override;
    bool       StrLenSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)		override;
    bool       AddFileSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       OpenLFileSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       LoadFileSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       CloseFileSeq(Sequence *parent,bool FlagConnectedMode)			override;
    bool       DeleteFileSeq(Sequence *parent,bool FlagConnectedMode)			override;
    bool       BPrintSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       BScanSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       InputFromString(Sequence *parent,QString &Src)					override;
    bool       FloatNumSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)override;

};

class   StringOperand : public StringBaseOperand,public NPList<StringOperand>
{
  public:
	  StringOperand(SeqControl *baseParent):StringBaseOperand(baseParent){}
    ~StringOperand(void){}

    QString    GetName(void)					override;
    virtual const	char    *GetKindName(void)	override{	return("String");		}
    virtual int     GetKindCode(void)			override{	return(KindCodeString);	}
    virtual Operand     *MakeDup(LocalReg *)	override{	return(NULL);			}
};

class   LocalStringOperand : public StringBaseOperand,public NPList<LocalStringOperand>
{
  public:
    LocalStringOperand(SeqControl *baseParent):StringBaseOperand(baseParent){}
    ~LocalStringOperand(void){}

    QString    GetName(void)					override;
    virtual const	char    *GetKindName(void)	override{	return("LocalString");			}
    virtual int     GetKindCode(void)			override{	return(KindCodeLocalString);	}
    virtual Operand     *MakeDup(LocalReg *DestLReg) override;
};

/*----------------------------------------------------------------------------*/
//  1.日本語名
//
//  2.概要
//
//  3.機能説明
//
//  4.備考
//
/*----------------------------------------------------------------------------*/
class   SpecialOperand : public Operand ,public NPList<SpecialOperand>
{
    Operand *Indirect;
  public:

	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
	  SpecialOperand(SeqControl *baseParent):Operand(baseParent){   Indirect=NULL;  }
    QString    GetName(void)	override;
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    virtual	const	char    *GetKindName(void)	override{ return("Special");  }
    virtual int     GetKindCode(void)			override{  return(KindCodeSpecial);    }
    bool    Load(char buff[])					override;
    int    GetNumeric(bool SrcReconstruct=false)override;
    void   SetNumeric(int d)					;
    int    GetStringCount(void)					override;
    QByteArray   GetString(bool ThreadMode=true)override;
    void      SetData(int d)					override;
    void      SetData(const QByteArray &d)		override;
    bool      IsGetEnabled(void)				override{	return(true);	}
    double     GetFloat(bool SrcReconstruct=false)	override{    return(GetNumeric(SrcReconstruct)); }
    virtual Operand     *MakeDup(LocalReg *)	override{	return(NULL);   }
    ExeHistAttr    GetHistAttr(void)			override{	return(EHA_OnlyExec);	}
    int     GetPreDataBitSize(void)				override{	return(sizeof(int));	}

    bool       LetSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       LetBSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       AddSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       SubSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       AndSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       OrSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)		override;
    bool       XorSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       NotSeq(Sequence *parent,bool FlagConnectedMode)					override;
    bool       FlushSeq(Sequence *parent,bool FlagConnectedMode)				override;
    bool       AllocSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       IndSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       BitloadSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src1 ,Operand *src2 ,Operand *src3)	override;
    bool       FlagSeq(Sequence *parent,bool FlagConnectedMode)					override;
    bool       CAndSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       COrSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       CXorSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       EqualSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       ZoneSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src1,Operand *src2)	override;
    bool       PartEqSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       UnequalSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)override;
    bool       GreaterSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)override;
    bool       LargeSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       LessSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       SmallSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       MultSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       DivSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       ModSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       StrMoveSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src1 ,Operand *src2)	override;
    bool       LowerSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       UpperSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       StateSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       TWSetSeq(Sequence *parent,bool FlagConnectedMode)				override;
    bool       FSetSeq(Sequence *parent,bool FlagConnectedMode)					override;
    bool       FResetSeq(Sequence *parent,bool FlagConnectedMode)				override;
    bool       RxTimeoutSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src1 ,Operand *src2)	override;
    bool       StrLenSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)		override;
    bool       AddFileSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       OpenLFileSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       LoadFileSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       CloseFileSeq(Sequence *parent,bool FlagConnectedMode)			override;
    bool       DeleteFileSeq(Sequence *parent,bool FlagConnectedMode)			override;
    bool       BPrintSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       BScanSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       InputFromString(Sequence *parent,QString &Src)					override;
    bool       FloatNumSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;

};

/*----------------------------------------------------------------------------*/
//  1.日本語名
//
//  2.概要
//
//  3.機能説明
//
//  4.備考
//
/*----------------------------------------------------------------------------*/
class   SpecialBitOperand : public Operand ,public NPList<SpecialBitOperand>
{
    Operand *Indirect;
  public:

	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
	  SpecialBitOperand(SeqControl *baseParent):Operand(baseParent){    Indirect=NULL;      }
    QString    GetName(void)	override;
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    virtual const	char    *GetKindName(void)	override{ return("SpecialBit");  }
    virtual int     GetKindCode(void)			override{  return(KindCodeSpeicalBit);  }
    bool    Load(char buff[])					override;
    int    GetNumeric(bool SrcReconstruct=false)override;
    void   SetNumeric(int d)					;
    int    GetStringCount(void)					override;
    QByteArray   GetString(bool ThreadMode=true)override;
    void      SetData(int d)					override;
    void      SetData(const QByteArray &d)		override;
    bool      IsGetEnabled(void)				override{  return(true);	}
    double     GetFloat(bool SrcReconstruct=false)	override{    return(GetNumeric(SrcReconstruct)); }
    virtual Operand     *MakeDup(LocalReg *)	override{	return(NULL);	}
    ExeHistAttr    GetHistAttr(void)			override{	return(EHA_OnlyExec);	}
    int     GetPreDataBitSize(void)				override{	return(1);		}

    bool       LetSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       LetBSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       AddSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       SubSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       AndSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       OrSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)		override;
    bool       XorSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       NotSeq(Sequence *parent,bool FlagConnectedMode)					override;
    bool       FlushSeq(Sequence *parent,bool FlagConnectedMode)				override;
    bool       AllocSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       IndSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       BitloadSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src1 ,Operand *src2 ,Operand *src3)	override;
    bool       FlagSeq(Sequence *parent,bool FlagConnectedMode)					override;
    bool       CAndSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       COrSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       CXorSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       EqualSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       ZoneSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src1,Operand *src2)	override;
    bool       PartEqSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       UnequalSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)override;
    bool       GreaterSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)override;
    bool       LargeSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       LessSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       SmallSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       MultSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       DivSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       ModSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       StrMoveSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src1 ,Operand *src2)	override;
    bool       LowerSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       UpperSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       StateSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       TWSetSeq(Sequence *parent,bool FlagConnectedMode)				override;
    bool       FSetSeq(Sequence *parent,bool FlagConnectedMode)					override;
    bool       FResetSeq(Sequence *parent,bool FlagConnectedMode)				override;
    bool       RxTimeoutSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src1 ,Operand *src2)	override;
    bool       StrLenSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)		override;
    bool       AddFileSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       OpenLFileSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       LoadFileSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       CloseFileSeq(Sequence *parent,bool FlagConnectedMode)			override;
    bool       DeleteFileSeq(Sequence *parent,bool FlagConnectedMode)			override;
    bool       BPrintSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       BScanSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       InputFromString(Sequence *parent,QString &Src)					override;
    bool       FloatNumSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)override;

};
/*----------------------------------------------------------------------------*/
//  1.日本語名
//
//  2.概要
//
//  3.機能説明
//
//  4.備考
//
/*----------------------------------------------------------------------------*/
class   SpecialStringOperand : public Operand ,public NPList<SpecialStringOperand>
{
    Operand *Indirect;
  public:

	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
	  SpecialStringOperand(SeqControl *baseParent):Operand(baseParent){    Indirect=NULL;      }
    QString    GetName(void)	override;
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    virtual const	char    *GetKindName(void)	override{ return("SpecialString");  }
    virtual int     GetKindCode(void)			override{  return(KindCodeSpeicalString);  }
    bool    Load(char buff[])					override;
    int    GetNumeric(bool SrcReconstruct=false)override;
    void   SetNumeric(int d)					;
    int    GetStringCount(void)					override;
    QByteArray   GetString(bool ThreadMode=true)override;
    void      SetData(int d)					override;
    void      SetData(const QByteArray &d)		override;
	void      SetData(const QString &d)	;
    bool      IsGetEnabled(void)				override{	return(true);   }
    double     GetFloat(bool SrcReconstruct=false)	override{    return(GetNumeric(SrcReconstruct)); }
    virtual Operand     *MakeDup(LocalReg *)	override{	return(NULL);   }
    ExeHistAttr    GetHistAttr(void)			override{	return(EHA_OnlyExec);   }
    int     GetPreDataBitSize(void)				override{	return(-1);      }

    bool       LetSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       LetBSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       AddSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       SubSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       AndSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       OrSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)		override;
    bool       XorSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       NotSeq(Sequence *parent,bool FlagConnectedMode)					override;
    bool       FlushSeq(Sequence *parent,bool FlagConnectedMode)				override;
    bool       AllocSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       IndSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       BitloadSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src1 ,Operand *src2 ,Operand *src3)	override;
    bool       FlagSeq(Sequence *parent,bool FlagConnectedMode)					override;
    bool       CAndSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       COrSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       CXorSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       EqualSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       ZoneSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src1,Operand *src2)	override;
    bool       PartEqSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       UnequalSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)override;
    bool       GreaterSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)override;
    bool       LargeSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       LessSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       SmallSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       MultSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       DivSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       ModSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       StrMoveSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src1 ,Operand *src2)	override;
    bool       LowerSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       UpperSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       StateSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       TWSetSeq(Sequence *parent,bool FlagConnectedMode)				override;
    bool       FSetSeq(Sequence *parent,bool FlagConnectedMode)					override;
    bool       FResetSeq(Sequence *parent,bool FlagConnectedMode)				override;
    bool       RxTimeoutSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src1 ,Operand *src2)	override;
    bool       StrLenSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)		override;
    bool       AddFileSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       OpenLFileSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       LoadFileSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       CloseFileSeq(Sequence *parent,bool FlagConnectedMode)			override;
    bool       DeleteFileSeq(Sequence *parent,bool FlagConnectedMode)			override;
    bool       BPrintSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       BScanSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       InputFromString(Sequence *parent,QString &Src)					override;
    bool       FloatNumSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;

};


/*----------------------------------------------------------------------------*/
//  1.日本語名
//
//  2.概要
//
//  3.機能説明
//
//  4.備考
//
/*----------------------------------------------------------------------------*/
class   SpecialFloatOperand : public Operand ,public NPList<SpecialFloatOperand>
{
    Operand *Indirect;
  public:

	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
	  SpecialFloatOperand(SeqControl *baseParent):Operand(baseParent){    Indirect=NULL;      }
    QString    GetName(void)	override;
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    virtual const	char    *GetKindName(void)	override{ return("SpecialFloat");  }
    virtual int     GetKindCode(void)			override{  return(KindCodeSpeicalFloat);  }
    bool    Load(char buff[])					override;
    int    GetNumeric(bool SrcReconstruct=false)override;
    void   SetNumeric(int d)					;
    int    GetStringCount(void)					override;
    QByteArray   GetString(bool ThreadMode=true)override;
	double    GetFloat(bool SrcReconstruct=false)override;
    void      SetData(int d)					override;
	void      SetFloat(double d)				override;
    void      SetData(const QByteArray &d)		override;
    bool      IsGetEnabled(void)				override{	return(true);   }
    virtual Operand     *MakeDup(LocalReg *)	override{	return(NULL);   }
    ExeHistAttr    GetHistAttr(void)			override{	return(EHA_OnlyExec);   }
    int     GetPreDataBitSize(void)				override{	return(1);      }

    bool       LetSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       LetBSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       AddSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       SubSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       AndSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       OrSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)		override;
    bool       XorSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       NotSeq(Sequence *parent,bool FlagConnectedMode)					override;
    bool       FlushSeq(Sequence *parent,bool FlagConnectedMode)				override;
    bool       AllocSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       IndSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       BitloadSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src1 ,Operand *src2 ,Operand *src3)	override;
    bool       FlagSeq(Sequence *parent,bool FlagConnectedMode)					override;
    bool       CAndSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       COrSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       CXorSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       EqualSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       ZoneSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src1,Operand *src2)	override;
    bool       PartEqSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       UnequalSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)override;
    bool       GreaterSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)override;
    bool       LargeSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       LessSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       SmallSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       MultSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       DivSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       ModSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       StrMoveSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src1 ,Operand *src2)	override;
    bool       LowerSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       UpperSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       StateSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       TWSetSeq(Sequence *parent,bool FlagConnectedMode)				override;
    bool       FSetSeq(Sequence *parent,bool FlagConnectedMode)					override;
    bool       FResetSeq(Sequence *parent,bool FlagConnectedMode)				override;
    bool       RxTimeoutSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src1 ,Operand *src2)	override;
    bool       StrLenSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)		override;
    bool       AddFileSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       OpenLFileSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       LoadFileSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       CloseFileSeq(Sequence *parent,bool FlagConnectedMode)			override;
    bool       DeleteFileSeq(Sequence *parent,bool FlagConnectedMode)			override;
    bool       BPrintSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       BScanSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       InputFromString(Sequence *parent,QString &Src)					override;
    bool       FloatNumSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;

};
/*----------------------------------------------------------------------------*/
//  1.日本語名
//
//  2.概要
//
//  3.機能説明
//
//  4.備考
//
/*----------------------------------------------------------------------------*/
class   NumberOperand : public Operand ,public NPList<NumberOperand>
{
    double  Data;
  public:
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
	  NumberOperand(SeqControl *baseParent):Operand(baseParent){	Data=0.0;	}

    QString    GetName(void)	override;
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    virtual const	char    *GetKindName(void)	override{ return("Number");  }
    virtual int     GetKindCode(void)			override{  return(KindCodeNumber);     }
    bool    Load(char buff[])					override;
    int   GetNumeric(bool SrcReconstruct=false)	override;
    int   GetStringCount(void)					override;
    QByteArray   GetString(bool ThreadMode=true)override;
    void		SetData(int d)					override	{	Data=d; ID=d;   }
    void		SetData(double n)							{	Data=n; }
    void		SetData(const QByteArray &d)	override;
    bool		IsGetEnabled(void)				override	{	return(true);   }
    double		GetFloat(bool SrcReconstruct=false)	override{	return(Data); }
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//    parent
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    virtual Operand     *MakeDup(LocalReg *)	override{	return(NULL);		}
    ExeHistAttr    GetHistAttr(void)			override{	return(EHA_Never);	}
    int     GetPreDataBitSize(void)				override{	return(sizeof(Data));	}
    bool    SaveBinHeader(FILE *file)			override;
    bool    LoadBinHeader(FILE *file)			override;

    bool       LetSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       LetBSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       AddSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       SubSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       AndSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       OrSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)		override;
    bool       XorSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       NotSeq(Sequence *parent,bool FlagConnectedMode)					override;
    bool       FlushSeq(Sequence *parent,bool FlagConnectedMode)				override;
    bool       AllocSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       IndSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       BitloadSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src1 ,Operand *src2 ,Operand *src3)	override;
    bool       FlagSeq(Sequence *parent,bool FlagConnectedMode)					override;
    bool       CAndSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       COrSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       CXorSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       EqualSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       ZoneSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src1,Operand *src2)	override;
    bool       PartEqSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       UnequalSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)override;
    bool       GreaterSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)override;
    bool       LargeSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       LessSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       SmallSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       MultSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       DivSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       ModSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       StrMoveSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src1 ,Operand *src2)	override;
    bool       LowerSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       UpperSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       StateSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       TWSetSeq(Sequence *parent,bool FlagConnectedMode)				override;
    bool       FSetSeq(Sequence *parent,bool FlagConnectedMode)					override;
    bool       FResetSeq(Sequence *parent,bool FlagConnectedMode)				override;
    bool       RxTimeoutSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src1 ,Operand *src2)	override;
    bool       StrLenSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)		override;
    bool       AddFileSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       OpenLFileSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       LoadFileSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       CloseFileSeq(Sequence *parent,bool FlagConnectedMode)			override;
    bool       DeleteFileSeq(Sequence *parent,bool FlagConnectedMode)			override;
    bool       BPrintSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       BScanSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       InputFromString(Sequence *parent,QString &Src)					override;
    bool       FloatNumSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)override;

};

/*----------------------------------------------------------------------------*/
//  1.日本語名
//
//  2.概要
//
//  3.機能説明
//
//  4.備考
//
/*----------------------------------------------------------------------------*/
class   CharOperand : public Operand ,public NPList<CharOperand>
{
  public:
    QByteArray    Data;

	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    CharOperand(SeqControl *baseParent);
    ~CharOperand(void);

    QString    GetName(void)	override;
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    virtual const	char    *GetKindName(void)	override{ return("Char");  }
    virtual int     GetKindCode(void)			override{  return(KindCodeCharacter);  }
    bool    Load(char buff[])					override;
    int    GetNumeric(bool SrcReconstruct=false)override;
///    void   SetData(BYTE *data ,int len)	override;
    void      SetData(const QByteArray &d)		override;
    bool      IsGetEnabled(void)				override{  return(true);   }
    void      SetData(int )						override{}
    double     GetFloat(bool SrcReconstruct=false)	override{	return(GetNumeric(SrcReconstruct)); }
    virtual Operand     *MakeDup(LocalReg *)		override{	return(NULL);   }
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
	int    GetStringCount(void)		override{   return(Data.length());    }
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    QByteArray   GetString(bool ThreadMode=true)	override{	return(Data);   }
    ExeHistAttr    GetHistAttr(void)				override{	return(EHA_Never);  }
	int     GetPreDataBitSize(void)					override{	return(Data.length());      }
    bool    SaveBinHeader(FILE *file)				override;
    bool    LoadBinHeader(FILE *file)				override;

	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//    parent
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    bool       LetSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       LetBSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       AddSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       SubSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       AndSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       OrSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)		override;
    bool       XorSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       NotSeq(Sequence *parent,bool FlagConnectedMode)					override;
    bool       FlushSeq(Sequence *parent,bool FlagConnectedMode)				override;
    bool       AllocSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       IndSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       BitloadSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src1 ,Operand *src2 ,Operand *src3)	override;
    bool       FlagSeq(Sequence *parent,bool FlagConnectedMode)					override;
    bool       CAndSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       COrSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       CXorSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       EqualSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       ZoneSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src1,Operand *src2)	override;
    bool       PartEqSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       UnequalSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)override;
    bool       GreaterSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)override;
    bool       LargeSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       LessSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       SmallSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       MultSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       DivSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       ModSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       StrMoveSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src1 ,Operand *src2)	override;
    bool       LowerSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       UpperSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       StateSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       TWSetSeq(Sequence *parent,bool FlagConnectedMode)				override;
    bool       FSetSeq(Sequence *parent,bool FlagConnectedMode)					override;
    bool       FResetSeq(Sequence *parent,bool FlagConnectedMode)				override;
    bool       RxTimeoutSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src1 ,Operand *src2)	override;
    bool       StrLenSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)		override;
    bool       AddFileSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       OpenLFileSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       LoadFileSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       CloseFileSeq(Sequence *parent,bool FlagConnectedMode)			override;
    bool       DeleteFileSeq(Sequence *parent,bool FlagConnectedMode)			override;
    bool       BPrintSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       BScanSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       InputFromString(Sequence *parent,QString &Src)					override;
    bool       FloatNumSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
};

const   int     GroupBitCount=32;
/*----------------------------------------------------------------------------*/
//  1.日本語名
//
//  2.概要
//
//  3.機能説明
//
//  4.備考
//
/*----------------------------------------------------------------------------*/
class   GroupOperand : public Operand,public NPList<GroupOperand>
{
  public:
    QString  EachBitName[GroupBitCount];
    Operand  *EachBitPoint[GroupBitCount];

	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    GroupOperand(SeqControl *BaseParent);
    QString    GetName(void)	override;
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    virtual const	char    *GetKindName(void)	override{ return("Group");  }
    virtual int     GetKindCode(void)			override{  return(KindCodeGroup);  }
    bool    Load(char buff[])					override;
    int    GetNumeric(bool SrcReconstruct=false)override;
    int    GetStringCount(void)					override;
    QByteArray    GetString(bool ThreadMode=true)	override;
    double     GetFloat(bool SrcReconstruct=false)	override{    return(GetNumeric(SrcReconstruct)); }

    void    InitialConstruct(void);
    int     GetBitCount(void);

	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//    d
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    void       SetData(int d)					override;
    void       SetData(const QByteArray &d)		override;
    bool      IsGetEnabled(void)				override{	return(true);	}
    virtual Operand     *MakeDup(LocalReg *)	override{	return(NULL);	}
    ExeHistAttr    GetHistAttr(void)			override{	return(EHA_OnlyExec);	}
    int     GetPreDataBitSize(void)				override{	return(sizeof(int));	}
    bool    SaveBinHeader(FILE *file)			override;
    bool    LoadBinHeader(FILE *file)			override;

	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//    parent
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    bool       LetSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       LetBSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       AddSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       SubSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       AndSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       OrSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)		override;
    bool       XorSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       NotSeq(Sequence *parent,bool FlagConnectedMode)					override;
    bool       FlushSeq(Sequence *parent,bool FlagConnectedMode)				override;
    bool       AllocSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       IndSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       BitloadSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src1 ,Operand *src2 ,Operand *src3)	override;
    bool       FlagSeq(Sequence *parent,bool FlagConnectedMode)					override;
    bool       CAndSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       COrSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       CXorSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       EqualSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       ZoneSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src1,Operand *src2)	override;
    bool       PartEqSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       UnequalSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)override;
    bool       GreaterSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)override;
    bool       LargeSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       LessSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       SmallSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       MultSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       DivSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       ModSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       StrMoveSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src1 ,Operand *src2)	override;
    bool       LowerSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       UpperSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       StateSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       TWSetSeq(Sequence *parent,bool FlagConnectedMode)				override;
    bool       FSetSeq(Sequence *parent,bool FlagConnectedMode)					override;
    bool       FResetSeq(Sequence *parent,bool FlagConnectedMode)				override;
    bool       RxTimeoutSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src1 ,Operand *src2)	override;
    bool       StrLenSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)		override;
    bool       AddFileSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       OpenLFileSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       LoadFileSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       CloseFileSeq(Sequence *parent,bool FlagConnectedMode)			override;
    bool       DeleteFileSeq(Sequence *parent,bool FlagConnectedMode)			override;
    bool       BPrintSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       BScanSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       InputFromString(Sequence *parent,QString &Src)					override;
    bool       FloatNumSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;

};

/*----------------------------------------------------------------------------*/
//  1.日本語名
//
//  2.概要
//
//  3.機能説明
//
//  4.備考
//
/*----------------------------------------------------------------------------*/

/*↓D-20051026------------------------------------------------------------------
class   MTWSocket : public  TWSocket
{
  public:
    BYTE    Dummy[256];
    bool    DeleteSign;

      MTWSocket(Classes::TComponent* AOwner) : TWSocket(AOwner){   DeleteSign=false;   }
      ~MTWSocket(void){ DeleteSign=true;    }
};

class   LanVarRCmd : public NPList<LanVarRCmd>
{
  public:
    BYTE    Cmd;
    QString  Data;
    TObject     *Sender;

    LanVarRCmd(TObject *sender ,BYTE cmd ,QChar *data);
};

class   LanVarSocketList : public NPList<LanVarSocketList>
{
  public:
    AnsiString  IPAddress;
    MTWSocket   *CliSock;
    volatile    bool        GotIt;
    volatile    bool        OnConnectingMode;
    bool        BuiltInListen;

    LanVarSocketList(void);
    ~LanVarSocketList(void);

    bool    Connect(void);
    bool    Close(void);
    bool    IsConnected(void);
    bool    SendStr(QChar *buff);

    void   RReceiverDataAvailable(
                          TObject *Sender, WORD Error);
    void   RReceiverSessionClosed(TObject *Sender,
                          WORD Error);
};

class   IPList : public NPList<IPList>
{
  public:
    AnsiString          IPAddress;
    LanVarSocketList    *Sock;

    IPList(void);
    IPList(QChar *ip);
    ~IPList(void){}

    void    Initial(void);
    bool    Connect(void);
    bool    IsConnected(void);
    bool    SendConnection(AnsiString name);

    bool    SendData(AnsiString &name ,AnsiString &data);
    bool    ReqData(AnsiString name);

    bool    ReqPrepare(AnsiString name);
    bool    ReqDone(void);

    bool    SaveBinHeader(FILE *file);
    bool    LoadBinHeader(FILE *file);
};

class   LanvarOperand : public Operand ,public NPList<LanvarOperand>
{
  public:
      NPListPack<IPList>    IP;
      QString    Data;
      bool          ReqPreparedMode;

///    LanvarOperand(void);
///    QString    GetName(void);

    virtual const	char    *GetKindName(void)	override{ return("Lanvar");  }
    virtual int     GetKindCode(void)			override{  return(KindCodeLanvar); }
    bool    Load(char buff[])					override;
    int    GetNumeric(bool SrcReconstruct=false)override;
    void   SetNumeric(int d)					override;
    int    GetStringCount(void)					override;
    QByteArray   GetString(bool ThreadMode=true)override;
    void      SetData(int d)					override;
    bool      IsGetEnabled(void)				override{  return(true);   }
    void      SetData(AnsiString d)				override;
    void      Initial(void);

    void      ReqPrepare(void);
    bool      ReqDone(void);
    double     GetFloat(bool SrcReconstruct=false)	override{	return(GetNumeric(SrcReconstruct)); }
    virtual Operand     *MakeDup(LocalReg *)	override{	return(NULL);   }
    ExeHistAttr    GetHistAttr(void)			override{	return(EHA_OnlyExec);  }
    int     GetPreDataBitSize(void)				override{	return(-1);      }
    bool    SaveBinHeader(FILE *file)			override;
    bool    LoadBinHeader(FILE *file)			override;

    bool       LetSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       LetBSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       AddSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       SubSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       AndSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       OrSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)		override;
    bool       XorSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       NotSeq(Sequence *parent,bool FlagConnectedMode)					override;
    bool       FlushSeq(Sequence *parent,bool FlagConnectedMode)				override;
    bool       AllocSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       IndSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       BitloadSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src1 ,Operand *src2 ,Operand *src3)	override;
    bool       FlagSeq(Sequence *parent,bool FlagConnectedMode)					override;
    bool       CAndSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       COrSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       CXorSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       EqualSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       ZoneSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src1,Operand *src2)	override;
    bool       PartEqSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       UnequalSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)override;
    bool       GreaterSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)override;
    bool       LargeSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       LessSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       SmallSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       MultSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       DivSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       ModSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       StrMoveSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src1 ,Operand *src2)	override;
    bool       LowerSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       UpperSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       StateSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       TWSetSeq(Sequence *parent,bool FlagConnectedMode)				override;
    bool       FSetSeq(Sequence *parent,bool FlagConnectedMode)					override;
    bool       FResetSeq(Sequence *parent,bool FlagConnectedMode)				override;
    bool       RxTimeoutSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src1 ,Operand *src2)	override;	
    bool       StrLenSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)		override;
    bool       AddFileSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       OpenLFileSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       LoadFileSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       CloseFileSeq(Sequence *parent,bool FlagConnectedMode)			override;
    bool       DeleteFileSeq(Sequence *parent,bool FlagConnectedMode)			override;
    bool       BPrintSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       BScanSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       InputFromString(Sequence *parent,AnsiString &Src)				override;
    bool       FloatNumSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;

};
↑D-20051026------------------------------------------------------------------*/


class   FifoClass : public NPList<FifoClass>
{
  public:
    QByteArray  Str;
    FifoClass(const QByteArray &data){    Str=data;   }
    FifoClass(int   data){      Str=QByteArray::number(data);   }
};

class   FifoOperand : public Operand ,public NPList<FifoOperand>
{
  public:
    NPListPack<FifoClass>   Data;
    int                     DataNumb;   //マルチスレッドでの個数確認
    volatile    bool        ReqList;
    QStringList             *ReqListData;
	QMutex					LockMutex;

	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    FifoOperand(SeqControl *BaseParent);
    ~FifoOperand(void){}

    QString    GetName(void)	override;
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    virtual const	char    *GetKindName(void)	override{ return("Fifo");  }
    virtual int     GetKindCode(void)			override{  return(KindCodeFifo); }
    bool    Load(char buff[])					override;
    int    GetNumeric(bool SrcReconstruct=false)override;
    bool      IsGetEnabled(void)				override;
    void      SetData(int d)					override;
    void      SetData(const QByteArray &d)		override;
	void      SetData(const QString &d)	;
    int    GetStringCount(void)					override;
    QByteArray   GetString(bool ThreadMode=true)override;
    void      FlushSource(void)					override;
    int       GetStackedNumb(void);
    int       GetStackedList(QStringList *d);
    void       GetStackedListInner(void);
    double     GetFloat(bool SrcReconstruct=false)	override{    return(GetNumeric(SrcReconstruct)); }
    virtual Operand     *MakeDup(LocalReg *)	override{	return(NULL);	}
    ExeHistAttr    GetHistAttr(void)			override{	return(EHA_OnlyExec);	}
    int     GetPreDataBitSize(void)				override{	return(-1);		}

	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//    parent
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    bool       LetSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       LetBSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       AddSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       SubSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       AndSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       OrSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)		override;
    bool       XorSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       NotSeq(Sequence *parent,bool FlagConnectedMode)					override;
    bool       FlushSeq(Sequence *parent,bool FlagConnectedMode)				override;
    bool       AllocSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       IndSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       BitloadSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src1 ,Operand *src2 ,Operand *src3)	override;
    bool       FlagSeq(Sequence *parent,bool FlagConnectedMode)					override;
    bool       CAndSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       COrSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       CXorSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       EqualSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       ZoneSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src1,Operand *src2)	override;
    bool       PartEqSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       UnequalSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)override;
    bool       GreaterSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)override;
    bool       LargeSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       LessSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       SmallSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       MultSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       DivSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       ModSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       StrMoveSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src1 ,Operand *src2)	override;
    bool       LowerSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       UpperSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       StateSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       TWSetSeq(Sequence *parent,bool FlagConnectedMode)				override;
    bool       FSetSeq(Sequence *parent,bool FlagConnectedMode)					override;
    bool       FResetSeq(Sequence *parent,bool FlagConnectedMode)				override;
    bool       RxTimeoutSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src1 ,Operand *src2)	override;
    bool       StrLenSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)		override;
    bool       AddFileSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       OpenLFileSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       LoadFileSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       CloseFileSeq(Sequence *parent,bool FlagConnectedMode)			override;
    bool       DeleteFileSeq(Sequence *parent,bool FlagConnectedMode)			override;
    bool       BPrintSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       BScanSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       InputFromString(Sequence *parent,QString &Src)					override;
    bool       FloatNumSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;

	void		Lock(void)		{	LockMutex.lock();	}
	void		Unlock(void)	{	LockMutex.unlock();	}

};

/*----------------------------------------------------------------------------*/
//  1.日本語名
//
//  2.概要
//
//  3.機能説明
//
//  4.備考
//
/*----------------------------------------------------------------------------*/

class   DLLVarOperand : public Operand ,public NPList<DLLVarOperand>
{
	DLLVarInterface	*Interface;
  public:
    QByteArray  Data;
    QString  VersionStr;

    DLLVarOperand(SeqControl *BaseParent);
	DLLVarOperand(const DLLVarOperand &src);
    ~DLLVarOperand(void);

	DLLVarInterface	*GetInterface(void)	{	return Interface;	}

	QString    GetName(void)	override;

	bool	IsDLLVarDLL(void);
	bool	LoadDLL(const QString &filename);
    QString	GetDLLVarName(void);
	void	GetExportFunctions(QStringList &Str);

	QString	GetFileName(void);
	QString	GetCopyright(void);
	WORD	GetVersion(void);
	WORD	GetDLLType(void);
	QString	GetExplain(void);

    virtual const	char    *GetKindName(void)	override{ return("DLLVar");  }
    virtual int     GetKindCode(void)			override{  return(KindCodeDLLVar); }
    bool    Load(char buff[])					override;
    bool    OpenInitialize(void);

    int		GetNumeric(bool SrcReconstruct=false)	override;
    bool	IsGetEnabled(void)						override{	return(true);   }
    void	SetData(int d)							override;
    void	SetData(const QByteArray &d)			override;
    int		GetStringCount(void)					override;
    QByteArray	GetString(bool ThreadMode=true)		override;
    double	GetFloat(bool SrcReconstruct=false)		override{	return(GetNumeric(SrcReconstruct)); }
    virtual Operand     *MakeDup(LocalReg *)		override{	return(NULL);   }
    ExeHistAttr    GetHistAttr(void)				override{	return(EHA_Never);  }
    int     GetPreDataBitSize(void)					override{	return(-1);      }

    bool    IsDebugMode(void);
    void    DLLDebug(QApplication *app);
    bool    SaveBinHeader(FILE *file)	override;
    bool    LoadBinHeader(FILE *file)	override;

    bool       LetSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       LetBSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       AddSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       SubSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       AndSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       OrSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)		override;
    bool       XorSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       NotSeq(Sequence *parent,bool FlagConnectedMode)					override;
    bool       FlushSeq(Sequence *parent,bool FlagConnectedMode)				override;
    bool       AllocSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       IndSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       BitloadSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src1 ,Operand *src2 ,Operand *src3)	override;
    bool       FlagSeq(Sequence *parent,bool FlagConnectedMode)					override;
    bool       CAndSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       COrSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       CXorSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       EqualSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       ZoneSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src1,Operand *src2)	override;
    bool       PartEqSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       UnequalSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)override;
    bool       GreaterSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)override;
    bool       LargeSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       LessSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       SmallSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       MultSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       DivSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       ModSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       StrMoveSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src1 ,Operand *src2)	override;
    bool       LowerSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       UpperSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       StateSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       TWSetSeq(Sequence *parent,bool FlagConnectedMode)				override;
    bool       FSetSeq(Sequence *parent,bool FlagConnectedMode)					override;
    bool       FResetSeq(Sequence *parent,bool FlagConnectedMode)				override;
    bool       RxTimeoutSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src1 ,Operand *src2)	override;
    bool       StrLenSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)		override;
    bool       AddFileSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       OpenLFileSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       LoadFileSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       CloseFileSeq(Sequence *parent,bool FlagConnectedMode)			override;
    bool       DeleteFileSeq(Sequence *parent,bool FlagConnectedMode)			override;
    bool       BPrintSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       BScanSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)	override;
    bool       FDLLCmdSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src1=NULL ,Operand *src2=NULL ,Operand *src3=NULL ,Operand *src4=NULL ,Operand *src5=NULL);
    bool       InputFromString(Sequence *parent,QString &Src)					override;
    bool       FloatNumSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)override;

	virtual	void		TransmitDirectly(GUIDirectMessage *packet)	override;

	//From DLLManager
	bool	GetRelatedDLL(QStringList &DLLFileNames);
	char	*GetRelatedDLLSystemVersion(const QString &DLLFileName ,VersionType vtype);
	const char	*GetSystemVersion(VersionType vtype);

	bool	CheckSystemVersionFunc(QStringList &Str 
							   ,const QString &DLLType 
							   ,const QString &DLLRoot 
							   ,const QString &DLLName);
};

class	DLLVarPack : public NPListPack<DLLVarOperand>,public ServiceForLayers
{
public:
	DLLVarPack(LayersBase *base):ServiceForLayers(base){}

	int	SearchAddDLL(SeqControl *SeqBase,int32 &ErrorCode);
};

class   SeqCommandList : public NPList<SeqCommandList>
{
	SeqControl	*BaseParent;
  public:
    DWORD       NowTime;
    QString  Cmd;
    int      ParamNumb;
    QByteArray  Param1;
    QByteArray  Param2;
    QByteArray  Param3;
	QByteArray  Param4;

    QByteArray  ResParam1;
    QByteArray  ResParam2;
    QByteArray  ResParam3;
	QByteArray  ResParam4;

    SeqCommandList(SeqControl *baseParent,QString &cmdstr);
    SeqCommandList(SeqControl *baseParent,QString &cmdstr ,QString &datastr);
    SeqCommandList(SeqControl *baseParent,QString &cmdstr ,int datastr);
    SeqCommandList(SeqControl *baseParent,QString &cmdstr ,int datastr1 ,int datastr2);
    SeqCommandList(SeqControl *baseParent,QString &cmdstr ,QString &datastr1 ,int datastr2);
    SeqCommandList(SeqControl *baseParent,QString &cmdstr ,QString &datastr1 ,QString &datastr2);
    SeqCommandList(SeqControl *baseParent,QString &cmdstr ,QString &datastr1 ,QString &datastr2 ,int data3);
    SeqCommandList(SeqControl *baseParent,QString &cmdstr ,int datas1 ,int datas2 ,int data3);
    SeqCommandList(SeqControl *baseParent,QString &cmdstr ,int datas1 ,int datas2 ,int data3 ,int data4);

    SeqCommandList(SeqControl *baseParent,QString &cmdstr ,QByteArray &datastr);
    SeqCommandList(SeqControl *baseParent,QString &cmdstr ,QByteArray &datastr1 ,int datastr2);
    SeqCommandList(SeqControl *baseParent,QString &cmdstr ,QByteArray &datastr1 ,QByteArray &datastr2);
    SeqCommandList(SeqControl *baseParent,QString &cmdstr ,QByteArray &datastr1 ,QByteArray &datastr2 ,int data3);


    void    SetResult(QString &datastr);
    void    SetResult(int datastr);
    void    SetResult(int datastr1 ,int datastr2);
    void    SetResult(QString &datastr1 ,int datastr2);
    void    SetResult(QString &datastr1 ,QString &datastr2);
    void    SetResult(QString &datastr1 ,QString &datastr2 ,int data3);
    void    SetResult(int data1 ,int data2 ,int datastr3);
    void    SetResult(int data1 ,int data2 ,int datastr3 ,int datastr4);

    void    SetResult(QByteArray &datastr);
    void    SetResult(QByteArray &datastr1 ,int datastr2);
    void    SetResult(QByteArray &datastr1 ,QByteArray &datastr2);
    void    SetResult(QByteArray &datastr1 ,QByteArray &datastr2 ,int data3);

    QString  GetNowTimeString(void);
	SeqControl	*GetSeqControl(){	return BaseParent;	}
};



/*----------------------------------------------------------------------------*/
//  1.日本語名
//
//  2.概要
//
//  3.機能説明
//
//  4.備考
//
/*----------------------------------------------------------------------------*/

class   FlagOrNode;
class   FlagAnd;
enum    ExecuteCondition{
        _ExeTrue
        ,_ExeFalse
        ,_Unconditional
        };

class   FlagBase
{
  protected:
    FlagBase    **Parent;
    int         ParentNumb;
    bool        NegMode;
  public:
    FlagBase(void);
    virtual ~FlagBase(void);

    virtual bool    Compare(bool *Flag, int flagLen)=0;
    void    SetParent(FlagBase *parent);
    void    ClearParent(void);
    void    SetNegMode(bool negmode){   NegMode=negmode;    }
    bool    GetNegMode(void)		{	return(NegMode);    }
    virtual void    Balansize(void)=0;    //不要なツリーを排除する
    virtual void    SearchAndSetNull(FlagBase *child)=0;
    void            SearchParentAndSetNull(FlagBase *parent);
    virtual void    AppendLastToEach(FlagBase *child)=0;
    virtual int GetLen(void)=0;
    virtual QString  GetFlagString(void)=0;
  protected:
    void    Copy(FlagBase &src);
};


class   FlagOrNode : public FlagBase
{
  friend class  FlagBase;
  friend class  FlagAnd;

    FlagBase **OrChildren;
    int         OrChildrenNumb;
    bool        LogicConnection;

  public:
    FlagOrNode(void);
    ~FlagOrNode(void);

    virtual	bool    Compare(bool *Flag, int flagLen)	override;
    int     GetOrNumb(void){    return(OrChildrenNumb); }

    void    AddChild(FlagBase *item);
    FlagOrNode  &operator=(FlagOrNode &src);

    virtual	void    Balansize(void)	override;    //不要なツリーを排除する
    virtual	void    SearchAndSetNull(FlagBase *child)	override;
    virtual	void    AppendLastToEach(FlagBase *child)	override;
    virtual	int     GetLen(void)						override;

    bool        IsConnection(void);     //論理結合のときtrue
    virtual	QString  GetFlagString(void)				override;
    void        SetLogicConnectionTrue(void){   LogicConnection=true;   }
};


class   FlagAnd : public FlagBase
{
  friend class  FlagOrNode;
    FlagBase    *Child;

  public:
    ExecuteCondition   Flag;

    FlagAnd(void);
    ~FlagAnd(void);

    QChar    *Get(QChar *fp);
    virtual	bool    Compare(bool *Flag, int flagLen)	override;
    void    AppendList(FlagBase *item);

    FlagAnd &operator=(FlagAnd &src);
    virtual	void    Balansize(void)	override;    //不要なツリーを排除する
    virtual	void    SearchAndSetNull(FlagBase *child)	override;
    virtual	void    AppendLastToEach(FlagBase *child)	override;
    virtual	int     GetLen(void)						override;
    virtual	QString	GetFlagString(void)					override;
};


class  TmpLoadFlags
{
  public:
    enum    TmpLFMode{
            __FFNone
            ,__FlagSign
            ,__NegSign
            ,__StartKK
            ,__EndKK
            ,__OrKK
            }Kind;
    QString    FlagSign;
    int     AllocNumb;

    FlagBase    *Items;

    TmpLoadFlags(void);
    ~TmpLoadFlags(void);

    void    AddSign(QString c);
    void    MakeFlagSignItem(void);
};


#define OpID_Let            1
#define OpID_LetB           2
#define OpID_Add            3
#define OpID_Sub            4
#define OpID_And            5
#define OpID_Or             6
#define OpID_Xor            7
#define OpID_Not            8
#define OpID_Flush          9
#define OpID_Alloc          10
#define OpID_Ind            11
#define OpID_Bitload        12
#define OpID_Goto           13
#define OpID_EqualGoto      14
#define OpID_NotEqualGoto   15
#define OpID_LargeGoto      16
#define OpID_GreaterGoto    17
#define OpID_SmallGoto      18
#define OpID_LessGoto       19
#define OpID_AndGoto        20
#define OpID_OrGoto         21
#define OpID_XorGoto        22
#define OpID_Set            23
#define OpID_Reset          24
#define OpID_Flag           25
#define OpID_Wait           26
#define OpID_CAnd           27
#define OpID_COr            28
#define OpID_CXor           29
#define OpID_Equal          30
#define OpID_Zone           31
#define OpID_PartEq         32
#define OpID_Unequal        33
#define OpID_Greater        34
#define OpID_Large          35
#define OpID_Less           36
#define OpID_Small          37
#define OpID_MOut           38
#define OpID_MYesNo         39
#define OpID_Mult           40
#define OpID_Div            41
#define OpID_Mod            42
#define OpID_StrMove        43
#define OpID_Lower          44
#define OpID_Upper          45
#define OpID_State          46
#define OpID_Return         47
#define OpID_TWSet          48
#define OpID_TWaitLess      49
#define OpID_TWaitGreater   50
#define OpID_FSet           51
#define OpID_FReset         52
#define OpID_RxTimeout      53
#define OpID_StrLen         54
#define OpID_AddFile        55
#define OpID_OpenLFile      56
#define OpID_LoadFile       57
#define OpID_CloseFile      58
#define OpID_DeleteFile     59
#define OpID_BPrint         60
#define OpID_BScan          61
#define OpID_SyncGet        62
#define OpID_DLLCmd         63
#define OpID_ShowOn         64
#define OpID_ShowOff        65
#define OpID_Nop            66
#define OpID_MInput         67
#define OpID_FloatNum       68
#define OpID_Call           69
#define OpID_MessageColor   70

#define MaxBreakPoint   16
class   SeqLine :public NPList<SeqLine>
{
	SeqControl	*BaseParent;
  public:
    int LNumber;
    int LCode;  //行のＩＤコード

    Operand *Op1;
    Operand *Op2;
    Operand *Op3;
    Operand *Op4;
	Operand *Op5;
	Operand *Op6;
    FlagOrNode  eFlag;

    SeqLine(SeqControl *baseParent);
    ~SeqLine(void);

	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//    flag
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    bool    ExecuteEOk(Sequence *Parent,FlagExecuted &eflag);

    void    Set(int lnumb , ExecuteCondition cond);
    void    Set(int lnumb , ExecuteCondition cond ,Operand *ope1);
    void    Set(int lnumb , ExecuteCondition cond ,Operand *ope1 ,Operand *ope2);
    void    Set(int lnumb , ExecuteCondition cond ,Operand *ope1 ,Operand *ope2 ,Operand *ope3);
    void    Set(int lnumb , ExecuteCondition cond ,Operand *ope1 ,Operand *ope2 ,Operand *ope3 ,Operand *ope4);
	void    Set(int lnumb , ExecuteCondition cond ,Operand *ope1 ,Operand *ope2 ,Operand *ope3 ,Operand *ope4 ,Operand *ope5);
	void    Set(int lnumb , ExecuteCondition cond ,Operand *ope1 ,Operand *ope2 ,Operand *ope3 ,Operand *ope4 ,Operand *ope5 ,Operand *ope6);

    virtual bool   Execute(Sequence *parent ,bool FlagConnectedMode)	=0;
    virtual QString GetName(void)			=0;
    virtual int     GetOpCount(void)		=0;
    virtual unsigned short  GetOpID(void)	=0;
	static	SeqLine *Get(unsigned short OpID ,SeqControl *parent);
	Operand *GetOpe(int n);

    void    Copy(LocalReg *DestLReg ,SeqLine *dest);
	SeqControl	*GetSeqControl(void){	return BaseParent;	}

    virtual SeqLine *MakeDup(LocalReg *DestLReg)	=0;
    bool    GetFlagConnectedMode(void){     return(eFlag.IsConnection());   }

    bool    WriteBin(FILE *file);
    bool    ReadBin(FILE *file);
};


/*----------------------------------------------------------------------------*/
//  1.日本語名
//
//  2.概要
//
//  3.機能説明
//
//  4.備考
//
/*----------------------------------------------------------------------------*/
class   LetSeq : public SeqLine
{
  public:
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
	  LetSeq(SeqControl *baseParent):SeqLine(baseParent){}

    bool   Execute(Sequence *parent ,bool FlagConnectedMode) override;
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    QString    GetName(void)	override	{ return(QString("Let"));  }
    unsigned short  GetOpID(void) override	{  return(OpID_Let);   }
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    int     GetOpCount(void) override{   return(2);  }
    SeqLine *MakeDup(LocalReg *DestLReg) override;
};

/*----------------------------------------------------------------------------*/
//  1.日本語名
//
//  2.概要
//
//  3.機能説明
//
//  4.備考
//
/*----------------------------------------------------------------------------*/
class   LetBSeq : public SeqLine
{
  public:
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    LetBSeq(SeqControl *baseParent):SeqLine(baseParent){}

    bool   Execute(Sequence *parent ,bool FlagConnectedMode) override;
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    QString    GetName(void)	override{ return(QString("LetB"));  }
    unsigned short  GetOpID(void) override{  return(OpID_LetB);   }
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    int     GetOpCount(void) override{   return(2);  }
    SeqLine *MakeDup(LocalReg *DestLReg) override;
};

/*----------------------------------------------------------------------------*/
//  1.日本語名
//
//  2.概要
//
//  3.機能説明
//
//  4.備考
//
/*----------------------------------------------------------------------------*/
class   AddSeq : public SeqLine
{
  public:
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    AddSeq(SeqControl *baseParent):SeqLine(baseParent){}

    bool   Execute(Sequence *parent ,bool FlagConnectedMode) override;
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    QString    GetName(void)	override{ return(QString("Add"));  }
    unsigned short  GetOpID(void) override{  return(OpID_Add);   }
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    int     GetOpCount(void) override{   return(2);  }
    SeqLine *MakeDup(LocalReg *DestLReg) override;
};

/*----------------------------------------------------------------------------*/
//  1.日本語名
//
//  2.概要
//
//  3.機能説明
//
//  4.備考
//
/*----------------------------------------------------------------------------*/
class   SubSeq : public SeqLine
{
  public:
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    SubSeq(SeqControl *baseParent):SeqLine(baseParent){}

    bool   Execute(Sequence *parent ,bool FlagConnectedMode) override;
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    QString    GetName(void)	override{ return(QString("Sub"));  }
    unsigned short  GetOpID(void) override{  return(OpID_Sub);   }
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    int     GetOpCount(void) override{   return(2);  }
    SeqLine *MakeDup(LocalReg *DestLReg) override;
};

/*----------------------------------------------------------------------------*/
//  1.日本語名
//
//  2.概要
//
//  3.機能説明
//
//  4.備考
//
/*----------------------------------------------------------------------------*/
class   AndSeq : public SeqLine
{
  public:
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    AndSeq(SeqControl *baseParent):SeqLine(baseParent){}

    bool   Execute(Sequence *parent ,bool FlagConnectedMode) override;
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    QString    GetName(void)	override{ return(QString("And"));  }
    unsigned short  GetOpID(void) override{  return(OpID_And);   }
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    int     GetOpCount(void) override{   return(2);  }
    SeqLine *MakeDup(LocalReg *DestLReg) override;
};

/*----------------------------------------------------------------------------*/
//  1.日本語名
//
//  2.概要
//
//  3.機能説明
//
//  4.備考
//
/*----------------------------------------------------------------------------*/
class   OrSeq : public SeqLine
{
  public:
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    OrSeq(SeqControl *baseParent):SeqLine(baseParent){}

    bool   Execute(Sequence *parent ,bool FlagConnectedMode) override;
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    QString    GetName(void)	override{ return(QString("Or"));  }
    unsigned short  GetOpID(void) override{  return(OpID_Or);   }
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    int     GetOpCount(void) override{   return(2);  }
    SeqLine *MakeDup(LocalReg *DestLReg) override;
};

/*----------------------------------------------------------------------------*/
//  1.日本語名
//
//  2.概要
//
//  3.機能説明
//
//  4.備考
//
/*----------------------------------------------------------------------------*/
class   XorSeq : public SeqLine
{
  public:
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    XorSeq(SeqControl *baseParent):SeqLine(baseParent){}

    bool   Execute(Sequence *parent ,bool FlagConnectedMode) override;
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    QString    GetName(void)	override{ return(QString("Xor"));  }
    unsigned short  GetOpID(void) override{  return(OpID_Xor);   }
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    int     GetOpCount(void) override{   return(2);  }
    SeqLine *MakeDup(LocalReg *DestLReg) override;
};

/*----------------------------------------------------------------------------*/
//  1.日本語名
//
//  2.概要
//
//  3.機能説明
//
//  4.備考
//
/*----------------------------------------------------------------------------*/
class   NotSeq : public SeqLine
{
  public:
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    NotSeq(SeqControl *baseParent):SeqLine(baseParent){}

    bool   Execute(Sequence *parent ,bool FlagConnectedMode) override;
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    QString    GetName(void)	override{ return(QString("Not"));  }
    unsigned short  GetOpID(void) override{  return(OpID_Not);   }
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    int     GetOpCount(void) override{   return(1);  }
    SeqLine *MakeDup(LocalReg *DestLReg) override;
};

/*----------------------------------------------------------------------------*/
//  1.日本語名
//
//  2.概要
//
//  3.機能説明
//
//  4.備考
//
/*----------------------------------------------------------------------------*/
class   FlushSeq : public SeqLine
{
  public:
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    FlushSeq(SeqControl *baseParent):SeqLine(baseParent){}

    bool   Execute(Sequence *parent ,bool FlagConnectedMode) override;
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    QString    GetName(void)	override{ return(QString("Flush"));  }
    unsigned short  GetOpID(void) override{  return(OpID_Flush);   }
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    int     GetOpCount(void) override{   return(1);  }
    SeqLine *MakeDup(LocalReg *DestLReg) override;
};

/*----------------------------------------------------------------------------*/
//  1.日本語名
//
//  2.概要
//
//  3.機能説明
//
//  4.備考
//
/*----------------------------------------------------------------------------*/
class   AllocSeq : public SeqLine
{
  public:
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    AllocSeq(SeqControl *baseParent):SeqLine(baseParent){}

    bool   Execute(Sequence *parent ,bool FlagConnectedMode) override;
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    QString    GetName(void)	override{ return(QString("Alloc"));  }
    unsigned short  GetOpID(void) override{  return(OpID_Alloc);   }
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    int     GetOpCount(void) override{   return(2);  }
    SeqLine *MakeDup(LocalReg *DestLReg) override;
};

/*----------------------------------------------------------------------------*/
//  1.日本語名
//
//  2.概要
//
//  3.機能説明
//
//  4.備考
//
/*----------------------------------------------------------------------------*/
class   IndSeq : public SeqLine
{
  public:
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    IndSeq(SeqControl *baseParent):SeqLine(baseParent){}

    bool   Execute(Sequence *parent ,bool FlagConnectedMode) override;
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    QString    GetName(void)	override{ return(QString("Ind"));  }
    unsigned short  GetOpID(void) override{  return(OpID_Ind);   }
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    int     GetOpCount(void) override{   return(2);  }
    SeqLine *MakeDup(LocalReg *DestLReg) override;
};

/*----------------------------------------------------------------------------*/
//  1.日本語名
//
//  2.概要
//
//  3.機能説明
//
//  4.備考
//
/*----------------------------------------------------------------------------*/
class   BitloadSeq : public SeqLine
{
  public:
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    BitloadSeq(SeqControl *baseParent):SeqLine(baseParent){}

    bool   Execute(Sequence *parent ,bool FlagConnectedMode) override;
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    QString    GetName(void)	override{ return(QString("Bitload"));  }
    unsigned short  GetOpID(void) override{  return(OpID_Bitload);   }
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    int     GetOpCount(void) override{   return(4);  }
    SeqLine *MakeDup(LocalReg *DestLReg) override;
};

/*----------------------------------------------------------------------------*/
//  1.日本語名
//
//  2.概要
//
//  3.機能説明
//
//  4.備考
//
/*----------------------------------------------------------------------------*/
class   GotoSeq : public SeqLine
{
  public:
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    GotoSeq(SeqControl *baseParent):SeqLine(baseParent){}

    bool   Execute(Sequence *parent ,bool FlagConnectedMode) override;
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    QString    GetName(void)	override{ return(QString("Goto"));  }
    unsigned short  GetOpID(void) override{  return(OpID_Goto);   }
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    int     GetOpCount(void) override{   return(1);  }
    SeqLine *MakeDup(LocalReg *DestLReg) override;
};

/*----------------------------------------------------------------------------*/
//  1.日本語名
//
//  2.概要
//
//  3.機能説明
//
//  4.備考
//
/*----------------------------------------------------------------------------*/
class   EqualGotoSeq : public SeqLine
{
  public:
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    EqualGotoSeq(SeqControl *baseParent):SeqLine(baseParent){}

    bool   Execute(Sequence *parent ,bool FlagConnectedMode) override;
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    QString    GetName(void)	override{ return(QString("EqualGoto"));  }
    unsigned short  GetOpID(void) override{  return(OpID_EqualGoto);   }
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    int     GetOpCount(void) override{   return(3);  }
    SeqLine *MakeDup(LocalReg *DestLReg) override;
};

/*----------------------------------------------------------------------------*/
//  1.日本語名
//
//  2.概要
//
//  3.機能説明
//
//  4.備考
//
/*----------------------------------------------------------------------------*/
class   NotEqualGotoSeq : public SeqLine
{
  public:
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    NotEqualGotoSeq(SeqControl *baseParent):SeqLine(baseParent){}

    bool   Execute(Sequence *parent ,bool FlagConnectedMode) override;
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    QString    GetName(void)	override{ return(QString("NotEqualGoto"));  }
    unsigned short  GetOpID(void) override{  return(OpID_NotEqualGoto);   }
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    int     GetOpCount(void) override{   return(3);  }
    SeqLine *MakeDup(LocalReg *DestLReg) override;
};

/*----------------------------------------------------------------------------*/
//  1.日本語名
//
//  2.概要
//
//  3.機能説明
//
//  4.備考
//
/*----------------------------------------------------------------------------*/
class   LargeGotoSeq : public SeqLine
{
  public:
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    LargeGotoSeq(SeqControl *baseParent):SeqLine(baseParent){}

    bool   Execute(Sequence *parent ,bool FlagConnectedMode) override;
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    QString    GetName(void)	override{ return(QString("LargeGoto"));  }
    unsigned short  GetOpID(void) override{  return(OpID_LargeGoto);   }
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    int     GetOpCount(void) override{   return(3);  }
    SeqLine *MakeDup(LocalReg *DestLReg) override;
};

/*----------------------------------------------------------------------------*/
//  1.日本語名
//
//  2.概要
//
//  3.機能説明
//
//  4.備考
//
/*----------------------------------------------------------------------------*/
class   GreaterGotoSeq : public SeqLine
{
  public:
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    GreaterGotoSeq(SeqControl *baseParent):SeqLine(baseParent){}

    bool   Execute(Sequence *parent ,bool FlagConnectedMode) override;
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    QString    GetName(void)	override{ return(QString("GreaterGoto"));  }
    unsigned short  GetOpID(void) override{  return(OpID_GreaterGoto);   }
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    int     GetOpCount(void) override{   return(3);  }
    SeqLine *MakeDup(LocalReg *DestLReg) override;
};


/*----------------------------------------------------------------------------*/
//  1.日本語名
//
//  2.概要
//
//  3.機能説明
//
//  4.備考
//
/*----------------------------------------------------------------------------*/
class   SmallGotoSeq : public SeqLine
{
  public:
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    SmallGotoSeq(SeqControl *baseParent):SeqLine(baseParent){}

    bool   Execute(Sequence *parent ,bool FlagConnectedMode) override;
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    QString    GetName(void)	override{ return(QString("SmallGoto"));  }
    unsigned short  GetOpID(void) override{  return(OpID_SmallGoto);   }
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    int     GetOpCount(void) override{   return(3);  }
    SeqLine *MakeDup(LocalReg *DestLReg) override;
};


/*----------------------------------------------------------------------------*/
//  1.日本語名
//
//  2.概要
//
//  3.機能説明
//
//  4.備考
//
/*----------------------------------------------------------------------------*/
class   LessGotoSeq : public SeqLine
{
  public:
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    LessGotoSeq(SeqControl *baseParent):SeqLine(baseParent){}

    bool   Execute(Sequence *parent ,bool FlagConnectedMode) override;
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    QString    GetName(void)	override{ return(QString("LessGoto"));  }
    unsigned short  GetOpID(void) override{  return(OpID_LessGoto);   }
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    int     GetOpCount(void) override{   return(3);  }
    SeqLine *MakeDup(LocalReg *DestLReg) override;
};



/*----------------------------------------------------------------------------*/
//  1.日本語名
//
//  2.概要
//
//  3.機能説明
//
//  4.備考
//
/*----------------------------------------------------------------------------*/
class   AndGotoSeq : public SeqLine
{
  public:
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    AndGotoSeq(SeqControl *baseParent):SeqLine(baseParent){}

    bool   Execute(Sequence *parent ,bool FlagConnectedMode) override;
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    QString    GetName(void)	override{ return(QString("AndGoto"));  }
    unsigned short  GetOpID(void) override{  return(OpID_AndGoto);   }
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    int     GetOpCount(void) override{   return(3);  }
    SeqLine *MakeDup(LocalReg *DestLReg) override;
};

/*----------------------------------------------------------------------------*/
//  1.日本語名
//
//  2.概要
//
//  3.機能説明
//
//  4.備考
//
/*----------------------------------------------------------------------------*/
class   OrGotoSeq : public SeqLine
{
  public:
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    OrGotoSeq(SeqControl *baseParent):SeqLine(baseParent){}

    bool   Execute(Sequence *parent ,bool FlagConnectedMode) override;
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    QString    GetName(void)	override{ return(QString("OrGoto"));  }
    unsigned short  GetOpID(void) override{  return(OpID_OrGoto);   }
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    int     GetOpCount(void) override{   return(3);  }
    SeqLine *MakeDup(LocalReg *DestLReg) override;
};


/*----------------------------------------------------------------------------*/
//  1.日本語名
//
//  2.概要
//
//  3.機能説明
//
//  4.備考
//
/*----------------------------------------------------------------------------*/
class   XorGotoSeq : public SeqLine
{
  public:
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    XorGotoSeq(SeqControl *baseParent):SeqLine(baseParent){}

    bool   Execute(Sequence *parent ,bool FlagConnectedMode) override;
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    QString    GetName(void)	override{ return(QString("XorGoto"));  }
    unsigned short  GetOpID(void) override{  return(OpID_XorGoto);   }
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    int     GetOpCount(void) override{   return(3);  }
    SeqLine *MakeDup(LocalReg *DestLReg) override;
};




/*----------------------------------------------------------------------------*/
//  1.日本語名
//
//  2.概要
//
//  3.機能説明
//
//  4.備考
//
/*----------------------------------------------------------------------------*/
class   SetSeq : public SeqLine
{
  public:
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    SetSeq(SeqControl *baseParent):SeqLine(baseParent){}

    bool   Execute(Sequence *parent ,bool FlagConnectedMode) override;
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    QString    GetName(void)	override{ return(QString("Set"));  }
    unsigned short  GetOpID(void) override{  return(OpID_Set);   }
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    int     GetOpCount(void) override{   return(0);  }
    SeqLine *MakeDup(LocalReg *DestLReg) override;
};

/*----------------------------------------------------------------------------*/
//  1.日本語名
//
//  2.概要
//
//  3.機能説明
//
//  4.備考
//
/*----------------------------------------------------------------------------*/
class   ResetSeq : public SeqLine
{
  public:
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    ResetSeq(SeqControl *baseParent):SeqLine(baseParent){}

    bool   Execute(Sequence *parent ,bool FlagConnectedMode) override;
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    QString    GetName(void)	override{ return(QString("Reset"));  }
    unsigned short  GetOpID(void) override{  return(OpID_Reset);   }
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    int     GetOpCount(void) override{   return(0);  }
    SeqLine *MakeDup(LocalReg *DestLReg) override;
};

/*----------------------------------------------------------------------------*/
//  1.日本語名
//
//  2.概要
//
//  3.機能説明
//
//  4.備考
//
/*----------------------------------------------------------------------------*/
class   FlagSeq : public SeqLine
{
  public:
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    FlagSeq(SeqControl *baseParent):SeqLine(baseParent){}

    bool   Execute(Sequence *parent ,bool FlagConnectedMode) override;
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    QString    GetName(void)	override{ return(QString("Flag"));  }
    unsigned short  GetOpID(void) override{  return(OpID_Flag);   }
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    int     GetOpCount(void) override{   return(1);  }
    SeqLine *MakeDup(LocalReg *DestLReg) override;
};

/*----------------------------------------------------------------------------*/
//  1.日本語名
//
//  2.概要
//
//  3.機能説明
//
//  4.備考
//
/*----------------------------------------------------------------------------*/
class   WaitSeq : public SeqLine
{
  public:
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    WaitSeq(SeqControl *baseParent):SeqLine(baseParent){}

    bool   Execute(Sequence *parent ,bool FlagConnectedMode) override;
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    QString    GetName(void)	override{ return(QString("Wait"));  }
    unsigned short  GetOpID(void) override{  return(OpID_Wait);   }
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    int     GetOpCount(void) override{   return(1);  }
    SeqLine *MakeDup(LocalReg *DestLReg) override;
};

/*----------------------------------------------------------------------------*/
//  1.日本語名
//
//  2.概要
//
//  3.機能説明
//
//  4.備考
//
/*----------------------------------------------------------------------------*/
class   CAndSeq : public SeqLine
{
  public:
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    CAndSeq(SeqControl *baseParent):SeqLine(baseParent){}

    bool   Execute(Sequence *parent ,bool FlagConnectedMode) override;
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    QString    GetName(void)	override{ return(QString("CAnd"));  }
    unsigned short  GetOpID(void) override{  return(OpID_CAnd);   }
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    int     GetOpCount(void) override{   return(2);  }
    SeqLine *MakeDup(LocalReg *DestLReg) override;
};

/*----------------------------------------------------------------------------*/
//  1.日本語名
//
//  2.概要
//
//  3.機能説明
//
//  4.備考
//
/*----------------------------------------------------------------------------*/
class   COrSeq : public SeqLine
{
  public:
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    COrSeq(SeqControl *baseParent):SeqLine(baseParent){}

    bool   Execute(Sequence *parent ,bool FlagConnectedMode) override;
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    QString    GetName(void)	override{ return(QString("COr"));  }
    unsigned short  GetOpID(void) override{  return(OpID_COr);   }
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    int     GetOpCount(void) override{   return(2);  }
    SeqLine *MakeDup(LocalReg *DestLReg) override;
};

/*----------------------------------------------------------------------------*/
//  1.日本語名
//
//  2.概要
//
//  3.機能説明
//
//  4.備考
//
/*----------------------------------------------------------------------------*/
class   CXorSeq : public SeqLine
{
  public:
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    CXorSeq(SeqControl *baseParent):SeqLine(baseParent){}

    bool   Execute(Sequence *parent ,bool FlagConnectedMode) override;
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    QString    GetName(void)	override{ return(QString("CXor"));  }
    unsigned short  GetOpID(void) override{  return(OpID_CXor);   }
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    int     GetOpCount(void) override{   return(2);  }
    SeqLine *MakeDup(LocalReg *DestLReg) override;
};

/*----------------------------------------------------------------------------*/
//  1.日本語名
//
//  2.概要
//
//  3.機能説明
//
//  4.備考
//
/*----------------------------------------------------------------------------*/
class   EqualSeq : public SeqLine
{
  public:
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    EqualSeq(SeqControl *baseParent):SeqLine(baseParent){}

    bool   Execute(Sequence *parent ,bool FlagConnectedMode) override;
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    QString    GetName(void)	override{ return(QString("Equal"));  }
    unsigned short  GetOpID(void) override{  return(OpID_Equal);   }
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    int     GetOpCount(void) override{   return(2);  }
    SeqLine *MakeDup(LocalReg *DestLReg) override;
};

/*----------------------------------------------------------------------------*/
//  1.日本語名
//
//  2.概要
//
//  3.機能説明
//
//  4.備考
//
/*----------------------------------------------------------------------------*/
class   ZoneSeq : public SeqLine
{
  public:
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    ZoneSeq(SeqControl *baseParent):SeqLine(baseParent){}

    bool   Execute(Sequence *parent ,bool FlagConnectedMode) override;
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    QString    GetName(void)	override{ return(QString("Zone"));  }
    unsigned short  GetOpID(void) override{  return(OpID_Zone);   }
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    int     GetOpCount(void) override{   return(3);  }
    SeqLine *MakeDup(LocalReg *DestLReg) override;
};

/*----------------------------------------------------------------------------*/
//  1.日本語名
//
//  2.概要
//
//  3.機能説明
//
//  4.備考
//
/*----------------------------------------------------------------------------*/
class   PartEqSeq : public SeqLine
{
  public:
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    PartEqSeq(SeqControl *baseParent):SeqLine(baseParent){}

    bool   Execute(Sequence *parent ,bool FlagConnectedMode) override;
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    QString    GetName(void)	override{ return(QString("PartEq"));  }
    unsigned short  GetOpID(void) override{  return(OpID_PartEq);   }
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    int     GetOpCount(void) override{   return(2);  }
    SeqLine *MakeDup(LocalReg *DestLReg) override;
};

/*----------------------------------------------------------------------------*/
//  1.日本語名
//
//  2.概要
//
//  3.機能説明
//
//  4.備考
//
/*----------------------------------------------------------------------------*/
class   UnequalSeq : public SeqLine
{
  public:
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    UnequalSeq(SeqControl *baseParent):SeqLine(baseParent){}

    bool   Execute(Sequence *parent ,bool FlagConnectedMode) override;
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    QString    GetName(void)	override{ return(QString("Unequal"));  }
    unsigned short  GetOpID(void) override{  return(OpID_Unequal);   }
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    int     GetOpCount(void) override{   return(2);  }
    SeqLine *MakeDup(LocalReg *DestLReg) override;
};

/*----------------------------------------------------------------------------*/
//  1.日本語名
//
//  2.概要
//
//  3.機能説明
//
//  4.備考
//
/*----------------------------------------------------------------------------*/
class   GreaterSeq : public SeqLine
{
  public:
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    GreaterSeq(SeqControl *baseParent):SeqLine(baseParent){}

    bool   Execute(Sequence *parent ,bool FlagConnectedMode) override;
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    QString    GetName(void)	override{ return(QString("Greater"));  }
    unsigned short  GetOpID(void) override{  return(OpID_Greater);   }
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    int     GetOpCount(void) override{   return(2);  }
    SeqLine *MakeDup(LocalReg *DestLReg) override;
};

/*----------------------------------------------------------------------------*/
//  1.日本語名
//
//  2.概要
//
//  3.機能説明
//
//  4.備考
//
/*----------------------------------------------------------------------------*/
class   LargeSeq : public SeqLine
{
  public:
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    LargeSeq(SeqControl *baseParent):SeqLine(baseParent){}

    bool   Execute(Sequence *parent ,bool FlagConnectedMode) override;
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    QString    GetName(void)	override{ return(QString("Large"));  }
    unsigned short  GetOpID(void) override{  return(OpID_Large);   }
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    int     GetOpCount(void) override{   return(2);  }
    SeqLine *MakeDup(LocalReg *DestLReg) override;
};

/*----------------------------------------------------------------------------*/
//  1.日本語名
//
//  2.概要
//
//  3.機能説明
//
//  4.備考
//
/*----------------------------------------------------------------------------*/
class   LessSeq : public SeqLine
{
  public:
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    LessSeq(SeqControl *baseParent):SeqLine(baseParent){}

    bool   Execute(Sequence *parent ,bool FlagConnectedMode) override;
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    QString    GetName(void)	override{ return(QString("Less"));  }
    unsigned short  GetOpID(void) override{  return(OpID_Less);   }
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    int     GetOpCount(void) override{   return(2);  }
    SeqLine *MakeDup(LocalReg *DestLReg) override;
};

/*----------------------------------------------------------------------------*/
//  1.日本語名
//
//  2.概要
//
//  3.機能説明
//
//  4.備考
//
/*----------------------------------------------------------------------------*/
class   SmallSeq : public SeqLine
{
  public:
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    SmallSeq(SeqControl *baseParent):SeqLine(baseParent){}

    bool   Execute(Sequence *parent ,bool FlagConnectedMode) override;
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    QString    GetName(void)	override{ return(QString("Small"));  }
    unsigned short  GetOpID(void) override{  return(OpID_Small);   }
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    int     GetOpCount(void) override{   return(2);  }
    SeqLine *MakeDup(LocalReg *DestLReg) override;
};

/*----------------------------------------------------------------------------*/
//  1.日本語名
//
//  2.概要
//
//  3.機能説明
//
//  4.備考
//
/*----------------------------------------------------------------------------*/
class   MOutSeq : public SeqLine
{
  public:
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    MOutSeq(SeqControl *baseParent):SeqLine(baseParent){}

    bool   Execute(Sequence *parent ,bool FlagConnectedMode) override;
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    QString    GetName(void)	override{ return(QString("MOut"));  }
    unsigned short  GetOpID(void) override{  return(OpID_MOut);   }
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    int     GetOpCount(void) override{   return(1);  }
    SeqLine *MakeDup(LocalReg *DestLReg) override;
};

class   MYesNoSeq : public SeqLine
{
  public:
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    MYesNoSeq(SeqControl *baseParent):SeqLine(baseParent){}

    bool   Execute(Sequence *parent ,bool FlagConnectedMode) override;
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    QString    GetName(void)	override{ return(QString("MYesNo"));  }
    unsigned short  GetOpID(void) override{  return(OpID_MYesNo);   }
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    int     GetOpCount(void) override{   return(1);  }
    SeqLine *MakeDup(LocalReg *DestLReg) override;
};

/*----------------------------------------------------------------------------*/
//  1.日本語名
//
//  2.概要
//
//  3.機能説明
//
//  4.備考
//
/*----------------------------------------------------------------------------*/
class   MultSeq : public SeqLine
{
  public:
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    MultSeq(SeqControl *baseParent):SeqLine(baseParent){}

    bool   Execute(Sequence *parent ,bool FlagConnectedMode) override;
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    QString    GetName(void)	override{ return(QString("Mult"));  }
    unsigned short  GetOpID(void) override{  return(OpID_Mult);   }
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    int     GetOpCount(void) override{   return(2);  }
    SeqLine *MakeDup(LocalReg *DestLReg) override;
};

/*----------------------------------------------------------------------------*/
//  1.日本語名
//
//  2.概要
//
//  3.機能説明
//
//  4.備考
//
/*----------------------------------------------------------------------------*/
class   DivSeq : public SeqLine
{
  public:
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    DivSeq(SeqControl *baseParent):SeqLine(baseParent){}

    bool   Execute(Sequence *parent ,bool FlagConnectedMode) override;
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    QString    GetName(void)	override{ return(QString("Div"));  }
    unsigned short  GetOpID(void) override{  return(OpID_Div);   }
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    int     GetOpCount(void) override{   return(2);  }
    SeqLine *MakeDup(LocalReg *DestLReg) override;
};

/*----------------------------------------------------------------------------*/
//  1.日本語名
//
//  2.概要
//
//  3.機能説明
//
//  4.備考
//
/*----------------------------------------------------------------------------*/
class   ModSeq : public SeqLine
{
  public:
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    ModSeq(SeqControl *baseParent):SeqLine(baseParent){}

    bool   Execute(Sequence *parent ,bool FlagConnectedMode) override;
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    QString    GetName(void)	override{ return(QString("Mod"));  }
    unsigned short  GetOpID(void) override{  return(OpID_Mod);   }
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    int     GetOpCount(void) override{   return(2);  }
    SeqLine *MakeDup(LocalReg *DestLReg) override;
};

/*----------------------------------------------------------------------------*/
//  1.日本語名
//
//  2.概要
//
//  3.機能説明
//
//  4.備考
//
/*----------------------------------------------------------------------------*/
class   StrMoveSeq : public SeqLine
{
  public:
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    StrMoveSeq(SeqControl *baseParent):SeqLine(baseParent){}

    bool   Execute(Sequence *parent ,bool FlagConnectedMode) override;
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    QString    GetName(void)	override{ return(QString("StrMove"));  }
    unsigned short  GetOpID(void) override{  return(OpID_StrMove);   }
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    int     GetOpCount(void) override{   return(2);  }
    SeqLine *MakeDup(LocalReg *DestLReg) override;
};

/*----------------------------------------------------------------------------*/
//  1.日本語名
//
//  2.概要
//
//  3.機能説明
//
//  4.備考
//
/*----------------------------------------------------------------------------*/
class   LowerSeq : public SeqLine
{
  public:
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    LowerSeq(SeqControl *baseParent):SeqLine(baseParent){}

    bool   Execute(Sequence *parent ,bool FlagConnectedMode) override;
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    QString    GetName(void)	override{ return(QString("Lower"));  }
    unsigned short  GetOpID(void) override{  return(OpID_Lower);   }
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    int     GetOpCount(void) override{   return(2);  }
    SeqLine *MakeDup(LocalReg *DestLReg) override;
};

/*----------------------------------------------------------------------------*/
//  1.日本語名
//
//  2.概要
//
//  3.機能説明
//
//  4.備考
//
/*----------------------------------------------------------------------------*/
class   UpperSeq : public SeqLine
{
  public:
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    UpperSeq(SeqControl *baseParent):SeqLine(baseParent){}

    bool   Execute(Sequence *parent ,bool FlagConnectedMode) override;
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    QString    GetName(void)	override{ return(QString("Upper"));  }
    unsigned short  GetOpID(void) override{  return(OpID_Upper);   }
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    int     GetOpCount(void) override{   return(2);  }
    SeqLine *MakeDup(LocalReg *DestLReg) override;
};

/*----------------------------------------------------------------------------*/
//  1.日本語名
//
//  2.概要
//
//  3.機能説明
//
//  4.備考
//
/*----------------------------------------------------------------------------*/
class   StateSeq : public SeqLine
{
  public:
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    StateSeq(SeqControl *baseParent):SeqLine(baseParent){}

    bool   Execute(Sequence *parent ,bool FlagConnectedMode) override;
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    QString    GetName(void)	override{ return(QString("State"));  }
    unsigned short  GetOpID(void) override{  return(OpID_State);   }
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    int     GetOpCount(void) override{   return(2);  }
    SeqLine *MakeDup(LocalReg *DestLReg) override;
};

/*----------------------------------------------------------------------------*/
//  1.日本語名
//
//  2.概要
//
//  3.機能説明
//
//  4.備考
//
/*----------------------------------------------------------------------------*/
class   ReturnSeq : public SeqLine
{
  public:
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    ReturnSeq(SeqControl *baseParent):SeqLine(baseParent){}

    bool   Execute(Sequence *parent ,bool FlagConnectedMode) override;
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    QString    GetName(void)	override{ return(QString("Return"));  }
    unsigned short  GetOpID(void) override{  return(OpID_Return);   }
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    int     GetOpCount(void) override{   return(0);  }
    SeqLine *MakeDup(LocalReg *DestLReg) override;
};

class   TWSetSeq : public SeqLine
{
  public:
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    TWSetSeq(SeqControl *baseParent):SeqLine(baseParent){}

    bool   Execute(Sequence *parent ,bool FlagConnectedMode) override;
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    QString    GetName(void)	override{ return(QString("TWSet"));  }
    unsigned short  GetOpID(void) override{  return(OpID_TWSet);   }
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    int     GetOpCount(void) override{   return(1);  }
    SeqLine *MakeDup(LocalReg *DestLReg) override;
};

class   TWaitLessSeq : public SeqLine
{
  public:
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    TWaitLessSeq(SeqControl *baseParent):SeqLine(baseParent){}

    bool   Execute(Sequence *parent ,bool FlagConnectedMode) override;
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    QString    GetName(void)	override{ return(QString("TWaitLess"));  }
    unsigned short  GetOpID(void) override{  return(OpID_TWaitLess);   }
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    int     GetOpCount(void) override{   return(3);  }
    SeqLine *MakeDup(LocalReg *DestLReg) override;
};

class   TWaitGreaterSeq : public SeqLine
{
  public:
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    TWaitGreaterSeq(SeqControl *baseParent):SeqLine(baseParent){}

    bool   Execute(Sequence *parent ,bool FlagConnectedMode) override;
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    QString    GetName(void)	override{ return(QString("TWaitGreater"));  }
    unsigned short  GetOpID(void) override{  return(OpID_TWaitGreater);   }
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    int     GetOpCount(void) override{   return(3);  }
    SeqLine *MakeDup(LocalReg *DestLReg) override;
};

class   FSetSeq : public SeqLine
{
  public:
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    FSetSeq(SeqControl *baseParent):SeqLine(baseParent){}

    bool   Execute(Sequence *parent ,bool FlagConnectedMode) override;
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    QString    GetName(void)	override{ return(QString("FSet"));  }
    unsigned short  GetOpID(void) override{  return(OpID_FSet);   }
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    int     GetOpCount(void) override{   return(1);  }
    SeqLine *MakeDup(LocalReg *DestLReg) override;
};

class   FResetSeq : public SeqLine
{
  public:
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    FResetSeq(SeqControl *baseParent):SeqLine(baseParent){}

    bool   Execute(Sequence *parent ,bool FlagConnectedMode) override;
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    QString    GetName(void)	override{ return(QString("FReset"));  }
    unsigned short  GetOpID(void) override{  return(OpID_FReset);   }
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    int     GetOpCount(void) override{   return(1);  }
    SeqLine *MakeDup(LocalReg *DestLReg) override;
};

class   RxTimeoutSeq : public SeqLine
{
  public:
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    RxTimeoutSeq(SeqControl *baseParent):SeqLine(baseParent){}

    bool   Execute(Sequence *parent ,bool FlagConnectedMode) override;
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    QString    GetName(void)	override{ return(QString("RxTimeout"));  }
    unsigned short  GetOpID(void) override{  return(OpID_RxTimeout);   }
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    int     GetOpCount(void) override{   return(3);  }
    SeqLine *MakeDup(LocalReg *DestLReg) override;
};

/*----------------------------------------------------------------------------*/
//  1.日本語名
//
//  2.概要
//
//  3.機能説明
//
//  4.備考
//
/*----------------------------------------------------------------------------*/
class   StrLenSeq : public SeqLine
{
  public:
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    StrLenSeq(SeqControl *baseParent):SeqLine(baseParent){}

    bool   Execute(Sequence *parent ,bool FlagConnectedMode) override;
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    QString    GetName(void)	override{ return(QString("StrLen"));  }
    unsigned short  GetOpID(void) override{  return(OpID_StrLen);   }
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    int     GetOpCount(void) override{   return(2);  }
    SeqLine *MakeDup(LocalReg *DestLReg) override;
};

/*----------------------------------------------------------------------------*/
//  1.日本語名
//
//  2.概要
//
//  3.機能説明
//
//  4.備考
//
/*----------------------------------------------------------------------------*/
class   AddFileSeq : public SeqLine
{
  public:
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    AddFileSeq(SeqControl *baseParent):SeqLine(baseParent){}

    bool   Execute(Sequence *parent ,bool FlagConnectedMode) override;
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    QString    GetName(void)	override{ return(QString("AddFile"));  }
    unsigned short  GetOpID(void) override{  return(OpID_AddFile);   }
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    int     GetOpCount(void) override{   return(2);  }
    SeqLine *MakeDup(LocalReg *DestLReg) override;
};

/*----------------------------------------------------------------------------*/
//  1.日本語名
//
//  2.概要
//
//  3.機能説明
//
//  4.備考
//
/*----------------------------------------------------------------------------*/
class   OpenLFileSeq : public SeqLine
{
  public:
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    OpenLFileSeq(SeqControl *baseParent):SeqLine(baseParent){}

    bool   Execute(Sequence *parent ,bool FlagConnectedMode) override;
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    QString    GetName(void)	override{ return(QString("OpenLFile"));  }
    unsigned short  GetOpID(void) override{  return(OpID_OpenLFile);   }
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    int     GetOpCount(void) override{   return(2);  }
    SeqLine *MakeDup(LocalReg *DestLReg) override;
};

/*----------------------------------------------------------------------------*/
//  1.日本語名
//
//  2.概要
//
//  3.機能説明
//
//  4.備考
//
/*----------------------------------------------------------------------------*/
class   LoadFileSeq : public SeqLine
{
  public:
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    LoadFileSeq(SeqControl *baseParent):SeqLine(baseParent){}

    bool   Execute(Sequence *parent ,bool FlagConnectedMode) override;
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    QString    GetName(void)	override{ return(QString("LoadFile"));  }
    unsigned short  GetOpID(void) override{  return(OpID_LoadFile);   }
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    int     GetOpCount(void) override{   return(2);  }
    SeqLine *MakeDup(LocalReg *DestLReg) override;
};

/*----------------------------------------------------------------------------*/
//  1.日本語名
//
//  2.概要
//
//  3.機能説明
//
//  4.備考
//
/*----------------------------------------------------------------------------*/
class   CloseFileSeq : public SeqLine
{
  public:
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    CloseFileSeq(SeqControl *baseParent):SeqLine(baseParent){}

    bool   Execute(Sequence *parent ,bool FlagConnectedMode) override;
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    QString    GetName(void)	override{ return(QString("CloseFile"));  }
    unsigned short  GetOpID(void) override{  return(OpID_CloseFile);   }
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    int     GetOpCount(void) override{   return(1);  }
    SeqLine *MakeDup(LocalReg *DestLReg) override;
};

/*----------------------------------------------------------------------------*/
//  1.日本語名
//
//  2.概要
//
//  3.機能説明
//
//  4.備考
//
/*----------------------------------------------------------------------------*/
class   DeleteFileSeq : public SeqLine
{
  public:
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    DeleteFileSeq(SeqControl *baseParent):SeqLine(baseParent){}

    bool   Execute(Sequence *parent ,bool FlagConnectedMode) override;
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    QString    GetName(void)	override{ return(QString("DeleteFile"));  }
    unsigned short  GetOpID(void) override{  return(OpID_DeleteFile);   }
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    int     GetOpCount(void) override{   return(1);  }
    SeqLine *MakeDup(LocalReg *DestLReg) override;
};

/*----------------------------------------------------------------------------*/
//  1.日本語名
//
//  2.概要
//
//  3.機能説明
//
//  4.備考
//
/*----------------------------------------------------------------------------*/
class   MessageColorSeq : public SeqLine
{
  public:
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    MessageColorSeq(SeqControl *baseParent):SeqLine(baseParent){}

    bool   Execute(Sequence *parent ,bool FlagConnectedMode) override;
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    QString    GetName(void)	override{ return(QString("MessageColor"));  }
    unsigned short  GetOpID(void) override{  return(OpID_MessageColor);   }
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    int     GetOpCount(void) override{   return(1);  }
    SeqLine *MakeDup(LocalReg *DestLReg) override;
};

/*----------------------------------------------------------------------------*/
//  1.日本語名
//
//  2.概要
//
//  3.機能説明
//
//  4.備考
//
/*----------------------------------------------------------------------------*/
class   BPrintSeq : public SeqLine
{
  public:
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    BPrintSeq(SeqControl *baseParent):SeqLine(baseParent){}

    bool   Execute(Sequence *parent ,bool FlagConnectedMode) override;
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    QString    GetName(void)	override{ return(QString("BPrint"));  }
    unsigned short  GetOpID(void) override{  return(OpID_BPrint);   }
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    int     GetOpCount(void) override{   return(2);  }
    SeqLine *MakeDup(LocalReg *DestLReg) override;
};

/*----------------------------------------------------------------------------*/
//  1.日本語名
//
//  2.概要
//
//  3.機能説明
//
//  4.備考
//
/*----------------------------------------------------------------------------*/
class   BScanSeq : public SeqLine
{
  public:
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    BScanSeq(SeqControl *baseParent):SeqLine(baseParent){}

    bool   Execute(Sequence *parent ,bool FlagConnectedMode) override;
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    QString    GetName(void)	override{ return(QString("BScan"));  }
    unsigned short  GetOpID(void) override{  return(OpID_BScan);   }
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    int     GetOpCount(void) override{   return(2);  }
    SeqLine *MakeDup(LocalReg *DestLReg) override;
};

class   SyncGetSeq : public SeqLine
{
  public:
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    SyncGetSeq(SeqControl *baseParent):SeqLine(baseParent){}

    bool   Execute(Sequence *parent ,bool FlagConnectedMode) override;
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    QString    GetName(void)	override{ return(QString("SyncGet"));  }
    unsigned short  GetOpID(void) override{  return(OpID_SyncGet);   }
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    int     GetOpCount(void) override{   return(2);  }
    SeqLine *MakeDup(LocalReg *DestLReg) override;
};

class   DLLCmdSeq : public SeqLine
{
  public:
    int     OpeNumb;
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    DLLCmdSeq(SeqControl *baseParent):SeqLine(baseParent){    OpeNumb=1;  }

    bool   Execute(Sequence *parent ,bool FlagConnectedMode) override;
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    QString    GetName(void)	override{ return(QString("DLLCmd"));  }
    unsigned short  GetOpID(void) override{  return(OpID_DLLCmd);   }
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    int     GetOpCount(void) override{   return(OpeNumb);  }
    SeqLine *MakeDup(LocalReg *DestLReg) override;
};

class   ShowOnSeq : public SeqLine
{
  public:
    int PageNumber;
    int RegNumber;
    int OpeNumb;

	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    ShowOnSeq(SeqControl *baseParent):SeqLine(baseParent){    OpeNumb=1;  PageNumber=0;   RegNumber=-1;  }

    bool   Execute(Sequence *parent ,bool FlagConnectedMode) override;
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    QString    GetName(void)	override{ return(QString("ShowOn"));  }
    unsigned short  GetOpID(void) override{  return(OpID_ShowOn);   }
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    int     GetOpCount(void) override{   return(OpeNumb);  }
    SeqLine *MakeDup(LocalReg *DestLReg) override;
};

class   ShowOffSeq : public SeqLine
{
  public:
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    ShowOffSeq(SeqControl *baseParent):SeqLine(baseParent){}

    bool   Execute(Sequence *parent ,bool FlagConnectedMode) override;
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    QString    GetName(void)	override{ return(QString("ShowOff"));  }
    unsigned short  GetOpID(void) override{  return(OpID_ShowOff);   }
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    int     GetOpCount(void) override{   return(0);  }
    SeqLine *MakeDup(LocalReg *DestLReg) override;
};

/*----------------------------------------------------------------------------*/
//  1.日本語名
//
//  2.概要
//
//  3.機能説明
//
//  4.備考
//
/*----------------------------------------------------------------------------*/
class   NopSeq : public SeqLine
{
  public:
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    NopSeq(SeqControl *baseParent):SeqLine(baseParent){}

    bool   Execute(Sequence *parent ,bool FlagConnectedMode) override;
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    QString    GetName(void)	override{ return(QString("Nop"));  }
    unsigned short  GetOpID(void) override{  return(OpID_Nop);   }
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    int     GetOpCount(void) override{   return(0);  }
    SeqLine *MakeDup(LocalReg *DestLReg) override;
};

class   MInputSeq : public SeqLine
{
  public:
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    MInputSeq(SeqControl *baseParent):SeqLine(baseParent){}

    bool   Execute(Sequence *parent ,bool FlagConnectedMode) override;
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    QString    GetName(void)	override{ return(QString("MInput"));  }
    unsigned short  GetOpID(void) override{  return(OpID_MInput);   }
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    int     GetOpCount(void) override{   return(2);  }
    SeqLine *MakeDup(LocalReg *DestLReg) override;
};

class   FloatNumSeq : public SeqLine
{
  public:
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    FloatNumSeq(SeqControl *baseParent):SeqLine(baseParent){}

    bool   Execute(Sequence *parent ,bool FlagConnectedMode) override;
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    QString    GetName(void)	override{ return(QString("FloatNum"));  }
    unsigned short  GetOpID(void) override{  return(OpID_FloatNum);   }
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    int     GetOpCount(void) override{   return(2);  }
    SeqLine *MakeDup(LocalReg *DestLReg) override;
};

class   CallSeq : public SeqLine
{
  public:
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    CallSeq(SeqControl *baseParent):SeqLine(baseParent){}

    bool   Execute(Sequence *parent ,bool FlagConnectedMode) override;
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    QString    GetName(void)	override{ return(QString("Call"));  }
    unsigned short  GetOpID(void) override{  return(OpID_Call);   }
	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/
    int     GetOpCount(void) override{   return(1);  }
    SeqLine *MakeDup(LocalReg *DestLReg) override;
};


class   OperandPackBase
{
  public:
    OperandPackBase(void){}

    virtual Operand *GetItemFromID(int id)=0;
    virtual int     GetNumber(void)=0;
};

class   IOOperandPack : public NPListPack<IOOperand> ,public OperandPackBase
{
  public:
    IOOperandPack(void){}

    Operand *GetItemFromID(int id){ return(NULL);   }
    int     GetNumber(void);
};

class   CommOperandPack : public NPListPack<CommOperand> ,public OperandPackBase
{
  public:
    CommOperandPack(void){}

    Operand *GetItemFromID(int id){ return(NULL);   }
    int     GetNumber(void);
};

class   BitOperandPack : public NPListPack<BitOperand> ,public OperandPackBase
{
  public:
    BitOperandPack(void){}

    Operand *GetItemFromID(int id);
    int     GetNumber(void);
};

class   WordOperandPack : public NPListPack<WordOperand> ,public OperandPackBase
{
  public:
    WordOperandPack(void){}

    Operand *GetItemFromID(int id);
    int     GetNumber(void);
};

class   FloatOperandPack : public NPListPack<FloatOperand> ,public OperandPackBase
{
  public:
    FloatOperandPack(void){}

    Operand *GetItemFromID(int id);
    int     GetNumber(void);
};

class   StringOperandPack : public NPListPack<StringOperand> ,public OperandPackBase
{
  public:
    StringOperandPack(void){}

    Operand *GetItemFromID(int id);
    int     GetNumber(void);
};

class   LocalBitOperandPack : public NPListPack<LocalBitOperand> ,public OperandPackBase
{
  public:
    LocalBitOperandPack(void){}

    Operand *GetItemFromID(int id);
    int     GetNumber(void);
};

class   LocalWordOperandPack : public NPListPack<LocalWordOperand> ,public OperandPackBase
{
  public:
    LocalWordOperandPack(void){}

    Operand *GetItemFromID(int id);
    int     GetNumber(void);
};

class   LocalFloatOperandPack : public NPListPack<LocalFloatOperand> ,public OperandPackBase
{
  public:
    LocalFloatOperandPack(void){}

    Operand *GetItemFromID(int id);
    int     GetNumber(void);
};

class   LocalStringOperandPack : public NPListPack<LocalStringOperand> ,public OperandPackBase
{
  public:
    LocalStringOperandPack(void){}

    Operand *GetItemFromID(int id);
    int     GetNumber(void);
};


class   SpecialOperandPack : public NPListPack<SpecialOperand> ,public OperandPackBase
{
  public:
    SpecialOperandPack(void){}

    Operand *GetItemFromID(int id);
    int     GetNumber(void);
};

class   NumberOperandPack : public NPListPack<NumberOperand> ,public OperandPackBase
{
  public:
    NumberOperandPack(void){}

    Operand *GetItemFromID(int id){ return(NULL);   }
    int     GetNumber(void);
};

class   CharOperandPack : public NPListPack<CharOperand> ,public OperandPackBase
{
  public:
    CharOperandPack(void){}

    Operand *GetItemFromID(int id){ return(NULL);   }
    int     GetNumber(void);
};

class   GroupOperandPack : public NPListPack<GroupOperand> ,public OperandPackBase
{
  public:
    GroupOperandPack(void){}

    Operand *GetItemFromID(int id){ return(NULL);   }
    int     GetNumber(void);
};

class   SpecialBitOperandPack : public NPListPack<SpecialBitOperand> ,public OperandPackBase
{
  public:
    SpecialBitOperandPack(void){}

    Operand *GetItemFromID(int id);
    int     GetNumber(void);
};

class   SpecialStringOperandPack : public NPListPack<SpecialStringOperand> ,public OperandPackBase
{
  public:
    SpecialStringOperandPack(void){}

    Operand *GetItemFromID(int id);
    int     GetNumber(void);
};

class   SpecialFloatOperandPack : public NPListPack<SpecialFloatOperand> ,public OperandPackBase
{
  public:
    SpecialFloatOperandPack(void){}

    Operand *GetItemFromID(int id);
    int     GetNumber(void);
};

/*↓D-20051026------------------------------------------------------------------
class   LanvarOperandPack : public NPListPack<LanvarOperand> ,public OperandPackBase
{
  public:
    LanvarOperandPack(void){}

    Operand *GetItemFromID(int id){ return(NULL);   }
    int     GetNumber(void);
};
↑D-20051026------------------------------------------------------------------*/

class   FifoOperandPack : public NPListPack<FifoOperand> ,public OperandPackBase
{
  public:
    FifoOperandPack(void){}

    Operand *GetItemFromID(int id){ return(NULL);   }
    int     GetNumber(void);
};

class   DLLVarOperandPack : public NPListPack<DLLVarOperand> ,public OperandPackBase
{
  public:
    DLLVarOperandPack(void){}

    Operand *GetItemFromID(int id){ return(NULL);   }
    int     GetNumber(void);
};



class   FlagExecuted
{
  public:
    bool    *FlagDim;
    int     AllocNumb;
    int     NowWTop;
    int     NeedWCount;

    FlagExecuted(void);
    ~FlagExecuted(void);

    void    Alloc(SequenceStock *s);
    void    AddFlag(bool flag);
    void    SetFlag(bool flag);
    bool    *GetTop(void);
    int     GetEffectiveLen(void);

    FlagExecuted    &operator=(FlagExecuted &src);
    bool      GetLatestFlag(void);

};


/*----------------------------------------------------------------------------*/
//  1.日本語名
//
//  2.概要
//
//  3.機能説明
//
//  4.備考
//
/*----------------------------------------------------------------------------*/

class   LocalReg
{
	SeqControl	*BaseParent;
  public:

    LocalBitOperandPack         LocalBitOpe;
    LocalWordOperandPack        LocalWordOpe;
    LocalFloatOperandPack       LocalFloatOpe;
    LocalStringOperandPack      LocalStringOpe;

    LocalReg(SeqControl	*baseParent);
    Operand *SearchReg(QString regname);
};


class   SequenceStock : public NPList<SequenceStock>
{
  friend    class   Sequence;

  public:
    enum    SType{
        _Main       =1
        ,_Watch     =2
        ,_Condition =3
        ,_Immidiate =4
        ,_Event     =5
        ,_Subroutine=6
        ,_Begin     =7
        ,_End       =8
        ,_Glance    =9
        };

  private:
	SeqControl	*BaseParent;
    QString		Name;
    SeqLine		*Cond;
    SType		stype;
    int			SCode;          //シーケンス識別番号

    SeqLine		**SLine;         //読み込んだプログラムラインが格納される
    LocalReg    LoadedLocalReg;
    int			SLineNumb;
    int			*SLineIndex;
    int			MaxLineNumb;
    QString		CommandName;    //Event用
    int			GlanceTime;

  public:
    SequenceStock(SeqControl *baseParent);
    ~SequenceStock(void);

    volatile    bool    Load(char *fp ,QFile &file);
    volatile    void    Clear(void);
    void        SetSCode(int scode){    SCode=scode;    }
    int     GetSLineNumb(void){     return(SLineNumb);  }
    SeqLine *GetSLine(int n){   return(SLine[n]);   }
    QString    &GetName(void){     return(Name);   }
    SType   GetSType(void){     return(stype);  }
    bool    SaveBinHeader(FILE *file);
    bool    LoadBinHeader(FILE *file);
    void    SetName(QString &name);
	SeqControl	*GetSeqControl(void){	return BaseParent;	}
  private:
    char    *LoadOpe(SequenceStock *seq ,char *fp ,Operand **ope);
  public:
    char    *LoadInt(char *fp ,Operand **ope);
    char    *LoadString(char *fp ,Operand **ope);
  private:
    char    *FpToInt(char *fp ,int &N);
    char    *FpToFloat(char *fp ,double &N);
    char    *FpToBinary(char *fp ,double &N);
    char    *FpToHex(char *fp ,double &N);


  public:
    char    *LoadFlag(FlagOrNode *eFlag,char *fp);

    BYTE    ToXDigit(char d);
    BYTE    ToXDigitOrError(char d);
};


class   Sequence : public NPList<Sequence>
{
	SeqControl	*BaseParent;
    SequenceStock   *SPoint;

    FlagExecuted    eFlag;
    //bool        Flag;
    //bool        LastFlag;
    int         NowLine;
    SeqLine     **SLine;     //実行時のラインが格納される

    DWORD   WaitStartTime;
    bool    WaitMode;
	QMutex	MutexSequence;

    struct  __TimingDataHeader  TimingDataHeader;
    BYTE                        TimingDataType; //1:int  2:AnsiString  3:BYTE
    int                         TimingDataI;
    double                      TimingDataF;
    QString						TimingDataS;
    BYTE                        *TimingDataB;
    int                         TimingDataLen;
    int                         TimingDataBAllocedSize;
    bool                        TimingWriteMode;

    volatile    bool    StopExecute;
    volatile    int     BreakPoint[MaxBreakPoint];
    volatile    int     BreakPointNumb;
    volatile    bool    GoMode;
    volatile    bool    StepBreak;
    volatile    bool    StepBreakMode;
    volatile    bool    DebugMode;
    volatile    bool    IsDebugStopped;

  public:
    bool        NowOnSubroutine;
    bool        ShouldDeleteSubroutine;
    Sequence    *SubroutineCall;
    Sequence    *SubroutineParent;
    LocalReg            LocalRegs;
    bool        LastExecuted;   //「+」条件のための、前回実行したかどうか

    Sequence(SeqControl	*BaseParent);
    ~Sequence(void);

    volatile    bool   StepExecute(void);
    volatile    bool    Start(void);
    volatile    bool    IsEnd(void);
    volatile    void    Clear(void);
	SeqControl	*GetSeqControl(void){	return BaseParent;	}

    void    ClearBreak(void);
    void    SetDebugMode(bool f){   DebugMode=f;  }
    //bool    GetFlag(void){  return(Flag);   }
    bool      GetLatestFlag(void){     return(eFlag.GetLatestFlag());  }
    void   SetFlag(bool FlagConnectedMode ,bool Flag);

    int     GetSLineNumb(void){     return(SPoint->SLineNumb);  }
    int     GetMaxLineNumb(void){   return(SPoint->MaxLineNumb);        }
    int     GetSLineIndex(int n);
    SeqLine *GetSLine(int n);
    int     GetNowLine(void){   return(NowLine);    }
    void    SetNowLine(int n){  NowLine=n;          }
    void    Add1NowLine(void){  NowLine=GetNowLine()+1;         }
    int     GetBreakPointNumb(void){    return(BreakPointNumb); }
    int     GetBreakPoint(int n){       return(BreakPoint[n]);  }
    QString &GetSeqName(void){          return(SPoint->Name);   }
    void    RemoveBreakPoint(int n);
    void    AddBreakPoint(int n);
    void    GoFromStep(void);
    void    StepIt(void);
    void    StopFromGo(void);
    bool    IsModeDebugStopped(void){   return(IsDebugStopped); }
    SequenceStock::SType    GetSType(void){ return(SPoint->stype);  }
    QString  GetCommandName(void){  return(SPoint->CommandName);    }
    int     GetSCode(void){     return(SPoint->SCode);  }

    bool    GetWaitMode(void)           {   return(WaitMode);       }
    void    SetWaitMode(bool f)         {   WaitMode=f;             }
    void    SetWaitStartTime(DWORD tmm) {   WaitStartTime=tmm;      }
    DWORD   GetWaitStartTime(void)      {   return(WaitStartTime);  }

    bool      WriteHPush(int         d     ,OpeChangeListBase::ForceChange ,Operand *);
    bool      WriteHPush(double      d     ,OpeChangeListBase::ForceChange ,Operand *);
    bool      WriteHPush(QString &d     ,OpeChangeListBase::ForceChange ,Operand *);
    bool      WriteHPush(BYTE *d,int len   ,OpeChangeListBase::ForceChange ,Operand *);
    bool      WriteExecute(QDataStream *f);

    Operand *SearchReg(QString regname);

    void    LoadFromStock(SequenceStock *base);
    bool    IsAliveExecuting(void);
    int     GetGlanceTime(void){    return(SPoint->GlanceTime); }

	void	Lock(void)		{		MutexSequence.lock();	}
	void	Unlock(void)	{		MutexSequence.unlock();	}

};

class   TmpNameValue : public NPList<TmpNameValue>
{
  public:
    QString  Name;
    QString  sValue;
    int         iValue;
    QStringList *lValue;

    TmpNameValue(void){     lValue=NULL;	iValue=0;   }
	TmpNameValue(const QString &name , const QString &value){	Name=name;	sValue=value;	lValue=NULL;	iValue=0;	}
	TmpNameValue(const QString &name , int value)			{	Name=name;	iValue=value;	lValue=NULL;	}
};

class   TmpSeqList : public NPList<TmpSeqList>
{
  public:
    QString  Name;
    int         NowLine;
    bool        NowFlag;
    FlagExecuted    eFlag;
    int         NowNearestLine;
    int         NowRelativeExeLine;
    QString  NowExeNimo;
    QString  NowExeOp1;
    QString  NowExeOp2;

    TmpSeqList(void);
};


/*----------------------------------------------------------------------------*/
//  1.日本語名
//
//  2.概要
//
//  3.機能説明
//
//  4.備考
//
/*----------------------------------------------------------------------------*/
class   SeqControl : public ServiceForLayers
{
    QChar    DummpBuff[100];
    QString  TimingFileName;
    QDataStream *WriteTimingFile;
    volatile    int ReqHalt;

  public:
    NPListPack<SequenceStock>   SeqStock;
    NPListPack<Sequence>        Seq;
    volatile    int                         SeqNumb;
    QThread		*Parent;
	PIOClass    *PIO;

    IOOperandPack               IOOpe;
    CommOperandPack             CommOpe;
    BitOperandPack              BitOpe;
    WordOperandPack             WordOpe;
    FloatOperandPack            FloatOpe;
    StringOperandPack           StringOpe;
    SpecialOperandPack          SpecialOpe;
    NumberOperandPack           NumberOpe;
    CharOperandPack             CharOpe;
    GroupOperandPack            GroupOpe;
    SpecialBitOperandPack       SpecialBitOpe;
    SpecialStringOperandPack    SpecialStringOpe;
    SpecialFloatOperandPack     SpecialFloatOpe;
///    static  LanvarOperandPack           LanvarOpe;	//D-20051026
    FifoOperandPack             FifoOpe;
    DLLVarOperandPack           DLLVarOpe;

    NPListPack<SeqCommandList>  CmdList;
    QMutex            *DLLSync;
    bool                        DLLDebugMode;
    DWORD                       StartTickCount;
    time_t                      StartTime;
	SeqLocalParam				*LocalParamPointer;	

    QString  SeqTitle;
    QString  TimingPath;

    volatile    bool    ReArrangehistSW;
    volatile    int     StepTime;
    volatile    int     LastOperationTime;  //最後に操作、実行された時刻
    bool            Started;
    volatile    bool    DoHalt;
    volatile    bool    OnHalting;
    volatile    bool    OnStepping;
    volatile    int     GlanceFreq;
    volatile    int     NowGlanceTime;
    QColor  MessageCol;
    time_t  S20Time;

    QString  ErrorLine;

	/*----------------------------------------------------------------------------*/
	//
	//  1.日本語名
	//
	//  2.パラメタ説明
	//
	//  3.概要
	//
	//  4.機能説明
	//
	//  5.戻り値
	//
	//  6.備考
	//
	/*----------------------------------------------------------------------------*/

	OutSequenceYesNo		*OutSequenceYesNoForm;
	OutSequenceShowYesNo	*OutSequenceShowYesNoForm;
	OutSequenceShow			*OutSequenceShowForm;
	OutSequenceShowOK		*OutSequenceShowOKForm;
	OutSequenceMessage		*OutSequenceMessageForm;
	OutSequenceInput		*OutSequenceInputForm;

	SeqControl(LayersBase *base);

    bool    Load(QFile &file);
    bool    ReLoad(QFile &file);
    bool    StepExecute(void);
    void    Start(void);
    void    Stop(void);
    void    HaltThread(void);
    void    RestartThread(void);
    bool    Initial(void);
    bool    NetInitial(void);
    void    Release(void);
    void    CloseLanPort(void);

    void    MessageOut(QString &s);
    bool    MessageYesNoOut(QString &s);
    bool    MessageInputOut(QString &defaultStr ,QString &msg);
    void    MessageShowOn(QString &s ,int PageCode=0 ,int WRegID=-1 ,Sequence *seq=NULL ,int RegKind=KindCodeWord);
    void    MessageShowOff(void);
    void    SetWReg(Sequence *seq ,int regkindcode ,int regid ,int data);
    bool    SaveBinHeader(FILE *file);
    bool    LoadBinHeader(FILE *file);

    void    SetBitMemory   (int id,int data);
    void    SetWordMemory  (int id,int data);
    void    SetStringMemory(int id,QChar *data ,int datalen);
    void    (*StateOut)(int code ,QByteArray &msg);

    void    ReArrangeHist(void);
    Operand *SearchReg(Sequence *seq ,const QString &regname);
    Operand *SearchReg(Sequence *seq ,OperandPackBase *base ,int id);
    Operand *SearchReg(int OpeKindCode ,int OpeId);
    bool    BPrintExecute(Sequence *seq ,QString &src, QString &formatStr);
    bool    BScanExecute(Sequence *seq ,QString &src, QString &formatStr);

///    static  MTWSocket   *ServerSock;	//D-20051026
    int         LanvarPort;
///    static  NPListPack<LanVarSocketList>    LanVarSocket;	//D-20051026
///            void   ServerSockSessionAvailable(
///                              TObject *Sender, WORD Error);	//D-20051026
///    static  NPListPack<LanVarRCmd>      LanVarRData;	//D-20051026
    QMutex                      *LanVarCSection;
    volatile    bool            GetLanverReqMode;
    void    ProcessLanvar(void);

    void    AddSpecialOperand(int id);
    void    AddSpecialBitOperand(int id);
    void    AddSpecialStringOperand(int id);
    void    AddSpecialFloatOperand(int id);

    void    (*XSeqLocalInit)(SeqLocalParam *param ,SeqControl *seqControl);

    void    (*SetDataSpecialOperand)(SeqLocalParam *param ,int ID, int d);
    int     (*GetDataSpecialOperand)(SeqLocalParam *param ,int ID);

    void    (*SetDataSpecialBitOperand)(SeqLocalParam *param ,int ID, bool d);
    bool    (*GetDataSpecialBitOperand)(SeqLocalParam *param ,int ID);

    void    (*SetDataSpecialStringOperand)(SeqLocalParam *param ,int ID, QString d);
    QString (*GetDataSpecialStringOperand)(SeqLocalParam *param ,int ID);

    void    (*SetDataSpecialFloatOperand)(SeqLocalParam *param ,int ID, double d);
    double  (*GetDataSpecialFloatOperand)(SeqLocalParam *param ,int ID);

    QString  GetTimingFileName(void);
    bool        WriteTimingFileTop(void);
    bool        WriteTimingSeq(Sequence *s);

    bool    EventStart(QString &commandname);
    bool    CheckCall(void);

    void    ClearCmdHistList(void);
	ThreadSequence	*GetThread(void);
	QObject	*GetThreadParent(void);
	SeqLocalParam	*GetLocalParamPointer(void)	{	return LocalParamPointer;	}

	PIOClass	*FindPIO(const QString &PIOName);
	PIOClass	*GetFirstPIO(void);
	void	LoopOnIdle(void);
};



#endif
