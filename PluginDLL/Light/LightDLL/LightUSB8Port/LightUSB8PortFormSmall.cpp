#include "LightUSB8PortFormSmall.h"
#include "ui_LightUSB8PortFormSmall.h"


LightUSB8PortFormSmall::LightUSB8PortFormSmall(LightControlFromUSB *iLight ,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LightUSB8PortFormSmall)
{
    ui->setupUi(this);

	BLight	=iLight;

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
	ChkList[4][i++]=ui->chk_5_0;
	ChkList[4][i++]=ui->chk_5_1;
	ChkList[4][i++]=ui->chk_5_2;
	ChkList[4][i++]=ui->chk_5_3;
	ChkList[4][i++]=ui->chk_5_4;
	ChkList[4][i++]=ui->chk_5_5;
	ChkList[4][i++]=ui->chk_5_6;
	ChkList[4][i++]=ui->chk_5_7;
	ChkList[4][i++]=ui->chk_5_8;
	ChkList[4][i++]=ui->chk_5_9;
	ChkList[4][i++]=ui->chk_5_10;
	ChkList[4][i++]=ui->chk_5_11;
	ChkList[4][i++]=ui->chk_5_12;
	ChkList[4][i++]=ui->chk_5_13;
	ChkList[4][i++]=ui->chk_5_14;
	ChkList[4][i++]=ui->chk_5_15;

	ChkList[4][i++]=ui->chk_5_16;
	ChkList[4][i++]=ui->chk_5_17;
	ChkList[4][i++]=ui->chk_5_18;
	ChkList[4][i++]=ui->chk_5_19;
	ChkList[4][i++]=ui->chk_5_20;
	ChkList[4][i++]=ui->chk_5_21;
	ChkList[4][i++]=ui->chk_5_22;
	ChkList[4][i++]=ui->chk_5_23;
	ChkList[4][i++]=ui->chk_5_24;
	ChkList[4][i++]=ui->chk_5_25;
	ChkList[4][i++]=ui->chk_5_26;
	ChkList[4][i++]=ui->chk_5_27;
	ChkList[4][i++]=ui->chk_5_28;
	ChkList[4][i++]=ui->chk_5_29;
	ChkList[4][i++]=ui->chk_5_30;
	ChkList[4][i++]=ui->chk_5_31;

	ChkList[4][i++]=ui->chk_5_32;
	ChkList[4][i++]=ui->chk_5_33;
	ChkList[4][i++]=ui->chk_5_34;
	ChkList[4][i++]=ui->chk_5_35;
	ChkList[4][i++]=ui->chk_5_36;
	ChkList[4][i++]=ui->chk_5_37;
	ChkList[4][i++]=ui->chk_5_38;
	ChkList[4][i++]=ui->chk_5_39;
	ChkList[4][i++]=ui->chk_5_40;
	ChkList[4][i++]=ui->chk_5_41;
	ChkList[4][i++]=ui->chk_5_42;
	ChkList[4][i++]=ui->chk_5_43;
	ChkList[4][i++]=ui->chk_5_44;
	ChkList[4][i++]=ui->chk_5_45;
	ChkList[4][i++]=ui->chk_5_46;
	ChkList[4][i++]=ui->chk_5_47;

	ChkList[4][i++]=ui->chk_5_48;
	ChkList[4][i++]=ui->chk_5_49;
	ChkList[4][i++]=ui->chk_5_50;
	ChkList[4][i++]=ui->chk_5_51;
	ChkList[4][i++]=ui->chk_5_52;
	ChkList[4][i++]=ui->chk_5_53;
	ChkList[4][i++]=ui->chk_5_54;
	ChkList[4][i++]=ui->chk_5_55;
	ChkList[4][i++]=ui->chk_5_56;
	ChkList[4][i++]=ui->chk_5_57;
	ChkList[4][i++]=ui->chk_5_58;
	ChkList[4][i++]=ui->chk_5_59;
	ChkList[4][i++]=ui->chk_5_60;
	ChkList[4][i++]=ui->chk_5_61;
	ChkList[4][i++]=ui->chk_5_62;
	ChkList[4][i++]=ui->chk_5_63;


	i=0;
	ChkList[5][i++]=ui->chk_6_0;
	ChkList[5][i++]=ui->chk_6_1;
	ChkList[5][i++]=ui->chk_6_2;
	ChkList[5][i++]=ui->chk_6_3;
	ChkList[5][i++]=ui->chk_6_4;
	ChkList[5][i++]=ui->chk_6_5;
	ChkList[5][i++]=ui->chk_6_6;
	ChkList[5][i++]=ui->chk_6_7;
	ChkList[5][i++]=ui->chk_6_8;
	ChkList[5][i++]=ui->chk_6_9;
	ChkList[5][i++]=ui->chk_6_10;
	ChkList[5][i++]=ui->chk_6_11;
	ChkList[5][i++]=ui->chk_6_12;
	ChkList[5][i++]=ui->chk_6_13;
	ChkList[5][i++]=ui->chk_6_14;
	ChkList[5][i++]=ui->chk_6_15;

	ChkList[5][i++]=ui->chk_6_16;
	ChkList[5][i++]=ui->chk_6_17;
	ChkList[5][i++]=ui->chk_6_18;
	ChkList[5][i++]=ui->chk_6_19;
	ChkList[5][i++]=ui->chk_6_20;
	ChkList[5][i++]=ui->chk_6_21;
	ChkList[5][i++]=ui->chk_6_22;
	ChkList[5][i++]=ui->chk_6_23;
	ChkList[5][i++]=ui->chk_6_24;
	ChkList[5][i++]=ui->chk_6_25;
	ChkList[5][i++]=ui->chk_6_26;
	ChkList[5][i++]=ui->chk_6_27;
	ChkList[5][i++]=ui->chk_6_28;
	ChkList[5][i++]=ui->chk_6_29;
	ChkList[5][i++]=ui->chk_6_30;
	ChkList[5][i++]=ui->chk_6_31;

	ChkList[5][i++]=ui->chk_6_32;
	ChkList[5][i++]=ui->chk_6_33;
	ChkList[5][i++]=ui->chk_6_34;
	ChkList[5][i++]=ui->chk_6_35;
	ChkList[5][i++]=ui->chk_6_36;
	ChkList[5][i++]=ui->chk_6_37;
	ChkList[5][i++]=ui->chk_6_38;
	ChkList[5][i++]=ui->chk_6_39;
	ChkList[5][i++]=ui->chk_6_40;
	ChkList[5][i++]=ui->chk_6_41;
	ChkList[5][i++]=ui->chk_6_42;
	ChkList[5][i++]=ui->chk_6_43;
	ChkList[5][i++]=ui->chk_6_44;
	ChkList[5][i++]=ui->chk_6_45;
	ChkList[5][i++]=ui->chk_6_46;
	ChkList[5][i++]=ui->chk_6_47;

	ChkList[5][i++]=ui->chk_6_48;
	ChkList[5][i++]=ui->chk_6_49;
	ChkList[5][i++]=ui->chk_6_50;
	ChkList[5][i++]=ui->chk_6_51;
	ChkList[5][i++]=ui->chk_6_52;
	ChkList[5][i++]=ui->chk_6_53;
	ChkList[5][i++]=ui->chk_6_54;
	ChkList[5][i++]=ui->chk_6_55;
	ChkList[5][i++]=ui->chk_6_56;
	ChkList[5][i++]=ui->chk_6_57;
	ChkList[5][i++]=ui->chk_6_58;
	ChkList[5][i++]=ui->chk_6_59;
	ChkList[5][i++]=ui->chk_6_60;
	ChkList[5][i++]=ui->chk_6_61;
	ChkList[5][i++]=ui->chk_6_62;
	ChkList[5][i++]=ui->chk_6_63;


	i=0;
	ChkList[6][i++]=ui->chk_7_0;
	ChkList[6][i++]=ui->chk_7_1;
	ChkList[6][i++]=ui->chk_7_2;
	ChkList[6][i++]=ui->chk_7_3;
	ChkList[6][i++]=ui->chk_7_4;
	ChkList[6][i++]=ui->chk_7_5;
	ChkList[6][i++]=ui->chk_7_6;
	ChkList[6][i++]=ui->chk_7_7;
	ChkList[6][i++]=ui->chk_7_8;
	ChkList[6][i++]=ui->chk_7_9;
	ChkList[6][i++]=ui->chk_7_10;
	ChkList[6][i++]=ui->chk_7_11;
	ChkList[6][i++]=ui->chk_7_12;
	ChkList[6][i++]=ui->chk_7_13;
	ChkList[6][i++]=ui->chk_7_14;
	ChkList[6][i++]=ui->chk_7_15;

	ChkList[6][i++]=ui->chk_7_16;
	ChkList[6][i++]=ui->chk_7_17;
	ChkList[6][i++]=ui->chk_7_18;
	ChkList[6][i++]=ui->chk_7_19;
	ChkList[6][i++]=ui->chk_7_20;
	ChkList[6][i++]=ui->chk_7_21;
	ChkList[6][i++]=ui->chk_7_22;
	ChkList[6][i++]=ui->chk_7_23;
	ChkList[6][i++]=ui->chk_7_24;
	ChkList[6][i++]=ui->chk_7_25;
	ChkList[6][i++]=ui->chk_7_26;
	ChkList[6][i++]=ui->chk_7_27;
	ChkList[6][i++]=ui->chk_7_28;
	ChkList[6][i++]=ui->chk_7_29;
	ChkList[6][i++]=ui->chk_7_30;
	ChkList[6][i++]=ui->chk_7_31;

	ChkList[6][i++]=ui->chk_7_32;
	ChkList[6][i++]=ui->chk_7_33;
	ChkList[6][i++]=ui->chk_7_34;
	ChkList[6][i++]=ui->chk_7_35;
	ChkList[6][i++]=ui->chk_7_36;
	ChkList[6][i++]=ui->chk_7_37;
	ChkList[6][i++]=ui->chk_7_38;
	ChkList[6][i++]=ui->chk_7_39;
	ChkList[6][i++]=ui->chk_7_40;
	ChkList[6][i++]=ui->chk_7_41;
	ChkList[6][i++]=ui->chk_7_42;
	ChkList[6][i++]=ui->chk_7_43;
	ChkList[6][i++]=ui->chk_7_44;
	ChkList[6][i++]=ui->chk_7_45;
	ChkList[6][i++]=ui->chk_7_46;
	ChkList[6][i++]=ui->chk_7_47;

	ChkList[6][i++]=ui->chk_7_48;
	ChkList[6][i++]=ui->chk_7_49;
	ChkList[6][i++]=ui->chk_7_50;
	ChkList[6][i++]=ui->chk_7_51;
	ChkList[6][i++]=ui->chk_7_52;
	ChkList[6][i++]=ui->chk_7_53;
	ChkList[6][i++]=ui->chk_7_54;
	ChkList[6][i++]=ui->chk_7_55;
	ChkList[6][i++]=ui->chk_7_56;
	ChkList[6][i++]=ui->chk_7_57;
	ChkList[6][i++]=ui->chk_7_58;
	ChkList[6][i++]=ui->chk_7_59;
	ChkList[6][i++]=ui->chk_7_60;
	ChkList[6][i++]=ui->chk_7_61;
	ChkList[6][i++]=ui->chk_7_62;
	ChkList[6][i++]=ui->chk_7_63;

	i=0;
	ChkList[7][i++]=ui->chk_8_0;
	ChkList[7][i++]=ui->chk_8_1;
	ChkList[7][i++]=ui->chk_8_2;
	ChkList[7][i++]=ui->chk_8_3;
	ChkList[7][i++]=ui->chk_8_4;
	ChkList[7][i++]=ui->chk_8_5;
	ChkList[7][i++]=ui->chk_8_6;
	ChkList[7][i++]=ui->chk_8_7;
	ChkList[7][i++]=ui->chk_8_8;
	ChkList[7][i++]=ui->chk_8_9;
	ChkList[7][i++]=ui->chk_8_10;
	ChkList[7][i++]=ui->chk_8_11;
	ChkList[7][i++]=ui->chk_8_12;
	ChkList[7][i++]=ui->chk_8_13;
	ChkList[7][i++]=ui->chk_8_14;
	ChkList[7][i++]=ui->chk_8_15;

	ChkList[7][i++]=ui->chk_8_16;
	ChkList[7][i++]=ui->chk_8_17;
	ChkList[7][i++]=ui->chk_8_18;
	ChkList[7][i++]=ui->chk_8_19;
	ChkList[7][i++]=ui->chk_8_20;
	ChkList[7][i++]=ui->chk_8_21;
	ChkList[7][i++]=ui->chk_8_22;
	ChkList[7][i++]=ui->chk_8_23;
	ChkList[7][i++]=ui->chk_8_24;
	ChkList[7][i++]=ui->chk_8_25;
	ChkList[7][i++]=ui->chk_8_26;
	ChkList[7][i++]=ui->chk_8_27;
	ChkList[7][i++]=ui->chk_8_28;
	ChkList[7][i++]=ui->chk_8_29;
	ChkList[7][i++]=ui->chk_8_30;
	ChkList[7][i++]=ui->chk_8_31;

	ChkList[7][i++]=ui->chk_8_32;
	ChkList[7][i++]=ui->chk_8_33;
	ChkList[7][i++]=ui->chk_8_34;
	ChkList[7][i++]=ui->chk_8_35;
	ChkList[7][i++]=ui->chk_8_36;
	ChkList[7][i++]=ui->chk_8_37;
	ChkList[7][i++]=ui->chk_8_38;
	ChkList[7][i++]=ui->chk_8_39;
	ChkList[7][i++]=ui->chk_8_40;
	ChkList[7][i++]=ui->chk_8_41;
	ChkList[7][i++]=ui->chk_8_42;
	ChkList[7][i++]=ui->chk_8_43;
	ChkList[7][i++]=ui->chk_8_44;
	ChkList[7][i++]=ui->chk_8_45;
	ChkList[7][i++]=ui->chk_8_46;
	ChkList[7][i++]=ui->chk_8_47;

	ChkList[7][i++]=ui->chk_8_48;
	ChkList[7][i++]=ui->chk_8_49;
	ChkList[7][i++]=ui->chk_8_50;
	ChkList[7][i++]=ui->chk_8_51;
	ChkList[7][i++]=ui->chk_8_52;
	ChkList[7][i++]=ui->chk_8_53;
	ChkList[7][i++]=ui->chk_8_54;
	ChkList[7][i++]=ui->chk_8_55;
	ChkList[7][i++]=ui->chk_8_56;
	ChkList[7][i++]=ui->chk_8_57;
	ChkList[7][i++]=ui->chk_8_58;
	ChkList[7][i++]=ui->chk_8_59;
	ChkList[7][i++]=ui->chk_8_60;
	ChkList[7][i++]=ui->chk_8_61;
	ChkList[7][i++]=ui->chk_8_62;
	ChkList[7][i++]=ui->chk_8_63;

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

	i=0;
	LabelList[4][i++]=ui->lb_5_0;
	LabelList[4][i++]=ui->lb_5_1;
	LabelList[4][i++]=ui->lb_5_2;
	LabelList[4][i++]=ui->lb_5_3;
	LabelList[4][i++]=ui->lb_5_4;
	LabelList[4][i++]=ui->lb_5_5;
	LabelList[4][i++]=ui->lb_5_6;
	LabelList[4][i++]=ui->lb_5_7;
	LabelList[4][i++]=ui->lb_5_8;
	LabelList[4][i++]=ui->lb_5_9;
	LabelList[4][i++]=ui->lb_5_10;
	LabelList[4][i++]=ui->lb_5_11;
	LabelList[4][i++]=ui->lb_5_12;
	LabelList[4][i++]=ui->lb_5_13;
	LabelList[4][i++]=ui->lb_5_14;
	LabelList[4][i++]=ui->lb_5_15;

	LabelList[4][i++]=ui->lb_5_16;
	LabelList[4][i++]=ui->lb_5_17;
	LabelList[4][i++]=ui->lb_5_18;
	LabelList[4][i++]=ui->lb_5_19;
	LabelList[4][i++]=ui->lb_5_20;
	LabelList[4][i++]=ui->lb_5_21;
	LabelList[4][i++]=ui->lb_5_22;
	LabelList[4][i++]=ui->lb_5_23;
	LabelList[4][i++]=ui->lb_5_24;
	LabelList[4][i++]=ui->lb_5_25;
	LabelList[4][i++]=ui->lb_5_26;
	LabelList[4][i++]=ui->lb_5_27;
	LabelList[4][i++]=ui->lb_5_28;
	LabelList[4][i++]=ui->lb_5_29;
	LabelList[4][i++]=ui->lb_5_30;
	LabelList[4][i++]=ui->lb_5_31;

	LabelList[4][i++]=ui->lb_5_32;
	LabelList[4][i++]=ui->lb_5_33;
	LabelList[4][i++]=ui->lb_5_34;
	LabelList[4][i++]=ui->lb_5_35;
	LabelList[4][i++]=ui->lb_5_36;
	LabelList[4][i++]=ui->lb_5_37;
	LabelList[4][i++]=ui->lb_5_38;
	LabelList[4][i++]=ui->lb_5_39;
	LabelList[4][i++]=ui->lb_5_40;
	LabelList[4][i++]=ui->lb_5_41;
	LabelList[4][i++]=ui->lb_5_42;
	LabelList[4][i++]=ui->lb_5_43;
	LabelList[4][i++]=ui->lb_5_44;
	LabelList[4][i++]=ui->lb_5_45;
	LabelList[4][i++]=ui->lb_5_46;
	LabelList[4][i++]=ui->lb_5_47;

	LabelList[4][i++]=ui->lb_5_48;
	LabelList[4][i++]=ui->lb_5_49;
	LabelList[4][i++]=ui->lb_5_50;
	LabelList[4][i++]=ui->lb_5_51;
	LabelList[4][i++]=ui->lb_5_52;
	LabelList[4][i++]=ui->lb_5_53;
	LabelList[4][i++]=ui->lb_5_54;
	LabelList[4][i++]=ui->lb_5_55;
	LabelList[4][i++]=ui->lb_5_56;
	LabelList[4][i++]=ui->lb_5_57;
	LabelList[4][i++]=ui->lb_5_58;
	LabelList[4][i++]=ui->lb_5_59;
	LabelList[4][i++]=ui->lb_5_60;
	LabelList[4][i++]=ui->lb_5_61;
	LabelList[4][i++]=ui->lb_5_62;
	LabelList[4][i++]=ui->lb_5_63;

	i=0;
	LabelList[5][i++]=ui->lb_6_0;
	LabelList[5][i++]=ui->lb_6_1;
	LabelList[5][i++]=ui->lb_6_2;
	LabelList[5][i++]=ui->lb_6_3;
	LabelList[5][i++]=ui->lb_6_4;
	LabelList[5][i++]=ui->lb_6_5;
	LabelList[5][i++]=ui->lb_6_6;
	LabelList[5][i++]=ui->lb_6_7;
	LabelList[5][i++]=ui->lb_6_8;
	LabelList[5][i++]=ui->lb_6_9;
	LabelList[5][i++]=ui->lb_6_10;
	LabelList[5][i++]=ui->lb_6_11;
	LabelList[5][i++]=ui->lb_6_12;
	LabelList[5][i++]=ui->lb_6_13;
	LabelList[5][i++]=ui->lb_6_14;
	LabelList[5][i++]=ui->lb_6_15;

	LabelList[5][i++]=ui->lb_6_16;
	LabelList[5][i++]=ui->lb_6_17;
	LabelList[5][i++]=ui->lb_6_18;
	LabelList[5][i++]=ui->lb_6_19;
	LabelList[5][i++]=ui->lb_6_20;
	LabelList[5][i++]=ui->lb_6_21;
	LabelList[5][i++]=ui->lb_6_22;
	LabelList[5][i++]=ui->lb_6_23;
	LabelList[5][i++]=ui->lb_6_24;
	LabelList[5][i++]=ui->lb_6_25;
	LabelList[5][i++]=ui->lb_6_26;
	LabelList[5][i++]=ui->lb_6_27;
	LabelList[5][i++]=ui->lb_6_28;
	LabelList[5][i++]=ui->lb_6_29;
	LabelList[5][i++]=ui->lb_6_30;
	LabelList[5][i++]=ui->lb_6_31;

	LabelList[5][i++]=ui->lb_6_32;
	LabelList[5][i++]=ui->lb_6_33;
	LabelList[5][i++]=ui->lb_6_34;
	LabelList[5][i++]=ui->lb_6_35;
	LabelList[5][i++]=ui->lb_6_36;
	LabelList[5][i++]=ui->lb_6_37;
	LabelList[5][i++]=ui->lb_6_38;
	LabelList[5][i++]=ui->lb_6_39;
	LabelList[5][i++]=ui->lb_6_40;
	LabelList[5][i++]=ui->lb_6_41;
	LabelList[5][i++]=ui->lb_6_42;
	LabelList[5][i++]=ui->lb_6_43;
	LabelList[5][i++]=ui->lb_6_44;
	LabelList[5][i++]=ui->lb_6_45;
	LabelList[5][i++]=ui->lb_6_46;
	LabelList[5][i++]=ui->lb_6_47;

	LabelList[5][i++]=ui->lb_6_48;
	LabelList[5][i++]=ui->lb_6_49;
	LabelList[5][i++]=ui->lb_6_50;
	LabelList[5][i++]=ui->lb_6_51;
	LabelList[5][i++]=ui->lb_6_52;
	LabelList[5][i++]=ui->lb_6_53;
	LabelList[5][i++]=ui->lb_6_54;
	LabelList[5][i++]=ui->lb_6_55;
	LabelList[5][i++]=ui->lb_6_56;
	LabelList[5][i++]=ui->lb_6_57;
	LabelList[5][i++]=ui->lb_6_58;
	LabelList[5][i++]=ui->lb_6_59;
	LabelList[5][i++]=ui->lb_6_60;
	LabelList[5][i++]=ui->lb_6_61;
	LabelList[5][i++]=ui->lb_6_62;
	LabelList[5][i++]=ui->lb_6_63;

	i=0;
	LabelList[6][i++]=ui->lb_7_0;
	LabelList[6][i++]=ui->lb_7_1;
	LabelList[6][i++]=ui->lb_7_2;
	LabelList[6][i++]=ui->lb_7_3;
	LabelList[6][i++]=ui->lb_7_4;
	LabelList[6][i++]=ui->lb_7_5;
	LabelList[6][i++]=ui->lb_7_6;
	LabelList[6][i++]=ui->lb_7_7;
	LabelList[6][i++]=ui->lb_7_8;
	LabelList[6][i++]=ui->lb_7_9;
	LabelList[6][i++]=ui->lb_7_10;
	LabelList[6][i++]=ui->lb_7_11;
	LabelList[6][i++]=ui->lb_7_12;
	LabelList[6][i++]=ui->lb_7_13;
	LabelList[6][i++]=ui->lb_7_14;
	LabelList[6][i++]=ui->lb_7_15;

	LabelList[6][i++]=ui->lb_7_16;
	LabelList[6][i++]=ui->lb_7_17;
	LabelList[6][i++]=ui->lb_7_18;
	LabelList[6][i++]=ui->lb_7_19;
	LabelList[6][i++]=ui->lb_7_20;
	LabelList[6][i++]=ui->lb_7_21;
	LabelList[6][i++]=ui->lb_7_22;
	LabelList[6][i++]=ui->lb_7_23;
	LabelList[6][i++]=ui->lb_7_24;
	LabelList[6][i++]=ui->lb_7_25;
	LabelList[6][i++]=ui->lb_7_26;
	LabelList[6][i++]=ui->lb_7_27;
	LabelList[6][i++]=ui->lb_7_28;
	LabelList[6][i++]=ui->lb_7_29;
	LabelList[6][i++]=ui->lb_7_30;
	LabelList[6][i++]=ui->lb_7_31;

	LabelList[6][i++]=ui->lb_7_32;
	LabelList[6][i++]=ui->lb_7_33;
	LabelList[6][i++]=ui->lb_7_34;
	LabelList[6][i++]=ui->lb_7_35;
	LabelList[6][i++]=ui->lb_7_36;
	LabelList[6][i++]=ui->lb_7_37;
	LabelList[6][i++]=ui->lb_7_38;
	LabelList[6][i++]=ui->lb_7_39;
	LabelList[6][i++]=ui->lb_7_40;
	LabelList[6][i++]=ui->lb_7_41;
	LabelList[6][i++]=ui->lb_7_42;
	LabelList[6][i++]=ui->lb_7_43;
	LabelList[6][i++]=ui->lb_7_44;
	LabelList[6][i++]=ui->lb_7_45;
	LabelList[6][i++]=ui->lb_7_46;
	LabelList[6][i++]=ui->lb_7_47;

	LabelList[6][i++]=ui->lb_7_48;
	LabelList[6][i++]=ui->lb_7_49;
	LabelList[6][i++]=ui->lb_7_50;
	LabelList[6][i++]=ui->lb_7_51;
	LabelList[6][i++]=ui->lb_7_52;
	LabelList[6][i++]=ui->lb_7_53;
	LabelList[6][i++]=ui->lb_7_54;
	LabelList[6][i++]=ui->lb_7_55;
	LabelList[6][i++]=ui->lb_7_56;
	LabelList[6][i++]=ui->lb_7_57;
	LabelList[6][i++]=ui->lb_7_58;
	LabelList[6][i++]=ui->lb_7_59;
	LabelList[6][i++]=ui->lb_7_60;
	LabelList[6][i++]=ui->lb_7_61;
	LabelList[6][i++]=ui->lb_7_62;
	LabelList[6][i++]=ui->lb_7_63;

	i=0;
	LabelList[7][i++]=ui->lb_8_0;
	LabelList[7][i++]=ui->lb_8_1;
	LabelList[7][i++]=ui->lb_8_2;
	LabelList[7][i++]=ui->lb_8_3;
	LabelList[7][i++]=ui->lb_8_4;
	LabelList[7][i++]=ui->lb_8_5;
	LabelList[7][i++]=ui->lb_8_6;
	LabelList[7][i++]=ui->lb_8_7;
	LabelList[7][i++]=ui->lb_8_8;
	LabelList[7][i++]=ui->lb_8_9;
	LabelList[7][i++]=ui->lb_8_10;
	LabelList[7][i++]=ui->lb_8_11;
	LabelList[7][i++]=ui->lb_8_12;
	LabelList[7][i++]=ui->lb_8_13;
	LabelList[7][i++]=ui->lb_8_14;
	LabelList[7][i++]=ui->lb_8_15;

	LabelList[7][i++]=ui->lb_8_16;
	LabelList[7][i++]=ui->lb_8_17;
	LabelList[7][i++]=ui->lb_8_18;
	LabelList[7][i++]=ui->lb_8_19;
	LabelList[7][i++]=ui->lb_8_20;
	LabelList[7][i++]=ui->lb_8_21;
	LabelList[7][i++]=ui->lb_8_22;
	LabelList[7][i++]=ui->lb_8_23;
	LabelList[7][i++]=ui->lb_8_24;
	LabelList[7][i++]=ui->lb_8_25;
	LabelList[7][i++]=ui->lb_8_26;
	LabelList[7][i++]=ui->lb_8_27;
	LabelList[7][i++]=ui->lb_8_28;
	LabelList[7][i++]=ui->lb_8_29;
	LabelList[7][i++]=ui->lb_8_30;
	LabelList[7][i++]=ui->lb_8_31;

	LabelList[7][i++]=ui->lb_8_32;
	LabelList[7][i++]=ui->lb_8_33;
	LabelList[7][i++]=ui->lb_8_34;
	LabelList[7][i++]=ui->lb_8_35;
	LabelList[7][i++]=ui->lb_8_36;
	LabelList[7][i++]=ui->lb_8_37;
	LabelList[7][i++]=ui->lb_8_38;
	LabelList[7][i++]=ui->lb_8_39;
	LabelList[7][i++]=ui->lb_8_40;
	LabelList[7][i++]=ui->lb_8_41;
	LabelList[7][i++]=ui->lb_8_42;
	LabelList[7][i++]=ui->lb_8_43;
	LabelList[7][i++]=ui->lb_8_44;
	LabelList[7][i++]=ui->lb_8_45;
	LabelList[7][i++]=ui->lb_8_46;
	LabelList[7][i++]=ui->lb_8_47;

	LabelList[7][i++]=ui->lb_8_48;
	LabelList[7][i++]=ui->lb_8_49;
	LabelList[7][i++]=ui->lb_8_50;
	LabelList[7][i++]=ui->lb_8_51;
	LabelList[7][i++]=ui->lb_8_52;
	LabelList[7][i++]=ui->lb_8_53;
	LabelList[7][i++]=ui->lb_8_54;
	LabelList[7][i++]=ui->lb_8_55;
	LabelList[7][i++]=ui->lb_8_56;
	LabelList[7][i++]=ui->lb_8_57;
	LabelList[7][i++]=ui->lb_8_58;
	LabelList[7][i++]=ui->lb_8_59;
	LabelList[7][i++]=ui->lb_8_60;
	LabelList[7][i++]=ui->lb_8_61;
	LabelList[7][i++]=ui->lb_8_62;
	LabelList[7][i++]=ui->lb_8_63;
	on_tbOnOff_clicked();

	iLight->GetLayersBase()->InstallOperationLog(this);
}

