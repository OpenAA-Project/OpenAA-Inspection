/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\Sequence\XPIOButton.h
** Author : YYYYYYYYYY
****************************************************************************-**/


/*----------------------------------------------------------------------------*/
//
//  äTóv
//
//  çÏê¨é“
//
/*----------------------------------------------------------------------------*/
#ifndef XPIOButtonH
#define XPIOButtonH

#include <QString>
#include <QStringList>
#include <stdio.h>
#include <QObject>
#include "XTypeDef.h"
#include "XServiceForLayers.h"
#include "NList.h"

class	PIOInterface;
class	EachPIOClass;
class	QWidget;
enum	VersionType;


class   PIOClass :   public QObject 
					,public NPList<PIOClass> 
					,public ServiceForLayers
{
	Q_OBJECT
		
	PIOInterface	*Interface;
public:
    explicit	PIOClass(LayersBase *base,bool psu);
    ~PIOClass(void);

	PIOInterface	*GetInterface(void)	{	return Interface;	}
	
	bool	IsPIODLL(void)		const;
	bool	LoadDLL(const QString &filename,bool OutputErrorMessage);
    bool    Initialize(QWidget *mainW,const QString &IODLLFileName,bool InitialOutput ,const QString &Something);
	void	GetExportFunctions(QStringList &Str);
	QString	GetFileName(void)	const;
	QString	GetCopyright(void)	const;
	QString	GetName(void)		const;
	WORD	GetVersion(void)	const;
	WORD	GetDLLType(void)	const;
	QString	GetExplain(void)	const;

	EachPIOClass    *GetPIOBrd(int brdnumb);

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

	int		GetBoardCount(void)		const;
	void	SetBoardName(int brdNo,const QString &BrdName);
	void	SetSomething(int brdNo,const QString &Something);
	QString	GetBoardName(int brdNo)	const;
	void	LoopOnIdle(void *handle ,int boardNumber);
	void	LoopOnIdle(void);

    bool    ReadDefFile (const QString &FileName,bool DefaultOut=true);
    bool    WriteDefFile(const QString &FileName);
	bool    ReadDefFileOfBoardName(const QString &FileName);

	const QString	&GetInBitName(int brdNo ,int bitNo)		const;
	const QString	&GetOutBitName(int brdNo ,int bitNo)	const;

	bool	GetRelatedDLL(QStringList &DLLFileNames);
	char	*GetRelatedDLLSystemVersion(const QString &DLLFileName ,VersionType vtype);
	const char	*GetSystemVersion(VersionType vtype);

	bool	CheckSystemVersionFunc(QStringList &Str 
							   ,const QString &DLLType 
							   ,const QString &DLLRoot 
							   ,const QString &DLLName);
public slots:
	void	SlotLogOutBit(int BoardNumber 
						,int portno,int bitno 
						,int data 
						,unsigned int MiliSec,int SepTime);
};

//extern  PIOClass    PIO;
class	PIOClassPack : public NPListPack<PIOClass>,public ServiceForLayers
{
public:
	PIOClassPack(LayersBase *base):ServiceForLayers(base){}

	int	SearchAddDLL(int32 &ErrorCode,bool OutputErrorMessage=true);
};

//--------------------------------------------------------------

#endif
