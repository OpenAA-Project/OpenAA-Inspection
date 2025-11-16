/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XGUI.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#define	ForApplication
#include<QSqlQuery>
#include<QStyleOptionTitleBar>
#include "XGUIInterfaceDLL.h"
#include "XGUI.h"
#include "XErrorCode.h"
#include <string.h>
#include "XGeneralFunc.h"
#include <QBuffer>
#include "XParamGlobal.h"
#include "XDataInLayer.h"
#include "XDataInExe.h"
#include "XDatabase.h"
#include "XFastComm.h"
#include "XGUIInExe.h"
#include "XCameraClass.h"
#include "XIntegrationBase.h"
#include "XIntegrationComm.h"
#include <QApplication>
#include "XCriticalFunc.h"
#include <QScreen>
#include <QGuiApplication>
#include "Regulus64System.h"
#include "XGeneralStocker.h"

EntryPointBase	*MakeEntryPointForGlobal(void)
{
	EntryPointForGlobal	*e	=new EntryPointForGlobal();
	return e;
}

void	GUIInitializer::WaitReadyReadAll(int milisec)
{
	if(CommRoot[0]!=NULL)
		CommRoot[0]->WaitReadyReadAll(milisec);
}

GUIFormBase	*GUIMouseLeftDownInEdit(GUIFormBase *Current ,QMouseEvent * Event);

StructListPack	&StructListPack::operator=(StructListPack &src)
{
	RemoveAll();
	for(StructList *p=src.GetFirst();p!=NULL;p=p->GetNext()){
		StructList	*q=new StructList();
		*q=*p;
		AppendList(q);
	}
	return(*this);
}

void	StructListPack::CopyFrom(StructListPack &src)
{
	for(StructList *p=src.GetFirst();p!=NULL;p=p->GetNext()){
		for(StructList	*q=GetFirst();q!=NULL;q=q->GetNext()){
			if(p->VName==q->VName && p->VType==q->VType){
				q->CopyFrom(*p);
				break;
			}
		}
	}
}

void	StructListPack::GetLineNumb(int &N)
{
	for(StructList *p=GetFirst();p!=NULL;p=p->GetNext()){
		if(p->Opened==true){
			p->StructInstance.GetLineNumb(N);
		}
		N++;
	}
}

StructList	*StructListPack::GetStructItem(int LineNo ,int &depthNo)
{
	int	N=0;
	depthNo=0;
	return(GetStructItem(LineNo,depthNo,N));
}

StructList	*StructListPack::GetStructItem(int LineNo ,int &depthNo ,int &N)
{
	depthNo++;
	for(StructList *p=GetFirst();p!=NULL;p=p->GetNext()){
		if(N==LineNo){
			return(p);
		}
		if(p->Opened==true){
			StructList *ret;
			//if((ret=p->StructInstance.GetStructItem(LineNo,N ,depthNo))!=NULL)
			N++;
			if((ret=p->StructInstance.GetStructItem(LineNo,depthNo ,N))!=NULL){
				return(ret);
			}
		}
		N++;
	}
	depthNo--;
	return(NULL);
}
StructList	*StructListPack::FindStructItem(const QString &VName)
{
	for(StructList *p=GetFirst();p!=NULL;p=p->GetNext()){
		if(p->VName==VName){
			return(p);
		}
		if(p->Opened==true){
			StructList *ret;
			if((ret=p->StructInstance.FindStructItem(VName))!=NULL){
				return ret;
			}
		}
	}
	return NULL;
}
void	StructListPack::ReplaceParam(LayersBase *base)
{
	if(base->GetEntryPoint()!=NULL){
		if(base->GetEntryPoint()->GUIIsEditMode()==false){
			for(StructList *c=GetFirst();c!=NULL;c=c->GetNext()){
				c->ReplaceParam(base);
			}
		}
	}
}

bool	StructListPack::Save(QIODevice *f)
{
	int32	N=GetNumber();
	if(f->write((const char *)&N,sizeof(N))!=sizeof(N)){
		return(false);
	}
	for(StructList *c=GetFirst();c!=NULL;c=c->GetNext()){
		if(c->Save(f)==false){
			return(false);
		}
	}
	return(true);
}
bool	StructListPack::Load(QIODevice *f)
{
	int32	N;
	RemoveAll();
	if(f->read((char *)&N,sizeof(N))!=sizeof(N)){
		return(false);
	}
	for(int i=0;i<N;i++){
		StructList *c=new StructList();
		if(c->Load(f)==false){
			return(false);
		}
		AppendList(c);
	}
	return(true);
}

StructList::StructList(void)
{
	Variable=NULL;
	VType	=_DT_None;
	Opened=false;
	DeleteOk=true;
}
StructList::~StructList(void)
{
	DeleteVariable();
}

void	StructList::DeleteVariable(void)
{
	QString	*pStr;
	if(Variable!=NULL && DeleteOk==true){
		switch(VType){
			case _DT_bool:
				delete	((bool *)Variable);
				break;
			case _DT_byte:
				delete	((BYTE *)Variable);
				break;
			case _DT_short:
				delete	((short *)Variable);
				break;
			case _DT_int:
				delete	((int *)Variable);
				break;
			case _DT_int32:
				delete	((int32 *)Variable);
				break;
			case _DT_int64:
				delete	((int64 *)Variable);
				break;
			case _DT_QString:
				pStr=((QString *)Variable);
				delete	pStr;
				break;
			case _DT_double:
				delete	((double *)Variable);
				break;
			case _DT_float:
				delete	((float *)Variable);
				break;
			case _DT_QColor:			
				delete	((QColor *)Variable);
				break;
			case _DT_QFont:
				delete	((QFont *)Variable);
				break;
			case _DT_enum:
				delete	((QString *)Variable);
				break;
			case _DT_QStringList:
				delete	((QStringList *)Variable);
				break;
			case _DT_struct:
				break;
			case _DT_TunableList:
				delete	((QStringList *)Variable);
				break;
			case _DT_FileName:
				delete	((QString *)Variable);
				break;
			case _DT_PathName:
				delete	((QString *)Variable);
				break;
			case _DT_FileNames:
				delete	((QStringList *)Variable);
				break;
			case _DT_QImage:
				delete	((QImage *)Variable);
				break;
			case _DT_QByteArray:
				delete	((QByteArray *)Variable);
				break;
			case _DT_IntList:
				delete	((IntList *)Variable);
				break;
			default:
				//delete	Variable;
				break;
		}
		Variable=NULL;
	}
}

StructList	&StructList::operator=(StructList &src)
{
	QBuffer	Q;
	Q.open(QIODevice::ReadWrite);
	src.Save(&Q);
	Q.seek(0);
	Load(&Q);
	Opened=src.Opened;
	return(*this);
}

void	StructList::CopyFrom(StructList &src)
{
	QBuffer	Q;
	Q.open(QIODevice::ReadWrite);
	src.Save(&Q);
	Q.seek(0);
	LoadNoClear(&Q);
	Opened=src.Opened;
}

bool	StructList::Save(QIODevice *f)
{
	if(f->write((const char *)&VType,sizeof(VType))!=sizeof(VType)){
		return(false);
	}
	int32	N=Enum.count();
	if(f->write((const char *)&N,sizeof(N))!=sizeof(N)){
		return(false);
	}
	for(int i=0;i<N;i++){
		if(::Save(f,Enum[i])==false){
			return(false);
		}
	}
	if(::Save(f,VName)==false){
		return(false);
	}
	N=StructInstance.GetNumber();
	if(f->write((const char *)&N,sizeof(N))!=sizeof(N)){
		return(false);
	}
	for(StructList *p=StructInstance.GetFirst();p!=NULL;p=p->GetNext()){
		if(p->Save(f)==false){
			return(false);
		}
	}
	QString	Qc;
	switch(VType){
		case _DT_bool:
			if(f->write((const char *)((bool *)Variable),sizeof(bool))!=sizeof(bool)){
				return(false);
			}
			break;
		case _DT_byte:
			if(f->write((const char *)((BYTE *)Variable),sizeof(BYTE))!=sizeof(BYTE)){
				return(false);
			}
			break;
		case _DT_short:
			if(f->write((const char *)((short *)Variable),sizeof(short))!=sizeof(short)){
				return(false);
			}
			break;
		case _DT_int:
			if(f->write((const char *)((int *)Variable),sizeof(int))!=sizeof(int)){
				return(false);
			}
			break;
		case _DT_int32:
			if(f->write((const char *)((int32 *)Variable),sizeof(int32))!=sizeof(int32)){
				return(false);
			}
			break;
		case _DT_int64:
			if(f->write((const char *)((int64 *)Variable),sizeof(int64))!=sizeof(int64)){
				return(false);
			}
			break;
		case _DT_QString:
			if(::Save(f,*((QString *)Variable))==false){
				return(false);
			}
			break;
		case _DT_double:
			if(f->write((const char *)((double *)Variable),sizeof(double))!=sizeof(double)){
				return(false);
			}
			break;
		case _DT_float:
			if(f->write((const char *)((float *)Variable),sizeof(float))!=sizeof(float)){
				return(false);
			}
			break;
		case _DT_QColor:
			Qc=QColor2QString(*(QColor *)Variable);
			if(::Save(f,Qc)==false){
				return(false);
			}
			break;
		case _DT_QFont:
			Qc=((QFont *)Variable)->toString();
			if(::Save(f,Qc)==false){
				return(false);
			}
			break;
		case _DT_enum:
			if(::Save(f,*((QString *)Variable))==false){
				return(false);
			}
			break;
		case _DT_QStringList:
			if(::Save(f,*((QStringList *)Variable))==false){
				return(false);
			}
			break;
		case _DT_IntList:
			if(((IntList *)Variable)->Save(f)==false){
				return(false);
			}
			break;
		case _DT_WidgetList:
			/*
			Qc=((QFont *)Variable)->toString();
			if(::Save(f,Qc)==false)
				return(false);
			*/
			break;
		case _DT_struct:
			break;
		case _DT_TunableList:
			if(::Save(f,*((QStringList *)Variable))==false){
				return(false);
			}
			break;
		case _DT_FileName:
			if(::Save(f,*((QString *)Variable))==false){
				return(false);
			}
			break;
		case _DT_PathName:
			if(::Save(f,*((QString *)Variable))==false){
				return(false);
			}
			break;
		case _DT_FileNames:
			if(::Save(f,*((QStringList *)Variable))==false){
				return(false);
			}
			break;
		case _DT_QImage:
			if(::Save(f,*((QImage *)Variable))==false){
				return(false);
			}
			break;
		case _DT_QByteArray:
			if(::Save(f,*((QByteArray *)Variable))==false){
				return(false);
			}
			break;
		default:
			break;
	}
	return(true);
}
bool	StructList::Load(QIODevice *f)
{
	if(Variable!=NULL){
		DeleteVariable();
	}
	if(f->read((char *)&VType,sizeof(VType))!=sizeof(VType)){
		return(false);
	}
	int32	N;
	Enum.clear();
	if(f->read((char *)&N,sizeof(N))!=sizeof(N)){
		return(false);
	}
	for(int i=0;i<N;i++){
		QString	d;
		if(::Load(f,d)==false){
			return(false);
		}
		Enum.append(d);
	}
	if(::Load(f,VName)==false){
		return(false);
	}
	StructInstance.RemoveAll();
	if(f->read((char *)&N,sizeof(N))!=sizeof(N)){
		return(false);
	}
	for(int i=0;i<N;i++){
		StructList *p=new StructList();
		if(p->Load(f)==false){
			return(false);
		}
		StructInstance.AppendList(p);
	}
	QString	Qc;
	switch(VType){
		case _DT_bool:
			Variable	=new bool;
			DeleteOk=true;
			if(f->read((char *)((bool *)Variable),sizeof(bool))!=sizeof(bool)){
				return(false);
			}
			break;
		case _DT_byte:
			Variable	=new BYTE;
			DeleteOk=true;
			if(f->read((char *)((BYTE *)Variable),sizeof(BYTE))!=sizeof(BYTE)){
				return(false);
			}
			break;
		case _DT_short:
			Variable	=new short;
			DeleteOk=true;
			if(f->read((char *)((short *)Variable),sizeof(short))!=sizeof(short)){
				return(false);
			}
			break;
		case _DT_int:
			Variable	=new int;
			DeleteOk=true;
			if(f->read((char *)((int *)Variable),sizeof(int))!=sizeof(int)){
				return(false);
			}
			break;
		case _DT_int32:
			Variable	=new int32;
			if(f->read((char *)((int32 *)Variable),sizeof(int32))!=sizeof(int32)){
				return(false);
			}
			break;
		case _DT_int64:
			Variable	=new int64;
			DeleteOk=true;
			if(f->read((char *)((int64 *)Variable),sizeof(int64))!=sizeof(int64)){
				return(false);
			}
			break;
		case _DT_QString:
			Variable	=new QString();
			DeleteOk=true;
			if(::Load(f,*((QString *)Variable))==false){
				return(false);
			}
			break;
		case _DT_double:
			Variable	=new double;
			DeleteOk=true;
			if(f->read((char *)((double *)Variable),sizeof(double))!=sizeof(double)){
				return(false);
			}
			break;
		case _DT_float:
			Variable	=new float;
			DeleteOk=true;
			if(f->read((char *)((float *)Variable),sizeof(float))!=sizeof(float)){
				return(false);
			}
			break;
		case _DT_QColor:			
			if(::Load(f,Qc)==false){
				return(false);
			}
			Variable	=new QColor(QString2QColor(Qc));
			DeleteOk=true;
			break;
		case _DT_QFont:
			if(::Load(f,Qc)==false){
				return(false);
			}
			Variable	=new QFont();
			DeleteOk=true;
			((QFont *)Variable)->fromString(Qc);
			break;
		case _DT_enum:
			Variable	=new QString();
			if(::Load(f,*((QString *)Variable))==false){
				return(false);
			}
			break;
		case _DT_IntList:
			Variable	=new IntList();
			if(((IntList *)Variable)->Load(f)==false){
				return(false);
			}
			break;
		case _DT_QStringList:
			Variable	=new QStringList();
			DeleteOk=true;
			if(::Load(f,*((QStringList *)Variable))==false){
				return(false);
			}
			break;
		case _DT_struct:
			break;
		case _DT_TunableList:
			Variable	=new QStringList();
			DeleteOk=true;
			if(::Load(f,*((QStringList *)Variable))==false){
				return(false);
			}
			break;
		case _DT_FileName:
			Variable	=new QString();
			DeleteOk=true;
			if(::Load(f,*((QString *)Variable))==false){
				return(false);
			}
			break;
		case _DT_PathName:
			Variable	=new QString();
			DeleteOk=true;
			if(::Load(f,*((QString *)Variable))==false){
				return(false);
			}
			break;
		case _DT_FileNames:
			Variable	=new QStringList();
			DeleteOk=true;
			if(::Load(f,*((QStringList *)Variable))==false){
				return(false);
			}
			break;
		case _DT_QImage:
			Variable	=new QImage();
			DeleteOk=true;
			if(::Load(f,*((QImage *)Variable))==false){
				return(false);
			}
			break;
		case _DT_QByteArray:
			Variable	=new QByteArray();
			DeleteOk=true;
			if(::Load(f,*((QByteArray *)Variable))==false){
				return(false);
			}
			break;
		default:
			break;
	}
	return(true);
}