LightUSB8PortFormSmall::~LightUSB8PortFormSmall()
{
    delete ui;
	//delete	BLight;
	//BLight=NULL;
}
void	LightUSB8PortFormSmall::resizeEvent ( QResizeEvent * event )
{
	ui->frame->move(width()-ui->frame->width(),0);
}

void	LightUSB8PortFormSmall::showEvent(QShowEvent *)
{
	for(int i=0;i<8;i++){
		for(int j=0;j<64;j++){
			ChkList[i][j]->setChecked(false);
			int	n=BLight->GetLEDBrightness(i,j);
			LabelList[i][j]->setText(QString::number(n));
		}
	}
	ui->le_1->setText(BLight->GetBoardComment(0));
	ui->le_2->setText(BLight->GetBoardComment(1));
	ui->le_3->setText(BLight->GetBoardComment(2));
	ui->le_4->setText(BLight->GetBoardComment(3));
	ui->le_5->setText(BLight->GetBoardComment(4));
	ui->le_6->setText(BLight->GetBoardComment(5));
	ui->le_7->setText(BLight->GetBoardComment(6));
	ui->le_8->setText(BLight->GetBoardComment(7));
}
void LightUSB8PortFormSmall::on_tbTopLeft_clicked()
{
	int	CountOff=0;
	for(int i=0;i<4;i++){
		for(int j=0;j<64;j++){
			if(ChkList[i][j]	->isChecked()==false){
				CountOff++;
			}
		}
	}
	
	if(CountOff==0){
		for(int i=0;i<4;i++){
			for(int j=0;j<64;j++){
				ChkList[i][j]	->setChecked(false);
			}
		}
	}
	else{
		for(int i=0;i<4;i++){
			for(int j=0;j<64;j++){
				ChkList[i][j]	->setChecked(true);
			}
		}
	}
}

