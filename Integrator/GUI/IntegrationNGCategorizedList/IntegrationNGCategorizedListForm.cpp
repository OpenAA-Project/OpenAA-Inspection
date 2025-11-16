#include "IntegrationNGCategorizedListResource.h"
#include "IntegrationNGCategorizedListForm.h"
#include "ui_IntegrationNGCategorizedListForm.h"
#include "XGeneralFunc.h"
#include <QStringList>
#include "XDLLType.h"

static	const	wchar_t	*ExcelUser	=L"MASATOSHI SASAI";
static	const	wchar_t* ExcelKey = L"windows-252a28070ccee00f6fbd6d65ady7m2ue";

IntegrationNGCategorizedListForm::IntegrationNGCategorizedListForm(LayersBase *Base,QWidget *parent) :
    QWidget(parent)
	,ServiceForLayers(Base)
    ,ui(new Ui::IntegrationNGCategorizedListForm)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);

	XLSXBook	=NULL;
	XLSXSheet	=NULL;
	Lang		=NULL;
	Fnt			=NULL;

	if(GetLayersBase()->GetIntegrationBasePointer()!=NULL){
		int	MachineCount=GetLayersBase()->GetIntegrationBasePointer()->GetIntegrationSlaveCount();
		ui->tableWidget->setColumnCount(MachineCount+1);

		::SetColumnWidthInTable(ui->tableWidget ,0, 40);
		int	Percentage=60/MachineCount;
		for(int i=0;i<MachineCount;i++){
			::SetColumnWidthInTable(ui->tableWidget ,i+1, Percentage);
		}

		QStringList	SlaveLabels;
		SlaveLabels.append(LangSolver.GetString(IntegrationNGCategorizedListForm_LS,LID_1)/*"NG category"*/);
		for(int i=0;i<MachineCount;i++){
			EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(i);
			if(m!=NULL){
				SlaveLabels.append(m->GetMachineName());
			}
			else{
				SlaveLabels.append(/**/"");
			}
		}
		ui->tableWidget->setHorizontalHeaderLabels(SlaveLabels);
	}
	MakeList();
}

IntegrationNGCategorizedListForm::~IntegrationNGCategorizedListForm()
{
    delete ui;
}

class NGTypeList : public NPList<NGTypeList>
{
public:
	int	PosResult;
	int	LibType;
	int	LibID;
	int	UniqueID;

	int	Count[20];

	NGTypeList(void);
};

class NGTypeListContainer : public NPListPack<NGTypeList>
{
public:
	NGTypeListContainer(void){}

	NGTypeList	*Find(NGPoint *p);
};

NGTypeList::NGTypeList(void)
{
	memset(Count,0,sizeof(Count));
}
NGTypeList	*NGTypeListContainer::Find(NGPoint *p)
{
	for(NGTypeList *q=GetFirst();q!=NULL;q=q->GetNext()){
		if(q->PosResult	==p->PosResult
		&& q->LibType	==p->LibType
		&& q->LibID		==p->LibID){
		//&& q->UniqueID	==p->UniqueID){
			return q;
		}
	}
	NGTypeList	*r=new NGTypeList();
	r->PosResult=p->PosResult;
	r->LibType	=p->LibType;
	r->LibID	=p->LibID;
	r->UniqueID	=p->UniqueID;
	AppendList(r);
	return r;
}

void IntegrationNGCategorizedListForm::MakeList(void)
{
	if(GetLayersBase()->GetIntegrationBasePointer()!=NULL){
		int	MachineCount=GetLayersBase()->GetIntegrationBasePointer()->GetIntegrationSlaveCount();
		NGTypeListContainer	NGContainer;
		for(int i=0;i<MachineCount;i++){
			EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(i);
			if(m!=NULL){
				for(InspectionList *s=m->GetCurrentInspection().GetFirst();s!=NULL;s=s->GetNext()){
					for(NGPointInAllPage *ph=s->NGPointAllPhases.GetFirst();ph!=NULL;ph=ph->GetNext()){
						for(NGPointInPage *pg=ph->NPListPack<NGPointInPage>::GetFirst();pg!=NULL;pg=pg->GetNext()){
							for(NGPoint *np=pg->NPListPack<NGPoint>::GetFirst();np!=NULL;np=np->GetNext()){
								if(np->Error>=2){
									NGTypeList	*k=NGContainer.Find(np);
									k->Count[i]++;
								}
							}
						}
					}
				}
			}
		}
		ui->tableWidget->setRowCount(NGContainer.GetCount());
		int	Row=0;
		for(NGTypeList *p=NGContainer.GetFirst();p!=NULL;p=p->GetNext(),Row++){
			QString	NGName=GetNGName(p);
			::SetDataToTable(ui->tableWidget,0, Row, NGName);
			for(int i=0;i<MachineCount;i++){
				::SetDataToTable(ui->tableWidget,i+1, Row, QString::number(p->Count[i]));
			}
		}
	}
}

QString	IntegrationNGCategorizedListForm::GetNGName(NGTypeList *Rp)
{
	QString	CauseStr;
	QString	LibName;
	DetailResultInfoListContainer ItemDetailList;
	if(Rp->LibType!=0){
		LibName=GetLayersBase()->GetIntegrationBasePointer()->GetLibraryName(Rp->LibType ,Rp->LibID);

		AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(Rp->LibType);
		if(ABase!=NULL){
			QRgb		NGColor;
			ResultPosList	RPos;
			RPos.result		=Rp->PosResult;
			ABase->GetDrawResultDetail(NULL ,&RPos ,ItemDetailList);
		}
		if(ItemDetailList.count()>0){
			DetailResultInfoList	*L=ItemDetailList.NPListPack<DetailResultInfoList>::GetFirst();
			return LibName+QString(/**/"-")+L->GetMessageOnly();
		}
		return LibName;
	}
	return /**/"No Lib";
}


