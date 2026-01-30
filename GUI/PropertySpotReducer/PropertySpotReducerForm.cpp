/*
 * Copyright (C) 2023
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

#include "CreateSpotReducerFormResource.h"
#include "PropertySpotReducerForm.h"
#include "XDataInLayer.h"
#include "XSpotReducer.h"
#include "XPropertySpotReducerPacket.h"
#include "CreateSpotReducerForm.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

PropertySpotReducerForm::PropertySpotReducerForm(LayersBase *Base ,QWidget *parent)
	: GUIFormBase(Base,parent)
{
	ui.setupUi(this);
}

PropertySpotReducerForm::~PropertySpotReducerForm()
{

}

void	PropertySpotReducerForm::BuildForShow(void)
{
}
void	PropertySpotReducerForm::TransmitDirectly(GUIDirectMessage *packet)
{
	AddSpotReducerArea	*AddSpotReducerAreaVar=dynamic_cast<AddSpotReducerArea *>(packet);
	if(AddSpotReducerAreaVar!=NULL){
		CreateSpotReducerForm	Q(GetLayersBase(),this);
		if(Q.exec()==(int)true){
			IntList PageList;
			GetLayersBase()->GetLocalPageFromArea(AddSpotReducerAreaVar->Area,PageList);
			for(IntClass *P=PageList.GetFirst();P!=NULL;P=P->GetNext()){
				DataInPage	*pdata=GetLayersBase()->GetPageData(P->GetValue());
				FlexArea	A=AddSpotReducerAreaVar->Area;
				pdata->ClipMoveAreaFromGlobal(A);
				if(A.GetPatternByte()>0){
					GUICmdAddSpotReducerArea	Cmd(GetLayersBase(),QString(sRoot),QString(sName),pdata->GetPage());
					Cmd.Area=A;
					Cmd.LayerList=AddSpotReducerAreaVar->LayerList;
					Cmd.SpotBrightness	=Q.SpotBrightness;
					Cmd.ReductionLevel	=Q.ReductionLevel;
					Cmd.SpotArea		=Q.SpotArea;
					Cmd.SpotCount		=Q.SpotCount;
					Cmd.SendOnly(pdata->GetPage(),0);
				}
			}
		}
	}
}
void	PropertySpotReducerForm::ShowInEdit(void)
{
}

SpotReducerBase	*PropertySpotReducerForm::GetSpotReducerBase(void)
{
	return (SpotReducerBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"SpotReducer");
}