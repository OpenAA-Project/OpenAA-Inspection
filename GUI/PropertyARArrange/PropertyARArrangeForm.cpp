#include "PropertyARArrangeResource.h"
#include "PropertyARArrangeForm.h"
#include "XPropertyARArrangePacket.h"
#include "XGeneralFunc.h"

extern	const	char	*sRoot;
extern	const	char	*sName;


PropertyARArrangeForm::PropertyARArrangeForm(LayersBase *Base ,QWidget *parent)
	: GUIFormBase(Base,parent)
{
	ui.setupUi(this);

	CurrentLearning=NULL;
}

PropertyARArrangeForm::~PropertyARArrangeForm()
{

}
	
void	PropertyARArrangeForm::BuildForShow(void)
{
}

void	PropertyARArrangeForm::TransmitDirectly(GUIDirectMessage *packet)
{
	GUICmdARArrangeDrawEnd	*GUICmdARArrangeDrawEndVar=dynamic_cast<GUICmdARArrangeDrawEnd *>(packet);
	if(GUICmdARArrangeDrawEndVar!=NULL){
		if(CurrentLearning!=NULL){
			IntList	PageList;
			int	PageN=GetLayersBase()->GetLocalPageFromArea(GUICmdARArrangeDrawEndVar->Area ,PageList);
			if(PageN<=0)
				return;

			for(IntClass *PList=PageList.GetFirst();PList!=NULL;PList=PList->GetNext()){
				int	LocalPage=PList->GetValue();
				int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(LocalPage);

				FlexArea	A=GUICmdARArrangeDrawEndVar->Area;
				GetLayersBase()->GetPageData(LocalPage)->ClipMoveAreaFromGlobal(A);				
				GUICmdReqAddARArrange	DNewMsg(GetLayersBase(),sRoot,sName,globalPage);
				DNewMsg.Area=A;
				DNewMsg.CreatedTime=CurrentLearning->GetCreatedTime();
				DNewMsg.Send(NULL,globalPage ,0);
			}
		}
		return;
	}
}


void	PropertyARArrangeForm::ShowInEdit(void)
{
}
void	PropertyARArrangeForm::ShowLearningList(void)
{
	LContainer.RemoveAll();
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdReqARLearningList		RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		GUICmdSendARLearningList	SCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		if(RCmd.Send(GlobalPage,0,SCmd)==true){
			LContainer+=SCmd.LearningPointerContainer;
		}
	}
	ui.tableWidgetRegistration->setRowCount(LContainer.GetCount());
	int	Row=0;
	for(LearningImagePointerList *a=LContainer.GetFirst();a!=NULL;a=a->GetNext()){
		::SetDataToTable(ui.tableWidgetRegistration,0,Row ,QString::number(a->GetGlobalPage()));
		::SetDataToTable(ui.tableWidgetRegistration,1,Row ,a->GetCreatedTime().toString(/**/"yy/MM/dd hh:mm:ss"));
		
		int x1, y1 , x2 ,y2;
		a->GetOrgLocalArea(x1, y1 , x2 ,y2);
		QString	s	=QString(/**/"(")
					+QString::number((x1+x2)/2)
					+QString(/**/",")
					+QString::number((y1+y2)/2)
					+QString(/**/")");

		::SetDataToTable(ui.tableWidgetRegistration,2,Row ,s);
		Row++;
	}
}
void	PropertyARArrangeForm::ShowArrangeList(void)
{
	CurrentARItemContainer.RemoveAll();
	if(CurrentLearning!=NULL){
		for(int page=0;page<GetPageNumb();page++){
			GUICmdReqARArrangeList		RCmd(GetLayersBase(),sRoot,sName,page);
			GUICmdSendARArrangeList		SCmd(GetLayersBase(),sRoot,sName,page);
			RCmd.CreatedTime=CurrentLearning->GetCreatedTime();
			if(RCmd.Send(page,0,SCmd)==true){
				CurrentARItemContainer+=SCmd.ItemContainer;
			}
		}
		ui.tableWidgetArrange->setRowCount(CurrentARItemContainer.GetCount());
		int	Row=0;
		for(ARItemList *a=CurrentARItemContainer.GetFirst();a!=NULL;a=a->GetNext()){
			::SetDataToTable(ui.tableWidgetArrange,0,Row ,QString::number(a->ItemID));
			QString	s	=QString(/**/"(")
						+QString::number(a->Position.GetX())
						+QString(/**/",")
						+QString::number(a->Position.GetY())
						+QString(/**/")");
			::SetDataToTable(ui.tableWidgetArrange,1,Row ,s);
			if(a->Result==ARArrangeItem::__NotYet)
				::SetDataToTable(ui.tableWidgetArrange,2,Row ,LangSolver.GetString(PropertyARArrangeForm_LS,LID_0)/*"--"*/);
			else if(a->Result==ARArrangeItem::__OK)
				::SetDataToTable(ui.tableWidgetArrange,2,Row ,LangSolver.GetString(PropertyARArrangeForm_LS,LID_1)/*"OK"*/);
			else if(a->Result==ARArrangeItem::__NG)
				::SetDataToTable(ui.tableWidgetArrange,2,Row ,LangSolver.GetString(PropertyARArrangeForm_LS,LID_2)/*"NG"*/);
			Row++;
		}
	}
	else{
		ui.tableWidgetArrange->setRowCount(0);
	}
}