bool	StructList::LoadNoClear(QIODevice *f)
{
	DirectValueType	iVType;
	if(f->read((char *)&iVType,sizeof(iVType))!=sizeof(iVType)){
		return(false);
	}
	if(iVType!=VType){
		DeleteVariable();
		VType=iVType;
	}
	int32	N;
	Enum.clear();
	if(f->read((char *)&N,sizeof(N))!=sizeof(N)){
		return(false);
	}
	for(int i=0;i<N;i++){
		QString	d;
		if(::Load(f,d)==false){
			return(false);
		}
		Enum.append(d);
	}
	if(::Load(f,VName)==false){
		return(false);
	}
	if(f->read((char *)&N,sizeof(N))!=sizeof(N)){
		return(false);
	}
	for(int i=0;i<N;i++){
		StructList H;
		if(H.LoadNoClear(f)==false)
			return(false);
		for(StructList *k=StructInstance.GetFirst();k!=NULL;k=k->GetNext()){
			if(k->VName==H.VName){
				k->CopyFrom(H);
				break;
			}
		}
	}

	QString	Qc;
	QString	A;
	QString	B;
	int		t,j;
	QStringList	VariableTunable;
	switch(VType){
		case _DT_bool:
			if(Variable==NULL){
				Variable	=new bool;
				DeleteOk=true;
			}
			if(f->read((char *)((bool *)Variable),sizeof(bool))!=sizeof(bool)){
				return(false);
			}
			break;
		case _DT_byte:
			if(Variable==NULL){
				Variable	=new BYTE;
				DeleteOk=true;
			}
			if(f->read((char *)((BYTE *)Variable),sizeof(BYTE))!=sizeof(BYTE)){
				return(false);
			}
			break;
		case _DT_short:
			if(Variable==NULL){
				Variable	=new short;
				DeleteOk=true;
			}
			if(f->read((char *)((short *)Variable),sizeof(short))!=sizeof(short)){
				return(false);
			}
			break;
		case _DT_int:
			if(Variable==NULL){
				Variable	=new int;
				DeleteOk=true;
			}
			if(f->read((char *)((int *)Variable),sizeof(int))!=sizeof(int)){
				return(false);
			}
			break;
		case _DT_int32:
			if(Variable==NULL){
				Variable	=new int32;
				DeleteOk=true;
			}
			if(f->read((char *)((int32 *)Variable),sizeof(int32))!=sizeof(int32)){
				return(false);
			}
			break;
		case _DT_int64:
			if(Variable==NULL){
				Variable	=new int64;
				DeleteOk=true;
			}
			if(f->read((char *)((int64 *)Variable),sizeof(int64))!=sizeof(int64)){
				return(false);
			}
			break;
		case _DT_QString:
			if(Variable==NULL){
				Variable	=new QString();
				DeleteOk=true;
			}
			if(::Load(f,*((QString *)Variable))==false){
				return(false);
			}
			break;
		case _DT_double:
			if(Variable==NULL){
				Variable	=new double;
				DeleteOk=true;
			}
			if(f->read((char *)((double *)Variable),sizeof(double))!=sizeof(double)){
				return(false);
			}
			break;
		case _DT_float:
			if(Variable==NULL){
				Variable	=new float;
				DeleteOk=true;
			}
			if(f->read((char *)((float *)Variable),sizeof(float))!=sizeof(float)){
				return(false);
			}
			break;
		case _DT_QColor:			
			if(::Load(f,Qc)==false){
				return(false);
			}
			if(Variable==NULL){
				Variable	=new QColor(QString2QColor(Qc));
				DeleteOk=true;
			}
			else{
				*((QColor *)Variable)=QString2QColor(Qc);
			}
			break;
		case _DT_QFont:
			if(::Load(f,Qc)==false){
				return(false);
			}
			if(Variable==NULL){
				Variable	=new QFont();
				DeleteOk=true;
			}
			((QFont *)Variable)->fromString(Qc);		
			break;
		case _DT_enum:
			if(Variable==NULL){
				Variable	=new QString();
				DeleteOk=true;
			}
			if(::Load(f,*((QString *)Variable))==false){
				return(false);
			}
			break;
		case _DT_IntList:
			if(Variable==NULL){
				Variable	=new IntList();
				DeleteOk=true;
			}
			if(((IntList *)Variable)->Load(f)==false){
				return(false);
			}
			break;
		case _DT_QStringList:
			if(Variable==NULL){
				Variable	=new QStringList();
				DeleteOk=true;
			}
			if(::Load(f,*((QStringList *)Variable))==false){
				return(false);
			}
			break;
		case _DT_struct:
			break;
		case _DT_TunableList:
			if(Variable==NULL){
				Variable	=new QStringList();
				DeleteOk=true;
			}
			if(::Load(f,VariableTunable)==false){
				return(false);
			}
			for(t=0;t<((QStringList *)Variable)->count();t++){
				A=(*((QStringList *)Variable))[t];
				for(j=0;j<VariableTunable.count();j++){
					B=VariableTunable[j];
					if(A==B){
						break;
					}
				}
				if(j>=VariableTunable.count()){
					VariableTunable.append(A);
				}
			}
			for(j=0;j<VariableTunable.count();){
				B=VariableTunable[j];
				for(t=0;t<((QStringList *)Variable)->count();t++){
					A=(*((QStringList *)Variable))[t];
					if(A==B){
						break;
					}
				}
				if(t>=((QStringList *)Variable)->count()){
					VariableTunable.removeAt(j);
				}
				else{
					j++;
				}
			}
			(*((QStringList *)Variable))=VariableTunable;
			break;
		case _DT_FileName:
			if(Variable==NULL){
				Variable	=new QString();
				DeleteOk=true;
			}
			if(::Load(f,*((QString *)Variable))==false){
				return(false);
			}
			break;
		case _DT_PathName:
			if(Variable==NULL){
				Variable	=new QString();
				DeleteOk=true;
			}
			if(::Load(f,*((QString *)Variable))==false){
				return(false);
			}
			break;
		case _DT_FileNames:
			if(Variable==NULL){
				Variable	=new QStringList();
				DeleteOk=true;
			}
			if(::Load(f,*((QStringList *)Variable))==false){
				return(false);
			}
			break;
		case _DT_QImage:
			if(Variable==NULL){
				Variable	=new QImage();
				DeleteOk=true;
			}
			if(::Load(f,*((QImage *)Variable))==false){
				return(false);
			}
			break;
		case _DT_QByteArray:
			if(Variable==NULL){
				Variable	=new QByteArray();
				DeleteOk=true;
			}
			if(::Load(f,*((QByteArray *)Variable))==false){
				return(false);
			}
			break;
		default:
			break;
	}
	return(true);
}

void	StructList::SetValue(bool v)
{
	if(VType==_DT_bool){
		*((bool *)Variable)=v;
	}
}
void	StructList::SetValue(BYTE v)
{
	if(VType==_DT_byte){
		*((BYTE *)Variable)=v;
	}
}
void	StructList::SetValue(short v)
{
	if(VType==_DT_short){
		*((short *)Variable)=v;
	}
	else if(VType==_DT_int){
		*((int *)Variable)=v;
	}
}
void	StructList::SetValue(int32 v)
{
	if(VType==_DT_int32){
		*((int32 *)Variable)=v;
	}
	else if(VType==_DT_int){
		*((int *)Variable)=v;
	}
}
void	StructList::SetValue(int64 v)
{
	if(VType==_DT_int64){
		*((int64 *)Variable)=v;
	}
	else if(VType==_DT_int){
		*((int *)Variable)=v;
	}
}
void	StructList::SetValue(const QString &v)
{
	if(VType==_DT_QString){
		*((QString *)Variable)=v;
	}
}
void	StructList::SetValue(double v)
{
	if(VType==_DT_double){
		*((double *)Variable)=v;
	}
}
void	StructList::SetValue(float v)
{
	if(VType==_DT_float){
		*((float *)Variable)=v;
	}
}
void	StructList::SetEnumValue(const QString &v)
{
	if(VType==_DT_enum){
		*((QString *)Variable)=v;
	}
}
void	StructList::SetIntListValue(const IntList &v)
{
	if(VType==_DT_IntList){
		*((IntList *)Variable)=v;
	}
}
void	StructList::SetValue(const QColor &v)
{
	if(VType==_DT_QColor){
		*((QColor *)Variable)=v;
	}
}
void	StructList::SetValue(const QFont &v)
{
	if(VType==_DT_QFont){
		*((QFont *)Variable)=v;
	}
}
void	StructList::SetValue(const QStringList &v)
{
	if(VType==_DT_QStringList){
		*((QStringList *)Variable)=v;
	}
}
void	StructList::SetValue(const QByteArray &v)
{
	if(VType==_DT_QByteArray){
		*((QByteArray *)Variable)=v;
	}
}
void	StructList::SetTunableValue(const QStringList &v)
{
	if(VType==_DT_TunableList){
		*((QStringList *)Variable)=v;
	}
}
	
void	StructList::SetFileNameValue(const QString &v)
{
	if(VType==_DT_FileName){
		*((QString *)Variable)=v;
	}
}
void	StructList::SetPathNameValue(const QString &v)
{
	if(VType==_DT_PathName){
		*((QString *)Variable)=v;
	}
}
void	StructList::SetFileNamesValue(const QStringList &v)
{
	if(VType==_DT_FileNames){
		*((QStringList *)Variable)=v;
	}
}
void	StructList::SetValue(const QImage &v)
{
	if(VType==_DT_QImage){
		*((QImage *)Variable)=v;
	}
}

bool	StructList::GetBool(void)
{
	return *((bool *)Variable);
}
BYTE	StructList::GetByte(void)
{
	return *((BYTE *)Variable);
}
short	StructList::GetShort(void)
{
	return *((short *)Variable);
}
int	StructList::GetInt(void)
{
	return *((int *)Variable);
}
int32	StructList::GetInt32(void)
{
	return *((int32 *)Variable);
}
int64	StructList::GetInt64(void)
{
	return *((int64 *)Variable);
}
QString	StructList::GetQString(void)
{
	return *((QString *)Variable);
}
double	StructList::GetDouble(void)
{
	return *((double *)Variable);
}
float	StructList::GetFloat(void)
{
	return *((float *)Variable);
}
QString	StructList::GetEnum(void)
{
	return *((QString *)Variable);
}
QColor	StructList::GetColor(void)
{
	return *((QColor *)Variable);
}
QFont	StructList::GetFont(void)
{
	return *((QFont *)Variable);
}
QStringList	StructList::GetQStringList(void)
{
	return *((QStringList *)Variable);
}
QStringList	StructList::GetTunableList(void)
{
	return *((QStringList *)Variable);
}
QImage		StructList::GetQImage(void)
{
	return *((QImage *)Variable);
}
QByteArray		StructList::GetQByteArray(void)
{
	return *((QByteArray *)Variable);
}
IntList	StructList::GetIntList(void)
{
	return *((IntList *)Variable);
}

void	StructList::ReplaceParam(LayersBase *base)
{
	if(VType==_DT_QString){
		QString	s=GetQString();
		QString	Ret=ReplaceParam(s,base);
		SetValue(Ret);
	}
	else if(VType==_DT_QStringList){
		QStringList	s=GetQStringList();
		QStringList	Ret;
		for(int i=0;i<s.count();i++){
			QString	R=ReplaceParam(s[i],base);
			Ret.append(R);
		}
		SetValue(Ret);
	}
	else if(VType==_DT_TunableList){
		QStringList	s=GetTunableList();
		QStringList	Ret;
		for(int i=0;i<s.count();i++){
			QString	R=ReplaceParam(s[i],base);
			Ret.append(R);
		}
		SetTunableValue(Ret);
	}
	StructInstance.ReplaceParam(base);
}

QString	StructList::ReplaceParam(const QString &Src ,LayersBase *base)
{
	QString	s=Src;
	bool	Changed;
	do{
		Changed=false;
		int	k1=s.indexOf(/**/"$$");
		if(0<=k1){
			int	k2=s.indexOf(/**/"$$",k1+2);
			if(2<=k2){
				QString Key=s.mid(k1+2,k2-k1-2);
				QString	L1=s.mid(0,k1);
				QString	L2=s.mid(k2+2);
				Key=Key.toUpper();
				if(Key==QString(/**/"MachineCode").toUpper()){
					s=L1+QString::number(base->GetMachineID())+L2;
					Changed=true;
				}
				else
				if(Key==QString(/**/"MachineID").toUpper()){
					s=L1+QString::number(base->GetMachineID())+L2;
					Changed=true;
				}
				else
				if(Key==QString(/**/"MachineName").toUpper()){
					QString MacNetID;
					QString MacName;
					QString MacVersion;
					QString MacRemark;
					if(base->SQLGetMachineInfo(base->GetMachineID()
									 ,MacNetID
									 ,MacName
									 ,MacVersion
									 ,MacRemark)==true){
						s=L1+MacName+L2;
						Changed=true;
					}
				}
				else
				if(Key.left(11)==QString(/**/"MachineName").toUpper()){
					QString	NStr=Key.mid(11);
					bool	ok;
					const int	MacID=NStr.toInt(&ok);
					if(ok==true){
						QString MacNetID;
						QString MacName;
						QString MacVersion;
						QString MacRemark;
						if(base->SQLGetMachineInfo(MacID
										 ,MacNetID
										 ,MacName
										 ,MacVersion
										 ,MacRemark)==true){
							s=L1+MacName+L2;
							Changed=true;
						}
					}
				}
				else
				if(Key==QString(/**/"Year").toUpper()){
					QDateTime	d=QDateTime::currentDateTime();
					s=L1+QString::number(d.date().year())+L2;
					Changed=true;
				}
				else
				if(Key==QString(/**/"Month").toUpper()){
					QDateTime	d=QDateTime::currentDateTime();
					s=L1+QString::number(d.date().month())+L2;
					Changed=true;
				}
				else
				if(Key==QString(/**/"Day").toUpper()){
					QDateTime	d=QDateTime::currentDateTime();
					s=L1+QString::number(d.date().day())+L2;
					Changed=true;
				}
				else
				if(Key==QString(/**/"Date").toUpper()){
					QDateTime	d=QDateTime::currentDateTime();
					s=L1+d.date().toString(/**/"yyMMdd")+L2;
					Changed=true;
				}
				else
				if(Key==QString(/**/"Hour").toUpper()){
					QDateTime	d=QDateTime::currentDateTime();
					s=L1+QString::number(d.time().hour())+L2;
					Changed=true;
				}
				else
				if(Key==QString(/**/"Minute").toUpper()){
					QDateTime	d=QDateTime::currentDateTime();
					s=L1+QString::number(d.time().minute())+L2;
					Changed=true;
				}
				else
				if(Key==QString(/**/"Second").toUpper()){
					QDateTime	d=QDateTime::currentDateTime();
					s=L1+QString::number(d.time().second())+L2;
					Changed=true;
				}
				else
				if(Key==QString(/**/"Time").toUpper()){
					QDateTime	d=QDateTime::currentDateTime();
					s=L1+d.time().toString(/**/"hhmmss")+L2;
					Changed=true;
				}
				else
				if(Key==QString(/**/"DateTime").toUpper()){
					QDateTime	d=QDateTime::currentDateTime();
					s=L1+d.toString(/**/"yyMMdd-hhmmss")+L2;
					Changed=true;
				}
			}
		}
	}while(Changed==true);

	return s;
}

//===============================================================================================
bool	GuiAdditionalDatabase::InitialAdditionalFieldFromGUI(const QSqlDatabase &DB)
{
	try {
		QString	s = QString(/**/"select ") +FieldName + QString(/**/" FROM ") + TableName;
		QSqlQuery query(s, DB);
		if (query.next() == true) {
			return true;
		}
	}
	catch (...) {
	}
	{
		QString	s = QString(/**/"alter table ") + TableName + QString(/**/" ADD ") + FieldName;
		if (DefaultData.type() == QVariant::Int) {
			s = s + QString(/**/" INTEGER default ") + QString::number(DefaultData.toInt());
		}
		else if (DefaultData.type() == QVariant::Double) {
			s = s + QString(/**/" DOUBLE PRECISION ");
		}
		else if (DefaultData.type() == QVariant::String) {
			s = s + QString(/**/" VARCHAR(64) ");
		}
		else if (DefaultData.type() == QVariant::DateTime) {
			s = s + QString(/**/" TIMESTAMP ");
		}
		else if (DefaultData.type() == QVariant::ByteArray) {
			s = s + QString(/**/" BLOB SUB_TYPE 0 SEGMENT SIZE 80 ");
		}
		else if (DefaultData.type() == QVariant::StringList) {
			s = s + QString(/**/" BLOB SUB_TYPE 0 SEGMENT SIZE 80 ");
		}
		else {
			return false;
		}
		QSqlQuery	query(DB);
		query.prepare(s);
		if (query.exec() == false) {
			//return false;
		}
	}
	return true;
}

bool	GeneralStocker::InitialAdditionalFieldFromGUI(QSqlDatabase &DB)
{
	bool	ret=true;
	if(DLL_GetGuiAdditionalDatabase!=NULL){
		NPListPack<GuiAdditionalDatabase> FieldList;
		DLL_GetGuiAdditionalDatabase(FieldList);
		for(GuiAdditionalDatabase *d=FieldList.GetFirst();d!=NULL;d=d->GetNext()){
			if(d->InitialAdditionalFieldFromGUI(DB)==false){
				ret=false;
			}
		}
	}
	return ret;
}


bool	GeneralStockerContainer::InitialAdditionalFieldFromGUI(QSqlDatabase &DB,QString &ErrorMsg)
{
	int	R = 0;
	for(GeneralStocker *s=GetFirst();s!=NULL;s=s->GetNext()){
		if(s->InitialAdditionalFieldFromGUI(DB)==false){
			ErrorMsg = QString("Error (")
				+ s->Name
				+ QString(") makes stop in InitialAdditionalFieldFromGUI")
				+ QString("(")
				+ QString::number(R)
				+ QString(")");
			return false;
		}
	}
	return true;
}
//===============================================================================================

GuiDLLItem::GuiDLLItem(LayersBase *Base)
:ServiceForLayers(Base)
{
	DLL_GetName					=NULL;
	DLL_GetDLLType				=NULL;
	DLL_GetVersion				=NULL;
	DLL_GetExplain				=NULL;
	DLL_SetLanguage				=NULL;
	DLL_SetLanguageCommon		=NULL;
	DLL_CheckCopyright			=NULL;
	DLL_Initial					=NULL;
	DLL_InitialQt				=NULL;
	DLL_Close					=NULL;
	DLL_ReceivePacket			=NULL;
	DLL_ReceivePacketDirectComm	=NULL;
	DLL_ReceiveIntegrationPacket=NULL;

	DLL_CreateInstance			=NULL;
	DLL_DeleteInstance			=NULL;
	DLL_GetPropertyString		=NULL;
	DLL_GetGuiAdditionalDatabase=NULL;

	DLL_GetIcon					=NULL;
	DLL_EntryAlgorithm			=NULL;
	DLL_AssociateComponent		=NULL;
	DLL_RegistMacroFunction		=NULL;
	
	icondata					=NULL;
	UsedInGUI					=false;
}

GuiDLLItem::~GuiDLLItem(void)
{
	if(ReEntrantDLL==true)
		return;
	ReEntrantDLL=true;

	if(DllLib.isLoaded()==true){
		DllLib.unload();
	}
	static	int	ForDebug=0;
	if(ForDebug!=0){
		LayersBase	*L=GetLayersBase();
		if(L!=NULL){
			L->ReleaseAll();
		}
	}

	icondata=NULL;
	ReEntrantDLL=false;
}
bool	GuiDLLItem::SetLanguage(GUIFormBase *Handle ,const QString &MemberName,LanguageStringList *s)
{
	struct	PropertyClass	PClass[1000];
	int32	n=GetPropertyString(Handle ,PClass ,sizeof(PClass)/sizeof(PClass[0]));
	if(n>0){
		for(int i=0;i<n;i++){
			if(PClass[i].VariableNameWithRoute==MemberName
			&& PClass[i].Type==/**/"QString"){
				QString	*str=(QString *)PClass[i].Pointer;
				*str=s->Text;
				return true;
			}
			else
			if(PClass[i].VariableNameWithRoute==MemberName
			&& PClass[i].Type==/**/"QStringList"){
				QStringList	*str=(QStringList *)PClass[i].Pointer;
				*str=s->TextList;
				return true;
			}
		}
	}
	return false;
}

