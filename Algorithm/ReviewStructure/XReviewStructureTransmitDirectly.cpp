#include "XDatabaseLoader.h"
#include "XOutlineOffset.h"

#include "XReviewStructure.h"
#include "ReviewStructurePacket.h"
#include "DXMLParser.h"
#include "XMLWriter.h"
#include "XReviewCommonPacket.h"
#include "ReviewStructureVRSSetting.h"
#include "XTransFile.h"
#include "XParamDatabase.h"
#include <QProgressDialog>
#include "XGeneralFunc.h"

void ReviewPIInPage::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdLoadSlave	*CmdLoadSlaveVar=dynamic_cast<CmdLoadSlave *>(packet);
	if(CmdLoadSlaveVar!=NULL){
		if((CmdLoadSlaveVar->Ret=LoadSlave(	 CmdLoadSlaveVar->MasterCode
										,CmdLoadSlaveVar->MachineID
										,CmdLoadSlaveVar->PhaseCode))==false){
											//QMessageBox::warning(NULL, "Master Image Load Error", "Master Image can not be loaded");
		}
		return;
	}
}

void ReviewPIBase::TransmitDirectly(GUIDirectMessage *packet)
{
	// マスターデータ読み込み要求
	if(ReciveCmdLoadMainMaster(packet))return;

	// スレーブ読み込み要求
	if(ReciveCmdLoadSlave(packet))return;

	if(ReciveCmdLoadPageImage(packet))return;

	// マスターコードからロット一覧を取得
	if(ReciveCmdServerSelectLotList(packet))return;

	// ロットを指定したファイル名、サイドにセットする
	if(ReciveCmdServerSetLot(packet))return;

	// 読み込んであるマスターデータに対応するロット一覧を要求する
	if(ReciveCmdServerReqCurrentLot(packet))return;

	// ロットの検査リスト一覧を書き込み、戻す
	if(ReciveCmdReqOrganizedHistoryList(packet))return;

	// ロットを現在の状態に更新する
	if(ReciveCmdServerUpdateLotList(packet))return;

	// カレントNGにFキー情報を付与・もしくは上書きする
	if(ReciveCmdSetFKeyToNGNail(packet))return;

	// NGNailのFキー情報をFキー情報なしにする
	if(ReciveCmdClearFKeyToNGNail(packet))return;

	// 全体画像を要求する
	if(ReciveCmdReqWholeImage(packet))return;

	// 現在履歴を設定する
	if(ReciveCmdSetCurrentHistory(packet))return;

	// 現在履歴を要求する
	if(ReciveCmdReqCurrentHistory(packet))return;

	// 現在ロットをリロードして現在履歴を更新する
	if(ReciveCmdUpdateCurrentLotData(packet))return;

	// ライブラリ情報を要求する
	if(ReciveCmdReqInsLib(packet))return;

	// NGNailのソート順を変更する
	if(ReciveCmdSetSortNGOrder(packet))return;

	// NGNailのソート順を取得する
	if(ReciveCmdReqSortNGOrder(packet))return;

	// 現在NGNailの周辺情報を要求する
	if(ReciveCmdReqAdjacentCurrentNG(packet))return;

	// 現在NGNailを移動する
	if(ReciveCmdMoveCurrentNGNail(packet))return;

	// 現在履歴を移動する
	if(ReciveCmdMoveCurrentHistory(packet))return;

	// 現在履歴をNGまで移動する
	if(ReciveCmdMoveCurrentHistoryToNGBoard(packet))return;

	// 現在NGNailを移動する
	if(ReciveCmdSetCurrentNGNail(packet))return;

	// お見込んでいるマスターデータの情報を取得する
	if(ReciveCmdReqMasterDataInfo(packet))return;

	// 現在のNGをチェック済みにする
	if(ReciveCmdSetCurrentNGChecked(packet))return;

	// 現在HistoryのNGNailにチェック済み情報を付与する
	if(ReciveCmdSetNGChecked(packet))return;

	// Fキーカラーリストを要求する
	if(ReciveCmdReqFKeyColorList(packet))return;

	// ReviewStructureが保持するマスター画像のイメージメモリの更新を促す
	if(ReciveCmdUpdateMasterBuff(packet))return;

	// マスター画像から切り抜いた一部分画像を要求する
	if(ReciveCmdReqMasterImagePiece(packet))return;

	// 一枚絵にしたマスター画像から部分画像のコピーを要求する
	if(ReciveCmdReqMasterImagePieceOnOneImage(packet))return;

	// 指定した履歴の全チェック状態を確認する
	if(ReciveCmdReqHistoryAllChecked(packet))return;

	// マスター画像の情報を要求する
	if(ReciveCmdReqWholeImageInfo(packet))return;

	// 指定したNGの番号から該当NGの表示形状を返す
	//if(ReciveCmdReqNGShape(packet))return;

	// 現在履歴のNGNailリストをNG表示形状付きで返す
	//if(ReciveCmdReqCurrentNGPointListWithShape(packet))return;

	// 履歴のソートを行う
	if(ReciveCmdSetSortHistoryOrder(packet))return;

	// 履歴のソート設定を返す
	if(ReciveCmdReqSortHistoryOrder(packet))return;

	// マスターデータをデータベースから要求する
	if(ReciveCmdReqMasterInfoFromDataBase(packet))return;

	// レイヤーのイメージメモリを開放する
	if(ReciveCmdFreeLayersImageMemory(packet))return;

	// 指定サイドのロット情報を削除する
	if(ReciveCmdClearSideLot(packet))return;

	// PCEのリストを取得する
	if(ReciveCmdReqPCEList(packet))return;

	// NG保存のマクロリストを取得する
	if(ReciveCmdReqSaveFormatMacroList(packet))return;

	// プロパティ設定ダイアログを提供する
	if(ReciveCommonCmdReqSettingPropertyDialog(packet))return;

	// NG画像の保存(現在NGNailのみ)
	if(ReciveCmdSaveCurrentNGImage(packet))return;

	// NG画像の保存(現在履歴のすべてのNGNail)
	if(ReciveCmdSaveCurrentHistoryNGImages(packet))return;

	// 現在読み込んでいるマスターデータに従い、ロットの情報を更新する
	if(ReciveCmdUpdateLotInfoList(packet))return;

	// 現在のロット一覧を取得する
	if(ReciveCmdReqCurrentLotAllList(packet))return;

	// VRSの情報を要求する
	if(ReciveCmdReqVRSSetting(packet))return;

	// VRSの情報を設定する
	if(ReciveCmdSetVRSSetting(packet))return;

	// マスター画像のリストを要求する
	if(ReciveCmdReqMasterImageList(packet))return;

	// 現在のVRS用アライメント設定を要求する
	if(ReciveCmdReqVRSAlignment(packet))return;

	// VRS用アライメントを設定する
	if(ReciveCmdSetVRSAlignment(packet))return;

	// VRSのモーター状況を要求する
	if(ReciveCmdReqVRSMotorState(packet))return;

	// VRSのモーター状況を設定する
	if(ReciveCmdSetVRSMotorState(packet))return;

	// カメラのアライメントを取得する
	if(ReciveCmdReqCameraAlignment(packet))return;

	// カメラのアライメントを設定する
	if(ReciveCmdSetCameraAlignment(packet))return;

	// シーケンスへの入力が行われているかを取得する
	if(ReciveCmdReqSequenceEnable(packet))return;

	// シーケンスへの入力を設定する
	if(ReciveCmdSetSequenceEnable(packet))return;

	// 現在NGの位置へ移動する
	if(ReciveCmdMoveVRSToCurrentNG(packet))return;

	// 微動
	if(ReciveCmdMoveVRSOnCameraView(packet))return;

	// XY移動(アライメント適用)
	if(ReciveCmdMoveVRSWithAlignment(packet))return;

	// 原点移動
	if(ReciveCmdMoveVRSToOrigin(packet))return;

	// 緊急回避地点移動
	if(ReciveCmdMoveVRSToEscape(packet))return;

	// マスター画像のダイレクトロード
	if(ReciveCmdLoadMasterImage(packet))return;

	// マスターのロード
	if(ReciveCmdLoadMaster(packet))return;

	// 現在の読み込みロットの要求
	if(ReciveCmdReqCurrentLotInfo(packet))return;
	
	// 直接指定VRS移動
	if(ReciveCmdMoveVRSDirectory(packet))return;

	// 共通VRS移動
	//if(ReciveCommonCmdMoveVRSWithAlignment(packet))return;
	//if(ReciveCommonCmdMoveVRSToOrigin(packet))return;

	CmdSetMachineID	*CmdSetMachineIDVar=dynamic_cast<CmdSetMachineID *>(packet);
	if(CmdSetMachineIDVar!=NULL){
		m_FrontMasterInfo.MachineID	=CmdSetMachineIDVar->MachineIDFront;
		m_BackMasterInfo.MachineID	=CmdSetMachineIDVar->MachineIDBack;

		loadOutlineOffset(Review::Front	, m_FrontMasterInfo.MachineID,m_FrontMasterInfo.MasterCode);
		loadOutlineOffset(Review::Back	, m_BackMasterInfo.MachineID ,m_BackMasterInfo.MasterCode );

		appendVRSAlignment(Review::Front, m_FrontMasterInfo.MachineID);
		return;
	}
	CmdSetOffsetVRS	*CmdSetOffsetVRSVar=dynamic_cast<CmdSetOffsetVRS *>(packet);
	if(CmdSetOffsetVRSVar!=NULL){
		VRSOffsetX=VRSDiffX;
		VRSOffsetY=VRSDiffY;
		return;
	}
	CmdResetDiffVRS	*CmdResetDiffVRSVar=dynamic_cast<CmdResetDiffVRS *>(packet);
	if(CmdResetDiffVRSVar!=NULL){
		VRSDiffX=0;
		VRSDiffY=0;
		return;
	}
	CmdAddDiffVRSX	*CmdAddDiffVRSXVar=dynamic_cast<CmdAddDiffVRSX *>(packet);
	if(CmdAddDiffVRSXVar!=NULL){
		VRSDiffX+=CmdAddDiffVRSXVar->Dx;
		return;
	}
	CmdAddDiffVRSY	*CmdAddDiffVRSYVar=dynamic_cast<CmdAddDiffVRSY *>(packet);
	if(CmdAddDiffVRSYVar!=NULL){
		VRSDiffY+=CmdAddDiffVRSYVar->Dy;
		return;
	}
	CmdAddDiffVRSXY	*CmdAddDiffVRSXYVar=dynamic_cast<CmdAddDiffVRSXY *>(packet);
	if(CmdAddDiffVRSXYVar!=NULL){
		VRSDiffX+=CmdAddDiffVRSXYVar->Dx;
		VRSDiffY+=CmdAddDiffVRSXYVar->Dy;
		return;
	}
	CmdReqCurrentLotInfoData	*CmdReqCurrentLotInfoDataVar=dynamic_cast<CmdReqCurrentLotInfoData *>(packet);
	if(CmdReqCurrentLotInfoDataVar!=NULL){
		LotInfoItem FrontLot	=getCurrentLotInfo(Review::Front);
		LotInfoItem BackLot		=getCurrentLotInfo(Review::Back);
		CmdReqCurrentLotInfoDataVar	->FrontLotID	=FrontLot.LotName;
		CmdReqCurrentLotInfoDataVar	->FrontLotName	=FrontLot.TableName;
		CmdReqCurrentLotInfoDataVar	->BackLotID		=BackLot.LotName;
		CmdReqCurrentLotInfoDataVar	->BackLotName	=BackLot.TableName;
		return;
	}
	CmdUpdateForSaveLotList	*CmdUpdateForSaveLotListVar=dynamic_cast<CmdUpdateForSaveLotList *>(packet);
	if(CmdUpdateForSaveLotListVar!=NULL){
		InitialCSVLotList();
		LoadCSV();
		return;
	}
	CmdReqForSaveBundle	*CmdReqForSaveBundleVar=dynamic_cast<CmdReqForSaveBundle *>(packet);
	if(CmdReqForSaveBundleVar!=NULL){
		SaveBundleOnHistry(CmdReqForSaveBundleVar->CurerntRow , CmdReqForSaveBundleVar->InspectionID ,CmdReqForSaveBundleVar->InspectionTime);
		return;
	}
	CmdReqForSaveNGList	*CmdReqForSaveNGListVar=dynamic_cast<CmdReqForSaveNGList *>(packet);
	if(CmdReqForSaveNGListVar!=NULL){
		for(ForSaveOneInspection *c=CurrentBundle.HistryList.GetFirst();c!=NULL;c=c->GetNext()){
			if(c->LineNumber==CurrentBundle.CurrentRow){
				for(ForSaveNGPoint *h=CmdReqForSaveNGListVar->Data.NGList.GetFirst();h!=NULL;h=h->GetNext()){
					ForSaveNGPoint	*k=c->FindByLineNumber(h->LineNumber);
					if(k==NULL){
						ForSaveNGPoint	*kk=new ForSaveNGPoint(h->LineNumber);
						*kk=*h;
						c->NGList.AppendList(kk);
					}
				}
				break;
			}
		}
		return;
	}
	CmdSetCurrentRowNGListForSave	*CmdSetCurrentRowNGListForSaveVar=dynamic_cast<CmdSetCurrentRowNGListForSave *>(packet);
	if(CmdSetCurrentRowNGListForSaveVar!=NULL){
		if(CurrentBundle.FocusPoint!=NULL){
			CurrentBundle.FocusPoint->Leaving	=XDateTime::currentDateTime();
		}
		for(ForSaveOneInspection *c=CurrentBundle.HistryList.GetFirst();c!=NULL;c=c->GetNext()){
			if(c->LineNumber==CurrentBundle.CurrentRow){
				ForSaveNGPoint	*k=c->FindByLineNumber(CmdSetCurrentRowNGListForSaveVar->CurrentRow);
				if(k!=NULL){
					CurrentBundle.FocusPoint=k;
					CurrentBundle.FocusPoint->Entering=XDateTime::currentDateTime();
					if(CurrentBundle.FocusPoint->FnKeyNumber<0){
						CurrentBundle.FocusPoint->FnKeyNumber=-1;
					}
				}
				break;
			}
		}
		return;
	}
	CmdSetCurrentNGInfo	*CmdSetCurrentNGInfoVar=dynamic_cast<CmdSetCurrentNGInfo *>(packet);
	if(CmdSetCurrentNGInfoVar!=NULL){
		CurrentBundle.NGCountTop	=CmdSetCurrentNGInfoVar->NGCountTop;
		CurrentBundle.NGCountBack	=CmdSetCurrentNGInfoVar->NGCountBack;
		CurrentBundle.InspectionTimeFirst	=CmdSetCurrentNGInfoVar->InspectionTimeFirst;
		CurrentBundle.InspectionTimeLast	=CmdSetCurrentNGInfoVar->InspectionTimeLast;
		CurrentBundle.InspectedMachine		=CmdSetCurrentNGInfoVar->InspectedMachine;
		CurrentBundle.ReviewWorkerID		=GetLayersBase()->GetWorkerID();
		CurrentBundle.ReviewWorkerName		=GetLayersBase()->GetWorkerName();
		return;
	}
	CmdSetHaltForSave	*CmdSetHaltForSaveVar=dynamic_cast<CmdSetHaltForSave *>(packet);
	if(CmdSetHaltForSaveVar!=NULL){
		for(ForSaveOneInspection *c=CurrentBundle.HistryList.GetFirst();c!=NULL;c=c->GetNext()){
			if(c->LineNumber==CurrentBundle.CurrentRow){
				c->Halt=CmdSetHaltForSaveVar->Halt;
				break;
			}
		}
		return;
	}
	CmdSetCountOkNgForSave	*CmdSetCountOkNgForSaveVar=dynamic_cast<CmdSetCountOkNgForSave*>(packet);
	if(CmdSetCountOkNgForSaveVar!=NULL){
		CurrentBundle.CountOK	=CmdSetCountOkNgForSaveVar->CountOK;
		CurrentBundle.CountNG	=CmdSetCountOkNgForSaveVar->CountNG;
		CurrentBundle.CountHalt	=CmdSetCountOkNgForSaveVar->CountHalt;
		return;
	}
	CmdSetFKeyForSave	*CmdSetFKeyForSaveVar=dynamic_cast<CmdSetFKeyForSave *>(packet);
	if(CmdSetFKeyForSaveVar!=NULL){
		if(CurrentBundle.FocusPoint!=NULL){
			CurrentBundle.FocusPoint->FnKeyNumber=(int)CmdSetFKeyForSaveVar->Key;
		}
		return;
	}
	CmdRemoveFKeyForSave	*CmdRemoveFKeyForSaveVar=dynamic_cast<CmdRemoveFKeyForSave *>(packet);
	if(CmdRemoveFKeyForSaveVar!=NULL){
		if(CurrentBundle.FocusPoint!=NULL){
			CurrentBundle.FocusPoint->FnKeyNumber=-1;
		}
		return;
	}
	CmdReqCSVOffset	*CmdReqCSVOffsetVar=dynamic_cast<CmdReqCSVOffset *>(packet);
	if(CmdReqCSVOffsetVar!=NULL){
		CmdReqCSVOffsetVar->CSVUnitMM	=getProperty().CSVUnitMM;
		CmdReqCSVOffsetVar->CSVOffsetX	=getProperty().CSVOffsetX;
		CmdReqCSVOffsetVar->CSVOffsetY	=getProperty().CSVOffsetY;
		CmdReqCSVOffsetVar->CSVReverseX	=getProperty().CSVReverseX;
		CmdReqCSVOffsetVar->CSVReverseY	=getProperty().CSVReverseY;
		CmdReqCSVOffsetVar->CSVMagnificationX	=getProperty().CSVMagnificationX;
		CmdReqCSVOffsetVar->CSVMagnificationY	=getProperty().CSVMagnificationY;
		return;
	}

}


