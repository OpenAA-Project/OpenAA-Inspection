
#include "XGUIReviewGlobal.h"
#include "XGUIReviewCommonPacket.h"
//#include "XReviewStructure.h"

#include <QMessageBox>

const QString ReviewGUI::Name::Root						= "Review";
const QString ReviewGUI::Name::ButtonToShowTotalNGMap	= "ButtonToShowTotalNGMap";
const QString ReviewGUI::Name::ListMasterDataAndLoad	= "ListMasterDataAndLoad";
const QString ReviewGUI::Name::ListStatisticNG			= "ListStatisticNG";
const QString ReviewGUI::Name::LiveCameraAlgoNTSC		= "LiveCameraAlgoNTSC";
const QString ReviewGUI::Name::LiveCameraDFK31AF03		= "LiveCameraDFK31AF03";
const QString ReviewGUI::Name::LiveCameraMightexUSB3	= "LiveCameraMightexUSB3";
const QString ReviewGUI::Name::LiveCameraMightexUSB2	= "LiveCameraMightexUSB2";
const QString ReviewGUI::Name::NGImageForReview			= "NGImageForReview";
const QString ReviewGUI::Name::NGImageListForReview		= "NGImageListForReview";
const QString ReviewGUI::Name::SelectLotForReview		= "SelectLotForReview";
const QString ReviewGUI::Name::ShowHistoryListForReview	= "ShowHistoryListForReview";
const QString ReviewGUI::Name::ShowThumbnail			= "ShowThumbnail";
const QString ReviewGUI::Name::ShowVRSOperation			= "ShowVRSOperation";
const QString ReviewGUI::Name::WholeImageForReview		= "WholeImageForReview";
const QString ReviewGUI::Name::SettingFileBase			= "ReviewProperty";
const QString ReviewGUI::Name::ListPiece				= "ListPiece";

const QString ReviewGUI::DLLFilePath::ButtonToShowTotalNGMap		= "GUI/" + ReviewGUI::Name::ButtonToShowTotalNGMap		+ ".dll";
const QString ReviewGUI::DLLFilePath::ListMasterDataAndLoad			= "GUI/" + ReviewGUI::Name::ListMasterDataAndLoad		+ ".dll";
const QString ReviewGUI::DLLFilePath::ListStatisticNG				= "GUI/" + ReviewGUI::Name::ListStatisticNG				+ ".dll";
const QString ReviewGUI::DLLFilePath::LiveCameraAlgoNTSC			= "GUI/" + ReviewGUI::Name::LiveCameraAlgoNTSC			+ ".dll";
const QString ReviewGUI::DLLFilePath::LiveCameraDFK31AF03			= "GUI/" + ReviewGUI::Name::LiveCameraDFK31AF03			+ ".dll";
const QString ReviewGUI::DLLFilePath::LiveCameraMightexUSB3			= "GUI/" + ReviewGUI::Name::LiveCameraMightexUSB3		+ ".dll";
const QString ReviewGUI::DLLFilePath::LiveCameraMightexUSB2			= "GUI/" + ReviewGUI::Name::LiveCameraMightexUSB2		+ ".dll";
const QString ReviewGUI::DLLFilePath::NGImageForReview				= "GUI/" + ReviewGUI::Name::NGImageForReview			+ ".dll";
const QString ReviewGUI::DLLFilePath::NGImageListForReview			= "GUI/" + ReviewGUI::Name::NGImageListForReview		+ ".dll";
const QString ReviewGUI::DLLFilePath::SelectLotForReview			= "GUI/" + ReviewGUI::Name::SelectLotForReview			+ ".dll";
const QString ReviewGUI::DLLFilePath::ShowHistoryListForReviewStr	= "GUI/" + ReviewGUI::Name::ShowHistoryListForReview	+ ".dll";
const QString ReviewGUI::DLLFilePath::ShowThumbnail					= "GUI/" + ReviewGUI::Name::ShowThumbnail				+ ".dll";
const QString ReviewGUI::DLLFilePath::ShowVRSOperation				= "GUI/" + ReviewGUI::Name::ShowVRSOperation			+ ".dll";
const QString ReviewGUI::DLLFilePath::WholeImageForReview			= "GUI/" + ReviewGUI::Name::WholeImageForReview			+ ".dll";

const QString ReviewGUI::PropertyGroupName::Global		= "Global";
const QString ReviewGUI::PropertyGroupName::Standard		= "Standard";
const QString ReviewGUI::PropertyGroupName::Thumbnail	= "Thumbnail";
const QString ReviewGUI::PropertyGroupName::VRS			= "VRS";

const QStringList ReviewGUI::Name::GUINameList()
{
	QStringList ret;
	ret << ButtonToShowTotalNGMap << ListMasterDataAndLoad << ListStatisticNG << LiveCameraAlgoNTSC << LiveCameraDFK31AF03 << NGImageForReview << NGImageListForReview
		<< SelectLotForReview << ShowHistoryListForReview << ShowThumbnail << ShowVRSOperation << WholeImageForReview;
	return ret;
}

