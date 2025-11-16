#include "ShowThumbnailResource.h"
#include "ShowThumbnail.h"
#include "ReviewStructureItems.h"
#include "ReviewStructurePacket.h"
#include "../WholeImageForReview/WholeImageForReviewPacket.h"
#include "../XGUIReviewCommonPacket.h"
#include "XReviewCommonPacket.h"
#include "../XGUIReviewGlobal.h"
#include "../ShowHistoryListForReview/ShowHistoryListForReviewPacket.h"
#include "../WholeImageForReview/WholeImageForReviewPacket.h"
#include "SettingDialog.h"
#include "ShowThumbnailProperty.h"
#include "ChooseNextDialog.h"

extern	char	*sRoot;
extern	char	*sName;


void ShowThumbnail::keyPressEvent(QKeyEvent *event)
{
	if(GetEditMode()==true){
		return;
	}

	static QTime time;
	static QTime timeForCheckPageAll;
	if(time.isNull()==true){
		time = QTime::currentTime();
		timeForCheckPageAll = QTime::currentTime();
		time.start();
		timeForCheckPageAll.start();
	}

	if(event->key()==Qt::Key_H){
		if(controlInfoDialog()!=NULL){
			controlInfoDialog()->setVisible(true);
		}
		return;
	}

	if(getCurrentThumbnail()==NULL || getCurrentRow()==-1 || getCurrentColumn()==-1){// 非選択状態の場合
		if(isKeyPressed()==true)return;

		// 現在の状態を取得
		CmdReqAdjacentCurrentNG AdjNGCmd(GetLayersBase());
		ReviewPIBase *RBase = GetReviewAlgorithm();

		if(RBase!=NULL){
			RBase->TransmitDirectly(&AdjNGCmd);
		}

		if(AdjNGCmd.existCurrentHistory()==false){// 履歴が読み込まれていないのならば
			return;// 中断
		}

		setKeyPressedState(true);
		return;
	}
	
	if(event->key()==Qt::Key_PageUp || event->key()==Qt::Key_PageDown){
		if(isKeyPressed()==true)return;

		if(event->key()==Qt::Key_PageUp){
			if(getMoveMode()==_moveMode::PerPage){
				moveHistory(Review::Direction::Previous, Review::ListLocate::First);
			}else{
				if(getCurrentPage()!=0){// まだ前ページがあるとき
					showPage(getCurrentSide(), getCurrentPage()-1, Review::ListLocate::First);
				}else if(getCurrentSide()==Review::Back && getThumbnailCount(Review::Front)!=0){
					setUpdatesEnabled(false);// 裏の場合で表があるとき
					showPage(Review::Front, getPageCount(Review::Front)-1, Review::ListLocate::First);// 表の最後のページの最初のサムネイル
					//getThumbnailCount(Review::Front) - getThumbnailCount(Review::Front)%getThumbnailCountInPage()
					setUpdatesEnabled(true);
				}else{// 裏の場合で表がない時、もしくは表の最初のページの時
					setUpdatesEnabled(false);
					moveHistory(Review::Direction::Previous, Review::ListLocate::End, NULL);// 前の履歴の最後に移動
					showPage(getCurrentSide(), getCurrentPage(), Review::ListLocate::First);
					setUpdatesEnabled(true);
				}
			}
		}else{
			if(getMoveMode()==_moveMode::PerPage){
				moveHistory(Review::Direction::Next, Review::ListLocate::First);
			}else{
				if(getCurrentPage()!=getCurrentPageLastIndex()){
					showPage(getCurrentSide(), getCurrentPage()+1, Review::ListLocate::First);
				}else{
					setUpdatesEnabled(false);
					if(getCurrentSide()==Review::Front && getThumbnailList(Review::Back).count()!=0){
						showPage(Review::Back, Review::First);// 裏の最初に移動する
					}else{
						moveHistory(Review::Direction::Next, Review::ListLocate::First);
					}
					setUpdatesEnabled(true);
				}
			}
		}
		
		setKeyPressedState(true);
		return;
	}

	if(event->key()==Qt::Key_Control || event->key()==Qt::Key_Asterisk){
		if(isKeyPressed()==true)return;

		inputKeyMoveModeChange();
		if(getExpandThumbnail()!=NULL){
			GUIFormBase *FBase = GetLayersBase()->FindByName(ReviewGUI::Name::Root, ReviewGUI::Name::WholeImageForReview, /**/"");
			if(FBase!=NULL){
				GUICmdSetCurrentNGView Send(GetLayersBase());
				if(getMoveMode()==_moveMode::PerPage){
					//getExpandThumbnail()->setVisible(false);
					setExpandThumbnailVisible(false);
					Send.visible = false;
				}else{
					//getExpandThumbnail()->setVisible(getExpandThumbnailVisible());
					setExpandThumbnailVisible(getExpandThumbnailVisible());
					Send.visible = true;
				}
				FBase->TransmitDirectly(&Send);
				GUICmdUpdateWholeImage Send2(GetLayersBase());
				FBase->TransmitDirectly(&Send2);
			}
		}
		setKeyPressedState(true);
		//updateHelpLabel();
		return;
	}

	// 入力キーが矢印キーの場合
	if(Review::isArrowKey(event->key())==true || event->key()==Qt::Key_2 || event->key()==Qt::Key_4 || event->key()==Qt::Key_6 || event->key()==Qt::Key_8){
		if(isKeyPressed()==true)return;

		//if(existCurrentThumbnail()==false){// カレントNGが無い場合は何もしない
		//	return;
		//}
		//qDebug() << "Current Side : " << (getCurrentSide()==Review::Front ? "Front" : "Back");
		//qDebug() << "Current Page/Max : " << getCurrentPage() << " / " << getCurrentPageCount();
		//qDebug() << "Current Row,Column : " << getCurrentRow() << "," << getCurrentColumn();

		// カーソルキーによる分岐

		//CmdReqInsLib ReqInsLibCmd(GetLayersBase());
		//ReviewPIBase *RBase = GetReviewAlgorithm();
		//if(RBase!=NULL){
		//	RBase->TransmitDirectly(&ReqInsLibCmd);
		//	if(ReqInsLibCmd.Ret==true){
		//		InsLibraryHashPtr InsLibHashPtr;
		//		if(getCurrentSide()==Review::Front){
		//			InsLibHashPtr = ReqInsLibCmd.FrontInsLibHashPtr;
		//		}else{
		//			InsLibHashPtr = ReqInsLibCmd.BackInsLibHashPtr;
		//		}

		//		if(InsLibHashPtr!=NULL){
		//			if(getCurrentThumbnail()!=NULL){
		//				for(int i=0; i<getCurrentThumbnail()->getNGNailItem().NGPointList.count(); i++){
		//					if(InsLibHashPtr->contains(getCurrentThumbnail()->getNGNailItem().NGPointList[i].Ral)==true){

		//						if(InsLibHashPtr->values(getCurrentThumbnail()->getNGNailItem().NGPointList[i].Ral)
		//					}
		//				}
		//			}

		//			if(getCurrentSide()==Review::Front){
		//			
		//			}
		//		}

		//	}
		//}


		switch(event->key()){
		case Qt::Key_Up:// ↑キー [戻り]
		case Qt::Key_8:
			if(getMoveMode()==_moveMode::PerThumbnail){
				if(time.elapsed()<getMoveDelay()){
					if(getCurrentThumbnail()!=NULL){
						Thumbnail *nextThumbnail = getThumbnail(getCurrentThumbnail()->getIndexInGlobal()-getColumnCount());
						if(nextThumbnail!=NULL && nextThumbnail->isChecked()==true){
							inputKeyUpArrow();
							time = QTime::currentTime();
							time.start();
							return;
						}
					}else{
						inputKeyUpArrow();
					}
				}else{
					inputKeyUpArrow();
					time = QTime::currentTime();
					time.start();
				}
			}else{
				inputKeyUpArrow();
				time = QTime::currentTime();
				time.start();
			}
			break;
		case Qt::Key_Down:// ↓キー [進み]
		case Qt::Key_2:
			if(getMoveMode()==_moveMode::PerThumbnail){
				if(time.elapsed()<getMoveDelay()){
					if(getCurrentThumbnail()!=NULL){
						Thumbnail *nextThumbnail = getThumbnail(getCurrentThumbnail()->getIndexInGlobal()+getColumnCount());
						if(nextThumbnail!=NULL && nextThumbnail->isChecked()==true){
							inputKeyDownArrow(false);
							time = QTime::currentTime();
							time.start();
							return;
						}
					}
				}else{
					inputKeyDownArrow(false);
				}
			}else{
				inputKeyDownArrow(false);
				time = QTime::currentTime();
				time.start();
			}
			break;
		case Qt::Key_Right:// →キー [進み]
		case Qt::Key_6:
			if(getMoveMode()==_moveMode::PerThumbnail){
				if(time.elapsed()<getMoveDelay()){
					if(getCurrentThumbnail()!=NULL){
						Thumbnail *nextThumbnail = getThumbnail(getCurrentThumbnail()->getIndexInGlobal()+1);
						if(nextThumbnail!=NULL && nextThumbnail->isChecked()==true){
							inputKeyRightArrow(false);
							time = QTime::currentTime();
							time.start();
							return;
						}
					}else{
						inputKeyRightArrow(false);
					}
				}else{
					inputKeyRightArrow(false);
					time = QTime::currentTime();
					time.start();
				}
			}else{
				inputKeyRightArrow(false);
			}
			break;
		case Qt::Key_Left:// ←キー [戻り]
		case Qt::Key_4:
			if(getMoveMode()==_moveMode::PerThumbnail){
				if(time.elapsed()<getMoveDelay()){
					if(getCurrentThumbnail()!=NULL){
						Thumbnail *nextThumbnail = getThumbnail(getCurrentThumbnail()->getIndexInGlobal()-1);
						if(nextThumbnail!=NULL && nextThumbnail->isChecked()==true){
							inputKeyLeftArrow();
							time = QTime::currentTime();
							time.start();
							return;
						}
					}else{
						inputKeyLeftArrow();
					}
				}else{
					inputKeyLeftArrow();
					time = QTime::currentTime();
					time.start();
				}
			}else{
				inputKeyLeftArrow();
			}
			break;
		default:
			break;
		}
		setKeyPressedState(true);
		return;
	}

	// Fキー挿入イベント
	if(Review::isFKey((Qt::Key)event->key())==true){
		if(isKeyPressed()==true)return;

		if(getMoveMode()==_moveMode::PerThumbnail){
			// eventの入力FキーでカレントNGのXML分に対応するFキー要素を付与、もしくは上書きする
			QColor FKeyColor = setFKey(Review::convertFKeyQtToReview((Qt::Key)event->key()));
			//SetFKeyIndex(getCurrentThumbnail()->getIndexInGlobal() ,Review::convertFKeyQtToReview((Qt::Key)event->key()));
			getCurrentThumbnail()->setFKey(Review::convertFKeyQtToReview((Qt::Key)event->key()));
			getCurrentThumbnail()->setFKeyColor(FKeyColor);// 対応する色で背景色を塗りつぶし
			
			inputKeyRightArrow(true);// 次のNGNailへ
			
			GUIFormBase *GBase = GetReviewGUIForm(ReviewGUI::Name::ShowHistoryListForReview);
			if(GBase!=NULL){
				GUICmdUpdateCurrentHistoryChecked Send(GetLayersBase());
				GBase->TransmitDirectly(&Send);
			}
			ReviewGUI::UpdateGUI(GetLayersBase(), ReviewGUI::Name::ListStatisticNG);
		}
		setKeyPressedState(true);
		return;
	}

	// Fキー削除イベント
	if(event->key()==Qt::Key_Delete){
		if(isKeyPressed()==true)return;

		QColor afterColor;// 削除後の色
		if(removeFKey(afterColor)==true){// Fキー要素の削除をトライ
			if(getCurrentThumbnail()!=NULL){
				getCurrentThumbnail()->setFKeyColor(afterColor);
			}
			ReviewGUI::UpdateGUI(GetLayersBase(), ReviewGUI::Name::ListStatisticNG);
		}else if(getMoveMode()==_moveMode::PerThumbnail){
			// 失敗時はメッセージを出力してなにもしない
			QMessageBox::warning(this
								, LangSolver.GetString(ShowThumbnail_LS,LID_11)/*"Remove FKey attribute error"*/
								, LangSolver.GetString(ShowThumbnail_LS,LID_12)/*"FKey attribute whold be not removed in XML file."*/);
		}
		setKeyPressedState(true);
		return;
	}

	// エンターキー、リターンキーイベント
	if(event->key()==Qt::Key_Return || event->key()==Qt::Key_Enter){
		if(event->modifiers()==Qt::NoModifier){
			// 別窓でカレントThumbnailを表示
			if(getMoveMode()==_moveMode::PerThumbnail){
				if(isKeyPressed()==true)return;// 押し続け対応
				if(getCurrentThumbnail()==NULL)return;// 現在サムネイルなし
				if(isEnableExpandThumbnal()==false)return;// 拡大サムネイル無効モード
				if(getExpandThumbnail()!=NULL){
					if(getMoveMode()==_moveMode::PerThumbnail){
						expandDialog()->setVisible( !getExpandThumbnailVisible() );
						setKeyPressedState(true);
						return;
					}else{
						expandDialog()->setVisible(false);
					}
				}
			}else{
				// ページモードの場合、一定間隔が空いているならばページのすべてをチェック済みにできる
				ThumbnailPage *currentThumbnailPage = dynamic_cast<ThumbnailPage *>(thumbnailBook()->widget(thumbnailBook()->currentIndex()));

				int nowElapsed = timeForCheckPageAll.elapsed();

				int haveToElapsed = getPageDelay(currentThumbnailPage);
			
				if(currentThumbnailPage!=NULL && pageWaitProgressBar()->value()==pageWaitProgressBar()->maximum()/*nowElapsed>haveToElapsed*/){
					ReviewPIBase *RBase = GetReviewAlgorithm();
					if(RBase!=NULL){
						CmdSetNGChecked Send(GetLayersBase());
						Send.side = getCurrentSide();
						Send.begin = getCurrentPage()*getThumbnailCountInPage();
						Send.length = getThumbnailCountInPage();
						RBase->TransmitDirectly(&Send);

						for(QList<Thumbnail*>::Iterator thumb=getCurrentThumbnailPageList()[getCurrentPage()].begin(); thumb!=getCurrentThumbnailPageList()[getCurrentPage()].end(); thumb++){
							(*thumb)->setChecked(true);
							(*thumb)->updateImage();
						}

						GUIFormBase *FBase = GetReviewGUIForm(ReviewGUI::Name::ShowHistoryListForReview);
					
						if(FBase!=NULL){
							GUICmdUpdateCurrentHistoryChecked Send2(GetLayersBase());
							FBase->TransmitDirectly(&Send2);
						}

						//update();
						timeForCheckPageAll = QTime::currentTime();
						timeForCheckPageAll.restart();
					}

					setKeyPressedState(true);
					update();
				}
			}
			return;
		}else if((event->modifiers() & Qt::ShiftModifier)!=0){
			ReviewPIBase *RBase = GetReviewAlgorithm();
			if(RBase==NULL){
				return;
			}

			CmdMoveVRSToCurrentNG moveVRSToCurrent(GetLayersBase());
			moveVRSToCurrent.checkVRSEnable = false;
			RBase->TransmitDirectly( &moveVRSToCurrent );

			return;
		}
	}

	if(event->key()==Qt::Key_Insert){
		if((event->modifiers() & Qt::AltModifier)!=0){
			ReviewPIBase *RBase = GetReviewAlgorithm();
			CmdSaveCurrentHistoryNGImages saveCurHistoryNGImg(GetLayersBase());
			RBase->TransmitDirectly(&saveCurHistoryNGImg);
			if(saveCurHistoryNGImg.Ret==true){
				QMessageBox::information(this
										, LangSolver.GetString(ShowThumbnail_LS,LID_13)/*"Operator to save NG Image"*/
										, LangSolver.GetString(ShowThumbnail_LS,LID_14)/*"NG Images in current Inspection are saved."*/);
			}
		}else{
			if(getMoveMode()==_moveMode::PerThumbnail){
				ReviewPIBase *RBase = GetReviewAlgorithm();
				CmdSaveCurrentNGImage saveNGImg(GetLayersBase());
				RBase->TransmitDirectly(&saveNGImg);
			}
		}
		return;
	}

	if(event->key()==Qt::Key_Space){
		for(int i=0; i<getThumbnailList(Review::Front).count(); i++){
			getThumbnailList(Review::Front)[i]->setDrawNGSingEnable( !getThumbnailList(Review::Front)[i]->isDrawNGSingEnable() );
		}
		for(int i=0; i<getThumbnailList(Review::Back).count(); i++){
			getThumbnailList(Review::Back)[i]->setDrawNGSingEnable( !getThumbnailList(Review::Back)[i]->isDrawNGSingEnable() );
		}
		return;
	}
	if(event->key()==Qt::Key_F){
		showPage(Review::Front, Review::First);
	}
	else if(event->key()==Qt::Key_B){
		showPage(Review::Back, Review::First);
	}
}

