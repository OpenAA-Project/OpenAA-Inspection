#include "AutoReStart.h"
#include "SettingParamDialog.h"
#include <QFile>
#include <QDir>
#include <QProcess>

bool	Save(QIODevice *file,const QString &d)
{
	int	Len=d.length()*2;
	if(file->write((const char *)&Len,sizeof(Len))!=sizeof(Len)){
		return(false);
	}
	if(file->write((const char *)d.constData(),Len)!=Len){
		return(false);
	}
	return(true);
}
bool	Save(QIODevice *f,int d)
{
	if(f->write((const char *)&d,sizeof(d))!=sizeof(d)){
		return false;
	}
	return true;
}

bool	Load(QIODevice *f,int &d)
{
	if(f->read((char *)&d,sizeof(d))!=sizeof(d)){
		return false;
	}
	return true;
}
bool	Load(QIODevice *file,QString &d)
{
	int	Len=0;
	if(file->read((char *)&Len,sizeof(Len))!=sizeof(Len)){
		return(false);
	}
	
	char	LocalBuff[2000];
	char	*Buff;
	if((Len+1)>=2000){
		Buff=new char[Len+10];
	}
	else{
		Buff=LocalBuff;
	}
	if(file->read((char *)Buff,Len)!=Len){
		if(Buff!=LocalBuff){
			delete	[]Buff;
		}
		return(false);
	}
	Buff[Len]=0;
	d=/**/"";
	QChar *p=(QChar *)Buff;
	for(int i=0;i<Len;i+=2,p++){ 
		d+=*p;
	}
	if(Buff!=LocalBuff){
		delete	[]Buff;
	}
	return(true);
}

//===========================================================


AutoReStartParam::AutoReStartParam()
{
    ExeFileName =/**/"xxx.exe";
    WorkingPath =/**/"";
    Parameter   =/**/"";
    WaitingSecond   =30;
}
AutoReStartParam::~AutoReStartParam()
{
}

bool    AutoReStartParam::Save(QIODevice *f)
{
	if(::Save(f,ExeFileName		)==false)	return false;
	if(::Save(f,WorkingPath		)==false)	return false;
	if(::Save(f,Parameter		)==false)	return false;
	if(::Save(f,WaitingSecond	)==false)	return false;
	return true;
}
bool    AutoReStartParam::Load(QIODevice *f)
{
	if(::Load(f,ExeFileName		)==false)	return false;
	if(::Load(f,WorkingPath		)==false)	return false;
	if(::Load(f,Parameter		)==false)	return false;
	if(::Load(f,WaitingSecond	)==false)	return false;
	return true;
}

//=====================================================

const	QString		DefaultParamFileName=/**/"AutoReStart.dat";


AutoReStart::AutoReStart(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    StopMode    =false;

    QFile   File(DefaultParamFileName);
    if(File.open(QIODevice::ReadOnly)==true){
        ParamData.Load(&File);
    }
    ui.dialLoop->setMaximum(ParamData.WaitingSecond);
    ui.dialLoop->setValue(0);

    TM.setInterval(1000);
    TM.setSingleShot(false);
    connect(&TM,SIGNAL(timeout()),this,SLOT(SlotDialTick()));
    TM.start();
}

AutoReStart::~AutoReStart()
{}

void AutoReStart::SlotDialTick()
{
    if(StopMode==false){
        int v=ui.dialLoop->value()+1;
        if(ui.dialLoop->maximum()<=v){
            v=0;
            on_pushButtonStart_clicked();
        }
        ui.dialLoop->setValue(v);
    }
}

void AutoReStart::on_pushButtonStart_clicked()
{
	QDir::setCurrent (ParamData.WorkingPath);
	
	if(ParamData.Parameter.isEmpty()==true)
		QProcess::execute ( ParamData.ExeFileName);
	else
		QProcess::execute ( ParamData.ExeFileName+QString(" ")+ParamData.Parameter);
}


void AutoReStart::on_toolButtonStop_triggered(QAction *arg1)
{
    StopMode=ui.toolButtonStop->isChecked();
}


void AutoReStart::on_pushButtonParam_clicked()
{
    SettingParamDialog  D(this);
    StopMode=true;
    if(D.exec()==true){
		QFile   File(DefaultParamFileName);
		if(File.open(QIODevice::WriteOnly)==true){
			ParamData.Save(&File);
		}
    }
    StopMode=ui.toolButtonStop->isChecked();
}

