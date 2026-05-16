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

#include "XMLGeneralFunc.h"
#include <QtXml/QDomElement>

wchar_t	*SkipSpace(wchar_t *fp)
{
	while(*fp==L' ' || *fp==L'\t' || *fp==L'\n'){
		fp++;
	}
	return fp;
}

QString	WChat2QString(wchar_t *src)
{
	QString	ret;
	while(*src!=L'\0'){
		if(*src==L'\''){
			ret+=QString("\\\'");
		}
		else if(*src==L'\"'){
			ret+=QString("\\\"");
		}
		else if(*src==L'\\'){
			ret+=QString("\\\\'");
		}
		else{
			ret += QString::fromWCharArray(src,1);
		}
		src++;
	}
	return ret;
}


wchar_t	*CutWord(wchar_t *fp ,wchar_t *dest ,int MaxDestLen)
{
	int	DestLen=0;
	if(*fp=='\"'){
		fp++;
		while(*fp!=L'\0'){
			if(*fp==L'\"'){
				*dest=L'\0';
				fp++;
				return fp;
			}
			if(*fp==L'\\'){
				fp++;
			}
			*dest=*fp;
			fp++;
			dest++;
			DestLen++;
			if((DestLen+1)>=MaxDestLen){
				*dest=L'\0';
				return fp;
			}
		}
		*dest=L'\0';
	}
	else if(*fp=='\''){
		fp++;
		while(*fp!=L'\0'){
			if(*fp==L'\''){
				*dest=L'\0';
				fp++;
				return fp;
			}
			if(*fp==L'\\'){
				fp++;
			}
			*dest=*fp;
			fp++;
			dest++;
			DestLen++;
			if((DestLen+1)>=MaxDestLen){
				*dest=L'\0';
				return fp;
			}
		}
		*dest=L'\0';
	}
	else{
		while(*fp!=L'\0'){
			const wchar_t	*k=wcschr(L" \t=!<>,/\n",*fp);
			if(k!=NULL){
				*dest=L'\0';
				return fp;
			}
			*dest=*fp;
			fp++;
			dest++;
			DestLen++;
			if((DestLen+1)>=MaxDestLen){
				*dest=L'\0';
				return fp;
			}
		}
		*dest=L'\0';
	}
	return fp;
}

wchar_t	*CutWordContent(wchar_t *fp ,wchar_t *dest,int MaxDestLen)
{
	int	DestLen=0;
	if(*fp=='\"'){
		fp++;
		while(*fp!=L'\0'){
			if(*fp==L'\"'){
				*dest=L'\0';
				fp++;
				return fp;
			}
			if(*fp==L'\\'){
				fp++;
			}
			*dest=*fp;
			fp++;
			dest++;
			DestLen++;
			if((DestLen+1)>=MaxDestLen){
				*dest=L'\0';
				return fp;
			}
		}
		*dest=L'\0';
	}
	else if(*fp=='\''){
		fp++;
		while(*fp!=L'\0'){
			if(*fp==L'\''){
				*dest=L'\0';
				fp++;
				return fp;
			}
			if(*fp==L'\\'){
				fp++;
			}
			*dest=*fp;
			fp++;
			dest++;
			DestLen++;
			if((DestLen+1)>=MaxDestLen){
				*dest=L'\0';
				return fp;
			}
		}
		*dest=L'\0';
	}
	else{
		while(*fp!=L'\0'){
			const wchar_t	*k=wcschr(L"<",*fp);
			if(k!=NULL){
				*dest=L'\0';
				return fp;
			}
			*dest=*fp;
			fp++;
			dest++;
			DestLen++;
			if((DestLen+1)>=MaxDestLen){
				*dest=L'\0';
				return fp;
			}
		}
		*dest=L'\0';
	}
	return fp;
}

static	int GetDigit(wchar_t *fp ,double &RetNumber)
{
	int	Ret=0;
	RetNumber=0.0;
	while(*fp!=L'\0'){
		const wchar_t	*k=wcschr(L"0123456789",*fp);
		if(k==NULL){
			return Ret;
		}
		RetNumber*=10.0;
		RetNumber+=(int)(*fp-L'0');
		Ret++;
		fp++;
	}
	return Ret;
}

