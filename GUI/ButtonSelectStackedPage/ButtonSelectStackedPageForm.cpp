#include "ButtonSelectStackedPageForm.h"
#include "ui_ButtonSelectStackedPageForm.h"
#include "GeneralStackForm.h"

ButtonSelectStackedPageForm::ButtonSelectStackedPageForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::ButtonSelectStackedPageForm)
{
    ui->setupUi(this);
	FirstPage	=0;
	Msg.append(/**/"Default");
	CharColor=Qt::black;

	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ButtonSelectStackedPageForm::~ButtonSelectStackedPageForm()
{
    delete ui;
}

void	ButtonSelectStackedPageForm::Prepare(void)
{
	int	N=Msg.count();

	//while(N>0){
	//	if(Msg[N-1].isEmpty()==true){
	//		Msg.removeAt(N-1);
	//		N=Msg.count();
	//	}
	//}

	if(N>10)
		N=10;

	B[0]=&ui->toolButton1;
	B[1]=&ui->toolButton2;
	B[2]=&ui->toolButton3;
	B[3]=&ui->toolButton4;
	B[4]=&ui->toolButton5;
	B[5]=&ui->toolButton6;
	B[6]=&ui->toolButton7;
	B[7]=&ui->toolButton8;
	B[8]=&ui->toolButton9;
	B[9]=&ui->toolButton10;

	for(int i=0;i<N;i++){
		(*B[i])->setVisible(true);
		(*B[i])->setText(Msg[i]);
		QPalette	P=(*B[i])->palette();
		P.setColor(QPalette::ButtonText,CharColor);
		(*B[i])->setPalette(P);
		(*B[i])->setFont (CFont);
	}
	for(int i=N;i<10;i++){
		(*B[i])->setVisible(false);
	}
	if(FirstPage<N){
		(*B[FirstPage])->setChecked(true);
	}
	ResizeAction();
}

void	ButtonSelectStackedPageForm::ResizeAction()
{
	int	N=Msg.count();
	if(N>10)
		N=10;
	int	W=width()/N;
	for(int i=0;i<N;i++){
		(*B[i])->setGeometry(W*i,0,W-1,height());
	}
}

void	ButtonSelectStackedPageForm::SelectPage(int page)
{
	(*B[page])->click();
}

void ButtonSelectStackedPageForm::on_toolButton1_clicked()
{
	GUIFormBase	*StackForm=GetLayersBase()->FindByName(StackFormInst);
	if(StackForm!=NULL){
		CmdShowPage	RCmd(GetLayersBase());
		RCmd.ID=0;
		StackForm->TransmitDirectly(&RCmd);
	}
}

void ButtonSelectStackedPageForm::on_toolButton2_clicked()
{
	GUIFormBase	*StackForm=GetLayersBase()->FindByName(StackFormInst);
	if(StackForm!=NULL){
		CmdShowPage	RCmd(GetLayersBase());
		RCmd.ID=1;
		StackForm->TransmitDirectly(&RCmd);
	}

}

void ButtonSelectStackedPageForm::on_toolButton3_clicked()
{
	GUIFormBase	*StackForm=GetLayersBase()->FindByName(StackFormInst);
	if(StackForm!=NULL){
		CmdShowPage	RCmd(GetLayersBase());
		RCmd.ID=2;
		StackForm->TransmitDirectly(&RCmd);
	}

}

void ButtonSelectStackedPageForm::on_toolButton4_clicked()
{
	GUIFormBase	*StackForm=GetLayersBase()->FindByName(StackFormInst);
	if(StackForm!=NULL){
		CmdShowPage	RCmd(GetLayersBase());
		RCmd.ID=3;
		StackForm->TransmitDirectly(&RCmd);
	}

}

void ButtonSelectStackedPageForm::on_toolButton5_clicked()
{
	GUIFormBase	*StackForm=GetLayersBase()->FindByName(StackFormInst);
	if(StackForm!=NULL){
		CmdShowPage	RCmd(GetLayersBase());
		RCmd.ID=4;
		StackForm->TransmitDirectly(&RCmd);
	}

}

void ButtonSelectStackedPageForm::on_toolButton6_clicked()
{
	GUIFormBase	*StackForm=GetLayersBase()->FindByName(StackFormInst);
	if(StackForm!=NULL){
		CmdShowPage	RCmd(GetLayersBase());
		RCmd.ID=5;
		StackForm->TransmitDirectly(&RCmd);
	}

}

void ButtonSelectStackedPageForm::on_toolButton7_clicked()
{
	GUIFormBase	*StackForm=GetLayersBase()->FindByName(StackFormInst);
	if(StackForm!=NULL){
		CmdShowPage	RCmd(GetLayersBase());
		RCmd.ID=6;
		StackForm->TransmitDirectly(&RCmd);
	}

}

void ButtonSelectStackedPageForm::on_toolButton8_clicked()
{
	GUIFormBase	*StackForm=GetLayersBase()->FindByName(StackFormInst);
	if(StackForm!=NULL){
		CmdShowPage	RCmd(GetLayersBase());
		RCmd.ID=7;
		StackForm->TransmitDirectly(&RCmd);
	}

}

void ButtonSelectStackedPageForm::on_toolButton9_clicked()
{
	GUIFormBase	*StackForm=GetLayersBase()->FindByName(StackFormInst);
	if(StackForm!=NULL){
		CmdShowPage	RCmd(GetLayersBase());
		RCmd.ID=8;
		StackForm->TransmitDirectly(&RCmd);
	}

}

void ButtonSelectStackedPageForm::on_toolButton10_clicked()
{
	GUIFormBase	*StackForm=GetLayersBase()->FindByName(StackFormInst);
	if(StackForm!=NULL){
		CmdShowPage	RCmd(GetLayersBase());
		RCmd.ID=9;
		StackForm->TransmitDirectly(&RCmd);
	}

}
