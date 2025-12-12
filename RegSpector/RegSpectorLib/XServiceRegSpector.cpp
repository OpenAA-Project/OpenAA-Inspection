#include <QStringList>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QSettings>
#include <QTextCodec>
#include "XServiceRegSpector.h"
#include "XCSV.h"
#include <math.h>

bool	InitialRegSpectorDatabase(QSqlDatabase &database)
{
	QSettings settings("RegSpector.ini", QSettings::IniFormat);
	settings.setIniCodec(QTextCodec::codecForName("UTF-8"));

	settings.beginGroup("Database");
	QString	HostName		=settings.value("HostName"		, "192.168.86.136").toString();
	int		Port			=settings.value("Port"			, 3306).toInt();
	QString	DatabaseName	=settings.value("DatabaseName"	, "RegSpector").toString();
	QString	UserName		=settings.value("UserName"		, "sample_user").toString();
	QString	LoginPassword	=settings.value("LoginPassword"	, "").toString();
	
	settings.setValue("HostName"		, HostName);
	settings.setValue("Port"			, Port);
	settings.setValue("DatabaseName"	, DatabaseName);
	settings.setValue("UserName"		, UserName);
	settings.setValue("LoginPassword"	, LoginPassword);
	
	settings.endGroup();

	QStringList Drv=QSqlDatabase::drivers();

	database = QSqlDatabase::addDatabase("QMYSQL");
    database.setHostName(HostName);
	database.setPort(Port);
    database.setDatabaseName(DatabaseName);
    database.setUserName(UserName);
    database.setPassword(LoginPassword);

	if(database.isOpen()==false){
		database.open();
	}
	if(database.isOpen()==true){
		return true;
	}
	QString error=database.lastError().text();
	return false;
}

//===============================================================================

TextList::TextList(const TextList &src)
{
    CountryCode =src.CountryCode ;
    CountryName =src.CountryName ;
    JPCountryStr=src.JPCountryStr;
    TextStr     =src.TextStr     ;
    MainCurrencyCode    =src.MainCurrencyCode;
}

TextList   &TextList::operator=(const TextList &src)
{
    CountryCode =src.CountryCode ;
    CountryName =src.CountryName ;
    JPCountryStr=src.JPCountryStr;
    TextStr     =src.TextStr     ;
    MainCurrencyCode    =src.MainCurrencyCode;
    return *this;
}

TextContainer::TextContainer(void)
{
}
bool    TextContainer::LoadFromCSV(const QString &FileName)
{
    RemoveAll();
    QStringListListCSV CSV;
    if(CSV.LoadFromCSVFile(FileName)==true){
        for(int i=0;i<CSV.GetRowCount();i++){
            QString CountryCode  =CSV.Get(0, i).left(2);
            TextList *t=new TextList;
            t->CountryCode  =CSV.Get(0, i).left(2);
            t->CountryName  =CSV.Get(1, i);
            t->JPCountryStr =CSV.Get(2, i);
            t->MainCurrencyCode =CSV.Get(3, i);
            AppendList(t);
        }
        return true;
    }
    return false;
}
TextContainer::TextContainer(const TextContainer &src)
{
    for(TextList *t=src.GetFirst();t!=NULL;t=t->GetNext()){
        TextList    *d=new TextList;
        *d=*t;
        AppendList(d);
    }
}

TextContainer   &TextContainer::operator=(const TextContainer &src)
{
    RemoveAll();
    for(TextList *t=src.GetFirst();t!=NULL;t=t->GetNext()){
        TextList    *d=new TextList;
        *d=*t;
        AppendList(d);
    }
    return *this;
}

