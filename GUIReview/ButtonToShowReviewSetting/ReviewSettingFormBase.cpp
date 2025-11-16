#include "ButtonToShowReviewSettingResource.h"
#include "ReviewSettingFormBase.h"
#include "XGUIReviewGlobal.h"

#include "XAlgorithmBase.h"
#include "XReviewCommon.h"

#include "XDataInLayer.h"
#include "XGUI.h"

#include "XReviewCommonPacket.h"
#include "XGUIReviewCommonPacket.h"
#include <QDesktopWidget>
#include <QString>
#include <QMessageBox>

extern const QString saveFilename;

bool ReviewSettingFormBase::checkPropertyEnable(AlgorithmBase *algorithm)
{
	ReviewCommonPacket::CmdReqSettingPropertyDialog cmdTest(GetLayersBase());
	if(algorithm==NULL){
		return false;
	}else{
		algorithm->TransmitDirectly(&cmdTest);
		return cmdTest.isValid();
	}
}

bool ReviewSettingFormBase::checkPropertyEnable(GUIFormBase *gui)
{
	ReviewCommonPacket::CmdReqSettingPropertyDialog cmdTest(GetLayersBase());
	if(gui==NULL){
		return false;
	}else{
		gui->TransmitDirectly(&cmdTest);
		return cmdTest.isValid();
	}
}

ReviewSettingFormBase::ReviewSettingFormBase(LayersBase *layer, QWidget *parent)
	:QDialog(parent),m_layer(layer)
{
	//ui.setupUi(this);
	//ui.pbReviewStructure->setEnabled(checkPropertyEnable(GetReviewAlgorithmBase()));

	//setButtonState(ui.pbButtonToShowTotalNGMap, GetReviewGUIForm(ReviewGUI::Name::ButtonToShowTotalNGMap), ReviewGUI::Name::ButtonToShowTotalNGMap);
	//setButtonState(ui.pbListMasterDataAndLoad, GetReviewGUIForm(ReviewGUI::Name::ListMasterDataAndLoad), ReviewGUI::Name::ListMasterDataAndLoad);
	//setButtonState(ui.pbListStatisticNG, GetReviewGUIForm(ReviewGUI::Name::ListStatisticNG), ReviewGUI::Name::ListStatisticNG);
	//setButtonState(ui.pbLiveCameraAlgoNTSC, GetReviewGUIForm(ReviewGUI::Name::LiveCameraAlgoNTSC), ReviewGUI::Name::LiveCameraAlgoNTSC);
	//setButtonState(NULL, GetReviewGUIForm(ReviewGUI::Name::LiveCameraDFK31AF03), ReviewGUI::Name::LiveCameraDFK31AF03);
	//setButtonState(ui.pbNGImageForReview, GetReviewGUIForm(ReviewGUI::Name::NGImageForReview), ReviewGUI::Name::NGImageForReview);
	//setButtonState(ui.pbNGImageListForReview, GetReviewGUIForm(ReviewGUI::Name::NGImageListForReview), ReviewGUI::Name::NGImageListForReview);
	//setButtonState(ui.pbSelectLotForReview, GetReviewGUIForm(ReviewGUI::Name::SelectLotForReview), ReviewGUI::Name::SelectLotForReview);
	//setButtonState(ui.pbShowHistoryListForReview, GetReviewGUIForm(ReviewGUI::Name::ShowHistoryListForReview), ReviewGUI::Name::ShowHistoryListForReview);
	//setButtonState(ui.pbShowThumbnail, GetReviewGUIForm(ReviewGUI::Name::ShowThumbnail), ReviewGUI::Name::ShowThumbnail);
	//setButtonState(ui.pbShowVRSOperation, GetReviewGUIForm(ReviewGUI::Name::ShowVRSOperation), ReviewGUI::Name::ShowVRSOperation);
	//setButtonState(ui.pbWholeImageForReview, GetReviewGUIForm(ReviewGUI::Name::WholeImageForReview), ReviewGUI::Name::WholeImageForReview);

	//for(int i=0; i<ui.tabWidget->count(); i++){
	//	QWidget *widget = ui.tabWidget->widget(i);
	//	bool visible = false;
	//	QObjectList list = widget->children();
	//	for(int j=0; j<list.count(); j++){
	//		QAbstractButton *button = dynamic_cast<QAbstractButton*>(list[j]);
	//		if(button!=NULL){
	//			if(button->isEnabled()==true){
	//				visible = true;
	//			}else{
	//				delete button;
	//			}
	//		}
	//	}

	//	if(visible==false){
	//		ui.tabWidget->removeTab(i);
	//		i--;
	//	}
	//}

	QList<QPair<ReviewCommonPacket::CmdReqSettingPropertyDialog, QPushButton*> > list;

	if(GetLayersBase()->GetLogicDLLBase()==NULL)return;

	LogicDLLBaseClass *logicDLL = GetLayersBase()->GetLogicDLLBase();
	for(LogicDLL *dll=logicDLL->GetFirst();dll!=NULL; dll=dll->GetNext()){
		if(dll->GetInstance()==NULL)continue;
		ReviewCommonPacket::CmdReqSettingPropertyDialog reqPropertyDialog(GetLayersBase());
		dll->GetInstance()->TransmitDirectly( &reqPropertyDialog );
		if(reqPropertyDialog.isValid()==true){
			list << QPair<ReviewCommonPacket::CmdReqSettingPropertyDialog, QPushButton*>(reqPropertyDialog, new QPushButton);
		}
	}

	GUIInstancePack *pack = GetLayersBase()->GetGUIInstancePack();
	if(pack==NULL)return;

	for(GUIItemInstance *inst=pack->NPListPack<GUIItemInstance>::GetFirst(); inst!=NULL; inst=inst->GetNext()){
		if(inst->DLLAccess==NULL || inst->GetForm()==NULL)continue;
		ReviewCommonPacket::CmdReqSettingPropertyDialog reqPropertyDialog(GetLayersBase());
		inst->GetForm()->TransmitDirectly( &reqPropertyDialog );
		if(reqPropertyDialog.isValid()==true){
			list << QPair<ReviewCommonPacket::CmdReqSettingPropertyDialog, QPushButton*>(reqPropertyDialog, new QPushButton);
		}
	}

	QTabWidget *tWid = new QTabWidget;
	for(int i=0; i<list.count(); i++){
		// ルートタブと名前が同じタブを探す
		int tabIndex = -1;
		for(int t=0; t<tWid->count(); t++){
			if(tWid->tabText(t)==list[i].first.groupName()){
				tabIndex = t;
				break;
			}
		}

		// 同じタブが無ければ追加
		if(tabIndex==-1){
			QWidget *wid = new QWidget;

			QLayout *layout = new QVBoxLayout;
			wid->setLayout(layout);

			tWid->addTab(wid, list[i].first.groupName());
			tabIndex = tWid->count()-1;
		}

		// ボタンを追加
		list[i].second->setText(list[i].first.GUIName());
		list[i].second->setMinimumSize( list[i].second->fontMetrics().width(list[i].first.GUIName()) + 30, list[i].second->minimumHeight() );
		tWid->widget(tabIndex)->layout()->addWidget( list[i].second );

		connect(list[i].second, SIGNAL(clicked()), list[i].first.dialog(), SLOT(exec()));
	}

	QGridLayout *mainLayout = new QGridLayout;
	setLayout(mainLayout);
	mainLayout->addWidget(tWid, 0, 0, 1, 1);

	adjustSize();

	QSize s;
	s.setWidth( sizeHint().width() + mainLayout->horizontalSpacing()*2 );
	s.setHeight( sizeHint().height() + mainLayout->verticalSpacing()*2 );

	QRect r;
	r.setTopLeft( geometry().topLeft() );
	r.setSize(s);

	r.setLeft( (qApp->desktop()->width() - s.width()) / 2 );
	r.setTop( (qApp->desktop()->height() - s.height()) / 2 );

	setGeometry(r);
}

