/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\XML\MTXMLServer\MTXMLLib\MTXMLLib.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "MTXMLLib.h"
#include <ctype.h>
#include <QBuffer>
#include "XGeneralFunc.h"
#include <omp.h>
#include "XLogOut.h"
#include <QDomDocument>
#include <QTextCodec>

//LogOutClass	LogData("C:\\LogFile.txt");


QTime	Timer;
StringStoker		XMLMainStock::StrStocker;


StringStokerItem::StringStokerItem(void)
{
	Str=NULL;
	IndexCount=0;
}

StringStokerItem::StringStokerItem(char *str)
{
	int	len=strlen(str);
	Str=new char[len+1];
	strcpy(Str,str);
	IndexCount=0;
}

StringStokerItem::~StringStokerItem(void)
{
	delete	[]Str;
	Str=NULL;
}


StringStokerItem	*StringStoker::GetItem(char *str)
{
	if(str!=NULL){
		int	C;
		if(*str==0){
			C=0;
		}
		else{
			C=*((WORD *)str);
		}
		DataMutex.lock();
		for(StringStokerItem *s=Data[C].GetFirst();s!=NULL;s=s->GetNext()){
			if(strcmp(s->GetString(),str)==0){
				s->IndexCount++;
				DataMutex.unlock();
				return s;
			}
		}
		DataMutex.unlock();
		StringStokerItem *d=new StringStokerItem(str);

		DataMutex.lock();
		Data[C].AppendList(d);
		DataMutex.unlock();
		return d;
	}
	return NULL;
}
StringStokerItem	*StringStoker::GetItem(QString &str)
{
	int	Len=str.length()*2+2;
	char	*tmp=new char [Len];
	QString2Char(str ,tmp ,Len);
	StringStokerItem	*s=GetItem(tmp);
	delete	[]tmp;
	return s;
}

StringStokerItem	*StringStoker::RemoveReference(StringStokerItem *ref)
{
	if(ref!=NULL){
		DataMutex.lock();
		ref->IndexCount--;
		if(ref->IndexCount<0){
			int	C;
			if(*ref->GetString()==0)
				C=0;
			else
				C=*((WORD *)ref->GetString());

			Data[C].RemoveList(ref);
			DataMutex.unlock();

			delete	ref;
			return NULL;
		}
		DataMutex.unlock();
	}
	return ref;
}

StringStokerItem	*StringStoker::GetPointer(StringStokerItem *nowpointer)
{
	if(nowpointer!=NULL){
		DataMutex.lock();
		nowpointer->IndexCount++;
		DataMutex.unlock();
		return nowpointer;
	}
	return NULL;
}

//======================================================================================

static	char	*SkipSpace(char *fp)
{
	while(*fp==' ' || *fp=='\t' || *fp=='\n')
		fp++;
	return fp;
}

static	char	*CutWord(char *fp, char Buff[] ,int BuffSize)
{
	for(int i=0;i<BuffSize-1;i++,fp++){
		if(*fp=='\0')
			return NULL;
		if(isalnum(*fp)!=0 || *fp=='_' || *fp==':')
			Buff[i]=*fp;
		else if(strchr(" \t=\"<>\n\r",*fp)!=NULL){
			Buff[i]=0;
			return fp;
		}
	}
	return NULL;
}

//=================================================================
XMLTagAttr::~XMLTagAttr(void)
{
	AttrName=XMLMainStock::GetStringStoker().RemoveReference(AttrName);
	AttrName=NULL;
	if(IsNumOK==false){
		AttrData=XMLMainStock::GetStringStoker().RemoveReference(AttrData);
		AttrData=NULL;
	}
}
char	*XMLTagAttr::Analyze(char *fp)
{
	fp=SkipSpace(fp);
	char	buff[1000];
	fp=CutWord(fp,buff ,sizeof(buff));
	if(fp==NULL)
		return NULL;

	XMLMainStock::GetStringStoker().RemoveReference(AttrName);
	AttrName=XMLMainStock::GetStringStoker().GetItem(buff);

	fp=SkipSpace(fp);
	int iLen;
	/*if(*fp!='=')			//不等号の判断
		return NULL;
	iLen=1;*/
	if(*fp=='=' ){		//不等号の判断
		iLen=1;
		CompareType=_Equal;
	}else if( *fp=='>' && *(fp+1)=='=' ){
		iLen=2;
		CompareType=_GreaterEqual;
	}else if(*fp=='<' && *(fp+1)=='='){
		iLen=2;
		CompareType=_SmallEqual;
	}else if(*fp=='>'){
		iLen=1;
		CompareType=_Greater;
	}else if(*fp=='<'){
		iLen=1;
		CompareType=_Small;
	}else{
		return NULL;
	}
	fp+=iLen;
	fp=SkipSpace(fp);
	if(*fp!='\"')
		return NULL;
	fp++;
	char	*cp=strchr(fp,'\"');
	if(cp==NULL)
		return NULL;
	int	Len=cp-fp;
	if(Len>sizeof(buff))
		return NULL;
	strncpy(buff,fp,Len);
	buff[Len]=0;

	fp=buff;
	while(*fp=='0' && *(fp+1)!=0)
		fp++;

	qint64	siAttrData=::StringToLongLong(fp ,IsNumOK);
	if(IsNumOK==false){
		AttrData=XMLMainStock::GetStringStoker().RemoveReference(AttrData);
		AttrData=NULL;
		AttrData=XMLMainStock::GetStringStoker().GetItem(buff);
	}
	else{
		iAttrData=siAttrData;
	}

	fp=cp+1;
	return fp;
}
int	XMLTagAttr::MakeStr(char buff[] ,int buffsize)
{
	if(IsNumOK==false){
		if(buffsize<strlen(AttrName->GetString())+4+strlen(AttrData->GetString()))
			return -1;
		//int	n=::QString2Char(AttrName,buff ,buffsize);
		strcpy(buff,AttrName->GetString());
		int	n=strlen(AttrName->GetString());

		if(CompareType==_Equal){
			buff[n]='=';
		}else if(CompareType==_GreaterEqual){
			buff[n]='>';
			n+=1;
			buff[n]='=';
		}else if(CompareType==_SmallEqual){
			buff[n]='<';
			n+=1;
			buff[n]='=';
		}else if(CompareType==_Greater){
			buff[n]='>';
		}else if(CompareType==_Small){
			buff[n]='<';
		}
		//buff[n]='=';
		buff[n+1]='\"';
		n+=2;
		//int	m=::QString2Char(AttrData,&buff[n] ,buffsize-n-2);
		//n+=m;
		if(AttrData!=NULL){
			strcpy(&buff[n],AttrData->GetString());
			int	m=strlen(AttrData->GetString());
			n+=m;
		}
		buff[n]='\"';
		buff[n+1]=0;
		return n+1;
	}
	else{
		QString	NStr=QString::number(iAttrData);
		if(buffsize<strlen(AttrName->GetString())+4+NStr.length())
			return -1;
		//int	n=::QString2Char(AttrName,buff ,buffsize);
		strcpy(buff,AttrName->GetString());
		int	n=strlen(AttrName->GetString());

		if(CompareType==_Equal){
			buff[n]='=';
		}else if(CompareType==_GreaterEqual){
			buff[n]='>';
			n+=1;
			buff[n]='=';
		}else if(CompareType==_SmallEqual){
			buff[n]='<';
			n+=1;
			buff[n]='=';
		}else if(CompareType==_Greater){
			buff[n]='>';
		}else if(CompareType==_Small){
			buff[n]='<';
		}
		//buff[n]='=';
		buff[n+1]='\"';
		n+=2;
		int	m=::QString2Char(NStr,&buff[n],buffsize-n-1);
		n+=m;
		buff[n]='\"';
		buff[n+1]=0;
		return n+1;
	}
}
bool	XMLTagAttr::Delete(void)
{
	//XMLMainStock	*p=GetTop();
	return true;
}

