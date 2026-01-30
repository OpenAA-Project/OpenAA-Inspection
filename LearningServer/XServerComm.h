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

#pragma once

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include "XServerLayerBase.h"
#include "NList.h"

class	LearningServer;

class LearningServerSocket : public QObject
							,public NPList<LearningServerSocket>
							,public ServiceForLayers
{
	Q_OBJECT

	LearningServer	*Parent;
	QTcpSocket		*sv;
	int				Error;
public:
	LearningServerSocket(QTcpSocket *s ,LearningServer *obj);

	QTcpSocket	*GetSocket(void)	const{	return sv;	}
private slots:
	void	SlotReadyRead();
	void	SlotDisconnected();
};