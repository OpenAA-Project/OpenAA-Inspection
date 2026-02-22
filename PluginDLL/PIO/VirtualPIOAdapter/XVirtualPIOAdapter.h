/*
 * Copyright (C) 2016
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

#if	!defined(XVirtualPIOAdapter_h)
#define	XVirtualPIOAdapter_h


#include "NList.h"
#include <QString>
#include "XTypeDef.h"
#include <QBuffer>
#include "XVirtualPIOCommon.h"
#include <QWidget>
#include <QSharedMemory>
#include <QMutex>
#include "XIODLL.h"

class	PIOAdapter : public PIODLLBaseClass
{
	struct	PIOMemoryMap	*MemMap;
	QSharedMemory		AttachedMem;
	int32				MemHandle;
	QMutex				Mutex;
public:

	PIOAdapter(QWidget *parent,const QString &IPAddress,int PortNumber=28200 ,const QString &MemName=/**/"VirtualPIO");
	~PIOAdapter(void);

	bool	LoadDefFile(const QString &FileName);
	int		GetBitCountIn(void);
	int		GetBitCountOut(void);

	int		GetBitData(int bitnumber);
	bool	SetBitData(int bitnumber ,int data);
	bool	GetBitInDataStream(BYTE BitData[] ,int BitNumb);
	bool	SetBitOutDataStream(BYTE BitData[] ,int BitNumb);
	bool	GetBitOutDataStream(BYTE BitData[] ,int BitNumb);

	int		GetBitOutData(int bitnumber);

private:
	int		GetAckCommand(void);
	void	ClearAckCommand(void);
};



#endif