void	GuiDLLItem::PickupGUILanguage(GUIFormBase *Handle ,GUILanguageContainer &GUILanguageContainerInst)
{
	struct	PropertyClass	PClass[1000];
	int32	n=GetPropertyString(Handle ,PClass ,sizeof(PClass)/sizeof(PClass[0]));
	if(n>0){
		for(int i=0;i<n;i++){
			if(PClass[i].Translatable==true
			&& PClass[i].Type==/**/"QString"){
				GUILanguageList *s=GUILanguageContainerInst.Find(GetDLLRoot()
																,GetDLLName()
																,Handle->GetName()
																,PClass[i].VariableNameWithRoute);
				if(s==NULL){
					s=new GUILanguageList();
					s->DLLRoot	=GetDLLRoot();
					s->DLLName	=GetDLLName();
					s->InstName	=Handle->GetName();
					s->MemberName=PClass[i].VariableNameWithRoute;
					GUILanguageContainerInst.AppendList(s);
				}
				LanguageStringList	*SList=s->LanguageText.FindLanguage(GetLayersBase()->GetLanguageCode());
				if(SList==NULL){
					SList=new LanguageStringList();
					SList->LanguageCode=GetLayersBase()->GetLanguageCode();
					s->LanguageText.AppendList(SList);
				}
				QString	*str=((QString *)PClass[i].Pointer);
				SList->Text=*str;
			}
			else
			if(PClass[i].Translatable==true
			&& PClass[i].Type==/**/"QStringList"){
				GUILanguageList *s=GUILanguageContainerInst.Find(GetDLLRoot()
																,GetDLLName()
																,Handle->GetName()
																,PClass[i].VariableNameWithRoute);
				if(s==NULL){
					s=new GUILanguageList();
					s->DLLRoot	=GetDLLRoot();
					s->DLLName	=GetDLLName();
					s->InstName	=Handle->GetName();
					s->MemberName=PClass[i].VariableNameWithRoute;
					GUILanguageContainerInst.AppendList(s);
				}
				LanguageStringList	*SList=s->LanguageText.FindLanguage(GetLayersBase()->GetLanguageCode());
				if(SList==NULL){
					SList=new LanguageStringList();
					SList->LanguageCode=GetLayersBase()->GetLanguageCode();
					s->LanguageText.AppendList(SList);
				}
				QStringList	*str=(QStringList *)PClass[i].Pointer;
				SList->TextList=*str;
			}
		}
	}
}

bool	GuiDLLItem::Close(void)
{
	if(DLL_Close!=NULL){
		DLL_Close();
	}
	return true;
}
bool	GuiDLLItemContainer::Close(void)
{
	bool	Ret=true;
	for(GuiDLLItem *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Close()==false){
			return Ret;
		}
	}
	return Ret;
}

#ifdef _MSC_VER
#define	DEFFUNCINEXE		__declspec(dllexport)
#endif

void	GUIFastComm::SlotReceived(int ID ,int Cmd)
{
	RecList	*R=UnpackTopRxBuff(ID);
	if(R!=NULL){
		const char	*EmitterRoot;
		char	EmitterRootBuff[100];
		const char	*EmitterName;
		char	EmitterNameBuff[100];
		const char	*CmdClass;
		char	CmdClassBuff[100];
		BYTE	*fp	=R->GetClassNamePointer(EmitterRootBuff ,EmitterNameBuff ,CmdClassBuff,sizeof(CmdClassBuff));
		if(fp==NULL){
			delete	R;
			return;
		}

		ErrorCodeList	ErrorData((ErrorCodeList::CautionLevel)R->ErrorLevel);
		if(ErrorData.GetLevel()!=ErrorCodeList::_None){
			fp	=R->GetError(fp,ErrorData);
		}
		LayersBase	*LBase=GetLayersBase()->GetTopLayersBase()->GetShadowTree(R->ShadowLevel ,R->ShadowNumber);


		EmitterRoot	=EmitterRootBuff;
		EmitterName	=EmitterNameBuff;
		CmdClass	=CmdClassBuff;
		QBuffer buff;
		R->GetPointer(fp ,buff);
		buff.open(QIODevice::ReadWrite);
		if(strcmp(EmitterRoot,/**/"ANY")==0 && strcmp(EmitterName,/**/"ANY")==0){
			for(GuiDLLItem *s=LBase->GetGuiInitializer()->GuiDLLPack->GetFirst();s!=NULL;s=s->GetNext()){
				if(s->ReceivePacket(Cmd ,R->GlobalPage ,EmitterRoot ,EmitterName ,CmdClass,buff,R->IDForUndo,ErrorData)==true){
					delete	R;
					return;
				}
			}
		}
		else{
			/*
			for(GuiDLLItem *s=LBase->GetGuiInitializer()->GetFirst();s!=NULL;s=s->GetNext()){
				if(s->RootName!=EmitterRoot || s->Name!=EmitterName)
					continue;
				if(s->ReceivePacket(Cmd ,R->GlobalPage ,EmitterRoot ,EmitterName ,CmdClass,buff)==true)
					break;
			}
			*/
			for(GUIRootClassified *L=LBase->GetGuiInitializer()->RootList.GetFirst();L!=NULL;L=L->GetNext()){
				if(L->Root==EmitterRoot){
					for(GUINameClassified *e=L->NameList.GetFirst();e!=NULL;e=e->GetNext()){
						if(e->Point->Name==EmitterName){
							//_CrtCheckMemory();
							if(e->Point->ReceivePacket(Cmd ,R->GlobalPage ,EmitterRoot ,EmitterName ,CmdClass,buff,R->IDForUndo,ErrorData)==true){
								//_CrtCheckMemory();
								delete	R;
								return;
							}
						}
					}
				}
			}
		}
		delete	R;
		MiscatchPacket(R->GlobalPage ,EmitterRoot ,EmitterName ,CmdClass);
	}	
}


void	GUIIntegrationCommPack::SlotReceived(int ID ,int Cmd)
{
	IntegrationRecList	*R=UnpackTopRxBuff(ID);
	if(R!=NULL){
		const char	*EmitterRoot;
		char	EmitterRootBuff[100];
		const char	*EmitterName;
		char	EmitterNameBuff[100];
		const char	*CmdClass;
		char	CmdClassBuff[100];
		BYTE	*fp	=R->GetClassNamePointer(EmitterRootBuff ,EmitterNameBuff ,CmdClassBuff,sizeof(CmdClassBuff));
		if(fp==NULL){
			delete	R;
			return;
		}

		ErrorCodeList	ErrorData((ErrorCodeList::CautionLevel)R->ErrorLevel);
		if(ErrorData.GetLevel()!=ErrorCodeList::_None){
			fp	=R->GetError(fp,ErrorData);
		}
		LayersBase	*LBase=GetLayersBase()->GetTopLayersBase()->GetShadowTree(R->ShadowLevel ,R->ShadowNumber);

		EmitterRoot	=EmitterRootBuff;
		EmitterName	=EmitterNameBuff;
		CmdClass	=CmdClassBuff;
		QBuffer buff;
		R->GetPointer(fp ,buff);
		buff.open(QIODevice::ReadWrite);
		if(strcmp(EmitterRoot,/**/"ANY")==0 && strcmp(EmitterName,/**/"ANY")==0){
			for(GuiDLLItem *s=LBase->GetGuiInitializer()->GuiDLLPack->GetFirst();s!=NULL;s=s->GetNext()){
				if(s->ReceiveIntegrationPacket(Cmd ,R->SlaveNo ,EmitterRoot ,EmitterName ,CmdClass,buff,R->IDForUndo,ErrorData)==true){
					delete	R;
					return;
				}
			}
		}
		else{
			for(GUIRootClassified *L=LBase->GetGuiInitializer()->RootList.GetFirst();L!=NULL;L=L->GetNext()){
				if(L->Root==EmitterRoot){
					for(GUINameClassified *e=L->NameList.GetFirst();e!=NULL;e=e->GetNext()){
						if(e->Point->Name==EmitterName){
							//_CrtCheckMemory();
							if(e->Point->ReceiveIntegrationPacket(Cmd ,R->SlaveNo ,EmitterRoot ,EmitterName ,CmdClass,buff,R->IDForUndo,ErrorData)==true){
								//_CrtCheckMemory();
								delete	R;
								return;
							}
						}
					}
				}
			}
		}
		delete	R;
		//MiscatchPacket(R->GlobalPage ,EmitterRoot ,EmitterName ,CmdClass);
	}	
}

bool	GuiDLLItem::LoadDLL(LayersBase *Base,const QString &filename ,DWORD &ErrorCode)
{
	DllLib.setFileName(filename);
	FileName=filename;
	if(DllLib.load()==false){
		Error=DllLib.errorString ();
		return false;
	}
	DLL_GetDLLType				=(WORD (*)(void))DllLib.resolve(/**/"DLL_GetDLLType");

	if(DLL_GetDLLType!=NULL){
		if(DLL_GetDLLType()!=GUILIB_ID){
			ErrorCode=Error_InvalidDLL_GetDLLType;
			return false;
		}
	}
	else{
		ErrorCode=Error_NoDLL_GetDLLType;
		return false;
	}
	if(DLLManager::LoadDLL(DllLib)==false){
		ErrorCode=Error_NoDLL_GetSystemVersion;
		return false;
	}

	DLL_GetVersion				=(WORD (*)(void))DllLib.resolve(/**/"DLL_GetVersion");
	if(DLL_GetVersion!=NULL){
		if(DLL_GetVersion()<GUILIB_Version){
			ErrorCode=Error_LowerDLL_GetVersion;
			return false;
		}
	}
	else{
		ErrorCode=Error_NoDLL_GetVersion;
		return false;
	}

	DLL_CheckCopyright			=(bool (*)(QString &CopyrightString))DllLib.resolve(/**/"DLL_CheckCopyright");
	if(DLL_CheckCopyright!=NULL){
		if(DLL_CheckCopyright(Copyright)==false){
			ErrorCode=Error_DLL_FalseInCopyright;
			return false;
		}
	}

	DLL_GetName					=(bool (*)(QString & ,QString &))DllLib.resolve(/**/"DLL_GetName");
	if(DLL_GetName==NULL){
		ErrorCode=Error_NoDLL_GetName;
		return(false);
	}
	DLL_GetName(RootName ,Name);

	DLL_CreateInstance			=(GUIFormBase *(*)(LayersBase *,QWidget *))DllLib.resolve(/**/"DLL_CreateInstance");
	if(DLL_CreateInstance==NULL){
		ErrorCode=Error_NoDLL_CreateInstance;
		return(false);
	}
	DLL_InitialQt				=(void (*)(QApplication *AppBase))DllLib.resolve(/**/"DLL_InitialQt");
	if(DLL_InitialQt==NULL){
		ErrorCode=Error_NoDLL_InitialQt;
		return(false);
	}

	DLL_DeleteInstance			=(void (*)(GUIFormBase *))DllLib.resolve(/**/"DLL_DeleteInstance");
	if(DLL_DeleteInstance==NULL){
		ErrorCode=Error_NoDLL_DeleteInstance;
		return(false);
	}
	DLL_GetExplain			=(const char *(*)(void))DllLib.resolve(/**/"DLL_GetExplain");
	if(DLL_GetExplain==NULL){
		ErrorCode=Error_NoDLL_GetExplain;
		return(false);
	}
	DLL_SetLanguage			=(void (*)(LanguagePackage &Pkg ,int LanguageCode))DllLib.resolve(/**/"DLL_SetLanguage");
	DLL_SetLanguageCommon	=(void (*)(LanguagePackage &Pkg ,int LanguageCode))DllLib.resolve(/**/"DLL_SetLanguageCommon");

	if(DLL_GetExplain!=NULL){
		const char	*c=DLL_GetExplain();
		if(c!=NULL){
			Explain=QString::fromLocal8Bit(c);
		}
	}

	DLL_Initial				=(void (*)(LayersBase *Base))DllLib.resolve(/**/"DLL_Initial");
	if(DLL_Initial==NULL){
		ErrorCode=Error_NoDLL_Initial;
		return(false);
	}
	DLL_ReceivePacket			=(bool (*)(LayersBase *Base,int32 ,int32 ,const char *,const char *,const char *,QBuffer&,int32,ErrorCodeList &))DllLib.resolve(/**/"DLL_ReceivePacket");
	DLL_ReceivePacketDirectComm	=(bool (*)(LayersBase *Base,int32 ,int32 ,const char *,const char *,const char *,QBuffer&,int32,ErrorCodeList &))DllLib.resolve(/**/"DLL_ReceivePacketDirectComm");
	DLL_ReceiveIntegrationPacket=(bool (*)(LayersBase *Base,int32 ,int32 ,const char *,const char *,const char *,QBuffer&,int32,ErrorCodeList &))DllLib.resolve(/**/"DLL_ReceiveIntegrationPacket");

	DLL_Close				=(void (*)(void))DllLib.resolve(/**/"DLL_Close");

	DLL_InitialQt(qApp);
	DLL_Initial(Base);

	DLL_GetPropertyString		=(int32 (*)(void *,struct	PropertyClass [] ,WORD))DllLib.resolve(/**/"DLL_GetPropertyString");
	if(DLL_GetPropertyString==NULL){
		ErrorCode=Error_NoDLL_GetPropertyString;
		return(false);
	}

	DLL_GetIcon					=(QIcon *(*)(void))DllLib.resolve(/**/"DLL_GetIcon");

	DLL_GetGuiAdditionalDatabase=(void (*)(NPListPack<GuiAdditionalDatabase> &Data))DllLib.resolve(/**/"DLL_GetGuiAdditionalDatabase");
	
	DLL_EntryAlgorithm			=(void (*)(LayersBase *Base,RootNameListContainer  &List))DllLib.resolve(/**/"DLL_EntryAlgorithm");
	DLL_AssociateComponent		=(void (*)(LayersBase *Base,ComponentListContainer &List))DllLib.resolve(/**/"DLL_AssociateComponent");
	DLL_RegistMacroFunction		=(int32 (*)(ExportFuncForMacro Functions[],int MaxBuffer))DllLib.resolve(/**/"DLL_RegistMacroFunction");

	if(GetLayersBase()!=NULL){
		GetLayersBase()->InformToLoadDLL(filename);
	}
	ErrorCode=Error_Nothing;
	return(true);
}
bool	GuiDLLItem::CheckSystemVersion(QStringList &Str)
{
	return CheckSystemVersionFunc(Str ,/**/"GUIDLL",RootName,Name);
}

bool	GuiDLLItem::InitialAdditionalFieldFromGUI(QSqlDatabase &DB)
{
	bool	ret=true;
	if(DLL_GetGuiAdditionalDatabase!=NULL){
		NPListPack<GuiAdditionalDatabase> FieldList;
		DLL_GetGuiAdditionalDatabase(FieldList);
		for(GuiAdditionalDatabase *d=FieldList.GetFirst();d!=NULL;d=d->GetNext()){
			if(d->InitialAdditionalFieldFromGUI(DB)==false){
				ret=false;
			}
		}
	}
	return ret;
}
bool	GuiDLLItem::CreateExcludedList(ExcludedListPack &EList)
{
	if(DLL_GetGuiAdditionalDatabase!=NULL){
		NPListPack<GuiAdditionalDatabase> FieldList;
		DLL_GetGuiAdditionalDatabase(FieldList);
		for(GuiAdditionalDatabase *d=FieldList.GetFirst();d!=NULL;d=d->GetNext()){
			ExcludedListForCheck	*e=new ExcludedListForCheck(d->TableName,d->FieldName);
			EList.AppendList(e);
		}
	}
	return true;		
}

bool	GuiDLLItem::SetLanguageCode(int LanguageCode)
{
	if(DLL_SetLanguageCommon!=NULL){
		DLL_SetLanguageCommon(GetLayersBase()->GetLanguagePackageData(),LanguageCode);
	}
	if(DLL_SetLanguage!=NULL){
		DLL_SetLanguage(GetLayersBase()->GetLanguagePackageData(),LanguageCode);
		return true;
	}
	return false;
}

GUIFormBase	*GuiDLLItem::CreateInstance(LayersBase *Base,QWidget *parent)
{	
	if(DLL_CreateInstance!=NULL){
		GUIFormBase	*ret=DLL_CreateInstance(Base,parent);
		Base->ExecuteLogoInGUIForm(ret ,RootName,Name);
		ret->SetCreatedInGUIDLL(true);
		ret->SetGuiDLLPoint(this);
		SetupMacro();

		return ret;
	}
	else{
		return NULL;
	}
}

QIcon	GuiDLLItem::GetIcon(void)
{
	if(icondata==NULL){
		if(DLL_GetIcon!=NULL){
			icondata=DLL_GetIcon();
		}
	}
	if(icondata!=NULL){
		return(*icondata);
	}
	return(QIcon());
}
void	GuiDLLItem::EntryAlgorithm(RootNameListContainer &List)
{
	if(DLL_EntryAlgorithm!=NULL){
		DLL_EntryAlgorithm(GetLayersBase(),List);
	}
}
void	GuiDLLItem::AssociateComponent(ComponentListContainer &List)
{
	if(DLL_AssociateComponent!=NULL){
		DLL_AssociateComponent(GetLayersBase(),List);
	}
}
WORD	GuiDLLItem::GetVersion(void)
{
	if(DLL_GetVersion!=NULL){
		return DLL_GetVersion();
	}
	return 0;
}

void	GuiDLLItem::GetExportFunctions(QStringList &Str)
{
	if(DLL_GetName!=NULL){
		Str.append("DLL_GetName");
	}
	if(DLL_GetDLLType!=NULL){
		Str.append("DLL_GetDLLType");
	}
	if(DLL_GetVersion!=NULL){
		Str.append("DLL_GetVersion");
	}
	if(DLL_CheckCopyright!=NULL){
		Str.append("DLL_CheckCopyright");
	}
	if(DLL_GetExplain!=NULL){
		Str.append("DLL_GetExplain");
	}
	if(DLL_SetLanguage!=NULL){
		Str.append("DLL_SetLanguage");
	}
	if(DLL_Initial!=NULL){
		Str.append("DLL_Initial");
	}
	if(DLL_Close!=NULL){
		Str.append("DLL_Close");
	}
	if(DLL_InitialQt!=NULL){
		Str.append("DLL_InitialQt");
	}
	if(DLL_ReceivePacket!=NULL){
		Str.append("DLL_ReceivePacket");
	}
	if(DLL_ReceivePacketDirectComm!=NULL){
		Str.append("DLL_ReceivePacketDirectComm");
	}
	if(DLL_ReceiveIntegrationPacket!=NULL){
		Str.append("DLL_ReceiveIntegrationPacket");
	}

	if(DLL_CreateInstance!=NULL){
		Str.append("DLL_CreateInstance");
	}
	if(DLL_DeleteInstance!=NULL){
		Str.append("DLL_DeleteInstance");
	}
	if(DLL_GetPropertyString!=NULL){
		Str.append("DLL_GetPropertyString");
	}
	if(DLL_GetGuiAdditionalDatabase!=NULL){
		Str.append("DLL_GetGuiAdditionalDatabase");
	}

	if(DLL_GetIcon!=NULL){
		Str.append("DLL_GetIcon");
	}
	if(DLL_EntryAlgorithm!=NULL){
		Str.append("DLL_EntryAlgorithm");
	}
	if(DLL_AssociateComponent!=NULL){
		Str.append("DLL_AssociateComponent");
	}
	if(DLL_RegistMacroFunction!=NULL){
		Str.append("DLL_RegistMacroFunction");
	}
	DLLManager::GetExportFunctions(Str);
}

