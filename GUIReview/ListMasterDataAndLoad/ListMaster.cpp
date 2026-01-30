/*
 * Copyright (C) 2023
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

#include "ListMasterDataAndLoadResource.h"
#include "ListMaster.h"
#include "XDataInLayer.h"
#include "XReviewStructure.h"
#include "XDataAlgorithm.h"
#include "XGeneralFunc.h"

#include "LoadMasterDataWindow.h"
#include "ListMasterDataAndLoadPacket.h"

#include "XGeneralDialog.h"
#include "XGUI.h"

#include "..\XGUICmdReviewCommon.h"

#include "XReviewStructure.h"
#include "ReviewStructurePacket.h"
#include "../SelectLotForReview/SelectLotForReviewPacket.h"
#include "../WholeImageForReview/WholeImageForReview.h"

#include "../WholeImageForReview/WholeImageForReviewPacket.h"
#include "XSequenceRepairLocal.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QScrollBar>

extern	char	*sRoot;
extern	char	*sName;

class ListMasterForm::ListMasterLocker : public GUILockerBase
{
public:
	ListMasterLocker(Ui::ListMasterFormClass *_ui, QWidget *updateWidget=NULL){
		ui = _ui;
		stack++;
		if(updateWidget!=NULL){
			updateWidget->update();
			qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
		}
		setGUIEnable(false);
	};
	~ListMasterLocker(){
		stack--;
		if(stack==0){
			setGUIEnable(true);
		}
	};
public:
	void setGUIEnable(bool enable){
		if(ui!=NULL){
			ui->pbSelect->setEnabled(enable);
			ui->pushButtonOpneInDetail->setEnabled(enable);
			ui->tbDataTable->setEnabled(enable);
			//ui->pbUpdate->setEnabled(enable);
		}
	};

private:
	Ui::ListMasterFormClass *ui;

	static int stack;
};

int ListMasterForm::ListMasterLocker::stack = 0;


ListMasterForm::ListMasterForm(LayersBase *Base ,QWidget *parent)
	: GUIFormBase(Base,parent)
{
	ui.setupUi(this);
	setFrameStyle(QFrame::WinPanel | QFrame::Raised);
	setLineWidth(2);
	LangSolver.SetUI(this);
	
	WidthID		=48;
	WidthName	=100;
	WidthLatest	=100;
	SameWidth	=true;

	ListMasterLocker locker(&ui);

	// �e�[�u����
	//MasterTableName = /**/"MASTERDATA";

	// �f�[�^�x�[�X�̖��O�ƕ\�����x���̑Ή�
	hHeaderRaw	<< /**/"MASTERCODE" << /**/"MASTERNAME" << /**/"LASTEDITTIME";
	hHeaderView	<< LangSolver.GetString(ListMaster_LS,LID_0)/*"ID"*/			<< LangSolver.GetString(ListMaster_LS,LID_1)/*"Name"*/		<< LangSolver.GetString(ListMaster_LS,LID_2)/*"LatestEdition"*/;

	// �I�����[�h�̐ݒ�
	ui.tbDataTable->setSelectionMode(QAbstractItemView::SingleSelection);
	ui.tbDataTable->setSelectionBehavior(QAbstractItemView::SelectRows);

	ui.tbDataTable->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	
	// �\��
	if(GetEditMode()==false){
		ShowList();

		connect(ui.pushButtonOpneInDetail, SIGNAL(clicked()), this, SLOT(ShowLoadMasterDataWindow()));
		connect(ui.tbDataTable, SIGNAL(doubleClicked(const QModelIndex &)), this, SLOT(SlotDoubleClicked(const QModelIndex &)));
		connect(ui.pbSelect, SIGNAL(clicked()), this, SLOT(SlotSelectButtonClicked()));
	}
}

void	ListMasterForm::Prepare(void)
{
	if(SameWidth==false){
		ui.tbDataTable	->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::Fixed);
		ui.tbDataTable	->setColumnWidth(0,WidthID);
		ui.tbDataTable	->setColumnWidth(1,WidthName);
		ui.tbDataTable	->setColumnWidth(2,WidthLatest);
	}
}
void ListMasterForm::SlotSelectButtonClicked()
{
	if(ui.tbDataTable->currentItem()!=NULL){
		ListMasterLocker locker(&ui, this);
		qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
		SlotDoubleClicked(ui.tbDataTable->currentIndex());
	}
}

