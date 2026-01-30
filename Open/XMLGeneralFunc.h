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

#if	!defined(XMLGeneralFunc_h)
#define	XMLGeneralFunc_h

#include <QString>
#include "XUnicodeGeneralFunc.h"
#include "XTypeDef.h"

wchar_t	*SkipSpace(wchar_t *fp);
QString	WChat2QString(wchar_t *src);
wchar_t	*CutWord(wchar_t *fp ,wchar_t *dest,int MaxDestLen);
wchar_t	*CutWordContent(wchar_t *fp ,wchar_t *dest,int MaxDestLen);
bool	IsDigit(wchar_t *fp ,double &RetNumber);

bool	GetXMLAttrStr (const QString &XMLSentense ,const QString &AttrName ,QString &RetAttrValue);
bool	GetXMLAttrInt (const QString &XMLSentense ,const QString &AttrName ,int &RetValue);
bool	GetXMLValueStr(const QString &XMLSentense ,const QString &TagName ,QString &RetTagValue);
bool	GetXMLCountValue(const QString &XMLSentense ,const QString &TagName ,int &RetCount);
	//<COUNT="90"/> �̂悤�Ȓl���擾

#endif