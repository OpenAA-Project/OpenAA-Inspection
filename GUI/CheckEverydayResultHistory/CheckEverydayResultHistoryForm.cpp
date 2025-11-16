#include "CheckEverydayResultHistoryResource.h"
#include "CheckEverydayResultHistoryForm.h"
#include "ui_CheckEverydayResultHistoryForm.h"
#include "XCheckEveryday.h"
#include "XGUIFormBase.h"
#include "XCheckEverydayGUIPacket.h"
#include "XCheckEverydayCommon.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

CheckEverydayResultHistoryForm::CheckEverydayResultHistoryForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::CheckEverydayResultHistoryForm)
{
    ui->setupUi(this);
}

CheckEverydayResultHistoryForm::~CheckEverydayResultHistoryForm()
{
    delete ui;
}


static	int	SortLightInfoFunc(const void *a , const void *b)
{
	CheckEverydayLightInfo	**aa=(CheckEverydayLightInfo **)a;
	CheckEverydayLightInfo	**bb=(CheckEverydayLightInfo **)b;
	if(aa[0]->Page<bb[0]->Page)
		return 1;
	if(aa[0]->Page>bb[0]->Page)
		return -1;
	if(aa[0]->Layer<bb[0]->Layer)
		return 1;
	if(aa[0]->Layer>bb[0]->Layer)
		return -1;
	if(aa[0]->ID<bb[0]->ID)
		return 1;
	if(aa[0]->ID>bb[0]->ID)
		return -1;
	return 0;
}


static	int	SortFocusInfoFunc(const void *a , const void *b)
{
	CheckEverydayFocusInfo	**aa=(CheckEverydayFocusInfo **)a;
	CheckEverydayFocusInfo	**bb=(CheckEverydayFocusInfo **)b;
	if(aa[0]->Page<bb[0]->Page)
		return 1;
	if(aa[0]->Page>bb[0]->Page)
		return -1;
	if(aa[0]->Layer<bb[0]->Layer)
		return 1;
	if(aa[0]->Layer>bb[0]->Layer)
		return -1;
	if(aa[0]->ID<bb[0]->ID)
		return 1;
	if(aa[0]->ID>bb[0]->ID)
		return -1;
	return 0;
}
	
