/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\LanguageSolver\LanguageSolver\XLanguageSolver.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "XLanguageNewSolver.h"
#include <QFile>
#include <QFileInfo>
#include <ctype.h>
#include <mbstring.h>
#include <QTextStream>
#include <QFileInfo>
#include <QTextCodec>
#include "XGeneralFunc.h"
#include <QString>
#include "XCSV.h"
#include "XExcelOperator.h"
#include "swap.h"
#include "libxl.h"
using namespace libxl;

static	QTextCodec	*HCodec[MAXLANGUAGECOUNT];




inline	char	*SkipSpace(char *fp)
{
	while(*fp==' ' || *fp=='\t')
		fp++;
	return(fp);
}

static	char	*CutWord(char *fp,char *kword ,int kwordlen)
{
	while(*fp==' ' || *fp=='\t')
		fp++;
	if(*fp=='\"'){
		for(;;){
			if(*fp=='\\' && *(fp+1)=='\\'){
				*kword=*fp;
				fp+=2;
				kword++;
				kwordlen--;
				if(kwordlen<=0)
					return fp;
				}
			else if(*fp=='\\' && *(fp+1)=='\"'){
				*kword=*(fp+1);
				fp+=2;
				kword++;
				kwordlen--;
				if(kwordlen<=0)
					return fp;
				}
			else if(*fp=='\\' && *(fp+1)=='\''){
				*kword=*(fp+1);
				fp+=2;
				kword++;
				kwordlen--;
				if(kwordlen<=0)
					return fp;
				}
			else if(_ismbblead(*((unsigned short *)fp))==0){
				*kword=*fp;
				fp++;
				kword++;
				kwordlen--;
				if(kwordlen<=0)
					return fp;
			}
			else{
				*kword=*fp;
				fp++;
				kword++;
				kwordlen--;
				if(kwordlen<=0)
					return fp;
				*kword=*fp;
				fp++;
				kword++;
				kwordlen--;
				if(kwordlen<=0)
					return fp;
			}
			if(*fp=='\"'){
				*kword=*fp;
				fp++;
				kword++;
				*kword=0;
				kwordlen--;
				if(kwordlen<=0)
					return fp;
				return fp;
			}
			if(*fp==0){
				*kword=0;
				return fp;
			}
		}
	}
	else if(*fp=='\''){
		for(;;){
			if(*fp=='\\' && *(fp+1)=='\\'){
				*kword=*fp;
				fp+=2;
				kword++;
				kwordlen--;
				if(kwordlen<=0)
					return fp;
				}
			else if(*fp=='\\' && *(fp+1)=='\"'){
				*kword=*(fp+1);
				fp+=2;
				kword++;
				kwordlen--;
				if(kwordlen<=0)
					return fp;
				}
			else if(*fp=='\\' && *(fp+1)=='\''){
				*kword=*(fp+1);
				fp+=2;
				kword++;
				kwordlen--;
				if(kwordlen<=0)
					return fp;
				}
			else if(isprint(*((unsigned char *)fp))){
				*kword=*fp;
				fp++;
				kword++;
				kwordlen--;
				if(kwordlen<=0)
					return fp;
			}
			else{
				*kword=*fp;
				fp++;
				kword++;
				kwordlen--;
				if(kwordlen<=0)
					return fp;
				*kword=*fp;
				fp++;
				kword++;
				kwordlen--;
				if(kwordlen<=0)
					return fp;
			}
			if(*fp=='\''){
				*kword=*fp;
				fp++;
				kword++;
				kwordlen--;
				if(kwordlen<=0)
					return fp;
				*kword=0;
				return fp;
			}
			if(*fp==0){
				*kword=0;
				return fp;
			}
		}
	}
	if(strchr("+/*-,.<>=()!#$%&~^|\\{}@:;\n",*fp)!=NULL){
		*kword=*fp;
		kword++;
		kwordlen--;
		if(kwordlen<=0)
			return fp;
		*kword=0;
		return fp+1;
	}
	for(;;){
		if(isprint(*((unsigned char *)fp))){
			*kword=*fp;
			fp++;
			kword++;
			kwordlen--;
			if(kwordlen<=0)
				return fp;
		}
		else{
			*kword=*fp;
			fp++;
			kword++;
			kwordlen--;
			if(kwordlen<=0)
				return fp;
			*kword=*fp;
			fp++;
			kword++;
			kwordlen--;
			if(kwordlen<=0)
				return fp;
		}
		if(strchr(" \t+/*-,.<>=()!#$%&~^|\\{}@:;\n",*fp)!=NULL){
			*kword=0;
			return fp;
		}
	}			
}
static	int	StrToHex(char c)
{
	switch(c){
		case '0':	return 0;
		case '1':	return 1;
		case '2':	return 2;
		case '3':	return 3;
		case '4':	return 4;
		case '5':	return 5;
		case '6':	return 6;
		case '7':	return 7;
		case '8':	return 8;
		case '9':	return 9;
		case 'a':	return 10;
		case 'A':	return 10;
		case 'b':	return 11;
		case 'B':	return 11;
		case 'c':	return 12;
		case 'C':	return 12;
		case 'd':	return 13;
		case 'D':	return 13;
		case 'e':	return 14;
		case 'E':	return 14;
		case 'f':	return 15;
		case 'F':	return 15;
	}
	return -1;
}

static	QChar	*CutWord(QChar *fp,QString &kword)
{
	while(*fp==' ' || *fp=='\t')
		fp++;
	if(*fp=='\"'){
		for(;;){
			if(*fp=='\\' && *(fp+1)=='\\'){
				kword.append(*fp);
				fp+=2;
			}
			else if(*fp=='\\' && *(fp+1)=='\"'){
				kword.append(*(fp+1));
				fp+=2;
			}
			else if(*fp=='\\' && *(fp+1)=='\''){
				kword.append(*(fp+1));
				fp+=2;
			}
			else{
				kword.append(*fp);
				fp++;
			}
			if(*fp=='\"'){
				kword.append(*fp);
				fp++;
				return fp;
			}
			if(*fp==0){
				return fp;
			}
		}
	}
	else if(*fp=='\''){
		for(;;){
			if(*fp=='\\' && *(fp+1)=='\\'){
				kword.append(*fp);
				fp+=2;
			}
			else if(*fp=='\\' && *(fp+1)=='\"'){
				kword.append(*(fp+1));
				fp+=2;
			}
			else if(*fp=='\\' && *(fp+1)=='\''){
				kword.append(*(fp+1));
				fp+=2;
			}
			else{
				kword.append(*fp);
				fp++;
			}

			if(*fp=='\''){
				kword.append(*fp);
				fp++;
				return fp;
			}
			if(*fp==0){
				return fp;
			}
		}
	}
	if(QString("+/*-,.<>=()!#$%&~^|\\{}@:;\n").contains(*fp)==true){
		kword.append(*fp);
		return fp+1;
	}
	for(;;){
		kword.append(*fp);
		fp++;	
		if(*fp==0){
			return fp;
		}
		if(QString(" \t+/*-,.<>=()!#$%&~^|\\{}@:;\n").contains(*fp)==true){
			return fp;
		}
	}			
}

char	*ConvertForC(char *Src ,char *Dst)
{
	char	buff[10];
	while(*Src!=0){
		if(*Src=='\"'){
			*Dst='\\';
			Dst++;
			*Dst='\"';
			Dst++;
			Src++;
		}
		else if(*Src=='\''){
			*Dst='\\';
			Dst++;
			*Dst='\'';
			Dst++;
			Src++;
		}
		else if(((unsigned char )*Src)<0x20){
			sprintf(buff,"%02x",(int)(((unsigned char )*Src)));
			*Dst='\\';
			Dst++;
			*Dst='x';
			Dst++;
			*Dst=buff[0];
			Dst++;
			*Dst=buff[1];
			Dst++;
			Src++;
		}
		else if(*Src=='\\'){
			*Dst='\\';
			Dst++;
			*Dst='\\';
			Dst++;
			Src++;
		}
		else if(_ismbblead(*((unsigned short *)Src))==0){
			*Dst=*Src;
			Src++;
			Dst++;
			}
		else{
			*Dst=*Src;
			Src++;
			Dst++;
			*Dst=*Src;
			Src++;
			Dst++;
		}
	}
	*Dst=0;
	return Src;
}

char	*ConvertFromC(char *Src ,char *Dst)
{
	while(*Src!=0){
		if(*Src=='\\'){
			Src++;
			if(*Src=='\\'){
				*Dst='\\';
				Dst++;
				Src++;
			}
			else if(*Src=='\"'){
				*Dst='\"';
				Dst++;
				Src++;
			}
			else if(*Src=='\''){
				*Dst='\'';
				Dst++;
				Src++;
			}
			else if(*Src=='x'){
				Src++;
				int	d1=StrToHex(*Src);
				Src++;
				int	d2=StrToHex(*Src);
				Src++;
				*Dst=d1*16+d2;
				Dst++;
			}
			else{
				*Dst=*Src;
				Src++;
				Dst++;
			}
		}
		else if(_ismbblead(*((unsigned short *)Src))==0){
			*Dst=*Src;
			Src++;
			Dst++;
			}
		else{
			*Dst=*Src;
			Src++;
			Dst++;
			*Dst=*Src;
			Src++;
			Dst++;
		}
	}
	*Dst=0;
	return Src;
}

