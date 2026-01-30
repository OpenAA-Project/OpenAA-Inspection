/*
 * Copyright (C) 2017
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

#include "NGImageListForReviewResource.h"
#include "NGImageListForReview.h"
#include "ReviewStructurePacket.h"
#include "NGImageListForReviewProperty.h"
#include "../XGUIReviewCommonPacket.h"
#include "../XGUIReviewGlobal.h"
#include "../NGImageForReview/NGImageForReviewPacket.h"

// �L�[���͉����֐�
// �㉺���E�A�t�@���N�V�����L�[�A�f���[�g�L�[�ɑΉ�
// [�㉺���E]
// ���ꂼ���uNG���P�����ɐi�߂��v�uNG���P�O�ɐi�߂��v�u�������P�߂��v�u�������P�i�߂��v
// [��]�́u������NG���Ȃ��ꍇ�͂P�����̗����������Έړ������B�܂��A�ړ����̗����̍Ō��ɃJ�����g���ړ������v
// [��]�́u�O��NG���Ȃ��ꍇ�͂P�O�̗����������Έړ������B�܂��A�ړ����̗����̍ŏ��ɃJ�����g���ړ������v
// [��]�́u�����̌��낪�����ꍇ�͈ړ������B�����̍ŏ��ɃJ�����g���ړ������v
// [�E]�́u�����̑O�������ꍇ�͈ړ������B�����̍ŏ��ɃJ�����g���ړ������v
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

	// ���̓L�[�������L�[�̏ꍇ
	if(Review::isArrowKey(event->key())==true || event->key()==Qt::Key_2 || event->key()==Qt::Key_4 || event->key()==Qt::Key_6 || event->key()==Qt::Key_8){
		if(reqData.NextListDelay!=0 || reqData.WaitProgressVisible==false){
			if(isKeyPressed()==true){
				ReEntrant=false;
				return;// ���������h�~
			}
		}
		if(isKeyMoveEnable()==false){
			ReEntrant=false;
			return;
		}

		CmdReqAdjacentCurrentNG Send(GetLayersBase());
		RBase->TransmitDirectly(&Send);
		// �J�[�\���L�[�ɂ��镪��
		switch(event->key()){
		case Qt::Key_Up:// ���L�[
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
		case Qt::Key_Down:// ���L�[
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
		case Qt::Key_Right:// ���L�[
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
		case Qt::Key_Left:// ���L�[
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

	// �y�[�W�A�b�v�_�E���ɂ��闚���ړ�
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

	// F�L�[�}���C�x���g
	if(Review::isFKey((Qt::Key)event->key())==true){
		if(isKeyPressed()==true){
			ReEntrant=false;
			return;// ���������h�~
		}
		if(isKeyMoveEnable()==false){
			ReEntrant=false;
			return;
		}

		// event�̓���F�L�[�ŃJ�����gNG��XML���ɑΉ�����F�L�[�v�f���t�^�A�������͏㏑������
		QColor FColor = setFKey(Review::convertFKeyQtToReview((Qt::Key)event->key()));
		fillBackgraundColorOnTableAtRow(ui.tblMain->currentRow(), FColor);// �Ή������F�Ŕw�i�F���h���Ԃ�
		inputKeyDownArrow(true);
		ReviewGUI::UpdateGUI(GetLayersBase(), ReviewGUI::Name::ListStatisticNG);
		setKeyPressedState(true);
		ReEntrant=false;
		return;
	}

	// F�L�[�폜�C�x���g
	if(event->key()==Qt::Key_Delete){
		if(isKeyPressed()==true){
			ReEntrant=false;
			return;// ���������h�~
		}
		if(isKeyMoveEnable()==false){
			ReEntrant=false;
			return;
		}

		QColor afterColor;// �폜���̐F
		if(removeFKey(afterColor)==true){// F�L�[�v�f�̍폜���g���C
			fillBackgraundColorOnTableAtRow(ui.tblMain->currentRow(), afterColor);
			ReviewGUI::UpdateGUI(GetLayersBase(), ReviewGUI::Name::ListStatisticNG);
			inputKeyDownArrow(false);
		}else{
			// ���s���̓��b�Z�[�W���o�͂��ĂȂɂ����Ȃ�
			QMessageBox::warning(this, LangSolver.GetString(NGImageListForReviewKeyEvents_LS,LID_13)/*"Remove FKey attribute error"*/, LangSolver.GetString(NGImageListForReviewKeyEvents_LS,LID_14)/*"FKey attribute whold be not removed in XML file."*/);
		}
		setKeyPressedState(true);
		ReEntrant=false;
		return;
	}

	if(event->key()==Qt::Key_Space){
		if(isKeyPressed()==true){
			ReEntrant=false;
			return;// ���������h�~
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

	// Insert�L�[�ɂ���NG�摜�ۑ�
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

	// �G���^�[�L�[�ɂ��鎟�ړ�
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


// NGNail���߂�
void NGImageListForReview::inputKeyUPArrow()
{
	if(/*ui.tblMain->currentRow()==0 || */ui.tblMain->currentRow()==-1)return;

	ReviewPIBase *RBase = GetReviewAlgorithm();

	if(RBase==NULL)return;

	CmdReqAdjacentCurrentNG	ExistNGCmd(GetLayersBase());		// �J�����gNG�̎��͂Ɋւ��������擾�R�}���h
	CmdMoveCurrentNGNail	NGMoveCmd(GetLayersBase());			// NG�ړ��p�R�}���h
	CmdMoveCurrentHistoryToNGBoard	HistoryMoveCmd(GetLayersBase());	// �����ړ��p�R�}���h

	RBase->TransmitDirectly(&ExistNGCmd);

	if(ExistNGCmd.Ret==true){
		if(ExistNGCmd.existPreviousNG()==true){// ������NG������
			NGMoveCmd.direction = Review::Previous;// NG�ړ��������ɐݒ�
			RBase->TransmitDirectly(&NGMoveCmd);// NG�������Ɉړ�

			setCheckedCurrentNG();// �J�����gNG���`�F�b�N�ς݂ɂ���

			// �f�[�^�ύX�ɍۂ��Ă̍X�V
			setCurrentRow(ui.tblMain->currentRow()-1);
			refleshTableRow(currentRow());// ������NG���X�g���X�V

			//GUIFormBase *FBase = GetLayersBase()->FindByName(ReviewGUI::Name::Root, ReviewGUI::Name::WholeImageForReview, "");
			//if(FBase!=NULL){
			//	GUICmdReqUpdateCurrentNG UpdateNGCmd(GetLayersBase());
			//	FBase->TransmitDirectly(&UpdateNGCmd);
			//}

			//ReviewGUI::UpdateGUI(GetLayersBase(), ReviewGUI::Name::NGImageForReview);// �C���[�W�摜�X�V

			return;
		}else{// ������NG�������̂ŗ������P�����Ɉړ�����

			// DAP 20120410 will recommand
			return;

			if(ExistNGCmd.existPreviousHistory()==true){// �����̗���������
				HistoryMoveCmd.direction = Review::Previous;// �����ړ������������ɐݒ�
				RBase->TransmitDirectly(&HistoryMoveCmd);

				if(ExistNGCmd.currentHistory()==HistoryMoveCmd.CurrentHistoryPtr)return;

				// NGNail�ʒu���Ō����ֈړ�
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
				// ����GUI�̃A�b�v�f�[�g
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
				
				//refleshTableRow(currentRow());// ������NG���X�g���X�V

				//GUIFormBase *FBase = GetLayersBase()->FindByName(ReviewGUI::Name::Root, ReviewGUI::Name::WholeImageForReview, "");
				//if(FBase!=NULL){
				//	GUICmdReqUpdateCurrentNG UpdateNGCmd(GetLayersBase());
				//	FBase->TransmitDirectly(&UpdateNGCmd);
				//}
				//ReviewGUI::UpdateGUI(GetLayersBase(), ReviewGUI::Name::NGImageForReview);// �C���[�W�摜�X�V

				return;
			}else{
				// �����̗����������̂ŉ������Ȃ�
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

// NGNail���i�߂�
void NGImageListForReview::inputKeyDownArrow(bool Skip)
{
	QString	AreaName;
	GetAreaNameAndChecked(currentRow() ,AreaName);

	NextMore:;
	if(ui.tblMain->currentRow()>=ui.tblMain->rowCount())return;

	ReviewPIBase *RBase = GetReviewAlgorithm();

	if(RBase==NULL)return;

	CmdReqAdjacentCurrentNG	ExistNGCmd(GetLayersBase());		// �J�����gNG�̎��͂Ɋւ��������擾�R�}���h
	CmdMoveCurrentNGNail	NGMoveCmd(GetLayersBase());			// NG�ړ��p�R�}���h
	CmdMoveCurrentHistoryToNGBoard	HistoryMoveCmd(GetLayersBase());	// �����ړ��p�R�}���h
	
	RBase->TransmitDirectly(&ExistNGCmd);

	if(ExistNGCmd.Ret==true){
		if(ExistNGCmd.existNextNG()==true){// ����NG������
			NGMoveCmd.direction = Review::Next;// NG�ړ������֐ݒ�
			RBase->TransmitDirectly(&NGMoveCmd);// NG�����ֈړ�

			setCheckedCurrentNG();// �J�����gNG���`�F�b�N�ς݂ɂ���

			// �f�[�^�ύX�ɍۂ��Ă̍X�V
			setCurrentRow(ui.tblMain->currentRow()+1);
			refleshTableRow(currentRow());// ������NG���X�g���X�V

			WorkedSpecifiedBroadcaster	OCasterCmd(this);
			BroadcastSpecifiedDirectly(&OCasterCmd);

			//ReviewGUI::UpdateGUI(GetLayersBase(), ReviewGUI::Name::NGImageForReview);// �C���[�W�摜�X�V

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


		}else{// �O��NG�������̂ŗ��������ֈړ�����

			if(ExistNGCmd.existNextHistory()==true){// ���̗���������
				if(ExistNGCmd.currentHistory()->isCheckedAll()==false)return;// ���ׂă`�F�b�N�ς݂łȂ��̂Ŏ��ɂ͂����Ȃ�

				// DAP�v�� (will recommand)
				return;

				HistoryMoveCmd.direction = Review::Next;// �����ړ������̕����ɐݒ�
				RBase->TransmitDirectly(&HistoryMoveCmd);// ���������ֈړ�

				if(ExistNGCmd.currentHistory()==HistoryMoveCmd.CurrentHistoryPtr)return;

				// NGNail�ʒu���擪�ֈړ�
				CmdSetCurrentNGNail SetNGPosCmd(GetLayersBase());
				SetNGPosCmd.locate = Review::First;
				RBase->TransmitDirectly(&SetNGPosCmd);

				setCheckedCurrentNG();// �J�����gNG���`�F�b�N�ς݂ɂ���

				//setCurrentRow(0);
				//refleshTableRow(currentRow());// ������NG���X�g���X�V
				updateGUI();

				// ����GUI�̃A�b�v�f�[�g
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
				//ReviewGUI::UpdateGUI(GetLayersBase(), ReviewGUI::Name::NGImageForReview);// �C���[�W�摜�X�V

				WorkedSpecifiedBroadcaster	OCasterCmd(this);
				BroadcastSpecifiedDirectly(&OCasterCmd);
				return;
			}else{
				// �����̗����������̂ŉ������Ȃ�
				return;
			}
		}
	}
}

// �������i�߂�
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

// �������߂�
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

