#pragma once

#include "XParamBase.h"
#include "XIntClass.h"
#include "NListComp.h"
#include "XTypeDef.h"

class RegulusWorld;

class RWDeviceParamList : public NPListSaveLoad<RWDeviceParamList>
{
public:
	int			DeviceID;
	QString		DLLFileName;
	QString		Parameter;

	RWDeviceParamList(void);
	RWDeviceParamList(const RWDeviceParamList &src);

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;

	RWDeviceParamList	&operator=(const RWDeviceParamList &src);
};

class RWDeviceParamListContainer: public NPListPackSaveLoad<RWDeviceParamList>
{
public:
	RWDeviceParamListContainer(void){}
	RWDeviceParamListContainer(const RWDeviceParamListContainer &src);

	virtual	RWDeviceParamList	*Create(void)	override;
	RWDeviceParamListContainer	&operator=(const RWDeviceParamListContainer &src);
};

//============================================================

class	ParamRegulusWorld : public ParamBase
{
	RegulusWorld	*Parent;
public:
	int32	PageNumb;
	QString	DataFilePath;
	QString	ErrorLogFile;
	RWDeviceParamListContainer	RWDeviceParams;

	ParamRegulusWorld(RegulusWorld *base);

	virtual	QString	GetDataText(void)			override{	return("GlobalRegulusWorld Data");	};
	virtual	QString	GetDefaultFileName(void)	override{	return("GlobalRegulusWorld.dat");	}

	virtual	bool	SaveParam(QIODevice *f ,int EnableCondition=-1)	override;
	virtual	bool	LoadParam(QIODevice *f ,int EnableCondition=-1)	override;
	virtual	bool	LoadParam(QIODevice *f ,int StartPoint ,int EndPoint ,int EnableCondition=-1)	override;

};
