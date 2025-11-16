#include "NickInspectionResource.h"
#include "ShowOperationalPanel.h"
#include "ui_ShowOperationalPanel.h"
#include "XDataInLayerCommander.h"
#include "XLibraryType.h"
#include "XGeneralFunc.h"
#include "swap.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

ShowOperationalPanel::ShowOperationalPanel(LayersBase *Base,QWidget *parent) :
    QWidget(parent),ServiceForLayers(Base)
	,PasswordInQWodget(Base,this)
    ,ui(new Ui::ShowOperationalPanel)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);

	IData=NULL;
	InstallOperationLog(this);
}

ShowOperationalPanel::~ShowOperationalPanel()
{
	if(IData!=NULL)
		delete	IData;
	IData=NULL;

    delete ui;
}

void	ShowOperationalPanel::Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data)
{
	AlgorithmLibraryContainerForEnum		LibList(InstBase->GetLayersBase());
	LibIDList.RemoveAll();
	LibList.EnumAllLibraries(GetLayersBase()->GetDatabase(),InstBase->GetLibType(),LibIDList);

	if(IData!=NULL)
		delete	IData;
	IData=new AlgorithmItemIndependentPack(InstBase->GetLayersBase());
	*IData=Data;

	CreateThreshld();
}

void	ShowOperationalPanel::CreateThreshld(void)
{
	IntList LayerList;
	//GetActiveLayerList(LayerList);
	//if(LayerList.GetFirst()==NULL)
	//	return;
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		//if(LayerList.GetFirst()->GetValue()!=D->Layer)
		//	continue;
		NickInspectionItem	*BData=dynamic_cast<NickInspectionItem *>(DA);
		if(BData==NULL)
			continue;
		GUICmdReqAlgorithmGeneralData	PacketReq(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		PacketReq.BuildData(sRoot,sName,NickInspectionReqThresholdReqCommand ,NickInspectionReqThresholdSendCommand);
		((NickInspectionThresholdReq *)PacketReq.Data)->GlobalPage	=D->GlobalPage;
		((NickInspectionThresholdReq *)PacketReq.Data)->Layer		=D->Layer;
		((NickInspectionThresholdReq *)PacketReq.Data)->ItemID	=DA->GetID();
		((NickInspectionThresholdReq *)PacketReq.Data)->Mastered=true;
		GUICmdSendAlgorithmGeneralData	PacketSend(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		if(PacketReq.Send(D->GlobalPage,0,PacketSend)==true){

			NickInspectionThresholdSend	*ThrePoint=(NickInspectionThresholdSend *)PacketSend.GetData();

			NGPercentage	=ThrePoint->NGPercentage;	
			RefBrightness	=ThrePoint->RefBrightness;	
			EnableWhite		=ThrePoint->EnableWhite	;	
			Result			=ThrePoint->Result;

			break;
		}
	}
	ShowLibrary();
}


void	ShowOperationalPanel::ShowLibrary(void)
{
	IntList LayerList;
	//GetActiveLayerList(LayerList);
	//if(LayerList.GetFirst()==NULL)
	//	return;
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		//if(LayerList.GetFirst()->GetValue()!=D->Layer)
		//	continue;
		NickInspectionItem	*BData=dynamic_cast<NickInspectionItem *>(DA);
		if(BData==NULL)
			continue;

		if(DA->GetLibID()<0){
			ui->EditLibID->setText(/**/"");
			ui->EditLibName->setText(/**/"");
		}
		else{
			ui->EditLibID	->setText(QString::number(DA->GetLibID()));
			ui->EditLibName->setText(/**/"");
			for(AlgorithmLibraryList *L=LibIDList.GetFirst();L!=NULL;L=L->GetNext()){
				if(L->GetLibID()==DA->GetLibID()){
					ui->EditLibName	->setText(L->GetLibName());
					break;
				}
			}
		}
			
		ui->spinBoxNGPercentage			->setValue	(BData->GetThresholdR(GetLayersBase())->NGPercentage	);
		ui->spinBoxRefBrightness		->setValue	(BData->GetThresholdR(GetLayersBase())->RefBrightness	);
		ui->checkBoxEnableWhite			->setChecked(BData->GetThresholdR(GetLayersBase())->EnableWhite	);

		ui->tableWidgetSelected->setRowCount(BData->GetThresholdR(GetLayersBase())->LibList.GetCount());
		int	row=0;
		for(AlgorithmLibraryListWithResult *a=BData->GetThresholdR(GetLayersBase())->LibList.GetFirst();a!=NULL;a=a->GetNext(),row++){
			LibraryTypeList	*LType=GetLayersBase()->GetInstalledLibType()->FindLibraryType(a->GetLibType());
			if(LType!=NULL){
				AlgorithmBase   *ABase=GetLayersBase()->GetAlgorithmBase(LType->GetLibType());
				if(ABase!=NULL){
					::SetDataToTable(ui->tableWidgetSelected,0,row ,ABase->GetNameByCurrentLanguage());
				}
				else{
					::SetDataToTable(ui->tableWidgetSelected,0,row ,LType->GetLibName());
				}
			}
			else{
				::SetDataToTable(ui->tableWidgetSelected,0,row ,LangSolver.GetString(ShowOperationalPanel_LS,LID_0)/*"Not registered"*/);
			}	
			::SetDataToTable(ui->tableWidgetSelected,1,row ,QString::number(a->GetLibID()));
			::SetDataToTable(ui->tableWidgetSelected,2,row ,a->GetLibName(GetLayersBase()));
			::SetDataToTable(ui->tableWidgetSelected,3,row ,a->GetResultOk()==true?"OK":LangSolver.GetString(ShowOperationalPanel_LS,LID_1)/*"NG"*/);
		}

		return;
	}
}
void	ShowOperationalPanel::GetDataFromWindow(void)
{
	IntList LayerList;
	//GetActiveLayerList(LayerList);
	//if(LayerList.GetFirst()==NULL)
	//	return;

	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		NickInspectionItem	*BData=dynamic_cast<NickInspectionItem *>(DA);
		if(BData==NULL)
			continue;
		NickInspectionThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
		Thr->NGPercentage	=ui->spinBoxNGPercentage	->value	();
		Thr->RefBrightness	=ui->spinBoxRefBrightness	->value	();
		Thr->EnableWhite	=ui->checkBoxEnableWhite	->isChecked();

		//return;
	}
}

