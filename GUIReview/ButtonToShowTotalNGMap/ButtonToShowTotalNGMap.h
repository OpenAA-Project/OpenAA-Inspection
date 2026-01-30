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

#ifndef BUTTONTOSHOWTOTALNGMAP_H
#define BUTTONTOSHOWTOTALNGMAP_H

#include <QPushButton>

#include "TotalNGMap.h"
#include "buttontoshowtotalngmap_global.h"
#include "ui_TotalNGMapForm.h"
#include "XDLLOnly.h"
#include "ReviewStructureItems.h"
//#include "StretchImageWidget.h"

// �v���p�e�B�錾�J�n
#include "XReviewPropertyBase.h"

class ButtonToShowTotalNGMap;
class ReviewPIBase;

template<>
class PropertyBase<ButtonToShowTotalNGMap>;

typedef PropertyBase<ButtonToShowTotalNGMap> ButtonToShowTotalNGMapProperty;

namespace Ui{
class ButtonToShowTotalNGMapPropertyClass;
}
// �v���p�e�B�錾�I��

// �{�^����������GUI
// �p�P�b�g�ɂ����X�V���߂������܂ōX�V���Ȃ�
// �X�V���߂����������͈̂ȉ��̒ʂ�
//
//  ListMasterDataAndLoad
//    �}�X�^�[�f�[�^���ǂݍ��񂾂Ƃ�
//  SelectLotForReview
//    ���b�g���I��(�ύX)�����Ƃ�
//  
class BUTTONTOSHOWTOTALNGMAP_EXPORT ButtonToShowTotalNGMap : public GUIFormBase
{
	Q_OBJECT

public:
	ButtonToShowTotalNGMap(LayersBase *Base, QWidget *parent);
	~ButtonToShowTotalNGMap();

	virtual void	Prepare(void)	override;
public:
	// �X�V�v�����󂯎����Am_map���X�V����
	virtual	void TransmitDirectly(GUIDirectMessage *packet)	override;

public:
	void updateGUI();// ReviewStructure�����f�[�^���擾����m_map�̏������X�V����

public slots:
	// �{�^�����N���b�N�������̓���
	void clicked(void);
	void ResizeAction(void);
	void updateMapImage();

protected:
	virtual	void paintEvent(QPaintEvent *event)	override;

private:
	QPushButton m_Btn;// m_map���\�������{�^��
	TotalNGMap m_map;// NG�}�b�v(�����X�V���\������)�������Ԃŕ\�������Ă��Ȃ�
	//Ui::TotalNGMapClass ui;
	
/*------------------------------------------------------------------------------------------------*/
/*----------------------------�v���p�e�B�֘A - �J�n-----------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/
	
// �v���p�e�B�̃��C���o�b�t�@(GUI�Ɏg�p����������Ui�����̓��o�͂Ɏg�p)
private:
	ButtonToShowTotalNGMapProperty *m_property;

// �v���p�e�B�ݒ��_�C�A���O(�O������(*���Ƀv���p�e�B�ݒ�GUI)�̗v���ŌĂяo������)
private:
	Ui::ButtonToShowTotalNGMapPropertyClass *m_propertyUi;
	QDialog *m_propertyDialog;

// �v���p�e�B�ւ̃A�N�Z�X
public:
	inline const ButtonToShowTotalNGMapProperty &getProperty() const { return *m_property; };
	ButtonToShowTotalNGMapProperty *getPropertyPtr() { return m_property; }

private:// �ҏW�\�͓��������̂�
	inline ButtonToShowTotalNGMapProperty &getProperty() { return *m_property; };

// �v���p�e�B�̃o�b�t�@�ƃv���p�e�B�ݒ��_�C�A���O�ւ̃A�N�Z�X�֐�
private:
	void setProperty(ButtonToShowTotalNGMapProperty *property){ m_property = property; };
	void setPropertyUi(Ui::ButtonToShowTotalNGMapPropertyClass *ui){ m_propertyUi = ui; };
	Ui::ButtonToShowTotalNGMapPropertyClass *getPropertyUi(void) const { return m_propertyUi; };
	void setPropertyDialog(QDialog *dialog){ m_propertyDialog = dialog; };
	QDialog *getPropertyDialog(void){ return m_propertyDialog; };
	
// �v���p�e�B�_�C�A���O�̃V�O�i��accepted(),rejected()�ɑΉ������X���b�g
private slots:
	void slot_propertyModified();
	void slot_propertyRejected();

private slots:
	void slot_tbNGColor_clicked();

// �v���p�e�B�̃R�s�[��Ui�t�@�C���Ƃ̘A�g
public:
	void setProperty(const ButtonToShowTotalNGMapProperty &property);
private:
	void setPropertyToUi(const ButtonToShowTotalNGMapProperty &property);
	void setPropertyToUi();
	void setPropertyFromUi(ButtonToShowTotalNGMapProperty &property);
	void setPropertyFromUi();

// �R���X�g���N�^�Ŏg�p�����v���p�e�B�̏�����
private:
	void initProperty();

private:
	void updateProperty(){ setProperty(getProperty()); };
};


#endif // BUTTONTOSHOWTOTALNGMAP_H