void LightUSB8PortFormSmall::on_tbTopRight_clicked()
{
	int	CountOff=0;
	for(int i=0;i<4;i++){
		for(int j=0;j<64;j++){
			if(ChkList[i+4][j]	->isChecked()==false){
				CountOff++;
			}
		}
	}
	
	if(CountOff==0){
		for(int i=0;i<4;i++){
			for(int j=0;j<64;j++){
				ChkList[i+4][j]	->setChecked(false);
			}
		}
	}
	else{
		for(int i=0;i<4;i++){
			for(int j=0;j<64;j++){
				ChkList[i+4][j]	->setChecked(true);
			}
		}
	}
}

void LightUSB8PortFormSmall::on_tb_1_clicked()
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

void LightUSB8PortFormSmall::on_tb_2_clicked()
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

void LightUSB8PortFormSmall::on_tb_3_clicked()
{
	int	CountOff=0;
	for(int j=0;j<64;j++){
		if(ChkList[2][j]	->isChecked()==false){
			CountOff++;
		}
	}
	if(CountOff==0){
		for(int j=0;j<64;j++){
			ChkList[2][j]	->setChecked(false);
		}
	}
	else{
		for(int j=0;j<64;j++){
			ChkList[2][j]	->setChecked(true);
		}
	}
}