void ShowThumbnail::keyReleaseEvent(QKeyEvent *event)
{
	if(event->isAutoRepeat()==false){
		setKeyPressedState(false);
	}
}

void ShowThumbnail::inputKeyMoveModeChange()
{
	if(getMoveMode()==_moveMode::PerThumbnail){
		setMoveMode(_moveMode::PerPage);
		if(getCurrentThumbnail()!=NULL){
			getCurrentThumbnail()->setSelected(false);
		}
	}else{
		setMoveMode(_moveMode::PerThumbnail);
		if(getCurrentThumbnail()!=NULL){
			getCurrentThumbnail()->setSelected(true);
			if(getCurrentThumbnail()->isChecked()==false){
				ReviewPIBase *RBase = GetReviewAlgorithm();
				if(RBase==NULL){
					updateInfoLabel();
					return;
				}
				CmdSetNGChecked NGCheckCmd(GetLayersBase());
				NGCheckCmd.side = getCurrentSide();
				NGCheckCmd.begin = getCurrentThumbnail()->getIndexInLocal();// 現在NGNail
				NGCheckCmd.length = 1;// そのNGのみ
				RBase->TransmitDirectly(&NGCheckCmd);
				getCurrentThumbnail()->setChecked(true);
				
				GUICmdUpdateCurrentHistoryChecked HistoryCheckCmd(GetLayersBase());
				ReviewGUI::ReviewGUICmdSend(GetLayersBase(), &HistoryCheckCmd, ReviewGUI::Name::ShowHistoryListForReview);
			}
		}
	}
	updateInfoLabel();
}


