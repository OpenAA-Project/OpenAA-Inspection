#include "PropertyRobotActionForm.h"
#include "ui_PropertyRobotActionForm.h"
#include "XGeneralFunc.h"
#include "XPropertyRobotActionPacket.h"
#include "EditMarkCaptureDialog.h"
#include "EditMarkMoveDialog.h"

extern	const	char	*sRoot;
extern	const	char	*sName;


PropertyRobotActionForm::PropertyRobotActionForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::PropertyRobotActionForm)
{
    ui->setupUi(this);
}

PropertyRobotActionForm::~PropertyRobotActionForm()
{
    delete ui;
}
RobotActionBase	*PropertyRobotActionForm::GetRobotActionBase(void)
{
	return (RobotActionBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"RobotAction");
}

GUIFormBase     *PropertyRobotActionForm::GetPanel(void)
{
    return GetLayersBase()->FindByName(/**/"Robot",/**/"ActionEditPanel",/**/"");
}

void	PropertyRobotActionForm::BuildForShow(void)
{
    ui->listWidgetRobotList->clear();
    RobotActionBase	*ABase=GetRobotActionBase();
    for(RobotAccessList *L=ABase->RobotPack.GetFirst();L!=NULL;L=L->GetNext()){
        ui->listWidgetRobotList->addItem(L->GetUniqueCode());
    }

    ShowList();
}

void    PropertyRobotActionForm::ShowList(void)
{
    RobotActionBase	*ABase=GetRobotActionBase();
    int N=ABase->RContainer.GetCount();
    ui->tableWidgetMarkList->setRowCount(N);
    int Row=0;
    for(ActionMarkBase *a=ABase->RContainer.GetFirst();a!=NULL;a=a->GetNext(),Row++){
        ::SetDataToTable(ui->tableWidgetMarkList, 0, Row, a->GetTypeName());
        ::SetDataToTable(ui->tableWidgetMarkList, 1, Row, a->GetAlgoLibName());
        ::SetDataToTable(ui->tableWidgetMarkList, 2, Row, a->GetParamStr());
    }
}

void	PropertyRobotActionForm::TransmitDirectly(GUIDirectMessage *packet)
{
    CmdRobotActionClicked   *CmdRobotActionClickedVar=dynamic_cast<CmdRobotActionClicked *>(packet);
    if(CmdRobotActionClickedVar!=NULL){
        if(ui->toolButtonMove->isChecked()==true){
            EditMarkMoveDialog  D(GetLayersBase());
            if(D.exec()==true){
                CmdRobotActionAddMove   RCmd(GetLayersBase());
                RCmd.UniversalDx=CmdRobotActionClickedVar->UniversalDx;
                RCmd.UniversalDy=CmdRobotActionClickedVar->UniversalDy;
                RCmd.Speed      =D.Speed;
                RobotActionBase	*f=GetRobotActionBase();
                f->TransmitDirectly(&RCmd);
                GUIFormBase     *panel=GetPanel();
                if(panel!=NULL){
                    panel->RepaintAll();
                }
            }
        }
        else
        if(ui->toolButtonCapture->isChecked()==true){
            EditMarkCaptureDialog   D(GetLayersBase());
            if(D.exec()==true){
                CmdRobotActionAddCapture   RCmd(GetLayersBase());
                RCmd.UniversalDx=CmdRobotActionClickedVar->UniversalDx;
                RCmd.UniversalDy=CmdRobotActionClickedVar->UniversalDy;
                RCmd.AlgorithmType	    =D.AlgorithmType	;
                RCmd.AlgorithmPhase	    =D.AlgorithmPhase	;
                RCmd.AlgorithmPage	    =D.AlgorithmPage	;
                RCmd.AlgorithmLayer	    =D.AlgorithmLayer	;
                RCmd.AlgorithmItemID	=D.AlgorithmItemID  ;
                RCmd.StopMilisec        =D.StopMilisec;
                RobotActionBase	*f=GetRobotActionBase();
                f->TransmitDirectly(&RCmd);
                GUIFormBase     *panel=GetPanel();
                if(panel!=NULL){
                    panel->RepaintAll();
                }
            }
        }
    }
}

void PropertyRobotActionForm::on_tableWidgetMarkList_clicked(const QModelIndex &index)
{

}

void PropertyRobotActionForm::on_tableWidgetMarkList_doubleClicked(const QModelIndex &index)
{
    int Row=ui->tableWidgetMarkList->currentRow();
    if(Row<0)
        return;
    RobotActionBase	*ABase=GetRobotActionBase();
    ActionMarkBase *a=ABase->RContainer.GetItem(Row);
    if(a!=NULL){
        int ClassID=a->GetClassID();
        if(ClassID==1){
            EditMarkMoveDialog  D(GetLayersBase());
            D.Initial(a);
            if(D.exec()==true){
                CmdRobotActionModifyMove   RCmd(GetLayersBase());
                RCmd.Speed      =D.Speed;
                RCmd.Number     =Row;
                ABase->TransmitDirectly(&RCmd);
                GUIFormBase     *panel=GetPanel();
                if(panel!=NULL){
                    panel->RepaintAll();
                }
                ShowList();
            }
        }
        else if(ClassID==2){
            EditMarkCaptureDialog   D(GetLayersBase());
            D.Initial(a);
            if(D.exec()==true){
                CmdRobotActionModifyCapture   RCmd(GetLayersBase());
                RCmd.AlgorithmType	    =D.AlgorithmType	;
                RCmd.AlgorithmPhase	    =D.AlgorithmPhase	;
                RCmd.AlgorithmPage	    =D.AlgorithmPage	;
                RCmd.AlgorithmLayer	    =D.AlgorithmLayer	;
                RCmd.AlgorithmItemID	=D.AlgorithmItemID  ;
                RCmd.StopMilisec        =D.StopMilisec;
                RCmd.Number     =Row;
                ABase->TransmitDirectly(&RCmd);
                GUIFormBase     *panel=GetPanel();
                if(panel!=NULL){
                    panel->RepaintAll();
                }
                ShowList();
            }
        }
    }
}


void PropertyRobotActionForm::on_pushButtonClearAll_clicked()
{
    RobotActionBase	*ABase=GetRobotActionBase();
    CmdRobotActionClear RCmd(GetLayersBase());
    ABase->TransmitDirectly(&RCmd);
    ShowList();
}


void PropertyRobotActionForm::on_toolButtonTeachingMode_clicked()
{
    RobotActionBase	*ABase=GetRobotActionBase();
    CmdRobotTeachingMode RCmd(GetLayersBase());
    RCmd.TeachingMode=ui->toolButtonTeachingMode->isChecked();
    ABase->TransmitDirectly(&RCmd);
}

