#include "ShowTotalCountForm.h"
#include "ui_ShowTotalCountForm.h"
#include "XGeneralFunc.h"
#include "XResult.h"

extern  const	char	*sRoot;
extern  const	char	*sName;

ShowTotalCountForm::ShowTotalCountForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::ShowTotalCountForm)
{
    ui->setupUi(this);

    TotalCount      =0;
    OKCount         =0;
    NGCount         =0;
    LotTotalCount   =0;
    LotOKCount      =0;
    LotNGCount      =0;
}

ShowTotalCountForm::~ShowTotalCountForm()
{
    delete ui;
}

void	ShowTotalCountForm::ResizeAction()
{
    ui->tableWidget->resize(width(),height()-ui->pushButtonReset->height());
    ui->pushButtonReset->move(0,height()-ui->pushButtonReset->height());
    ui->pushButtonReset->resize(width(),ui->pushButtonReset->height());
}

void    ShowTotalCountForm::ShowCounter(void)
{
    ::SetDataToTable(ui->tableWidget,0, 0, QString::number(TotalCount));
    ::SetDataToTable(ui->tableWidget,0, 1, QString::number(OKCount));
    ::SetDataToTable(ui->tableWidget,0, 2, QString::number(NGCount));
    ::SetDataToTable(ui->tableWidget,0, 3, QString::number(LotTotalCount));
    ::SetDataToTable(ui->tableWidget,0, 4, QString::number(LotOKCount));
    ::SetDataToTable(ui->tableWidget,0, 5, QString::number(LotNGCount));
}

void ShowTotalCountForm::on_pushButtonReset_clicked()
{
    TotalCount =0;
    OKCount    =0;
    NGCount    =0;
    LotTotalCount   =0;
    LotOKCount      =0;
    LotNGCount      =0;

    ShowCounter();
}
void	ShowTotalCountForm::StartLot	(void)
{
    LotTotalCount   =0;
    LotOKCount      =0;
    LotNGCount      =0;
    ShowCounter();
}
void	ShowTotalCountForm::ShowInPlayer(int64 shownInspectionID)
{
    LayersBase	*LBase	=GetLayersBase();
    bool	ResultOK=true;
	if(LBase->IsLocalCamera()==false){
		for(int page=0;page<GetPageNumb();page++){
			int	GlobalPage=LBase->GetGlobalPageFromLocal(page);
			GUICmdReqResult		CmdReq(LBase,sRoot,sName,GlobalPage);
			CmdReq.ShownInspectionID=shownInspectionID;
			GUICmdSendResult	CmdAck(LBase,sRoot,sName,GlobalPage);
			if(CmdReq.Send(GlobalPage ,0,CmdAck)==true){
				if(CmdAck.ResultOK==false){
					ResultOK=false;
				}
			}
		}
	}
	else{
		ResultInspection	*R=GetLayersBase()->GetBufferedResultAbsolutely(shownInspectionID);
		if(R!=NULL){
			bool3	OK;
			bool	MaxError , TimeOver;
			R->GatherResult(OK ,MaxError , TimeOver,true,false);
			ResultOK=(OK==true3)?true:false;
		}
	}
    TotalCount++;
    LotTotalCount++;
    if(ResultOK==true){
        OKCount++;
        LotOKCount++;
    }
    else{
        NGCount++;
        LotNGCount++;
    }
    ShowCounter();
}

//=======================================================================

GUICmdReqResult::GUICmdReqResult(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqResult::Save(QIODevice *f)
{
	if(::Save(f,ShownInspectionID)==false)  return false;
	return(true);
}
bool	GUICmdReqResult::Load(QIODevice *f)
{
	if(::Load(f,ShownInspectionID)==false)  return false;
	return(true);
}

void	GUICmdReqResult::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendResult	*SendBack=GetSendBack(GUICmdSendResult,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	ResultInspection	*R=GetLayersBase()->GetBufferedResult(ShownInspectionID);
	if(R!=NULL){
		SendBack->ResultOK=R->IsResultOK();
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

//=======================================================================
GUICmdSendResult::GUICmdSendResult(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	ResultOK=true;
}


bool	GUICmdSendResult::Load(QIODevice *f)
{
	if(::Load(f,ResultOK)==false){
		return false;
	}

	return true;
}
bool	GUICmdSendResult::Save(QIODevice *f)
{
	if(::Save(f,ResultOK)==false){
		return false;
	}

	return true;
}
