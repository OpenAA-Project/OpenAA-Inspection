#include "XTypeDef.h"
#include "XAlgorithmWindow.h"
#include <QLineEdit>
#include <QCheckBox>
#include <QRadioButton>
#include <QDoubleSpinBox>
#include <QSpinBox>
#include <QComboBox>
#include <QToolButton>
#include "XDataInLayerCmdLocal.h"
#include "XAlgorithmLibrary.h"
#include "XDataAlgorithmList.h"

ItemMember::ItemMember(QLineEdit *e ,QString *member)
{
	LineEdit	=e;
	ControlType	=Enum_LineEdit;
	StringMember=member;
	MemberType	=Enum_QString;
}
ItemMember::ItemMember(QCheckBox *e ,bool *member)
{
	CheckBox	=e;
	ControlType	=Enum_CheckBox ;
	BoolMember=member;
	MemberType	=Enum_bool;
}
ItemMember::ItemMember(QRadioButton *e ,bool *member)
{
	RadioButton	=e;
	ControlType	=Enum_RadioButton;
	BoolMember=member;
	MemberType	=Enum_bool;
}
ItemMember::ItemMember(QDoubleSpinBox *e ,double *member)
{
	DoubleSpinBox	=e;
	ControlType	=Enum_DoubleSpinBox;
	DoubleMember=member;
	MemberType	=Enum_double;
}
ItemMember::ItemMember(QDoubleSpinBox *e ,float *member)
{
	DoubleSpinBox	=e;
	ControlType	=Enum_DoubleSpinBox;
	FloatMember=member;
	MemberType	=Enum_float;
}
ItemMember::ItemMember(QSpinBox *e ,int *member)
{
	SpinBox	=e;
	ControlType	=Enum_SpinBox;
	IntMember=member;
	MemberType	=Enum_int;
}
ItemMember::ItemMember(QComboBox *e ,int *member)
{
	ComboBox	=e;
	ControlType	=Enum_ComboBox;
	IntMember=member;
	MemberType	=Enum_int;
}
ItemMember::ItemMember(QToolButton *e ,bool *member)
{
	ToolButton	=e;
	ControlType	=Enum_ToolButton;
	BoolMember=member;
	MemberType	=Enum_bool;
}
void	ItemMember::Show(void)
{
	switch(ControlType){
	case Enum_LineEdit		:
		LineEdit->setText(*StringMember);
		break;
	case Enum_CheckBox		:
		CheckBox->setChecked(*BoolMember);
		break;
	case Enum_RadioButton	:
		RadioButton->setChecked(*BoolMember);
		break;
	case Enum_DoubleSpinBox	:
		if(MemberType==Enum_double){
			DoubleSpinBox->setValue(*DoubleMember);
		}
		else
		if(MemberType==Enum_float){
			DoubleSpinBox->setValue(*FloatMember);
		}
		break;
	case Enum_SpinBox		:
		SpinBox->setValue(*IntMember);
		break;
	case Enum_ComboBox		:
		ComboBox->setCurrentIndex(*IntMember);
		break;
	case Enum_ToolButton	:
		ToolButton->setChecked(*BoolMember);
		break;
	}
}
void	ItemMember::GetDataFromControl(void)
{
	switch(ControlType){
	case Enum_LineEdit		:
		*StringMember	=LineEdit->text();
		break;
	case Enum_CheckBox		:
		*BoolMember=CheckBox->isChecked();
		break;
	case Enum_RadioButton	:
		*BoolMember=RadioButton->isChecked();
		break;
	case Enum_DoubleSpinBox	:
		if(MemberType==Enum_double){
			*DoubleMember=DoubleSpinBox->value();
		}
		else
		if(MemberType==Enum_float){
			*FloatMember	=DoubleSpinBox->value();
		}
		break;
	case Enum_SpinBox		:
		*IntMember=SpinBox->value();
		break;
	case Enum_ComboBox		:
		*IntMember=ComboBox->currentIndex();
		break;
	case Enum_ToolButton	:
		*BoolMember	=ToolButton->isChecked();
		break;
	}
}