bool ReviewPIBase::ReciveCmdLoadMainMaster(GUIDirectMessage *packet)
{
	CmdLoadMainMaster *cmd = dynamic_cast<CmdLoadMainMaster *>(packet);
	if(cmd==NULL)return false;

	int32	iMachineID;
	int		iPhaseNumb;

	MasterDataInfo MInfo;

	bool addMode = Review::isBack(cmd->side);

	// マスターデータ読み込み
	bool ret = LoadMaster(	cmd->side,
							cmd->PhaseCode,
							cmd->MasterCode,
							iMachineID,
							iPhaseNumb,
							MInfo,
							addMode);

	// 結果格納・失敗時終了
	cmd->Ret = ret;
	if(ret==false)return true;

	MasterDataInfo *TargetMasterInfo;
	QList<QList<QImage> > *TargetImageList;
	QList<QSize> *TargetWholeImgSize;
	QList<QList<QPoint> > *TargetMasterWholeImgDrawPoints;
	QList<QList<QPoint> > *TargetOutlines;

	TargetMasterInfo = getMasterInfoPtr(cmd->side);
	TargetImageList = getMasterWholePageImageListPtr(cmd->side);
	TargetWholeImgSize = getMasterWholeImageSizePtr(cmd->side);
	TargetMasterWholeImgDrawPoints = getMasterWholeImgDrawPointsPtr(cmd->side);
	TargetOutlines = getMasterWholePageOutlineListPtr(cmd->side);

	// 情報の保存
	*TargetMasterInfo = MInfo;

	// 画像バッファの確保（中身は空）
	while(TargetImageList->count()<MInfo.PhaseNumb){
		TargetImageList->append(QVector<QImage>(MInfo.PageNumb).toList());
	}
	for(int phase=0; phase<TargetImageList->count(); phase++){
		while(TargetImageList->at(phase).count()<MInfo.PageNumb){
			(*TargetImageList)[phase].append(QImage());
		}
	}

	// 全体画像サイズバッファの確保
	while(TargetWholeImgSize->count()<MInfo.PhaseNumb){
		TargetWholeImgSize->append(QSize());
	}

	// アウトラインバッファの確保
	while(TargetOutlines->count()<MInfo.PhaseNumb){
		TargetOutlines->append(QList<QPoint>());
	}

	for(int phase=0; phase<getMasterWholePageOutlineList(Review::Front).count(); phase++){
		while((*TargetOutlines)[phase].count()<MInfo.PageNumb){
			(*TargetOutlines)[phase].append(QPoint());
		}
	}

	int backPhaseNumb = 0;
	if(getMasterInfo(Review::Back).isEmpty()==false){
		backPhaseNumb += getMasterInfo(Review::Back).PhaseNumb;
	}
	if(Review::isFront(cmd->side)==true){
		for(int phase=0; phase<GetLayersBase()->GetPhaseNumb()-backPhaseNumb; phase++){
			for(int page=0; page<GetLayersBase()->GetPageNumb(); page++){
				OutlineOffsetInBlob blob(GetLayersBase());

				GetLayersBase()->GetDatabaseLoader()->G_SQLLoadOutlineOfset(GetDatabase(), iMachineID, &blob);

				(*TargetOutlines)[phase][page] = QPoint(blob.GetData(phase, page).Dx, blob.GetData(phase, page).Dy);

				//(*TargetOutlines)[phase][page] = QPoint( GetLayersBase()->GetPhaseData()[phase]->GetPageData(page)->GetOutlineOffset()->x
				//	,GetLayersBase()->GetPhaseData()[phase]->GetPageData(page)->GetOutlineOffset()->y);
			}
		}
	}else{
		for(int phase=backPhaseNumb; phase<GetLayersBase()->GetPhaseNumb(); phase++){
			for(int page=0; page<GetLayersBase()->GetPageNumb(); page++){
				OutlineOffsetInBlob blob(GetLayersBase());

				GetLayersBase()->GetDatabaseLoader()->G_SQLLoadOutlineOfset(GetDatabase(), iMachineID, &blob);

				(*TargetOutlines)[phase-backPhaseNumb][page] = QPoint(blob.GetData(phase, page).Dx, blob.GetData(phase, page).Dy);

				//(*TargetOutlines)[phase-backPhaseNumb][page] = QPoint( GetLayersBase()->GetPhaseData()[phase]->GetPageData(page)->GetOutlineOffset()->x
				//	,GetLayersBase()->GetPhaseData()[phase]->GetPageData(page)->GetOutlineOffset()->y);
			}
		}
	}

	// 描画位置バッファの確保
	while(TargetMasterWholeImgDrawPoints->count()<MInfo.PhaseNumb){
		TargetMasterWholeImgDrawPoints->append(QList<QPoint>());
	}

	for(int phase=0; phase<MInfo.PhaseNumb; phase++){
		while((*TargetMasterWholeImgDrawPoints)[phase].count()<MInfo.PageNumb){
			(*TargetMasterWholeImgDrawPoints)[phase].append(QPoint());
		}
	}

	// 戻り値を格納
	cmd->MachineID	=iMachineID;
	cmd->PhaseCount=iPhaseNumb;

	// マシンIDとマスターコードを設定
	GetLayersBase()->SetMachineID(iMachineID);
	GetLayersBase()->SetMasterCode(cmd->MasterCode);

	//QStringList a;
	//XML_GetLot(cmd->MasterCode, iMachineID, a);

	//int PageNum = GetLayersBase()->GetPageNumb();

	appendVRSAlignment(cmd->side, iMachineID);
	getVRSAlignment(cmd->side).setPageCount(MInfo.PageNumb);

	return true;
}

bool ReviewPIBase::ReciveCmdLoadSlave(GUIDirectMessage *packet)
{
	CmdLoadSlave *cmd = dynamic_cast<CmdLoadSlave *>(packet);
	if(cmd==NULL)return false;

	AlgorithmInPageInOnePhase	*Ph=GetPageDataPhase(cmd->PhaseCode);
	if(Ph!=NULL){
		AlgorithmInPageRoot	*Pg=Ph->GetPageData(cmd->LocalPage);
		if(Pg!=NULL){
			Pg->TransmitDirectly(cmd);
		}
	}

	cmd->Ret = true;
	return true;
}

bool ReviewPIBase::ReciveCmdLoadPageImage(GUIDirectMessage *packet)
{
	CmdLoadPageImage *cmd = dynamic_cast<CmdLoadPageImage *>(packet);
	if(cmd==NULL)return false;
	
	// ターゲットの確認
	QList<QImage> *TargetPageImages;
	TargetPageImages = getMasterWholePageImageListPtr(cmd->side, cmd->Phase);
	//if(cmd->side==Review::Front){
	//	TargetPageImages = &(FrontPageImages[cmd->Phase]);
	//}else{
	//	TargetPageImages = &(BackPageImages[cmd->Phase]);
	//}

	// ページ数を調整
	while(TargetPageImages->count()<GetPageNumb()){
		TargetPageImages->append(QList<QImage>());
	}

	QStringList pathList = GetParamGlobal()->ImageFilePath.split(/**/';', QString::SkipEmptyParts);
	
	if(pathList.isEmpty()){
		cmd->Ret = false;
		return true;
	}

	for(int i=0; i<TargetPageImages->count(); i++){
		// ファイル名の作成
		QString Sep=/**/"";
		QChar s = GetParamGlobal()->ImageFilePath[GetParamGlobal()->ImageFilePath.count()-1];
		if(s.cell()!=/**/'/' && s.cell()!=/**/'\\'){
			Sep = GetSeparator();
		}
		QString	rightPath;
		if(cmd->Phase==0){
			rightPath = Sep
				+QString(/**/"Image")+QString::number(cmd->MasterCode)+QString(/**/"-")
				+QString(/**/"Page")+QString::number(GetLayersBase()->GetGlobalPageFromLocal(i))+QString(/**/"-")
				+QString(/**/"Mac")+QString::number(cmd->MachineID)
				+QString(/**/".img");
		}
		else{
			rightPath = Sep
				+QString(/**/"Image")+QString::number(cmd->MasterCode)+QString(/**/"-")
				+QString(/**/"Phase")+QString::number(cmd->Phase)+QString(/**/"-")
				+QString(/**/"Page")+QString::number(GetLayersBase()->GetGlobalPageFromLocal(i))+QString(/**/"-")
				+QString(/**/"Mac")+QString::number(cmd->MachineID)
				+QString(/**/".img");
		}

		if(GetParamGlobal()->ImageFileCachePort==0){
			int existInd = -1;
			for(int pathInd=0; pathInd<pathList.count(); pathInd++){
				if(QFile::exists(pathList[pathInd] + rightPath)==true){
					existInd = pathInd;
					break;
				}
			}

			if(existInd==-1){
				continue;
			}
			QFile file(pathList[existInd] + rightPath);
		
			if(file.open(QIODevice::ReadOnly)==false){
				cmd->Ret = false;
				return true;
			}

			LoadPageImage(file ,(*TargetPageImages)[i],cmd->Ret);
		}
		else{
			int existInd = -1;
			for(int pathInd=0; pathInd<pathList.count(); pathInd++){
				TrFile	file(pathList[pathInd] + rightPath
							,GetParamGlobal()->TransDatabaseIP
							,GetParamGlobal()->ImageFileCachePort);
				if(file.exists()==true){
					existInd = pathInd;
					if(file.open(QIODevice::ReadOnly)==false){
						cmd->Ret = false;
						return true;
					}

					LoadPageImage(file ,(*TargetPageImages)[i],cmd->Ret);
					break;
				}
			}
		}
	}

	//for(int i=0; i<TargetPageImages->count(); i++){
	//	(*TargetPageImages)[i].save(QString("Test%1.jpg").arg(i), "JPG");
	//}

	cmd->Ret = true;
	return true;
}

bool ReviewPIBase::LoadPageImage(QIODevice &file ,QImage &TargetPageImages,bool &Ret)
{
	if(file.open(QIODevice::ReadOnly)==false){
		Ret = false;
		return true;
	}

	// ファイルの読み込み
	int iMaxX,iMaxY,iMemoryType;
	int iPage;
	int	Ver;

	if(file.read((char *)&Ver,sizeof(Ver))!=sizeof(Ver)){
		return false;
	}
	
	if(Ver==2){
		for(int layer=0; layer<GetLayerNumb(0); layer++){
			
		}
		if(file.read((char *)&iPage,sizeof(iPage))!=sizeof(iPage)){
			return false;
		}
		if(file.read((char *)&iMemoryType,sizeof(iMemoryType))!=sizeof(iMemoryType)){
			return false;
		}
		if(file.read((char *)&iMaxX,sizeof(iMaxX))!=sizeof(iMaxX)){
			return false;
		}
		if(file.read((char *)&iMaxY,sizeof(iMaxY))!=sizeof(iMaxY)){
			return false;
		}
		if(iPage>=0 && iMaxX>0 && iMaxY>0){

			TargetPageImages = QImage(iMaxX, iMaxY, QImage::Format_RGB32);
			for(int y=0;y<iMaxY;y++){
				if(file.read((char *)TargetPageImages.scanLine(y),iMaxX)!=iMaxX){
					Ret = false;
					return true;
				}
			}
		}
		else{
			BYTE	*Dummy=new BYTE[iMaxX];
			for(int y=0;y<iMaxY;y++){
				if(file.read((char *)Dummy,iMaxX)!=iMaxX){
					delete	[]Dummy;
					Ret = false;
					return true;
				}
			}
			delete	[]Dummy;
		}
	}else{
		Ret = false;
		return true;
	}
	return true;
}


bool ReviewPIBase::ReciveCmdServerSelectLotList(GUIDirectMessage *packet)
{
	CmdServerSelectLotList *cmd = dynamic_cast<CmdServerSelectLotList *>(packet);
	if(cmd==NULL)return false;

	int MasterCode	= cmd->MasterCode;
	int MachineID	= cmd->MachineID;

	LotInfoList list;
	
	QStringList enumLotFileList;

	if(XML_GetLot(MasterCode, MachineID, enumLotFileList)==false){
		cmd->Ret = false;
		return true;
	}
	
	XMLOpener opener(this);
	if(opener.isOpen()==false){
		cmd->Ret = false;
		return true;
	}

	QProgressDialog progDiag(QString(/**/"MasterCode : %1\nMachineID : %2\n\tGetting infomation of Lots").arg(cmd->MasterCode).arg(cmd->MachineID), "Cancel after", 0, enumLotFileList.count(), GetLayersBase()->GetMainWidget());
	progDiag.setWindowModality(Qt::WindowModal);

	for(int i=0; i<enumLotFileList.count(); i++){
		LotInfoItem thisLot = XML_GetLotInfo(enumLotFileList[i]);
		if(thisLot.LotName=="(irregularity)"){
			continue;
		}
		list.append(thisLot);
		progDiag.setValue(i);

		qApp->processEvents();
		if(progDiag.wasCanceled()==true){
			break;
		}
	}
	/*
	for(int i=progDiag.value()+1; i<enumLotFileList.count(); i++){
		LotInfoItem thisLot;
		thisLot.MasterCode = MasterCode;
		thisLot.MachineCode = MachineID;
		thisLot.TableName = enumLotFileList[i];
		thisLot.LotName = "(canceled)";
		thisLot.Remark = thisLot.LotName;

		list.append(thisLot);
	}
	*/
	
	cmd->list = list;// 呼び出し元へ送り返し

	cmd->Ret = true;

	//XML_Close();

	return true;
}

bool ReviewPIBase::ReciveCmdServerSetLot(GUIDirectMessage *packet)
{
	CmdServerSetLot *cmd = dynamic_cast<CmdServerSetLot *>(packet);
	if(cmd==NULL)return false;
	
	XMLOpener opener(this);
	if(opener.isOpen()==false){
		cmd->Ret = false;
		return true;
	}

	MasterDataInfo info = getMasterInfo(cmd->side);

	if(info.MasterCode==-1 || info.MachineID==-1){
		XML_ClearLot(cmd->side);
		cmd->Ret = true;
		return true;
	}

	bool ok = XML_SetLotToSide(cmd->LotFileName, cmd->side);
	if(ok==true){
		cmd->Ret = true;
	}else{
		cmd->Ret = false;
	}

	setCurrentOrganizedHistory(Review::ListLocate::First);
	//LastOrganizedHistory = OrganizedHistoryList::Iterator();
	//CurrentOrganizedHistory = getHistoryPackIterator(0);
	//NextOrganizedHistory = getHistoryPackIterator(1);

	setCurrentNGNail(Review::ListLocate::First);
	//LastNGNail = NGNailList::Iterator();
	//if(CurrentOrganizedHistory!=OrganizedHistoryList::Iterator()){
	//	CurrentNGNail = CurrentOrganizedHistory->getNGNailItemIterator(0);
	//	NextNGNail = CurrentOrganizedHistory->getNGNailItemIterator(1);
	//}else{
	//	CurrentNGNail = NGNailList::Iterator();
	//	NextNGNail = NGNailList::Iterator();
	//}

	return true;
}

bool ReviewPIBase::ReciveCmdServerReqCurrentLot(GUIDirectMessage *packet)
{
	CmdServerReqCurrentLot *cmd = dynamic_cast<CmdServerReqCurrentLot *>(packet);
	if(cmd==NULL)return false;

	XMLOpener opener(this);
	if(opener.isOpen()==false){
		cmd->Ret = false;
		return true;
	}

	cmd->FrontCurrentLotInfo = getCurrentLotInfo(Review::Front);
	cmd->BackCurrentLotInfo = getCurrentLotInfo(Review::Back);

	cmd->FrontLotList = getLotInfoAllList(Review::Front);
	cmd->BackLotList = getLotInfoAllList(Review::Back);
	
	getXMLServerHandle()->EnumTables(QString(/**/"%1-%2").arg(getMasterInfo(Review::Front).MachineID).arg(getMasterInfo(Review::Front).MasterCode), cmd->FrontReqServerEnumTableList);
	getXMLServerHandle()->EnumTables(QString(/**/"%1-%2").arg(getMasterInfo(Review::Back).MachineID).arg(getMasterInfo(Review::Back).MasterCode), cmd->BackReqServerEnumTableList);

	cmd->Ret = true;
	return true;
}

bool ReviewPIBase::ReciveCmdReqOrganizedHistoryList(GUIDirectMessage *packet)
{
	CmdReqOrganizedHistoryList *cmd = dynamic_cast<CmdReqOrganizedHistoryList *>(packet);
	if(cmd==NULL)return false;

	// 戻すのはまとめられたデータ
	cmd->listPtr = &getOrganizedHistoryList();
	cmd->Ret = true;

	return true;
}

bool ReviewPIBase::ReciveCmdServerUpdateLotList(GUIDirectMessage *packet)
{
	CmdServerUpdateLotList *cmd = dynamic_cast<CmdServerUpdateLotList *>(packet);
	if(cmd==NULL)return false;
	
	// ロット選択コマンドパケット
	CmdServerSelectLotList SelectLotCmd(GetLayersBase());

	// 表側
	SelectLotCmd.MasterCode = getMasterInfo(Review::Front).MasterCode;
	SelectLotCmd.MachineID = getMasterInfo(Review::Front).MachineID;

	// 設定
	ReciveCmdServerSelectLotList( &SelectLotCmd );

	// 表側の情報を格納
	cmd->FrontLotList = SelectLotCmd.list;
	
	// 裏側
	SelectLotCmd.MasterCode = getMasterInfo(Review::Back).MasterCode;
	SelectLotCmd.MachineID = getMasterInfo(Review::Back).MachineID;

	// 設定
	ReciveCmdServerSelectLotList( &SelectLotCmd );

	// 裏側の情報を格納
	cmd->BackLotList = SelectLotCmd.list;

	return true;
}

bool ReviewPIBase::ReciveCmdSetFKeyToNGNail(GUIDirectMessage *packet)
{
	CmdSetFKeyToNGNail *cmd = dynamic_cast<CmdSetFKeyToNGNail *>(packet);
	if(cmd==NULL)return false;

	NGNailList::Iterator CurrentNG = getRoundCurrentNGNailIterator(Review::CurrentPos);
	OrganizedHistoryList::Iterator CurrentHistory = getRoundCurrentOrganizedHistoryIterator(Review::CurrentPos);

	if(CurrentBundle.FocusPoint!=NULL){
		CurrentBundle.FocusPoint->FnKeyNumber=(int)cmd->key;
	}
	// 同じなら何もしない
	if(CurrentNG->FKey==cmd->key){
		cmd->FKeyColor = getFKeyColor(cmd->key);
		cmd->Ret = true;
		return true;
	}

	//XMLOperationHandle *xmlOperatorHdl;
	//if(CurrentOrganizedHistory->getWhitchSide(CurrentNGNail->getNGNailItemRef())==Review::Front){
	//	xmlOperatorHdl = xmlServerHdl->OpenXMLOperation(FrontLotFilename);
	//}else{
	//	xmlOperatorHdl = xmlServerHdl->OpenXMLOperation(BackLotFilename);
	//}
	//
	//if(XML_SetCurrentPosToNGI(xmlOperatorHdl, CurrentOrganizedHistory->getInspectID(),
	//	CurrentNGNail->page, CurrentNGNail->phase, CurrentNGNail->TargetPosX, CurrentNGNail->TargetPosY)==false){
	//	cmd->Ret = false;
	//	delete xmlOperatorHdl;
	//	return true;
	//}

	//// 指定したポイントにFキー情報を付与
	//if(xmlOperatorHdl->InsUpdateAttr(QString("FK=%1").arg(Review::FKeyToInt(cmd->key)))==false){
	//	cmd->Ret = false;
	//	delete xmlOperatorHdl;
	//	return true;
	//}

	//CurrentNGNail->FKey = cmd->key;
	//cmd->FKeyColor = getFKeyColor(cmd->key);

	//delete xmlOperatorHdl;

	QString TableName;
	if(isFront(CurrentHistory->getWhitchSide(*CurrentNG))){
		TableName = getCurrentLotInfo(Review::Front).TableName;
	}else{
		TableName = getCurrentLotInfo(Review::Back).TableName;
	}

	ReqXMLWrite reqXMLWrite(getRoundCurrentOrganizedHistoryIterator(Review::CurrentPos)->getInspectID(), CurrentNG->phase, CurrentNG->page, TableName);
	reqXMLWrite.addItem(CurrentNG->TargetPosX, CurrentNG->TargetPosY, CurrentNG->isChecked, cmd->key, stReqXMLWrite::WriteFKey);

	getXMLWriter()->push_back(reqXMLWrite);
	
	CurrentNG->FKey = cmd->key;
	cmd->FKeyColor = getFKeyColor(cmd->key);

	cmd->Ret = true;
	return true;
}

