#pragma once

#include "XServiceForLayers.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XParamCustomized.h"
#include "XIntegrationPacketComm.h"
#include "XAlgorithmLibrary.h"
//#include "XDotColorMatchingLibrary.h"
//#include "XDotColorMatching.h"
#include "NListComp.h"
#include "XIntClass.h"
#include "XFlexArea.h"
#include <QByteArray>

//===============================================================================

class	IntegrationReqDotColorMatchingTryResult: public IntegrationCmdPacketBase
{
public:
	ListPhasePageLayerItem	ItemIndex;
	QByteArray				ThresholdData;

	IntegrationReqDotColorMatchingTryResult(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd,QString &EmitterRoot,QString &EmitterName);
};

class	IntegrationAckDotColorMatchingTryResult: public IntegrationCmdPacketBase
{
public:
	struct ResultInfo
	{
		WORD	CenterBrightR;
		WORD	CenterBrightG;
		WORD	CenterBrightB;
		WORD	CenterTargetBrightR;
		WORD	CenterTargetBrightG;
		WORD	CenterTargetBrightB;

		int		CurrentRotationPatternNo;
		int		ResultDx;
		int		ResultDy;
		int		ResultSelfSeachDx;
		int		ResultSelfSeachDy;
		int		ResultCode;			//1:OK	2:NGSize	3:MultiCount	4:

		DWORD	NGResultSize;
		DWORD	NGResultLength;
		DWORD	NGResultGroundSize;
		DWORD	NGResultGroundLength;
		DWORD	NGResultRedSize;
		DWORD	NGResultMultiCount;
	}ResultInfoData;
	FlexArea	NGShape;

	IntegrationAckDotColorMatchingTryResult(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo,int cmd,QString &EmitterRoot,QString &EmitterName){}
};
