#include "ShowCheckEverydayFormResource.h"
#include "ShowCheckEverydayForm.h"
#include "ui_ShowCheckEverydayForm.h"
#include "XCheckEveryday.h"
#include "XDataInLayer.h"
#include "XCheckEverydayGUIPacket.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

ShowCheckEverydayForm::ShowCheckEverydayForm(LayersBase *Base ,QWidget *parent) :
     GUIFormBase(Base,parent),
    ui(new Ui::ShowCheckEverydayForm)
{
    ui->setupUi(this);
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
	UpdateInEveryInspection=false;
}

ShowCheckEverydayForm::~ShowCheckEverydayForm()
{
    delete ui;
}
CheckEverydayBase	*ShowCheckEverydayForm::GetCheckEverydayBase(void)
{
	return (CheckEverydayBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"CheckEveryday");
}
void	ShowCheckEverydayForm::Prepare(void)
{
	ResizeAction();
}

void	ShowCheckEverydayForm::TransmitDirectly(GUIDirectMessage *packet)
{
}

void	ShowCheckEverydayForm::ResizeAction()
{
	ui->tableWidget->resize(width(),height()-ui->frameTop->height());
	ui->frameTop->resize(width(),ui->frameTop->height());
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


void ShowCheckEverydayForm::on_pushButtonUpdate_clicked()
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
	for(CheckEverydayLightInfo *L=TmpInfoLight.GetFirst();L!=NULL;L=L->GetNext()){
		LTmp[LRow]=L;
		LRow++;
	}
	int	FRow=0;
	for(CheckEverydayFocusInfo *F=TmpInfoFocus.GetFirst();F!=NULL;F=F->GetNext()){
		FTmp[FRow]=F;
		FRow++;
	}
	QSort(LTmp,LRow,sizeof(CheckEverydayLightInfo *),SortLightInfoFunc);
	QSort(FTmp,FRow,sizeof(CheckEverydayFocusInfo *),SortFocusInfoFunc);

	int	ColNum=0;
	for(int page=0;page<GetPageNumb();page++){
		int	ColInPage=0;
		for(int Layer=0;Layer<GetLayerNumb(page);Layer++){
			int	LCounter=0;
			for(int row=0;row<LRow;row++){
				if(LTmp[row]->Page==page && LTmp[row]->Layer==Layer){
					LCounter++;
				}
			}
			if(ColInPage<LCounter){
				ColInPage=LCounter;
			}
			LCounter=0;
			for(int row=0;row<FRow;row++){
				if(FTmp[row]->Page==page && FTmp[row]->Layer==Layer){
					LCounter++;
				}
			}
			if(ColInPage<LCounter){
				ColInPage=LCounter;
			}
		}
		ColNum+=ColInPage;
	}
	if(ColNum>0){
		ui->tableWidget->setColumnCount(ColNum);
		QStringList	Labels;
		for(int i=0;i<ColNum;i++){
			ui->tableWidget->setColumnWidth(i,(ui->tableWidget->width()-50)/ColNum);
			Labels.append(QString::number(i));
		}
		ui->tableWidget->setHorizontalHeaderLabels(Labels);
	}

	int	Col=0;
	for(int page=0;page<GetPageNumb();page++){
		int	ColInPage=0;
		for(int Layer=0;Layer<GetLayerNumb(page);Layer++){
			int	LCounter=0;
			for(int row=0;row<LRow;row++){
				if(LTmp[row]->Page==page && LTmp[row]->Layer==Layer){
					LCounter++;
				}
			}
			if(ColInPage<LCounter){
				ColInPage=LCounter;
			}
			LCounter=0;
			for(int row=0;row<FRow;row++){
				if(FTmp[row]->Page==page && FTmp[row]->Layer==Layer){
					LCounter++;
				}
			}
			if(ColInPage<LCounter){
				ColInPage=LCounter;
			}
		}
		for(int c=0;c<ColInPage;c++){
			::SetDataToTable(ui->tableWidget ,Col+c,0,QString::number(page));
		}
		for(int Layer=0;Layer<GetLayerNumb(page);Layer++){
			int	LCounter=0;
			for(int row=0;row<LRow;row++){
				if(LTmp[row]->Page==page && LTmp[row]->Layer==Layer){
					if(LTmp[row]->Result==true){
						::SetDataToTable(ui->tableWidget ,Col+LCounter,1+Layer ,LangSolver.GetString(ShowCheckEverydayForm_LS,LID_0)/*"OK :"*/+QString::number(LTmp[row]->CurrentValue));
					}
					else{
						::SetDataToTable(ui->tableWidget ,Col+LCounter,1+Layer ,LangSolver.GetString(ShowCheckEverydayForm_LS,LID_1)/*"NG :"*/+QString::number(LTmp[row]->CurrentValue));
					}
					LCounter++;
				}
			}
			LCounter=0;
			for(int row=0;row<FRow;row++){
				if(FTmp[row]->Page==page && FTmp[row]->Layer==Layer
				&& FTmp[row]->CurrentValue>0){
					if(FTmp[row]->Result==true){
						::SetDataToTable(ui->tableWidget ,Col+LCounter,4 ,LangSolver.GetString(ShowCheckEverydayForm_LS,LID_2)/*"OK :"*/+QString::number(FTmp[row]->CurrentValue));
					}
					else{
						::SetDataToTable(ui->tableWidget ,Col+LCounter,4 ,LangSolver.GetString(ShowCheckEverydayForm_LS,LID_3)/*"NG :"*/+QString::number(FTmp[row]->CurrentValue));
					}
					LCounter++;
				}
			}
		}
		Col+=ColInPage;
	}
	delete	[]LTmp;
	delete	[]FTmp;
}
void	ShowCheckEverydayForm::ShowInPlayer		(int64 shownInspectionID)
{
	if(UpdateInEveryInspection==true){
		on_pushButtonUpdate_clicked();
	}
}
