/*
 * Copyright (C) 2022
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

#include "ListStatisticNGResource.h"
#include <QFileDialog>

#include "ListStatisticNG.h"
#include "../XGUIReviewCommonPacket.h"
#include "XReviewStructure.h"
#include "ReviewStructurePacket.h"
#include "ReviewStructureItems.h"
#include "../XGUIReviewGlobal.h"
#include "XReviewCommonPacket.h"
#include "XReviewCommon.h"



static	char	*sRoot=/**/"Review";
static	char	*sName=/**/"ListStatisticNG";


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Export Functions
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show List for Static NG");
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ListStatisticNG(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);

	return true;
}

DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<12)
		return(-1);

	for(int i=0; i<12; i++){
		Data[i].Type = /**/"QString";
		Data[i].VariableNameWithRoute = QString(/**/"NameOfF%1").arg(i+1);
		Data[i].Pointer = ((ListStatisticNG *)Instance)->getFKeyDefinedNamesPtr(i);
	}

	return(12);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ListStatisticNG.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ListStatisticNG
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ListStatisticNG::ListStatisticNG(LayersBase *Base,QWidget *parent)
	:GUIFormBase(Base, parent),m_FKeyDefinedNames()
{
	initFKeyDefinedNames();

	ui.setupUi(this);
	QStringList vHeader, hHeader;
	vHeader << /**/"Borad Front" << /**/"Board Back" << /**/"NG Cnt Front" << /**/"NG Cnt Back";
	hHeader << /**/"F1" << /**/"F2" << /**/"F3" << /**/"F4" << /**/"F5" << /**/"F6" << /**/"F7" << /**/"F8" << /**/"F9" << /**/"F10" << /**/"F11" << /**/"F12" << /**/"NG" << /**/"OK";

	ui.tblMain->setVerticalHeaderLabels(vHeader);
	ui.tblMain->setHorizontalHeaderLabels(hHeader);

	ui.tblMain->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);	// �c�����w�b�_�[�����ϓ��̕��ŐL�k�\��������
	ui.tblMain->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

	connect(this, SIGNAL(SignalResize()), SLOT(ResizeAction()));

	initProperty();
}

ListStatisticNG::~ListStatisticNG()
{

}

void ListStatisticNG::initFKeyDefinedNames()
{
	m_FKeyDefinedNames = QVector<QString>(14).toList();
	for(int i=0; i<m_FKeyDefinedNames.count()-2; i++){
		m_FKeyDefinedNames[i] = QString(/**/"F%1").arg(i+1);
	}
	m_FKeyDefinedNames[m_FKeyDefinedNames.count()-2] = /**/"NG";
	m_FKeyDefinedNames.last() = /**/"OK";
}

void ListStatisticNG::Prepare(void)
{
	QStringList hHeader = getFKeyDefinedNames();
	ui.tblMain->setHorizontalHeaderLabels(hHeader);
	for(int column=0; column<hHeader.count(); column++){
		ui.tblMain->setColumnHidden(column, hHeader[column].isEmpty());
	}
}

void ListStatisticNG::TransmitDirectly(GUIDirectMessage *packet)
{
	GUICmdReviewUpdateLocal *GUICmdReviewUpdateLocalVar = dynamic_cast<GUICmdReviewUpdateLocal *>(packet);
	if(GUICmdReviewUpdateLocalVar!=NULL){
		updateGUI();
		GUICmdReviewUpdateLocalVar->Ret = true;
		return;
	}

	ReviewCommonPacket::CmdReqSettingPropertyDialog *CmdReqSettingPropertyDialogVar = dynamic_cast<ReviewCommonPacket::CmdReqSettingPropertyDialog *>(packet);
	if(CmdReqSettingPropertyDialogVar!=NULL){
		//CmdReqSettingPropertyDialogVar->dialog = getPropertyDialog();
		CmdReqSettingPropertyDialogVar->setDialog(NULL);
		CmdReqSettingPropertyDialogVar->setGroupName(ReviewGUI::PropertyGroupName::Global);
		CmdReqSettingPropertyDialogVar->setGUIName(ReviewGUI::Name::ListStatisticNG);
		return;
	}
}

