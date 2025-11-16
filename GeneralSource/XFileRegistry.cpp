/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XFileRegistry.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XTypeDef.h"
#include "XFileRegistry.h"
#include "XGeneralFunc.h"

FileRegistry::RegistryLeaf::RegistryLeaf(void)
{
	DataInt	=NULL;
	DataLen	=0;
	DType	=_Int;
}
FileRegistry::RegistryLeaf::~RegistryLeaf(void)
{
	DeleteData();
	DataLen=0;
}
void	FileRegistry::RegistryLeaf::DeleteData(void)
{
	switch(DType){
		case _Int:
			delete	DataInt;
			break;
		case _String:
			delete	[]DataString;
			break;
		case _StringList:
			delete	[]DataStringList;
			break;
		case _Bool:
			delete	DataBool;
			break;
		case _Double:
			delete	DataDouble;
			break;
		case _BYTEAlloc:
			delete	[]DataAlloc;
			break;
		case _Image:
			delete	[]DataImage;
			break;
		case _Color:
			delete	DataColor;
			break;
		case _Rect:
			delete	DataRect;
			break;
		case _DateTime:
			delete	[]DataDateTime;
			break;
	}
	DataInt=NULL;
}

bool	FileRegistry::RegistryLeaf::Save(QIODevice *f)
{
	BYTE	d=(BYTE)DType;
	if(::Save(f,d)==false){
		return false;
	}
	if(::Save(f,Keyword)==false){
		return false;
	}
	if(::Save(f,DataLen)==false){
		return false;
	}
	switch(DType){
		case _Int:
			if(::Save(f,(char *)DataInt,DataLen)==false){
				return false;
			}
			break;
		case _String:
			if(::Save(f,(char *)DataString,DataLen)==false){
				return false;
			}
			break;
		case _StringList:
			if(::Save(f,(char *)DataStringList,DataLen)==false){
				return false;
			}
			break;
		case _Bool:
			if(::Save(f,(char *)DataBool,DataLen)==false){
				return false;
			}
			break;
		case _Double:
			if(::Save(f,(char *)DataDouble,DataLen)==false){
				return false;
			}
			break;
		case _BYTEAlloc:
			if(::Save(f,(char *)DataAlloc,DataLen)==false){
				return false;
			}
			break;
		case _Image:
			if(::Save(f,(char *)DataImage,DataLen)==false){
				return false;
			}
			break;
		case _Color:
			if(::Save(f,(char *)DataColor,DataLen)==false){
				return false;
			}
			break;
		case _Rect:
			if(::Save(f,(char *)DataRect,DataLen)==false){
				return false;
			}
			break;
		case _DateTime:
			if(::Save(f,(char *)DataDateTime,DataLen)==false){
				return false;
			}
			break;
	}
	return true;
}
bool	FileRegistry::RegistryLeaf::Load(QIODevice *f)
{
	BYTE	d;
	if(::Load(f,d)==false){
		return false;
	}
	DType=(DataType)d;
	if(::Load(f,Keyword)==false){
		return false;
	}
	if(::Load(f,DataLen)==false){
		return false;
	}
	DeleteData();
	int64 Len;
	switch(DType){
		case _Int:
			DataInt=new int32;
			if(::Load(f,(char *)DataInt,Len,(int64)DataLen)==false){
				return false;
			}
			break;
		case _String:
			DataString=new BYTE[DataLen];
			if(::Load(f,(char *)DataString,Len,(int64)DataLen)==false){
				return false;
			}
			break;
		case _StringList:
			DataStringList=new BYTE[DataLen];
			if(::Load(f,(char *)DataStringList,Len,(int64)DataLen)==false){
				return false;
			}
			break;
		case _Bool:
			DataBool=new bool;
			if(::Load(f,(char *)DataBool,Len,(int64)DataLen)==false){
				return false;
			}
			break;
		case _Double:
			DataDouble=new double;
			if(::Load(f,(char *)DataDouble,Len,(int64)DataLen)==false){
				return false;
			}
			break;
		case _BYTEAlloc:
			DataAlloc=new BYTE[DataLen];
			if(::Load(f,(char *)DataAlloc,Len,(int64)DataLen)==false){
				return false;
			}
			break;
		case _Image:
			DataImage=new BYTE[DataLen];
			if(::Load(f,(char *)DataImage,Len,(int64)DataLen)==false){
				return false;
			}
			break;
		case _Color:
			DataColor=new QRgb;
			if(::Load(f,(char *)DataColor,Len,(int64)DataLen)==false){
				return false;
			}
			break;
		case _Rect:
			DataRect=new QRect;
			if(::Load(f,(char *)DataRect,Len,(int64)DataLen)==false){
				return false;
			}
			break;
		case _DateTime:
			DataDateTime=new BYTE[DataLen];
			if(::Load(f,(char *)DataDateTime,Len,(int64)DataLen)==false){
				return false;
			}
			break;
	}	
	return true;
}