void LightUSB8PortFormSmall::on_tb_4_clicked()
{
	int	CountOff=0;
	for(int j=0;j<64;j++){
		if(ChkList[3][j]	->isChecked()==false){
			CountOff++;
		}
	}
	if(CountOff==0){
		for(int j=0;j<64;j++){
			ChkList[3][j]	->setChecked(false);
		}
	}
	else{
		for(int j=0;j<64;j++){
			ChkList[3][j]	->setChecked(true);
		}
	}
}

void LightUSB8PortFormSmall::on_tb_5_clicked()
{
	int	CountOff=0;
	for(int j=0;j<64;j++){
		if(ChkList[4][j]	->isChecked()==false){
			CountOff++;
		}
	}
	if(CountOff==0){
		for(int j=0;j<64;j++){
			ChkList[4][j]	->setChecked(false);
		}
	}
	else{
		for(int j=0;j<64;j++){
			ChkList[4][j]	->setChecked(true);
		}
	}
}

void LightUSB8PortFormSmall::on_tb_6_clicked()
{
	int	CountOff=0;
	for(int j=0;j<64;j++){
		if(ChkList[5][j]	->isChecked()==false){
			CountOff++;
		}
	}
	if(CountOff==0){
		for(int j=0;j<64;j++){
			ChkList[5][j]	->setChecked(false);
		}
	}
	else{
		for(int j=0;j<64;j++){
			ChkList[5][j]	->setChecked(true);
		}
	}
}

