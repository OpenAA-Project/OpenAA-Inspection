#include "LightDLL2PortForm.h"
#include "SetBaseForm.h"

int		LightDLL2PortForm::BasePort[LEDBARNUMB]={0,1};

LightDLL2PortForm::LightDLL2PortForm(LightDLL1	*p,QWidget *parent)
	: QDialog(parent),BLight(p->GetLayersBase())
{
	ui.setupUi(this);
	int	i=0;
	ChkList[0][i++]=ui.chk_1_0;
	ChkList[0][i++]=ui.chk_1_1;
	ChkList[0][i++]=ui.chk_1_2;
	ChkList[0][i++]=ui.chk_1_3;
	ChkList[0][i++]=ui.chk_1_4;
	ChkList[0][i++]=ui.chk_1_5;
	ChkList[0][i++]=ui.chk_1_6;
	ChkList[0][i++]=ui.chk_1_7;
	ChkList[0][i++]=ui.chk_1_8;
	ChkList[0][i++]=ui.chk_1_9;
	ChkList[0][i++]=ui.chk_1_10;
	ChkList[0][i++]=ui.chk_1_11;
	ChkList[0][i++]=ui.chk_1_12;
	ChkList[0][i++]=ui.chk_1_13;
	ChkList[0][i++]=ui.chk_1_14;
	ChkList[0][i++]=ui.chk_1_15;

	ChkList[0][i++]=ui.chk_1_16;
	ChkList[0][i++]=ui.chk_1_17;
	ChkList[0][i++]=ui.chk_1_18;
	ChkList[0][i++]=ui.chk_1_19;
	ChkList[0][i++]=ui.chk_1_20;
	ChkList[0][i++]=ui.chk_1_21;
	ChkList[0][i++]=ui.chk_1_22;
	ChkList[0][i++]=ui.chk_1_23;
	ChkList[0][i++]=ui.chk_1_24;
	ChkList[0][i++]=ui.chk_1_25;
	ChkList[0][i++]=ui.chk_1_26;
	ChkList[0][i++]=ui.chk_1_27;
	ChkList[0][i++]=ui.chk_1_28;
	ChkList[0][i++]=ui.chk_1_29;
	ChkList[0][i++]=ui.chk_1_30;
	ChkList[0][i++]=ui.chk_1_31;

	ChkList[0][i++]=ui.chk_1_32;
	ChkList[0][i++]=ui.chk_1_33;
	ChkList[0][i++]=ui.chk_1_34;
	ChkList[0][i++]=ui.chk_1_35;
	ChkList[0][i++]=ui.chk_1_36;
	ChkList[0][i++]=ui.chk_1_37;
	ChkList[0][i++]=ui.chk_1_38;
	ChkList[0][i++]=ui.chk_1_39;
	ChkList[0][i++]=ui.chk_1_40;
	ChkList[0][i++]=ui.chk_1_41;
	ChkList[0][i++]=ui.chk_1_42;
	ChkList[0][i++]=ui.chk_1_43;
	ChkList[0][i++]=ui.chk_1_44;
	ChkList[0][i++]=ui.chk_1_45;
	ChkList[0][i++]=ui.chk_1_46;
	ChkList[0][i++]=ui.chk_1_47;

	ChkList[0][i++]=ui.chk_1_48;
	ChkList[0][i++]=ui.chk_1_49;
	ChkList[0][i++]=ui.chk_1_50;
	ChkList[0][i++]=ui.chk_1_51;
	ChkList[0][i++]=ui.chk_1_52;
	ChkList[0][i++]=ui.chk_1_53;
	ChkList[0][i++]=ui.chk_1_54;
	ChkList[0][i++]=ui.chk_1_55;
	ChkList[0][i++]=ui.chk_1_56;
	ChkList[0][i++]=ui.chk_1_57;
	ChkList[0][i++]=ui.chk_1_58;
	ChkList[0][i++]=ui.chk_1_59;
	ChkList[0][i++]=ui.chk_1_60;
	ChkList[0][i++]=ui.chk_1_61;
	ChkList[0][i++]=ui.chk_1_62;
	ChkList[0][i++]=ui.chk_1_63;


	i=0;
	ChkList[1][i++]=ui.chk_2_0;
	ChkList[1][i++]=ui.chk_2_1;
	ChkList[1][i++]=ui.chk_2_2;
	ChkList[1][i++]=ui.chk_2_3;
	ChkList[1][i++]=ui.chk_2_4;
	ChkList[1][i++]=ui.chk_2_5;
	ChkList[1][i++]=ui.chk_2_6;
	ChkList[1][i++]=ui.chk_2_7;
	ChkList[1][i++]=ui.chk_2_8;
	ChkList[1][i++]=ui.chk_2_9;
	ChkList[1][i++]=ui.chk_2_10;
	ChkList[1][i++]=ui.chk_2_11;
	ChkList[1][i++]=ui.chk_2_12;
	ChkList[1][i++]=ui.chk_2_13;
	ChkList[1][i++]=ui.chk_2_14;
	ChkList[1][i++]=ui.chk_2_15;

	ChkList[1][i++]=ui.chk_2_16;
	ChkList[1][i++]=ui.chk_2_17;
	ChkList[1][i++]=ui.chk_2_18;
	ChkList[1][i++]=ui.chk_2_19;
	ChkList[1][i++]=ui.chk_2_20;
	ChkList[1][i++]=ui.chk_2_21;
	ChkList[1][i++]=ui.chk_2_22;
	ChkList[1][i++]=ui.chk_2_23;
	ChkList[1][i++]=ui.chk_2_24;
	ChkList[1][i++]=ui.chk_2_25;
	ChkList[1][i++]=ui.chk_2_26;
	ChkList[1][i++]=ui.chk_2_27;
	ChkList[1][i++]=ui.chk_2_28;
	ChkList[1][i++]=ui.chk_2_29;
	ChkList[1][i++]=ui.chk_2_30;
	ChkList[1][i++]=ui.chk_2_31;

	ChkList[1][i++]=ui.chk_2_32;
	ChkList[1][i++]=ui.chk_2_33;
	ChkList[1][i++]=ui.chk_2_34;
	ChkList[1][i++]=ui.chk_2_35;
	ChkList[1][i++]=ui.chk_2_36;
	ChkList[1][i++]=ui.chk_2_37;
	ChkList[1][i++]=ui.chk_2_38;
	ChkList[1][i++]=ui.chk_2_39;
	ChkList[1][i++]=ui.chk_2_40;
	ChkList[1][i++]=ui.chk_2_41;
	ChkList[1][i++]=ui.chk_2_42;
	ChkList[1][i++]=ui.chk_2_43;
	ChkList[1][i++]=ui.chk_2_44;
	ChkList[1][i++]=ui.chk_2_45;
	ChkList[1][i++]=ui.chk_2_46;
	ChkList[1][i++]=ui.chk_2_47;

	ChkList[1][i++]=ui.chk_2_48;
	ChkList[1][i++]=ui.chk_2_49;
	ChkList[1][i++]=ui.chk_2_50;
	ChkList[1][i++]=ui.chk_2_51;
	ChkList[1][i++]=ui.chk_2_52;
	ChkList[1][i++]=ui.chk_2_53;
	ChkList[1][i++]=ui.chk_2_54;
	ChkList[1][i++]=ui.chk_2_55;
	ChkList[1][i++]=ui.chk_2_56;
	ChkList[1][i++]=ui.chk_2_57;
	ChkList[1][i++]=ui.chk_2_58;
	ChkList[1][i++]=ui.chk_2_59;
	ChkList[1][i++]=ui.chk_2_60;
	ChkList[1][i++]=ui.chk_2_61;
	ChkList[1][i++]=ui.chk_2_62;
	ChkList[1][i++]=ui.chk_2_63;


	i=0;
	LabelList[0][i++]=ui.lb_1_0;
	LabelList[0][i++]=ui.lb_1_1;
	LabelList[0][i++]=ui.lb_1_2;
	LabelList[0][i++]=ui.lb_1_3;
	LabelList[0][i++]=ui.lb_1_4;
	LabelList[0][i++]=ui.lb_1_5;
	LabelList[0][i++]=ui.lb_1_6;
	LabelList[0][i++]=ui.lb_1_7;
	LabelList[0][i++]=ui.lb_1_8;
	LabelList[0][i++]=ui.lb_1_9;
	LabelList[0][i++]=ui.lb_1_10;
	LabelList[0][i++]=ui.lb_1_11;
	LabelList[0][i++]=ui.lb_1_12;
	LabelList[0][i++]=ui.lb_1_13;
	LabelList[0][i++]=ui.lb_1_14;
	LabelList[0][i++]=ui.lb_1_15;

	LabelList[0][i++]=ui.lb_1_16;
	LabelList[0][i++]=ui.lb_1_17;
	LabelList[0][i++]=ui.lb_1_18;
	LabelList[0][i++]=ui.lb_1_19;
	LabelList[0][i++]=ui.lb_1_20;
	LabelList[0][i++]=ui.lb_1_21;
	LabelList[0][i++]=ui.lb_1_22;
	LabelList[0][i++]=ui.lb_1_23;
	LabelList[0][i++]=ui.lb_1_24;
	LabelList[0][i++]=ui.lb_1_25;
	LabelList[0][i++]=ui.lb_1_26;
	LabelList[0][i++]=ui.lb_1_27;
	LabelList[0][i++]=ui.lb_1_28;
	LabelList[0][i++]=ui.lb_1_29;
	LabelList[0][i++]=ui.lb_1_30;
	LabelList[0][i++]=ui.lb_1_31;

	LabelList[0][i++]=ui.lb_1_32;
	LabelList[0][i++]=ui.lb_1_33;
	LabelList[0][i++]=ui.lb_1_34;
	LabelList[0][i++]=ui.lb_1_35;
	LabelList[0][i++]=ui.lb_1_36;
	LabelList[0][i++]=ui.lb_1_37;
	LabelList[0][i++]=ui.lb_1_38;
	LabelList[0][i++]=ui.lb_1_39;
	LabelList[0][i++]=ui.lb_1_40;
	LabelList[0][i++]=ui.lb_1_41;
	LabelList[0][i++]=ui.lb_1_42;
	LabelList[0][i++]=ui.lb_1_43;
	LabelList[0][i++]=ui.lb_1_44;
	LabelList[0][i++]=ui.lb_1_45;
	LabelList[0][i++]=ui.lb_1_46;
	LabelList[0][i++]=ui.lb_1_47;

	LabelList[0][i++]=ui.lb_1_48;
	LabelList[0][i++]=ui.lb_1_49;
	LabelList[0][i++]=ui.lb_1_50;
	LabelList[0][i++]=ui.lb_1_51;
	LabelList[0][i++]=ui.lb_1_52;
	LabelList[0][i++]=ui.lb_1_53;
	LabelList[0][i++]=ui.lb_1_54;
	LabelList[0][i++]=ui.lb_1_55;
	LabelList[0][i++]=ui.lb_1_56;
	LabelList[0][i++]=ui.lb_1_57;
	LabelList[0][i++]=ui.lb_1_58;
	LabelList[0][i++]=ui.lb_1_59;
	LabelList[0][i++]=ui.lb_1_60;
	LabelList[0][i++]=ui.lb_1_61;
	LabelList[0][i++]=ui.lb_1_62;
	LabelList[0][i++]=ui.lb_1_63;

	i=0;
	LabelList[1][i++]=ui.lb_2_0;
	LabelList[1][i++]=ui.lb_2_1;
	LabelList[1][i++]=ui.lb_2_2;
	LabelList[1][i++]=ui.lb_2_3;
	LabelList[1][i++]=ui.lb_2_4;
	LabelList[1][i++]=ui.lb_2_5;
	LabelList[1][i++]=ui.lb_2_6;
	LabelList[1][i++]=ui.lb_2_7;
	LabelList[1][i++]=ui.lb_2_8;
	LabelList[1][i++]=ui.lb_2_9;
	LabelList[1][i++]=ui.lb_2_10;
	LabelList[1][i++]=ui.lb_2_11;
	LabelList[1][i++]=ui.lb_2_12;
	LabelList[1][i++]=ui.lb_2_13;
	LabelList[1][i++]=ui.lb_2_14;
	LabelList[1][i++]=ui.lb_2_15;

	LabelList[1][i++]=ui.lb_2_16;
	LabelList[1][i++]=ui.lb_2_17;
	LabelList[1][i++]=ui.lb_2_18;
	LabelList[1][i++]=ui.lb_2_19;
	LabelList[1][i++]=ui.lb_2_20;
	LabelList[1][i++]=ui.lb_2_21;
	LabelList[1][i++]=ui.lb_2_22;
	LabelList[1][i++]=ui.lb_2_23;
	LabelList[1][i++]=ui.lb_2_24;
	LabelList[1][i++]=ui.lb_2_25;
	LabelList[1][i++]=ui.lb_2_26;
	LabelList[1][i++]=ui.lb_2_27;
	LabelList[1][i++]=ui.lb_2_28;
	LabelList[1][i++]=ui.lb_2_29;
	LabelList[1][i++]=ui.lb_2_30;
	LabelList[1][i++]=ui.lb_2_31;

	LabelList[1][i++]=ui.lb_2_32;
	LabelList[1][i++]=ui.lb_2_33;
	LabelList[1][i++]=ui.lb_2_34;
	LabelList[1][i++]=ui.lb_2_35;
	LabelList[1][i++]=ui.lb_2_36;
	LabelList[1][i++]=ui.lb_2_37;
	LabelList[1][i++]=ui.lb_2_38;
	LabelList[1][i++]=ui.lb_2_39;
	LabelList[1][i++]=ui.lb_2_40;
	LabelList[1][i++]=ui.lb_2_41;
	LabelList[1][i++]=ui.lb_2_42;
	LabelList[1][i++]=ui.lb_2_43;
	LabelList[1][i++]=ui.lb_2_44;
	LabelList[1][i++]=ui.lb_2_45;
	LabelList[1][i++]=ui.lb_2_46;
	LabelList[1][i++]=ui.lb_2_47;

	LabelList[1][i++]=ui.lb_2_48;
	LabelList[1][i++]=ui.lb_2_49;
	LabelList[1][i++]=ui.lb_2_50;
	LabelList[1][i++]=ui.lb_2_51;
	LabelList[1][i++]=ui.lb_2_52;
	LabelList[1][i++]=ui.lb_2_53;
	LabelList[1][i++]=ui.lb_2_54;
	LabelList[1][i++]=ui.lb_2_55;
	LabelList[1][i++]=ui.lb_2_56;
	LabelList[1][i++]=ui.lb_2_57;
	LabelList[1][i++]=ui.lb_2_58;
	LabelList[1][i++]=ui.lb_2_59;
	LabelList[1][i++]=ui.lb_2_60;
	LabelList[1][i++]=ui.lb_2_61;
	LabelList[1][i++]=ui.lb_2_62;
	LabelList[1][i++]=ui.lb_2_63;

	p->GetLayersBase()->InstallOperationLog(this);
}

