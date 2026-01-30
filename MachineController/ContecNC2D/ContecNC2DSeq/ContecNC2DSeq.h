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

#ifndef CONTECNC2DSEQ_H
#define CONTECNC2DSEQ_H

#include "contecnc2dseq_global.h"
#include "XContecNC2DPipe.h"
#include <QLocalSocket>
#include <QLocalServer>
#include <QWidget>

class	ContecNC2DController : public QObject
{
	Q_OBJECT

	QLocalSocket	*Socket;
	bool			Received;
public:
	ContecNC2DController(QObject *parents);
	~ContecNC2DController(void);

	bool	StartConnect(void);

	void	SendCommand(const QString &Str);
	bool	WaitForRead(void);

	QString		RData;

private slots:
	void	SlotReadyRead();
};

#endif // CONTECNC2DSEQ_H