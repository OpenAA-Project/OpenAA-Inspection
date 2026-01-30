/*
 * Copyright (C) 2025
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

#include "XIntClass.h"
#include "NList.h"
#include <QString>
#include <QDateTime>
#include <QMutex>
#include "XServiceForLayers.h"
#include "XErrorCode.h"

class	AuthenticationInComponent;
class	GUIFormBase;
class	GUIDirectMessage;

class	AuthenticationPaper : public NPList<AuthenticationPaper>
{
	friend class	AuthenticationInComponent;

	QString		AuthenticationName;
	qint64		SpanSecFromInstall;
	int			CodeInHasp;
	GUIFormBase	*Form;
public:
	explicit	AuthenticationPaper(GUIFormBase *f ,const QString &_AuthenticationName=QString());
	virtual	~AuthenticationPaper(void);

	void		SetTerm(qint64 SpanSecFromInstall);
	qint64		GetTerm(void);

	GUIFormBase	*GetGUIForm(void)	{	return Form;	}

	void		SetCodeInHasp(int id=-1);
	int			GetCodeInHasp(void);
	virtual	void	TransmitDirectly(GUIDirectMessage *packet){}
};

class	AuthenticationInComponent : public ServiceForLayers
{
	friend	class	AuthenticationPaper;

	NPListPack<AuthenticationPaper>	AuthenticationBook;
	QString		ApplicationCode;
	QMutex		Mutex;
public:
	explicit	AuthenticationInComponent(LayersBase *base);
	virtual	~AuthenticationInComponent(void);

	void	ReleaseBook(void);
	bool	AddInitialHasp(const QString &HaspDLLFileName,const QString &Parameter=QString());

	QString	GetApplicationCode(void);
	void	SetApplicationCode(const QString &code);
	virtual	void	TransmitDirectly(GUIDirectMessage *packet);

	void	AddAuthentication(GUIFormBase *f 
				,const QString &_AuthenticationName=QString()
				,qint64 SpanSecFromInstall=-1
				,int id=-1);
	void	DelAuthentication(GUIFormBase *f);

	qint64	GetSpanSecFromInstall(GUIFormBase *f 
								,const QString &_AuthenticationName=QString()
								,int id=-1);
	qint64	GetSpanSecFromInstall(const QString &_AuthenticationName=QString()
								,int id=-1);

	bool	IsAuthenticationPassed(GUIFormBase *f
									,QString &FailMessage 
									,int &ErrorCode	//Described in XErrorCode.h
									,const QString &_AuthenticationName=QString()
									,const QString &_CurrentVersion=QString());
	bool	IsAuthenticationPassed( QString &FailMessage
									,int &ErrorCode	//Described in XErrorCode.h
									,const QString &_AuthenticationName=QString()
									,const QString &_CurrentVersion=QString());

	bool	IsAuthenticationPassed(GUIFormBase *f
									,qint64 SpanSecFromInstall
									,QString &FailMessage
									,int &ErrorCode	//Described in XErrorCode.h
									,const QString &_AuthenticationName=QString()
									,const QString &_CurrentVersion=QString());
	bool	IsAuthenticationPassed(qint64 SpanSecFromInstall
									,QString &FailMessage
									,int &ErrorCode	//Described in XErrorCode.h
									,const QString &_AuthenticationName=QString()
									,const QString &_CurrentVersion=QString());
};

