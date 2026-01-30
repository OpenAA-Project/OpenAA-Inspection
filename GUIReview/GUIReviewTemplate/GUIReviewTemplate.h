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

#ifndef GUIREVIEWTEMPLATE_H
#define GUIREVIEWTEMPLATE_H

#include "GUIReviewTemplate_global.h"

#include "ui_GUIReviewTemplateForm.h"

#include "XDLLOnly.h"

#include "ReviewStructureItems.h"

// �e���v���[�gGUIReview
class GUIREVIEWTEMPLATE_EXPORT GUIReviewTemplate : public GUIFormBase
{
	Q_OBJECT

public:
	GUIReviewTemplate(LayersBase *Base,QWidget *parent);
	~GUIReviewTemplate();

public:
	// �X�V�v�����󂯎����Am_map���X�V����
	virtual	void TransmitDirectly(GUIDirectMessage *packet)	override;

public:
	void updateGUI();// ReviewStructure�����f�[�^���擾����m_map�̏������X�V����

public slots:
	void ResizeAction(void);

private:
	Ui::GUIReviewTemplateClass ui;
};


#endif // GUIREVIEWTEMPLATE_H