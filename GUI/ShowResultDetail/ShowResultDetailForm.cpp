#include "ShowResultDetailForm.h"
#include "ui_ShowResultDetailForm.h"
#include "XGeneralFunc.h"
#include "XLotInformation.h"
#include "XCSV.h"
/*
* Keyword
*   %i                  検査番号
*   %m                  マスター番号
*   %c                  装置番号
*   %t[yyMMddhhmmss]    日時  []内は日時フォーマット
*   %l                  ロット番号
*/
extern	const	char	*sRoot;
extern	const	char	*sName;
//============================================================================

ResultDetailList::ResultDetailList(const ResultDetailList &src)
{
    Phase   =src.Phase   ;
    Page    =src.Page    ;
    Layer   =src.Layer   ;
    ItemID  =src.ItemID  ;
    LibType =src.LibType ;
    LibID   =src.LibID   ;
    PosX    =src.PosX    ;
    PosY    =src.PosY    ;
    Message =src.Message ;
    Res1    =src.Res1    ;
    Res2    =src.Res2    ;
    Res3    =src.Res3    ;
}
    
ResultDetailList    &ResultDetailList::operator=(const ResultDetailList &src)
{
    Phase   =src.Phase   ;
    Page    =src.Page    ;
    Layer   =src.Layer   ;
    ItemID  =src.ItemID  ;
    LibType =src.LibType ;
    LibID   =src.LibID   ;
    PosX    =src.PosX    ;
    PosY    =src.PosY    ;
    Message =src.Message ;
    Res1    =src.Res1    ;
    Res2    =src.Res2    ;
    Res3    =src.Res3    ;
    return *this;
}
	
bool	ResultDetailList::Save(QIODevice *f)
{
    if(::Save(f,Phase   )==false)   return false;
    if(::Save(f,Page    )==false)   return false;
    if(::Save(f,Layer   )==false)   return false;
    if(::Save(f,ItemID  )==false)   return false;
    if(::Save(f,LibType )==false)   return false;
    if(::Save(f,LibID   )==false)   return false;
    if(::Save(f,PosX    )==false)   return false;
    if(::Save(f,PosY    )==false)   return false;
    if(::Save(f,Message )==false)   return false;
    if(::Save(f,Res1    )==false)   return false;
    if(::Save(f,Res2    )==false)   return false;
    if(::Save(f,Res3    )==false)   return false;
    return true;
}
bool	ResultDetailList::Load(QIODevice *f)
{
    if(::Load(f,Phase   )==false)   return false;
    if(::Load(f,Page    )==false)   return false;
    if(::Load(f,Layer   )==false)   return false;
    if(::Load(f,ItemID  )==false)   return false;
    if(::Load(f,LibType )==false)   return false;
    if(::Load(f,LibID   )==false)   return false;
    if(::Load(f,PosX    )==false)   return false;
    if(::Load(f,PosY    )==false)   return false;
    if(::Load(f,Message )==false)   return false;
    if(::Load(f,Res1    )==false)   return false;
    if(::Load(f,Res2    )==false)   return false;
    if(::Load(f,Res3    )==false)   return false;
    return true;
}
    
ResultDetailListContainer::ResultDetailListContainer(const ResultDetailListContainer &src)
{
    for(ResultDetailList *s=src.GetFirst();s!=NULL;s=s->GetNext()){
        ResultDetailList *d=new ResultDetailList(*s);
        AppendList(d);
    }
}

ResultDetailList	*ResultDetailListContainer::Create(void)
{
    return new ResultDetailList();
}

ResultDetailListContainer   &ResultDetailListContainer::operator=(const ResultDetailListContainer &src)
{
    RemoveAll();
    for(ResultDetailList *s=src.GetFirst();s!=NULL;s=s->GetNext()){
        ResultDetailList *d=new ResultDetailList(*s);
        AppendList(d);
    }
    return *this;
}
ResultDetailListContainer   &ResultDetailListContainer::operator+=(const ResultDetailListContainer &src)
{
    for(ResultDetailList *s=src.GetFirst();s!=NULL;s=s->GetNext()){
        ResultDetailList *d=new ResultDetailList(*s);
        AppendList(d);
    }
    return *this;
}

//============================================================================

