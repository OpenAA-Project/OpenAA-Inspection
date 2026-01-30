/*
 * Copyright (C) 2014
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

#if	!defined(XAUTOFOCUSCONTROL_H)
#define	XAUTOFOCUSCONTROL_H

#include "XGUIPacketForDLL.h"

class	QextSerialPort;

class	AFControl
{
public:
	int				CommPort;
	QextSerialPort    *sio;

	AFControl(void);

	bool	OpenPort(int port);
	bool	ClosePort(void);
	bool	IsOpened(void);

	bool	GoAutofocus(void);
	int		GetCurrentZ(void);
	bool	ChangeNumber(char number);

private:
	int		GetChar(void);
	void	SendChar(unsigned char d);

	bool	SendStr(char *s);
	bool	GetStr(char buff[] ,int maxlen);
};

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

class	CmdSetLensRange : public GUIDirectMessage
{
public:
	int		Number;

	CmdSetLensRange(LayersBase *base)
		:GUIDirectMessage(base){}
};

class	CmdReqLensRange : public GUIDirectMessage
{
public:
	int		Number;
	int		ZoomRate;

	CmdReqLensRange(LayersBase *base)
		:GUIDirectMessage(base){	Number=1;	}
};

class	CmdMovePosition : public GUIDirectMessage
{
public:
	CmdMovePosition(LayersBase *base)
		:GUIDirectMessage(base){}
};


#endif