//===============================================================================--

AlgorithmWindow::AlgorithmWindow(LayersBase *Base)
	:ServiceForLayers(Base),PasswordInQWodget(Base,NULL)
{
	ABase	=NULL;
	TempData=NULL;
}
AlgorithmWindow::~AlgorithmWindow(void)
{
	if(TempData!=NULL){
		delete	TempData;
		TempData=NULL;
	}
}

void	AlgorithmWindow::Initial(ItemsByAlgorithm &items)
{
	Items	=items;

	ListPhasePageID	*FirstData=Items.ItemID.GetFirst();
	if(FirstData!=NULL){
		ABase=GetLayersBase()->GetAlgorithmBase(Items.LibType);
		TempData=CreateThresholdInstance(ABase);

		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(FirstData->Page);
		GUICmdReqThresholdInstance	RCmd(GetLayersBase(),/**/"ANY",/**/"ANY",GlobalPage);
		GUICmdAckThresholdInstance	ACmd(GetLayersBase(),/**/"ANY",/**/"ANY",GlobalPage);
		RCmd.LibType=Items.LibType;
		RCmd.LibID	=Items.LibID;
		RCmd.Layer	=Items.Layer;
		RCmd.ItemID	=FirstData->ID;
		if(RCmd.Send(GlobalPage,0,ACmd)==true){
			QBuffer	Buff(&ACmd.Array);
			Buff.open(QIODevice::ReadWrite);
			TempData->Load(&Buff);
		}
		AllocateItemMember(TempData);
		for(ItemMember *a=ItemMemberContainer.GetFirst();a!=NULL;a=a->GetNext()){
			a->Show();
		}
	}
}

bool	AlgorithmWindow::SaveInLibrary(void)
{
	GetDataInTempFromWindow();

	AlgorithmLibraryContainer	*Container=ABase->GetLibraryContainer();
	AlgorithmLibraryLevelContainer	DestLib(Container);
	if(Container->GetLibrary(Items.LibID ,DestLib)==true){
		AlgorithmLibrary	*ALib=DestLib.GetLibrary();
		TempData->ToLibrary(ALib);
		return Container->Update(DestLib);
	}
	return false;
}

bool	AlgorithmWindow::LoadFromLibrary(void)
{
	AlgorithmLibraryContainer	*Container=ABase->GetLibraryContainer();
	AlgorithmLibraryLevelContainer	SrcLib(Container);
	if(Container->GetLibrary(Items.LibID ,SrcLib)==true){
		AlgorithmLibrary	*ALib=SrcLib.GetLibrary();
		TempData->FromLibrary(ALib);
		ShowDataInTempToWindow();
		return true;
	}
	return false;
}
bool	AlgorithmWindow::ReflectOne(void)
{
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm("Reflecting ONE(Only selected) threshold");

	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Reflect one threshold");
	GetDataInTempFromWindow();

	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdReflectThresholdInstanceOne	RCmd(GetLayersBase(),/**/"ANY",/**/"ANY",GlobalPage);
		for(ListPhasePageID	*d=Items.ItemID.GetFirst();d!=NULL;d=d->GetNext()){
			if(d->Page==page){
				RCmd.ItemID.Add(d->ID);
			}
		}
		if(RCmd.ItemID.GetCount()>0){
			RCmd.LibType=Items.LibType;
			RCmd.LibID	=Items.LibID;
			RCmd.Layer	=Items.Layer;

			QBuffer	Buff;
			Buff.open(QIODevice::ReadWrite);
			TempData->Save(&Buff);

			RCmd.ThresholdData	=Buff.buffer();
			RCmd.ChangedMapInThreshold=ChangedMapInThreshold;
			RCmd.Send(NULL,page,0);
		}
	}
	GetLayersBase()->WaitAllAcknowledged(60*10);
	GetLayersBase()->CloseProcessingForm();
	return true;
}

