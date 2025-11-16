/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\PluginDLL\Light\LightDLL\LightDLL\LightDLL1Form.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "LightDLL1Form.h"

LightDLL1Form::LightDLL1Form(LightDLL1 *p, QWidget *parent)
: QDialog(parent),BLight(p->GetLayersBase()),SavedLight(p->GetLayersBase())
{
	ui.setupUi(this);

	//CheckBox-List
	int i=0;
	ChkList[i++]=ui.chk_1_1;
	ChkList[i++]=ui.chk_1_2;
	ChkList[i++]=ui.chk_1_3;
	ChkList[i++]=ui.chk_1_4;
	ChkList[i++]=ui.chk_1_5;
	ChkList[i++]=ui.chk_1_6;
	ChkList[i++]=ui.chk_1_7;
	ChkList[i++]=ui.chk_1_8;
	ChkList[i++]=ui.chk_1_9;
	ChkList[i++]=ui.chk_1_10;
	ChkList[i++]=ui.chk_1_11;
	ChkList[i++]=ui.chk_1_12;
	ChkList[i++]=ui.chk_1_13;
	ChkList[i++]=ui.chk_1_14;
	ChkList[i++]=ui.chk_1_15;
	ChkList[i++]=ui.chk_1_16;
	ChkList[i++]=ui.chk_1_17;
	ChkList[i++]=ui.chk_1_18;
	ChkList[i++]=ui.chk_1_19;
	ChkList[i++]=ui.chk_1_20;
	ChkList[i++]=ui.chk_1_21;
	ChkList[i++]=ui.chk_1_22;
	ChkList[i++]=ui.chk_1_23;
	ChkList[i++]=ui.chk_1_24;
	ChkList[i++]=ui.chk_1_25;
	ChkList[i++]=ui.chk_1_26;
	ChkList[i++]=ui.chk_1_27;
	ChkList[i++]=ui.chk_1_28;
	ChkList[i++]=ui.chk_1_29;
	ChkList[i++]=ui.chk_1_30;
	ChkList[i++]=ui.chk_1_31;
	ChkList[i++]=ui.chk_1_32;

	ChkList[i++]=ui.chk_2_1;
	ChkList[i++]=ui.chk_2_2;
	ChkList[i++]=ui.chk_2_3;
	ChkList[i++]=ui.chk_2_4;
	ChkList[i++]=ui.chk_2_5;
	ChkList[i++]=ui.chk_2_6;
	ChkList[i++]=ui.chk_2_7;
	ChkList[i++]=ui.chk_2_8;
	ChkList[i++]=ui.chk_2_9;
	ChkList[i++]=ui.chk_2_10;
	ChkList[i++]=ui.chk_2_11;
	ChkList[i++]=ui.chk_2_12;
	ChkList[i++]=ui.chk_2_13;
	ChkList[i++]=ui.chk_2_14;
	ChkList[i++]=ui.chk_2_15;
	ChkList[i++]=ui.chk_2_16;
	ChkList[i++]=ui.chk_2_17;
	ChkList[i++]=ui.chk_2_18;
	ChkList[i++]=ui.chk_2_19;
	ChkList[i++]=ui.chk_2_20;
	ChkList[i++]=ui.chk_2_21;
	ChkList[i++]=ui.chk_2_22;
	ChkList[i++]=ui.chk_2_23;
	ChkList[i++]=ui.chk_2_24;
	ChkList[i++]=ui.chk_2_25;
	ChkList[i++]=ui.chk_2_26;
	ChkList[i++]=ui.chk_2_27;
	ChkList[i++]=ui.chk_2_28;
	ChkList[i++]=ui.chk_2_29;
	ChkList[i++]=ui.chk_2_30;
	ChkList[i++]=ui.chk_2_31;
	ChkList[i++]=ui.chk_2_32;

	ChkList[i++]=ui.chk_3_1;
	ChkList[i++]=ui.chk_3_2;
	ChkList[i++]=ui.chk_3_3;
	ChkList[i++]=ui.chk_3_4;
	ChkList[i++]=ui.chk_3_5;
	ChkList[i++]=ui.chk_3_6;
	ChkList[i++]=ui.chk_3_7;
	ChkList[i++]=ui.chk_3_8;
	ChkList[i++]=ui.chk_3_9;
	ChkList[i++]=ui.chk_3_10;
	ChkList[i++]=ui.chk_3_11;
	ChkList[i++]=ui.chk_3_12;
	ChkList[i++]=ui.chk_3_13;
	ChkList[i++]=ui.chk_3_14;
	ChkList[i++]=ui.chk_3_15;
	ChkList[i++]=ui.chk_3_16;
	ChkList[i++]=ui.chk_3_17;
	ChkList[i++]=ui.chk_3_18;
	ChkList[i++]=ui.chk_3_19;
	ChkList[i++]=ui.chk_3_20;
	ChkList[i++]=ui.chk_3_21;
	ChkList[i++]=ui.chk_3_22;
	ChkList[i++]=ui.chk_3_23;
	ChkList[i++]=ui.chk_3_24;
	ChkList[i++]=ui.chk_3_25;
	ChkList[i++]=ui.chk_3_26;
	ChkList[i++]=ui.chk_3_27;
	ChkList[i++]=ui.chk_3_28;
	ChkList[i++]=ui.chk_3_29;
	ChkList[i++]=ui.chk_3_30;
	ChkList[i++]=ui.chk_3_31;
	ChkList[i++]=ui.chk_3_32;

	ChkList[i++]=ui.chk_4_1;
	ChkList[i++]=ui.chk_4_2;
	ChkList[i++]=ui.chk_4_3;
	ChkList[i++]=ui.chk_4_4;
	ChkList[i++]=ui.chk_4_5;
	ChkList[i++]=ui.chk_4_6;
	ChkList[i++]=ui.chk_4_7;
	ChkList[i++]=ui.chk_4_8;
	ChkList[i++]=ui.chk_4_9;
	ChkList[i++]=ui.chk_4_10;
	ChkList[i++]=ui.chk_4_11;
	ChkList[i++]=ui.chk_4_12;
	ChkList[i++]=ui.chk_4_13;
	ChkList[i++]=ui.chk_4_14;
	ChkList[i++]=ui.chk_4_15;
	ChkList[i++]=ui.chk_4_16;
	ChkList[i++]=ui.chk_4_17;
	ChkList[i++]=ui.chk_4_18;
	ChkList[i++]=ui.chk_4_19;
	ChkList[i++]=ui.chk_4_20;
	ChkList[i++]=ui.chk_4_21;
	ChkList[i++]=ui.chk_4_22;
	ChkList[i++]=ui.chk_4_23;
	ChkList[i++]=ui.chk_4_24;
	ChkList[i++]=ui.chk_4_25;
	ChkList[i++]=ui.chk_4_26;
	ChkList[i++]=ui.chk_4_27;
	ChkList[i++]=ui.chk_4_28;
	ChkList[i++]=ui.chk_4_29;
	ChkList[i++]=ui.chk_4_30;
	ChkList[i++]=ui.chk_4_31;
	ChkList[i++]=ui.chk_4_32;

	ChkList[i++]=ui.chk_5_1;
	ChkList[i++]=ui.chk_5_2;
	ChkList[i++]=ui.chk_5_3;
	ChkList[i++]=ui.chk_5_4;
	ChkList[i++]=ui.chk_5_5;
	ChkList[i++]=ui.chk_5_6;
	ChkList[i++]=ui.chk_5_7;
	ChkList[i++]=ui.chk_5_8;
	ChkList[i++]=ui.chk_5_9;
	ChkList[i++]=ui.chk_5_10;
	ChkList[i++]=ui.chk_5_11;
	ChkList[i++]=ui.chk_5_12;
	ChkList[i++]=ui.chk_5_13;
	ChkList[i++]=ui.chk_5_14;
	ChkList[i++]=ui.chk_5_15;
	ChkList[i++]=ui.chk_5_16;
	ChkList[i++]=ui.chk_5_17;
	ChkList[i++]=ui.chk_5_18;
	ChkList[i++]=ui.chk_5_19;
	ChkList[i++]=ui.chk_5_20;
	ChkList[i++]=ui.chk_5_21;
	ChkList[i++]=ui.chk_5_22;
	ChkList[i++]=ui.chk_5_23;
	ChkList[i++]=ui.chk_5_24;
	ChkList[i++]=ui.chk_5_25;
	ChkList[i++]=ui.chk_5_26;
	ChkList[i++]=ui.chk_5_27;
	ChkList[i++]=ui.chk_5_28;
	ChkList[i++]=ui.chk_5_29;
	ChkList[i++]=ui.chk_5_30;
	ChkList[i++]=ui.chk_5_31;
	ChkList[i++]=ui.chk_5_32;

	ChkList[i++]=ui.chk_6_1;
	ChkList[i++]=ui.chk_6_2;
	ChkList[i++]=ui.chk_6_3;
	ChkList[i++]=ui.chk_6_4;
	ChkList[i++]=ui.chk_6_5;
	ChkList[i++]=ui.chk_6_6;
	ChkList[i++]=ui.chk_6_7;
	ChkList[i++]=ui.chk_6_8;
	ChkList[i++]=ui.chk_6_9;
	ChkList[i++]=ui.chk_6_10;
	ChkList[i++]=ui.chk_6_11;
	ChkList[i++]=ui.chk_6_12;
	ChkList[i++]=ui.chk_6_13;
	ChkList[i++]=ui.chk_6_14;
	ChkList[i++]=ui.chk_6_15;
	ChkList[i++]=ui.chk_6_16;
	ChkList[i++]=ui.chk_6_17;
	ChkList[i++]=ui.chk_6_18;
	ChkList[i++]=ui.chk_6_19;
	ChkList[i++]=ui.chk_6_20;
	ChkList[i++]=ui.chk_6_21;
	ChkList[i++]=ui.chk_6_22;
	ChkList[i++]=ui.chk_6_23;
	ChkList[i++]=ui.chk_6_24;
	ChkList[i++]=ui.chk_6_25;
	ChkList[i++]=ui.chk_6_26;
	ChkList[i++]=ui.chk_6_27;
	ChkList[i++]=ui.chk_6_28;
	ChkList[i++]=ui.chk_6_29;
	ChkList[i++]=ui.chk_6_30;
	ChkList[i++]=ui.chk_6_31;
	ChkList[i++]=ui.chk_6_32;

	//Label-List
	i=0;
	LabelList[i++]=ui.lb_1_1;
	LabelList[i++]=ui.lb_1_2;
	LabelList[i++]=ui.lb_1_3;
	LabelList[i++]=ui.lb_1_4;
	LabelList[i++]=ui.lb_1_5;
	LabelList[i++]=ui.lb_1_6;
	LabelList[i++]=ui.lb_1_7;
	LabelList[i++]=ui.lb_1_8;
	LabelList[i++]=ui.lb_1_9;
	LabelList[i++]=ui.lb_1_10;
	LabelList[i++]=ui.lb_1_11;
	LabelList[i++]=ui.lb_1_12;
	LabelList[i++]=ui.lb_1_13;
	LabelList[i++]=ui.lb_1_14;
	LabelList[i++]=ui.lb_1_15;
	LabelList[i++]=ui.lb_1_16;
	LabelList[i++]=ui.lb_1_17;
	LabelList[i++]=ui.lb_1_18;
	LabelList[i++]=ui.lb_1_19;
	LabelList[i++]=ui.lb_1_20;
	LabelList[i++]=ui.lb_1_21;
	LabelList[i++]=ui.lb_1_22;
	LabelList[i++]=ui.lb_1_23;
	LabelList[i++]=ui.lb_1_24;
	LabelList[i++]=ui.lb_1_25;
	LabelList[i++]=ui.lb_1_26;
	LabelList[i++]=ui.lb_1_27;
	LabelList[i++]=ui.lb_1_28;
	LabelList[i++]=ui.lb_1_29;
	LabelList[i++]=ui.lb_1_30;
	LabelList[i++]=ui.lb_1_31;
	LabelList[i++]=ui.lb_1_32;

	LabelList[i++]=ui.lb_2_1;
	LabelList[i++]=ui.lb_2_2;
	LabelList[i++]=ui.lb_2_3;
	LabelList[i++]=ui.lb_2_4;
	LabelList[i++]=ui.lb_2_5;
	LabelList[i++]=ui.lb_2_6;
	LabelList[i++]=ui.lb_2_7;
	LabelList[i++]=ui.lb_2_8;
	LabelList[i++]=ui.lb_2_9;
	LabelList[i++]=ui.lb_2_10;
	LabelList[i++]=ui.lb_2_11;
	LabelList[i++]=ui.lb_2_12;
	LabelList[i++]=ui.lb_2_13;
	LabelList[i++]=ui.lb_2_14;
	LabelList[i++]=ui.lb_2_15;
	LabelList[i++]=ui.lb_2_16;
	LabelList[i++]=ui.lb_2_17;
	LabelList[i++]=ui.lb_2_18;
	LabelList[i++]=ui.lb_2_19;
	LabelList[i++]=ui.lb_2_20;
	LabelList[i++]=ui.lb_2_21;
	LabelList[i++]=ui.lb_2_22;
	LabelList[i++]=ui.lb_2_23;
	LabelList[i++]=ui.lb_2_24;
	LabelList[i++]=ui.lb_2_25;
	LabelList[i++]=ui.lb_2_26;
	LabelList[i++]=ui.lb_2_27;
	LabelList[i++]=ui.lb_2_28;
	LabelList[i++]=ui.lb_2_29;
	LabelList[i++]=ui.lb_2_30;
	LabelList[i++]=ui.lb_2_31;
	LabelList[i++]=ui.lb_2_32;

	LabelList[i++]=ui.lb_3_1;
	LabelList[i++]=ui.lb_3_2;
	LabelList[i++]=ui.lb_3_3;
	LabelList[i++]=ui.lb_3_4;
	LabelList[i++]=ui.lb_3_5;
	LabelList[i++]=ui.lb_3_6;
	LabelList[i++]=ui.lb_3_7;
	LabelList[i++]=ui.lb_3_8;
	LabelList[i++]=ui.lb_3_9;
	LabelList[i++]=ui.lb_3_10;
	LabelList[i++]=ui.lb_3_11;
	LabelList[i++]=ui.lb_3_12;
	LabelList[i++]=ui.lb_3_13;
	LabelList[i++]=ui.lb_3_14;
	LabelList[i++]=ui.lb_3_15;
	LabelList[i++]=ui.lb_3_16;
	LabelList[i++]=ui.lb_3_17;
	LabelList[i++]=ui.lb_3_18;
	LabelList[i++]=ui.lb_3_19;
	LabelList[i++]=ui.lb_3_20;
	LabelList[i++]=ui.lb_3_21;
	LabelList[i++]=ui.lb_3_22;
	LabelList[i++]=ui.lb_3_23;
	LabelList[i++]=ui.lb_3_24;
	LabelList[i++]=ui.lb_3_25;
	LabelList[i++]=ui.lb_3_26;
	LabelList[i++]=ui.lb_3_27;
	LabelList[i++]=ui.lb_3_28;
	LabelList[i++]=ui.lb_3_29;
	LabelList[i++]=ui.lb_3_30;
	LabelList[i++]=ui.lb_3_31;
	LabelList[i++]=ui.lb_3_32;

	LabelList[i++]=ui.lb_4_1;
	LabelList[i++]=ui.lb_4_2;
	LabelList[i++]=ui.lb_4_3;
	LabelList[i++]=ui.lb_4_4;
	LabelList[i++]=ui.lb_4_5;
	LabelList[i++]=ui.lb_4_6;
	LabelList[i++]=ui.lb_4_7;
	LabelList[i++]=ui.lb_4_8;
	LabelList[i++]=ui.lb_4_9;
	LabelList[i++]=ui.lb_4_10;
	LabelList[i++]=ui.lb_4_11;
	LabelList[i++]=ui.lb_4_12;
	LabelList[i++]=ui.lb_4_13;
	LabelList[i++]=ui.lb_4_14;
	LabelList[i++]=ui.lb_4_15;
	LabelList[i++]=ui.lb_4_16;
	LabelList[i++]=ui.lb_4_17;
	LabelList[i++]=ui.lb_4_18;
	LabelList[i++]=ui.lb_4_19;
	LabelList[i++]=ui.lb_4_20;
	LabelList[i++]=ui.lb_4_21;
	LabelList[i++]=ui.lb_4_22;
	LabelList[i++]=ui.lb_4_23;
	LabelList[i++]=ui.lb_4_24;
	LabelList[i++]=ui.lb_4_25;
	LabelList[i++]=ui.lb_4_26;
	LabelList[i++]=ui.lb_4_27;
	LabelList[i++]=ui.lb_4_28;
	LabelList[i++]=ui.lb_4_29;
	LabelList[i++]=ui.lb_4_30;
	LabelList[i++]=ui.lb_4_31;
	LabelList[i++]=ui.lb_4_32;

	LabelList[i++]=ui.lb_5_1;
	LabelList[i++]=ui.lb_5_2;
	LabelList[i++]=ui.lb_5_3;
	LabelList[i++]=ui.lb_5_4;
	LabelList[i++]=ui.lb_5_5;
	LabelList[i++]=ui.lb_5_6;
	LabelList[i++]=ui.lb_5_7;
	LabelList[i++]=ui.lb_5_8;
	LabelList[i++]=ui.lb_5_9;
	LabelList[i++]=ui.lb_5_10;
	LabelList[i++]=ui.lb_5_11;
	LabelList[i++]=ui.lb_5_12;
	LabelList[i++]=ui.lb_5_13;
	LabelList[i++]=ui.lb_5_14;
	LabelList[i++]=ui.lb_5_15;
	LabelList[i++]=ui.lb_5_16;
	LabelList[i++]=ui.lb_5_17;
	LabelList[i++]=ui.lb_5_18;
	LabelList[i++]=ui.lb_5_19;
	LabelList[i++]=ui.lb_5_20;
	LabelList[i++]=ui.lb_5_21;
	LabelList[i++]=ui.lb_5_22;
	LabelList[i++]=ui.lb_5_23;
	LabelList[i++]=ui.lb_5_24;
	LabelList[i++]=ui.lb_5_25;
	LabelList[i++]=ui.lb_5_26;
	LabelList[i++]=ui.lb_5_27;
	LabelList[i++]=ui.lb_5_28;
	LabelList[i++]=ui.lb_5_29;
	LabelList[i++]=ui.lb_5_30;
	LabelList[i++]=ui.lb_5_31;
	LabelList[i++]=ui.lb_5_32;

	LabelList[i++]=ui.lb_6_1;
	LabelList[i++]=ui.lb_6_2;
	LabelList[i++]=ui.lb_6_3;
	LabelList[i++]=ui.lb_6_4;
	LabelList[i++]=ui.lb_6_5;
	LabelList[i++]=ui.lb_6_6;
	LabelList[i++]=ui.lb_6_7;
	LabelList[i++]=ui.lb_6_8;
	LabelList[i++]=ui.lb_6_9;
	LabelList[i++]=ui.lb_6_10;
	LabelList[i++]=ui.lb_6_11;
	LabelList[i++]=ui.lb_6_12;
	LabelList[i++]=ui.lb_6_13;
	LabelList[i++]=ui.lb_6_14;
	LabelList[i++]=ui.lb_6_15;
	LabelList[i++]=ui.lb_6_16;
	LabelList[i++]=ui.lb_6_17;
	LabelList[i++]=ui.lb_6_18;
	LabelList[i++]=ui.lb_6_19;
	LabelList[i++]=ui.lb_6_20;
	LabelList[i++]=ui.lb_6_21;
	LabelList[i++]=ui.lb_6_22;
	LabelList[i++]=ui.lb_6_23;
	LabelList[i++]=ui.lb_6_24;
	LabelList[i++]=ui.lb_6_25;
	LabelList[i++]=ui.lb_6_26;
	LabelList[i++]=ui.lb_6_27;
	LabelList[i++]=ui.lb_6_28;
	LabelList[i++]=ui.lb_6_29;
	LabelList[i++]=ui.lb_6_30;
	LabelList[i++]=ui.lb_6_31;
	LabelList[i++]=ui.lb_6_32;

	//CheckBox-Sort-List
	i=0;
	ChkSortList[i++]=ui.chk_1_32;
	ChkSortList[i++]=ui.chk_1_31;
	ChkSortList[i++]=ui.chk_1_30;
	ChkSortList[i++]=ui.chk_1_29;
	ChkSortList[i++]=ui.chk_1_28;
	ChkSortList[i++]=ui.chk_1_27;
	ChkSortList[i++]=ui.chk_1_26;
	ChkSortList[i++]=ui.chk_1_25;
	ChkSortList[i++]=ui.chk_1_24;
	ChkSortList[i++]=ui.chk_1_23;
	ChkSortList[i++]=ui.chk_1_22;
	ChkSortList[i++]=ui.chk_1_21;
	ChkSortList[i++]=ui.chk_1_20;
	ChkSortList[i++]=ui.chk_1_19;
	ChkSortList[i++]=ui.chk_1_18;
	ChkSortList[i++]=ui.chk_1_17;
	ChkSortList[i++]=ui.chk_1_16;
	ChkSortList[i++]=ui.chk_1_15;
	ChkSortList[i++]=ui.chk_1_14;
	ChkSortList[i++]=ui.chk_1_13;
	ChkSortList[i++]=ui.chk_1_12;
	ChkSortList[i++]=ui.chk_1_11;
	ChkSortList[i++]=ui.chk_1_10;
	ChkSortList[i++]=ui.chk_1_9;
	ChkSortList[i++]=ui.chk_1_8;
	ChkSortList[i++]=ui.chk_1_7;
	ChkSortList[i++]=ui.chk_1_6;
	ChkSortList[i++]=ui.chk_1_5;
	ChkSortList[i++]=ui.chk_1_4;
	ChkSortList[i++]=ui.chk_1_3;
	ChkSortList[i++]=ui.chk_1_2;
	ChkSortList[i++]=ui.chk_1_1;

	ChkSortList[i++]=ui.chk_2_32;
	ChkSortList[i++]=ui.chk_2_31;
	ChkSortList[i++]=ui.chk_2_30;
	ChkSortList[i++]=ui.chk_2_29;
	ChkSortList[i++]=ui.chk_2_28;
	ChkSortList[i++]=ui.chk_2_27;
	ChkSortList[i++]=ui.chk_2_26;
	ChkSortList[i++]=ui.chk_2_25;
	ChkSortList[i++]=ui.chk_2_24;
	ChkSortList[i++]=ui.chk_2_23;
	ChkSortList[i++]=ui.chk_2_22;
	ChkSortList[i++]=ui.chk_2_21;
	ChkSortList[i++]=ui.chk_2_20;
	ChkSortList[i++]=ui.chk_2_19;
	ChkSortList[i++]=ui.chk_2_18;
	ChkSortList[i++]=ui.chk_2_17;
	ChkSortList[i++]=ui.chk_2_16;
	ChkSortList[i++]=ui.chk_2_15;
	ChkSortList[i++]=ui.chk_2_14;
	ChkSortList[i++]=ui.chk_2_13;
	ChkSortList[i++]=ui.chk_2_12;
	ChkSortList[i++]=ui.chk_2_11;
	ChkSortList[i++]=ui.chk_2_10;
	ChkSortList[i++]=ui.chk_2_9;
	ChkSortList[i++]=ui.chk_2_8;
	ChkSortList[i++]=ui.chk_2_7;
	ChkSortList[i++]=ui.chk_2_6;
	ChkSortList[i++]=ui.chk_2_5;
	ChkSortList[i++]=ui.chk_2_4;
	ChkSortList[i++]=ui.chk_2_3;
	ChkSortList[i++]=ui.chk_2_2;
	ChkSortList[i++]=ui.chk_2_1;

	ChkSortList[i++]=ui.chk_6_31;
	ChkSortList[i++]=ui.chk_6_32;
	ChkSortList[i++]=ui.chk_6_29;
	ChkSortList[i++]=ui.chk_6_30;
	ChkSortList[i++]=ui.chk_6_27;
	ChkSortList[i++]=ui.chk_6_28;
	ChkSortList[i++]=ui.chk_6_25;
	ChkSortList[i++]=ui.chk_6_26;
	ChkSortList[i++]=ui.chk_6_23;
	ChkSortList[i++]=ui.chk_6_24;
	ChkSortList[i++]=ui.chk_6_21;
	ChkSortList[i++]=ui.chk_6_22;
	ChkSortList[i++]=ui.chk_6_19;
	ChkSortList[i++]=ui.chk_6_20;
	ChkSortList[i++]=ui.chk_6_17;
	ChkSortList[i++]=ui.chk_6_18;
	ChkSortList[i++]=ui.chk_6_15;
	ChkSortList[i++]=ui.chk_6_16;
	ChkSortList[i++]=ui.chk_6_13;
	ChkSortList[i++]=ui.chk_6_14;
	ChkSortList[i++]=ui.chk_6_11;
	ChkSortList[i++]=ui.chk_6_12;
	ChkSortList[i++]=ui.chk_6_9;
	ChkSortList[i++]=ui.chk_6_10;
	ChkSortList[i++]=ui.chk_6_7;
	ChkSortList[i++]=ui.chk_6_8;
	ChkSortList[i++]=ui.chk_6_5;
	ChkSortList[i++]=ui.chk_6_6;
	ChkSortList[i++]=ui.chk_6_3;
	ChkSortList[i++]=ui.chk_6_4;
	ChkSortList[i++]=ui.chk_6_1;
	ChkSortList[i++]=ui.chk_6_2;

	ChkSortList[i++]=ui.chk_5_31;
	ChkSortList[i++]=ui.chk_5_32;
	ChkSortList[i++]=ui.chk_5_29;
	ChkSortList[i++]=ui.chk_5_30;
	ChkSortList[i++]=ui.chk_5_27;
	ChkSortList[i++]=ui.chk_5_28;
	ChkSortList[i++]=ui.chk_5_25;
	ChkSortList[i++]=ui.chk_5_26;
	ChkSortList[i++]=ui.chk_5_23;
	ChkSortList[i++]=ui.chk_5_24;
	ChkSortList[i++]=ui.chk_5_21;
	ChkSortList[i++]=ui.chk_5_22;
	ChkSortList[i++]=ui.chk_5_19;
	ChkSortList[i++]=ui.chk_5_20;
	ChkSortList[i++]=ui.chk_5_17;
	ChkSortList[i++]=ui.chk_5_18;
	ChkSortList[i++]=ui.chk_5_15;
	ChkSortList[i++]=ui.chk_5_16;
	ChkSortList[i++]=ui.chk_5_13;
	ChkSortList[i++]=ui.chk_5_14;
	ChkSortList[i++]=ui.chk_5_11;
	ChkSortList[i++]=ui.chk_5_12;
	ChkSortList[i++]=ui.chk_5_9;
	ChkSortList[i++]=ui.chk_5_10;
	ChkSortList[i++]=ui.chk_5_7;
	ChkSortList[i++]=ui.chk_5_8;
	ChkSortList[i++]=ui.chk_5_5;
	ChkSortList[i++]=ui.chk_5_6;
	ChkSortList[i++]=ui.chk_5_3;
	ChkSortList[i++]=ui.chk_5_4;
	ChkSortList[i++]=ui.chk_5_1;
	ChkSortList[i++]=ui.chk_5_2;

	ChkSortList[i++]=ui.chk_3_32;
	ChkSortList[i++]=ui.chk_3_31;
	ChkSortList[i++]=ui.chk_3_30;
	ChkSortList[i++]=ui.chk_3_29;
	ChkSortList[i++]=ui.chk_3_28;
	ChkSortList[i++]=ui.chk_3_27;
	ChkSortList[i++]=ui.chk_3_26;
	ChkSortList[i++]=ui.chk_3_25;
	ChkSortList[i++]=ui.chk_3_24;
	ChkSortList[i++]=ui.chk_3_23;
	ChkSortList[i++]=ui.chk_3_22;
	ChkSortList[i++]=ui.chk_3_21;
	ChkSortList[i++]=ui.chk_3_20;
	ChkSortList[i++]=ui.chk_3_19;
	ChkSortList[i++]=ui.chk_3_18;
	ChkSortList[i++]=ui.chk_3_17;
	ChkSortList[i++]=ui.chk_3_16;
	ChkSortList[i++]=ui.chk_3_15;
	ChkSortList[i++]=ui.chk_3_14;
	ChkSortList[i++]=ui.chk_3_13;
	ChkSortList[i++]=ui.chk_3_12;
	ChkSortList[i++]=ui.chk_3_11;
	ChkSortList[i++]=ui.chk_3_10;
	ChkSortList[i++]=ui.chk_3_9;
	ChkSortList[i++]=ui.chk_3_8;
	ChkSortList[i++]=ui.chk_3_7;
	ChkSortList[i++]=ui.chk_3_6;
	ChkSortList[i++]=ui.chk_3_5;
	ChkSortList[i++]=ui.chk_3_4;
	ChkSortList[i++]=ui.chk_3_3;
	ChkSortList[i++]=ui.chk_3_2;
	ChkSortList[i++]=ui.chk_3_1;

	ChkSortList[i++]=ui.chk_4_31;
	ChkSortList[i++]=ui.chk_4_32;
	ChkSortList[i++]=ui.chk_4_29;
	ChkSortList[i++]=ui.chk_4_30;
	ChkSortList[i++]=ui.chk_4_27;
	ChkSortList[i++]=ui.chk_4_28;
	ChkSortList[i++]=ui.chk_4_25;
	ChkSortList[i++]=ui.chk_4_26;
	ChkSortList[i++]=ui.chk_4_23;
	ChkSortList[i++]=ui.chk_4_24;
	ChkSortList[i++]=ui.chk_4_21;
	ChkSortList[i++]=ui.chk_4_22;
	ChkSortList[i++]=ui.chk_4_19;
	ChkSortList[i++]=ui.chk_4_20;
	ChkSortList[i++]=ui.chk_4_17;
	ChkSortList[i++]=ui.chk_4_18;
	ChkSortList[i++]=ui.chk_4_15;
	ChkSortList[i++]=ui.chk_4_16;
	ChkSortList[i++]=ui.chk_4_13;
	ChkSortList[i++]=ui.chk_4_14;
	ChkSortList[i++]=ui.chk_4_11;
	ChkSortList[i++]=ui.chk_4_12;
	ChkSortList[i++]=ui.chk_4_9;
	ChkSortList[i++]=ui.chk_4_10;
	ChkSortList[i++]=ui.chk_4_7;
	ChkSortList[i++]=ui.chk_4_8;
	ChkSortList[i++]=ui.chk_4_5;
	ChkSortList[i++]=ui.chk_4_6;
	ChkSortList[i++]=ui.chk_4_3;
	ChkSortList[i++]=ui.chk_4_4;
	ChkSortList[i++]=ui.chk_4_1;
	ChkSortList[i++]=ui.chk_4_2;

	//Label-List
	i=0;
	LabelSortList[i++]=ui.lb_1_32;
	LabelSortList[i++]=ui.lb_1_31;
	LabelSortList[i++]=ui.lb_1_30;
	LabelSortList[i++]=ui.lb_1_29;
	LabelSortList[i++]=ui.lb_1_28;
	LabelSortList[i++]=ui.lb_1_27;
	LabelSortList[i++]=ui.lb_1_26;
	LabelSortList[i++]=ui.lb_1_25;
	LabelSortList[i++]=ui.lb_1_24;
	LabelSortList[i++]=ui.lb_1_23;
	LabelSortList[i++]=ui.lb_1_22;
	LabelSortList[i++]=ui.lb_1_21;
	LabelSortList[i++]=ui.lb_1_20;
	LabelSortList[i++]=ui.lb_1_19;
	LabelSortList[i++]=ui.lb_1_18;
	LabelSortList[i++]=ui.lb_1_17;
	LabelSortList[i++]=ui.lb_1_16;
	LabelSortList[i++]=ui.lb_1_15;
	LabelSortList[i++]=ui.lb_1_14;
	LabelSortList[i++]=ui.lb_1_13;
	LabelSortList[i++]=ui.lb_1_12;
	LabelSortList[i++]=ui.lb_1_11;
	LabelSortList[i++]=ui.lb_1_10;
	LabelSortList[i++]=ui.lb_1_9;
	LabelSortList[i++]=ui.lb_1_8;
	LabelSortList[i++]=ui.lb_1_7;
	LabelSortList[i++]=ui.lb_1_6;
	LabelSortList[i++]=ui.lb_1_5;
	LabelSortList[i++]=ui.lb_1_4;
	LabelSortList[i++]=ui.lb_1_3;
	LabelSortList[i++]=ui.lb_1_2;
	LabelSortList[i++]=ui.lb_1_1;

	LabelSortList[i++]=ui.lb_2_32;
	LabelSortList[i++]=ui.lb_2_31;
	LabelSortList[i++]=ui.lb_2_30;
	LabelSortList[i++]=ui.lb_2_29;
	LabelSortList[i++]=ui.lb_2_28;
	LabelSortList[i++]=ui.lb_2_27;
	LabelSortList[i++]=ui.lb_2_26;
	LabelSortList[i++]=ui.lb_2_25;
	LabelSortList[i++]=ui.lb_2_24;
	LabelSortList[i++]=ui.lb_2_23;
	LabelSortList[i++]=ui.lb_2_22;
	LabelSortList[i++]=ui.lb_2_21;
	LabelSortList[i++]=ui.lb_2_20;
	LabelSortList[i++]=ui.lb_2_19;
	LabelSortList[i++]=ui.lb_2_18;
	LabelSortList[i++]=ui.lb_2_17;
	LabelSortList[i++]=ui.lb_2_16;
	LabelSortList[i++]=ui.lb_2_15;
	LabelSortList[i++]=ui.lb_2_14;
	LabelSortList[i++]=ui.lb_2_13;
	LabelSortList[i++]=ui.lb_2_12;
	LabelSortList[i++]=ui.lb_2_11;
	LabelSortList[i++]=ui.lb_2_10;
	LabelSortList[i++]=ui.lb_2_9;
	LabelSortList[i++]=ui.lb_2_8;
	LabelSortList[i++]=ui.lb_2_7;
	LabelSortList[i++]=ui.lb_2_6;
	LabelSortList[i++]=ui.lb_2_5;
	LabelSortList[i++]=ui.lb_2_4;
	LabelSortList[i++]=ui.lb_2_3;
	LabelSortList[i++]=ui.lb_2_2;
	LabelSortList[i++]=ui.lb_2_1;

	LabelSortList[i++]=ui.lb_6_31;
	LabelSortList[i++]=ui.lb_6_32;
	LabelSortList[i++]=ui.lb_6_29;
	LabelSortList[i++]=ui.lb_6_30;
	LabelSortList[i++]=ui.lb_6_27;
	LabelSortList[i++]=ui.lb_6_28;
	LabelSortList[i++]=ui.lb_6_25;
	LabelSortList[i++]=ui.lb_6_26;
	LabelSortList[i++]=ui.lb_6_23;
	LabelSortList[i++]=ui.lb_6_24;
	LabelSortList[i++]=ui.lb_6_21;
	LabelSortList[i++]=ui.lb_6_22;
	LabelSortList[i++]=ui.lb_6_19;
	LabelSortList[i++]=ui.lb_6_20;
	LabelSortList[i++]=ui.lb_6_17;
	LabelSortList[i++]=ui.lb_6_18;
	LabelSortList[i++]=ui.lb_6_15;
	LabelSortList[i++]=ui.lb_6_16;
	LabelSortList[i++]=ui.lb_6_13;
	LabelSortList[i++]=ui.lb_6_14;
	LabelSortList[i++]=ui.lb_6_11;
	LabelSortList[i++]=ui.lb_6_12;
	LabelSortList[i++]=ui.lb_6_9;
	LabelSortList[i++]=ui.lb_6_10;
	LabelSortList[i++]=ui.lb_6_7;
	LabelSortList[i++]=ui.lb_6_8;
	LabelSortList[i++]=ui.lb_6_5;
	LabelSortList[i++]=ui.lb_6_6;
	LabelSortList[i++]=ui.lb_6_3;
	LabelSortList[i++]=ui.lb_6_4;
	LabelSortList[i++]=ui.lb_6_1;
	LabelSortList[i++]=ui.lb_6_2;

	LabelSortList[i++]=ui.lb_5_31;
	LabelSortList[i++]=ui.lb_5_32;
	LabelSortList[i++]=ui.lb_5_29;
	LabelSortList[i++]=ui.lb_5_30;
	LabelSortList[i++]=ui.lb_5_27;
	LabelSortList[i++]=ui.lb_5_28;
	LabelSortList[i++]=ui.lb_5_25;
	LabelSortList[i++]=ui.lb_5_26;
	LabelSortList[i++]=ui.lb_5_23;
	LabelSortList[i++]=ui.lb_5_24;
	LabelSortList[i++]=ui.lb_5_21;
	LabelSortList[i++]=ui.lb_5_22;
	LabelSortList[i++]=ui.lb_5_19;
	LabelSortList[i++]=ui.lb_5_20;
	LabelSortList[i++]=ui.lb_5_17;
	LabelSortList[i++]=ui.lb_5_18;
	LabelSortList[i++]=ui.lb_5_15;
	LabelSortList[i++]=ui.lb_5_16;
	LabelSortList[i++]=ui.lb_5_13;
	LabelSortList[i++]=ui.lb_5_14;
	LabelSortList[i++]=ui.lb_5_11;
	LabelSortList[i++]=ui.lb_5_12;
	LabelSortList[i++]=ui.lb_5_9;
	LabelSortList[i++]=ui.lb_5_10;
	LabelSortList[i++]=ui.lb_5_7;
	LabelSortList[i++]=ui.lb_5_8;
	LabelSortList[i++]=ui.lb_5_5;
	LabelSortList[i++]=ui.lb_5_6;
	LabelSortList[i++]=ui.lb_5_3;
	LabelSortList[i++]=ui.lb_5_4;
	LabelSortList[i++]=ui.lb_5_1;
	LabelSortList[i++]=ui.lb_5_2;

	LabelSortList[i++]=ui.lb_3_32;
	LabelSortList[i++]=ui.lb_3_31;
	LabelSortList[i++]=ui.lb_3_30;
	LabelSortList[i++]=ui.lb_3_29;
	LabelSortList[i++]=ui.lb_3_28;
	LabelSortList[i++]=ui.lb_3_27;
	LabelSortList[i++]=ui.lb_3_26;
	LabelSortList[i++]=ui.lb_3_25;
	LabelSortList[i++]=ui.lb_3_24;
	LabelSortList[i++]=ui.lb_3_23;
	LabelSortList[i++]=ui.lb_3_22;
	LabelSortList[i++]=ui.lb_3_21;
	LabelSortList[i++]=ui.lb_3_20;
	LabelSortList[i++]=ui.lb_3_19;
	LabelSortList[i++]=ui.lb_3_18;
	LabelSortList[i++]=ui.lb_3_17;
	LabelSortList[i++]=ui.lb_3_16;
	LabelSortList[i++]=ui.lb_3_15;
	LabelSortList[i++]=ui.lb_3_14;
	LabelSortList[i++]=ui.lb_3_13;
	LabelSortList[i++]=ui.lb_3_12;
	LabelSortList[i++]=ui.lb_3_11;
	LabelSortList[i++]=ui.lb_3_10;
	LabelSortList[i++]=ui.lb_3_9;
	LabelSortList[i++]=ui.lb_3_8;
	LabelSortList[i++]=ui.lb_3_7;
	LabelSortList[i++]=ui.lb_3_6;
	LabelSortList[i++]=ui.lb_3_5;
	LabelSortList[i++]=ui.lb_3_4;
	LabelSortList[i++]=ui.lb_3_3;
	LabelSortList[i++]=ui.lb_3_2;
	LabelSortList[i++]=ui.lb_3_1;

	LabelSortList[i++]=ui.lb_4_31;
	LabelSortList[i++]=ui.lb_4_32;
	LabelSortList[i++]=ui.lb_4_29;
	LabelSortList[i++]=ui.lb_4_30;
	LabelSortList[i++]=ui.lb_4_27;
	LabelSortList[i++]=ui.lb_4_28;
	LabelSortList[i++]=ui.lb_4_25;
	LabelSortList[i++]=ui.lb_4_26;
	LabelSortList[i++]=ui.lb_4_23;
	LabelSortList[i++]=ui.lb_4_24;
	LabelSortList[i++]=ui.lb_4_21;
	LabelSortList[i++]=ui.lb_4_22;
	LabelSortList[i++]=ui.lb_4_19;
	LabelSortList[i++]=ui.lb_4_20;
	LabelSortList[i++]=ui.lb_4_17;
	LabelSortList[i++]=ui.lb_4_18;
	LabelSortList[i++]=ui.lb_4_15;
	LabelSortList[i++]=ui.lb_4_16;
	LabelSortList[i++]=ui.lb_4_13;
	LabelSortList[i++]=ui.lb_4_14;
	LabelSortList[i++]=ui.lb_4_11;
	LabelSortList[i++]=ui.lb_4_12;
	LabelSortList[i++]=ui.lb_4_9;
	LabelSortList[i++]=ui.lb_4_10;
	LabelSortList[i++]=ui.lb_4_7;
	LabelSortList[i++]=ui.lb_4_8;
	LabelSortList[i++]=ui.lb_4_5;
	LabelSortList[i++]=ui.lb_4_6;
	LabelSortList[i++]=ui.lb_4_3;
	LabelSortList[i++]=ui.lb_4_4;
	LabelSortList[i++]=ui.lb_4_1;
	LabelSortList[i++]=ui.lb_4_2;

	//ToolButton
	ui.tb_1		->setCheckable(true);
	ui.tb_2		->setCheckable(true);
	ui.tb_3		->setCheckable(true);
	ui.tb_4		->setCheckable(true);
	ui.tb_5		->setCheckable(true);
	ui.tb_6		->setCheckable(true);
	ui.tbLeft_1	->setCheckable(true);
	ui.tbLeft_2	->setCheckable(true);
	ui.tbLeft_3	->setCheckable(true);
	ui.tbLeft_4	->setCheckable(true);
	ui.tbLeft_5	->setCheckable(true);
	ui.tbLeft_6	->setCheckable(true);
	ui.tbLeft_7	->setCheckable(true);
	ui.tbLeft_8	->setCheckable(true);
	ui.tbRight_1->setCheckable(true);
	ui.tbRight_2->setCheckable(true);
	ui.tbRight_3->setCheckable(true);
	ui.tbRight_4->setCheckable(true);
	ui.tbRight_5->setCheckable(true);
	ui.tbRight_6->setCheckable(true);
	ui.tbRight_7->setCheckable(true);
	ui.tbRight_8->setCheckable(true);
	ui.tbLeft	->setCheckable(true);
	ui.tbRight	->setCheckable(true);
	ui.tbOnOff	->setCheckable(true);

	//Color
	QPalette palette;
	palette.setColor(QPalette::Background,QColor(Qt::green));
	ui.fm_1_1	->setPalette(palette);
	ui.fm_1_3	->setPalette(palette);
	ui.fm_1_5	->setPalette(palette);
	ui.fm_1_7	->setPalette(palette);
	ui.fm_1_9	->setPalette(palette);
	ui.fm_1_11	->setPalette(palette);
	ui.fm_1_13	->setPalette(palette);
	ui.fm_1_15	->setPalette(palette);
	ui.fm_1_17	->setPalette(palette);
	ui.fm_1_19	->setPalette(palette);
	ui.fm_1_21	->setPalette(palette);
	ui.fm_1_23	->setPalette(palette);
	palette.setColor(QPalette::Background,QColor(Qt::darkGreen));
	ui.fm_1_2	->setPalette(palette);
	ui.fm_1_4	->setPalette(palette);
	ui.fm_1_6	->setPalette(palette);
	ui.fm_1_8	->setPalette(palette);
	ui.fm_1_10	->setPalette(palette);
	ui.fm_1_12	->setPalette(palette);
	ui.fm_1_14	->setPalette(palette);
	ui.fm_1_16	->setPalette(palette);
	ui.fm_1_18	->setPalette(palette);
	ui.fm_1_20	->setPalette(palette);
	ui.fm_1_22	->setPalette(palette);
	ui.fm_1_24	->setPalette(palette);
	palette.setColor(QPalette::Background,QColor(Qt::darkGray));
	ui.fm_1		->setPalette(palette);
	ui.fm_2		->setPalette(palette);
	ui.fm_3		->setPalette(palette);
	ui.fm_4		->setPalette(palette);
	ui.fm_5		->setPalette(palette);
	ui.fm_6		->setPalette(palette);

	ui.dwLeft	->setFeatures(QDockWidget::NoDockWidgetFeatures);
	ui.dwRight	->setFeatures(QDockWidget::NoDockWidgetFeatures);

	//connect
	connect(ui.tb_1,			SIGNAL(toggled(bool)),		this,SLOT(tb_1Toggled(bool)));
	connect(ui.tb_2,			SIGNAL(toggled(bool)),		this,SLOT(tb_2Toggled(bool)));
	connect(ui.tb_3,			SIGNAL(toggled(bool)),		this,SLOT(tb_3Toggled(bool)));
	connect(ui.tb_4,			SIGNAL(toggled(bool)),		this,SLOT(tb_4Toggled(bool)));
	connect(ui.tb_5,			SIGNAL(toggled(bool)),		this,SLOT(tb_5Toggled(bool)));
	connect(ui.tb_6,			SIGNAL(toggled(bool)),		this,SLOT(tb_6Toggled(bool)));
	connect(ui.tbLeft_1,		SIGNAL(toggled(bool)),		this,SLOT(tbLeft_1Toggled(bool)));
	connect(ui.tbLeft_2,		SIGNAL(toggled(bool)),		this,SLOT(tbLeft_2Toggled(bool)));
	connect(ui.tbLeft_3,		SIGNAL(toggled(bool)),		this,SLOT(tbLeft_3Toggled(bool)));
	connect(ui.tbLeft_4,		SIGNAL(toggled(bool)),		this,SLOT(tbLeft_4Toggled(bool)));
	connect(ui.tbLeft_5,		SIGNAL(toggled(bool)),		this,SLOT(tbLeft_5Toggled(bool)));
	connect(ui.tbLeft_6,		SIGNAL(toggled(bool)),		this,SLOT(tbLeft_6Toggled(bool)));
	connect(ui.tbLeft_7,		SIGNAL(toggled(bool)),		this,SLOT(tbLeft_7Toggled(bool)));
	connect(ui.tbLeft_8,		SIGNAL(toggled(bool)),		this,SLOT(tbLeft_8Toggled(bool)));
	connect(ui.tbRight_1,		SIGNAL(toggled(bool)),		this,SLOT(tbRight_1Toggled(bool)));
	connect(ui.tbRight_2,		SIGNAL(toggled(bool)),		this,SLOT(tbRight_2Toggled(bool)));
	connect(ui.tbRight_3,		SIGNAL(toggled(bool)),		this,SLOT(tbRight_3Toggled(bool)));
	connect(ui.tbRight_4,		SIGNAL(toggled(bool)),		this,SLOT(tbRight_4Toggled(bool)));
	connect(ui.tbRight_5,		SIGNAL(toggled(bool)),		this,SLOT(tbRight_5Toggled(bool)));
	connect(ui.tbRight_6,		SIGNAL(toggled(bool)),		this,SLOT(tbRight_6Toggled(bool)));
	connect(ui.tbRight_7,		SIGNAL(toggled(bool)),		this,SLOT(tbRight_7Toggled(bool)));
	connect(ui.tbRight_8,		SIGNAL(toggled(bool)),		this,SLOT(tbRight_8Toggled(bool)));
	connect(ui.tbLeft,			SIGNAL(toggled(bool)),		this,SLOT(tbLeftToggled(bool)));
	connect(ui.tbRight,			SIGNAL(toggled(bool)),		this,SLOT(tbRightToggled(bool)));
	connect(ui.tbOnOff,			SIGNAL(toggled(bool)),		this,SLOT(tbOnOffToggled(bool)));
	connect(ui.sbBrightness,	SIGNAL(valueChanged(int)),	this,SLOT(sbBrightnessValueChanged(int)));
	connect(ui.vsBrightness,	SIGNAL(valueChanged(int)),	this,SLOT(vsBrightnessValueChanged(int)));
	connect(ui.pbTransport,		SIGNAL(clicked()),			this,SLOT(pbTransportClicked()));
	connect(ui.pbAllSelect,		SIGNAL(clicked()),			this,SLOT(pbAllSelectClicked()));
	connect(ui.pbClearSelect,	SIGNAL(clicked()),			this,SLOT(pbClearSelectClicked()));
	connect(ui.pbOK,			SIGNAL(clicked()),			this,SLOT(pbOKClicked()));
	connect(ui.pbCancel,		SIGNAL(clicked()),			this,SLOT(pbCancelClicked()));

	//‰æ–ÊƒZƒbƒg
	BLight=*p;
	for(int i=0;i<LEDBARNUMB;i++){
		for(int j=0;j<LEDsNumb;j++){
			int Cnt=i*LEDsNumb+j;
			if(BLight.LEDBright[i][j]==0)
				ChkSortList[Cnt]->setChecked(false);
			else
				ChkSortList[Cnt]->setChecked(true);
			LabelSortList[Cnt]->setText(QString::number(BLight.LEDBright[i][j]));
			BLight.SaveLEDBright[i][j]=BLight.LEDBright[i][j];
		}
	}
	p->GetLayersBase()->InstallOperationLog(this);
}

