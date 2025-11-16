#include "XRobotActionExecuter.h"
#include "XDataInLayer.h"


RobotActionExecuter::RobotActionExecuter(LayersBase *base,RobotActionBase *aBase)
	:ServiceForLayers(base)
{
	ABase=aBase;

	ModeInspection	=false;
	ModeTeaching	=false;
}

void	RobotActionExecuter::run()
{
	while(GetLayersBase()->GetOnTerminating()==false){
		if(ModeInspection==true){
			for(ActionMarkBase *a=ABase->RContainer.GetFirst();a!=NULL;a=a->GetNext()){
				if(a->ExecuteProcessing()==false){
					break;
				}
			}
		}
		else
		if(ModeTeaching==true){
			//ABase->RobotPack.
		}
	}
}