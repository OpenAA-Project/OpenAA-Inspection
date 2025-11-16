#include "EasyGenerateAlignmentResource.h"
#include "EasyGenerateAlignmentForm.h"
#include "ui_EasyGenerateAlignmentForm.h"
#include "CartonMenuForm.h"

EasyGenerateAlignmentForm::EasyGenerateAlignmentForm(LayersBase *Base ,QWidget *parent) :
     GUIFormBase(Base,parent),
    ui(new Ui::EasyGenerateAlignmentForm)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

EasyGenerateAlignmentForm::~EasyGenerateAlignmentForm()
{
    delete ui;
}
void	EasyGenerateAlignmentForm::Prepare(void)
{
	ResizeAction();
}
void	EasyGenerateAlignmentForm::ResizeAction()
{
	ui->toolButtonAutoGenerate->move(0,0);
	ui->toolButtonAutoGenerate->resize(width(),height());
}
void EasyGenerateAlignmentForm::on_toolButtonAutoGenerate_clicked()
{
	GUIFormBase	*Ret[100];
	int	N=GetLayersBase()->EnumGUIInst(/**/"KidaPrint",/**/"EasyPropertyAlignment",Ret,100);
	for(int i=0;i<N;i++){
		//IntegrationGenerateAutomatically	Cmd(GetLayersBase());
		IntegrationGenerateAlignmentMark	Cmd(GetLayersBase());
		Ret[i]->TransmitDirectly(&Cmd);
	}

	emit	SignalBusy();

	bool	NowOnIdle;
	do{
		NowOnIdle=true;
		for(EachMaster *m=GetLayersBase()->GetIntegrationBasePointer()->MasterDatas.GetFirst();m!=NULL;m=m->GetNext()){
			int	SNo=m->GetIntegrationSlaveNo();
			if(GetLayersBase()->GetIntegrationBasePointer()->CheckOnProcessing(SNo)==false){
				NowOnIdle=false;
			}
		}
	}while(NowOnIdle==false);

	emit	SignalIdle();
	RepaintAll();
}
