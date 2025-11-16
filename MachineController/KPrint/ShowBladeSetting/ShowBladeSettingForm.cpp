#include "ShowBladeSettingForm.h"
#include "ui_ShowBladeSettingForm.h"
#include "EasyPropertyDentMeasureForm.h"
#include "XMeasureCommon.h"
#include "InputPanelDialog.h"

ShowBladeSettingForm::ShowBladeSettingForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::ShowBladeSettingForm)
{
    ui->setupUi(this);
	PropertyForm=NULL;
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ShowBladeSettingForm::~ShowBladeSettingForm()
{
    delete ui;
}

void	ShowBladeSettingForm::ResizeAction()
{
	ui->tableWidgetBladeWidth->resize(width()-ui->tableWidgetBladeWidth	->geometry().left(),ui->tableWidgetBladeWidth->height());
	ui->tableWidgetBladeY	 ->resize(width()-ui->tableWidgetBladeY		->geometry().left(),ui->tableWidgetBladeY	 ->height());
	ui->tableWidgetBladeX	 ->resize(width()-ui->tableWidgetBladeX		->geometry().left(),ui->tableWidgetBladeX	 ->height());
	ui->tableWidgetBladeX	 ->resize(width()-ui->tableWidgetBladeR		->geometry().left(),ui->tableWidgetBladeR	 ->height());

	ui->tableWidgetBladeWidth->setColumnWidth(0,(width()-ui->tableWidgetBladeWidth	->geometry().left()-40)/2);
	ui->tableWidgetBladeWidth->setColumnWidth(1,(width()-ui->tableWidgetBladeWidth	->geometry().left()-40)/2);
	ui->tableWidgetBladeY	 ->setColumnWidth(0,(width()-ui->tableWidgetBladeY	->geometry().left()-40)/2);
	ui->tableWidgetBladeY	 ->setColumnWidth(1,(width()-ui->tableWidgetBladeY	->geometry().left()-40)/2);
	ui->tableWidgetBladeX	 ->setColumnWidth(0,(width()-ui->tableWidgetBladeX	->geometry().left()-40)/2);
	ui->tableWidgetBladeX	 ->setColumnWidth(1,(width()-ui->tableWidgetBladeX	->geometry().left()-40)/2);
	ui->tableWidgetBladeR	 ->setColumnWidth(0,(width()-ui->tableWidgetBladeR	->geometry().left()-40)/2);
	ui->tableWidgetBladeR	 ->setColumnWidth(1,(width()-ui->tableWidgetBladeR	->geometry().left()-40)/2);
}
struct	MeasureHVInfo	*FindMeasureHVInfo(BladeMeasure &BData
							,bool	bOnlyInside
							,bool	bHorizontal
							,bool	bFrom0
							,bool	bPartnerFrom0
							,int	turn)
{
	int	n=0;
	for(int i=0;i<BData.CountGenDatas;i++){
		if(BData.GenDatas[i].bOnlyInside==bOnlyInside
		&& BData.GenDatas[i].bHorizontal==bHorizontal
		&& BData.GenDatas[i].bFrom0==bFrom0
		&& BData.GenDatas[i].bPartnerFrom0==bPartnerFrom0){
			if(n==turn){
				return &BData.GenDatas[i];
			}
			n++;
		}
	}
	return NULL;
}

void	ShowBladeSettingForm::BuildForShow(void)
{
	if(PropertyForm!=NULL){
		IntegrationCmdUpdateBladeList	RCmd(GetLayersBase());
		PropertyForm->TransmitDirectly(&RCmd);
	}
	StartPage();
}

EasyPropertyDentMeasureForm *ShowBladeSettingForm::GetEasyPropertyDentMeasureForm(void)
{
	GUIFormBase *Ret[10];
	int N=GetLayersBase()->EnumGUIInst(/**/"KidaPrint",/**/"EasyPropertyDentMeasure",Ret ,10);
	for(int SlaveNo=0;SlaveNo<2;SlaveNo++){
		for(int i=0;i<N;i++){
			EasyPropertyDentMeasureForm		*f=dynamic_cast<EasyPropertyDentMeasureForm	*>(Ret[i]);
			if(f!=NULL && f->SlaveNo==SlaveNo){
				return f;
			}
		}
	}
	return NULL;
}

void	ShowBladeSettingForm::StartPage	(void)
{
	GUIFormBase *Ret[10];
	int N=GetLayersBase()->EnumGUIInst(/**/"KidaPrint",/**/"EasyPropertyDentMeasure",Ret ,10);
	for(int SlaveNo=0;SlaveNo<2;SlaveNo++){
		for(int i=0;i<N;i++){
			EasyPropertyDentMeasureForm		*f=dynamic_cast<EasyPropertyDentMeasureForm	*>(Ret[i]);
			if(f!=NULL && f->SlaveNo==SlaveNo){
				//IntegrationReqBladeList	DMCmd(GetLayersBase());
				//f->TransmitDirectly(&DMCmd);

				if(f->BladeUpsideDown==false){
					{
						struct	MeasureHVInfo	*s=FindMeasureHVInfo(f->BladeMeasureData,true,true,true,true,0);
						if(s!=NULL){
							PropertyForm=f;
							::SetDataToTable(ui->tableWidgetBladeWidth ,0,0 ,QString::number(s->CorrectLength -s->OKWidth/2.0,'f',2),Qt::ItemIsEditable);
							::SetDataToTable(ui->tableWidgetBladeWidth ,1,0 ,QString::number(s->CorrectLength +s->OKWidth/2.0,'f',2),Qt::ItemIsEditable);
						}
					}
					{
						struct	MeasureHVInfo	*s=FindMeasureHVInfo(f->BladeMeasureData,true,true,true,false,0);
						if(s!=NULL){
							PropertyForm=f;
							::SetDataToTable(ui->tableWidgetBladeWidth ,0,1 ,QString::number(s->CorrectLength -s->OKWidth/2.0,'f',2),Qt::ItemIsEditable);
							::SetDataToTable(ui->tableWidgetBladeWidth ,1,1 ,QString::number(s->CorrectLength +s->OKWidth/2.0,'f',2),Qt::ItemIsEditable);
						}
					}
					{
						struct	MeasureHVInfo	*s=FindMeasureHVInfo(f->BladeMeasureData,false,true,false,true,0);
						if(s!=NULL){
							PropertyForm=f;
							::SetDataToTable(ui->tableWidgetBladeY ,0,0 ,QString::number(s->CorrectLength -s->OKWidth/2.0,'f',2),Qt::ItemIsEditable);
							::SetDataToTable(ui->tableWidgetBladeY ,1,0 ,QString::number(s->CorrectLength +s->OKWidth/2.0,'f',2),Qt::ItemIsEditable);
						}
					}
					{
						struct	MeasureHVInfo	*s=FindMeasureHVInfo(f->BladeMeasureData,false,true,false,false,0);
						if(s!=NULL){
							PropertyForm=f;
							::SetDataToTable(ui->tableWidgetBladeY ,0,1 ,QString::number(s->CorrectLength -s->OKWidth/2.0,'f',2),Qt::ItemIsEditable);
							::SetDataToTable(ui->tableWidgetBladeY ,1,1 ,QString::number(s->CorrectLength +s->OKWidth/2.0,'f',2),Qt::ItemIsEditable);
						}
					}
					{
						struct	MeasureHVInfo	*s=FindMeasureHVInfo(f->BladeMeasureData,false,true,false,true,1);
						if(s!=NULL){
							PropertyForm=f;
							::SetDataToTable(ui->tableWidgetBladeY ,0,2 ,QString::number(s->CorrectLength -s->OKWidth/2.0,'f',2),Qt::ItemIsEditable);
							::SetDataToTable(ui->tableWidgetBladeY ,1,2 ,QString::number(s->CorrectLength +s->OKWidth/2.0,'f',2),Qt::ItemIsEditable);
						}
					}
					{
						struct	MeasureHVInfo	*s=FindMeasureHVInfo(f->BladeMeasureData,false,false,true,true,0);
						if(s!=NULL){
							PropertyForm=f;
							::SetDataToTable(ui->tableWidgetBladeX ,0,0 ,QString::number(s->CorrectLength -s->OKWidth/2.0,'f',2),Qt::ItemIsEditable);
							::SetDataToTable(ui->tableWidgetBladeX ,1,0 ,QString::number(s->CorrectLength +s->OKWidth/2.0,'f',2),Qt::ItemIsEditable);
						}
					}
					{
						struct	MeasureHVInfo	*s=FindMeasureHVInfo(f->BladeMeasureData,false,false,false,true,0);
						if(s!=NULL){
							PropertyForm=f;
							::SetDataToTable(ui->tableWidgetBladeX ,0,1 ,QString::number(s->CorrectLength -s->OKWidth/2.0,'f',2),Qt::ItemIsEditable);
							::SetDataToTable(ui->tableWidgetBladeX ,1,1 ,QString::number(s->CorrectLength +s->OKWidth/2.0,'f',2),Qt::ItemIsEditable);
						}
					}
					{
						//Pet
						struct	MeasureHVInfo	*s=FindMeasureHVInfo(f->FilmMeasureData,true,false,false,true,0);
						if(s!=NULL){
							PropertyForm=f;
							::SetDataToTable(ui->tableWidgetBladeR ,0,0 ,QString::number(s->CorrectLength -s->OKWidth/2.0,'f',2),Qt::ItemIsEditable);
							::SetDataToTable(ui->tableWidgetBladeR ,1,0 ,QString::number(s->CorrectLength +s->OKWidth/2.0,'f',2),Qt::ItemIsEditable);
						}
					}
					{
						//Pet
						struct	MeasureHVInfo	*s=FindMeasureHVInfo(f->FilmMeasureData,true,false,false,false,0);
						if(s!=NULL){
							PropertyForm=f;
							::SetDataToTable(ui->tableWidgetBladeR ,0,1 ,QString::number(s->CorrectLength -s->OKWidth/2.0,'f',2),Qt::ItemIsEditable);
							::SetDataToTable(ui->tableWidgetBladeR ,1,1 ,QString::number(s->CorrectLength +s->OKWidth/2.0,'f',2),Qt::ItemIsEditable);
						}
					}
				}
				else{
					{
						struct	MeasureHVInfo	*s=FindMeasureHVInfo(f->BladeMeasureData,true,true,true,true,0);
						if(s!=NULL){
							PropertyForm=f;
							::SetDataToTable(ui->tableWidgetBladeWidth ,0,1 ,QString::number(s->CorrectLength -s->OKWidth/2.0,'f',2),Qt::ItemIsEditable);
							::SetDataToTable(ui->tableWidgetBladeWidth ,1,1 ,QString::number(s->CorrectLength +s->OKWidth/2.0,'f',2),Qt::ItemIsEditable);
						}
					}
					{
						struct	MeasureHVInfo	*s=FindMeasureHVInfo(f->BladeMeasureData,true,true,true,false,0);
						if(s!=NULL){
							PropertyForm=f;
							::SetDataToTable(ui->tableWidgetBladeWidth ,0,0 ,QString::number(s->CorrectLength -s->OKWidth/2.0,'f',2),Qt::ItemIsEditable);
							::SetDataToTable(ui->tableWidgetBladeWidth ,1,0 ,QString::number(s->CorrectLength +s->OKWidth/2.0,'f',2),Qt::ItemIsEditable);
						}
					}
					{
						struct	MeasureHVInfo	*s=FindMeasureHVInfo(f->BladeMeasureData,false,true,false,true,0);
						if(s!=NULL){
							PropertyForm=f;
							::SetDataToTable(ui->tableWidgetBladeY ,0,1 ,QString::number(s->CorrectLength -s->OKWidth/2.0,'f',2),Qt::ItemIsEditable);
							::SetDataToTable(ui->tableWidgetBladeY ,1,1 ,QString::number(s->CorrectLength +s->OKWidth/2.0,'f',2),Qt::ItemIsEditable);
						}
					}
					{
						struct	MeasureHVInfo	*s=FindMeasureHVInfo(f->BladeMeasureData,false,true,false,false,0);
						if(s!=NULL){
							PropertyForm=f;
							::SetDataToTable(ui->tableWidgetBladeY ,0,0 ,QString::number(s->CorrectLength -s->OKWidth/2.0,'f',2),Qt::ItemIsEditable);
							::SetDataToTable(ui->tableWidgetBladeY ,1,0 ,QString::number(s->CorrectLength +s->OKWidth/2.0,'f',2),Qt::ItemIsEditable);
						}
					}
					{
						struct	MeasureHVInfo	*s=FindMeasureHVInfo(f->BladeMeasureData,false,true,false,true,1);
						if(s!=NULL){
							PropertyForm=f;
							::SetDataToTable(ui->tableWidgetBladeY ,0,2 ,QString::number(s->CorrectLength -s->OKWidth/2.0,'f',2),Qt::ItemIsEditable);
							::SetDataToTable(ui->tableWidgetBladeY ,1,2 ,QString::number(s->CorrectLength +s->OKWidth/2.0,'f',2),Qt::ItemIsEditable);
						}
					}
					{
						struct	MeasureHVInfo	*s=FindMeasureHVInfo(f->BladeMeasureData,false,false,true,true,0);
						if(s!=NULL){
							PropertyForm=f;
							::SetDataToTable(ui->tableWidgetBladeX ,0,1 ,QString::number(s->CorrectLength -s->OKWidth/2.0,'f',2),Qt::ItemIsEditable);
							::SetDataToTable(ui->tableWidgetBladeX ,1,1 ,QString::number(s->CorrectLength +s->OKWidth/2.0,'f',2),Qt::ItemIsEditable);
						}
					}
					{
						struct	MeasureHVInfo	*s=FindMeasureHVInfo(f->BladeMeasureData,false,false,false,true,0);
						if(s!=NULL){
							PropertyForm=f;
							::SetDataToTable(ui->tableWidgetBladeX ,0,0 ,QString::number(s->CorrectLength -s->OKWidth/2.0,'f',2),Qt::ItemIsEditable);
							::SetDataToTable(ui->tableWidgetBladeX ,1,0 ,QString::number(s->CorrectLength +s->OKWidth/2.0,'f',2),Qt::ItemIsEditable);
						}
					}
					{
						//Pet
						struct	MeasureHVInfo	*s=FindMeasureHVInfo(f->FilmMeasureData,true,false,false,true,0);
						if(s!=NULL){
							PropertyForm=f;
							::SetDataToTable(ui->tableWidgetBladeR ,0,1 ,QString::number(s->CorrectLength -s->OKWidth/2.0,'f',2),Qt::ItemIsEditable);
							::SetDataToTable(ui->tableWidgetBladeR ,1,1 ,QString::number(s->CorrectLength +s->OKWidth/2.0,'f',2),Qt::ItemIsEditable);
						}
					}
					{
						//Pet
						struct	MeasureHVInfo	*s=FindMeasureHVInfo(f->FilmMeasureData,true,false,false,false,0);
						if(s!=NULL){
							PropertyForm=f;
							::SetDataToTable(ui->tableWidgetBladeR ,0,0 ,QString::number(s->CorrectLength -s->OKWidth/2.0,'f',2),Qt::ItemIsEditable);
							::SetDataToTable(ui->tableWidgetBladeR ,1,0 ,QString::number(s->CorrectLength +s->OKWidth/2.0,'f',2),Qt::ItemIsEditable);
						}
					}
				}
			}
		}
	}
}

void ShowBladeSettingForm::on_tableWidgetBladeWidth_doubleClicked(const QModelIndex &index)
{
	if(PropertyForm!=NULL){
		QString	Str=::GetDataToTable(ui->tableWidgetBladeWidth ,index.column() ,index.row());
		InputPanelDialog	D(IPD_Number ,Str);
		if(D.exec()==(bool)true){
			GUIFormBase *Ret[10];
			int N=GetLayersBase()->EnumGUIInst(/**/"KidaPrint",/**/"EasyPropertyDentMeasure",Ret ,10);
			for(int SlaveNo=0;SlaveNo<2;SlaveNo++){
				for(int i=0;i<N;i++){
					EasyPropertyDentMeasureForm		*f=dynamic_cast<EasyPropertyDentMeasureForm	*>(Ret[i]);
					if(f!=NULL && f->SlaveNo==SlaveNo){
						struct	MeasureHVInfo	*s=NULL;
						if(f->BladeUpsideDown==false){
							if(index.row() ==0)
								s=FindMeasureHVInfo(PropertyForm->BladeMeasureData,true,true,true,true,0);
							else
								s=FindMeasureHVInfo(PropertyForm->BladeMeasureData,true,true,true,false,0);
						}
						else{
							if(index.row() !=0)
								s=FindMeasureHVInfo(PropertyForm->BladeMeasureData,true,true,true,true,0);
							else
								s=FindMeasureHVInfo(PropertyForm->BladeMeasureData,true,true,true,false,0);
						}
						if(s!=NULL){
							double	L=s->CorrectLength -s->OKWidth/2.0;
							double	H=s->CorrectLength +s->OKWidth/2.0;
							bool	ok=false;
							if(index.column()==0)
								L=D.GetResult().toDouble(&ok);
							else
								H=D.GetResult().toDouble(&ok);
							if(ok==true){
								s->CorrectLength	=(H+L)/2;
								s->OKWidth			=fabs(H-L);
							}
						}

						IntegrationCmdUpdateBladeList	RCmd(GetLayersBase());
						PropertyForm->TransmitDirectly(&RCmd);
						StartPage();
					}
				}
			}
		}
	}
}

void ShowBladeSettingForm::on_tableWidgetBladeY_doubleClicked(const QModelIndex &index)
{
	if(PropertyForm!=NULL){
		QString	Str=::GetDataToTable(ui->tableWidgetBladeY ,index.column() ,index.row());
		InputPanelDialog	D(IPD_Number ,Str);
		if(D.exec()==(bool)true){
			GUIFormBase *Ret[10];
			int N=GetLayersBase()->EnumGUIInst(/**/"KidaPrint",/**/"EasyPropertyDentMeasure",Ret ,10);
			for(int SlaveNo=0;SlaveNo<2;SlaveNo++){
				for(int i=0;i<N;i++){
					EasyPropertyDentMeasureForm		*f=dynamic_cast<EasyPropertyDentMeasureForm	*>(Ret[i]);
					if(f!=NULL && f->SlaveNo==SlaveNo){
						struct	MeasureHVInfo	*s=NULL;
						if(f->BladeUpsideDown==false){
							if(index.row() ==0)
								s=FindMeasureHVInfo(PropertyForm->BladeMeasureData,false,true,false,true,0);
							else if(index.row() ==1)
								s=FindMeasureHVInfo(PropertyForm->BladeMeasureData,false,true,false,false,0);
							else if(index.row() ==2)
								s=FindMeasureHVInfo(PropertyForm->BladeMeasureData,false,true,false,true,1);
						}
						else{
							if(index.row() ==1)
								s=FindMeasureHVInfo(PropertyForm->BladeMeasureData,false,true,false,true,0);
							else if(index.row() ==0)
								s=FindMeasureHVInfo(PropertyForm->BladeMeasureData,false,true,false,false,0);
							else if(index.row() ==2)
								s=FindMeasureHVInfo(PropertyForm->BladeMeasureData,false,true,false,true,1);
						}
						if(s!=NULL){
							double	L=s->CorrectLength -s->OKWidth/2.0;
							double	H=s->CorrectLength +s->OKWidth/2.0;
							bool	ok=false;
							if(index.column()==0)
								L=D.GetResult().toDouble(&ok);
							else
								H=D.GetResult().toDouble(&ok);
							if(ok==true){
								s->CorrectLength	=(H+L)/2;
								s->OKWidth			=fabs(H-L);
							}
						}
						IntegrationCmdUpdateBladeList	RCmd(GetLayersBase());
						PropertyForm->TransmitDirectly(&RCmd);
						StartPage();
					}
				}
			}
		}
	}
}

void ShowBladeSettingForm::on_tableWidgetBladeX_doubleClicked(const QModelIndex &index)
{
	if(PropertyForm!=NULL){
		QString	Str=::GetDataToTable(ui->tableWidgetBladeX ,index.column() ,index.row());
		InputPanelDialog	D(IPD_Number ,Str);
		if(D.exec()==(bool)true){
			GUIFormBase *Ret[10];
			int N=GetLayersBase()->EnumGUIInst(/**/"KidaPrint",/**/"EasyPropertyDentMeasure",Ret ,10);
			for(int SlaveNo=0;SlaveNo<2;SlaveNo++){
				for(int i=0;i<N;i++){
					EasyPropertyDentMeasureForm		*f=dynamic_cast<EasyPropertyDentMeasureForm	*>(Ret[i]);
					if(f!=NULL && f->SlaveNo==SlaveNo){
						struct	MeasureHVInfo	*s=NULL;
						if(f->BladeUpsideDown==false){
							if(index.row() ==0)
								s=FindMeasureHVInfo(PropertyForm->BladeMeasureData,false,false,true,true,0);
							else
								s=FindMeasureHVInfo(PropertyForm->BladeMeasureData,false,false,false,true,0);
						}
						else{
							if(index.row() !=0)
								s=FindMeasureHVInfo(PropertyForm->BladeMeasureData,false,false,true,true,0);
							else
								s=FindMeasureHVInfo(PropertyForm->BladeMeasureData,false,false,false,true,0);
						}
						if(s!=NULL){
							double	L=s->CorrectLength -s->OKWidth/2.0;
							double	H=s->CorrectLength +s->OKWidth/2.0;
							bool	ok=false;
							if(index.column()==0)
								L=D.GetResult().toDouble(&ok);
							else
								H=D.GetResult().toDouble(&ok);
							if(ok==true){
								s->CorrectLength	=(H+L)/2;
								s->OKWidth			=fabs(H-L);
							}
						}
						IntegrationCmdUpdateBladeList	RCmd(GetLayersBase());
						PropertyForm->TransmitDirectly(&RCmd);
						StartPage();
					}
				}
			}
		}
	}
}

void ShowBladeSettingForm::on_tableWidgetBladeR_doubleClicked(const QModelIndex &index)
{
	if(PropertyForm!=NULL){
		QString	Str=::GetDataToTable(ui->tableWidgetBladeR ,index.column() ,index.row());
		InputPanelDialog	D(IPD_Number ,Str);
		if(D.exec()==(bool)true){
			GUIFormBase *Ret[10];
			int N=GetLayersBase()->EnumGUIInst(/**/"KidaPrint",/**/"EasyPropertyDentMeasure",Ret ,10);
			for(int SlaveNo=0;SlaveNo<2;SlaveNo++){
				for(int i=0;i<N;i++){
					EasyPropertyDentMeasureForm		*f=dynamic_cast<EasyPropertyDentMeasureForm	*>(Ret[i]);
					if(f!=NULL && f->SlaveNo==SlaveNo){
						struct	MeasureHVInfo	*s=NULL;
						if(f->BladeUpsideDown==false){
							if(index.row() ==0)
								s=FindMeasureHVInfo(PropertyForm->FilmMeasureData,true,false,false,true,0);
							else
								s=FindMeasureHVInfo(PropertyForm->FilmMeasureData,true,false,false,false,0);
						}
						else{
							if(index.row() !=0)
								s=FindMeasureHVInfo(PropertyForm->FilmMeasureData,true,false,false,false,0);
							else
								s=FindMeasureHVInfo(PropertyForm->FilmMeasureData,true,false,false,true,0);
						}
						if(s!=NULL){
							double	L=s->CorrectLength -s->OKWidth/2.0;
							double	H=s->CorrectLength +s->OKWidth/2.0;
							bool	ok=false;
							if(index.column()==0)
								L=D.GetResult().toDouble(&ok);
							else
								H=D.GetResult().toDouble(&ok);
							if(ok==true){
								s->CorrectLength	=(H+L)/2;
								s->OKWidth			=fabs(H-L);
							}
						}
						IntegrationCmdUpdateBladeList	RCmd(GetLayersBase());
						PropertyForm->TransmitDirectly(&RCmd);
						StartPage();
					}
				}
			}
		}
	}
}

