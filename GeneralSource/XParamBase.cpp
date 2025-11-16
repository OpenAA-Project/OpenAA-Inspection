/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XParamBase.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XTypeDef.h"
#include "XParamBase.h"
#include <string.h>
#include "XGeneralFunc.h"
#include <stdio.h>
#include <memory.h>
#include <QFile>
#include <QBuffer>


ParamBase::ParamStruct::ParamStruct(ParamBase* parent, int64* value, const char* category, const char* name, int64  minData, int64  maxData, const char* explain)
	:ParamBase::ParamStruct::ParamStruct(parent, value, category, name, minData, maxData, QString::fromLocal8Bit(explain))
{
}
ParamBase::ParamStruct::ParamStruct(ParamBase* parent, int64* value, const char* category, const char* name, int64  minData, int64  maxData, const QString &explain)
	: Parent(parent)
{
	MaxData=maxData;
	MinData=minData;
	EnableCondition=-1;
	DeleteMode=false;
	pVarInt64	=value;
	rType	=__int64__;
	Name	=name;
	Category=category;
	Explain= explain;
}

ParamBase::ParamStruct::ParamStruct(ParamBase* parent, int32* value, const char* category, const char* name, int32  minData, int32  maxData, const char* explain)
	:ParamBase::ParamStruct::ParamStruct(parent, value, category, name, minData, maxData, QString::fromLocal8Bit(explain))
{}
ParamBase::ParamStruct::ParamStruct(ParamBase *parent,int32	*value ,const char *category ,const char *name ,int32  minData ,int32  maxData, const QString& explain)
	:Parent(parent)
{
	MaxData=maxData;
	MinData=minData;
	EnableCondition=-1;
	DeleteMode=false;
	pVarInt32	=value;
	rType	=__int32__;
	Name	=name;
	Category=category;
	Explain = explain;
}

ParamBase::ParamStruct::ParamStruct(ParamBase* parent, int16* value, const char* category, const char* name, int16  minData, int16  maxData, const char* explain)
	:ParamBase::ParamStruct::ParamStruct(parent, value, category, name, minData, maxData, QString::fromLocal8Bit(explain))
{}
ParamBase::ParamStruct::ParamStruct(ParamBase *parent,int16	*value ,const char *category ,const char *name ,int16  minData ,int16  maxData, const QString& explain)
	:Parent(parent)
{
	MaxData=maxData;
	MinData=minData;
	EnableCondition=-1;
	DeleteMode=false;
	pVarInt16	=value;
	rType	=__int16__;
	Name	=name;
	Category=category;
	Explain = explain;
}

ParamBase::ParamStruct::ParamStruct(ParamBase* parent, WORD* value, const char* category, const char* name, WORD  minData, WORD  maxData, const char* explain)
	:ParamBase::ParamStruct::ParamStruct(parent, value, category, name, minData, maxData, QString::fromLocal8Bit(explain))
{}
ParamBase::ParamStruct::ParamStruct(ParamBase* parent, WORD* value, const char* category, const char* name, WORD  minData, WORD  maxData, const QString& explain)
	: Parent(parent)
{
	MaxData = maxData;
	MinData = minData;
	EnableCondition = -1;
	DeleteMode = false;
	pVarWord = value;
	rType	= __WORD__;
	Name	=name;
	Category=category;
	Explain = explain;
}

ParamBase::ParamStruct::ParamStruct(ParamBase* parent, double* value, const char* category, const char* name, double minData, double maxData, const char* explain)
	:ParamBase::ParamStruct::ParamStruct(parent, value, category, name, minData, maxData, QString::fromLocal8Bit(explain))
{}
ParamBase::ParamStruct::ParamStruct(ParamBase *parent,double	*value ,const char *category ,const char *name ,double minData ,double maxData, const QString& explain)
	:Parent(parent)
{
	MaxData=maxData;
	MinData=minData;
	EnableCondition=-1;
	DeleteMode=false;
	pVarDouble	=value;
	rType	=__double__;
	Name	=name;
	Category=category;
	Explain = explain;
}

ParamBase::ParamStruct::ParamStruct(ParamBase* parent, QString* value, const char* category, const char* name, const char* explain)
	:ParamBase::ParamStruct::ParamStruct(parent, value, category, name, QString::fromLocal8Bit(explain))
{}
ParamBase::ParamStruct::ParamStruct(ParamBase* parent, QString* value, const char* category, const char* name, const QString& explain)
	:Parent(parent)
{
	MaxData=MinData=0;
	EnableCondition=-1;
	DeleteMode=false;
	pVarString	=value;
	rType	=__QString__;
	Name	=name;
	Category=category;
	Explain = explain;
}

ParamBase::ParamStruct::ParamStruct(ParamBase* parent, QColor* value, const char* category, const char* name, const char* explain)
	:ParamBase::ParamStruct::ParamStruct(parent, value, category, name, QString::fromLocal8Bit(explain))
{}
ParamBase::ParamStruct::ParamStruct(ParamBase* parent, QColor* value, const char* category, const char* name, const QString& explain)
	:Parent(parent)
{
	MaxData=MinData=0;
	EnableCondition=-1;
	DeleteMode=false;
	pVarColor	=value;
	rType	=__QColor__;
	Name	=name;
	Category=category;
	Explain = explain;
}

ParamBase::ParamStruct::ParamStruct(ParamBase* parent, ColorLogic* value, const char* category, const char* name, const char* explain)
	:ParamBase::ParamStruct::ParamStruct(parent, value, category, name, QString::fromLocal8Bit(explain))
{}
ParamBase::ParamStruct::ParamStruct(ParamBase* parent, ColorLogic* value, const char* category, const char* name, const QString& explain)
	:Parent(parent)
{
	MaxData=MinData=0;
	EnableCondition=-1;
	DeleteMode=false;
	pVarColorLogic	=value;
	rType	=__ColorLogic__;
	Name	=name;
	Category=category;
	Explain = explain;
}

