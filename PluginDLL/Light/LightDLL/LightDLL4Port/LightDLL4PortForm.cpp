#include "LightDLL4PortForm.h"
#include "ui_LightDLL4PortForm.h"

int		LightDLL4PortForm::BasePort[LEDBARNUMB]={0,1,2,3};

LightDLL4PortForm::LightDLL4PortForm(LightDLL1	*p,QWidget *parent) :
    QDialog(parent),BLight(p->GetLayersBase()),
    ui(new Ui::LightDLL4PortForm)
{
    ui->setupUi(this);
	int	i=0;
	ChkList[0][i++]=ui->chk_1_0;
	ChkList[0][i++]=ui->chk_1_1;
	ChkList[0][i++]=ui->chk_1_2;
	ChkList[0][i++]=ui->chk_1_3;
	ChkList[0][i++]=ui->chk_1_4;
	ChkList[0][i++]=ui->chk_1_5;
	ChkList[0][i++]=ui->chk_1_6;
	ChkList[0][i++]=ui->chk_1_7;
	ChkList[0][i++]=ui->chk_1_8;
	ChkList[0][i++]=ui->chk_1_9;
	ChkList[0][i++]=ui->chk_1_10;
	ChkList[0][i++]=ui->chk_1_11;
	ChkList[0][i++]=ui->chk_1_12;
	ChkList[0][i++]=ui->chk_1_13;
	ChkList[0][i++]=ui->chk_1_14;
	ChkList[0][i++]=ui->chk_1_15;

	ChkList[0][i++]=ui->chk_1_16;
	ChkList[0][i++]=ui->chk_1_17;
	ChkList[0][i++]=ui->chk_1_18;
	ChkList[0][i++]=ui->chk_1_19;
	ChkList[0][i++]=ui->chk_1_20;
	ChkList[0][i++]=ui->chk_1_21;
	ChkList[0][i++]=ui->chk_1_22;
	ChkList[0][i++]=ui->chk_1_23;
	ChkList[0][i++]=ui->chk_1_24;
	ChkList[0][i++]=ui->chk_1_25;
	ChkList[0][i++]=ui->chk_1_26;
	ChkList[0][i++]=ui->chk_1_27;
	ChkList[0][i++]=ui->chk_1_28;
	ChkList[0][i++]=ui->chk_1_29;
	ChkList[0][i++]=ui->chk_1_30;
	ChkList[0][i++]=ui->chk_1_31;

	ChkList[0][i++]=ui->chk_1_32;
	ChkList[0][i++]=ui->chk_1_33;
	ChkList[0][i++]=ui->chk_1_34;
	ChkList[0][i++]=ui->chk_1_35;
	ChkList[0][i++]=ui->chk_1_36;
	ChkList[0][i++]=ui->chk_1_37;
	ChkList[0][i++]=ui->chk_1_38;
	ChkList[0][i++]=ui->chk_1_39;
	ChkList[0][i++]=ui->chk_1_40;
	ChkList[0][i++]=ui->chk_1_41;
	ChkList[0][i++]=ui->chk_1_42;
	ChkList[0][i++]=ui->chk_1_43;
	ChkList[0][i++]=ui->chk_1_44;
	ChkList[0][i++]=ui->chk_1_45;
	ChkList[0][i++]=ui->chk_1_46;
	ChkList[0][i++]=ui->chk_1_47;

	ChkList[0][i++]=ui->chk_1_48;
	ChkList[0][i++]=ui->chk_1_49;
	ChkList[0][i++]=ui->chk_1_50;
	ChkList[0][i++]=ui->chk_1_51;
	ChkList[0][i++]=ui->chk_1_52;
	ChkList[0][i++]=ui->chk_1_53;
	ChkList[0][i++]=ui->chk_1_54;
	ChkList[0][i++]=ui->chk_1_55;
	ChkList[0][i++]=ui->chk_1_56;
	ChkList[0][i++]=ui->chk_1_57;
	ChkList[0][i++]=ui->chk_1_58;
	ChkList[0][i++]=ui->chk_1_59;
	ChkList[0][i++]=ui->chk_1_60;
	ChkList[0][i++]=ui->chk_1_61;
	ChkList[0][i++]=ui->chk_1_62;
	ChkList[0][i++]=ui->chk_1_63;


	i=0;
	ChkList[1][i++]=ui->chk_2_0;
	ChkList[1][i++]=ui->chk_2_1;
	ChkList[1][i++]=ui->chk_2_2;
	ChkList[1][i++]=ui->chk_2_3;
	ChkList[1][i++]=ui->chk_2_4;
	ChkList[1][i++]=ui->chk_2_5;
	ChkList[1][i++]=ui->chk_2_6;
	ChkList[1][i++]=ui->chk_2_7;
	ChkList[1][i++]=ui->chk_2_8;
	ChkList[1][i++]=ui->chk_2_9;
	ChkList[1][i++]=ui->chk_2_10;
	ChkList[1][i++]=ui->chk_2_11;
	ChkList[1][i++]=ui->chk_2_12;
	ChkList[1][i++]=ui->chk_2_13;
	ChkList[1][i++]=ui->chk_2_14;
	ChkList[1][i++]=ui->chk_2_15;

	ChkList[1][i++]=ui->chk_2_16;
	ChkList[1][i++]=ui->chk_2_17;
	ChkList[1][i++]=ui->chk_2_18;
	ChkList[1][i++]=ui->chk_2_19;
	ChkList[1][i++]=ui->chk_2_20;
	ChkList[1][i++]=ui->chk_2_21;
	ChkList[1][i++]=ui->chk_2_22;
	ChkList[1][i++]=ui->chk_2_23;
	ChkList[1][i++]=ui->chk_2_24;
	ChkList[1][i++]=ui->chk_2_25;
	ChkList[1][i++]=ui->chk_2_26;
	ChkList[1][i++]=ui->chk_2_27;
	ChkList[1][i++]=ui->chk_2_28;
	ChkList[1][i++]=ui->chk_2_29;
	ChkList[1][i++]=ui->chk_2_30;
	ChkList[1][i++]=ui->chk_2_31;

	ChkList[1][i++]=ui->chk_2_32;
	ChkList[1][i++]=ui->chk_2_33;
	ChkList[1][i++]=ui->chk_2_34;
	ChkList[1][i++]=ui->chk_2_35;
	ChkList[1][i++]=ui->chk_2_36;
	ChkList[1][i++]=ui->chk_2_37;
	ChkList[1][i++]=ui->chk_2_38;
	ChkList[1][i++]=ui->chk_2_39;
	ChkList[1][i++]=ui->chk_2_40;
	ChkList[1][i++]=ui->chk_2_41;
	ChkList[1][i++]=ui->chk_2_42;
	ChkList[1][i++]=ui->chk_2_43;
	ChkList[1][i++]=ui->chk_2_44;
	ChkList[1][i++]=ui->chk_2_45;
	ChkList[1][i++]=ui->chk_2_46;
	ChkList[1][i++]=ui->chk_2_47;

	ChkList[1][i++]=ui->chk_2_48;
	ChkList[1][i++]=ui->chk_2_49;
	ChkList[1][i++]=ui->chk_2_50;
	ChkList[1][i++]=ui->chk_2_51;
	ChkList[1][i++]=ui->chk_2_52;
	ChkList[1][i++]=ui->chk_2_53;
	ChkList[1][i++]=ui->chk_2_54;
	ChkList[1][i++]=ui->chk_2_55;
	ChkList[1][i++]=ui->chk_2_56;
	ChkList[1][i++]=ui->chk_2_57;
	ChkList[1][i++]=ui->chk_2_58;
	ChkList[1][i++]=ui->chk_2_59;
	ChkList[1][i++]=ui->chk_2_60;
	ChkList[1][i++]=ui->chk_2_61;
	ChkList[1][i++]=ui->chk_2_62;
	ChkList[1][i++]=ui->chk_2_63;


	i=0;
	ChkList[2][i++]=ui->chk_3_0;
	ChkList[2][i++]=ui->chk_3_1;
	ChkList[2][i++]=ui->chk_3_2;
	ChkList[2][i++]=ui->chk_3_3;
	ChkList[2][i++]=ui->chk_3_4;
	ChkList[2][i++]=ui->chk_3_5;
	ChkList[2][i++]=ui->chk_3_6;
	ChkList[2][i++]=ui->chk_3_7;
	ChkList[2][i++]=ui->chk_3_8;
	ChkList[2][i++]=ui->chk_3_9;
	ChkList[2][i++]=ui->chk_3_10;
	ChkList[2][i++]=ui->chk_3_11;
	ChkList[2][i++]=ui->chk_3_12;
	ChkList[2][i++]=ui->chk_3_13;
	ChkList[2][i++]=ui->chk_3_14;
	ChkList[2][i++]=ui->chk_3_15;

	ChkList[2][i++]=ui->chk_3_16;
	ChkList[2][i++]=ui->chk_3_17;
	ChkList[2][i++]=ui->chk_3_18;
	ChkList[2][i++]=ui->chk_3_19;
	ChkList[2][i++]=ui->chk_3_20;
	ChkList[2][i++]=ui->chk_3_21;
	ChkList[2][i++]=ui->chk_3_22;
	ChkList[2][i++]=ui->chk_3_23;
	ChkList[2][i++]=ui->chk_3_24;
	ChkList[2][i++]=ui->chk_3_25;
	ChkList[2][i++]=ui->chk_3_26;
	ChkList[2][i++]=ui->chk_3_27;
	ChkList[2][i++]=ui->chk_3_28;
	ChkList[2][i++]=ui->chk_3_29;
	ChkList[2][i++]=ui->chk_3_30;
	ChkList[2][i++]=ui->chk_3_31;

	ChkList[2][i++]=ui->chk_3_32;
	ChkList[2][i++]=ui->chk_3_33;
	ChkList[2][i++]=ui->chk_3_34;
	ChkList[2][i++]=ui->chk_3_35;
	ChkList[2][i++]=ui->chk_3_36;
	ChkList[2][i++]=ui->chk_3_37;
	ChkList[2][i++]=ui->chk_3_38;
	ChkList[2][i++]=ui->chk_3_39;
	ChkList[2][i++]=ui->chk_3_40;
	ChkList[2][i++]=ui->chk_3_41;
	ChkList[2][i++]=ui->chk_3_42;
	ChkList[2][i++]=ui->chk_3_43;
	ChkList[2][i++]=ui->chk_3_44;
	ChkList[2][i++]=ui->chk_3_45;
	ChkList[2][i++]=ui->chk_3_46;
	ChkList[2][i++]=ui->chk_3_47;

	ChkList[2][i++]=ui->chk_3_48;
	ChkList[2][i++]=ui->chk_3_49;
	ChkList[2][i++]=ui->chk_3_50;
	ChkList[2][i++]=ui->chk_3_51;
	ChkList[2][i++]=ui->chk_3_52;
	ChkList[2][i++]=ui->chk_3_53;
	ChkList[2][i++]=ui->chk_3_54;
	ChkList[2][i++]=ui->chk_3_55;
	ChkList[2][i++]=ui->chk_3_56;
	ChkList[2][i++]=ui->chk_3_57;
	ChkList[2][i++]=ui->chk_3_58;
	ChkList[2][i++]=ui->chk_3_59;
	ChkList[2][i++]=ui->chk_3_60;
	ChkList[2][i++]=ui->chk_3_61;
	ChkList[2][i++]=ui->chk_3_62;
	ChkList[2][i++]=ui->chk_3_63;


	i=0;
	ChkList[3][i++]=ui->chk_4_0;
	ChkList[3][i++]=ui->chk_4_1;
	ChkList[3][i++]=ui->chk_4_2;
	ChkList[3][i++]=ui->chk_4_3;
	ChkList[3][i++]=ui->chk_4_4;
	ChkList[3][i++]=ui->chk_4_5;
	ChkList[3][i++]=ui->chk_4_6;
	ChkList[3][i++]=ui->chk_4_7;
	ChkList[3][i++]=ui->chk_4_8;
	ChkList[3][i++]=ui->chk_4_9;
	ChkList[3][i++]=ui->chk_4_10;
	ChkList[3][i++]=ui->chk_4_11;
	ChkList[3][i++]=ui->chk_4_12;
	ChkList[3][i++]=ui->chk_4_13;
	ChkList[3][i++]=ui->chk_4_14;
	ChkList[3][i++]=ui->chk_4_15;

	ChkList[3][i++]=ui->chk_4_16;
	ChkList[3][i++]=ui->chk_4_17;
	ChkList[3][i++]=ui->chk_4_18;
	ChkList[3][i++]=ui->chk_4_19;
	ChkList[3][i++]=ui->chk_4_20;
	ChkList[3][i++]=ui->chk_4_21;
	ChkList[3][i++]=ui->chk_4_22;
	ChkList[3][i++]=ui->chk_4_23;
	ChkList[3][i++]=ui->chk_4_24;
	ChkList[3][i++]=ui->chk_4_25;
	ChkList[3][i++]=ui->chk_4_26;
	ChkList[3][i++]=ui->chk_4_27;
	ChkList[3][i++]=ui->chk_4_28;
	ChkList[3][i++]=ui->chk_4_29;
	ChkList[3][i++]=ui->chk_4_30;
	ChkList[3][i++]=ui->chk_4_31;

	ChkList[3][i++]=ui->chk_4_32;
	ChkList[3][i++]=ui->chk_4_33;
	ChkList[3][i++]=ui->chk_4_34;
	ChkList[3][i++]=ui->chk_4_35;
	ChkList[3][i++]=ui->chk_4_36;
	ChkList[3][i++]=ui->chk_4_37;
	ChkList[3][i++]=ui->chk_4_38;
	ChkList[3][i++]=ui->chk_4_39;
	ChkList[3][i++]=ui->chk_4_40;
	ChkList[3][i++]=ui->chk_4_41;
	ChkList[3][i++]=ui->chk_4_42;
	ChkList[3][i++]=ui->chk_4_43;
	ChkList[3][i++]=ui->chk_4_44;
	ChkList[3][i++]=ui->chk_4_45;
	ChkList[3][i++]=ui->chk_4_46;
	ChkList[3][i++]=ui->chk_4_47;

	ChkList[3][i++]=ui->chk_4_48;
	ChkList[3][i++]=ui->chk_4_49;
	ChkList[3][i++]=ui->chk_4_50;
	ChkList[3][i++]=ui->chk_4_51;
	ChkList[3][i++]=ui->chk_4_52;
	ChkList[3][i++]=ui->chk_4_53;
	ChkList[3][i++]=ui->chk_4_54;
	ChkList[3][i++]=ui->chk_4_55;
	ChkList[3][i++]=ui->chk_4_56;
	ChkList[3][i++]=ui->chk_4_57;
	ChkList[3][i++]=ui->chk_4_58;
	ChkList[3][i++]=ui->chk_4_59;
	ChkList[3][i++]=ui->chk_4_60;
	ChkList[3][i++]=ui->chk_4_61;
	ChkList[3][i++]=ui->chk_4_62;
	ChkList[3][i++]=ui->chk_4_63;


	i=0;
	LabelList[0][i++]=ui->lb_1_0;
	LabelList[0][i++]=ui->lb_1_1;
	LabelList[0][i++]=ui->lb_1_2;
	LabelList[0][i++]=ui->lb_1_3;
	LabelList[0][i++]=ui->lb_1_4;
	LabelList[0][i++]=ui->lb_1_5;
	LabelList[0][i++]=ui->lb_1_6;
	LabelList[0][i++]=ui->lb_1_7;
	LabelList[0][i++]=ui->lb_1_8;
	LabelList[0][i++]=ui->lb_1_9;
	LabelList[0][i++]=ui->lb_1_10;
	LabelList[0][i++]=ui->lb_1_11;
	LabelList[0][i++]=ui->lb_1_12;
	LabelList[0][i++]=ui->lb_1_13;
	LabelList[0][i++]=ui->lb_1_14;
	LabelList[0][i++]=ui->lb_1_15;

	LabelList[0][i++]=ui->lb_1_16;
	LabelList[0][i++]=ui->lb_1_17;
	LabelList[0][i++]=ui->lb_1_18;
	LabelList[0][i++]=ui->lb_1_19;
	LabelList[0][i++]=ui->lb_1_20;
	LabelList[0][i++]=ui->lb_1_21;
	LabelList[0][i++]=ui->lb_1_22;
	LabelList[0][i++]=ui->lb_1_23;
	LabelList[0][i++]=ui->lb_1_24;
	LabelList[0][i++]=ui->lb_1_25;
	LabelList[0][i++]=ui->lb_1_26;
	LabelList[0][i++]=ui->lb_1_27;
	LabelList[0][i++]=ui->lb_1_28;
	LabelList[0][i++]=ui->lb_1_29;
	LabelList[0][i++]=ui->lb_1_30;
	LabelList[0][i++]=ui->lb_1_31;

	LabelList[0][i++]=ui->lb_1_32;
	LabelList[0][i++]=ui->lb_1_33;
	LabelList[0][i++]=ui->lb_1_34;
	LabelList[0][i++]=ui->lb_1_35;
	LabelList[0][i++]=ui->lb_1_36;
	LabelList[0][i++]=ui->lb_1_37;
	LabelList[0][i++]=ui->lb_1_38;
	LabelList[0][i++]=ui->lb_1_39;
	LabelList[0][i++]=ui->lb_1_40;
	LabelList[0][i++]=ui->lb_1_41;
	LabelList[0][i++]=ui->lb_1_42;
	LabelList[0][i++]=ui->lb_1_43;
	LabelList[0][i++]=ui->lb_1_44;
	LabelList[0][i++]=ui->lb_1_45;
	LabelList[0][i++]=ui->lb_1_46;
	LabelList[0][i++]=ui->lb_1_47;

	LabelList[0][i++]=ui->lb_1_48;
	LabelList[0][i++]=ui->lb_1_49;
	LabelList[0][i++]=ui->lb_1_50;
	LabelList[0][i++]=ui->lb_1_51;
	LabelList[0][i++]=ui->lb_1_52;
	LabelList[0][i++]=ui->lb_1_53;
	LabelList[0][i++]=ui->lb_1_54;
	LabelList[0][i++]=ui->lb_1_55;
	LabelList[0][i++]=ui->lb_1_56;
	LabelList[0][i++]=ui->lb_1_57;
	LabelList[0][i++]=ui->lb_1_58;
	LabelList[0][i++]=ui->lb_1_59;
	LabelList[0][i++]=ui->lb_1_60;
	LabelList[0][i++]=ui->lb_1_61;
	LabelList[0][i++]=ui->lb_1_62;
	LabelList[0][i++]=ui->lb_1_63;

	i=0;
	LabelList[1][i++]=ui->lb_2_0;
	LabelList[1][i++]=ui->lb_2_1;
	LabelList[1][i++]=ui->lb_2_2;
	LabelList[1][i++]=ui->lb_2_3;
	LabelList[1][i++]=ui->lb_2_4;
	LabelList[1][i++]=ui->lb_2_5;
	LabelList[1][i++]=ui->lb_2_6;
	LabelList[1][i++]=ui->lb_2_7;
	LabelList[1][i++]=ui->lb_2_8;
	LabelList[1][i++]=ui->lb_2_9;
	LabelList[1][i++]=ui->lb_2_10;
	LabelList[1][i++]=ui->lb_2_11;
	LabelList[1][i++]=ui->lb_2_12;
	LabelList[1][i++]=ui->lb_2_13;
	LabelList[1][i++]=ui->lb_2_14;
	LabelList[1][i++]=ui->lb_2_15;

	LabelList[1][i++]=ui->lb_2_16;
	LabelList[1][i++]=ui->lb_2_17;
	LabelList[1][i++]=ui->lb_2_18;
	LabelList[1][i++]=ui->lb_2_19;
	LabelList[1][i++]=ui->lb_2_20;
	LabelList[1][i++]=ui->lb_2_21;
	LabelList[1][i++]=ui->lb_2_22;
	LabelList[1][i++]=ui->lb_2_23;
	LabelList[1][i++]=ui->lb_2_24;
	LabelList[1][i++]=ui->lb_2_25;
	LabelList[1][i++]=ui->lb_2_26;
	LabelList[1][i++]=ui->lb_2_27;
	LabelList[1][i++]=ui->lb_2_28;
	LabelList[1][i++]=ui->lb_2_29;
	LabelList[1][i++]=ui->lb_2_30;
	LabelList[1][i++]=ui->lb_2_31;

	LabelList[1][i++]=ui->lb_2_32;
	LabelList[1][i++]=ui->lb_2_33;
	LabelList[1][i++]=ui->lb_2_34;
	LabelList[1][i++]=ui->lb_2_35;
	LabelList[1][i++]=ui->lb_2_36;
	LabelList[1][i++]=ui->lb_2_37;
	LabelList[1][i++]=ui->lb_2_38;
	LabelList[1][i++]=ui->lb_2_39;
	LabelList[1][i++]=ui->lb_2_40;
	LabelList[1][i++]=ui->lb_2_41;
	LabelList[1][i++]=ui->lb_2_42;
	LabelList[1][i++]=ui->lb_2_43;
	LabelList[1][i++]=ui->lb_2_44;
	LabelList[1][i++]=ui->lb_2_45;
	LabelList[1][i++]=ui->lb_2_46;
	LabelList[1][i++]=ui->lb_2_47;

	LabelList[1][i++]=ui->lb_2_48;
	LabelList[1][i++]=ui->lb_2_49;
	LabelList[1][i++]=ui->lb_2_50;
	LabelList[1][i++]=ui->lb_2_51;
	LabelList[1][i++]=ui->lb_2_52;
	LabelList[1][i++]=ui->lb_2_53;
	LabelList[1][i++]=ui->lb_2_54;
	LabelList[1][i++]=ui->lb_2_55;
	LabelList[1][i++]=ui->lb_2_56;
	LabelList[1][i++]=ui->lb_2_57;
	LabelList[1][i++]=ui->lb_2_58;
	LabelList[1][i++]=ui->lb_2_59;
	LabelList[1][i++]=ui->lb_2_60;
	LabelList[1][i++]=ui->lb_2_61;
	LabelList[1][i++]=ui->lb_2_62;
	LabelList[1][i++]=ui->lb_2_63;

	i=0;
	LabelList[2][i++]=ui->lb_3_0;
	LabelList[2][i++]=ui->lb_3_1;
	LabelList[2][i++]=ui->lb_3_2;
	LabelList[2][i++]=ui->lb_3_3;
	LabelList[2][i++]=ui->lb_3_4;
	LabelList[2][i++]=ui->lb_3_5;
	LabelList[2][i++]=ui->lb_3_6;
	LabelList[2][i++]=ui->lb_3_7;
	LabelList[2][i++]=ui->lb_3_8;
	LabelList[2][i++]=ui->lb_3_9;
	LabelList[2][i++]=ui->lb_3_10;
	LabelList[2][i++]=ui->lb_3_11;
	LabelList[2][i++]=ui->lb_3_12;
	LabelList[2][i++]=ui->lb_3_13;
	LabelList[2][i++]=ui->lb_3_14;
	LabelList[2][i++]=ui->lb_3_15;

	LabelList[2][i++]=ui->lb_3_16;
	LabelList[2][i++]=ui->lb_3_17;
	LabelList[2][i++]=ui->lb_3_18;
	LabelList[2][i++]=ui->lb_3_19;
	LabelList[2][i++]=ui->lb_3_20;
	LabelList[2][i++]=ui->lb_3_21;
	LabelList[2][i++]=ui->lb_3_22;
	LabelList[2][i++]=ui->lb_3_23;
	LabelList[2][i++]=ui->lb_3_24;
	LabelList[2][i++]=ui->lb_3_25;
	LabelList[2][i++]=ui->lb_3_26;
	LabelList[2][i++]=ui->lb_3_27;
	LabelList[2][i++]=ui->lb_3_28;
	LabelList[2][i++]=ui->lb_3_29;
	LabelList[2][i++]=ui->lb_3_30;
	LabelList[2][i++]=ui->lb_3_31;

	LabelList[2][i++]=ui->lb_3_32;
	LabelList[2][i++]=ui->lb_3_33;
	LabelList[2][i++]=ui->lb_3_34;
	LabelList[2][i++]=ui->lb_3_35;
	LabelList[2][i++]=ui->lb_3_36;
	LabelList[2][i++]=ui->lb_3_37;
	LabelList[2][i++]=ui->lb_3_38;
	LabelList[2][i++]=ui->lb_3_39;
	LabelList[2][i++]=ui->lb_3_40;
	LabelList[2][i++]=ui->lb_3_41;
	LabelList[2][i++]=ui->lb_3_42;
	LabelList[2][i++]=ui->lb_3_43;
	LabelList[2][i++]=ui->lb_3_44;
	LabelList[2][i++]=ui->lb_3_45;
	LabelList[2][i++]=ui->lb_3_46;
	LabelList[2][i++]=ui->lb_3_47;

	LabelList[2][i++]=ui->lb_3_48;
	LabelList[2][i++]=ui->lb_3_49;
	LabelList[2][i++]=ui->lb_3_50;
	LabelList[2][i++]=ui->lb_3_51;
	LabelList[2][i++]=ui->lb_3_52;
	LabelList[2][i++]=ui->lb_3_53;
	LabelList[2][i++]=ui->lb_3_54;
	LabelList[2][i++]=ui->lb_3_55;
	LabelList[2][i++]=ui->lb_3_56;
	LabelList[2][i++]=ui->lb_3_57;
	LabelList[2][i++]=ui->lb_3_58;
	LabelList[2][i++]=ui->lb_3_59;
	LabelList[2][i++]=ui->lb_3_60;
	LabelList[2][i++]=ui->lb_3_61;
	LabelList[2][i++]=ui->lb_3_62;
	LabelList[2][i++]=ui->lb_3_63;

	i=0;
	LabelList[3][i++]=ui->lb_4_0;
	LabelList[3][i++]=ui->lb_4_1;
	LabelList[3][i++]=ui->lb_4_2;
	LabelList[3][i++]=ui->lb_4_3;
	LabelList[3][i++]=ui->lb_4_4;
	LabelList[3][i++]=ui->lb_4_5;
	LabelList[3][i++]=ui->lb_4_6;
	LabelList[3][i++]=ui->lb_4_7;
	LabelList[3][i++]=ui->lb_4_8;
	LabelList[3][i++]=ui->lb_4_9;
	LabelList[3][i++]=ui->lb_4_10;
	LabelList[3][i++]=ui->lb_4_11;
	LabelList[3][i++]=ui->lb_4_12;
	LabelList[3][i++]=ui->lb_4_13;
	LabelList[3][i++]=ui->lb_4_14;
	LabelList[3][i++]=ui->lb_4_15;

	LabelList[3][i++]=ui->lb_4_16;
	LabelList[3][i++]=ui->lb_4_17;
	LabelList[3][i++]=ui->lb_4_18;
	LabelList[3][i++]=ui->lb_4_19;
	LabelList[3][i++]=ui->lb_4_20;
	LabelList[3][i++]=ui->lb_4_21;
	LabelList[3][i++]=ui->lb_4_22;
	LabelList[3][i++]=ui->lb_4_23;
	LabelList[3][i++]=ui->lb_4_24;
	LabelList[3][i++]=ui->lb_4_25;
	LabelList[3][i++]=ui->lb_4_26;
	LabelList[3][i++]=ui->lb_4_27;
	LabelList[3][i++]=ui->lb_4_28;
	LabelList[3][i++]=ui->lb_4_29;
	LabelList[3][i++]=ui->lb_4_30;
	LabelList[3][i++]=ui->lb_4_31;

	LabelList[3][i++]=ui->lb_4_32;
	LabelList[3][i++]=ui->lb_4_33;
	LabelList[3][i++]=ui->lb_4_34;
	LabelList[3][i++]=ui->lb_4_35;
	LabelList[3][i++]=ui->lb_4_36;
	LabelList[3][i++]=ui->lb_4_37;
	LabelList[3][i++]=ui->lb_4_38;
	LabelList[3][i++]=ui->lb_4_39;
	LabelList[3][i++]=ui->lb_4_40;
	LabelList[3][i++]=ui->lb_4_41;
	LabelList[3][i++]=ui->lb_4_42;
	LabelList[3][i++]=ui->lb_4_43;
	LabelList[3][i++]=ui->lb_4_44;
	LabelList[3][i++]=ui->lb_4_45;
	LabelList[3][i++]=ui->lb_4_46;
	LabelList[3][i++]=ui->lb_4_47;

	LabelList[3][i++]=ui->lb_4_48;
	LabelList[3][i++]=ui->lb_4_49;
	LabelList[3][i++]=ui->lb_4_50;
	LabelList[3][i++]=ui->lb_4_51;
	LabelList[3][i++]=ui->lb_4_52;
	LabelList[3][i++]=ui->lb_4_53;
	LabelList[3][i++]=ui->lb_4_54;
	LabelList[3][i++]=ui->lb_4_55;
	LabelList[3][i++]=ui->lb_4_56;
	LabelList[3][i++]=ui->lb_4_57;
	LabelList[3][i++]=ui->lb_4_58;
	LabelList[3][i++]=ui->lb_4_59;
	LabelList[3][i++]=ui->lb_4_60;
	LabelList[3][i++]=ui->lb_4_61;
	LabelList[3][i++]=ui->lb_4_62;
	LabelList[3][i++]=ui->lb_4_63;

	p->GetLayersBase()->InstallOperationLog(this);
}

