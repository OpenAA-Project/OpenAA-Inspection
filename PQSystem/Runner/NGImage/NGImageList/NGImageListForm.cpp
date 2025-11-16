#include "NGImageListResource.h"
#include "NGImageListForm.h"
#include "ui_NGImageListForm.h"
#include "NGImageDialog.h"
#include "SelectRelationalMasterDataDialog.h"
#include "XGeneralFunc.h"
#include "XDatabaseLoader.h"

NGImageListForm::NGImageListForm(LayersBase *base ,const QString &root ,const QString &name
								,QWidget *parent) :
    PQSystemRunner(base ,root ,name,parent)
	,LotForm(base)
    ,ui(new Ui::NGImageListForm)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);

	ResultRelationCode	=-1;
	CurrentAlgorithm	=NULL;
	CurrentLibrary		=NULL;

	ui->dateTimeEditStart	->setDateTime(QDateTime::currentDateTime());
	ui->dateTimeEditEnd		->setDateTime(QDateTime::currentDateTime());

	::SetColumnWidthInTable(ui->tableWidgetLibrary,0, 25);
	::SetColumnWidthInTable(ui->tableWidgetLibrary,1, 75);

	LotForm.setParent(ui->frameSelectLot);
	LotForm.setGeometry(0,0,ui->frameSelectLot->width(),ui->frameSelectLot->height());
	//TestPanel.setParent(ui->frame);

	ReferredExcelFileName=/**/"D:\\Data\\YamashitaData\\ひな型.xlsx";

	GetParamGUI()->SetParam(&ReferredExcelFileName, /**/"NGImageList",/**/"ReferredExcelFileName"	
												,LangSolver.GetString(NGImageListForm_LS,LID_0)/*"Referred Excel file name"*/		);

}

NGImageListForm::~NGImageListForm()
{
    delete ui;
}
bool	NGImageListForm::Initial(void)
{
	return true;
}
const QString	NGImageListForm::GetPath(void)
{
	return LangSolver.GetString(NGImageListForm_LS,LID_1)/*"NG画像表示/ＮＧ画像リスト"*/;
}

void NGImageListForm::showEvent(QShowEvent *event)
{
	ResultRelationCode	=-1;
	CurrentAlgorithm	=NULL;
	CurrentLibrary		=NULL;

	ui->lineEditMasterID	->setText(LangSolver.GetString(NGImageListForm_LS,LID_2)/*""*/);
	ui->lineEditMasterName	->setText(LangSolver.GetString(NGImageListForm_LS,LID_3)/*"非選択で全マスターが対象"*/);

	GetAllAlgorithmPointers(AlgorithmContainer);
	ui->listWidgetAlgorithm->clear();
	for(AlgorithmBasePointerList *a=AlgorithmContainer.GetFirst();a!=NULL;a=a->GetNext()){
		ui->listWidgetAlgorithm->addItem(a->GetAlgorithmBase()->GetExplain());
	}
	ui->tableWidgetLibrary->setRowCount(0);
	ui->listWidgetSpecial	->clear();
	ui->listWidgetThreshold	->clear();
}

void NGImageListForm::on_pushButtonSelectMaster_clicked()
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
			ui->lineEditMasterID	->setText(QString::number(ResultRelationCode));
			ui->lineEditMasterName	->setText(RetRelationName);

			LotForm.Update();
		}
	}
}

