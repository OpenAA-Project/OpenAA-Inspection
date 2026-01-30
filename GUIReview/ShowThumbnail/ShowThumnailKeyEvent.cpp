/*
 * Copyright (C) 2021
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

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

	if(getCurrentThumbnail()==NULL || getCurrentRow()==-1 || getCurrentColumn()==-1){// ���I�����Ԃ̏ꍇ
		if(isKeyPressed()==true)return;

		// ���݂̏��Ԃ��擾
		CmdReqAdjacentCurrentNG AdjNGCmd(GetLayersBase());
		ReviewPIBase *RBase = GetReviewAlgorithm();

		if(RBase!=NULL){
			RBase->TransmitDirectly(&AdjNGCmd);
		}

		if(AdjNGCmd.existCurrentHistory()==false){// �������ǂݍ��܂��Ă��Ȃ��̂Ȃ���
			return;// ���f
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
				if(getCurrentPage()!=0){// �܂��O�y�[�W�������Ƃ�
					showPage(getCurrentSide(), getCurrentPage()-1, Review::ListLocate::First);
				}else if(getCurrentSide()==Review::Back && getThumbnailCount(Review::Front)!=0){
					setUpdatesEnabled(false);// ���̏ꍇ�ŕ\�������Ƃ�
					showPage(Review::Front, getPageCount(Review::Front)-1, Review::ListLocate::First);// �\�̍Ō��̃y�[�W�̍ŏ��̃T���l�C��
					//getThumbnailCount(Review::Front) - getThumbnailCount(Review::Front)%getThumbnailCountInPage()
					setUpdatesEnabled(true);
				}else{// ���̏ꍇ�ŕ\���Ȃ����A�������͕\�̍ŏ��̃y�[�W�̎�
					setUpdatesEnabled(false);
					moveHistory(Review::Direction::Previous, Review::ListLocate::End, NULL);// �O�̗����̍Ō��Ɉړ�
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
						showPage(Review::Back, Review::First);// ���̍ŏ��Ɉړ�����
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

	// ���̓L�[�������L�[�̏ꍇ
	if(Review::isArrowKey(event->key())==true || event->key()==Qt::Key_2 || event->key()==Qt::Key_4 || event->key()==Qt::Key_6 || event->key()==Qt::Key_8){
		if(isKeyPressed()==true)return;

		//if(existCurrentThumbnail()==false){// �J�����gNG�������ꍇ�͉������Ȃ�
		//	return;
		//}
		//qDebug() << "Current Side : " << (getCurrentSide()==Review::Front ? "Front" : "Back");
		//qDebug() << "Current Page/Max : " << getCurrentPage() << " / " << getCurrentPageCount();
		//qDebug() << "Current Row,Column : " << getCurrentRow() << "," << getCurrentColumn();

		// �J�[�\���L�[�ɂ��镪��

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
		case Qt::Key_Up:// ���L�[ [�߂�]
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
		case Qt::Key_Down:// ���L�[ [�i��]
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
		case Qt::Key_Right:// ���L�[ [�i��]
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
		case Qt::Key_Left:// ���L�[ [�߂�]
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

	// F�L�[�}���C�x���g
	if(Review::isFKey((Qt::Key)event->key())==true){
		if(isKeyPressed()==true)return;

		if(getMoveMode()==_moveMode::PerThumbnail){
			// event�̓���F�L�[�ŃJ�����gNG��XML���ɑΉ�����F�L�[�v�f���t�^�A�������͏㏑������
			QColor FKeyColor = setFKey(Review::convertFKeyQtToReview((Qt::Key)event->key()));
			//SetFKeyIndex(getCurrentThumbnail()->getIndexInGlobal() ,Review::convertFKeyQtToReview((Qt::Key)event->key()));
			getCurrentThumbnail()->setFKey(Review::convertFKeyQtToReview((Qt::Key)event->key()));
			getCurrentThumbnail()->setFKeyColor(FKeyColor);// �Ή������F�Ŕw�i�F���h���Ԃ�
			
			inputKeyRightArrow(true);// ����NGNail��
			
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

	// F�L�[�폜�C�x���g
	if(event->key()==Qt::Key_Delete){
		if(isKeyPressed()==true)return;

		QColor afterColor;// �폜���̐F
		if(removeFKey(afterColor)==true){// F�L�[�v�f�̍폜���g���C
			if(getCurrentThumbnail()!=NULL){
				getCurrentThumbnail()->setFKeyColor(afterColor);
			}
			ReviewGUI::UpdateGUI(GetLayersBase(), ReviewGUI::Name::ListStatisticNG);
		}else if(getMoveMode()==_moveMode::PerThumbnail){
			// ���s���̓��b�Z�[�W���o�͂��ĂȂɂ����Ȃ�
			QMessageBox::warning(this
								, LangSolver.GetString(ShowThumbnail_LS,LID_11)/*"Remove FKey attribute error"*/
								, LangSolver.GetString(ShowThumbnail_LS,LID_12)/*"FKey attribute whold be not removed in XML file."*/);
		}
		setKeyPressedState(true);
		return;
	}

	// �G���^�[�L�[�A���^�[���L�[�C�x���g
	if(event->key()==Qt::Key_Return || event->key()==Qt::Key_Enter){
		if(event->modifiers()==Qt::NoModifier){
			// �ʑ��ŃJ�����gThumbnail���\��
			if(getMoveMode()==_moveMode::PerThumbnail){
				if(isKeyPressed()==true)return;// ���������Ή�
				if(getCurrentThumbnail()==NULL)return;// ���݃T���l�C���Ȃ�
				if(isEnableExpandThumbnal()==false)return;// �g���T���l�C���������[�h
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
				// �y�[�W���[�h�̏ꍇ�A�����Ԋu���󂢂Ă����Ȃ��΃y�[�W�̂��ׂĂ��`�F�b�N�ς݂ɂł���
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
				NGCheckCmd.begin = getCurrentThumbnail()->getIndexInLocal();// ����NGNail
				NGCheckCmd.length = 1;// ����NG�̂�
				RBase->TransmitDirectly(&NGCheckCmd);
				getCurrentThumbnail()->setChecked(true);
				
				GUICmdUpdateCurrentHistoryChecked HistoryCheckCmd(GetLayersBase());
				ReviewGUI::ReviewGUICmdSend(GetLayersBase(), &HistoryCheckCmd, ReviewGUI::Name::ShowHistoryListForReview);
			}
		}
	}
	updateInfoLabel();
}