static	char	*CutWordFromC(char *fp,char *kword ,int kwordlen)
{
	while(*fp==' ' || *fp=='\t')
		fp++;
	if(*fp=='\"'){
		for(;;){
			if(*fp=='\\'){
				fp++;
				if(*fp=='\\'){
					*kword='\\';
					fp++;
					kword++;
					kwordlen--;
					if(kwordlen<=0)
						return fp;
				}
				else if(*fp=='\"'){
					*kword='\"';
					fp++;
					kword++;
					kwordlen--;
					if(kwordlen<=0)
						return fp;
				}
				else if(*fp=='\''){
					*kword='\'';
					fp++;
					kword++;
					kwordlen--;
					if(kwordlen<=0)
						return fp;
				}
				else if(*fp=='x'){
					fp++;
					int	d1=StrToHex(*fp);
					fp++;
					int	d2=StrToHex(*fp);
					fp++;
					*kword=d1*16+d2;
					kword++;
					kwordlen--;
					if(kwordlen<=0)
						return fp;
				}
				else{
					*kword=*fp;
					fp++;
					kword++;
					kwordlen--;
					if(kwordlen<=0)
						return fp;
				}
			}
			else if(_ismbblead(*((unsigned short *)fp))==0){
				*kword=*fp;
				fp++;
				kword++;
				kwordlen--;
				if(kwordlen<=0)
					return fp;
			}
			else{
				*kword=*fp;
				fp++;
				kword++;
				kwordlen--;
				if(kwordlen<=0)
					return fp;
				*kword=*fp;
				fp++;
				kword++;
				kwordlen--;
				if(kwordlen<=0)
					return fp;
			}
			if(*fp=='\"'){
				*kword=*fp;
				fp++;
				kword++;
				*kword=0;
				kwordlen--;
				if(kwordlen<=0)
					return fp;
				return fp;
			}
			if(*fp==0){
				*kword=0;
				return fp;
			}
		}
	}
	if(*fp=='\''){
		for(;;){
			if(isprint(*((unsigned char *)fp))){
				*kword=*fp;
				fp++;
				kword++;
				kwordlen--;
				if(kwordlen<=0)
					return fp;
			}
			else{
				*kword=*fp;
				fp++;
				kword++;
				kwordlen--;
				if(kwordlen<=0)
					return fp;
				*kword=*fp;
				fp++;
				kword++;
				kwordlen--;
				if(kwordlen<=0)
					return fp;
			}
			if(*fp=='\''){
				*kword=*fp;
				fp++;
				kword++;
				kwordlen--;
				if(kwordlen<=0)
					return fp;
				*kword=0;
				return fp;
			}
			if(*fp==0){
				*kword=0;
				return fp;
			}
		}
	}
	if(strchr("+/*-,.<>=()!#$%&~^|\\{}@:;\n",*fp)!=NULL){
		*kword=*fp;
		kword++;
		kwordlen--;
		if(kwordlen<=0)
			return fp;
		*kword=0;
		return fp+1;
	}
	for(;;){
		if(isprint(*((unsigned char *)fp))){
			*kword=*fp;
			fp++;
			kword++;
			kwordlen--;
			if(kwordlen<=0)
				return fp;
		}
		else{
			*kword=*fp;
			fp++;
			kword++;
			kwordlen--;
			if(kwordlen<=0)
				return fp;
			*kword=*fp;
			fp++;
			kword++;
			kwordlen--;
			if(kwordlen<=0)
				return fp;
		}
		if(strchr(" \t+/*-,.<>=()!#$%&~^|\\{}@:;\n",*fp)!=NULL){
			*kword=0;
			return fp;
		}
	}			
}

//====================================================================================

void	ReplaceForSource(QString &s)
{
	s.replace("\\" ,"\\" "\\");
	s.replace("\"","\\""\"");
	s.replace("//","/\" \"/");
	s.replace("/" "*" ,"/\" \"*");
	s.replace("*" "/" ,"*\" \"/");
}


void	SaveResourceText(QTextStream &OutData,QString &s)
{
	char	*fp;
	QChar	c;
	static	const	char	*IntToHexStr[16]={	"0","1","2","3","4","5","6","7","8","9","a","b","c","d","e","f"	};
	int	H,L;
	bool	ChangedToChar=false;
	for(int i=0;i<s.length();i++){
		c=s.at(i);
		QByteArray	mbuff;
		QTextStream	Txt(&mbuff);
		Txt<<c;
		Txt.flush();
		fp=mbuff.data();
		if(strlen(fp)==1){
			if(ChangedToChar==true){
				OutData<<"\"\"";
				ChangedToChar=false;
			}
			OutData<<c;
		}
		else{
			for(int j=0;j<strlen(fp);j++){
				OutData<<"\\x";
				H=((*(fp+j))>>4)&0xF;
				L= (*(fp+j))&0xF;
				OutData<<IntToHexStr[H];
				OutData<<IntToHexStr[L];
			}
			ChangedToChar=true;
		}
	}
}

bool	LanguageString::SaveResource(QIODevice &File)
{
	if(::SaveText(&File,(char *)"\t\"")==false)
		return false;
	WORD	N=Data.count();
	char	Buff[10000];

	if(N==1){
		QString	s=Data.value(0);
		QStringList	KList=s.split("\n");
		if(KList.count()==1){
			ReplaceForSource(s);
			QTextStream	TStr(&File);
			//TStr<<s;
			SaveResourceText(TStr,s);
			if(s.length()!=0){
				TStr<<QChar(' ');
			}
			TStr.flush();
		}
		else{
			N=KList.count();
			sprintf(Buff,"\\%02x\\%02x",((N>>8)&0xFF)+1 ,N&0xFF);
			if(::SaveText(&File,Buff)==false)
				return false;

			for(int i=0;i<KList.count();i++){
				QString	s=KList.value(i);
				ReplaceForSource(s);
				QTextStream	TStr(&File);
				//TStr<<s;
				SaveResourceText(TStr,s);
				if(s.length()!=0){
					TStr<<QChar(' ');
				}
				TStr.flush();
				if(i<KList.count()-1){
					if(::SaveText(&File,(char *)"\\" 
						"n")==false)
						return false;
				}
			}
		}
	}
	else if(N>1){
		sprintf(Buff,"\\%02x\\%02x",((N>>8)&0xFF)+1 ,N&0xFF);
		if(::SaveText(&File,Buff)==false)
			return false;

		for(int i=0;i<Data.count();i++){
			QString	s=Data.value(i);
			ReplaceForSource(s);
			QTextStream	TStr(&File);
			//TStr<<s;
			SaveResourceText(TStr,s);
			TStr.flush();
			//int	n=QString2Char(s,Buff ,sizeof(Buff));
			//ConvertForC(Buff,ConvertBuff);
			//if(::SaveText(&File,ConvertBuff)==false)
			//	return false;
			if(i<Data.count()-1){
				if(::SaveText(&File,(char *)"\\" 
					"0")==false)
					return false;
			}
		}
	}
	if(::SaveText(&File,(char *)"\"")==false)
		return false;
	return true;
}


static	int		AnalyzeHexFrom2Byte(char *fp)
{
	int	d1=StrToHex(*fp);
	if(d1<0)
		return -1;
	int	d2=StrToHex(*(fp+1));
	if(d2<0)
		return -1;
	return d1*16+d2;
}

bool	LanguageString::operator==(LanguageString &src)
{
	if(Data==src.Data){
		return true;
	}
	return false;
}

char	*LanguageString::LoadResourceFromString(char *fp)
{
	char	Buff[10240];
	char	*cp=fp;
	if(*fp=='\\'){
		fp++;
		int	d1=AnalyzeHexFrom2Byte(fp)-1;
		if(d1<0)
			goto	RNext;
		fp+=2;
		if(*fp!='\\')
			return NULL;
		fp++;
		int	d2=AnalyzeHexFrom2Byte(fp);
		if(d2<0)
			goto	RNext;
		fp+=2;
		int	NCount=(d1<<8)+d2;

		for(int i=0;i<NCount;i++){
			char	*kword=Buff;
			fp=Load1Word(fp ,Buff,sizeof(Buff)-1);
			Data.append(Buff);
		}
	}
	else{
RNext:;
		//ConvertFromC(cp ,Buff);
		//Data.append(Buff);
		Data.append(cp);
	}
	return fp;
}

