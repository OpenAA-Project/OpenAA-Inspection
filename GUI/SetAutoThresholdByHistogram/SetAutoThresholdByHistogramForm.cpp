#include "SetAutoThresholdByHistogramForm.h"
#include "ui_SetAutoThresholdByHistogramForm.h"
#include "SetAutoThresholdByHistogram.h"
#include "XGeneralFunc.h"
#include "SettingDialogAuto.h"
#include "XDataAlgorithmList.h"

extern  const	char	*sRoot;
extern  const	char	*sName;

SetAutoThresholdByHistogramForm::SetAutoThresholdByHistogramForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::SetAutoThresholdByHistogramForm)
{
    ui->setupUi(this);

    LibType =-1;
    LibID   =-1;
    Strength=50;
}

SetAutoThresholdByHistogramForm::~SetAutoThresholdByHistogramForm()
{
    delete ui;
}

void	SetAutoThresholdByHistogramForm::ReadyParam(void)
{
	ui->horizontalSliderStrength->setValue(Strength);
	ui->toolButton              ->setText(ButtonName);
}

void	SetAutoThresholdByHistogramForm::BuildForShow(void)
{
    if(GetParamGlobal()->MakeHistgramData==true){
        setEnabled(true);
    }
    else{
        setEnabled(false);
	}
}

bool	SetAutoThresholdByHistogramForm::SaveContent(QIODevice *f)
{
	int32	Ver = 1;

    if(::Save(f,Ver)==false)        return false;
    
    if(::Save(f,LibType)==false)    return false;
    if(::Save(f,LibID)==false)      return false;
    if(HistID.Save(f)==false)       return false;
    if(::Save(f,Strength)==false)   return false;
    if(::Save(f,ButtonName)==false) return false;
	return true;
}

bool	SetAutoThresholdByHistogramForm::LoadContent(QIODevice *f)
{
	int32	Ver;

    if(::Load(f,Ver)==false)        return false;
    
    if(::Load(f,LibType)==false)    return false;
    if(::Load(f,LibID)==false)      return false;
    if(HistID.Load(f)==false)       return false;
    if(::Load(f,Strength)==false)   return false;
    if(::Load(f,ButtonName)==false) return false;

    ui->toolButton  ->setText(ButtonName);
    ShowStrength();
    ShowSlider();
	return true;
}

void SetAutoThresholdByHistogramForm::on_horizontalSliderStrength_valueChanged(int value)
{
	int v = ui->horizontalSliderStrength->value();
	Strength = v;
	ShowStrength();
	UpdateThresholdByHistogram();
}

void    SetAutoThresholdByHistogramForm::UpdateThresholdByHistogram(void)
{
	for(int page = 0;page<GetLayersBase()->GetPageNumb();page++){
		int GlobalPage = GetLayersBase()->GetGlobalPageFromLocal(page);
        GUICmdSetAutoThresholdByHistogram   RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		RCmd.LibType = LibType;
		RCmd.LibID = LibID;
		RCmd.HistID = HistID;
		RCmd.Strength = Strength;
		RCmd.Send(NULL,GlobalPage,0);
    }
}

void    SetAutoThresholdByHistogramForm::ShowStrength(void)
{
    ui->labelValue->setText(QString::asprintf("%.1f%%",Strength/((double)ui->horizontalSliderStrength->maximum())*100.0));
}
void    SetAutoThresholdByHistogramForm::ShowSlider(void)
{
    ui->horizontalSliderStrength->setValue(Strength);
}

void	SetAutoThresholdByHistogramForm::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdUpdateThresholdByHistogram *CmdUpdateThresholdByHistogramVar = dynamic_cast<CmdUpdateThresholdByHistogram *>(packet);
    if(CmdUpdateThresholdByHistogramVar!=NULL){
        UpdateThresholdByHistogram();
        return;
    }
}

void SetAutoThresholdByHistogramForm::on_toolButton_clicked()
{
	SettingDialogAuto   D(this);
    if(D.exec()==true){
        LibType     =D.LibType     ;
        LibID       =D.LibID       ;
        HistID      =D.HistID      ;
        Strength    =D.Strength    ;
	    ButtonName  =D.ButtonName  ;
        ui->toolButton  ->setText(ButtonName);
        ShowStrength();
    }
}
//======================================================================

GUICmdSetAutoThresholdByHistogram::GUICmdSetAutoThresholdByHistogram(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSetAutoThresholdByHistogram::Load(QIODevice *f)
{
	if(::Load(f,LibType)==false)	return false;
	if(::Load(f,LibID)==false)		return false;
	if(HistID.Load(f)==false)		return false;
	if(::Load(f,Strength)==false)	return false;

	return(true);
}
bool	GUICmdSetAutoThresholdByHistogram::Save(QIODevice *f)
{
	if(::Save(f,LibType)==false)	return false;
	if(::Save(f,LibID)==false)		return false;
	if(HistID.Save(f)==false)		return false;
	if(::Save(f,Strength)==false)	return false;

	return(true);
}

void	GUICmdSetAutoThresholdByHistogram::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase *ABase = GetLayersBase()->GetAlgorithmBase(LibType);
    if(ABase!=NULL){
		AlgorithmLibraryContainer *LibCon = ABase->GetLibraryContainer();  
		AlgorithmInPageRoot *Ap = ABase->GetPageData(localPage);
		if(Ap!=NULL){
            IntList LibIDs;
			LibIDs.Add(LibID);
            AlgorithmItemPointerListContainer   ItemPointers;
            Ap->EnumItemsByLib(LibIDs ,ItemPointers);
            for(AlgorithmItemPointerList *al=ItemPointers.GetFirst();al!=NULL;al=al->GetNext()){
                AlgorithmItemRoot *Item = al->GetItem();
                if(Item!=NULL){
                    AlgorithmThreshold  *AThr=Item->GetThresholdBaseWritable();
                    for(IntClass *v=HistID.GetFirst();v!=NULL;v=v->GetNext()){
                        AThr->SetAutoThresholdByHistogram(v->GetValue(), Strength/100.0);
					}
                }
			}
        }
	}
}
