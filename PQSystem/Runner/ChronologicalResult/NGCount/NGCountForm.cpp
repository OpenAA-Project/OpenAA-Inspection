#include "NGCountForm.h"
#include "ui_NGCountForm.h"
#include "SelectRelationalMasterDataDialog.h"
#include "XGeneralFunc.h"
#include "XDatabaseLoader.h"
#include "ChronologicalGraphForm.h"
#include "SelectAreaForm.h"

int SortFuncNGResultList(const NGResultList **a,const NGResultList **b)
{
	if((*a)->RelationCode<(*b)->RelationCode)
		return -1;
	if((*a)->RelationCode>(*b)->RelationCode)
		return 1;

	if((*a)->InspectionID<(*b)->InspectionID)
		return -1;
	if((*a)->InspectionID>(*b)->InspectionID)
		return 1;
	return 0;
}

NGCountForm::NGCountForm(LayersBase *base ,const QString &root ,const QString &name
						 ,QWidget *parent) :
	PQSystemRunner(base ,root ,name,parent)
	,LotForm(base)
    ,ui(new Ui::NGCountForm)
{
    ui->setupUi(this);
	ResultRelationCode	=-1;
	Graph				=NULL;

	ui->dateTimeEditStart	->setDateTime(QDateTime::currentDateTime());
	ui->dateTimeEditEnd		->setDateTime(QDateTime::currentDateTime());

	LotForm.setParent(ui->frameSelectLot);
	LotForm.setGeometry(0,0,ui->frameSelectLot->width(),ui->frameSelectLot->height());
}

NGCountForm::~NGCountForm()
{
    delete ui;
	delete	Graph;
}
bool	NGCountForm::Initial(void)
{
	return true;
}
const QString	NGCountForm::GetPath(void)
{
	return "検査結果時系列表示/NG個数グラフ表示";
}

void NGCountForm::showEvent(QShowEvent *event)
{
	ResultRelationCode	=-1;
	ui->lineEditMasterID	->setText("");
	ui->lineEditMasterName	->setText("非選択で全マスターが対象");
}

void NGCountForm::on_pushButtonSelectMaster_clicked()
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
			ui->pushButtonSelectArea->setEnabled(true);
			LotForm.Update();
		}
	}
}

void NGCountForm::on_pushButtonStartSearch_clicked()
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
	ResultList.RemoveAll();
	IntegrationBase	*LBase=GetLayersBase()->GetIntegrationBasePointer();
	for(LotListContainerWithRelationCode *L=AllLotList.GetFirst();L!=NULL;L=L->GetNext()){
		for(LotListWithResult *h=L->Container.GetFirst();h!=NULL;h=h->GetNext()){
			ui->progressBar->setValue(ui->progressBar->value()+1);
			h->LoadResult(LBase);
			NPListPack<NGResultList>	TmpResultList;
			for(InspectionListByMaster *e=h->CurrentInspection.GetFirst();e!=NULL;e=e->GetNext()){
				for(InspectionList *ins=e->NPListPack<InspectionList>::GetFirst();ins!=NULL;ins=ins->GetNext()){
					QDateTime	tm=ins->InspectionTime.GetQDateTime();
					if(StartTime<=tm && tm<=EndTime){
						bool	Necessary=false;
						for(NGPointInAllPage *ph=ins->NGPointAllPhases.GetFirst();ph!=NULL;ph=ph->GetNext()){
							for(NGPointInPage *pg=ph->NPListPack<NGPointInPage>::GetFirst();pg!=NULL;pg=pg->GetNext()){
								for(NGPoint *p=pg->NPListPack<NGPoint>::GetFirst();p!=NULL;p=p->GetNext()){
									if(CheckByLib(p)==true){
										Necessary=true;
										goto FoundNG;
									}
								}
							}
						}
					FoundNG:;
						if(Necessary==true){
							NGResultList *t;
							for(t=TmpResultList.GetFirst();t!=NULL;t=t->GetNext()){
								if(t->InspectionID==ins->ID
								&& t->RelationCode==L->RelationCode){
									break;
								}
							}
							if(t==NULL){
								NGResultList	*NGList=new NGResultList();
								NGList->InspectionTime	=ins->InspectionTime;
								NGList->InspectionID	=ins->ID;
								NGList->LotPointer		=h;
								NGList->RelationCode	=L->RelationCode;
								TmpResultList.AppendList(NGList);
							}
						}
					}
				}
			}
			TmpResultList.Sort(SortFuncNGResultList);
			ResultList.AddMove(TmpResultList);
		}
	}
	ResultList.Sort(SortFuncNGResultList);
}

void NGCountForm::on_pushButtonView_clicked()
{
	if(Graph==NULL){
		Graph=new ChronologicalGraphForm(this);
	}
	Graph->show();
}

void NGCountForm::on_pushButtonExcel_clicked()
{

}

void NGCountForm::on_pushButtonSelectArea_clicked()
{
	SelectAreaForm	D(this);
	D.SelectArea=SelectArea;
	if(D.exec()==true){
		SelectArea=D.SelectArea;
	}
}

bool	NGCountForm::CheckByLib(NGPoint *NG)
{
	return true;
}