// NGを戻る
// 基本は現在ロウを１つ引く
// ただし、現在ロウが0の場合はそのページのNGをすべてチェックしている場合のみページを１つ戻す
// ただし、現在ページが表のある裏の0の時は表の最後のNGにカレントNGを移す
// でなければ、履歴を１つ戻し最後のNGへカレントNGを移動する
// 以前の履歴が無ければ何もしない
void ShowThumbnail::inputKeyUpArrow()
{
	// サムネイル単位移動
	if(getMoveMode()==_moveMode::PerThumbnail){
		if(getCurrentRow()!=0){//カレントNGがページの一番上ではない場合
			showPage(Review::Manual, getCurrentThumbnail()->getIndexInGlobal() - getColumnCount());// １つ行を上げる
			//setCurrentNG(getCurrentSide(), getCurrentPage(), getCurrentRow()-1, getCurrentColumn());
		}else{// カレントNGのロウがページの一番上の場合
			if(getCurrentPage()==0){
				//if(isMoveHistoryEnable()==false){
				//	bool expandVisible = getExpandThumbnailVisible();
				//	QMessageBox::warning(this, "History can't be changed.", "You would be changed on all Thumbnail Item was checked in current History.");
				//	setExpandThumbnailVisible(expandVisible);
				//	return;
				//}

				if(getCurrentSide()==Review::Front){// 表側の場合、履歴を１つ戻り、カレントNGを最後に移す

					return;// 無効 20120528

					// 全チェックしていないとき何もしない
					if(isMoveHistoryEnable()==false){
						return;
					}

					//ReviewPIBase *RBase = GetReviewAlgorithm();
					//if(RBase==NULL)return;

					//CmdReqCurrentHistory ReqCurrHisCmd(GetLayersBase());
					//RBase->TransmitDirectly(&ReqCurrHisCmd);

					//if(ReqCurrHisCmd.Ret==false || ReqCurrHisCmd.OrgHistoryPtr==NULL){
					//	return;
					//}
					
					bool ok;
					if(moveHistory(Review::Direction::Previous, Review::ListLocate::End, &ok)==true){
						// 正常終了
						return;
					}
					if(ok==true){// 次の履歴があるのに移動失敗
						// エラー
						ReviewGUI::ReviewGUIAllUpdate(GetLayersBase());
					}else{
						// 通常終了
						return;
					}
				}else{// 後ろ側の場合
					if(getThumbnailList(Review::Front).count()!=0){// 表側履歴がある場合
						showPage(Review::Front, Review::End);// 表側の最後のページの最後の要素を選択する
					}else{// 表側履歴がない場合、履歴を１つ戻す
						return;// 戻さない
						// 全チェックしていないとき何もしない
						if(isMoveHistoryEnable()==false){
							return;
						}

						bool ok;
						if(moveHistory(Review::Direction::Previous, Review::ListLocate::End, &ok)==true){
							// 正常終了
							return;
						}
						if(ok==true){// 次の履歴があるのに移動失敗
						// エラー
							ReviewGUI::ReviewGUIAllUpdate(GetLayersBase());
						}else{
							// 通常終了
							return;
						}
					}
				}
			}else{
				showPage(Review::Manual, getCurrentThumbnail()->getIndexInGlobal() - getColumnCount());
			}
		}
	}else{// ページ単位移動
		if(getCurrentPage()>0){
			showPage(getCurrentSide(), getCurrentPage()-1, Review::First);
		}else if(getCurrentPage()==0){
			if(getCurrentSide()==Review::Front){// 表側の場合、履歴を１つ戻る

				// 全チェックしていないとき何もしない
				if(isMoveHistoryEnable()==false){
					return;
				}

				bool ok;
				if(moveHistory(Review::Direction::Previous, Review::ListLocate::End, &ok)==true){
					// 正常終了
					return;
				}
				if(ok==true){// 次の履歴があるのに移動失敗
					// エラー
					ReviewGUI::ReviewGUIAllUpdate(GetLayersBase());
				}else{
					// 通常終了
					return;
				}
			}else{// 後ろ側の場合
				if(getThumbnailList(Review::Front).count()!=0){// 表側履歴がある場合
					showPage(Review::Front, Review::End);// 表側の最後のページの最後の要素を選択する
				}else{// 表側履歴がない場合、履歴を１つ戻す
					
					// 全チェックしていないとき何もしない
					if(isMoveHistoryEnable()==false){
						return;
					}

					bool ok;
					if(moveHistory(Review::Direction::Previous, Review::ListLocate::End, &ok)==true){
						// 正常終了
						return;
					}
					if(ok==true){// 次の履歴があるのに移動失敗
					// エラー
						ReviewGUI::ReviewGUIAllUpdate(GetLayersBase());
					}else{
						// 通常終了
						return;
					}
				}
			}
		}
	}
}