ParamBase::ParamStruct::ParamStruct(ParamBase* parent, bool* value, const char* category, const char* name, const char* explain)
	:ParamBase::ParamStruct::ParamStruct(parent, value, category, name, QString::fromLocal8Bit(explain))
{}
ParamBase::ParamStruct::ParamStruct(ParamBase* parent, bool* value, const char* category, const char* name, const QString& explain)
	:Parent(parent)
{
	MaxData=MinData=0;
	EnableCondition=-1;
	DeleteMode=false;
	pVarBool	=value;
	rType	=__bool__;
	Name	=name;
	Category=category;
	Explain = explain;
}

ParamBase::ParamStruct::ParamStruct(ParamBase* parent, QStringList* value, const char* category, const char* name, const char* explain)
	:ParamBase::ParamStruct::ParamStruct(parent, value, category, name, QString::fromLocal8Bit(explain))
{}
ParamBase::ParamStruct::ParamStruct(ParamBase* parent, QStringList* value, const char* category, const char* name, const QString& explain)
	:Parent(parent)
{
	MaxData=MinData=0;
	EnableCondition=-1;
	DeleteMode=false;
	pVarStringList	=value;
	rType	=__QStringList__;
	Name	=name;
	Category=category;
	Explain = explain;
}

ParamBase::ParamStruct::ParamStruct(ParamBase* parent, QByteArray* value, const char* category, const char* name, const char* explain)
	:ParamBase::ParamStruct::ParamStruct(parent, value, category, name, QString::fromLocal8Bit(explain))
{}
ParamBase::ParamStruct::ParamStruct(ParamBase* parent, QByteArray* value, const char* category, const char* name, const QString& explain)
	:Parent(parent)
{
	MaxData=MinData=0;
	EnableCondition=-1;
	DeleteMode=false;
	pVarByteArray	=value;
	rType	=__ByteArray__;
	Name	=name;
	Category=category;
	Explain = explain;
}

long	double	ParamBase::ParamStruct::Clip(long double data)
{
	if(data<MinData){
		return MinData;
	}
	if(data>MaxData){
		return MaxData;
	}
	return data;
}

ParamBase::ParamStruct::ParamStruct(ParamBase *parent,ParamBase::ParamStruct &src)
	:Parent(parent)
{
	MinData=src.MinData;
	MaxData=src.MaxData;
	EnableCondition=-1;
	DeleteMode=true;
	rType	=src.rType;
	Name	=src.Name;
	Category=src.Category;
	Explain	=src.Category;
	switch(rType){
		case __int64__:
				pVarInt64	=&VarInt64;
				VarInt64	=(int64)Clip(*src.pVarInt64);
				break;
		case __int32__:
				pVarInt32	=&VarInt32;
				VarInt32	=(int32)Clip(*src.pVarInt32);
				break;
		case __int16__:
				pVarInt16	=&VarInt16;
				VarInt16	=(int16)Clip(*src.pVarInt16);
				break;
		case __double__:
				pVarDouble	=&VarDouble;
				VarDouble	=(double)Clip(*src.pVarDouble);
				break;
		case __QString__:
				pVarString	=&VarString;
				VarString	=*src.pVarString;
				break;
		case __bool__:
				pVarBool	=&VarBool;
				VarBool	=*src.pVarBool;
				break;
		case __FileName__:
				pVarString	=&VarString;
				VarString	=*src.pVarString;
				break;
		case __Path__:
				pVarString	=&VarString;
				VarString	=*src.pVarString;
				break;
		case __QColor__:
				pVarColor	=&VarColor;
				VarColor	=*src.pVarColor;
				break;
		case __WORD__:
				pVarWord	=&VarWord;
				VarWord	=(WORD)Clip(*src.pVarWord);
				break;
		case __ColorLogic__:
				pVarColorLogic	=&VarColorLogic;
				VarColorLogic	=*src.pVarColorLogic;
				break;				
		case __QStringList__:
				pVarStringList	=&VarStringList;
				VarStringList	=*src.pVarStringList;
				break;
		case __ByteArray__:
				pVarByteArray	=&VarByteArray;
				VarByteArray	=*src.pVarByteArray;
				break;
	}
}


ParamBase::ParamStruct::~ParamStruct(void)
{
}

