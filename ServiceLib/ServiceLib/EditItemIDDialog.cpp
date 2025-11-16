#include "ServiceLibResource.h"
#include "EditItemIDDialog.h"
#include "ui_EditItemIDDialog.h"
#include "XDataAlgorithm.h"
#include "XDataInLayerCmdLocal.h"
#include <QMessageBox>

EditItemIDDialog::EditItemIDDialog(LayersBase *base,QWidget *parent) :
    QDialog(parent)
    ,ServiceForLayers(base)
    ,ui(new Ui::EditItemIDDialog)
{
    ui->setupUi(this);
    LangLibSolver.SetUI(this);
}

EditItemIDDialog::~EditItemIDDialog()
{
    delete ui;
}

void    EditItemIDDialog::Initial(AlgorithmBase *_ABase
                                ,int _Phase ,int _Page ,int _Layer
                                ,int _OldItemID, int _NewItemID
                                ,bool _EnableMessage)
{
    ABase       =_ABase;
    Phase       =_Phase;
    Page        =_Page;
    Layer       =_Layer;
    ui->spinBoxOldItemID->setValue(_OldItemID);
    ui->spinBoxNewItemID->setValue(_NewItemID);
    EnableMessage=_EnableMessage;
}

void EditItemIDDialog::on_pushButtonUpdate_clicked()
{
    GUICmdChangeItemID  RCmd(GetLayersBase(),/**/"ANY",/**/"ANY",Page);
    GUIAckChangeItemID  ACmd(GetLayersBase(),/**/"ANY",/**/"ANY",Page);

    ABase->GetAlgorithmRootName(RCmd.AlgoRoot,RCmd.AlgoName);
    RCmd.Phase  =Phase;
    RCmd.Layer  =Layer;
    RCmd.OldItemID  =ui->spinBoxOldItemID->value();
    RCmd.NewItemID  =ui->spinBoxNewItemID->value();
    if(RCmd.Send(Page,0,ACmd)==true){
        if(ACmd.DoneSuccessful==true){
            NewItemID=RCmd.NewItemID;
            done(true);
        }
        else{
            if(EnableMessage==true){
                if(ACmd.NoItem==true){
                    QMessageBox::warning(NULL,"更新できません"
                                            ,"アイテムが見つかりません");
                }
                else
                if(ACmd.DupID==true){
                    QMessageBox::warning(NULL,"更新できません"
                                            ,"重複したIDです");
                }
            }
        }
    }
    else{
        done(false);
    }
}


void EditItemIDDialog::on_pushButtonCancel_clicked()
{
    done(false);
}

