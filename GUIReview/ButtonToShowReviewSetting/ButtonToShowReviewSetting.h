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

#ifndef BUTTONTOSHOWREVIEWSETTING_H
#define BUTTONTOSHOWREVIEWSETTING_H

#include "ButtonToShowReviewSetting_global.h"

#include "ui_ButtonToShowReviewSettingForm.h"
#include "ReviewSettingFormBase.h"

#include "XDLLOnly.h"

// �ݒ����ʂ��\�������{�^����GUI
class BUTTONTOSHOWREVIEWSETTING_EXPORT ButtonToShowReviewSetting : public GUIFormBase
{
	Q_OBJECT

public:
	ButtonToShowReviewSetting(LayersBase *Base,QWidget *parent);
	~ButtonToShowReviewSetting();

public:
	virtual	void TransmitDirectly(GUIDirectMessage *packet)	override;

public:
	void updateGUI();// ReviewStructure�����f�[�^���擾����m_map�̏������X�V����

public slots:
	void ResizeAction(void);
	void clicked();

private:
	Ui::ButtonToShowReviewSettingClass ui;
};


#endif // GUIREVIEWTEMPLATE_H