ParamBase::ParamStruct::ParamStruct(ParamBase *parent,char *TxBuff)
	:Parent(parent)
{
	MaxData=MinData=0;
	EnableCondition=-1;
	DeleteMode=true;
	char	CBuff[100000];
	char	*cp,*gp;
	int	len;

	char	*fp=&TxBuff[1];
	cp=strchr(fp,' ');
	len=(unsigned int)(cp-fp);
	memcpy(CBuff,fp,len);
	CBuff[len]=0;
	Category=QString::fromLocal8Bit(CBuff);
	fp=cp+1;
	while(*fp==' ' || *fp=='\t'){
		fp++;
	}


	switch(*TxBuff){
		case 'I':
			rType=__int64__;
			cp=strchr(fp,' ');
			if(cp!=NULL){
				len=(unsigned int)(cp-fp);
				memcpy(CBuff,fp,len);
				CBuff[len]=0;
				pVarInt64	=&VarInt64;
				*pVarInt64=StrToInt64(cp+1);
			}
			break;
		case 'e':
			rType=__int32__;
			cp=strchr(fp,' ');
			if(cp!=NULL){
				len=(unsigned int)(cp-fp);
				memcpy(CBuff,fp,len);
				CBuff[len]=0;
				pVarInt32	=&VarInt32;
				*pVarInt32=StrToInt32(cp+1);
			}
			break;
		case 'i':
			rType=__int16__;
			cp=strchr(fp,' ');
			if(cp!=NULL){
				len=(unsigned int)(cp-fp);
				memcpy(CBuff,fp,len);
				CBuff[len]=0;
				pVarInt16	=&VarInt16;
				*pVarInt16=StrToInt16(cp+1);
			}
			break;
		case 'w':
			rType=__WORD__;
			cp=strchr(fp,' ');
			if(cp!=NULL){
				len=(unsigned int)(cp-fp);
				memcpy(CBuff,fp,len);
				CBuff[len]=0;
				pVarWord	=&VarWord;
				*pVarWord=(WORD)StrToInt32(cp+1);
			}
			break;
		case 'D':
			rType=__double__;
			cp=strchr(fp,' ');
			if(cp!=NULL){
				len=(unsigned int)(cp-fp);
				memcpy(CBuff,fp,len);
				CBuff[len]=0;
				pVarDouble	=&VarDouble;
				*pVarDouble	=StrToDouble(cp+1);
			}
			break;
		case 'S':
			rType=__QString__;
			cp=strchr(fp,' ');
			if(cp!=NULL){
				len=(unsigned int)(cp-fp);
				memcpy(CBuff,fp,len);
				CBuff[len]=0;
				gp=strchr(cp,'\x0a');
				if(gp!=NULL){
					*gp=0;
				}
				pVarString	=&VarString;
				//*pVarString=QString(cp+1);
				*pVarString=QString::fromLocal8Bit(cp+1);
			}
			break;
		case 'C':
			rType=__QColor__;
			cp=strchr(fp,' ');
			if(cp!=NULL){
				len=(unsigned int)(cp-fp);
				memcpy(CBuff,fp,len);
				CBuff[len]=0;
				gp=strchr(cp,'\x0a');
				if(gp!=NULL){
					*gp=0;
				}
				pVarColor	=&VarColor;
				*pVarColor=QString2QColor(QString(cp+1));
			}
			break;
		case 'L':
			rType=__ColorLogic__;
			cp=strchr(fp,' ');
			if(cp!=NULL){
				len=(unsigned int)(cp-fp);
				memcpy(CBuff,fp,len);
				CBuff[len]=0;
				gp=strchr(cp,'\x0a');
				if(gp!=NULL){
					*gp=0;
				}
				pVarColorLogic	=&VarColorLogic;
				*pVarColorLogic	=QString2ColorLogic(QString(cp+1));
			}
			break;
		case 'B':
			rType=__bool__;
			cp=strchr(fp,' ');
			if(cp!=NULL){
				len=(unsigned int)(cp-fp);
				memcpy(CBuff,fp,len);
				CBuff[len]=0;
				pVarBool	=&VarBool;
				if(strnicmp(cp+1,"TRUE",4)==0){
					*pVarBool=true;
				}
				else{
					*pVarBool=false;
				}
			}
			break;
		case 'F':
			rType=__FileName__;
			cp=strchr(fp,' ');
			if(cp!=NULL){
				len=(unsigned int)(cp-fp);
				memcpy(CBuff,fp,len);
				CBuff[len]=0;
				if(strcmp(CBuff,/**/"Name")==0){
					fp=strchr(fp,' ');
					if(fp==NULL){
						break;
					}
					fp++;
					cp=strchr(fp,' ');
					if(cp!=NULL){
						len=(unsigned int)(cp-fp);
						memcpy(CBuff,fp,len);
						CBuff[len]=0;
					}
				}
				if(cp!=NULL){
					gp=strchr(cp,'\x0a');
					if(gp!=NULL){
						*gp=0;
					}
				}
				pVarString	=&VarString;
				if(cp!=NULL){
					//*pVarString=QString(cp+1);
					*pVarString=QString::fromLocal8Bit(cp+1);
				}
			}
			break;
		case 'P':
			rType=__Path__;
			cp=strchr(fp,' ');
			if(cp!=NULL){
				len=(unsigned int)(cp-fp);
				memcpy(CBuff,fp,len);
				CBuff[len]=0;
				if(strcmp(CBuff,/**/"Name")==0){
					fp=strchr(fp,' ');
					if(fp==NULL){
						break;
					}
					fp++;
					cp=strchr(fp,' ');
					if(cp!=NULL){
						len=(unsigned int)(cp-fp);
						memcpy(CBuff,fp,len);
						CBuff[len]=0;
					}
				}
				if(cp!=NULL){
					gp=strchr(cp,'\x0a');
					if(gp!=NULL){
						*gp=0;
					}
				}
				pVarString	=&VarString;
				if(cp!=NULL){
					//*pVarString=QString(cp+1);
					*pVarString=QString::fromLocal8Bit(cp+1);
				}
			}
			break;
		case 'T':
			rType=__QStringList__;
			cp=strchr(fp,' ');
			if(cp!=NULL){
				len=(unsigned int)(cp-fp);
				memcpy(CBuff,fp,len);
				CBuff[len]=0;
				pVarStringList	=&VarStringList;
				cp++;
				bool	Fin=false;
				while(Fin==false){
					char	*kp;
					for(kp=cp;*kp!=0;kp++){
						if(*kp=='\x0a'){
							Fin=true;
							break;
						}
						if(*kp=='\x0c'){
							Fin=true;
							break;
						}
						if(*kp=='\x0b'){
							Fin=false;
							break;
						}
					}
					*kp=0;
					QString	s=QString::fromLocal8Bit(cp);
					//pVarStringList->append(QString(cp));
					pVarStringList->append(s);
					cp=kp+1;
				}
			}
			break;
		case 'A':
			rType=__ByteArray__;
			cp=strchr(fp,' ');
			if(cp!=NULL){
				len=(unsigned int)(cp-fp);
				memcpy(CBuff,fp,len);
				CBuff[len]=0;
				gp=strchr(cp,'\x0a');
				if(gp!=NULL){
					*gp=0;
				}
				pVarByteArray	=&VarByteArray;
				*pVarByteArray	=QString2ByteArray(QString(cp+1));
			}
			break;
	}
	Name=QString::fromLocal8Bit(CBuff);
}

