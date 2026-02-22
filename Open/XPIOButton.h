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



#ifndef XPIOButtonH
#define XPIOButtonH

#include <QString>
#include <QStringList>
#include <stdio.h>
#include <QObject>
#include "XTypeDef.h"
#include "XServiceForLayers.h"
#include "NList.h"
#include "XIODLL.h"

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
	
	void	InitialPrepare(void);
	void	Prepare(void)		;
	void	AfterPrepare(void)	;
	void	ReadyParam(void)	;
	void	AfterStartSequence(void);

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

	int		GetIOInBitCount		(PIODLLBaseClass *handle ,int boardNumber);
	int		GetIOOutBitCount	(PIODLLBaseClass *handle ,int boardNumber);
	PIODLLBaseClass	*Open				(QWidget *mainW,int boardNumber , char *name ,int maxbuffsize,const QString &Something);
	bool	Close			(PIODLLBaseClass *handle ,int boardNumber);

	BYTE	IO_GetBit		(PIODLLBaseClass *handle ,int boardNumber , BYTE bitIndex);
	BYTE	IO_GetByte		(PIODLLBaseClass *handle ,int boardNumber , BYTE byteIndex);
	bool	IO_SetBit		(PIODLLBaseClass *handle ,int boardNumber , BYTE bitIndex , BYTE data);
	bool	IO_SetByte		(PIODLLBaseClass *handle ,int boardNumber , BYTE byteIndex , BYTE data);
	int		IO_GetOutByte	(PIODLLBaseClass *handle ,int boardNumber , BYTE byteIndex);
	int		IO_GetOutBit	(PIODLLBaseClass *handle ,int boardNumber , BYTE bitIndex);
	int     GetEchobackOutBit(int boardNumber , int bitno);
	BYTE    GetEchobackOutByte(int boardNumber , int portno);

	void	LoopIO(void);

	int		GetBoardCount(void)		const;
	void	SetBoardName(int brdNo,const QString &BrdName);
	void	SetSomething(int brdNo,const QString &Something);
	QString	GetBoardName(int brdNo)	const;
	void	LoopOnIdle(PIODLLBaseClass *handle ,int boardNumber);
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

class	PIOClassPack : public NPListPack<PIOClass>,public ServiceForLayers
{
public:
	PIOClassPack(LayersBase *base):ServiceForLayers(base){}

	int	SearchAddDLL(int32 &ErrorCode,bool OutputErrorMessage=true);

	void	InitialPrepare(void);
	void	Prepare(void)		;
	void	AfterPrepare(void)	;
	void	ReadyParam(void)	;
	void	AfterStartSequence(void);
};

//--------------------------------------------------------------

#endif