int		GuiDLLItem::RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	if(DLL_RegistMacroFunction!=NULL){
		return DLL_RegistMacroFunction(Functions,MaxBuffer);
	}
	return 0;
}

inline	char	*SkipSpace(char *fp)
{
	while(*fp==' ' || *fp=='\t'){
		fp++;
	}
	return(fp);
}

static	const	char	*CKeyword=/**/" .,\t();";

static	char	*CutWord(char *fp ,char buff[] ,int bufflen)
{
	char	*cp;
	for(cp=fp;*cp!=0;cp++){
		if(strchr(CKeyword,*cp)!=NULL){
			break;
		}
	}
	if(cp==NULL){
		cp=strchr(fp,0);
		if(cp==NULL){
			return(NULL);
		}
	}
	int	len=cp-fp;
	if(len>=bufflen){
		return(NULL);
	}
	memcpy(buff,fp,len);
	buff[len]=0;
	fp=SkipSpace(cp);
	return(fp);
}


class	PropertyLeafInnerClass
{
public:
	QStringList	Member;
	QString		Name;
	PropertyClass	*Point;

	PropertyLeafInnerClass(void){	Point=NULL;	}

	PropertyLeafInnerClass	&operator=(PropertyLeafInnerClass &src);
	void	Analyze(void);
};
	
PropertyLeafInnerClass	&PropertyLeafInnerClass::operator=(PropertyLeafInnerClass &src)
{
	Member	=src.Member;
	Name	=src.Name;
	Point	=src.Point;
	return(*this);
}
void	PropertyLeafInnerClass::Analyze(void)
{
	char	Buff[1000];
	QString2Char(Point->VariableNameWithRoute ,Buff ,sizeof(Buff));
	char	*fp=Buff;

	QString	LastWord;
	for(;;){
		fp=SkipSpace(fp);
		if(*fp==0){
			break;
		}
		char	nbuff[256];
		fp=CutWord(fp,nbuff,sizeof(nbuff));
		if(LastWord.isEmpty()==false){
			Member<<LastWord;
		}
		LastWord=QString(nbuff);
		fp=SkipSpace(fp);
		if(*fp==0){
			break;
		}
		if(*fp=='.'){
			fp++;
		}
	}
	Name=LastWord;
}

void	StructList::SetType(const QString &Type ,void *Pointer)
{
	//if(Variable!=NULL)
	//	delete	Variable;
	//Variable=NULL;
	DeleteOk=false;
	if(Type==/**/"bool"){
		VType=_DT_bool;
		//Variable=new bool;
		//*((bool *)Variable)	=*((bool *)Pointer);
	}
	else if(Type==/**/"byte"){
		VType=_DT_byte;
		//Variable=new BYTE;
		//*((BYTE *)Variable)	=*((BYTE *)Pointer);
	}
	else if(Type==/**/"short"){
		VType=_DT_short;
		//Variable=new short;
		//*((short *)Variable)=*((short *)Pointer);
	}
	else if(Type==/**/"int16"){
		VType=_DT_short;
		//Variable=new short;
		//*((short *)Variable)=*((short *)Pointer);
	}
	else if(Type==/**/"int"){
		VType=_DT_int;
		//Variable=new int32;
		//*((int32 *)Variable)	=*((int32 *)Pointer);
	}
	else if(Type==/**/"int32"){
		VType=_DT_int32;
		//Variable=new int32;
		//*((int32 *)Variable)	=*((int32 *)Pointer);
	}
	else if(Type==/**/"int64"){
		VType=_DT_int64;
		//Variable=new int64;
		//*((int64 *)Variable)	=*((int64 *)Pointer);
	}
	else if(Type==/**/"QString"){
		VType=_DT_QString;
		//Variable=new QString;
		//*((QString *)Variable)	=*((QString *)Pointer);
	}
	else if(Type==/**/"double"){
		VType=_DT_double;
		//Variable=new double;
		//*((double *)Variable)	=*((double *)Pointer);
	}
	else if(Type==/**/"float"){
		VType=_DT_float;
		//Variable=new float;
		//*((float *)Variable)	=*((float *)Pointer);
	}
	else if(Type==/**/"QColor"){
		VType=_DT_QColor;
		//Variable=new QColor();
		//*((QColor *)Variable)	=*((QColor *)Pointer);
	}
	else if(Type==/**/"QFont"){
		VType=_DT_QFont;
		//Variable=new QFont();
		//*((QFont *)Variable)	=*((QFont *)Pointer);
	}
	else if(Type==/**/"QStringList"){
		VType=_DT_QStringList;
		//Variable=new QString;
		//*((QString *)Variable)	=*((QString *)Pointer);
	}
	else if(Type==/**/"TunableList"){
		VType=_DT_TunableList;
		//Variable=new QString;
		//*((QString *)Variable)	=*((QString *)Pointer);
	}
	else if(Type==/**/"FileName"){
		VType=_DT_FileName;
	}
	else if(Type==/**/"PathName"){
		VType=_DT_PathName;
	}
	else if(Type==/**/"FileNames"){
		VType=_DT_FileNames;
	}
	else if(Type==/**/"QImage"){
		VType=_DT_QImage;
	}
	else if(Type==/**/"QByteArray"){
		VType=_DT_QByteArray;
	}
	else if(Type==/**/"IntList"){
		VType=_DT_IntList;
	}
	else{
		VType=_DT_enum;
		char	Buff[1000];
		QString2Char(Type ,Buff ,sizeof(Buff));
		char	*fp=Buff;
		for(;;){
			fp=SkipSpace(fp);
			if(*fp==0){
				break;
			}
			char	nbuff[100];
			fp=CutWord(fp,nbuff,sizeof(nbuff));
			Enum.append(nbuff);
			fp=SkipSpace(fp);
			if(*fp==0){
				break;
			}
			while(strchr(CKeyword,*fp)!=NULL){
				fp++;
				if(*fp==0){
					break;
				}
				fp=SkipSpace(fp);
			}
			if(*fp==0){
				break;
			}
		}
		//Variable=new QString;
		//*((QString *)Variable)	=*((QString *)Pointer);
	}
	Variable	=Pointer;
}


void	StructList::SetValueTo(void *v)
{
	switch(VType){
		case _DT_bool:
			*((bool *)v)=GetBool();
			break;
		case _DT_byte:
			*((BYTE *)v)=GetByte();
			break;
		case _DT_short:
			*((short *)v)=GetShort();
			break;
		case _DT_int:
			*((int *)v)=GetInt32();
			break;
		case _DT_int32:
			*((int32 *)v)=GetInt32();
			break;
		case _DT_int64:
			*((int64 *)v)=GetInt64();
			break;
		case _DT_QString:
			*((QString *)v)=GetQString();
			break;
		case _DT_double:
			*((double *)v)=GetDouble();
			break;
		case _DT_float:
			*((float *)v)=GetFloat();
			break;
		case _DT_enum:
			*((QString *)v)=GetEnum();
			break;
		case _DT_IntList:
			*((IntList *)v)=GetIntList();
			break;
		case _DT_struct:
			//*((bool *)v)=GetBool();
			break;
		case _DT_QColor:
			*((QColor *)v)=GetColor();
			break;
		case _DT_QFont:
			*((QFont *)v)=GetFont();
			break;
		case _DT_QStringList:
			*((QStringList *)v)=GetQStringList();
			break;
		case _DT_TunableList:
			*((QStringList *)v)=GetTunableList();
			break;
		case _DT_FileName:
			*((QString *)v)=GetQString();
			break;
		case _DT_PathName:
			*((QString *)v)=GetQString();
			break;
		case _DT_FileNames:
			*((QStringList *)v)=GetQStringList();
			break;
		case _DT_QImage:
			*((QImage *)v)=GetQImage();
			break;
		case _DT_QByteArray:
			*((QByteArray *)v)=GetQByteArray();
			break;
		default:
			break;
	}
}


//====================================================================================================
//GUIInstancePack	GUIInstanceRoot;

GUIItemInstance::GUIItemInstance(GUIInstancePack *p,GuiDLLItem	*seed)
	:Parent(p)
{
	DLLAccess	=seed;
	Handle		=NULL;
	InstanceID	=0;
	ParentInstanceID=0;
	GUIPositionX1	=0;
	GUIPositionY1	=0;
	GUIPositionX2	=0;
	GUIPositionY2	=0;
}
GUIItemInstance::~GUIItemInstance(void)
{
	if(Handle!=NULL){
		if(DLLAccess!=NULL){
			//Handle->setParent(NULL);
			//if(Handle->testAttribute (Qt::WA_DeleteOnClose)==false){
				DLLAccess->DeleteInstance(Handle);
				//Handle->deleteLater();
			//}
		}
		else{
			delete	DLLAccess;
		}
	}
	Handle=NULL;
}

bool	GUIItemInstance::SetLanguage(const QString &MemberName,LanguageStringList *s)
{
	if(DLLAccess!=NULL){
		return DLLAccess->SetLanguage(Handle,MemberName,s);
	}
	return false;
}

void	GUIItemInstance::PickupGUILanguage(GUILanguageContainer &GUILanguageContainerInst)
{
	if(DLLAccess!=NULL){
		DLLAccess->PickupGUILanguage(Handle,GUILanguageContainerInst);
	}
}


void	GUIItemInstance::Clear(void)
{
	DLLAccess=NULL;
	Handle	=NULL;
	StructInstance.RemoveAll();
}

bool	GUIItemInstance::Initial(LayersBase *Base,QWidget *parent ,DWORD &ErrorCode , GuiDLLItem *access)
{
	if(access!=NULL){
		DLLAccess=access;
	}
	if(Handle==NULL){
		Handle=DLLAccess->CreateInstance(Base,parent);
	}
				
	Handle->setAttribute (Qt::WA_DeleteOnClose,true);
	connect(Handle,SIGNAL(SignalRaiseUp()),this,SLOT(SlotRaiseUp()));

	StructInstance.RemoveAll();
	Handle->InstPoint=this;

	struct	PropertyClass	PClass[1000];
	int32	n=DLLAccess->GetPropertyString(Handle ,PClass ,sizeof(PClass)/sizeof(PClass[0]));
	if(n<0){
		ErrorCode=Error_DLLAnalyzeProperty;
		return(false);
	}
	PropertyLeafInnerClass	*D=new PropertyLeafInnerClass[n];
	for(int i=0;i<n;i++){
		D[i].Point=&PClass[i];
		D[i].Analyze();
	}
	KNext:;
	for(int i=0;i<n;i++){
		int	j;
		for(j=i+1;j<n;j++){
			if(D[i].Member!=D[j].Member){
				break;
			}
		}
		if(j<n){
			int	k;
			for(k=j+1;j<n && k<n;j++){
				if(D[i].Member==D[k].Member){
					PropertyLeafInnerClass	Dummy;
					Dummy=D[k];
					D[k]=D[j];
					D[j]=Dummy;
					goto	KNext;
				}
			}		
		}
	}
	StructList *qName=new StructList();

	//RealName=Handle->Name;
	qName->SetType(QString(/**/"QString"),&Handle->Name);
	qName->VName=/**/"Name";
	StructInstance.AppendList(qName);

	//RealComment=Handle->Comment;
	StructList *qComment=new StructList();
	qComment->SetType(QString(/**/"QString"),&Handle->Comment);
	qComment->VName=/**/"Comment";
	StructInstance.AppendList(qComment);

	//RealAlignment=Handle->Alignment;
	StructList *qAlignment=new StructList();
	qAlignment->SetType(QString(/**/"None,Top,Left,Right,Bottom,Client"),&Handle->Alignment);
	qAlignment->VName=/**/"Alignment";
	StructInstance.AppendList(qAlignment);

	StructList *qLeft=new StructList();
	qLeft->SetType(QString(/**/"int32"),&GUIPositionX1);
	qLeft->VName=/**/"Left";
	StructInstance.AppendList(qLeft);

	StructList *qTop=new StructList();
	qTop->SetType(QString(/**/"int32"),&GUIPositionY1);
	qTop->VName=/**/"Top";
	StructInstance.AppendList(qTop);

	StructList *qRight=new StructList();
	qRight->SetType(QString(/**/"int32"),&GUIPositionX2);
	qRight->VName=/**/"Right";
	StructInstance.AppendList(qRight);

	StructList *qBottom=new StructList();
	qBottom->SetType(QString(/**/"int32"),&GUIPositionY2);
	qBottom->VName=/**/"Bottom";
	StructInstance.AppendList(qBottom);

	StructList *qTargetPage=new StructList();
	qTargetPage->SetType(QString(/**/"int32"),&Handle->TargetPage);
	qTargetPage->VName=/**/"TargetPage";
	StructInstance.AppendList(qTargetPage);

	StructList *qShowingOrder=new StructList();
	qShowingOrder->SetType(QString(/**/"int32"),&Handle->ShowingOrder);
	qShowingOrder->VName=/**/"ShowingOrder";
	StructInstance.AppendList(qShowingOrder);


	for(int i=0;i<n;i++){
		StructListPack	*p=&StructInstance;
		for(int j=0;j<D[i].Member.count();j++){
			StructList *q;
			for(q=p->GetFirst();q!=NULL;q=q->GetNext()){
				if(q->VType==_DT_struct && q->VName==D[i].Member[j]){
					p=&q->StructInstance;
					break;
				}
			}
			if(q==NULL){
				q=new StructList();
				q->VType=_DT_struct;
				q->VName=D[i].Member[j];
				p->AppendList(q);
				p=&q->StructInstance;
			}
		}
		StructList *q=new StructList();
		q->SetType(D[i].Point->Type ,D[i].Point->Pointer);
		q->VName=D[i].Name;
		p->AppendList(q);
	}
	delete	[]D;
	ErrorCode=Error_Nothing;
	return(true);
}

QString	GUIItemInstance::GetDLLRoot(void)
{
	if(DLLAccess!=NULL){
		return DLLAccess->RootName;
	}
	return /**/"";
}
QString	GUIItemInstance::GetDLLName(void)
{
	if(DLLAccess!=NULL){
		return DLLAccess->Name;
	}
	return /**/"";
}
void	GUIItemInstance::AssociateComponent(ComponentListContainer &List)
{
	if(Handle!=NULL){
		Handle->AssociateComponent(List);
	}
}
LayersBase	*GUIItemInstance::GetLayersBase(void)
{
	if(Parent!=NULL){
		return Parent->GetLayersBase();
	}
	if(Handle!=NULL && Handle->GetLayersBase()!=NULL){
		return Handle->GetLayersBase();
	}
	return NULL;
}

void	GUIItemInstance::ReplaceParam(void)
{
	StructInstance.ReplaceParam(GetLayersBase());
}
bool	GUIItemInstance::ReflectToFormData(DWORD &ErrorCode , GuiDLLItem *access)
{
	struct	PropertyClass	PClass[1000];
	int32	n=DLLAccess->GetPropertyString(Handle ,PClass ,sizeof(PClass)/sizeof(PClass[0]));
	if(n<0){
		ErrorCode=Error_DLLAnalyzeProperty;
		return(false);
	}
	ReplaceParam();

	for(int i=0;i<n;i++){
		PropertyLeafInnerClass	D;
		D.Point=&PClass[i];
		D.Analyze();
		for(StructList *q=StructInstance.GetFirst();q!=NULL;q=q->GetNext()){
			if(D.Name==q->VName){
				q->SetValueTo(D.Point->Pointer);
				break;
			}
		}
	}
	ErrorCode=Error_Nothing;
	return(true);
}

void	GUIItemInstance::SlotRaiseUp()
{
	if(RaiseUp()==true){
		if(Handle!=NULL){
			if(Handle->SelectedWindowPointer!=NULL){
				Handle->SelectedWindowPointer->raise();
			}
			Handle->raise();
			SelectedWindow	*SelectedW=Handle->SelectedWindowPointer;
			QObject	*P=Handle->parent();
			if(P!=NULL){
				QObjectList	Q=P->children();
				QObject	*Current=NULL;
				QObject	*CurrentS=NULL;
				for(int	i=0;i<Q.count();i++){
					QObject	*o=Q[i];
					o->setParent(NULL);
					if(o==Handle){
						Current=o;
					}
					if(o==SelectedW){
						CurrentS=o;
					}
				}
				if(CurrentS!=NULL){
					CurrentS->setParent(P);
				}
				if(Current!=NULL){
					Current->setParent(P);
				}
				for(int	i=0;i<Q.count();i++){
					QObject	*o=Q[i];
					if(o!=Handle && o!=CurrentS){
						o->setParent(P);
					}
				}
			}
		}
	}
}
bool	GUIItemInstance::RaiseUp(void)
{
	if(Parent==NULL)
		return false;
	for(GUIItemInstance *p=Parent->NPListPack<GUIItemInstance>::GetFirst();p!=NULL;p=p->GetNext()){
		if(p->InstanceID==InstanceID){
			break;
		}
		if(p->ParentInstanceID==ParentInstanceID){
			Parent->NPListPack<GUIItemInstance>::RemoveList(this);
			Parent->NPListPack<GUIItemInstance>::InsertForward(p,this);
			return true;
		}
	}
	return false;
}

