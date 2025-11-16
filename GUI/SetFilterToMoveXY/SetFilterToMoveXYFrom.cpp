#include "SetFilterToMoveXYFromResource.h"
#include "SetFilterToMoveXYFrom.h"
#include "ui_SetFilterToMoveXYFrom.h"
#include "MoveXYDialog.h"
#include "XCommonFilterMoveImage.h"
#include "XFilterClass.h"
#include "XFilterInstance.h"

extern	const	char	*sRoot;
extern	const	char	*sName;


SetFilterToMoveXYFrom::SetFilterToMoveXYFrom(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::SetFilterToMoveXYFrom)
{
    ui->setupUi(this);

	DefaultPushed	=false;
	ui->pushButtonSetShftFilter->move(0,0);
	Msg=/**/"Set Shift filter";
//	Msg=LangSolver.GetString(SetFilterToMoveXYFrom_LS,LID_0)/*"MoveImage"*/;
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

SetFilterToMoveXYFrom::~SetFilterToMoveXYFrom()
{
    delete ui;
}

void	SetFilterToMoveXYFrom::Prepare(void)
{
	ui->pushButtonSetShftFilter->setText(Msg);
	ui->pushButtonSetShftFilter->setFont (CFont);
	ResizeAction();
}

void	SetFilterToMoveXYFrom::ResizeAction()
{
	ui->pushButtonSetShftFilter->resize(width(),height());
}

void SetFilterToMoveXYFrom::on_pushButtonSetShftFilter_clicked()
{
	D=new MoveXYDialog(GetLayersBase());
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdReqShiftMove	RCmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
		GUICmdAckShiftMove	ACmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);

		if(RCmd.Send(GlobalPage,0,ACmd)==true){
			MoveXYList	*a=new MoveXYList();
			a->GlobalPage=GlobalPage;
			a->Dx	=ACmd.MovX;
			a->Dy	=ACmd.MovY;
			D->MoveXYListContainer.AppendList(a);
		}
	}

	D->Init();
	//if(D.exec()==(int)true){
	//}
	D->show();
}

//========================================================================================================

GUICmdReqShiftMove::GUICmdReqShiftMove(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdReqShiftMove::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckShiftMove	*SendBack=GetSendBack(GUICmdAckShiftMove,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	PageDataInOnePhase	*Ph=GetLayersBase()->GetCurrentPageDataPhase();
	FilterInstanceContainer	*Pc=Ph->GetFilterContainer(localPage);
	if(Pc!=NULL){
		FilterInstanceList	*F=Pc->Search(LangSolver.GetString(SetFilterToMoveXYFrom_LS,LID_1)/*"MoveImage"*/);
		if(F!=NULL){
			CmdFilterReqXY	Cmd(GetLayersBase());
			F->TransmitDirectly(&Cmd);
			SendBack->MovX	=Cmd.MovX;
			SendBack->MovY	=Cmd.MovY;
		}
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

//========================================================================================================

GUICmdAckShiftMove::GUICmdAckShiftMove(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdAckShiftMove::Load(QIODevice *f)
{
	if(::Load(f,MovX)==false)
		return false;
	if(::Load(f,MovY)==false)
		return false;
	return true;
}

bool	GUICmdAckShiftMove::Save(QIODevice *f)
{
	if(::Save(f,MovX)==false)
		return false;
	if(::Save(f,MovY)==false)
		return false;
	return true;
}

void	GUICmdAckShiftMove::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}
//========================================================================================================

GUICmdSetShiftMove::GUICmdSetShiftMove(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSetShiftMove::Load(QIODevice *f)
{
	if(::Load(f,MovX)==false)
		return false;
	if(::Load(f,MovY)==false)
		return false;
	return true;
}

bool	GUICmdSetShiftMove::Save(QIODevice *f)
{
	if(::Save(f,MovX)==false)
		return false;
	if(::Save(f,MovY)==false)
		return false;
	return true;
}

void	GUICmdSetShiftMove::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	PageDataInOnePhase	*Ph=GetLayersBase()->GetCurrentPageDataPhase();
	FilterInstanceContainer	*Pc=Ph->GetFilterContainer(localPage);
	if(Pc!=NULL){
		FilterInstanceList	*F=Pc->Search(LangSolver.GetString(SetFilterToMoveXYFrom_LS,LID_2)/*"MoveImage"*/);
		if(F!=NULL){
			CmdFilterReqXY	SCmd(GetLayersBase());
			F->TransmitDirectly(&SCmd);

			if(SCmd.MovX!=MovX || SCmd.MovY!=MovY){
				CmdFilterSetXY	DCmd(GetLayersBase());
				DCmd.MovX=MovX;
				DCmd.MovY=MovY;
				F->TransmitDirectly(&DCmd);

				GetLayersBase()->SaveFilterDef();
			}
		}
	}
	SendAck(localPage);
}