XMLTagAttr	&XMLTagAttr::operator=(XMLTagAttr &src)
{
	XMLMainStock::GetStringStoker().RemoveReference(AttrName);
	AttrName=XMLMainStock::GetStringStoker().GetItem(src.AttrName->GetString());
	IsNumOK		=src.IsNumOK;
	if(IsNumOK==false){
		XMLMainStock::GetStringStoker().RemoveReference(AttrData);
		AttrData=XMLMainStock::GetStringStoker().GetPointer(src.AttrData);
	}
	else{
		iAttrData	=src.iAttrData;
	}
	CompareType	=src.CompareType;
	return *this;
}
bool	XMLTagAttr::operator==(XMLTagAttr &src)
{
   return false;
}
bool	XMLTagAttr::hCompare(XMLTagAttr &src)
{
	//if(AttrName	!=src.AttrName)
	//	return false;
	if(AttrName==NULL)
		return false;
	if(src.AttrName==NULL)
		return false;
	if(strcmp(AttrName->GetString(), src.AttrName->GetString())!=0)
		return false;

	if(CompareType==src._Equal){
		if(IsNumOK==false || src.IsNumOK==false ){
			if(IsNumOK==true)
				return false;
			if(AttrData==NULL)
				return false;
			if(src.AttrData==NULL)
				return false;
			if(strcmp(src.AttrData->GetString(),AttrData->GetString())==0)
				return true;
			if(strcmp(AttrData->GetString(), "*")==0)
				return true;
		}else{
			if(iAttrData==src.iAttrData)
				return true;
		}
	}else if(CompareType==_GreaterEqual){
		if(IsNumOK==true && src.IsNumOK==true){
			if(iAttrData<=src.iAttrData)
				return true;
		}
	}else if(CompareType==_SmallEqual){
		if(IsNumOK==true && src.IsNumOK==true){
			if(iAttrData>=src.iAttrData)
				return true;
		}
	}else if(CompareType==_Greater){
		if(IsNumOK==true && src.IsNumOK==true){
			if(iAttrData<src.iAttrData)
				return true;
		}
	}else if(CompareType==_Small){
		if(IsNumOK==true && src.IsNumOK==true){
			if(iAttrData>src.iAttrData)
				return true;
		}
	}
	return false;
}
/*
bool	XMLTagAttr::operator>(XMLTagAttr &src)
{
	if(AttrName	!=src.AttrName)
		return false;
	if(iAttrData	>src.iAttrData)
		return true;
	return false;
}
bool	XMLTagAttr::operator>=(XMLTagAttr &src)
{
	if(AttrName	!=src.AttrName)
		return false;
	if(iAttrData	>=src.iAttrData)
		return true;
	return false;
}
bool	XMLTagAttr::operator<(XMLTagAttr &src)
{
	if(AttrName	!=src.AttrName)
		return false;
	if(iAttrData	<src.iAttrData)
		return true;
	return false;
}
bool	XMLTagAttr::operator<=(XMLTagAttr &src)
{
	if(AttrName	!=src.AttrName)
		return false;
	if(iAttrData	<=src.iAttrData)
		return true;
	return false;
}
*/
XMLMainStock	*XMLTagAttr::GetTop()
{
	XMLElement	*p=Parent->Parent;
	while(p->Parent!=NULL)
		p=p->Parent;
	return dynamic_cast<XMLMainStock *>(p);
}

int		XMLTagAttr::Size(void)
{
	if(IsNumOK==false){
		if(AttrName==NULL){
			if(AttrData==NULL){
				return	sizeof(iAttrData)
						+sizeof(IsNumOK)
						+sizeof(CompareType)
						+8;
			}else{
				return	strlen(AttrData->GetString())
						+sizeof(iAttrData)
						+sizeof(IsNumOK)
						+sizeof(CompareType)
						+8;
			}
		}else{
			if(AttrData==NULL){
				return strlen(AttrName->GetString())
					   +sizeof(iAttrData)
					   +sizeof(IsNumOK)
					   +sizeof(CompareType)
					   +8;
			}
		}
		return strlen(AttrName->GetString())
			+strlen(AttrData->GetString())
			   +sizeof(iAttrData)
			   +sizeof(IsNumOK)
			   +sizeof(CompareType)
			   +8;
	}
	else{
		if(AttrName==NULL){
			return	sizeof(iAttrData)
					+sizeof(IsNumOK)
					+sizeof(CompareType)
					+8;
		}else{
			return strlen(AttrName->GetString())
				   +sizeof(iAttrData)
				   +sizeof(IsNumOK)
				   +sizeof(CompareType)
				   +8;
		}
	}
}
bool	XMLTagAttr::Save(QIODevice &Buff)
{
	bool	NullName;
	if(AttrName==NULL)
		NullName=true;
	else
		NullName=false;
	if(::Save(&Buff,NullName)==false)
		return false;
	if(AttrName!=NULL){
		if(::Save(&Buff,AttrName->GetString())==false)
			return false;
	}
	if(::Save(&Buff,IsNumOK)==false)
		return false;
	if(IsNumOK==false){
		bool	NullData;
		if(AttrData==NULL)
			NullData=true;
		else
			NullData=false;
		if(::Save(&Buff,NullData)==false)
			return false;
		if(AttrData!=NULL){
			if(::Save(&Buff,AttrData->GetString())==false)
				return false;
		}
	}
	else{
		if(::Save(&Buff,iAttrData)==false)
			return false;
	}
	return true;
}
bool	XMLTagAttr::Load(QIODevice &Buff)
{
	bool	NullName;
	if(::Load(&Buff,NullName)==false)
		return false;

	if(NullName==false){
		char	*tmpAttrName=LoadString(&Buff);
		XMLMainStock::GetStringStoker().RemoveReference(AttrName);
		AttrName=XMLMainStock::GetStringStoker().GetItem(tmpAttrName);
		delete	[]tmpAttrName;
	}else{
		AttrName=NULL;
	}

	if(::Load(&Buff,IsNumOK)==false)
		return false;
	if(IsNumOK==false){
		bool	NullData;
		if(::Load(&Buff,NullData)==false)
			return false;

		if(NullData==false){
			char	*tmpAttrData=LoadString(&Buff);
			XMLMainStock::GetStringStoker().RemoveReference(AttrData);
			AttrData=XMLMainStock::GetStringStoker().GetItem(tmpAttrData);
			delete	[]tmpAttrData;
		}else{
			AttrData=NULL;
		}
	}
	else{
		if(::Load(&Buff,iAttrData)==false)
			return false;
	}
	CompareType=_Equal;
	return true;
}

