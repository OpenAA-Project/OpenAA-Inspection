#include "GraphTrendKidaResource.h"
#include "BladeLogForm.h"
#include "ui_BladeLogForm.h"
#include "XIntegrationBase.h"
#include "XDataInLayer.h"
#include "XMeasureLineMove.h"
#include "IntegrationLib.h"
#include "EasyPropertyDentMeasureForm.h"
#include "GraphTrendKidaForm.h"

static	const	wchar_t	*ExcelUser	=L"MASATOSHI SASAI";
static	const	wchar_t	*ExcelKey = L"windows-252a28070ccee00f6fbd6d65ady7m2ue";

BladeLogForm::BladeLogForm(GraphTrendKidaForm *p ,LayersBase *Base ,QWidget *parent) :
    QWidget(parent)
	,ServiceForLayers(Base)
	,Parent(p)
    ,ui(new Ui::BladeLogForm)
{
    ui->setupUi(this);

	Qt::WindowFlags	f=windowFlags ();
	f|=Qt::WindowStaysOnTopHint;
	setWindowFlags(f);

	CountGraphLine=0;
	
	Headers.append(/**/"ID-Time");
	for(EachMaster *M=GetLayersBase()->GetIntegrationBasePointer()->MasterDatas.GetFirst();M!=NULL;M=M->GetNext()){
		if(Parent->SlaveNo==M->GetIntegrationSlaveNo() || Parent->SlaveNo==-1){
			InspectionList	*n=M->GetCurrentInspection().GetFirst();
			if(n!=NULL){
				for(NGPointInAllPage *Ph=n->NGPointAllPhases.GetFirst();Ph!=NULL;Ph=Ph->GetNext()){
					for(NGPointInPage *Pg=Ph->NPListPack<NGPointInPage>::GetFirst();Pg!=NULL;Pg=Pg->GetNext()){
						for(NGPoint *p=Pg->NPListPack<NGPoint>::GetFirst();p!=NULL;p=p->GetNext()){
							if(p->LibType==DefLibTypeMeasureLineMove){
								if(CountGraphLine<100){
									QString	Str;
									EasyPropertyDentMeasureForm	*f=Parent->EasyPropertyDentMeasurePointer[M->GetIntegrationSlaveNo()];
									if(f!=NULL){
										Str=QString::fromLocal8Bit(f->BladeMeasureData.GenDatas[CountGraphLine].MeasureName);
									}
									if(Str.isEmpty()==true){
										Str=QString(LangSolver.GetString(BladeLogForm_LS,LID_2)/*"Blade"*/)+QString::number(CountGraphLine+1);
									}
									Headers.append(Str);
									BladeItemID[CountGraphLine]=p->UniqueID;
									CountGraphLine++;
								}
							}
						}
					}
				}
			}
		}
	}
	
	ui->tableWidget->setColumnCount(1+CountGraphLine);
	ui->tableWidget->setHorizontalHeaderLabels(Headers);

	for(int i=0;i<CountGraphLine;i++){
		BladeItemID[i]=i;
		NGList[i]=new double[MaxNGCount];
		for(int j=0;j<MaxNGCount;j++){
			NGList[i][j]=0.0;
		}
	}
	InspectionID	=new int [MaxNGCount];
	InspectionTime	=new XDateTime[MaxNGCount];
	RowCount=0;
	for(EachMaster *M=GetLayersBase()->GetIntegrationBasePointer()->MasterDatas.GetFirst();M!=NULL;M=M->GetNext()){
		if(Parent->SlaveNo==M->GetIntegrationSlaveNo() || Parent->SlaveNo==-1){
			for(InspectionList	*n=M->GetCurrentInspection().GetFirst();n!=NULL;n=n->GetNext()){
				bool	FoundNG=false;
				for(NGPointInAllPage *Ph=n->NGPointAllPhases.GetFirst();Ph!=NULL;Ph=Ph->GetNext()){
					for(NGPointInPage *Pg=Ph->NPListPack<NGPointInPage>::GetFirst();Pg!=NULL;Pg=Pg->GetNext()){
						for(NGPoint *p=Pg->NPListPack<NGPoint>::GetFirst();p!=NULL;p=p->GetNext()){
							if(p->Error>=2 && p->LibType==DefLibTypeMeasureLineMove){
								for(int i=0;i<CountGraphLine;i++){
									if(BladeItemID[i]==p->UniqueID){
										NGList[i][RowCount]=p->DoubleCause;
										break;
									}
								}
								FoundNG=true;
							}
						}
					}
				}
				if(FoundNG==true){
					InspectionID	[RowCount]=n->ID;
					InspectionTime	[RowCount]=n->InspectionTime;
					RowCount++;
					if(RowCount>=MaxNGCount){
						break;
					}
				}
			}
		}
	}
	ui->tableWidget->setRowCount(RowCount);
	ui->tableWidget->setUpdatesEnabled(false);
	for(int row=0;row<RowCount;row++){
		::SetDataToTable(ui->tableWidget ,0 ,RowCount-row-1 ,QString::number(InspectionID[row])
												+ QString(/**/"-")
												+ InspectionTime[row].toString(/**/"hh:mm:ss"));
		for(int col=0;col<CountGraphLine;col++){
			if(NGList[col][row]>0){
				::SetDataToTable(ui->tableWidget ,1+col ,RowCount-row-1 ,QString::number(NGList[col][row],'f',2));
			}
		}
	}
	ui->tableWidget->setUpdatesEnabled(true);
}