bool	FileRegistry::RegistryLeaf::Set(int data)
{
	DeleteData();
	DataInt=new int32;
	DataLen=sizeof(int32);
	*DataInt=data;
	DType=_Int;
	return true;
}
bool	FileRegistry::RegistryLeaf::Set(const QString &data)
{
	DeleteData();
	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	::Save(&Buff,data);
	DataLen=Buff.buffer().length();
	DataString=new BYTE[DataLen];
	memcpy(DataString,Buff.buffer().data(),DataLen);
	DType=_String;
	return true;
}
bool	FileRegistry::RegistryLeaf::Set(const QStringList &data)
{
	DeleteData();
	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	::Save(&Buff,data);
	DataLen=Buff.buffer().length();
	DataStringList=new BYTE[DataLen];
	memcpy(DataStringList,Buff.buffer().data(),DataLen);
	DType=_StringList;
	return true;
}
bool	FileRegistry::RegistryLeaf::Set(bool data)
{
	DeleteData();
	DataBool=new bool;
	DataLen=sizeof(bool);
	*DataBool=data;
	DType=_Bool;
	return true;
}
bool	FileRegistry::RegistryLeaf::Set(double data)
{
	DeleteData();
	DataDouble=new double;
	DataLen=sizeof(double);
	*DataDouble=data;
	DType=_Double;
	return true;
}

bool	FileRegistry::RegistryLeaf::Set(void *data ,int databyte)
{
	DeleteData();
	DataAlloc=new BYTE[databyte];
	DataLen=databyte;
	memcpy(DataAlloc,data,DataLen);
	DType=_BYTEAlloc;
	return true;
}

bool	FileRegistry::RegistryLeaf::Set(const QImage &data)
{
	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	data.save(&Buff,"PNG");

	DeleteData();

	DataImage=new BYTE[Buff.size()];
	DataLen=Buff.size();
	memcpy(DataImage,Buff.data().data(),DataLen);
	DType=_Image;
	return true;
}

bool	FileRegistry::RegistryLeaf::Set(const QColor &data)
{
	DeleteData();
	DataColor=new QRgb;
	DataLen=sizeof(QRgb);
	*DataColor=data.rgba();
	DType=_Color;
	return true;
}
bool	FileRegistry::RegistryLeaf::Set(const QRect &data)
{
	DeleteData();
	DataRect=new QRect;
	DataLen=sizeof(QRect);
	*DataRect=data;
	DType=_Rect;
	return true;
}
bool	FileRegistry::RegistryLeaf::Set(const XDateTime &data)
{
	DeleteData();
	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	::Save(&Buff,data);
	DataLen=Buff.buffer().length();
	DataDateTime=new BYTE[DataLen];
	memcpy(DataDateTime,Buff.buffer().data(),DataLen);
	DType=_DateTime;
	return true;
}

