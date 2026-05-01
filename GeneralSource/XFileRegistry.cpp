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


#include "XTypeDef.h"
#include "XFileRegistry.h"
#include "XGeneralFunc.h"

FileRegistry::RegistryLeaf::RegistryLeaf(void)
{
	DataInt	=NULL;
	DataLen	=0;
	DType	=___Int;
}
FileRegistry::RegistryLeaf::~RegistryLeaf(void)
{
	DeleteData();
	DataLen=0;
}
void	FileRegistry::RegistryLeaf::DeleteData(void)
{
	switch(DType){
		case ___Int:
			delete	DataInt;
			break;
		case ___String:
			delete	[]DataString;
			break;
		case ___StringList:
			delete	[]DataStringList;
			break;
		case ___Bool:
			delete	DataBool;
			break;
		case ___Double:
			delete	DataDouble;
			break;
		case ___BYTEAlloc:
			delete	[]DataAlloc;
			break;
		case ___Image:
			delete	[]DataImage;
			break;
		case ___Color:
			delete	DataColor;
			break;
		case ___Rect:
			delete	DataRect;
			break;
		case ___DateTime:
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
		case ___Int:
			if(::Save(f,(char *)DataInt,DataLen)==false){
				return false;
			}
			break;
		case ___String:
			if(::Save(f,(char *)DataString,DataLen)==false){
				return false;
			}
			break;
		case ___StringList:
			if(::Save(f,(char *)DataStringList,DataLen)==false){
				return false;
			}
			break;
		case ___Bool:
			if(::Save(f,(char *)DataBool,DataLen)==false){
				return false;
			}
			break;
		case ___Double:
			if(::Save(f,(char *)DataDouble,DataLen)==false){
				return false;
			}
			break;
		case ___BYTEAlloc:
			if(::Save(f,(char *)DataAlloc,DataLen)==false){
				return false;
			}
			break;
		case ___Image:
			if(::Save(f,(char *)DataImage,DataLen)==false){
				return false;
			}
			break;
		case ___Color:
			if(::Save(f,(char *)DataColor,DataLen)==false){
				return false;
			}
			break;
		case ___Rect:
			if(::Save(f,(char *)DataRect,DataLen)==false){
				return false;
			}
			break;
		case ___DateTime:
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
		case ___Int:
			DataInt=new int32;
			if(::Load(f,(char *)DataInt,Len,(int64)DataLen)==false){
				return false;
			}
			break;
		case ___String:
			DataString=new BYTE[DataLen];
			if(::Load(f,(char *)DataString,Len,(int64)DataLen)==false){
				return false;
			}
			break;
		case ___StringList:
			DataStringList=new BYTE[DataLen];
			if(::Load(f,(char *)DataStringList,Len,(int64)DataLen)==false){
				return false;
			}
			break;
		case ___Bool:
			DataBool=new bool;
			if(::Load(f,(char *)DataBool,Len,(int64)DataLen)==false){
				return false;
			}
			break;
		case ___Double:
			DataDouble=new double;
			if(::Load(f,(char *)DataDouble,Len,(int64)DataLen)==false){
				return false;
			}
			break;
		case ___BYTEAlloc:
			DataAlloc=new BYTE[DataLen];
			if(::Load(f,(char *)DataAlloc,Len,(int64)DataLen)==false){
				return false;
			}
			break;
		case ___Image:
			DataImage=new BYTE[DataLen];
			if(::Load(f,(char *)DataImage,Len,(int64)DataLen)==false){
				return false;
			}
			break;
		case ___Color:
			DataColor=new QRgb;
			if(::Load(f,(char *)DataColor,Len,(int64)DataLen)==false){
				return false;
			}
			break;
		case ___Rect:
			DataRect=new QRect;
			if(::Load(f,(char *)DataRect,Len,(int64)DataLen)==false){
				return false;
			}
			break;
		case ___DateTime:
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
	DType=___Int;
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
	DType=___String;
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
	DType=___StringList;
	return true;
}
bool	FileRegistry::RegistryLeaf::Set(bool data)
{
	DeleteData();
	DataBool=new bool;
	DataLen=sizeof(bool);
	*DataBool=data;
	DType=___Bool;
	return true;
}
bool	FileRegistry::RegistryLeaf::Set(double data)
{
	DeleteData();
	DataDouble=new double;
	DataLen=sizeof(double);
	*DataDouble=data;
	DType=___Double;
	return true;
}

bool	FileRegistry::RegistryLeaf::Set(void *data ,int databyte)
{
	DeleteData();
	DataAlloc=new BYTE[databyte];
	DataLen=databyte;
	memcpy(DataAlloc,data,DataLen);
	DType=___BYTEAlloc;
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
	DType=___Image;
	return true;
}

bool	FileRegistry::RegistryLeaf::Set(const QColor &data)
{
	DeleteData();
	DataColor=new QRgb;
	DataLen=sizeof(QRgb);
	*DataColor=data.rgba();
	DType=___Color;
	return true;
}
bool	FileRegistry::RegistryLeaf::Set(const QRect &data)
{
	DeleteData();
	DataRect=new QRect;
	DataLen=sizeof(QRect);
	*DataRect=data;
	DType=___Rect;
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
	DType=___DateTime;
	return true;
}

int			FileRegistry::RegistryLeaf::GetInt			(void)
{
	if(DType==___Int){
		return *DataInt;
	}
	return 0;
}
QString		FileRegistry::RegistryLeaf::GetString		(void)
{
	if(DType==___String){
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
	if(DType==___StringList){
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
	if(DType==___Bool){
		return *DataBool;
	}
	return 0;
}
double		FileRegistry::RegistryLeaf::GetDouble		(void)
{
	if(DType==___Double){
		return *DataDouble;
	}
	return 0;
}
void		*FileRegistry::RegistryLeaf::GetBuffer		(int &databyte)
{
	if(DType==___BYTEAlloc){
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
	if(DType==___Image){
		QByteArray	LArray((char *)DataImage,DataLen);
		QBuffer	Buff(&LArray);
		Buff.open(QIODevice::ReadOnly);
		Ret.load(&Buff,"PNG");
	}
	return Ret;
}
QColor		FileRegistry::RegistryLeaf::GetColor		(void)
{
	if(DType==___Color){
		QRgb	b= *DataColor;
		return QColor(b);
	}
	return Qt::black;
}
QRect		FileRegistry::RegistryLeaf::GetRect		(void)
{
	if(DType==___Rect){
		QRect	b= *DataRect;
		return b;
	}
	return QRect();
}
XDateTime	FileRegistry::RegistryLeaf::GetDateTime	(void)
{
	if(DType==___DateTime){
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