//=================================================================
XMLTag::~XMLTag(void)
{
	TagName=XMLMainStock::GetStringStoker().RemoveReference(TagName);
	TagName=NULL;
}
char	*XMLTag::Analyze(char *fp ,bool &Finished)
{
	fp=SkipSpace(fp);
	if(*fp!='<')
		return NULL;
	fp++;
	fp=SkipSpace(fp);
	char	buff[1000];
	fp=CutWord(fp,buff ,sizeof(buff));
	if(fp==NULL)
		return NULL;

	XMLMainStock::GetStringStoker().RemoveReference(TagName);
	TagName=XMLMainStock::GetStringStoker().GetItem(buff);

	fp=SkipSpace(fp);
	while(*fp!='>' && strncmp(fp,"/>",2)!=0){
		XMLTagAttr	*p=new XMLTagAttr(this);
		fp=p->Analyze(fp);
		if(fp==NULL)
			return NULL;
		Attrs.AppendList(p);
		fp=SkipSpace(fp);
	}
	if(*fp=='>'){
		Finished=false;
		fp++;
		return fp;
	}
	if(strncmp(fp,"/>",2)==0){
		Finished=true;
		fp+=2;
		return fp;
	}
	return NULL;
}
int	XMLTag::MakeStr(char buff[] ,int buffsize)
{
	if(buffsize<3)
		return -1;
	buff[0]='<';
	buffsize--;
	if(TagName==NULL)
		return -1;
	strcpy(&buff[1],TagName->GetString());
	int	n=strlen(TagName->GetString());
	n+=1;
	for(XMLTagAttr *r=Attrs.GetFirst();r!=NULL;r=r->GetNext()){
		if(buffsize<=0)
			return -1;
		buff[n]=' ';
		buffsize--;
		n++;
		int	m=r->MakeStr(&buff[n],buffsize);
		if(m<0)
			return -1;
		n+=m;
		buffsize-=m;
		if(buffsize<=0)
			return -1;
	}
	if(buffsize<2)
		return -1;
	buff[n]='>';
	buff[n+1]=0;

	return n+1;
}
bool	XMLTag::Delete(void)
{
	for(XMLTagAttr *s=Attrs.GetFirst();s!=NULL;s=s->GetNext()){
		s->Delete();
	}
	return true;
}


XMLMainStock	*XMLTag::GetTop()
{
	XMLElement	*p=Parent;
	while(p->Parent!=NULL)
		p=p->Parent;
	return dynamic_cast<XMLMainStock *>(p);
}

XMLTag	&XMLTag::operator=(XMLTag &src)
{
	XMLMainStock::GetStringStoker().RemoveReference(TagName);
	TagName=XMLMainStock::GetStringStoker().GetItem(src.TagName->GetString());

	Attrs.RemoveAll();

	for(XMLTagAttr *s=src.Attrs.GetFirst();s!=NULL;s=s->GetNext()){
		XMLTagAttr *d=new XMLTagAttr(this);
		*d=*s;
		Attrs.AppendList(d);
	}
	return *this;
}
//bool	XMLTag::Match(XMLTag &MatchPoint)
bool	XMLTag::Match(XMLTag &MatchPoint,XMLElement *e)
{
	if(TagName==NULL)
		return false;
	//if(src.TagName==NULL)
	if(MatchPoint.TagName==NULL)
		return false;
	if(strcmp(MatchPoint.TagName->GetString(),"ANY")!=0 && strcmp(TagName->GetString(),MatchPoint.TagName->GetString())!=0)//ANY又は一致するタグ名があった時通過
		return false;
	for(XMLTagAttr *a=MatchPoint.Attrs.GetFirst();a!=NULL;a=a->GetNext()){//MachiPointからデータを渡す
		XMLTagAttr *b;
		for(b=Attrs.GetFirst();b!=NULL;b=b->GetNext()){//自分自身のデータを渡す
//			if(a->AttrSign=="="){
				//if(*a == *b){
			if( a->hCompare(*b)){//一つ目の条件を判断する
					if(e->Parent->GetTop()!=NULL){//XMLElementを取ってくる
						if(e->Parent->GetTop()->MatchXMLTag->count()==0)//データがある
							break;
						if(CheckNextTag(e->Parent,*(e->Parent->GetTop()->MatchXMLTag)))
							break;
					}
				}
/*			}
			else if(a->AttrSign==">"){
				if(*b>*a)
					break;
			}
			else if(a->AttrSign==">="){
				if(*b>=*a)
					break;
			}
			else if(a->AttrSign=="<"){
				if(*b<*a)
					break;
			}
			else if(a->AttrSign=="<="){
				if(*b<=*a)
					break;
			}
*/
		}
		if(b==NULL)
			return false;
	}
	return true;
}