LightDLL4PortForm::~LightDLL4PortForm()
{
    delete ui;
}

void	LightDLL4PortForm::showEvent(QShowEvent *)
{
	for(int i=0;i<LEDBARNUMB;i++){
		for(int j=0;j<64;j++){
			ChkList[i][j]->setChecked(false);
			int	n=BLight.LEDBright[i][j];
			LabelList[i][j]->setText(QString::number(n));
			BLight.SaveLEDBright[i][j]=n;
		}
	}
}

void LightDLL4PortForm::on_pushButtonSet_clicked()
{

}

void LightDLL4PortForm::on_tbTopLeft_clicked()
{
	for(int i=0;i<2;i++){
		for(int j=0;j<64;j++){
			ChkList[i][j]	->setChecked(true);
		}
	}
}

void LightDLL4PortForm::on_tbTopRight_clicked()
{
	for(int i=0;i<2;i++){
		for(int j=0;j<64;j++){
			ChkList[i+2][j]	->setChecked(true);
		}
	}
}

void LightDLL4PortForm::on_tb_1_clicked()
{
	for(int j=0;j<64;j++){
		ChkList[0][j]	->setChecked(true);
	}
}

void LightDLL4PortForm::on_tb_2_clicked()
{
	for(int j=0;j<64;j++){
		ChkList[1][j]	->setChecked(true);
	}
}

