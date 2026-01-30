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

#include "XLanguageCodec.h"
#include <QTextCodec>
#include <QFile>
#include "XGeneralFunc.h"

QString	LanguagePack::DefaultFileName		=/**/"LanguagePack.dat";

bool	LanguageClass::Save(QIODevice *f)
{
	if(::Save(f,ColumnNo)==false)
		return false;
	if(::Save(f,LanguageName)==false)
		return false;
	if(::Save(f,ExcelFont)==false)
		return false;
	if(::Save(f,QtCotec)==false)
		return false;
	return true;
}

bool	LanguageClass::Load(QIODevice *f)
{
	if(::Load(f,ColumnNo)==false)
		return false;
	if(::Load(f,LanguageName)==false)
		return false;
	if(::Load(f,ExcelFont)==false)
		return false;
	if(::Load(f,QtCotec)==false)
		return false;
	return true;
}


bool	LanguagePack::SaveDefault(void)
{
	QFile	File(DefaultFileName);
	if(File.open(QIODevice::WriteOnly)==false){
		return false;
	}
	if(Save(&File)==false){
		return false;
	}
	return true;
}

bool	LanguagePack::LoadDefault(void)
{
	QFile	File(DefaultFileName);
	if(File.open(QIODevice::ReadOnly)==false){
		return false;
	}
	if(Load(&File)==false){
		return false;
	}
	return true;
}

void	LanguagePack::AllocCodec(void)
{
	for(LanguageClass *c=GetFirst();c!=NULL;c=c->GetNext()){
		char	Buff[100];
		QString2Char(c->QtCotec,Buff ,sizeof(Buff));
		c->CurrentCodec= QTextCodec::codecForName(Buff);
	}
}

void	LanguagePack::SetCodec(int n)
{
	LanguageClass	*c=GetItem(n);
	if(c!=NULL){
		if(c->CurrentCodec!=NULL){
			//QTextCodec::setCodecForCStrings	(c->CurrentCodec);
			QTextCodec::setCodecForLocale	(c->CurrentCodec);
			//QTextCodec::setCodecForTr		(c->CurrentCodec);
		}
	}
}