void	GUIItemInstance::InitialInPaste(int dx,int dy)
{
	Handle->setGeometry(GUIPositionX1+dx,GUIPositionY1+dy,GUIPositionX2-GUIPositionX1+1,GUIPositionY2-GUIPositionY1+1);
	Handle->ReflectAlignment();
	Handle->ReflectGUILanguage();
	Handle->InitialPrepare();
	Handle->Prepare();
	Handle->SetName(tmpName);
	Handle->SetComment(tmpComment);
	Handle->SetAlignment(tmpAlignment);
	Handle->SetFormBaseID(FormBaseID);
	Handle->AfterPrepare();
	if(GetLayersBase()->GetEntryPoint()->GUIIsEditMode()==true){
		Handle->SetEditMode();
		Handle->CreateSelectedWindow();
		connect(Handle,SIGNAL(SignalMove())		,this,SLOT(SlotMove()));
		connect(Handle,SIGNAL(SignalResize())	,this,SLOT(SlotResize()));
		connect(Handle,SIGNAL(SignalRelease())	,this,SLOT(SlotRelease()));
	}
}

void	GUIItemInstance::SetAcceptDropsForAll(void)
{
	if(Handle!=NULL){
		Handle->SetAcceptDropsForAll();
	}
}

void	GUIItemInstance::ChangedValue(void)
{
	if(Handle!=NULL){
		DWORD	ErrorCode;
		ReflectToFormData(ErrorCode , DLLAccess);
		//GUIFormBase	*p=Handle->GetTopParent();
		//if(p!=NULL){
		//	p->ReflectAlignment();
		//}
		//else{
			Handle->ReflectAlignment();
		//}
		Handle->ChangedValue();
	}
}

GUIItemInstance	&GUIItemInstance::operator=(GUIItemInstance &src)
{
	//Parent=
	DLLAccess	=src.DLLAccess;
	Handle		=src.Handle;
	StructInstance	=src.StructInstance;
	GUIPositionX1	=src.GUIPositionX1;
	GUIPositionY1	=src.GUIPositionY1;
	GUIPositionX2	=src.GUIPositionX2;
	GUIPositionY2	=src.GUIPositionY2;
	//InstanceID	=src.
	ParentInstanceID=src.ParentInstanceID;
	FormBaseID		=src.FormBaseID;
	ChildNumber		=src.ChildNumber;
	tmpName			=src.tmpName;
	tmpComment		=src.tmpComment;
	tmpAlignment	=src.tmpAlignment;
	return(*this);
}

bool	GUIItemInstance::SaveInstance(QIODevice *f)
{
	bool	DLLAccessExist;
	if(DLLAccess==NULL){
		DLLAccessExist=false;
		if(f->write((const char *)&DLLAccessExist,sizeof(DLLAccessExist))!=sizeof(DLLAccessExist)){
			return(false);
		}
	}
	else{
		DLLAccessExist=true;
		if(f->write((const char *)&DLLAccessExist,sizeof(DLLAccessExist))!=sizeof(DLLAccessExist)){
			return(false);
		}
		if(::Save(f,DLLAccess->RootName)==false){
			return(false);
		}
		if(::Save(f,DLLAccess->Name)==false){
			return(false);
		}
	}
	if(Handle!=NULL){
		GUIPositionX1=Handle->geometry().left();
		GUIPositionY1=Handle->geometry().top();
		GUIPositionX2=Handle->geometry().right();
		GUIPositionY2=Handle->geometry().bottom();
	}
	if(f->write((const char *)&GUIPositionX1,sizeof(GUIPositionX1))!=sizeof(GUIPositionX1)){
		return(false);
	}
	if(f->write((const char *)&GUIPositionY1,sizeof(GUIPositionY1))!=sizeof(GUIPositionY1)){
		return(false);
	}
	if(f->write((const char *)&GUIPositionX2,sizeof(GUIPositionX2))!=sizeof(GUIPositionX2)){
		return(false);
	}
	if(f->write((const char *)&GUIPositionY2,sizeof(GUIPositionY2))!=sizeof(GUIPositionY2)){
		return(false);
	}
	if(f->write((const char *)&InstanceID,sizeof(InstanceID))!=sizeof(InstanceID)){
		return(false);
	}
	if(f->write((const char *)&ParentInstanceID,sizeof(ParentInstanceID))!=sizeof(ParentInstanceID)){
		return(false);
	}
	if(Handle!=NULL){
		FormBaseID=Handle->FormBaseID;
	}
	if(f->write((const char *)&FormBaseID,sizeof(FormBaseID))!=sizeof(FormBaseID)){
		return(false);
	}

	if(Handle!=NULL){
		int ID=Handle->FormBaseID;
		Handle->SetFormBaseID(ID);

		GUIFormBase	*w=Handle->GetParentFormBase();
		if(w!=NULL){
		ChildNumber=w->FormBaseID;
			}
		else{
			ChildNumber=-1;
		}
		if(f->write((const char *)&ChildNumber,sizeof(ChildNumber))!=sizeof(ChildNumber)){
			return(false);
		}

		if(::Save(f,Handle->Name)==false){
			return(false);
		}
		if(::Save(f,Handle->Comment)==false){
			return(false);
		}
		if(::Save(f,Handle->Alignment)==false){
			return(false);
		}
	}
	else{
		int32	ChildNumber=0;
		if(f->write((const char *)&ChildNumber,sizeof(ChildNumber))!=sizeof(ChildNumber)){
			return(false);
		}
		QString	tName;
		QString	tComment;
		QString	tAlignment;
		if(::Save(f,tName)==false){
			return(false);
		}
		if(::Save(f,tComment)==false){
			return(false);
		}
		if(::Save(f,tAlignment)==false){
			return(false);
		}
	}
	if(StructInstance.Save(f)==false){
		return(false);
	}
	return(true);
}
bool	GUIItemInstance::LoadInstance(QIODevice *f ,QString &ErrorMsg)
{
	bool	DLLAccessExist;
	if(f->read((char *)&DLLAccessExist,sizeof(DLLAccessExist))!=sizeof(DLLAccessExist)){
		return(false);
	}
	if(DLLAccessExist==true){
		QString	tRootName;
		QString	tName;
		if(::Load(f,tRootName)==false){
			return(false);
		}
		if(::Load(f,tName)==false){
			return(false);
		}
		DLLAccess=GetLayersBase()->GetGuiInitializer()->Search(tRootName,tName);
		if(DLLAccess==NULL){
			ErrorMsg=QString(/**/"Can not find DLL (Root:")+tRootName
					+QString(/**/"  Name:")+tName
					+QString(/**/")");
			return(false);
		}
		DLLAccess->UsedInGUI=true;
	}
	else{
		DLLAccess=NULL;
	}

	if(f->read((char *)&GUIPositionX1,sizeof(GUIPositionX1))!=sizeof(GUIPositionX1)){
		ErrorMsg=QString(/**/"Data Error");
		return(false);
	}
	if(f->read((char *)&GUIPositionY1,sizeof(GUIPositionY1))!=sizeof(GUIPositionY1)){
		ErrorMsg=QString(/**/"Data Error");
		return(false);
	}
	if(f->read((char *)&GUIPositionX2,sizeof(GUIPositionX2))!=sizeof(GUIPositionX2)){
		ErrorMsg=QString(/**/"Data Error");
		return(false);
	}
	if(f->read((char *)&GUIPositionY2,sizeof(GUIPositionY2))!=sizeof(GUIPositionY2)){
		ErrorMsg=QString(/**/"Data Error");
		return(false);
	}
	if(f->read((char *)&InstanceID,sizeof(InstanceID))!=sizeof(InstanceID)){
		ErrorMsg=QString(/**/"Data Error");
		return(false);
	}
	if(f->read((char *)&ParentInstanceID,sizeof(ParentInstanceID))!=sizeof(ParentInstanceID)){
		ErrorMsg=QString(/**/"Data Error");
		return(false);
	}
	if(f->read((char *)&FormBaseID,sizeof(FormBaseID))!=sizeof(FormBaseID)){
		ErrorMsg=QString(/**/"Data Error");
		return(false);
	}
	if(f->read((char *)&ChildNumber,sizeof(ChildNumber))!=sizeof(ChildNumber)){
		ErrorMsg=QString(/**/"Data Error");
		return(false);
	}
	if(::Load(f,tmpName)==false){
		ErrorMsg=QString(/**/"Data Error");
		return(false);
	}
	if(::Load(f,tmpComment)==false){
		ErrorMsg=QString(/**/"Data Error");
		return(false);
	}
	if(::Load(f,tmpAlignment)==false){
		ErrorMsg=QString(/**/"Data Error");
		return(false);
	}
	if(StructInstance.Load(f)==false){
		ErrorMsg=QString(/**/"Data Error");
		return(false);
	}
	return(true);
}


bool	GUIItemInstance::SaveInstanceMessage(QIODevice *f)
{
	if(Handle!=NULL){
		return Handle->SaveTextMessageContainerData(f);
	}
	return false;
}

bool	GUIItemInstance::LoadInstanceMessage(QIODevice *f)
{
	return TextMessageContainerData.Load(f);
}

void	GUIItemInstance::ReflectMessage(void)
{
	if(Handle!=NULL){
		Handle->TextMessageContainerData=TextMessageContainerData;
		//Handle->SetTextMessage();
	}
}

void	GUIItemInstance::ViewRefreshInPlayer(int64 shownInspectionID)
{
	if(Handle!=NULL){
		Handle->ViewRefreshInPlayer(shownInspectionID);
	}
}
void	GUIItemInstance::ViewOnTheWayInPlayer(int64 shownInspectionID)
{
	if(Handle!=NULL){
		Handle->ViewOnTheWayInPlayer(shownInspectionID);
	}
}

void	GUIItemInstance::RefreshByEveryInspection(int64 shownInspectionID)
{
	if(Handle!=NULL){
		Handle->RefreshByEveryInspection(shownInspectionID);
	}
}

void	GUIItemInstance::ViewRefreshInScanning(int64 shownInspectionID)
{
	if(Handle!=NULL){
		Handle->ViewRefreshInScanning(shownInspectionID);
	}
}

void	GUIItemInstance::ViewRefreshInEdit(void)
{
	if(Handle!=NULL){
		Handle->ViewRefreshInEdit();
	}
}
void	GUIItemInstance::DoneExecute(int64 shownInspectionID,ExecuteInspectBase::MotionMode mode)
{
	if(Handle!=NULL){
		Handle->DoneExecuteFromGUI(shownInspectionID,mode);
	}
}

void	GUIItemInstance::SetGridUnitForEditMode(int n)
{
	if(Handle!=NULL){
		Handle->SetGridUnitForEditMode(n);
	}
}

int		GUIItemInstance::GetGridUnitForEditMode(void)
{
	if(Handle!=NULL){
		return Handle->GetGridUnitForEditMode();
	}
	return 1;
}

//---------------------------------------------------------------------

DelayedViewThread::DelayedViewThread(GUIInstancePack *obj)
:QThread(obj),Parent(obj)
{
	WaitMilisec			=10;
	ShownInspectionID	=0;
}

void DelayedViewThread::run()
{
	//msleep(WaitMilisec);
	emit	SignalViewRefreshInPlayer(ShownInspectionID);
}

void	DelayedViewThread::SetViewRefreshInPlayer (int64 shownInspectionID ,int milisec)
{
	ShownInspectionID=shownInspectionID;
	WaitMilisec	=milisec;
	start();
}

bool	Connected=false;

GUIInstancePack::GUIInstancePack(LayersBase *Base,GUIInitializer *p,QObject *parent)
:QObject(parent),ServiceForLayers(Base),DThread(this),Parent(p)
{	
	if((bool)connect(&DThread, SIGNAL(SignalViewRefreshInPlayer(int)), this, SLOT(SlotViewRefreshInPlayer(int)), Qt::QueuedConnection)==true){
		Connected=true;
	}
}

GUIInstancePack::~GUIInstancePack(void)
{
	GUIItemInstance	*e;
	while((e=NPListPack<GUIItemInstance>::GetLast())!=NULL){
		RemoveList(e);
		delete	e;
	}
}

bool	GUIInstancePack::InitialLayers(QString &Msg,bool NoDatabase)
{
	if(GetLayersBase()->Initial(Msg ,NoDatabase)==false){
		return false;
	}
	return true;
}

bool	GUIInstancePack::SaveInstances(QIODevice *f)
{
	int32	Ver=10002;

	if(::Save(f,Ver)==false){
		return false;
	}

	AlgorithmList.RemoveAll();

	GetEntryAlgorithm(AlgorithmList);
	int32	ListNumb=AlgorithmList.GetNumber();
	if(::Save(f,ListNumb)==false){
		return false;
	}
	for(RootNameList *a=AlgorithmList.GetFirst();a!=NULL;a=a->GetNext()){
		if(::Save(f,a->DLLRoot)==false){
			return false;
		}
		if(::Save(f,a->DLLName)==false){
			return false;
		}
	}

	int32	N=NPListPack<GUIItemInstance>::GetNumber();
	if(f->write((const char *)&N,sizeof(N))!=sizeof(N)){
		return(false);
	}

	int	Nk=0;
	for(GUIItemInstance *c=NPListPack<GUIItemInstance>::GetFirst();c!=NULL;c=c->GetNext(),Nk++){
		if(c->SaveInstance(f)==false){
			return(false);
		}
	}
	Nk=0;
	for(GUIItemInstance *c=NPListPack<GUIItemInstance>::GetFirst();c!=NULL;c=c->GetNext(),Nk++){
		if(c->SaveInstanceMessage(f)==false){
			return(false);
		}
	}
	return(true);
}
bool	GUIInstancePack::LoadInstances(QIODevice *f ,QString &ErrorMsg)
{
	int32	Ver;

	if(::Load(f,Ver)==false){
		return false;
	}
	if(Ver>=10000){
		int32	ListNumb;
		AlgorithmList.RemoveAll();
		if(::Load(f,ListNumb)==false){
			return false;
		}
		for(int i=0;i<ListNumb;i++){
			RootNameList *a=new RootNameList();
			if(::Load(f,a->DLLRoot)==false){
				return false;
			}
			if(::Load(f,a->DLLName)==false){
				return false;
			}
			AlgorithmList.AppendList(a);
		}

		int32	N;
		RemoveAll();
		if(f->read((char *)&N,sizeof(N))!=sizeof(N)){
			return(false);
		}
		for(int i=0;i<N;i++){
			GUIItemInstance	*c=new GUIItemInstance(this);
			if(c->LoadInstance(f ,ErrorMsg)==false){
				return(false);
			}
			AppendList(c);
		}
	}
	else{
		int32	N=Ver;
		RemoveAll();
		for(int i=0;i<N;i++){
			GUIItemInstance	*c=new GUIItemInstance(this);
			if(c->LoadInstance(f ,ErrorMsg)==false){
				return(false);
			}
			AppendList(c);
		}
	}
	if(Ver>=10002){
		for(GUIItemInstance *c=NPListPack<GUIItemInstance>::GetFirst();c!=NULL;c=c->GetNext()){
			if(c->LoadInstanceMessage(f)==false){
				return(false);
			}
		}
	}
	RNext:;
	int	Nk=0;
	for(GUIItemInstance *c=NPListPack<GUIItemInstance>::GetFirst();c!=NULL;c=c->GetNext(),Nk++){
		if(Nk!=0 && c->DLLAccess==NULL){
			NPListPack<GUIItemInstance>::RemoveList(c);
			delete	c;
			goto	RNext;
		}
	}

	return(true);
}

bool	GUIInstancePack::LoadOnlyAlgorithm(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false){
		return false;
	}
	if(Ver>=10000){
		int32	ListNumb;
		AlgorithmList.RemoveAll();
		if(::Load(f,ListNumb)==false){
			return false;
		}
		for(int i=0;i<ListNumb;i++){
			RootNameList *a=new RootNameList();
			if(::Load(f,a->DLLRoot)==false){
				return false;
			}
			if(::Load(f,a->DLLName)==false){
				return false;
			}
			AlgorithmList.AppendList(a);
		}
		return true;
	}
	return false;
}

void	GUIInstancePack::ReflectMessage(void)
{
	for(GUIItemInstance *c=NPListPack<GUIItemInstance>::GetFirst();c!=NULL;c=c->GetNext()){
		c->ReflectMessage();
	}
}

void	GUIInstancePack::SetAcceptDropsForAll(void)
{
	for(GUIItemInstance *c=NPListPack<GUIItemInstance>::GetFirst();c!=NULL;c=c->GetNext()){
		c->SetAcceptDropsForAll();
	}
}

int32	GUIInstancePack::GetMaxInstanceID(void)
{
	int32	ret=0;
	for(GUIItemInstance *s=NPListPack<GUIItemInstance>::GetFirst();s!=NULL;s=s->GetNext()){
		if(ret<s->InstanceID){
			ret=s->InstanceID;
		}
	}
	return(ret+1);
}

void	GUIInstancePack::SetGridUnitForEditMode(int n)
{
	for(GUIItemInstance *s=NPListPack<GUIItemInstance>::GetFirst();s!=NULL;s=s->GetNext()){
		s->SetGridUnitForEditMode(n);
	}
}

int		GUIInstancePack::GetGridUnitForEditMode(void)
{
	GUIItemInstance *s=NPListPack<GUIItemInstance>::GetFirst();
	if(s!=NULL){
		return s->GetGridUnitForEditMode();
	}
	return 1;
}

GUIFormBase	*GUIInstancePack::CreateMainForm(LayersBase *LayersBasePointer ,_FormPosition Pos 
									,bool ModeAddSystemMenu)
{
	for(GUIItemInstance	*h=NPListPack<GUIItemInstance>::GetFirst();h!=NULL;h=h->GetNext()){
		h->Parent=this;
	}
	MainGUIFormBase	*f=NULL;
	GUIItemInstance	*v=NPListPack<GUIItemInstance>::GetFirst();
	QScreen	*Scr=QGuiApplication::screens()[0];
	QRect R= Scr->geometry();	//QApplication::desktop()->screenGeometry();
	if(v!=NULL){
		f=new MainGUIFormBase(LayersBasePointer);
		//f->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint | Qt::WindowTitleHint);
		if(ModeAddSystemMenu==true){
			f->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);
		}
		else{
			f->setWindowFlags(Qt::WindowTitleHint);
		}
		v->Handle=f;
		f->setGeometry(v->GUIPositionX1,v->GUIPositionY1,v->GUIPositionX2-v->GUIPositionX1+1,v->GUIPositionY2-v->GUIPositionY1+1);
		f->FormPosition=Pos;
		switch(Pos){
			case _Center:
				f->move((R.width()-f->width())/2,(R.height()-f->height())/2);
				break;
			case _AttachTop:
				f->move(f->geometry().left(),0);
				break;
			case _AttachLeft:
				f->move(0,f->geometry().top());
				break;
			case _AttachBottom:
				f->move(f->geometry().left(),R.height()-f->height());
				break;
			case _AttachRight:
				f->move(R.width()-f->width(),f->geometry().top());
				break;
			case _None:
				break;
			default:
				break;
		}
		f->ReflectGUILanguage();
		f->InitialPrepare();
		f->Prepare();
		f->AfterPrepare();
		f->show();
	}
	return f;
}

