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

#include "XServiceUpdater.h"
#include "XGeneralFuncCore.h"
#include <QFileInfo>

UpdatedFileList::UpdatedFileList(void)
{
	FileOperation= _Update;
}

UpdatedFileList::~UpdatedFileList(void)
{
}

bool	UpdatedFileList::Save(QIODevice* f)
{
	if (::Save(f, RelativeFileName) == false)	return false;
	if (::Save(f, FileStamp)		== false)	return false;
	return true;
}
bool	UpdatedFileList::Load(QIODevice* f)
{
	if (::Load(f, RelativeFileName) == false)	return false;
	if (::Load(f, FileStamp) == false)	return false;
	return true;
}

UpdatedFileList* UpdatedFileListContainer::Create(void)
{
	return new UpdatedFileList();
}

bool	UpdatedFileListContainer::LoadFromFileList(const QString& AbsPath,QTextStream& Txt)
{
	RemoveAll();
	while(Txt.atEnd()==false){
		QString	TxtLine=Txt.readLine(1000);

		if (TxtLine.left(8).toLower() == "#version"
		&& (TxtLine.length() >=9 && (TxtLine.at(8) == ' ' || TxtLine.at(8) == '\t'))) {
			Version = TxtLine.mid(9).trimmed();
		}
		else
		if(TxtLine.left(6).toLower()=="force"
		&& (TxtLine.length()>=6 && (TxtLine.at(5)==' ' || TxtLine.at(5)=='\t'))){
			QString	s= TxtLine.mid(6).trimmed();
			UpdatedFileList	*a=new UpdatedFileList();
			a->FileOperation= UpdatedFileList::_ForceUpdate;
			a->RelativeFileName=s;
			QFileInfo	FInfo(AbsPath+::GetSeparator()+s);
			if(FInfo.exists()==true){
				a->FileStamp	=FInfo.lastModified();
				AppendList(a);
			}
			else{
				delete	a;
			}
		}
		else
		if(TxtLine.left(6).toLower()=="del"
		&& (TxtLine.length()>=4 && (TxtLine.at(3)==' ' || TxtLine.at(3)=='\t'))){
			QString	s= TxtLine.mid(4).trimmed();
			UpdatedFileList	*a=new UpdatedFileList();
			a->FileOperation= UpdatedFileList::_Delete;
			a->RelativeFileName=s;
			AppendList(a);
		}
		else{
			QString	s=TxtLine;
			UpdatedFileList* a=new UpdatedFileList();
			a->FileOperation=UpdatedFileList::_Update;
			a->RelativeFileName=s;
			QFileInfo	FInfo(AbsPath + ::GetSeparator() + s);
			if (FInfo.exists()==true) {
				a->FileStamp = FInfo.lastModified();
				AppendList(a);
			}
			else {
				delete	a;
			}
		}
	}
	return true;
}

bool	UpdatedFileListContainer::SaveFileList(const QString& AbsPath, QTextStream& Txt)
{
	Txt <<"#version ";
	Txt <<Version;
	Txt <<"\n";
	for (UpdatedFileList* s = GetFirst(); s != NULL; s = s->GetNext()) {
		if(s->FileOperation== UpdatedFileList::_Delete){
			Txt<<"del ";
			Txt<<s->RelativeFileName;
			Txt<<"\n";
		}
		else
		if (s->FileOperation == UpdatedFileList::_ForceUpdate) {
			Txt << "force ";
			Txt << s->RelativeFileName;
			Txt << "\n";
		}
		else{
			Txt << s->RelativeFileName;
			Txt << "\n";
		}
	}
}

UpdatedFileListContainer& UpdatedFileListContainer::operator=(const UpdatedFileListContainer& src)
{
	Version=src.Version;
	RemoveAll();
	for(UpdatedFileList *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		UpdatedFileList	*d=new UpdatedFileList();
		*d=*s;
		AppendList(d);
	}
	return *this;
}

bool	UpdatedFileListContainer::Save(QIODevice* f)
{
	if(::Save(f, Version)==false)	return false;
	return NPListPackSaveLoad<UpdatedFileList>::Save(f);
}
bool	UpdatedFileListContainer::Load(QIODevice* f)
{
	if (::Load(f, Version) == false)	return false;
	return NPListPackSaveLoad<UpdatedFileList>::Load(f);
}