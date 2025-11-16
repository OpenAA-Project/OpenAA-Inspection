#include "PQSystemSettingForm.h"
#include "ui_PQSystemSettingForm.h"
#include "XParamBase.h"
#include "XPQRunnerController.h"

PQSystemSettingForm::PQSystemSettingForm(LayersBase *base ,const QString &root ,const QString &name
                                        ,QWidget *parent) :
    PQSystemRunner(base ,root ,name,parent),
    ui(new Ui::PQSystemSettingForm)
{
    ui->setupUi(this);

	int EnableCondition=ParamEnableInTransfer;
	int	BarHeight=ui->frame->height();
	int	WGeneralWidth	=width();
	int	WGeneralHeight	=height()-BarHeight;
    LayersBasePQSystem	*LBase=(LayersBasePQSystem *)GetLayersBase();
	QWidget	*WGeneral	=ui->tabWidgetAllParam->widget(0);
	WTabGeneral=new WEditParameterTab(LBase->GetParamPQSystem() ,EnableCondition,WGeneral);
	WTabGeneral->move(0,0);
	WTabGeneral->resize(WGeneralWidth,WGeneralHeight);
}

PQSystemSettingForm::~PQSystemSettingForm()
{
    delete ui;
}
bool	PQSystemSettingForm::Initial(void)
{
	int EnableCondition=ParamEnableInTransfer;

	//LayersBasePQSystem	*PQLBase=(LayersBasePQSystem *)GetLayersBase();
	//int	N=0;
	//for(PQRunnerController *p=PQLBase->GetPQRunnerControllerContainer()->GetFirst();p!=NULL;p=p->GetNext(),N++){
	//	PQSystemRunner	*r=p->GetRunner();
	//	WEditParameterTab	*WTabAlgorithm=new WEditParameterTab(r ,ParamEnableInTransfer,NULL);
	//	ui->tabWidgetRunner->insertTab(N,WTabAlgorithm,r->GetDataText());
	//}

	int	BarHeight=ui->frame->height();
	int	WGeneralWidth	=width();
	int	WGeneralHeight	=height()-BarHeight;
	QWidget	*WGUI	=ui->tabWidgetAllParam->widget(1);
	WEditParameterTab	*WTabGUI=new WEditParameterTab(GetParamGUI() ,EnableCondition,WGUI);
	WTabGUI->move(0,0);
	WTabGUI->resize(WGeneralWidth,WGeneralHeight);
	return true;
}
const QString	PQSystemSettingForm::GetPath(void)
{
	return "PQSystem/設定";
}
void PQSystemSettingForm::on_ButtonOK_clicked()
{
	WTabGeneral->LoadFromWindow();
	LayersBasePQSystem	*LBase=(LayersBasePQSystem *)GetLayersBase();
	LBase->GetParamPQSystem()->SaveDefault(GetLayersBase()->GetUserPath());
}
