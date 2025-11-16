#include "ShowPrintTotalBladeForm.h"
#include "ui_ShowPrintTotalBladeForm.h"
#include "swap.h"
#include "XMeasureLineMove.h"
#include "XIntegrationBasePacket.h"
#include "XDataInLayer.h"
#include "XDatabaseLoader.h"
#include <QSqlQuery>
#include <QBuffer>
#include <QSqlRecord>
#include <QImage>
#include "CartonMenuForm.h"

static	const	wchar_t	*ExcelUser	=L"MASATOSHI SASAI";
static	const	wchar_t* ExcelKey	=L"windows-252a28070ccee00f6fbd6d65ady7m2ue";

BladeResultInMachine::BladeResultInMachine(void)
{	
	CountingPoint	=0;
	AllocatedResultCount	=MaxCountTotalResultDim;
	ResultDim	=new BladeResult[AllocatedResultCount];
	ResultCount		=0;
	for(int i=0;i<AllocatedResultCount;i++){
		ResultDim[i].InspectionID=0;
	}
	BladeNGCount	=0;
}

BladeResultInMachine::~BladeResultInMachine(void)
{
	delete	[]ResultDim;
	ResultDim			=NULL;
	ResultCount			=0;
	AllocatedResultCount=0;
	BladeNGCount		=0;
}

void	BladeResultInMachine::SetResultPage(InspectionList *n)
{
	if(ResultCount<AllocatedResultCount){
		bool	NGFlag=false;
		for(NGPointInAllPage *Ph=n->NGPointAllPhases.GetFirst();Ph!=NULL;Ph=Ph->GetNext()){
			for(NGPointInPage *Pg=Ph->NPListPack<NGPointInPage>::GetFirst();Pg!=NULL;Pg=Pg->GetNext()){
				for(NGPoint *p=Pg->NPListPack<NGPoint>::GetFirst();p!=NULL;p=p->GetNext()){
					if(p->LibType==DefLibTypeMeasureLineMove && p->UniqueID<MaxCountOfMeasureBlade){
						int	N=p->UniqueID;
						ResultDim[ResultCount].InspectionID	=n->ID;
						ResultDim[ResultCount].ResultDouble[N]=p->DoubleCause;
						if(p->Error>1){
							NGFlag=true;
						}
					}
				}
			}
		}
		if(NGFlag==true){
			BladeNGCount++;
		}
		ResultCount++;
	}
}
void	BladeResultInMachine::RemoveAll(void)
{
	CountingPoint=0;

	for(int i=0;i<AllocatedResultCount;i++){
		ResultDim[i].InspectionID=0;
	}
	ResultCount	=0;
}

//------------------------------------------------------------------------------------------

ShowPrintTotalBladeForm::ShowPrintTotalBladeForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::ShowPrintTotalBladeForm)
{
    ui->setupUi(this);

	TopCount	=0;
	BottomCount	=0;
	MonoCount	=0;
	TopNG		=0;
	BottomNG	=0;
	MonoNG		=0;
}

ShowPrintTotalBladeForm::~ShowPrintTotalBladeForm()
{
    delete ui;
}