QString     TextContainer::Find(const QString &CountryCode)
{
    for(TextList *t=GetFirst();t!=NULL;t=t->GetNext()){
        if(t->CountryCode==CountryCode){
            return t->TextStr;
        }
    }
    return /**/"";
}
TextList   *TextContainer::FindTextList(const QString &CountryCode)
{
    for(TextList *t=GetFirst();t!=NULL;t=t->GetNext()){
        if(t->CountryCode==CountryCode){
            return t;
        }
    }
    return NULL;
}
QString     TextContainer::FindMainCurrencyCode(const QString &CountryCode)
{
    for(TextList *t=GetFirst();t!=NULL;t=t->GetNext()){
        if(t->CountryCode==CountryCode){
            return t->MainCurrencyCode;
        }
    }
    return /**/"USD";
}

//===============================================================================

PriceList::PriceList(const PriceList &src)
{
    CurrencyCode    =src.CurrencyCode    ;
    CurrencyMark    =src.CurrencyMark    ;
    CurrencyName    =src.CurrencyName    ;
    Head            =src.Head            ;
    PriceValue      =src.PriceValue      ;
}

PriceList   &PriceList::operator=(const PriceList &src)
{
    CurrencyCode    =src.CurrencyCode    ;
    CurrencyMark    =src.CurrencyMark    ;
    CurrencyName    =src.CurrencyName    ;
    Head            =src.Head            ;
    PriceValue      =src.PriceValue      ;
    return *this;
}

bool    PriceList::LoadFromDB(const QSqlDatabase &DBase ,int ApplicationAutoCount ,int PriceCode)
{
	QString	S=QString(/**/"SELECT priceValue FROM RegSpector.Price where applicationAutoCount=")+QString::number(ApplicationAutoCount)
             +QString(/**/" and  priceCode=")+QString::number(PriceCode)
             +QString(/**/" and  currency=\'")+CurrencyCode+QString("\'");
	QSqlQuery query(S ,DBase);
	if(query.next ()==true){
        PriceValue          =query.record().value(/**/"priceValue").toDouble();
        return true;
    }
    return false;
}
bool    PriceList::SaveToDB  (const QSqlDatabase &DBase ,int ApplicationAutoCount ,int PriceCode)
{
	QString	S=QString(/**/"SELECT priceValue FROM RegSpector.Price where applicationAutoCount=")+QString::number(ApplicationAutoCount)
             +QString(/**/" and  priceCode=")+QString::number(PriceCode)
             +QString(/**/" and  currency=")+CurrencyCode;
	QSqlQuery query(S ,DBase);
	if(query.next ()==true){
	    QSqlQuery queryUpdate(DBase);
	    queryUpdate.prepare("UPDATE RegSpector.Price SET "
                            "priceValue=:priceValue "
                            "WHERE  applicationAutoCount=")+QString::number(ApplicationAutoCount)
                            +QString(/**/" and  priceCode=")+QString::number(PriceCode)
                            +QString(/**/" and  currency=")+CurrencyCode;

	    queryUpdate.bindValue(0	, PriceValue	);
	    if(queryUpdate.exec()==true){
            return true;
        }
    }
    else{
	    QSqlQuery queryInsrt(DBase);
	    queryInsrt.prepare("INSERT INTO RegSpector.Price("
                            "applicationAutoCount,"
                            "priceCode,"
                            "currency,"
                            "priceValue) "
	    	            "VALUES("
                            ":applicationAutoCount,"
                            ":priceCode,"
                            ":currency,"
                            ":priceValue)");
        queryInsrt.bindValue(0	, ApplicationAutoCount	);
	    queryInsrt.bindValue(1	, PriceCode);
	    queryInsrt.bindValue(2	, CurrencyCode	);
        queryInsrt.bindValue(3	, PriceValue	);

	    if(queryInsrt.exec()==true){
            return true;
        }
    }
    return false;
}
QString PriceList::MakePriceStr(double priceValue)
{
    double  N=priceValue-floor(priceValue);
    if(N<0.001){
        int nPrice=floor(priceValue);
        if(Head==true){
            return CurrencyMark+QString(" ")+QString::number(nPrice);
        }
        else{
            return QString::number(nPrice)+QString(" ")+CurrencyMark;
        }
    }
    else{
        if(Head==true){
            return CurrencyMark+QString(" ")+QString::number(priceValue,'f',3);
        }
        else{
            return QString::number(priceValue,'f',3)+QString(" ")+CurrencyMark;
        }
    }
}