void	GUIInstancePack::ShowAll(GUIFormBase	*f
								,LayersBase *LayersBasePointer
								,ParamBase *PBase
								,bool EditMode)
{
	GUIItemInstance	*v=NPListPack<GUIItemInstance>::GetFirst();
	SetupInstance(LayersBasePointer ,v,v->InstanceID ,PBase ,EditMode);
	ShowInstance(v->InstanceID);
	f->SetEnableBroadcastForAll(true);
	//f->ReflectAlignment();
	ReflectMessage();
	if(LayersBasePointer!=NULL
	&& LayersBasePointer->GetEntryPoint()!=NULL
	&& LayersBasePointer->GetEntryPoint()->IsMasterPC()==true){
		IdleTimer.setInterval(LayersBasePointer->GetParamGlobal()->IdleLoopMiliSec);
		connect(&IdleTimer,SIGNAL(timeout()),this,SLOT(TimeOutForIdle()),Qt::QueuedConnection);
		IdleTimer.start();
	}
	if(LayersBasePointer!=NULL){
		LayersBasePointer->CloseInformed();
	}
}

void	GUIInstancePack::ReadyParam(GUIFormBase	*f)
{
	f->BroadcastReadyParam();
}

void	GUIInstancePack::TimeOutForIdle(void)
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true){
		return;
	}
	if(GetLayersBase()->GetEnableLoopOnIdle()==false){
		return;
	}
	ReEntrant=true;

	MutexTimerFunc.lock();
	//DWORD	D1=::GetComputerMiliSec();
	for(TimerIdleFunctionList *f=TimerFuncList.GetFirst();f!=NULL;f=f->GetNext()){
		f->Func(GetLayersBase());
	}
	//DWORD	D2=::GetComputerMiliSec();
	//DWORD	SpentTime1=D2-D1;

	//for(GUIItemInstance	*v=NPListPack<GUIItemInstance>::GetFirst();v!=NULL;v=v->GetNext()){
	//	if(v->Handle!=NULL){
	//		v->Handle->OnIdleCountUp();
	//	}
	//}

	bool	GUIResult=true;
	for(GUIItemInstance	*v=NPListPack<GUIItemInstance>::GetFirst();v!=NULL;v=v->GetNext()){
		if(v->Handle!=NULL){
			if(v->Handle->LoopOnIdle()==false){
				GUIResult=false;
			}
		}
	}
	if(GUIResult==false){
		GUIResult=true;
		for(GUIItemInstance	*v=NPListPack<GUIItemInstance>::GetFirst();v!=NULL;v=v->GetNext()){
			if(v->Handle!=NULL){
				if(v->Handle->LoopOnIdle()==false){
					GUIResult=false;
				}
			}
		}
	}
	//DWORD	D3=::GetComputerMiliSec();
	//DWORD	SpentTime2=D3-D2;
	GetLayersBase()->LoopOnIdle();

	//DWORD	D4=::GetComputerMiliSec();
	//DWORD	SpentTime3=D4-D3;

	if(GetEntryPoint()!=NULL){
		GetEntryPoint()->LoopOnIdle();
	}
	//DWORD	D5=::GetComputerMiliSec();
	//DWORD	SpentTime4=D5-D4;

	MutexTimerFunc.unlock();

	ReEntrant=false;
}

void	GUIInstancePack::AppendTimerFunc(void (*Func)(LayersBase *))
{
	TimerIdleFunctionList	*L=new TimerIdleFunctionList();
	L->Func=Func;
	MutexTimerFunc.lock();
	TimerFuncList.AppendList(L);
	MutexTimerFunc.unlock();
}

void	GUIInstancePack::RemoveTimerFunc(void (*Func)(LayersBase *))
{
	MutexTimerFunc.lock();
PNext:;
	for(TimerIdleFunctionList *f=TimerFuncList.GetFirst();f!=NULL;f=f->GetNext()){
		if(f->Func==Func){
			TimerFuncList.AppendList(f);
			delete	f;
			goto	PNext;
		}
	}
	MutexTimerFunc.unlock();
}

GUIFormBase	*GetChildNumberWidget(QObject *base ,int matchNumber)
{
	GUIFormBase *b=dynamic_cast<GUIFormBase *>(base);
	if(b!=NULL){
		if(b->GetFormBaseID()==matchNumber){
			return b;
		}
	}
	QObjectList Q=base->children();
	for(int i=0;i<Q.count();i++){
		GUIFormBase *k=dynamic_cast<GUIFormBase *>(Q[i]);
		if(k!=NULL && k->IsCreatedInGUIDLL()==true){
			continue;
		}
		GUIFormBase *C=GetChildNumberWidget(Q[i] ,matchNumber);
		if(C!=NULL){
			if(C->IsCreatedInGUIDLL()==true){
				continue;
			}
			return C;
		}
	}
	return NULL;
}

static	int	GUIInstancePackError=0;
void	GUIInstancePack::SetupInstance(LayersBase *LayersBasePointer ,GUIItemInstance *parent,int32 parentid ,ParamBase *PBase ,bool EditMode)
{
	GUIFormBase	*f;
	GUIItemInstance	*v;
	for(v=NPListPack<GUIItemInstance>::GetFirst();v!=NULL;v=v->GetNext()){
		if(v->DLLAccess!=NULL && v->DLLAccess->Name=="ButtonExit"){
			GUIInstancePackError++;
		}
		if(v->ParentInstanceID==parentid){
			int	StartPoint=PBase->GetParamCount();
			if(v->DLLAccess!=NULL){
				LayersBasePointer->InformToLoadDLL(v->DLLAccess->GetFileName());
				QWidget *QParent=NULL;
				if(parent->Handle!=NULL){
					if(v->ChildNumber!=-1){
						GUIFormBase	*w=GetChildNumberWidget(parent->Handle,v->ChildNumber);
						QParent=w;
						f=v->DLLAccess->CreateInstance(LayersBasePointer,w);
					}
					else{
						QParent=parent->Handle;
						f=v->DLLAccess->CreateInstance(LayersBasePointer,parent->Handle);
					}
				}
				if(f!=NULL){
					f->SetParent(GetParent() ,this);
				}
				v->Handle=f;
				DWORD ErrorCode;
				StructListPack	SaveStructInstance;
				SaveStructInstance=v->StructInstance;
				//if(v->DLLAccess!=NULL && v->DLLAccess->GetDLLName()=="GeneralDisplayWholeImage"){
				//	QMessageBox::critical ( NULL, /**/"SetupInstance ", QString(/**/"DLLRoot:")+v->DLLAccess->GetDLLRoot()
				//												+ QString(/**/" DLLName:")+v->DLLAccess->GetDLLName()
				//												+ QString(/**/" Inst:")+v->tmpName
				//												+ QString(/**/" 0")
				//												, QMessageBox::Ok);
				//}

				v->Initial(LayersBasePointer,QParent,ErrorCode ,v->DLLAccess);
				//if(v->DLLAccess!=NULL && v->DLLAccess->GetDLLName()=="GeneralDisplayWholeImage"){
				//	QMessageBox::critical ( NULL, /**/"SetupInstance ", QString(/**/"DLLRoot:")+v->DLLAccess->GetDLLRoot()
				//												+ QString(/**/" DLLName:")+v->DLLAccess->GetDLLName()
				//												+ QString(/**/" Inst:")+v->tmpName
				//												+ QString(/**/" 1")
				//												, QMessageBox::Ok);
				//}
				v->StructInstance.CopyFrom(SaveStructInstance);
				//if(v->DLLAccess!=NULL && v->DLLAccess->GetDLLName()=="GeneralDisplayWholeImage"){
				//	QMessageBox::critical ( NULL, /**/"SetupInstance ", QString(/**/"DLLRoot:")+v->DLLAccess->GetDLLRoot()
				//												+ QString(/**/" DLLName:")+v->DLLAccess->GetDLLName()
				//												+ QString(/**/" Inst:")+v->tmpName
				//												+ QString(/**/" 2")
				//												, QMessageBox::Ok);
				//}
				f->ReflectGUILanguage();
				v->ReflectToFormData(ErrorCode ,v->DLLAccess);
				//if(v->DLLAccess!=NULL && v->DLLAccess->GetDLLName()=="GeneralDisplayWholeImage"){
				//	QMessageBox::critical ( NULL, /**/"SetupInstance ", QString(/**/"DLLRoot:")+v->DLLAccess->GetDLLRoot()
				//												+ QString(/**/" DLLName:")+v->DLLAccess->GetDLLName()
				//												+ QString(/**/" Inst:")+v->tmpName
				//												+ QString(/**/" 3")
				//												, QMessageBox::Ok);
				//}
			}
			else{
				f=new GUIFormBase(LayersBasePointer);
				v->Handle=f;
			}
			int	EndPoint=PBase->GetParamCount();
			if(StartPoint!=EndPoint){
				PBase->LoadDefault(LayersBasePointer->GetUserPath(),StartPoint,EndPoint);
			}
			//if(v->DLLAccess!=NULL){
			//	QMessageBox::critical ( NULL, /**/"ShowAll ", QString(/**/"DLLRoot:")+v->DLLAccess->GetDLLRoot()
			//												+ QString(/**/" DLLName:")+v->DLLAccess->GetDLLName()
			//												+ QString(/**/" Inst:")+v->tmpName
			//												, QMessageBox::Ok);
			//}

			f->setGeometry(v->GUIPositionX1,v->GUIPositionY1,v->GUIPositionX2-v->GUIPositionX1+1,v->GUIPositionY2-v->GUIPositionY1+1);
			f->ReflectAlignment();
			f->InitialPrepare();
			f->Prepare();
			f->SetName(v->tmpName);
			f->SetComment(v->tmpComment);
			f->SetAlignment(v->tmpAlignment);
			f->SetFormBaseID(v->FormBaseID);
			//f->AfterPrepare();
			//if(v->DLLAccess!=NULL){
			//	QMessageBox::critical ( NULL, /**/"ShowAll ", QString(/**/"DLLRoot:")+v->DLLAccess->GetDLLRoot()
			//												+ QString(/**/" DLLName:")+v->DLLAccess->GetDLLName()
			//												+ QString(/**/" Inst:")+v->tmpName
			//												+ QString(/**/" A")
			//												, QMessageBox::Ok);
			//}
			if(f->objectName().isEmpty()){
				f->setObjectName(v->tmpName);
			}

			if(GetLayersBase()->GetEntryPoint()->GUIIsEditMode()==true){
				f->SetEditMode();
				f->CreateSelectedWindow();
				v->connect(v->Handle,SIGNAL(SignalMove())	,v,SLOT(SlotMove()));
				v->connect(v->Handle,SIGNAL(SignalResize())	,v,SLOT(SlotResize()));
				v->connect(v->Handle,SIGNAL(SignalRelease()),v,SLOT(SlotRelease()));
			}
			//f->show();
			SetupInstance(LayersBasePointer ,v,v->InstanceID ,PBase,EditMode);			
		}
		else{
			GUIInstancePackError++;
		}
	}
}

void	GUIInstancePack::AfterPrepare(void)
{
	GUIItemInstance	*v;
	for(v=NPListPack<GUIItemInstance>::GetFirst();v!=NULL;v=v->GetNext()){
		if(v->Handle!=NULL){
			v->Handle->AfterPrepare();
		}
	}
}

void	GUIInstancePack::AfterStartSequence(void)
{
	GUIItemInstance	*v;
	for(v=NPListPack<GUIItemInstance>::GetFirst();v!=NULL;v=v->GetNext()){
		if(v->Handle!=NULL){
			v->Handle->AfterStartSequence();
		}
	}
}
void	GUIInstancePack::ShowInstance(int32 parentid)
{
	GUIItemInstance	*v;
	for(v=NPListPack<GUIItemInstance>::GetFirst();v!=NULL;v=v->GetNext()){
		if(v->ParentInstanceID==parentid){	
			v->Handle->show();
			ShowInstance(v->InstanceID);			
		}
	}
}

void	GUIInstancePack::CloseAll(void)
{
	GUIItemInstance	*v=NPListPack<GUIItemInstance>::GetFirst();
	if(v!=NULL){
		v->Handle->close();
	}
}

ExeResult	GUIInstancePack::ExecuteStartByInspection	(void)
{
	ExeResult	Ret=_ER_true;
	for(GUIFormBasePointer *f=RegisteredStartByInspection.GetFirst();f!=NULL;f=f->GetNext()){
		ExeResult	r=f->GetForm()->ExecuteStartByInspection();
		if(r!=_ER_true){
			Ret=r;
		}
	}
	return Ret;
}
ExeResult	GUIInstancePack::ExecutePreAlignment		(void)
{
	ExeResult	Ret=_ER_true;
	for(GUIFormBasePointer *f=RegisteredPreAlignment.GetFirst();f!=NULL;f=f->GetNext()){
		ExeResult	r=f->GetForm()->ExecutePreAlignment();
		if(r!=_ER_true){
			Ret=r;
		}
	}
	return Ret;
}
ExeResult	GUIInstancePack::ExecuteAlignment			(void)
{
	ExeResult	Ret=_ER_true;
	for(GUIFormBasePointer *f=RegisteredAlignment.GetFirst();f!=NULL;f=f->GetNext()){
		ExeResult	r=f->GetForm()->ExecuteAlignment();
		if(r!=_ER_true){
			Ret=r;
		}
	}
	return Ret;
}
ExeResult	GUIInstancePack::ExecutePreProcessing		(void)
{
	ExeResult	Ret=_ER_true;
	for(GUIFormBasePointer *f=RegisteredPreProcessing.GetFirst();f!=NULL;f=f->GetNext()){
		ExeResult	r=f->GetForm()->ExecutePreProcessing();
		if(r!=_ER_true){
			Ret=r;
		}
	}
	return Ret;
}
ExeResult	GUIInstancePack::ExecuteProcessing			(void)
{
	ExeResult	Ret=_ER_true;
	for(GUIFormBasePointer *f=RegisteredProcessing.GetFirst();f!=NULL;f=f->GetNext()){
		ExeResult	r=f->GetForm()->ExecuteProcessing();
		if(r!=_ER_true){
			Ret=r;
		}
	}
	return Ret;
}
ExeResult	GUIInstancePack::ExecuteProcessingRevived	(void)
{
	ExeResult	Ret=_ER_true;
	for(GUIFormBasePointer *f=RegisteredProcessingRevived.GetFirst();f!=NULL;f=f->GetNext()){
		ExeResult	r=f->GetForm()->ExecuteProcessingRevived();
		if(r!=_ER_true){
			Ret=r;
		}
	}
	return Ret;
}
ExeResult	GUIInstancePack::ExecutePostProcessing		(void)
{
	ExeResult	Ret=_ER_true;
	for(GUIFormBasePointer *f=RegisteredPostProcessing.GetFirst();f!=NULL;f=f->GetNext()){
		ExeResult	r=f->GetForm()->ExecutePostProcessing();
		if(r!=_ER_true){
			Ret=r;
		}
	}
	return Ret;
}
ExeResult	GUIInstancePack::ExecuteFinished	(void)
{
	ExeResult	Ret=_ER_true;
	for(GUIFormBasePointer *f=RegisteredPostProcessing.GetFirst();f!=NULL;f=f->GetNext()){
		ExeResult	r=f->GetForm()->ExecuteFinished();
		if(r!=_ER_true){
			Ret=r;
		}
	}
	return Ret;
}

void	GUIInstancePack::ViewRefreshInPlayer(int64 shownInspectionID)
{
	for(GUIItemInstance	*v=NPListPack<GUIItemInstance>::GetFirst();v!=NULL;v=v->GetNext()){
		v->ViewRefreshInPlayer(shownInspectionID);
	}
}
void	GUIInstancePack::ViewOnTheWayInPlayer(int64 shownInspectionID)
{
	for(GUIItemInstance	*v=NPListPack<GUIItemInstance>::GetFirst();v!=NULL;v=v->GetNext()){
		v->ViewOnTheWayInPlayer(shownInspectionID);
	}
}
void	GUIInstancePack::RefreshByEveryInspection(int64 shownInspectionID)
{
	for(GUIItemInstance	*v=NPListPack<GUIItemInstance>::GetFirst();v!=NULL;v=v->GetNext()){
		v->RefreshByEveryInspection(shownInspectionID);
	}
}
void	GUIInstancePack::ViewRefreshInEdit(void)
{
	for(GUIItemInstance	*v=NPListPack<GUIItemInstance>::GetFirst();v!=NULL;v=v->GetNext()){
		v->ViewRefreshInEdit();
	}
}
void	GUIInstancePack::ViewRefreshInScanning(int64 shownInspectionID)
{
	for(GUIItemInstance	*v=NPListPack<GUIItemInstance>::GetFirst();v!=NULL;v=v->GetNext()){
		v->ViewRefreshInScanning(shownInspectionID);
	}
}

void	GUIInstancePack::DelayedViewRefreshInPlayer(int64 shownInspectionID ,int MiliSec)
{
	DThread.SetViewRefreshInPlayer (shownInspectionID ,MiliSec);
}

void	GUIInstancePack::SlotViewRefreshInPlayer (int shownInspectionID)
{
	for(GUIItemInstance	*v=NPListPack<GUIItemInstance>::GetFirst();v!=NULL;v=v->GetNext()){
		v->ViewRefreshInPlayer(shownInspectionID);
	}
}

