#include "EditRWParameter.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include <QFile>
#include <QDir>
#include <QFileDialog>
#include <QListWidget>
#include <QListWidgetItem>
#include "XDatabase.h"
#include "XDatabaseLoader.h"
#include "XDatabase.h"
#include "XDLLType.h"
#include "swap.h"
#include "mtTBarGraph.h"
#include "XDataInExe.h"
#include "XShadowControlInterface.h"
#include "XShadowTree.h"
#include "Regulus64System.h"
#include "XRegulusWorld.h"


EditRWParameter::EditRWParameter(LayersBase *base,QWidget *parent)
    : QMainWindow(parent)
    ,ServiceForLayers(base)
{
    ui.setupUi(this);
    //LangEPSolver.SetLanguage(base.GetLanguagePackageData(),LanguageCode);
    //LangEPSolver.SetUI(this);
    //LangSolverGUILib.SetLanguage(base.GetLanguagePackageData(),LanguageCode);

    ui.tabWidget->setCurrentIndex(0);
    RegulusWorld	*R=GetRegulusWorld(GetLayersBase());
    //--------------------------------------------------------------------

    WTab = new WEditParameterTab(R->GetParamRegulusWorld() ,-1,ui.frameRWParam);

    RWParamLoadedFileName=R->GetParamRegulusWorld()->GetSavedFileName();
    ui.lineEditGlobalParam->setText(RWParamLoadedFileName);
    QFile	F(RWParamLoadedFileName);
    if(F.open(QIODevice::ReadOnly)==true){
        if(WTab->Load(&F)==true){
            WTab->ShowToWindow();
        }
    }
    //--------------------------------------------------------------------
    WDeviceTab	=new EditRWDeviceParamForm(GetLayersBase(),ui.frameFormDevice);
    WDeviceTab->Show();
    
}

EditRWParameter::~EditRWParameter()
{
    delete	WTab;
    delete	WDeviceTab;
}

void EditRWParameter::on_SaveButton_clicked()
{
    QString	 fileName=GetLayersBase()->LGetSaveFileName (NULL, WTab->GetDataText(), QString(), QString(/**/"dat(*.dat);;AllFile(*.*)"));
    if(fileName.isEmpty()==false){
        QFile	F(fileName);
        if(F.open(QIODevice::WriteOnly)==true){
            WTab        ->LoadFromWindow();
            WDeviceTab  ->LoadFromWindow();
            WTab->Save(&F);
        }
    }
}


void EditRWParameter::on_UpdateDefaultButton_clicked()
{
    QFile	F(RWParamLoadedFileName);
    if(F.open(QIODevice::WriteOnly)==true){
        WTab        ->LoadFromWindow();
        WDeviceTab  ->LoadFromWindow();
        WTab->Save(&F);
    }
}


void EditRWParameter::on_LoadButton_clicked()
{
    QString	 fileName=GetLayersBase()->LGetOpenFileName(NULL, WTab->GetDataText(), QString(), QString(/**/"dat(*.dat);;AllFile(*.*)"));
    if(fileName.isEmpty()==false){
        RWParamLoadedFileName=fileName;

        QFile	F(RWParamLoadedFileName);
        if(F.open(QIODevice::ReadOnly)==true){
            WTab->Load(&F);
            WDeviceTab->Show();
        }
    }
}

void EditRWParameter::on_CancelButton_clicked()
{
    close();
}

void EditRWParameter::resizeEvent(QResizeEvent *e)
{
	ui.frameBottom->setGeometry(0,height()-ui.frameBottom->height(),width(),ui.frameBottom->height());
	ui.tabWidget->resize(width()-20,height()-10-ui.frameBottom->height());

	ui.frameRWParam->resize(ui.tabWidget->width()-20,ui.tabWidget->height()-20);
	WTab->resize(ui.frameRWParam->width(),ui.frameRWParam->height()-30);
}