void	CheckEverydayResultHistoryForm::BuildForShow(void)
{
	CheckEverydayLightInfoContainer	TmpInfoLight;
	CheckEverydayFocusInfoContainer	TmpInfoFocus;

	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdReqInfo	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		GUICmdAckInfo	ACmd(GetLayersBase(),sRoot,sName,GlobalPage);
		if(RCmd.Send(GlobalPage,0,ACmd)==true){
			TmpInfoLight+=ACmd.InfoLight;
			TmpInfoFocus+=ACmd.InfoFocus;
		}
	}
	CheckEverydayLightInfo	**LTmp=new CheckEverydayLightInfo*[TmpInfoLight.GetNumber()];
	CheckEverydayFocusInfo	**FTmp=new CheckEverydayFocusInfo*[TmpInfoFocus.GetNumber()];

	int	LRow=0;
	for(CheckEverydayLightInfo *L=TmpInfoLight.GetFirst();L!=NULL;){
		CheckEverydayLightInfo *LNext=L->GetNext();
		LTmp[LRow]=L;
		LRow++;
		TmpInfoLight.RemoveList(L);
		L=LNext;
	}
	int	FRow=0;
	for(CheckEverydayFocusInfo *F=TmpInfoFocus.GetFirst();F!=NULL;){
		CheckEverydayFocusInfo *FNext=F->GetNext();
		FTmp[FRow]=F;
		FRow++;
		TmpInfoFocus.RemoveList(F);
		F=FNext;
	}
	QSort(LTmp,LRow,sizeof(CheckEverydayLightInfo *),SortLightInfoFunc);
	QSort(FTmp,FRow,sizeof(CheckEverydayFocusInfo *),SortFocusInfoFunc);

	ui->tableWidgetItemList->setRowCount(LRow+FRow);
	int	row=0;
	for(row=0;row<LRow;row++){
		::SetDataToTable(ui->tableWidgetItemList ,0,row ,QString::number(LTmp[row]->Page));
		::SetDataToTable(ui->tableWidgetItemList ,1,row ,QString::number(LTmp[row]->Layer));
		::SetDataToTable(ui->tableWidgetItemList ,2,row ,LangSolver.GetString(CheckEverydayResultHistoryForm_LS,LID_0)/*"Light"*/);
		if(LTmp[row]->ItemName.isEmpty()==true)
			::SetDataToTable(ui->tableWidgetItemList ,3,row ,QString::number(LTmp[row]->ID));
		else
			::SetDataToTable(ui->tableWidgetItemList ,3,row ,QString::number(LTmp[row]->ID) + QString(/**/" / ")+LTmp[row]->ItemName);

		TmpInfoLight.AppendList(LTmp[row]);
	}
	for(;row<FRow;row++){
		::SetDataToTable(ui->tableWidgetItemList ,0,row ,QString::number(FTmp[row]->Page));
		::SetDataToTable(ui->tableWidgetItemList ,1,row ,QString::number(FTmp[row]->Layer));
		::SetDataToTable(ui->tableWidgetItemList ,2,row ,LangSolver.GetString(CheckEverydayResultHistoryForm_LS,LID_1)/*"Focus"*/);
		if(FTmp[row]->ItemName.isEmpty()==true)
			::SetDataToTable(ui->tableWidgetItemList ,3,row ,QString::number(FTmp[row]->ID));
		else
			::SetDataToTable(ui->tableWidgetItemList ,3,row ,QString::number(FTmp[row]->ID) + QString(/**/" / ")+FTmp[row]->ItemName);

		TmpInfoFocus.AppendList(FTmp[row]);
	}
	delete	[]LTmp;
	delete	[]FTmp;

	InfoLight=TmpInfoLight;
	InfoFocus=TmpInfoFocus;

	HistoryList.RemoveAll();
}
void	CheckEverydayResultHistoryForm::ShowInPlayer(int64 shownInspectionID)
{
	if(InfoLight.GetCount()+InfoFocus.IsEmpty()==false){
		XDateTime	CurrentTime=XDateTime::currentDateTime();

		for(int page=0;page<GetPageNumb();page++){
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdReqInfo	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
			GUICmdAckInfo	ACmd(GetLayersBase(),sRoot,sName,GlobalPage);
			if(RCmd.Send(GlobalPage,0,ACmd)==true){
				for(CheckEverydayLightInfo *L=ACmd.InfoLight.GetFirst();L!=NULL;L=L->GetNext()){
					HistoryListOfCheckEveryday *a;
					for(a=HistoryList.GetFirst();a!=NULL;a=a->GetNext()){
						if(a->Page==L->Page && a->Layer==L->Layer && a->ID==L->ID){
							break;
						}
					}
					if(a==NULL){
						a=new HistoryListOfCheckEveryday(this);
						a->Page		=L->Page;
						a->Layer	=L->Layer;
						a->ID		=L->ID;
						HistoryList.AppendList(a);
					}
					ResultListOfCheckEveryday	*r=new ResultListOfCheckEveryday();
					r->CurrentValue	=L->CurrentValue;
					r->Result		=L->Result;
					r->InspectionID	=shownInspectionID;
					a->ResultContainer.AppendList(r);
				}
				for(CheckEverydayFocusInfo *F=ACmd.InfoFocus.GetFirst();F!=NULL;F=F->GetNext()){
					HistoryListOfCheckEveryday *a;
					for(a=HistoryList.GetFirst();a!=NULL;a=a->GetNext()){
						if(a->Page==F->Page && a->Layer==F->Layer && a->ID==F->ID){
							break;
						}
					}
					if(a==NULL){
						a=new HistoryListOfCheckEveryday(this);
						a->Page		=F->Page;
						a->Layer	=F->Layer;
						a->ID		=F->ID;
						HistoryList.AppendList(a);
					}
					ResultListOfCheckEveryday	*r=new ResultListOfCheckEveryday();
					r->CurrentValue	=F->CurrentValue;
					r->Result		=F->Result;
					r->InspectionID	=shownInspectionID;
					a->ResultContainer.AppendList(r);
				}
			}
		}
	}
}

