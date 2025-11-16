#include "ShowIOForm.h"
#include "ui_ShowIOForm.h"
#include "IntegratePlayer.h"

ShowIOForm::ShowIOForm(IntegratePlayer *P,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShowIOForm) ,Parent(P)
{
    ui->setupUi(this);

    ui->comboBoxBoardNumber->clear();
    int	N=Parent->GetNetworkPIOCount();
	Parent->GetClientIDList(PIOIDList);
    for(int i=0;i<N;i++){
        ui->comboBoxBoardNumber->addItem(QString::number(PIOIDList[i]));
    }

    on_chkEchoBack_clicked();

	TM.setSingleShot(false);
	TM.setInterval(50);
	connect(&TM,SIGNAL(timeout()),this,SLOT(SlotTimeout()));
	TM.start();
}

ShowIOForm::~ShowIOForm()
{
    delete ui;
}

void ShowIOForm::on_comboBoxBoardNumber_currentIndexChanged(int index)
{
    int	BoardNumber=ui->comboBoxBoardNumber->currentIndex();
    if(BoardNumber<0){
        return;
    }
	int	ID=PIOIDList[BoardNumber];

    int	InBitCount	=Parent->GetIOInBitCount(ID);
    int	OutBitCount	=Parent->GetIOOutBitCount(ID);
    ui->twIN		->setRowCount(InBitCount);
    ui->twIN		->setColumnCount(1);
    ui->twIN		->setColumnWidth(0,200);

    ui->twOUT	->setRowCount(OutBitCount);
    ui->twOUT	->setColumnCount(1);
    ui->twOUT	->setColumnWidth(0,200);

    for(int i=0;i<InBitCount;i++){
        QTableWidgetItem *itemIN=new QTableWidgetItem(Parent->GetPIOInBitName(ID,i));
        itemIN->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        ui->twIN->setItem(i,0,itemIN);
        itemIN->setCheckState(Qt::Unchecked);
        ui->twIN->verticalHeader()->resizeSection(i,19);
    }

    for(int i=0;i<OutBitCount;i++){
        QTableWidgetItem *itemOUT=new QTableWidgetItem(Parent->GetPIOOutBitName(ID,i));
        itemOUT->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
        ui->twOUT->setItem(i,0,itemOUT);
        itemOUT->setCheckState(Qt::Unchecked);
        ui->twOUT->verticalHeader()->resizeSection(i,19);
    }
    ui->twIN	->setHorizontalHeaderLabels(QStringList("Input bit"));
    ui->twOUT->setHorizontalHeaderLabels(QStringList("Output bit"));

    QStringList	VInStr;
    QStringList	VOutStr;
    for(int i=0;i<InBitCount;i++){
        VInStr	+=QString("IN ")+QString::number(i);
    }
    for(int i=0;i<OutBitCount;i++){
        VOutStr	+=QString("OUT ")+QString::number(i);
    }
    ui->twIN	->setVerticalHeaderLabels(VInStr);
    ui->twOUT	->setVerticalHeaderLabels(VOutStr);
}

void ShowIOForm::on_chkEchoBack_clicked()
{
    int	BoardNumber=ui->comboBoxBoardNumber->currentIndex();
    if(BoardNumber<0){
        return;
    }
	int	ID=PIOIDList[BoardNumber];
    int	OutBitCount	=Parent->GetIOOutBitCount(ID);

    if(ui->chkEchoBack->isChecked()==true){
        QPalette palette=ui->twOUT->palette();
        palette.setColor(QPalette::Base,QColor(Qt::cyan));
        ui->twOUT->setPalette(palette);

        for(int i=0;i<OutBitCount;i++){
            QTableWidgetItem *itemOUT=ui->twOUT->item(i,0);
            if(itemOUT!=NULL){
                itemOUT->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
            }
        }
    }
    else{
        QPalette palette=ui->twOUT->palette();
        palette.setColor(QPalette::Base,QColor(Qt::white));
        ui->twOUT->setPalette(palette);

        for(int i=0;i<OutBitCount;i++){
            QTableWidgetItem *itemOUT=ui->twOUT->item(i,0);
            if(itemOUT!=NULL){
                itemOUT->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
            }
        }
    }
}

void	ShowIOForm::SlotShowIO()
{
    int	BoardNumber=ui->comboBoxBoardNumber->currentIndex();
    if(BoardNumber<0){
        return;
    }
	int	ID=PIOIDList[BoardNumber];
    int	InBitCount	=Parent->GetIOInBitCount(ID);

    for(int i=0;i<InBitCount;i++){
        QTableWidgetItem *itemIN=ui->twIN->item(i,0);
        if(Parent->GetPIOInBit(ID,i)==0){
            itemIN->setCheckState(Qt::Unchecked);
        }
        else{
            itemIN->setCheckState(Qt::Checked);
        }
    }
    if(ui->chkEchoBack->isChecked()==true){
        int	OutBitCount	=Parent->GetIOOutBitCount(ID);
        for(int i=0;i<OutBitCount;i++){
            QTableWidgetItem *itemOUT=ui->twOUT->item(i,0);
            if(Parent->GetPIOOutBit(ID,i)==0){
                itemOUT->setCheckState(Qt::Unchecked);
            }
            else{
                itemOUT->setCheckState(Qt::Checked);
            }
        }
    }
}

void	ShowIOForm::SlotTimeout()
{
	SlotShowIO();
}