LightDLL1Form::~LightDLL1Form()
{
}

void LightDLL1Form::tb_1Toggled(bool Tog)
{
	int First	=0;
	int End		=1;
	SetCheckBox(First<<5,(End<<5),Tog);
}

void LightDLL1Form::tb_2Toggled(bool Tog)
{
	int First	=1;
	int End		=2;
	SetCheckBox(First<<5,(End<<5),Tog);
}

void LightDLL1Form::tb_3Toggled(bool Tog)
{
	int First	=2;
	int End		=3;
	SetCheckBox(First<<5,(End<<5),Tog);
}

void LightDLL1Form::tb_4Toggled(bool Tog)
{
	int First	=3;
	int End		=4;
	SetCheckBox(First<<5,(End<<5),Tog);
}

void LightDLL1Form::tb_5Toggled(bool Tog)
{
	int First	=4;
	int End		=5;
	SetCheckBox(First<<5,(End<<5),Tog);
}

void LightDLL1Form::tb_6Toggled(bool Tog)
{
	int First	=5;
	int End		=6;
	SetCheckBox(First<<5,(End<<5),Tog);
}

void LightDLL1Form::tbLeft_1Toggled(bool Tog)
{
	for(int i=0;i<12;i++)
		ChkList[i<<3]->setChecked(Tog);
}