void LightDLL4PortForm::on_tb_3_clicked()
{
	for(int j=0;j<64;j++){
		ChkList[2][j]	->setChecked(true);
	}
}

void LightDLL4PortForm::on_tb_4_clicked()
{
	for(int j=0;j<64;j++){
		ChkList[3][j]	->setChecked(true);
	}
}

void LightDLL4PortForm::on_tbLeft_0_clicked()
{
	for(int i=0;i<2;i++){
		ChkList[i][0+0*16]	->setChecked(true);
		ChkList[i][0+1*16]	->setChecked(true);
		ChkList[i][0+2*16]	->setChecked(true);
		ChkList[i][0+3*16]	->setChecked(true);
	}
}

void LightDLL4PortForm::on_tbLeft_1_clicked()
{
	for(int i=0;i<2;i++){
		ChkList[i][1+0*16]	->setChecked(true);
		ChkList[i][1+1*16]	->setChecked(true);
		ChkList[i][1+2*16]	->setChecked(true);
		ChkList[i][1+3*16]	->setChecked(true);
	}
}

void LightDLL4PortForm::on_tbLeft_2_clicked()
{
	for(int i=0;i<2;i++){
		ChkList[i][2+0*16]	->setChecked(true);
		ChkList[i][2+1*16]	->setChecked(true);
		ChkList[i][2+2*16]	->setChecked(true);
		ChkList[i][2+3*16]	->setChecked(true);
	}
}

