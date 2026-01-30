/*
 * Copyright (C) 2024
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

#if	!defined(XForceRebooter_h)
#define	XForceRebooter_h

#include"NListComp.h"
#include<QString>
#include<QIODevice>
#include"XTransSocket.h"


#define	DefaultForceRebooterPortNumber	15400

class	ForceRebooter;

class	PartnerInfo : public NPListSaveLoad<PartnerInfo>
{
public:
	QString		HostName;
	int			PortNumber;
	QString		Remark;

	PartnerInfo(void);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
	PartnerInfo	&operator=(PartnerInfo &src);
};


class	RebooterParam : public NPListPackSaveLoad<PartnerInfo>
{
public:
	int			OwnPortNumber;
	QStringList	RebootedPrograms;

	RebooterParam(void);

	virtual	PartnerInfo	*Create(void);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);

	QString	GetDefaultFileName(void)	{	return QString("ForceRebooterSetting.dat");	}

	bool	Save(void);
	bool	Load(void);

};

class	RebooterSocket : public TrSocketClient
{
    Q_OBJECT

	PartnerInfo	Info;
	int			RecvCmd;
	const RebooterParam	&Param;
public:
	QWidget	*Parent;

	RebooterSocket(QWidget *parent,const RebooterParam &param ,PartnerInfo *info);

	bool	RebootPrograms(void);
	bool	RebootPC(void);
	bool	ShutdownPC(void);
private slots:
	void	SlotReceived(int);
private:
	void	RealRebootPrograms(void);
	void	RealRebootPC(void);
	void	RealShutdownPC(void);
};

class	RebooterServer : public TrSocketServer
{
    Q_OBJECT

	int		BaseID;
	QWidget	*Parent;

public:
	RebooterParam	Param;

	RebooterServer(QWidget *parent);

	virtual	RebooterSocket	*NewSocket(void);

	bool	RebootPrograms(void);
	bool	RebootPC(void);
	bool	ShutdownPC(void);
};

#define	Cmd_None			0
#define	Cmd_RebootPrograms	1
#define	Cmd_RebootPC		2
#define	Cmd_ShutDownPC		3
#define	Cmd_OwnRebootPC		4
#define	Cmd_OwnShutDownPC	5
#endif