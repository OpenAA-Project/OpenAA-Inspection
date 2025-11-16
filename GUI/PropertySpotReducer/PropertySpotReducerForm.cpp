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
