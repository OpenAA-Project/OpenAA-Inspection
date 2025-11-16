#include "LEDControl16FDialog.h"
#include "ui_LEDControl16FDialog.h"

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

LineGroup::LineGroup(LEDControl16FDialog *p ,QWidget *parent)
	:Parent(p),Button(false,parent)
{
	for(int i=0;i<sizeof(LineData)/sizeof(LineData[0]);i++){
		LineData[i]=NULL;
	}
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
void	LineGroup::AddLine(LEDControl16FPanel::DefUnit::DefBoard::DefLine	*L ,QWidget *parent)
{
	for(int i=0;i<sizeof(LineData)/sizeof(LineData[0]);i++){
		if(LineData[i]==NULL){
			LineData[i]=new LineWindow(parent);
			LineData[i]->PointerForDefLine=L;
			LineData[i]->EditComment->setText(L->Comment);
			break;
		}
	}
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

LEDControl16FDialog::LEDControl16FDialog(LEDControl16FPanel *p,QWidget *parent) :
    QDialog(parent)
	,Panel(p)
    ,ui(new Ui::LEDControl16FDialog)
{
    ui->setupUi(this);
	ui->lineEditVersion->setText(Panel->VersionStr);
	ui->pushButtonShowIO		->setVisible(false);

	for(int i=0;i<sizeof(LineGroupData)/sizeof(LineGroupData[0]);i++){
		LineGroupData[i]=NULL;
	}
	LineGroupDataNumb=0;

	p->GetLayersBase()->InstallOperationLog(this);

	for(int r=0;r<Panel->CountOfUnit;r++){
		for(int b=0;b<Panel->DefUnitDim[r].CountOfBoard;b++){
			for(int L=0;L<Panel->DefUnitDim[r].DefBoardDim[b].CountOfLine;L++){
				int	k;
				for(k=0;k<LineGroupDataNumb;k++){
					if(LineGroupData[k]->ColorType==Panel->DefUnitDim[r].DefBoardDim[b].DefLineDim[L].ColorType
					&& LineGroupData[k]->LightID  ==Panel->DefUnitDim[r].DefBoardDim[b].DefLineDim[L].LightID){
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
					LineGroupData[k]->ColorType=Panel->DefUnitDim[r].DefBoardDim[b].DefLineDim[L].ColorType;
					LineGroupData[k]->LightID  =Panel->DefUnitDim[r].DefBoardDim[b].DefLineDim[L].LightID;
					LineGroupDataNumb++;
				}
				LineGroupData[k]->AddLine(&Panel->DefUnitDim[r].DefBoardDim[b].DefLineDim[L],FrameAreaInside[k]);
			}
		}
	}
	SetPatternValue(0);

	for(int k=0;k<LineGroupDataNumb;k++){
		int	Y=0;
		for(int i=0;i<sizeof(LineGroupData[k]->LineData)/sizeof(LineGroupData[k]->LineData[0]);i++){
			if(LineGroupData[k]->LineData[i]==NULL)
				break;
			LineGroupData[k]->LineData[i]->SetY(Y);
			Y++;
		}
		FrameAreaInside[k]->resize(ui->stackedWidgetSetting->width()-1,Y*24+48);
		FrameArea[k]->setWidget(FrameAreaInside[k]);
	}
	for(int k=0;k<LineGroupDataNumb;k++){
		for(int i=0;i<sizeof(LineGroupData[k]->LineData)/sizeof(LineGroupData[k]->LineData[0]);i++){
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

LEDControl16FDialog::~LEDControl16FDialog()
{
	for(int k=0;k<LineGroupDataNumb;k++){
		delete	LineGroupData[k];
		LineGroupData[k]=NULL;
	}
	delete ui;
}

void LEDControl16FDialog::SetPatternValue(int PatternNo)
{
	for(int k=0;k<LineGroupDataNumb;k++){
		for(int i=0;i<sizeof(LineGroupData[k]->LineData)/sizeof(LineGroupData[k]->LineData[0]);i++){
			if(LineGroupData[k]->LineData[i]==NULL)
				break;
			LEDControl16FPanel::DefUnit::DefBoard::DefLine	*L=LineGroupData[k]->LineData[i]->PointerForDefLine;

			for(int h=0;h<Panel->LightData[PatternNo].Pattern.AllocatedCountOfLines;h++){
				LEDControl16FPanel::DefUnit::DefBoard::DefLine	*D=Panel->LightData[PatternNo].Pattern.LineValueDim[h].PointerForDefLine;
				if(L!=NULL && D!=NULL 
				&& D->BoardNo==L->BoardNo
				&& D->UnitNo==L->UnitNo
				&& D->LineNo==L->LineNo){
					LineGroupData[k]->LineData[i]->EditValue->setMaximum(L->MaxValue);
					LineGroupData[k]->LineData[i]->EditValue->setValue(Panel->LightData[PatternNo].Pattern.LineValueDim[h].Value);
					goto	Found;
				}
			}
Found:;
		}
	}
}
void LEDControl16FDialog::GetPatternValue(int PatternNo)
{
	for(int k=0;k<LineGroupDataNumb;k++){
		for(int i=0;i<sizeof(LineGroupData[k]->LineData)/sizeof(LineGroupData[k]->LineData[0]);i++){
			if(LineGroupData[k]->LineData[i]==NULL)
				break;
			LEDControl16FPanel::DefUnit::DefBoard::DefLine	*L=LineGroupData[k]->LineData[i]->PointerForDefLine;

			for(int h=0;h<Panel->LightData[PatternNo].Pattern.AllocatedCountOfLines;h++){
				LEDControl16FPanel::DefUnit::DefBoard::DefLine	*D=Panel->LightData[PatternNo].Pattern.LineValueDim[h].PointerForDefLine;
				if(D!=NULL && L!=NULL
				&& D->BoardNo==L->BoardNo
				&& D->UnitNo==L->UnitNo
				&& D->LineNo==L->LineNo){
					Panel->LightData[PatternNo].Pattern.LineValueDim[h].Value	=LineGroupData[k]->LineData[i]->EditValue->value();
					goto	Found;
				}
			}
Found:;
		}
	}
}

void	LEDControl16FDialog::SlotClicked(int n)
{
	ui->stackedWidgetSetting->setCurrentIndex(n);
}

QProgressBar	*LEDControl16FDialog::GetBar(void)
{
	return ui->progressBar;
}

void LEDControl16FDialog::on_pushButtonOK_clicked()
{
	GetPatternValue(GetCurrentPatternNo());
	close();
}

void LEDControl16FDialog::on_pushButtonSetAll_clicked()
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

void LEDControl16FDialog::on_pushButtonTransfer_clicked()
{
	GetPatternValue(GetCurrentPatternNo());
	Panel->ReflectDataInDialog();
}

void LEDControl16FDialog::on_toolButtonON_clicked()
{
	GetPatternValue(GetCurrentPatternNo());
	Panel->ReflectOnOffInDialog(ui->toolButtonON->isChecked());
}

void LEDControl16FDialog::on_pushButtonDefinition_clicked()
{
	SetDefinitionDialog	D(Panel);
	D.exec();
	Panel->SaveDef();
}

void LEDControl16FDialog::on_pushButtonShowIO_clicked()
{
	//ShowIODialog	D(Panel);
	//D.exec();
}


void LEDControl16FDialog::on_pushButtonShowSpecial_clicked()
{
    //TestStencilDialog	D(Panel);
    //D.exec();
    //Panel->SaveDef();
}

void LEDControl16FDialog::on_pushButtonIODeliverer_clicked()
{
	//IODelivererDialog	D(Panel);
	//D.exec();
}