// NGを進める
// 基本は現在ロウを１つ足す
// ただし、現在ロウがページの最後の場合はページを１つ進める
// ただし、現在ページが裏のある表の0の時は裏の最初のNGにカレントNGを移す
// でなければ、履歴を１つ進めて最初のNGへカレントNGを移動する
// 次の履歴が無ければ何もしない
void ShowThumbnail::inputKeyDownArrow(bool Skip)
{
	// サムネイル単位移動
	if(getMoveMode()==_moveMode::PerThumbnail){
		if((getCurrentThumbnailList().count() - getCurrentThumbnail()->getIndexInLocal()) <= getColumnCount()){// 現在サムネイル表示の下部に該当するサムネイルがない最後から一列分の場合
			if(isCurrentPageAllChecked()==true){
				if(getCurrentSide()==Review::Front && getThumbnailList(Review::Back).count()!=0){// 表の場合で、裏がある場合
					showPage(Review::Back, Review::First);// 裏の最初に移動する
				}else{// 次の履歴に移動する
					ChooseNextDialog	D;
					if(D.exec()==(int)true){
						if(isMoveHistoryEnable()==true){// 現在の全てのアイテムがチェック済みでのみ移動可能 //
							bool ok;
							if(moveHistory(Review::Direction::Next, Review::ListLocate::First, &ok)==true){
								// 正常終了
								return;
							}
							if(ok==true){// １つ前の履歴があるのに移動失敗
					// エラー
								ReviewGUI::ReviewGUIAllUpdate(GetLayersBase());
							}else{
								// 通常終了
								return;
							}
						}
					}
					return; // 無効
				}
			}
		}else if(getCurrentRow()!=getRowCount()-1){// 同じページ内で下へ移動できる場合
			showPage(getCurrentSide(), getCurrentPage(), Review::Manual, getCurrentThumbnail()->getRow()+1, getCurrentThumbnail()->getColumn());
		}else{// ページを１つ上げ、最初の行へ移動する
			if(isCurrentPageAllChecked()==true){// そのページが全チェック済みである場合のみ次のページへ移動できる
				showPage(getCurrentSide(), getCurrentPage()+1, Review::Manual, 0, getCurrentThumbnail()->getColumn());
			}else{
				// 
			}
		}
	}else{// ページ単位移動
		if(isCurrentPageAllChecked()==true){// すべてチェック済みの場合のみ次ページへ移動可能 //
			if(getCurrentPage()!=getCurrentPageLastIndex()){
					showPage(getCurrentSide(), getCurrentPage()+1, Review::First);
				if(getCurrentThumbnail()!=NULL){
 					CmdSetNGChecked NGCheckCmd(GetLayersBase());
					NGCheckCmd.side = getCurrentSide();
					NGCheckCmd.begin = getGlobalIndex(getCurrentPage(), getCurrentRow(), getCurrentColumn(), getCurrentSide());
					NGCheckCmd.length = getRowCount() * getColumnCount();	//1;// そのNGのみ
					ReviewPIBase *RBase = GetReviewAlgorithm();
					if(RBase!=NULL){
						RBase->TransmitDirectly(&NGCheckCmd);
					}
					for(int row=0;row<getRowCount();row++){
						for(int column=0;column<getColumnCount();column++){
							int	n=getLocalIndex(getCurrentPage(), row, column, getCurrentSide());
							if(0<=n && n<getThumbnailList(getCurrentSide()).count()){
								getThumbnailList(getCurrentSide())[n]->setChecked(true);
							}
						}
					}
				}
			}else if(getCurrentPage()==getCurrentPageLastIndex()){
				if(getCurrentSide()==Review::Front && getThumbnailList(Review::Back).count()!=0){// 表の場合で、裏がある場合
					showPage(Review::Back, Review::First);// 裏の最初に移動する
					getCurrentThumbnail()->setChecked(true);
					//for(int row=0;row<getRowCount();row++){
					//	for(int column=0;column<getColumnCount();column++){
					//		int	n=getLocalIndex(getCurrentPage(), row, column, getCurrentSide());
					//		if(0<=n && n<getThumbnailList(getCurrentSide()).count()){
					//			getThumbnailList(getCurrentSide())[n]->setChecked(true);
					//		}
					//	}
					//}
				}
				else if(getCurrentSide()==Review::Front && getThumbnail(Review::Back, getCurrentPage()+1-getThumbnailPageList(Review::Front).count(),0,0)!=NULL
					&& getThumbnail(Review::Back, getCurrentPage()+1-getThumbnailPageList(Review::Front).count(),0,0)->getNGNailItem().phase==1){// Phase=1の裏がある場合
					showPage(Review::Back, Review::First);// 裏の最初に移動する
					getCurrentThumbnail()->setChecked(true);
					//for(int row=0;row<getRowCount();row++){
					//	for(int column=0;column<getColumnCount();column++){
					//		int	n=getLocalIndex(getCurrentPage(), row, column, getCurrentSide());
					//		if(0<=n && n<getThumbnailList(getCurrentSide()).count()){
					//			getThumbnailList(getCurrentSide())[n]->setChecked(true);
					//		}
					//	}
					//}
				}else{// 次の履歴に移動する
					ChooseNextDialog	D;
					if(D.exec()==(int)true){
						// 次の履歴に移動する
						if(isMoveHistoryEnable()==true){// 現在の全てのアイテムがチェック済みでのみ移動可能 //
							bool ok;
							if(moveHistory(Review::Direction::Next, Review::ListLocate::First, &ok)==true){
								// 正常終了
								return;
							}
							if(ok==true){// １つ前の履歴があるのに移動失敗
								// エラー
								ReviewGUI::ReviewGUIAllUpdate(GetLayersBase());
							}else{
								// 通常終了
								return;
							}
						}
					}
					return;// しない
				}
			}
		}
	}
}

