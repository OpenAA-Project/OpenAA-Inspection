/*
 * Copyright (C) 2021
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

#if	!defined(XQuickBuffer_h)
#define	XQuickBuffer_h

#include "NList.h"
#include <QIODevice>
#include <QByteArray>
#include "XTypeDef.h"

#define	QuickBufferFirstSize	1000


class	QuickBuffer : public QIODevice
{
	class	MemoryInBuffer : public NPList<MemoryInBuffer>
	{
	public:
		BYTE		*Pointer;
		int			AllocSize;
		int			WSize;

		MemoryInBuffer(int Len);
		~MemoryInBuffer(void);
	};
	NPListPack<MemoryInBuffer>	BuffStock;

	MemoryInBuffer	*CurrentBuff;
	int				Current;
	QIODevice::OpenMode Mode;
public:
	QuickBuffer(QByteArray *buff);
	QuickBuffer(void);
	virtual	~QuickBuffer();

	virtual bool open ( QIODevice::OpenMode mode );
	virtual	void close ();
	
	virtual qint64 pos () const;
	virtual bool reset ();
	virtual bool seek ( qint64 pos );
	virtual qint64 size () const;

protected:
	virtual qint64 readData ( char * data, qint64 maxSize );
	virtual qint64 readLineData ( char * data, qint64 maxSize );
	virtual qint64 writeData ( const char * data, qint64 maxSize );

};


#endif