int			FileRegistry::RegistryLeaf::GetInt			(void)
{
	if(DType==_Int){
		return *DataInt;
	}
	return 0;
}
QString		FileRegistry::RegistryLeaf::GetString		(void)
{
	if(DType==_String){
		QBuffer	Buff;
		Buff.setData((const char *)DataString,DataLen);
		Buff.open(QIODevice::ReadOnly);
		QString	ret;
		::Load(&Buff,ret);
		return ret;
	}
	return QString();
}
QStringList	FileRegistry::RegistryLeaf::GetStringList	(void)
{
	if(DType==_StringList){
		QBuffer	Buff;
		Buff.setData((const char *)DataStringList,DataLen);
		Buff.open(QIODevice::ReadOnly);
		QStringList	ret;
		::Load(&Buff,ret);
		return ret;
	}
	return QStringList();
}
bool		FileRegistry::RegistryLeaf::GetBool			(void)
{
	if(DType==_Bool){
		return *DataBool;
	}
	return 0;
}
double		FileRegistry::RegistryLeaf::GetDouble		(void)
{
	if(DType==_Double){
		return *DataDouble;
	}
	return 0;
}
void		*FileRegistry::RegistryLeaf::GetBuffer		(int &databyte)
{
	if(DType==_BYTEAlloc){
		BYTE	*data=new BYTE[DataLen];
		memcpy(data,DataAlloc,DataLen);
		databyte	=DataLen;
		return data;
	}
	return NULL;
}
QImage	FileRegistry::RegistryLeaf::GetImage		(void)
{
	QImage	Ret;
	if(DType==_Image){
		QByteArray	LArray((char *)DataImage,DataLen);
		QBuffer	Buff(&LArray);
		Buff.open(QIODevice::ReadOnly);
		Ret.load(&Buff,"PNG");
	}
	return Ret;
}
QColor		FileRegistry::RegistryLeaf::GetColor		(void)
{
	if(DType==_Color){
		QRgb	b= *DataColor;
		return QColor(b);
	}
	return Qt::black;
}
QRect		FileRegistry::RegistryLeaf::GetRect		(void)
{
	if(DType==_Rect){
		QRect	b= *DataRect;
		return b;
	}
	return QRect();
}
XDateTime	FileRegistry::RegistryLeaf::GetDateTime	(void)
{
	if(DType==_DateTime){
		QBuffer	Buff;
		Buff.setData((const char *)DataDateTime,DataLen);
		Buff.open(QIODevice::ReadOnly);
		XDateTime	ret;
		::Load(&Buff,ret);
		return ret;
	}
	return XDateTime();
}

//============================================================================

bool	FileRegistry::LoadContainer(void)
{
	LeafContainer.RemoveAll();
	QFile	File(FileName);
	if(File.open(QIODevice::ReadOnly)==true){
		while(File.atEnd()==false){
			RegistryLeaf	*L=new RegistryLeaf();
			if(L->Load(&File)==false){
				delete	L;
				return false;
			}
			LeafContainer.AppendList(L);
		}
	}
	return true;
}
bool	FileRegistry::SaveContainer(void)
{
	QFile	File(FileName);
	if(File.open(QIODevice::WriteOnly)==true){
		for(RegistryLeaf *L=LeafContainer.GetFirst();L!=NULL;L=L->GetNext()){
			if(L->Save(&File)==false){
				return false;
			}
		}
	}
	return true;
}

//====================================================================

FileRegistry::FileRegistry(const QString &filename)
{
	FileName=filename;
	LoadContainer();
}