// 全GUIのクリア
// クリアする内容はGUIコンポーネントによる
void ReviewGUI::ReviewGUIAllUpdate(LayersBase *Base, bool showProgressDialog){
	QMessageBox mbox;
	if(showProgressDialog==true){
		mbox.setParent(Base->GetMainWidget());
		mbox.setWindowModality(Qt::WindowModal);
		mbox.setStandardButtons(QMessageBox::StandardButton::NoButton);
		mbox.repaint();
	}
	GUICmdReviewUpdateLocal Send(Base);
	ReviewGUICmdSendAll(Base, &Send);
}

void ReviewGUI::ReviewGUICmdSendAll(LayersBase *Base, GUIDirectMessage *packet)
{
	ReviewGUICmdSend(Base, packet, ReviewGUI::Name::ButtonToShowTotalNGMap);
	ReviewGUICmdSend(Base, packet, ReviewGUI::Name::ListMasterDataAndLoad);
	ReviewGUICmdSend(Base, packet, ReviewGUI::Name::ListStatisticNG);
	ReviewGUICmdSend(Base, packet, ReviewGUI::Name::LiveCameraAlgoNTSC);
	ReviewGUICmdSend(Base, packet, ReviewGUI::Name::LiveCameraDFK31AF03);
	ReviewGUICmdSend(Base, packet, ReviewGUI::Name::LiveCameraMightexUSB3);
	ReviewGUICmdSend(Base, packet, ReviewGUI::Name::LiveCameraMightexUSB2);
	ReviewGUICmdSend(Base, packet, ReviewGUI::Name::NGImageForReview);
	ReviewGUICmdSend(Base, packet, ReviewGUI::Name::NGImageListForReview);
	ReviewGUICmdSend(Base, packet, ReviewGUI::Name::SelectLotForReview);
	ReviewGUICmdSend(Base, packet, ReviewGUI::Name::ShowHistoryListForReview);
	ReviewGUICmdSend(Base, packet, ReviewGUI::Name::ShowThumbnail);
	ReviewGUICmdSend(Base, packet, ReviewGUI::Name::ShowVRSOperation);
	ReviewGUICmdSend(Base, packet, ReviewGUI::Name::WholeImageForReview);
}

void ReviewGUI::ReviewGUICmdSend(LayersBase *Base, GUIDirectMessage *packet, QString GUIName){
	GUIFormBase *GUIBase = Base->FindByName(ReviewGUI::Name::Root, GUIName, "");
	if(GUIBase!=NULL)GUIBase->TransmitDirectly(packet);
}

bool ReviewGUI::UpdateGUI(LayersBase *Base, QString GUIName){
	GUIFormBase *GUIForm = Base->FindByName(Name::Root, GUIName, "");
	if(GUIForm!=NULL){
		GUICmdReviewUpdateLocal UpdateCmd(Base);
		GUIForm->TransmitDirectly(&UpdateCmd);
		return UpdateCmd.Ret;
	}
	return false;
}

void ReviewGUI::UpdateHistoryGUI(LayersBase *Base, QString GUIName){
	GUIFormBase *GUIForm = Base->FindByName(Name::Root, GUIName, "");
	if(GUIForm!=NULL){
		GUICmdUpdateCurrentHistory UpdateCmd(Base);
		GUIForm->TransmitDirectly(&UpdateCmd);
	}
}

void ReviewGUI::UpdateLotGUI(LayersBase *Base, QString GUIName){
	GUIFormBase *GUIForm = Base->FindByName(Name::Root, GUIName, "");
	if(GUIForm!=NULL){
		GUICmdUpdateCurrentLot UpdateCmd(Base);
		GUIForm->TransmitDirectly(&UpdateCmd);
	}
}


void ReviewGUI::UpdateNGNailGUI(LayersBase *Base, QString GUIName){
	GUIFormBase *GUIForm = Base->FindByName(Name::Root, GUIName, "");
	if(GUIForm!=NULL){
		GUICmdUpdateCurrentNGNail UpdateCmd(Base);
		GUIForm->TransmitDirectly(&UpdateCmd);
	}
}

void ReviewGUI::UpdateHistoryGUIAll(LayersBase *Base){
	GUICmdUpdateCurrentHistory Cmd(Base);
	ReviewGUICmdSendAll(Base, &Cmd);
}

void ReviewGUI::UpdateNGNailGUIAll(LayersBase *Base){
	GUICmdUpdateCurrentNGNail Cmd(Base);
	ReviewGUICmdSendAll(Base, &Cmd);
}

QList<GUIFormBase *> ReviewGUI::ReviewGUIExistList(LayersBase *Base)
{
	QStringList list = Name::GUINameList();
	QList<GUIFormBase *> retList;

	for(int i=0; i<list.count(); i++){
		GUIFormBase *gui = Base->FindByName(Name::Root, list[i], "");
		if(gui!=NULL){
			retList.append(gui);
		}
	}
	
	return retList;
}

QStringList ReviewGUI::ReviewGUIExistNameList(LayersBase *Base)
{
	QStringList list = Name::GUINameList();
	QStringList ret;

	for(int i=0; i<list.count(); i++){
		if(Base->FindByName(Name::Root, list[i], "")!=NULL){
			ret.append(list[i]);
		}
	}
	
	return ret;
}