void ShowOperationalPanel::on_ButtonRelrectOnlyBlock_clicked()
{
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm(LangSolver.GetString(ShowOperationalPanel_LS,LID_2)/*"Reflecting ONE block threshold"*/);

	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Reflect one block threshold");
	GetDataFromWindow();
	GUICmdSendAlgorithmItemIndependentPack	Packet(IData->Base,QString(/**/"ANY"),QString(/**/"ANY"),-1,true);
	Packet.Command=SetIndependentItemDataCommand_OnlyOne;
	Packet.IData=*IData;
	for(int page=0;page<GetPageNumb();page++){
		Packet.Send(NULL,page,0);
	}
	GetLayersBase()->WaitAllAcknowledged(60*10);
	GetLayersBase()->CloseProcessingForm();
}

void ShowOperationalPanel::on_ButtonSaveToLibrary_clicked()
{
	GetDataFromWindow();

	IntList LayerList;
	//GetActiveLayerList(LayerList);
	//if(LayerList.GetFirst()==NULL)
	//	return;
	int	ThresholdLevel=GetLayersBase()->SelectThresholdLevel();
	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		NickInspectionItem	*BData=dynamic_cast<NickInspectionItem *>(DA);
		if(BData==NULL)
			continue;

		int	LibID=BData->GetLibID();
		AlgorithmLibraryContainer	*Container=BData->GetLibraryContainer();
		AlgorithmLibraryLevelContainer	DestLib(Container);
		if(BData->GetLibraryContainer()->GetLibrary(LibID ,DestLib)==true){
			NickInspectionLibrary	*ALib=dynamic_cast<NickInspectionLibrary *>(DestLib.GetLibrary(ThresholdLevel));
			NickInspectionThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
			Thr->ToLibrary(ALib);
			BData->GetLibraryContainer()->Update(DestLib);
			return;
		}
	}
}

void ShowOperationalPanel::on_ButtonLoadFromLibrary_clicked()
{
	IntList LayerList;
	//GetActiveLayerList(LayerList);
	//if(LayerList.GetFirst()==NULL)
	//	return;
	int	ThresholdLevel=GetLayersBase()->SelectThresholdLevel();
	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		NickInspectionItem	*BData=dynamic_cast<NickInspectionItem *>(DA);
		if(BData==NULL)
			continue;

		int	LibID=BData->GetLibID();
		AlgorithmLibraryContainer	*Container=BData->GetLibraryContainer();
		AlgorithmLibraryLevelContainer	SrcLib(Container);
		if(BData->GetLibraryContainer()->GetLibrary(LibID ,SrcLib)==true){
			NickInspectionLibrary	*ALib=dynamic_cast<NickInspectionLibrary *>(SrcLib.GetLibrary(ThresholdLevel));
			NickInspectionThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
			Thr->FromLibrary(ALib);
			ShowLibrary();
			return;
		}
	}
}

void ShowOperationalPanel::on_ButtonReflectAllBlocks_clicked()
{
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm(LangSolver.GetString(ShowOperationalPanel_LS,LID_3)/*"Reflecting ALL blocks\' threshold"*/);

	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Reflect all blocks threshold");
	GetDataFromWindow();
	GUICmdSendAlgorithmItemIndependentPack	Packet(IData->Base,QString(/**/"ANY"),QString(/**/"ANY"),-1,true);
	Packet.Command=SetIndependentItemDataCommand_All;
	Packet.IData=*IData;
	for(int page=0;page<GetPageNumb();page++){
		Packet.Send(NULL,page,0);
	}
	GetLayersBase()->WaitAllAcknowledged(60*10);
	GetLayersBase()->CloseProcessingForm();
}

void ShowOperationalPanel::on_ButtonClose_clicked()
{
	close();
}
