/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\ThreadSequence.h
** Author : YYYYYYYYYY
****************************************************************************-**/
/*----------------------------------------------------------------------------*/
//
//  概要
//
//  作成者
//
/*----------------------------------------------------------------------------*/

#ifndef ThreadSequenceH
#define ThreadSequenceH
//---------------------------------------------------------------------------
#include <QtGui>
#include <QWidget>
#include <QTime>
#include "XFifoClass.h"
#include "NList.h"
#include "XParamBase.h"
#include "XServiceForLayers.h"
#include "XTypeDef.h"

class	PIOClass;
class   Sequence;
class	SeqControl;
class	SeqLocalParam;
class	CommWindow;
class	QSerialPort;

enum    SeqErrorCode
{
	 _SeqError_NoError		=0
	,_SeqError_DuplicateID	=1
};

class	SeqErrorInfo
{
public:
	SeqErrorCode	Error;
	QString			DupRegExplain;

	SeqErrorInfo(void);
	SeqErrorInfo(const SeqErrorInfo &src);

	SeqErrorInfo &operator=(const SeqErrorInfo &src);
};

//---------------------------------------------------------------

class	CommWindow : public QWidget ,public ServiceForLayers
{
    Q_OBJECT

	int		ComNo;
	bool	Ret;
	QSerialPort *ComPointer;
	char	RxBuff[1024];
	int		RxByte ,RPoint,WPoint;
	QMutex	RxLock;
public:
	CommWindow(int _ComNo ,LayersBase *base ,QWidget *mainW);

	QSerialPort *OpenCommInThread(int Character ,int Parity ,int Stopbit ,int BPS);
	int			CommBytesAvailable(void);
	int			CommReadByte(char *Buff ,int MaxLen);
private slots:
	void	SlotReadyRead();
	void	SlotOpenCommInThread(int Character ,int Parity ,int Stopbit ,int BPS);
signals:
	void	SignalOpenCommInThread(int Character ,int Parity ,int Stopbit ,int BPS);
};


class	NReqIntLeaf : public NPList<NReqIntLeaf>
{
  public:
    int     RegID;
    int     Data;
    Sequence                *ShowOnSeq;
    int                     RegKindCode;

    NReqIntLeaf(void);
    ~NReqIntLeaf(void);

    void    SetData(int regcode ,int data ,Sequence *seq , int regkind);
};

class   FifoReqIntPacket
{
    NPListPack<NReqIntLeaf>     LData;
    QMutex						CSection;

  public:
	FifoReqIntPacket(void){}
	virtual ~FifoReqIntPacket(void){}

    void    Push(int regcode ,int data  ,Sequence *seq , int regkind);
    bool    Pop(int &regcode ,int &data ,Sequence **seq , int &regkind);
};

/*
void    _XSeqLocalInit(void);

void    _SetDataSpecialOperand(int ID, int d);
int     _GetDataSpecialOperand(int ID);

void    _SetDataSpecialBitOperand(int ID, bool d);
bool    _GetDataSpecialBitOperand(int ID);

void    _SetDataSpecialStringOperand(int ID, QString d);
QString  _GetDataSpecialStringOperand(int ID);

void    _SetDataSpecialFloatOperand(int ID, double d);
double  _GetDataSpecialFloatOperand(int ID);
*/

class ThreadSequenceAbstract : public ServiceForLayers
{
public:
	explicit	ThreadSequenceAbstract(LayersBase *base)
		:ServiceForLayers(base){}

public:
	virtual	void	MessageOutExec(int N){}
};

class ThreadSequence : public QThread,public ThreadSequenceAbstract
{
    Q_OBJECT

	QWidget			*MainW;
	SeqControl		*MainSeqControl;
	CommWindow		*CommWindowDim[30];
protected:
    virtual	void run()	override;
public:
    ThreadSequence(LayersBase *base ,QWidget *mainW);
	~ThreadSequence(void);