void ListMasterForm::SlotUpdateButtonClicked()
{
	ListMasterLocker locker(&ui, this);
	qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
	ShowList();
}

bool ListMasterForm::LoadMasterData(int SelectedMasterCode)
{
	SeqControlParam	*Param=NULL;
	if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL){
		Param=(SeqControlParam *)GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetSeqParam();
		if(Param!=NULL){
			Param	->MasterID	=SelectedMasterCode;
		}
	}

	GetLayersBase()->SetMasterCode(SelectedMasterCode);
	ListMasterLocker locker(&ui, this);
	ReviewPIBase *RBase = GetReviewAlgorithm();

	CmdLoadMaster cmdLoadMaster(GetLayersBase());
	cmdLoadMaster.MasterCode = SelectedMasterCode;
	RBase->TransmitDirectly( &cmdLoadMaster );

	GUIFormBase *WForm = GetLayersBase()->FindByName(ReviewGUI::Name::Root, ReviewGUI::Name::WholeImageForReview, /**/"");

	if(WForm!=NULL){
		GUICmdLoadMasterImage WholeMLoadCmd(GetLayersBase());

		WholeMLoadCmd.side = Review::Front;
		WForm->TransmitDirectly(&WholeMLoadCmd);

		WholeMLoadCmd.side = Review::Back;
		WForm->TransmitDirectly(&WholeMLoadCmd);
	}

	ReviewGUI::ReviewGUIAllUpdate(GetLayersBase(), true);

	GUIFormBase *NGLForm = GetLayersBase()->FindByName(ReviewGUI::Name::Root, ReviewGUI::Name::NGImageListForReview, /**/"");
	if(NGLForm!=NULL){
		GUICmdSetFocus SetFocusCmd(GetLayersBase());

		NGLForm->TransmitDirectly(&SetFocusCmd);
	}else{
		GUIFormBase *TForm = GetLayersBase()->FindByName(ReviewGUI::Name::Root, ReviewGUI::Name::ShowThumbnail,/**/"");
		if(TForm!=NULL){
			GUICmdSetFocus SetFocusCmd(GetLayersBase());
			TForm->TransmitDirectly(&SetFocusCmd);
		}
	}
	
	ReviewGUI::UpdateGUI(GetLayersBase(), ReviewGUI::Name::WholeImageForReview);

	ExecuteInitialAfterEditInfo EInfo;
	GetLayersBase()->ExecuteInitialAfterEdit(EInfo);
	#ifdef _MSC_VER
	_CrtCheckMemory();
	#endif
	
	BroadcastDirectly(_BC_BuildForShow,GetLayersBase()->GetCurrentInspectIDForDisplay());

	GetLayersBase()->CloseInformed();

	return true;
}