static	int GetDigit(wchar_t *fp ,int &RetNumber)
{
	int	Ret=0;
	RetNumber=0.0;
	while(*fp!=L'\0'){
		const wchar_t	*k=wcschr(L"0123456789",*fp);
		if(k==NULL){
			return Ret;
		}
		RetNumber*=10;
		RetNumber+=(int)(*fp-L'0');
		Ret++;
		fp++;
	}
	return Ret;
}


static	int IsSmall(wchar_t *fp ,double &RetNumber)
{
	int	Ret=0;
	RetNumber=0;
	double	Mask=0.1;
	while(*fp!=L'\0'){
		const wchar_t	*k=wcschr(L"0123456789",*fp);
		if(k==NULL){
			return Ret;
		}
		RetNumber+=Mask*(*fp-L'0');
		Mask *=0.1;
		Ret++;
		fp++;
	}
	return Ret;
}

bool	IsDigit(wchar_t *fp ,double &RetNumber)
{
	double	Sign=1.0;
	RetNumber	=0.0;
	if(*fp==L'+'){
		fp++;
	}
	else if(*fp==L'-'){
		Sign=-1.0;
		fp++;
	}
	double	L1=0.0;
	double	RetSmall=0.0;
	int	n=GetDigit(fp ,L1);
	fp+=n;
	if(*fp==L'.'){
		fp++;
		int	nn=IsSmall(fp,RetSmall);
		fp+=nn;
	}
	if((n!=0 || RetSmall!=0.0) && (*fp==L'e' || *fp==L'E')){
		double	eSign=1.0;
		fp++;
		if(*fp==L'+'){
			fp++;
		}
		else if(*fp==L'-'){
			eSign=-1.0;
			fp++;
		}
		double	L2;
		int	m=GetDigit(fp ,L2);
		fp+=m;
		if(*fp==L'\0' && m>0){
			RetNumber=L1+RetSmall;
			RetNumber=RetNumber*pow(10.0,L2*eSign);
			RetNumber*=Sign;
			return true;
		}
		return false;
	}
	if((n!=0 || RetSmall!=0.0) && *fp==L'\0'){
		RetNumber=L1+RetSmall;
		RetNumber*=Sign;
		return true;
	}
	return false;
}

QString	FromWChar(wchar_t *src ,int MaxLen)
{
	QString	Ret;
	for(int i=0;i<MaxLen;i++){
		if(*src==L'\0')
			return Ret;
		QChar	a(*src);
		if(a.isLetterOrNumber()==true || a.isSpace()==true || a.isPunct()==true){
			Ret+=a;
		}
		src++;
	}
	return Ret;
}

//===============================================================================================================
bool SearchXMLAttr(const QDomElement &elem, const QString &TagName, const QString &AttrName, QString &RetAttrValue)
{
	if((TagName.isEmpty() || elem.tagName()==TagName) && elem.hasAttribute(AttrName)==true){// TagName�����̏ꍇ�͍ŏ��̑����l���Ԃ�
		RetAttrValue = elem.attribute(AttrName);
		return true;
	}
	if(elem.hasChildNodes()==false){// �q�m�[�h�������Ȃ��ꍇ�͏I��
		return false;
	}
	for(QDomElement e = elem.firstChildElement(); !e.isNull(); e = e.nextSiblingElement()){// �q�m�[�h����
		if(SearchXMLAttr(e, TagName, AttrName, RetAttrValue)==true){// �ċA����
			return true;
		}
	}
	return false;
}
bool SearchXMLText(const QDomElement &elem, const QString &TagName, QString &RetAttrValue)
{
	if(TagName.isEmpty() || elem.tagName()==TagName){// TagName�����̏ꍇ�͍ŏ��̑����l���Ԃ�
		RetAttrValue = elem.firstChild().toText().data();
		return true;
	}
	if(elem.hasChildNodes()==false){// �q�m�[�h�������Ȃ��ꍇ�͏I��
		return false;
	}
	for(QDomElement e = elem.firstChildElement(); !e.isNull(); e = e.nextSiblingElement()){// �q�m�[�h����
		if(SearchXMLText(e, TagName, RetAttrValue)==true){// �ċA����
			return true;
		}
	}
	return false;
}

