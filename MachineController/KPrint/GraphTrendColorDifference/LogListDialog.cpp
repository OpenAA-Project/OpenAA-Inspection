#include "GraphTrendColorDifferenceResource.h"
#include "LogListDialog.h"
#include "ui_LogListDialog.h"
#include "GraphTrendColorDifferenceForm.h"
#include "XGeneralFunc.h"

static	const	wchar_t	*ExcelUser	=L"MASATOSHI SASAI";
static	const	wchar_t* ExcelKey = L"windows-252a28070ccee00f6fbd6d65ady7m2ue";

LogListDialog::LogListDialog(GraphTrendColorDifferenceForm *p ,QWidget *parent) :
    QDialog(parent)
	,Parent(p)
    ,ui(new Ui::LogListDialog)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);
	setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::WindowSystemMenuHint);

	LogListDim	=new struct	LogList[10000];
	LogListCount=0;

	MakeLogList();
	ShowList();
}

LogListDialog::~LogListDialog()
{
    delete ui;
	delete	[]LogListDim;
	LogListCount=0;
}

void LogListDialog::resizeEvent ( QResizeEvent * event )
{
	ui->tableWidget->resize(width(),height()-ui->frame->height());
	ui->frame->setGeometry(0,height()-ui->frame->height(),width(),ui->frame->height());

	ui->pushButtonClose->move(width()-ui->pushButtonClose->width()-10,ui->pushButtonClose->geometry().top());

	ui->tableWidget->setColumnWidth(0,60);
	ui->tableWidget->setColumnWidth(1,48);
	int	W=width()-60-48-32;
	if(W>0 && Parent->ColorItems.GetCount()>0){
		W/=Parent->ColorItems.GetCount();
		int	n=0;
		for(ColorItem *c=Parent->ColorItems.GetFirst();c!=NULL;c=c->GetNext(),n++){
			ui->tableWidget->setColumnWidth(n+2,W);
		}
	}
}

static	int	SortFuncLogList(const void *a ,const void *b)
{
	struct	LogList	*pa=(struct	LogList *)a;
	struct	LogList	*pb=(struct	LogList *)b;
	int	n=pb->Point[0]->InspectionID-pa->Point[0]->InspectionID;
	return n;
}

void LogListDialog::MakeLogList(void)
{
	LogListCount=0;
	for(ColorItem *c=Parent->ColorItems.GetFirst();c!=NULL;c=c->GetNext()){
		for(int i=0;i<c->CurrentCountDim;i++){
			struct	RunningColorHSVE	*C=&c->RunningColorDim[i];
			if(C->TmInfo.Ok==false){
				bool	Found=false;
				for(int k=0;k<LogListCount;k++){
					if(LogListDim[k].Point[0]->InspectionID==C->InspectionID){
						for(int h=1;h<sizeof(LogListDim[k].Point)/sizeof(LogListDim[k].Point[0]);h++){
							if(LogListDim[k].Point[h]==NULL){
								LogListDim[k].Point[h]=C;
								break;
							}
						}
						Found=true;
						break;
					}
				}
				if(Found==false && LogListCount<10000){
					LogListDim[LogListCount].Point[0]=C;
					for(int h=1;h<sizeof(LogListDim[0].Point)/sizeof(LogListDim[0].Point[0]);h++){
						LogListDim[LogListCount].Point[h]=NULL;
					}
					LogListCount++;
				}
			}
		}
	}
	qsort(LogListDim,LogListCount,sizeof(struct	LogList),SortFuncLogList);
}