void ListMasterForm::ShowList()
{
	if(GetEditMode()==true)return;

	ListMasterLocker locker(&ui);
	ui.tbDataTable->setRowCount(0);
	ui.tbDataTable->setColumnCount(hHeaderView.count());
	QSqlQuery query( GetLayersBase()->GetDatabase() );
	if(query.exec(/**/"select MACHINEID from MACHINE ORDER BY MACHINEID")==false){
		while(query.next()){
			int id = query.record().value(0).toInt();
			if(MachineIDFilter.contains(id)==false){
				MachineIDFilter.removeAll(id);
			}
		}
	}

	if(MachineIDFilter.isEmpty()==true){
		if(query.exec(/**/"SELECT MASTERCODE,MASTERNAME,LASTEDITTIME FROM MASTERDATA ORDER BY MASTERCODE")==false){
			return;
		}
	}else{
		QStringList MachineOrderList;
		for(int i=0; i<MachineIDFilter.count(); i++){
			MachineOrderList << QString(/**/"MACHINEID=%1").arg(MachineIDFilter[i]);
		}
		QString filterStr = MachineOrderList.join(/**/" OR ");
		QString queryStr = QString(/**/"SELECT MASTERCODE,MASTERNAME,LASTEDITTIME FROM MASTERDATA WHERE %1 ORDER BY MASTERCODE").arg(filterStr);
		if(query.exec(queryStr)==false){
			return;
		}
	}

	ui.tbDataTable->setHorizontalHeaderLabels(hHeaderView);

	for(int row=0; query.next(); row++){
		ui.tbDataTable->insertRow(row);
		QStringList list;
		QList<QPoint> pList;
		for(int i=0; i<hHeaderRaw.count(); i++){
			QString currentStr = hHeaderRaw[i];
			int recordIndex = query.record().indexOf(currentStr);
			QString viewTable = query.value(recordIndex).toString();

			QTableWidgetItem *item = new QTableWidgetItem();
			item->setText(viewTable);
			ui.tbDataTable->setItem(row, i, item);

			pList << QPoint(row, i);
			list << viewTable;
		}
		//qDebug() << pList;
		//qDebug() << list;
	}
	
	ui.tbDataTable->verticalHeader()->setHidden(true);
	//ui.tbDataTable->sortByColumn(0, Qt::SortOrder::DescendingOrder);
}

void ListMasterForm::SlotDoubleClicked(const QModelIndex &index)
{
	ListMasterLocker locker(&ui, this);
	int MasterCode = ui.tbDataTable->item(index.row(), 0)->text().toInt();// �}�X�^�[�R�[�h

	// �}�X�^�[�f�[�^�̓ǂݍ���
	LoadMasterData(MasterCode);

	// �ǂݍ��񂾃}�X�^�[�R�[�h�փJ�����g�Z�����ړ�
	MoveCellToMasterCode(MasterCode);

	GUICmdLoadMasterImage Cmd(GetLayersBase());
	Cmd.side = Review::Front;
	ReviewGUI::ReviewGUICmdSend(GetLayersBase(), &Cmd, ReviewGUI::Name::WholeImageForReview);
	Cmd.side = Review::Back;
	ReviewGUI::ReviewGUICmdSend(GetLayersBase(), &Cmd, ReviewGUI::Name::WholeImageForReview);
}

void ListMasterForm::ShowSelectLot(int MasterCode, int MachineID, Review::SideType side)
{
	ListMasterLocker locker(&ui);
	// �A���S���Y���Ƀ}�X�^�[�R�[�h�ɊY�����郍�b�g�̈ꗗ���v��
	ReviewPIBase *Base = GetReviewAlgorithm();
	CmdServerSelectLotList Send(GetLayersBase());

	Send.MasterCode = MasterCode;
	Send.MachineID = MachineID;
	
	Base->TransmitDirectly(&Send);

	if(Send.Ret==false){
		return;
	}
	if(Send.list.count()==0)return;

	// ���b�g��(�t�@�C����)�𔲂��o��
	GUICmdReviewLotList GUISend(GetLayersBase());
	GUISend.lotList = Send.list;

	// �}�X�^�[�R�[�h�A�}�V��ID�Ɨ��\���Z�b�g
	GUISend.MasterCode = MasterCode;
	GUISend.MachineID = MachineID;
	GUISend.side = side;

	// SelectLotForReview��GUI�������A�����΂����ɏ����𑗐M�B�Ȃ�����GUI��DLL���璼�ڋN���BDLL���������΂����ŏI���B
	GUIFormBase *TagGUI = GetLayersBase()->FindByName(ReviewGUI::Name::Root, ReviewGUI::Name::SelectLotForReview, /**/"");
	if(TagGUI!=NULL){
		TagGUI->TransmitDirectly(&GUISend);
	}else{
	}
}

