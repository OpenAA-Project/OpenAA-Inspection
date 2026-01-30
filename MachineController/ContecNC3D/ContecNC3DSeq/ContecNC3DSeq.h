/*
 * Copyright (C) 2015
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

#ifndef CONTECNC3DSEQ_H
#define CONTECNC3DSEQ_H

#include "contecnc3dseq_global.h"
#include "XContecNC3DPipe.h"
#include <QLocalSocket>
#include <QLocalServer>
#include <QObject>

class	ContecNC3DController : public QObject
{
	Q_OBJECT

	QLocalSocket	*Socket;
	bool			Received;
public:
	ContecNC3DController(QObject *parents);
	~ContecNC3DController(void);

	bool	StartConnect(void);

	void	SendCommand(const QString &Str);
	void	SendCommand(const QString &Str ,int data);
	bool	WaitForRead(int WTm=100);

	QString		RData;

private slots:
	void	SlotReadyRead();
};

#endif // CONTECNC3DSEQ_H