void LightDLL1Form::tbLeft_2Toggled(bool Tog)
{
	for(int i=0;i<12;i++)
		ChkList[(i<<3)+1]->setChecked(Tog);
}

void LightDLL1Form::tbLeft_3Toggled(bool Tog)
{
	for(int i=0;i<12;i++)
		ChkList[(i<<3)+2]->setChecked(Tog);
}

void LightDLL1Form::tbLeft_4Toggled(bool Tog)
{
	for(int i=0;i<12;i++)
		ChkList[(i<<3)+3]->setChecked(Tog);
}

void LightDLL1Form::tbLeft_5Toggled(bool Tog)
{
	for(int i=0;i<12;i++)
		ChkList[(i<<3)+4]->setChecked(Tog);
}

void LightDLL1Form::tbLeft_6Toggled(bool Tog)
{
	for(int i=0;i<12;i++)
		ChkList[(i<<3)+5]->setChecked(Tog);
}

void LightDLL1Form::tbLeft_7Toggled(bool Tog)
{
	for(int i=0;i<12;i++)
		ChkList[(i<<3)+6]->setChecked(Tog);
}

void LightDLL1Form::tbLeft_8Toggled(bool Tog)
{
	for(int i=0;i<12;i++)
		ChkList[(i<<3)+7]->setChecked(Tog);
}

