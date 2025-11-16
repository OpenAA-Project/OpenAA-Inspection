#include "CheckInstall.h"

CheckInstall::CheckInstall(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    Thread=NULL;
}
   
void    CheckInstall::StartThread(void)
{
    Thread=new CheckInstall(this);
    Thread->start();
}
    
void    CheckInstall::StopThread(void)
{
    if(Thread!=NULL){
        Thread->SetTerminate(true);
        Thread->wait(5000);
        delete  Thread;
        Thread=NULL;
    }
}

//===========================================
CheckThread::CheckThread(CheckInstall *p)
    :QThread(p),Parent(p)
{
    Terminated=false;
}
CheckThread::~CheckThread(void)
{
}

void    CheckThread::SetTerminate(bool b)
{
    Terminated=true;
}

void    CheckThread::run()
{
}

