/*
 * Copyright (C) 2012
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

#ifndef LOGINTEGRATOR_PACK_H
#define LOGINTEGRATOR_PACK_H
#include "NList.h"
#include <QString>

class clsLogResult;
class clsLogResultContainer;
class clsLogItem;
class clsLogItemContainer;

class clsLogResult : public NPList<clsLogResult>
{
public :
	QString NgNo;
	QString NgResult;

	clsLogResult &operator=(clsLogResult &src);
};

class clsLogResultContainer : public NPListPack<clsLogResult>
{
public :
	void sort();
	int  cntNg();
};

class clsLogItem : public NPList<clsLogItem>
{
public:
	QString Hinsyu;
	QString LotNo;
	QString BaseNo;
	int UpperOrLower;
	QString SaveDate;
	QString SaveTime;
	QString HDName;
	QString NgNo;
	QString NgResult;
	//int nCnt;	//�����������AIntegrateProperty�֐��ŃC���N�������g������
	clsLogItem *AnotherItem;

	clsLogResultContainer NgLst;

	clsLogItem(){AnotherItem = NULL; InitializeProperties();}
	~clsLogItem(){}

	void InitializeProperties(void);
	bool SetProperty(QString buf);
	bool SetPropertiesFromFileName(QString filename);
	void calcNgCnt();
	bool clsLogItem::SetAnotherItem(clsLogItem *src);
	bool IntegrateProperty(clsLogItem *src);
	int cntNg() { return NgLst.cntNg(); }
	bool chkOutSame(clsLogItem &src);
	bool operator==(clsLogItem &src);
	clsLogItem &operator=(clsLogItem &src);
};

class clsLogItemContainer : public NPListPack<clsLogItem>
{
public :
	void sort();
};
#endif // LOGINTEGRATOR_PACK_H