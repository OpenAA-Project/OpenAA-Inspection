/*
 * Copyright (C) 2015
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

#include "XUnicodeGeneralFunc.h"
#include "XGeneralFunc.h"
#include<qstring.h>

bool	Save(QIODevice *f,wchar_t *d)
{
	QString	s=QString::fromWCharArray(d);
	return ::Save(f,s);
}
bool	Load(QIODevice *f,wchar_t *d,int64 &len ,int64 maxbuffsize)
{
	QString	dtmp;
	if(::Load(f,dtmp)==false){
		return false;
	}
	memset(d,0,sizeof(wchar_t)*maxbuffsize);
	len=dtmp.toWCharArray(d);
	d[len]=L'\0';
	return true;
}