bool	ParamBase::ParamStruct::GetString(char buff[],int Len)
{
	char	ABuff[400];
	char	CBuff[400];
	char	VBuff[100000];
	char	C;
	QString	MStr;
	char	*fp;
	int		VBuffLen,ULen;
	int		i;

	QString2Char(Category	,ABuff ,sizeof(ABuff));
	QString2Char(Name		,CBuff ,sizeof(CBuff));
	switch(rType){
		case __int64__:
			Int64ToStr(*pVarInt64 ,VBuff);
			C='I';
			break;
		case __int32__:
			Int32ToStr(*pVarInt32 ,VBuff);
			C='e';
			break;
		case __int16__:
			Int16ToStr(*pVarInt16 ,VBuff);
			C='i';
			break;
		case __WORD__:
			Int32ToStr((int32)*pVarWord ,VBuff);
			C='w';
			break;
		case __double__:
			sprintf(VBuff,"%lf",*pVarDouble);
			C='D';
			break;
		case __QString__:
			QString2Char(*pVarString ,VBuff ,sizeof(VBuff));
			C='S';
			break;
		case __QColor__:
			MStr=QColor2QString(*pVarColor );
			QString2Char(MStr ,VBuff ,sizeof(VBuff));
			C='C';
			break;
		case __ColorLogic__:
			MStr=ColorLogic2QString(*pVarColorLogic );
			QString2Char(MStr ,VBuff ,sizeof(VBuff));
			C='L';
			break;
		case __bool__:
			if(*pVarBool==true)
				strcpy(VBuff,"TRUE");
			else
				strcpy(VBuff,"false");
			C='B';
			break;
		case __FileName__:
			QString2Char(*pVarString ,VBuff ,sizeof(VBuff));
			C='F';
			break;
		case __Path__:
			QString2Char(*pVarString ,VBuff ,sizeof(VBuff));
			C='P';
			break;
		case __QStringList__:
			fp=VBuff;
			VBuffLen=sizeof(VBuff);
			for(i=0;i<pVarStringList->count();i++){
				QString2Char((*pVarStringList)[i] ,fp,VBuffLen);
				ULen=strlen(fp);
				VBuffLen-=ULen+1;
				if((i+1)<pVarStringList->count())
					fp[ULen]=0x0b;
				else
					fp[ULen]=0x0c;
				fp+=ULen+1;
			}
			*fp=0;
			C='T';
			break;
		case __ByteArray__:
			MStr=QByteArray2QString(*pVarByteArray );
			QString2Char(MStr ,VBuff ,sizeof(VBuff));
			C='A';
			break;
		default:
			C=0;
	}
	if(Len<strlen(CBuff)+strlen(VBuff)+3){
		return(false);
	}
	buff[0]=C;
	strcpy(&buff[1],ABuff);
	strcat(buff," ");
	strcat(buff,CBuff);
	strcat(buff," ");
	strcat(buff,VBuff);
	return(true);
}
QString	ParamBase::ParamStruct::GetValue(void)
{
	char	VBuff[100000];
	char	*fp;
	QString	MStr;
	int		VBuffLen,ULen;
	int		i;

	switch(rType){
		case __int64__:
			Int64ToStr(*pVarInt64 ,VBuff);
			break;
		case __int32__:
			Int32ToStr(*pVarInt32 ,VBuff);
			break;
		case __int16__:
			Int16ToStr(*pVarInt16 ,VBuff);
			break;
		case __WORD__:
			Int32ToStr((int32)*pVarWord ,VBuff);
			break;
		case __double__:
			sprintf(VBuff,"%lf",*pVarDouble);
			break;
		case __QString__:
			return *pVarString;
			//QString2Char(*pVarString ,VBuff ,sizeof(VBuff));
			//break;
		case __QColor__:
			MStr=QColor2QString(*pVarColor);
			QString2Char(MStr ,VBuff ,sizeof(VBuff));
			break;
		case __ColorLogic__:
			MStr=ColorLogic2QString(*pVarColorLogic);
			QString2Char(MStr ,VBuff ,sizeof(VBuff));
			break;
		case __bool__:
			if(*pVarBool==true){
				strcpy(VBuff,"TRUE");
			}
			else{
				strcpy(VBuff,"false");
			}
			break;
		case __FileName__:
			//QString2Char(*pVarString ,VBuff ,sizeof(VBuff));
			return *pVarString;
			//break;
		case __Path__:
			return *pVarString;
			//QString2Char(*pVarString ,VBuff ,sizeof(VBuff));
			//break;
		case __QStringList__:
			fp=VBuff;
			VBuffLen=sizeof(VBuff);
			for(i=0;i<pVarStringList->count();i++){
				QString2Char((*pVarStringList)[i] ,fp,VBuffLen);
				ULen=strlen(fp);
				VBuffLen-=ULen+1;
				if((i+1)<pVarStringList->count())
					fp[ULen]=0x0b;
				else
					fp[ULen]=0x0c;
				fp+=ULen+1;
			}
			*fp=0;
			break;
		case __ByteArray__:
			MStr=QByteArray2QString(*pVarByteArray);
			QString2Char(MStr ,VBuff ,sizeof(VBuff));
			break;
		default:
			VBuff[0]=0;
			break;
	}
	return(VBuff);
}
QStringList	ParamBase::ParamStruct::GetStringList(void)
{
	if(rType==__QStringList__){
		return *pVarStringList;
	}
	else{
		return QStringList();
	}
}