void LightDLL4PortForm::on_tbLeft_3_clicked()
{
	for(int i=0;i<2;i++){
		ChkList[i][3+0*16]	->setChecked(true);
		ChkList[i][3+1*16]	->setChecked(true);
		ChkList[i][3+2*16]	->setChecked(true);
		ChkList[i][3+3*16]	->setChecked(true);
	}
}

void LightDLL4PortForm::on_tbLeft_4_clicked()
{
	for(int i=0;i<2;i++){
		ChkList[i][4+0*16]	->setChecked(true);
		ChkList[i][4+1*16]	->setChecked(true);
		ChkList[i][4+2*16]	->setChecked(true);
		ChkList[i][4+3*16]	->setChecked(true);
	}
}

void LightDLL4PortForm::on_tbLeft_5_clicked()
{
	for(int i=0;i<2;i++){
		ChkList[i][5+0*16]	->setChecked(true);
		ChkList[i][5+1*16]	->setChecked(true);
		ChkList[i][5+2*16]	->setChecked(true);
		ChkList[i][5+3*16]	->setChecked(true);
	}
}

void LightDLL4PortForm::on_tbLeft_6_clicked()
{
	for(int i=0;i<2;i++){
		ChkList[i][6+0*16]	->setChecked(true);
		ChkList[i][6+1*16]	->setChecked(true);
		ChkList[i][6+2*16]	->setChecked(true);
		ChkList[i][6+3*16]	->setChecked(true);
	}
}