bool ReviewPIBase::ReciveCmdClearFKeyToNGNail(GUIDirectMessage *packet)
{
	CmdClearFKeyToNGNail *cmd = dynamic_cast<CmdClearFKeyToNGNail *>(packet);
	if(cmd==NULL)return false;

	//XMLOperationHandle *xmlOperatorHdl;
	//if(CurrentOrganizedHistory->getWhitchSide(CurrentNGNail->getNGNailItemRef())==Review::Front){
	//	xmlOperatorHdl = xmlServerHdl->OpenXMLOperation(FrontLotFilename);
	//}else{
	//	xmlOperatorHdl = xmlServerHdl->OpenXMLOperation(BackLotFilename);
	//}

	//if(xmlOperatorHdl==NULL)return false;
	//
	//if(XML_SetCurrentPosToNGI(xmlOperatorHdl, CurrentOrganizedHistory->getInspectID(),
	//	CurrentNGNail->page, CurrentNGNail->phase, CurrentNGNail->TargetPosX, CurrentNGNail->TargetPosY)==false){
	//	cmd->Ret = false;
	//	return false;
	//}

	//// FK情報を破棄
	//if(xmlOperatorHdl->DeleteAttr("FK")==false){
	//	cmd->Ret = false;
	//	return true;
	//}

	OrganizedHistoryList::Iterator CurrentOrganizedHistory = getRoundCurrentOrganizedHistoryIterator(Review::CurrentPos);
	NGNailList::Iterator CurrentNGNail = getRoundCurrentNGNailIterator(Review::CurrentPos);

	if(CurrentBundle.FocusPoint!=NULL){
		CurrentBundle.FocusPoint->FnKeyNumber=0;
	}
	if(CurrentOrganizedHistory.i==NULL || CurrentNGNail.i==NULL){
		cmd->Ret = false;
		return true;
	}

	if(CurrentNGNail->FKey==Review::NoFKey){
		cmd->CheckedColor = getFKeyColor(Review::NoFKey);
		cmd->Ret = true;
		return true;
	}

	QString TableName;
	if(CurrentOrganizedHistory->getWhitchSide(CurrentNGNail->getNGNailItemRef())==Review::Front){
		TableName = getCurrentLotInfo(Review::Front).TableName;
	}else{
		TableName = getCurrentLotInfo(Review::Back).TableName;
	}

	ReqXMLWrite reqXMLWrite(CurrentOrganizedHistory->getInspectID(), CurrentNGNail->phase, CurrentNGNail->page, TableName);
	reqXMLWrite.addItem(CurrentNGNail->TargetPosX, CurrentNGNail->TargetPosY, CurrentNGNail->isChecked, Review::NoFKey, stReqXMLWrite::WriteFKey);

	getXMLWriter()->push_back(reqXMLWrite);

	CurrentNGNail->FKey = Review::NoFKey;// Fキー無し
	cmd->CheckedColor = getFKeyColor(Review::NoFKey);// チェック色

	cmd->Ret = true;
	return true;
}

bool ReviewPIBase::ReciveCmdReqWholeImage(GUIDirectMessage *packet)
{
	CmdReqWholeImage *cmd = dynamic_cast<CmdReqWholeImage *>(packet);
	if(cmd==NULL)return false;

	// 
	//cmd->FrontWholePic = FrontWholeImage;
	//cmd->BackWholePic = BackWholeImage;
	QImage fImg = GetMasterWholeImage(Review::Front, cmd->reqPhase(), cmd->reqWidth(),cmd->reqHeight(),cmd->ZoomImageFromFile);
	QImage bImg = GetMasterWholeImage(Review::Back, cmd->reqPhase(), cmd->reqWidth(), cmd->reqHeight(),cmd->ZoomImageFromFile);
	//fImg.save("C:\\Tmp\\FrontImage.bmp","BMP");


	cmd->_setWholePic(fImg,bImg);

	//cmd->FrontWholePic.save("FrontWholeImage.jpg", "JPG");
	//cmd->BackWholePic.save("BackWholeImage.jpg", "JPG");

	QSize fsize(0,0),bsize(0,0);;
	qreal fzoomRate = -1;
	qreal bzoomRate = -1;

	if(getMasterWholeImageSize(Review::Front).count()>cmd->reqPhase()){
		fsize = getMasterWholeImageSize(Review::Front)[cmd->reqPhase()];

		QSize orgSize = fsize;
		QSize tagSize = QSize(cmd->reqWidth(), cmd->reqHeight());
		QSize sclSize = orgSize;

		sclSize.scale(tagSize, Qt::KeepAspectRatio);

		fzoomRate = sclSize.width() / qreal(orgSize.width());
	}

	if(getMasterWholeImageSize(Review::Back).count()>cmd->reqPhase()){
		bsize = getMasterWholeImageSize(Review::Back)[cmd->reqPhase()];

		QSize orgSize = bsize;
		QSize tagSize = QSize(cmd->reqWidth(), cmd->reqHeight());
		QSize sclSize = orgSize;

		sclSize.scale(tagSize, Qt::KeepAspectRatio);

		bzoomRate = (sclSize.width() / qreal(orgSize.width()));
	}
	cmd->_setZoomRate(fzoomRate, bzoomRate);
	cmd->_setWholeSize(fsize, bsize);

	cmd->_setSkipMasterImageRate(getProperty().SkipMasterImageRate, getProperty().SkipMasterImageRate);

	return true;
}

bool ReviewPIBase::ReciveCmdSetCurrentHistory(GUIDirectMessage *packet)
{
	CmdSetCurrentHistory *cmd = dynamic_cast<CmdSetCurrentHistory *>(packet);
	if(cmd==NULL)return false;

	if(getOrganizedHistoryList().isEmpty()){
		cmd->Ret = false;
		return true;
	}

	if(cmd->Index>=0){
		if(cmd->Index<0 || getOrganizedHistoryList().count()<=cmd->Index){
			cmd->Ret = false;
			return true;
		}

		if(getRoundCurrentOrganizedHistoryIterator(Review::CurrentPos) != getOrganizedHistoryIterator(cmd->Index)){// 現在と違う場合のみ設定

			setCurrentOrganizedHistory(cmd->Index);

			// 最初のNGを設定(NGは少なくとも１個)
			setCurrentNGNail(0);
		}
	}else if(cmd->InspectID>=0){
		for(int i=0; i<getOrganizedHistoryList().count(); i++){
			if(cmd->InspectID==getOrganizedHistoryList()[i].getInspectID()){
				setCurrentOrganizedHistory(i);
				setCurrentNGNail(0);
			}
		}
	}

	loadNGImageRoundCurrent();
	
	cmd->Ret = true;
	return true;
}

bool ReviewPIBase::ReciveCmdReqCurrentHistory(GUIDirectMessage *packet)
{
	CmdReqCurrentHistory *cmd = dynamic_cast<CmdReqCurrentHistory *>(packet);
	if(cmd==NULL)return false;

	cmd->Ret = false;
	
	if(getRoundCurrentOrganizedHistoryIterator(Review::CurrentPos).i!=NULL){
		OrganizedHistoryList::Iterator CurrentOrganizedHistory = getRoundCurrentOrganizedHistoryIterator(Review::CurrentPos);

		if(CurrentOrganizedHistory.i==NULL){
			cmd->setOrganizedHistroyPtr(NULL);
			cmd->Ret = true;
			return true;
		}

		OrganizedHistoryItem CurrentOrgHistory = *CurrentOrganizedHistory;
		
		int index=0;
		OrganizedHistoryList::ConstIterator beginIt, endIt;
		beginIt = getOrganizedHistoryList().constBegin();
		endIt = getOrganizedHistoryList().constEnd();

		for(OrganizedHistoryList::ConstIterator it=beginIt; it!=endIt; it++,index++){
			if(CurrentOrganizedHistory==it){
				cmd->setIndex(index);
				cmd->setOrganizedHistroyPtr(&CurrentOrganizedHistory.i->t());
				cmd->Ret = true;
			}
		}
	}

	return true;
}

bool ReviewPIBase::ReciveCmdUpdateCurrentLotData(GUIDirectMessage *packet)
{
	CmdUpdateCurrentLotData *cmd = dynamic_cast<CmdUpdateCurrentLotData *>(packet);
	if(cmd==NULL)return false;

	CmdServerSetLot Send(GetLayersBase());
	if(getCurrentLotInfo(Review::Front).TableName.isEmpty()==false){
		Send.side = Review::Front;
		Send.LotFileName = getCurrentLotInfo(Review::Front).Filename();
		ReciveCmdServerSetLot( &Send );
	}
	if(getCurrentLotInfo(Review::Back).TableName.isEmpty()==false){
		Send.side = Review::Back;
		Send.LotFileName = getCurrentLotInfo(Review::Back).Filename();
		ReciveCmdServerSetLot( &Send );
	}

	return true;
}

bool ReviewPIBase::ReciveCmdReqInsLib(GUIDirectMessage *packet)
{
	CmdReqInsLib *cmd = dynamic_cast<CmdReqInsLib *>(packet);
	if(cmd==NULL)return false;
	
	cmd->FrontInsLibHash = getInsLibHash(Review::Front);
	cmd->BackInsLibHash = getInsLibHash(Review::Back);
	
	cmd->Ret = true;
	return true;
}

bool ReviewPIBase::ReciveCmdSetSortNGOrder(GUIDirectMessage *packet)
{
	CmdSetSortNGOrder *cmd = dynamic_cast<CmdSetSortNGOrder *>(packet);
	if(cmd==NULL)return false;

	if(getNGSortOrder()==cmd->order){
		return true;
	}

	// カレント画像位置を保存
	NGNailList::Iterator CurrentNG = getRoundCurrentNGNailIterator(Review::CurrentPos);

	//if(CurrentNGNail!=NGNailList::Iterator()){
	//	CmdReqAdjacentCurrentNG adjNG(GetLayersBase());
	//	ReciveCmdReqAdjacentCurrentNG( &adjNG );
	//	NGIndex = adjNG.currentNGIndex;
	//}else{
	//	NGIndex = -1;
	//}

	// ソート実行
	setNGSortOrder(cmd->order);

	sortNGNailList();

	//saveSetting();

	// 履歴がある場合、元のカレント画像位置に移動
	OrganizedHistoryList::Iterator CurrentOrganizedHistory = getRoundCurrentOrganizedHistoryIterator(Review::CurrentPos);
	if(CurrentOrganizedHistory!=OrganizedHistoryList::Iterator()){
		for(int i=0; i<CurrentOrganizedHistory->getNGNailCount(); i++){
			if(CurrentNG == CurrentOrganizedHistory->getNGNailItemIterator(i)){
				CmdSetCurrentNGNail setNGNail(GetLayersBase());
				setNGNail.Index = i;
				setNGNail.refType = Review::RefType::Ref_Index;
				ReciveCmdSetCurrentNGNail( &setNGNail );
				break;
			}
		}
	}

	//if(NGIndex!=-1){
	//	CmdSetCurrentNGNail setNG(GetLayersBase());
	//	setNG.Index = NGIndex;
	//	setNG.refType = Review::RefType::Ref_Index;
	//	setNG.locate = Review::ListLocate::Manual;

	//	ReciveCmdSetCurrentNGNail( &setNG );
	//}
	
	return true;
}

bool ReviewPIBase::ReciveCmdReqSortNGOrder(GUIDirectMessage *packet)
{
	CmdReqSortNGOrder *cmd = dynamic_cast<CmdReqSortNGOrder *>(packet);
	if(cmd==NULL)return false;
	
	cmd->order = getProperty().NGNailListSortOrder;
	
	return true;
}

bool ReviewPIBase::ReciveCmdSetSortHistoryOrder(GUIDirectMessage *packet)
{
	CmdSetSortHistoryOrder *cmd = dynamic_cast<CmdSetSortHistoryOrder *>(packet);
	if(cmd==NULL)return false;

	if(getHistorySortOrder()==cmd->order){
		return true;
	}

	// 履歴リストのカレントを保存
	int CurrentHistoryID = -1;
	int CurrentNGNailIndex = -1;
	OrganizedHistoryList::Iterator CurrentOrganizedHistory = getRoundCurrentOrganizedHistoryIterator(Review::CurrentPos);
	if(CurrentOrganizedHistory!=OrganizedHistoryList::Iterator()){
		CurrentHistoryID = CurrentOrganizedHistory->getInspectID();
		NGNailList::Iterator CurrentNGNail = getRoundCurrentNGNailIterator(Review::CurrentPos);
		for(int i=0; i<CurrentOrganizedHistory->getNGNailCount(); i++){
			if(CurrentNGNail==CurrentOrganizedHistory->getNGNailItemIterator(i)){
				CurrentNGNailIndex = i;
				break;
			}
		}
	}

	setHistorySortOrder(cmd->order);

	//saveSetting();

	if(CurrentHistoryID==-1){
		return true;
	}

	// 履歴が読み込まれている場合カレントを戻す
	CmdSetCurrentHistory setHistory(GetLayersBase());
	setHistory.InspectID = CurrentHistoryID;
	ReciveCmdSetCurrentHistory( &setHistory );

	if(CurrentNGNailIndex==-1){
		return true;
	}
	
	// 画像リストのカレントを戻す
	CmdSetCurrentNGNail setNGNail(GetLayersBase());
	setNGNail.Index = CurrentNGNailIndex;
	setNGNail.refType = Review::RefType::Ref_Index;
	ReciveCmdSetCurrentNGNail( &setNGNail );

	return true;
}

bool ReviewPIBase::ReciveCmdReqSortHistoryOrder(GUIDirectMessage *packet)
{
	CmdReqSortHistoryOrder *cmd = dynamic_cast<CmdReqSortHistoryOrder *>(packet);
	if(cmd==NULL)return false;

	cmd->order = getHistorySortOrder();
	
	return true;
}

bool ReviewPIBase::ReciveCmdReqAdjacentCurrentNG(GUIDirectMessage *packet)
{
	CmdReqAdjacentCurrentNG *cmd = dynamic_cast<CmdReqAdjacentCurrentNG *>(packet);
	if(cmd==NULL)return false;
	
	// 前の履歴
	if(getRoundCurrentOrganizedHistoryIterator(Review::PreviousPos).i==NULL){
		cmd->setPreviousHistory(NULL);
		//qDebug() << "Previous InspectID : none";
	}else{
		cmd->setPreviousHistory(&getRoundCurrentOrganizedHistoryIterator(Review::PreviousPos).i->t());
		//qDebug() << "Previous InspectID : " << cmd->previousHistory->getInspectID();
	}
	// 現在の履歴
	if(getRoundCurrentOrganizedHistoryIterator(Review::CurrentPos).i==NULL){
		cmd->setCurrentHistory(NULL);
		//qDebug() << "Current InspectID : none";
	}else{
		cmd->setCurrentHistory(&getRoundCurrentOrganizedHistoryIterator(Review::CurrentPos).i->t());
		//qDebug() << "Current InspectID : " << cmd->currentHistory->getInspectID();
	}
	// 次の履歴
	if(getRoundCurrentOrganizedHistoryIterator(Review::NextPos).i==NULL){
		cmd->setNextHistory(NULL);
		//qDebug() << "Next InspectID : none";
	}else{
		cmd->setNextHistory(&getRoundCurrentOrganizedHistoryIterator(Review::NextPos).i->t());
		//qDebug() << "Next InspectID : " << cmd->nextHistory->getInspectID();
	}


	// 前のNGNail
	if(getRoundCurrentNGNailIterator(Review::PreviousPos).i==NULL){
		cmd->setPreviousNG(NULL);
	}else{
		cmd->setPreviousNG(&getRoundCurrentNGNailIterator(Review::PreviousPos).i->t());
	}
	// 現在のNGNail
	if(getRoundCurrentNGNailIterator(Review::CurrentPos).i==NULL){
		cmd->setCurrentNG(NULL);
		cmd->setCurrentNGIndex(-1);
	}else{
		cmd->setCurrentNG(&getRoundCurrentNGNailIterator(Review::CurrentPos).i->t());
		cmd->setCurrentNGIndex(getRoundCurrentOrganizedHistoryIterator(Review::CurrentPos)->indexOf(getRoundCurrentNGNailIterator(Review::CurrentPos)->getNGNailItemRef()));
	}
	// 次のNGNail
	if(getRoundCurrentNGNailIterator(Review::NextPos).i==NULL){
		cmd->setNextNG(NULL);
	}else{
		cmd->setNextNG(&getRoundCurrentNGNailIterator(Review::NextPos).i->t());
	}
	cmd->setCurrentSide(getCurrentSideType());
	
	cmd->Ret = true;
	return true;
}

bool ReviewPIBase::ReciveCmdMoveCurrentNGNail(GUIDirectMessage *packet)
{
	CmdMoveCurrentNGNail *cmd = dynamic_cast<CmdMoveCurrentNGNail *>(packet);
	if(cmd==NULL)return false;

	OrganizedHistoryList::Iterator CurrentOrganizedHistory = getRoundCurrentOrganizedHistoryIterator(Review::CurrentPos);
	if(CurrentOrganizedHistory==OrganizedHistoryList::Iterator()){
		cmd->Ret = false;
		return true;
	}

	NGNailList::Iterator PreviousNGNail, CurrentNGNail, NextNGNail;
	getRoundCurrentNGNailIterator(PreviousNGNail, CurrentNGNail, NextNGNail);

	if(cmd->direction==Review::Next){
		int currentNGIndex = CurrentOrganizedHistory->indexOf(*getRoundCurrentNGNailIterator(Review::CurrentPos));
		PreviousNGNail = CurrentNGNail;
		CurrentNGNail = NextNGNail;
		NextNGNail = CurrentOrganizedHistory->getNGNailItemIterator(currentNGIndex+2);
	}else if(cmd->direction==Review::Previous){
		int currentNGIndex = CurrentOrganizedHistory->indexOf(*CurrentNGNail);
		NextNGNail = CurrentNGNail;
		CurrentNGNail = PreviousNGNail;
		PreviousNGNail = CurrentOrganizedHistory->getNGNailItemIterator(currentNGIndex-2);
	}else{
		int index;
		if(cmd->index==-1){
			index = CurrentOrganizedHistory->indexOf(*(cmd->CurrentNGPtr));
		}else{
			index = cmd->index;
		}

		if(index==-1){
			cmd->Ret = false;
			return true;
		}else{
			PreviousNGNail = CurrentOrganizedHistory->getNGNailItemIterator(index-1);
			CurrentNGNail = CurrentOrganizedHistory->getNGNailItemIterator(index);
			NextNGNail = CurrentOrganizedHistory->getNGNailItemIterator(index+1);
		}
	}

	setRoundCurrentNGNailIterator(Review::PreviousPos, PreviousNGNail);
	setRoundCurrentNGNailIterator(Review::CurrentPos, CurrentNGNail);
	setRoundCurrentNGNailIterator(Review::NextPos, NextNGNail);

	cmd->Ret = true;
	return true;
}

