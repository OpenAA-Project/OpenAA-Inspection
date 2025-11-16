#include "SetThresholdByHistogramResource.h"
#include "SetThresholdDialog.h"
#include "ui_SetThresholdDialog.h"
#include "XAlgorithmBase.h"
#include "XDataInLayer.h"
#include "XDataAlgorithm.h"
#include "XGeneralFunc.h"
#include "ShowThresholdHistgramForm.h"
#include "XGeneralDialog.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

bool	AlgoHistList::Save(QIODevice *f)
{
	if(::Save(f,Use)==false)
		return false;
	if(::Save(f,HistID)==false)
		return false;
	if(::Save(f,HistName)==false)
		return false;
	return true;
}
bool	AlgoHistList::Load(QIODevice *f)
{
	if(::Load(f,Use)==false)
		return false;
	if(::Load(f,HistID)==false)
		return false;
	if(::Load(f,HistName)==false)
		return false;
	return true;
}


void	AlgorithmListContainerForHistgram::Merge(const QString &AlgoRoot ,const QString &AlgoName ,IntStringContainer &src)
{
	AlgorithmListForHistgram *a;
	for(a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->AlgoRoot==AlgoRoot && a->AlgoName==AlgoName){
			break;
		}
	}
	if(a==NULL){
		a=new AlgorithmListForHistgram();
		a->AlgoRoot=AlgoRoot;
		a->AlgoName=AlgoName;
		AppendList(a);
	}
	if(a!=NULL){
		for(IntStringList *s=src.GetFirst();s!=NULL;s=s->GetNext()){
			AlgoHistList *t;
			for(t=a->AlgoHistData.GetFirst();t!=NULL;t=t->GetNext()){
				if(t->HistID==s->Data){
					break;
				}
			}
			if(t==NULL){
				t=new AlgoHistList();
				t->HistID=s->Data;
				t->HistName=s->Str;
				a->AlgoHistData.AppendList(t);
			}
		}
	}
}

bool	AlgorithmListForHistgram::Save(QIODevice *f)
{
	if(::Save(f,Use)==false)
		return false;
	if(::Save(f,AlgoRoot)==false)
		return false;
	if(::Save(f,AlgoName)==false)
		return false;
	if(AlgoHistData.Save(f)==false)
		return false;
	return true;
}
bool	AlgorithmListForHistgram::Load(QIODevice *f)
{
	if(::Load(f,Use)==false)
		return false;
	if(::Load(f,AlgoRoot)==false)
		return false;
	if(::Load(f,AlgoName)==false)
		return false;
	if(AlgoHistData.Load(f)==false)
		return false;
	return true;
}

SetThresholdDialog::SetThresholdDialog(LayersBase *base ,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(base)
    ,ui(new Ui::SetThresholdDialog)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);

	ui->tableWidgetAlgorithm->setColumnWidth(0,32);
	ui->tableWidgetAlgorithm->setColumnWidth(1,220);

	ui->tableWidgetHistogram->setColumnWidth(0,32);
	ui->tableWidgetHistogram->setColumnWidth(1,220);

	ShowAlgoList();
	LastAlgo=-1;
	Thr=NULL;

	InstallOperationLog(this);
}

void SetThresholdDialog::ShowAlgoList(void)
{
	for(LogicDLL *DLL=GetLayersBase()->GetLogicDLLBase()->GetFirst();DLL!=NULL;DLL=DLL->GetNext()){		
		for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdReqEnumEffectiveHistgram	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
			GUICmdAckEnumEffectiveHistgram	ACmd(GetLayersBase(),sRoot,sName,GlobalPage);
			RCmd.AlgoRoot=DLL->GetDLLRoot();
			RCmd.AlgoName=DLL->GetDLLName();
			if(RCmd.Send(GlobalPage,0,ACmd)==true){
				AList.Merge(RCmd.AlgoRoot,RCmd.AlgoName,ACmd.HistData);
			}
		}
	}
	for(AlgorithmListForHistgram *s=AList.GetFirst();s!=NULL;){
		AlgorithmListForHistgram *d=s->GetNext();
		if(s->AlgoHistData.GetCount()==0){
			AList.RemoveList(s);
			delete	s;
		}
		s=d;
	}

	int	Row=0;
	ui->tableWidgetAlgorithm->setRowCount(AList.count());
	for(AlgorithmListForHistgram *s=AList.GetFirst();s!=NULL;s=s->GetNext(),Row++){
		::SetDataToTableCheckable(ui->tableWidgetAlgorithm ,0 ,Row ,/**/"" ,s->Use);
		::SetDataToTable		 (ui->tableWidgetAlgorithm ,1 ,Row ,s->AlgoRoot+QString(/**/" / ")+s->AlgoName);
	}

}

