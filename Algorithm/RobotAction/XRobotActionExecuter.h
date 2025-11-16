#pragma once

#include <QThread>
#include "XServiceForLayers.h"
#include "XRobotAction.h"


class RobotActionExecuter : public QThread,public ServiceForLayers
{
	RobotActionBase		*ABase;
public:
	bool	ModeInspection	;
	bool	ModeTeaching	;

	RobotActionExecuter(LayersBase *base,RobotActionBase *aBase);

private:
	virtual	void	run()	override;
};