bool	FileRegistry::Save(const QString &keyword ,int data)
{
	for(RegistryLeaf *L=LeafContainer.GetFirst();L!=NULL;L=L->GetNext()){
		if(L->Keyword==keyword){
			L->Set(data);
			if(SaveContainer()==false){
				return false;
			}
			return true;
		}
	}
	RegistryLeaf	*M=new RegistryLeaf();
	M->Keyword=keyword;
	M->Set(data);
	LeafContainer.AppendList(M);
	if(SaveContainer()==false){
		return false;
	}
	return true;
}
bool	FileRegistry::Save(const QString &keyword ,const QString &data)
{
	for(RegistryLeaf *L=LeafContainer.GetFirst();L!=NULL;L=L->GetNext()){
		if(L->Keyword==keyword){
			L->Set(data);
			if(SaveContainer()==false){
				return false;
			}
			return true;
		}
	}
	RegistryLeaf	*M=new RegistryLeaf();
	M->Keyword=keyword;
	M->Set(data);
	LeafContainer.AppendList(M);
	if(SaveContainer()==false){
		return false;
	}
	return true;
}
bool	FileRegistry::Save(const QString &keyword ,const  QStringList &data)
{
	for(RegistryLeaf *L=LeafContainer.GetFirst();L!=NULL;L=L->GetNext()){
		if(L->Keyword==keyword){
			L->Set(data);
			if(SaveContainer()==false){
				return false;
			}
			return true;
		}
	}
	RegistryLeaf	*M=new RegistryLeaf();
	M->Keyword=keyword;
	M->Set(data);
	LeafContainer.AppendList(M);
	if(SaveContainer()==false){
		return false;
	}
	return true;
}
bool	FileRegistry::Save(const QString &keyword ,bool data)
{
	for(RegistryLeaf *L=LeafContainer.GetFirst();L!=NULL;L=L->GetNext()){
		if(L->Keyword==keyword){
			L->Set(data);
			if(SaveContainer()==false){
				return false;
			}
			return true;
		}
	}
	RegistryLeaf	*M=new RegistryLeaf();
	M->Keyword=keyword;
	M->Set(data);
	LeafContainer.AppendList(M);
	if(SaveContainer()==false){
		return false;
	}
	return true;
}
bool	FileRegistry::Save(const QString &keyword ,double data)
{
	for(RegistryLeaf *L=LeafContainer.GetFirst();L!=NULL;L=L->GetNext()){
		if(L->Keyword==keyword){
			L->Set(data);
			if(SaveContainer()==false){
				return false;
			}
			return true;
		}
	}
	RegistryLeaf	*M=new RegistryLeaf();
	M->Keyword=keyword;
	M->Set(data);
	LeafContainer.AppendList(M);
	if(SaveContainer()==false){
		return false;
	}
	return true;
}
bool	FileRegistry::Save(const QString &keyword ,void *data ,int databyte)
{
	for(RegistryLeaf *L=LeafContainer.GetFirst();L!=NULL;L=L->GetNext()){
		if(L->Keyword==keyword){
			L->Set(data,databyte);
			if(SaveContainer()==false){
				return false;
			}
			return true;
		}
	}
	RegistryLeaf	*M=new RegistryLeaf();
	M->Keyword=keyword;
	M->Set(data,databyte);
	LeafContainer.AppendList(M);
	if(SaveContainer()==false){
		return false;
	}
	return true;
}

bool	FileRegistry::Save(const QString &keyword ,const QImage &Img)
{
	for(RegistryLeaf *L=LeafContainer.GetFirst();L!=NULL;L=L->GetNext()){
		if(L->Keyword==keyword){
			L->Set(Img);
			if(SaveContainer()==false){
				return false;
			}
			return true;
		}
	}
	RegistryLeaf	*M=new RegistryLeaf();
	M->Keyword=keyword;
	M->Set(Img);
	LeafContainer.AppendList(M);
	if(SaveContainer()==false){
		return false;
	}
	return true;
}

bool	FileRegistry::Save(const QString &keyword ,const QColor &data)
{
	for(RegistryLeaf *L=LeafContainer.GetFirst();L!=NULL;L=L->GetNext()){
		if(L->Keyword==keyword){
			L->Set(data);
			if(SaveContainer()==false){
				return false;
			}
			return true;
		}
	}
	RegistryLeaf	*M=new RegistryLeaf();
	M->Keyword=keyword;
	M->Set(data);
	LeafContainer.AppendList(M);
	if(SaveContainer()==false){
		return false;
	}
	return true;
}