bool	ParamBase::ParamStruct::SetValue(ParamStruct &Dest)
{
	if(rType==Dest.rType){
		switch(rType){
			case __int64__:
				*Dest.pVarInt64	=(int64)Dest.Clip(*pVarInt64);
				break;
			case __int32__:
				*Dest.pVarInt32	=(int32)Dest.Clip(*pVarInt32);
				break;
			case __int16__:
				*Dest.pVarInt16	=(int16)Dest.Clip(*pVarInt16);
				break;
			case __WORD__:
				*Dest.pVarWord	=(WORD)Dest.Clip(*pVarWord);
				break;
			case __double__:
				*Dest.pVarDouble	=(double)Dest.Clip(*pVarDouble);
				break;
			case __QString__:
				*Dest.pVarString	=*pVarString;
				break;
			case __QColor__:
				*Dest.pVarColor	=*pVarColor;
				break;
			case __ColorLogic__:
				*Dest.pVarColorLogic=*pVarColorLogic;
				break;
			case __bool__:
				*Dest.pVarBool	=*pVarBool;
				break;
			case __FileName__:
				*Dest.pVarString	=*pVarString;
				break;
			case __Path__:
				*Dest.pVarString	=*pVarString;
				break;
			case __QStringList__:
				*Dest.pVarStringList	=*pVarStringList;
				break;
			case __ByteArray__:
				*Dest.pVarByteArray	=*pVarByteArray;
				break;
			default:
				return(false);
		}
		return(true);
	}
	if((rType==__FileName__ && Dest.rType==__Path__)
	|| (rType==__Path__ && Dest.rType==__FileName__)){
		*Dest.pVarString=*pVarString;
		return true;
	}
	return(false);
}

void	ParamBase::ParamStruct::SetValue(const QString &str)
{
	char	VBuff[100000];
	char	*cp;
	bool	Fin;
	char	*kp;

	QString2Char(str	,VBuff ,sizeof(VBuff));
	switch(rType){
		case __int64__:
			*pVarInt64=(int64)Clip(StrToInt64(VBuff));
			break;
		case __int32__:
			*pVarInt32=(int32)Clip(StrToInt32(VBuff));
			break;
		case __int16__:
			*pVarInt16=(int16)Clip(StrToInt16(VBuff));
			break;
		case __WORD__:
			*pVarWord=(WORD)Clip(StrToInt32(VBuff));
			break;
		case __double__:
			*pVarDouble=(double)Clip(StrToDouble(VBuff));
			break;
		case __QString__:
			*pVarString=str;
			break;
		case __QColor__:
			*pVarColor=QString2QColor(str);
			break;
		case __ColorLogic__:
			*pVarColorLogic=QString2ColorLogic(str);
			break;
		case __bool__:
			break;
		case __FileName__:
			*pVarString=str;
			break;
		case __Path__:
			*pVarString=str;
			break;
		case __QStringList__:
			QString2Char(str ,VBuff ,sizeof(VBuff));
			cp=VBuff;
			Fin=false;
			while(Fin==false){				
				for(kp=cp;*kp!=0;kp++){
					if(*kp=='\x0a'){
						Fin=true;
						break;
					}
					if(*kp=='\x0c'){
						Fin=true;
						break;
					}
					if(*kp=='\x0b'){
						Fin=false;
						break;
					}
				}
				*kp=0;
				pVarStringList->append(QString(cp));
				cp=kp+1;
			}
			break;
		case __ByteArray__:
			*pVarByteArray=QString2ByteArray(str);
			break;
	}
}
void	ParamBase::ParamStruct::SetValue(const QColor &col)
{
	switch(rType){
		case __QColor__:
			*pVarColor=col;
			break;
	}
}

void	ParamBase::ParamStruct::SetValue(const ColorLogic &col)
{
	switch(rType){
		case __ColorLogic__:
			*pVarColorLogic=col;
			break;
	}
}
void	ParamBase::ParamStruct::SetValue(const QStringList &str)
{
	switch(rType){
		case __QStringList__:
			*pVarStringList=str;
			break;
	}
}

void	ParamBase::ParamStruct::SetBoolValue(bool value)
{
	switch(rType){
		case __bool__:
			*pVarBool=value;
			break;
	}
}
void	ParamBase::ParamStruct::SetValue(const QByteArray &barray)
{
	switch(rType){
		case __ByteArray__:
			pVarByteArray=&VarByteArray;
			*pVarByteArray=barray;
			break;
	}
}

QByteArray	ParamBase::ParamStruct::GetByteArray(void)
{
	//pVarByteArray=&VarByteArray;
	VarByteArray=*pVarByteArray;
	return *pVarByteArray;
}


ParamBase::ParamBase(void)
{
	ParamData.RemoveAll();
}
ParamBase::~ParamBase(void)
{
	ParamData.RemoveAll();
}

void	ParamBase::SetParam(int64  *Value ,const char *category ,const char *name ,const char *explain ,int64  minData ,int64  maxData,int EnableCondition)
{
	ParamStruct	*c=new ParamStruct(this,Value ,category ,name ,minData ,maxData,explain);
	c->EnableCondition=EnableCondition;
	ParamData.AppendList(c);
}
void	ParamBase::SetParam(int32  *Value ,const char *category ,const char *name ,const char *explain ,int32  minData ,int32  maxData,int EnableCondition)
{
	ParamStruct	*c=new ParamStruct(this,Value ,category ,name ,minData ,maxData,explain);
	c->EnableCondition=EnableCondition;
	ParamData.AppendList(c);
}
void	ParamBase::SetParam(int16  *Value ,const char *category ,const char *name ,const char *explain ,int16  minData ,int16  maxData,int EnableCondition)
{
	ParamStruct	*c=new ParamStruct(this,Value ,category ,name ,minData ,maxData,explain);
	c->EnableCondition=EnableCondition;
	ParamData.AppendList(c);
}

