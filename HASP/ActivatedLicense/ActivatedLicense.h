#pragma once

#include "activatedlicense_global.h"
#include "XHaspLib.h"
#include "XServiceForLayers.h"
#include "XGUIPacketForDLL.h"


class   ActivatedLicense : public HaspHandle,public ServiceForLayers
{
public:
    ActivatedLicense(LayersBase *base);

	virtual	bool3	PermitByDate(const QString &DLLRoot ,const QString &DLLName
														,qint64 SpanSecFromInstall
														,const QString &_CurrentVersion
														,QString &FailMessage
														,int &ErrorCode)	override;
	virtual	bool3	PermitByProgram(const QString &ProgramCode
														,const QString &_CurrentVersion
														,QString &FailMessage
														,int &ErrorCode)	override;
	virtual	bool3	PermitByID(const QString &DLLRoot ,const QString &DLLName, int id
														,const QString &_CurrentVersion
														,QString &FailMessage
														,int &ErrorCode)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

private:

};