bool ReviewPIBase::ReciveCmdMoveCurrentHistory(GUIDirectMessage *packet)
{
	CmdMoveCurrentHistory *cmd = dynamic_cast<CmdMoveCurrentHistory *>(packet);
	if(cmd==NULL)return false;

	if(cmd->direction==Review::Next){// 次へ
		OrganizedHistoryList::Iterator PreviousOrganizedHistory = getRoundCurrentOrganizedHistoryIterator(Review::CurrentPos);
		OrganizedHistoryList::Iterator CurrentOrganizedHistory = getRoundCurrentOrganizedHistoryIterator(Review::NextPos);
		OrganizedHistoryList::Iterator NextOrganizedHistory;

		for(OrganizedHistoryList::Iterator it=getOrganizedHistoryIteratorBegin(); it!=getOrganizedHistoryIteratorEnd(); it++){
			//qDebug() << "Search Ptr" << it.i;
			if(it==CurrentOrganizedHistory){
				if(it!=getOrganizedHistoryIteratorEnd()-1){
					NextOrganizedHistory = it+1;
				}
				break;
			}
		}
		
		if(CurrentOrganizedHistory.i!=NULL){
			cmd->CurrentHistoryPtr = &CurrentOrganizedHistory.i->t();
		}else{
			cmd->CurrentHistoryPtr = NULL;
		}

		setRoundCurrentOrganizedHistoryIterator(PreviousOrganizedHistory, CurrentOrganizedHistory, NextOrganizedHistory);

		// NG現在位置を最初へ移動
		CmdSetCurrentNGNail Send(GetLayersBase());
		Send.refType = Review::RefType::Ref_Index;
		Send.locate = Review::First;
		ReciveCmdSetCurrentNGNail(&Send);

	}else if(cmd->direction==Review::Previous){// 前へ
		OrganizedHistoryList::Iterator PreviousOrganizedHistory;
		OrganizedHistoryList::Iterator CurrentOrganizedHistory = getRoundCurrentOrganizedHistoryIterator(Review::PreviousPos);
		OrganizedHistoryList::Iterator NextOrganizedHistory = getRoundCurrentOrganizedHistoryIterator(Review::CurrentPos);

		for(OrganizedHistoryList::Iterator it=getOrganizedHistoryIteratorBegin(); it!=getOrganizedHistoryIteratorEnd(); it++){
			if(it==CurrentOrganizedHistory){
				if(it!=getOrganizedHistoryList().begin()){
					PreviousOrganizedHistory = it-1;
				}
				break;
			}
		}
		
		if(CurrentOrganizedHistory.i!=NULL){
			cmd->CurrentHistoryPtr = &CurrentOrganizedHistory.i->t();
		}else{
			cmd->CurrentHistoryPtr = NULL;
		}

		setRoundCurrentOrganizedHistoryIterator(PreviousOrganizedHistory, CurrentOrganizedHistory, NextOrganizedHistory);
		
		CmdSetCurrentNGNail Send(GetLayersBase());
		Send.refType = Review::RefType::Ref_Index;
		Send.locate = Review::First;
		ReciveCmdSetCurrentNGNail(&Send);
	}else{
		//for(int i=0; i<HistoryPack.size(); i++){


		//	if(cmd->CurrentHistoryPtr->getFront() == HistoryPack[i].getFront() &&
		//		cmd->CurrentHistoryPtr->getBack() == HistoryPack[i].getBack() ){
		//			
		//		if(i==0){
		//			LastOrganizedHistory = OrganizedHistoryList::Iterator();
		//		}else{
		//			LastOrganizedHistory = HistoryPack.begin() + i - 1;
		//		}

		//		CurrentOrganizedHistory = HistoryPack.begin() + i;

		//		if(i==HistoryPack.size()-1){
		//			NextOrganizedHistory = OrganizedHistoryList::Iterator();
		//		}else{
		//			NextOrganizedHistory = HistoryPack.begin() + i + 1;
		//		}

		//		cmd->Ret = true;

		//		loadNGImageRoundCurrent();

		//		return true;
		//	}
		//}

		//
		//cmd->CurrentHistoryPtr = &CurrentOrganizedHistory.i->t();
		//
		//CmdSetCurrentNGNail Send(GetLayersBase());
		//Send.refType = Review::RefType::Ref_Index;
		//Send.locate = Review::First;
		//ReciveCmdSetCurrentNGNail(&Send);

		cmd->Ret = false;
		return true;
	}

	cmd->Ret = true;
	return true;
}

bool ReviewPIBase::ReciveCmdMoveCurrentHistoryToNGBoard(GUIDirectMessage *packet)
{
	CmdMoveCurrentHistoryToNGBoard *cmd = dynamic_cast<CmdMoveCurrentHistoryToNGBoard *>(packet);
	if(cmd==NULL)return false;
	
	OrganizedHistoryList::Iterator CurrentHistory = getRoundCurrentOrganizedHistoryIterator(Review::CurrentPos);

	// 現在履歴が未設定の場合は異常終了
	if(CurrentHistory==OrganizedHistoryList::Iterator()){
		cmd->Ret = false;
		return true;
	}

	// 現在の履歴の位置を調べる
	int index = 0;
	for(OrganizedHistoryList::Iterator it=getOrganizedHistoryIteratorBegin(); it!=getOrganizedHistoryIteratorEnd(); it++,index++){
		if(it==CurrentHistory){
			break;
		}
	}

	// 見つからなかった場合は異常終了
	if(index==getOrganizedHistoryList().count()){
		cmd->Ret = false;
		return true;
	}

	// 指定方向進行コマンド
	CmdMoveCurrentHistory Cmd(GetLayersBase());
	Cmd.direction = cmd->direction;
	forever{
		ReciveCmdMoveCurrentHistory(&Cmd);
		if(Cmd.CurrentHistoryPtr==NULL){// 末端まで来た
			CmdSetCurrentHistory ReturnToOrgCmd(GetLayersBase());
			ReturnToOrgCmd.Index = index;
			ReciveCmdSetCurrentHistory(&ReturnToOrgCmd);
			cmd->CurrentHistoryPtr = &(getRoundCurrentOrganizedHistoryIterator(Review::CurrentPos).i->t());
			cmd->Ret = true;
			return true;
		}else if(Cmd.CurrentHistoryPtr->isOK()==false){// NG基盤が見つかった
			break;
		}
	}

	cmd->CurrentHistoryPtr = Cmd.CurrentHistoryPtr;

	loadNGImageRoundCurrent();

	cmd->Ret = true;
	return true;
}

bool ReviewPIBase::ReciveCmdSetCurrentNGNail(GUIDirectMessage *packet)
{
	CmdSetCurrentNGNail *cmd = dynamic_cast<CmdSetCurrentNGNail *>(packet);
	if(cmd==NULL)return false;

	OrganizedHistoryList::Iterator CurrentOrganizedHistory = getRoundCurrentOrganizedHistoryIterator(Review::CurrentPos);

	if(CurrentOrganizedHistory.i==NULL){
		cmd->Ret = false;
		return true;
	}
	
	if(cmd->refType==Review::RefType::Ref_Index){
		if(cmd->locate==Review::ListLocate::First){
			setRoundCurrentNGNailIterator(Review::PreviousPos, NGNailList::Iterator());
			setRoundCurrentNGNailIterator(Review::CurrentPos, CurrentOrganizedHistory->getNGNailItemIterator(0));
			setRoundCurrentNGNailIterator(Review::NextPos, CurrentOrganizedHistory->getNGNailItemIterator(1));
		}else if(cmd->locate==Review::ListLocate::End){
			setRoundCurrentNGNailIterator(Review::PreviousPos, CurrentOrganizedHistory->getNGNailItemIterator(CurrentOrganizedHistory->getNGNailCount() - 2));
			setRoundCurrentNGNailIterator(Review::CurrentPos, CurrentOrganizedHistory->getNGNailItemIterator(CurrentOrganizedHistory->getNGNailCount() - 1));
			setRoundCurrentNGNailIterator(Review::NextPos, NGNailList::Iterator());
		}else{
			setRoundCurrentNGNailIterator(Review::PreviousPos, CurrentOrganizedHistory->getNGNailItemIterator(cmd->Index - 1));
			setRoundCurrentNGNailIterator(Review::CurrentPos, CurrentOrganizedHistory->getNGNailItemIterator(cmd->Index));
			setRoundCurrentNGNailIterator(Review::NextPos, CurrentOrganizedHistory->getNGNailItemIterator(cmd->Index + 1));
		}
	}else if(cmd->refType==Review::RefType::Ref_Instance){
		for(int i=0; i<CurrentOrganizedHistory->getNGCount(); i++){
			if(cmd->refItem==(*CurrentOrganizedHistory->getNGNailItemIterator(i))){
				setRoundCurrentNGNailIterator(Review::PreviousPos, CurrentOrganizedHistory->getNGNailItemIterator(i-1));
				setRoundCurrentNGNailIterator(Review::CurrentPos, CurrentOrganizedHistory->getNGNailItemIterator(i));
				setRoundCurrentNGNailIterator(Review::NextPos, CurrentOrganizedHistory->getNGNailItemIterator(i+1));

				cmd->Ret = true;
				return true;
			}
		}
		cmd->Ret = false;
		return true;
	}

	cmd->Ret = true;
	return true;
}

bool ReviewPIBase::ReciveCmdReqMasterDataInfo(GUIDirectMessage *packet)
{
	CmdReqMasterDataInfo *cmd = dynamic_cast<CmdReqMasterDataInfo *>(packet);
	if(cmd==NULL)return false;

	cmd->FrontMasterDataInfo = getMasterInfo(Review::Front);
	cmd->BackMasterDataInfo = getMasterInfo(Review::Back);
	
	cmd->Ret = true;
	return true;
};

bool ReviewPIBase::ReciveCmdSetCurrentNGChecked(GUIDirectMessage *packet)
{
	CmdSetCurrentNGChecked *cmd = dynamic_cast<CmdSetCurrentNGChecked *>(packet);
	if(cmd==NULL)return false;

	OrganizedHistoryList::Iterator CurrentOrganizedHistory = getRoundCurrentOrganizedHistoryIterator(Review::CurrentPos);
	NGNailList::Iterator CurrentNGNail = getRoundCurrentNGNailIterator(Review::CurrentPos);

	// カレントNGがないもしくはチェック済みなら何もしない
	if(CurrentNGNail==NGNailList::Iterator() || CurrentNGNail->isChecked==true)return true;
	
	QString TableName;
	if(isFront(CurrentOrganizedHistory->getWhitchSide(*CurrentNGNail))==true){
		TableName = getCurrentLotInfo(Review::Front).TableName;
	}else{
		TableName = getCurrentLotInfo(Review::Back).TableName;
	}

	ReqXMLWrite XMLPosToPage(CurrentOrganizedHistory->getInspectID(), CurrentNGNail->phase, CurrentNGNail->page, TableName);

	XMLPosToPage.addItem(CurrentNGNail->TargetPosX, CurrentNGNail->TargetPosY, cmd->isChecked, CurrentNGNail->FKey, stReqXMLWrite::WriteChecked);

	getXMLWriter()->push_back(XMLPosToPage);

	CurrentNGNail->isChecked = cmd->isChecked;
	
	cmd->Ret = true;
	return true;
}

bool ReviewPIBase::ReciveCmdSetNGChecked(GUIDirectMessage *packet)
{
	CmdSetNGChecked *cmd = dynamic_cast<CmdSetNGChecked *>(packet);
	if(cmd==NULL)return false;

	OrganizedHistoryList::Iterator CurrentOrganizedHistory = getRoundCurrentOrganizedHistoryIterator(Review::CurrentPos);
	
	// 現在履歴がない場合
	if(CurrentOrganizedHistory.i==NULL){
		cmd->Ret = false;
		return true;
	}

	// 付与先があるかどうかのチェック
	if(isFront(cmd->side)==true){
		if(CurrentOrganizedHistory->hasFront()==false || cmd->begin>=CurrentOrganizedHistory->getFront()->getNGNails().count()){
			cmd->Ret = false;
			return true;
		}
		bool allChecked = true;
		NGNailList::ConstIterator itend = CurrentOrganizedHistory->getFront()->getNGNails().constBegin() + cmd->begin + cmd->length;
		for(NGNailList::ConstIterator it = CurrentOrganizedHistory->getFront()->getNGNails().constBegin() + cmd->begin;
			it!=CurrentOrganizedHistory->getFront()->getNGNails().constEnd() && it!=itend; it++){
				if(it->isChecked==false){
					allChecked = false;
					break;
				}
		}
		if(allChecked==true){
			cmd->Ret = true;
			return true;
		}
	}else if(cmd->side==Review::Back){
		if(CurrentOrganizedHistory->hasBack()==false || cmd->begin>=CurrentOrganizedHistory->getBack()->getNGNails().count()){
			cmd->Ret = false;
			return true;
		}
		bool allChecked = true;
		NGNailList::ConstIterator itend = CurrentOrganizedHistory->getBack()->getNGNails().constBegin() + cmd->begin + cmd->length;
		for(NGNailList::ConstIterator it = CurrentOrganizedHistory->getBack()->getNGNails().constBegin() + cmd->begin;
			it!=CurrentOrganizedHistory->getBack()->getNGNails().constEnd() && it!=itend; it++){
				if(it->isChecked==false){
					allChecked = false;
					break;
				}
		}
		if(allChecked==true){
			cmd->Ret = true;
			return true;
		}
	}
	
	XMLOpener opener(this);
	if(opener.isOpen()==false){
		cmd->Ret = false;
		return true;
	}

	if(cmd->length==0){// 長さが0の場合なにもしない
		cmd->Ret = true;
		return true;
	}else if(cmd->length>0){// 長さが正の場合、その長さの分だけチェックを付与する
		QString TableName = getCurrentLotInfo(cmd->side).TableName;
		NGNailListPtr pNGNails;

		if(cmd->side==Review::Front){
			// 現在の履歴が設定されていない、表の履歴がない、表の履歴がNGなしの場合は失敗
			if(CurrentOrganizedHistory==OrganizedHistoryList::Iterator() || CurrentOrganizedHistory->hasFront()==false || CurrentOrganizedHistory->getFront()->getNGNails().isEmpty()==true){
				cmd->Ret = false;
				return true;
			}
			pNGNails = &(CurrentOrganizedHistory->getFront()->getNGNails());
		}else{
			// 現在の履歴が設定されていない、裏の履歴がない、現在履歴がNGなしの場合は失敗
			if(CurrentOrganizedHistory==OrganizedHistoryList::Iterator() || CurrentOrganizedHistory->hasBack()==false || CurrentOrganizedHistory->getBack()->getNGNails().isEmpty()==true){
				cmd->Ret = false;
				return true;
			}
			pNGNails = &(CurrentOrganizedHistory->getBack()->getNGNails());
		}
		
		// 末端部を調査。末端インデックスが対象NGリストの末尾を過ぎる場合はそのNGリストの末端までとする
		NGNailList::Iterator itend;
		if(cmd->begin+cmd->length>=pNGNails->count()){
			itend = pNGNails->end();
		}else{
			itend = pNGNails->begin() + cmd->begin + cmd->length;
		}

		// 書き込み対象を作成
		ReqXMLWrite reqXMLWrite(CurrentOrganizedHistory->getInspectID(), pNGNails->front().phase, pNGNails->front().page, TableName);
		for(NGNailList::Iterator it = pNGNails->begin()+cmd->begin; it!=itend; it++){
			if(it->isChecked==false){
				reqXMLWrite.addItem(it->TargetPosX, it->TargetPosY, true, it->FKey, stReqXMLWrite::WriteChecked);
				it->isChecked=true;
			}
		}

		// スレッドに投げる
		getXMLWriter()->push_back(reqXMLWrite);
	}else{
		cmd->Ret = false;
		return true;
	}

		/////////////////////////

	//	if(cmd->side==Review::Front){
	//		XMLOperationHandle *xmlOperatorHdl;
	//		xmlOperatorHdl = xmlServerHdl->OpenXMLOperation(FrontLotFilename);

	//		if(xmlOperatorHdl==NULL){
	//			cmd->Ret = false;
	//			return true;
	//		}

	//		NGNailList::Iterator itend;
	//		if(cmd->begin+cmd->length>=CurrentOrganizedHistory->getFront()->NGNails.count()){
	//			itend = CurrentOrganizedHistory->getFront()->NGNails.end();
	//		}else{
	//			itend = CurrentOrganizedHistory->getFront()->NGNails.begin() + cmd->begin + cmd->length;
	//		}
	//		for(NGNailList::Iterator it = CurrentOrganizedHistory->getFront()->NGNails.begin()+cmd->begin; it!=itend; it++){
	//			if(it->isChecked==false){
	//				if(XML_SetCurrentPosToNGI(xmlOperatorHdl, CurrentOrganizedHistory->getInspectID(), it->page, it->phase, it->TargetPosX, it->TargetPosY)==false){
	//					delete xmlOperatorHdl;
	//					cmd->Ret = false;
	//					return true;
	//				}
	//				// 指定したポイントにチェック済み情報を付与
	//				if(xmlOperatorHdl->InsUpdateAttr("Checked=1")==false){
	//					delete xmlOperatorHdl;
	//					cmd->Ret = false;
	//					return true;
	//				}
	//				it->isChecked=true;
	//			}
	//		}
	//		delete xmlOperatorHdl;
	//	}else{
	//		XMLOperationHandle *xmlOperatorHdl;
	//		xmlOperatorHdl = xmlServerHdl->OpenXMLOperation(BackLotFilename);

	//		if(xmlOperatorHdl==NULL){
	//			cmd->Ret = false;
	//			return true;
	//		}
	//		
	//		NGNailList::Iterator itend;
	//		if(cmd->begin+cmd->length>=CurrentOrganizedHistory->getBack()->NGNails.count()){
	//			itend = CurrentOrganizedHistory->getBack()->NGNails.end();
	//		}else{
	//			itend = CurrentOrganizedHistory->getBack()->NGNails.begin() + cmd->begin + cmd->length;
	//		}
	//		for(NGNailList::Iterator it = CurrentOrganizedHistory->getBack()->NGNails.begin()+cmd->begin; it!=itend; it++){
	//			if(it->isChecked==false){
	//				if(XML_SetCurrentPosToNGI(xmlOperatorHdl, CurrentOrganizedHistory->getInspectID(), it->page, it->phase, it->TargetPosX, it->TargetPosY)==false){
	//					delete xmlOperatorHdl;
	//					cmd->Ret = false;
	//					return true;
	//				}
	//				// 指定したポイントにチェック済み情報を付与
	//				if(xmlOperatorHdl->InsUpdateAttr("Checked=1")==false){
	//					delete xmlOperatorHdl;
	//					cmd->Ret = false;
	//					return true;
	//				}
	//				it->isChecked = true;
	//			}
	//		}
	//		delete xmlOperatorHdl;
	//	}
	//}else{
	//	cmd->Ret = false;
	//	return true;
	//}

	cmd->Ret = true;
	return true;
}

bool ReviewPIBase::ReciveCmdReqFKeyColorList(GUIDirectMessage *packet)
{
	CmdReqFKeyColorList *cmd = dynamic_cast<CmdReqFKeyColorList *>(packet);
	if(cmd==NULL)return false;

	cmd->list = Review::getDefaultFKeyColorList();

	cmd->Ret = true;
	return true;
}