ShowResultDetailForm::ShowResultDetailForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::ShowResultDetailForm)
{
    ui->setupUi(this);
    AutoWrite=true;
    FileName=/**/"c:/Result/Inspection/%t[yyMM]/%t[MMdd]/%t[yyyyMMdd_hhmmss].csv";
    connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ShowResultDetailForm::~ShowResultDetailForm()
{
    delete ui;
}
void	ShowResultDetailForm::ResizeAction()
{
    ui->tableWidget->resize(width(),height()-ui->pushButtonWriteResult->height());
    int L=(width()-ui->pushButtonWriteResult->width())/2;
    ui->pushButtonWriteResult->move(L,height()-ui->pushButtonWriteResult->height());

    ::SetColumnWidthInTable(ui->tableWidget ,0, 5);
    ::SetColumnWidthInTable(ui->tableWidget ,1, 5);
    ::SetColumnWidthInTable(ui->tableWidget ,2, 5);
    ::SetColumnWidthInTable(ui->tableWidget ,3, 6);
    ::SetColumnWidthInTable(ui->tableWidget ,4, 5);
    ::SetColumnWidthInTable(ui->tableWidget ,5, 15);
    ::SetColumnWidthInTable(ui->tableWidget ,6, 20);
    ::SetColumnWidthInTable(ui->tableWidget ,7, 13);
    ::SetColumnWidthInTable(ui->tableWidget ,8, 13);
    ::SetColumnWidthInTable(ui->tableWidget ,9, 13);
}
QString ShowResultDetailForm::MakePathFile(void)
{
    QString F1=FileName .replace(/**/"%i",QString::number(GetLayersBase()->GetInspectionNumber()));
    QString F2=F1       .replace(/**/"%m",QString::number(GetLayersBase()->GetMasterCode()));
            F2=F2       .replace(/**/"%c",QString::number(GetLayersBase()->GetMachineID()));
    QDateTime   t=QDateTime::currentDateTime();

    for(;;){
        int n=F2.indexOf("%t");
        if(n<0){
            break;
        }
        QString F3;
        F3=F2.mid(0,n);
        int n1=F2.indexOf("[");
        int n2=F2.indexOf("]");
        if(n1<0 || n2<0 || n1>=n2){
            break;
        }
        QString DTFormat=F2.mid(n1+1,n2-n1-1);
        F3=F3+t.toString(DTFormat);
        F3=F3+F2.mid(n2+1);
        F2=F3;
    }
    LotInformation  *L=GetLayersBase()->GetLot(0);
    if(L!=NULL){
        QString F4=F2       .replace(/**/"%l",L->GetLotID());
        return F4;
    }
    return F2;
}

void	ShowResultDetailForm::ShowInPlayer		(int64 shownInspectionID)
{
    if(GetLayersBase()->GetShadowLevel()==0){
        ResultContainer.RemoveAll();
	    for(int page=0;page<GetPageNumb();page++){
	    	int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
	    	GUICmdReqResultDetailList	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
            GUICmdAckResultDetailList	ACmd(GetLayersBase(),sRoot,sName,GlobalPage);
            if(RCmd.Send(GlobalPage,0,ACmd)==true){
                ResultContainer+=ACmd.ResultContainer;
            }
        }
        ui->tableWidget->setRowCount(ResultContainer.GetCount());
        int row=0;
        for(ResultDetailList *L=ResultContainer.GetFirst();L!=NULL;L=L->GetNext(),row++){
            ::SetDataToTable(ui->tableWidget,0, row, QString::number(L->Phase));
            ::SetDataToTable(ui->tableWidget,1, row, QString::number(L->Page));
            ::SetDataToTable(ui->tableWidget,2, row, QString::number(L->Layer));
            ::SetDataToTable(ui->tableWidget,3, row, QString::number(L->ItemID));
            ::SetDataToTable(ui->tableWidget,4, row, QString::number(L->LibID));
            QString LibName=GetLayersBase()->GetLibraryName(L->LibType,L->LibID);
            ::SetDataToTable(ui->tableWidget,5, row, LibName);
            ::SetDataToTable(ui->tableWidget,6, row, L->Message);
            ::SetDataToTable(ui->tableWidget,7, row, L->Res1);
            ::SetDataToTable(ui->tableWidget,8, row, L->Res2);
            ::SetDataToTable(ui->tableWidget,9, row, L->Res3);
        }

        QString FileName=MakePathFile();
        QFileInfo   FInfo(FileName);
        QString Path=FInfo.path();
        ::ForceDirectories(Path);
        WriteOut(FileName);
    }
}

void ShowResultDetailForm::on_pushButtonWriteResult_clicked()
{
    QString FileName=QFileDialog::getSaveFileName(nullptr
                                    , "Write result detail"
                                    , QString()
                                    , "CSV file (*.csv)");
    if(FileName.isEmpty()==false){
        QFileInfo   FInfo(FileName);
        QString Path=FInfo.path();
        ::ForceDirectories(Path);
        WriteOut(FileName);
    }
}

bool    ShowResultDetailForm::WriteOut(const QString &FileName)
{
    QStringListListCSV  CSV;
    int row=0;
    CSV.Set(0, row ,/**/"Phase");
    CSV.Set(1, row ,/**/"Page");
    CSV.Set(2, row ,/**/"Layer");
    CSV.Set(3, row ,/**/"ItemID");
    CSV.Set(4, row ,/**/"LibName");
    CSV.Set(5, row ,/**/"Position");
    CSV.Set(6, row ,/**/"Message");
    CSV.Set(7, row ,/**/"Res1");
    CSV.Set(8, row ,/**/"Res2");
    CSV.Set(9, row ,/**/"Res3");
    row++;
    for(ResultDetailList *L=ResultContainer.GetFirst();L!=NULL;L=L->GetNext(),row++){
        CSV.Set(0, row ,QString::number(L->Phase));
        CSV.Set(1, row ,QString::number(L->Page));
        CSV.Set(2, row ,QString::number(L->Layer));
        CSV.Set(3, row ,QString::number(L->ItemID));
        QString LibName=GetLayersBase()->GetLibraryName(L->LibType,L->LibID);
        CSV.Set(4, row ,LibName);
        CSV.Set(5, row ,QString::number(L->PosX)+QString(/**/",")+QString::number(L->PosY));
        CSV.Set(6, row ,L->Message);
        CSV.Set(7, row ,L->Res1);
        CSV.Set(8, row ,L->Res2);
        CSV.Set(9, row ,L->Res3);
    }
    return CSV.SaveFromCSVFile(FileName);
}

//============================================================================

GUICmdReqResultDetailList::GUICmdReqResultDetailList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
void	GUICmdReqResultDetailList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckResultDetailList	*SendBack=GetSendBack(GUICmdAckResultDetailList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

    MakeList            (SendBack->ResultContainer ,GetLayersBase(),localPage);
    MakeListShadowTree  (SendBack->ResultContainer ,GetLayersBase(),localPage);

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

void    GUICmdReqResultDetailList::MakeListShadowTree(ResultDetailListContainer &ResultContainer 
                                                        ,LayersBase *Base
                                                        ,int localPage)
{
    int N=Base->GetShadowChildrenCount();
    for(int i=0;i<N;i++){
        ShadowTree	*s=Base->GetShadowChildren(i);
        if(s!=NULL){
            LayersBase	*B=s->GetTreeLayersBase();
            MakeList(ResultContainer ,B,localPage);
            MakeListShadowTree  (ResultContainer ,B,localPage);
        }
    }
}

void    GUICmdReqResultDetailList::MakeList(ResultDetailListContainer &ResultContainer 
                                            ,LayersBase *Base,int localPage)
{
	ResultInspection	*R=Base->GetCurrentResultForDraw();
	if(R!=NULL){
        for(ResultBaseForAlgorithmRoot	*r=R->GetResultBaseDimFirst();r!=NULL;r=r->GetNext()){
            AlgorithmBase   *ABase=r->GetAlgorithm();
            for(int phase=0;phase<GetPhaseNumb();phase++){
                ResultBasePhase		*Ph=r->GetPageDataPhase(phase);
                AlgorithmInPageInOnePhase   *Ah=ABase->GetPageDataPhase(phase);
                if(Ph!=NULL && Ah!=NULL){
                    ResultInPageRoot	*Rp=Ph->GetPageData(localPage);
                    AlgorithmInPageRoot *Ap=Ah->GetPageData(localPage);
                    if(Rp!=NULL && Ap!=NULL){
                        DetailResultInfoListContainerAll List;
                        Rp->MakeResultDetailInNG(List);
                        for(DetailResultInfoListContainer *C=List.GetFirst();C!=NULL;C=C->GetNext()){
                            for(DetailResultInfoList *a=C->NPListPack<DetailResultInfoList>::GetFirst();a!=NULL;a=a->GetNext()){
                                ResultDetailList    *L=new ResultDetailList();
                                //AlgorithmItemRoot   *AItem=Ap->GetItemData(C->Data.Layer,C->Data.ItemID);
                                L->Phase    =C->Data.Phase;
                                L->Page     =C->Data.Page;
                                L->Layer    =C->Data.Layer;
                                L->ItemID   =C->Data.ItemID;
                                L->LibType  =C->Data.LibType;
                                L->LibID    =C->Data.LibID;
                                L->PosX     =C->Data.PosX;
                                L->PosY     =C->Data.PosY;
                                L->Message  =a->MessageString;
                                if(a->ResultValueContainer.GetCount()>=1)
                                    L->Res1     =a->ResultValueContainer.GetItem(0)->GetResultValue();
                                if(a->ResultValueContainer.GetCount()>=2)
                                    L->Res2     =a->ResultValueContainer.GetItem(1)->GetResultValue();
                                if(a->ResultValueContainer.GetCount()>=3)
                                    L->Res3     =a->ResultValueContainer.GetItem(2)->GetResultValue();
                                ResultContainer.AppendList(L);
                            }
                        }
                    }
                }
            }
        }
    }
}

GUICmdAckResultDetailList::GUICmdAckResultDetailList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdAckResultDetailList::Load(QIODevice *f)
{
    if(ResultContainer.Load(f)==false)  return false;
    return true;
}
bool	GUICmdAckResultDetailList::Save(QIODevice *f)
{
    if(ResultContainer.Save(f)==false)  return false;
    return true;
}