char	*LanguageString::Load1Word(char *fp ,char *kword,int kwordlen)
{
	for(;;){
		if(*fp==0){
			*kword=0;
			kword++;
			kwordlen--;
			break;
		}
		else if(*fp=='\\'){
			fp++;
			if(*fp=='\"' || *fp=='\''){
				*kword=*fp;
				fp++;
				kword++;
				kwordlen--;
				if(kwordlen<=0){
					*kword=0;
					break;
				}
			}
			else if(*fp=='a'){
				*kword='\a';
				fp++;
				kword++;
				kwordlen--;
				if(kwordlen<=0){
					*kword=0;
					break;
				}
			}
			else if(*fp=='b'){
				*kword='\b';
				fp++;
				kword++;
				kwordlen--;
				if(kwordlen<=0){
					*kword=0;
					break;
				}
			}
			else if(*fp=='r'){
				*kword='\r';
				fp++;
				kword++;
				kwordlen--;
				if(kwordlen<=0){
					*kword=0;
					break;
				}
			}
			else if(*fp=='n'){
				*kword='\n';
				fp++;
				kword++;
				kwordlen--;
				if(kwordlen<=0){
					*kword=0;
					break;
				}
			}
			else if(*fp=='x'){
				fp++;
				*kword=AnalyzeHexFrom2Byte(fp);
				fp+=2;
				kword++;
				kwordlen--;
				if(kwordlen<=0){
					*kword=0;
					break;
				}
			}
			else if(*fp=='0'){
				*kword=0;
				fp++;
				return fp;
			}
		}
		else if(*fp=='\"'){
			*kword=0;
			kword++;
			kwordlen--;
			if(kwordlen<=0){
				*kword=0;
				break;
			}
		}
		else if(_ismbblead(*((unsigned short *)fp))==0){
			if(*fp=='\\' && *(fp+1)=='0'){
				*kword=0;
				break;
			}
			*kword=*fp;
			fp++;
			kword++;
			kwordlen--;
			if(kwordlen<=0){
				*kword=0;
				break;
			}
		}
		else{
			*kword=*fp;
			fp++;
			kword++;
			kwordlen--;
			if(kwordlen<=0)
				return fp;
			*kword=*fp;
			fp++;
			kword++;
			kwordlen--;
			if(kwordlen<=0)
				return fp;
		}
	}
	return fp;
}


bool	LanguageString::SaveCSVFile(QString &FStr)
{
	WORD	N=Data.count();
	if(N==1){
		FStr =Data.value(0);
	}
	else if(N>1){
		char	Buff[100];
		sprintf(Buff,"\\%02x\\%02x",(N>>8)&0xFF ,N&0xFF);
		FStr=Buff;

		for(int i=0;i<Data.count();i++){
			QString	s=Data.value(i);
			FStr = FStr+s;
			if(i<Data.count()-1){
				FStr = FStr+"\\" "0";
			}
		}
	}
	return true;
}
	
bool	LanguageString::LoadCSVFile(QString &FStr)
{
	QString	Header=FStr.left(6);
	char	buff[10240];
	int	n=QString2Char(Header,buff ,sizeof(buff));
	char	*fp=buff;
	if(*fp=='\\'){
		fp++;
		int	d1=AnalyzeHexFrom2Byte(fp);
		fp+=2;
		if(*fp!='\\'){
			goto	NoHeader;
		}
		fp++;
		int	d2=AnalyzeHexFrom2Byte(fp);
		fp+=2;
		Data.clear();
		int	NCount=(d1<<8)+d2;
		QString	MStr=FStr.remove(0,6);
		QString2Char(MStr,buff ,sizeof(buff));
		char	Buff[10240];
		fp=buff;
		for(int i=0;i<NCount;i++){
			char	*kword=Buff;
			fp=Load1Word(fp ,Buff,sizeof(Buff)-1);
			Data.append(Buff);
		}
	}
	else{
NoHeader:;
		Data.append(FStr);
	}
	return true;
}


bool	LanguageStringResource::SaveResource(QIODevice &File)
{
	if(::SaveText(&File,(char *)"\t{\t")==false)
		return false;
	char	buff[1000];
	int	n=QString2Char(SourceFileName,buff ,sizeof(buff));
	if(::SaveText(&File,buff)==false)
		return false;
	if(::SaveText(&File,(char *)"_LS,LID_")==false)
		return false;
	sprintf(buff,"%d",ID);
	if(::SaveText(&File,buff)==false)
		return false;
	if(::SaveText(&File,(char *)",")==false)
		return false;
	int	N=0;
	for(LanguageString *s=List.GetFirst();s!=NULL;s=s->GetNext(),N++){
		//QTextCodec::setCodecForCStrings	(HCodec[N]);
		QTextCodec::setCodecForLocale	(HCodec[N]);
		//QTextCodec::setCodecForTr		(HCodec[N]);
		if(s->SaveResource(File)==false)
			return false;
		if(N<MAXLANGUAGECOUNT-1){
			if(::SaveText(&File,(char *)",")==false)
				return false;
		}
	}
	for(;N<MAXLANGUAGECOUNT;N++){
		if(::SaveText(&File,(char *)"\"\"")==false)
			return false;
		if(N<MAXLANGUAGECOUNT-1){
			if(::SaveText(&File,(char *)",")==false)
				return false;
		}
	}
	if(::SaveText(&File,(char *)"\t}")==false)
		return false;

	return true;
}
bool	LanguageStringResource::LoadResource(QIODevice &File,char Key[100])
{
	char	buff[10240];
	bool	InStrMode=false;
	bool	Success=false;

	for(int i=0;i<sizeof(buff);i++){
		if(File.read((char *)&buff[i],1)!=1)
			return false;
		if(buff[i]=='\"'){
			InStrMode=!InStrMode;
		}
		if(buff[i]=='\n'){
			buff[i]=0;
			Success=true;
			break;
		}
	}
	if(Success!=true)
		return false;

	strncpy(Key,buff,100);

	char	*fp=buff;
	fp=SkipSpace(fp);
	if(*fp!='{')
		return false;
	fp++;
	fp=SkipSpace(fp);
	char	KeyBuff[1000];
	fp=CutWord(fp,KeyBuff,sizeof(KeyBuff));
	if(strlen(KeyBuff)==0)
		return false;
	int	len=strlen(KeyBuff);
	if(len>3 && strcmp(&KeyBuff[len-3],"_LS")==0)
		KeyBuff[len-3]=0;
	SourceFileName=KeyBuff;

	fp=SkipSpace(fp);
	if(*fp!=',')
		return false;

	fp++;
	fp=SkipSpace(fp);
	if(memcmp(fp,"LID_",4)!=0)
		return false;
	fp+=4;
	if(sscanf(fp,"%d",&ID)!=1)
		return false;
	fp=strchr(fp,',');
	if(fp==NULL)
		return false;
	
	for(int i=0;i<MAXLANGUAGECOUNT;i++){
		fp=SkipSpace(fp);
		if(*fp!=',')
			return false;
		fp++;
		fp=SkipSpace(fp);
		fp=CutWordFromC(fp,KeyBuff,sizeof(KeyBuff));
		int	Len=strlen(KeyBuff);
		if(KeyBuff[0]!='\"' || KeyBuff[Len-1]!='\"')
			return false;
		KeyBuff[Len-1]=0;
		if(KeyBuff[1]!=0){
			LanguageString	*C=new LanguageString();
			if(C->LoadResourceFromString(&KeyBuff[1])==NULL)
				return false;
			List.AppendList(C);
		}
	}
	fp=SkipSpace(fp);
	if(*fp!='}')
		return false;

	return true;
}

bool	LanguageString::IsHtml(void)
{
	if(Data.count()==0)
		return false;
	QString	s=Data[0];
	if(s.contains('<')==true)
		return true;
	return false;
}
void	LanguageString::ReplaceData(const QString &text)
{
	Data.clear();
	Data.append(text);
}

bool	LanguageStringResource::SaveCSVFile(QStringList &FStr)
{
	FStr.append(SourceFileName);

	char	buff[1000];
	sprintf(buff,"LID_%d",ID);
	FStr.append(buff);
	int	N=0;
	for(LanguageString *s=List.GetFirst();s!=NULL;s=s->GetNext(),N++){
		QString	Str;
		if(s->SaveCSVFile(Str)==false)
			return false;
		FStr.append(Str);
	}
	for(;N<MAXLANGUAGECOUNT;N++){
		FStr.append("");
	}

	return true;
}
bool	LanguageStringResource::LoadCSVFile(QStringList &FStr)
{
	if(FStr.count()<2)
		return false;
	SourceFileName=FStr.value(0);
	QString	LIDStr=FStr.value(1);
	QString	LidNumber=LIDStr.remove(0,4);
	ID=LidNumber.toInt();
	if(FStr.count()>=3){
		for(int i=2;i<FStr.count() && i<MAXLANGUAGECOUNT+2;i++){
			LanguageString	*C=new LanguageString();
			QString	s=FStr.value(i);
			if(s.isEmpty()==false){
				if(C->LoadCSVFile(s)==false)
					return false;
			}
			List.AppendList(C);
		}
	}
	else{
		LanguageString	*C=new LanguageString();
		List.AppendList(C);
	}

	return true;
}

bool	LanguageStringResource::SaveHeader(QIODevice &File)
{
	char	buff[200];
	sprintf(buff,"#define\tLID_%d\t%d",ID,ID);
	if(::SaveText(&File,buff)==false)
		return false;
	return true;
}