void PropertyARArrangeForm::ShowLearningImage(LearningImagePointerList	*p)
{
	if(CurrentLearning!=NULL){
		int	GlobalPage=CurrentLearning->GetGlobalPage();
		GUICmdReqLearningThumnail		RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		GUICmdSendLearningThumnail		SCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		RCmd.CreatedTime	=CurrentLearning->GetCreatedTime();
		RCmd.ImageWidth		=ui.labelThumnail->width();
		RCmd.ImageHeight	=ui.labelThumnail->height();

		RCmd.CreatedTime=CurrentLearning->GetCreatedTime();
		if(RCmd.Send(GlobalPage,0,SCmd)==true){
			ui.labelThumnail->setPixmap(QPixmap::fromImage(*SCmd.Img));
		}
	}
}

void PropertyARArrangeForm::on_tableWidgetRegistration_clicked(const QModelIndex &)
{
	int	Row=ui.tableWidgetRegistration->currentRow();
	if(Row>=0){
		CurrentLearning=LContainer.GetItem(Row);
		ShowLearningImage(CurrentLearning);
	}
	else{
		CurrentLearning=NULL;
	}
	ShowArrangeList();
}

void PropertyARArrangeForm::on_tableWidgetArrange_clicked(const QModelIndex &)
{
	int	Row=ui.tableWidgetArrange->currentRow();
	if(Row>=0){
		ARItemList	*a=CurrentARItemContainer.GetItem(Row);
	}
}

void PropertyARArrangeForm::on_pushButtonUpdate_clicked()
{
	ShowLearningList();

	int	Row=ui.tableWidgetRegistration->currentRow();
	if(Row>=0){
		CurrentLearning=LContainer.GetItem(Row);
		ShowLearningImage(CurrentLearning);
	}
	else{
		CurrentLearning=NULL;
	}
	ShowArrangeList();
}

void PropertyARArrangeForm::on_tableWidgetRegistration_doubleClicked(QModelIndex)
{
	if(CurrentLearning!=NULL){
		for(int page=0;page<GetPageNumb();page++){
			LearningImage	*L=GetLayersBase()->GetPageData(page)->Find(CurrentLearning->GetCreatedTime());
			if(L!=NULL){
				GetLayersBase()->GetEntryPoint()->ShowOtherGUI(
					this
					,GetLayersBase()->GetGUIFileName()
					,L->GetLearningLayersBase());
				break;
			}
		}
	}
}
void PropertyARArrangeForm::on_tableWidgetArrange_doubleClicked(QModelIndex)
{
	if(CurrentLearning!=NULL){
		int	Row=ui.tableWidgetArrange->currentRow();
		if(Row>=0){
			ARItemList	*a=CurrentARItemContainer.GetItem(Row);
			for(int page=0;page<GetPageNumb();page++){
				LearningImage	*L=GetLayersBase()->GetPageData(page)->Find(CurrentLearning->GetCreatedTime());
				if(L!=NULL){
					GetLayersBase()->GetEntryPoint()->ShowOtherGUI(
						this
						,GetLayersBase()->GetGUIFileName()
						,L->GetLearningLayersBase());
					break;
				}
			}
		}
	}
}
