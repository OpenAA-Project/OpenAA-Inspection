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

#if	!defined(XDXFOperationCommon_H)
#define	XDXFOperationCommon_H

#include "XTypeDef.h"
#include <QColor>
#include "NListComp.h"
#include "XAlgorithmLibrary.h"
#include "XGeneralFunc.h"
#include "XIntClass.h"
#include "XAllocationLibByColor.h"

#define	DXFCommonDataID		1

class	ColorCodeList : public NPListSaveLoad<ColorCodeList>
{
public:
	IntList	ColorCode;
	QColor	Color;	//This is available in ColorCode==-1

	ColorCodeList(void){}
	ColorCodeList(int colorcode ,const QColor &col):Color(col){	ColorCode.Add(colorcode);	}
	ColorCodeList(IntList &colorcode ,const QColor &col):ColorCode(colorcode),Color(col){}

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

class	ColorCodeListContainer : public NPListPackSaveLoad<ColorCodeList>
{
public:
	ColorCodeListContainer(void){}

	virtual	ColorCodeList	*Create(void){	return new ColorCodeList();	}
	bool	IsExist(const QColor &Col);
	ColorCodeList	*Find(const QColor &Col);
};

inline	bool	ColorCodeList::Save(QIODevice *f)
{
	int32	Ver=1;
	if(::Save(f,Ver			)==false)	return false;
	if(ColorCode.Save(f)==false)		return false;
	if(::Save(f,Color		)==false)	return false;
	return true;
}
inline	bool	ColorCodeList::Load(QIODevice *f)
{
	int32	Ver;
	if(::Load(f,Ver			)==false)	return false;
	if(ColorCode.Load(f)==false)		return false;
	if(::Load(f,Color		)==false)	return false;
	return true;
}
inline	bool	ColorCodeListContainer::IsExist(const QColor &Col)
{
	for(ColorCodeList *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Color==Col)
			return true;
	}
	return false;
}
inline	ColorCodeList	*ColorCodeListContainer::Find(const QColor &Col)
{
	for(ColorCodeList *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Color==Col)
			return a;
	}
	return NULL;
}


#endif