void	GUIInstancePack::SlotViewOnTheWayInPlayer (int shownInspectionID)
{
	for(GUIItemInstance	*v=NPListPack<GUIItemInstance>::GetFirst();v!=NULL;v=v->GetNext()){
		v->ViewOnTheWayInPlayer(shownInspectionID);
	}
}

void	GUIInstancePack::SlotViewRefreshInScanning (int shownInspectionID)
{
	for(GUIItemInstance	*v=NPListPack<GUIItemInstance>::GetFirst();v!=NULL;v=v->GetNext()){
		v->ViewRefreshInScanning(shownInspectionID);
	}
}

void	GUIInstancePack::DoneExecute(int64 shownInspectionID,ExecuteInspectBase::MotionMode mode)
{
	for(GUIItemInstance	*v=NPListPack<GUIItemInstance>::GetFirst();v!=NULL;v=v->GetNext()){
		v->DoneExecute(shownInspectionID,mode);
	}
}

GUIItemInstance	*GUIInstancePack::Search(GUIFormBase *m)
{
	for(GUIItemInstance *v=NPListPack<GUIItemInstance>::GetFirst();v!=NULL;v=v->GetNext()){
		if(v->Handle==m){
			return(v);
		}
	}
	return(NULL);
}

void	GUIInstancePack::GetEntryAlgorithm(RootNameListContainer &List)
{
	for(GUIItemInstance *v=NPListPack<GUIItemInstance>::GetFirst();v!=NULL;v=v->GetNext()){
		RootNameListContainer TmpList;
		if(v->DLLAccess!=NULL){
			v->DLLAccess->EntryAlgorithm(TmpList);
			for(RootNameList *L=TmpList.GetFirst();L!=NULL;L=L->GetNext()){
				RootNameList	*Boss;
				for(Boss=List.GetFirst();Boss!=NULL;Boss=Boss->GetNext()){
					if(Boss->DLLRoot==L->DLLRoot && Boss->DLLName==L->DLLName){
						break;
					}
				}
				if(Boss==NULL){
					List.AppendList(new RootNameList(L->DLLRoot,L->DLLName));
				}
			}
		}
	}
}

void	GUIInstancePack::AssociateComponent	 (ComponentListContainer &List)
{
	for(GUIItemInstance *v=NPListPack<GUIItemInstance>::GetFirst();v!=NULL;v=v->GetNext()){
		ComponentListContainer TmpList;
		if(v->DLLAccess!=NULL){
			v->DLLAccess->AssociateComponent(TmpList);
			for(ComponentList *L=TmpList.GetFirst();L!=NULL;L=L->GetNext()){
				ComponentList	*Boss;
				for(Boss=List.GetFirst();Boss!=NULL;Boss=Boss->GetNext()){
					if(*Boss==*L){
						break;
					}
				}
				if(Boss==NULL){
					ComponentList	*d=new ComponentList(*L);
					List.AppendList(d);
				}
			}
		}
	}
}

void	GUIInstancePack::RemoveUselessGUI(GuiDLLItem *g)
{
	for(GUIItemInstance *v=NPListPack<GUIItemInstance>::GetFirst();v!=NULL;){
		GUIItemInstance *VNext=v->GetNext();
		if(v->DLLAccess==g){
			NPListPack<GUIItemInstance>::RemoveList(v);
			delete	v;
		}
		v=VNext;
	}
}

//=================================================================


void	GUIInitializer::Release(void)
{
	for(int i=0;i<CommRootNumb;i++){
		if(CommRoot[i]!=NULL){
			delete	CommRoot[i];
			CommRoot[i]=NULL;
		}
	}
}

bool	GUIInitializer::Initial(LayersBase *Base,DWORD &ErrorCode ,QString &ErrorMsg,bool LoadAll)
{
	qRegisterMetaType<int64>(/**/"int64");

	QStringList	GUIPath;
	GUIPath.append(DefGUIPath);
	GUIPath.append(DefIntegratorGUIPath);
	GUIPath.append(DefRegulusWorldGUIPath);

	if(SearchAddDLL(Base,GUIPath ,ErrorCode ,ErrorMsg,LoadAll)==false){
		return false;
	}

	const	char	*LNameStr=/**/"Replace.def";
	QString	LName=LNameStr;
	if(QFile::exists (LName)==true){
		FILE	*file=fopen(LNameStr,/**/"rt");
		if(file!=NULL){
			LoadReplaceNameList(file);
			fclose(file);
		}
	}
	for(GuiDLLItem *L=GuiDLLPack->GetFirst();L!=NULL;L=L->GetNext()){
		bool	NextAddMode=false;
		for(GUIRootClassified *d=RootList.GetFirst();d!=NULL;d=d->GetNext()){
			if(d->Root==L->RootName){
				d->NameList.AppendList(new GUINameClassified(L));
				NextAddMode=true;
				break;
			}
		}
		if(NextAddMode==false){
			GUIRootClassified	*e=new GUIRootClassified(L->RootName);
			e->NameList.AppendList(new GUINameClassified(L));
			RootList.AppendList(e);
		}
	}
	QStringList	tErrorMsg;
	if(CheckDuplicated(tErrorMsg)==true){
		for(int i=0;i<tErrorMsg.count();i++){
			ErrorMsg +=tErrorMsg[i];
		}
		return false;
	}
	return true;
}
void	GUIInitializer::InitialIntegration(void)
{
	if(IntegrationComm!=NULL){
		IntegrationComm->Start();
	}
}
bool	GUIInitializer::CheckDuplicated(QStringList &Error)
{
	bool	Dup=false;
	for(GuiDLLItem *L=GuiDLLPack->GetFirst();L!=NULL;L=L->GetNext()){
		if(L->RootName=="" && L->Name==""){
			QString	Msg=QString("No Root and Name in GUI (")
						+L->RootName
						+QString(",")
						+L->Name
						+QString(")");
			Error.append(Msg);
			Dup=true;
		}
		else{
			for(GuiDLLItem *M=L->GetNext();M!=NULL;M=M->GetNext()){
				if(L->RootName==M->RootName && L->Name==M->Name){
					QString	Msg=QString("Installed duplicated GUI (")
								+L->RootName
								+QString(",")
								+L->Name
								+QString(")");
					Error.append(Msg);
					Dup=true;
				}
			}
		}
	}
	return Dup;
}

bool	GUIInitializer::LoadExcludedFileList(const QString &GUIExcludedListFile,QStringList	&ExcludedFiles)
{
	QFile	F(GUIExcludedListFile);
	if(F.open(QIODevice::ReadOnly)==true){
		QTextStream	Str(&F);
		while(Str.atEnd()==false){
			QString	L=Str.readLine();
			L=L.trimmed ();
			if(L.left(2)=="//"){
				continue;
			}
			ExcludedFiles.append(L);
		}
		return true;
	}
	return false;
}

bool	GUIInitializer::SearchAddDLL(LayersBase *Base,const QStringList &pathlist
									 ,DWORD &ErrorCode ,QString &ErrorMsg,bool LoadAll)
{
	

	QString	NowD=QDir::currentPath();
	GuiDLLItem	*DLL;
	QString	FileName;
	QStringList	ExcludedFiles;

	if(LoadAll==false){
		LoadExcludedFileList(Base->GetParamGlobal()->GUIExcludedListFile,ExcludedFiles);
	}
	bool	Ret=false;
	for(int k=0;k<pathlist.count();k++){
		QDir::setCurrent(NowD);
		QString	path=pathlist[k];
		QDir	Dir;
		if(Dir.cd(path)==true){
			QString	SearchFile=QString(/**/"*.")+GetDynamicFileExt();
			QStringList nameFilters(SearchFile);
			QStringList List=Dir.entryList ( nameFilters, QDir::Files, QDir::NoSort );
			int	N=0;
			for(int i=0;i<List.size();i++){
				QString	DLLFileName=List.at(i);
				for(int k=0;k<ExcludedFiles.count();k++){
					if(ExcludedFiles[k].toLower()==DLLFileName.toLower()){
						goto	LNext;
					}
				}
				FileName=path+QString(QDir::separator())+DLLFileName;
				Base->TestLoadDLL(FileName);
				if(QLibrary::isLibrary(FileName)==true){
					DLL=new GuiDLLItem(Base);
					QDir::setCurrent(NowD);
					if(DLL->LoadDLL(Base,FileName,ErrorCode)==false){
						delete	DLL;
						ErrorMsg=QString(/**/"GUI-DLL Error on loading : ")+FileName;
						return(false);
					}
					GuiDLLPack->AppendList(DLL);
					N++;
				}
				LNext:;
			}
			Ret=true;
		}
	}
	QDir::setCurrent(NowD);
	if(Ret==true)
		return true;
	ErrorCode=Error_DLL_NotExistPath;
	return false;
}
void	GUIInitializer::SetLanguageCode(int LanguageCode)
{
	for(GuiDLLItem *v=GuiDLLPack->GetFirst();v!=NULL;v=v->GetNext()){
		v->SetLanguageCode(LanguageCode);
	}
}
bool	GUIInitializer::CheckSystemVersion(QStringList &Str)
{
	bool	Ret=true;
	for(GuiDLLItem *L=GuiDLLPack->GetFirst();L!=NULL;L=L->GetNext()){
		if(L->CheckSystemVersion(Str)==false){
			Ret=false;
		}
	}
	return Ret;
}
	
void	GUIInitializer::SetGridUnitForEditMode(int n)
{
	for(GUIInstancePack *L=GUIInstanceRoot.GetFirst();L!=NULL;L=L->GetNext()){
		L->SetGridUnitForEditMode(n);
	}
}

int		GUIInitializer::GetGridUnitForEditMode(void)
{
	GUIInstancePack	*L=GUIInstanceRoot.GetFirst();
	if(L!=NULL){
		return L->GetGridUnitForEditMode();
	}
	return 1;
}

void	GUIInitializer::InitialMultiComputer(QObject * parent)
{
	if(GetParamComm()->Mastered==true){
		CommRoot[CommRootNumb]=new GUIFastComm(GetLayersBase(),parent);
		CommRootNumb++;
		for(int i=0;i<GetParamComm()->ConnectedPCNumb;i++){
			ConnectionInfo	*p=GetParamComm()->GetConnection(i);
			if(p!=NULL){
				QString	PortStr=p->IPAddress.section(':',1,1);
				if(PortStr.isEmpty()==true){
					CommRoot[0]->AddReqConnection(parent ,i,p->IPAddress,GUICommPort);
				}
				else{
					CommRoot[0]->AddReqConnection(parent ,i,p->IPAddress.section(':',0,0),PortStr.toInt());
				}
			}
		}
		if(GetParamComm()->ConnectedPCNumb!=0){
			CommRoot[0]->StartAllReqConnection(GetParamGlobal()->WaitMilisecForConnect);
		}
	}
	else{
		for(int i=0;i<GetParamComm()->ConnectedPCNumb;i++){
			CommRoot[CommRootNumb]=new GUIFastComm(GetLayersBase(),parent);
			ConnectionInfo	*p=GetParamComm()->GetConnection(i);
			if(p!=NULL){
				QString	PortStr=p->IPAddress.section(':',1,1);
				if(PortStr.isEmpty()==true){
					CommRoot[CommRootNumb]->StartServer(GUICommPort);
				}
				else{
					CommRoot[CommRootNumb]->StartServer(PortStr.toInt());
				}
			}
			CommRootNumb++;
		}
	}
}

void	GUIInitializer::InitialMultiComputerAgain(QObject * parent)
{
	if(GetParamComm()->Mastered==true){
		if(CommRoot[0]!=NULL){	
			if(GetParamComm()->ConnectedPCNumb!=0){
				CommRoot[0]->StartAllReqConnection(GetParamGlobal()->WaitMilisecForConnect);
			}
		}
	}
}
void	GUIInitializer::RemoveUselessGUI(void)
{
	for(GuiDLLItem *g=GuiDLLPack->GetFirst();g!=NULL;){
		GuiDLLItem *GNext=g->GetNext();
		if(g->UsedInGUI==false){
			for(GUIRootClassified *r=RootList.GetFirst();r!=NULL;r=r->GetNext()){
				for(GUINameClassified *q=r->NameList.GetFirst();q!=NULL;q=q->GetNext()){
					if(q->Point==g){
						r->NameList.RemoveList(q);
						delete	q;
						break;
					}
				}
			}
			for(GUIInstancePack *s=GUIInstanceRoot.GetFirst();s!=NULL;s=s->GetNext()){
				s->RemoveUselessGUI(g);
			}
			if(GetLayersBase()!=NULL){
				GetLayersBase()->RemovePacket(g->GetDLLRoot(),g->GetDLLName());
			}
			GuiDLLPack->RemoveList(g);
			delete	g;
		}
		g=GNext;
	}
}
void	GUIInitializer::AfterStartSequence(void)
{
	for(GUIInstancePack *c=GUIInstanceRoot.GetFirst();c!=NULL;c=c->GetNext()){
		c->AfterStartSequence();
	}
}

bool	GUIInitializer::TxData(int32 globalPage 
							,struct EntryPointBase::EntryPointPacketInfo &IndoPacket
							,int CommID ,QBuffer *f
							,ErrorCodeList &ErrorData)
{
	if(CommRoot[CommID]!=NULL){
		return CommRoot[CommID]->TxData(globalPage ,IndoPacket,CommID ,f,ErrorData);
	}
	else if(CommRoot[0]!=NULL){
		return CommRoot[0]->TxData(globalPage ,IndoPacket,CommID ,f,ErrorData);
	}
	return false;
}
bool	GUIInitializer::TxData(int32 globalPage 
							,struct EntryPointBase::EntryPointPacketInfo &IndoPacket
							,int CommID ,QByteArray *f
							,ErrorCodeList &ErrorData)
{
	if(CommRoot[CommID]!=NULL){
		return CommRoot[CommID]->TxData(globalPage ,IndoPacket,CommID ,f,ErrorData);
	}
	else if(CommRoot[0]!=NULL){
		return CommRoot[0]->TxData(globalPage ,IndoPacket,CommID ,f,ErrorData);
	}
	return false;
}
bool	GUIInitializer::TxIntegrationData(int32 slaveNo 
							,struct EntryPointBase::EntryPointPacketInfo &IndoPacket
							,QBuffer *f
							,ErrorCodeList &ErrorData)
{
	if(IntegrationComm!=NULL){
		bool	Ret=IntegrationComm->Send(slaveNo ,IndoPacket
										,f->buffer(),ErrorData);
		return Ret;
	}
	return false;
}

QTcpSocket	*GUIInitializer::GetSocket(int ComNo)
{
	if(CommRoot[0]!=NULL){
		return CommRoot[0]->GetSocket(ComNo);
	}
	return NULL;
}

QTcpSocket	*GUIInitializer::GetIntegrationSocket(int slaveNo)
{
	if(IntegrationComm!=NULL){
		IntegrationCommPipe	*s=IntegrationComm->GetSocket(slaveNo);
		if(s!=NULL){
			return s->GetSocket();
		}
	}
	return NULL;
}


GuiDLLItem	*GUIInitializer::Search(QString &rootName ,QString &name)
{
	for(ReplaceNameList *r=ReplaceNameListData.GetFirst();r!=NULL;r=r->GetNext()){
		if(r->OldRoot==rootName && r->OldName==name){
			rootName=r->NewRoot;
			name	=r->NewName;
			break;
		}
	}
	for(GuiDLLItem *c=GuiDLLPack->GetFirst();c!=NULL;c=c->GetNext()){
		if(c->RootName==rootName && c->Name==name){
			return(c);
		}
	}
	return(NULL);
}

bool	GUIInitializer::LoadReplaceNameList(FILE *file)
{
	char	Buff[100];
	char	OldRootBuff[100];
	char	OldNameBuff[100];
	char	NewRootBuff[100];
	char	NewNameBuff[100];

	ReplaceNameListData.RemoveAll();

	while(fgets(Buff,sizeof(Buff)-1,file)!=NULL){
		char	*fp=Buff;
		while(*fp==' ' || *fp=='\t'){
			fp++;
		}
		char	*cp=strchr(fp,',');
		if(cp==NULL){
			continue;
		}
		char	*kp=cp;
		while(*(kp-1)==' ' || *(kp-1)=='\t'){
			kp--;
		}
		int	n=kp-fp;
		strncpy(OldRootBuff,fp,n);
		OldRootBuff[n]=0;
		
		fp=cp+1;
		while(*fp==' ' || *fp=='\t'){
			fp++;
		}
		cp=strchr(fp,',');
		if(cp==NULL){
			continue;
		}
		kp=cp;
		while(*(kp-1)==' ' || *(kp-1)=='\t'){
			kp--;
		}
		n=kp-fp;
		strncpy(OldNameBuff,fp,n);
		OldNameBuff[n]=0;
		
		fp=cp+1;
		while(*fp==' ' || *fp=='\t'){
			fp++;
		}
		cp=strchr(fp,',');
		if(cp==NULL){
			continue;
		}
		kp=cp;
		while(*(kp-1)==' ' || *(kp-1)=='\t'){
			kp--;
		}
		n=kp-fp;
		strncpy(NewRootBuff,fp,n);
		NewRootBuff[n]=0;
		
		fp=cp+1;
		while(*fp==' ' || *fp=='\t'){
			fp++;
		}
		cp=strchr(fp,'\n');
		if(cp==NULL){
			continue;
		}
		kp=cp;
		while(*(kp-1)==' ' || *(kp-1)=='\t'){
			kp--;
		}
		n=kp-fp;
		strncpy(NewNameBuff,fp,n);
		NewNameBuff[n]=0;
		
		ReplaceNameList	*c=new ReplaceNameList();
		c->OldRoot=OldRootBuff;
		c->OldName=OldNameBuff;
		c->NewRoot=NewRootBuff;
		c->NewName=NewNameBuff;
		ReplaceNameListData.AppendList(c);
	}
	return true;
}