void	ParamBase::SetParam(WORD  *Value ,const char *category ,const char *name ,const char *explain ,WORD minData ,WORD maxData,int EnableCondition)
{
	ParamStruct	*c=new ParamStruct(this,Value ,category ,name ,minData ,maxData,explain);
	c->EnableCondition=EnableCondition;
	ParamData.AppendList(c);
}
void	ParamBase::SetParam(double *Value ,const char *category ,const char *name ,const char *explain ,double minData ,double maxData,int EnableCondition)
{
	ParamStruct	*c=new ParamStruct(this,Value,category ,name ,minData ,maxData,explain);
	c->EnableCondition=EnableCondition;
	ParamData.AppendList(c);
}
void	ParamBase::SetParam(QString *Value ,const char *category ,const char *name ,const char *explain ,int EnableCondition)
{
	ParamStruct	*c=new ParamStruct(this,Value,category ,name ,explain);
	c->EnableCondition=EnableCondition;
	ParamData.AppendList(c);
}
void	ParamBase::SetParam(QColor *Value ,const char *category ,const char *name ,const char *explain ,int EnableCondition)
{
	ParamStruct	*c=new ParamStruct(this,Value,category ,name ,explain);
	c->EnableCondition=EnableCondition;
	ParamData.AppendList(c);
}
void	ParamBase::SetParam(ColorLogic *Value ,const char *category ,const char *name ,const char *explain ,int EnableCondition)
{
	ParamStruct	*c=new ParamStruct(this,Value,category ,name ,explain);
	c->EnableCondition=EnableCondition;
	ParamData.AppendList(c);
}
void	ParamBase::SetParam(bool *Value ,const char *category ,const char *name ,const char *explain ,int EnableCondition)
{
	ParamStruct	*c=new ParamStruct(this,Value,category ,name ,explain);
	c->EnableCondition=EnableCondition;
	ParamData.AppendList(c);
}

void	ParamBase::SetParamFileName	(QString *Value ,const char *Category ,const char *name ,const char *explain ,int EnableCondition)
{
	ParamStruct	*c=new ParamStruct(this,Value,Category ,name ,explain);
	c->rType=__FileName__;
	c->EnableCondition=EnableCondition;
	ParamData.AppendList(c);
}
void	ParamBase::SetParamPath		(QString *Value ,const char *Category ,const char *name ,const char *explain ,int EnableCondition)
{
	ParamStruct	*c=new ParamStruct(this,Value,Category ,name ,explain);
	c->rType=__Path__;
	c->EnableCondition=EnableCondition;
	ParamData.AppendList(c);
}
void	ParamBase::SetParam(QStringList *Value ,const char *category ,const char *name ,const char *explain ,int EnableCondition)
{
	ParamStruct	*c=new ParamStruct(this,Value,category ,name ,explain);
	c->EnableCondition=EnableCondition;
	ParamData.AppendList(c);
}
void	ParamBase::SetParam(QByteArray *Value ,const char *category ,const char *name ,const char *explain ,int EnableCondition)
{
	ParamStruct	*c=new ParamStruct(this,Value,category ,name ,explain);
	c->EnableCondition=EnableCondition;
	ParamData.AppendList(c);
}


void	ParamBase::SetParam(int64* Value, const char* category, const char* name, const QString &explain, int64  minData, int64  maxData, int EnableCondition)
{
	ParamStruct* c = new ParamStruct(this, Value, category, name, minData, maxData, explain);
	c->EnableCondition = EnableCondition;
	ParamData.AppendList(c);
}
void	ParamBase::SetParam(int32* Value, const char* category, const char* name, const QString& explain, int32  minData, int32  maxData, int EnableCondition)
{
	ParamStruct* c = new ParamStruct(this, Value, category, name, minData, maxData, explain);
	c->EnableCondition = EnableCondition;
	ParamData.AppendList(c);
}
void	ParamBase::SetParam(int16* Value, const char* category, const char* name, const QString& explain, int16  minData, int16  maxData, int EnableCondition)
{
	ParamStruct* c = new ParamStruct(this, Value, category, name, minData, maxData, explain);
	c->EnableCondition = EnableCondition;
	ParamData.AppendList(c);
}
void	ParamBase::SetParam(WORD* Value, const char* category, const char* name, const QString& explain, WORD minData, WORD maxData, int EnableCondition)
{
	ParamStruct* c = new ParamStruct(this, Value, category, name, minData, maxData, explain);
	c->EnableCondition = EnableCondition;
	ParamData.AppendList(c);
}
void	ParamBase::SetParam(double* Value, const char* category, const char* name, const QString& explain, double minData, double maxData, int EnableCondition)
{
	ParamStruct* c = new ParamStruct(this, Value, category, name, minData, maxData, explain);
	c->EnableCondition = EnableCondition;
	ParamData.AppendList(c);
}
void	ParamBase::SetParam(QString* Value, const char* category, const char* name, const QString& explain, int EnableCondition)
{
	ParamStruct* c = new ParamStruct(this, Value, category, name, explain);
	c->EnableCondition = EnableCondition;
	ParamData.AppendList(c);
}
void	ParamBase::SetParam(QColor* Value, const char* category, const char* name, const QString& explain, int EnableCondition)
{
	ParamStruct* c = new ParamStruct(this, Value, category, name, explain);
	c->EnableCondition = EnableCondition;
	ParamData.AppendList(c);
}
void	ParamBase::SetParam(ColorLogic* Value, const char* category, const char* name, const QString& explain, int EnableCondition)
{
	ParamStruct* c = new ParamStruct(this, Value, category, name, explain);
	c->EnableCondition = EnableCondition;
	ParamData.AppendList(c);
}
void	ParamBase::SetParam(bool* Value, const char* category, const char* name, const QString& explain, int EnableCondition)
{
	ParamStruct* c = new ParamStruct(this, Value, category, name, explain);
	c->EnableCondition = EnableCondition;
	ParamData.AppendList(c);
}