bool	GetXMLAttrStr (const QString &XMLSentense ,const QString &_AttrName ,QString &RetAttrValue)
{
	QDomDocument doc;
	if (!doc.setContent(XMLSentense)) {
		return false;
	}

	QDomElement elem = doc.documentElement();
	if(SearchXMLAttr(elem, "", _AttrName, RetAttrValue)){
		return true;
	}else{
		return false;
	}

	int	Len=XMLSentense.count();
	wchar_t	XMLSentense_AutoBuff[4096];
	wchar_t	*pSentense;
	if(Len>=4000){
		pSentense=new wchar_t[Len+2];
		memset(pSentense,0,sizeof(wchar_t)*(Len+2));
	}
	else{
		pSentense=XMLSentense_AutoBuff;
	}
	memset(pSentense,0,sizeof(wchar_t)*(Len+2));
	XMLSentense.toWCharArray(pSentense);

	bool	Ret=false;
	wchar_t TagName[8192];
	wchar_t AttrName[8192];
	wchar_t Dest[8192];
	wchar_t	*fp=pSentense;

	while(*fp!=L'\0' && fp!=NULL){
		fp=CutWord(fp ,TagName,sizeof(TagName));
		if(fp==NULL){
			Ret=false;
			goto	EndFunc;
		}
		if(TagName[0]==L'<'){
			fp=CutWord(fp ,TagName,sizeof(TagName));
			if(fp==NULL){
				Ret=false;
				goto	EndFunc;
			}
			while(*fp!=L'\0' && fp!=NULL){
				fp=CutWord(fp ,AttrName,sizeof(AttrName));
				if(fp==NULL){
					Ret=false;
					goto	EndFunc;
				}
				if(AttrName[0]==L'>'){
					break;
				}
				fp=SkipSpace(fp);
				if(*fp=='='){
					fp=CutWord(fp ,Dest,sizeof(Dest));
					if(fp==NULL){
						Ret=false;
						goto	EndFunc;
					}
				}
				if(_AttrName==QString::fromWCharArray(AttrName)){
					RetAttrValue=QString::fromWCharArray(Dest);
					Ret=true;
					goto	EndFunc;
				}
			}
		}
	}
	EndFunc:;
	if(pSentense!=XMLSentense_AutoBuff){
		delete	[]pSentense;
	}
	return Ret;
}
bool	GetXMLAttrInt (const QString &XMLSentense ,const QString &_AttrName ,int &RetValue)
{
	int	Len=XMLSentense.count();
	wchar_t	XMLSentense_AutoBuff[4096];
	wchar_t	*pSentense;
	if(Len>=4080){
		pSentense=new wchar_t[Len+2];
		memset(pSentense,0,sizeof(wchar_t)*(Len+2));
	}
	else{
		pSentense=XMLSentense_AutoBuff;
		memset(pSentense,0,sizeof(XMLSentense_AutoBuff));
	}
	XMLSentense.toWCharArray(pSentense);

	bool	Ret=false;
	wchar_t TagName[8192];
	wchar_t AttrName[8192];
	wchar_t Dest[8192];
	wchar_t	*fp=pSentense;
	QString	S;

	while(*fp!=L'\0' && fp!=NULL){
		if(*fp==L'<'){
			fp++;
			fp=SkipSpace(fp);
		}
		wchar_t	*gp=CutWord(fp ,TagName,sizeof(TagName));
		if(gp==NULL){
			Ret=false;
			goto	EndFunc;
		}
		if(gp==fp){
			fp++;
			continue;
		}
		fp=gp;
		fp=SkipSpace(fp);
		while(*fp!=L'\0' && fp!=NULL){
			gp=CutWord(fp ,AttrName,sizeof(AttrName));
			if(gp==NULL){
				Ret=false;
				goto	EndFunc;
			}
			if(gp==fp){
				fp++;
				continue;
			}
			fp=gp;
			if(fp==NULL){
				Ret=false;
				goto	EndFunc;
			}
			if(*fp==L'>'){
				break;
			}
			if(AttrName[0]==0){
				fp++;
				continue;
			}
			fp=SkipSpace(fp);
			if(*fp=='='){
				fp++;
				fp=SkipSpace(fp);
				gp=CutWord(fp ,Dest,sizeof(Dest));
				if(gp==NULL){
					Ret=false;
					goto	EndFunc;
				}
				if(gp==fp){
					fp++;
					continue;
				}
				fp=gp;
			}
			//if(_AttrName==QString::fromWCharArray(AttrName)){		Error occurs
			S=FromWChar(AttrName,sizeof(AttrName));
			if(_AttrName==S){
				bool	ok;
				//RetValue=QString::fromWCharArray(Dest).toInt(&ok);
				RetValue=FromWChar(Dest,sizeof(Dest)).toInt(&ok);
				if(ok==true){
					Ret=true;
				}
				else{
					Ret=false;
				}
				goto	EndFunc;
			}
		}
	}
	EndFunc:;
	if(pSentense!=XMLSentense_AutoBuff){
		delete	[]pSentense;
	}
	return Ret;
}
bool	GetXMLValueStr(const QString &XMLSentense ,const QString &_TagName ,QString &RetTagValue)
{
	QDomDocument doc;
	if(!doc.setContent(XMLSentense)){
		return false;
	}
	QDomElement elem = doc.documentElement();
	if(SearchXMLText(elem, _TagName, RetTagValue)){
		return true;
	}else{
		return false;
	}

	int	Len=XMLSentense.count();
	wchar_t	XMLSentense_AutoBuff[4096];
	wchar_t	*pSentense;
	if(Len>=4000){
		pSentense=new wchar_t[Len+2];
	}
	else{
		pSentense=XMLSentense_AutoBuff;
	}
	memset(pSentense,0,sizeof(wchar_t)*(Len+2));
	XMLSentense.toWCharArray(pSentense);

	bool	Ret=false;
	wchar_t TagName[8192];
	wchar_t AttrName[8192];
	wchar_t Dest[8192];
	wchar_t	*fp=pSentense;

	while(*fp!=L'\0' && fp!=NULL){
		fp=CutWord(fp ,TagName,sizeof(TagName));
		if(fp==NULL){
			Ret=false;
			goto	EndFunc;
		}
		if(TagName[0]==L'<'){
			fp=CutWord(fp ,TagName,sizeof(TagName));
			if(fp==NULL){
				Ret=false;
				goto	EndFunc;
			}
			for(;;){
				fp=CutWord(fp ,AttrName,sizeof(AttrName));
				if(fp==NULL){
					Ret=false;
					goto	EndFunc;
				}
				if(AttrName[0]==L'>'){
					break;
				}
			}
			fp=CutWord(fp ,Dest,sizeof(Dest));
			if(fp==NULL){
				Ret=false;
				goto	EndFunc;
			}
			if(Dest[0]!=L'<'){
				if(_TagName ==QString::fromWCharArray(TagName)){
					RetTagValue=QString::fromWCharArray(Dest);
					Ret=true;
					goto	EndFunc;
				}
			}
		}
	}
	EndFunc:;
	if(pSentense!=XMLSentense_AutoBuff){
		delete	[]pSentense;
	}
	return Ret;
}