bool ReviewPIBase::ReciveCmdUpdateMasterBuff(GUIDirectMessage *packet)
{
	CmdUpdateMasterBuff *cmd = dynamic_cast<CmdUpdateMasterBuff *>(packet);
	if(cmd==NULL)return false;

	if(cmd->phase==-1){
		cmd->Ret = false;
		return true;
	}

	//QImage *TargetImage;
	QList<QImage> *TargetPageList;
	QList<QPoint> *TargetOutlineList;
	QSize *TargetWholeSize;
	QList<QPoint> *TargetWholeImgDrawPoints;
	MasterDataInfo TargetInfo;

	TargetPageList = getMasterWholePageImageListPtr(cmd->side, cmd->phase);
	TargetOutlineList = getMasterWholePageOutlineListPtr(cmd->side, cmd->phase);
	TargetWholeSize = getMasterWholeImageSizePtr(cmd->side, cmd->phase);
	TargetWholeImgDrawPoints = getMasterWholeImgDrawPointsPtr(cmd->side, cmd->phase);
	TargetInfo = getMasterInfo(cmd->side);

	//if(cmd->side==Review::Front){
	//	//TargetImage = &FrontWholeImage;
	//	TargetInfo = FrontMasterInfo;
	//	TargetPageList = &FrontPageImages[cmd->phase];
	//	TargetOutlineList = &FrontOutline[cmd->phase];
	//	TargetWholeSize = &FrontMasterWholeImgSize[cmd->phase];
	//	TargetWholeImgDrawPoints = &FrontMasterWholeImgDrawPoints[cmd->phase];
	//}else{
	//	//TargetImage = &BackWholeImage;
	//	TargetInfo = BackMasterInfo;
	//	TargetPageList = &BackPageImages[cmd->phase];
	//	TargetOutlineList = &BackOutline[cmd->phase];
	//	TargetWholeSize = &BackMasterWholeImgSize[cmd->phase];
	//	TargetWholeImgDrawPoints = &BackMasterWholeImgDrawPoints[cmd->phase];
	//}

	TargetPageList->clear();
	*TargetWholeSize = QSize();
	TargetOutlineList->clear();
	TargetWholeImgDrawPoints->clear();

	while(TargetPageList->count()<GetPageNumb()){
		TargetPageList->append(QImage());
	}
	
	int skipRatio = getProperty().SkipMasterImageRate;// 0~
	int skipCount = skipRatio+1;
	if(GetLayerNumb(0)>=3){// カラー
		BYTE *pR,*pG,*pB;
		for(int page=0; page<GetLayersBase()->GetPageNumb(); page++){
			int width = GetLayersBase()->GetPhaseData()[cmd->phase]->GetPageData(page)->GetDotPerLine();
			int height = GetLayersBase()->GetPhaseData()[cmd->phase]->GetPageData(page)->GetMaxLines();

			QImage image(width / skipCount, height / skipCount, QImage::Format_RGB32);

			int IY=0;
			//#pragma omp for
			for(int Y=0; Y<height && IY<image.height(); Y+=skipCount){
				pR=GetPageDataPhase(cmd->phase)->GetPageData(page)->GetDataInLayer(0)->GetMasterBuff().GetY(Y);
				pG=GetPageDataPhase(cmd->phase)->GetPageData(page)->GetDataInLayer(1)->GetMasterBuff().GetY(Y);
				pB=GetPageDataPhase(cmd->phase)->GetPageData(page)->GetDataInLayer(2)->GetMasterBuff().GetY(Y);
				QRgb *pYLine=(QRgb *)image.scanLine(IY);
				for(int X=0; X<width; X+=skipCount,pR+=skipCount,pG+=skipCount,pB+=skipCount){
					*pYLine = qRgb(*pR,*pG,*pB);
					pYLine++;
				}
				IY++;
			}
			
			(*TargetPageList)[page] = image;

			TargetOutlineList->append(QPoint(GetLayersBase()->GetPageData(page)->GetOutlineOffset()->x,GetLayersBase()->GetPageData(page)->GetOutlineOffset()->y));
		}
	}else if(GetLayerNumb(0)==1){// モノクロ
		BYTE *pM;
		for(int page=0; page<GetLayersBase()->GetPageNumb(); page++){
			int width = GetLayersBase()->GetPhaseData()[cmd->phase]->GetPageData(page)->GetDotPerLine();
			int height = GetLayersBase()->GetPhaseData()[cmd->phase]->GetPageData(page)->GetMaxLines();
			QImage image(width, height, QImage::Format_RGB32);

			#pragma omp for
			for(int Y=0;Y<GetLayersBase()->GetPhaseData()[cmd->phase]->GetPageData(page)->GetMaxLines();Y++){
				pM = GetLayersBase()->GetPhaseData()[cmd->phase]->GetPageData(page)->GetLayerData(0)->GetMasterBuff().GetY(Y);
				QRgb *pYLine=(QRgb *)image.scanLine(Y);

				for(int i=0; i<width; i++, pM++){
					pYLine[i] = qRgb(*pM, *pM, *pM);
				}
			}

			(*TargetPageList)[page] = image;

			TargetOutlineList->append(QPoint(GetLayersBase()->GetPageData(page)->GetOutlineOffset()->x,GetLayersBase()->GetPageData(page)->GetOutlineOffset()->y));
		}
	}else if(GetLayerNumb(0)==2){// 特殊2色
		BYTE *pR,*pG;
		for(int page=0; page<GetLayersBase()->GetPageNumb(); page++){
			QImage image(GetLayersBase()->GetPhaseData()[cmd->phase]->GetPageData(page)->GetDotPerLine(), GetLayersBase()->GetPhaseData()[cmd->phase]->GetPageData(page)->GetMaxLines(), QImage::Format_RGB32);

			int width = GetLayersBase()->GetPhaseData()[cmd->phase]->GetPageData(page)->GetDotPerLine();
			int height = GetLayersBase()->GetPhaseData()[cmd->phase]->GetPageData(page)->GetMaxLines();

			#pragma omp for
			for(int Y=0; Y<height; Y++){
				pR=GetPageDataPhase(cmd->phase)->GetPageData(page)->GetDataInLayer(0)->GetMasterBuff().GetY(Y);
				pG=GetPageDataPhase(cmd->phase)->GetPageData(page)->GetDataInLayer(1)->GetMasterBuff().GetY(Y);
				QRgb *pYLine=(QRgb *)image.scanLine(Y);
				for(int X=0; X<width; X++,pR++,pG++){
					*pYLine = qRgb(*pR, *pG, 128);// 要検討128
					pYLine++;
				}
			}
			
			(*TargetPageList)[page] = image;

			TargetOutlineList->append(QPoint(GetLayersBase()->GetPageData(page)->GetOutlineOffset()->x,GetLayersBase()->GetPageData(page)->GetOutlineOffset()->y));
		}
	}else{
		for(int page=0; page<GetLayersBase()->GetPageNumb(); page++){
			(*TargetPageList)[page] = QImage();
			TargetOutlineList->append(QPoint(0,0));
			TargetWholeImgDrawPoints->append(QPoint(0,0));
		}
		cmd->Ret = false;
		return false;
	}

	if(TargetOutlineList->count()>1){
		int minX,maxX;
		int minY,maxY;
		minX = maxX = TargetOutlineList->first().x();
		minY = maxY = TargetOutlineList->first().y();

		for(int i=1; i<TargetOutlineList->count(); i++){
			if(minX>TargetOutlineList->at(i).x()){
				minX = TargetOutlineList->at(i).x();
			}
			if(maxX<TargetOutlineList->at(i).x()){
				maxX = TargetOutlineList->at(i).x();
			}
			if(minY>TargetOutlineList->at(i).y()){
				minY = TargetOutlineList->at(i).y();
			}
			if(maxY<TargetOutlineList->at(i).y()){
				maxY = TargetOutlineList->at(i).y();
			}
		}

		QPoint p(-minX, -minY);

		int w = qAbs(maxX - minX) + GetLayersBase()->GetDotPerLine(-1);
		int h = qAbs(maxY - minY) + GetLayersBase()->GetMaxLines(-1);

		*TargetWholeSize = QSize(w, h);

		//QList<QPoint> shiftOutlineList;
		TargetWholeImgDrawPoints->clear();
		for(int i=0; i<TargetOutlineList->count(); i++){
			//shiftOutlineList.append(QPoint(OutlineList->at(i) + p));
			TargetWholeImgDrawPoints->append(QPoint(TargetOutlineList->at(i) + p));
		}
	}else if(TargetOutlineList->count()==1){
		//*TargetImage = BuffImgList.front();
		*TargetWholeSize = TargetPageList->first().size();
		TargetWholeImgDrawPoints->append(TargetOutlineList->first());
	}else{
		//*TargetImage = QImage();
		(*TargetPageList).append(QImage());
		*TargetWholeSize = QSize(0, 0);
		TargetWholeImgDrawPoints->append(QPoint(0,0));
	}

	cmd->Ret = true;
	return true;
}

bool ReviewPIBase::ReciveCmdReqMasterImagePiece(GUIDirectMessage *packet)
{
	CmdReqMasterImagePiece *cmd = dynamic_cast<CmdReqMasterImagePiece *>(packet);
	if(cmd==NULL)return false;

	if(getMasterWholePageImageList(cmd->side).count()<cmd->phase+1){
		cmd->Ret = false;
		return true;
	}
	if(getMasterWholePageImageList(cmd->side, cmd->phase).isEmpty()==true){
		cmd->Ret = false;
		return true;
	}

	//if(cmd->side==Review::Front){
	//	//if(FrontWholeImage.isNull()){
	//	//	cmd->Ret = false;
	//	//	return true;
	//	//}
	//	if(FrontPageImages.count()<cmd->phase+1){
	//		cmd->Ret = false;
	//		return true;
	//	}
	//	if(FrontPageImages[cmd->phase].isEmpty()==true){
	//		cmd->Ret = false;
	//		return true;
	//	}
	//	//cmd->image = FrontWholeImage.copy(cmd->MasterX, cmd->MasterY, cmd->Width, cmd->Height);
	//}else{
	//	//if(BackWholeImage.isNull()){
	//	//	cmd->Ret = false;
	//	//	return true;
	//	//}
	//	if(BackPageImages.count()<cmd->phase+1){
	//		cmd->Ret = false;
	//		return true;
	//	}
	//	if(BackPageImages[cmd->phase].isEmpty()==true){
	//		cmd->Ret = false;
	//		return true;
	//	}
	//	//cmd->image = BackWholeImage.copy(cmd->MasterX, cmd->MasterY, cmd->Width, cmd->Height);
	//}
	
	cmd->image = GetMasterImagePiece(cmd->side, cmd->phase, cmd->page, cmd->MasterX, cmd->MasterY, cmd->Width, cmd->Height);
	
	cmd->Ret = true;
	return true;
}

bool ReviewPIBase::ReciveCmdReqMasterImagePieceOnOneImage(GUIDirectMessage *packet)
{
	CmdReqMasterImagePieceOnOneImage *cmd = dynamic_cast<CmdReqMasterImagePieceOnOneImage *>(packet);
	if(cmd==NULL)return false;
	
	if(getMasterWholePageImageList(cmd->side).count()<cmd->phase+1){
		cmd->Ret = false;
		return true;
	}
	if(getMasterWholePageImageList(cmd->side, cmd->phase).isEmpty()==true){
		cmd->Ret = false;
		return true;
	}

	//if(cmd->side==Review::Front){
	//	//if(FrontWholeImage.isNull()){
	//	//	cmd->Ret = false;
	//	//	return true;
	//	//}
	//	if(FrontPageImages.count()<cmd->phase+1){
	//		cmd->Ret = false;
	//		return true;
	//	}
	//	if(FrontPageImages[cmd->phase].isEmpty()==true){
	//		cmd->Ret = false;
	//		return true;
	//	}
	//	//cmd->image = FrontWholeImage.copy(cmd->MasterX, cmd->MasterY, cmd->Width, cmd->Height);
	//}else{
	//	//if(BackWholeImage.isNull()){
	//	//	cmd->Ret = false;
	//	//	return true;
	//	//}
	//	if(BackPageImages.count()<cmd->phase+1){
	//		cmd->Ret = false;
	//		return true;
	//	}
	//	if(BackPageImages[cmd->phase].isEmpty()==true){
	//		cmd->Ret = false;
	//		return true;
	//	}
	//	//cmd->image = BackWholeImage.copy(cmd->MasterX, cmd->MasterY, cmd->Width, cmd->Height);
	//}
		
	cmd->image = GetMasterImagePiece(cmd->side, cmd->phase, cmd->MasterX, cmd->MasterY, cmd->Width, cmd->Height);

	cmd->Ret = true;
	return true;
}

bool ReviewPIBase::ReciveCmdReqHistoryAllChecked(GUIDirectMessage *packet)
{
	CmdReqHistoryAllChecked *cmd = dynamic_cast<CmdReqHistoryAllChecked *>(packet);
	if(cmd==NULL)return false;

	OrganizedHistoryList HistoryPack = getOrganizedHistoryList();

	if(cmd->index>-1 && cmd->index<HistoryPack.count()){
		if(HistoryPack[cmd->index].hasFront()==true){
			for(int i=0; i<HistoryPack[cmd->index].getFront()->getNGNails().count(); i++){
				if(HistoryPack[cmd->index].getFront()->getNGNails()[i].isChecked==false){
					cmd->isAllChecked = false;
					cmd->Ret = true;
					return true;
				}
			}
		}
		if(HistoryPack[cmd->index].hasBack()==true){
			for(int i=0; i<HistoryPack[cmd->index].getBack()->getNGNails().count(); i++){
				if(HistoryPack[cmd->index].getBack()->getNGNails()[i].isChecked==false){
					cmd->isAllChecked = false;
					cmd->Ret = true;
					return true;
				}
			}
		}
	}else if(cmd->EID!=-1){
		for(int k=0; k<HistoryPack.count(); k++){
			if(HistoryPack[k].getInspectID()==cmd->EID){
				if(HistoryPack[k].hasFront()==true){
					for(int i=0; i<HistoryPack[k].getFront()->getNGNails().count(); i++){
						if(HistoryPack[k].getFront()->getNGNails()[i].isChecked==false){
							cmd->isAllChecked = false;
							cmd->Ret = true;
							return true;
						}
					}
				}
				if(HistoryPack[k].hasBack()==true){
					for(int i=0; i<HistoryPack[k].getBack()->getNGNails().count(); i++){
						if(HistoryPack[k].getBack()->getNGNails()[i].isChecked==false){
							cmd->isAllChecked = false;
							cmd->Ret = true;
							return true;
						}
					}
				}

				cmd->isAllChecked = true;
				cmd->Ret = true;
				return true;
			}
		}
		cmd->Ret = false;
		return true;
	}else{
		cmd->Ret = false;
		return true;
	}

	cmd->Ret = false;
	return true;
}

bool ReviewPIBase::ReciveCmdReqWholeImageInfo(GUIDirectMessage *packet)
{
	CmdReqWholeImageInfo *cmd = dynamic_cast<CmdReqWholeImageInfo *>(packet);
	if(cmd==NULL)return false;
	
	cmd->FrontWholeOrizinalSize	=	getMasterWholeImageSize(Review::Front);
	cmd->BackWholeOrizinalSize	=	getMasterWholeImageSize(Review::Back);
	cmd->FrontOutlineOffset		=	getMasterWholePageOutlineList(Review::Front);
	cmd->BackOutlineOffset		=	getMasterWholePageOutlineList(Review::Back);
	cmd->FrontOutlineDrawOffset	=	getMasterWholeImgDrawPoints(Review::Front);
	cmd->BackOutlineDrawOffset	=	getMasterWholeImgDrawPoints(Review::Back);

	cmd->zoomRate = getMasterImageNormalizeZoomRate();

	return true;
}

bool ReviewPIBase::ReciveCmdReqMasterInfoFromDataBase(GUIDirectMessage *packet)
{
	CmdReqMasterInfoFromDataBase *cmd = dynamic_cast<CmdReqMasterInfoFromDataBase *>(packet);
	if(cmd==NULL)return false;

	bool		ret;
	int			iMachineID;
	XDateTime	iRegTime;
	QString		iMasterName;
	QString		iRemark;
	int32		iVersion;
	XDateTime	iLastEditTime;
	int32		iCategoryID;
	int16		iMasterType;
	int			iDotPerLine;
	int			iMaxLines;
	int			iLayerNumb;
	int			iPageNumb;
	int			iPhaseNumb;
	int32		iLibFolderID;
	int32 		iThresholdLevelID;
	int32 		iThresholdLevelParentID;

	if(GetLayersBase()->GetDatabaseLoader()){
		ret=GetLayersBase()->GetDatabaseLoader()->G_SQLLoadMasterData2(GetLayersBase()->GetDatabase()
							,cmd->MasterCode
							,iMachineID
							,iRegTime
							,iMasterName ,iRemark
							,iVersion
							,iLastEditTime
							,iCategoryID
							,iMasterType
							,iDotPerLine
							,iMaxLines
							,iLayerNumb
							,iPageNumb
							,iPhaseNumb
							,iLibFolderID
							,iThresholdLevelID
							,iThresholdLevelParentID);

		if(ret==false){
			cmd->Ret = false;
			return true;
		}

		cmd->info.MasterCode = cmd->MasterCode;
		cmd->info.MachineID = iMachineID;
		cmd->info.RegTime = iRegTime;
		cmd->info.MasterName = iMasterName;
		cmd->info.Remark = iRemark;
		cmd->info.Version = iVersion;
		cmd->info.LastEditTime = iLastEditTime;
		cmd->info.CategoryID = iCategoryID;
		cmd->info.MasterType = iMasterType;
		cmd->info.DotPerLine = iDotPerLine;
		cmd->info.MaxLines = iMaxLines;
		cmd->info.LayerNumb = iLayerNumb;
		cmd->info.PageNumb = iPageNumb;
		cmd->info.LibFolderID	=iLibFolderID;
		if(iPhaseNumb==0){
			cmd->info.PhaseNumb = 1;
		}else{
			cmd->info.PhaseNumb = iPhaseNumb;
		}
		cmd->info.ThresholdLevelID		=iThresholdLevelID;
		cmd->info.ThresholdLevelParentID=iThresholdLevelParentID;

		cmd->Ret = true;
		return true;
	}

	cmd->Ret = false;
	return true;
}

bool ReviewPIBase::ReciveCmdFreeLayersImageMemory(GUIDirectMessage *packet)
{
	CmdFreeLayersImageMemory *cmd = dynamic_cast<CmdFreeLayersImageMemory *>(packet);
	if(cmd==NULL)return false;

	if(getFreeMasterBufferEnable()==true && (GetDotPerLine(-1)!=1 || GetMaxLines(-1)!=1)){
		GetParamGlobal()->DotPerLine=1;
		GetParamGlobal()->MaxLines	=1;
		GetLayersBase()->ResetSize();
		LayersBase *base = GetLayersBase();
		base->SetMasterCode(-1);
		base->SetMachineID(-1);
		base->InitialAfterParamLoaded();
		base->InitialCreatePages(GetLayersBase()->GetEntryPoint());
		base->ReallocAlgorithm();
		base->InitialResult();
	}

	return true;
}

bool ReviewPIBase::ReciveCmdClearSideLot(GUIDirectMessage *packet)
{
	CmdClearSideLot *cmd = dynamic_cast<CmdClearSideLot *>(packet);
	if(cmd==NULL)return false;

	XML_ClearLot(cmd->side);

	return true;
}

bool ReviewPIBase::ReciveCmdReqPCEList(GUIDirectMessage *packet)
{
	CmdReqPCEList *cmd = dynamic_cast<CmdReqPCEList *>(packet);
	if(cmd==NULL)return false;

	cmd->FrontList = getPCEList(Review::Front);
	cmd->BackList = getPCEList(Review::Back);
	
	return true;
}

bool ReviewPIBase::ReciveCmdReqSaveFormatMacroList(GUIDirectMessage *packet)
{
	CmdReqSaveFormatMacroList *cmd = dynamic_cast<CmdReqSaveFormatMacroList *>(packet);
	if(cmd==NULL)return false;
	
	cmd->macroSimbolInfoPairList = Review::getSaveNGImageFormatMacroList();

	return true;
}