void LightDLL1Form::tbRight_1Toggled(bool Tog)
{
	for(int i=12;i<24;i++)
		ChkList[i<<3]->setChecked(Tog);
}

void LightDLL1Form::tbRight_2Toggled(bool Tog)
{
	for(int i=12;i<24;i++)
		ChkList[(i<<3)+1]->setChecked(Tog);
}

void LightDLL1Form::tbRight_3Toggled(bool Tog)
{
	for(int i=12;i<24;i++)
		ChkList[(i<<3)+2]->setChecked(Tog);
}

void LightDLL1Form::tbRight_4Toggled(bool Tog)
{
	for(int i=12;i<24;i++)
		ChkList[(i<<3)+3]->setChecked(Tog);
}

void LightDLL1Form::tbRight_5Toggled(bool Tog)
{
	for(int i=12;i<24;i++)
		ChkList[(i<<3)+4]->setChecked(Tog);
}

void LightDLL1Form::tbRight_6Toggled(bool Tog)
{
	for(int i=12;i<24;i++)
		ChkList[(i<<3)+5]->setChecked(Tog);
}

void LightDLL1Form::tbRight_7Toggled(bool Tog)
{
	for(int i=12;i<24;i++)
		ChkList[(i<<3)+6]->setChecked(Tog);
}

