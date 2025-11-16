#include "NGMapForm.h"
#include "ui_NGMapForm.h"
#include "SelectRelationalMasterDataDialog.h"
#include "XGeneralFunc.h"
#include "XDatabaseLoader.h"
#include "MapForm.h"

void	MapListByMaster::Add(int x ,int y)
{
	NGPointList	*a=new NGPointList();
	a->XPos=x;
	a->YPos=y;
	NGPoints.AppendList(a);
}

NGMapForm::NGMapForm(LayersBase *base ,const QString &root ,const QString &name
						 ,QWidget *parent) :
    PQSystemRunner(base ,root ,name,parent)
	,LotForm(base)
    ,ui(new Ui::NGMapForm)
{
    ui->setupUi(this);
	ResultRelationCode	=-1;
	MapResult			=NULL;

	ui->dateTimeEditStart	->setDateTime(QDateTime::currentDateTime());
	ui->dateTimeEditEnd		->setDateTime(QDateTime::currentDateTime());

	LotForm.setParent(ui->frameSelectLot);
	LotForm.setGeometry(0,0,ui->frameSelectLot->width(),ui->frameSelectLot->height());
}

NGMapForm::~NGMapForm()
{
    delete ui;
	if(MapResult!=NULL){
		delete	MapResult;
		MapResult=NULL;
	}
}
bool	NGMapForm::Initial(void)
{
	return true;
}
const QString	NGMapForm::GetPath(void)
{
	return "マップ表示/場所ごとのNG個数マップ";
}
void NGMapForm::showEvent(QShowEvent *event)
{
	ResultRelationCode	=-1;

	ui->lineEditMasterID	->setText("");
	ui->lineEditMasterName	->setText("非選択で全マスターが対象");
}
void NGMapForm::on_pushButtonSelectMaster_clicked()
{
	SelectRelationalMasterDataDialog	D(GetLayersBase(),0,1,-1);
	if(D.exec()==(bool)true){
		ResultRelationCode=D.ResultRelationCode;
		QString		RetRelationNumber;
		QString		RetRelationName;
		QString		RetRemark;
		int			RetRelationType;
		QByteArray	CommonData;
		int32		ThresholdLevelID;
		if(GetMasterRelation(ResultRelationCode
							,RetRelationNumber
							,RetRelationName
							,RetRemark
							,RetRelationType
							,CommonData
							,ThresholdLevelID)==true){

			bool	tNoLoadSaveMasterImage=GetParamGlobal()->NoLoadSaveMasterImage;
			GetParamGlobal()->NoLoadSaveMasterImage=false;
			LoadMasterImage(ResultRelationCode);
			GetParamGlobal()->NoLoadSaveMasterImage =tNoLoadSaveMasterImage;

			ui->lineEditMasterID	->setText(QString::number(ResultRelationCode));
			ui->lineEditMasterName	->setText(RetRelationName);
			LotForm.Update();
		}
	}
}