void LightDLL4PortForm::on_tbLeft_7_clicked()
{
	for(int i=0;i<2;i++){
		ChkList[i][7+0*16]	->setChecked(true);
		ChkList[i][7+1*16]	->setChecked(true);
		ChkList[i][7+2*16]	->setChecked(true);
		ChkList[i][7+3*16]	->setChecked(true);
	}
}

void LightDLL4PortForm::on_tbLeft_8_clicked()
{
	for(int i=0;i<2;i++){
		ChkList[i][8+0*16]	->setChecked(true);
		ChkList[i][8+1*16]	->setChecked(true);
		ChkList[i][8+2*16]	->setChecked(true);
		ChkList[i][8+3*16]	->setChecked(true);
	}
}

void LightDLL4PortForm::on_tbLeft_9_clicked()
{
	for(int i=0;i<2;i++){
		ChkList[i][9+0*16]	->setChecked(true);
		ChkList[i][9+1*16]	->setChecked(true);
		ChkList[i][9+2*16]	->setChecked(true);
		ChkList[i][9+3*16]	->setChecked(true);
	}
}

void LightDLL4PortForm::on_tbLeft_10_clicked()
{
	for(int i=0;i<2;i++){
		ChkList[i][10+0*16]	->setChecked(true);
		ChkList[i][10+1*16]	->setChecked(true);
		ChkList[i][10+2*16]	->setChecked(true);
		ChkList[i][10+3*16]	->setChecked(true);
	}
}