void	ParamBase::SetParamFileName(QString* Value, const char* Category, const char* name, const QString& explain, int EnableCondition)
{
	ParamStruct* c = new ParamStruct(this, Value, Category, name, explain);
	c->rType = __FileName__;
	c->EnableCondition = EnableCondition;
	ParamData.AppendList(c);
}
void	ParamBase::SetParamPath(QString* Value, const char* Category, const char* name, const QString& explain, int EnableCondition)
{
	ParamStruct* c = new ParamStruct(this, Value, Category, name, explain);
	c->rType = __Path__;
	c->EnableCondition = EnableCondition;
	ParamData.AppendList(c);
}
void	ParamBase::SetParam(QStringList* Value, const char* category, const char* name, const QString& explain, int EnableCondition)
{
	ParamStruct* c = new ParamStruct(this, Value, category, name, explain);
	c->EnableCondition = EnableCondition;
	ParamData.AppendList(c);
}
void	ParamBase::SetParam(QByteArray* Value, const char* category, const char* name, const QString& explain, int EnableCondition)
{
	ParamStruct* c = new ParamStruct(this, Value, category, name, explain);
	c->EnableCondition = EnableCondition;
	ParamData.AppendList(c);
}
void	ParamBase::Push(void)
{
	LastParamData.RemoveAll();
	for(ParamStruct *c=ParamData.GetFirst();c!=NULL;c=c->GetNext()){
		ParamStruct *d=new ParamStruct(this,*c);
		LastParamData.AppendList(d);
	}
}
void	ParamBase::Pop(void)
{
	for(ParamStruct *s=LastParamData.GetFirst();s!=NULL;s=s->GetNext()){
		for(ParamStruct *c=ParamData.GetFirst();c!=NULL;c=c->GetNext()){
			if(s->Category==c->Category && s->Name==c->Name){
				s->SetValue(*c);
			}
		}
	}
}

bool	ParamBase::IsChangedCritically(const QString &name)
{
	ParamStruct *src1=NULL;
	ParamStruct *src2=NULL;
	for(ParamStruct *c=ParamData.GetFirst();c!=NULL;c=c->GetNext()){
		if(c->Name==name){
			src1=c;
			break;
		}
	}
	for(ParamStruct *c=LastParamData.GetFirst();c!=NULL;c=c->GetNext()){
		if(c->Name==name){
			src2=c;
			break;
		}
	}
	if(src1!=NULL && src2!=NULL){
		if(src1->GetValue()!=src2->GetValue()){
			return true;
		}
	}
	return false;
}

QString	ParamBase::GetSavedFileName(void)
{
	if(DefaultFileName.isEmpty()==true){
		return GetDefaultFileName();
	}
	return DefaultFileName;
}
void	ParamBase::SetDefaultFileName(const QString &defaultfilename)
{
	DefaultFileName=defaultfilename;
}

bool	ParamBase::SaveParam(QIODevice *f,int EnableCondition)
{
	int32	N=0;
	for(ParamStruct *c=ParamData.GetFirst();c!=NULL;c=c->GetNext()){
		if(EnableCondition!=-1 && EnableCondition!=0 && (EnableCondition & c->EnableCondition)==0){
			continue;
		}
		N++;
	}
	if(f->write((const char *)&N,sizeof(N))!=sizeof(N)){
		return(false);
	}
	for(ParamStruct *c=ParamData.GetFirst();c!=NULL;c=c->GetNext()){
		char	VBuff[100000];
		if(EnableCondition!=-1 && EnableCondition!=0 && (EnableCondition & c->EnableCondition)==0){
			continue;
		}
		const char	*cp="@@";
		if(f->write(cp,strlen(cp))!=strlen(cp)){
			return false;
		}
		if(c->GetString(VBuff,sizeof(VBuff))==false){
			return false;
		}
		if(f->write(VBuff,strlen(VBuff))!=strlen(VBuff)){
			return false;
		}
		const char	*fp="\n";
		if(f->write(fp,strlen(fp))!=strlen(fp)){
			return false;
		}
	}
	return(true);
}