// NGを進める
// 基本はカレントNGを１つ進める
// ただし、カレントNGがカレント履歴の最後の場合は次の履歴へ移動する
// 次の履歴が無ければ何もしない
void ShowThumbnail::inputKeyRightArrow(bool Skip)
{
	if(getMoveMode()==_moveMode::PerThumbnail){
		QString	AreaName;
		GetAreaNameAndChecked(getCurrentThumbnail()->getIndexInGlobal() ,AreaName);
		int	CurrentGlobalIndex=getCurrentThumbnail()->getIndexInGlobal();
NextMore:;
		if(CurrentGlobalIndex==getCurrentThumbnailLastGlobalIndex()){// 現在の履歴における最後のサムネイルの場合、次の履歴へ移動を試みる
			
			return;// 無効 20120523
				
			// 現在のページが全てチェック済みか調査
			if(isMoveHistoryEnable()==true){
				bool ok;
				// 次の履歴へ移動
				if(moveHistory(Review::Direction::Next, Review::ListLocate::First, &ok)==true){
					// 正常終了
					return;
				}
				if(ok==true){
					// エラー
					ReviewGUI::ReviewGUIAllUpdate(GetLayersBase());
				}else{
					// 次の履歴無し(正常終了)
					// なにもしない
					return;
				}
			}
		}else{
			// 次のページへ移動するときに、現在のページの全てにチェックが入っていなければ移動禁止
			if(SkipSamePiece==false){
				if(getCurrentRow()==getRowCount()-1 && getCurrentColumn()==getColumnCount()-1 && isCurrentPageAllChecked()==false){
					return;
				}
			}

			CurrentGlobalIndex++;
			if(SkipSamePiece==true && Skip==true){
				QString	tAreaName;
				GetAreaNameAndChecked(CurrentGlobalIndex,tAreaName);
				if(tAreaName.isEmpty()==false && tAreaName==AreaName){
					goto	NextMore;
				}
			}
			else if(SkipSamePiece==true && Skip==false){
				int	Row=CurrentGlobalIndex;
				QString	tAreaName;
				GetAreaNameAndChecked(Row,tAreaName);
				if(tAreaName.isEmpty()==false && tAreaName!=AreaName){
					for(int k=0;k<Row-1;k++){
						QString	mAreaName;
						if(GetAreaNameAndChecked(k,mAreaName)==true && tAreaName==mAreaName){
							goto	NextMore;
						}
					}
				}
			}
			// 次のサムネイルを選択する
			showPage(Review::Manual, CurrentGlobalIndex);
		}
	}else{// ページ単位移動

		// 無条件移動 20120528
		//// 全チェックしていないとき何もしない
		//if(isMoveHistoryEnable()==false){
		//	return;
		//}
		bool ok;
		if(moveHistory(Review::Direction::Next, Review::ListLocate::First, &ok)==true){
			// 正常終了
			return;
		}
		if(ok==true){// １つ前の履歴があるのに移動失敗
			// エラー
			ReviewGUI::ReviewGUIAllUpdate(GetLayersBase());
		}else{
			// 通常終了
			return;
		}
	}
}

