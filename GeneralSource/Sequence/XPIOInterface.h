/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\Sequence\XPIOButton.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#ifndef XPIOInterfaceH
#define XPIOInterfaceH

#include <QString>
#include <QMutex>
#include <QLibrary>
#include <QObject>
#include <QTextStream>
#include <stdio.h>
#include "XTypeDef.h"
#include "XParamBase.h"
#include "XServiceForLayers.h"
#include "XDLLManager.h"
#include "XPIOButton.h"

class	PIOClass;
class   PIOInterface;

class   EachPIOClass : public QObject
{
	Q_OBJECT
		
	QString  Name;
    int         PIO_INBITNUMB ;
    int         PIO_OUTBITNUMB;
    volatile    BYTE    *OutData;		//出力バッファ
    volatile    BYTE    *LastOutData;   //出力バッファ
    volatile    BYTE    *InData;		//入力バッファ
	volatile    DWORD	*LastOutMilisec;

    int         BoardNumber;
    bool        Initialized;
    bool        Opened;
	QMutex		IOAccessMutex;

    QString  *DefInName;
    QString  *DefOutName;
    bool        *DefaultOutData;
	PIOInterface	*Parent;
	bool		AttrNoLoop;
	void		*Handle;
	bool		*EnableScanLoopIn ;
	bool		*EnableScanLoopOut;

  public:
    explicit	EachPIOClass(void);
    ~EachPIOClass(void);

    void    Initialize(PIOInterface *parent);
	void    InitialOutput(void);

    bool    Open(QWidget *mainW,const QString &Something);
    bool    Close(void);
    bool    ReadDefFile(FILE *file,char *buff ,int buffsize ,bool DefaultOut=true);
	bool    ReadDefFile(QTextStream &file ,QString &StrBuff,int buffsize,bool DefaultOut=true);
    bool    WriteDefFile(FILE *file);
    EachPIOClass  &  operator=(const EachPIOClass &src);

 	int		GetIOInBitCount		(void)	const;
	int		GetIOOutBitCount	(void)	const;
	
	BYTE    GetByte(int portno);
    int     GetBit(int portno ,int bitno);
    void    SetByte(int portno ,BYTE data);
    void    SetBit(int portno ,int bitno  ,BYTE data);

    BYTE    GetOutByte(int portno);
    int     GetOutBit(int bitno);
    BYTE    GetBufferedInByte(int portno);
    BYTE    GetBufferedOutByte(int portno);

    BYTE    GetEchobackOutByte(int portno);
    int     GetEchobackOutBit(int bitno);

	int		GetBoardNumber(void)	const	{	return BoardNumber;		}
	void	SetBoardNumber(int d)			{	BoardNumber=d;			}
	void    LoopIO(void);
	void	PutByteData(int portno,BYTE data);
	void	PutBitData(int portno,int bitno ,BYTE data);

	const QString	&GetInBitName(int bitNo)	const	{	return DefInName[bitNo];	}
	const QString	&GetOutBitName(int bitNo)	const	{	return DefOutName[bitNo];	}

	void	LoopOnIdle(void);
protected:
	void    SetBitWithoutLock(int portno ,int bitno  ,BYTE data);
	void	LogOutBit(int portno,int bitno ,BYTE data);
signals:
	void	SignalLogOutBit(int BoardNumber ,int portno,int bitno 
							,int data 
							,unsigned int MiliSec,int SepTime);
};

class	PIOBrdNameList : public NPList<PIOBrdNameList>
{
public:
	int		BrdNo;
	QString	BrdName;

	explicit	PIOBrdNameList(int brdNo ,const QString	&brdName){	BrdNo=brdNo;	BrdName=brdName;	}
};

class	PIOBrdSomethingList : public NPList<PIOBrdSomethingList>
{
public:
	int		BrdNo;
	QString	Something;

	explicit	PIOBrdSomethingList(int brdNo ,const QString &something){	BrdNo=brdNo;	Something=something;	}
};

class   PIOInterface : public DLLManager ,public ServiceForLayers
{
	int		PIO_BoardNumb;
    EachPIOClass    *PIOBrd;
	bool	Loaded;

	WORD	(*DLL_GetDLLType)(void);
	bool	(*DLL_GetName)(QString &str);
	const char	*(*DLL_GetExplain)(void);
	WORD	(*DLL_GetVersion)(void);
	bool	(*DLL_CheckCopyright)(QString &CopyrightString);