void LightUSB8PortFormSmall::on_tb_7_clicked()
{
	int	CountOff=0;
	for(int j=0;j<64;j++){
		if(ChkList[6][j]	->isChecked()==false){
			CountOff++;
		}
	}
	if(CountOff==0){
		for(int j=0;j<64;j++){
			ChkList[6][j]	->setChecked(false);
		}
	}
	else{
		for(int j=0;j<64;j++){
			ChkList[6][j]	->setChecked(true);
		}
	}
}

void LightUSB8PortFormSmall::on_tb_8_clicked()
{
	int	CountOff=0;
	for(int j=0;j<64;j++){
		if(ChkList[7][j]	->isChecked()==false){
			CountOff++;
		}
	}
	if(CountOff==0){
		for(int j=0;j<64;j++){
			ChkList[7][j]	->setChecked(false);
		}
	}
	else{
		for(int j=0;j<64;j++){
			ChkList[7][j]	->setChecked(true);
		}
	}
}

void LightUSB8PortFormSmall::on_tbLeft_0_clicked()
{
	for(int i=0;i<4;i++){
		ChkList[i][0+0*16]	->setChecked(true);
		ChkList[i][0+1*16]	->setChecked(true);
		ChkList[i][0+2*16]	->setChecked(true);
		ChkList[i][0+3*16]	->setChecked(true);
	}
}