void	LanguageStringResource::MakeHeaderDefinition(StringDefinition &Ret)
{
	char	buff[200];
	sprintf(buff,"LID_%d",ID);
	Ret.KeyString=buff;
	Ret.KeyNumber=ID;
}

bool	LanguageStringResource::Compare(LanguageStringResource *dest)
{
	if(SourceFileName==dest->SourceFileName && ID==dest->ID)
		return true;
	return false;
}

StringDefinition	*StringDefinitionContainer::Search(const QString &keyStr)
{
	for(StringDefinition *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->KeyString==keyStr){
			return a;
		}
	}
	return NULL;
}

bool	UIStringResource::SaveResource(QIODevice &File)
{
	if(::SaveText(&File,(char *)"\t{\t")==false)
		return false;
	char	buff[1000];
	if(::SaveText(&File,(char *)"\"")==false)
		return false;
	QString2Char(UIClassName,buff ,sizeof(buff));
	if(::SaveText(&File,buff)==false)
		return false;
	if(::SaveText(&File,(char *)"\",\"")==false)
		return false;

	QString2Char(ClassTypeName,buff ,sizeof(buff));
	if(::SaveText(&File,buff)==false)
		return false;
	if(::SaveText(&File,(char *)"\",\"")==false)
		return false;

	QString2Char(ControlName,buff ,sizeof(buff));
	if(::SaveText(&File,buff)==false)
		return false;
	if(::SaveText(&File,(char *)"\",\"")==false)
		return false;

	QString2Char(PropertyName,buff ,sizeof(buff));
	if(::SaveText(&File,buff)==false)
		return false;
	if(::SaveText(&File,(char *)"\",")==false)
		return false;

	int	N=0;
	for(LanguageString *s=List.GetFirst();s!=NULL && N<MAXLANGUAGECOUNT;s=s->GetNext(),N++){
		//QTextCodec::setCodecForCStrings	(HCodec[N]);
		QTextCodec::setCodecForLocale	(HCodec[N]);
		//QTextCodec::setCodecForTr		(HCodec[N]);
		if(s->SaveResource(File)==false)
			return false;
		//if(N<MAXLANGUAGECOUNT-1){
			if(::SaveText(&File,(char *)",")==false)
				return false;
		//}
	}
	for(;N<MAXLANGUAGECOUNT;N++){
		if(::SaveText(&File,(char *)"\"\"")==false)
			return false;
		if(N<MAXLANGUAGECOUNT-1){
			if(::SaveText(&File,(char *)",")==false)
				return false;
		}
	}
	if(::SaveText(&File,(char *)"\t}")==false)
		return false;
	return true;
}
bool	UIStringResource::LoadResource(QIODevice &File,char Key[100])
{
	char	buff[10240];
	bool	InStrMode=false;
	bool	Success=false;

	for(int i=0;i<sizeof(buff);i++){
		if(File.read((char *)&buff[i],1)!=1)
			return false;
		if(buff[i]=='\"'){
			InStrMode=!InStrMode;
		}
		if(buff[i]=='\n'){
			buff[i]=0;
			Success=true;
			break;
		}
	}
	if(Success!=true)
		return false;

	strncpy(Key,buff,100);

	char	*fp=buff;
	fp=SkipSpace(fp);
	if(*fp!='{')
		return false;
	fp++;
	fp=SkipSpace(fp);
	if(*fp!='\"')
		return false;
	char	KeyBuff[1000];
	fp=CutWord(fp,KeyBuff,sizeof(KeyBuff));
	if(strlen(KeyBuff)==0)
		return false;
	int	len=strlen(KeyBuff);
	if(KeyBuff[len-1]=='\"')
		KeyBuff[len-1]=0;
	UIClassName=&KeyBuff[1];
	fp=SkipSpace(fp);
	if(*fp!=',')
		return false;
	fp++;

	fp=SkipSpace(fp);
	if(*fp!='\"')
		return false;
	fp=CutWord(fp,KeyBuff,sizeof(KeyBuff));
	if(strlen(KeyBuff)==0)
		return false;
	len=strlen(KeyBuff);
	if(KeyBuff[len-1]=='\"')
		KeyBuff[len-1]=0;
	ClassTypeName=&KeyBuff[1];
	fp=SkipSpace(fp);
	if(*fp!=',')
		return false;
	fp++;

	fp=SkipSpace(fp);
	if(*fp!='\"')
		return false;
	fp=CutWord(fp,KeyBuff,sizeof(KeyBuff));
	if(strlen(KeyBuff)==0)
		return false;
	len=strlen(KeyBuff);
	if(KeyBuff[len-1]=='\"')
		KeyBuff[len-1]=0;
	ControlName=&KeyBuff[1];
	fp=SkipSpace(fp);
	if(*fp!=',')
		return false;
	fp++;

	fp=SkipSpace(fp);
	if(*fp!='\"')
		return false;
	fp=CutWord(fp,KeyBuff,sizeof(KeyBuff));
	if(strlen(KeyBuff)==0)
		return false;
	len=strlen(KeyBuff);
	if(KeyBuff[len-1]=='\"')
		KeyBuff[len-1]=0;
	PropertyName=&KeyBuff[1];
	
	for(int i=0;i<MAXLANGUAGECOUNT;i++){
		fp=SkipSpace(fp);
		if(*fp!=',')
			return false;
		fp++;
		fp=SkipSpace(fp);
		fp=CutWordFromC(fp,KeyBuff,sizeof(KeyBuff));
		int	Len=strlen(KeyBuff);
		if(KeyBuff[0]!='\"' || KeyBuff[Len-1]!='\"')
			return false;
		KeyBuff[Len-1]=0;
		if(KeyBuff[1]!=0){
			LanguageString	*C=new LanguageString();
			if(C->LoadResourceFromString(&KeyBuff[1])==NULL)
				return false;
			List.AppendList(C);
		}
	}
	fp=SkipSpace(fp);
	if(*fp!='}')
		return false;

	return true;
}

bool	UIStringResource::SaveCSVFile(QStringList &FStr)
{
	FStr.append(UIClassName);
	FStr.append(ClassTypeName);
	FStr.append(ControlName);
	FStr.append(PropertyName);

	int	N=0;
	for(LanguageString *s=List.GetFirst();s!=NULL;s=s->GetNext(),N++){
		QString	Str;
		if(s->SaveCSVFile(Str)==false)
			return false;
		FStr.append(Str);
	}
	for(;N<MAXLANGUAGECOUNT;N++){
		FStr.append("");
	}

	return true;
}

QString	MakeHTMLFileName(const QString &ExelFileBase
						,const QString &UIClassName
						,const QString &ClassTypeName
						,const QString &ControlName
						,const QString &LanguageName)
{
	return ExelFileBase		+QString('.')
			+UIClassName	+QString('.')
			+ClassTypeName	+QString('.')
			+ControlName	+QString('.')
			+LanguageName	+QString('.')
			+QString(/**/"html");
}
bool	UIStringResource::SaveHtmlCSVFile(QStringList &FStr
											,const QString &XLSXFolder 
											,const QString &ExelFileBase 
											,LanguagePack &LangPack)
{
	FStr.append(UIClassName);
	FStr.append(ClassTypeName);
	FStr.append(ControlName);
	FStr.append(PropertyName);

	int	N=0;
	for(LanguageString *s=List.GetFirst();s!=NULL;s=s->GetNext(),N++){
		LanguageClass	*LangC=LangPack[N];
		if(LangC!=NULL){
			QString	str=s->GetFirstString();
			QString	HtmlFileName=MakeHTMLFileName(ExelFileBase
												,UIClassName
												,ClassTypeName
												,ControlName
												,LangC->LanguageName);

			FStr.append(HtmlFileName);

			QString	WHtmlName=XLSXFolder+QDir::separator()+HtmlFileName;
			QFile	WHtmlFile(WHtmlName);
			if(WHtmlFile.open(QIODevice::WriteOnly)==true){
				QTextStream	TStr(&WHtmlFile);
				TStr<<str;
			}
		}
	}
	for(;N<MAXLANGUAGECOUNT;N++){
		LanguageClass	*LangC=LangPack[N];
		if(LangC!=NULL){
			LanguageString *s=List.GetFirst();
			QString	str=s->GetFirstString();
			QString	HtmlFileName=MakeHTMLFileName(ExelFileBase
												,UIClassName
												,ClassTypeName
												,ControlName
												,LangC->LanguageName);

			FStr.append(HtmlFileName);

			QString	WHtmlName=XLSXFolder+QDir::separator()+HtmlFileName;
			QFile	WHtmlFile(WHtmlName);
			if(WHtmlFile.open(QIODevice::WriteOnly)==true){
				QTextStream	TStr(&WHtmlFile);
				TStr<<str;
			}
		}
		else{
			FStr.append("");
		}
	}

	return true;

}