bool	XMLTag::Matched(XMLTag &MatchPoint)
{
	if(TagName==NULL)
		return false;
	if(MatchPoint.TagName==NULL)
		return false;
	if(strcmp(MatchPoint.TagName->GetString(),"ANY")!=0 && strcmp(TagName->GetString(),MatchPoint.TagName->GetString())!=0)//ANY又は一致するタグ名があった時通過
		return false;
	for(XMLTagAttr *a=MatchPoint.Attrs.GetFirst();a!=NULL;a=a->GetNext()){//MachiPointからデータを渡す
		XMLTagAttr *b;
		for(b=Attrs.GetFirst();b!=NULL;b=b->GetNext()){//自分自身のデータを渡す
			if(a->hCompare(*b)==true){
				break;
			}
		}
		if(b==NULL){
			return false;
		}
	}
	return true;
}


int		XMLTag::Size(void)
{
	int iSize=0;
	for(XMLTagAttr *d=Attrs.GetFirst();d!=NULL;d=d->GetNext()){
		iSize=iSize+d->Size();
	}
	if(TagName==NULL)
		return	10
				+iSize;//+sizeof(qint64);*/
	return	strlen(TagName->GetString())*2
			+10
			+iSize;//+sizeof(qint64);*/
}

bool	XMLTag::Save(QIODevice &Buff)
{
	bool	NullData;
	if(TagName==NULL)
		NullData=true;
	else
		NullData=false;
	if(::Save(&Buff,NullData)==false)
		return false;
	if(TagName!=NULL){
		if(::Save(&Buff,TagName->GetString())==false)
			return false;
	}

	XMLTagAttr *d=Attrs.GetFirst();
	//int AAA=Attrs.GetNumber();
	if(::Save(&Buff,(int)Attrs.GetNumber())==false)
		return false;
	XMLTagAttr *Prev=NULL;
	for(d=Attrs.GetFirst();d!=NULL;d=d->GetNext()){
		if(d->Save(Buff)==false)
			return false;
		Prev=d;
	}
	return true;
}
bool	XMLTag::Load(QIODevice &Buff)
{
	bool	NullData;
	if(::Load(&Buff,NullData)==false)
		return false;
	if(NullData==false){
		char	*tmpTagName=LoadString(&Buff);
		XMLMainStock::GetStringStoker().RemoveReference(TagName);
		TagName=XMLMainStock::GetStringStoker().GetItem(tmpTagName);
		delete	[]tmpTagName;
	}else{
		TagName=NULL;
	}
	Attrs.RemoveAll();
	int	Count;
	if(::Load(&Buff,Count)==false)
		return false;

	for(int Cnt=0;Cnt<Count;Cnt++){
		XMLTagAttr *TagAttr=new XMLTagAttr(this);
		if(TagAttr->Load(Buff)==false)
			return false;
		Attrs.AppendList(TagAttr);
	}
	return true;
}

char	*XMLTag::GetTagName(void)
{
	if(TagName==NULL){
		return NULL;
	}
	return TagName->GetString();
}

bool	XMLTag::AddTag(XMLTag &Src)
{
	for(XMLTagAttr *a=Src.Attrs.GetFirst();a!=NULL;a=a->GetNext()){
		XMLTagAttr *b;
		for(b=Attrs.GetFirst();b!=NULL;b=b->GetNext()){
			if(strcmp(a->AttrName->GetString(),b->AttrName->GetString())==0){
				*b=*a;
				break;
			}
		}
		if(b==NULL){
			XMLTagAttr *k=new XMLTagAttr(this);
			*k=*a;
			Attrs.AppendList(k);
		}
	}
	return true;
}


bool	XMLTag::CheckNextTag(XMLElement *Src,QList<XMLTag*> MatchPoint)
//2つ目の条件を見る（引数1:　引数2：）
{
	for(int Cnt=0;Cnt<MatchPoint.count();Cnt++){
		for(XMLElement *E=Src->GetFirst();E!=NULL;E=E->GetNext()){
			for(XMLElement *E=Src->Datas.GetFirst();E!=NULL;E=E->GetNext()){
				if(E->StartTag.TagName==NULL)
					return false;
				if(MatchPoint.at(Cnt)->TagName==NULL)
					return false;
				if(strcmp(E->StartTag.TagName->GetString(),MatchPoint.at(Cnt)->TagName->GetString())==0){
					for(XMLTagAttr *TA=E->StartTag.Attrs.GetFirst();TA!=NULL;TA=TA->GetNext()){
						//if(TA->AttrName==MatchPoint.at(Cnt)->Attrs.GetFirst()->AttrName){
						if(TA->AttrName==NULL)
							return false;
						if(MatchPoint.at(Cnt)->Attrs.GetFirst()->AttrName==NULL)
							return false;
						if(strcmp(TA->AttrName->GetString(),MatchPoint.at(Cnt)->Attrs.GetFirst()->AttrName->GetString())==0){
							if( MatchPoint.at(Cnt)->Attrs.GetFirst()->hCompare(*TA))
							//XMLTagAttr *b;
							//for(b=MatchPoint.at(Cnt)->Attrs.GetFirst();b!=NULL;b=b->GetNext()){//自分自身のデータを渡す
							//	if( b->hCompare(*TA))
									return true;
							//}
						}
					}
				}
			}
		}
	}
	return false;
}

bool	XMLTag::FindTagAttr(XMLElement *Src,QString strTagName,QString strAttrName,QString &strRet)
{
	int	len=Src->Size();
	char	*buff=new char[len];
	Src->MakeStr(buff ,len);
	if(AnalyzeXMLElement(buff,strTagName,strAttrName,strRet)){
		delete []buff;
		return true;
	}
	delete []buff;
	return false;
}

bool	XMLTag::AnalyzeXMLElement(char *fp,QString strTagName,QString strAttrName,QString &strRet)
{
	for(;;){
		fp=SkipSpace(fp);
		if(fp==NULL)
			break;
		if(*fp!='<')
			break;
		if(*(fp+1)=='/')
			break;
		fp++;
		fp=SkipSpace(fp);
		char	buff[1000];
		fp=CutWord(fp,buff ,sizeof(buff));
		if(fp==NULL)
			break;

		//TagNameの比較
		if(strTagName!=buff){
			fp=GotoTagEnd(fp,buff);
			continue;
		}

		for(;;){
			//TagNameが合致したらAttrNameの比較
			fp=SkipSpace(fp);
			char	buff[1000];
			fp=CutWord(fp,buff ,sizeof(buff));
			if(fp==NULL)
				break;
			QString sAttrName=buff;
			fp=SkipSpace(fp);
			if(*fp!='=')
				break;
			fp++;
			fp=SkipSpace(fp);
			if(*fp!='\"')
				break;
			fp++;
			char	*cp=strchr(fp,'\"');
			if(cp==NULL)
				break;
			int	Len=cp-fp;
			if(Len>sizeof(buff))
				break;
			strncpy(buff,fp,Len);
			buff[Len]=0;
			strRet=buff;
			fp=cp+1;

			//AttrNameの比較
			if(sAttrName==strAttrName)
				return true;
		}
	}
	return false;
}