void LightUSB8PortFormSmall::on_tbLeft_1_clicked()
{
	for(int i=0;i<4;i++){
		ChkList[i][1+0*16]	->setChecked(true);
		ChkList[i][1+1*16]	->setChecked(true);
		ChkList[i][1+2*16]	->setChecked(true);
		ChkList[i][1+3*16]	->setChecked(true);
	}
}

void LightUSB8PortFormSmall::on_tbLeft_2_clicked()
{
	for(int i=0;i<4;i++){
		ChkList[i][2+0*16]	->setChecked(true);
		ChkList[i][2+1*16]	->setChecked(true);
		ChkList[i][2+2*16]	->setChecked(true);
		ChkList[i][2+3*16]	->setChecked(true);
	}
}

void LightUSB8PortFormSmall::on_tbLeft_3_clicked()
{
	for(int i=0;i<4;i++){
		ChkList[i][3+0*16]	->setChecked(true);
		ChkList[i][3+1*16]	->setChecked(true);
		ChkList[i][3+2*16]	->setChecked(true);
		ChkList[i][3+3*16]	->setChecked(true);
	}
}

void LightUSB8PortFormSmall::on_tbLeft_4_clicked()
{
	for(int i=0;i<4;i++){
		ChkList[i][4+0*16]	->setChecked(true);
		ChkList[i][4+1*16]	->setChecked(true);
		ChkList[i][4+2*16]	->setChecked(true);
		ChkList[i][4+3*16]	->setChecked(true);
	}
}

void LightUSB8PortFormSmall::on_tbLeft_5_clicked()
{
	for(int i=0;i<4;i++){
		ChkList[i][5+0*16]	->setChecked(true);
		ChkList[i][5+1*16]	->setChecked(true);
		ChkList[i][5+2*16]	->setChecked(true);
		ChkList[i][5+3*16]	->setChecked(true);
	}
}

