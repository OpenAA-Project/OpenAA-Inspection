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

#ifndef LISTMASTERFORM_H
#define LISTMASTERFORM_H

#include <QWidget>
#include <QThread>
#include <QComboBox>
#include <QScrollArea>
#include <QSqlTableModel>
#include "ui_ListMaster.h"
#include "XGUIFormBase.h"
#include "XServiceForLayers.h"
#include "XGUIPacketForDLL.h"
#include "XReviewCommon.h"

// ���X�g���\�����郁�C���t�H�[��
class ListMasterForm : public GUIFormBase
{
	Q_OBJECT

public:
	ListMasterForm(LayersBase *Base ,QWidget *parent = 0);

	int		WidthID;
	int		WidthName;
	int		WidthLatest;
	bool	SameWidth;
	
	virtual	void	Prepare(void)	override;

public:
	void updateGUI();// ���X�g�̍X�V
	void setGUIEnable(bool enable);// �L����������
	void setMachineIDFilter(const QList<int> &machineIDFilter){
		if(MachineIDFilter!=machineIDFilter){
			MachineIDFilter = machineIDFilter;
			ShowList();
		}
	};

private:
	Ui::ListMasterFormClass ui;	// UI
	QStringList	hHeaderView;	// ���X�g�̉������w�b�_�[
	QStringList hHeaderRaw;		// ���X�g�̏c�����w�b�_�[
	QList<int> MachineIDFilter;

	// �}�X�^�[�f�[�^�̓ǂݍ��݊֐�
	bool	LoadMasterData(int SelectedMasterCode);

	// �}�X�^�[�f�[�^�̈ꗗ�\��
	void	ShowList();

	// ���b�g�ǂݍ���
	void	ShowSelectLot(int MasterCode, int MachineID, Review::SideType side);
	void	ShowSelectLot();

	// �}�X�^�[�R�[�h�̈ʒu�ɃJ�����g�Z�����ړ�
	void	MoveCellToMasterCode(int MasterCode);

	class ListMasterLocker;
private slots:
	// �}�X�^�[�f�[�^�̏ڍׂȑI�����ʂ��\������
	void	ShowLoadMasterDataWindow();
	// ���X�g���_�u���N���b�N�����ꍇ�̃}�X�^�[�f�[�^�ǂݍ��ݓ���
	void	SlotDoubleClicked(const QModelIndex &index);
	// �I���{�^�����N���b�N�����Ƃ��̓���
	void	SlotSelectButtonClicked();
	// �X�V�{�^�����N���b�N�����Ƃ��̓���
	void	SlotUpdateButtonClicked();
};

#endif // PROPERTYREALTIMEGRAPHFORM_H