	void	SetFunction(SeqLocalParam *param
						,void (*XSeqLocalInit)					(SeqLocalParam *param ,SeqControl *seqControl)
						,void (*SetDataSpecialOperand)			(SeqLocalParam *param ,int ID, int d)
						,int  (*GetDataSpecialOperand)			(SeqLocalParam *param ,int ID)
						,void (*SetDataSpecialBitOperand)		(SeqLocalParam *param ,int ID, bool d)
						,bool (*GetDataSpecialBitOperand)		(SeqLocalParam *param ,int ID)
						,void (*SetDataSpecialStringOperand)	(SeqLocalParam *param ,int ID, QString d)
						,QString (*GetDataSpecialStringOperand)	(SeqLocalParam *param ,int ID)
						,void (*SetDataSpecialFloatOperand)		(SeqLocalParam *param ,int ID, double d)
						,double (*GetDataSpecialFloatOperand)	(SeqLocalParam *param ,int ID)
						);

	bool	LoadStartSequenceFile(QWidget *mainW,const QString &FileName 
												,const QString &IODLLFileName
												,const QString &IODefFileName 
												,QString &ErrorLine
												,QString Something
												,bool InitialOutput=true);
	QString					GetTitle(void);

	QSerialPort *OpenCommInThread(int ComNo,int Character ,int Parity ,int Stopbit ,int BPS);
	int			CommBytesAvailable(int ComNo);
	int			CommReadByte(int ComNo ,char *Buff ,int MaxLen);
private:
    QString			Msg;
	//static	ThreadSequence	*InstSeq;

    void  MessageOutFunc(void);
    void  MessageYesNoOutFunc(void);

    QString  DefaultString;
    void  MessageInputOutFunc(void);

    bool		Result;
	volatile	bool		Terminated;

    QString		ShowingMsg;
    int         PageCode;
    int         WRegID;
    Sequence                *ShowOnSeq;
    int                     RegKindCode;
    bool                    AliveMode;

    void  MessageShowOnFunc(void);
    void  MessageShowOffFunc(void);
    virtual void     BeforeActionOnExecute(void){}
    virtual void     AfterActionOnExecute(void){}

public:
	SeqControl	*GetMainSeqControl(void){	return MainSeqControl;	}

public:
	virtual	void	MessageOutExec(int N)	override;

public:
	//ThreadSequence	*GetInstSeq(void){	return InstSeq;	}
	static	void	MSleep(int milisec);
	static	int		GetNowMiliSec(void);

	void	MessageOut(const QString &s);
    bool	MessageYesNoOut(const QString &s);
    bool	MessageInputOut(const QString &defaultStr ,const QString &msg);
    void	MessageShowOn(const QString &s ,int _PageCode ,int _WRegID ,Sequence *seq ,int _RegKind);
    void	MessageShowOff(void);
    FifoReqIntPacket       ReqWRegChange;

	QWidget	*ShowSimulateSequence(QWidget *parent);
	void	SetTerminateFlag(void)	{	Terminated=true;	}
	QWidget *GetMainWindow(void)	{	return MainW;	}

	bool	IsAliveMode(void)	{	return AliveMode;	}
	PIOClass	*FindPIO(const QString &PIOName);
	PIOClass	*GetFirstPIO(void);
	void		LoopOnIdle(void);
signals:
    void SignalMessage(int N);

};

class	SignalOperandBase : public QObject , public NPList<SignalOperandBase>
{
	Q_OBJECT

	IdentifiedClass *Obj;
	int	ID;
	QString	Explain;
public:
	explicit	SignalOperandBase(IdentifiedClass *obj,int id ,const QString &explain=QString())
		:Obj(obj),ID(id),Explain(explain){}

	IdentifiedClass	*GetIdentifiedClass(void)	{	return Obj;	}
	virtual	QString	GetSignalOperandClassName(void)	const	=0;
	int		GetID(void)					const	{	return ID;	}
	const	QString &GetExplain(void)	const	{	return Explain;	}