void	LogListDialog::ShowList(void)
{
	int	N=Parent->ColorItems.GetCount();
	ui->tableWidget->setColumnCount(N+2);
	QStringList	Labels;
	Labels.append(LangSolver.GetString(LogListDialog_LS,LID_4)/*"時刻"*/);
	Labels.append(LangSolver.GetString(LogListDialog_LS,LID_5)/*"ID"*/);
	int	n=0;
	for(ColorItem *c=Parent->ColorItems.GetFirst();c!=NULL;c=c->GetNext(),n++){
		Labels.append(QString::number(c->SlaveNo)
					 +QString(/**/"-")
					 +QString::number(c->ItemID));
	}
	ui->tableWidget->setHorizontalHeaderLabels(Labels);
	ui->tableWidget->setRowCount(LogListCount);

	for(int row=0;row<LogListCount;row++){
		::SetDataToTable(ui->tableWidget ,0 ,row ,QString::number(LogListDim[row].Point[0]->TmInfo.Hour)
												 +QString(/**/":")
												 +QString::number(LogListDim[row].Point[0]->TmInfo.Minute)
												 +QString(/**/":")
												 +QString::number(LogListDim[row].Point[0]->TmInfo.Second));
		::SetDataToTable(ui->tableWidget ,1 ,row ,QString::number(LogListDim[row].Point[0]->InspectionID));
		int	Col=2;
		for(ColorItem *c=Parent->ColorItems.GetFirst();c!=NULL;c=c->GetNext(),Col++){
			for(int h=0;h<sizeof(LogListDim[0].Point)/sizeof(LogListDim[0].Point[0]);h++){
				if(LogListDim[row].Point[h]!=NULL){
					if(c->RunningColorDim<=LogListDim[row].Point[h] && LogListDim[row].Point[h]<&c->RunningColorDim[c->CurrentCountDim]){
						::SetDataToTable(ui->tableWidget,Col,row,QString(/**/"H:")
																+QString::number(LogListDim[row].Point[h]->HSVE[0],'f',2)
																+QString(/**/" S:")
																+QString::number(LogListDim[row].Point[h]->HSVE[1],'f',2)
																+QString(/**/" V:")
																+QString::number(LogListDim[row].Point[h]->HSVE[2],'f',2)
																+QString(/**/" E:")
																+QString::number(LogListDim[row].Point[h]->HSVE[3],'f',2));
					}
				}
			}
		}
	}
}


void LogListDialog::on_pushButtonExcel_clicked()
{
	QString	ExcelFileName=QFileDialog::getSaveFileName(NULL
													,LangSolver.GetString(LogListDialog_LS,LID_13)/*"Save EXCEL"*/
													,QString()
													,/**/"Excel(*.xlsx);;All files(*.*)");
	if(ExcelFileName.isEmpty()==true)
		return;
	XLSXBook = xlCreateXMLBook();
	XLSXBook->setKey(ExcelUser, ExcelKey);
	XLSXSheet=XLSXBook->addSheet(L"Master");

	Lang	=XLSXBook->addFormat();
	Fnt	=XLSXBook->addFont();

	QString	FontName;
	switch (Parent->GetLayersBase()->GetLanguageCode()) {
	case 0:	FontName = /**/"ＭＳ Ｐゴシック";	break;
	case 1:	FontName = /**/"Arial";				break;
	case 2:	FontName = /**/"SimSun";			break;
	case 3:	FontName = /**/"MingLiU";			break;
	case 4:	FontName = /**/"Gulim";				break;
	}
	wchar_t	WBuff[100];
	memset(WBuff, 0, sizeof(WBuff));
	FontName.toWCharArray(WBuff);
	Fnt->setName(WBuff);

	Lang->setFont(Fnt);

	WriteCell(0, 0,LangSolver.GetString(LogListDialog_LS,LID_19)/*"作成日時"*/);
	WriteCell(0, 1,QDateTime::currentDateTime().toString());


	int	N=Parent->ColorItems.GetCount();
	ui->tableWidget->setColumnCount(N+2);
	WriteCell(1, 0,LangSolver.GetString(LogListDialog_LS,LID_20)/*"時刻"*/);
	WriteCell(1, 1,LangSolver.GetString(LogListDialog_LS,LID_21)/*"ID"*/);
	{
		int	Col=2;
		for(ColorItem *c=Parent->ColorItems.GetFirst();c!=NULL;c=c->GetNext(),Col++){
			WriteCell(1, Col,QString::number(c->SlaveNo)
							+QString(/**/"-")
							+QString::number(c->ItemID));
		}
	}

	for(int n=0;n<LogListCount;n++){
		int	row=n+2;
		WriteCell(row, 0,QString::number(LogListDim[n].Point[0]->TmInfo.Hour)
						+QString(/**/":")
						+QString::number(LogListDim[n].Point[0]->TmInfo.Minute)
						+QString(/**/":")
						+QString::number(LogListDim[n].Point[0]->TmInfo.Second));
		WriteCell(row, 1,QString::number(LogListDim[n].Point[0]->InspectionID));
		int	Col=2;
		for(ColorItem *c=Parent->ColorItems.GetFirst();c!=NULL;c=c->GetNext(),Col++){
			for(int h=0;h<sizeof(LogListDim[0].Point)/sizeof(LogListDim[0].Point[0]);h++){
				if(LogListDim[row].Point[h]!=NULL){
					if(c->RunningColorDim<=LogListDim[row].Point[h] && LogListDim[row].Point[h]<&c->RunningColorDim[c->CurrentCountDim]){
						WriteCell(row, Col	,QString(/**/"H:")
											+QString::number(LogListDim[n].Point[h]->HSVE[0],'f',2)
											+QString(/**/" S:")
											+QString::number(LogListDim[n].Point[h]->HSVE[1],'f',2)
											+QString(/**/" V:")
											+QString::number(LogListDim[n].Point[h]->HSVE[2],'f',2)
											+QString(/**/" E:")
											+QString::number(LogListDim[n].Point[h]->HSVE[3],'f',2));
					}
				}
			}
		}
	}
	wchar_t	FileNameStr[256];
	memset(FileNameStr,0,sizeof(FileNameStr));
	ExcelFileName.toWCharArray(FileNameStr);

	if(XLSXBook->save(FileNameStr)==false){
		delete	XLSXBook;
		return;
	}
	XLSXBook->release();
}