bool	UIStringResource::LoadCSVFile(QStringList &FStr)
{
	if(FStr.count()<5)
		return false;
	UIClassName		=FStr.value(0);
	ClassTypeName	=FStr.value(1);
	ControlName		=FStr.value(2);
	PropertyName	=FStr.value(3);

	for(int i=4;i<FStr.count() && i<MAXLANGUAGECOUNT+4;i++){
		LanguageString	*C=new LanguageString();
		QString	s=FStr.value(i);
		if(C->LoadCSVFile(s)==false)
			return false;
		List.AppendList(C);
	}
	return true;
}

bool	UIStringResource::SaveHeader(QIODevice &File)
{
	return true;
}
QString	LanguageStocker::GetExtendParent(const QString &ClassTypeName)
{
	for(CustomWidgetExtend *r=UIExtends.GetFirst();r!=NULL;r=r->GetNext()){
		if(r->CustomWidgetName==ClassTypeName){
			return r->EntendedParent;
		}
	}
	return /**/"";
}

bool	UIStringResource::Compare(LanguageStocker *Parent,UIStringResource *dest)
{
	if(ClassTypeName==/**/"QTableWidget"
	|| Parent->GetExtendParent(ClassTypeName)==/**/"QTableWidget"){
		if(UIClassName==dest->UIClassName
		&& ClassTypeName==dest->ClassTypeName
		&& ControlName==dest->ControlName
		&& PropertyName==dest->PropertyName){
			if(List.GetCount()>=1 && dest->List.GetCount()>=1){
				LanguageString	*s=List.GetFirst();
				LanguageString	*d=dest->List.GetFirst();
				if(*s==*d){
					return true;
				}
			}
			else{
				return true;
			}
		}
	}
	else
	if(ClassTypeName==/**/"QComboBox"
	|| Parent->GetExtendParent(ClassTypeName)==/**/"QComboBox"){
		if(UIClassName==dest->UIClassName
		&& ClassTypeName==dest->ClassTypeName
		&& ControlName==dest->ControlName
		&& PropertyName==dest->PropertyName){
			if(List.GetCount()>=1 && dest->List.GetCount()>=1){
				LanguageString	*s=List.GetFirst();
				LanguageString	*d=dest->List.GetFirst();
				if(*s==*d){
					return true;
				}
			}
			else{
				return true;
			}
		}
	}
	else{
		if(UIClassName==dest->UIClassName && ClassTypeName==dest->ClassTypeName && ControlName==dest->ControlName && PropertyName==dest->PropertyName)
			return true;
	}
	return false;
}


QString	GetSourceFileNameFromLS(QString str)
{
	str=str.simplified();
	if(str.right(3)=="_LS"){
		int	len=str.length()-3;
		return str.left(len);
	}
	return "";
}

int	GetSourceID(QString str)
{
	for(int i=str.length()-1;i>=0;i--){
		QChar	C=str.at(i);
		if(C.isNumber()==false){
			QString	s=str.right(str.length()-(i+1));
			bool	ok;
			int	k=s.toInt(&ok);
			if(ok==false)
				return -1;
			return k;
		}
	}
	return -1;
}

void	LanguageStocker::GetCommentStrings(NPListPack<LanguageString> &List ,QString &commentStr)
{
	int	len=commentStr.length();
	for(int i=2;i<len-2;i++){
		QChar	C=commentStr.at(i);
		if(C.isSpace()==true)
			continue;
		if(C==QChar('\"')){
			for(int j=i+1;j<len-2;j++){
				QChar	D=commentStr.at(j);
				if(D==QChar('\"')){
					QString	K=commentStr.mid(i+1,j-i-1);
					LanguageString	*H=new LanguageString();
					H->Data.append(K);
					List.AppendList(H);
					i=j;
					break;
				}
			}
		}
	}
}


class	SourceAnalyzeParser : public NPList<SourceAnalyzeParser>
{
public:
	QString		Source;
	QString		PWord;
};


bool	LanguageStocker::MakeCPPParser(LanguagePack &LangPack ,QString CPPFile ,NPListPack<SourceAnalyzeParser>	&SPack)
{
	QFile	file(CPPFile);
	if(file.open(QIODevice::ReadOnly | QIODevice::Text)==false)
		return false;

	int	LineNumber=0;
	QTextStream	Text(&file);
	while(Text.atEnd()==false){
		QString LineBuff=Text.readLine();
		for(QChar *fp=LineBuff.data();*fp!=0;){
			QChar	*tp=fp;
			if(*tp==' ' || *tp=='\t'){
				while(*tp==' ' || *tp=='\t')
					tp++;
				SourceAnalyzeParser	*p=new SourceAnalyzeParser();
				int	len=tp-fp;
				int	startp=fp-LineBuff.data();
				p->Source	=p->Source+LineBuff.mid(startp,len);
				p->PWord =" ";
				SPack.AppendList(p);
				fp=tp;
				if(*fp==0)
					break;
			}
			if(*tp=='/' && *(tp+1)=='/'){
				SourceAnalyzeParser	*p=new SourceAnalyzeParser();
				int	startp=fp-LineBuff.data();
				p->Source=LineBuff.mid(startp);
				p->PWord ="//";
				SPack.AppendList(p);
				break;
			}
			else if(*tp=='/' && *(tp+1)=='*'){
				SourceAnalyzeParser	*p=new SourceAnalyzeParser();
				for(;;){
					int	startp=fp-LineBuff.data();
					int	GP=LineBuff.indexOf("*/",startp);
					if(GP>=0){
						p->Source	=p->Source+LineBuff.mid(startp,GP-startp+2);
						p->PWord	="/*";
						fp=&LineBuff.data()[GP+2];
						break;
					}
					p->Source	=p->Source+QString(fp)+QString("\n");
					if(Text.atEnd()==true)
						return false;
					LineBuff=Text.readLine();
						
					fp=LineBuff.data();
				}
				SPack.AppendList(p);
				if(*fp==0)
					break;
			}						
			else{
				QString	nbuff;
				QChar	*np=CutWord(fp ,nbuff);
				SourceAnalyzeParser	*p=new SourceAnalyzeParser();
				int	len=np-fp;
				int	startp=fp-LineBuff.data();
				p->Source=p->Source+LineBuff.mid(startp,len);
				p->PWord	=nbuff;
				SPack.AppendList(p);
				fp=np;
			}
		}
		SourceAnalyzeParser	*p=new SourceAnalyzeParser();
		p->Source	=/**/"\n";
		p->PWord	=/**/"\n";
		SPack.AppendList(p);
		LineNumber++;
	}
	//
	//
	//char	LineBuff[10240];
	//char	nbuff[10240];
	//
	//memset(LineBuff,0,sizeof(LineBuff));
	//
	//LangPack.SetCodec(0);
	//
	//while(file.readLine(LineBuff,sizeof(LineBuff))>0){
	//	for(char *fp=LineBuff;*fp!=0;){
	//		char	*tp=fp;
	//		if(*tp==' ' || *tp=='\t'){
	//			while(*tp==' ' || *tp=='\t')
	//				tp++;
	//			SourceAnalyzeParser	*p=new SourceAnalyzeParser();
	//			int	len=tp-fp;
	//			char	*hp=new char[len+1];
	//			memcpy(hp,fp,len);
	//			hp[len]=0;
	//			p->Source	=p->Source+QString(hp);
	//			p->PWord =" ";
	//			delete	[]hp;
	//			SPack.AppendList(p);
	//			fp=tp;				
	//		}
	//		if(*tp=='/' && *(tp+1)=='/'){
	//			SourceAnalyzeParser	*p=new SourceAnalyzeParser();
	//			p->Source=fp;
	//			p->PWord ="//";
	//			SPack.AppendList(p);
	//			break;
	//		}
	//		else if(*tp=='/' && *(tp+1)=='*'){
	//			SourceAnalyzeParser	*p=new SourceAnalyzeParser();
	//			for(;;){
	//				char	*gp=strstr(fp,"*/");
	//				if(gp!=NULL){
	//					int	len=gp-fp+2;
	//					char	*hp=new char[len+1];
	//					memcpy(hp,fp,len);
	//					hp[len]=0;
	//					p->Source	=p->Source+QString(hp);
	//					delete	[]hp;
	//					p->PWord	="/*";
	//					fp=gp+2;
	//					break;
	//				}
	//				p->Source	=p->Source+QString(fp);
	//				if(file.readLine(LineBuff,sizeof(LineBuff))<=0)
	//					return false;
	//				fp=LineBuff;
	//			}
	//			SPack.AppendList(p);
	//		}						
	//		else{
	//			char	*np=CutWord(fp ,nbuff,sizeof(nbuff));
	//			SourceAnalyzeParser	*p=new SourceAnalyzeParser();
	//			int	len=np-fp;
	//			char	*hp=new char[len+1];
	//			memcpy(hp,fp,len);
	//			hp[len]=0;
	//			p->Source	=p->Source+QString(hp);
	//			delete	[]hp;
	//			p->PWord	=nbuff;
	//			SPack.AppendList(p);
	//			fp=np;
	//		}
	//	}
	//}
	return true;
}

	
bool	LanguageStocker::ScanLoadCPPFile(LanguagePack &LangPack ,QString CPPFile)
{
	NPListPack<SourceAnalyzeParser>	SPack;

	if(MakeCPPParser(LangPack,CPPFile ,SPack)==false)
		return false;
	for(SourceAnalyzeParser *s1=SPack.GetFirst();s1!=NULL;s1=s1->GetNext()){
		SourceAnalyzeParser *s2=s1->GetNext();
		if(s2==NULL)
			break;
		SourceAnalyzeParser *s3=s2->GetNext();
		if(s3==NULL)
			break;
		SourceAnalyzeParser *s4=s3->GetNext();
		if(s4==NULL)
			break;
		SourceAnalyzeParser *s5=s4->GetNext();
		if(s5==NULL)
			break;
		SourceAnalyzeParser *s6=s5->GetNext();
		if(s6==NULL)
			break;
		SourceAnalyzeParser *s7=s6->GetNext();
		if(s7==NULL)
			break;
		SourceAnalyzeParser *s8=s7->GetNext();
		if(s8==NULL)
			break;
		SourceAnalyzeParser *s9=s8->GetNext();
		if(s9==NULL)
			break;
		if(s1->PWord==KeywordForLangSolver
		&& s2->PWord=="." 
		&& s3->PWord=="GetString" 
		&& s4->PWord=="("
		&& s6->PWord==","
		&& s8->PWord==")"
		&& s9->PWord=="/*"){
			LanguageStringResource	*L=new LanguageStringResource();
			L->SourceFileName	=GetSourceFileNameFromLS(s5->Source)+QString("_LS");
			L->ID				=GetSourceID(s7->PWord);
			GetCommentStrings(L->List ,s9->Source);

			LanguageStringResource *k;
			for(k=LStringR.GetFirst();k!=NULL;k=k->GetNext()){
				if(k->Compare(L)==true)
					break;
			}
			if(k==NULL){
				L->SetUsedInSource();
				LStringR.AppendList(L);
			}
			else{
				k->SetUsedInSource();
				delete	L;
			}
		}
	}
	return true;
}
	