PriceContainer::PriceContainer(void)
{
}
PriceContainer::PriceContainer(const PriceContainer &src)
{
    for(PriceList *t=src.GetFirst();t!=NULL;t=t->GetNext()){
        PriceList    *d=new PriceList;
        *d=*t;
        AppendList(d);
    }
}
double  PriceContainer::FindPrice(const QString &CurrencyCode)
{
    for(PriceList *t=GetFirst();t!=NULL;t=t->GetNext()){
        if(t->CurrencyCode==CurrencyCode){
            return t->PriceValue;
        }
    }
    return 0.0;
}
   
PriceList   *PriceContainer::FindPriceList(const QString &CurrencyCode)
{
    for(PriceList *t=GetFirst();t!=NULL;t=t->GetNext()){
        if(t->CurrencyCode==CurrencyCode){
            return t;
        }
    }
    return NULL;
}

PriceContainer   &PriceContainer::operator=(const PriceContainer &src)
{
    RemoveAll();
    for(PriceList *t=src.GetFirst();t!=NULL;t=t->GetNext()){
        PriceList    *d=new PriceList;
        *d=*t;
        AppendList(d);
    }
    return *this;
}
    
bool    PriceContainer::LoadFromDB(const QSqlDatabase &DBase ,int ApplicationAutoCount ,int PriceCode)
{
    QStringListListCSV CSV;
    if(CSV.LoadFromCSVFile(CurrencyListFileName)==true){
        int RowCount=CSV.GetRowCount();
        for(int row=0;row<RowCount;row++){
            QString Code=CSV.Get(0, row).left(3);
            PriceList *t;
            for(t=GetFirst();t!=NULL;t=t->GetNext()){
                if(t->CurrencyCode==Code){
                    t->CurrencyMark =CSV.Get(1, row);
                    t->CurrencyName =CSV.Get(2, row);
                    t->Head         =(CSV.Get(4, row)=='F')?true:false;
                    break;
                }
            }
            if(t==NULL){
                t=new PriceList;
                t->CurrencyCode=Code;
                t->CurrencyMark =CSV.Get(1, row);
                t->CurrencyName =CSV.Get(2, row);
                t->Head         =(CSV.Get(4, row)=='F')?true:false;
                AppendList(t);
            }
        }
    }
     for(PriceList *t=GetFirst();t!=NULL;t=t->GetNext()){
         t->LoadFromDB(DBase ,ApplicationAutoCount ,PriceCode);
     }
     return true;
}

bool    PriceContainer::SaveToDB  (const QSqlDatabase &DBase ,int ApplicationAutoCount ,int PriceCode)
{
     for(PriceList *t=GetFirst();t!=NULL;t=t->GetNext()){
         if(t->SaveToDB(DBase ,ApplicationAutoCount ,PriceCode)==false){
             return false;
         }
     }
     return true;
}

bool    PriceContainer::LoadFromCSV(const QString &FileName)
{
    RemoveAll();
    QStringListListCSV CSV;
    if(CSV.LoadFromCSVFile(FileName)==true){
        int RowCount=CSV.GetRowCount();
        for(int row=0;row<RowCount;row++){
            QString Code=CSV.Get(0, row).left(3);
            PriceList *t=new PriceList;
            t->CurrencyCode=Code;
            t->CurrencyMark =CSV.Get(1, row);
            t->CurrencyName =CSV.Get(2, row);
            t->Head         =(CSV.Get(4, row)=='F')?true:false;
            AppendList(t);
        }
        return true;
    }
    return false;
}

#include <boost/multiprecision/cpp_int.hpp>

using namespace boost::multiprecision;