bool	GUIInitializer::InitialAdditionalFieldFromGUI(QSqlDatabase &DB,QString &ErrorMsg)
{
	int	R = 0;
	for(GuiDLLItem *c=GuiDLLPack->GetFirst();c!=NULL;c=c->GetNext(),R++){
		if(c->InitialAdditionalFieldFromGUI(DB)==false){
			ErrorMsg = QString("Error (")
				+ c->RootName
				+ QString(":")
				+ c->Name
				+ QString(") makes stop in InitialAdditionalFieldFromGUI")
				+ QString("(")
				+ QString::number(R)
				+ QString(")");
			return false;
		}
	}
	return true;
}
bool	GUIInitializer::CreateExcludedList(ExcludedListPack &EList)
{
	for(GuiDLLItem *c=GuiDLLPack->GetFirst();c!=NULL;c=c->GetNext()){
		if(c->CreateExcludedList(EList)==false){
			return false;
		}
	}
	return true;
}


void	GUIInitializer::ViewRefreshInPlayer(int64 shownInspectionID)
{
	for(GUIInstancePack *c=GUIInstanceRoot.GetFirst();c!=NULL;c=c->GetNext()){
		c->ViewRefreshInPlayer(shownInspectionID);
	}
}

void	GUIInitializer::ViewOnTheWayInPlayer(int64 shownInspectionID)
{
	for(GUIInstancePack *c=GUIInstanceRoot.GetFirst();c!=NULL;c=c->GetNext()){
		c->ViewOnTheWayInPlayer(shownInspectionID);
	}
}

void	GUIInitializer::RefreshByEveryInspection(int64 shownInspectionID)
{
	for(GUIInstancePack *c=GUIInstanceRoot.GetFirst();c!=NULL;c=c->GetNext()){
		c->RefreshByEveryInspection(shownInspectionID);
	}
}
void	GUIInitializer::ViewRefreshInEdit(void)
{
	for(GUIInstancePack *c=GUIInstanceRoot.GetFirst();c!=NULL;c=c->GetNext()){
		c->ViewRefreshInEdit();
	}
}
void	GUIInitializer::ViewRefreshInScanning(int64 shownInspectionID)
{
	for(GUIInstancePack *c=GUIInstanceRoot.GetFirst();c!=NULL;c=c->GetNext()){
		c->ViewRefreshInScanning(shownInspectionID);
	}
}
void	GUIInitializer::DelayedViewRefreshInPlayer(int64 shownInspectionID ,int MiliSec)
{
	for(GUIInstancePack *c=GUIInstanceRoot.GetFirst();c!=NULL;c=c->GetNext()){
		c->DelayedViewRefreshInPlayer(shownInspectionID,MiliSec);
	}
}
void	GUIInitializer::SetAcceptDropsForAll(void)
{
	for(GUIInstancePack *c=GUIInstanceRoot.GetFirst();c!=NULL;c=c->GetNext()){
		c->SetAcceptDropsForAll();
	}
}
ExeResult	GUIInitializer::ExecuteStartByInspection(void)
{
	ExeResult	Ret=_ER_true;
	for(GUIInstancePack *c=GUIInstanceRoot.GetFirst();c!=NULL;c=c->GetNext()){
		ExeResult	r=c->ExecuteStartByInspection();
		if(r!=_ER_true){
			Ret=r;
		}
	}
	return Ret;
}
ExeResult	GUIInitializer::ExecutePreAlignment		(void)
{
	ExeResult	Ret=_ER_true;
	for(GUIInstancePack *c=GUIInstanceRoot.GetFirst();c!=NULL;c=c->GetNext()){
		ExeResult	r=c->ExecutePreAlignment();
		if(r!=_ER_true){
			Ret=r;
		}
	}
	return Ret;
}
ExeResult	GUIInitializer::ExecuteAlignment		(void)
{
	ExeResult	Ret=_ER_true;
	for(GUIInstancePack *c=GUIInstanceRoot.GetFirst();c!=NULL;c=c->GetNext()){
		ExeResult	r=c->ExecuteAlignment();
		if(r!=_ER_true){
			Ret=r;
		}
	}
	return Ret;
}
ExeResult	GUIInitializer::ExecutePreProcessing	(void)
{
	ExeResult	Ret=_ER_true;
	for(GUIInstancePack *c=GUIInstanceRoot.GetFirst();c!=NULL;c=c->GetNext()){
		ExeResult	r=c->ExecutePreProcessing();
		if(r!=_ER_true){
			Ret=r;
		}
	}
	return Ret;
}
ExeResult	GUIInitializer::ExecuteProcessing		(void)
{
	ExeResult	Ret=_ER_true;
	for(GUIInstancePack *c=GUIInstanceRoot.GetFirst();c!=NULL;c=c->GetNext()){
		ExeResult	r=c->ExecuteProcessing();
		if(r!=_ER_true){
			Ret=r;
		}
	}
	return Ret;
}
ExeResult	GUIInitializer::ExecuteProcessingRevived(void)
{
	ExeResult	Ret=_ER_true;
	for(GUIInstancePack *c=GUIInstanceRoot.GetFirst();c!=NULL;c=c->GetNext()){
		ExeResult	r=c->ExecuteProcessingRevived();
		if(r!=_ER_true){
			Ret=r;
		}
	}
	return Ret;
}
ExeResult	GUIInitializer::ExecutePostProcessing	(void)
{
	ExeResult	Ret=_ER_true;
	for(GUIInstancePack *c=GUIInstanceRoot.GetFirst();c!=NULL;c=c->GetNext()){
		ExeResult	r=c->ExecutePostProcessing();
		if(r!=_ER_true){
			Ret=r;
		}
	}
	return Ret;
}
ExeResult	GUIInitializer::ExecuteFinished	(void)
{
	ExeResult	Ret=_ER_true;
	for(GUIInstancePack *c=GUIInstanceRoot.GetFirst();c!=NULL;c=c->GetNext()){
		ExeResult	r=c->ExecuteFinished();
		if(r!=_ER_true){
			Ret=r;
		}
	}
	return Ret;
}
//===========================================================================================================

SocketForMainGUI::SocketForMainGUI(QLocalSocket *s,MainGUIFormBase *p)
	:Sock(s),Parent(p)
{
	connect(Sock,SIGNAL(disconnected()),this,SLOT(SlotDisconnected()));
	connect(Sock,SIGNAL(readyRead()),this,SLOT(SlotReadyRead()));
}

void	SocketForMainGUI::SlotDisconnected()
{
	for(SocketForMainGUI *s=Parent->IdentificationSocket.GetFirst();s!=NULL;s=s->GetNext()){
		if(s==this){
			Parent->IdentificationSocket.RemoveList(s);
			s->deleteLater();
		}
	}
}
void	SocketForMainGUI::SlotReadyRead ()
{
	struct	SocketForMainGUIPacketHeader	Header;
	if(Sock->read((char *)&Header,sizeof(Header))!=sizeof(Header))
		return;
	BYTE	*Buff=new BYTE[Header.DataLen];
	if(Sock->read((char *)Buff,Header.DataLen)!=Header.DataLen){
		delete	[]Buff;
		return;
	}
	if(Header.Cmd==Cmd_SocketForMainGUIPacketHeader_ReqAck){
		struct	SocketForMainGUIPacketHeader	RHeader;
		RHeader.Cmd	=Cmd_SocketForMainGUIPacketHeader_AckMask + Cmd_SocketForMainGUIPacketHeader_ReqAck;
		RHeader.DataLen	=sizeof(qint64);
		if(Sock->write((const char *)&RHeader,sizeof(RHeader))!=sizeof(RHeader)){
			delete	[]Buff;
			return;
		}
		Sock->flush();
	}
	else
	if(Header.Cmd==Cmd_SocketForMainGUIPacketHeader_ReqPID){
		qint64	pid=QCoreApplication::applicationPid ();
		struct	SocketForMainGUIPacketHeader	RHeader;
		RHeader.Cmd	=Cmd_SocketForMainGUIPacketHeader_AckMask + Cmd_SocketForMainGUIPacketHeader_ReqPID;
		RHeader.DataLen	=sizeof(qint64);
		if(Sock->write((const char *)&RHeader,sizeof(RHeader))!=sizeof(RHeader)){
			delete	[]Buff;
			return;
		}
		if(Sock->write((const char *)&pid,sizeof(pid))!=sizeof(pid)){
			delete	[]Buff;
			return;
		}
		Sock->flush();
	}
	else
	if(Header.Cmd==Cmd_SocketForMainGUIPacketHeader_SetGeometry){
		int32	x1,y1,x2,y2;
		QByteArray	Array=QByteArray::fromRawData((const char *)Buff,Header.DataLen);
		QBuffer	ABuff(&Array);
		ABuff.open(QIODevice::ReadOnly);
		::Load(&ABuff,x1);
		::Load(&ABuff,y1);
		::Load(&ABuff,x2);
		::Load(&ABuff,y2);
		Parent->setGeometry(x1,y1,x2-x1,y2-y1);
	}
	else
	if(Header.Cmd==Cmd_SocketForMainGUIPacketHeader_ReqClose){
		Parent->GetLayersBase()->CloseAll();
	}
	else
	if(Header.Cmd==Cmd_SocketForMainGUIPacketHeader_Maximize){
		Parent->showMaximized();
	}
	else
	if(Header.Cmd==Cmd_SocketForMainGUIPacketHeader_Minimize){
		Parent->showMinimized();
	}
	delete	[]Buff;
}

MainGUIFormBase::MainGUIFormBase(LayersBase	*_LayersBasePoint,QWidget *parent)
	:GUIFormBase(_LayersBasePoint,parent)
{	
	FormPosition	=GUIInstancePack::_Center;
	CloseCompletely=true;
	TopForm=true;
	SetKeyGrab(true);
	//grabKeyboard();
	Execution=NULL;
}

void MainGUIFormBase::closeEvent ( QCloseEvent * event )
{
	if(GetLayersBase()->GetBootingLevel()!=0){
		if(GUIInstancePackPoint!=NULL){
			GUIInitializerPoint->GUIInstanceRoot.RemoveList(GUIInstancePackPoint);
			GUIInstancePackPoint->deleteLater();
		}
		return;
	}
			
	if(CloseCompletely==false){
		event->ignore();
		emit	QuitFromMenu();
	}
	if(GetLayersBase()->GetInsideLearningEditor()==false){
		OutputPosition();
	}
	else{
		GUIInitializerPoint->GUIInstanceRoot.RemoveList(GUIInstancePackPoint);
		GUIInstancePackPoint->deleteLater();
	}
	for(GUIFormPointer *f=ShouldCloseWindow.GetFirst();f!=NULL;f=f->GetNext()){
		if(f->GetGUIFormBase()!=NULL){
			f->GetGUIFormBase()->close();
		}
		f->SetGUIFormBase(NULL);
	}

	GetLayersBase()->SetOnTerminating(true);
	BroadcastTerminated();
	emit	SignalCloseEvent();
}

void	MainGUIFormBase::OutputPosition(void)
{
	BroadcastLeavePage();

	int	PosX;
	int	PosY;
	QString	FileName=GetPositionFileName();
	QFile	F(FileName);
	if(F.open(QIODevice::WriteOnly)==true){
		QWidget	*Win=this;
		while(Win->parentWidget()!=NULL){
			Win=Win->parentWidget();
		}

		int32	Ver=0x7FFF0001;
		if(::Save(&F,Ver)==false){
			return;
		}
		QList<QScreen *> Scr=QGuiApplication::screens();
		QScreen *S=Scr[0];
		int32	ScreenWidth	=S->size().width();
		int32	ScreenHeight=S->size().height();
		if(::Save(&F,ScreenWidth)==false){
			return;
		}
		if(::Save(&F,ScreenHeight)==false){
			return;
		}

		PosX=Win->frameGeometry().left();
		PosY=Win->frameGeometry().top();
		if(::Save(&F,PosX)==false){
			return;
		}
		if(::Save(&F,PosY)==false){
			return;
		}
		int	W=Win->geometry().width();
		int	H=Win->geometry().height();
		if(::Save(&F,W)==false){
			return;
		}
		if(::Save(&F,H)==false){
			return;
		}
	}
}

void	MainGUIFormBase::StartIdentificationServer(const QString &IdentificationName)
{
	connect(&IdentificationServer,SIGNAL(newConnection()),this,SLOT(SlotNewConnection()));
	IdentificationServer.listen(IdentificationName);
}
void	MainGUIFormBase::SlotNewConnection ()
{
	QLocalSocket *s=IdentificationServer.nextPendingConnection ();
	SocketForMainGUI	*sk=new SocketForMainGUI(s,this);
	IdentificationSocket.AppendList(sk);
}

QString	MainGUIFormBase::GetPositionFileName(void)
{
	return GetLayersBase()->GetUserPath()+QString("/MainPosition.dat");
}

void	MainGUIFormBase::ReflectAlignment(void)
{
	bool	SuccessLoadedPos=false;
	QWidget	*Win=this;
	while(Win->parentWidget()!=NULL){
		Win=Win->parentWidget();
	}
	int	PosX,PosY;
	QString	FileName=GetPositionFileName();
	QFile	F(FileName);

	if(F.open(QIODevice::ReadOnly)==true){
		int32	Ver=0x7FFF0001;
		if(::Load(&F,Ver)==false){
			return;
		}
		if((Ver&0xFFFF0000)==0x7FFF0000){
			int32	ScreenWidth;
			int32	ScreenHeight;
			if(::Load(&F,ScreenWidth)==false){
				return;
			}
			if(::Load(&F,ScreenHeight)==false){
				return;
			}
			QList<QScreen *> Scr=QGuiApplication::screens();
			QScreen *S=Scr[0];
			if(ScreenWidth==S->size().width()
			&& ScreenHeight==S->size().height()){

				if(::Load(&F,PosX)==false){
					return;
				}
				if(::Load(&F,PosY)==false){
					return;
				}
				int	W,H;
				if(::Load(&F,W)==false){
					return;
				}
				if(::Load(&F,H)==false){
					return;
				}		//move(PosX,PosY);

				//QDesktopWidget	*s=QApplication::desktop ();
				//QRect R=s->availableGeometry ();
				QScreen	*g=QGuiApplication::screens()[0];

				QStyleOptionTitleBar options;
				options.initFrom(this);
				int tbh = style()->pixelMetric( QStyle::PM_TitleBarHeight, &options, this )+6;
   
				int	MaxW=g->geometry().width();
				int	MaxH=g->geometry().height();
				if(32<=W && W<MaxW && 32<H && H<MaxH
				&& 0<(PosX+W) && PosX<MaxW && 0<(PosY+H) && PosY<MaxH){
					QCoreApplication::processEvents();
					Win->setGeometry(PosX+1,PosY+tbh,W,H);
					SuccessLoadedPos=true;
					//QMessageBox::information(NULL,/**/"Position"
					//	,QString::number(PosX)
					//	+QString(/**/",")
					//	+QString::number(PosY)
					//	+QString(/**/" - ")
					//	+QString::number(W)
					//	+QString(/**/",")
					//	+QString::number(H));
				}
			}
		}
		FormPosition=GUIInstancePack::_None;
	}

	//QMessageBox::critical(NULL,/**/"Test", /**/"BootingH1");


	if(SuccessLoadedPos==false){
		QList<QScreen *> Scr=QGuiApplication::screens();

		if(Scr.count()>0){
			QScreen *S=Scr[0];
			int32	ScreenWidth	=S->size().width();
			int32	ScreenHeight=S->size().height();
						
			QCoreApplication::processEvents();
			//QMessageBox::critical(NULL,/**/"Test"
			//					, /**/"BootingH6");

			if(ScreenWidth!=0 && ScreenHeight!=0){
				//Error occurs
				//Win->setGeometry(ScreenWidth/4,ScreenHeight/4,ScreenWidth/2,ScreenHeight/2);
				//QMessageBox::critical(NULL,/**/"Test", /**/"BootingH7");
			}
		}
	}

}
	
void	MainGUIFormBase::moveEvent ( QMoveEvent * event )
{
	GUIFormBase::moveEvent (event );
	int	PosX=geometry().x();
	int	PosY=geometry().y();
	emit	SignalMoveWindow(PosX ,PosY);
}

void	MainGUIFormBase::resizeEvent ( QResizeEvent * event )
{
	SetClientX2(0);
	SetClientY2(0);
	GUIFormBase::resizeEvent ( event );
}


void	MainGUIFormBase::SetSingleExecution(const QString &IdentifiedName)
{
	if(Execution!=NULL)
		return;
	Execution=new CheckSingleExecution(IdentifiedName,this);
	connect(Execution,SIGNAL(SignalTerminateFromOther()),this,SLOT(SlotTerminateFromOther()));
}
bool	MainGUIFormBase::CheckDoubleBoot(void)
{
	if(Execution!=NULL){
		return Execution->CheckDoubleBoot();
	}
	return false;
}
bool	MainGUIFormBase::RequirePrebootedSoftwareToTerminate(void)
{
	if(Execution!=NULL){
		return Execution->RequireTerminate();
	}
	return false;
}

void	MainGUIFormBase::SlotTerminateFromOther()
{
	emit QuitUnconditionally();
}



//=========================================================================================

CheckSingleExecution::CheckSingleExecution(const QString &_IdentifiedName,QObject *parent)
	:Server(parent),Client(parent)
{
	IdentifiedName	=_IdentifiedName;
	ClientInServer=NULL;
}
CheckSingleExecution::~CheckSingleExecution(void)
{
}

bool	CheckSingleExecution::CheckDoubleBoot(void)
{
	Client.connectToServer (IdentifiedName);
	if(Client.waitForConnected(1000)==false){
		connect(&Server,SIGNAL(newConnection()),this ,SLOT(SlotNewConnection()));
		Server.listen(IdentifiedName);
		return false;
	}
	return true;
}

void CheckSingleExecution::SlotNewConnection ()
{
	ClientInServer=Server.nextPendingConnection ();
	if(ClientInServer!=NULL){
		connect(ClientInServer,SIGNAL(readyRead()),this ,SLOT(SlotReadyReadInServer()));
	}
}
bool	CheckSingleExecution::RequireTerminate(void)
{
	if(Client.state()== QLocalSocket::ConnectedState){
		Client.write("Close");
		Client.flush();
	}
	return true;
}

void	CheckSingleExecution::SlotReadyReadInServer()
{
	if(ClientInServer!=NULL && ClientInServer->bytesAvailable()>0){
		char	Buff[100];
		ClientInServer->read(Buff,sizeof(Buff));
		if(QString(Buff)=="Close"){
			emit	SignalTerminateFromOther();
		}
	}
}