bool ReviewPIBase::ReciveCommonCmdReqSettingPropertyDialog(GUIDirectMessage *packet)
{
	ReviewCommonPacket::CmdReqSettingPropertyDialog *cmd = dynamic_cast<ReviewCommonPacket::CmdReqSettingPropertyDialog *>(packet);
	if(cmd==NULL)return false;

	setPropertyToUi(getProperty());

	cmd->setDialog(getPropertyDialog());
	cmd->setGroupName(/**/"Global");
	cmd->setGUIName(/**/"ReviewStructure");

	return true;
};

bool ReviewPIBase::ReciveCmdSaveCurrentNGImage(GUIDirectMessage *packet)
{
	CmdSaveCurrentNGImage *cmd = dynamic_cast<CmdSaveCurrentNGImage *>(packet);
	if(cmd==NULL)return false;

	if(getRoundCurrentOrganizedHistoryIterator(Review::CurrentPos)==OrganizedHistoryList::Iterator()){
		cmd->Ret = false;
		return true;
	}

	bool saveSuccess = false;

	// コンバート後のファイルパスを取得
	QString filename = convertedSaveNGFileName(getCurrentSideType(), getRoundCurrentOrganizedHistoryIterator(Review::CurrentPos), getRoundCurrentNGNailIterator(Review::CurrentPos));

	// ファイルを保存する場所の情報を取得
	QFileInfo info(filename);

	// ディレクトリがない場合は保存に失敗するので作成する
	QDir dir;
	if(dir.mkpath(info.absolutePath())){// 作成成功時のみ保存
		// 画像の作成

		// NGの元画像
		QImage image = getRoundCurrentNGNailIterator(Review::CurrentPos)->image();

		// 要求に応じてNGを描画
		if(cmd->drawNGShape==true){
			QPainter painter(&image);
			for(ReviewNGPointList::Iterator pIt=getRoundCurrentNGNailIterator(Review::CurrentPos)->NGPointList.begin(); pIt!=getRoundCurrentNGNailIterator(Review::CurrentPos)->NGPointList.end(); pIt++){
				Review::DrawNGShapeToPainter(&painter, pIt->Tag.NGColor, pIt->Tag.NGShape, pIt->getNGPos(), cmd->NGSingRoundSize);
			}
		}
	
		// 保存
		if(image.save(filename)==false){
			// 失敗する場合は強制的にPNG画像形式で保存させる
			if(image.save(filename + ".png", "PNG")==false){
				// それでも失敗する場合はメッセージ付きファイルを生成して終了
				QFile file(filename + ".txt");
				if(file.open(QIODevice::WriteOnly)==true){
					QTextStream stream(&file);
					stream << "This image is not saved." << endl;
					stream << "Image file would not exist." << endl;
				}
			}else{
				saveSuccess = true;
			}
		}else{
			saveSuccess = true;
		}
	}

	if(saveSuccess==true){
		QMessageBox::information(NULL, "Saving NG image operation", "Finished");
	}else{
		QMessageBox::information(NULL, "Saving NG image operation", "Failure");
	}

	return true;
}

bool ReviewPIBase::ReciveCmdSaveCurrentHistoryNGImages(GUIDirectMessage *packet)
{
	CmdSaveCurrentHistoryNGImages *cmd = dynamic_cast<CmdSaveCurrentHistoryNGImages *>(packet);
	if(cmd==NULL)return false;
	
	OrganizedHistoryList::Iterator hIt = getRoundCurrentOrganizedHistoryIterator(Review::CurrentPos);

	if(hIt==OrganizedHistoryList::Iterator()){
		QMessageBox::information(NULL, "Saving NG image operation in current inspection", "Failure");
		cmd->Ret = false;
		return true;
	}

	int saveTargetCount = 0;
	int saveSuccessCount = 0;

	if(hIt->hasFront()==true){
		saveTargetCount += hIt->getFront()->getNGNails().count();
	}
	if(hIt->hasBack()==true){
		saveTargetCount += hIt->getBack()->getNGNails().count();
	}

	QProgressDialog progress;
	progress.setRange(0, saveTargetCount);
	progress.setValue(0);
	progress.setLabelText("Now saving NG image...");

	if(hIt->hasFront()==true){
		for(NGNailList::Iterator it=hIt->getFront()->getNGNails().begin(); it!=hIt->getFront()->getNGNails().end(); it++){
			saveTargetCount++;

			if(progress.wasCanceled()==true){
				return true;
			}
			progress.setValue(progress.value()+1);

			// コンバート後のファイルパスを取得
			QString filename = convertedSaveNGFileName(Review::Front, hIt, it);
			
			// ファイルを保存する場所の情報を取得
			QFileInfo info(filename);

			// ディレクトリがない場合は保存に失敗するので作成する
			QDir dir;
			if(dir.mkpath(info.absolutePath())){// 作成成功時のみ保存
				// 画像の作成

				// NGの元画像
				QImage image = it->image();

				// 要求に応じてNGを描画
				if(cmd->drawNGShape==true){
					QPainter painter(&image);
					for(ReviewNGPointList::Iterator pIt=it->NGPointList.begin(); pIt!=it->NGPointList.end(); pIt++){
						Review::DrawNGShapeToPainter(&painter, pIt->Tag.NGColor, pIt->Tag.NGShape, pIt->getNGPos(), cmd->NGSingRoundSize);
					}
				}

				// 保存
				if(image.save(filename)==false){
					// 失敗する場合は強制的にPNG画像形式で保存させる
					if(image.save(filename + ".png", "PNG")==false){
						// それでも失敗する場合はメッセージ付きファイルを生成して終了
						QFile file(filename + ".txt");
						if(file.open(QIODevice::WriteOnly)==true){
							QTextStream stream(&file);
							stream << "This image is not saved." << endl;
							stream << "Image file would not exist." << endl;
						}
					}else{
						saveSuccessCount++;
					}
				}else{
					saveSuccessCount++;
				}
			}
		}
	}
	if(hIt->hasBack()==true){
		for(NGNailList::Iterator it=hIt->getBack()->getNGNails().begin(); it!=hIt->getBack()->getNGNails().end(); it++){
			saveTargetCount++;
			
			if(progress.wasCanceled()==true){
				return true;
			}
			progress.setValue(progress.value()+1);
			
			// コンバート後のファイルパスを取得
			QString filename = convertedSaveNGFileName(Review::Back, hIt, it);
			
			// ファイルを保存する場所の情報を取得
			QFileInfo info(filename);
			
			// ディレクトリがない場合は保存に失敗するので作成する
			QDir dir;
			if(dir.mkpath(info.absolutePath())){// 作成成功時のみ保存
				// 画像の作成

				// NGの元画像
				QImage image = it->image();

				// 要求に応じてNGを描画
				if(cmd->drawNGShape==true){
					QPainter painter(&image);
					for(ReviewNGPointList::Iterator pIt=it->NGPointList.begin(); pIt!=it->NGPointList.end(); pIt++){
						Review::DrawNGShapeToPainter(&painter, pIt->Tag.NGColor, pIt->Tag.NGShape, pIt->getNGPos(), cmd->NGSingRoundSize);
					}
				}

				// 保存
				if(image.save(filename)==false){
					// 失敗する場合は強制的にPNG画像形式で保存させる
					if(image.save(filename + ".png", "PNG")==false){
						// それでも失敗する場合はメッセージ付きファイルを生成して終了
						QFile file(filename + ".txt");
						if(file.open(QIODevice::WriteOnly)==true){
							QTextStream stream(&file);
							stream << "This image is not saved." << endl;
							stream << "Image file would not exist." << endl;
						}
					}else{
						saveSuccessCount++;
					}
				}else{
					saveSuccessCount++;
				}
			}
		}
	}

	if(saveTargetCount==saveSuccessCount){
		QMessageBox::information(NULL, "Saving NG image operation in current inspection", "Finished");
	}else{
		QMessageBox::information(NULL, "Saving NG image operation in current inspection", "Some image could not be saved.");
	}

	return true;
}

bool ReviewPIBase::ReciveCmdUpdateLotInfoList(GUIDirectMessage *packet)
{
	CmdUpdateLotInfoList *cmd = dynamic_cast<CmdUpdateLotInfoList *>(packet);
	if(cmd==NULL)return false;

	QStringList enumList;
	LotInfoList list;
	Review::SideType side;

	MasterDataInfo FMData =  getMasterInfo(Review::Front);
	MasterDataInfo BMData =  getMasterInfo(Review::Back);

	// 表 //
	side = Review::Front;

	XML_GetLot(FMData.MasterCode, FMData.MachineID, enumList);

	for(int i=0; i<enumList.count(); i++){
		list << XML_GetLotInfo(enumList[i]);
	}

	cmd->FrontLotList = list;

	setLotInfoAllList(side, list);
	list.clear();

	// 裏
	XML_GetLot(BMData.MasterCode, BMData.MachineID, enumList);

	for(int i=0; i<enumList.count(); i++){
		list << XML_GetLotInfo(enumList[i]);
	}

	cmd->BackLotList = list;

	setLotInfoAllList(side, list);

	return true;
}

bool ReviewPIBase::ReciveCmdReqCurrentLotAllList(GUIDirectMessage *packet)
{
	CmdReqCurrentLotAllList *cmd = dynamic_cast<CmdReqCurrentLotAllList *>(packet);
	if(cmd==NULL)return false;

	cmd->FrontLotList = getLotInfoAllList(Review::Front);
	cmd->BackLotList = getLotInfoAllList(Review::Back);
	
	return true;
}

bool ReviewPIBase::ReciveCmdReqVRSSetting(GUIDirectMessage *packet)
{
	CmdReqVRSSetting *cmd = dynamic_cast<CmdReqVRSSetting *>(packet);
	if(cmd==NULL)return false;

	cmd->setting = getVRSSetting();

	return true;
}

bool ReviewPIBase::ReciveCmdSetVRSSetting(GUIDirectMessage *packet)
{
	CmdSetVRSSetting *cmd = dynamic_cast<CmdSetVRSSetting *>(packet);
	if(cmd==NULL)return false;

	setVRSSetting(cmd->setting);

	return true;
}

bool ReviewPIBase::ReciveCmdReqMasterImageList(GUIDirectMessage *packet)
{
	CmdReqMasterImageList *cmd = dynamic_cast<CmdReqMasterImageList *>(packet);
	if(cmd==NULL)return false;

	CmdReqMasterImageList::ConstImageList *frontList;
	if(getMasterInfo(Review::Front).MasterCode!=-1 && getMasterInfo(Review::Front).MachineID!=-1){
		frontList = new CmdReqMasterImageList::ConstImageList(getMasterWholePageImageList(Review::Front));
	}else{
		frontList = NULL;
	}

	CmdReqMasterImageList::ConstImageList *backList;
	if(getMasterInfo(Review::Back).MasterCode!=-1 && getMasterInfo(Review::Back).MachineID!=-1){
		backList = new CmdReqMasterImageList::ConstImageList(getMasterWholePageImageList(Review::Back));
	}else{
		backList = NULL;
	}

	QList<QList<QPoint> > frontOutlineList;
	if(frontList!=NULL){
		frontOutlineList = getMasterWholePageOutlineList(Review::Front);
	}

	QList<QList<QPoint> > backOutlineList;
	if(backList!=NULL){
		backOutlineList = getMasterWholePageOutlineList(Review::Back);
	}

	cmd->setImageList(frontList, backList);
	cmd->setOutlineList(frontOutlineList, backOutlineList);
	cmd->MasterImageNormalizeZoomRate = getMasterImageNormalizeZoomRate();

	return true;
}

bool ReviewPIBase::ReciveCmdReqVRSAlignment(GUIDirectMessage *packet)
{
	CmdReqVRSAlignment *cmd = dynamic_cast<CmdReqVRSAlignment *>(packet);
	if(cmd==NULL)return false;

	cmd->frontAlignment = getVRSAlignment(Review::Front);
	cmd->backAlignment = getVRSAlignment(Review::Back);

	//VRSAlignment::ThreePointAlignment setting = getVRSAlignmentFromWhole(cmd->side);
	//cmd->InspectionWholeRects.setFirst(setting.getInsAlignmentRect(Review::Alignment_First));
	//cmd->InspectionWholeRects.setSecond(setting.getInsAlignmentRect(Review::Alignment_Second));
	//cmd->InspectionWholeRects.setThird(setting.getInsAlignmentRect(Review::Alignment_Third));

	//cmd->MachineWholeRects.setFirst(setting.getVRSAlignmentRect(Review::Alignment_First));
	//cmd->MachineWholeRects.setSecond(setting.getVRSAlignmentRect(Review::Alignment_Second));
	//cmd->MachineWholeRects.setThird(setting.getVRSAlignmentRect(Review::Alignment_Third));

	//
	//QList<VRSAlignment::ThreePointAlignment> settingList = getVRSAlignmentFromEachPage(cmd->side);
	//cmd->InspectionEachPageRects.clear();
	//cmd->MachineEachPageRects.clear();
	//for(int i=0; i<settingList.count(); i++){
	//	Review::ThreeValue<QRect> InsRects,MachineRects;

	//	InsRects.setFirst(settingList[i].getInsAlignmentRect(Review::Alignment_First));
	//	MachineRects.setFirst(settingList[i].getVRSAlignmentRect(Review::Alignment_First));
	//	
	//	InsRects.setSecond(settingList[i].getInsAlignmentRect(Review::Alignment_Second));
	//	MachineRects.setSecond(settingList[i].getVRSAlignmentRect(Review::Alignment_Second));

	//	InsRects.setThird(settingList[i].getInsAlignmentRect(Review::Alignment_Third));
	//	MachineRects.setThird(settingList[i].getVRSAlignmentRect(Review::Alignment_Third));

	//	cmd->InspectionEachPageRects << InsRects;
	//	cmd->MachineEachPageRects << MachineRects;
	//}

	return true;
}

bool ReviewPIBase::ReciveCmdSetVRSAlignment(GUIDirectMessage *packet)
{
	CmdSetVRSAlignment *cmd = dynamic_cast<CmdSetVRSAlignment *>(packet);
	if(cmd==NULL)return false;

	VRSAlignment::ThreePointAlignment wAlignment;
	bool isWChanged = false;

	if(cmd->isVRSAlignmentTypeChanged()==true){
		isWChanged = true;
		getVRSAlignment(cmd->side()).setAlignmentType(cmd->getVRSAlignmentType());
	}
	
	if(cmd->isInspectionWholeRectsChanged()==true){
		isWChanged = true;
		wAlignment.setInsAlignment( cmd->getInspectionWholeRects() );
	}else{
		wAlignment.setInsAlignment( getVRSAlignmentFromWhole(cmd->side()).getInsAlignment() );
	}

	if(cmd->isMachineWholeRectsChanged()==true){
		isWChanged = true;
		wAlignment.setVRSAlignment( cmd->getInspectionWholeRects() );
	}else{
		wAlignment.setVRSAlignment( getVRSAlignmentFromWhole(cmd->side()).getVRSAlignment() );
	}

	if(isWChanged == true){
		setVRSAlignmentToWhole(cmd->side(), wAlignment);
	}

	QList<VRSAlignment::ThreePointAlignment> eAlignmentList;
	bool isEChanged = false;
	if(cmd->isInspectionEachPageRectsChanged()==true){
		isEChanged = true;
		for(int i=0; i<cmd->getInspectionEachPageRects().count(); i++){
			VRSAlignment::ThreePointAlignment eAlignItem;

			eAlignItem.setInsAlignment( cmd->getInspectionEachPageRects()[i] );

			eAlignmentList << eAlignItem;
		}
	}else{
		for(int i=0; i<getVRSAlignmentFromEachPage(cmd->side()).count(); i++){
			VRSAlignment::ThreePointAlignment eAlignItem;

			eAlignItem.setInsAlignment( getVRSAlignmentFromEachPage(cmd->side())[i].getInsAlignment() );

			eAlignmentList << eAlignItem;
		}
	}

	if(cmd->isMachineEachPageRectsChanged()==true){
		isEChanged = true;
		while(eAlignmentList.count()<cmd->getMachineEachPageRects().count()){
			eAlignmentList << VRSAlignment::ThreePointAlignment();
		}

		for(int i=0; i<cmd->getMachineEachPageRects().count(); i++){
			eAlignmentList[i].setVRSAlignment( cmd->getMachineEachPageRects()[i] );
		}
	}else{
		while(eAlignmentList.count()<getVRSAlignmentFromEachPage(cmd->side()).count()){
			eAlignmentList << VRSAlignment::ThreePointAlignment();
		}

		for(int i=0; i<getVRSAlignmentFromEachPage(cmd->side()).count(); i++){
			eAlignmentList[i].setVRSAlignment( getVRSAlignmentFromEachPage(cmd->side())[i].getVRSAlignment() );
		}
	}

	if(isEChanged==true){
		setVRSAlignmentToEachPage(cmd->side(), eAlignmentList);
	}

	if(isWChanged==true || isEChanged==true){
		saveVRSSetting();
	}

	return true;
}

bool ReviewPIBase::ReciveCmdReqVRSMotorState(GUIDirectMessage *packet)
{
	CmdReqVRSMotorState *cmd = dynamic_cast<CmdReqVRSMotorState *>(packet);
	if(cmd==NULL)return false;
	if(hasSequenceThread()==false){
		cmd->ret = false;
		return true;
	}

	cmd->x = getSequenceThread()->x();
	cmd->y = getSequenceThread()->y();
	cmd->z = getSequenceThread()->z();

	cmd->x_enable = getSequenceThread()->isXEnable();
	cmd->y_enable = getSequenceThread()->isYEnable();
	cmd->z_enable = getSequenceThread()->isZEnable();

	cmd->ret = true;

	return true;
}

bool ReviewPIBase::ReciveCmdSetVRSMotorState(GUIDirectMessage *packet)
{
	CmdSetVRSMotorState *cmd = dynamic_cast<CmdSetVRSMotorState *>(packet);
	if(cmd==NULL)return false;

	cmd->ret = false;
	
	if(isSequenceEnable()==false || cmd->isEmpty()==true){
		return true;
	}

	ReviewSequenceRequire item;
	if(cmd->isXEnable()==true){
		item.setMoveX(cmd->x());
	}
	if(cmd->isYEnable()==true){
		item.setMoveY(cmd->y());
	}
	if(cmd->isZEnable()==true){
		ZHeightBeforeEscape=cmd->z();
		item.setMoveZ(cmd->z());
	}
	EscapeLastTime=false;
	getSequenceThread()->append(item);
	
	cmd->ret = true;

	return true;
}

bool ReviewPIBase::ReciveCmdReqCameraAlignment(GUIDirectMessage *packet)
{
	CmdReqCameraAlignment *cmd = dynamic_cast<CmdReqCameraAlignment *>(packet);
	if(cmd==NULL)return false;

	if(cmd->isEnable()==false){
		return true;
	}
	int pulsePerMM_x = getSequenceThread()->pulsePerMM_x();
	int pulsePerMM_y = getSequenceThread()->pulsePerMM_y();
	QSize cameraViewRealSize = getVRSSetting().getVRSSideSetting().CameraViewRealSize;
	QSize cameraViewMotorValSize = cameraViewRealSize;
	cameraViewMotorValSize.setWidth( cameraViewMotorValSize.width() * pulsePerMM_x / 1000.0 );
	cameraViewMotorValSize.setHeight( cameraViewMotorValSize.height() * pulsePerMM_y / 1000.0 );

	QPoint alignPoint;

	if(cmd->VRSAlignmentType()==Review::VRSAlignmentType::VRSAlingmentWholeImage){
		VRSAlignment::ThreePointAlignment points = getVRSAlignmentFromWhole(cmd->side());


		alignPoint	=points.getAlignmentPoint(Review::AlignmentSide_VRSMachine,
						static_cast<Review::AlignmentNo>(cmd->number()));

	}else{
		QList<VRSAlignment::ThreePointAlignment> points = getVRSAlignmentFromEachPage(cmd->side());

		alignPoint	=points[cmd->page()].getAlignmentPoint(Review::AlignmentSide_VRSMachine,
						static_cast<Review::AlignmentNo>(cmd->number()));
	}
	cmd->setPoint(alignPoint);
	return true;
}