SetThresholdDialog::~SetThresholdDialog()
{
    delete ui;
	//if(Thr!=NULL)
	//	delete	Thr;
	//Thr=NULL;
}

void SetThresholdDialog::on_tableWidgetAlgorithm_clicked(const QModelIndex &index)
{
	if(LastAlgo>0){
		FromWindow(LastAlgo);
	}
	int	Row=ui->tableWidgetAlgorithm->currentRow();
	if(Row<0)
		return;
	LastAlgo=Row;
	ToWindow(Row);
}

void SetThresholdDialog::FromWindow(int AlgoNo)
{
	AlgorithmListForHistgram *s=AList[AlgoNo];
	int	Row=0;
	for(AlgoHistList *a=s->AlgoHistData.GetFirst();a!=NULL;a=a->GetNext()){
		a->Use=::GetCheckedFromTable(ui->tableWidgetHistogram ,0 ,Row);
		Row++;
	}
}

void SetThresholdDialog::ToWindow(int AlgoNo)
{
	AlgorithmListForHistgram *s=AList[AlgoNo];
	ui->tableWidgetHistogram->setRowCount(s->AlgoHistData.GetCount());
	int	Row=0;
	for(AlgoHistList *a=s->AlgoHistData.GetFirst();a!=NULL;a=a->GetNext()){
		::SetDataToTableCheckable(ui->tableWidgetHistogram ,0 ,Row ,/**/"" ,a->Use);
		::SetDataToTable		 (ui->tableWidgetHistogram ,1 ,Row ,a->HistName);
		Row++;
	}
}

void SetThresholdDialog::on_pushButtonSet_clicked()
{
	if(LastAlgo>0){
		FromWindow(LastAlgo);
	}
	int	Row=0;
	for(AlgorithmListForHistgram *s=AList.GetFirst();s!=NULL;s=s->GetNext(),Row++){
		s->Use=::GetCheckedFromTable(ui->tableWidgetAlgorithm ,0 ,Row);
	}
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdReqExecuteAutoThreshold	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		RCmd.AdoptRate		=ui->doubleSpinBoxAdoptRate->value()/100.0;
		RCmd.SigmaMultiply	=ui->doubleSpinBoxSigmaMultiply->value();
		RCmd.ModeOneWork	=ui->checkBoxModeOneWork	->isChecked();
		RCmd.ModeMultiWork	=ui->checkBoxModeMultiWork	->isChecked();
		RCmd.AList			=AList;
		RCmd.Send(NULL,GlobalPage,0);
	}
	close();
}

void SetThresholdDialog::on_pushButtonCancel_clicked()
{
	close();
}


void SetThresholdDialog::on_checkBoxCheckAllAlgorithm_clicked()
{
	if(ui->checkBoxCheckAllAlgorithm->isChecked()==true){
		for(AlgorithmListForHistgram *s=AList.GetFirst();s!=NULL;s=s->GetNext()){
			s->Use=true;
		}
	}
	else{
		for(AlgorithmListForHistgram *s=AList.GetFirst();s!=NULL;s=s->GetNext()){
			s->Use=false;
		}
	}
	ShowAlgoList();
}

void SetThresholdDialog::on_checkBoxCheckAllHistogram_clicked()
{
	int	AlgoNo=ui->tableWidgetAlgorithm->currentRow();
	if(AlgoNo<0)
		return;
	AlgorithmListForHistgram *s=AList[AlgoNo];
	if(ui->checkBoxCheckAllHistogram->isChecked()==true){
		for(AlgoHistList *a=s->AlgoHistData.GetFirst();a!=NULL;a=a->GetNext()){
			a->Use=true;
		}
	}
	else{
		for(AlgoHistList *a=s->AlgoHistData.GetFirst();a!=NULL;a=a->GetNext()){
			a->Use=false;
		}
	}
	ToWindow(AlgoNo);
}


void SetThresholdDialog::on_tableWidgetHistogram_doubleClicked(const QModelIndex &index)
{
	int	AlgoNo=ui->tableWidgetAlgorithm->currentRow();
	if(AlgoNo<0)
		return;
	AlgorithmListForHistgram *s=AList[AlgoNo];
	if(s==NULL)
		return;

	int	HistNo=ui->tableWidgetHistogram->currentRow();
	if(HistNo<0)
		return;
	AlgoHistList *a=s->AlgoHistData[HistNo];
	if(a==NULL)
		return;

	int	Phase		;
	int	GlobalPage	;
	int	Layer		;
	if(ExeSelectPhasePageLayerDialog(GetLayersBase()
									,Phase		
									,GlobalPage	
									,Layer		)==true){
		Thr=new ShowThresholdHistgramForm(GetLayersBase());
		if(Thr->Initial(Phase ,GlobalPage ,Layer  ,a->HistID
											,s->AlgoRoot ,s->AlgoName )==true){
			GeneralDialog	gD(GetLayersBase(),Thr,NULL,false);
			//Thr->show();
			gD.exec();
		}
		else{
			delete	Thr;
			Thr=NULL;
		}
	}
}