void	ShowPrintTotalBladeForm::ReadyParam(void)
{
	connect(GetLayersBase()->GetIntegrationBasePointer(),SIGNAL(SignalDoneLoadResult(InspectionList *)),this,SLOT(SlotDoneLoadResult(InspectionList *)));
}
void	ShowPrintTotalBladeForm::ShowData(void)
{
	int	TotalCount	=GetLayersBase()->GetIntegrationBasePointer()->TotalCount;
	int	NGCount		=GetLayersBase()->GetIntegrationBasePointer()->NGCount;
	ui->label_TotalCount	->setText(QString::number(TotalCount));
	//ui->label_NGCount		->setText(QString::number(NGCount));


	int	BladeNG= BladeResultTop.BladeNGCount
				+BladeResultBottom.BladeNGCount;
	int	BladeTotal	=BladeResultTop.ResultCount
					+BladeResultBottom.ResultCount;
	ui->label_BladeOKCount	->setText(QString::number(TotalCount-BladeNG));
	ui->label_BladeNG		->setText(QString::number(BladeNG));

	EachMaster	*M0		=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(0);
	if(M0!=NULL){
		int	TopNGCount		=M0->GetCurrentInspection().NGCount;
		int	TopTotalCount	=M0->GetCurrentInspection().TotalCount;
		ui->label_TopCount		->setText(QString::number(TopTotalCount-TopNGCount));
		ui->label_TopNGCount	->setText(QString::number(TopNGCount));
	}

	EachMaster	*M1		=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(1);
	if(M1!=NULL){
		int	BottomNGCount	=M1->GetCurrentInspection().NGCount;
		int	BottomTotalCount=M1->GetCurrentInspection().TotalCount;
		ui->label_BottomCount	->setText(QString::number(BottomTotalCount-BottomNGCount));
		ui->label_BottomNGCount	->setText(QString::number(BottomNGCount));
	}

	EachMaster	*M2		=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(2);
	if(M2!=NULL){
		int	MonoNGCount		=M2->GetCurrentInspection().NGCount;
		int	MonoTotalCount	=M2->GetCurrentInspection().TotalCount;
		ui->label_MonoOKCount	->setText(QString::number(MonoTotalCount-MonoNGCount));
		ui->label_MonoNGCount	->setText(QString::number(MonoNGCount));
	}
}
void	ShowPrintTotalBladeForm::SpecifiedDirectly(SpecifiedBroadcaster *v)
{
	CmdChangeLotID	*CmdChangeLotIDVar=dynamic_cast<CmdChangeLotID *>(v);
	CmdChangeNewLotID	*CmdChangeNewLotIDVar=dynamic_cast<CmdChangeNewLotID *>(v);
	CmdUpdatedMasterImage	*CmdUpdatedMasterImageVar=dynamic_cast<CmdUpdatedMasterImage *>(v);
	if(CmdChangeLotIDVar!=NULL || CmdUpdatedMasterImageVar!=NULL || CmdChangeNewLotIDVar!=NULL){
		TopCount	=0;
		BottomCount	=0;
		MonoCount	=0;
		TopNG		=0;
		BottomNG	=0;
		MonoNG		=0;
		BladeResultTop		.RemoveAll();
		BladeResultBottom	.RemoveAll();

		BladeResultTop.BladeNGCount		=0;
		BladeResultBottom.BladeNGCount	=0;
		BladeResultTop.ResultCount		=0;
		BladeResultBottom.ResultCount	=0;
		ShowData();
		return;
	}
}

void	ShowPrintTotalBladeForm::SlotDoneLoadResult(InspectionList *n)
{
	ShowData();
	if(n!=NULL){
		EachMaster	*m=n->GetMaster();
		if(m->GetIntegrationSlaveNo()==0)
			BladeResultTop.SetResultPage(n);
		else
			BladeResultBottom.SetResultPage(n);
	}
	else{
		BladeResultTop.RemoveAll();
		BladeResultBottom.RemoveAll();
	}
	emit	SignalUpdated();
}


void	ShowPrintTotalBladeForm::WriteCell(int Row, int Col ,const QString &Str)
{
	wchar_t	Buff[1000];
	memset(Buff,0,sizeof(Buff));
	Str.toWCharArray(Buff);

	XLSXSheet->setCellFormat(Row, Col,Lang);
	XLSXSheet->writeStr(Row, Col,Buff);
}

void	ShowPrintTotalBladeForm::WriteCellV(int Row, int Col ,const QVariant &Data)
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