void CheckEverydayResultHistoryForm::on_pushButtonSaveButton_clicked()
{
	QString	FileName=QFileDialog::getSaveFileName( 0
												, LangSolver.GetString(CheckEverydayResultHistoryForm_LS,LID_2)/*"Save CheckEveryday result"*/
												, QString()
												, QString(/**/"*.txt(*.txt);;All files(*.*)"));
	if(FileName.isEmpty()==false){
		QFile	File(FileName);
		if(File.open(QIODevice::WriteOnly)==true){
			QTextStream	Txt(&File);
			for(HistoryListOfCheckEveryday *h=HistoryList.GetFirst();h!=NULL;h=h->GetNext()){
				h->SaveText(Txt);
			}
		}
	}
}

HistoryListOfCheckEveryday	*CheckEverydayResultHistoryForm::SearchHistory(int page ,int layer ,int id)
{
	for(HistoryListOfCheckEveryday *h=HistoryList.GetFirst();h!=NULL;h=h->GetNext()){
		if(h->Page==page && h->Layer==layer && h->ID==id)
			return h;
	}
	return NULL;
}

void CheckEverydayResultHistoryForm::on_tableWidgetItemList_clicked(const QModelIndex &index)
{
	int	Row=ui->tableWidgetItemList->currentRow();
	if(Row<0)
		return;
	int	row=0;
	HistoryListOfCheckEveryday	*a=NULL;
	for(CheckEverydayLightInfo *L=InfoLight.GetFirst();L!=NULL;L=L->GetNext(),row++){
		if(Row==row){
			a=SearchHistory(L->Page,L->Layer ,L->ID);
			break;
		}
	}
	if(a==NULL){
		for(CheckEverydayFocusInfo *F=InfoFocus.GetFirst();F!=NULL;F=F->GetNext(),row++){
			if(Row==row){
				a=SearchHistory(F->Page,F->Layer ,F->ID);
				break;
			}
		}
	}
	if(a!=NULL){
		int	N=a->ResultContainer.GetCount();
		ui->tableWidgetHistoryList	->setRowCount(N);
		int	MRow=0;
		for(ResultListOfCheckEveryday *k=a->ResultContainer.GetFirst();k!=NULL;k=k->GetNext(),MRow++){
			::SetDataToTable(ui->tableWidgetHistoryList ,0,MRow ,QString::number(k->InspectionID));
			::SetDataToTable(ui->tableWidgetHistoryList ,1,MRow ,QString::number(k->CurrentValue));
		}
	}
}
QString	CheckEverydayResultHistoryForm::SearchItemName(int page ,int layer ,int id)
{
	for(CheckEverydayLightInfo *L=InfoLight.GetFirst();L!=NULL;L=L->GetNext()){
		if(L->Page==page && L->Layer==layer && L->ID==id)
			return L->ItemName;
	}
	for(CheckEverydayFocusInfo *F=InfoFocus.GetFirst();F!=NULL;F=F->GetNext()){
		if(F->Page==page && F->Layer==layer && F->ID==id)
			return F->ItemName;
	}
	return /**/"";
}

//===========================================================================================
bool	ResultListOfCheckEveryday::SaveText(QTextStream &f)
{
	f<<QString::number(InspectionID) << QString(/**/"\t\t") << QString::number(CurrentValue)<<QString(/**/"\r\n");
	return true;
}

bool	HistoryListOfCheckEveryday::SaveText(QTextStream &f)
{
	f<<QString(/**/"Page=")<<QString::number(Page)<<QString(/**/"\r\n");
	f<<QString(/**/"Layer=")<<QString::number(Page)<<QString(/**/"\r\n");
	f<<QString(/**/"ID/Name=")<<QString::number(ID);
	QString	ItemName=Parent->SearchItemName(Page ,Layer ,ID);
	if(ItemName.isEmpty()==false){
		f<<::GetSeparator()+ItemName;
	}
	f<<QString(/**/"\r\n");

	for(ResultListOfCheckEveryday *r=ResultContainer.GetFirst();r!=NULL;r=r->GetNext()){
		if(r->SaveText(f)==false)
			return false;
	}
	f<<QString(/**/"\r\n");
	f<<QString(/**/"\r\n");
	f<<QString(/**/"\r\n");
	return true;
}

