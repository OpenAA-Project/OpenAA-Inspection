#include "InputTextInLanguageDialog.h"
#include "ui_InputTextInLanguageDialog.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QMessageBox>
#include <QTableWidget>
#include <QScrollBar>
#include "XGeneralFunc.h"
#include <QCheckBox>
#include "XServiceRegSpector.h"


//===============================================================================

InputTextInLanguageDialog::InputTextInLanguageDialog(const QSqlDatabase &_database ,int TextClass ,int IndexAutoCount ,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InputTextInLanguageDialog)
{
    ui->setupUi(this);

    database    =_database;

    LoadTextInLanguageFromDB(database,TextClass ,IndexAutoCount,TextCode);

    int RowCount=TextCode.GetCount();
    ui->tableWidget->setRowCount(RowCount);
    int row=0;
    for(TextList *t=TextCode.GetFirst();t!=NULL;t=t->GetNext(),row++){
        ::SetDataToTable(ui->tableWidget, 0, row, t->CountryCode);
        ::SetDataToTable(ui->tableWidget, 1, row, t->CountryName);
        CheckBoxInTable   *b=::SetDataToTableCheckable(ui->tableWidget, 2, row, "", false);
        ::SetDataToTable(ui->tableWidget, 3, row, t->TextStr,Qt::ItemIsEditable);

        connect(b,SIGNAL(checked(int,int,bool)),this,SLOT(SlotDefaultChecked(int,int,bool)));
    }

    setResult(false);
}

InputTextInLanguageDialog::InputTextInLanguageDialog(const QSqlDatabase &dbase ,const TextContainer &text ,QWidget *parent):
    QDialog(parent),
    ui(new Ui::InputTextInLanguageDialog)
{
    ui->setupUi(this);

    database    =dbase;
    TextCode    =text;

    QStringListListCSV CSV;
    if(CSV.LoadFromCSVFile(LanguageListFileName)==true){
        int RowCount=CSV.GetRowCount();
        for(int row=0;row<RowCount;row++){
            QString Code=CSV.Get(0, row).left(2);
            TextList *t;
            for(t=TextCode.GetFirst();t!=NULL;t=t->GetNext()){
                if(t->CountryCode==Code){
                    t->CountryName  =CSV.Get(1, row);
                    t->JPCountryStr =CSV.Get(2, row);
                    t->MainCurrencyCode =CSV.Get(3, row);
                    break;
                }
            }
            if(t==NULL){
                t=new TextList;
                t->CountryCode  =Code;
                t->CountryName  =CSV.Get(1, row);
                t->JPCountryStr =CSV.Get(2, row);
                t->MainCurrencyCode =CSV.Get(3, row);
                TextCode.AppendList(t);
            }
        }
    }

    int RowCount=TextCode.GetCount();
    ui->tableWidget->setRowCount(RowCount);
    int row=0;
    for(TextList *t=TextCode.GetFirst();t!=NULL;t=t->GetNext(),row++){
        ::SetDataToTable(ui->tableWidget, 0, row, t->CountryCode);
        ::SetDataToTable(ui->tableWidget, 1, row, t->CountryName);
        CheckBoxInTable   *b=::SetDataToTableCheckable(ui->tableWidget, 2, row, "", false);
        ::SetDataToTable(ui->tableWidget, 3, row, t->TextStr,Qt::ItemIsEditable);

        connect(b,SIGNAL(checked(int,int,bool)),this,SLOT(SlotDefaultChecked(int,int,bool)));
    }

    setResult(false);
}

InputTextInLanguageDialog::~InputTextInLanguageDialog()
{
    delete ui;
}

void InputTextInLanguageDialog::resizeEvent(QResizeEvent *event)
{
    ui->frame->setGeometry(0,height()-ui->frame->height(),width(),ui->frame->height());
    ui->tableWidget ->resize(width(),height()-ui->frame->height());
    ui->tableWidget ->setColumnWidth(0,48);
    ui->tableWidget ->setColumnWidth(1,150);
    ui->tableWidget ->setColumnWidth(2,32);
    int W=ui->tableWidget->verticalHeader()->width() + ui->tableWidget->verticalScrollBar()->width();
    ui->tableWidget ->setColumnWidth(3,width()-48-150-32-W-4);

    ui->pushButtonOK    ->move(  width()/3-ui->pushButtonOK    ->width()/2,ui->pushButtonOK    ->geometry().top());
    ui->pushButtonCancel->move(2*width()/3-ui->pushButtonCancel->width()/2,ui->pushButtonCancel->geometry().top());
}

void InputTextInLanguageDialog::on_pushButtonOK_clicked()
{
    QString DefaultStr;
    int row=0;
    for(TextList *t=TextCode.GetFirst();t!=NULL;t=t->GetNext(),row++){
        bool   b=::GetCheckedFromTable(ui->tableWidget, 2, row);
        if(b==true){
            DefaultStr=::GetDataToTable(ui->tableWidget, 3, row);
            break;
        }
    }
    row=0;
    for(TextList *t=TextCode.GetFirst();t!=NULL;t=t->GetNext(),row++){
        QString TextStr=::GetDataToTable(ui->tableWidget, 3, row);
        if(TextStr.isEmpty()==true)
            TextStr=DefaultStr;
        t->TextStr  =TextStr;
    }

    done(true);
}


void InputTextInLanguageDialog::on_pushButtonCancel_clicked()
{
    done(false);
}