void LightDLL4PortForm::on_tbLeft_11_clicked()
{
	for(int i=0;i<2;i++){
		ChkList[i][11+0*16]	->setChecked(true);
		ChkList[i][11+1*16]	->setChecked(true);
		ChkList[i][11+2*16]	->setChecked(true);
		ChkList[i][11+3*16]	->setChecked(true);
	}
}

void LightDLL4PortForm::on_tbLeft_12_clicked()
{
	for(int i=0;i<2;i++){
		ChkList[i][12+0*16]	->setChecked(true);
		ChkList[i][12+1*16]	->setChecked(true);
		ChkList[i][12+2*16]	->setChecked(true);
		ChkList[i][12+3*16]	->setChecked(true);
	}
}

void LightDLL4PortForm::on_tbLeft_13_clicked()
{
	for(int i=0;i<2;i++){
		ChkList[i][13+0*16]	->setChecked(true);
		ChkList[i][13+1*16]	->setChecked(true);
		ChkList[i][13+2*16]	->setChecked(true);
		ChkList[i][13+3*16]	->setChecked(true);
	}
}

void LightDLL4PortForm::on_tbLeft_14_clicked()
{
	for(int i=0;i<2;i++){
		ChkList[i][14+0*16]	->setChecked(true);
		ChkList[i][14+1*16]	->setChecked(true);
		ChkList[i][14+2*16]	->setChecked(true);
		ChkList[i][14+3*16]	->setChecked(true);
	}
}

