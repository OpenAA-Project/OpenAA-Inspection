#include "ShowHistoryListForReviewResource.h"
#include "HistoryListErrorDialog.h"
#include "ReviewStructureItems.h"

void HistoryListErrorDialog::setHistory(OrganizedHistoryListPtr listPtr, Review::OrganizedSideType oside)
{
	if(listPtr!=NULL && listPtr->isEmpty()==false){
		if(oside==Review::OrganizedSideType::Both){// 両面の場合
			// エラーチェック
			// 検査IDの飛び、重複を検索

			QHash<int,bool> FrontMultiIDError;
			QList<int> FrontNoExistError;// 表側のないID
			QHash<int,bool> BackMultiIDError;
			QList<int> BackNoExistError;// 裏側のないID
			int FrontOKCount=0;
			int FrontNGCount=0;
			int BackOKCount=0;
			int BackNGCount=0;

			for(int i=0; i<listPtr->count(); i++){
				if(listPtr->at(i).hasFront()==false){// 表検査履歴チェック
					FrontNoExistError.append(listPtr->at(i).getInspectID());// 検査履歴なし
				}else{
					if(FrontMultiIDError.contains(listPtr->at(i).getInspectID())==true){// 検査IDが複数存在している
						FrontMultiIDError[listPtr->at(i).getInspectID()] = false;
					}else{
						FrontMultiIDError.insert(listPtr->at(i).getInspectID(), true);// 通常はIDごとにここに一度だけ入る
					}
					if(listPtr->at(i).getFront()->isOK()){// OKかNGかで分岐、加算
						FrontOKCount++;
					}else{
						FrontNGCount++;
					}
				}
				if(listPtr->at(i).hasBack()==false){// 裏検査履歴チェック
					BackNoExistError.append(listPtr->at(i).getInspectID());// 検査履歴なし
				}else{
					if(BackMultiIDError.contains(listPtr->at(i).getInspectID())==true){// 検査IDが複数存在している
						BackMultiIDError[listPtr->at(i).getInspectID()] = false;
					}else{
						BackMultiIDError.insert(listPtr->at(i).getInspectID(), true);// 通常はIDごとにここに一度だけ入る
					}
					if(listPtr->at(i).getBack()->isOK()){// OKかNGかで分岐、加算
						BackOKCount++;
					}else{
						BackNGCount++;
					}
				}
			}

			{
			// エラーじゃないものを取り除く
			QList<int> keys;
			keys = FrontMultiIDError.keys(true);// エラーじゃない
			for(int i=0; i<keys.count(); i++){
				FrontMultiIDError.remove(keys[i]);// 取り除き
			}
			keys = BackMultiIDError.keys(true);// エラーじゃない
			for(int i=0; i<keys.count(); i++){
				BackMultiIDError.remove(keys[i]);// 取り除き
			}
			}

			// 検査ボード計上結果
			ui.twBoardCount->setItem(0, 0, new QTableWidgetItem(QString::number(FrontOKCount)));
			ui.twBoardCount->setItem(1, 0, new QTableWidgetItem(QString::number(FrontNGCount)));
			ui.twBoardCount->setItem(2, 0, new QTableWidgetItem(QString::number(FrontOKCount+FrontNGCount)));
			ui.twBoardCount->setItem(0, 1, new QTableWidgetItem(QString::number(BackOKCount)));
			ui.twBoardCount->setItem(1, 1, new QTableWidgetItem(QString::number(BackNGCount)));
			ui.twBoardCount->setItem(2, 1, new QTableWidgetItem(QString::number(BackOKCount+BackNGCount)));
			
			// 何らかのエラーがあった場合
			if(/*MultiErrorInspectIDList.isEmpty()==false	|| NoExistErrorInspectIDList.empty()==false ||*/
				FrontMultiIDError.isEmpty()==false		|| FrontNoExistError.isEmpty()==false ||
				BackMultiIDError.isEmpty()==false		|| BackNoExistError.isEmpty()==false){

				ui.twBoardCount->setColumnCount(2);
				QStringList list;
				list << /**/"Front" << /**/"Back";
				ui.twBoardCount->setHorizontalHeaderLabels(list);

				// 検査ボード計上結果
				ui.twBoardCount->setItem(0, 0, new QTableWidgetItem(QString::number(FrontOKCount)));
				ui.twBoardCount->setItem(1, 0, new QTableWidgetItem(QString::number(FrontNGCount)));
				ui.twBoardCount->setItem(2, 0, new QTableWidgetItem(QString::number(FrontOKCount+FrontNGCount)));
				ui.twBoardCount->setItem(0, 1, new QTableWidgetItem(QString::number(BackOKCount)));
				ui.twBoardCount->setItem(1, 1, new QTableWidgetItem(QString::number(BackNGCount)));
				ui.twBoardCount->setItem(2, 1, new QTableWidgetItem(QString::number(BackOKCount+BackNGCount)));

				if(FrontMultiIDError.isEmpty()==false || FrontNoExistError.isEmpty()==false){
					ui.twFrontError->setRowCount(FrontMultiIDError.count() + FrontNoExistError.count());// 行数の調整
					QList<int> keyList = FrontMultiIDError.keys();// キーの取得
					qSort(keyList);// IDを昇順に並べ替え
					int row=0;
					for(int i=0; i<keyList.count(); i++,row++){
						ui.twFrontError->setItem(row, 0, new QTableWidgetItem(QString::number(keyList[i])));
						ui.twFrontError->setItem(row, 1, new QTableWidgetItem(LangSolver.GetString(HistoryListErrorDialog_LS,LID_0)/*"Multi ID"*/));
					}
					qSort(FrontNoExistError);// IDを昇順に並べ替え
					for(int i=0; i<FrontNoExistError.count(); i++,row++){
						ui.twFrontError->setItem(row, 0, new QTableWidgetItem(QString::number(FrontNoExistError[i])));
						ui.twFrontError->setItem(row, 1, new QTableWidgetItem(LangSolver.GetString(HistoryListErrorDialog_LS,LID_1)/*"No ID"*/));
					}
					ui.twFrontError->setVisible(true);
				}else{
					ui.twFrontError->setVisible(false);
				}

				if(BackMultiIDError.isEmpty()==false || BackNoExistError.isEmpty()==false){
					ui.twBackError->setRowCount(BackMultiIDError.count() + BackNoExistError.count());// 行数の調整
					QList<int> keyList = BackMultiIDError.keys();// キーの取得
					qSort(keyList);// IDを昇順に並べ替え
					int row=0;
					for(int i=0; i<keyList.count(); i++,row++){
						ui.twBackError->setItem(row, 0, new QTableWidgetItem(QString::number(keyList[i])));
						ui.twBackError->setItem(row, 1, new QTableWidgetItem(LangSolver.GetString(HistoryListErrorDialog_LS,LID_2)/*"Multi ID"*/));
					}
					qSort(BackNoExistError);// IDを昇順に並べ替え
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
		}else if(oside==Review::OrganizedSideType::FrontOnly){// 表のみ
			// エラーチェック
			// 検査IDの飛び、重複を検索
			QHash<int,bool> FrontMultiIDError;
			QList<int> FrontNoExistError;// 表側のないID
			int FrontOKCount=0;
			int FrontNGCount=0;

			for(int i=0; i<listPtr->count(); i++){
				if(listPtr->at(i).hasFront()==false){// 表検査履歴チェック
					FrontNoExistError.append(listPtr->at(i).getInspectID());// 検査履歴なし
				}else{
					if(FrontMultiIDError.contains(listPtr->at(i).getInspectID())==true){// 検査IDが複数存在している
						FrontMultiIDError[listPtr->at(i).getInspectID()] = false;
					}else{
						FrontMultiIDError.insert(listPtr->at(i).getInspectID(), true);// 通常はIDごとにここに一度だけ入る
					}
					if(listPtr->at(i).getFront()->isOK()){// OKかNGかで分岐、加算
						FrontOKCount++;
					}else{
						FrontNGCount++;
					}
				}
			}

			{
			// エラーじゃないものを取り除く
			QList<int> keys;
			keys = FrontMultiIDError.keys(true);// エラーじゃない
			for(int i=0; i<keys.count(); i++){
				FrontMultiIDError.remove(keys[i]);// 取り除き
			}
			}

			// 検査ボード計上結果
			ui.twBoardCount->setItem(0, 0, new QTableWidgetItem(QString::number(FrontOKCount)));
			ui.twBoardCount->setItem(1, 0, new QTableWidgetItem(QString::number(FrontNGCount)));
			ui.twBoardCount->setItem(2, 0, new QTableWidgetItem(QString::number(FrontOKCount+FrontNGCount)));
			
			// 何らかのエラーがあった場合
			if(/*MultiErrorInspectIDList.isEmpty()==false	|| NoExistErrorInspectIDList.empty()==false ||*/
				FrontMultiIDError.isEmpty()==false		|| FrontNoExistError.isEmpty()==false){

				ui.twBoardCount->setColumnCount(1);
				QStringList list;
				list << /**/"Front";
				ui.twBoardCount->setHorizontalHeaderLabels(list);

				// 検査ボード計上結果
				ui.twBoardCount->setItem(0, 0, new QTableWidgetItem(QString::number(FrontOKCount)));
				ui.twBoardCount->setItem(1, 0, new QTableWidgetItem(QString::number(FrontNGCount)));
				ui.twBoardCount->setItem(2, 0, new QTableWidgetItem(QString::number(FrontOKCount+FrontNGCount)));

				if(FrontMultiIDError.isEmpty()==false || FrontNoExistError.isEmpty()==false){
					ui.twFrontError->setRowCount(FrontMultiIDError.count() + FrontNoExistError.count());// 行数の調整
					QList<int> keyList = FrontMultiIDError.keys();// キーの取得
					qSort(keyList);// IDを昇順に並べ替え
					int row=0;
					for(int i=0; i<keyList.count(); i++,row++){
						ui.twFrontError->setItem(row, 0, new QTableWidgetItem(QString::number(keyList[i])));
						ui.twFrontError->setItem(row, 1, new QTableWidgetItem(/**/"Multi ID"));
					}
					qSort(FrontNoExistError);// IDを昇順に並べ替え
					for(int i=0; i<FrontNoExistError.count(); i++,row++){
						ui.twFrontError->setItem(row, 0, new QTableWidgetItem(QString::number(FrontNoExistError[i])));
						ui.twFrontError->setItem(row, 1, new QTableWidgetItem(/**/"No ID"));
					}
					ui.twFrontError->setVisible(true);
				}else{
					ui.twFrontError->setVisible(false);
				}

				ui.twBackError->setVisible(false);

			}else{// 裏のみ、読み込み無しは設定なし
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