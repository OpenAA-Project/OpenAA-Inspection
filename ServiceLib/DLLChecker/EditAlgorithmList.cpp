#include "EditAlgorithmList.h"
#include "XAlgorithmInterfaceDLL.h"
#include "XAlgorithmBase.h"
#include "XDataInLayer.h"
#include "XGeneralFunc.h"


void	AlgoGrid::ChangeValue(int row ,int col,const QVariant &value)
{
	EditAlgorithmList	*dw=MParent;
	if(dw!=NULL){
		AlgorithmDLLList *L=GetLayersBase()->GetAlgoDLLContPointer()->GetItem(row);
		switch(col){
			case 0:	dw->EffectiveList.GetItem(row)->SetValue(value.toBool());
					break;
			case 1:	L->SetPriorityDetail(AlgorithmDLLList::ModeInitialAfterEdit	,value.toInt());
					break;
			case 2:	L->SetPriorityDetail(AlgorithmDLLList::ModeStartByInspection,value.toInt());
					break;
			case 3:	L->SetPriorityDetail(AlgorithmDLLList::ModePreAlignment		,value.toInt());
					break;
			case 4:	L->SetPriorityDetail(AlgorithmDLLList::ModeAlignment		,value.toInt());
					break;
			case 5:	L->SetPriorityDetail(AlgorithmDLLList::ModePreProcessing	,value.toInt());
					break;
			case 6:	L->SetPriorityDetail(AlgorithmDLLList::ModeProcessing		,value.toInt());
					break;
			case 7:	L->SetPriorityDetail(AlgorithmDLLList::ModePostProcessing	,value.toInt());
					break;
			case 8:	L->SetPriorityDetail(AlgorithmDLLList::ModePreScanning		,value.toInt());
					break;
			case 9:	L->SetPriorityDetail(AlgorithmDLLList::ModeScanning			,value.toInt());
					break;
			case 10:L->SetPriorityDetail(AlgorithmDLLList::ModePostScanning		,value.toInt());
					break;
			case 11:L->SetPriorityDetail(AlgorithmDLLList::ModeManageResult		,value.toInt());
					break;
			case 12:L->SetPriorityDetail(AlgorithmDLLList::ModeAutoGeneration	,value.toInt());
					break;
			case 13:L->SetPriorityDetail(AlgorithmDLLList::ModeProcessingRevived	,value.toInt());
					break;
		}
	}
}
void	AlgoGrid::GetValue(int row ,int col,QVariant &value)
{
	EditAlgorithmList	*dw=MParent;
	if(dw!=NULL){
		AlgorithmDLLList *L=GetLayersBase()->GetAlgoDLLContPointer()->GetItem(row);
		switch(col){
			case 0:	value.setValue(dw->EffectiveList.GetItem(row)->GetValue());
					break;
			case 1:	value.setValue(L->GetPriorityDetail(AlgorithmDLLList::ModeInitialAfterEdit));
					break;
			case 2:	value.setValue(L->GetPriorityDetail(AlgorithmDLLList::ModeStartByInspection));
					break;
			case 3:	value.setValue(L->GetPriorityDetail(AlgorithmDLLList::ModePreAlignment	));
					break;
			case 4:	value.setValue(L->GetPriorityDetail(AlgorithmDLLList::ModeAlignment		));
					break;
			case 5:	value.setValue(L->GetPriorityDetail(AlgorithmDLLList::ModePreProcessing	));
					break;
			case 6:	value.setValue(L->GetPriorityDetail(AlgorithmDLLList::ModeProcessing	));
					break;
			case 7:	value.setValue(L->GetPriorityDetail(AlgorithmDLLList::ModePostProcessing));
					break;
			case 8:	value.setValue(L->GetPriorityDetail(AlgorithmDLLList::ModePreScanning	));
					break;
			case 9:	value.setValue(L->GetPriorityDetail(AlgorithmDLLList::ModeScanning		));
					break;
			case 10:value.setValue(L->GetPriorityDetail(AlgorithmDLLList::ModePostScanning	));
					break;
			case 11:value.setValue(L->GetPriorityDetail(AlgorithmDLLList::ModeManageResult	));
					break;
			case 12:value.setValue(L->GetPriorityDetail(AlgorithmDLLList::ModeAutoGeneration));
					break;
			case 13:value.setValue(L->GetPriorityDetail(AlgorithmDLLList::ModeProcessingRevived));
					break;
		}
	}
}