void LightDLL4PortForm::on_tbLeft_15_clicked()
{
	for(int i=0;i<2;i++){
		ChkList[i][15+0*16]	->setChecked(true);
		ChkList[i][15+1*16]	->setChecked(true);
		ChkList[i][15+2*16]	->setChecked(true);
		ChkList[i][15+3*16]	->setChecked(true);
	}
}

void LightDLL4PortForm::on_tbRight_0_clicked()
{
	for(int i=0;i<2;i++){
		ChkList[2+i][0+0*16]	->setChecked(true);
		ChkList[2+i][0+1*16]	->setChecked(true);
		ChkList[2+i][0+2*16]	->setChecked(true);
		ChkList[2+i][0+3*16]	->setChecked(true);
	}
}

void LightDLL4PortForm::on_tbRight_1_clicked()
{
	for(int i=0;i<2;i++){
		ChkList[2+i][1+0*16]	->setChecked(true);
		ChkList[2+i][1+1*16]	->setChecked(true);
		ChkList[2+i][1+2*16]	->setChecked(true);
		ChkList[2+i][1+3*16]	->setChecked(true);
	}
}

void LightDLL4PortForm::on_tbRight_2_clicked()
{
	for(int i=0;i<2;i++){
		ChkList[2+i][2+0*16]	->setChecked(true);
		ChkList[2+i][2+1*16]	->setChecked(true);
		ChkList[2+i][2+2*16]	->setChecked(true);
		ChkList[2+i][2+3*16]	->setChecked(true);
	}
}

void LightDLL4PortForm::on_tbRight_3_clicked()
{
	for(int i=0;i<2;i++){
		ChkList[2+i][3+0*16]	->setChecked(true);
		ChkList[2+i][3+1*16]	->setChecked(true);
		ChkList[2+i][3+2*16]	->setChecked(true);
		ChkList[2+i][3+3*16]	->setChecked(true);
	}
}

void LightDLL4PortForm::on_tbRight_4_clicked()
{
	for(int i=0;i<2;i++){
		ChkList[2+i][4+0*16]	->setChecked(true);
		ChkList[2+i][4+1*16]	->setChecked(true);
		ChkList[2+i][4+2*16]	->setChecked(true);
		ChkList[2+i][4+3*16]	->setChecked(true);
	}
}

void LightDLL4PortForm::on_tbRight_5_clicked()
{
	for(int i=0;i<2;i++){
		ChkList[2+i][5+0*16]	->setChecked(true);
		ChkList[2+i][5+1*16]	->setChecked(true);
		ChkList[2+i][5+2*16]	->setChecked(true);
		ChkList[2+i][5+3*16]	->setChecked(true);
	}
}

void LightDLL4PortForm::on_tbRight_6_clicked()
{
	for(int i=0;i<2;i++){
		ChkList[2+i][6+0*16]	->setChecked(true);
		ChkList[2+i][6+1*16]	->setChecked(true);
		ChkList[2+i][6+2*16]	->setChecked(true);
		ChkList[2+i][6+3*16]	->setChecked(true);
	}
}

void LightDLL4PortForm::on_tbRight_7_clicked()
{
	for(int i=0;i<2;i++){
		ChkList[2+i][7+0*16]	->setChecked(true);
		ChkList[2+i][7+1*16]	->setChecked(true);
		ChkList[2+i][7+2*16]	->setChecked(true);
		ChkList[2+i][7+3*16]	->setChecked(true);
	}
}

