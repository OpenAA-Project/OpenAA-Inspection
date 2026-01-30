/*
 * Copyright (C) 2022
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

#if	!defined(XSingleExecuteBySocket_h)
#define	XSingleExecuteBySocket_h

#include <QLocalServer>
#include <QLocalSocket>
#include <QString>
#include <QObject>

class	CheckSingleExecution : public QObject
{
	Q_OBJECT

	QLocalServer	Server;
	QLocalSocket	Client;
	QLocalSocket	*ClientInServer;
	QString	IdentifiedName;

public:
	CheckSingleExecution(const QString &IdentifiedName,QObject *parent);
	~CheckSingleExecution(void);

	bool	CheckDoubleBoot(void);
	bool	RequireTerminate(void);

public slots:
	void	SlotNewConnection ();
	void	SlotReadyReadInServer();
signals:
	void	SignalTerminateFromOther();
};

class	ClassSingleExecution
{
	CheckSingleExecution	Execution;
public:
	explicit	ClassSingleExecution(QObject *parent);
};


#endif