void LightUSB8PortFormSmall::on_tbLeft_6_clicked()
{	
	for(int i=0;i<4;i++){
		ChkList[i][6+0*16]	->setChecked(true);
		ChkList[i][6+1*16]	->setChecked(true);
		ChkList[i][6+2*16]	->setChecked(true);
		ChkList[i][6+3*16]	->setChecked(true);
	}
}

void LightUSB8PortFormSmall::on_tbLeft_7_clicked()
{
	for(int i=0;i<4;i++){
		ChkList[i][7+0*16]	->setChecked(true);
		ChkList[i][7+1*16]	->setChecked(true);
		ChkList[i][7+2*16]	->setChecked(true);
		ChkList[i][7+3*16]	->setChecked(true);
	}
}

void LightUSB8PortFormSmall::on_tbLeft_8_clicked()
{
	for(int i=0;i<4;i++){
		ChkList[i][8+0*16]	->setChecked(true);
		ChkList[i][8+1*16]	->setChecked(true);
		ChkList[i][8+2*16]	->setChecked(true);
		ChkList[i][8+3*16]	->setChecked(true);
	}
}

void LightUSB8PortFormSmall::on_tbLeft_9_clicked()
{
	for(int i=0;i<4;i++){
		ChkList[i][9+0*16]	->setChecked(true);
		ChkList[i][9+1*16]	->setChecked(true);
		ChkList[i][9+2*16]	->setChecked(true);
		ChkList[i][9+3*16]	->setChecked(true);
	}
}

void LightUSB8PortFormSmall::on_tbLeft_10_clicked()
{
	for(int i=0;i<4;i++){
		ChkList[i][10+0*16]	->setChecked(true);
		ChkList[i][10+1*16]	->setChecked(true);
		ChkList[i][10+2*16]	->setChecked(true);
		ChkList[i][10+3*16]	->setChecked(true);
	}
}

void LightUSB8PortFormSmall::on_tbLeft_11_clicked()
{
	for(int i=0;i<4;i++){
		ChkList[i][11+0*16]	->setChecked(true);
		ChkList[i][11+1*16]	->setChecked(true);
		ChkList[i][11+2*16]	->setChecked(true);
		ChkList[i][11+3*16]	->setChecked(true);
	}
}

void LightUSB8PortFormSmall::on_tbLeft_12_clicked()
{
	for(int i=0;i<4;i++){
		ChkList[i][12+0*16]	->setChecked(true);
		ChkList[i][12+1*16]	->setChecked(true);
		ChkList[i][12+2*16]	->setChecked(true);
		ChkList[i][12+3*16]	->setChecked(true);
	}
}

void LightUSB8PortFormSmall::on_tbLeft_13_clicked()
{
	for(int i=0;i<4;i++){
		ChkList[i][13+0*16]	->setChecked(true);
		ChkList[i][13+1*16]	->setChecked(true);
		ChkList[i][13+2*16]	->setChecked(true);
		ChkList[i][13+3*16]	->setChecked(true);
	}
}

void LightUSB8PortFormSmall::on_tbLeft_14_clicked()
{
	for(int i=0;i<4;i++){
		ChkList[i][14+0*16]	->setChecked(true);
		ChkList[i][14+1*16]	->setChecked(true);
		ChkList[i][14+2*16]	->setChecked(true);
		ChkList[i][14+3*16]	->setChecked(true);
	}
}

void LightUSB8PortFormSmall::on_tbLeft_15_clicked()
{
	for(int i=0;i<4;i++){
		ChkList[i][15+0*16]	->setChecked(true);
		ChkList[i][15+1*16]	->setChecked(true);
		ChkList[i][15+2*16]	->setChecked(true);
		ChkList[i][15+3*16]	->setChecked(true);
	}
}

void LightUSB8PortFormSmall::on_tbRight_0_clicked()
{
	for(int i=0;i<4;i++){
		ChkList[4+i][0+0*16]	->setChecked(true);
		ChkList[4+i][0+1*16]	->setChecked(true);
		ChkList[4+i][0+2*16]	->setChecked(true);
		ChkList[4+i][0+3*16]	->setChecked(true);
	}
}

void LightUSB8PortFormSmall::on_tbRight_1_clicked()
{
	for(int i=0;i<4;i++){
		ChkList[4+i][1+0*16]	->setChecked(true);
		ChkList[4+i][1+1*16]	->setChecked(true);
		ChkList[4+i][1+2*16]	->setChecked(true);
		ChkList[4+i][1+3*16]	->setChecked(true);
	}
}

void LightUSB8PortFormSmall::on_tbRight_2_clicked()
{
	for(int i=0;i<4;i++){
		ChkList[4+i][2+0*16]	->setChecked(true);
		ChkList[4+i][2+1*16]	->setChecked(true);
		ChkList[4+i][2+2*16]	->setChecked(true);
		ChkList[4+i][2+3*16]	->setChecked(true);
	}
}

void LightUSB8PortFormSmall::on_tbRight_3_clicked()
{
	for(int i=0;i<4;i++){
		ChkList[4+i][3+0*16]	->setChecked(true);
		ChkList[4+i][3+1*16]	->setChecked(true);
		ChkList[4+i][3+2*16]	->setChecked(true);
		ChkList[4+i][3+3*16]	->setChecked(true);
	}
}

void LightUSB8PortFormSmall::on_tbRight_4_clicked()
{
	for(int i=0;i<4;i++){
		ChkList[4+i][4+0*16]	->setChecked(true);
		ChkList[4+i][4+1*16]	->setChecked(true);
		ChkList[4+i][4+2*16]	->setChecked(true);
		ChkList[4+i][4+3*16]	->setChecked(true);
	}
}

void LightUSB8PortFormSmall::on_tbRight_5_clicked()
{
	for(int i=0;i<4;i++){
		ChkList[4+i][5+0*16]	->setChecked(true);
		ChkList[4+i][5+1*16]	->setChecked(true);
		ChkList[4+i][5+2*16]	->setChecked(true);
		ChkList[4+i][5+3*16]	->setChecked(true);
	}
}

void LightUSB8PortFormSmall::on_tbRight_6_clicked()
{
	for(int i=0;i<4;i++){
		ChkList[4+i][6+0*16]	->setChecked(true);
		ChkList[4+i][6+1*16]	->setChecked(true);
		ChkList[4+i][6+2*16]	->setChecked(true);
		ChkList[4+i][6+3*16]	->setChecked(true);
	}
}