void LightDLL4PortForm::on_tbRight_8_clicked()
{
	for(int i=0;i<2;i++){
		ChkList[2+i][8+0*16]	->setChecked(true);
		ChkList[2+i][8+1*16]	->setChecked(true);
		ChkList[2+i][8+2*16]	->setChecked(true);
		ChkList[2+i][8+3*16]	->setChecked(true);
	}
}

void LightDLL4PortForm::on_tbRight_9_clicked()
{
	for(int i=0;i<2;i++){
		ChkList[2+i][9+0*16]	->setChecked(true);
		ChkList[2+i][9+1*16]	->setChecked(true);
		ChkList[2+i][9+2*16]	->setChecked(true);
		ChkList[2+i][9+3*16]	->setChecked(true);
	}
}

void LightDLL4PortForm::on_tbRight_10_clicked()
{
	for(int i=0;i<2;i++){
		ChkList[2+i][10+0*16]	->setChecked(true);
		ChkList[2+i][10+1*16]	->setChecked(true);
		ChkList[2+i][10+2*16]	->setChecked(true);
		ChkList[2+i][10+3*16]	->setChecked(true);
	}
}

void LightDLL4PortForm::on_tbRight_11_clicked()
{
	for(int i=0;i<2;i++){
		ChkList[2+i][11+0*16]	->setChecked(true);
		ChkList[2+i][11+1*16]	->setChecked(true);
		ChkList[2+i][11+2*16]	->setChecked(true);
		ChkList[2+i][11+3*16]	->setChecked(true);
	}
}

void LightDLL4PortForm::on_tbRight_12_clicked()
{
	for(int i=0;i<2;i++){
		ChkList[2+i][12+0*16]	->setChecked(true);
		ChkList[2+i][12+1*16]	->setChecked(true);
		ChkList[2+i][12+2*16]	->setChecked(true);
		ChkList[2+i][12+3*16]	->setChecked(true);
	}
}

void LightDLL4PortForm::on_tbRight_13_clicked()
{
	for(int i=0;i<2;i++){
		ChkList[2+i][13+0*16]	->setChecked(true);
		ChkList[2+i][13+1*16]	->setChecked(true);
		ChkList[2+i][13+2*16]	->setChecked(true);
		ChkList[2+i][13+3*16]	->setChecked(true);
	}
}

void LightDLL4PortForm::on_tbRight_14_clicked()
{
	for(int i=0;i<2;i++){
		ChkList[2+i][14+0*16]	->setChecked(true);
		ChkList[2+i][14+1*16]	->setChecked(true);
		ChkList[2+i][14+2*16]	->setChecked(true);
		ChkList[2+i][14+3*16]	->setChecked(true);
	}
}

void LightDLL4PortForm::on_tbRight_15_clicked()
{
	for(int i=0;i<2;i++){
		ChkList[2+i][15+0*16]	->setChecked(true);
		ChkList[2+i][15+1*16]	->setChecked(true);
		ChkList[2+i][15+2*16]	->setChecked(true);
		ChkList[2+i][15+3*16]	->setChecked(true);
	}
}

void LightDLL4PortForm::on_vsBrightness_valueChanged(int value)
{
	int	n=ui->vsBrightness->value();
	ui->sbBrightness->setValue(n);
}

void LightDLL4PortForm::on_pbTransport_clicked()
{
	ui->pgbLight->setValue(0);
	for(int i=0;i<LEDBARNUMB;i++){
		for(int j=0;j<LEDsNumb;j++){
			BLight.CLED[i].Change(j,BLight.SaveLEDBright[i][j]);
			BLight.CLED[i].OutData(j,BLight.Gain[i][j]);
		}
		ui->pgbLight->setValue(100*(i+1)/LEDBARNUMB);
	}
}

void LightDLL4PortForm::on_sbBrightness_valueChanged(int arg1)
{
	int	n=ui->sbBrightness->value();
	for(int i=0;i<LEDBARNUMB;i++){
		for(int j=0;j<64;j++){
			if(ChkList[i][j]->isChecked()==true){
				BLight.SaveLEDBright[i][j]=n;
				LabelList[i][j]->setText(QString::number(n));
			}
		}
	}
}

void LightDLL4PortForm::on_tbOnOff_clicked()
{
	if(ui->tbOnOff->isChecked()==true){
		ui->pgbLight->setValue(0);
		for(int i=0;i<LEDBARNUMB;i++){
			for(int j=0;j<LEDsNumb;j++){
				BLight.CLED[i].Change(j,BLight.SaveLEDBright[i][j]);
				BLight.CLED[i].OutData(j,BLight.Gain[i][j]);
			}
			ui->pgbLight->setValue(100*(i+1)/LEDBARNUMB);
		}
	}
	else{
		BLight.SetLighting(false);
	}
}

void LightDLL4PortForm::on_pbAllSelect_clicked()
{
	for(int i=0;i<LEDBARNUMB;i++){
		for(int j=0;j<64;j++){
			ChkList[i][j]	->setChecked(true);
		}
	}
}

void LightDLL4PortForm::on_pbClearSelect_clicked()
{
	for(int i=0;i<LEDBARNUMB;i++){
		for(int j=0;j<64;j++){
			ChkList[i][j]	->setChecked(false);
		}
	}
}

void LightDLL4PortForm::on_pbOK_clicked()
{
	for(int i=0;i<LEDBARNUMB;i++){
		for(int j=0;j<64;j++){
			BLight.LEDBright[i][j]=BLight.SaveLEDBright[i][j];
		}
	}
	accept();
}

void LightDLL4PortForm::on_pbCancel_clicked()
{
	reject();
}
