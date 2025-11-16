#include "XConfirmAlgorithm.h"
#include "ButtonShowConfirm.h"
#include "ConfirmForm.h"
#include "XConfirmPacket.h"

ConfirmAlgorithm::ConfirmAlgorithm(ConfirmForm *p)
	:Parent(p)
{	
	OnChanging=false;
	EnableChangeMode=true;
}
int	ConfirmAlgorithm::GetSlaveNo(void)
{
	return Parent->Parent->SlaveNo;
}

void	ConfirmAlgorithm::ZoomArea(int ux1,int uy1,int ux2,int uy2)
{
	Parent->ZoomArea(ux1,uy1,ux2,uy2);
}
void	ConfirmAlgorithm::PushButton(void)
{
	Button->setChecked(true);
	Parent->SlotButtonClicked();
}
void	ConfirmAlgorithm::AlgoMouseMove(int ux ,int uy)
{
    EachMaster	*m=Parent->GetLayersBase()->GetIntegrationBasePointer()->GetMaster(GetSlaveNo());
    if(m!=NULL){
		IntList	LayerList;
		for(int Layer=0;Layer<m->GetMaxLayerNumb();Layer++){
			LayerList.Add(Layer);
		}
		int		localX ,localY;
		int	Page=m->GetLocalMatrixFromGlobal(ux,uy,localX ,localY);
		if(Page>=0){
			IntegrationSetActivateItem	RCmd(Parent->GetLayersBase(),sRoot,sName,GetSlaveNo());
			RCmd.Phase=m->GetCurrentPhase();
			RCmd.localX=localX;
			RCmd.localY=localY;
			RCmd.LibType=GetLibType();
			RCmd.LayerList	=LayerList;
			RCmd.Send(NULL,GetSlaveNo(),Page);
		}
	}
}
void	ConfirmAlgorithm::AlgoMouseRDown(int ux ,int uy)
{
	ClearSelectItems();
	Parent->SelectedArea.Clear();
}
void	ConfirmAlgorithm::CanvasSlotDrawEnd(FlexArea &Area)
{
    //EachMaster	*m=Parent->GetLayersBase()->GetIntegrationBasePointer()->GetMaster(GetSlaveNo());
    //if(m!=NULL){
	//	 for(int page=0;page<m->GetPageNumb();page++){
	//		IntegrationSetSelectedArea	RCmd(Parent->GetLayersBase(),sRoot,sName,GetSlaveNo(),page);
	//		RCmd.SelectedArea=Area;
	//		RCmd.Send(NULL,GetSlaveNo(),page,0);
	//	 }
	//}
	Parent->SetSelectedArea(Area);
}

void	ConfirmAlgorithm::MakeConfirmItemList(void)
{
	AlgorithmBase	*ABase=Parent->GetLayersBase()->GetAlgorithmBase(GetLibType());
	if(ABase!=NULL){
		IntegrationCmdReqConfirmItemList	RCmd(Parent->GetLayersBase(),sRoot,sName,GetSlaveNo());
		IntegrationCmdAckConfirmItemList	ACmd(Parent->GetLayersBase(),sRoot,sName,GetSlaveNo());
		ABase->GetAlgorithmRootName(RCmd.AlgorithmRoot,RCmd.AlgorithmName);
		if(RCmd.Send(GetSlaveNo(),0,ACmd)==true){
			ConfirmItemInst=ACmd.ItemList;
		}
	}
}

