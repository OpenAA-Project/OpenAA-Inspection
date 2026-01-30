/*
 * Copyright (C) 2013
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

#if	!defined(XIOLogThread_H)
#define	XIOLogThread_H

#include <QThread>
#include "XDateTime.h"
#include <QReadWriteLock>
#include "XTypeDef.h"
#include "XSequence.h"

class	RegList : public NPList<RegList>
{
public:
	Operand *Ope;
	bool	LastDataB;
	int		LastDataN;
	double	LastDataD;
	QString	LastDataS;
	bool	Changed;
	char	StrName[20];

	RegList(SeqControl *seq,const QString &RegStr);

	bool	GetAndCompare(void);
	void	MakeStr(char Buff[]);
	void	I2Str(char *s,int n);
	void	B2Str(char *s,bool n);
};

class ThreadIOLogger : public QThread
{
	Q_OBJECT

public:
	char		FileName[256];
	SeqControl	*Seq;
	NPListPack<RegList>	RegDatas;

	BYTE	LastInByte[100];
	BYTE	LastOutByte[100];
	int		PIOBoardNumber;
	int		IBitCount;
	int		OBitCount;
	QStringList		PushedMesssages;
	QMutex			MutexMessage;

	ThreadIOLogger(SeqControl *seq);

	void run();

	void	AddReg(const QString &RegStr);
	void	AddMessage(const QString &Str);
};

#endif