void ListStatisticNG::updateGUI()
{
	ReviewPIBase *RBase = GetReviewAlgorithm();
	if(RBase!=NULL){
		// ������
		int FrontOKBoard = 0;				// OK�ɑ���������
		int BackOKBoard = 0;

		QVector<int> FrontBoardWithFKeyList(13, 0);	// F[i-1]�L�[�̊��� + F�L�[�Ȃ�
		QVector<int> FrontNGWithFKeyList(13, 0);	// F[i-1]�L�[�ɑ�����NG�̍��v�l + F�L�[�Ȃ�
		QVector<int> BackBoardWithFKeyList(13, 0);	// F[i-1]�L�[�̊��� + F�L�[�Ȃ�
		QVector<int> BackNGWithFKeyList(13, 0);		// F[i-1]�L�[�ɑ�����NG�̍��v�l + F�L�[�Ȃ�
		
		// �v��
		CmdReqOrganizedHistoryList Send(GetLayersBase());
		RBase->TransmitDirectly(&Send);
		if(Send.Ret==true){
			foreach(OrganizedHistoryItem ohItem, *Send.listPtr){// �������[�v
				if(ohItem.hasFront()==true){
					// �\���̊������ǉ�

					if(ohItem.getFront()->NGCount==0){
						FrontOKBoard++;
						continue;
					}

					QList<int> perNail, perNG;
					Review::FKey key = ohItem.getFront()->getFKeyInfo(perNail, perNG);
					FrontBoardWithFKeyList[Review::FKeyToInt(key)] += 1;
					for(int i=0; i<perNG.count(); i++){
						FrontNGWithFKeyList[i] += perNG[i];
					}

					//QList<int> OneBoardFKeyList;// 
					//Review::FKey BoardFKeyType = ohItem.getFront()->getFKeyInfo(OneBoardFKeyList); // ������������F�L�[�^�C�v(��������NG�������ԑ���F�L�[�^�C�v)
					//if(BoardFKeyType!=Review::NoFKey){
					//	for(int i=0; i<OneBoardFKeyList.count(); i++){
					//		FrontNGWithFKeyList[i] += OneBoardFKeyList[i]; // NG�����Z
					//	}
					//}else{
					//	FrontOKBoard++;// OK�����C���N�������g
					//}
				}
				if(ohItem.getBack()!=NULL){
					// �����̊������ǉ�
					
					if(ohItem.getBack()->NGCount==0){
						BackOKBoard++;
						continue;
					}

					QList<int> perNail, perNG;
					Review::FKey key = ohItem.getBack()->getFKeyInfo(perNail, perNG);
					BackBoardWithFKeyList[Review::FKeyToInt(key)] += 1;
					for(int i=0; i<perNG.count(); i++){
						BackNGWithFKeyList[i] += perNG[i];
					}

					//QList<int> OneBoardFKeyList;
					//Review::FKey BoardFKeyType = ohItem.getBack()->getFKeyInfo(OneBoardFKeyList); // ������������F�L�[�^�C�v(��������NG�������ԑ���F�L�[�^�C�v)
					//BackBoardWithFKeyList[Review::FKeyToInt(BoardFKeyType)] += 1;
					//if(BoardFKeyType!=Review::NoFKey){
					//	for(int i=0; i<OneBoardFKeyList.count(); i++){
					//		BackNGWithFKeyList[i] += OneBoardFKeyList[i]; // NG�����Z
					//	}
					//}else{
					//	BackOKBoard++;// OK�����C���N�������g
					//}
				}
			}
		}

		int row=0, column=0;
		// "���� �\"
		for(column=0; column<ui.tblMain->columnCount()-1; column++){
			ui.tblMain->setItem(row, column, new QTableWidgetItem(QString::number(FrontBoardWithFKeyList[column])));
		}
		ui.tblMain->setItem(row, column, new QTableWidgetItem(QString::number(FrontOKBoard)));

		row++;

		// "���� ��"
		for(column=0; column<ui.tblMain->columnCount()-1; column++){
			ui.tblMain->setItem(row, column, new QTableWidgetItem(QString::number(BackBoardWithFKeyList[column])));
		}
		ui.tblMain->setItem(row, column, new QTableWidgetItem(QString::number(BackOKBoard)));

		row++;

		// "NG�� �\"
		for(column=0; column<ui.tblMain->columnCount()-1; column++){
			ui.tblMain->setItem(row, column, new QTableWidgetItem(QString::number(FrontNGWithFKeyList[column])));
		}
		ui.tblMain->setItem(row, column, new QTableWidgetItem(/**/" - "));

		row++;

		// "NG�� ��"
		for(column=0; column<ui.tblMain->columnCount()-1; column++){
			ui.tblMain->setItem(row, column, new QTableWidgetItem(QString::number(BackNGWithFKeyList[column])));
		}
		ui.tblMain->setItem(row, column, new QTableWidgetItem(/**/" - "));
	}
}

void ListStatisticNG::ResizeAction()
{
	ui.gridLayout->setGeometry( QRect(0, 0, width(), height()) );
}


