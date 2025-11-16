#include "PanelResolutionSizeForm.h"
#include "ui_PanelResolutionSizeForm.h"
#include "XParamGlobal.h"
#include "XDataInLayer.h"
#include "XGeneralFunc.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

PanelResolutionSizeForm::PanelResolutionSizeForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::PanelResolutionSizeForm)
{
    ui->setupUi(this);
    Unit=/**/"micrometer";
}

PanelResolutionSizeForm::~PanelResolutionSizeForm()
{
    delete ui;
}

void	PanelResolutionSizeForm::Prepare(void)
{
    if(Unit==/**/"micrometer"){
        ui->doubleSpinBoxResolutionX->setValue(GetParamGlobal()->ResolutionXNano/1000.0);
        ui->doubleSpinBoxResolutionY->setValue(GetParamGlobal()->ResolutionYNano/1000.0);
        ui->labelUnitX->setText(/**/"um");
        ui->labelUnitY->setText(/**/"um");
    }
    else
    if(Unit==/**/"milimeter"){
        ui->doubleSpinBoxResolutionX->setValue(GetParamGlobal()->ResolutionXNano/1000000.0);
        ui->doubleSpinBoxResolutionY->setValue(GetParamGlobal()->ResolutionYNano/1000000.0);
        ui->labelUnitX->setText(/**/"mm");
        ui->labelUnitY->setText(/**/"mm");
    }

    ui->doubleSpinBoxResolutionX->setDecimals(GetParamGlobal()->SmallNumberFigure);
    ui->doubleSpinBoxResolutionY->setDecimals(GetParamGlobal()->SmallNumberFigure);

    ui->spinBoxXLen->setValue(GetDotPerLine(0));
    ui->spinBoxYLen->setValue(GetMaxLines(0));
}

void PanelResolutionSizeForm::on_pushButtonSet_clicked()
{
	for(int page=0;page<GetPageNumb();page++){
		int	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),page);
		GUICmdResolutionSize	RCmd(GetLayersBase(),sRoot,sName,globalPage);


        if(Unit==/**/"micrometer"){
            RCmd.ResolutionXNano=ui->doubleSpinBoxResolutionX->value()*1000.0;
            RCmd.ResolutionYNano=ui->doubleSpinBoxResolutionY->value()*1000.0;
        }
        else
        if(Unit==/**/"milimeter"){
            RCmd.ResolutionXNano=ui->doubleSpinBoxResolutionX->value()*1000000.0;
            RCmd.ResolutionYNano=ui->doubleSpinBoxResolutionY->value()*1000000.0;
        }

        RCmd.XLen=ui->spinBoxXLen->value();
        RCmd.YLen=ui->spinBoxYLen->value();
    	RCmd.Send(NULL,globalPage,0);
    }
}

//============================================================================================

GUICmdResolutionSize::GUICmdResolutionSize(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdResolutionSize::Load(QIODevice *f)
{
    if(::Load(f,ResolutionXNano)==false)    return false;
    if(::Load(f,ResolutionYNano)==false)    return false;
    if(::Load(f,XLen)==false)               return false;
    if(::Load(f,YLen)==false)               return false;
    return true;
}
bool	GUICmdResolutionSize::Save(QIODevice *f)
{
    if(::Save(f,ResolutionXNano)==false)    return false;
    if(::Save(f,ResolutionYNano)==false)    return false;
    if(::Save(f,XLen)==false)               return false;
    if(::Save(f,YLen)==false)               return false;
    return true;
}

void	GUICmdResolutionSize::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
    if(localPage==0){
        GetParamGlobal()->ResolutionXNano=ResolutionXNano;
        GetParamGlobal()->ResolutionYNano=ResolutionYNano;
        GetLayersBase()->ReallocXYPixels(XLen,YLen);
    }
}