LightDLL2PortForm::~LightDLL2PortForm()
{

}

void	LightDLL2PortForm::showEvent(QShowEvent *)
{
	for(int i=0;i<2;i++){
		for(int j=0;j<64;j++){
			ChkList[i][j]->setChecked(false);
			int	n=BLight.LEDBright[i][j];
			LabelList[i][j]->setText(QString::number(n));
			BLight.SaveLEDBright[i][j]=n;
		}
	}
	ui.le_1->setText(BLight.BarComment[0]);
	ui.le_2->setText(BLight.BarComment[1]);
}

void LightDLL2PortForm::on_tb_1_clicked()
{
	int	CountOff=0;
	for(int j=0;j<64;j++){
		if(ChkList[0][j]	->isChecked()==false){
			CountOff++;
		}
	}
	if(CountOff==0){
		for(int j=0;j<64;j++){
			ChkList[0][j]	->setChecked(false);
		}
	}
	else{
		for(int j=0;j<64;j++){
			ChkList[0][j]	->setChecked(true);
		}
	}
}

void LightDLL2PortForm::on_tb_2_clicked()
{
	int	CountOff=0;
	for(int j=0;j<64;j++){
		if(ChkList[1][j]	->isChecked()==false){
			CountOff++;
		}
	}
	if(CountOff==0){
		for(int j=0;j<64;j++){
			ChkList[1][j]	->setChecked(false);
		}
	}
	else{
		for(int j=0;j<64;j++){
			ChkList[1][j]	->setChecked(true);
		}
	}
}