void ListStatisticNG::on_pbShowDetail_clicked()
{
	QString errMsg;
	QTableWidget *table = createDetailTableWidget(&errMsg);

	if(table==NULL){
		QMessageBox::warning(this
							, LangSolver.GetString(ListStatisticNG_LS,LID_0)/*"Failuer to show detail table"*/
							, errMsg);
		return;
	}

	QDialog *dialog = new QDialog(this);

	QGridLayout *layout = new QGridLayout;
	layout->addWidget( table, 0, 0, 1, 1);

	dialog->setLayout( layout );

	table->horizontalHeader()->resizeSections(QHeaderView::ResizeMode::ResizeToContents);
	table->resizeColumnsToContents();

	dialog->setMinimumWidth( table->horizontalHeader()->width() );
	dialog->setMinimumHeight( table->verticalHeader()->defaultSectionSize() * 10 );

	dialog->setModal(false);
	dialog->exec();

	delete dialog;
}

void ListStatisticNG::on_pbSaveToFile_clicked()
{
	QTableWidget *table = createDetailTableWidget();
	if(table==NULL){
		QMessageBox::warning(this
							, LangSolver.GetString(ListStatisticNG_LS,LID_1)/*"Failuer"*/
							, LangSolver.GetString(ListStatisticNG_LS,LID_2)/*"No data in this current"*/);
		return;
	}
	
	Review::DeleteAtEnd<QTableWidget> delAtEnd(table);

	QString filename = QFileDialog::getSaveFileName(this
													,LangSolver.GetString(ListStatisticNG_LS,LID_3)/*"Save FKey State"*/
													, /**/""
													, /**/"csv format (*.csv)");

	if(filename.isEmpty()==true){
		return;
	}

	QFile file(filename);

	if(file.open(QIODevice::WriteOnly)==false){
		QMessageBox::warning(this
							, LangSolver.GetString(ListStatisticNG_LS,LID_4)/*"Save Error"*/
							, LangSolver.GetString(ListStatisticNG_LS,LID_5)/*"File was not opened."*/);
		return;
	}

	QTextStream stream( &file );

	QList<int> enableIndexList;
	QStringList hHeaderList;
	for(int i=0; i<table->horizontalHeader()->count(); i++){
		QString headerStr = table->horizontalHeaderItem(i)->text();
		if(headerStr.isEmpty()==false){
			hHeaderList << headerStr;
			enableIndexList << i;
		}
	}

	stream << hHeaderList.join(/**/",") << Qt::endl;

	for(int row=0; row<table->rowCount(); row++){
		QStringList lineItemList;
		for(int column=0; column<enableIndexList.count(); column++){
			lineItemList << table->item(row, enableIndexList[column])->text();
		}
		stream << lineItemList.join(/**/",") << Qt::endl;
	}
}