void	LogListDialog::WriteCell(int Row, int Col ,const QString &Str)
{
	wchar_t	Buff[1000];
	memset(Buff,0,sizeof(Buff));
	Str.toWCharArray(Buff);

	XLSXSheet->setCellFormat(Row, Col,Lang);
	XLSXSheet->writeStr(Row, Col,Buff);
}

void	LogListDialog::WriteCellV(int Row, int Col ,const QVariant &Data)
{
	XLSXSheet->setCellFormat(Row, Col,Lang);

	wchar_t	Buff[1000];
	memset(Buff,0,sizeof(Buff));
	if(Data.type()==QVariant::Bool){
		if(Data.toBool()==true){
			XLSXSheet->writeStr(Row, Col,L"true");
		}
		else{
			XLSXSheet->writeStr(Row, Col,L"false");
		}
	}
	else if(Data.type()==QVariant::Char){
		QString	s(Data.toChar());
		s.toWCharArray(Buff);	
		XLSXSheet->writeStr(Row, Col,Buff);
	}
	else if(Data.type()==QVariant::Date){
		QString	s(Data.toDate().toString());
		s.toWCharArray(Buff);	
		XLSXSheet->writeStr(Row, Col,Buff);
	}
	else if(Data.type()==QVariant::DateTime){
		QString	s(Data.toDateTime().toString());
		s.toWCharArray(Buff);	
		XLSXSheet->writeStr(Row, Col,Buff);
	}
	else if(Data.type()==QVariant::Double){
		QString	s=QString::number(Data.toDouble(),'f');
		s.toWCharArray(Buff);
		XLSXSheet->writeStr(Row, Col,Buff);
	}
	else if(Data.type()==QVariant::Int){
		QString	s=QString::number(Data.toInt());
		s.toWCharArray(Buff);
		XLSXSheet->writeStr(Row, Col,Buff);
	}
	else if(Data.type()==QVariant::String){
		QString	s=Data.toString();
		s.toWCharArray(Buff);
		XLSXSheet->writeStr(Row, Col,Buff);
	}
	else if(Data.type()==QVariant::Time){
		QString	s(Data.toTime().toString());
		s.toWCharArray(Buff);	
		XLSXSheet->writeStr(Row, Col,Buff);
	}
	else if(Data.type()==QVariant::UInt){
		QString	s=QString::number(Data.toUInt());
		s.toWCharArray(Buff);
		XLSXSheet->writeStr(Row, Col,Buff);
	}
	else{
		XLSXSheet->writeStr(Row, Col,L"Error");
	}
}

void LogListDialog::on_pushButtonClose_clicked()
{
	done(true);
}