// NGを戻す
// 基本はカレントNGを１つ戻す
// ただし、カレントNGがカレント履歴の最初の場合は１つ後ろの履歴へ移動する
// 後ろの履歴が無ければ何もしない
void ShowThumbnail::inputKeyLeftArrow()
{
	if(getMoveMode()==_moveMode::PerThumbnail){
		if(getCurrentThumbnail()->getIndexInGlobal()==0){// 履歴の最初の場合

			return;// 無効 20120523

			// 全チェックしていないとき何もしない
			if(isMoveHistoryEnable()==false){
				return;
			}
			// 前の履歴へ移動
			bool ok;
			if(moveHistory(Review::Direction::Previous, Review::ListLocate::End, &ok)==true){
				// 正常終了
				return;
			}
			if(ok==true){
				// エラー
				ReviewGUI::ReviewGUIAllUpdate(GetLayersBase());
			}else{
				// 次の履歴無し(正常終了)
				// なにもしない
				return;
			}
		}else{
			showPage(Review::Manual, getCurrentThumbnail()->getIndexInGlobal()-1);
		}
	}else{// ページ単位移動
		
		// 無条件移動 20120528
		//// 全チェックしていないとき何もしない
		//if(isMoveHistoryEnable()==false){
		//	return;
		//}

		bool ok;
		if(moveHistory(Review::Direction::Previous, Review::ListLocate::First, &ok)==true){
			// 正常終了
			return;
		}
		if(ok==true){// 次の履歴があるのに移動失敗
			// エラー
			ReviewGUI::ReviewGUIAllUpdate(GetLayersBase());
		}else{
			// 通常終了
			return;
		}
	}
}

