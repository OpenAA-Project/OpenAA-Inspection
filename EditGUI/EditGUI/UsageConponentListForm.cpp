#include "UsageConponentListForm.h"
#include "ui_UsageConponentListForm.h"
#include "XGeneralFunc.h"
#include "XGUI.h"
#include "XDataInLayer.h"
#include<QTextStream>
#include<QFileInfo>
#include "itemlistwindow.h"
#include <QTabWidget>
#include "propertylist.h"
#include "CopyBATDialog.h"
#include "XGUIInterfaceDLL.h"

extern	ItemListWindow	*MainItem;
extern	PropertyList	*MainProperty;

UsageConponentListForm::UsageConponentListForm(EditGUI *p,LayersBase *base,QWidget *parent) :
    QWidget(parent),ServiceForLayers(base),Parent(p),
    ui(new Ui::UsageConponentListForm)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);

    ui->tableWidget->setColumnWidth(0,100);
    ui->tableWidget->setColumnWidth(1,100);
    ui->tableWidget->setColumnWidth(2,180);
    ui->tableWidget->setColumnWidth(3,180);

    for(GUIItemInstance *c=GetLayersBase()->GetEntryPoint()->GetGUIInstancePack()->NPListPack<GUIItemInstance>::GetFirst();c!=NULL;c=c->GetNext()){
        if(c->DLLAccess!=NULL){
            GUIItemInstancePointerList	*t=new GUIItemInstancePointerList(c);
            ItemListContainer.AppendList(t);
        }
    }
    ShowList();
    connect(ui->tableWidget->horizontalHeader() ,SIGNAL(sectionClicked (int)),this,SLOT(MListSectionClicked (int)));
}

UsageConponentListForm::~UsageConponentListForm()
{
    delete ui;
}

void UsageConponentListForm::ShowList(void)
{
    int	N=ItemListContainer.GetCount();
    ui->tableWidget->setRowCount(N);
    int	Row=0;

    for(GUIItemInstancePointerList *p=ItemListContainer.GetFirst();p!=NULL;p=p->GetNext(),Row++){
        if(p->Point->DLLAccess!=NULL){
            SetDataToTable(ui->tableWidget,0,Row,p->Point->DLLAccess->RootName);
            SetDataToTable(ui->tableWidget,1,Row,p->Point->DLLAccess->Name);
            SetDataToTable(ui->tableWidget,2,Row,p->Point->Handle->GetName());
            RootNameListContainer List;
            p->Point->DLLAccess->EntryAlgorithm(List);
            QString	s;
            for(RootNameList *r=List.GetFirst();r!=NULL;r=r->GetNext()){
                s+=r->DLLRoot + QString(":")+r->DLLName+QString("\n");
            }
            SetDataToTable(ui->tableWidget,3,Row,s);
        }
    }
}
void UsageConponentListForm::on_tableWidget_clicked(const QModelIndex &index)
{
    int	Row=ui->tableWidget->currentRow();
    if(Row<0)
        return;
    GUIItemInstancePointerList *p=ItemListContainer.GetItem(Row);
    if(p!=NULL){
        MainProperty->DLLInst	=p->Point;
        if(p->Point->DLLAccess!=NULL && p->Point->GetForm()!=NULL){
            MainProperty->PutTop	=p->Point->GetForm()->GetParentFormBase();
            MainProperty->ShowList(p->Point->DLLAccess->RootName,p->Point->DLLAccess->Name);
            GetLayersBase()->SetZoneWindow(p->Point->GetForm());
        }
        else{
            MainProperty->ClearList();
        }

    }
}

void UsageConponentListForm::on_pushButtonMakeCopyBAT_clicked()
{
    CopyBATDialog	E(Parent ,GetLayersBase(), NULL);
    E.exec();
}

void UsageConponentListForm::on_pushButtonDelete_clicked()
{
    int	R=ui->tableWidget->currentRow();
    if(R<0)
        return;
    GUIItemInstancePointerList *p=ItemListContainer[R];
    if(p==NULL)
        return;
    GetLayersBase()->GetEntryPoint()->GetGUIInstancePack()->NPListPack<GUIItemInstance>::RemoveList(p->Point);
    delete	p->Point;

    ItemListContainer.RemoveAll();
    for(GUIItemInstance *c=GetLayersBase()->GetEntryPoint()->GetGUIInstancePack()->NPListPack<GUIItemInstance>::GetFirst();c!=NULL;c=c->GetNext()){
        if(c->DLLAccess!=NULL){
            GUIItemInstancePointerList	*t=new GUIItemInstancePointerList(c);
            ItemListContainer.AppendList(t);
        }
    }
    ShowList();
}

void UsageConponentListForm::on_pushButtonClose_clicked()
{
    close();
}

void UsageConponentListForm::on_pushButtonExcludedListOut_clicked()
{
    QString FileName=GetLayersBase()->LGetSaveFileName(this, "Save Excluded list file", QString(), "Excluded File (*.dat);;All files (*.*)");
    if(FileName.isEmpty()==false){
        QFile	File(FileName);
        if(File.open(QIODevice::WriteOnly)==true){
            QTextStream	Txt(&File);
            int	pnumb=0;
            for(GuiDLLItem *p=GetLayersBase()->GetGuiInitializer()->GuiDLLPack->GetFirst();p!=NULL;p=p->GetNext(),pnumb++){
                GUIItemInstance *c;
                for(c=GetLayersBase()->GetEntryPoint()->GetGUIInstancePack()->NPListPack<GUIItemInstance>::GetFirst();c!=NULL;c=c->GetNext()){
                    if(c->DLLAccess!=NULL && p->RootName==c->DLLAccess->RootName && p->Name==c->DLLAccess->Name){
                        break;
                    }
                }
                if(c==NULL){
                    QFileInfo	TFile(p->FileName);
                    Txt<<TFile.fileName()<</**/"\n";
                }
            }
        }
    }
}

