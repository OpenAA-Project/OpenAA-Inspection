#if	!defined(XPQSystemParam_h)
#define	XPQSystemParam_h

#include <QString>
#include "XTypeDef.h"
#include "XParamBase.h"

class	ParamBase;

class	PQSystemParam : public ParamBase
{
public:
	QString	LocalDatabase_HostName;
	int32	LocalDatabase_Port;
	QString	LocalDatabase_FileName;

	QString	ImageFilePath;

	QString	ResultDLLFileName;


	PQSystemParam(void);

	virtual	QString	GetDataText(void){	return("PQSystem Data");	};
	virtual	QString	GetDefaultFileName(void){	return DefaultFileName.isEmpty() ? "PQSystem.dat" : DefaultFileName;	}
};

#endif