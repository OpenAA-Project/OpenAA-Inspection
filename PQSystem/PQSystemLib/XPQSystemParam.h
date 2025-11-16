#pragma once
#include "XParamBase.h"
#include "XIntClass.h"
#include "XServiceForLayers.h"
#include "NListComp.h"


class	ParamPQSystem : public ParamBase ,public ServiceForLayers
{
public:
	QString	TitleMasterNumber	;
	QString	TitleMasterName		;
	QString	TitleRemark			;
	QString	TitleLotID			;
	QString	TitleLotNumber		;
	QString	TitleSubCode		;

	ParamPQSystem(LayersBase *base);
	~ParamPQSystem(void);
	virtual	QString	GetDataText(void)		override{	return("PQSystem Data");	};
	virtual	QString	GetDefaultFileName(void)override{	return("PQSystem.dat");		}

};