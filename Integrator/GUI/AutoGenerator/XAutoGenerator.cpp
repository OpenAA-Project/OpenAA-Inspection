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

#include "XGeneralFunc.h"
#include "XAutoGenerator.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

ListAutoGenerator::ListAutoGenerator(void)
{
}
ListAutoGenerator::ListAutoGenerator(const ListAutoGenerator &src)
{
	Code			=src.Code				;
	Name			=src.Name				;
	DXFFileName		=src.DXFFileName		;
	PDFFileName		=src.PDFFileName		;
	AlignFileName	=src.AlignFileName		;
	SpecialFileName	=src.SpecialFileName	;
}

bool	ListAutoGenerator::Save(QIODevice *f)
{
	int	Ver=1;

	if(::Save(f,Ver)==false)
		return false;

	if(::Save(f,Code)==false)
		return false;
	if(::Save(f,Name)==false)
		return false;
	if(::Save(f,DXFFileName)==false)
		return false;
	if(::Save(f,PDFFileName)==false)
		return false;
	if(::Save(f,AlignFileName)==false)
		return false;
	if(::Save(f,SpecialFileName)==false)
		return false;
	return true;
}
bool	ListAutoGenerator::Load(QIODevice *f)
{
	int	Ver;

	if(::Load(f,Ver)==false)
		return false;

	if(::Load(f,Code)==false)
		return false;
	if(::Load(f,Name)==false)
		return false;
	if(::Load(f,DXFFileName)==false)
		return false;
	if(::Load(f,PDFFileName)==false)
		return false;
	if(::Load(f,AlignFileName)==false)
		return false;
	if(::Load(f,SpecialFileName)==false)
		return false;
	return true;
}

ListAutoGenerator	&ListAutoGenerator::operator=(const ListAutoGenerator &src)
{
	Code			=src.Code				;
	Name			=src.Name				;
	DXFFileName		=src.DXFFileName		;
	PDFFileName		=src.PDFFileName		;
	AlignFileName	=src.AlignFileName		;
	SpecialFileName	=src.SpecialFileName	;

	return *this;
}


ListAutoGeneratorContainer::ListAutoGeneratorContainer(void)
{
}
ListAutoGeneratorContainer::ListAutoGeneratorContainer(const ListAutoGeneratorContainer &src)
{
	for(ListAutoGenerator *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		ListAutoGenerator	*d=new ListAutoGenerator(*s);
		AppendList(d);
	}
}

ListAutoGenerator	*ListAutoGeneratorContainer::Create(void)
{
	return new ListAutoGenerator();
}

ListAutoGeneratorContainer	&ListAutoGeneratorContainer::operator=(const ListAutoGeneratorContainer &src)
{
	for(ListAutoGenerator *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		ListAutoGenerator	*d=new ListAutoGenerator(*s);
		AppendList(d);
	}
	return *this;
}

//=========================================================================================
IntegrationCmdExecuteAutoGenerator::IntegrationCmdExecuteAutoGenerator(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}

bool	IntegrationCmdExecuteAutoGenerator::Load(QIODevice *f)
{
	if(::Load(f,DXFData		)==false)	return false;
	if(::Load(f,PDFData		)==false)	return false;
	if(::Load(f,AlignData	)==false)	return false;
	if(::Load(f,SpecialData	)==false)	return false;
	return true;
}
bool	IntegrationCmdExecuteAutoGenerator::Save(QIODevice *f)
{
	if(::Save(f,DXFData		)==false)	return false;
	if(::Save(f,PDFData		)==false)	return false;
	if(::Save(f,AlignData	)==false)	return false;
	if(::Save(f,SpecialData	)==false)	return false;
	return true;
}

void	IntegrationCmdExecuteAutoGenerator::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase	*f=GetLayersBase()->FindByName(sRoot,sName,/**/"");
	if(f!=NULL){
		f->TransmitDirectly(this);
	}
}