bool	GetXMLCountValue(const QString &XMLSentense ,const QString &_TagName ,int &RetCount)
{
	int	Len=XMLSentense.count();
	wchar_t	XMLSentense_AutoBuff[4096];
	wchar_t	*pSentense;
	if(Len>=4000){
		pSentense=new wchar_t[Len+2];
	}
	else{
		pSentense=XMLSentense_AutoBuff;
	}
	memset(pSentense,0,sizeof(wchar_t)*(Len+2));
	XMLSentense.toWCharArray(pSentense);

	bool	Ret=false;
	wchar_t TagName[8192];
	wchar_t AttrName[8192];
	wchar_t Dest[8192];
	wchar_t	*fp=pSentense;

	while(*fp!=L'\0' && fp!=NULL){
		fp=CutWord(fp ,TagName,sizeof(TagName));
		if(fp==NULL){
			Ret=false;
			goto	EndFunc;
		}
		if(TagName[0]==L'<'){
			for(;;){
				fp=CutWord(fp ,AttrName,sizeof(AttrName));
				if(fp==NULL){
					Ret=false;
					goto	EndFunc;
				}
				if(AttrName[0]==L'>'){
					break;
				}
				fp=SkipSpace(fp);
				if(*fp=='='){
					fp=CutWord(fp ,Dest,sizeof(Dest));
					if(fp==NULL){
						Ret=false;
						goto	EndFunc;
					}
				}
				if(_TagName==QString::fromWCharArray(AttrName)){
					if(GetDigit(Dest,RetCount)>0){
						Ret=true;
						goto	EndFunc;
					}
				}
			}
		}
	}
	EndFunc:;
	if(pSentense!=XMLSentense_AutoBuff){
		delete	[]pSentense;
	}
	return Ret;
}
