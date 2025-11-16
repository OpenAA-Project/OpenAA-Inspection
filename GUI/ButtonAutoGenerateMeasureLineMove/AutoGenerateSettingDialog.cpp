#include "AutoGenerateSettingDialog.h"
#include "ui_AutoGenerateSettingDialog.h"
#include <QComboBox>

AutoGenerateSettingDialog::AutoGenerateSettingDialog(LayersBase *Base ,BladeMeasure &_BladeMeasureData ,QWidget *parent) :
    QDialog(parent),ServiceForLayers(Base)
	,BladeMeasureData(_BladeMeasureData)
    ,ui(new Ui::AutoGenerateSettingDialog)
{
    ui->setupUi(this);
}

AutoGenerateSettingDialog::~AutoGenerateSettingDialog()
{
    delete ui;
}
void	AutoGenerateSettingDialog::ShowList(void)
{
	QStringList	List;
	List.append("左から水平計測/上からの位置");
	List.append("左から水平計測/下からの位置");
	List.append("右から水平計測/上からの位置");
	List.append("右から水平計測/下からの位置");
	List.append("上から垂直計測/左からの位置");
	List.append("上から垂直計測/右からの位置");
	List.append("下から垂直計測/左からの位置");
	List.append("下から垂直計測/右からの位置");
	List.append("横幅/上からの位置");
	List.append("横幅/下からの位置");
	List.append("縦幅/左からの位置");
	List.append("縦幅/右からの位置");

	ui->tableWidgetBladePos->setRowCount(BladeMeasureData.CountGenDatas);
	for(int row=0;row<BladeMeasureData.CountGenDatas;row++){
		struct	MeasureHVInfo	&p=BladeMeasureData.GenDatas[row];

		if(p.bOnlyInside==false && p.bHorizontal==true && p.bFrom0==true && p.bPartnerFrom0==true){
			::SetDataToTableComboBox(ui->tableWidgetBladePos ,0 ,row ,List ,0);
			ShwListInner(row,0);
		}
		else
		if(p.bOnlyInside==false && p.bHorizontal==true && p.bFrom0==true && p.bPartnerFrom0==false){
			::SetDataToTableComboBox(ui->tableWidgetBladePos ,0 ,row ,List ,1);
			ShwListInner(row,1);
		}
		else
		if(p.bOnlyInside==false && p.bHorizontal==true && p.bFrom0==false && p.bPartnerFrom0==true){
			::SetDataToTableComboBox(ui->tableWidgetBladePos ,0 ,row ,List ,2);
			ShwListInner(row,2);
		}
		else
		if(p.bOnlyInside==false && p.bHorizontal==true && p.bFrom0==false && p.bPartnerFrom0==false){
			::SetDataToTableComboBox(ui->tableWidgetBladePos ,0 ,row ,List ,3);
			ShwListInner(row,3);
		}
		else
		if(p.bOnlyInside==false && p.bHorizontal==false && p.bFrom0==true && p.bPartnerFrom0==true){
			::SetDataToTableComboBox(ui->tableWidgetBladePos ,0 ,row ,List ,4);
			ShwListInner(row,4);
		}
		else
		if(p.bOnlyInside==false && p.bHorizontal==false && p.bFrom0==true && p.bPartnerFrom0==false){
			::SetDataToTableComboBox(ui->tableWidgetBladePos ,0 ,row ,List ,5);
			ShwListInner(row,5);
		}
		else
		if(p.bOnlyInside==false && p.bHorizontal==false && p.bFrom0==false && p.bPartnerFrom0==true){
			::SetDataToTableComboBox(ui->tableWidgetBladePos ,0 ,row ,List ,6);
			ShwListInner(row,6);
		}
		else
		if(p.bOnlyInside==false && p.bHorizontal==false && p.bFrom0==false && p.bPartnerFrom0==false){
			::SetDataToTableComboBox(ui->tableWidgetBladePos ,0 ,row ,List ,7);
			ShwListInner(row,7);
		}
		else
		if(p.bOnlyInside==true && p.bHorizontal==true && p.bPartnerFrom0==true){
			::SetDataToTableComboBox(ui->tableWidgetBladePos ,0 ,row ,List ,8);
			ShwListInner(row,8);
		}
		else
		if(p.bOnlyInside==true && p.bHorizontal==true && p.bPartnerFrom0==false){
			::SetDataToTableComboBox(ui->tableWidgetBladePos ,0 ,row ,List ,9);
			ShwListInner(row,9);
		}
		else
		if(p.bOnlyInside==true && p.bHorizontal==false && p.bPartnerFrom0==true){
			::SetDataToTableComboBox(ui->tableWidgetBladePos ,0 ,row ,List ,10);
			ShwListInner(row,10);
		}
		else
		if(p.bOnlyInside==true && p.bHorizontal==false && p.bPartnerFrom0==false){
			::SetDataToTableComboBox(ui->tableWidgetBladePos ,0 ,row ,List ,11);
			ShwListInner(row,11);
		}
		else{
			::SetDataToTableComboBox(ui->tableWidgetBladePos ,0 ,row ,List ,0);
			ShwListInner(row,0);
		}
		QWidget *w=ui->tableWidgetBladePos->cellWidget(row,0);
		if(w!=NULL){
			QComboBox	*b=dynamic_cast<QComboBox *>(w);
			if(b!=NULL){
				connect(b,SIGNAL(currentIndexChanged (int)),this ,SLOT(SlotBladeListIndexChanged (int)));
			}
		}

		::SetDataToTable(ui->tableWidgetBladePos ,5 ,row ,QString::number(p.OKWidth,'f',1),Qt::ItemIsEditable);
		::SetDataToTable(ui->tableWidgetBladePos ,6 ,row ,QString::number(p.RegLineLength),Qt::ItemIsEditable);
	}
}
void	AutoGenerateSettingDialog::SlotBladeListIndexChanged ( int index )
{
	int	row=ui->tableWidgetBladePos->currentRow();
	int	Index=::GetDataToTableComboBoxIndex(ui->tableWidgetBladePos ,0 ,row);
	ShwListInner(row, Index );
}
void	AutoGenerateSettingDialog::ShwListInner(int row, int Index )
{
	struct	MeasureHVInfo	&p=BladeMeasureData.GenDatas[row];
	if(Index==0){
		::SetDataToTable(ui->tableWidgetBladePos ,1,row ,/**/"");
		::SetDataToTable(ui->tableWidgetBladePos ,2,row ,QString::number(p.PartnerPos,'f',1),Qt::ItemIsEditable);
		::SetDataToTable(ui->tableWidgetBladePos ,3,row ,/**/"");
		::SetDataToTable(ui->tableWidgetBladePos ,4,row ,/**/"");
	}
	if(Index==1){
		::SetDataToTable(ui->tableWidgetBladePos ,1,row ,/**/"");
		::SetDataToTable(ui->tableWidgetBladePos ,2,row ,/**/"");
		::SetDataToTable(ui->tableWidgetBladePos ,3,row ,/**/"");
		::SetDataToTable(ui->tableWidgetBladePos ,4,row ,QString::number(p.PartnerPos,'f',1),Qt::ItemIsEditable);
	}
	if(Index==2){
		::SetDataToTable(ui->tableWidgetBladePos ,1,row ,/**/"");
		::SetDataToTable(ui->tableWidgetBladePos ,2,row ,QString::number(p.PartnerPos,'f',1),Qt::ItemIsEditable);
		::SetDataToTable(ui->tableWidgetBladePos ,3,row ,/**/"");
		::SetDataToTable(ui->tableWidgetBladePos ,4,row ,/**/"");
	}
	if(Index==3){
		::SetDataToTable(ui->tableWidgetBladePos ,1,row ,/**/"");
		::SetDataToTable(ui->tableWidgetBladePos ,2,row ,/**/"");
		::SetDataToTable(ui->tableWidgetBladePos ,3,row ,/**/"");
		::SetDataToTable(ui->tableWidgetBladePos ,4,row ,QString::number(p.PartnerPos,'f',1),Qt::ItemIsEditable);
	}
	if(Index==4){
		::SetDataToTable(ui->tableWidgetBladePos ,1,row ,QString::number(p.PartnerPos,'f',1),Qt::ItemIsEditable);
		::SetDataToTable(ui->tableWidgetBladePos ,2,row ,/**/"");
		::SetDataToTable(ui->tableWidgetBladePos ,3,row ,/**/"");
		::SetDataToTable(ui->tableWidgetBladePos ,4,row ,/**/"");
	}
	if(Index==5){
		::SetDataToTable(ui->tableWidgetBladePos ,1,row ,/**/"");
		::SetDataToTable(ui->tableWidgetBladePos ,2,row ,/**/"");
		::SetDataToTable(ui->tableWidgetBladePos ,3,row ,QString::number(p.PartnerPos,'f',1),Qt::ItemIsEditable);
		::SetDataToTable(ui->tableWidgetBladePos ,4,row ,/**/"");
	}
	if(Index==6){
		::SetDataToTable(ui->tableWidgetBladePos ,1,row ,QString::number(p.PartnerPos,'f',1),Qt::ItemIsEditable);
		::SetDataToTable(ui->tableWidgetBladePos ,2,row ,/**/"");
		::SetDataToTable(ui->tableWidgetBladePos ,3,row ,/**/"");
		::SetDataToTable(ui->tableWidgetBladePos ,4,row ,/**/"");
	}
	if(Index==7){
		::SetDataToTable(ui->tableWidgetBladePos ,1,row ,/**/"");
		::SetDataToTable(ui->tableWidgetBladePos ,2,row ,/**/"");
		::SetDataToTable(ui->tableWidgetBladePos ,3,row ,QString::number(p.PartnerPos,'f',1),Qt::ItemIsEditable);
		::SetDataToTable(ui->tableWidgetBladePos ,4,row ,/**/"");
	}
	else
	if(Index==8){
		::SetDataToTable(ui->tableWidgetBladePos ,1,row ,/**/"");
		::SetDataToTable(ui->tableWidgetBladePos ,2,row ,QString::number(p.PartnerPos,'f',1),Qt::ItemIsEditable);
		::SetDataToTable(ui->tableWidgetBladePos ,3,row ,/**/"");
		::SetDataToTable(ui->tableWidgetBladePos ,4,row ,/**/"");
	}
	else
	if(Index==9){
		::SetDataToTable(ui->tableWidgetBladePos ,1,row ,/**/"");
		::SetDataToTable(ui->tableWidgetBladePos ,2,row ,/**/"");
		::SetDataToTable(ui->tableWidgetBladePos ,3,row ,/**/"");
		::SetDataToTable(ui->tableWidgetBladePos ,4,row ,QString::number(p.PartnerPos,'f',1),Qt::ItemIsEditable);
	}
	else
	if(Index==10){
		::SetDataToTable(ui->tableWidgetBladePos ,1,row ,QString::number(p.PartnerPos,'f',1),Qt::ItemIsEditable);
		::SetDataToTable(ui->tableWidgetBladePos ,2,row ,/**/"");
		::SetDataToTable(ui->tableWidgetBladePos ,3,row ,/**/"");
		::SetDataToTable(ui->tableWidgetBladePos ,4,row ,/**/"");
	}
	else
	if(Index==11){
		::SetDataToTable(ui->tableWidgetBladePos ,1,row ,/**/"");
		::SetDataToTable(ui->tableWidgetBladePos ,2,row ,/**/"");
		::SetDataToTable(ui->tableWidgetBladePos ,3,row ,QString::number(p.PartnerPos,'f',1),Qt::ItemIsEditable);
		::SetDataToTable(ui->tableWidgetBladePos ,4,row ,/**/"");
	}
	else{
		::SetDataToTable(ui->tableWidgetBladePos ,1,row ,/**/"");
		::SetDataToTable(ui->tableWidgetBladePos ,2,row ,QString::number(p.PartnerPos,'f',1),Qt::ItemIsEditable);
		::SetDataToTable(ui->tableWidgetBladePos ,3,row ,/**/"");
		::SetDataToTable(ui->tableWidgetBladePos ,4,row ,/**/"");
	}
}
void	AutoGenerateSettingDialog::GetDataFromList(void)
{
	for(int row=0;row<BladeMeasureData.CountGenDatas;row++){
		struct	MeasureHVInfo	&p=BladeMeasureData.GenDatas[row];
		int	Index=::GetDataToTableComboBoxIndex(ui->tableWidgetBladePos ,0 ,row);
		if(Index==0){
			QString	s=GetDataToTable(ui->tableWidgetBladePos ,2 ,row);
			p.bOnlyInside	=false;
			p.bHorizontal	=true;
			p.bFrom0			=true;
			p.bPartnerFrom0	=true;
			p.PartnerPos=s.toDouble();
		}
		if(Index==1){
			QString	s=GetDataToTable(ui->tableWidgetBladePos ,4 ,row);
			p.bOnlyInside	=false;
			p.bHorizontal	=true;
			p.bFrom0			=true;
			p.bPartnerFrom0	=false;
			p.PartnerPos=s.toDouble();
		}
		if(Index==2){
			QString	s=GetDataToTable(ui->tableWidgetBladePos ,2 ,row);
			p.bOnlyInside	=false;
			p.bHorizontal	=true;
			p.bFrom0			=false;
			p.bPartnerFrom0	=true;
			p.PartnerPos=s.toDouble();
		}
		if(Index==3){
			QString	s=GetDataToTable(ui->tableWidgetBladePos ,4 ,row);
			p.bOnlyInside	=false;
			p.bHorizontal	=true;
			p.bFrom0			=false;
			p.bPartnerFrom0	=false;
			p.PartnerPos=s.toDouble();
		}
		if(Index==4){
			QString	s=GetDataToTable(ui->tableWidgetBladePos ,1 ,row);
			p.bOnlyInside	=false;
			p.bHorizontal	=false;
			p.bFrom0			=true;
			p.bPartnerFrom0	=true;
			p.PartnerPos=s.toDouble();
		}
		if(Index==5){
			QString	s=GetDataToTable(ui->tableWidgetBladePos ,3 ,row);
			p.bOnlyInside	=false;
			p.bHorizontal	=false;
			p.bFrom0			=true;
			p.bPartnerFrom0	=false;
			p.PartnerPos=s.toDouble();
		}
		if(Index==6){
			QString	s=GetDataToTable(ui->tableWidgetBladePos ,1 ,row);
			p.bOnlyInside	=false;
			p.bHorizontal	=false;
			p.bFrom0			=false;
			p.bPartnerFrom0	=true;
			p.PartnerPos=s.toDouble();
		}
		if(Index==7){
			QString	s=GetDataToTable(ui->tableWidgetBladePos ,3 ,row);
			p.bOnlyInside	=false;
			p.bHorizontal	=false;
			p.bFrom0			=false;
			p.bPartnerFrom0	=false;
			p.PartnerPos=s.toDouble();
		}
		if(Index==8){
			QString	s=GetDataToTable(ui->tableWidgetBladePos ,2 ,row);
			p.bOnlyInside	=true;
			p.bHorizontal	=true;
			p.bFrom0			=true;
			p.bPartnerFrom0	=true;
			p.PartnerPos=s.toDouble();
		}
		if(Index==9){
			QString	s=GetDataToTable(ui->tableWidgetBladePos ,2 ,row);
			p.bOnlyInside	=true;
			p.bHorizontal	=true;
			p.bFrom0			=true;
			p.bPartnerFrom0	=false;
			p.PartnerPos=s.toDouble();
		}
		if(Index==10){
			QString	s=GetDataToTable(ui->tableWidgetBladePos ,2 ,row);
			p.bOnlyInside	=true;
			p.bHorizontal	=false;
			p.bFrom0			=true;
			p.bPartnerFrom0	=true;
			p.PartnerPos=s.toDouble();
		}
		if(Index==11){
			QString	s=GetDataToTable(ui->tableWidgetBladePos ,2 ,row);
			p.bOnlyInside	=true;
			p.bHorizontal	=false;
			p.bFrom0			=true;
			p.bPartnerFrom0	=false;
			p.PartnerPos=s.toDouble();
		}
		QString	s=GetDataToTable(ui->tableWidgetBladePos ,5 ,row);
		p.OKWidth=s.toDouble();
		QString	sL=GetDataToTable(ui->tableWidgetBladePos ,6 ,row);
		p.RegLineLength=sL.toInt();
	}
}
void AutoGenerateSettingDialog::on_PushButtonSaveBladePos_clicked()
{

}

void AutoGenerateSettingDialog::on_PushButtonLoadBladePos_clicked()
{

}

void AutoGenerateSettingDialog::on_PushButtonClose_clicked()
{
	done(true);
}