char	*XMLTag::GotoTagEnd(char *fp ,char *buff)
{
	while(*fp!='>' && strncmp(fp,"/>",2)!=0)
		fp++;
	if(strcmp(buff,"IST")==0)
		return ++fp;
	if(strncmp(fp,"/>",2)==0)
		return fp+=2;
	else
		fp++;

	while(*fp!='>' && strncmp(fp,"/>",2)!=0)
		fp++;
	if(strncmp(fp,"/>",2)==0)
		fp+=2;
	else
		fp++;
	return fp;
}

//=================================================================
XMLElement::XMLElement(XMLElement *parent):StartTag(this)
{
	Parent	=parent;
	ID		=0;
	InsertedNumb=0;
	StrData=NULL;
}
XMLElement::~XMLElement(void)
{
	StrData=XMLMainStock::GetStringStoker().RemoveReference(StrData);
	StrData=NULL;
}
char	*XMLElement::Analyze(char *fp)
{
	fp=SkipSpace(fp);
	bool	Finished;
	fp=StartTag.Analyze(fp,Finished);
	if(fp==NULL)
		return NULL;
	if(Finished==true)
		return fp;
	char	buff[1000];
	for(;;){
		if(*fp=='<'){
			if(*(fp+1)=='/'){
				fp+=2;
				fp=SkipSpace(fp);
				fp=CutWord(fp,buff ,sizeof(buff));
				if(fp==NULL)
					return NULL;
				fp=SkipSpace(fp);
				if(*fp!='>')
					return NULL;
				fp++;
				return fp;
			}
			else{
				XMLElement	*a;
				if(dynamic_cast<XMLElementWithIncrementalID *>(this)!=NULL)
					a=new XMLElementWithIncrementalID(this);
				else
					a=new XMLElement(this);

				fp=a->Analyze(fp);
				if(fp==NULL)
					return NULL;
				if(Datas.GetLast()!=NULL)
					a->InsertedNumb=Datas.GetLast()->InsertedNumb+1;
				else
					a->InsertedNumb=0;
				Datas.AppendList(a);
			}
		}
		else{
			buff[0]=0;
			for(int i=0;i<sizeof(buff)-1;i++){
				buff[i]=*fp;
				if(*fp=='<'){
					if(*(fp+1)=='/'){
						buff[i]=0;
						break;
					}
				}
				else if(*fp=='\n'){
					buff[i]='\n';
					i++;
					buff[i]=0;
					fp++;
					break;
				}
				fp++;
				if(*fp==0)
					return NULL;
			}
			XMLElement	*a;
			if(dynamic_cast<XMLElementWithIncrementalID *>(this)!=NULL)
				a=new XMLElementWithIncrementalID(this);
			else
				a=new XMLElement(this);

			XMLMainStock::GetStringStoker().RemoveReference(a->StrData);
			a->StrData=XMLMainStock::GetStringStoker().GetItem(buff);

			if(Datas.GetLast()!=NULL)
				a->InsertedNumb=Datas.GetLast()->InsertedNumb+1;
			else
				a->InsertedNumb=0;
			Datas.AppendList(a);
		}
	}
}

int	XMLElement::MakeStr(char buff[], int buffsize)
{
	if(StartTag.TagName==NULL || strlen(StartTag.TagName->GetString())==0){
		if(StrData != NULL){
			if(strlen(StrData->GetString())>buffsize)
				return -1;
			strcpy(buff, StrData->GetString());
			int	n=strlen(StrData->GetString());
			return n;
		}
	}
	int	n=StartTag.MakeStr(buff,buffsize);
	if(n<0)
		return -1;
	buffsize-=n;
	for(XMLElement *e=Datas.GetFirst();e!=NULL;e=e->GetNext()){
		int m=e->MakeStr(&buff[n],buffsize);
		if(m<0)
			return -1;
		buffsize-=m;
		n+=m;
	}
	if(StartTag.TagName!=NULL && strlen(StartTag.TagName->GetString())+4>buffsize)
		return -1;
	buff[n]='<';
	n++;
	buff[n]='/';
	n++;
	if(StartTag.TagName!=NULL){
		strcpy(&buff[n],StartTag.TagName->GetString());
		int	m=strlen(StartTag.TagName->GetString());
		n+=m;
	}
	buff[n]='>';
	n++;
	buff[n]=0;
	return n;
}

XMLElement	&XMLElement::operator=(XMLElement &src)
{
	ID			=src.ID;

	XMLMainStock::GetStringStoker().RemoveReference(StrData);
	StrData=XMLMainStock::GetStringStoker().GetItem(src.StrData->GetString());

	StartTag	=src.StartTag;
	InsertedNumb=src.InsertedNumb;

	Datas.RemoveAll();
	for(XMLElement *s=src.Datas.GetFirst();s!=NULL;s=s->GetNext()){
		XMLElement	*d;
		if(dynamic_cast<XMLElementWithIncrementalID *>(this)!=NULL)
			d=new XMLElementWithIncrementalID(this);
		else
			d=new XMLElement(this);
		*d=*s;

		if(Datas.GetLast()!=NULL)
			d->InsertedNumb=Datas.GetLast()->InsertedNumb+1;
		else
			d->InsertedNumb=0;
		Datas.AppendList(d);
	}
	return *this;
}
bool	XMLElement::Delete(void)
{
	for(XMLElement *s=Datas.GetFirst();s!=NULL;s=s->GetNext()){
		s->Delete();
	}
	StartTag.Delete();
	if(Parent!=NULL)
		Parent->Datas.RemoveList(this);
	return true;
}

XMLMainStock	*XMLElement::GetTop()
{
	XMLElement	*e=this;
	while(e->Parent!=NULL)
		e=e->Parent;
	return dynamic_cast<XMLMainStock *>(e);
}