bool	ParamBase::LoadParam(QIODevice *f ,int EnableCondition)
{
	char	VBuff[100000];
	int32	N;
	if(f->read((char *)&N,sizeof(N))!=sizeof(N))
		return(false);
	if(N==0)
		return true;
	int	INumb=0;
	while(f->readLine(VBuff,sizeof(VBuff))>0){
		if(strncmp(VBuff,"@@",2)==0){
			ParamStruct D(this,&VBuff[2]);
			for(ParamStruct *c=ParamData.GetFirst();c!=NULL;c=c->GetNext()){
				if(EnableCondition!=-1 && EnableCondition!=0 && (EnableCondition & c->EnableCondition)==0){
					continue;
				}
				if(c->Category==D.Category &&c->Name==D.Name){
					//if(_CrtCheckMemory()==false)
					//	return(false);
					if(D.SetValue(*c)==false){
						//return(false);
					}
					//if(_CrtCheckMemory()==false)
					//	return(false);
					break;
				}
			}
		}
		INumb++;
		if(INumb>=N){
			break;
		}
	}
	return(true);
}
bool	ParamBase::LoadParam(QIODevice *f ,int StartPoint ,int EndPoint ,int EnableCondition)
{
	char	VBuff[100000];
	int32	N;
	if(f->read((char *)&N,sizeof(N))!=sizeof(N))
		return(false);
	if(N==0)
		return true;
	int	INumb=0;
	while(f->readLine(VBuff,sizeof(VBuff))>0){
		if(strncmp(VBuff,"@@",2)==0){
			ParamStruct D(this,&VBuff[2]);
			int	n=0;
			for(ParamStruct *c=ParamData.GetFirst();c!=NULL;c=c->GetNext(),n++){
				if(EnableCondition!=-1 && EnableCondition!=0 && (EnableCondition & c->EnableCondition)==0){
					continue;
				}
				if(StartPoint<=n && n<EndPoint){
					if(c->Category==D.Category &&c->Name==D.Name){
						if(D.SetValue(*c)==false){
						}
						break;
					}
				}
			}
		}
		INumb++;
		if(INumb>=N){
			break;
		}
	}
	return(true);
}
bool	ParamBase::SaveDefault(const QString &UserPath)
{
	if(WriteEnableToDefaultFile()==true){
		QFile	F(UserPath+::GetSeparator()+GetSavedFileName());
		if(F.open(QIODevice::WriteOnly)==true){
			if(SaveParam(&F)==true){
				return(true);
			}
		}
	}
	return(false);
}
bool	ParamBase::LoadDefault(const QString &UserPath)
{
	if(UserPath.isEmpty()==true){
		return LoadFromFile(UserPath+::GetSeparator()+GetSavedFileName());
	}
	else{
		QFileInfo	FInfo(GetSavedFileName());
		QString		FileName=FInfo.fileName();

		return LoadFromFile(UserPath+::GetSeparator()+FileName);
	}
}
bool	ParamBase::LoadDefault(const QString &UserPath,int StartPoint ,int EndPoint)
{
	if(UserPath.isEmpty()==true){
		return LoadFromFile(UserPath+::GetSeparator()+GetSavedFileName(),StartPoint,EndPoint);
	}
	else{
		QFileInfo	FInfo(GetSavedFileName());
		QString		FileName=FInfo.fileName();
		return LoadFromFile(UserPath+::GetSeparator()+FileName,StartPoint,EndPoint);
	}
}
bool	ParamBase::LoadFromFile(const QString &filename)
{
	bool	Ret=false;
	try{
		QFile	F(filename);
		if(F.open(QIODevice::ReadOnly)==true){
			if(LoadParam(&F,0)==true){
				Ret=true;
			}
		}
	}
	catch(...)
	{
	}

	return Ret;
}
bool	ParamBase::LoadFromFile(const QString &filename,int StartPoint ,int EndPoint)
{
	bool	Ret=false;
	try{
		QFile	F(filename);
		if(F.open(QIODevice::ReadOnly)==true){
			if(LoadParam(&F,StartPoint ,EndPoint,0)==true){
				Ret=true;
			}
		}
	}
	catch(...)
	{
	}

	return Ret;
}
bool	ParamBase::SaveToFile(const QString &filename)
{
	QFile	F(filename);
	if(F.open(QIODevice::WriteOnly)==true){
		if(SaveParam(&F,0)==true){
			return(true);
		}
	}
	return(false);
}


void	ParamBase::CopyFrom(ParamBase &src)
{
	QBuffer	F;
	F.open(QIODevice::ReadWrite);
	src.SaveParam(&F);
	F.seek(0);
	LoadParam(&F);
}


ParamBase::ParamStruct	*ParamBase::Search(const QString &Category ,const QString &Name)
{
	for(ParamStruct *c=ParamData.GetFirst();c!=NULL;c=c->GetNext()){
		if(c->Category==Category && c->Name==Name){
			return(c);
		}
	}
	return(NULL);
}

void	ParamBase::SetCategoryLanguage(const QString &OriginalCategory,const QString &CurrentCategory)
{
	for(CategoryLanguageList *L=CategoryContainer.GetFirst();L!=NULL;L=L->GetNext()){
		if(L->GetOriginalCategory()==OriginalCategory){
			return;
		}
	}
	CategoryLanguageList	*L=new CategoryLanguageList(OriginalCategory,CurrentCategory);
	CategoryContainer.AppendList(L);
}
QString	ParamBase::GetCategoryLabel(const QString &OriginalCategory)
{
	for(CategoryLanguageList *L=CategoryContainer.GetFirst();L!=NULL;L=L->GetNext()){
		if(L->GetOriginalCategory()==OriginalCategory){
			return L->GetCurrentCategory();
		}
	}
	return /**/"";
}
ParamBase::CategoryLanguageList::CategoryLanguageList(const QString &_OriginalCategory,const QString &_CurrentCategory)
{
	OriginalCategory=_OriginalCategory;
	CurrentCategory	=_CurrentCategory;
}
QString	ParamBase::CategoryLanguageList::GetCurrentCategory(void)
{
	return CurrentCategory;
}
QString	ParamBase::CategoryLanguageList::GetOriginalCategory(void)
{
	return OriginalCategory;
}



ParamBaseForAlgorithm::ParamBaseForAlgorithm(void)
{
}
ParamBaseForAlgorithm::~ParamBaseForAlgorithm(void)
{
}
QString	ParamBaseForAlgorithm::GetDataText(void)
{
	return QString("");
}
QString	ParamBaseForAlgorithm::GetDefaultFileName(void)
{
	return QString("");
}
