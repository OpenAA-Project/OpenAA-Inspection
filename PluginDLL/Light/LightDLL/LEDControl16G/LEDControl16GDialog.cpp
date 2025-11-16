#include "LEDControl16GDialog.h"
#include "ui_LEDControl16GDialog.h"
#include "XTypeDef.h"
//#include "TestStencilDialog.h"
#include "SetDefinitionDialog.h"
//#include "ShowIODialog.h"
//#include "IODelivererDialog.h"

QString	GetColorStr(int ColorType)
{
	switch(ColorType){
	case 0:
		return "None";
	case 1:
		return "Red";
	case 2:
		return "Green";
	case 3:
		return "Blue";
	case 4:
		return "IR";
	case 5:
		return "UV";
	case 6:
		return "White";
	case 7:
		return "Other";
	default:
		return "----";
	}
}

QColor	GetColor(int ColorType)
{
	switch(ColorType){
	case 0:
		return Qt::darkGray;
	case 1:
		return Qt::red;
	case 2:
		return Qt::green;
	case 3:
		return Qt::blue;
	case 4:
		return Qt::darkRed;
	case 5:
		return Qt::magenta;
	case 6:
		return Qt::white;
	case 7:
		return Qt::gray;
	default:
		return Qt::black;
	}
}

LineGroup::LineWindow::LineWindow(QWidget *parent)
{
	Label	 	=new QLabel		(parent);
	EditValue	=new QSpinBox	(parent);
	EditComment	=new QLineEdit	(parent);
	PointerForDefLine=NULL;
}

LineGroup::LineWindow::~LineWindow(void)
{
	Label		->setParent(NULL);
	EditValue	->setParent(NULL);
	EditComment	->setParent(NULL);

	delete	Label;
	delete	EditValue;
	delete	EditComment;
}

LineGroup::LineGroup(LEDControl16GDialog *p ,QWidget *parent)
	:Button(false,parent),Parent(p)
{
	for(int i=0;i<sizeof(LineData)/sizeof(LineData[0]);i++){
		LineData[i]=NULL;
	}
	LineNumb=0;
}
LineGroup::~LineGroup(void)
{
	for(int i=0;i<sizeof(LineData)/sizeof(LineData[0]);i++){
		if(LineData[i]==NULL){
			delete	LineData[i];
			LineData[i]=NULL;
		}
	}
}
void	LineGroup::AddLine(struct LightLineUnit	*L ,QWidget *parent)
{
	LineData[LineNumb]=new LineWindow(parent);
	LineData[LineNumb]->PointerForDefLine=L;
	LineData[LineNumb]->EditComment->setText(QString::fromWCharArray(L->Comment));
	LineNumb++;
}
			
void	LineGroup::LineWindow::SetY(int n)
{
	Label->setText(QString("Line ")+QString::number(n));
	Label->move(0,12+24*n);
	Label->resize(58,21);

	EditValue->move(70,12+24*n);
	EditValue->resize(101,21);

	EditComment->move(180,12+24*n);
	EditComment->resize(210,21);
}

void	LineGroup::LineWindow::Show(void)
{
	Label->show();
	EditValue->show();
	EditComment->show();
}
void	LineGroup::Initial(int n)
{
	Number=n;
	Button.setText(GetColorStr(ColorType));
	Button.setColor(GetColor(ColorType));
	Button.setGeometry(10+n*110,10,100,31);
	Button.setCheckable(true);
	Button.setAutoExclusive(true);
	Parent->connect(&Button,SIGNAL(clicked()),this,SLOT(SlotClicked()));
	Button.show();
}
void	LineGroup::SlotClicked()
{
	emit	SignalClicked(Number);
}

LEDControl16GDialog::LEDControl16GDialog(LEDControl16GPanel *p,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LEDControl16GDialog)
	,Panel(p)
{
    ui->setupUi(this);
	ui->lineEditVersion->setText(Panel->VersionStr);
	ui->pushButtonShowIO		->setVisible(false);

	for(int i=0;i<sizeof(LineGroupData)/sizeof(LineGroupData[0]);i++){
		LineGroupData[i]=NULL;
	}
	LineGroupDataNumb=0;

	p->GetLayersBase()->InstallOperationLog(this);

	for(int b=0;b<Panel->BoardCount;b++){
		for(int L=0;L<Panel->UsageLines;L++){
			int	k;
			for(k=0;k<LineGroupDataNumb;k++){
				if(LineGroupData[k]->ColorType==Panel->LineData[L].ColorType){
					break;
				}
			}
			if(k>=LineGroupDataNumb && (k+1)<sizeof(LineGroupData)/sizeof(LineGroupData[0])){
				FrameArea[k]=new QScrollArea();
				FrameArea[k]->setParent(ui->stackedWidgetSetting->widget(k));
				FrameArea[k]->move(0,0);
				FrameArea[k]->resize(ui->stackedWidgetSetting->width()-1,ui->stackedWidgetSetting->height()-1);
				FrameArea[k]->setHorizontalScrollBarPolicy (Qt::ScrollBarAlwaysOff);
				FrameAreaInside[k]=new QWidget();

				LineGroupData[k]=new LineGroup(this,ui->frame);
				LineGroupData[k]->ColorType=Panel->LineData[L].ColorType;
				LineGroupDataNumb++;
			}
			LineGroupData[k]->AddLine(&Panel->LineData[L],FrameAreaInside[k]);
		}
	}
	
	SetPatternValue(0);

	for(int k=0;k<LineGroupDataNumb;k++){
		int	Y=0;
		for(int i=0;i<LineGroupData[k]->LineNumb;i++){
			if(LineGroupData[k]->LineData[i]==NULL)
				break;
			LineGroupData[k]->LineData[i]->SetY(Y);
			Y++;
		}
		FrameAreaInside[k]->resize(ui->stackedWidgetSetting->width()-1,Y*24+48);
		FrameArea[k]->setWidget(FrameAreaInside[k]);
	}
	for(int k=0;k<LineGroupDataNumb;k++){
		for(int i=0;i<LineGroupData[k]->LineNumb;i++){
			if(LineGroupData[k]->LineData[i]==NULL)
				break;
			LineGroupData[k]->LineData[i]->Show();
		}
	}

	for(int k=0;k<LineGroupDataNumb;k++){
		LineGroupData[k]->Initial(k);
		connect(LineGroupData[k],SIGNAL(SignalClicked(int)),this,SLOT(SlotClicked(int)));
	}
	if(LineGroupDataNumb!=0){
		LineGroupData[0]->Button.setChecked(true);
		SlotClicked(0);
	}
}