void LightUSB8PortFormSmall::on_tbRight_7_clicked()
{
	for(int i=0;i<4;i++){
		ChkList[4+i][7+0*16]	->setChecked(true);
		ChkList[4+i][7+1*16]	->setChecked(true);
		ChkList[4+i][7+2*16]	->setChecked(true);
		ChkList[4+i][7+3*16]	->setChecked(true);
	}
}

void LightUSB8PortFormSmall::on_tbRight_8_clicked()
{
	for(int i=0;i<4;i++){
		ChkList[4+i][8+0*16]	->setChecked(true);
		ChkList[4+i][8+1*16]	->setChecked(true);
		ChkList[4+i][8+2*16]	->setChecked(true);
		ChkList[4+i][8+3*16]	->setChecked(true);
	}
}

void LightUSB8PortFormSmall::on_tbRight_9_clicked()
{
	for(int i=0;i<4;i++){
		ChkList[4+i][9+0*16]	->setChecked(true);
		ChkList[4+i][9+1*16]	->setChecked(true);
		ChkList[4+i][9+2*16]	->setChecked(true);
		ChkList[4+i][9+3*16]	->setChecked(true);
	}
}

void LightUSB8PortFormSmall::on_tbRight_10_clicked()
{
	for(int i=0;i<4;i++){
		ChkList[4+i][10+0*16]	->setChecked(true);
		ChkList[4+i][10+1*16]	->setChecked(true);
		ChkList[4+i][10+2*16]	->setChecked(true);
		ChkList[4+i][10+3*16]	->setChecked(true);
	}
}

void LightUSB8PortFormSmall::on_tbRight_11_clicked()
{
	for(int i=0;i<4;i++){
		ChkList[4+i][11+0*16]	->setChecked(true);
		ChkList[4+i][11+1*16]	->setChecked(true);
		ChkList[4+i][11+2*16]	->setChecked(true);
		ChkList[4+i][11+3*16]	->setChecked(true);
	}
}

void LightUSB8PortFormSmall::on_tbRight_12_clicked()
{
	for(int i=0;i<4;i++){
		ChkList[4+i][12+0*16]	->setChecked(true);
		ChkList[4+i][12+1*16]	->setChecked(true);
		ChkList[4+i][12+2*16]	->setChecked(true);
		ChkList[4+i][12+3*16]	->setChecked(true);
	}
}

void LightUSB8PortFormSmall::on_tbRight_13_clicked()
{
	for(int i=0;i<4;i++){
		ChkList[4+i][13+0*16]	->setChecked(true);
		ChkList[4+i][13+1*16]	->setChecked(true);
		ChkList[4+i][13+2*16]	->setChecked(true);
		ChkList[4+i][13+3*16]	->setChecked(true);
	}
}

void LightUSB8PortFormSmall::on_tbRight_14_clicked()
{
	for(int i=0;i<4;i++){
		ChkList[4+i][14+0*16]	->setChecked(true);
		ChkList[4+i][14+1*16]	->setChecked(true);
		ChkList[4+i][14+2*16]	->setChecked(true);
		ChkList[4+i][14+3*16]	->setChecked(true);
	}
}

void LightUSB8PortFormSmall::on_tbRight_15_clicked()
{
	for(int i=0;i<4;i++){
		ChkList[4+i][15+0*16]	->setChecked(true);
		ChkList[4+i][15+1*16]	->setChecked(true);
		ChkList[4+i][15+2*16]	->setChecked(true);
		ChkList[4+i][15+3*16]	->setChecked(true);
	}
}

void LightUSB8PortFormSmall::on_pbOK_clicked()
{
	BLight->SetBoardComment(0,ui->le_1->text());
	BLight->SetBoardComment(1,ui->le_2->text());
	BLight->SetBoardComment(2,ui->le_3->text());
	BLight->SetBoardComment(3,ui->le_4->text());
	BLight->SetBoardComment(4,ui->le_5->text());
	BLight->SetBoardComment(5,ui->le_6->text());
	BLight->SetBoardComment(6,ui->le_7->text());
	BLight->SetBoardComment(7,ui->le_8->text());

	accept();
}

void LightUSB8PortFormSmall::on_pbCancel_clicked()
{
	reject();
}

void LightUSB8PortFormSmall::on_pbAllSelect_clicked()
{
	for(int i=0;i<8;i++){
		for(int j=0;j<64;j++){
			ChkList[i][j]	->setChecked(true);
		}
	}
}

void LightUSB8PortFormSmall::on_pbClearSelect_clicked()
{
	for(int i=0;i<8;i++){
		for(int j=0;j<64;j++){
			ChkList[i][j]	->setChecked(false);
		}
	}
}

void LightUSB8PortFormSmall::on_pbTransport_clicked()
{
	BLight->ReflectDataInDialog();
	ui->pgbLight->setValue(100);

	/*
	BLight->BeginTranster();
	for(int i=0;i<8;i++){
		for(int j=0;j<64;j++){
			//BLight.CLED[i].Change(j,BLight.SaveLEDBright[i][j]);
			//BLight.CLED[i].OutData(j,BLight.Gain[i][j]);
			BLight->GetLED(i,j)->Transfer(BLight->GetDirectAccessor());
		}
		ui->pgbLight->setValue(100*(i+1)/8);
	}
	BLight->EndTranster();
	*/
}

void LightUSB8PortFormSmall::on_tbOnOff_clicked()
{
	if(ui->tbOnOff->isChecked()==true){
		BLight->ReflectOnOffInDialog(true);
	}
	else{
		BLight->ReflectOnOffInDialog(false);
	}
}

void LightUSB8PortFormSmall::on_vsBrightness_valueChanged(int value)
{
	int	n=ui->vsBrightness->value();
	ui->sbBrightness->setValue(n);
}

void LightUSB8PortFormSmall::on_sbBrightness_valueChanged(int arg1)
{
	int	n=ui->sbBrightness->value();
	for(int i=0;i<8;i++){
		for(int j=0;j<64;j++){
			if(ChkList[i][j]->isChecked()==true){
				BLight->SetLEDBrightness(i,j,n);
				LabelList[i][j]->setText(QString::number(n));
			}
		}
	}
}
