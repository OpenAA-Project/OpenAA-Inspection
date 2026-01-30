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

#if	!defined(XRemoteLightController_h)
#define	XRemoteLightController_h

#include "NListComp.h"
#include "XSocketClient.h"
#include "XServiceForLayers.h"

class	LightAccessList;
class	RemoteLightContainer;

class	RemoteLightItem : public SocketClient ,public ServiceForLayers
{
    Q_OBJECT

	RemoteLightContainer	*Parent;
	LightAccessList	*LightPointer;
	QByteArray		LightRawData;
public:
	int			ID;
	QString		DLLFileName;
	QString		RegName;
	QString		IPAddress;
	int			PortNumber;
	QString		InitialString;

	RemoteLightItem(LayersBase *Base ,RemoteLightContainer *parent);
	~RemoteLightItem(void);

	RemoteLightItem	*GetNextD(RemoteLightContainer &parent);

	RemoteLightItem	&operator=(RemoteLightItem &src);
	QString	GetDLLName(void);

	bool	ShowSetting(QWidget *parent);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	bool	SaveLightSetting(QIODevice *f);
	bool	LoadLightSetting(QIODevice *f);
	LightAccessList	*GetLightPointer(void)	{	return LightPointer;	}
	bool	ReflectLight(void);

	bool	SetOnOff(bool OnMode);
	
	bool	OpenDLL(QObject *parent);
	bool	CloseDLL(void);
	bool	SendCommand(BYTE *Data ,int32 DataLen);

public slots:
	void	SlotReceived(int);
	void	SlotReflectDataInDialog();
	void	SlotReflectOnOffInDialog(bool LightOn);
};


const int	LightDimCount=100;
class	RemoteLightContainer  :public ServiceForLayers
{
	RemoteLightItem		*Dim[LightDimCount];
public:
	RemoteLightContainer(LayersBase *Base);

	virtual	RemoteLightItem	*Create(void);
	int		GetMaxID(void);

	QString	GetDefaultFileName(void){	return "RemoteLight.dat";	}

	RemoteLightContainer	&operator=(RemoteLightContainer &src);
	void			RemoveAll(void);
	RemoteLightItem	*GetFirst(void);
	RemoteLightItem	*GetNextItem(RemoteLightItem *p);
	RemoteLightItem	*GetItem(int n);
	int				GetCount(void);
	bool			AppendList(RemoteLightItem	*a);
	bool			RemoveList(RemoteLightItem	*a);
	void			MoveFrom(RemoteLightContainer &a);

	bool	OpenDLL(QObject *parent);
	bool	CloseDLL(void);
	bool	ReflectLight(void);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

#endif