LEDControl16GDialog::~LEDControl16GDialog()
{
	for(int k=0;k<LineGroupDataNumb;k++){
		delete	LineGroupData[k];
		LineGroupData[k]=NULL;
	}
	delete ui;
}

void LEDControl16GDialog::SetPatternValue(int PatternNo)
{
	for(int k=0;k<LineGroupDataNumb;k++){
		for(int i=0;i<LineGroupData[k]->LineNumb;i++){
			if(LineGroupData[k]->LineData[i]==NULL)
				break;
			struct	LightLineUnit	*L=LineGroupData[k]->LineData[i]->PointerForDefLine;

			LineGroupData[k]->LineData[i]->EditValue->setMaximum(L->MaxValue);

			for(int h=0;h<Panel->BoardCount;h++){
				LightBoard	*D=&Panel->BoardData[h];
				if(L!=NULL && D!=NULL 
				&& D->DipSW==L->BoardID){
					LineGroupData[k]->LineData[i]->EditValue->setValue(D->LineInfo[L->LineNo].TargetValue[PatternNo]);
					break;
				}
			}
		}
	}
}
void LEDControl16GDialog::GetPatternValue(int PatternNo)
{
	for(int k=0;k<LineGroupDataNumb;k++){
		for(int i=0;i<LineGroupData[k]->LineNumb;i++){
			if(LineGroupData[k]->LineData[i]==NULL)
				break;
			struct	LightLineUnit	*L=LineGroupData[k]->LineData[i]->PointerForDefLine;

			LineGroupData[k]->LineData[i]->EditValue->setMaximum(L->MaxValue);

			for(int h=0;h<Panel->BoardCount;h++){
				LightBoard	*D=&Panel->BoardData[h];
				if(L!=NULL && D!=NULL 
				&& D->DipSW==L->BoardID){
					D->LineInfo[L->LineNo].TargetValue[PatternNo]=LineGroupData[k]->LineData[i]->EditValue->value();
					break;
				}
			}
		}
	}
}

void	LEDControl16GDialog::SlotClicked(int n)
{
	ui->stackedWidgetSetting->setCurrentIndex(n);
}

QProgressBar	*LEDControl16GDialog::GetBar(void)
{
	return ui->progressBar;
}

void LEDControl16GDialog::on_pushButtonOK_clicked()
{
	GetPatternValue(GetCurrentPatternNo());
	close();
}

void LEDControl16GDialog::on_pushButtonSetAll_clicked()
{
	int	V=ui->spinBoxBrightness->value();
	for(int k=0;k<LineGroupDataNumb;k++){
		if(LineGroupData[k]->Button.isChecked()==true){
			for(int i=0;i<sizeof(LineGroupData[k]->LineData)/sizeof(LineGroupData[k]->LineData[0]);i++){
				if(LineGroupData[k]->LineData[i]==NULL)
					break;
				LineGroupData[k]->LineData[i]->EditValue->setValue(V);
			}
		}
	}
}

void LEDControl16GDialog::on_pushButtonSetTestLED_clicked()
{
	for(int k=0;k<Panel->BoardCount;k++){
		Panel->BoardData[k].SetTestLED(ui->pushButtonSetTestLED->isChecked());
	}
}

void LEDControl16GDialog::on_pushButtonTransfer_clicked()
{
	GetPatternValue(GetCurrentPatternNo());
	Panel->ReflectDataInDialog();
}

void LEDControl16GDialog::on_toolButtonON_clicked()
{
	GetPatternValue(GetCurrentPatternNo());
	Panel->ReflectOnOffInDialog(ui->toolButtonON->isChecked());
}

void LEDControl16GDialog::on_pushButtonDefinition_clicked()
{
	SetDefinitionDialog	D(Panel);
	D.exec();
	Panel->SaveDef();
}

void LEDControl16GDialog::on_pushButtonShowIO_clicked()
{
	//ShowIODialog	D(Panel);
	//D.exec();
}


void LEDControl16GDialog::on_pushButtonShowSpecial_clicked()
{
    //TestStencilDialog	D(Panel);
    //D.exec();
    //Panel->SaveDef();
}

void LEDControl16GDialog::on_pushButtonIODeliverer_clicked()
{
	//IODelivererDialog	D(Panel);
	//D.exec();
}