void ShowPrintTotalBladeForm::on_pushButtonExcelSave_clicked()
{
	QString	ExcelFileName=QFileDialog::getSaveFileName(NULL
													,"Save EXCEL"
													,QString()
													,/**/"Excel(*.xlsx);;All files(*.*)");
	if(ExcelFileName.isEmpty()==true)
		return;

	IntegrationBase	*MBase=GetLayersBase()->GetIntegrationBasePointer();
	EachMaster		*M0=MBase->GetMaster(0);
	if(M0==NULL)
		return;

	QString	RetRelationNumber;
	QString	RetRelationName;
	QString	RetRemark;
	int		RetRelationType;
	QByteArray	CommonData;
	int32	ThresholdLevelID;
	if(MBase->GetInformation(RetRelationNumber
							,RetRelationName
							,RetRemark
							,RetRelationType
							,CommonData
							,ThresholdLevelID)==false){
		return;
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
	WriteCell(1, 1,QString::number(MBase->GetMasterRelationCode()));
	WriteCell(2, 0,"名称");
	WriteCell(2, 1,RetRelationNumber);
	WriteCell(2, 2,RetRelationName);
	WriteCell(3, 0,"備考");
	WriteCell(3, 1,RetRemark);

	WriteCell(4, 0,"ロット");
	if(M0->GetCurrentLot()==NULL){
		WriteCell(4, 1,"ロットなし");
	}
	else{
		WriteCell(4, 1,M0->GetCurrentLot()->LotName);
	}
	int	Row=5;

	for(EachMaster *m=MBase->MasterDatas.GetFirst();m!=NULL;m=m->GetNext()){
		int	SlaveNo=m->GetIntegrationSlaveNo();
		WriteCell(Row, 0,"検査ユニット");
		WriteCell(Row, 1,m->GetMachineName());

		XLSXSheet->setRow(Row,256);

		QTemporaryFile	TmpImageFile;
		TmpImageFile.setAutoRemove(true);
		if(TmpImageFile.open()==true){
			QString	TmpImageFileName=TmpImageFile.fileName();
			QImage	TopView=LoadDataFromMaster(m->GetMasterCode());
			TopView.save(&TmpImageFile,"PNG");
			TmpImageFile.flush();
			TmpImageFile.close();
			wchar_t	TmpImageFileBuff[1000];
			memset(TmpImageFileBuff,0,sizeof(TmpImageFileBuff));
			TmpImageFileName.toWCharArray(TmpImageFileBuff);

			int	ImageID=XLSXBook->addPicture(TmpImageFileBuff);
			XLSXSheet->setPicture2(Row, 2, ImageID, 256, 256);
		}

		Row++;

		IntegrationReqUsageAlgorithm	RCmd(GetLayersBase(),/**/"ANY",/**/"ANY",SlaveNo);
		IntegrationAckUsageAlgorithm	ACmd(GetLayersBase(),/**/"ANY",/**/"ANY",SlaveNo);
		if(RCmd.Send(SlaveNo,0,ACmd)==true){
			for(AlgorithmRootNameList *a=ACmd.Datas.GetFirst();a!=NULL;a=a->GetNext()){
				IntegrationReqReportedTopics	ItemRCmd(GetLayersBase(),/**/"ANY",/**/"ANY",SlaveNo);
				IntegrationAckReportedTopics	ItemACmd(GetLayersBase(),/**/"ANY",/**/"ANY",SlaveNo);

				ItemRCmd.DLLRoot=a->DLLRoot;
				ItemRCmd.DLLName=a->DLLName;

				QStringList	TopicTitleList;

				if(ItemRCmd.Send(SlaveNo,0,ItemACmd)==true){
					for(ReportedTopicsInItem *Item=ItemACmd.Datas.GetFirst();Item!=NULL;Item=Item->GetNext()){
						QString	LibName=GetLayersBase()->GetDatabaseLoader()->G_GetLibraryName2(*GetLayersBase()->GetDataBase(),a->LibType,Item->LibID);
						WriteCell(Row, 0,QString::number(Item->LibID));
						WriteCell(Row, 1,LibName);
						int	Col=2;
						for(ReportedTopic *t=Item->TopicsContainer.GetFirst();t!=NULL;t=t->GetNext(),Col++){
							WriteCell(Row, Col,t->Title);
						}
						Row++;
						Col=2;
						for(ReportedTopic *t=Item->TopicsContainer.GetFirst();t!=NULL;t=t->GetNext(),Col++){
							WriteCellV(Row, Col,t->Data);
						}
						Row++;
					}
				}
			}
		}
	}

	WriteCell(Row, 0,"全体検査数");
	WriteCell(Row, 1,QString::number(GetLayersBase()->GetIntegrationBasePointer()->TotalCount));
	Row++;
	WriteCell(Row, 0,"全体NG数");
	WriteCell(Row, 1,QString::number(GetLayersBase()->GetIntegrationBasePointer()->NGCount));
	Row++;

	int	BladeNG= BladeResultTop.BladeNGCount
				+BladeResultBottom.BladeNGCount;
	WriteCell(Row, 0,"刃のNG数");
	WriteCell(Row, 1,QString::number(BladeNG));

	if(M0!=NULL){
		WriteCell(Row, 0,"上流NG数");
		WriteCell(Row, 1,QString::number(M0->GetCurrentInspection().NGCount));
		Row++;
	}

	EachMaster	*M1		=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(1);
	if(M1!=NULL){
		WriteCell(Row, 0,"下流NG数");
		WriteCell(Row, 1,QString::number(M1->GetCurrentInspection().NGCount));
		Row++;
	}
	EachMaster	*M2		=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(2);
	if(M2!=NULL){
		WriteCell(Row, 0,"モノクロNG数");
		WriteCell(Row, 1,QString::number(M2->GetCurrentInspection().NGCount));
		Row++;
	}
	InspectionList	*L0=NULL;
	InspectionList	*L1=NULL;
	InspectionList	*L2=NULL;
	if(M0!=NULL){
		L0=M0->GetCurrentInspection().GetLast();
	}
	if(M1!=NULL){
		L1=M1->GetCurrentInspection().GetLast();
	}
	if(M2!=NULL){
		L2=M2->GetCurrentInspection().GetLast();
	}
	int	Printout_MaxCountfNGImage=0;
	CartonMenuForm	*GProp=(CartonMenuForm *)GetLayersBase()->FindByName(/**/"KidaPrint" ,/**/"CartonMenu" ,/**/"");
	if(GProp!=NULL){
		Printout_MaxCountfNGImage=GProp->GetParam()->Printout_MaxCountfNGImage;
	}
	int	N=0;
	while(N<Printout_MaxCountfNGImage){
		if(L0!=NULL){
			N=SetNGImageToExcel(L0,Printout_MaxCountfNGImage,N,Row);
			L0=L0->GetPrev();
		}
		if(L1!=NULL){
			N=SetNGImageToExcel(L1,Printout_MaxCountfNGImage,N,Row);
			L1=L1->GetPrev();
		}
		if(L2!=NULL){
			N=SetNGImageToExcel(L2,Printout_MaxCountfNGImage,N,Row);
			L2=L2->GetPrev();
		}
		if(L0==NULL && L1==NULL && L2==NULL){
			break;
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

	return;
}
QImage ShowPrintTotalBladeForm::LoadDataFromMaster(int masterCode)
{
	QString	S=QString(/**/"SELECT"
							/**/" TOPVIEW"
							/**/" from MASTERDATA where MASTERCODE=")+QString::number(masterCode);
	QSqlQuery query(S ,GetLayersBase()->GetDatabase());
	if(query.next()==true){
		QByteArray	STopview=query.value(query.record().indexOf("TOPVIEW")).toByteArray();
		QBuffer	TopviewBuff;
		TopviewBuff.setData(STopview);
		if(TopviewBuff.open(QIODevice::ReadOnly)==true){
			QImage	TopView;
			if(TopView.load(&TopviewBuff,"PNG")==true){
				return TopView;
			}
		}
	}
	return QImage();
}

int	ShowPrintTotalBladeForm::SetNGImageToExcel(InspectionList *L, int Printout_MaxCountfNGImage ,int N,int &Row)
{
	if(N>=Printout_MaxCountfNGImage){
		return N;
	}
	for(NGPointInAllPage *Ph=L->NGPointAllPhases.GetFirst();Ph!=NULL;Ph=Ph->GetNext()){
		for(NGPointInPage *Pg=Ph->NPListPack<NGPointInPage>::GetFirst();Pg!=NULL;Pg=Pg->GetNext()){
			for(IntegNGImage *g=Pg->NGImages.GetFirst();g!=NULL;g=g->GetNext()){
				WriteCell(Row, 0,L->GetMaster()->GetMachineName());

				QTemporaryFile	TmpImageFile;
				TmpImageFile.setAutoRemove(true);
				if(TmpImageFile.open()==true){
					XLSXSheet->setRow(Row,256);
					QString	TmpImageFileName=TmpImageFile.fileName();
					g->GetImage().save(&TmpImageFile,"PNG");
					TmpImageFile.flush();
					TmpImageFile.close();
					wchar_t	TmpImageFileBuff[10000];
					memset(TmpImageFileBuff,0,sizeof(TmpImageFileBuff));
					TmpImageFileName.toWCharArray(TmpImageFileBuff);

					int	ImageID=XLSXBook->addPicture(TmpImageFileBuff);
					XLSXSheet->setPicture2(Row, 1, ImageID, g->GetImage().width(), g->GetImage().height());
				}
				for(NGPoint *Rp=Pg->NPListPack<NGPoint>::GetFirst();Rp!=NULL;Rp=Rp->GetNext()){
					int	TargetCx,TargetCy;
					Rp->GetTargetCenter(TargetCx,TargetCy);
					if(Rp->IsNG()==true
					&& g->x1 <=TargetCx && TargetCx<g->x2
					&& g->y1 <=TargetCy && TargetCy<g->y2){
						QString	LibName=GetLayersBase()->GetDatabaseLoader()->G_GetLibraryName2(*GetLayersBase()->GetDataBase(), Rp->LibType,Rp->LibID);
						WriteCell(Row, 2,QString::number(Rp->LibID));
						WriteCell(Row, 3,LibName);
						WriteCell(Row, 4,QString::number(Rp->Cause[0]));
						break;
					}
				}
				Row++;
				N++;
				if(N>=Printout_MaxCountfNGImage){
					return N;
				}
			}
		}
	}
	return N;
}
void ShowPrintTotalBladeForm::on_PushButtonReset_clicked()
{
	GetLayersBase()->GetIntegrationBasePointer()->TotalCount	=0;
	GetLayersBase()->GetIntegrationBasePointer()->NGCount		=0;

	BladeResultTop	 .BladeNGCount=0;
	BladeResultBottom.BladeNGCount=0;

	EachMaster	*M0		=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(0);
	if(M0!=NULL){
		M0->ResetCounterCurrentInspection();
	}

	EachMaster	*M1		=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(1);
	if(M1!=NULL){
		M1->ResetCounterCurrentInspection();
	}
	EachMaster	*M2		=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(2);
	if(M2!=NULL){
		M2->ResetCounterCurrentInspection();
	}
	ShowData();
}