void ShowThumbnail::inputKeyFunction(Review::FKey key)
{
	ReviewPIBase *RBase = GetReviewAlgorithm();
	if(RBase!=NULL){
		CmdSetFKeyToNGNail Send(GetLayersBase());
		Send.key = key;
		RBase->TransmitDirectly(&Send);
		getCurrentThumbnail()->setFKeyColor(Send.FKeyColor);
	}
}

void ShowThumbnail::inputKeyDelete()
{
	if(getCurrentThumbnail()==NULL){// カレントNGが無い場合は何もしない
		return;
	}

	ReviewPIBase *RBase = GetReviewAlgorithm();
	if(RBase!=NULL){
		CmdClearFKeyToNGNail Send(GetLayersBase());
		RBase->TransmitDirectly(&Send);
		if(Send.Ret==true){
			getCurrentThumbnail()->clearFKeyColor();
		}
	}
}


QColor ShowThumbnail::setFKey(Review::FKey key)
{
	ReviewPIBase *RBase = GetReviewAlgorithm();

	if(RBase!=NULL){
		CmdSetFKeyToNGNail Send(GetLayersBase());
		Send.key = key;
		RBase->TransmitDirectly(&Send);
		if(Send.Ret==true){

			CmdSetFKeyForSave SetSend(GetLayersBase());
			SetSend.Key=key;
			RBase->TransmitDirectly(&SetSend);


			return Send.FKeyColor;
		}
	}

	CmdSetFKeyForSave SetSend(GetLayersBase());
	SetSend.Key=key;
	RBase->TransmitDirectly(&SetSend);

	return Review::getDefaultFKeyColor(Review::NoFKey);
}

