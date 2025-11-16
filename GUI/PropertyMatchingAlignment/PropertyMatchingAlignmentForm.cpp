#include "AddManualItemFormResource.h"
#include "PropertyMatchingAlignmentForm.h"
#include "AddManualItemForm.h"
#include "XDataInLayer.h"
#include "XMatchingAlignment.h"
#include "XGeneralFunc.h"
#include "XRememberer.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

PropertyMatchingAlignmentForm::PropertyMatchingAlignmentForm(LayersBase *Base ,QWidget *parent)
	: GUIFormBase(Base,parent)
{
	ui.setupUi(this);

	ControlRememberer::LoadValue(ui.spinBoxBlockSize		,10);
	ControlRememberer::LoadValue(ui.doubleSpinBoxCoverRate	,0.3);
	ControlRememberer::LoadValue(ui.doubleSpinBoxPickUpVar	,10000);
}

PropertyMatchingAlignmentForm::~PropertyMatchingAlignmentForm()
{

}

MatchingAlignmentBase	*PropertyMatchingAlignmentForm::GetMatchingAlignmentBase(void)
{
	return (MatchingAlignmentBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"MatchingAlignment");
}

void	PropertyMatchingAlignmentForm::BuildForShow(void)
{
	ShowAreaGrid();
}
void	PropertyMatchingAlignmentForm::TransmitDirectly(GUIDirectMessage *packet)
{
	AddMatchingAlignmentAreaPacket	*MakeAP=dynamic_cast<AddMatchingAlignmentAreaPacket *>(packet);
	if(MakeAP!=NULL){
		AddManualItemForm	Q(GetLayersBase(),this);
		if(Q.exec()==(int)true){
			IntList PageList;
			GetLayersBase()->GetLocalPageFromArea(MakeAP->Area,PageList);
			for(IntClass *P=PageList.GetFirst();P!=NULL;P=P->GetNext()){
				DataInPage	*pdata=GetLayersBase()->GetPageData(P->GetValue());
				FlexArea	A=MakeAP->Area;
				pdata->ClipMoveAreaFromGlobal(A);
				if(A.GetPatternByte()>0){
					GUICmdAddMatchingAlignmentArea	Cmd(GetLayersBase(),QString(sRoot),QString(sName),pdata->GetPage());
					Cmd.Area=A;
					Cmd.LayerList=MakeAP->LayerList;
					Cmd.MatchingRate=Q.MatchingRate;
					Cmd.SearchDot	=Q.SearchDot;
					Cmd.SendOnly(pdata->GetPage(),0);
				}
			}
		}
		ShowAreaGrid();
		return;
	}
	DisplayModeOfMatchingAlignment	*DisplayModeOfMatchingAlignmentVar=dynamic_cast<DisplayModeOfMatchingAlignment *>(packet);
	if(DisplayModeOfMatchingAlignmentVar!=NULL){
		if(ui.toolButtonSpecified->isChecked()==true)
			DisplayModeOfMatchingAlignmentVar->ModeSpecified=true;
		else
			DisplayModeOfMatchingAlignmentVar->ModeSpecified=false;
		return;
	}
}

void	PropertyMatchingAlignmentForm::ShowAreaGrid(void)
{
}


void PropertyMatchingAlignmentForm::on_toolButtonSpecified_clicked()
{
	BroadcastShowInEdit();
}

void PropertyMatchingAlignmentForm::on_pushButtonCreateSpecified_clicked()
{
	ControlRememberer::SetValue(ui.doubleSpinBoxCoverRate	);
	ControlRememberer::SetValue(ui.doubleSpinBoxPickUpVar	);
	ControlRememberer::SetValue(ui.spinBoxBlockSize			);

	for(int page=0;page<GetPageNumb();page++){
		GUICmdCreateSpecified	RCmd(GetLayersBase(),sRoot,sName,page);
		RCmd.CoverRate	=ui.doubleSpinBoxCoverRate->value();
		RCmd.PickUpVar	=ui.doubleSpinBoxPickUpVar->value();
		RCmd.BlockSize	=ui.spinBoxBlockSize->value();
		RCmd.Send(NULL,page,0);
	}
}
//=====================================================================================
GUICmdAddMatchingAlignmentArea::GUICmdAddMatchingAlignmentArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdAddMatchingAlignmentArea::Load(QIODevice *f)
{
	if(Area.Load(f)==false)
		return false;
	if(LayerList.Load(f)==false)
		return false;
	if(::Load(f,MatchingRate)==false)
		return false;
	if(::Load(f,SearchDot)==false)
		return false;
	return true;
}
bool	GUICmdAddMatchingAlignmentArea::Save(QIODevice *f)
{
	if(Area.Save(f)==false)
		return false;
	if(LayerList.Save(f)==false)
		return false;
	if(::Save(f,MatchingRate)==false)
		return false;
	if(::Save(f,SearchDot)==false)
		return false;
	return true;
}

void	GUICmdAddMatchingAlignmentArea::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*L=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"MatchingAlignment");
	if(L==NULL)
		return;
	AlgorithmInPageRoot		*PData=L->GetPageData(localPage);
	if(PData==NULL)
		return;
	AddMatchingAlignmentAreaPacket	Cmd(this);
	Cmd.Area=Area;
	Cmd.LayerList=LayerList;
	Cmd.MatchingRate=MatchingRate;
	Cmd.SearchDot	=SearchDot;
	PData->TransmitDirectly(&Cmd);
	
	SendAck(localPage);
}

GUICmdCreateSpecified::GUICmdCreateSpecified(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdCreateSpecified::Load(QIODevice *f)
{
	if(::Load(f,CoverRate)==false)
		return false;
	if(::Load(f,PickUpVar)==false)
		return false;
	if(::Load(f,BlockSize)==false)
		return false;
	return true;
}
bool	GUICmdCreateSpecified::Save(QIODevice *f)
{
	if(::Save(f,CoverRate)==false)
		return false;
	if(::Save(f,PickUpVar)==false)
		return false;
	if(::Save(f,BlockSize)==false)
		return false;
	return true;
}

void	GUICmdCreateSpecified::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*L=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"MatchingAlignment");
	if(L==NULL)
		return;
	AlgorithmInPageRoot		*PData=L->GetPageData(localPage);
	if(PData==NULL)
		return;
	CreateSpecifiedPacket	Cmd(this);
	Cmd.CoverRate	=CoverRate;
	Cmd.PickUpVar	=PickUpVar;
	Cmd.BlockSize	=BlockSize;
	PData->TransmitDirectly(&Cmd);
	
	SendAck(localPage);
}