	void	ShowErrorMessage(const SeqErrorInfo &ErrorCode);
signals:
	void	changed();
	void	loaded();
	void	changed(int);
	void	loaded(int);

};

class	SignalOperandInt : public SignalOperandBase
{
	int	Data;
public:
	explicit	SignalOperandInt(IdentifiedClass *Obj
								,int id ,const QString &explain=QString())
					:SignalOperandBase(Obj,id,explain){	Data=0;	}
	virtual	QString	GetSignalOperandClassName(void)	const	override	{	return /**/"SignalOperandInt";	}
	
	void	Set(int data)		{	Data=data;		}
	int		Get(void)	const	{	return Data;	}

	void	SetData(int data);
	int		GetData(void);
};

class	SignalOperandString : public SignalOperandBase
{
	QString	Data;
public:
	explicit	SignalOperandString(IdentifiedClass *Obj
									,int id,const QString &explain=QString())
					:SignalOperandBase(Obj,id,explain){}
	virtual	QString	GetSignalOperandClassName(void)	const	override	{	return /**/"SignalOperandString";	}

	void	Set(const QString &data)	{	Data=data;		}
	QString	Get(void)			const	{	return Data;	}

	void	SetData(const QString &data);
	QString		GetData(void);
};

class	SignalOperandBit : public SignalOperandBase
{
	bool	Data;
public:
	explicit	SignalOperandBit(IdentifiedClass *Obj
								,int id,const QString &explain=QString())
					:SignalOperandBase(Obj,id,explain){	Data=true;	}
	virtual	QString	GetSignalOperandClassName(void)	const	override	{	return /**/"SignalOperandBit";	}

	void	Set(bool data)		{	Data=data;		}
	bool	Get(void)	const	{	return Data;	}

	void	SetData(bool data);
	bool	GetData(void);
};

class	SignalOperandFloat : public SignalOperandBase
{
	double	Data;
public:
	explicit	SignalOperandFloat(IdentifiedClass *Obj
									,int id,const QString &explain=QString())
				:SignalOperandBase(Obj,id,explain){	Data=0;	}
	virtual	QString	GetSignalOperandClassName(void)	const	override	{	return /**/"SignalOperandFloat";	}

	void	Set(double data)	{	Data=data;		}
	double	Get(void)	const	{	return Data;	}

	void	SetData(double data);
	double	GetData(void);
};


class	LayersBase;
class   SeqLocalParam : public ServiceForLayers
{
public:
	enum	SpecialOperandRW{
				_ReadOnly
				,_WriteOnly
				,_ReadWrite	};

    FifoIntPacket       SeqWriteID;

    explicit	SeqLocalParam(LayersBase *base);
    ~SeqLocalParam(void);

	void	SetSpecialOperand(volatile int     *data ,int Default			,int code ,const char *Explain ,SpecialOperandRW RWMode=_ReadWrite);
	void	SetSpecialOperand(volatile bool	  *data ,bool Default			,int code ,const char *Explain ,SpecialOperandRW RWMode=_ReadWrite);
	void	SetSpecialOperand(volatile QString *data ,const char *Default	,int code ,const char *Explain ,SpecialOperandRW RWMode=_ReadWrite);
	void	SetSpecialOperand(volatile double *data ,double Default			,int code ,const char *Explain ,SpecialOperandRW RWMode=_ReadWrite);
			
	virtual	bool	SetSpecialOperand(SignalOperandInt *Ope		,SeqErrorInfo *Error=NULL,bool EnableDup=false);
	virtual	bool	SetSpecialOperand(SignalOperandBit *Ope		,SeqErrorInfo *Error=NULL,bool EnableDup=false);
	virtual	bool	SetSpecialOperand(SignalOperandString *Ope	,SeqErrorInfo *Error=NULL,bool EnableDup=false);
	virtual	bool	SetSpecialOperand(SignalOperandFloat *Ope	,SeqErrorInfo *Error=NULL,bool EnableDup=false);