void LightDLL1Form::tbRight_8Toggled(bool Tog)
{
	for(int i=12;i<24;i++)
		ChkList[(i<<3)+7]->setChecked(Tog);
}

void LightDLL1Form::tbLeftToggled(bool Tog)
{
	int First	=0;
	int End		=3;
	SetCheckBox(First<<5,(End<<5),Tog);
}

void LightDLL1Form::tbRightToggled(bool Tog)
{
	int First	=3;
	int End		=6;
	SetCheckBox(First<<5,(End<<5),Tog);
}

void LightDLL1Form::tbOnOffToggled(bool Tog)
{
	if(Tog){
		ui.pgbLight->setValue(0);
		for(int i=0;i<LEDBARNUMB;i++){
			for(int j=0;j<LEDsNumb;j++){
				BLight.CLED[i].Change(j,BLight.SaveLEDBright[i][j]);
				BLight.CLED[i].OutData(j,BLight.Gain[i][j]);
			}
			ui.pgbLight->setValue(100*(i+1)/LEDBARNUMB);
		}
	}
	else
		BLight.SetLighting(Tog);
}

void LightDLL1Form::sbBrightnessValueChanged(int Val)
{
	ui.vsBrightness->setValue(Val);
}

void LightDLL1Form::vsBrightnessValueChanged(int Val)
{
	ui.sbBrightness->setValue(Val);
}

