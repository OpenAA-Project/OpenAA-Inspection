#include "XTypeDef.h"
#include "ShowCOMForm.h"
#include "ui_ShowCOMForm.h"
#include "XSequence.h"
#include "XGeneralFunc.h"

ShowCOMForm::ShowCOMForm(CommOperand *Ope ,QWidget *parent) :
    QWidget(parent),OpeIndex(Ope),
    ui(new Ui::ShowCOMForm)
{
    ui->setupUi(this);

    setWindowTitle(OpeIndex->GetName());

    connect(OpeIndex,SIGNAL(SignalTx(const QByteArray &)),this,SLOT(SlotTx(const QByteArray &)),Qt::QueuedConnection);
    connect(OpeIndex,SIGNAL(SignalRx(const QByteArray &)),this,SLOT(SlotRx(const QByteArray &)),Qt::QueuedConnection);
}

ShowCOMForm::~ShowCOMForm()
{
    delete ui;
}

void ShowCOMForm::closeEvent(QCloseEvent *event)
{
    event->ignore();
}
void ShowCOMForm::resizeEvent(QResizeEvent *event)
{
    ui->tableWidget->resize(width(),height());

    ::SetColumnWidthInTable(ui->tableWidget ,0, 20);
    ::SetColumnWidthInTable(ui->tableWidget ,1, 20);
    ::SetColumnWidthInTable(ui->tableWidget ,2, 20);
    ::SetColumnWidthInTable(ui->tableWidget ,3, 20);
    ::SetColumnWidthInTable(ui->tableWidget ,4, 20);
}

QChar   MakeHexStr(int n)
{
    switch(n){
    case 0: return '0';
    case 1: return '1';
    case 2: return '2';
    case 3: return '3';
    case 4: return '4';
    case 5: return '5';
    case 6: return '6';
    case 7: return '7';
    case 8: return '8';
    case 9: return '9';
    case 10: return 'A';
    case 11: return 'B';
    case 12: return 'C';
    case 13: return 'D';
    case 14: return 'E';
    case 15: return 'F';
    }
    return ' ';
}

QString ShowCOMForm::GetBinaryStr(const QByteArray &str)
{
    QString ret;
    int N=str.length();
    for(int i=0;i<N;i++){
        char    c=str.data()[i];
        ret+=MakeHexStr(c>>8);
        ret+=MakeHexStr(c&0x0f);
        ret+=" ";
    }
    return ret;
}

void	ShowCOMForm::SlotTx(const QByteArray &str)
{
    ui->tableWidget->insertRow(0);
    QString TimeStr=QTime::currentTime().toString("hh:mm:ss");
    ::SetDataToTable(ui->tableWidget, 0, 0, TimeStr);
    ::SetDataToTable(ui->tableWidget, 1, 0, GetBinaryStr(str));
    ::SetDataToTable(ui->tableWidget, 2, 0, QString::fromStdString(str.toStdString()));
}
	
void	ShowCOMForm::SlotRx(const QByteArray &str)
{
    ui->tableWidget->insertRow(0);
    QString TimeStr=QTime::currentTime().toString("hh:mm:ss");
    ::SetDataToTable(ui->tableWidget, 0, 0, TimeStr);
    ::SetDataToTable(ui->tableWidget, 3, 0, GetBinaryStr(str));
    ::SetDataToTable(ui->tableWidget, 4, 0, QString::fromStdString(str.toStdString()));
}