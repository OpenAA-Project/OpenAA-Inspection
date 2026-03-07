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

#include "ShowHistoryListForReviewResource.h"
#include "HistoryListErrorDialog.h"
#include "ReviewStructureItems.h"

void HistoryListErrorDialog::setHistory(OrganizedHistoryListPtr listPtr, Review::OrganizedSideType oside)
{
	if(listPtr!=NULL && listPtr->isEmpty()==false){
		if(oside==Review::OrganizedSideType::Both){// ���ʂ̏ꍇ
			// �G���[�`�F�b�N
			// ����ID�̔��сA�d��������

			QHash<int,bool> FrontMultiIDError;
			QList<int> FrontNoExistError;// �\���̂Ȃ�ID
			QHash<int,bool> BackMultiIDError;
			QList<int> BackNoExistError;// �����̂Ȃ�ID
			int FrontOKCount=0;
			int FrontNGCount=0;
			int BackOKCount=0;
			int BackNGCount=0;

			for(int i=0; i<listPtr->count(); i++){
				if(listPtr->at(i).hasFront()==false){// �\���������`�F�b�N
					FrontNoExistError.append(listPtr->at(i).getInspectID());// ���������Ȃ�
				}else{
					if(FrontMultiIDError.contains(listPtr->at(i).getInspectID())==true){// ����ID���������݂��Ă���
						FrontMultiIDError[listPtr->at(i).getInspectID()] = false;
					}else{
						FrontMultiIDError.insert(listPtr->at(i).getInspectID(), true);// �ʏ���ID���Ƃɂ����Ɉ��x��������
					}
					if(listPtr->at(i).getFront()->isOK()){// OK��NG���ŕ����A���Z
						FrontOKCount++;
					}else{
						FrontNGCount++;
					}
				}
				if(listPtr->at(i).hasBack()==false){// �����������`�F�b�N
					BackNoExistError.append(listPtr->at(i).getInspectID());// ���������Ȃ�
				}else{
					if(BackMultiIDError.contains(listPtr->at(i).getInspectID())==true){// ����ID���������݂��Ă���
						BackMultiIDError[listPtr->at(i).getInspectID()] = false;
					}else{
						BackMultiIDError.insert(listPtr->at(i).getInspectID(), true);// �ʏ���ID���Ƃɂ����Ɉ��x��������
					}
					if(listPtr->at(i).getBack()->isOK()){// OK��NG���ŕ����A���Z
						BackOKCount++;
					}else{
						BackNGCount++;
					}
				}
			}

			{
			// �G���[�����Ȃ����̂����菜��
			QList<int> keys;
			keys = FrontMultiIDError.keys(true);// �G���[�����Ȃ�
			for(int i=0; i<keys.count(); i++){
				FrontMultiIDError.remove(keys[i]);// ���菜��
			}
			keys = BackMultiIDError.keys(true);// �G���[�����Ȃ�
			for(int i=0; i<keys.count(); i++){
				BackMultiIDError.remove(keys[i]);// ���菜��
			}
			}

			// �����{�[�h�v�㌋��
			ui.twBoardCount->setItem(0, 0, new QTableWidgetItem(QString::number(FrontOKCount)));
			ui.twBoardCount->setItem(1, 0, new QTableWidgetItem(QString::number(FrontNGCount)));
			ui.twBoardCount->setItem(2, 0, new QTableWidgetItem(QString::number(FrontOKCount+FrontNGCount)));
			ui.twBoardCount->setItem(0, 1, new QTableWidgetItem(QString::number(BackOKCount)));
			ui.twBoardCount->setItem(1, 1, new QTableWidgetItem(QString::number(BackNGCount)));
			ui.twBoardCount->setItem(2, 1, new QTableWidgetItem(QString::number(BackOKCount+BackNGCount)));
			
			// ���炩�̃G���[���������ꍇ
			if(/*MultiErrorInspectIDList.isEmpty()==false	|| NoExistErrorInspectIDList.empty()==false ||*/
				FrontMultiIDError.isEmpty()==false		|| FrontNoExistError.isEmpty()==false ||
				BackMultiIDError.isEmpty()==false		|| BackNoExistError.isEmpty()==false){

				ui.twBoardCount->setColumnCount(2);
				QStringList list;
				list << /**/"Front" << /**/"Back";
				ui.twBoardCount->setHorizontalHeaderLabels(list);

				// �����{�[�h�v�㌋��
				ui.twBoardCount->setItem(0, 0, new QTableWidgetItem(QString::number(FrontOKCount)));
				ui.twBoardCount->setItem(1, 0, new QTableWidgetItem(QString::number(FrontNGCount)));
				ui.twBoardCount->setItem(2, 0, new QTableWidgetItem(QString::number(FrontOKCount+FrontNGCount)));
				ui.twBoardCount->setItem(0, 1, new QTableWidgetItem(QString::number(BackOKCount)));
				ui.twBoardCount->setItem(1, 1, new QTableWidgetItem(QString::number(BackNGCount)));
				ui.twBoardCount->setItem(2, 1, new QTableWidgetItem(QString::number(BackOKCount+BackNGCount)));

				if(FrontMultiIDError.isEmpty()==false || FrontNoExistError.isEmpty()==false){
					ui.twFrontError->setRowCount(FrontMultiIDError.count() + FrontNoExistError.count());
					QList<int> keyList = FrontMultiIDError.keys();
					std::sort(keyList.begin(), keyList.end());
					int row=0;
					for(int i=0; i<keyList.count(); i++,row++){
						ui.twFrontError->setItem(row, 0, new QTableWidgetItem(QString::number(keyList[i])));
						ui.twFrontError->setItem(row, 1, new QTableWidgetItem(LangSolver.GetString(HistoryListErrorDialog_LS,LID_0)/*"Multi ID"*/));
					}
					std::sort(FrontNoExistError.begin(), FrontNoExistError.end());
					for(int i=0; i<FrontNoExistError.count(); i++,row++){
						ui.twFrontError->setItem(row, 0, new QTableWidgetItem(QString::number(FrontNoExistError[i])));
						ui.twFrontError->setItem(row, 1, new QTableWidgetItem(LangSolver.GetString(HistoryListErrorDialog_LS,LID_1)/*"No ID"*/));
					}
					ui.twFrontError->setVisible(true);
				}else{
					ui.twFrontError->setVisible(false);
				}

				if(BackMultiIDError.isEmpty()==false || BackNoExistError.isEmpty()==false){
					ui.twBackError->setRowCount(BackMultiIDError.count() + BackNoExistError.count());
					QList<int> keyList = BackMultiIDError.keys();
					std::sort(keyList.begin(), keyList.end());
					int row=0;
					for(int i=0; i<keyList.count(); i++,row++){
						ui.twBackError->setItem(row, 0, new QTableWidgetItem(QString::number(keyList[i])));
						ui.twBackError->setItem(row, 1, new QTableWidgetItem(LangSolver.GetString(HistoryListErrorDialog_LS,LID_2)/*"Multi ID"*/));
					}
					std::sort(BackNoExistError.begin(), BackNoExistError.end());
					for(int i=0; i<BackNoExistError.count(); i++,row++){
						ui.twBackError->setItem(row, 0, new QTableWidgetItem(QString::number(BackNoExistError[i])));
						ui.twBackError->setItem(row, 1, new QTableWidgetItem(LangSolver.GetString(HistoryListErrorDialog_LS,LID_3)/*"No ID"*/));
					}
					ui.twBackError->setVisible(true);
				}else{
					ui.twBackError->setVisible(false);
				}
			}else{
				ui.twFrontError->setRowCount(0);
				ui.twBackError->setRowCount(0);
				ui.twFrontError->setVisible(false);
				ui.twBackError->setVisible(false);
			}
		}else if(oside==Review::OrganizedSideType::FrontOnly){// �\�̂�
			// �G���[�`�F�b�N
			// ����ID�̔��сA�d��������
			QHash<int,bool> FrontMultiIDError;
			QList<int> FrontNoExistError;// �\���̂Ȃ�ID
			int FrontOKCount=0;
			int FrontNGCount=0;

			for(int i=0; i<listPtr->count(); i++){
				if(listPtr->at(i).hasFront()==false){
					FrontNoExistError.append(listPtr->at(i).getInspectID());
				}else{
					if(FrontMultiIDError.contains(listPtr->at(i).getInspectID())==true){
						FrontMultiIDError[listPtr->at(i).getInspectID()] = false;
					}else{
						FrontMultiIDError.insert(listPtr->at(i).getInspectID(), true);
					}
					if(listPtr->at(i).getFront()->isOK()){
						FrontOKCount++;
					}else{
						FrontNGCount++;
					}
				}
			}

			{

			QList<int> keys;
			keys = FrontMultiIDError.keys(true);
			for(int i=0; i<keys.count(); i++){
				FrontMultiIDError.remove(keys[i]);
			}
			}


			ui.twBoardCount->setItem(0, 0, new QTableWidgetItem(QString::number(FrontOKCount)));
			ui.twBoardCount->setItem(1, 0, new QTableWidgetItem(QString::number(FrontNGCount)));
			ui.twBoardCount->setItem(2, 0, new QTableWidgetItem(QString::number(FrontOKCount+FrontNGCount)));
			
			if(/*MultiErrorInspectIDList.isEmpty()==false	|| NoExistErrorInspectIDList.empty()==false ||*/
				FrontMultiIDError.isEmpty()==false		|| FrontNoExistError.isEmpty()==false){

				ui.twBoardCount->setColumnCount(1);
				QStringList list;
				list << /**/"Front";
				ui.twBoardCount->setHorizontalHeaderLabels(list);

				ui.twBoardCount->setItem(0, 0, new QTableWidgetItem(QString::number(FrontOKCount)));
				ui.twBoardCount->setItem(1, 0, new QTableWidgetItem(QString::number(FrontNGCount)));
				ui.twBoardCount->setItem(2, 0, new QTableWidgetItem(QString::number(FrontOKCount+FrontNGCount)));

				if(FrontMultiIDError.isEmpty()==false || FrontNoExistError.isEmpty()==false){
					ui.twFrontError->setRowCount(FrontMultiIDError.count() + FrontNoExistError.count());
					QList<int> keyList = FrontMultiIDError.keys();
					std::sort(keyList.begin(), keyList.end());
					int row=0;
					for(int i=0; i<keyList.count(); i++,row++){
						ui.twFrontError->setItem(row, 0, new QTableWidgetItem(QString::number(keyList[i])));
						ui.twFrontError->setItem(row, 1, new QTableWidgetItem(/**/"Multi ID"));
					}
					std::sort(FrontNoExistError.begin(), FrontNoExistError.end());
					for(int i=0; i<FrontNoExistError.count(); i++,row++){
						ui.twFrontError->setItem(row, 0, new QTableWidgetItem(QString::number(FrontNoExistError[i])));
						ui.twFrontError->setItem(row, 1, new QTableWidgetItem(/**/"No ID"));
					}
					ui.twFrontError->setVisible(true);
				}else{
					ui.twFrontError->setVisible(false);
				}

				ui.twBackError->setVisible(false);

			}else{
				ui.twBoardCount->setItem(0, 0, new QTableWidgetItem(QString::number(0)));
				ui.twBoardCount->setItem(1, 0, new QTableWidgetItem(QString::number(0)));
				ui.twBoardCount->setItem(2, 0, new QTableWidgetItem(QString::number(0)));
				ui.twBoardCount->setItem(0, 1, new QTableWidgetItem(QString::number(0)));
				ui.twBoardCount->setItem(1, 1, new QTableWidgetItem(QString::number(0)));
				ui.twBoardCount->setItem(2, 1, new QTableWidgetItem(QString::number(0)));
				ui.twFrontError->setRowCount(0);
				ui.twBackError->setRowCount(0);
				ui.twFrontError->setVisible(false);
				ui.twBackError->setVisible(false);
			}
		}else{
			ui.twBoardCount->setItem(0, 0, new QTableWidgetItem(QString::number(0)));
			ui.twBoardCount->setItem(1, 0, new QTableWidgetItem(QString::number(0)));
			ui.twBoardCount->setItem(2, 0, new QTableWidgetItem(QString::number(0)));
			ui.twBoardCount->setItem(0, 1, new QTableWidgetItem(QString::number(0)));
			ui.twBoardCount->setItem(1, 1, new QTableWidgetItem(QString::number(0)));
			ui.twBoardCount->setItem(2, 1, new QTableWidgetItem(QString::number(0)));
			ui.twFrontError->setRowCount(0);
			ui.twBackError->setRowCount(0);
			ui.twFrontError->setVisible(false);
			ui.twBackError->setVisible(false);
		}
	}else{
		ui.twBoardCount->setItem(0, 0, new QTableWidgetItem(QString::number(0)));
		ui.twBoardCount->setItem(1, 0, new QTableWidgetItem(QString::number(0)));
		ui.twBoardCount->setItem(2, 0, new QTableWidgetItem(QString::number(0)));
		ui.twBoardCount->setItem(0, 1, new QTableWidgetItem(QString::number(0)));
		ui.twBoardCount->setItem(1, 1, new QTableWidgetItem(QString::number(0)));
		ui.twBoardCount->setItem(2, 1, new QTableWidgetItem(QString::number(0)));
		ui.twFrontError->setRowCount(0);
		ui.twBackError->setRowCount(0);
		ui.twFrontError->setVisible(false);
		ui.twBackError->setVisible(false);
	}
}

bool HistoryListErrorDialog::hasError()
{
	if(ui.twBoardCount->columnCount()==0)return false;
	for(int i=0; i<ui.twBoardCount->columnCount(); i++){
		if(ui.twBoardCount->item(2,0)==NULL){
			return false;
		}
	}

	bool ok;
	int num = ui.twBoardCount->item(2,0)->text().toInt(&ok);
	if(ok==false)return false;

	for(int i=1; i<ui.twBoardCount->columnCount(); i++){
		int nnum = ui.twBoardCount->item(2,i)->text().toInt(&ok);
		if(ok==false){
			return false;
		}
		if(num!=nnum){
			return true;
		}
	}
	if(ui.twFrontError->rowCount()!=0){
		return true;
	}
	if(ui.twBackError->rowCount()!=0){
		return true;
	}
	return false;
}