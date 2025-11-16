#include "ButtonShowConfirmResource.h"
#include "ConfirmItemListForm.h"
#include "ui_ConfirmItemListForm.h"
#include "ConfirmForm.h"
#include "XConfirmAlgorithm.h"
#include "XGeneralFunc.h"

int	ComfirmItemListPointer::Compare(ComfirmItemListPointer &src)
{
    int d=(int)CItem->CType - (int)src.CItem->CType;
    return d;
}

ConfirmItemListForm::ConfirmItemListForm(LayersBase *Base,ConfirmForm *P,QWidget *parent) :
    QWidget(parent)
    ,ServiceForLayers(Base)
    ,Parent(P)
    ,ui(new Ui::ConfirmItemListForm)
{
    setWindowFlags(Qt::WindowTitleHint | Qt::WindowStaysOnTopHint);
    ui->setupUi(this);
    LangSolver.SetUI(this);
}

ConfirmItemListForm::~ConfirmItemListForm()
{
    delete ui;
}

void    ConfirmItemListForm::BuildShowItemList(void)
{
    ComfirmItems.RemoveAll();
	for(int i=0;i<sizeof(Parent->AlgoList)/sizeof(Parent->AlgoList[0]);i++){
		for(ConfirmItemList *p=Parent->AlgoList[i]->ConfirmItemInst.GetFirst();p!=NULL;p=p->GetNext()){
	        ComfirmItemListPointer  *h=new ComfirmItemListPointer();
            h->CAlgorithm=Parent->AlgoList[i];
            h->CItem     =p;
            ComfirmItems.AppendList(h);
        }
    }
    ComfirmItems.Sort();

    int N=ComfirmItems.GetCount();
    ui->tableWidgetCause->setRowCount(N);
    ComfirmItemListPointer  *h=ComfirmItems.GetFirst();
    for(int row=0;row<N && h!=NULL;row++,h=h->GetNext()){
        QString StrCType;
        switch(h->CItem->CType){
        case CF_Emergency	:   StrCType=LangSolver.GetString(ConfirmItemListForm_LS,LID_0)/*"緊急"*/;
                                break;
        case CF_NG		    :	StrCType=LangSolver.GetString(ConfirmItemListForm_LS,LID_2)/*"NG"*/;
                                break;
        case CF_Alert	    :	StrCType=LangSolver.GetString(ConfirmItemListForm_LS,LID_3)/*"注意"*/;
                                break;
        case CF_ReqConfirm  :   StrCType=LangSolver.GetString(ConfirmItemListForm_LS,LID_5)/*"確認"*/;
                                break;
        }
        ::SetDataToTable(ui->tableWidgetCause, 0, row, StrCType);
        AlgorithmBase   *ABase=GetLayersBase()->GetAlgorithmBase(h->CAlgorithm->GetLibType());
        ::SetDataToTable(ui->tableWidgetCause, 1, row, ABase->GetNameByCurrentLanguage());
        ::SetDataToTable(ui->tableWidgetCause, 2, row, QString::number(h->CItem->Phase));
        ::SetDataToTable(ui->tableWidgetCause, 3, row, QString::number(h->CItem->ItemID));
        ::SetDataToTable(ui->tableWidgetCause, 4, row, h->CItem->Cause);
    }

}
void ConfirmItemListForm::resizeEvent(QResizeEvent *event)
{
    ui->tableWidgetCause->resize(width(),height());
    
    ::SetColumnWidthInTable(ui->tableWidgetCause ,0, 8);
    ::SetColumnWidthInTable(ui->tableWidgetCause ,1, 25);
    ::SetColumnWidthInTable(ui->tableWidgetCause ,2, 8);
    ::SetColumnWidthInTable(ui->tableWidgetCause ,3, 8);
    ::SetColumnWidthInTable(ui->tableWidgetCause ,4, 50);
}

void ConfirmItemListForm::on_tableWidgetCause_itemSelectionChanged()
{
    int row=ui->tableWidgetCause->currentRow();
    if(row>=0){
        ComfirmItemListPointer  *h=ComfirmItems.GetItem(row);
        if(h!=NULL && h->CAlgorithm!=NULL && h->CItem!=NULL){
            Parent->ShowConfirmItem(h->CAlgorithm,h->CItem);
        }
    }
}


void ConfirmItemListForm::on_tableWidgetCause_clicked(const QModelIndex &index)
{
    on_tableWidgetCause_itemSelectionChanged();
}