	int		( *AIP_IO_GetIOBoardNumb)(void);
	int		( *AIP_IO_GetIOInBitCount) (void *handle ,int boardNumber);
	int		( *AIP_IO_GetIOOutBitCount)(void *handle ,int boardNumber);
	bool	( *AIP_IO_Initial)(const QStringList &NameList);
	void	*( *AIP_IO_Open)	(QWidget *mainW,int boardNumber , char *name ,int maxbuffsize,const QString &Something);
	BYTE	( *AIP_IO_GetBit)	(void *handle ,int boardNumber , BYTE bitIndex);
	BYTE	( *AIP_IO_GetByte)	(void *handle ,int boardNumber , BYTE byteIndex);
	void	( *AIP_IO_SetBit)	(void *handle ,int boardNumber , BYTE bitIndex ,BYTE data);
	BYTE	( *AIP_IO_SetByte)	(void *handle ,int boardNumber , BYTE byteIndex , BYTE data);
	int		( *AIP_IO_GetOutByte)(void *handle ,int boardNumber , BYTE byteIndex);
	int		( *AIP_IO_GetOutBit)(void *handle ,int boardNumber , BYTE bitIndex);
	bool	( *AIP_IO_Close)	(void *handle ,int boardNumber);
	bool	( *AIP_IO_Release)(void);
	void	( *AIP_IO_LoopOnIdle)(void *handle,int boardNumber);
	QLibrary 	DllLib;

    volatile    bool    Initialized;
    volatile    bool    Changed;
	QString		PIOFileName;

    bool    Psu;						// Ｉ／Ｏの仮想化
	NPListPack<PIOBrdNameList>		BrdNameListContainer;
	NPListPack<PIOBrdSomethingList>	BrdSomethingListContainer;

public:
    explicit	PIOInterface(LayersBase *base,bool psu);
    ~PIOInterface(void);

	bool	IsPIODLL(void)	const;
	bool	LoadDLL(const QString &filename,bool OutputErrorMessage);
    bool    Initialize(QWidget *mainW,const QString &IODLLFileName,bool InitialOutput ,const QString &Something);
	virtual	void	GetExportFunctions(QStringList &Str)	override;
	QString	GetFileName(void)	const{	return PIOFileName;	}
	QString	GetCopyright(void)	const;
	QString	GetName(void)		const;
	WORD	GetVersion(void)	const;
	WORD	GetDLLType(void)	const;
	const QString	GetExplain(void)	const;

	EachPIOClass    *GetPIOBrd(int brdnumb)	const;

    BYTE    GetByteInvolved	(int brdnumb ,int portno);
    BYTE    GetByte			(int brdnumb ,int portno);
    int     GetBit			(int brdnumb ,int portno ,int bitno);
    void    SetByte			(int brdnumb ,int portno ,BYTE data);
    void    SetBit			(int brdnumb ,int portno ,int bitno  ,BYTE data);

    BYTE    GetOutByte			(int brdnumb ,int portno);
    int     GetOutBit			(int brdnumb ,int bitno);
    BYTE    GetBufferedInByte	(int brdnumb ,int portno);
    BYTE    GetBufferedOutByte	(int brdnumb ,int portno);
	int		GetIOInBitCount		(int brdnumb);
	int		GetIOOutBitCount	(int brdnumb);

	bool	SetBit(const QString &OutBitName,BYTE data);
	bool	GetBit(const QString &InBitName ,BYTE &data);
	bool	GetEchobackBit(const QString &OutBitName ,BYTE &data);

	int		GetIOInBitCount		(void *handle ,int boardNumber);
	int		GetIOOutBitCount	(void *handle ,int boardNumber);
	void	*Open				(QWidget *mainW,int boardNumber , char *name ,int maxbuffsize,const QString &Something);
	bool	Close				(void *handle ,int boardNumber);

	BYTE	IO_GetBit		(void *handle ,int boardNumber , BYTE bitIndex);
	BYTE	IO_GetByte		(void *handle ,int boardNumber , BYTE byteIndex);
	bool	IO_SetBit		(void *handle ,int boardNumber , BYTE bitIndex , BYTE data);
	bool	IO_SetByte		(void *handle ,int boardNumber , BYTE byteIndex , BYTE data);
	int		IO_GetOutByte	(void *handle ,int boardNumber , BYTE byteIndex);
	int		IO_GetOutBit	(void *handle ,int boardNumber , BYTE bitIndex);
	int     GetEchobackOutBit(int boardNumber , int bitno);
	BYTE    GetEchobackOutByte(int boardNumber , int portno);

	void	LoopIO(void);

	int		GetBoardCount(void)		const	{	return PIO_BoardNumb;	}
	void	SetBoardName(int brdNo,const QString &BrdName);
	void	SetSomething(int brdNo,const QString &Something);
	QString	GetBoardName(int brdNo)	const;
	void	LoopOnIdle(void *handle ,int boardNumber);
	void	LoopOnIdle(void);
  public:
    char    *DefFileName;
    bool    ReadDefFile (const QString &FileName,bool DefaultOut=true);
    bool    WriteDefFile(const QString &FileName);
	bool    ReadDefFileOfBoardName(const QString &FileName);

	const QString	&GetInBitName(int brdNo ,int bitNo)		const	{	return PIOBrd[brdNo].GetInBitName(bitNo);	}
	const QString	&GetOutBitName(int brdNo ,int bitNo)	const	{	return PIOBrd[brdNo].GetOutBitName(bitNo);	}
};


//--------------------------------------------------------------

#endif