	void	XSeqLocalInit(SeqControl *seqControl);

	virtual	void	SetDataSpecialOperand(int ID, int d);
	virtual	int		GetDataSpecialOperand(int ID)		const	;
	virtual	void	SetDataSpecialBitOperand(int ID, bool d);
	virtual	bool	GetDataSpecialBitOperand(int ID)	const	;
	virtual	void	SetDataSpecialStringOperand(int ID, QString d);
	virtual	QString GetDataSpecialStringOperand(int ID)	const	;
	virtual	void	SetDataSpecialFloatOperand(int ID, double d);
	virtual	double	GetDataSpecialFloatOperand(int ID)	const	;

	virtual	QString GetExplainSpecialOperand(int ID)		const;
	virtual	QString GetExplainSpecialBitOperand(int ID)		const;
	virtual	QString GetExplainSpecialStringOperand(int ID)	const;
	virtual	QString GetExplainSpecialFloatOperand(int ID)	const;

private:
	class	SpecialOperandListBase
	{
	public:
		int		Code;
		const	char	*Explain;
		SpecialOperandRW RWMode;

		SpecialOperandListBase(int code ,const char *explain, SpecialOperandRW rwMode):Code(code),Explain(explain),RWMode(rwMode){}
	};

	class	SpecialOperandListInt : public SpecialOperandListBase ,public NPList<SpecialOperandListInt>
	{
	public:
		volatile int		*Data;
		SpecialOperandListInt(volatile int *data ,int code ,const char *explain ,SpecialOperandRW rwMode):SpecialOperandListBase(code,explain,rwMode),Data(data){}
	};
	class	SpecialOperandListBit : public SpecialOperandListBase ,public NPList<SpecialOperandListBit>
	{
	public:
		volatile bool	*Data;
		SpecialOperandListBit(volatile bool *data ,int code ,const char *explain ,SpecialOperandRW rwMode):SpecialOperandListBase(code,explain,rwMode),Data(data){}
	};
	class	SpecialOperandListString : public SpecialOperandListBase ,public NPList<SpecialOperandListString>
	{
	public:
		volatile QString	*Data;
		SpecialOperandListString(volatile QString *data ,int code ,const char *explain ,SpecialOperandRW rwMode):SpecialOperandListBase(code,explain,rwMode),Data(data){}
	};
	class	SpecialOperandListFloat : public SpecialOperandListBase ,public NPList<SpecialOperandListFloat>
	{
	public:
		volatile double	*Data;
		SpecialOperandListFloat(volatile double *data ,int code ,const char *explain ,SpecialOperandRW rwMode):SpecialOperandListBase(code,explain,rwMode),Data(data){}
	};

	NPListPack<SpecialOperandListInt>		SpecialOperandListIntData;
	NPListPack<SpecialOperandListBit>		SpecialOperandListBitData;
	NPListPack<SpecialOperandListString>	SpecialOperandListStringData;
	NPListPack<SpecialOperandListFloat>		SpecialOperandListFloatData;

	SpecialOperandListInt		**IntDimPoint;
	SpecialOperandListBit		**BitDimPoint;
	SpecialOperandListString	**StringDimPoint;
	SpecialOperandListFloat		**FloatDimPoint;

	NPListPack<SignalOperandBase>	SpecialSignalOperandInt;
	NPListPack<SignalOperandBase>	SpecialSignalOperandString;
	NPListPack<SignalOperandBase>	SpecialSignalOperandBit;
	NPListPack<SignalOperandBase>	SpecialSignalOperandFloat;

	int	MaxCodeInt;
	int	MaxCodeBit;
	int	MaxCodeString;
	int	MaxCodeFloat;
};

//---------------------------------------------------------------------------
#endif
