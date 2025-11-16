#include "MakeLanguageDialog.h"
#include "XGUILanguage.h"
#include "ui_MakeLanguageDialog.h"
#include "XDataInLayer.h"
#include "XGeneralFunc.h"

MakeLanguageDialog::MakeLanguageDialog(LayersBase *base ,QWidget *parent) :
    QDialog(parent),ServiceForLayers(base),
    ui(new Ui::MakeLanguageDialog)
{
    ui->setupUi(this);

    QDir::setCurrent(GetLayersBase()->GetUserPath());
    LPack.LoadDefault();

    GetLayersBase()->PickupGUILanguage();
    ShowGrid();
}

MakeLanguageDialog::~MakeLanguageDialog()
{
    delete ui;
}

void MakeLanguageDialog::ShowGrid(void)
{
    ui->tableWidget->setRowCount(GetLayersBase()->GetGUILanguageContainer().GetCount());
    int Row=0;
    for(GUILanguageList *g=GetLayersBase()->GetGUILanguageContainer().GetFirst();g!=NULL;g=g->GetNext(),Row++){
        ::SetDataToTable(ui->tableWidget, 0, Row, g->DLLRoot);
        ::SetDataToTable(ui->tableWidget, 1, Row, g->DLLName);
        ::SetDataToTable(ui->tableWidget, 2, Row, g->InstName);
        ::SetDataToTable(ui->tableWidget, 3, Row, g->MemberName);
        LanguageStringList	*s=g->LanguageText.FindLanguage(GetLayersBase()->GetLanguageCode());
        QString Str;
        QStringList StrList;
        if(s!=NULL){
            Str     =s->Text;
            StrList =s->TextList;
        }
        if(Str.isEmpty()==false){
            ::SetDataToTable(ui->tableWidget, 4, Row, Str);
        }
        else{
            ::SetDataToTable(ui->tableWidget,4,Row,/**/"QStringList");
        }
    }
}

void MakeLanguageDialog::on_pushButtonLoadGUILanguageFile_clicked()
{
    QString GLNFileName=QFileDialog::getOpenFileName(NULL,"Load GUILanguage file"
                                                    ,/**/""
                                                    ,/**/"GUI language file(*.GLN)");
    if(GLNFileName.isEmpty()==false){
        GetLayersBase()->LoadGUILanguage(GLNFileName);
        ShowGrid();
    }
}


void MakeLanguageDialog::on_pushButtonSaveGUILanguageFile_clicked()
{
    QString GLNFileName=QFileDialog::getSaveFileName(NULL,"Save GUILanguage file"
                                                    ,/**/""
                                                    ,/**/"GUI language file(*.GLN)");
    if(GLNFileName.isEmpty()==false){
        GetLayersBase()->SaveGUILanguage(GLNFileName);
    }
}

void MakeLanguageDialog::on_pushButtonLoadLanguageExcel_clicked()
{
    QString ExcelFileName=QFileDialog::getOpenFileName(NULL,"Load Excel file for language"
                                                    ,/**/""
                                                    ,/**/"Excel file(*.xlsx)");
    if(ExcelFileName.isEmpty()==false){
        LoadExcelFile(LPack,ExcelFileName,GetLayersBase()->GetGUILanguageContainer());
        ShowGrid();
    }
}

void MakeLanguageDialog::on_pushButtonSaveLanguageExcel_clicked()
{
    QString ExcelFileName=QFileDialog::getSaveFileName(NULL,"Save Excel file for language"
                                                    ,/**/""
                                                    ,/**/"Excel file(*.xlsx)");
    if(ExcelFileName.isEmpty()==false){
        SaveExcelFile(LPack,ExcelFileName,GetLayersBase()->GetGUILanguageContainer());
    }
}

