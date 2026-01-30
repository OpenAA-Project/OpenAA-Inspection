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

#ifndef LIVECAMERADFK31AF03_H
#define LIVECAMERADFK31AF03_H

#include "LiveCameraDFK31AF03_global.h"

#include "ui_LiveCameraDFK31AF03Form.h"

#include "XDLLOnly.h"

#include "ReviewStructureItems.h"

#include "AreaCamera.h"

//#include "AreaCameraLib.h"

// �e���v���[�gGUIReview
class LIVECAMERADFK31AF03_EXPORT LiveCameraDFK31AF03 : public GUIFormBase
{
	Q_OBJECT

public:
	LiveCameraDFK31AF03(LayersBase *Base,QWidget *parent);
	~LiveCameraDFK31AF03();

public:
	// �X�V�v�����󂯎����Am_map���X�V����
	virtual	void TransmitDirectly(GUIDirectMessage *packet)	override;

protected:
	virtual	void mousePressEvent(QMouseEvent *)	override;

public:
	void updateGUI();// ReviewStructure�����f�[�^���擾����m_map�̏������X�V����

public slots:
	void ResizeAction(void);

private:
	Ui::LiveCameraDFK31AF03Class ui;
	QWidget *widget;
};


#endif // LIVECAMERADFK31AF03_H