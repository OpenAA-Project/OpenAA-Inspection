/*
 * Copyright (C) 2025
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

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