#include "ButtonAddSubForm.h"
#include "ButtonAddSubPage.h"
#include "ui_ButtonAddSubForm.h"
#include "XDataAlgorithm.h"
#include "XAlgorithmBase.h"
#include "XFilterInstance.h"

ButtonAddSubForm::ButtonAddSubForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent)
    ,ui(new Ui::ButtonAddSubForm)
{
    ui->setupUi(this);

	CopyAllAlgorithm=true;
	CopyAllFilters	=true;
}

ButtonAddSubForm::~ButtonAddSubForm()
{
    delete ui;
}

void ButtonAddSubForm::on_toolButtonAdd_clicked()
{
	if(GetParamComm()->IsMastered()==true && GetParamComm()->GetConnectedPCNumb()==0){
		GetLayersBase()->Reallocate(GetPhaseNumb(),GetPageNumb()+1,GetLayersBase()->GetMaxLayerNumb());
		int	SrcPage=GetPageNumb()-2;
		int	DstPage=GetPageNumb()-1;
		GetLayersBase()->CopyPageData(DstPage ,SrcPage	
									,CopyAllAlgorithm ,CopyAllFilters);

		GetParamGlobal()->SetCameraNo(DstPage,0);
		GetParamGlobal()->SetMaxScanStrategy(GetPageNumb());
		for(int layer=0;layer<GetLayersBase()->GetMaxLayerNumb();layer++){
			GetParamGlobal()->SetStrategyCode(DstPage ,layer ,GetPageNumb()-1);
		}
	}
}


void ButtonAddSubForm::on_toolButtonSub_clicked()
{
	if(GetParamComm()->IsMastered()==true && GetParamComm()->GetConnectedPCNumb()==0
	&& GetPageNumb()>=2){
		GetLayersBase()->Reallocate(GetPhaseNumb(),GetPageNumb()-1,GetLayersBase()->GetMaxLayerNumb());
	}
}

void	ButtonAddSubForm::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdAddPage	*CmdAddPageVar=dynamic_cast<CmdAddPage *>(packet);
	if(CmdAddPageVar!=NULL){
		on_toolButtonAdd_clicked();
		return;
	}
	CmdSubPage	*CmdSubPageVar=dynamic_cast<CmdSubPage *>(packet);
	if(CmdSubPageVar!=NULL){
		on_toolButtonSub_clicked();
		return;
	}
	CmdInsertPage	*CmdInsertPageVar=dynamic_cast<CmdInsertPage *>(packet);
	if(CmdInsertPageVar!=NULL){
		if(GetParamComm()->IsMastered()==true && GetParamComm()->GetConnectedPCNumb()==0){
			GetLayersBase()->InsertPage(CmdInsertPageVar->IndexPage);
			int	SrcPage=CmdInsertPageVar->IndexPage;
			int	DstPage=CmdInsertPageVar->IndexPage+1;
			if(DstPage<GetPageNumb()){
				GetLayersBase()->CopyPageData(DstPage ,SrcPage	
											,CopyAllAlgorithm ,CopyAllFilters);
			}
			GetParamGlobal()->SetCameraNo(DstPage,0);
			GetParamGlobal()->SetMaxScanStrategy(GetPageNumb());
			for(int layer=0;layer<GetLayersBase()->GetMaxLayerNumb();layer++){
				GetParamGlobal()->SetStrategyCode(DstPage ,layer ,GetPageNumb()-1);
			}
		}
		return;
	}
	CmdRemovePage	*CmdRemovePageVar=dynamic_cast<CmdRemovePage *>(packet);
	if(CmdRemovePageVar!=NULL){
		if(GetParamComm()->IsMastered()==true && GetParamComm()->GetConnectedPCNumb()==0){
			GetLayersBase()->RemovePage(CmdRemovePageVar->IndexPage);
			GetParamGlobal()->SetMaxScanStrategy(GetPageNumb());
		}
		return;
	}
}

