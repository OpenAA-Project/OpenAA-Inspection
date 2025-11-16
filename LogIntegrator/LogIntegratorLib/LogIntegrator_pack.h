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
	//int nCnt;	//統合した数、IntegrateProperty関数でインクリメントされる
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