// NG���߂�
// ���{�͌��݃��E���P����
// �������A���݃��E��0�̏ꍇ�͂��̃y�[�W��NG�����ׂă`�F�b�N���Ă����ꍇ�̂݃y�[�W���P�߂�
// �������A���݃y�[�W���\�̂��闠��0�̎��͕\�̍Ō���NG�ɃJ�����gNG���ڂ�
// �łȂ����΁A�������P�߂��Ō���NG�փJ�����gNG���ړ�����
// �ȑO�̗������������Ή������Ȃ�
void ShowThumbnail::inputKeyUpArrow()
{
	// �T���l�C���P�ʈړ�
	if(getMoveMode()==_moveMode::PerThumbnail){
		if(getCurrentRow()!=0){//�J�����gNG���y�[�W�̈��ԏ��ł͂Ȃ��ꍇ
			showPage(Review::Manual, getCurrentThumbnail()->getIndexInGlobal() - getColumnCount());// �P�s���グ��
			//setCurrentNG(getCurrentSide(), getCurrentPage(), getCurrentRow()-1, getCurrentColumn());
		}else{// �J�����gNG�̃��E���y�[�W�̈��ԏ��̏ꍇ
			if(getCurrentPage()==0){
				//if(isMoveHistoryEnable()==false){
				//	bool expandVisible = getExpandThumbnailVisible();
				//	QMessageBox::warning(this, "History can't be changed.", "You would be changed on all Thumbnail Item was checked in current History.");
				//	setExpandThumbnailVisible(expandVisible);
				//	return;
				//}

				if(getCurrentSide()==Review::Front){// �\���̏ꍇ�A�������P�߂��A�J�����gNG���Ō��Ɉڂ�

					return;// ���� 20120528

					// �S�`�F�b�N���Ă��Ȃ��Ƃ��������Ȃ�
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
						// �����I��
						return;
					}
					if(ok==true){// ���̗����������̂Ɉړ����s
						// �G���[
						ReviewGUI::ReviewGUIAllUpdate(GetLayersBase());
					}else{
						// �ʏ��I��
						return;
					}
				}else{// ���둤�̏ꍇ
					if(getThumbnailList(Review::Front).count()!=0){// �\�������������ꍇ
						showPage(Review::Front, Review::End);// �\���̍Ō��̃y�[�W�̍Ō��̗v�f���I������
					}else{// �\���������Ȃ��ꍇ�A�������P�߂�
						return;// �߂��Ȃ�
						// �S�`�F�b�N���Ă��Ȃ��Ƃ��������Ȃ�
						if(isMoveHistoryEnable()==false){
							return;
						}

						bool ok;
						if(moveHistory(Review::Direction::Previous, Review::ListLocate::End, &ok)==true){
							// �����I��
							return;
						}
						if(ok==true){// ���̗����������̂Ɉړ����s
						// �G���[
							ReviewGUI::ReviewGUIAllUpdate(GetLayersBase());
						}else{
							// �ʏ��I��
							return;
						}
					}
				}
			}else{
				showPage(Review::Manual, getCurrentThumbnail()->getIndexInGlobal() - getColumnCount());
			}
		}
	}else{// �y�[�W�P�ʈړ�
		if(getCurrentPage()>0){
			showPage(getCurrentSide(), getCurrentPage()-1, Review::First);
		}else if(getCurrentPage()==0){
			if(getCurrentSide()==Review::Front){// �\���̏ꍇ�A�������P�߂�

				// �S�`�F�b�N���Ă��Ȃ��Ƃ��������Ȃ�
				if(isMoveHistoryEnable()==false){
					return;
				}

				bool ok;
				if(moveHistory(Review::Direction::Previous, Review::ListLocate::End, &ok)==true){
					// �����I��
					return;
				}
				if(ok==true){// ���̗����������̂Ɉړ����s
					// �G���[
					ReviewGUI::ReviewGUIAllUpdate(GetLayersBase());
				}else{
					// �ʏ��I��
					return;
				}
			}else{// ���둤�̏ꍇ
				if(getThumbnailList(Review::Front).count()!=0){// �\�������������ꍇ
					showPage(Review::Front, Review::End);// �\���̍Ō��̃y�[�W�̍Ō��̗v�f���I������
				}else{// �\���������Ȃ��ꍇ�A�������P�߂�
					
					// �S�`�F�b�N���Ă��Ȃ��Ƃ��������Ȃ�
					if(isMoveHistoryEnable()==false){
						return;
					}

					bool ok;
					if(moveHistory(Review::Direction::Previous, Review::ListLocate::End, &ok)==true){
						// �����I��
						return;
					}
					if(ok==true){// ���̗����������̂Ɉړ����s
					// �G���[
						ReviewGUI::ReviewGUIAllUpdate(GetLayersBase());
					}else{
						// �ʏ��I��
						return;
					}
				}
			}
		}
	}
}

