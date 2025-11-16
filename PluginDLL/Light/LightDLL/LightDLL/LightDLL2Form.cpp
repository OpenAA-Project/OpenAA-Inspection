#include "LightDLL2Form.h"

int		LightDLL2Form::BasePort[LEDBARNUMB];

LightDLL2Form::LightDLL2Form(LightDLL1 *p, QWidget *parent)
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

	//ToolButton
	ui.tb_1		->setCheckable(true);
	ui.tb_2		->setCheckable(true);

	ui.tbLeft_1	->setCheckable(true);
	ui.tbLeft_2	->setCheckable(true);
	ui.tbLeft_3	->setCheckable(true);
	ui.tbLeft_4	->setCheckable(true);
	ui.tbLeft_5	->setCheckable(true);
	ui.tbLeft_6	->setCheckable(true);
	ui.tbLeft_7	->setCheckable(true);
	ui.tbLeft_8	->setCheckable(true);

	ui.tbOnOff	->setCheckable(true);

	connect(ui.tb_1,			SIGNAL(toggled(bool)),		this,SLOT(tb_1Toggled(bool)));
	connect(ui.tb_2,			SIGNAL(toggled(bool)),		this,SLOT(tb_2Toggled(bool)));
	connect(ui.tbLeft_1,		SIGNAL(toggled(bool)),		this,SLOT(tbLeft_1Toggled(bool)));
	connect(ui.tbLeft_2,		SIGNAL(toggled(bool)),		this,SLOT(tbLeft_2Toggled(bool)));
	connect(ui.tbLeft_3,		SIGNAL(toggled(bool)),		this,SLOT(tbLeft_3Toggled(bool)));
	connect(ui.tbLeft_4,		SIGNAL(toggled(bool)),		this,SLOT(tbLeft_4Toggled(bool)));
	connect(ui.tbLeft_5,		SIGNAL(toggled(bool)),		this,SLOT(tbLeft_5Toggled(bool)));
	connect(ui.tbLeft_6,		SIGNAL(toggled(bool)),		this,SLOT(tbLeft_6Toggled(bool)));
	connect(ui.tbLeft_7,		SIGNAL(toggled(bool)),		this,SLOT(tbLeft_7Toggled(bool)));
	connect(ui.tbLeft_8,		SIGNAL(toggled(bool)),		this,SLOT(tbLeft_8Toggled(bool)));
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
			if(Cnt<64){
				if(BLight.LEDBright[i][j]==0)
					ChkSortList[Cnt]->setChecked(false);
				else
					ChkSortList[Cnt]->setChecked(true);
				LabelSortList[Cnt]->setText(QString::number(BLight.LEDBright[i][j]));
				BLight.SaveLEDBright[i][j]=BLight.LEDBright[i][j];
			}
		}
	}
	p->GetLayersBase()->InstallOperationLog(this);
}

LightDLL2Form::~LightDLL2Form()
{

}


void LightDLL2Form::tb_1Toggled(bool Tog)
{
	int First	=0;
	int End		=1;
	SetCheckBox(First<<5,(End<<5),Tog);
}

void LightDLL2Form::tb_2Toggled(bool Tog)
{
	int First	=1;
	int End		=2;
	SetCheckBox(First<<5,(End<<5),Tog);
}

void LightDLL2Form::tbLeft_1Toggled(bool Tog)
{
	for(int i=0;i<12;i++)
		ChkList[i<<3]->setChecked(Tog);
}

void LightDLL2Form::tbLeft_2Toggled(bool Tog)
{
	for(int i=0;i<12;i++)
		ChkList[(i<<3)+1]->setChecked(Tog);
}

void LightDLL2Form::tbLeft_3Toggled(bool Tog)
{
	for(int i=0;i<12;i++)
		ChkList[(i<<3)+2]->setChecked(Tog);
}

void LightDLL2Form::tbLeft_4Toggled(bool Tog)
{
	for(int i=0;i<12;i++)
		ChkList[(i<<3)+3]->setChecked(Tog);
}

void LightDLL2Form::tbLeft_5Toggled(bool Tog)
{
	for(int i=0;i<12;i++)
		ChkList[(i<<3)+4]->setChecked(Tog);
}

void LightDLL2Form::tbLeft_6Toggled(bool Tog)
{
	for(int i=0;i<12;i++)
		ChkList[(i<<3)+5]->setChecked(Tog);
}

void LightDLL2Form::tbLeft_7Toggled(bool Tog)
{
	for(int i=0;i<12;i++)
		ChkList[(i<<3)+6]->setChecked(Tog);
}

void LightDLL2Form::tbLeft_8Toggled(bool Tog)
{
	for(int i=0;i<12;i++)
		ChkList[(i<<3)+7]->setChecked(Tog);
}

void LightDLL2Form::tbOnOffToggled(bool Tog)
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

void LightDLL2Form::sbBrightnessValueChanged(int Val)
{
	ui.vsBrightness->setValue(Val);
}

void LightDLL2Form::vsBrightnessValueChanged(int Val)
{
	ui.sbBrightness->setValue(Val);
}

void LightDLL2Form::pbTransportClicked()
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

void LightDLL2Form::pbAllSelectClicked()
{
	int First	=0;
	int End		=6;
	SetCheckBox(First<<5,(End<<5),true);
}

void LightDLL2Form::pbClearSelectClicked()
{
	int First	=0;
	int End		=6;
	SetCheckBox(First<<5,(End<<5),false);
}

void LightDLL2Form::pbOKClicked()
{
	for(int i=0;i<LEDBarNumb;i++){
		for(int j=0;j<LEDNumbPerLine;j++){
			BLight.LEDBright[i][j]=BLight.SaveLEDBright[i][j];
		}
	}
	accept();
}

void LightDLL2Form::pbCancelClicked()
{
	reject();
}

void LightDLL2Form::SetCheckBox(int First,int End,bool Tog)
{
	for(int i=First;i<End;i++)
		ChkList[i]->setChecked(Tog);
}