EditAlgorithmList::EditAlgorithmList(LayersBase *Base,QWidget *parent, Qt::WindowFlags flags)
	: QWidget(parent, flags),ServiceForLayers(Base),WTable(Base,this)
{
	ui.setupUi(this);

	GetLayersBase()->GetAlgoDLLContPointer()->LoadAlgorithmDefFile();

	WTable.move(0,0);
	WTable.resize(ui.frame->width(),ui.frame->height());
	WTable.setParent(ui.frame);

	WTable.SetColumnCount(14);
	WTable.SetRowCount(GetLayersBase()->GetAlgoDLLContPointer()->GetNumber());

	WTable.SetTopHeader(0 ,"Effective");
	WTable.SetTopHeader(1 ,"InitialAfterEdit");
	WTable.SetTopHeader(2 ,"StartByInspection");
	WTable.SetTopHeader(3 ,"PreAlignment");
	WTable.SetTopHeader(4 ,"Alignment");
	WTable.SetTopHeader(5 ,"PreProcessing");
	WTable.SetTopHeader(6 ,"Processing");
	WTable.SetTopHeader(7 ,"PostProcessing");
	WTable.SetTopHeader(8 ,"PreScanning");
	WTable.SetTopHeader(9 ,"Scanning");
	WTable.SetTopHeader(10,"PostScanning");
	WTable.SetTopHeader(11,"ManageResult");
	WTable.SetTopHeader(12,"AutoGeneration");
	WTable.SetTopHeader(13 ,"ProcessingRevived");

	EffectiveList.RemoveAll();
	int	Row=0;
	for(AlgorithmDLLList *L=GetLayersBase()->GetAlgoDLLContPointer()->GetFirst();L!=NULL;L=L->GetNext(),Row++){
		WMultiGrid::CellData *W=WTable.GetData(Row ,0);
		QFileInfo	fileInfo(L->GetFileName());
		WTable.SetLeftHeader(Row,fileInfo.fileName());

		if(GetLayersBase()->GetAlgoDLLContPointer()->SearchDef(fileInfo.fileName())==NULL){
			W->Value	=false;
			EffectiveList.Add(false);
		}
		else{
			W->Value	=true;
			EffectiveList.Add(true);
		}
		W->CType	=WMultiGrid::_CType_CheckBox;
		W->Alignment=Qt::AlignVCenter | Qt::AlignCenter;

		for(int i=1;i<14;i++){
			W=WTable.GetData(Row ,i);
			switch(i){
				case 1:	W->Value=L->GetPriorityDetail(AlgorithmDLLList::ModeInitialAfterEdit);
						break;
				case 2:	W->Value=L->GetPriorityDetail(AlgorithmDLLList::ModeStartByInspection);
						break;
				case 3:	W->Value=L->GetPriorityDetail(AlgorithmDLLList::ModePreAlignment	);
						break;
				case 4:	W->Value=L->GetPriorityDetail(AlgorithmDLLList::ModeAlignment		);
						break;
				case 5:	W->Value=L->GetPriorityDetail(AlgorithmDLLList::ModePreProcessing	);
						break;
				case 6:	W->Value=L->GetPriorityDetail(AlgorithmDLLList::ModeProcessing		);
						break;
				case 7:	W->Value=L->GetPriorityDetail(AlgorithmDLLList::ModePostProcessing	);
						break;
				case 8:	W->Value=L->GetPriorityDetail(AlgorithmDLLList::ModePreScanning		);
						break;
				case 9:	W->Value=L->GetPriorityDetail(AlgorithmDLLList::ModeScanning		);
						break;
				case 10:W->Value=L->GetPriorityDetail(AlgorithmDLLList::ModePostScanning	);
						break;
				case 11:W->Value=L->GetPriorityDetail(AlgorithmDLLList::ModeManageResult	);
						break;
				case 12:W->Value=L->GetPriorityDetail(AlgorithmDLLList::ModeAutoGeneration	);
						break;
				case 13:W->Value=L->GetPriorityDetail(AlgorithmDLLList::ModeProcessingRevived);
						break;
			}
			W->CType	=WMultiGrid::_CType_SpinBox;
			W->Alignment=Qt::AlignVCenter | Qt::AlignCenter;
		}
	}
	WTable.InitialGrid();
}

EditAlgorithmList::~EditAlgorithmList()
{

}


void EditAlgorithmList::on_pushButtonSave_clicked()
{
	int	Row=0;
	QStringList	EffectiveAlgoFileNames;

	for(AlgorithmDLLList *L=GetLayersBase()->GetAlgoDLLContPointer()->GetFirst();L!=NULL;L=L->GetNext(),Row++){
		if(EffectiveList.GetItem(Row)->GetValue()==true){
		QFileInfo	fileInfo(L->GetFileName());
			EffectiveAlgoFileNames.append(fileInfo.fileName());
		}
	}
	GetLayersBase()->GetAlgoDLLContPointer()->SaveAlgorithmDefFile(EffectiveAlgoFileNames);
	emit	SignalClose();
	close();
}

void EditAlgorithmList::on_pushButtonCancel_clicked()
{
	emit	SignalClose();
	close();
}