void IntegrationNGCategorizedListForm::on_pushButtonOK_clicked()
{
	close();
}

void IntegrationNGCategorizedListForm::resizeEvent(QResizeEvent *event)
{
	ui->frame->setGeometry(0,height()-ui->frame->height(),width(),ui->frame->height());
	ui->tableWidget->setGeometry(0,0,width(),height()-ui->frame->height());

	if(GetLayersBase()->GetIntegrationBasePointer()!=NULL){
		int	MachineCount=GetLayersBase()->GetIntegrationBasePointer()->GetIntegrationSlaveCount();

		::SetColumnWidthInTable(ui->tableWidget ,0, 40);
		int	Percentage=60/MachineCount;
		for(int i=0;i<MachineCount;i++){
			::SetColumnWidthInTable(ui->tableWidget ,i+1, Percentage);
		}
	}
}


void	IntegrationNGCategorizedListForm::WriteCell(int Row, int Col ,const QString &Str)
{
	wchar_t	Buff[1000];
	memset(Buff,0,sizeof(Buff));
	Str.toWCharArray(Buff);

	XLSXSheet->setCellFormat(Row, Col,Lang);
	XLSXSheet->writeStr(Row, Col,Buff);
}

void	IntegrationNGCategorizedListForm::WriteCellV(int Row, int Col ,const QVariant &Data)
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
		QString	s(Data.toDate().toString(Qt::TextDate));
		s.toWCharArray(Buff);	
		XLSXSheet->writeStr(Row, Col,Buff);
	}
	else if(Data.type()==QVariant::DateTime){
		QString	s(Data.toDateTime().toString(Qt::TextDate));
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
		QString	s(Data.toTime().toString(Qt::TextDate));
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

void IntegrationNGCategorizedListForm::on_pushButtonEXCEL_clicked()
{
	QString	ExcelFileName=QFileDialog::getSaveFileName(NULL
													,LangSolver.GetString(IntegrationNGCategorizedListForm_LS,LID_3)/*"Save EXCEL"*/
													,QString()
													,/**/"Excel(*.xlsx);;All files(*.*)");
	if(ExcelFileName.isEmpty()==true)
		return;

	IntegrationBase	*MBase=GetLayersBase()->GetIntegrationBasePointer();
	if(MBase==NULL){
		return;
	}
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
	switch(GetLayersBase()->GetLanguageCode()){
		case 0:	FontName= /**/"ＭＳ Ｐゴシック";	break;
		case 1:	FontName= /**/"Arial";				break;
		case 2:	FontName= /**/"SimSun";				break;
		case 3:	FontName= /**/"MingLiU";			break;
		case 4:	FontName= /**/"Gulim";				break;
	}
	wchar_t	WBuff[100];
	memset(WBuff, 0, sizeof(WBuff));
	FontName.toWCharArray(WBuff);
	Fnt->setName(WBuff);

	Lang->setFont(Fnt);

	WriteCell(0, 0,LangSolver.GetString(IntegrationNGCategorizedListForm_LS,LID_9)/*"作成日時"*/);
	WriteCell(0, 1,QDateTime::currentDateTime().toString(Qt::TextDate));

	WriteCell(1, 0,LangSolver.GetString(IntegrationNGCategorizedListForm_LS,LID_10)/*"マスター"*/);
	WriteCell(1, 1,QString::number(MBase->GetMasterRelationCode()));
	WriteCell(2, 0,LangSolver.GetString(IntegrationNGCategorizedListForm_LS,LID_11)/*"名称"*/);
	WriteCell(2, 1,RetRelationNumber);
	WriteCell(2, 2,RetRelationName);
	WriteCell(3, 0,LangSolver.GetString(IntegrationNGCategorizedListForm_LS,LID_12)/*"備考"*/);
	WriteCell(3, 1,RetRemark);

	WriteCell(4, 0,LangSolver.GetString(IntegrationNGCategorizedListForm_LS,LID_13)/*"ロット"*/);
	if(M0->GetCurrentLot()!=NULL){
		WriteCell(4,1,M0->GetCurrentLot()->LotName);
	}
	else{
		WriteCell(4,1,"ロット無し");
	}
	
	int	Row=5;

	int	MachineCount=GetLayersBase()->GetIntegrationBasePointer()->GetIntegrationSlaveCount();
	NGTypeListContainer	NGContainer;
	for(int i=0;i<MachineCount;i++){
		EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(i);
		if(m!=NULL){
			for(InspectionList *s=m->GetCurrentInspection().GetFirst();s!=NULL;s=s->GetNext()){
				for(NGPointInAllPage *ph=s->NGPointAllPhases.GetFirst();ph!=NULL;ph=ph->GetNext()){
					for(NGPointInPage *pg=ph->NPListPack<NGPointInPage>::GetFirst();pg!=NULL;pg=pg->GetNext()){
						for(NGPoint *np=pg->NPListPack<NGPoint>::GetFirst();np!=NULL;np=np->GetNext()){
							if(np->Error>=2){
								NGTypeList	*k=NGContainer.Find(np);
								k->Count[i]++;
							}
						}
					}
				}
			}
		}
	}
	//ui->tableWidget->setRowCount(NGContainer.GetCount());
	//for(NGTypeList *p=NGContainer.GetFirst();p!=NULL;p=p->GetNext(),Row++){
	//	QString	NGName=GetNGName(p);
	//	::SetDataToTable(ui->tableWidget,0, Row, NGName);
	//	for(int i=0;i<MachineCount;i++){
	//		::SetDataToTable(ui->tableWidget,i+1, Row, QString::number(p->Count[i]));
	//	}
	//}
}
