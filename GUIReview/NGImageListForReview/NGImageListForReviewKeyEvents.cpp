#include "NGImageListForReviewResource.h"
#include "NGImageListForReview.h"
#include "ReviewStructurePacket.h"
#include "NGImageListForReviewProperty.h"
#include "../XGUIReviewCommonPacket.h"
#include "../XGUIReviewGlobal.h"
#include "../NGImageForReview/NGImageForReviewPacket.h"

// キー入力応答関数
// 上下左右、ファンクションキー、デリートキーに対応
// [上下左右]
// それぞれ「NGを１つ後ろに進める」「NGを１つ前に進める」「履歴を１つ戻す」「履歴を１つ進める」
// [上]は「後ろにNGがない場合は１つ後ろの履歴があれば移動する。また、移動先の履歴の最後にカレントが移動する」
// [下]は「前にNGがない場合は１つ前の履歴があれば移動する。また、移動先の履歴の最初にカレントが移動する」
// [左]は「履歴の後ろがある場合は移動する。履歴の最初にカレントが移動する」
// [右]は「履歴の前がある場合は移動する。履歴の最初にカレントが移動する」
void NGImageListForReview::keyPressEvent(QKeyEvent *event)
{
	static	bool	ReEntrant=false;
	if(GetEditMode()==true){
		return;
	}

	if(ReEntrant==true)
		return;
	ReEntrant=true;

	CmdReqCurrentHistory reqCurrHistory(GetLayersBase());
	//ReviewPIBase *RBase = GetReviewAlgorithm();
	MakeReviewAlgorithm(RBase);
	if(RBase==NULL){
		ReEntrant=false;
		return;
	}
	RBase->TransmitDirectly( &reqCurrHistory );
	if(reqCurrHistory.Ret==false || reqCurrHistory.historyPrt()==NULL){
		int	d=event->key();
		if(d==Qt::Key_7 || d==Qt::Key_1){
			event->setAccepted(false);
			ResetPassedEventFlag();
			BroadcastEvent(event );
			event->setAccepted(true);
		}

		ReEntrant=false;
		return;
	}

	// 入力キーが矢印キーの場合
	if(Review::isArrowKey(event->key())==true || event->key()==Qt::Key_2 || event->key()==Qt::Key_4 || event->key()==Qt::Key_6 || event->key()==Qt::Key_8){
		if(reqData.NextListDelay!=0 || reqData.WaitProgressVisible==false){
			if(isKeyPressed()==true){
				ReEntrant=false;
				return;// 押し続け防止
			}
		}
		if(isKeyMoveEnable()==false){
			ReEntrant=false;
			return;
		}

		CmdReqAdjacentCurrentNG Send(GetLayersBase());
		RBase->TransmitDirectly(&Send);
		// カーソルキーによる分岐
		switch(event->key()){
		case Qt::Key_Up:// ↑キー
		case Qt::Key_8:
			if(Send.existPreviousNG()==true){
				if(Send.previousNG()->isChecked==false){
					if(isKeyMoveEnable()==false){
						ReEntrant=false;
						return;
					}
				}
			}else if(Send.existPreviousHistory()==true && Send.previousHistory()->isCheckedAll()==false){
				if(isKeyMoveEnable()==false){
					ReEntrant=false;
					return;
				}
			}
			inputKeyUPArrow();
			break;
		case Qt::Key_Down:// ↓キー
		case Qt::Key_2:
			if(Send.existNextNG()==true){
				if(Send.nextNG()->isChecked==false){
					if(isKeyMoveEnable()==false){
						ReEntrant=false;
						return;
					}
				}
			}else if(Send.existNextHistory()==true && Send.nextHistory()->isCheckedAll()==false){
				if(isKeyMoveEnable()==false){
					ReEntrant=false;
					return;
				}
			}
			inputKeyDownArrow(false);
			break;
		case Qt::Key_Right:// →キー
		case Qt::Key_6:
			if(Send.existNextHistory()==true){
				if(Send.nextHistory()->isCheckedAll()==false){
					if(isKeyMoveEnable()==false){
						ReEntrant=false;
						return;
					}
				}
				qDebug() << LangSolver.GetString(NGImageListForReviewKeyEvents_LS,LID_12)/*"Right Key do."*/;
				inputKeyRightArrow();
			}
			break;
		case Qt::Key_Left:// ←キー
		case Qt::Key_4:
			if(Send.existPreviousHistory()==true){
				if(Send.previousHistory()->isCheckedAll()==false){
					if(isKeyMoveEnable()==false){
						ReEntrant=false;
						return;
					}
				}
				inputKeyLeftArrow();
			}
			break;
		default:
			break;
		}
		setKeyPressedState(true);
		ReEntrant=false;
		return;
	}

	// ページアップダウンによる履歴移動
	if(event->key()==Qt::Key_PageUp || event->key()==Qt::Key_PageDown){
		if(isKeyPressed()==true){
			ReEntrant=false;
			return;
		}
		if(isKeyMoveEnable()==false){
			ReEntrant=false;
			return;
		}

		if(event->key()==Qt::Key_PageUp){
			inputKeyLeftArrow();
		}else{
			inputKeyRightArrow();
		}
		
		setKeyPressedState(true);
		ReEntrant=false;
		return;
	}

	// Fキー挿入イベント
	if(Review::isFKey((Qt::Key)event->key())==true){
		if(isKeyPressed()==true){
			ReEntrant=false;
			return;// 押し続け防止
		}
		if(isKeyMoveEnable()==false){
			ReEntrant=false;
			return;
		}

		// eventの入力FキーでカレントNGのXML分に対応するFキー要素を付与、もしくは上書きする
		QColor FColor = setFKey(Review::convertFKeyQtToReview((Qt::Key)event->key()));
		fillBackgraundColorOnTableAtRow(ui.tblMain->currentRow(), FColor);// 対応する色で背景色を塗りつぶし
		inputKeyDownArrow(true);
		ReviewGUI::UpdateGUI(GetLayersBase(), ReviewGUI::Name::ListStatisticNG);
		setKeyPressedState(true);
		ReEntrant=false;
		return;
	}

	// Fキー削除イベント
	if(event->key()==Qt::Key_Delete){
		if(isKeyPressed()==true){
			ReEntrant=false;
			return;// 押し続け防止
		}
		if(isKeyMoveEnable()==false){
			ReEntrant=false;
			return;
		}

		QColor afterColor;// 削除後の色
		if(removeFKey(afterColor)==true){// Fキー要素の削除をトライ
			fillBackgraundColorOnTableAtRow(ui.tblMain->currentRow(), afterColor);
			ReviewGUI::UpdateGUI(GetLayersBase(), ReviewGUI::Name::ListStatisticNG);
			inputKeyDownArrow(false);
		}else{
			// 失敗時はメッセージを出力してなにもしない
			QMessageBox::warning(this, LangSolver.GetString(NGImageListForReviewKeyEvents_LS,LID_13)/*"Remove FKey attribute error"*/, LangSolver.GetString(NGImageListForReviewKeyEvents_LS,LID_14)/*"FKey attribute whold be not removed in XML file."*/);
		}
		setKeyPressedState(true);
		ReEntrant=false;
		return;
	}

	if(event->key()==Qt::Key_Space){
		if(isKeyPressed()==true){
			ReEntrant=false;
			return;// 押し続け防止
		}
		if(isKeyMoveEnable()==false){
			ReEntrant=false;
			return;
		}

		GUIFormBase *FBase = GetReviewGUIForm(ReviewGUI::Name::NGImageForReview);
		if(FBase!=NULL){
			GUICmdExchangeNGVisible Send(GetLayersBase());
			FBase->TransmitDirectly(&Send);
		}

		setKeyPressedState(true);
		ReEntrant=false;
		return;
	}

	// InsertキーによるNG画像保存
	if(event->key()==Qt::Key_Insert){
		if((event->modifiers() & Qt::AltModifier)!=0){
			CmdSaveCurrentHistoryNGImages saveCurHistoryNGImg(GetLayersBase());
			RBase->TransmitDirectly(&saveCurHistoryNGImg);
			if(saveCurHistoryNGImg.Ret==true){
				QMessageBox::information(this, LangSolver.GetString(NGImageListForReviewKeyEvents_LS,LID_15)/*"Operator to save NG Image"*/, LangSolver.GetString(NGImageListForReviewKeyEvents_LS,LID_16)/*"NG Images in current Inspection are saved."*/);
			}
		}else{
			CmdSaveCurrentNGImage saveNGImg(GetLayersBase());
			RBase->TransmitDirectly(&saveNGImg);
		}
		ReEntrant=false;
		return;
	}

	// エンターキーによる次移動
	if(event->key()==Qt::Key_Enter || event->key()==Qt::Key_Return){
		if((event->modifiers() & Qt::ShiftModifier)==0){
			inputKeyEnter();
			ReEntrant=false;
			return;
		}else if((event->modifiers() & Qt::ShiftModifier)!=0){
			CmdMoveVRSToCurrentNG moveVRSToCurrent(GetLayersBase());
			moveVRSToCurrent.checkVRSEnable = false;
			RBase->TransmitDirectly( &moveVRSToCurrent );
			ReEntrant=false;
			return;
		}
	}
	else{
		event->setAccepted(false);
		ResetPassedEventFlag();
		BroadcastEvent(event );
		event->setAccepted(true);
		ReEntrant=false;
	}
}

