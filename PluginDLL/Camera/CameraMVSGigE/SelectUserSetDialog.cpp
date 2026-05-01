#include "SelectUserSetDialog.h"
#include "ui_SelectUserSetDialog.h"

SelectUserSetDialog::SelectUserSetDialog(CameraMVSGigE *P,const QByteArray &CamData ,QWidget *parent)
    : QDialog(parent)
	, Parent(P)
    , ui(new Ui::SelectUserSetDialog)
{
    ui->setupUi(this);
	RetCamData=CamData;

	int	CValue=1;
	bool	ok;
	int	t=RetCamData.toInt(&ok);
	if(ok==true){
		CValue=t;
	}
	int	CurrentIntValue;
	int	EnumCount;
	if(Parent->GetEnumValue ("UserSetSelector",CurrentIntValue ,EnumUserSetSelectorData,EnumCount)==true){
		ui->comboBoxUserSetSelector->clear();
		for(int i=0;i<EnumCount;i++){
			QString Str;
			if(Parent->GetEnumSymblic ("UserSetSelector",EnumUserSetSelectorData[i] ,Str)==true){
				ui->comboBoxUserSetSelector->addItem(Str);
				if(CValue==EnumUserSetSelectorData[i]){
					ui->comboBoxUserSetSelector->setCurrentIndex(i);
				}
			}
		}
	}
}

SelectUserSetDialog::~SelectUserSetDialog()
{
    delete ui;
}

void SelectUserSetDialog::on_pushButtonSelect_clicked()
{
	int	Index = ui->comboBoxUserSetSelector->currentIndex();
	int	SelectNo = EnumUserSetSelectorData[Index];
	RetCamData = QByteArray::number(SelectNo);
	done(true);
}


void SelectUserSetDialog::on_pushButtonCancel_clicked()
{
	done(false);
}