bool ShowThumbnail::removeFKey(QColor &afterColor)
{
	if(getMoveMode()==_moveMode::PerThumbnail){
		getCurrentThumbnail()->setFKey(Review::NoFKey);
		//int	GlobalIndex	=getCurrentThumbnail()->getIndexInGlobal();
		//SetFKeyIndex(GlobalIndex,Review::NoFKey);

		ReviewPIBase *RBase = GetReviewAlgorithm();
		if(RBase!=NULL){
			CmdClearFKeyToNGNail Send(GetLayersBase());
			RBase->TransmitDirectly(&Send);
			if(Send.Ret==true){
				setFKey(Review::NoFKey);
				afterColor = Send.CheckedColor;
				getCurrentThumbnail()->repaint();
				return true;
			}
		}

	}else{
		bool ch = false;
		if(getExpandThumbnailVisible()==true){
			ch = true;
			setExpandThumbnailVisible(false);
		}
		QMessageBox::warning(this
							, LangSolver.GetString(ShowThumbnail_LS,LID_15)/*"Delete F Key Operation"*/
							, LangSolver.GetString(ShowThumbnail_LS,LID_16)/*"This Operation must be \"per Thumbnail Mode\".\n(Please recommand after you press 'Ctrl' key.)"*/);
		if(ch==true){
			setExpandThumbnailVisible(true);
		}
		return false;
	}

	return false;
}

bool	ShowThumbnail::GetAreaNameAndChecked(int GlobalIndex ,QString &AreaName)
{
	NGNailItem	NGItem;
	if(GlobalIndex<getThumbnailList(Review::Front).count()){
		int page = GlobalIndex / (getRowCount() * getColumnCount());
		int row = (GlobalIndex % (getRowCount() * getColumnCount())) / getColumnCount();
		int column = GlobalIndex % getColumnCount();
		ThumbnailPageItem	M=getThumbnailPageList(Review::Front)[page];
		for(int i=0;i<M.count();i++){
			if(M[i]->getRow()==row && M[i]->getColumn()==column){
				NGItem=M[i]->getNGNailItem();
				break;
			}
		}
	}else{
		int bindex = GlobalIndex - getThumbnailList(Review::Front).count();// 裏のみで見たインデックス
		int page = bindex / (getRowCount() * getColumnCount());
		int row = (bindex % (getRowCount() * getColumnCount())) / getColumnCount();
		int column = bindex % getColumnCount();
		ThumbnailPageItem	M=getThumbnailPageList(Review::Back)[page];
		for(int i=0;i<M.count();i++){
			if(M[i]->getRow()==row && M[i]->getColumn()==column){
				NGItem=M[i]->getNGNailItem();
				break;
			}
		}
	}
	for(int ng=0; ng<NGItem.NGPointList.count(); ng++){
		for(int pci=0; pci<NGItem.NGPointList[ng].PCEItems.count(); pci++){
			AreaName=NGItem.NGPointList[ng].PCEItems[pci].pieceName();
			if(AreaName.isEmpty()==true || NGItem.FKey==Review::NoFKey)
				return false;
			return true;
		}
	}

	return false;
}