static	int		SortByRoot(const void *a, const void *b)
{
    UsageConponentListForm::GUIItemInstancePointerList	*pa=((UsageConponentListForm::GUIItemInstancePointerList	**)a)[0];
    UsageConponentListForm::GUIItemInstancePointerList	*pb=((UsageConponentListForm::GUIItemInstancePointerList	**)b)[0];


    if(pa->Point->DLLAccess->RootName<pb->Point->DLLAccess->RootName)
        return -1;
    if(pa->Point->DLLAccess->RootName>pb->Point->DLLAccess->RootName)
        return 1;

    if(pa->Point->DLLAccess->Name<pb->Point->DLLAccess->Name)
        return -1;
    if(pa->Point->DLLAccess->Name>pb->Point->DLLAccess->Name)
        return 1;

    if(pa->Point->Handle->GetName()<pb->Point->Handle->GetName())
        return -1;
    if(pa->Point->Handle->GetName()>pb->Point->Handle->GetName())
        return 1;

    return 0;
}

static	int		SortByInst(const void *a, const void *b)
{
    UsageConponentListForm::GUIItemInstancePointerList	*pa=((UsageConponentListForm::GUIItemInstancePointerList	**)a)[0];
    UsageConponentListForm::GUIItemInstancePointerList	*pb=((UsageConponentListForm::GUIItemInstancePointerList	**)b)[0];

    if(pa->Point->Handle->GetName()<pb->Point->Handle->GetName())
        return -1;
    if(pa->Point->Handle->GetName()>pb->Point->Handle->GetName())
        return 1;

    if(pa->Point->Handle->GetName()<pb->Point->Handle->GetName())
        return -1;
    if(pa->Point->Handle->GetName()>pb->Point->Handle->GetName())
        return 1;

    if(pa->Point->DLLAccess->RootName<pb->Point->DLLAccess->RootName)
        return -1;
    if(pa->Point->DLLAccess->RootName>pb->Point->DLLAccess->RootName)
        return 1;

    if(pa->Point->DLLAccess->Name<pb->Point->DLLAccess->Name)
        return -1;
    if(pa->Point->DLLAccess->Name>pb->Point->DLLAccess->Name)
        return 1;

    return 0;
}

static	int		SortByAlgorithm(const void *a, const void *b)
{
    UsageConponentListForm::GUIItemInstancePointerList	*pa=((UsageConponentListForm::GUIItemInstancePointerList	**)a)[0];
    UsageConponentListForm::GUIItemInstancePointerList	*pb=((UsageConponentListForm::GUIItemInstancePointerList	**)b)[0];

    RootNameListContainer AList;
    pa->Point->DLLAccess->EntryAlgorithm(AList);

    RootNameListContainer BList;
    pb->Point->DLLAccess->EntryAlgorithm(BList);

    if(AList.GetCount()>0 && BList.GetCount()==0)
        return -1;
    if(AList.GetCount()==0 && BList.GetCount()>0)
        return 1;

    if(AList.GetCount()>0 && BList.GetCount()>0){
        RootNameList	*ka=AList[0];
        RootNameList	*kb=BList[0];
        if(ka->DLLRoot<kb->DLLRoot)
            return -1;
        if(ka->DLLRoot>kb->DLLRoot)
            return 1;

        if(ka->DLLName<kb->DLLName)
            return -1;
        if(ka->DLLName>kb->DLLName)
            return 1;
    }

    if(pa->Point->Handle->GetName()<pb->Point->Handle->GetName())
        return -1;
    if(pa->Point->Handle->GetName()>pb->Point->Handle->GetName())
        return 1;

    if(pa->Point->Handle->GetName()<pb->Point->Handle->GetName())
        return -1;
    if(pa->Point->Handle->GetName()>pb->Point->Handle->GetName())
        return 1;

    if(pa->Point->DLLAccess->RootName<pb->Point->DLLAccess->RootName)
        return -1;
    if(pa->Point->DLLAccess->RootName>pb->Point->DLLAccess->RootName)
        return 1;

    if(pa->Point->DLLAccess->Name<pb->Point->DLLAccess->Name)
        return -1;
    if(pa->Point->DLLAccess->Name>pb->Point->DLLAccess->Name)
        return 1;

    return 0;
}

void	UsageConponentListForm::resizeEvent ( QResizeEvent * event )
{
    ui->frame->setGeometry(0,height()-ui->frame->height(),width(),ui->frame->height());
    ui->tableWidget->resize(width(),height()-ui->frame->height());

    int	W=width()-32;
    ui->tableWidget->setColumnWidth(0,W*0.18);
    ui->tableWidget->setColumnWidth(1,W*0.18);
    ui->tableWidget->setColumnWidth(2,W*0.32);
    ui->tableWidget->setColumnWidth(3,W*0.32);
}

void UsageConponentListForm::MListSectionClicked (int n)
{
    if(n==0 || n==1)
        ItemListContainer.Sort(SortByRoot);
    else if(n==2)
        ItemListContainer.Sort(SortByInst);
    else if(n==3)
        ItemListContainer.Sort(SortByAlgorithm);

    ShowList();
}
