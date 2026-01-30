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

#if	!defined(ContecNC3DPipe_h)
#define	ContecNC3DPipe_h
#include <QLocalSocket>
#include <QLocalServer>


class	ContecNC3DPipe;
class	ContecNC3D;

class	ContecNC3DPipeInstance : public QObject
{
	Q_OBJECT

	ContecNC3DPipe	*Parent;
	QLocalSocket	*Socket;
public:
	ContecNC3DPipeInstance(ContecNC3DPipe *parent ,QLocalSocket *s);

private slots:
	void	SlotReadyRead();
};

class	ContecNC3DPipe : public QLocalServer
{
	Q_OBJECT

	ContecNC3D	*Parent;
public:
	ContecNC3DPipe ( ContecNC3D * parent = 0 );

	void	Start(void);
	void	ExeOrigin(void);
	void	ExeStartXY();
	void	ExeStepXY();
	bool	IsEndXY();
	void	ExeStartZ(int ZMicron);
	bool	IsEndZ();
	bool	IsStartButton();

	void	SetLightGreen(bool b);
	void	SetBlink(bool b);
	void	GoMoveZ(int ZMicron);
	void	SetVacuum(bool b);

private slots:
	void	SlotNewConnection ();

};
#endif