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

#if	!defined(XPrinterClass_H)
#define	XPrinterClass_H

#include <QtGui>
//#include <QSqlDatabase>
#include <QLibrary>
#include <QMutex>
#include <QString>
#include <QIODevice>
#include "XServiceForLayers.h"
#include "XTypeDef.h"
#include "NList.h"
#include "XDLLManager.h"
#include "XGUIFormBase.h"

class	GUIDirectMessage;


class	PrinterStatus
{
	bool	ConnectionError;
	bool	Busy;
	bool	NoPaper;

};

class	PrinterDLLBaseClass : public QWidget ,public ServiceForLayers
{
public:
	PrinterDLLBaseClass(QWidget *parent ,LayersBase *base):QWidget(parent),ServiceForLayers(base){}
	virtual	~PrinterDLLBaseClass(void){}

	virtual	bool	Close(void){	return true;	}
	virtual	void	TransmitDirectly(GUIDirectMessage *packet){}
	virtual	void	LoopOnIdle(void){}

	virtual	bool	Save(QIODevice *f)						=0;
	virtual	bool	Load(QIODevice *f)						=0;

//Data level
	virtual	bool	CreateHeader	(int FormatID ,int DataID ,QStringList &Str)	=0;
	virtual	bool	CreatePageData	(int FormatID ,int DataID ,QStringList &Str)	=0;

//Device level
	virtual	bool	Initial(void)							=0;
	virtual	bool	ShowSettingDialog(void)					=0;
	virtual	bool	OutputPrinter(QStringList &Str)			=0;
	virtual	bool	OutputChangePage(void)					=0;
	virtual	bool	CheckStatus(PrinterStatus &Status)		=0;
};


#endif