void NGMapForm::on_pushButtonStartSearch_clicked()
{
	QDateTime	StartTime	=ui->dateTimeEditStart	->dateTime();
	QDateTime	EndTime		=ui->dateTimeEditEnd	->dateTime();

	AllLotList.RemoveAll();
	std::shared_ptr<DatabaseLoader>	Ld=GetLayersBase()->GetDatabaseLoader();
	if(ResultRelationCode<0){
		IntList RelationCodes;
		Ld->G_EnumMasterRelation(GetLayersBase()->GetDatabase() ,RelationCodes);
		int	N=RelationCodes.GetCount();
		if(N>0){
			ui->progressBar->setMaximum(N);
		}
		int	n=0;
		for(IntClass *c=RelationCodes.GetFirst();c!=NULL;c=c->GetNext(),n++){
			ui->progressBar->setValue(n);
			QString		RetRelationNumber;
			QString		RetRelationName;
			QString		RetRemark;
			int			RetRelationType;
			QByteArray	CommonData;
			int32		ThresholdLevelID;
			if(GetMasterRelation(c->GetValue()
								,RetRelationNumber
								,RetRelationName
								,RetRemark
								,RetRelationType
								,CommonData
								,ThresholdLevelID)==true){
				LotForm.Update();
				LotListContainerWithRelationCode	*L=new LotListContainerWithRelationCode();
				for(LotListWithResult *k=LotForm.LotContainer.GetFirst();k!=NULL;k=k->GetNext()){
					LotListWithResult	*h=new LotListWithResult();
					*h=*k;
					L->Container.AppendList(h);
				}
				L->RelationCode=c->GetValue();
				AllLotList.AppendList(L);
			}
		}
	}
	else{
		LotListContainerWithRelationCode	*L=new LotListContainerWithRelationCode();
		if(LotForm.CurrentLot==NULL){
			for(LotListWithResult *k=LotForm.LotContainer.GetFirst();k!=NULL;k=k->GetNext()){
				LotListWithResult	*h=new LotListWithResult();
				*h=*k;
				L->Container.AppendList(h);
			}
		}
		else{
			LotListWithResult	*h=new LotListWithResult();
			*h=*LotForm.CurrentLot;
			L->Container.AppendList(h);
		}
		L->RelationCode=ResultRelationCode;
		AllLotList.AppendList(L);
	}
	int	N=0;
	for(LotListContainerWithRelationCode *L=AllLotList.GetFirst();L!=NULL;L=L->GetNext()){
		N+=L->Container.GetCount();
	}
	if(N>0){
		ui->progressBar->setMaximum(N);
		ui->progressBar->setValue(0);
	}
	MapList.RemoveAll();
	IntegrationBase	*LBase=GetLayersBase()->GetIntegrationBasePointer();
	for(LotListContainerWithRelationCode *L=AllLotList.GetFirst();L!=NULL;L=L->GetNext()){
		for(LotListWithResult *h=L->Container.GetFirst();h!=NULL;h=h->GetNext()){
			ui->progressBar->setValue(ui->progressBar->value()+1);
			h->LoadResult(LBase);

			for(InspectionListByMaster *e=h->CurrentInspection.GetFirst();e!=NULL;e=e->GetNext()){
				MapListByMaster *M;
				for(M=MapList.GetFirst();M!=NULL;M=M->GetNext()){
					if(M->MachineID==e->MachineID){
						break;
					}
				}
				if(M==NULL){
					M=new MapListByMaster();
					M->MachineID=e->MachineID;
					M->Master=LBase->FindMaster(M->MachineID);
					MapList.AppendList(M);
				}
				
				for(InspectionList *ins=e->NPListPack<InspectionList>::GetFirst();ins!=NULL;ins=ins->GetNext()){
					QDateTime	tm=ins->InspectionTime.GetQDateTime();
					if(StartTime<=tm && tm<=EndTime){
						for(NGPointInAllPage *ph=ins->NGPointAllPhases.GetFirst();ph!=NULL;ph=ph->GetNext()){
							for(NGPointInPage *pg=ph->NPListPack<NGPointInPage>::GetFirst();pg!=NULL;pg=pg->GetNext()){
								for(NGPoint *p=pg->NPListPack<NGPoint>::GetFirst();p!=NULL;p=p->GetNext()){
									if(CheckByLib(p)==true){
										XYData	*xy=M->Master->GetOutlineOffset(ph->Phase, pg->Page);
										int	cx,cy;
										p->GetMasterCenter(cx, cy);
										M->Add(cx+xy->x,cy+xy->y);
									}
								}
							}
						}
					}
				}
			}
		}
	}
}

void NGMapForm::on_pushButtonView_clicked()
{
	if(MapResult==NULL){
		MapResult=new MapForm(this);
	}
	MapResult->show();
}

bool	NGMapForm::CheckByLib(NGPoint *NG)
{
	return true;
}