void    InputTextInLanguageDialog::SlotDefaultChecked(int Column,int Row ,bool b)
{
    if(b==true){
        int row=0;
        for(TextList *t=TextCode.GetFirst();t!=NULL;t=t->GetNext(),row++){
            if(row!=Row){
                ::SetDataToTableCheckable(ui->tableWidget, 2, row, "", false);
            }
        }
    }
}

//=============================================================================================

QString GetTextInLanguage(const QSqlDatabase &dbase ,int TextClass ,int IndexAutoCount,const QString &CountryCode)
{
	QString	S=QString(/**/"SELECT textStr FROM RegSpector.TextInLanguage ")
            +QString(/**/"where textClass=")+QString::number(TextClass)
            +QString(/**/" and indexAutoCount=")+QString::number(IndexAutoCount)
            +QString(/**/" and country=\'")+CountryCode +QString(/**/"\'");

	QSqlQuery query(S ,dbase);
	if(query.next ()==true){
        QString TextStr =query.value(query.record().indexOf(/**/"textStr")).toByteArray();
        return TextStr;
    }
    return QString("");
}

bool StoreTextInLanguageInDB(const QSqlDatabase &dbase ,int TextClass ,int IndexAutoCount,const TextContainer &TextCode)
{
    for(TextList *t=TextCode.GetFirst();t!=NULL;t=t->GetNext()){
        QString CountryCode=t->CountryCode;
	    QString	S=QString(/**/"SELECT textStr FROM RegSpector.TextInLanguage ")
                 +QString(/**/"where textClass=")+QString::number(TextClass)
                 +QString(/**/" and indexAutoCount=")+QString::number(IndexAutoCount)
                 +QString(/**/" and country=\'")+CountryCode +QString("\'");

	    QSqlQuery query(S ,dbase);
	    if(query.next ()==true){
            QString TextStr =query.value(query.record().indexOf(/**/"textStr")).toString();
            if(t->TextStr!=TextStr){
	            QSqlQuery queryUpdate(dbase);
	            queryUpdate.prepare(QString(/**/"UPDATE RegSpector.TextInLanguage SET "
                                            /**/"textStr=:textStr ")
                                   +QString(/**/"where textClass=")+QString::number(TextClass)
                                   +QString(/**/" and indexAutoCount=")+QString::number(IndexAutoCount)
                                   +QString(/**/" and country=\'")+CountryCode +QString(/**/"\'"));
	            queryUpdate.bindValue(0	, TextStr.toUtf8());

	            if(queryUpdate.exec()==false){
                    QMessageBox::warning(NULL,"Error","Can not update TextInLanguage");
                    return false;
                }
            }
        }
        else{
            QString TextStr =t->TextStr;

	        QSqlQuery queryInsrt(dbase);
	        queryInsrt.prepare(/**/"INSERT INTO RegSpector.TextInLanguage("
                                /**/"textClass,"
                                /**/"indexAutoCount,"
                                /**/"country,"
                                /**/"textStr) "
	        	            /**/"VALUES("
                                /**/":textClass,"
                                /**/":indexAutoCount,"
                                /**/":country,"
                                /**/":textStr);");
            queryInsrt.bindValue(0	, TextClass	);
	        queryInsrt.bindValue(1	, IndexAutoCount);
	        queryInsrt.bindValue(2	, CountryCode	);
	        queryInsrt.bindValue(3	, TextStr.toUtf8());

	        if(queryInsrt.exec()==false){
                QMessageBox::warning(NULL,"Error","Can not update TextInLanguage");
                return false;
            }
        }
    }
    return true;
}

bool LoadTextInLanguageFromDB(const QSqlDatabase &dbase ,int TextClass ,int IndexAutoCount,TextContainer &TextCode)
{
    QStringListListCSV CSV;
    if(CSV.LoadFromCSVFile(LanguageListFileName)==true){

        for(int i=0;i<CSV.GetRowCount();i++){
            QString CountryCode  =CSV.Get(0, i).left(2);
            TextList *t;
            for(t=TextCode.GetFirst();t!=NULL;t=t->GetNext()){
                if(t->CountryCode==CountryCode){
                    t->CountryName  =CSV.Get(1, i);
                    t->JPCountryStr =CSV.Get(2, i);
                    t->MainCurrencyCode =CSV.Get(3, i);
                    break;
                }
            }
            if(t==NULL){
                t=new TextList;
                t->CountryCode  =CSV.Get(0, i).left(2);
                t->CountryName  =CSV.Get(1, i);
                t->JPCountryStr =CSV.Get(2, i);
                t->MainCurrencyCode =CSV.Get(3, i);
                TextCode.AppendList(t);
            }
        }

	    QString	S=QString(/**/"SELECT country,textStr FROM RegSpector.TextInLanguage ")
                 +QString(/**/"where textClass=")+QString::number(TextClass)
                 +QString(/**/" and indexAutoCount=")+QString::number(IndexAutoCount);

	    QSqlQuery query(S ,dbase);
	    if(query.next ()==true){
            do{
                QString Country =query.record().value(/**/"country").toString();
                QString TextStr =query.record().value(/**/"textStr").toByteArray();

                for(TextList *t=TextCode.GetFirst();t!=NULL;t=t->GetNext()){
                    if(t->CountryCode==Country){
                        t->TextStr  =TextStr;
                        break;
                    }
                }
            }while(query.next ()==true);
        }
        return true;
    }
    return false;
}