BladeLogForm::~BladeLogForm()
{
    delete ui;
	for(int i=0;i<CountGraphLine;i++){
		delete	[]NGList[i];
		NGList[i]=NULL;
	}
	delete	[]InspectionID;
	InspectionID=NULL;
	delete	[]InspectionTime;
	InspectionTime=NULL;
}

void BladeLogForm::on_pushButtonClose_clicked()
{
	close();
}

void BladeLogForm::on_pushButtonExcel_clicked()
{
	QString	ExcelFileName=QFileDialog::getSaveFileName(NULL
													,LangSolver.GetString(BladeLogForm_LS,LID_3)/*"Save EXCEL"*/
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
	switch (GetLayersBase()->GetLanguageCode()) {
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

	WriteCell(0, 0,LangSolver.GetString(BladeLogForm_LS,LID_9)/*"作成日時"*/);
	WriteCell(0, 1,QDateTime::currentDateTime().toString());

	WriteCell(1, 0,LangSolver.GetString(BladeLogForm_LS,LID_10)/*"マスター"*/);
	for(int col=0;col<CountGraphLine;col++){
		WriteCell(1, 1+col,Headers[col+1]);
	}
	for(int row=0;row<RowCount;row++){
		int	Row=row+2;
		WriteCell(Row,0 ,QString::number(InspectionID[row])
												+ QString(/**/"-")
												+ InspectionTime[row].toString(/**/"hh:mm:ss"));
		for(int col=0;col<CountGraphLine;col++){
			if(NGList[col][row]>0){
				WriteCell(Row,1+col ,QString::number(NGList[col][row],'f',2));
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

void BladeLogForm::resizeEvent ( QResizeEvent * event )
{
	ui->frame->setGeometry(0,height()-ui->frame->height(),width(),ui->frame->height());
	ui->tableWidget->setGeometry(0,0,width(),height()-ui->frame->height());

	int	W=width();
	ui->tableWidget->setColumnWidth(0,80);
	W-=80+48;
	if(CountGraphLine>0){
		int	EachWidth=W/CountGraphLine;
		for(int col=0;col<CountGraphLine;col++){
			ui->tableWidget->setColumnWidth(col,EachWidth);
		}
	}
}

void	BladeLogForm::WriteCell(int Row, int Col ,const QString &Str)
{
	wchar_t	Buff[1000];
	memset(Buff,0,sizeof(Buff));
	Str.toWCharArray(Buff);

	XLSXSheet->setCellFormat(Row, Col,Lang);
	XLSXSheet->writeStr(Row, Col,Buff);
}

void	BladeLogForm::WriteCellV(int Row, int Col ,const QVariant &Data)
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