void LightDLL2PortForm::on_tbLeft_0_clicked()
{
	for(int i=0;i<2;i++){
		ChkList[i][0+0*16]	->setChecked(true);
		ChkList[i][0+1*16]	->setChecked(true);
		ChkList[i][0+2*16]	->setChecked(true);
		ChkList[i][0+3*16]	->setChecked(true);
	}
}

void LightDLL2PortForm::on_tbLeft_1_clicked()
{
	for(int i=0;i<2;i++){
		ChkList[i][1+0*16]	->setChecked(true);
		ChkList[i][1+1*16]	->setChecked(true);
		ChkList[i][1+2*16]	->setChecked(true);
		ChkList[i][1+3*16]	->setChecked(true);
	}
}

void LightDLL2PortForm::on_tbLeft_2_clicked()
{
	for(int i=0;i<2;i++){
		ChkList[i][2+0*16]	->setChecked(true);
		ChkList[i][2+1*16]	->setChecked(true);
		ChkList[i][2+2*16]	->setChecked(true);
		ChkList[i][2+3*16]	->setChecked(true);
	}
}

void LightDLL2PortForm::on_tbLeft_3_clicked()
{
	for(int i=0;i<2;i++){
		ChkList[i][3+0*16]	->setChecked(true);
		ChkList[i][3+1*16]	->setChecked(true);
		ChkList[i][3+2*16]	->setChecked(true);
		ChkList[i][3+3*16]	->setChecked(true);
	}
}