bool	LanguageStocker::ReplaceCPPFile(LanguagePack &LangPack ,QString SrcCPPFile ,QString DstCPPFile ,QString ResourceFileName)
{
	NPListPack<SourceAnalyzeParser>	SPack;

	if(MakeCPPParser(LangPack,SrcCPPFile ,SPack)==false)
		return false;

	SourceAnalyzeParser *s1=NULL;
	SourceAnalyzeParser *s2=NULL;
	bool	Changed=false;
	bool	ChangedInclude=false;
	for(SourceAnalyzeParser *s3=SPack.GetFirst();s3!=NULL;s3=s3->GetNext()){
		if((s1==NULL && s2==NULL && s3->PWord.left(1)=="\"")
		|| (s1==NULL && s2!=NULL && s2->Source.contains("/**/")!=true && s3->PWord.left(1)=="\"")
		|| (s1!=NULL && s2!=NULL && s1->PWord!="#" && s2->Source.contains("/**/")!=true && s3->PWord.left(1)=="\"")){			
			SourceAnalyzeParser *p1=s3->GetPrev();
			while(p1!=NULL && p1->PWord==" ")
				p1=p1->GetPrev();
			if(p1!=NULL){
				SourceAnalyzeParser *p2=p1->GetPrev();
				if(p2!=NULL){
					if(p2->PWord=="#" && p1->PWord=="include")
						goto	PreOutputNormal;
				}
			}
			Changed=true;
		}
		else{
PreOutputNormal:;
		}
		s1=s2;
		s2=s3;
	}
	if(ResourceFileName.isEmpty()==false){
		if(ScanCPPFileForInclude(SrcCPPFile,ResourceFileName)==false)
			ChangedInclude=true;
	}

	if(Changed==true || ChangedInclude==true)
		CopyToBak(DstCPPFile);

	LangPack.SetCodec(0);
	QFile	file(DstCPPFile);
	if(file.open(QIODevice::WriteOnly | QIODevice::Text)==false)
		return false;

	QTextCodec *codec=QTextCodec::codecForName ( /**/"UTF-8" );
	QTextCodec *CurrentCodec=QTextCodec::codecForLocale();
	QTextCodec::setCodecForLocale(codec);
	QTextStream	FStr(&file);
	if(ChangedInclude==true){
		QFileInfo	ResourceFileInfo(ResourceFileName);
		QString		ResourceFileNameOnly=ResourceFileInfo.baseName() + QString(".h");
		FStr<<"#include \"";
		FStr<<ResourceFileNameOnly;
		FStr<<"\"\n";
	}
	s1=NULL;
	s2=NULL;
	for(SourceAnalyzeParser *s3=SPack.GetFirst();s3!=NULL;s3=s3->GetNext()){
		if((s1==NULL && s2==NULL && s3->PWord.left(1)=="\"")
		|| (s1==NULL && s2!=NULL && s2->Source.contains("/**/")!=true && s3->PWord.left(1)=="\"")
		|| (s1!=NULL && s2!=NULL && s1->PWord!="#" && s2->Source.contains("/**/")!=true && s3->PWord.left(1)=="\"")){			
			SourceAnalyzeParser *p1=s3->GetPrev();
			while(p1!=NULL && p1->PWord==" ")
				p1=p1->GetPrev();
			if(p1!=NULL){
				SourceAnalyzeParser *p2=p1->GetPrev();
				if(p2!=NULL){
					if(p2->PWord=="#" && p1->PWord=="include")
						goto	OutputNormal;
				}
			}

			FStr<<KeywordForLangSolver;
			FStr<<".GetString(";
			QFileInfo	F(DstCPPFile);
			QString	BName=F.baseName();
			FStr<<BName;
			FStr<<"_LS,LID_";
			int	ID=GetEmptyStringID();
			FStr<<ID;
			FStr<<")/*";
			FStr<<s3->Source;
			FStr<<"*/";
			LanguageStringResource	*L=new LanguageStringResource();
			L->SourceFileName	=BName+QString("_LS");
			L->ID				=ID;
			LanguageString	*J=new LanguageString();
			QString	SContent=s3->PWord;
			SContent.chop(1);
			J->Data.append(SContent.mid(1));
			L->List.AppendList(J);

			L->SetUsedInSource();
			LStringR.AppendList(L);
		}
		else{
OutputNormal:;
			FStr<<s3->Source;
		}
		s1=s2;
		s2=s3;
	}
	QTextCodec::setCodecForLocale(CurrentCodec);

	return true;
}

bool	LanguageStocker::ScanCPPFileForInclude(QString CPPFile ,QString ResourceFileName)
{
	QFile	file(CPPFile);
	if(file.open(QIODevice::ReadOnly | QIODevice::Text)==false)
		return false;
	QTextStream	FStr(&file);

	QFileInfo	ResourceFileInfo(ResourceFileName);
	QString		ResourceFileNameOnly=ResourceFileInfo.baseName() + QString(".h");

	while(FStr.atEnd()==false){
		QString S=FStr.readLine ();
		int	index1=S.indexOf("#",0);
		if(index1<0)
			continue;
		int	index2=S.indexOf("include",index1+1);
		if(index2<0)
			continue;
		int	index3_1=S.indexOf("<",index2+7);
		int	index3_2=S.indexOf("\"",index2+7);
		if(index3_1<0 && index3_2<0)
			continue;
		int	index3=0;
		if(index3_1>0 && index3_2>0)
			index3=min(index3_1,index3_2);
		else if(index3_1>0)
			index3=index3_1;
		else if(index3_2>0)
			index3=index3_2;
		int	index4=S.indexOf(ResourceFileNameOnly,index3+1);
		if(index4<0)
			continue;
		int	index5_1=S.indexOf(">",index4+ResourceFileNameOnly.length());
		int	index5_2=S.indexOf("\"",index4+ResourceFileNameOnly.length());
		if(index5_1<0 && index5_2<0)
			continue;
		return true;
	}
	return false;
}
bool	LanguageStocker::ReplaceCPPFileForInclude(QString CPPFile ,QString ResourceFileName)
{
	QFile	Rfile(CPPFile);
	if(Rfile.open(QIODevice::ReadOnly | QIODevice::Text)==false)
		return false;
	QTextStream	RStr(&Rfile);
	QStringList	CPPSource;

	while(RStr.atEnd()==false){
		QString S=RStr.readLine ();
		CPPSource.append(S);
	}
	Rfile.close();

	QFile	Wfile(CPPFile);
	if(Wfile.open(QIODevice::WriteOnly | QIODevice::Text)==false)
		return false;
	QTextStream	WStr(&Wfile);

	QFileInfo	ResourceFileInfo(ResourceFileName);
	QString		ResourceFileNameOnly=ResourceFileInfo.baseName() + QString(".h");
	WStr<<"#include \"";
	WStr<<ResourceFileNameOnly;
	WStr<<"\"\n";
	for(int i=0;i<CPPSource.count();i++){
		WStr<<CPPSource.value(i);
		WStr<<"\n";
	}

	return true;
}


