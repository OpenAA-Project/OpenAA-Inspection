#include "BladeNGListForm.h"
#include "ui_BladeNGListForm.h"
#include "XMeasureLineMove.h"
#include "ShowPrintTotalBladeForm.h"
#include "EasyPropertyDentMeasureForm.h"

static	const	wchar_t	*ExcelUser	=L"MASATOSHI SASAI";
static	const	wchar_t* ExcelKey = L"windows-252a28070ccee00f6fbd6d65ady7m2ue";

BladeList::BladeList(int index,BladeNGListForm *p)
	:Parent(p),Index(index)
{
	Machine			=NULL;
	LibID			=-1;
	UniqueID		=-1;
	IndexInMachine	=-1;
	StartIndex		=-1;
}
	

BladeNGListForm::BladeNGListForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::BladeNGListForm)
{
    ui->setupUi(this);

	Clear();
	for(int i=0;i<MaxCountGraphLine;i++){
		BladeListDim[i]=new BladeList(i,this);
	}
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

BladeNGListForm::~BladeNGListForm()
{
	for(int i=0;i<MaxCountGraphLine;i++){
		delete	[]BladeListDim[i];
	}
	delete ui;
}

void	BladeNGListForm::ResizeAction()
{
	ui->frame->resize(width(),ui->frame->height());
	ui->tableWidgetNGList->resize(width(),height()-ui->frame->height());
	ui->pushButtonExcelOut->move((width()-ui->pushButtonExcelOut->width())/2,2);
}
void	BladeNGListForm::Prepare(void)
{
	ResizeAction();
}
void	BladeNGListForm::ReadyParam(void)
{
	ShowPrintTotalBladePointer		=(ShowPrintTotalBladeForm	  *)GetLayersBase()->FindByName(/**/"KidaPrint",/**/"ShowPrintTotalBlade",/**/"");

	GUIFormBase *Ret[10];
	int N=GetLayersBase()->EnumGUIInst(/**/"KidaPrint",/**/"EasyPropertyDentMeasure",Ret ,10);
	for(int i=0;i<N;i++){
		EasyPropertyDentMeasureForm		*f=dynamic_cast<EasyPropertyDentMeasureForm	*>(Ret[i]);
		if(f!=NULL && f->SlaveNo>=0 && f->SlaveNo<10){
			EasyPropertyDentMeasurePointer[f->SlaveNo]	=f;
		}
	}
	connect(GetLayersBase()->GetIntegrationBasePointer(),SIGNAL(SignalInspectionDone(int,int64,bool))
			,this,SLOT(SlotInspectionDone(int,int64,bool)));
}

void	BladeNGListForm::SpecifiedDirectly(SpecifiedBroadcaster *v)
{
	CmdReqUpdateHistory	*CmdReqUpdateHistoryVar=dynamic_cast<CmdReqUpdateHistory *>(v);
	if(CmdReqUpdateHistoryVar!=NULL){
		return;
	}
	CmdChangeLotID	*CmdChangeLotIDVar=dynamic_cast<CmdChangeLotID *>(v);
	if(CmdChangeLotIDVar!=NULL){
		Clear();
		return;
	}
	CmdChangeNewLotID	*CmdChangeNewLotIDVar=dynamic_cast<CmdChangeNewLotID *>(v);
	if(CmdChangeNewLotIDVar!=NULL){
		Clear();
		return;
	}
}

void	BladeNGListForm::SlotInspectionDone(int SlaveNo,int64 InspectionID,bool OK)
{
	EachMaster	*M		=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
	if(M!=NULL){
		SetBladeList(M);
	}
	ShowData();
}

void	BladeNGListForm::SetBladeList(EachMaster *M)
{
	bool	FlagAddLine=false;
	int		LastCountGraphLine=CountGraphLine;
	InspectionList	*n=M->GetCurrentInspection().GetFirst();
	if(n!=NULL){
		for(NGPointInAllPage *Ph=n->NGPointAllPhases.GetFirst();Ph!=NULL;Ph=Ph->GetNext()){
			for(NGPointInPage *Pg=Ph->NPListPack<NGPointInPage>::GetFirst();Pg!=NULL;Pg=Pg->GetNext()){
				for(NGPoint *p=Pg->NPListPack<NGPoint>::GetFirst();p!=NULL;p=p->GetNext()){
					if(p->LibType==DefLibTypeMeasureLineMove){
						bool	Found=false;
						for(int i=0;i<CountGraphLine;i++){
							if(BladeListDim[i]->Machine==M
							&& BladeListDim[i]->LibID==p->LibID
							&& BladeListDim[i]->UniqueID==p->UniqueID){
								Found=true;
								break;
							}
						}
						if(Found==false && CountGraphLine<MaxCountGraphLine){
							int		IndexInMachine=0;
							for(int i=0;i<CountGraphLine;i++){
								if(BladeListDim[i]->Machine==M){
									IndexInMachine++;
								}
							}
							BladeListDim[CountGraphLine]->Machine	=M;
							BladeListDim[CountGraphLine]->IndexInMachine	=IndexInMachine;
							BladeListDim[CountGraphLine]->LibID	=p->LibID;
							BladeListDim[CountGraphLine]->UniqueID	=p->UniqueID;
							CountGraphLine++;
							FlagAddLine=true;
						}
					}
				}
			}
		}
	}
	if(FlagAddLine==true){
		//ui->tableWidgetNGList->clear();
		SetLabels();
	}
}
void	BladeNGListForm::StartLot(void)
{
	SetLabels();
}
void	BladeNGListForm::SetLabels(void)
{
	//ReflectAlignment();
	//ResizeAction();

	ui->tableWidgetNGList->setColumnCount(CountGraphLine+2);
	QStringList	Labels;
	Labels.append(/**/"ID");
	Labels.append(/**/"日時");
	for(int Col=0;Col<CountGraphLine;Col++){
		QString	Str;
		EasyPropertyDentMeasureForm	*f=EasyPropertyDentMeasurePointer[BladeListDim[Col]->Machine->GetIntegrationSlaveNo()];
		if(f!=NULL){
			Str=QString::fromLocal8Bit(f->BladeMeasureData.GenDatas[Col].MeasureName);
		}
		if(Str.isEmpty()==true){
			Str=QString("Blade")+QString::number(Col+1);
		}
		Labels.append(Str);
	}
	ui->tableWidgetNGList->setHorizontalHeaderLabels(Labels);
	for(int row=CountGraphLine;row<MaxCountGraphLine;row++){
		BladeListDim[row]->Machine=NULL;
	}

	ui->tableWidgetNGList->setColumnWidth(0,64);
	ui->tableWidgetNGList->setColumnWidth(1,100);
	if(CountGraphLine>0){
		int	Wid=ui->tableWidgetNGList->width();
		int	W=(Wid-64-100-64)/CountGraphLine;
		if(W<0){
			W=120;
		}
		for(int Col=0;Col<CountGraphLine;Col++){
			ui->tableWidgetNGList->setColumnWidth(2+Col,W);
		}
	}
}

void	BladeNGListForm::Clear(void)
{
	LastInspectionID=0;
	CountGraphLine=0;
	ui->tableWidgetNGList->setRowCount(0);
}


void	BladeNGListForm::ShowData(void)
{
	if(CountGraphLine>0){
		EachMaster *M=BladeListDim[0]->Machine;
		for(InspectionList	*n=M->GetCurrentInspection().GetFirst();n!=NULL;n=n->GetNext()){
			if(n->ID<=LastInspectionID)
				continue;
			LastInspectionID=n->ID;
			bool	FoundNG=false;
			bool	AddedLine=false;
			for(NGPointInAllPage *Ph=n->NGPointAllPhases.GetFirst();Ph!=NULL;Ph=Ph->GetNext()){
				for(NGPointInPage *Pg=Ph->NPListPack<NGPointInPage>::GetFirst();Pg!=NULL;Pg=Pg->GetNext()){
					for(NGPoint *p=Pg->NPListPack<NGPoint>::GetFirst();p!=NULL;p=p->GetNext()){
						if(p->Error>=2 && p->LibType==DefLibTypeMeasureLineMove){
							for(int i=0;i<CountGraphLine;i++){
								if(BladeListDim[i]->UniqueID==p->UniqueID){
									if(AddedLine==false){
										ui->tableWidgetNGList->insertRow(0);
										if(ui->tableWidgetNGList->rowCount()==1){
											SetLabels();
										}
										AddedLine=true;
										::SetDataToTable(ui->tableWidgetNGList ,0,0 ,QString::number(n->ID));
										::SetDataToTable(ui->tableWidgetNGList ,1,0 ,QDateTime::currentDateTime().toString(/**/"dd-hh:mm:ss"));
									}
									::SetDataToTable(ui->tableWidgetNGList ,i+2,0 ,QString::number(p->DoubleCause,'f',2));
									break;
								}
							}
							FoundNG=true;
						}
					}
				}
			}
		}
	}
}

void BladeNGListForm::on_pushButtonExcelOut_clicked()
{
	QString	ExcelFileName=QFileDialog::getSaveFileName(NULL
													,"Save EXCEL"
													,QString()
													,/**/"Excel(*.xlsx);;All files(*.*)");
	if(ExcelFileName.isEmpty()==true)
		return;

	int		CountGraphLine;
	int		BladeItemID[100];
	int		*InspectionID;
	double	*NGList[100];
	int		RowCount;
	XDateTime			*InspectionTime;
	QStringList	Headers;


	CountGraphLine=0;
	
	Headers.append(/**/"ID-Time");
	for(EachMaster *M=GetLayersBase()->GetIntegrationBasePointer()->MasterDatas.GetFirst();M!=NULL;M=M->GetNext()){
		InspectionList	*n=M->GetCurrentInspection().GetFirst();
		if(n!=NULL){
			for(NGPointInAllPage *Ph=n->NGPointAllPhases.GetFirst();Ph!=NULL;Ph=Ph->GetNext()){
				for(NGPointInPage *Pg=Ph->NPListPack<NGPointInPage>::GetFirst();Pg!=NULL;Pg=Pg->GetNext()){
					for(NGPoint *p=Pg->NPListPack<NGPoint>::GetFirst();p!=NULL;p=p->GetNext()){
						if(p->LibType==DefLibTypeMeasureLineMove){
							if(CountGraphLine<100){
								QString	Str;
								EasyPropertyDentMeasureForm	*f=EasyPropertyDentMeasurePointer[M->GetIntegrationSlaveNo()];
								if(f!=NULL){
									Str=QString::fromLocal8Bit(f->BladeMeasureData.GenDatas[CountGraphLine].MeasureName);
								}
								if(Str.isEmpty()==true){
									Str=QString("Blade")+QString::number(CountGraphLine+1);
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

	XLSXBook = xlCreateXMLBook();
	XLSXBook->setKey(ExcelUser, ExcelKey);
	XLSXSheet=XLSXBook->addSheet(L"Master");

	Lang	=XLSXBook->addFormat();
	Fnt	=XLSXBook->addFont();

	QString	FontName;
	switch (GetLayersBase()->GetLanguageCode()) {
	case 0:	FontName = "ＭＳ Ｐゴシック";	break;
	case 1:	FontName = "Arial";				break;
	case 2:	FontName = "SimSun";			break;
	case 3:	FontName = "MingLiU";			break;
	case 4:	FontName = "Gulim";				break;
	}
	wchar_t	WBuff[100];
	memset(WBuff, 0, sizeof(WBuff));
	FontName.toWCharArray(WBuff);
	Fnt->setName(WBuff);

	Lang->setFont(Fnt);

	WriteCell(0, 0,"作成日時");
	WriteCell(0, 1,QDateTime::currentDateTime().toString());

	WriteCell(1, 0,"マスター");
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


	for(int i=0;i<CountGraphLine;i++){
		delete	[]NGList[i];
		NGList[i]=NULL;
	}
	delete	[]InspectionID;
	InspectionID=NULL;
	delete	[]InspectionTime;
	InspectionTime=NULL;
}

void	BladeNGListForm::WriteCell(int Row, int Col ,const QString &Str)
{
	wchar_t	Buff[1000];
	memset(Buff,0,sizeof(Buff));
	Str.toWCharArray(Buff);

	XLSXSheet->setCellFormat(Row, Col,Lang);
	XLSXSheet->writeStr(Row, Col,Buff);
}

void	BladeNGListForm::WriteCellV(int Row, int Col ,const QVariant &Data)
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

void BladeNGListForm::on_pushButtonReDraw_clicked()
{
	ShowData();
}
