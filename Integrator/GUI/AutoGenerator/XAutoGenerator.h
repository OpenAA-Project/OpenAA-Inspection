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

#include "NListComp.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "IntegrationLib.h"
#include "XIntegrationPacketComm.h"

class ListAutoGenerator : public NPListSaveLoad<ListAutoGenerator>
{
public:
	QString	Code			;
	QString	Name			;
	QString	DXFFileName		;
	QString	PDFFileName		;
	QString	AlignFileName	;
	QString	SpecialFileName	;

	ListAutoGenerator(void);
	ListAutoGenerator(const ListAutoGenerator &src);

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;

	ListAutoGenerator	&operator=(const ListAutoGenerator &src);

};
class ListAutoGeneratorContainer : public NPListPackSaveLoad<ListAutoGenerator>
{
public:
	ListAutoGeneratorContainer(void);
	ListAutoGeneratorContainer(const ListAutoGeneratorContainer &src);

	virtual	ListAutoGenerator	*Create(void)	override;

	ListAutoGeneratorContainer	&operator=(const ListAutoGeneratorContainer &src);
};

//==================================================================================

class	IntegrationCmdExecuteAutoGenerator : public IntegrationCmdPacketBase
{
public:
	QByteArray	DXFData		;
	QByteArray	PDFData		;
	QByteArray	AlignData	;
	QByteArray	SpecialData	;

	IntegrationCmdExecuteAutoGenerator(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	

private:

};