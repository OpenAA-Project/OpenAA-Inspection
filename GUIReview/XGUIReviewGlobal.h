#pragma once

#include <QString>

#define GetReviewGUIForm(GUIName) GetLayersBase()->FindByName(ReviewGUI::Name::Root,GUIName,/**/"")

class LayersBase;
class GUIDirectMessage;
class GUIFormBase;

#define GetReviewAlgorithm() (dynamic_cast<ReviewPIBase*>(GetLayersBase()->GetAlgorithmBase(/**/"Review",/**/"ReviewStructure")))
#define MakeReviewAlgorithm(R) ReviewPIBase*R=dynamic_cast<ReviewPIBase*>(GetLayersBase()->GetAlgorithmBase(/**/"Review",/**/"ReviewStructure"))
#define GetReviewAlgorithmBase() (GetLayersBase()->GetAlgorithmBase(/**/"Review",/**/"ReviewStructure"))

class ReviewGUI{
private:
	ReviewGUI(){};
public:
	class Name{
	private:
		Name(){};
	public:
		static const QString Root;
		static const QString ButtonToShowTotalNGMap;
		static const QString ListMasterDataAndLoad;
		static const QString ListStatisticNG;
		static const QString LiveCameraAlgoNTSC;
		static const QString LiveCameraDFK31AF03;
		static const QString LiveCameraMightexUSB3;
		static const QString LiveCameraMightexUSB2;
		static const QString NGImageForReview;
		static const QString NGImageListForReview;
		static const QString SelectLotForReview;
		static const QString ShowHistoryListForReview;
		static const QString ShowThumbnail;
		static const QString ShowVRSOperation;
		static const QString WholeImageForReview;
		static const QString SettingFileBase;
		static const QString ListPiece;

	public:
		static const QStringList GUINameList();
	};

	class DLLFilePath{
	private:
		DLLFilePath(){};
	public:
		static const QString ButtonToShowTotalNGMap;
		static const QString ListMasterDataAndLoad;
		static const QString ListStatisticNG;
		static const QString LiveCameraAlgoNTSC;
		static const QString LiveCameraDFK31AF03;
		static const QString LiveCameraMightexUSB3;
		static const QString LiveCameraMightexUSB2;
		static const QString NGImageForReview;
		static const QString NGImageListForReview;
		static const QString SelectLotForReview;
		static const QString ShowHistoryListForReviewStr;
		static const QString ShowThumbnail;
		static const QString ShowVRSOperation;
		static const QString WholeImageForReview;
	};

	class PropertyGroupName{
	private:
		PropertyGroupName(){};
	public:
		static const QString Global;
		static const QString Standard;
		static const QString Thumbnail;
		static const QString VRS;
	};

	static void ReviewGUIAllUpdate(LayersBase *Base, bool showProgressDialog=false);
	static void ReviewGUICmdSendAll(LayersBase *Base, GUIDirectMessage *packet);
	static void ReviewGUICmdSend(LayersBase *Base, GUIDirectMessage *packet, QString GUIName);
	static bool UpdateGUI(LayersBase *Base, QString GUIName);
	static void UpdateHistoryGUI(LayersBase *Base, QString GUIName);
	static void UpdateLotGUI(LayersBase *Base, QString GUName);
	static void UpdateNGNailGUI(LayersBase *Base, QString GUIName);
	static void UpdateHistoryGUIAll(LayersBase *Base);
	static void UpdateNGNailGUIAll(LayersBase *Base);
	static QList<GUIFormBase *> ReviewGUIExistList(LayersBase *Base);
	static QStringList ReviewGUIExistNameList(LayersBase *Base);
};

class GUILockerBase
{
public:
	GUILockerBase(){
		setGUIEnable(false);
	};
	virtual ~GUILockerBase(){
		setGUIEnable(true);
	};
public:
	virtual void setGUIEnable(bool enable){};
};