bool	LanguageStocker::CopyToBak(QString SourceFile)
{
	QFile	Rfile(SourceFile);
	if(Rfile.open(QIODevice::ReadOnly | QIODevice::Text)==false)
		return false;
	QTextStream	RStr(&Rfile);
	QStringList	SourceList;

	while(RStr.atEnd()==false){
		QString S=RStr.readLine ();
		SourceList.append(S);
	}
	Rfile.close();

	QString	BakFileName;
	for(int m=0;;m++){
		BakFileName=SourceFile + QString(".bak")+QString::number(m);
		if(QFile::exists(BakFileName)==false)
			break;
	}
	QFile	Wfile(BakFileName);
	if(Wfile.open(QIODevice::WriteOnly | QIODevice::Text)==false)
		return false;
	QTextStream	WStr(&Wfile);
	for(int i=0;i<SourceList.count();i++){
		WStr<<SourceList.value(i);
		WStr<<"\n";
	}
	return true;
}


LanguageStocker::LanguageStocker(void)
{	
}



bool	LanguageStocker::SaveXLSXFile(QString XLSXFileName,LanguagePack &LangPack)
{
	QStringListListXLSX	XLSXStr;

	QStringList	s0;
	s0.append("IDName");
	s0.append(IDName);
	XLSXStr.append(s0);

	QStringList	s1;
	s1.append("String");
	s1.append(" ");
	for(LanguageClass *t=LangPack.GetFirst();t!=NULL;t=t->GetNext()){
		s1.append(t->LanguageName);
	}
	XLSXStr.append(s1);

	for(LanguageStringResource *s=LStringR.GetFirst();s!=NULL;s=s->GetNext()){
		QStringList	S;
		if(s->SaveCSVFile(S)==false)
			return false;
		XLSXStr.append(S);
	}
	QStringList	s2;
	s2.append("UI");
	s2.append(" ");
	s2.append(" ");
	s2.append(" ");
	for(LanguageClass *t=LangPack.GetFirst();t!=NULL;t=t->GetNext()){
		s2.append(t->LanguageName);
	}
	XLSXStr.append(s2);
	for(UIStringResource *s=UIStringR.GetFirst();s!=NULL;s=s->GetNext()){
		if(s->ClassTypeName==/**/"QTextEdit" && s->PropertyName==/**/"html"){
			QStringList	S;
			QFileInfo	FInfo(XLSXFileName);
			if(s->SaveHtmlCSVFile(S,XLSXFolder,FInfo.baseName(),LangPack)==false)
				return false;
			XLSXStr.append(S);			
		}
		else{
			QStringList	S;
			if(s->SaveCSVFile(S)==false)
				return false;
			XLSXStr.append(S);
		}
	}
	//LoadSettingFile();

	QStringListListXLSX	XLSXDefStr;
	for(StringDefinition *s=LStringDef.GetFirst();s!=NULL;s=s->GetNext()){
		QStringList	h;
		h.append(s->KeyString);
		h.append(QString::number(s->KeyNumber));
		XLSXDefStr.append(h);
	}

	int	LangCount=LangPack.GetCount();
	wchar_t **ExcelFont=new wchar_t *[LangCount];
	for(int i=0;i<LangCount;i++){
		ExcelFont[i]=NULL;
	}
	for(LanguageClass *f=LangPack.GetFirst();f!=NULL;f=f->GetNext()){
		wchar_t	WBuff[100];
		memset(WBuff,0,sizeof(WBuff));
		f->ExcelFont.toWCharArray(WBuff);
		if(f->ColumnNo<LangCount){
			int	Len = wcslen(WBuff);
			ExcelFont[f->ColumnNo]=new wchar_t[Len+1];
			*(ExcelFont[f->ColumnNo] +Len)=L'\0';
			wcscpy(ExcelFont[f->ColumnNo],WBuff);
		}
	}

	if(XLSXStr.SaveFromXLSXFile(XLSXDefStr,XLSXFileName,ExcelFont,LangCount)==false){
		return false;
	}

	for(int i=0;i<LangCount;i++){
		if(ExcelFont[i]!=NULL){
			delete	[]ExcelFont[i];
		}
	}
	delete	[]ExcelFont;

	return true;
}

bool	LanguageStocker::LoadXLSXFile(QString XLSXFileName)
{
	QStringListListXLSX	XLSXStr;

	if(XLSXStr.LoadFromXLSXFile(0,XLSXFileName)==false)
		return false;
	int	N=0;
	if(XLSXStr.value(N).value(0)=="IDName"){
		IDName=XLSXStr.value(N).value(1);
		N++;
	}
	if(XLSXStr.value(N).value(0)=="String"){
		N++;
		for(;N<XLSXStr.count();N++){
			if(XLSXStr.value(N).value(0)=="UI")
				break;
			LanguageStringResource *s=new LanguageStringResource();
			QStringList	SList=XLSXStr.value(N);
			if(SList.count()>1){
				QString	Str=SList[0];
				if(Str.right(3)!=QString("_LS")){
					SList[0]=Str+QString("_LS");
				}
			}

			if(s->LoadCSVFile(SList)==true){
				LanguageStringResource *k;
				for(k=LStringR.GetFirst();k!=NULL;k=k->GetNext()){
					if(k->Compare(s)==true)
						break;
				}
				if(k!=NULL){
					LStringR.RemoveList(k);
					delete	k;
				}
				LStringR.AppendList(s);
			}
		}
	}
	if(XLSXStr.value(N).value(0)=="UI"){
		N++;
		for(;N<XLSXStr.count();N++){
			UIStringResource *s=new UIStringResource();
			QStringList	SList=XLSXStr.value(N);
			if(s->LoadCSVFile(SList)==true){
				UIStringResource *k;
				for(k=UIStringR.GetFirst();k!=NULL;k=k->GetNext()){
					if(k->Compare(this,s)==true)
						break;
				}
				if(k!=NULL){
					UIStringR.RemoveList(k);
					delete	k;
				}
				if(s->ClassTypeName==/**/"QTextEdit" && s->PropertyName==/**/"html"){
					for(LanguageString *L=s->List.GetFirst();L!=NULL;L=L->GetNext()){
						if(L->IsHtml()==false){
							QString	HtmlFileName=XLSXFolder+QDir::separator()+L->GetFirstString();
							QFile	HtmlFile(HtmlFileName);
							if(HtmlFile.open(QIODevice::ReadOnly)==true){
								QTextStream	HtmlStream(&HtmlFile);
								QString	str=HtmlStream.readAll();
								L->ReplaceData(str);
							}
						}
					}
				}
				UIStringR.AppendList(s);
			}
		}
	}
	return true;
}

bool	LanguageStocker::SaveResource(QString RFileName)
{
	QFile	file(RFileName);
	if(file.open(QIODevice::WriteOnly | QIODevice::Text)==false)
		return false;
		
	QFileInfo	FInfo(RFileName);	
	QString	HeaderFileName=FInfo.baseName() + QString(".h");
	char	Buff[500];
	QString2Char(HeaderFileName ,Buff ,sizeof(Buff));

	if(::SaveText(&file,(char *)"#include \"")==false)
		return false;
	if(::SaveText(&file,Buff)==false)
		return false;
	if(::SaveText(&file,(char *)"\"\n")==false)
		return false;


	if(::SaveText(&file,(char *)"LangSolverNew\t")==false)
		return false;
	QString2Char(KeywordForLangSolver,Buff ,sizeof(Buff));
	if(::SaveText(&file,Buff)==false)
		return false;

	if(::SaveText(&file,(char *)"(\"")==false)
		return false;
	QString2Char(IDName ,Buff ,sizeof(Buff));
	if(::SaveText(&file,Buff)==false)
		return false;

	if(::SaveText(&file,(char *)"\");\n")==false)
		return false;
	return true;
}

void	LanguageStocker::BuildExtend(QDomDocument &doc)
{
	UIExtends.RemoveAll();

	QDomElement docElem = doc.documentElement();
	QDomNode n = docElem.firstChild();
	while(!n.isNull()) {
		QDomElement e = n.toElement(); // try to convert the node to an element.
		if(!e.isNull()){
			if(e.tagName()=="customwidgets"){
				BuildCustomWidgets(e);
			}
		}
		n = n.nextSibling();
	}
}
void	LanguageStocker::BuildCustomWidgets(QDomElement &E)
{
	QDomNode n = E.firstChild();
	while(!n.isNull()) {
		QDomElement e = n.toElement(); // try to convert the node to an element.
		if(!e.isNull()) {
			if(e.tagName()=="customwidget"){
				BuildCustomWidget(e);
			}
		}
		n = n.nextSibling();
	}
}
void	LanguageStocker::BuildCustomWidget(QDomElement &E)
{
	QDomNode n = E.firstChild();
	QString	ClassName;
	QString	ParentName;
	while(!n.isNull()) {
		QDomElement e = n.toElement(); // try to convert the node to an element.
		if(!e.isNull()) {
			if(e.tagName()=="class"){
				ClassName=e.text();
			}
			else if(e.tagName()=="extends"){
				ParentName=e.text();
			}
		}
		n = n.nextSibling();
	}
	if(ClassName.isEmpty()==false && ParentName.isEmpty()==false){
		CustomWidgetExtend	*R=new CustomWidgetExtend();
		R->CustomWidgetName	=ClassName;
		R->EntendedParent	=ParentName;
		UIExtends.AppendList(R);
	}
}