void ReviewSettingFormBase::on_pbReviewStructure_clicked(){
	execPropertyDialog( GetReviewAlgorithmBase() );
	ReviewGUI::UpdateHistoryGUIAll(GetLayersBase());
}
void ReviewSettingFormBase::on_pbButtonToShowTotalNGMap_clicked(){
	execPropertyDialog( GetReviewGUIForm(ReviewGUI::Name::ButtonToShowTotalNGMap) );
}
void ReviewSettingFormBase::on_pbListMasterDataAndLoad_clicked(){
	execPropertyDialog( GetReviewGUIForm(ReviewGUI::Name::ListMasterDataAndLoad) );
}
void ReviewSettingFormBase::on_pbLiveCameraAlgoNTSC_clicked(){
	execPropertyDialog( GetReviewGUIForm(ReviewGUI::Name::LiveCameraAlgoNTSC) );
}
void ReviewSettingFormBase::on_pbNGImageForReview_clicked(){
	execPropertyDialog( GetReviewGUIForm(ReviewGUI::Name::NGImageForReview) );
}
void ReviewSettingFormBase::on_pbNGImageListForReview_clicked(){
	execPropertyDialog( GetReviewGUIForm(ReviewGUI::Name::NGImageListForReview) );
}
void ReviewSettingFormBase::on_pbSelectLotForReview_clicked(){
	execPropertyDialog( GetReviewGUIForm(ReviewGUI::Name::SelectLotForReview) );
}
void ReviewSettingFormBase::on_pbShowHistoryListForReview_clicked(){
	execPropertyDialog( GetReviewGUIForm(ReviewGUI::Name::ShowHistoryListForReview) );
}
void ReviewSettingFormBase::on_pbShowThumbnail_clicked(){
	execPropertyDialog( GetReviewGUIForm(ReviewGUI::Name::ShowThumbnail) );
}
void ReviewSettingFormBase::on_pbShowVRSOperation_clicked(){
	execPropertyDialog( GetReviewGUIForm(ReviewGUI::Name::ShowVRSOperation) );
}
void ReviewSettingFormBase::on_pbWholeImageForReview_clicked(){
	execPropertyDialog( GetReviewGUIForm(ReviewGUI::Name::WholeImageForReview) );
}

void ReviewSettingFormBase::execPropertyDialog(AlgorithmBase *ABase){
	ReviewCommonPacket::CmdReqSettingPropertyDialog reqProDlg(GetLayersBase());
	ABase->TransmitDirectly(&reqProDlg);

	if(reqProDlg.isValid()==true){
		reqProDlg.dialog()->exec();
	};
}

void ReviewSettingFormBase::execPropertyDialog(GUIFormBase *GBase){
	if(GBase==NULL){
		return;
	}
	ReviewCommonPacket::CmdReqSettingPropertyDialog reqProDlg(GetLayersBase());
	GBase->TransmitDirectly(&reqProDlg);

	if(reqProDlg.isValid()==true){
		reqProDlg.dialog()->exec();
	};
}

void ReviewSettingFormBase::setButtonState(QAbstractButton *button, GUIFormBase *Base, const QString &text)
{
	if(button==NULL){
		return;
	}
	if(Base==NULL){
		button->setEnabled(false);
		return;
	}
	button->setText(text);

	ReviewCommonPacket::CmdReqSettingPropertyDialog reqProDlg(GetLayersBase());
	Base->TransmitDirectly( &reqProDlg );

	button->setEnabled(reqProDlg.isValid());
}