// NG���i�߂�
// ���{�͌��݃��E���P����
// �������A���݃��E���y�[�W�̍Ō��̏ꍇ�̓y�[�W���P�i�߂�
// �������A���݃y�[�W�����̂����\��0�̎��͗��̍ŏ���NG�ɃJ�����gNG���ڂ�
// �łȂ����΁A�������P�i�߂čŏ���NG�փJ�����gNG���ړ�����
// ���̗������������Ή������Ȃ�
void ShowThumbnail::inputKeyDownArrow(bool Skip)
{
	// �T���l�C���P�ʈړ�
	if(getMoveMode()==_moveMode::PerThumbnail){
		if((getCurrentThumbnailList().count() - getCurrentThumbnail()->getIndexInLocal()) <= getColumnCount()){// ���݃T���l�C���\���̉����ɊY�������T���l�C�����Ȃ��Ōォ�����񕪂̏ꍇ
			if(isCurrentPageAllChecked()==true){
				if(getCurrentSide()==Review::Front && getThumbnailList(Review::Back).count()!=0){// �\�̏ꍇ�ŁA���������ꍇ
					showPage(Review::Back, Review::First);// ���̍ŏ��Ɉړ�����
				}else{// ���̗����Ɉړ�����
					ChooseNextDialog	D;
					if(D.exec()==(int)true){
						if(isMoveHistoryEnable()==true){// ���݂̑S�ẴA�C�e�����`�F�b�N�ς݂ł݈̂ړ��\ //
							bool ok;
							if(moveHistory(Review::Direction::Next, Review::ListLocate::First, &ok)==true){
								// �����I��
								return;
							}
							if(ok==true){// �P�O�̗����������̂Ɉړ����s
					// �G���[
								ReviewGUI::ReviewGUIAllUpdate(GetLayersBase());
							}else{
								// �ʏ��I��
								return;
							}
						}
					}
					return; // ����
				}
			}
		}else if(getCurrentRow()!=getRowCount()-1){// �����y�[�W���ŉ��ֈړ��ł����ꍇ
			showPage(getCurrentSide(), getCurrentPage(), Review::Manual, getCurrentThumbnail()->getRow()+1, getCurrentThumbnail()->getColumn());
		}else{// �y�[�W���P�グ�A�ŏ��̍s�ֈړ�����
			if(isCurrentPageAllChecked()==true){// ���̃y�[�W���S�`�F�b�N�ς݂ł����ꍇ�̂ݎ��̃y�[�W�ֈړ��ł���
				showPage(getCurrentSide(), getCurrentPage()+1, Review::Manual, 0, getCurrentThumbnail()->getColumn());
			}else{
				// 
			}
		}
	}else{// �y�[�W�P�ʈړ�
		if(isCurrentPageAllChecked()==true){// ���ׂă`�F�b�N�ς݂̏ꍇ�̂ݎ��y�[�W�ֈړ��\ //
			if(getCurrentPage()!=getCurrentPageLastIndex()){
					showPage(getCurrentSide(), getCurrentPage()+1, Review::First);
				if(getCurrentThumbnail()!=NULL){
 					CmdSetNGChecked NGCheckCmd(GetLayersBase());
					NGCheckCmd.side = getCurrentSide();
					NGCheckCmd.begin = getGlobalIndex(getCurrentPage(), getCurrentRow(), getCurrentColumn(), getCurrentSide());
					NGCheckCmd.length = getRowCount() * getColumnCount();	//1;// ����NG�̂�
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
				if(getCurrentSide()==Review::Front && getThumbnailList(Review::Back).count()!=0){// �\�̏ꍇ�ŁA���������ꍇ
					showPage(Review::Back, Review::First);// ���̍ŏ��Ɉړ�����
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
					&& getThumbnail(Review::Back, getCurrentPage()+1-getThumbnailPageList(Review::Front).count(),0,0)->getNGNailItem().phase==1){// Phase=1�̗��������ꍇ
					showPage(Review::Back, Review::First);// ���̍ŏ��Ɉړ�����
					getCurrentThumbnail()->setChecked(true);
					//for(int row=0;row<getRowCount();row++){
					//	for(int column=0;column<getColumnCount();column++){
					//		int	n=getLocalIndex(getCurrentPage(), row, column, getCurrentSide());
					//		if(0<=n && n<getThumbnailList(getCurrentSide()).count()){
					//			getThumbnailList(getCurrentSide())[n]->setChecked(true);
					//		}
					//	}
					//}
				}else{// ���̗����Ɉړ�����
					ChooseNextDialog	D;
					if(D.exec()==(int)true){
						// ���̗����Ɉړ�����
						if(isMoveHistoryEnable()==true){// ���݂̑S�ẴA�C�e�����`�F�b�N�ς݂ł݈̂ړ��\ //
							bool ok;
							if(moveHistory(Review::Direction::Next, Review::ListLocate::First, &ok)==true){
								// �����I��
								return;
							}
							if(ok==true){// �P�O�̗����������̂Ɉړ����s
								// �G���[
								ReviewGUI::ReviewGUIAllUpdate(GetLayersBase());
							}else{
								// �ʏ��I��
								return;
							}
						}
					}
					return;// ���Ȃ�
				}
			}
		}
	}
}

// NG���i�߂�
// ���{�̓J�����gNG���P�i�߂�
// �������A�J�����gNG���J�����g�����̍Ō��̏ꍇ�͎��̗����ֈړ�����
// ���̗������������Ή������Ȃ�
void ShowThumbnail::inputKeyRightArrow(bool Skip)
{
	if(getMoveMode()==_moveMode::PerThumbnail){
		QString	AreaName;
		GetAreaNameAndChecked(getCurrentThumbnail()->getIndexInGlobal() ,AreaName);
		int	CurrentGlobalIndex=getCurrentThumbnail()->getIndexInGlobal();
NextMore:;
		if(CurrentGlobalIndex==getCurrentThumbnailLastGlobalIndex()){// ���݂̗����ɂ������Ō��̃T���l�C���̏ꍇ�A���̗����ֈړ������݂�
			
			return;// ���� 20120523
				
			// ���݂̃y�[�W���S�ă`�F�b�N�ς݂�����
			if(isMoveHistoryEnable()==true){
				bool ok;
				// ���̗����ֈړ�
				if(moveHistory(Review::Direction::Next, Review::ListLocate::First, &ok)==true){
					// �����I��
					return;
				}
				if(ok==true){
					// �G���[
					ReviewGUI::ReviewGUIAllUpdate(GetLayersBase());
				}else{
					// ���̗��𖳂�(�����I��)
					// �Ȃɂ����Ȃ�
					return;
				}
			}
		}else{
			// ���̃y�[�W�ֈړ������Ƃ��ɁA���݂̃y�[�W�̑S�ĂɃ`�F�b�N�������Ă��Ȃ����Έړ��֎~
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
			// ���̃T���l�C�����I������
			showPage(Review::Manual, CurrentGlobalIndex);
		}
	}else{// �y�[�W�P�ʈړ�

		// �������ړ� 20120528
		//// �S�`�F�b�N���Ă��Ȃ��Ƃ��������Ȃ�
		//if(isMoveHistoryEnable()==false){
		//	return;
		//}
		bool ok;
		if(moveHistory(Review::Direction::Next, Review::ListLocate::First, &ok)==true){
			// �����I��
			return;
		}
		if(ok==true){// �P�O�̗����������̂Ɉړ����s
			// �G���[
			ReviewGUI::ReviewGUIAllUpdate(GetLayersBase());
		}else{
			// �ʏ��I��
			return;
		}
	}
}

// NG���߂�
// ���{�̓J�����gNG���P�߂�
// �������A�J�����gNG���J�����g�����̍ŏ��̏ꍇ�͂P�����̗����ֈړ�����
// �����̗������������Ή������Ȃ�
void ShowThumbnail::inputKeyLeftArrow()
{
	if(getMoveMode()==_moveMode::PerThumbnail){
		if(getCurrentThumbnail()->getIndexInGlobal()==0){// �����̍ŏ��̏ꍇ

			return;// ���� 20120523

			// �S�`�F�b�N���Ă��Ȃ��Ƃ��������Ȃ�
			if(isMoveHistoryEnable()==false){
				return;
			}
			// �O�̗����ֈړ�
			bool ok;
			if(moveHistory(Review::Direction::Previous, Review::ListLocate::End, &ok)==true){
				// �����I��
				return;
			}
			if(ok==true){
				// �G���[
				ReviewGUI::ReviewGUIAllUpdate(GetLayersBase());
			}else{
				// ���̗��𖳂�(�����I��)
				// �Ȃɂ����Ȃ�
				return;
			}
		}else{
			showPage(Review::Manual, getCurrentThumbnail()->getIndexInGlobal()-1);
		}
	}else{// �y�[�W�P�ʈړ�
		
		// �������ړ� 20120528
		//// �S�`�F�b�N���Ă��Ȃ��Ƃ��������Ȃ�
		//if(isMoveHistoryEnable()==false){
		//	return;
		//}

		bool ok;
		if(moveHistory(Review::Direction::Previous, Review::ListLocate::First, &ok)==true){
			// �����I��
			return;
		}
		if(ok==true){// ���̗����������̂Ɉړ����s
			// �G���[
			ReviewGUI::ReviewGUIAllUpdate(GetLayersBase());
		}else{
			// �ʏ��I��
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
	if(getCurrentThumbnail()==NULL){// �J�����gNG�������ꍇ�͉������Ȃ�
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
		int bindex = GlobalIndex - getThumbnailList(Review::Front).count();// ���݂̂Ō����C���f�b�N�X
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