bool	LanguageStocker::LoadUIFile(QString RFileName)
{
	QDomDocument	doc(RFileName);
	QFile	file(RFileName);
	if(!file.open(QIODevice::ReadOnly))
		 return false;
	if(!doc.setContent(&file)) {
		file.close();
		return false;
	}
	file.close();

	BuildExtend(doc);

	QString	ClassName;
	QDomElement docElem = doc.documentElement();
	QDomNode n = docElem.firstChild();
	while(!n.isNull()) {
		QDomElement e = n.toElement(); // try to convert the node to an element.
		if(!e.isNull()) {
			if(e.tagName()=="class"){
				 ClassName=e.text();
				 break;
			}
		}
		n = n.nextSibling();
	}
	
	QString	AClassStr;
	QString	ANameStr;
	QString	APropStr;
	while(!n.isNull()) {
		QDomElement e = n.toElement(); // try to convert the node to an element.
		if(!e.isNull()) {
			SearchUIAddText(e,ClassName,AClassStr ,ANameStr ,APropStr);
		}
		n = n.nextSibling();
	}
	return true;
}

void	LanguageStocker::RemoveUnusedHeader(void)
{
	for(LanguageStringResource *s=LStringR.GetFirst();s!=NULL;){
		LanguageStringResource *NextS=s->GetNext();
		if(s->IsUsedInSource()==false){
			LStringR.RemoveList(s);
			delete	s;
			s=NextS;
		}
		else{
			s=s->GetNext();
		}
	}
	for(StringDefinition *d=LStringDef.GetFirst();d!=NULL;){
		LanguageStringResource *s;
		for(s=LStringR.GetFirst();s!=NULL;s=s->GetNext()){
			if(s->GetFileName()==d->KeyString){
				break;
			}
		}
		if(s==NULL){
			StringDefinition *NextD=d->GetNext();
			LStringDef.RemoveList(d);
			delete	d;
			d=NextD;
		}
		else{
			d=d->GetNext();
		}
	}	
	for(LanguageStringResource *s=LStringR.GetFirst();s!=NULL;s=s->GetNext()){
		StringDefinition *d;
		for(d=LStringDef.GetFirst();d!=NULL;d=d->GetNext()){
			if(s->GetFileName()==d->KeyString){
				break;
			}
		}
		if(d==NULL){
			d=new StringDefinition(s->GetFileName(),0);
			LStringDef.AppendList(d);
		}
	}
}

void	LanguageStocker::ReNumberHeader(void)
{
	int	ID=1;
	for(StringDefinition *d=LStringDef.GetFirst();d!=NULL;d=d->GetNext(),ID++){
		d->KeyNumber=ID;
	}
}

void	LanguageStocker::MakeHeaderDefinition(void)
{
	char	Buff[500];
	QStringList		FileNameList;
	for(LanguageStringResource *s=LStringR.GetFirst();s!=NULL;s=s->GetNext()){
		StringDefinition	DefStr;
		s->MakeHeaderDefinition(DefStr);
		if(LStringDef.Search(DefStr.KeyString)==NULL){
			StringDefinition	*a=new StringDefinition(DefStr);
			LStringDef.AppendList(a);
		}
		int	i;
		for(i=0;i<FileNameList.count();i++){
			if(s->GetFileName()==FileNameList.value(i)){
				break;
			}
		}
		if(i>=FileNameList.count()){
			FileNameList.append(s->GetFileName());
		}
	}
	for(int i=0;i<FileNameList.count();i++){
		QString	Str=FileNameList.value(i);
		QString2Char(Str ,Buff ,sizeof(Buff));
		if(Str.right(3)!=QString("_LS")){
			strcat(Buff,"_LS");
		}
		if(LStringDef.Search(Buff)==NULL){
			StringDefinition	*a=new StringDefinition(Buff,0);
			LStringDef.AppendList(a);
		}
	}
	int	ID=0;
	for(StringDefinition *s=LStringDef.GetFirst();s!=NULL;s=s->GetNext()){
		s->KeyNumber=ID;
		ID++;
	}
}

bool	LanguageStocker::SaveHeaderFile(QString RFileName)
{
	QFile	file(RFileName);
	char	Buff[500];
	if(file.open(QIODevice::WriteOnly | QIODevice::Text)==false)
		return false;

	if(::SaveText(&file,(char *)"#if !defined(LSHEADER_H)\n")==false)
		return false;
	if(::SaveText(&file,(char *)"#define LSHEADER_H\n")==false)
		return false;
	if(::SaveText(&file,(char *)"#include \"XLanguageClass.h\"\n")==false)
		return false;
	if(::SaveText(&file,(char *)"extern	LangSolverNew	")==false)
		return false;
	QString2Char(KeywordForLangSolver,Buff ,sizeof(Buff));
	if(::SaveText(&file,Buff)==false)
		return false;
	if(::SaveText(&file,(char *)";\n")==false)
		return false;

	for(StringDefinition *s=LStringDef.GetFirst();s!=NULL;s=s->GetNext()){
		QString2Char(s->KeyString ,Buff ,sizeof(Buff));
		if(::SaveText(&file,(char *)"#define\t")==false)
			return false;
		if(::SaveText(&file,Buff)==false)
			return false;
		sprintf(Buff,"\t%d\n",s->KeyNumber);
		if(::SaveText(&file,Buff)==false)
			return false;
	}

	if(::SaveText(&file,(char *)"#endif\n")==false)
		return false;
	return true;
}

bool	LanguageStocker::LoadHeaderFile(QString RFileName)
{
	QFile	file(RFileName);
	if(file.open(QIODevice::ReadOnly | QIODevice::Text)==false)
		return false;
	QTextStream	TextIn(&file);
	while(TextIn.atEnd()==false){
		QString	TextLine=TextIn.readLine(1000);
		QStringList	TextList	=TextLine.split('\t',Qt::KeepEmptyParts);
		if(TextList[0]=="#define" && TextList.count()>=3){
			QString	KeyText=TextList[1];
			bool	ok;
			int		KeyNumber=TextList[2].toInt(&ok);
			if(ok==true){
				if(LStringDef.Search(KeyText)==NULL){
					StringDefinition	*a=new StringDefinition(KeyText,KeyNumber);
					LStringDef.AppendList(a);
				}
			}
		}
	}
	return true;
}

void	LanguageStocker::SearchUIAddText(QDomElement &docElem ,QString &ClassName ,QString AClassStr ,QString ANameStr,QString APropStr)
{
	QString	CTagName;
	CTagName=docElem.tagName();
	if(CTagName=="widget"){
		QDomAttr	AClass=docElem.attributeNode ("class");
		QDomAttr	AName=docElem.attributeNode ("name");
		if(AClass.isNull()==false && AName.isNull()==false){
			AClassStr=AClass.value();
			ANameStr=AName.value();
		}		
	}
	else if(CTagName=="string"){
		UIStringResource	*R=new UIStringResource();
		R->UIClassName	=ClassName;
		R->ClassTypeName=AClassStr;
		R->ControlName	=ANameStr;
		R->PropertyName	=APropStr;
		LanguageString	*a=new LanguageString();
		a->Data.append(docElem.text());
		R->List.AppendList(a);
		UIStringResource	*k=NULL;
		//if(AClassStr!="QTableWidget"){
			for(k=UIStringR.GetFirst();k!=NULL;k=k->GetNext()){
				if(k->Compare(this,R)==true){
					break;
				}
			}
		//}
		if(k==NULL)
			UIStringR.AppendList(R);
		else
			delete	R;
	}
	else if(CTagName=="property"){
		QDomAttr	AName=docElem.attributeNode ("name");
		if(AName.isNull()==false){
			APropStr=AName.value();
		}
	}
	QDomNode n = docElem.firstChild();
	while(!n.isNull()) {
		QDomElement e = n.toElement(); // try to convert the node to an element.
		if(!e.isNull()) {
			SearchUIAddText(e ,ClassName ,AClassStr ,ANameStr ,APropStr);
		}
		n = n.nextSibling();
	}
}

bool	LanguageStocker::CopyToOld(QString SrcFileName,QString DestFileName)
{
	return true;
}

int		LanguageStocker::GetEmptyStringID(void)
{
	for(int m=0;;m++){
		for(LanguageStringResource *k=LStringR.GetFirst();k!=NULL;k=k->GetNext()){
			if(k->ID==m){
				goto	PNext;
			}
		}
		return m;
PNext:;
	}
	return 0;
}


void	LanguageStocker::ClearStocker(void)
{
	LStringR.RemoveAll();
	UIStringR.RemoveAll();
	LStringDef.RemoveAll();
	CPPFileList.clear();
	UIFileList.clear();
}