void LightDLL2PortForm::on_tbLeft_4_clicked()
{
	for(int i=0;i<2;i++){
		ChkList[i][4+0*16]	->setChecked(true);
		ChkList[i][4+1*16]	->setChecked(true);
		ChkList[i][4+2*16]	->setChecked(true);
		ChkList[i][4+3*16]	->setChecked(true);
	}
}

void LightDLL2PortForm::on_tbLeft_5_clicked()
{
	for(int i=0;i<2;i++){
		ChkList[i][5+0*16]	->setChecked(true);
		ChkList[i][5+1*16]	->setChecked(true);
		ChkList[i][5+2*16]	->setChecked(true);
		ChkList[i][5+3*16]	->setChecked(true);
	}
}

void LightDLL2PortForm::on_tbLeft_6_clicked()
{
	for(int i=0;i<2;i++){
		ChkList[i][6+0*16]	->setChecked(true);
		ChkList[i][6+1*16]	->setChecked(true);
		ChkList[i][6+2*16]	->setChecked(true);
		ChkList[i][6+3*16]	->setChecked(true);
	}
}

void LightDLL2PortForm::on_tbLeft_7_clicked()
{
	for(int i=0;i<2;i++){
		ChkList[i][7+0*16]	->setChecked(true);
		ChkList[i][7+1*16]	->setChecked(true);
		ChkList[i][7+2*16]	->setChecked(true);
		ChkList[i][7+3*16]	->setChecked(true);
	}
}

