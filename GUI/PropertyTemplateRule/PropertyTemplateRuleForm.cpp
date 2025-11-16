#include "PropertyTemplateRuleForm.h"
#include "ui_PropertyTemplateRuleForm.h"
#include "EditTemplateRuleItemDialog.h"
#include "XGeneralFunc.h"
#include "SelectLibFolderDialog.h"
#include "XAlgorithmBase.h"
#include "XDataAlgorithm.h"
#include "XDataInLayer.h"
#include "XDatabaseLoader.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

PropertyTemplateRuleForm::PropertyTemplateRuleForm(LayersBase *Base,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::PropertyTemplateRuleForm)
{
    ui->setupUi(this);

    ::SetColumnWidthInTable(ui->tableWidgetAlgorithmType ,0, 15);
    ::SetColumnWidthInTable(ui->tableWidgetAlgorithmType ,1, 80);

    RetSelectedLibFolderID=-1;

    for(LogicDLL *L=GetLayersBase()->GetLogicDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
        AlgorithmBase   *ABase=L->GetInstance();
        if(ABase->GetLibType()>0){
            AlgorithLibTypeList.Add(ABase->GetLibType());
        }
    }
    ui->tableWidgetAlgorithmType->setRowCount(AlgorithLibTypeList.GetCount());
    int Row=0;
    for(IntClass *c=AlgorithLibTypeList.GetFirst();c!=NULL;c=c->GetNext(),Row++){
        int LibType=c->GetValue();
        ::SetDataToTable(ui->tableWidgetAlgorithmType, 0, Row, QString::number(LibType));
        ::SetDataToTable(ui->tableWidgetAlgorithmType, 1, Row, GetLayersBase()->GetLibTypeName(LibType));
    }
}

PropertyTemplateRuleForm::~PropertyTemplateRuleForm()
{
    delete ui;
}

TemplateRuleBase	*PropertyTemplateRuleForm::GetTemplateRuleBase(void)
{
	return (TemplateRuleBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"TemplateRule");
}
void PropertyTemplateRuleForm::on_tableWidgetItemList_clicked(const QModelIndex &index)
{

}


void PropertyTemplateRuleForm::on_tableWidgetItemList_doubleClicked(const QModelIndex &index)
{

}


void PropertyTemplateRuleForm::on_tableWidgetAlgorithmType_clicked(const QModelIndex &index)
{

}


void PropertyTemplateRuleForm::on_pushButtonEditLibFolder_clicked()
{
    int Row=ui->tableWidgetAlgorithmType->currentRow();
    int _LibType=AlgorithLibTypeList[Row];

	SelectLibFolderDialog	D(_LibType,GetLayersBase());
	if(D.exec()==(int)true){
		RetSelectedLibFolderID	=D.SelectedLibFolderID;
		ui->labelLibFolderName->setText(D.SelectedFolderName);
	}
}


void	PropertyTemplateRuleForm::ShowLibList(void)
{
    int Row=ui->tableWidgetAlgorithmType->currentRow();
    int _LibType=AlgorithLibTypeList[Row];

	ui->tableWidgetLibList->setRowCount(0);
	AlgorithmBase	*BBase=GetLayersBase()->GetAlgorithmBase(_LibType);
	if(BBase!=NULL){
		int		IDList[1000];
		int	N=GetLayersBase()->GetDatabaseLoader()->G_EnumLibraryByTypeInt(*GetLayersBase()->GetDataBase()
																	,_LibType
																	,RetSelectedLibFolderID
																	,IDList ,sizeof(IDList)/sizeof(IDList[0]));
		int	row=0;
		ui->tableWidgetLibList->setRowCount(N);
		for(int i=0;i<N;i++){
			QTableWidgetItem *W;
			W=ui->tableWidgetLibList->item ( row, 0);
			if(W==NULL){
				W=new QTableWidgetItem();
				ui->tableWidgetLibList->setItem ( row, 0,W);
				W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);			
			}
			W->setText(QString::number(IDList[i]));
			W=ui->tableWidgetLibList->item ( row, 1);
			if(W==NULL){
				W=new QTableWidgetItem();
				ui->tableWidgetLibList->setItem ( row, 1,W);
				W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			}
			QString	LibName=GetLayersBase()->GetLibraryName(_LibType,IDList[i]);
			W->setText(LibName);
		}
	}
}

void	PropertyTemplateRuleForm::TransmitDirectly(GUIDirectMessage *packet)
{

}

void PropertyTemplateRuleForm::on_tableWidgetLibList_doubleClicked(const QModelIndex &index)
{

}


void PropertyTemplateRuleForm::on_tableWidgetGeneratedLibList_doubleClicked(const QModelIndex &index)
{

}


void PropertyTemplateRuleForm::on_pushButtonSetFrom_clicked()
{

}


void PropertyTemplateRuleForm::on_pushButtonGetBack_clicked()
{

}


void PropertyTemplateRuleForm::on_pushButtonSetFromAll_clicked()
{

}


void PropertyTemplateRuleForm::on_pushButtonGetBackAll_clicked()
{

}