void LightDLL1Form::pbTransportClicked()
{
	ui.pgbLight->setValue(0);
	for(int i=0;i<LEDBarNumb;i++){
		for(int j=0;j<LEDNumbPerLine;j++){
			int Cnt=i*LEDNumbPerLine+j;
			if(ChkSortList[Cnt]->isChecked()){
				BLight.SaveLEDBright[i][j]=(short)ui.sbBrightness->value();
				LabelSortList[Cnt]->setText(QString::number(ui.sbBrightness->value()));
			}
		}
		ui.pgbLight->setValue(100*(i+1)/LEDBARNUMB);
	}
}

void LightDLL1Form::pbAllSelectClicked()
{
	int First	=0;
	int End		=6;
	SetCheckBox(First<<5,(End<<5),true);
}

void LightDLL1Form::pbClearSelectClicked()
{
	int First	=0;
	int End		=6;
	SetCheckBox(First<<5,(End<<5),false);
}

void LightDLL1Form::pbOKClicked()
{
	for(int i=0;i<LEDBarNumb;i++){
		for(int j=0;j<LEDNumbPerLine;j++){
			BLight.LEDBright[i][j]=BLight.SaveLEDBright[i][j];
		}
	}
	accept();
}

void LightDLL1Form::pbCancelClicked()
{
	reject();
}

void LightDLL1Form::SetCheckBox(int First,int End,bool Tog)
{
	for(int i=First;i<End;i++)
		ChkList[i]->setChecked(Tog);
}