//========================================================================================================

bool	IntStringList::Save(QIODevice *f)
{
	if(::Save(f,Data)==false)
		return false;
	if(::Save(f,Str)==false)
		return false;
	return true;
}

bool	IntStringList::Load(QIODevice *f)
{
	if(::Load(f,Data)==false)
		return false;
	if(::Load(f,Str)==false)
		return false;
	return true;
}

GUICmdReqEnumEffectiveHistgram::GUICmdReqEnumEffectiveHistgram(LayersBase *base,const QString &EmitterRoot ,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdReqEnumEffectiveHistgram::Load(QIODevice *f)
{
	if(::Load(f,AlgoRoot)==false)
		return false;
	if(::Load(f,AlgoName)==false)
		return false;
	return true;
}
bool	GUICmdReqEnumEffectiveHistgram::Save(QIODevice *f)
{
	if(::Save(f,AlgoRoot)==false)
		return false;
	if(::Save(f,AlgoName)==false)
		return false;
	return true;
}

void	GUICmdReqEnumEffectiveHistgram::Receive(int32 localPage, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckEnumEffectiveHistgram	*SendBack=GetSendBack(GUICmdAckEnumEffectiveHistgram,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	AlgorithmBase	*Algo=GetLayersBase()->GetAlgorithmBase(AlgoRoot ,AlgoName);
	if(Algo!=NULL && localPage==0){
		AlgorithmBase::RegisteredHistgramListContainer	List;
		Algo->EnumHistgram(List);
		for(AlgorithmBase::RegisteredHistgramList *L=List.GetFirst();L!=NULL;L=L->GetNext()){
			IntStringList	*p=new IntStringList();
			p->Data=L->GetID();
			p->Str=L->GetName();
			SendBack->HistData.AppendList(p);
		}
	}

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}


GUICmdAckEnumEffectiveHistgram::GUICmdAckEnumEffectiveHistgram(LayersBase *base,const QString &EmitterRoot ,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdAckEnumEffectiveHistgram::Load(QIODevice *f)
{
	if(HistData.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdAckEnumEffectiveHistgram::Save(QIODevice *f)
{
	if(HistData.Save(f)==false)
		return false;
	return true;
}

//========================================================================================================
	
GUICmdReqExecuteAutoThreshold::GUICmdReqExecuteAutoThreshold(LayersBase *base,const QString &EmitterRoot ,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdReqExecuteAutoThreshold::Load(QIODevice *f)
{
	if(::Load(f,ModeOneWork)==false)
		return false;
	if(::Load(f,ModeMultiWork)==false)
		return false;
	if(::Load(f,AdoptRate)==false)
		return false;
	if(::Load(f,SigmaMultiply)==false)
		return false;
	if(AList.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdReqExecuteAutoThreshold::Save(QIODevice *f)
{
	if(::Save(f,ModeOneWork)==false)
		return false;
	if(::Save(f,ModeMultiWork)==false)
		return false;
	if(::Save(f,AdoptRate)==false)
		return false;
	if(::Save(f,SigmaMultiply)==false)
		return false;
	if(AList.Save(f)==false)
		return false;
	return true;
}

void	GUICmdReqExecuteAutoThreshold::Receive(int32 localPage, int cmd ,QString &EmitterRoot,QString &EmitterName)	
{
	for(AlgorithmListForHistgram *s=AList.GetFirst();s!=NULL;s=s->GetNext()){
		if(s->Use==false)
			continue;
		AlgorithmBase	*Algo=GetLayersBase()->GetAlgorithmBase(s->AlgoRoot ,s->AlgoName);
		if(Algo!=NULL){
			AlgorithmInPageRoot	*Ap=Algo->GetPageData(localPage);
			if(Ap!=NULL){
				for(AlgoHistList *a=s->AlgoHistData.GetFirst();a!=NULL;a=a->GetNext()){
					if(a->Use==false)
						continue;
					ParamAutoThreshold *H=Ap->CreateParamAutoThreshold();
					H->DirectThreshold=false;
					H->LibID		=-1;
					H->HistID		=a->HistID;
					H->AdoptRate	=AdoptRate;
					H->SigmaMultiply=SigmaMultiply;
					H->ModeOneWork	=ModeOneWork;
					H->ModeMultiWork=ModeMultiWork;
					Ap->ExecuteAutoThreshold(*H);
					delete	H;
				}
			}
		}
	}
}