int	XMLElement::Size(void)
{
	int iSize=0;
	for(XMLElement *d=Datas.GetFirst();d!=NULL;d=d->GetNext()){
		iSize=iSize+d->Size();
	}
	if(StrData==NULL)
		return 	StartTag.Size()
				+5
				+iSize;//+sizeof(qint64);
	return 	strlen(StrData->GetString())
			+StartTag.Size()
			+5
			+iSize;//+sizeof(qint64);

}
bool	XMLElement::Save(QIODevice &Buff)
{
	if(::Save(&Buff,ID)==false)
		return false;

	bool	NullData;
	if(StrData==NULL)
		NullData=true;
	else
		NullData=false;
	if(::Save(&Buff,NullData)==false)
		return false;
	if(StrData!=NULL){
		if(::Save(&Buff,StrData->GetString())==false)
			return false;
	}

	if(StartTag.Save(Buff)==false)
		return false;
	if(::Save(&Buff,(int)Datas.GetNumber())==false)
		return false;

	XMLElement *Prev=NULL;
	for(XMLElement *d=Datas.GetFirst();d!=NULL;d=d->GetNext()){
		if(d->Save(Buff)==false)
			return false;
		Prev=d;
	}
	return true;
}
bool XMLElement::Load(QIODevice &Buff)
{
	if(::Load(&Buff,ID)==false)
		return false;

	bool	NullData;
	if(::Load(&Buff,NullData)==false)
		return false;

	if(NullData==false){
		char	*tmpStrData=LoadString(&Buff);
		XMLMainStock::GetStringStoker().RemoveReference(StrData);
		StringStokerItem *sData;
		sData=XMLMainStock::GetStringStoker().GetItem(tmpStrData);
		StrData=sData;
		/*if(QByteArray(tmpStrData).right(6)==".DBXML"){
			StrData=StrData;
		}else{
			StrData=sData;
		}*/
		delete	[]tmpStrData;
	}else{
		StrData=NULL;
	}

	if(StartTag.Load(Buff)==false)
		return false;
	Datas.RemoveAll();
	int	Count;
	if(::Load(&Buff,Count)==false)
		return false;
	for(int Cnt=0;Cnt<Count;Cnt++){
		XMLElementWithIncrementalID	*Element=new XMLElementWithIncrementalID(this,0);
		if(Element->Load(Buff)==false)
			return false;
		Element->InsertedNumb=Cnt;
		Datas.AppendList(Element);
	}
	return true;
}
XMLElement	*XMLElement::SearchByID(qint64 id)
{
	if(ID==id)
		return this;
	for(XMLElement *d=Datas.GetFirst();d!=NULL;d=d->GetNext()){
		XMLElement	*ret=d->SearchByID(id);
		if(ret!=NULL)
			return ret;
	}
	return NULL;
}

bool	XMLElement::AddElement(XMLElement &Src)
{
	StartTag.AddTag(Src.StartTag);
	for(XMLElement *a=Src.Datas.GetFirst();a!=NULL;a=a->GetNext()){
		XMLElement *b=new XMLElement(this);
		*b=*a;
		Datas.AppendList(b);
	}
	return true;
}


XMLElement	*XMLElement::MatchNextFromChild(XMLTag &MatchPoint, int ChildInsertedNumb)
{
	for(XMLElement *e=Datas.GetItem(ChildInsertedNumb+1);e!=NULL;e=e->GetNext()){
		XMLElement *ret=e->MatchFirstRoot(MatchPoint);
		if(ret!=NULL)
			return ret;
	}
	if(Parent!=NULL){
		return Parent->MatchNextFromChild(MatchPoint, InsertedNumb);
	}
	return NULL;
}
/*
XMLElement	*XMLElement::MatchNext(XMLTag &MatchPoint, XMLElement *PrevData)
{
	for(XMLElement *e=PrevData->Datas.GetFirst();e!=NULL;e=e->GetNext()){
		XMLElement *ret=e->MatchFirst(MatchPoint);
		if(ret!=NULL)
			return ret;
	}
	if(PrevData->Parent!=NULL)
		return PrevData->Parent->MatchNextFromChild(MatchPoint, PrevData->InsertedNumb);
	return NULL;
}
*/
void	XMLElement::RebuildInsertedNumb(int InsertedNumb)
{
	for(XMLElement *e=Datas.GetItem(InsertedNumb);e!=NULL;e=e->GetNext()){
		e->InsertedNumb=InsertedNumb;
		InsertedNumb++;
	}
}
XMLElement	*XMLElement::FindFirstByTag(char *tagName)
{
	XMLElement *ret=FindFirstByTagRoot(tagName);
	if(ret!=NULL){
//		LogData.PutLogA1R(__LINE__,"XMLMainStock::FindFirstByTag",ID,ret->ID);
		return ret;
	}
//	LogData.PutLogA1R(__LINE__,"XMLMainStock::FindFirstByTag",ID,(int64)NULL);
	return NULL;
}
XMLElement	*XMLElement::FindLastByTag(char *tagName)
{
	XMLElement *ret=FindLastByTagRoot(tagName);
	if(ret!=NULL){
//		LogData.PutLogA1R(__LINE__,"XMLMainStock::FindFirstByTag",ID,ret->ID);
		return ret;
	}
//	LogData.PutLogA1R(__LINE__,"XMLMainStock::FindFirstByTag",ID,(int64)NULL);
	return NULL;
}
XMLElement	*XMLElement::FindFirstByTagRoot(char *tagName)
{
	if(StartTag.TagName!=NULL){
		if(strcmp(StartTag.TagName->GetString(),tagName)==0)
			return this;
	}
	for(XMLElement *e=Datas.GetFirst();e!=NULL;e=e->GetNext()){
		XMLElement	*ret=e->FindFirstByTagRoot(tagName);
		if(ret!=NULL)
			return ret;
	}
	return NULL;
}