bool ReviewPIBase::ReciveCmdSetCameraAlignment(GUIDirectMessage *packet)
{
	CmdSetCameraAlignment *cmd = dynamic_cast<CmdSetCameraAlignment *>(packet);
	if(cmd==NULL)return false;

	if(cmd->isEnable()==false){
		return true;
	}

	int pulsePerMM_x = getSequenceThread()->pulsePerMM_x();
	int pulsePerMM_y = getSequenceThread()->pulsePerMM_y();

	QPoint currentCenter(getSequenceThread()->x(), getSequenceThread()->y());

	QSize cameraViewRealSize = getVRSSetting().getVRSSideSetting().CameraViewRealSize;
	QSize cameraViewMotorValSize = cameraViewRealSize;
	cameraViewMotorValSize.setWidth( cameraViewMotorValSize.width() * pulsePerMM_x / 1000.0 );
	cameraViewMotorValSize.setHeight( cameraViewMotorValSize.height() * pulsePerMM_y / 1000.0 );

	//本来中心に来るはずのもののずれを計算
	QRectF alignmentVRSRect;
	alignmentVRSRect.setTopLeft( QPoint(currentCenter.x() - cameraViewMotorValSize.width()/2, currentCenter.y() - cameraViewMotorValSize.height()/2) );
	alignmentVRSRect.setSize( cameraViewMotorValSize );

	/*
	CmdReqVRSSetting reqVRSSetting(GetLayersBase());
	TransmitDirectly( &reqVRSSetting );
	GUICmdReqCamSize	reqCamSize(GetLayersBase());
	GetLayersBase()->DeliverTransmitDirectly(&reqCamSize);
	
	double	cx=(cmd->rect().left()+cmd->rect().right())/2;
	double	cy=(cmd->rect().top()+cmd->rect().bottom())/2;
	int		gshiftX=alignmentVRSRect.width()*cx;	//画面上のずれX
	int		gshiftY=alignmentVRSRect.height()*cy;	//画面上のずれY
	double	ResCamXY=reqVRSSetting.setting.getVRSSideSetting().CameraViewRealSize.width()/
	*/

	alignmentVRSRect.setLeft(alignmentVRSRect.left() + alignmentVRSRect.width() * cmd->rect().left() );
	alignmentVRSRect.setTop(alignmentVRSRect.top() + alignmentVRSRect.height() * cmd->rect().top() );
	alignmentVRSRect.setRight(alignmentVRSRect.left() + alignmentVRSRect.width() * cmd->rect().right() );
	alignmentVRSRect.setBottom(alignmentVRSRect.top() + alignmentVRSRect.height() * cmd->rect().bottom() );

	QRect alignRect = alignmentVRSRect.toRect();

	if(cmd->VRSAlignmentType()==Review::VRSAlignmentType::VRSAlingmentWholeImage){
		VRSAlignment::ThreePointAlignment points = getVRSAlignmentFromWhole(cmd->side());

		points.setAlignmentPoint(Review::AlignmentSide_VRSMachine,
			static_cast<Review::AlignmentNo>(cmd->number()),
			alignRect);

		setVRSAlignmentToWhole(cmd->side(), points);
	}else{
		QList<VRSAlignment::ThreePointAlignment> points = getVRSAlignmentFromEachPage(cmd->side());

		Review::increase(cmd->page()+1, points);

		points[cmd->page()].setAlignmentPoint(Review::AlignmentSide_VRSMachine,
			static_cast<Review::AlignmentNo>(cmd->number()),
			alignRect);

		setVRSAlignmentToEachPage(cmd->side(), points);
	}

	saveVRSSetting();
	
	return true;
}

bool ReviewPIBase::ReciveCmdReqSequenceEnable(GUIDirectMessage *packet)
{
	CmdReqSequenceEnable *cmd = dynamic_cast<CmdReqSequenceEnable *>(packet);
	if(cmd==NULL)return false;

	cmd->enable = isSequenceEnable();
	
	return true;
}

bool ReviewPIBase::ReciveCmdSetSequenceEnable(GUIDirectMessage *packet)
{
	CmdSetSequenceEnable *cmd = dynamic_cast<CmdSetSequenceEnable *>(packet);
	if(cmd==NULL)return false;

	setSequenceEnable(cmd->enable);
	
	return true;
}

bool ReviewPIBase::ReciveCmdMoveVRSToCurrentNG(GUIDirectMessage *packet)
{
	CmdMoveVRSToCurrentNG *cmd = dynamic_cast<CmdMoveVRSToCurrentNG *>(packet);
	if(cmd==NULL)return false;

	NGNailList::Iterator curNG = getRoundCurrentNGNailIterator(Review::CurrentPos);
	if(curNG!=NGNailList::Iterator()){
		sendVRSToMoveXY(*curNG, cmd->checkVRSEnable);
	}

	return true;
}

bool ReviewPIBase::ReciveCmdClearVRSCommandBuffer(GUIDirectMessage *packet)
{
	CmdClearVRSCommandBuffer *cmd = dynamic_cast<CmdClearVRSCommandBuffer *>(packet);
	if(cmd==NULL)return false;

	if(hasSequenceThread()==true){
		getSequenceThread()->clear();
	}

	return true;
}

bool ReviewPIBase::ReciveCmdMoveVRSOnCameraView(GUIDirectMessage *packet)
{
	CmdMoveVRSOnCameraView *cmd = dynamic_cast<CmdMoveVRSOnCameraView *>(packet);
	if(cmd==NULL)return false;

	if(isSequenceEnable()==false){
		return true;
	}
	
	const VRSSetting &vrs = getVRSSetting();

	int currentX = getSequenceThread()->x();
	int currentY = getSequenceThread()->y();
	int pulsePerMM_x = getSequenceThread()->pulsePerMM_x();
	int pulsePerMM_y = getSequenceThread()->pulsePerMM_y();

	QSize viewSize = vrs.getVRSSideSetting().CameraViewRealSize;

	if((pulsePerMM_x<=0 && pulsePerMM_y<=0) || viewSize.width()==0 || viewSize.height()==0){
		return true;
	}

	int toX = qRound( qreal(currentX) + cmd->x * viewSize.width()/2 * pulsePerMM_x / 1000.0 );
	int toY = qRound( qreal(currentY) + cmd->y * viewSize.height()/2 * pulsePerMM_y / 1000.0 );

	sendVRSToMoveXY(toX, toY);

	return true;
}

bool ReviewPIBase::ReciveCmdMoveVRSWithAlignment(GUIDirectMessage *packet)
{
	CmdMoveVRSWithAlignment *cmd = dynamic_cast<CmdMoveVRSWithAlignment *>(packet);
	if(cmd==NULL)return false;

	if(cmd->type==Review::VRSAlignmentType::VRSAlingmentWholeImage){
		sendVRSToMoveXYAsWhole(cmd->side, cmd->phase, cmd->page, cmd->x, cmd->y);
	}else{
		sendVRSToMoveXYAsEachPage(cmd->side, cmd->phase, cmd->page, cmd->x, cmd->y);
	}
	
	return true;
}

bool ReviewPIBase::ReciveCmdMoveVRSToOrigin(GUIDirectMessage *packet)
{
	CmdMoveVRSToOrigin *cmd = dynamic_cast<CmdMoveVRSToOrigin *>(packet);
	if(cmd==NULL)return false;

	const QPoint origin = getVRSSetting().getVRSSideSetting().MotorOrigin;

	//sendVRSToMoveXY(origin.x(), origin.y(), cmd->isCheckVRSEnable());
	sendVRSToOrigin(cmd->isCheckVRSEnable());
	return true;
}

bool	ReviewPIBase::ReciveCmdMoveVRSToEscape(GUIDirectMessage *packet)
{
	EscapeLastTime=true;

	CmdMoveVRSToEscape *cmd = dynamic_cast<CmdMoveVRSToEscape *>(packet);
	if(cmd==NULL)return false;

	const QVector3D escape = getVRSSetting().getVRSSideSetting().EscapePosition;

	sendVRSToMoveXYZ(escape.x(), escape.y(), escape.z(), cmd->isCheckVRSEnable());
	//sendVRSToMoveZ(escape.z(), cmd->isCheckVRSEnable());

	return true;
}

bool ReviewPIBase::LoadMasterImage(int skipCount ,int LayerNumb ,QList<QImage> &ImageByPage ,const QString &FileName)
{
	if(GetParamGlobal()->ImageFileCachePort==0){
		QFile file;

		file.setFileName(FileName);
		if(file.exists()==true && file.open(QIODevice::ReadOnly)==true){
			if(LoadMasterImage(skipCount ,LayerNumb ,ImageByPage ,file)==false)
				return false;
		}
		else{
			return false;
		}
	}
	else{
		TrFile	file(FileName,GetParamGlobal()->TransDatabaseIP
							 ,GetParamGlobal()->ImageFileCachePort);
		if(file.exists()==true && file.open(QIODevice::ReadOnly)==true){
			if(LoadMasterImage(skipCount ,LayerNumb ,ImageByPage ,file)==false)
				return false;
		}
		else{
			return false;
		}
	}
	return true;
}

bool ReviewPIBase::LoadMasterImage(int skipCount ,int LayerNumb ,QList<QImage> &ImageByPage 
					,QIODevice &file)
{
	ImageBuffer dummyBuffer;

	int layer;
	for(layer=0; layer<LayerNumb; layer++){
		QImage image = ImageBuffer::toImage(&file, skipCount);
		if(image.isNull()==true){
			return false;
		}
		ImageByPage.append(image);

		//image.convertToFormat(QImage::Format_RGB32).scaled(500, 500, Qt::KeepAspectRatio).save(QString("MPix"));
						
		if(dummyBuffer.Load(&file)==false){
			return false;
		}
		if(dummyBuffer.Load(&file)==false){
			return false;
		}
	}
	return true;
}

bool ReviewPIBase::ReciveCmdLoadMasterImage(GUIDirectMessage *packet)
{
	CmdLoadMasterImage *cmd = dynamic_cast<CmdLoadMasterImage *>(packet);
	if(cmd==NULL)return false;

	QList<QList<QImage> >* ptr = getMasterWholePageImageListPtr(cmd->side);

	QList<QList<QImage> > imageList = *ptr;

	int PhaseNumb=0;
	int PageNumb=0;
	for(int i=0; i<cmd->imgDataList.count(); i++){
		if(cmd->imgDataList[i].phase+1>PhaseNumb){
			PhaseNumb = cmd->imgDataList[i].phase+1;
		}
		
		if(cmd->imgDataList[i].page+1>PageNumb){
			PageNumb = cmd->imgDataList[i].page+1;
		}
	}

	if(PhaseNumb==0 || PageNumb==0){
		return true;
	}

	Review::increase(PhaseNumb, PageNumb, imageList);

	int	PageCOunt=cmd->imgDataList.count();
	int skipCount = getProperty().SkipMasterImageRate;
	QList<QImage> ImageByPage[100];
	//#pragma omp parallel
	//{
	//	#pragma omp for
	//if(GetParamGlobal()->AllocateMasterBuff==true){	//2019.5.26
		for(int i=0; i<PageCOunt; i++){
			Review::MasterImageFileData data = cmd->imgDataList[i];
			if(LoadMasterImage(skipCount ,getMasterInfo(cmd->side).LayerNumb,ImageByPage[i] ,data.fileName)==false){
				GSleep(2000);
				if(LoadMasterImage(skipCount ,getMasterInfo(cmd->side).LayerNumb,ImageByPage[i] ,data.fileName)==false){
					GSleep(30000);
					if(LoadMasterImage(skipCount ,getMasterInfo(cmd->side).LayerNumb,ImageByPage[i] ,data.fileName)==false){
						GSleep(60000);
						if(LoadMasterImage(skipCount ,getMasterInfo(cmd->side).LayerNumb,ImageByPage[i] ,data.fileName)==false){
							continue;
						}
					}
				}
			}
		}
		for(int i=0; i<PageCOunt; i++){
			int layer=getMasterInfo(cmd->side).LayerNumb;
			QImage	image;
			if(layer==0){
				continue;
			}else if(layer==1){
				image = Review::toRGBImage(ImageByPage[i].first(), QImage(), QImage(), true);
				//ImageByPage[i].first().save("C:\\Tmp\\FrontImage.bmp","BMP");
				//image				  .save("C:\\Tmp\\FrontImage.bmp","BMP");
			}else if(layer==2){
				image = Review::toRGBImage(ImageByPage[i][0], ImageByPage[i][1], QImage(), true);
			}else if(layer==3){
				image = Review::toRGBImage(ImageByPage[i][0], ImageByPage[i][1], ImageByPage[i][2], true);
			}
			if(imageList.count()>cmd->imgDataList[i].phase && imageList.at(cmd->imgDataList[i].phase).count()>cmd->imgDataList[i].page){
				imageList[cmd->imgDataList[i].phase][cmd->imgDataList[i].page] = image;
			}
		}
	//}

	*ptr = imageList;

	//for(int phase=0; phase<ptr->count(); phase++){
	//	for(int page=0; page<ptr->at(phase).count(); page++){
	//		ptr->at(phase).at(page).scaled(500, 500, Qt::KeepAspectRatio).save(QString("MImage-Phase%1-Page%2.png").arg(phase).arg(page));
	//	}
	//}

	QList<QList<QPoint> > drawPointList;
	QList<QSize> wholeSizeList;

	drawPointList = getMasterWholeImgDrawPoints(cmd->side);
	Review::increase(PhaseNumb, PageNumb, drawPointList);
	Review::increase(PhaseNumb, PageNumb, m_FrontOutline);
	Review::increase(PhaseNumb, PageNumb, m_BackOutline);

	for(int phase=0; phase<PhaseNumb; phase++){
		QList<QPoint> outlines = getMasterWholePageOutlineList(cmd->side, phase);
		drawPointList[phase] = outlines;
		if((*ptr)[phase].count()>1){
			int minX,maxX;
			int minY,maxY;
			minX = maxX = outlines.first().x();
			minY = maxY = outlines.first().y();
			
			for(int page=1; page<ptr->at(phase).count(); page++){
				if(minX>outlines.at(page).x()){
					minX = outlines.at(page).x();
				}
				if(maxX<outlines.at(page).x()){
					maxX = outlines.at(page).x();
				}
				if(minY>outlines.at(page).y()){
					minY = outlines.at(page).y();
				}
				if(maxY<outlines.at(page).y()){
					maxY = outlines.at(page).y();
				}
			}

			QPoint p(-minX, -minY);

			int w = qAbs(maxX - minX) + getMasterInfo(cmd->side).DotPerLine;
			int h = qAbs(maxY - minY) + getMasterInfo(cmd->side).MaxLines;

			wholeSizeList.append(QSize(w,h));

			for(int page=0; page<drawPointList[phase].count(); page++){
				drawPointList[phase][page] = QPoint(outlines[page] + p);
			}
		}else if((*ptr)[phase].count()==1){
			drawPointList[phase][0] = QPoint(0,0);
			wholeSizeList.append(QSize(getMasterInfo(cmd->side).DotPerLine, getMasterInfo(cmd->side).MaxLines));
		}else{
			// Error
			wholeSizeList.clear();
		}
	}

	//qDebug() << drawPointList;
	//qDebug() << wholeSizeList;

	*getMasterWholeImgDrawPointsPtr(cmd->side) = drawPointList;
	*getMasterWholeImageSizePtr(cmd->side) = wholeSizeList;

	//for(int phase=0; phase<ptr->count(); phase++){
	//	drawPoints[phase] = QVector<QPoint>(ptr->at(phase).count()).toList();
	//	QList<QPoint> outlines = getMasterWholePageOutlineList(cmd->side, phase);

	//	for(int page=0; page<ptr->at(phase).count(); page++){
	//		
	//		// 描画位置バッファの確保
	//		QList<QPoint> drawPointList = getMasterWholePageOutlineList(cmd->side, phase);

	//		// 全体画像サイズの調整
	//		QList<QSize> *wholeSizeList = getMasterWholeImageSizePtr(cmd->side);
	//		*wholeSizeList = QVector<QSize>(drawPointList.count()).toList();

	//		for(int phase=0; phase<ptr->count(); phase++){
	//			if((*ptr)[phase].count()>1){
	//				int minX,maxX;
	//				int minY,maxY;
	//				minX = maxX = outlines.first().x();
	//				minY = maxY = outlines.first().y();
	//		
	//				for(int page=1; page<ptr->at(phase).count(); page++){
	//					if(minX>outlines.at(page).x()){
	//						minX = outlines.at(page).x();
	//					}
	//					if(maxX<outlines.at(page).x()){
	//						maxX = outlines.at(page).x();
	//					}
	//					if(minY>outlines.at(page).y()){
	//						minY = outlines.at(page).y();
	//					}
	//					if(maxY<outlines.at(page).y()){
	//						maxY = outlines.at(page).y();
	//					}
	//				}

	//				QPoint p(-minX, -minY);

	//				int w = qAbs(maxX - minX) + GetLayersBase()->GetDotPerLine();
	//				int h = qAbs(maxY - minY) + GetLayersBase()->GetMaxLines();



	//				for(int i=0; i<drawPointList.count(); i++){
	//					(*TargetWholeImgDrawPoints)[phase].append(QPoint(TargetOutlines->at(phase)[i] + p));
	//				}
	//			}else{
	//				(*TargetWholeImgDrawPoints)[phase].append(QPoint(0,0));
	//			}
	//		}
	//	}
	//}
	
	return true;
}

