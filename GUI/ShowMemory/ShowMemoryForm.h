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

#ifndef SHOWMEMORYFORM_H
#define SHOWMEMORYFORM_H

#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"


namespace Ui {
class ShowMemoryForm;
}


struct	__ShowMemoryStruct
{
	unsigned long		dwLength;
	unsigned long		dwMemoryLoad;
	unsigned long long	ullTotalPhys;
	unsigned long long	ullAvailPhys;
	unsigned long long	ullTotalPageFile;
	unsigned long long	ullAvailPageFile;
	unsigned long long	ullTotalVirtual;
	unsigned long long	ullAvailVirtual;
	unsigned long long	ullAvailExtendedVirtual;
};

class ShowMemoryForm : public GUIFormBase
{
    Q_OBJECT
    QTimer	TM;
public:
	QFont	CFont;
	struct	__ShowMemoryStruct	ShowMemoryStruct;
	struct	__ShowMemoryStruct	*ShowMemoryStructInSlave;
	int		SlavePageNumb;

    explicit ShowMemoryForm(LayersBase *Base ,QWidget *parent = 0);
    ~ShowMemoryForm();
	virtual void	Prepare(void)	override;
private:
    Ui::ShowMemoryForm *ui;
	
private slots:
	void	SlotTimeout();
	void	ResizeAction();
};

//============================================================================================

class	GUICmdReqShowMemory : public GUICmdPacketBase
{
public:
	GUICmdReqShowMemory(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckShowMemory : public GUICmdPacketBase
{
public:
	struct	__ShowMemoryStruct	ShowMemoryStruct;

	GUICmdAckShowMemory(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};
//============================================================================================

bool	GetMemoryInfo(
	 unsigned long		&dwMemoryLoad
	,unsigned long long	&ullTotalPhys
	,unsigned long long	&ullAvailPhys
	,unsigned long long	&ullTotalPageFile
	,unsigned long long	&ullAvailPageFile
	,unsigned long long	&ullTotalVirtual
	,unsigned long long	&ullAvailVirtual
	,unsigned long long	&ullAvailExtendedVirtual
	);

#endif // SHOWMEMORYFORM_H