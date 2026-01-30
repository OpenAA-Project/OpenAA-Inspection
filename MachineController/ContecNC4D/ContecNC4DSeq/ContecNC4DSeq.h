/*
 * Copyright (C) 2017
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

#ifndef CONTECNC4DSEQ_H
#define CONTECNC4DSEQ_H

#include "contecnc4dseq_global.h"
#include "XContecNC4DPipe.h"
#include <QLocalSocket>
#include <QLocalServer>
#include <QObject>

class	ContecNC4DController : public QObject
{
	Q_OBJECT

	QLocalSocket	*Socket;
	bool			Received;
public:
	ContecNC4DController(QObject *parents);
	~ContecNC4DController(void);

	bool	StartConnect(void);

	void	SendCommand(const QString &Str);
	void	SendCommand(const QString &Str ,int data);
	void	SendCommand(const QString &Str ,int data1,int data2);
	bool	WaitForRead(int WTm=100);

	QString		RData;

private slots:
	void	SlotReadyRead();
};


#endif // CONTECNC4DSEQ_H