void	ConfirmAlgorithm::GetItemsByArea(int LibID,FlexArea &GlobalArea)
{
    EachMaster	*m=Parent->GetLayersBase()->GetIntegrationBasePointer()->GetMaster(GetSlaveNo());
    if(m!=NULL){
		IntegrationReqSelectItems	RCmd(Parent->GetLayersBase(),sRoot,sName,GetSlaveNo());
		RCmd.SelectedLib.SetLibType(GetLibType());
		RCmd.SelectedLib.SetLibID(LibID);
		RCmd.Phase	=m->GetCurrentPhase();
		RCmd.GlobalArea=GlobalArea;
		RCmd.Mode=0;
		IntegrationAckSelectItems	ACmd(Parent->GetLayersBase(),sRoot,sName,GetSlaveNo());
		if(RCmd.Send(GetSlaveNo(),0,ACmd)==true){
			SelectedItems=ACmd.Items;
		}
	}
}
void	ConfirmAlgorithm::GetItemsByPoint(int GlobalX, int GlobalY)
{
    EachMaster	*m=Parent->GetLayersBase()->GetIntegrationBasePointer()->GetMaster(GetSlaveNo());
    if(m!=NULL){
		IntegrationReqSelectItems	RCmd(Parent->GetLayersBase(),sRoot,sName,GetSlaveNo());
		RCmd.SelectedLib.SetLibType(GetLibType());
		RCmd.SelectedLib.SetLibID(-1);
		RCmd.Phase	=m->GetCurrentPhase();
		RCmd.GlobalX=GlobalX;
		RCmd.GlobalY=GlobalY;
		RCmd.Mode=1;
		IntegrationAckSelectItems	ACmd(Parent->GetLayersBase(),sRoot,sName,GetSlaveNo());
		if(RCmd.Send(GetSlaveNo(),0,ACmd)==true){
			SelectedItems=ACmd.Items;
		}
	}
}
void	ConfirmAlgorithm::GetAllItems(int LibID)
{
    EachMaster	*m=Parent->GetLayersBase()->GetIntegrationBasePointer()->GetMaster(GetSlaveNo());
    if(m!=NULL){
		IntegrationReqSelectItems	RCmd(Parent->GetLayersBase(),sRoot,sName,GetSlaveNo());
		RCmd.SelectedLib.SetLibType(GetLibType());
		RCmd.SelectedLib.SetLibID(LibID);
		RCmd.Phase	=m->GetCurrentPhase();
		RCmd.Mode=2;
		IntegrationAckSelectItems	ACmd(Parent->GetLayersBase(),sRoot,sName,GetSlaveNo());
		if(RCmd.Send(GetSlaveNo(),0,ACmd)==true){
			SelectedItems=ACmd.Items;
		}
	}
}

void	ConfirmAlgorithm::SetSelectItems(void)
{
    EachMaster	*m=Parent->GetLayersBase()->GetIntegrationBasePointer()->GetMaster(GetSlaveNo());
    if(m!=NULL){
		for(int page=0;page<m->GetPageNumb();page++){
			IntegrationSetSelectItems	RCmd(Parent->GetLayersBase(),sRoot,sName,GetSlaveNo());
			RCmd.LibType=GetLibType();
			RCmd.Items=SelectedItems;
			RCmd.Send(NULL,GetSlaveNo(),m->GetLocalPageFromGlobal(page));
		}
	}
}
void	ConfirmAlgorithm::ClearSelectItems(void)
{
    EachMaster	*m=Parent->GetLayersBase()->GetIntegrationBasePointer()->GetMaster(GetSlaveNo());
    if(m!=NULL){
		for(int page=0;page<m->GetPageNumb();page++){
			IntegrationClearSelectItems	RCmd(Parent->GetLayersBase(),sRoot,sName,GetSlaveNo());
			RCmd.LibType=GetLibType();
			RCmd.Send(NULL,GetSlaveNo(),m->GetLocalPageFromGlobal(page));
		}
		SelectedItems.RemoveAll();
	}
}
void	ConfirmAlgorithm::SetSelectItemsByGroupID(int ErrorGroupID)
{
    EachMaster	*m=Parent->GetLayersBase()->GetIntegrationBasePointer()->GetMaster(GetSlaveNo());
    if(m!=NULL){
		SelectedItems.RemoveAll();

		for(int page=0;page<m->GetPageNumb();page++){
			IntegrationReqSelectItemsByGroupID	RCmd(Parent->GetLayersBase(),sRoot,sName,GetSlaveNo());
			IntegrationAckSelectItemsByGroupID	ACmd(Parent->GetLayersBase(),sRoot,sName,GetSlaveNo());
			RCmd.LibType=GetLibType();
			RCmd.Phase	=m->GetCurrentPhase();
			RCmd.ErrorGroupID=ErrorGroupID;
			if(RCmd.Send(GetSlaveNo(),m->GetLocalPageFromGlobal(page),ACmd)==true){
				SelectedItems=ACmd.Items;
			}
		}
	}
}




void	ConfirmAlgorithm::RegisterComponent(int MemberID ,QSpinBox *e)
{
	MemberComponentList	*r=new MemberComponentList(MemberID,e);
	MemberComponentContainer.AppendList(r);
	connect(e,SIGNAL(valueChanged(int)),this,SLOT(SlotValueChangedInt(int)));
}
void	ConfirmAlgorithm::RegisterComponent(int MemberID ,QDoubleSpinBox *e)
{
	MemberComponentList	*r=new MemberComponentList(MemberID,e);
	MemberComponentContainer.AppendList(r);
	connect(e,SIGNAL(valueChanged(double)),this,SLOT(SlotValueChangedDouble(double)));
}
void	ConfirmAlgorithm::RegisterComponent(int MemberID ,QLineEdit *e)
{
	MemberComponentList	*r=new MemberComponentList(MemberID,e);
	MemberComponentContainer.AppendList(r);
	connect(e,SIGNAL(textChanged(const QString &)),this,SLOT(SlotTextChanged(const QString &)));
}

