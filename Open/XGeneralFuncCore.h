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

#pragma once

#include<QIODevice>
#include<QByteArray>
#include<QThread>
#include<QDir>

#include"XTypeDef.h"
#include"XYCross.h"
#include<QVariant>

class	QIODevice;
class	QString;
class	IntList;
class	QDateTime;
class	XDateTime;
class	QChar;


#define	mhypot(x,y)		sqrt((double)((x)*(x)+(y)*(y)))

bool	FuncCall	Save(QIODevice* f, int8 d);
bool	FuncCall	Save(QIODevice* f, int32 d);
bool	FuncCall	Save(QIODevice* f, uint32 d);
bool	FuncCall	Save(QIODevice* f, int64 d);
bool	FuncCall	Save(QIODevice* f, short d);
bool	FuncCall	Save(QIODevice* f, WORD d);
bool	FuncCall	Save(QIODevice* f, DWORD d);
bool	FuncCall	Save(QIODevice* f, float d);
bool	FuncCall	Save(QIODevice* f, double d);
bool	FuncCall	Save(QIODevice* f, BYTE d);
bool	FuncCall	Save(QIODevice* f, const QChar& d);
bool	FuncCall	Save(QIODevice* f, char d);
bool	FuncCall	Save(QIODevice* f, bool d);
bool	FuncCall	Save(QIODevice* f, bool3 d);
bool	FuncCall	Save(QIODevice* f, const char* d, int64 len);
//bool	FuncCall	Save(QIODevice* f, const char* d);
bool	FuncCall	Save(QIODevice* f, const QString& d);
bool	FuncCall	Save(QIODevice* f, const QStringList& d);
bool	FuncCall	Save(QIODevice* f, const XYData& d);
bool	FuncCall	Save(QIODevice* f, const QDateTime& d);
bool	FuncCall	Save(QIODevice* f, const QDate& d);
bool	FuncCall	Save(QIODevice* f, const QTime& d);
bool	FuncCall	Save(QIODevice* f, const XDateTime& d);
//bool	FuncCall	Save(QIODevice *f,QRgb &d);
bool	FuncCall	Save(QIODevice* f, const QByteArray& d);
bool	FuncCall	Save(QIODevice* f, const QByteArrayList& d);
bool	FuncCall	Save(QIODevice* f, BYTE** Point, int XLen, int YLen);
bool	FuncCall	SaveText(QIODevice* f, char* s);
bool	FuncCall	Save(QIODevice* f, const QPoint& d);
bool	FuncCall	Save(QIODevice* f, const QPointF& d);
bool	FuncCall	Save(QIODevice* f, const QSize& d);
	
bool	FuncCall	Load(QIODevice* f, int8& d);
bool	FuncCall	Load(QIODevice* f, int32& d);
bool	FuncCall	Load(QIODevice* f, long& d);
bool	FuncCall	Load(QIODevice* f, uint32& d);
bool	FuncCall	Load(QIODevice* f, int64& d);
bool	FuncCall	Load(QIODevice* f, short& d);
bool	FuncCall	Load(QIODevice* f, WORD& d);
bool	FuncCall	Load(QIODevice* f, float& d);
bool	FuncCall	Load(QIODevice* f, double& d);
bool	FuncCall	Load(QIODevice* f, QChar& d);
bool	FuncCall	Load(QIODevice* f, DWORD& d);
bool	FuncCall	Load(QIODevice* f, BYTE& d);
bool	FuncCall	Load(QIODevice* f, char& d);
bool	FuncCall	Load(QIODevice* f, bool& d);
bool	FuncCall	Load(QIODevice* f, bool3& d);
bool	FuncCall	Load(QIODevice* f, char* d, int64& len, int64 maxbuffsize);	//Save(QIODevice *f,char *d,int64 Len)�ɑ΂���Load
bool	FuncCall	Load(QIODevice* f, char* d, int32& len, int32 maxbuffsize);		//Save(QIODevice *file,char *d)�ɑ΂���Load
bool	FuncCall	Load(QIODevice* f, QString& d);
char* FuncCall	LoadStringInQString(QIODevice* file);
char* FuncCall	LoadString(QIODevice* file);			//Load data which is saved by "Save(QIODevice *f,char *d);"
bool	FuncCall	Load(QIODevice* f, QStringList& d);
bool	FuncCall	Load(QIODevice* f, XYData& d);
bool	FuncCall	Load(QIODevice* f, QDateTime& d);
bool	FuncCall	Load(QIODevice* f, QDate& d);
bool	FuncCall	Load(QIODevice* f, QTime& d);
bool	FuncCall	Load(QIODevice* f, XDateTime& d);
//bool	FuncCall	Load(QIODevice *f,QRgb &d);
bool	FuncCall	Load(QIODevice* f, QByteArray& d);
bool	FuncCall	Load(QIODevice* f, QByteArrayList& d);
bool	FuncCall	Load(QIODevice* f, BYTE** Point, int XLen, int YLen);
bool	FuncCall	Load(QIODevice* f, QPoint& d);
bool	FuncCall	Load(QIODevice* f, QPointF& d);
bool	FuncCall	Load(QIODevice* f, QSize& d);

QString FuncCall	ForceDirectories(const QString &path);
//Delphi�̊֐��Ɠ����͓��� �Ԓl�͈Ⴄ
//�����̃p�X�������I�ɍ���
//�����̉ۂɊւ��炸�쐬�ł����Ƃ����܂ł̃p�X���Ԃ�
QStringList	FuncCall	FindFiles(const QString& dir, const QString& FileFilter);

QString		FuncCall	GetDynamicFileExt(void);
inline	QString		FuncCall	GetSeparator(void)		{	return QString("/");	}	//QDir::separator();	}
QObject*	FuncCall	SearchNested(QObject* Root, const QString& objectName);
void		FuncCall	QSort(void* parray, int lenArray, int datasize, int (*func)(const void* a, const void* b), bool3 ThreadMode = none3);
QString		FuncCall	TransformPathName(const QString& Str);
void		FuncCall	QSort64(void* parray, int64 lenArray, int datasize, int (*func)(const void* a, const void* b), bool3 ThreadMode = none3);

bool	FuncCall	RemoveAllInFolder(const QString &folder ,bool DeleteSubFolder=true);