void NGImageListForReview::keyReleaseEvent(QKeyEvent *event)
{
	if(event->isAutoRepeat()==true)return;
	setKeyPressedState(false);
}


// NGNailを戻る
void NGImageListForReview::inputKeyUPArrow()
{
	if(/*ui.tblMain->currentRow()==0 || */ui.tblMain->currentRow()==-1)return;

	ReviewPIBase *RBase = GetReviewAlgorithm();

	if(RBase==NULL)return;

	CmdReqAdjacentCurrentNG	ExistNGCmd(GetLayersBase());		// カレントNGの周囲に関する情報取得コマンド
	CmdMoveCurrentNGNail	NGMoveCmd(GetLayersBase());			// NG移動用コマンド
	CmdMoveCurrentHistoryToNGBoard	HistoryMoveCmd(GetLayersBase());	// 履歴移動用コマンド

	RBase->TransmitDirectly(&ExistNGCmd);

	if(ExistNGCmd.Ret==true){
		if(ExistNGCmd.existPreviousNG()==true){// 後ろのNGがある
			NGMoveCmd.direction = Review::Previous;// NG移動を後ろに設定
			RBase->TransmitDirectly(&NGMoveCmd);// NGを後ろに移動

			setCheckedCurrentNG();// カレントNGをチェック済みにする

			// データ変更に際しての更新
			setCurrentRow(ui.tblMain->currentRow()-1);
			refleshTableRow(currentRow());// 自分のNGリストを更新

			//GUIFormBase *FBase = GetLayersBase()->FindByName(ReviewGUI::Name::Root, ReviewGUI::Name::WholeImageForReview, "");
			//if(FBase!=NULL){
			//	GUICmdReqUpdateCurrentNG UpdateNGCmd(GetLayersBase());
			//	FBase->TransmitDirectly(&UpdateNGCmd);
			//}

			//ReviewGUI::UpdateGUI(GetLayersBase(), ReviewGUI::Name::NGImageForReview);// イメージ画像更新

			return;
		}else{// 後ろのNGが無いので履歴を１つ後ろに移動する

			// DAP 20120410 will recommand
			return;

			if(ExistNGCmd.existPreviousHistory()==true){// 後ろの履歴がある
				HistoryMoveCmd.direction = Review::Previous;// 履歴移動を後ろ方向に設定
				RBase->TransmitDirectly(&HistoryMoveCmd);

				if(ExistNGCmd.currentHistory()==HistoryMoveCmd.CurrentHistoryPtr)return;

				// NGNail位置を最後尾へ移動
				CmdSetCurrentNGNail SetNGPosCmd(GetLayersBase());
				SetNGPosCmd.locate = Review::End;
				RBase->TransmitDirectly(&SetNGPosCmd);
				if(SetNGPosCmd.Ret==true){
					setCheckedCurrentNG();
				}

				updateGUI();
				
				//GUIFormBase *GBase = GetReviewGUIForm(ReviewGUI::Name::WholeImageForReview);
				//if(GBase!=NULL){
				//	GUICmdReqUpdateCurrentNG UpdateCurrentNG(GetLayersBase());
				//	GBase->TransmitDirectly(&UpdateCurrentNG);
				//}
				// 履歴GUIのアップデート
				//if(ReviewGUI::UpdateGUI(GetLayersBase(), ReviewGUI::Name::ShowHistoryListForReview)==false){
				//	QMessageBox::warning(this, "Update Error", ReviewGUI::Name::Root + "::" + ReviewGUI::Name::ShowHistoryListForReview + " isn't updated.");
				//	return;
				//}
				GUICmdUpdateCurrentHistory Cmd(GetLayersBase());
				GUIFormBase *Base = GetReviewGUIForm(ReviewGUI::Name::ShowHistoryListForReview);
				if(Base!=NULL){
					Base->TransmitDirectly(&Cmd);
				}
				ReviewGUI::UpdateHistoryGUI(GetLayersBase(), ReviewGUI::Name::WholeImageForReview);

				setCurrentRow(ui.tblMain->rowCount()-1);
				
				//refleshTableRow(currentRow());// 自分のNGリストを更新

				//GUIFormBase *FBase = GetLayersBase()->FindByName(ReviewGUI::Name::Root, ReviewGUI::Name::WholeImageForReview, "");
				//if(FBase!=NULL){
				//	GUICmdReqUpdateCurrentNG UpdateNGCmd(GetLayersBase());
				//	FBase->TransmitDirectly(&UpdateNGCmd);
				//}
				//ReviewGUI::UpdateGUI(GetLayersBase(), ReviewGUI::Name::NGImageForReview);// イメージ画像更新

				return;
			}else{
				// 後ろの履歴が無いので何もしない
				return;
			}
		}
	}
}