XMLElement	*XMLElement::FindLastByTagRoot(char *tagName)
{//	for(XMLElement *e=PrevData->Datas.GetLast();e!=NULL;e=e->GetPrev()){
	if(StartTag.TagName!=NULL){
		if(strcmp(StartTag.TagName->GetString(),tagName)==0)
			return this;
	}
	for(XMLElement *e=Datas.GetLast();e!=NULL;e=e->GetPrev()){
		XMLElement	*ret=e->FindLastByTagRoot(tagName);
		if(ret!=NULL)
			return ret;
	}
	return NULL;
}
XMLElement	*XMLElement::FindNextByTagFromChild(char *tagName, int ChildInsertedNumb)
{
	for(XMLElement *e=Datas.GetItem(ChildInsertedNumb+1);e!=NULL;e=e->GetNext()){
		XMLElement *ret=e->FindFirstByTagRoot(tagName);
		if(ret!=NULL)
			return ret;
	}
	if(Parent!=NULL){
		return Parent->FindNextByTagFromChild(tagName, InsertedNumb);
	}
	return NULL;
}
XMLElement *XMLElement::FindNextByTag(XMLElement *PrevData, char *tagName)
{
	for(XMLElement *e=PrevData->Datas.GetFirst();e!=NULL;e=e->GetNext()){
	//for(XMLElement *e=PrevData->GetNext(); e!=NULL; e=e->GetNext()){
		XMLElement *ret=e->FindFirstByTagRoot(tagName);
		if(ret!=NULL){
//			LogData.PutLogA1R(__LINE__,"XMLElement::FindNextByTag",PrevData->ID,(int64)ret->ID);
			return ret;
		}
	}
	if(PrevData->Parent!=NULL){
		XMLElement *ret=PrevData->Parent->FindNextByTagFromChild(tagName,PrevData->InsertedNumb);
		if(ret!=NULL){
//			LogData.PutLogA1R(__LINE__,"XMLElement::FindNextByTag",PrevData->ID,(int64)ret->ID);
			return ret;
		}
	}
//	LogData.PutLogA1R(__LINE__,"XMLElement::FindNextByTag",PrevData->ID,(int64)NULL);
	return NULL;
}
XMLElement *XMLElement::MatchFirst(XMLTag &MatchPoint)
{
	XMLElement *ret=MatchFirstRoot(MatchPoint);
	if(ret!=NULL){
//		LogData.PutLogA1R(__LINE__,"XMLElement::MatchFirst",ID,ret->ID);
		return ret;
	}
//	LogData.PutLogA1R(__LINE__,"XMLElement::MatchFirst",ID,(int64)NULL);
	return NULL;
}
XMLElement *XMLElement::MatchFirstRoot(XMLTag &MatchPoint)
{
	if(StartTag.Match(MatchPoint,this)==true)
		return this;
	for(XMLElement *e=Datas.GetFirst();e!=NULL;e=e->GetNext()){
		XMLElement *ret=e->MatchFirstRoot(MatchPoint);
		if(ret!=NULL)
			return ret;
	}
	return NULL;
}
XMLElement *XMLElement::MatchFirst(XMLElement **Answer, XMLTag &MatchPoint, int iParent)
{
	XMLElement *e=MatchFirstRoot(MatchPoint);
	if(e!=NULL){
		*Answer=e;
		for(int i=0;i<iParent;i++){
			if(e->Parent!=NULL)
				e=e->Parent;
		}
//		LogData.PutLogA1R(__LINE__,"XMLElement::MatchFirst", (*Answer)->ID, e->ID);
		return e;
	}
	//LogData.PutLogA1R(__LINE__,"XMLMainStock::MatchFirst",(*Answer)->ID,(int64)NULL);
	//LogData.PutLogA1R(__LINE__,"XMLMainStock::MatchFirst" ,(*Answer)->ID, false);
	return NULL;
}

XMLElement *XMLElement::MatchNext(XMLTag &MatchPoint,XMLElement *PrevData)
{
	XMLElement *ret=MatchNextRoot(MatchPoint,PrevData);
	if(ret!=NULL){
//		LogData.PutLogA1R(__LINE__,"XMLElement::MatchNext",PrevData->ID,ret->ID);
		return ret;
	}
//	LogData.PutLogA1R(__LINE__,"XMLElement::MatchNext",PrevData->ID,(int64)NULL);
	return NULL;
}
XMLElement *XMLElement::MatchNextRoot(XMLTag &MatchPoint,XMLElement *PrevData)
{
	for(XMLElement *e=PrevData->Datas.GetFirst();e!=NULL;e=e->GetNext()){
		XMLElement *ret=e->MatchFirstRoot(MatchPoint);
		if(ret!=NULL){
			return ret;
		}
	}
	if(PrevData->Parent!=NULL){
		XMLElement *ret=PrevData->Parent->MatchNextFromChild(MatchPoint ,PrevData->InsertedNumb);
		return ret;
	}
	return NULL;
}
XMLElement *XMLElement::MatchNext(XMLTag &MatchPoint,XMLElement *PrevData ,XMLElement **AnswerPrev, int iParent)
{
	XMLElement *e=MatchNextRoot(MatchPoint,PrevData);
	if(e!=NULL){
		*AnswerPrev=e;
		for(int i=0;i<iParent;i++){
			if(e->Parent!=NULL)
				e=e->Parent;
		}
//		LogData.PutLogA1R(__LINE__,"XMLElement::MatchNext",PrevData->ID,e->ID);
		return e;
	}
//	LogData.PutLogA1R(__LINE__,"XMLElement::MatchNext",PrevData->ID,(int64)NULL);
	return NULL;
}
void	XMLElement::ErrorLog(int &Num)
{
//	LogData.PutLogA1R(__LINE__,"UpApp::ErrorLog",Num,false);
}

XMLElement	*XMLElement::SearchAndMatch(XMLElement &SearchElement)
{
	if(MatchOnly(SearchElement)==true){
		return this;
	}
	for(XMLElement *e=Datas.GetFirst();e!=NULL;e=e->GetNext()){
		XMLElement *Ret=e->SearchAndMatch(SearchElement);
		if(Ret!=NULL){
			return Ret;
		}
	}
	return NULL;
}
bool	XMLElement::MatchOnly(XMLElement &SearchElement)
{
	if(StartTag.Matched(SearchElement.StartTag)==true){
		if(SearchElement.StrData!=NULL && strcmp(SearchElement.StrData->GetString(),StrData->GetString())==0){
			XMLElement *e;
			for(e=SearchElement.Datas.GetFirst();e!=NULL;e=e->GetNext()){
				XMLElement *f;
				for(f=Datas.GetFirst();f!=NULL;f=f->GetNext()){
					if(strcmp(e->StartTag.TagName->GetString(),f->StartTag.TagName->GetString())==true){
						if(f->MatchOnly(*e)==true){
							break;
						}
					}
				}
				if(f==NULL){
					break;
				}
			}
			if(e==NULL){	//Matchするとき
				return true;
			}
		}
	}
	return false;
}


XMLElementWithIncrementalID::XMLElementWithIncrementalID(XMLElement *parent)
:XMLElement(parent)
{
	if(Parent!=NULL){
		XMLMainStock	*p=GetTop();
		if(p!=NULL){
			ID=p->BaseID;
			p->BaseID++;
		}
	}
}
XMLElementWithIncrementalID::XMLElementWithIncrementalID(XMLElement *parent,int X)
:XMLElement(parent)
{
}
//=================================================================

void	XMLThreadCommandItemDelete::Run(void)
{
	delete	Item;
}


void XMLThreadCommander::run ()
{
	for(;;){
		XMLThreadCommandItemBase	*p=PopFromList();
		if(p!=NULL){
			p->Run();
			delete	p;
		}
		else{
			if(FinishMode==true)
				break;
			msleep(100);
		}
	}
}