bool ReviewPIBase::ReciveCmdLoadMaster(GUIDirectMessage *packet)
{
	CmdLoadMaster *cmd = dynamic_cast<CmdLoadMaster *>(packet);
	if(cmd==NULL)return false;

	if(cmd->isEnable()==false){
		return true;
	}

	RelationMasterList MasterListDim[100];
	int	MasterListDimCount=0;
	int	RelationCode=GetLayersBase()->SQLGetRelationCode(cmd->MasterCode);
	Review::OrganizedSideType type;
	if(RelationCode!=-1){
		MasterListDimCount=GetLayersBase()->SQLSearchMasterCode(RelationCode ,MasterListDim ,100);
		type = Review::Both;

		//for(int i=0; i<MasterListDimCount; i++){
		//	if(MasterListDim[i].MasterCode==cmd->MasterCode){
		//		if(i==0){
		//			break;
		//		}else{
		//			RelationMasterList tmp = MasterListDim[i];
		//			MasterListDim[i] = MasterListDim[0];
		//			MasterListDim[0] = tmp;
		//		}
		//	}
		//}
	}
	else{
		MasterListDimCount=1;
		MasterListDim[0].MasterCode=cmd->MasterCode;
		type = Review::FrontOnly;
	}
	int	Phase=0;// 初期フェイズは0

	QList<CmdReqMasterInfoFromDataBase> MInfoList;

	QList<QPair<int, int> > phasePageNumbList;
	int allCount=0;
	for(int i=0; i<MasterListDimCount; i++){
		CmdReqMasterInfoFromDataBase FromData(GetLayersBase());

		FromData.MasterCode = MasterListDim[i].MasterCode;
		TransmitDirectly( &FromData );

		phasePageNumbList << QPair<int, int>(FromData.info.PhaseNumb, FromData.info.PageNumb);
		allCount += FromData.info.PhaseNumb * FromData.info.PageNumb;

		MInfoList << FromData;
	}

	QProgressDialog progress(QString("Loading Master Data 1/%1\nphase : 0, page : 0").arg(MasterListDimCount), "", 0, allCount + MasterListDimCount, GetLayersBase()->GetMainWidget());
	progress.setWindowModality(Qt::WindowModal);
	progress.setCancelButton(NULL);
	progress.setValue(0);
	progress.show();
	qApp->processEvents(QEventLoop::ExcludeUserInputEvents);

	for(int i=0;i<MasterListDimCount;i++){
		// マスターデータロードコマンド
		CmdLoadMainMaster	CmdLoadInMain(GetLayersBase());
		Review::SideType side;
		if(MasterListDim[i].MasterCode==cmd->MasterCode){
			CmdLoadInMain.side = Review::Front;
		}else{
			CmdLoadInMain.side = Review::Back;
		}
		side = CmdLoadInMain.side;

		//// データベースからのマスターデータ情報の取得コマンド
		//CmdReqMasterInfoFromDataBase FromDatabaseCmd(GetLayersBase());
		//FromDatabaseCmd.MasterCode = MasterListDim[i].MasterCode;
		//RBase->TransmitDirectly(&FromDatabaseCmd);
		
		CmdLoadInMain.MasterCode	= MasterListDim[i].MasterCode;

		CmdReqMasterInfoFromDataBase FromData = MInfoList[i];

		// アウトラインの取得
		loadOutlineOffset(side, FromData.info.MachineID,CmdLoadInMain.MasterCode);
		
		QList<Review::MasterImageFileData> imgFileList;
		for(int phase=0; phase<FromData.info.PhaseNumb; phase++){
			// マスターデータの保存
			MasterDataInfo *info = getMasterInfoPtr(side);
			(*info) = FromData.info;

			//if(i==0){
			//	GetLayersBase()->ShowProcessingForm("Save master data",false, MasterListDimCount);
			//}

			//QString showProcessStr = QString("Loading Master Data %1/%2\nphase : 0, page : 0").arg(i+1).arg(MasterListDimCount);
			//GetLayersBase()->StepProcessing(showProcessStr);

			// 全ページの読み込み命令を作成する
			for(int page=0; page<FromData.info.PageNumb; page++){
				Review::MasterImageFileData data;
				data.phase = phase;
				data.page = page;
				data.MasterCode = FromData.info.MasterCode;
				data.MachineID = FromData.info.MachineID;

				QStringList pathList = GetLayersBase()->GetParamGlobal()->ImageFilePath.split(';');
				QString imgPath;
				for(int p=0; p<pathList.count(); p++){
					QString filePath = Review::makeMasterImageName(FromData.MasterCode, FromData.info.MachineID, phase, page, pathList[p]);
					if(GetParamGlobal()->ImageFileCachePort==0){
						if(QFile::exists(filePath)==true){
							data.fileName = filePath;
							break;
						}
					}
					else{
						TrFile	file(filePath,GetParamGlobal()->TransDatabaseIP
									 ,GetParamGlobal()->ImageFileCachePort);
						if(file.exists()==true){
							data.fileName = filePath;
							break;
						}
					}
				}
				imgFileList << data;

				progress.setLabelText(QString("Loading Master Data %1/%2\nphase : %3, page : %4").arg(i+1).arg(MasterListDimCount).arg(phase).arg(page));
				progress.setValue( progress.value()+1 );
				qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
			}
		}
		CmdLoadMasterImage loadMasterImageCmd(GetLayersBase());
		loadMasterImageCmd.side = side;
		loadMasterImageCmd.imgDataList = imgFileList;

		TransmitDirectly( &loadMasterImageCmd );
		progress.setLabelText(QString("Loading Master Data %1/%2\nLoaing Master Image...").arg(i+1).arg(MasterListDimCount));
		progress.setValue( progress.value()+1 );
		qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
			

		appendVRSAlignment(side, FromData.info.MachineID);
		getVRSAlignment(side).setPageCount(FromData.info.PageNumb);

		Phase+=CmdLoadInMain.PhaseCount;
		
	//	QList<QSize> *TargetWholeImgSize;
	//	QList<QList<QPoint> > *TargetMasterWholeImgDrawPoints;
	//	QList<QList<QPoint> > *TargetOutlines;

	//	TargetWholeImgSize = getMasterWholeImageSizePtr(side);
	//	TargetMasterWholeImgDrawPoints = getMasterWholeImgDrawPointsPtr(side);
	//	TargetOutlines = getMasterWholePageOutlineListPtr(side);

	//	// 全体画像サイズバッファの確保
	//	while(TargetWholeImgSize->count()<FromData.info.PhaseNumb){
	//		TargetWholeImgSize->append(QSize());
	//	}

	//	// アウトラインバッファの確保
	//	while(TargetOutlines->count()<FromData.info.PhaseNumb){
	//		TargetOutlines->append(QList<QPoint>());
	//	}

	//	for(int phase=0; phase<getMasterWholePageOutlineList(Review::Front).count(); phase++){
	//		while((*TargetOutlines)[phase].count()<FromData.info.PageNumb){
	//			(*TargetOutlines)[phase].append(QPoint());
	//		}
	//	}

	//	int backPhaseNumb = 0;
	//	if(getMasterInfo(Review::Back).isEmpty()==false){
	//		backPhaseNumb += getMasterInfo(Review::Back).PhaseNumb;
	//	}
	//	if(Review::isFront(side)==true){
	//		for(int phase=0; phase<GetLayersBase()->GetPhaseNumb()-backPhaseNumb; phase++){
	//			for(int page=0; page<GetLayersBase()->GetPageNumb(); page++){
	//				OutlineOffsetInBlob blob(GetLayersBase());

	//				GetLayersBase()->GetDatabaseLoader()->G_SQLLoadOutlineOfset(GetDatabase(), FromData.info.MachineID, &blob);

	//				(*TargetOutlines)[phase][page] = QPoint(blob.GetData(phase, page).Dx, blob.GetData(phase, page).Dy);

	//				//(*TargetOutlines)[phase][page] = QPoint( GetLayersBase()->GetPhaseData()[phase]->GetPageData(page)->GetOutlineOffset()->x
	//				//	,GetLayersBase()->GetPhaseData()[phase]->GetPageData(page)->GetOutlineOffset()->y);
	//			}
	//		}
	//	}else{
	//		for(int phase=backPhaseNumb; phase<GetLayersBase()->GetPhaseNumb(); phase++){
	//			for(int page=0; page<GetLayersBase()->GetPageNumb(); page++){
	//				OutlineOffsetInBlob blob(GetLayersBase());

	//				GetLayersBase()->GetDatabaseLoader()->G_SQLLoadOutlineOfset(GetDatabase(), FromData.info.MachineID, &blob);

	//				(*TargetOutlines)[phase-backPhaseNumb][page] = QPoint(blob.GetData(phase, page).Dx, blob.GetData(phase, page).Dy);

	//				//(*TargetOutlines)[phase-backPhaseNumb][page] = QPoint( GetLayersBase()->GetPhaseData()[phase]->GetPageData(page)->GetOutlineOffset()->x
	//				//	,GetLayersBase()->GetPhaseData()[phase]->GetPageData(page)->GetOutlineOffset()->y);
	//			}
	//		}
	//	}

	//	// 描画位置バッファの確保
	//	while(TargetMasterWholeImgDrawPoints->count()<FromData.info.PhaseNumb){
	//		TargetMasterWholeImgDrawPoints->append(QList<QPoint>());
	//	}

	//	for(int phase=0; phase<FromData.info.PhaseNumb; phase++){
	//		while((*TargetMasterWholeImgDrawPoints)[phase].count()<FromData.info.PageNumb){
	//			(*TargetMasterWholeImgDrawPoints)[phase].append(QPoint());
	//		}
	//	}
	//	
	//	if(TargetOutlines->count()>1){
	//		int minX,maxX;
	//		int minY,maxY;
	//		minX = maxX = TargetOutlines->first().x();
	//		minY = maxY = TargetOutlines->first().y();

	//		for(int i=1; i<TargetOutlineList->count(); i++){
	//			if(minX>TargetOutlineList->at(i).x()){
	//				minX = TargetOutlineList->at(i).x();
	//			}
	//			if(maxX<TargetOutlineList->at(i).x()){
	//				maxX = TargetOutlineList->at(i).x();
	//			}
	//			if(minY>TargetOutlineList->at(i).y()){
	//				minY = TargetOutlineList->at(i).y();
	//			}
	//			if(maxY<TargetOutlineList->at(i).y()){
	//				maxY = TargetOutlineList->at(i).y();
	//			}
	//		}

	//		QPoint p(-minX, -minY);

	//		int w = qAbs(maxX - minX) + GetLayersBase()->GetDotPerLine();
	//		int h = qAbs(maxY - minY) + GetLayersBase()->GetMaxLines();

	//		*TargetWholeSize = QSize(w, h);

	//		//QList<QPoint> shiftOutlineList;
	//		TargetWholeImgDrawPoints->clear();
	//		for(int i=0; i<TargetOutlineList->count(); i++){
	//			//shiftOutlineList.append(QPoint(OutlineList->at(i) + p));
	//			TargetWholeImgDrawPoints->append(QPoint(TargetOutlineList->at(i) + p));
	//		}

	//	}else if(TargetOutlineList->count()==1){
	//		//*TargetImage = BuffImgList.front();
	//		*TargetWholeSize = TargetPageList->first().size();
	//		TargetWholeImgDrawPoints->append(TargetOutlineList->first());
	//	}else{
	//		//*TargetImage = QImage();
	//		(*TargetPageList).append(QImage());
	//		*TargetWholeSize = QSize(0, 0);
	//		TargetWholeImgDrawPoints->append(QPoint(0,0));
	//	}
	}
	
	
	return true;
}

bool ReviewPIBase::ReciveCmdReqCurrentLotInfo(GUIDirectMessage *packet)
{
	CmdReqCurrentLotInfo *cmd = dynamic_cast<CmdReqCurrentLotInfo *>(packet);
	if(cmd==NULL)return false;

	cmd->_setLotInfo(Review::Front, getCurrentLotInfo(Review::Front));
	cmd->_setLotInfo(Review::Back, getCurrentLotInfo(Review::Back));

	return true;
}

// Common

//bool ReviewPIBase::ReciveCommonCmdMoveVRSWithAlignment(GUIDirectMessage *packet)
//{
//	ReviewCommonPacket::CmdMoveVRSWithAlignment *cmd = dynamic_cast<ReviewCommonPacket::CmdMoveVRSWithAlignment *>(packet);
//	if(cmd==NULL)return false;
//
//	static QList<VRSAlignment> alignList;
//
//	if(cmd->isEnable()==false){
//		return true;
//	}
//
//	int existNo = -1;
//	for(int i=0; i<alignList.count(); i++){
//		if(alignList[i].machineID()==cmd->machineID()){
//			existNo = i;
//			break;
//		}
//	}
//
//	SettingFileReader reader;
//	VRSAlignment alignItem;
//	alignItem.setMachineID(cmd->machineID());
//	reader.setFilename( alignItem.filename() );
//	if(reader.load()==true){
//		alignItem.fromBuffer( reader.sectionBuffer( alignItem.sectionName() ) );
//	}else{
//		//QMessageBox::warning(NULL, "Alignment is not managed.", "Please set alignment by ReviewGUI.");
//		//cmd->_setErrorMsg("Alignment is not setted.");
//		return true;
//	}
//
//	if(existNo==-1){
//		alignList << alignItem;
//		existNo = alignList.count()-1;
//	}else{
//		alignList[existNo] = alignItem;
//	}
//
//	//QString debugOutStr;
//
//	//debugOutStr += QString("MachineID:%1,Phase:%2,Page:%2").arg(cmd->machineID()).arg(cmd->phase()).arg(cmd->page());
//
//	QPoint outlineOffset;
//	if(cmd->isOutlineOffsetEnable()==true){
//		//debugOutStr += "OutlineOffset is in cmd.";
//		outlineOffset = cmd->outlineOffset();
//	}else{
//		CmdReqMasterInfoFromDataBase reqMFromDataBase(GetLayersBase());
//		OutlineOffsetInBlob blob(GetLayersBase());
//		GetLayersBase()->GetDatabaseLoader()->G_SQLLoadOutlineOfset(GetDatabase(), cmd->machineID(), &blob);
//		outlineOffset.rx() = blob.GetData(cmd->phase(), cmd->page()).Dx;
//		outlineOffset.ry() = blob.GetData(cmd->phase(), cmd->page()).Dy;
//
//		//outlineOffset.setX(GetLayersBase()->GetPhaseData()[cmd->phase()]->GetPageData()[cmd->page()]->GetOutlineOffset()->x);
//		//outlineOffset.setY(GetLayersBase()->GetPhaseData()[cmd->phase()]->GetPageData()[cmd->page()]->GetOutlineOffset()->y);
//	}
//
//	VRSSetting vrsSetting;
//	VRSSetting::VRSSideSetting setting;
//	{
//	SettingFileReader reader;
//	reader.setFilename(vrsSetting.filePath());
//	if(reader.load()==true){
//		vrsSetting.fromSectionBufferList( reader.sectionList() );
//		SectionBuffer buffer = reader.sectionBuffer(setting.sectionName());
//		if(buffer.isValid()==true){
//			setting.fromBuffer( buffer );
//		}else{
//			return true;
//		}
//	}else{
//		return true;
//	}
//	}
//	
//	//debugOutStr += QString("Outline:(%1,%2),").arg(outlineOffset.x()).arg(outlineOffset.y());
//	
//	int convertedX = cmd->x();
//	int convertedY = cmd->y();
//	QMatrix matrix;
//
//	if(alignItem.getAlignmentType()==Review::VRSAlignmentType::VRSAlingmentWholeImage){
//		if(alignItem.isWholeAffinMatrixEnable()==false){
//			return true;
//		}
//
//		matrix = alignItem.getWholeAffinMatrix();
//	}else{
//		if(alignItem.isEachPageAffinMatrixEnable(cmd->page())==false){
//			return true;
//		}
//
//		matrix = alignItem.getEachPageAffinMatrix(cmd->page());
//	}
//
//	int sx = cmd->x() + outlineOffset.x();
//	int sy = cmd->y() + outlineOffset.y();
//	
//	convertedX = sx * matrix.m11() + sy * matrix.m12() + matrix.dx() + setting.MotorOffset.x();// mx = ix * a + iy * b + c
//	convertedY = sx * matrix.m21() + sy * matrix.m22() + matrix.dy() + setting.MotorOffset.y();// my = ix * d + iy * e + f
//	
//	convertedX = qBound(0, convertedX, getSequenceThread()->pulsePerMM_x() * setting.MotorMovableAreaSize.width());
//	convertedY = qBound(0, convertedY, getSequenceThread()->pulsePerMM_y() * setting.MotorMovableAreaSize.height());
//	
//	sendVRSToMoveXY(convertedX, convertedY, false);
//
//	//debugOutStr += QString("sorceXY:(%1,%2),convertedXY:(%3,%4)\n").arg(cmd->x()).arg(cmd->y()).arg(convertedX).arg(convertedY);
//
//	//debugOutStr += QString("%1 %2\n").arg(matrix.m11()).arg(matrix.m12());
//	//debugOutStr += QString("%1 %2\n").arg(matrix.m21()).arg(matrix.m22());
//	//debugOutStr += QString("%1 %2\n").arg(matrix.dx()).arg(matrix.dy());
//
//
//	//if(getVRSSetting().getVRSSideSetting().ZInitialDistance != getSequenceThread()->z()){
//	//	sendVRSToMoveZ(getVRSSetting().getVRSSideSetting().ZInitialDistance);
//	//	debugOutStr += QString("MoveZ:%1").arg(getVRSSetting().getVRSSideSetting().ZInitialDistance);
//	//}
//
//	//QMessageBox::information(NULL, "VRSMove", debugOutStr);
//	
//	return true;
//}

bool ReviewPIBase::ReciveCmdMoveVRSDirectory(GUIDirectMessage *packet)
{
	CmdMoveVRSDirectory *cmd = dynamic_cast<CmdMoveVRSDirectory *>(packet);
	if(cmd==NULL)return false;

	static QList<VRSAlignment> alignList;

	if(cmd->isEnable()==false){
		return true;
	}

	int existNo = -1;
	for(int i=0; i<alignList.count(); i++){
		if(alignList[i].machineID()==cmd->machineID()){
			existNo = i;
			break;
		}
	}

	SettingFileReader reader;
	VRSAlignment alignItem;
	alignItem.setMachineID(cmd->machineID());
	reader.setFilename( alignItem.filename() );
	if(reader.load()==true){
		alignItem.fromBuffer( reader.sectionBuffer( alignItem.sectionName() ) );
	}else{
		//QMessageBox::warning(NULL, "Alignment is not managed.", "Please set alignment by ReviewGUI.");
		cmd->_setErrorMsg("Alignment is not setted.");
		return true;
	}

	if(existNo==-1){
		alignList << alignItem;
		existNo = alignList.count()-1;
	}else{
		alignList[existNo] = alignItem;
	}

	QPoint outlineOffset;
	if(cmd->isOutlineOffsetEnable()==true){
		outlineOffset = cmd->outlineOffset();
	}else{
		OutlineOffsetInBlob blob(GetLayersBase());

		GetLayersBase()->GetDatabaseLoader()->G_SQLLoadOutlineOfset(GetDatabase(), cmd->machineID(), &blob);

		outlineOffset = QPoint(blob.GetData(cmd->phase(), cmd->page()).Dx, blob.GetData(cmd->phase(), cmd->page()).Dy);

		//outlineOffset.setX(GetLayersBase()->GetPhaseData()[cmd->phase()]->GetPageData()[cmd->page()]->GetOutlineOffset()->x);
		//outlineOffset.setY(GetLayersBase()->GetPhaseData()[cmd->phase()]->GetPageData()[cmd->page()]->GetOutlineOffset()->y);
	}
	
	//int fixX = qBound(0, cmd->x() + outlineOffset.x(), getSequenceThread()->pulsePerMM_x()*getVRSSetting().getVRSSideSetting().MotorMovableAreaSize.width());
	//int fixY = qBound(0, cmd->y() + outlineOffset.y(), getSequenceThread()->pulsePerMM_y()*getVRSSetting().getVRSSideSetting().MotorMovableAreaSize.height());
	int fixX = cmd->x() + outlineOffset.x();
	int fixY = cmd->y() + outlineOffset.y();

	sendVRSToMoveXY(fixX, fixY);

	return true;
}

//bool ReviewPIBase::ReciveCommonCmdMoveVRSToOrigin(GUIDirectMessage *packet)
//{
//	ReviewCommonPacket::CmdMoveVRSToOrigin *cmd = dynamic_cast<ReviewCommonPacket::CmdMoveVRSToOrigin *>(packet);
//
//	const QPoint origin = getVRSSetting().getVRSSideSetting().MotorOrigin;
//
//	sendVRSToMoveXY(origin.x(), origin.y(), false);
//
//	return true;
//}