static  const   char    *YCodeStr="56wxy$%789AQRz+#SUVefghijk12HIJKL=*?WXYZac34v&CEFqrsu0G/-";
QByteArray  ConvDat2YCode(const QByteArray &d)
{
    int Len=strlen(YCodeStr);
    int N=d.length();
    cpp_int u=0;
    std::string s;
    for(int i=0;i<N;i++){
        u *=256;
        unsigned char    k=d.data()[i];
        u+=(int)k;
    }
    s=u.str();

    cpp_int H=1;
    int     L=0;
    for(int i=0;L<999;i++,L++){
        if(H>=u){
            H/=Len;
            break;
        }
        H*=Len;
    }
    char    Buff[1000];
    for(int i=0;i<L;i++){
        cpp_int a=u/H;
        int am=(int)a;
        Buff[i]=YCodeStr[am];
        u=u-H*a;
        H/=Len;
    }
    Buff[L]=0;
    QByteArray  ret(Buff,L);
    return ret;
}

QByteArray  ConvYCode2Dat(const QByteArray &d)
{
    int Len=strlen(YCodeStr);
    int N=d.length();
    cpp_int u=0;
    std::string s;
    for(int i=0;i<N;i++){
        u *=Len;
        unsigned char    k=d.data()[i];
        const   char    *fp=strchr(YCodeStr,k);
        if(fp==NULL){
            return QByteArray();
        }
        u+=(int)(fp-YCodeStr);
    }
    s=u.str();

    cpp_int H=1;
    int     L=0;
    for(int i=0;L<999;i++,L++){
        if(H>=u){
            H/=256;
            break;
        }
        H*=256;
    }
    char    Buff[1000];
    for(int i=0;i<L;i++){
        cpp_int a=u/H;
        int am=(int)a;
        Buff[i]=am;
        u=u-H*a;
        H/=256;
    }
    Buff[L]=0;
    QByteArray  ret(Buff,L);
    return ret;
}

static  const char    *TxtCodeStr="56wxy789AQRzSUVefghijk12HIJKLWXYZac34vCEFqrsu0G";
QByteArray  ConvDat2TxtCode(const QByteArray &d)
{
    int Len=strlen(TxtCodeStr);
    int N=d.length();
    cpp_int u=0;
    std::string s;
    for(int i=0;i<N;i++){
        u *=256;
        unsigned char    k=d.data()[i];
        u+=(int)k;
    }
    s=u.str();

    cpp_int H=1;
    int     L=0;
    for(int i=0;L<999;i++,L++){
        if(H>=u){
            H/=Len;
            break;
        }
        H*=Len;
    }
    char    Buff[1000];
    for(int i=0;i<L;i++){
        cpp_int a=u/H;
        int am=(int)a;
        Buff[i]=TxtCodeStr[am];
        u=u-H*a;
        H/=Len;
    }
    Buff[L]=0;
    QByteArray  ret(Buff,L);
    return ret;
}

QByteArray  ConvTxtCode2Dat(const QByteArray &d)
{
    int Len=strlen(TxtCodeStr);
    int N=d.length();
    cpp_int u=0;
    std::string s;
    for(int i=0;i<N;i++){
        u *=Len;
        unsigned char    k=d.data()[i];
        const   char    *fp=strchr(TxtCodeStr,k);
        if(fp==NULL){
            return QByteArray();
        }
        u+=(int)(fp-TxtCodeStr);
    }
    s=u.str();

    cpp_int H=1;
    int     L=0;
    for(int i=0;L<999;i++,L++){
        if(H>=u){
            H/=256;
            break;
        }
        H*=256;
    }
    char    Buff[1000];
    for(int i=0;i<L;i++){
        cpp_int a=u/H;
        int am=(int)a;
        Buff[i]=am;
        u=u-H*a;
        H/=256;
    }
    Buff[L]=0;
    QByteArray  ret(Buff,L);
    return ret;
}