bool	FileRegistry::Save(const QString &keyword ,const QRect &data)
{
	for(RegistryLeaf *L=LeafContainer.GetFirst();L!=NULL;L=L->GetNext()){
		if(L->Keyword==keyword){
			L->Set(data);
			if(SaveContainer()==false){
				return false;
			}
			return true;
		}
	}
	RegistryLeaf	*M=new RegistryLeaf();
	M->Keyword=keyword;
	M->Set(data);
	LeafContainer.AppendList(M);
	if(SaveContainer()==false){
		return false;
	}
	return true;
}
bool	FileRegistry::Save(const QString &keyword ,const XDateTime &data)
{
	for(RegistryLeaf *L=LeafContainer.GetFirst();L!=NULL;L=L->GetNext()){
		if(L->Keyword==keyword){
			L->Set(data);//416  800011
			if(SaveContainer()==false){
				return false;
			}
			return true;
		}
	}
	RegistryLeaf	*M=new RegistryLeaf();
	M->Keyword=keyword;
	M->Set(data);
	LeafContainer.AppendList(M);
	if(SaveContainer()==false){
		return false;
	}
	return true;
}

int			FileRegistry::LoadRegInt			(const QString &keyword	,int DefaultValue)
{
	for(RegistryLeaf *L=LeafContainer.GetFirst();L!=NULL;L=L->GetNext()){
		if(L->Keyword==keyword){
			return L->GetInt();
		}
	}
	return DefaultValue;
}
QString		FileRegistry::LoadRegString		(const QString &keyword	,const QString &DefaultValue)
{
	for(RegistryLeaf *L=LeafContainer.GetFirst();L!=NULL;L=L->GetNext()){
		if(L->Keyword==keyword){
			return L->GetString();
		}
	}
	return DefaultValue;
}

QStringList	FileRegistry::LoadRegStringList	(const QString &keyword	,const QStringList &DefaultValue)
{
	for(RegistryLeaf *L=LeafContainer.GetFirst();L!=NULL;L=L->GetNext()){
		if(L->Keyword==keyword){
			return L->GetStringList();
		}
	}
	return DefaultValue;
}
bool		FileRegistry::LoadRegBool			(const QString &keyword	,bool DefaultValue)
{
	for(RegistryLeaf *L=LeafContainer.GetFirst();L!=NULL;L=L->GetNext()){
		if(L->Keyword==keyword){
			return L->GetBool();
		}
	}
	return DefaultValue;
}
double		FileRegistry::LoadRegDouble		(const QString &keyword	,double DefaultValue)
{
	for(RegistryLeaf *L=LeafContainer.GetFirst();L!=NULL;L=L->GetNext()){
		if(L->Keyword==keyword){
			return L->GetDouble();
		}
	}
	return DefaultValue;
}
void		*FileRegistry::LoadRegBuffer		(const QString &keyword	,int &databyte)
{
	for(RegistryLeaf *L=LeafContainer.GetFirst();L!=NULL;L=L->GetNext()){
		if(L->Keyword==keyword){
			return L->GetBuffer(databyte);
		}
	}
	databyte=0;
	return NULL;
}
QImage	FileRegistry::LoadRegImage		(const QString &keyword)
{
	for(RegistryLeaf *L=LeafContainer.GetFirst();L!=NULL;L=L->GetNext()){
		if(L->Keyword==keyword){
			return L->GetImage();
		}
	}
	return QImage();
}
QColor		FileRegistry::LoadRegColor		(const QString &keyword	,const QColor &DefaultValue)
{
	for(RegistryLeaf *L=LeafContainer.GetFirst();L!=NULL;L=L->GetNext()){
		if(L->Keyword==keyword){
			return L->GetColor();
		}
	}
	return DefaultValue;
}
QRect	FileRegistry::LoadRegRect		(const QString &keyword)
{
	for(RegistryLeaf *L=LeafContainer.GetFirst();L!=NULL;L=L->GetNext()){
		if(L->Keyword==keyword){
			return L->GetRect();
		}
	}
	return QRect();
}
XDateTime	FileRegistry::LoadRegDateTime		(const QString &keyword)
{
	for(RegistryLeaf *L=LeafContainer.GetFirst();L!=NULL;L=L->GetNext()){
		if(L->Keyword==keyword){
			return L->GetDateTime();
		}
	}
	return XDateTime();
}