void	XMLThreadCommander::AppendList(XMLThreadCommandItemBase *d)
{
	DataMutex.lock();
	CommandData.AppendList(d);
	DataMutex.unlock();
}
XMLThreadCommandItemBase	*XMLThreadCommander::PopFromList(void)
{
	DataMutex.lock();
	XMLThreadCommandItemBase	*d=CommandData.GetFirst();
	if(d!=NULL){
		CommandData.RemoveList(d);
	}
	DataMutex.unlock();
	return d;
}


//=================================================================
XMLMainStock::XMLMainStock(char *fileName)
	:XMLElement(NULL)
	,BaseID(1)
{
	MatchXMLTag =new QList<XMLTag*>();

	XMLMainStock	*q=GetTop();
	if(q!=NULL)
		q->StrStocker.RemoveReference(StrData);
	StrData=q->StrStocker.GetItem(fileName);

	XMLThreadCommand.start();

//	LogData.Initial();
//	LogData.PutLogA1(__LINE__,"XMLMainStock",StrData->GetString());
}
XMLMainStock::~XMLMainStock(void)
{
	XMLThreadCommand.FinishMode=true;
	XMLThreadCommand.wait(10000);
}

char	*XMLMainStock::GetFileName(void)
{
	if(StrData!=NULL){
		return StrData->GetString();
	}
	return NULL;
}

StringStoker		&XMLMainStock::GetStringStoker(void)
{
	return StrStocker;
}

bool	XMLMainStock::Create(void)
{
	//QString qStrData=StrData->GetString();
	QTextCodec *code=QTextCodec::codecForName ("Shift-JIS") ;
	QString qStrData=code->toUnicode(QByteArray(StrData->GetString()));
	QFile	FileHandle;
	FileHandle.setFileName(qStrData);
	FileHandle.open(QIODevice::ReadWrite);
	FileHandle.close();
	return true;
}

bool	XMLMainStock::UpdateToStream(void)
{
	QFile	FileHandle;
	//QString qStrData=StrData->GetString();
	QTextCodec *code=QTextCodec::codecForName ("Shift-JIS") ;
	QString qStrData=code->toUnicode(QByteArray(StrData->GetString()));
#if 1 // 20100223
	if (DDB != qStrData)
		qStrData = DDB;
#endif
	FileHandle.setFileName(qStrData);
	FileHandle.open(QIODevice::WriteOnly | QIODevice::Append);

#if 1 // 20100222
	if (::Save(&FileHandle, BaseID) == false)
	{
		FileHandle.close();
		return false;
	}

	if(XMLElement::Save(FileHandle) == false)
	{
		FileHandle.close();
		return false;
	}
#else
	if(::Save(&FileHandle,BaseID)==false)
		return false;
	if(XMLElement::Save(FileHandle)==false)
		return false;
#endif
	FileHandle.close();
	return true;
}
bool	XMLMainStock::LoadFromStream(void)
{
	QFile	FileHandle;
	//QString qStrData=StrData->GetString();
	QTextCodec *code=QTextCodec::codecForName ("Shift-JIS") ;
	QString qStrData=code->toUnicode(QByteArray(StrData->GetString()));
	FileHandle.setFileName(qStrData);
	FileHandle.open(QIODevice::ReadWrite);

	QString Ver;
	QString Day;
	QString Lot;

	if (::Load(&FileHandle, Ver) == false)
	{
		FileHandle.close();
		return false;
	}

	if (::Load(&FileHandle, Day) == false)
	{
		FileHandle.close();
		return false;
	}

	if (::Load(&FileHandle, Lot) == false)
	{
		FileHandle.close();
		return false;
	}

	if (::Load(&FileHandle, BaseID) == false)
	{
		FileHandle.close();
		return false;
	}

	if(Load(FileHandle)==false){
		FileHandle.close();
		//LogData.PutLogA1R(__LINE__,"XMLMainStock::LoadFromStream",StrData->GetString(),false);
		return false;
	}
	//int64	DataNumb=Datas.GetNumber();
	//LogData.PutLogA2R(__LINE__,"XMLMainStock::LoadFromStream",StrData->GetString(),DataNumb,true);
	FileHandle.close();
	return true;
}
bool XMLMainStock::Append(qint64 AppID, char *xmlStr)
{
	XMLElement	*p=SearchByID(AppID);
	if(p==NULL){
//		LogData.PutLogA1R(__LINE__,"XMLMainStock::Append",AppID,false);
		return false;
	}

	XMLElement	*d=new XMLElementWithIncrementalID(p);
	d->Analyze(xmlStr);
	d->InsertedNumb=p->Datas.GetNumber();
	p->Datas.AppendList(d);
//	LogData.PutLogA1R(__LINE__,"XMLMainStock::Append",AppID,d->ID);
	return true;
}
bool	XMLMainStock::Delete(qint64 DelID, QString &NGJ)
{
	XMLElement	*p=SearchByID(DelID);
	if(p!=NULL){
		char	buff[1000];//=new char[1000];
		p->MakeStr(buff, 1000);
		XMLGetData(QByteArray(buff), NGJ);
		XMLElement	*ParentQ=p->Parent;
		int			InsertedCountQ=p->InsertedNumb;
		p->Delete();
		//delete	p;
		XMLThreadCommandItemDelete	*DelItem=new XMLThreadCommandItemDelete(p);
		XMLThreadCommand.AppendList(DelItem);
		if(ParentQ!=NULL){
			ParentQ->RebuildInsertedNumb(InsertedCountQ);
		}

//		LogData.PutLogA1R(__LINE__,"XMLMainStock::Delete", DelID, true);
		//DelID=0;
		//delete []buff;
		return true;
	}else{
//		LogData.PutLogA1R(__LINE__,"XMLMainStock::Delete", DelID, false);
		//DelID=0;
		return false;
	}

}
void  XMLMainStock::XMLGetData(const QByteArray &Info, QString &NGJ)
{
	QDomDocument d;
	QTextCodec *code=QTextCodec::codecForName ("Shift-JIS") ;
	QString Sinfo=code->toUnicode(Info);
	d.setContent(Sinfo);
	QDomElement n = d.firstChildElement();
	while (!n.isNull()) {
		if (n.tagName()=="IST"){
			NGJ=n.attribute("NGJ");
			return ;
			QDomElement child = n.firstChildElement();
			while (!child.isNull()) {
				child=child.nextSiblingElement();
			}
		}
		return ;
	}
}