bool	NGImageListForReview::GetAreaNameAndChecked(int row ,QString &AreaName)
{
	CmdReqCurrentHistory Send(GetLayersBase());
	ReviewPIBase *RBase = GetReviewAlgorithm();
	RBase->TransmitDirectly(&Send);
	if(Send.historyPrt()->hasFront()==true){
		NGNailList NGList = Send.historyPrt()->getFront()->getNGNails();
		if(row<NGList.count()){
			NGNailItem NGItem = NGList.at(row);
			for(int ng=0; ng<NGItem.NGPointList.count(); ng++){
				for(int pci=0; pci<NGItem.NGPointList[ng].PCEItems.count(); pci++){
					AreaName=NGItem.NGPointList[ng].PCEItems[pci].pieceName();
					if(AreaName.isEmpty()==true || NGItem.FKey==Review::NoFKey)
						return false;
					return true;
				}
			}
		}
		row-=NGList.count();
	}
	if(Send.historyPrt()->hasBack()==true){
		if(row>=0){
			NGNailList NGList = Send.historyPrt()->getBack()->getNGNails();
			NGNailItem NGItem = NGList.at(row);
			for(int ng=0; ng<NGItem.NGPointList.count(); ng++){
				for(int pci=0; pci<NGItem.NGPointList[ng].PCEItems.count(); pci++){
					AreaName=NGItem.NGPointList[ng].PCEItems[pci].pieceName();
					if(AreaName.isEmpty()==true || NGItem.FKey==Review::NoFKey)
						return false;
					return true;
				}
			}
		}
	}
	return false;
}