void LightDLL2PortForm::on_tbLeft_8_clicked()
{
	for(int i=0;i<2;i++){
		ChkList[i][8+0*16]	->setChecked(true);
		ChkList[i][8+1*16]	->setChecked(true);
		ChkList[i][8+2*16]	->setChecked(true);
		ChkList[i][8+3*16]	->setChecked(true);
	}
}

void LightDLL2PortForm::on_tbLeft_9_clicked()
{
	for(int i=0;i<2;i++){
		ChkList[i][9+0*16]	->setChecked(true);
		ChkList[i][9+1*16]	->setChecked(true);
		ChkList[i][9+2*16]	->setChecked(true);
		ChkList[i][9+3*16]	->setChecked(true);
	}
}

void LightDLL2PortForm::on_tbLeft_10_clicked()
{
	for(int i=0;i<2;i++){
		ChkList[i][10+0*16]	->setChecked(true);
		ChkList[i][10+1*16]	->setChecked(true);
		ChkList[i][10+2*16]	->setChecked(true);
		ChkList[i][10+3*16]	->setChecked(true);
	}
}

void LightDLL2PortForm::on_tbLeft_11_clicked()
{
	for(int i=0;i<2;i++){
		ChkList[i][11+0*16]	->setChecked(true);
		ChkList[i][11+1*16]	->setChecked(true);
		ChkList[i][11+2*16]	->setChecked(true);
		ChkList[i][11+3*16]	->setChecked(true);
	}
}

