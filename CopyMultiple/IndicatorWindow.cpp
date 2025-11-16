#include "IndicatorWindow.h"
#include "ui_IndicatorWindow.h"
#include "XCopyMultiple.h"
#include "CopyMultiple.h"
#include "XGeneralFunc.h"

IndicatorWindow::IndicatorWindow(QWidget *parent) :
    QWidget(NULL),
    ui(new Ui::IndicatorWindow)
{
    ui->setupUi(this);

	Parent=(CopyMultiple*)parent;
	DestCount=Parent->Data.GetDestCount();
	ui->tableWidget->setColumnCount(1+DestCount);
	ui->tableWidget->setColumnWidth(0,300);
	QStringList Header;
	Header << "File";
	for(int i=0;i<DestCount;i++){
		ui->tableWidget->setColumnWidth(1+i,45);
		QString Destnumber="Dest ";
		Destnumber+=Destnumber.number(1+i,10);
		Header << Destnumber;
	}
	ui->tableWidget->setHorizontalHeaderLabels(Header);
	ui->tableWidget->setRowCount(Parent->Data.SourceFiles.GetCount());
	int	Row=0;
	for(CopyMultipleData::FoundFileClass *L=Parent->Data.SourceFiles.GetFirst();L!=NULL;L=L->GetNext(),Row++){
		::SetDataToTable(ui->tableWidget,0,Row ,L->FoundFile);
	}

	TM.setInterval(200);
	TM.setSingleShot(false);
	connect(&TM,SIGNAL(timeout()),this,SLOT(SlotTimeout()));
	TM.start();
}

IndicatorWindow::~IndicatorWindow()
{
    delete ui;
	Parent->Indicator=NULL;
}

void IndicatorWindow::closeEvent ( QCloseEvent * event )
{
	deleteLater();
}

void	IndicatorWindow::SlotTimeout ()
{
	int	Row=0;
	for(CopyMultipleData::FoundFileClass *L=Parent->Data.SourceFiles.GetFirst();L!=NULL;L=L->GetNext(),Row++){
		for(int i=0;i<DestCount;i++){
			if(L->CopiedState[i]==CopyMultipleData::FoundFileClass::_NotYet){
				::SetDataToTable(ui->tableWidget,i+1,Row ,/**/"");
			}
			if(L->CopiedState[i]==CopyMultipleData::FoundFileClass::_Copied){
				::SetDataToTable(ui->tableWidget,i+1,Row ,/**/"OK");
			}
			if(L->CopiedState[i]==CopyMultipleData::FoundFileClass::_NotCopied){
				::SetDataToTable(ui->tableWidget,i+1,Row ,/**/"X");
			}
		}
	}
}