int	NGImageListForReview::GetListCount(void)
{
	CmdReqCurrentHistory Send(GetLayersBase());
	ReviewPIBase *RBase = GetReviewAlgorithm();
	RBase->TransmitDirectly(&Send);
	int	N=0;
	if(Send.historyPrt()->hasFront()==true){
		NGNailList NGList = Send.historyPrt()->getFront()->getNGNails();
		N+=NGList.count();
	}
	if(Send.historyPrt()->hasBack()==true){
		NGNailList NGList = Send.historyPrt()->getBack()->getNGNails();
		N+=NGList.count();
	}
	return N;
}

// NGNailを進める
void NGImageListForReview::inputKeyDownArrow(bool Skip)
{
	QString	AreaName;
	GetAreaNameAndChecked(currentRow() ,AreaName);

	NextMore:;
	if(ui.tblMain->currentRow()>=ui.tblMain->rowCount())return;

	ReviewPIBase *RBase = GetReviewAlgorithm();

	if(RBase==NULL)return;

	CmdReqAdjacentCurrentNG	ExistNGCmd(GetLayersBase());		// カレントNGの周囲に関する情報取得コマンド
	CmdMoveCurrentNGNail	NGMoveCmd(GetLayersBase());			// NG移動用コマンド
	CmdMoveCurrentHistoryToNGBoard	HistoryMoveCmd(GetLayersBase());	// 履歴移動用コマンド
	
	RBase->TransmitDirectly(&ExistNGCmd);

	if(ExistNGCmd.Ret==true){
		if(ExistNGCmd.existNextNG()==true){// 次のNGがある
			NGMoveCmd.direction = Review::Next;// NG移動を次へ設定
			RBase->TransmitDirectly(&NGMoveCmd);// NGを次へ移動

			setCheckedCurrentNG();// カレントNGをチェック済みにする

			// データ変更に際しての更新
			setCurrentRow(ui.tblMain->currentRow()+1);
			refleshTableRow(currentRow());// 自分のNGリストを更新

			WorkedSpecifiedBroadcaster	OCasterCmd(this);
			BroadcastSpecifiedDirectly(&OCasterCmd);

			//ReviewGUI::UpdateGUI(GetLayersBase(), ReviewGUI::Name::NGImageForReview);// イメージ画像更新

			//GUIFormBase *FBase = GetLayersBase()->FindByName(ReviewGUI::Name::Root, ReviewGUI::Name::WholeImageForReview, "");
			//if(FBase!=NULL){
			//	GUICmdReqUpdateCurrentNG UpdateNGCmd(GetLayersBase());
			//	FBase->TransmitDirectly(&UpdateNGCmd);
			//}

			if(SkipSamePiece==true && Skip==true){
				CmdReqCurrentHistory Send(GetLayersBase());
				RBase->TransmitDirectly(&Send);
				int	Row=currentRow();
				int	ListCount=GetListCount();
				QString	tAreaName;
				GetAreaNameAndChecked(Row,tAreaName);
				if(tAreaName.isEmpty()==false && tAreaName==AreaName){
					goto	NextMore;
				}
			}
			else if(SkipSamePiece==true && Skip==false){
				CmdReqCurrentHistory Send(GetLayersBase());
				RBase->TransmitDirectly(&Send);
				int	Row=currentRow();
				int	ListCount=GetListCount();
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

			return;


		}else{// 前のNGが無いので履歴を次へ移動する

			if(ExistNGCmd.existNextHistory()==true){// 次の履歴がある
				if(ExistNGCmd.currentHistory()->isCheckedAll()==false)return;// すべてチェック済みでないので次にはいけない

				// DAP要求 (will recommand)
				return;

				HistoryMoveCmd.direction = Review::Next;// 履歴移動を次の方向に設定
				RBase->TransmitDirectly(&HistoryMoveCmd);// 履歴を次へ移動

				if(ExistNGCmd.currentHistory()==HistoryMoveCmd.CurrentHistoryPtr)return;

				// NGNail位置を先頭へ移動
				CmdSetCurrentNGNail SetNGPosCmd(GetLayersBase());
				SetNGPosCmd.locate = Review::First;
				RBase->TransmitDirectly(&SetNGPosCmd);

				setCheckedCurrentNG();// カレントNGをチェック済みにする

				//setCurrentRow(0);
				//refleshTableRow(currentRow());// 自分のNGリストを更新
				updateGUI();

				// 履歴GUIのアップデート
				//ReviewGUI::UpdateGUI(GetLayersBase(), ReviewGUI::Name::ShowHistoryListForReview);
				GUICmdUpdateCurrentHistory Cmd(GetLayersBase());
				GUIFormBase *Base = GetReviewGUIForm(ReviewGUI::Name::ShowHistoryListForReview);
				if(Base!=NULL){
					Base->TransmitDirectly(&Cmd);
				}
				ReviewGUI::UpdateHistoryGUI(GetLayersBase(), ReviewGUI::Name::WholeImageForReview);
				//GUIFormBase *FBase = GetLayersBase()->FindByName(ReviewGUI::Name::Root, ReviewGUI::Name::WholeImageForReview, "");
				//if(FBase!=NULL){
				//	GUICmdReqUpdateCurrentNG UpdateNGCmd(GetLayersBase());
				//	FBase->TransmitDirectly(&UpdateNGCmd);
				//}
				//ReviewGUI::UpdateGUI(GetLayersBase(), ReviewGUI::Name::NGImageForReview);// イメージ画像更新

				WorkedSpecifiedBroadcaster	OCasterCmd(this);
				BroadcastSpecifiedDirectly(&OCasterCmd);
				return;
			}else{
				// 後ろの履歴が無いので何もしない
				return;
			}
		}
	}
}

// 履歴を進める
void NGImageListForReview::inputKeyRightArrow()
{
	// check
	if(getProperty().isMoveHistoryOnLeftRightKey==false){
		return;
	}

	if(getProperty().isAllCheckOnMoveHistoryByLeftRightKey==true){
		qDebug() << LangSolver.GetString(NGImageListForReviewKeyEvents_LS,LID_17)/*"Right key start."*/;
		ReviewPIBase *RBase = GetReviewAlgorithm();
		if(RBase==NULL)return;

		CmdReqCurrentHistory reqCurrentHistroy(GetLayersBase());
		RBase->TransmitDirectly( &reqCurrentHistroy );

		if(reqCurrentHistroy.historyPrt()==NULL){
			return;
		}

		// Search all NG checked.
		if(reqCurrentHistroy.historyPrt()->isCheckedAll()==false){
			// MaxError and TimeOut are ignore?
			if(getProperty().isIgnoreResultError==true){
				if(reqCurrentHistroy.historyPrt()->hasFront()==true){
					qDebug() << reqCurrentHistroy.historyPrt()->getFront()->Result;
				}
				if(reqCurrentHistroy.historyPrt()->hasBack()==true){
					qDebug() << reqCurrentHistroy.historyPrt()->getBack()->Result;
				}
				// check include error result.
				if(reqCurrentHistroy.historyPrt()->isErrorBoard()==false){
					return;
				}
				WorkedSpecifiedBroadcaster	OCasterCmd(this);
				BroadcastSpecifiedDirectly(&OCasterCmd);

				//bool hasResultError = false;
				//if(reqCurrentHistroy.OrgHistoryPtr->hasFront()==true){
				//	if(hasResultError==false && reqCurrentHistroy.OrgHistoryPtr->getFront()->Result.contains(Review::StaticString::InspectionResult::MaxError)==true){
				//		hasResultError = true;
				//	}
				//	if(hasResultError==false && reqCurrentHistroy.OrgHistoryPtr->getFront()->Result.contains(Review::StaticString::InspectionResult::TimeOut)==true){
				//		hasResultError = true;
				//	}
				//}
				//if(reqCurrentHistroy.OrgHistoryPtr->hasBack()==true){
				//	if(hasResultError==false && reqCurrentHistroy.OrgHistoryPtr->getBack()->Result.contains(Review::StaticString::InspectionResult::MaxError)==true){
				//		hasResultError = true;
				//	}
				//	if(hasResultError==false && reqCurrentHistroy.OrgHistoryPtr->getBack()->Result.contains(Review::StaticString::InspectionResult::TimeOut)==true){
				//		hasResultError = true;
				//	}
				//}
				//if(hasResultError==false){
				//	return;
				//}
			}else{
				return;
			}
		}
	}

	moveHistory(Review::Direction::Next);
}

// 履歴を戻る
void NGImageListForReview::inputKeyLeftArrow()
{
	if(getProperty().isMoveHistoryOnLeftRightKey==false){
		return;
	}

	//  check
	if(getProperty().isAlwaysPreviousOperationEnable==false){

		if(getProperty().isAllCheckOnMoveHistoryByLeftRightKey==true){
			ReviewPIBase *RBase = GetReviewAlgorithm();
			if(RBase==NULL)return;

			CmdReqCurrentHistory reqCurrentHistroy(GetLayersBase());
			RBase->TransmitDirectly( &reqCurrentHistroy );

			if(reqCurrentHistroy.historyPrt()==NULL){
				return;
			}
			WorkedSpecifiedBroadcaster	OCasterCmd(this);
			BroadcastSpecifiedDirectly(&OCasterCmd);

			// Search all NG checked.
			if(reqCurrentHistroy.historyPrt()->isCheckedAll()==false){
				// MaxError and TimeOut are ignore?
				if(getProperty().isIgnoreResultError==true){
					// check include error result.
					bool hasResultError = false;
					if(reqCurrentHistroy.historyPrt()->hasFront()==true){
						if(hasResultError==false && reqCurrentHistroy.historyPrt()->getFront()->Result.contains(Review::StaticString::InspectionResult::MaxError)==true){
							hasResultError = true;
						}
						if(hasResultError==false && reqCurrentHistroy.historyPrt()->getFront()->Result.contains(Review::StaticString::InspectionResult::TimeOut)==true){
							hasResultError = true;
						}
					}
					if(reqCurrentHistroy.historyPrt()->hasBack()==true){
						if(hasResultError==false && reqCurrentHistroy.historyPrt()->getBack()->Result.contains(Review::StaticString::InspectionResult::MaxError)==true){
							hasResultError = true;
						}
						if(hasResultError==false && reqCurrentHistroy.historyPrt()->getBack()->Result.contains(Review::StaticString::InspectionResult::TimeOut)==true){
							hasResultError = true;
						}
					}
					if(hasResultError==false){
						return;
					}
				}else{
					return;
				}
			}
		}
	}

	moveHistory(Review::Direction::Previous);
}

void NGImageListForReview::inputKeyEnter()
{
	//  check
	if(getProperty().isMoveHistoryOnEnterKey==false){
		return;
	}

	if(getProperty().isAllCheckOnMoveHistoryByEnterKey==true){
		ReviewPIBase *RBase = GetReviewAlgorithm();
		if(RBase==NULL)return;

		CmdReqCurrentHistory reqCurrentHistroy(GetLayersBase());
		RBase->TransmitDirectly( &reqCurrentHistroy );

		if(reqCurrentHistroy.historyPrt()==NULL){
			return;
		}

		WorkedSpecifiedBroadcaster	OCasterCmd(this);
		BroadcastSpecifiedDirectly(&OCasterCmd);

		// Search all NG checked.
		if(reqCurrentHistroy.historyPrt()->isCheckedAll()==false){
			// MaxError and TimeOut are ignore?
			if(getProperty().isIgnoreResultError==true){
				// check include error result.
				bool hasResultError = false;
				if(reqCurrentHistroy.historyPrt()->hasFront()==true){
					if(hasResultError==false && reqCurrentHistroy.historyPrt()->getFront()->Result.contains(Review::StaticString::InspectionResult::MaxError)==true){
						hasResultError = true;
					}
					if(hasResultError==false && reqCurrentHistroy.historyPrt()->getFront()->Result.contains(Review::StaticString::InspectionResult::TimeOut)==true){
						hasResultError = true;
					}
				}
				if(reqCurrentHistroy.historyPrt()->hasBack()==true){
					if(hasResultError==false && reqCurrentHistroy.historyPrt()->getBack()->Result.contains(Review::StaticString::InspectionResult::MaxError)==true){
						hasResultError = true;
					}
					if(hasResultError==false && reqCurrentHistroy.historyPrt()->getBack()->Result.contains(Review::StaticString::InspectionResult::TimeOut)==true){
						hasResultError = true;
					}
				}
				if(hasResultError==false){
					return;
				}
			}else{
				return;
			}
		}
	}

	moveHistory(Review::Direction::Next);
}