void LightDLL2PortForm::on_tbLeft_12_clicked()
{
	for(int i=0;i<2;i++){
		ChkList[i][12+0*16]	->setChecked(true);
		ChkList[i][12+1*16]	->setChecked(true);
		ChkList[i][12+2*16]	->setChecked(true);
		ChkList[i][12+3*16]	->setChecked(true);
	}
}

void LightDLL2PortForm::on_tbLeft_13_clicked()
{
	for(int i=0;i<2;i++){
		ChkList[i][13+0*16]	->setChecked(true);
		ChkList[i][13+1*16]	->setChecked(true);
		ChkList[i][13+2*16]	->setChecked(true);
		ChkList[i][13+3*16]	->setChecked(true);
	}
}

void LightDLL2PortForm::on_tbLeft_14_clicked()
{
	for(int i=0;i<2;i++){
		ChkList[i][14+0*16]	->setChecked(true);
		ChkList[i][14+1*16]	->setChecked(true);
		ChkList[i][14+2*16]	->setChecked(true);
		ChkList[i][14+3*16]	->setChecked(true);
	}
}

void LightDLL2PortForm::on_tbLeft_15_clicked()
{
	for(int i=0;i<2;i++){
		ChkList[i][15+0*16]	->setChecked(true);
		ChkList[i][15+1*16]	->setChecked(true);
		ChkList[i][15+2*16]	->setChecked(true);
		ChkList[i][15+3*16]	->setChecked(true);
	}
}
void LightDLL2PortForm::on_vsBrightness_valueChanged(int)
{
	int	n=ui.vsBrightness->value();
	ui.sbBrightness->setValue(n);
}

void LightDLL2PortForm::on_sbBrightness_valueChanged(int)
{
	int	n=ui.sbBrightness->value();
	for(int i=0;i<2;i++){
		for(int j=0;j<64;j++){
			if(ChkList[i][j]->isChecked()==true){
				BLight.SaveLEDBright[i][j]=n;
				LabelList[i][j]->setText(QString::number(n));
			}
		}
	}
}

void LightDLL2PortForm::on_pbTransport_clicked()
{
	ui.pgbLight->setValue(0);
	for(int i=0;i<LEDBARNUMB;i++){
		for(int j=0;j<LEDsNumb;j++){
			BLight.CLED[i].Change(j,BLight.SaveLEDBright[i][j]);
			BLight.CLED[i].OutData(j,BLight.Gain[i][j]);
		}
		ui.pgbLight->setValue(100*(i+1)/LEDBARNUMB);
	}
}

void LightDLL2PortForm::on_tbOnOff_clicked()
{
	if(ui.tbOnOff->isChecked()==true){
		ui.pgbLight->setValue(0);
		for(int i=0;i<LEDBARNUMB;i++){
			for(int j=0;j<LEDsNumb;j++){
				BLight.CLED[i].Change(j,BLight.SaveLEDBright[i][j]);
				BLight.CLED[i].OutData(j,BLight.Gain[i][j]);
			}
			ui.pgbLight->setValue(100*(i+1)/LEDBARNUMB);
		}
	}
	else{
		BLight.SetLighting(false);
	}
}

void LightDLL2PortForm::on_pbAllSelect_clicked()
{
	for(int i=0;i<LEDBARNUMB;i++){
		for(int j=0;j<LEDsNumb;j++){
			ChkList[i][j]	->setChecked(true);
		}
	}
}

void LightDLL2PortForm::on_pbClearSelect_clicked()
{
	for(int i=0;i<LEDBARNUMB;i++){
		for(int j=0;j<LEDsNumb;j++){
			ChkList[i][j]	->setChecked(false);
		}
	}
}

void LightDLL2PortForm::on_pbOK_clicked()
{
	for(int i=0;i<LEDBARNUMB;i++){
		for(int j=0;j<LEDsNumb;j++){
			BLight.LEDBright[i][j]=BLight.SaveLEDBright[i][j];
		}
	}
	BLight.BarComment[0]=ui.le_1->text();
	BLight.BarComment[1]=ui.le_2->text();

	accept();
}

void LightDLL2PortForm::on_pbCancel_clicked()
{
	reject();
}

void LightDLL2PortForm::on_pushButtonSet_clicked()
{
	SetBaseForm	D(BLight.GetLayersBase(),BasePort);
	D.exec();
	for(int i=0;i<LEDBARNUMB;i++){
		BLight.CLED[i].SetID(BasePort[i]);
	}
}