QTableWidget *ListStatisticNG::createDetailTableWidget(QString *errMsg)
{
	ReviewPIBase *RBase = GetReviewAlgorithm();
	if(RBase==NULL){
		if(errMsg!=NULL){
			*errMsg = /**/"Review algorithm was not found.";
		}
		return NULL;
	}

	CmdReqMasterDataInfo reqMInfo(GetLayersBase());
	RBase->TransmitDirectly( &reqMInfo );

	if(reqMInfo.Ret==false){
		if(errMsg!=NULL){
			*errMsg = /**/"Failuer to get master infomation from review algorithm.";
		}
		return NULL;
	}

	CmdReqOrganizedHistoryList reqOrgHistList(GetLayersBase());
	RBase->TransmitDirectly( &reqOrgHistList );

	if(reqOrgHistList.Ret==false || reqOrgHistList.listPtr==NULL){
		if(errMsg!=NULL){
			*errMsg = /**/"Failuer to load history data from review algorithm.";
		}
		return NULL;
	}

	if(reqOrgHistList.listPtr->isEmpty()==true){
		if(errMsg!=NULL){
			*errMsg = /**/"Hisroty is empty.";
		}
		return NULL;
	}

	Review::OrganizedSideType type = Review::OrganizedSideType::None;
	
	if(reqMInfo.getInfo(Review::Front).isEmpty()==false){
		type = Review::OrganizedSideType::FrontOnly;
	}
	
	if(reqMInfo.getInfo(Review::Front).isEmpty()==false){
		if(type==Review::OrganizedSideType::None){
			type = Review::OrganizedSideType::BackOnly;
		}else{
			type = Review::OrganizedSideType::Both;
		}
	}

	if(type==Review::OrganizedSideType::None){
		if(errMsg!=NULL){
			*errMsg = /**/"Master data is not loaded.\nFirst you must load master data.";
		}
		return NULL;
	}

	const OrganizedHistoryListPtr list = reqOrgHistList.listPtr;

	int rowCount = list->count();
	QStringList hHeader = getFKeyDefinedNames(true);// 12��
	hHeader.push_front(/**/"Inspect ID");// 13��
	hHeader.push_back(/**/"NoFKey");// 14��

	QTableWidget *table = new QTableWidget;
	table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::Stretch);
	table->horizontalHeader()->setStretchLastSection(true);
	table->setColumnCount(hHeader.count());// �\�݂̂̃J�E���g
	table->setHorizontalHeaderLabels(hHeader);
	table->verticalHeader()->setHidden(true);
	table->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);
	table->setSelectionMode(QAbstractItemView::SelectionMode::NoSelection);

	if(type==Review::OrganizedSideType::FrontOnly){
		QList<QList<QTableWidgetItem *> > tableItemTable;// �e�[�u���̃A�C�e��

		for(int row=0; row<list->count(); row++){
			// 1�s���̃A�C�e�����X�g����
			if(list->at(row).hasFront()==true && list->at(row).getFront()->isOK()==false){
				QList<QTableWidgetItem *> currentRowItemList;

				currentRowItemList << new QTableWidgetItem( QString(/**/"%1").arg(list->at(row).getFront()->InspectID()) );

				QList<int> perNail,perNG;

				list->at(row).getFront()->getFKeyInfo(perNail, perNG);

				for(int i=0; i<perNail.count(); i++){
					currentRowItemList << new QTableWidgetItem(QString::number(perNail[i]));
				}

				tableItemTable << currentRowItemList;
			}
		}

		table->setRowCount( tableItemTable.count() );

		for(int row=0; row<tableItemTable.count(); row++){
			for(int column=0; column<hHeader.count(); column++){
				table->setItem(row, column, tableItemTable[row][column]);
			}
		}
	}else if(type==Review::OrganizedSideType::BackOnly){
		QList<QList<QTableWidgetItem *> > tableItemTable;// �e�[�u���̃A�C�e��

		for(int row=0; row<list->count(); row++){
			// 1�s���̃A�C�e�����X�g����
			if(list->at(row).hasBack()==true && list->at(row).getBack()->isOK()==false){
				QList<QTableWidgetItem *> currentRowItemList;

				currentRowItemList << new QTableWidgetItem( QString(/**/"%1").arg(list->at(row).getBack()->InspectID()) );

				QList<int> perNail,perNG;

				list->at(row).getBack()->getFKeyInfo(perNail, perNG);

				for(int i=0; i<perNail.count(); i++){
					currentRowItemList << new QTableWidgetItem(QString::number(perNail[i]));
				}

				tableItemTable << currentRowItemList;
			}
		}

		table->setRowCount( tableItemTable.count() );

		for(int row=0; row<tableItemTable.count(); row++){
			for(int column=0; column<hHeader.count(); column++){
				table->setItem(row, column, tableItemTable[row][column]);
			}
		}
	}else if(type==Review::OrganizedSideType::Both){
		QList<QList<QTableWidgetItem *> > tableItemTable;// �e�[�u���̃A�C�e��

		for(int row=0; row<list->count(); row++){
			// �\���v�Z

			// 1�s���̃A�C�e�����X�g����
			if(list->at(row).hasFront()==true && list->at(row).getFront()->isOK()==false){
				QList<QTableWidgetItem *> currentRowItemList;

				currentRowItemList << new QTableWidgetItem( QString(/**/"%1(Front)").arg(list->at(row).getFront()->InspectID()) );

				QList<int> perNail,perNG;

				list->at(row).getFront()->getFKeyInfo(perNail, perNG);

				for(int i=0; i<perNail.count(); i++){
					currentRowItemList << new QTableWidgetItem(QString::number(perNail[i]));
				}

				tableItemTable << currentRowItemList;
			}
			
			// �����v�Z

			// 1�s���̃A�C�e�����X�g����
			if(list->at(row).hasBack()==true && list->at(row).getBack()->isOK()==false){
				QList<QTableWidgetItem *> currentRowItemList;

				currentRowItemList << new QTableWidgetItem( QString(/**/"%1(Back)").arg(list->at(row).getBack()->InspectID()) );

				QList<int> perNail,perNG;

				list->at(row).getBack()->getFKeyInfo(perNail, perNG);

				for(int i=0; i<perNail.count(); i++){
					currentRowItemList << new QTableWidgetItem(QString::number(perNail[i]));
				}

				tableItemTable << currentRowItemList;

				QStringList outList;
				for(int i=0; i<currentRowItemList.count(); i++){
					outList << currentRowItemList[i]->text();
				}
				//qDebug() << outList;
			}
		}

		table->setRowCount( tableItemTable.count() );

		for(int row=0; row<tableItemTable.count(); row++){
			for(int column=0; column<hHeader.count(); column++){
				table->setItem(row, column, tableItemTable[row][column]);
			}
		}
	}

	for(int column=0; column<hHeader.count(); column++){
		if(hHeader[column].isEmpty()==true){
			table->setColumnHidden(column, true);
		}
	}

	return table;
}