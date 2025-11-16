#ifndef INTEGRATIONLIB_H
#define INTEGRATIONLIB_H

#include "XParamIntegrationMaster.h"


class	IntegratorRelation
{
	ParamIntegrationMaster	*ParamIntegrationMasterData;

public:
	IntegratorRelation(void)	{	ParamIntegrationMasterData=NULL;	}

	void	SetParamPointer(ParamIntegrationMaster *p);
	ParamIntegrationMaster	*GetParamIntegrationMaster(void){	return ParamIntegrationMasterData;	}
};



#endif // INTEGRATIONLIB_H