bool	AlgorithmWindow::ReflectAll(void)
{
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm("Reflecting all items threshold");

	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Reflect all item threshold");
	GetDataInTempFromWindow();

	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdReflectThresholdInstanceAll	RCmd(GetLayersBase(),/**/"ANY",/**/"ANY",GlobalPage);

		RCmd.LibType=Items.LibType;
		RCmd.LibID	=Items.LibID;
		RCmd.Layer	=Items.Layer;

		QBuffer	Buff;
		Buff.open(QIODevice::ReadWrite);
		TempData->Save(&Buff);

		RCmd.ThresholdData	=Buff.buffer();
		RCmd.ChangedMapInThreshold=ChangedMapInThreshold;
		RCmd.Send(NULL,page,0);
	}
	GetLayersBase()->WaitAllAcknowledged(60*10);
	GetLayersBase()->CloseProcessingForm();
	return true;
}

bool	AlgorithmWindow::Test(void)
{
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm("Reflecting ONE(Only selected) threshold");

	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Reflect one threshold");
	GetDataInTempFromWindow();

	QByteArrayList	ResultItemDataList;

	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdTestThresholdInstance		RCmd(GetLayersBase(),/**/"ANY",/**/"ANY",GlobalPage);
		GUICmdResultThresholdInstance	ACmd(GetLayersBase(),/**/"ANY",/**/"ANY",GlobalPage);
		for(ListPhasePageID	*d=Items.ItemID.GetFirst();d!=NULL;d=d->GetNext()){
			if(d->Page==page){
				RCmd.ItemID.Add(d->ID);
			}
		}
		if(RCmd.ItemID.GetCount()>0){
			RCmd.LibType=Items.LibType;
			RCmd.LibID	=Items.LibID;
			RCmd.Layer	=Items.Layer;

			QBuffer	Buff;
			Buff.open(QIODevice::ReadWrite);
			TempData->Save(&Buff);

			RCmd.ThresholdData	=Buff.buffer();
			RCmd.ChangedMapInThreshold=ChangedMapInThreshold;
			if(RCmd.Send(GlobalPage,0,ACmd)==true){
				ResultItemDataList.append(ACmd.ResultInItemData);
			}
		}
	}
	ShowResultItemData(ResultItemDataList);

	GetLayersBase()->WaitAllAcknowledged(60*10);
	GetLayersBase()->CloseProcessingForm();
	return true;
}

void	AlgorithmWindow::AddItemMember(QLineEdit *e		,QString *member)
{
	ItemMemberContainer.AppendList(new ItemMember(e,member));
}
void	AlgorithmWindow::AddItemMember(QCheckBox *e		,bool *member)
{
	ItemMemberContainer.AppendList(new ItemMember(e,member));
}
void	AlgorithmWindow::AddItemMember(QRadioButton *e	,bool *member)
{
	ItemMemberContainer.AppendList(new ItemMember(e,member));
}
void	AlgorithmWindow::AddItemMember(QDoubleSpinBox *e,double *member)
{
	ItemMemberContainer.AppendList(new ItemMember(e,member));
}
void	AlgorithmWindow::AddItemMember(QDoubleSpinBox *e,float *member)
{
	ItemMemberContainer.AppendList(new ItemMember(e,member));
}
void	AlgorithmWindow::AddItemMember(QSpinBox *e		,int *member)
{
	ItemMemberContainer.AppendList(new ItemMember(e,member));
}
void	AlgorithmWindow::AddItemMember(QComboBox *e		,int *member)
{
	ItemMemberContainer.AppendList(new ItemMember(e,member));
}
void	AlgorithmWindow::AddItemMember(QToolButton *e	,bool *member)
{
	ItemMemberContainer.AppendList(new ItemMember(e,member));
}

void	AlgorithmWindow::GetDataInTempFromWindow(void)
{
	for(ItemMember *a=ItemMemberContainer.GetFirst();a!=NULL;a=a->GetNext()){
		a->GetDataFromControl();
	}
}
void	AlgorithmWindow::ShowDataInTempToWindow(void)
{
	for(ItemMember *a=ItemMemberContainer.GetFirst();a!=NULL;a=a->GetNext()){
		a->Show();
	}
}
void	AlgorithmWindow::ShowResultItemData(QByteArrayList &ResultItemDataList)
{
}