void ListMasterForm::ShowSelectLot()
{
	ReviewPIBase *RBase = GetReviewAlgorithm();
	if(RBase==NULL)return;

	GUIFormBase *Base = GetReviewGUIForm(ReviewGUI::Name::SelectLotForReview);
	if(Base==NULL)return;

	CmdUpdateLotInfoList doUpdateLotInfo(GetLayersBase());
	RBase->TransmitDirectly(&doUpdateLotInfo);

	CmdReqCurrentLotAllList reqLotList(GetLayersBase());
	RBase->TransmitDirectly(&reqLotList);

	CmdReqMasterDataInfo reqMasterInfo(GetLayersBase());
	RBase->TransmitDirectly(&reqMasterInfo);

	// �\ //
	// ���b�g��(�t�@�C����)�𔲂��o��
	GUICmdReviewLotList GUISend(GetLayersBase());
	GUISend.lotList = reqLotList.FrontLotList;

	// �}�X�^�[�R�[�h�A�}�V��ID�Ɨ��\���Z�b�g
	GUISend.MasterCode = reqMasterInfo.FrontMasterDataInfo.MasterCode;
	GUISend.MachineID = reqMasterInfo.FrontMasterDataInfo.MachineID;
	GUISend.side = Review::Front;
	
	// ���M
	Base->TransmitDirectly(&GUISend);

	// ��
	// ���b�g��(�t�@�C����)�𔲂��o��
	GUISend.lotList = reqLotList.BackLotList;

	// �}�X�^�[�R�[�h�A�}�V��ID�Ɨ��\���Z�b�g
	GUISend.MasterCode = reqMasterInfo.BackMasterDataInfo.MasterCode;
	GUISend.MachineID = reqMasterInfo.BackMasterDataInfo.MachineID;
	GUISend.side = Review::Back;

	// ���M
	Base->TransmitDirectly(&GUISend);

}

void ListMasterForm::MoveCellToMasterCode(int MasterCode)
{
	ListMasterLocker locker(&ui);
	// ���X�g�̓��}�X�^�[�R�[�h�̍s���I������
	// ���X�g�̑S�s���ƃ}�X�^�[�R�[�h�̗����擾
	int rowMax = ui.tbDataTable->rowCount();
	int CodeIndex = hHeaderRaw.indexOf(/**/"MASTERCODE");

	// �ǂݍ��񂾃}�X�^�[�R�[�h���������đI�����Ԃɂ���
	QList<QTableWidgetItem *> pItems = ui.tbDataTable->findItems(QString::number(MasterCode), Qt::MatchExactly);
	if(pItems.size()==0)return;
	ui.tbDataTable->setCurrentItem(pItems.first());
	ui.tbDataTable->verticalScrollBar()->setValue(pItems.first()->row());
}

void ListMasterForm::ShowLoadMasterDataWindow()
{
	ListMasterLocker locker(&ui);
	// �}�X�^�[�I���t�H�[���\��
	LoadMasterDataWindow *form = new LoadMasterDataWindow(GetLayersBase(), sRoot, sName, this);
	GeneralDialog *D = new GeneralDialog(GetLayersBase(), form, this);
	
	// ���s
	D->exec();

	// Load�`�F�b�N
	if(form->isAccepted()==false){
		delete form;
		delete D;
		return;
	}

	int		MasterCode	= form->SelectedMasterCode;// �}�X�^�[�R�[�h
	int		MachineID	= form->currentMachineID();// �}�V��ID
	
	delete form;
	delete D;

	//// �\�������̖₢����
	//Review::SideType side = Review::ShowMessageFrontOrBack();

	//// �t�F�C�Y�R�[�h(Front:0 or Back:1)
	//SendData.PhaseCode = 0;// �Ƃ肠�����\ //

	// �}�X�^�[�f�[�^�̓ǂݍ���
	LoadMasterData(MasterCode);

	// �ǂݍ��񂾃}�X�^�[�R�[�h�փJ�����g�Z�����ړ�
	MoveCellToMasterCode(MasterCode);

	ReviewGUI::UpdateGUI(GetLayersBase(), ReviewGUI::Name::WholeImageForReview);
}

void ListMasterForm::updateGUI()
{
	ListMasterLocker locker(&ui);
	//ShowList();
}

void ListMasterForm::setGUIEnable(bool enable)
{
	ui.pbSelect->setEnabled(enable);
	ui.pushButtonOpneInDetail->setEnabled(enable);
	ui.tbDataTable->setEnabled(enable);
}

//=======================================================================================================