void NGImageListForm::on_pushButtonStartSearch_clicked()
{
	StartTime	=ui->dateTimeEditStart	->dateTime();
	EndTime		=ui->dateTimeEditEnd	->dateTime();

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
			h->Effective=false;
			ui->progressBar->setValue(ui->progressBar->value()+1);
			h->LoadResult(LBase);
			for(InspectionListByMaster *e=h->CurrentInspection.GetFirst();e!=NULL;e=e->GetNext()){
				for(InspectionList *ins=e->NPListPack<InspectionList>::GetFirst();ins!=NULL;ins=ins->GetNext()){
					QDateTime	tm=ins->InspectionTime.GetQDateTime();
					if(StartTime<=tm && tm<=EndTime){
						h->Effective=true;
						NGListByMaster	*NG=NULL;
						for(NGPointInAllPage *ph=ins->NGPointAllPhases.GetFirst();ph!=NULL;ph=ph->GetNext()){
							for(NGPointInPage *pg=ph->NPListPack<NGPointInPage>::GetFirst();pg!=NULL;pg=pg->GetNext()){
								if(pg->ImageFileName.isEmpty()==false){
									QString	ImageFileName=LBase->ReplaceImageFile(pg->ImageFileName,e->MachineID);
									
									NPListPack<IntegNGImage> NGImages[1000];
									if(ImageFileName.isEmpty()==false){
										LoadNGImageFile(ImageFileName,NGImages,1000);
									}
									IntegNGImage	*G;
									while((G=NGImages[ph->Phase].GetFirst())!=NULL){
										NGImages[ph->Phase].RemoveList(G);
										pg->NGImages.AppendList(G);
									}
									pg->UncompressImages();

									for(IntegNGImage *g=pg->NGImages.GetFirst();g!=NULL;g=g->GetNext()){
										NPListPack<NGPointPointerList> NGList;
										g->EnumNGPoint(pg,NGList);
										bool	Necessary=false;
										for(NGPointPointerList *p=NGList.GetFirst();p!=NULL;p=p->GetNext()){
											if(CheckByLib(p->NG)==true){
												Necessary=true;
												break;
											}
										}
										if(Necessary==true){
											if(NG==NULL){
												NG=new NGListByMaster();
												NG->MachineID=e->MachineID;
											}
											NG->NGImages.AppendList(g);
										}
									}
								}
							}
						}
						if(NG!=NULL){
							NGListWithImages *t;
							for(t=ResultList.GetFirst();t!=NULL;t=t->GetNext()){
								if(t->RelationCode==L->RelationCode
								&& t->InspectionID==ins->ID){
									break;
								}
							}
							if(t!=NULL){
								t->NGImageBYMaster.AppendList(NG);
							}
							else{
								NGListWithImages	*NGList=new NGListWithImages();
								NGList->InspectionTime	=ins->InspectionTime;
								NGList->InspectionID	=ins->ID;
								NGList->LotPointer		=h;
								NGList->RelationCode	=L->RelationCode;
								NGList->NGImageBYMaster.AppendList(NG);
								ResultList.AppendList(NGList);
							}
						}
					}
				}							
			}
		}
	}
}

void NGImageListForm::on_pushButtonView_clicked()
{
	NGImageDialog	D(this);
	D.exec();
}

void NGImageListForm::on_pushButtonExcel_clicked()
{
	//TestPanel.setGeometry(0,0,ui->frame->width(),ui->frame->height());
	//QImage	Img;
	//Img.load("C:\\image\\images.png");
	//TestPanel.Add(Img);
	//TestPanel.Add(Img);
	//TestPanel.Add(Img);
	//TestPanel.Add(Img);
	//TestPanel.Add(Img);
	//TestPanel.Add(Img);
	//TestPanel.Add(Img);
	//TestPanel.Add(Img);
	//TestPanel.Add(Img);
	//TestPanel.Add(Img);
	//TestPanel.Assign();
	QString	ExcelFileName=QFileDialog::getSaveFileName(nullptr
													   , LangSolver.GetString(NGImageListForm_LS,LID_4)/*"Save EXCEL file"*/
													   , QString()
													   , LangSolver.GetString(NGImageListForm_LS,LID_5)/*"EXCEL file(*.xlsx);;all files(*.*)"*/);
	if(ExcelFileName.isEmpty()==false){
		WriteExcel(ExcelFileName);
	}
}


void NGImageListForm::on_listWidgetAlgorithm_clicked(const QModelIndex &index)
{
	int	Row=ui->listWidgetAlgorithm->currentRow();
	if(Row>=0){
		AlgorithmBasePointerList *a=AlgorithmContainer[Row];
		if(a!=NULL){
			CurrentAlgorithm=a->GetAlgorithmBase();
			AlgorithmLibraryContainer	*LibC=CurrentAlgorithm->GetLibraryContainer();
			if(LibC!=NULL){
				LibC->EnumLibrary(LibIDList);
				ui->tableWidgetLibrary->setRowCount(LibIDList.GetCount());
				int	ARow=0;
				for(AlgorithmLibraryList *L=LibIDList.GetFirst();L!=NULL;L=L->GetNext(),ARow++){
					::SetDataToTable(ui->tableWidgetLibrary,0,ARow,QString::number(L->GetLibID()));
					::SetDataToTable(ui->tableWidgetLibrary,1,ARow,L->GetLibName());
				}
				return;
			}
		}
	}
	ui->tableWidgetLibrary->setRowCount(0);
}

void NGImageListForm::on_tableWidgetLibrary_clicked(const QModelIndex &index)
{
	int	Row=ui->tableWidgetLibrary->currentRow();
	if(Row>=0){
		CurrentLibrary=LibIDList[Row];
		if(CurrentLibrary!=NULL){
		}
	}
}

void NGImageListForm::on_listWidgetThreshold_clicked(const QModelIndex &index)
{

}

void NGImageListForm::on_listWidgetSpecial_clicked(const QModelIndex &index)
{

}

bool	NGImageListForm::CheckByLib(NGPoint *NG)
{
	if(CurrentAlgorithm==NULL || CurrentLibrary==NULL){
		return true;
	}
	if(CurrentAlgorithm->GetLibType()==NG->LibType
	&& CurrentLibrary->GetLibID()==NG->LibID){
		return true;
	}
	return false;
}
