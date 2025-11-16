#pragma once

#include "trialterm_global.h"
#include "XHaspLib.h"
#include "XServiceForLayers.h"
#include "XGUIPacketForDLL.h"

class TrialTerm : public HaspHandle ,public ServiceForLayers
{
	QString CurrentVersion;
public:
    TrialTerm(LayersBase *base);
	~TrialTerm(void);

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
};

class	CmdReqTrialTermInfo: public GUIDirectMessage
{
public:
	int		PassedDays;

	CmdReqTrialTermInfo(LayersBase *base):GUIDirectMessage(base){}
};