void	ConfirmAlgorithm::RegisterComponent(int MemberID ,QCheckBox *e)
{
	MemberComponentList	*r=new MemberComponentList(MemberID,e);
	MemberComponentContainer.AppendList(r);
	connect(e,SIGNAL(stateChanged(int)),this,SLOT(SlotStateChanged(int)));
}
void	ConfirmAlgorithm::RegisterComponent(int MemberID ,QComboBox *e)
{
	MemberComponentList	*r=new MemberComponentList(MemberID,e);
	MemberComponentContainer.AppendList(r);
	connect(e,SIGNAL(currentIndexChanged(int)),this,SLOT(SlotCurrentIndexChanged(int)));
}

void	ConfirmAlgorithm::SlotValueChangedInt(int n)
{
	if(EnableChangeMode==true){
		QObject *p=sender();
		if(p!=NULL){
			QString	objName=p->objectName();
			for(MemberComponentList *r=MemberComponentContainer.GetFirst();r!=NULL;r=r->GetNext()){
				QSpinBox	*e=dynamic_cast<QSpinBox *>(r->GetComponent());
				//if(e!=NULL && e->hasFocus()==true){
				if(e!=NULL && e->objectName()==objName){
					r->SetEditted(true);
				}
			}
		}
	}
}

void	ConfirmAlgorithm::SlotValueChangedDouble(double n)
{
	if(EnableChangeMode==true){
		QObject *p=sender();
		if(p!=NULL){
			QString	objName=p->objectName();
			for(MemberComponentList *r=MemberComponentContainer.GetFirst();r!=NULL;r=r->GetNext()){
				QDoubleSpinBox	*e=dynamic_cast<QDoubleSpinBox *>(r->GetComponent());
				//if(e!=NULL && e->hasFocus()==true){
				if(e!=NULL && e->objectName()==objName){
					r->SetEditted(true);
				}
			}
		}
	}
}

void	ConfirmAlgorithm::SlotTextChanged(const QString &text)
{
	if(EnableChangeMode==true){
		QObject *p=sender();
		if(p!=NULL){
			QString	objName=p->objectName();
			for(MemberComponentList *r=MemberComponentContainer.GetFirst();r!=NULL;r=r->GetNext()){
				QLineEdit	*e=dynamic_cast<QLineEdit *>(r->GetComponent());
				//if(e!=NULL && e->hasFocus()==true){
				if(e!=NULL && e->objectName()==objName){
					r->SetEditted(true);
				}
			}
		}
	}
}

void	ConfirmAlgorithm::SlotStateChanged(int state)
{
	if(EnableChangeMode==true){
		QObject *p=sender();
		if(p!=NULL){
			QString	objName=p->objectName();
			for(MemberComponentList *r=MemberComponentContainer.GetFirst();r!=NULL;r=r->GetNext()){
				QCheckBox	*e=dynamic_cast<QCheckBox *>(r->GetComponent());
				//if(e!=NULL && e->hasFocus()==true){
				if(e!=NULL && e->objectName()==objName){
					r->SetEditted(true);
				}
			}
		}
	}
}

void	ConfirmAlgorithm::SlotCurrentIndexChanged(int state)
{
	if(EnableChangeMode==true){
		QObject *p=sender();
		if(p!=NULL){
			QString	objName=p->objectName();
			for(MemberComponentList *r=MemberComponentContainer.GetFirst();r!=NULL;r=r->GetNext()){
				QComboBox	*e=dynamic_cast<QComboBox *>(r->GetComponent());
				//if(e!=NULL && e->hasFocus()==true){
				if(e!=NULL && e->objectName()==objName){
					r->SetEditted(true);
				}
			}
		}
	}
}
void	ConfirmAlgorithm::ClearRegisterComponent(void)
{
	for(MemberComponentList *r=MemberComponentContainer.GetFirst();r!=NULL;r=r->GetNext()){
		r->SetEditted(false);
	}
}
void	ConfirmAlgorithm::GetEdittedList(IntList &EdittedMemberID)
{
	for(MemberComponentList *r=MemberComponentContainer.GetFirst();r!=NULL;r=r->GetNext()){
		if(r->IsEditted()==true && EdittedMemberID.IsInclude(r->GetMemberID())==false){
			EdittedMemberID.Add(r->GetMemberID());
		}
	}
}
