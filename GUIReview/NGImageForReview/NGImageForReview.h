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

#ifndef NGIMAGEFORREVIEW_H
#define NGIMAGEFORREVIEW_H

#include <QLayout>
#include <QLabel>
#include "ngimageforreview_global.h"

#include "XDLLOnly.h"

#include "ImageDataUnit.h"

#include "XReviewCommon.h"
#include "ReviewStructureItems.h"
#include "PieceDisplay.h"

// �v���p�e�B�錾�J�n
#include "XReviewPropertyBase.h"

class NGImageForReview;

template<>
class PropertyBase<NGImageForReview>;

typedef PropertyBase<NGImageForReview> NGImageForReviewProperty;

namespace Ui{
class NGImageForReviewPropertyClass;
}

// �v���p�e�B�錾�I��

class NGIMAGEFORREVIEW_EXPORT NGImageForReview : public GUIFormBase
{
	Q_OBJECT

public:
	// �R���X�g���N�^�ŉ��ʂ̕\���𐮂���
	NGImageForReview(LayersBase *Base,QWidget *parent);
	~NGImageForReview();

public:
	// NG�ƃ}�X�^�[�摜�̍X�V�v�����󂯎����A���ʂ��X�V����
	virtual	void TransmitDirectly(GUIDirectMessage *packet)	override;
	void setOrientation(Qt::Orientation orient);// �c�������т̐ݒ�
	//void setMasterSide(Review::SideType side);
	void adjustImageSize(void);// NG�摜�T�C�Y�ƕ\���G���A�T�C�Y����NG�摜�ƃ}�X�^�[�摜�̑傫���𒲐����ANG�摜�̃}�X�^�[�摜�ʒu�̏��񂩂��}�X�^�[�摜�̃V�t�g�ړ����s���摜�S�ʂ̒�������

	void updateGUI(void);
	virtual	void Prepare(void)	override;

private:
	// check�`
	// EditGUI�ŕύX���ꂽ�v���p�e�B�ɑ΂��ē��I�ɕύX���邽�߂̊֐�
	// �v���p�e�B�̃p�l���̐��l�Ȃǂ��ύX�����Č��肳�ꂽ�ꍇ�Ɏ��s������
	// ���ۂɎ��s�������̂�GUIFormBase��ChangedValue()��Prepare���Ă΂��A�ȉ��̊֐����Ă΂���
	void checkOrientation();

public:
	int32 reqOrientation;
	bool isMasterView;
	bool isNGImageView;

private:
	//Review::SideType	currentMasterSide;	// ���ݕ\�����̉摜�T�C�h
	//
	//MasterImagePiece	*FrontMasterImage;	// �}�X�^�[�摜�g���}(�\ //
	//MasterImagePiece	*BackMasterImage;	// �}�X�^�[�摜�g���}(��
	//NGImagePiece		*NGNailImage;			// NG�摜

	MasterPieceDisplay		MasterPImage;
	NGNailDisplay			NGNailImage;
	QLabel					MasterLabel;
	QLabel					NGNailLabel;

	QGridLayout *mainLayout;// ���C�A�E�g
	QVBoxLayout *vLayout;	// �c���їp���C�A�E�g
	QHBoxLayout *hLayout;	// �����їp���C�A�E�g

	Qt::Orientation			viewType;			// ���ѕ���

	NGNailItemRef NGNailInfo;

	QColor DefaultNGNailLabelWindowColor;
	QColor DefaultMasterLabelWindowColor;

public slots:
	void	ResizeAction();//�E�B���h�E�T�C�Y�ύX���̓���

	
/*------------------------------------------------------------------------------------------------*/
/*----------------------------�v���p�e�B�֘A - �J�n-----------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/
	
// �v���p�e�B�̃��C���o�b�t�@(GUI�Ɏg�p����������Ui�����̓��o�͂Ɏg�p)
private:
	NGImageForReviewProperty *m_property;

// �v���p�e�B�ݒ��_�C�A���O(�O������(*���Ƀv���p�e�B�ݒ�GUI)�̗v���ŌĂяo������)
private:
	Ui::NGImageForReviewPropertyClass *m_propertyUi;
	QDialog *m_propertyDialog;

// �v���p�e�B�ւ̃A�N�Z�X
public:
	inline const NGImageForReviewProperty &getProperty() const { return *m_property; };
	NGImageForReviewProperty *getPropertyPtr() { return m_property; }

private:// �ҏW�\�͓��������̂�
	inline NGImageForReviewProperty &getProperty() { return *m_property; };

// �v���p�e�B�̃o�b�t�@�ƃv���p�e�B�ݒ��_�C�A���O�ւ̃A�N�Z�X�֐�
private:
	void setProperty(NGImageForReviewProperty *property){ m_property = property; };
	void setPropertyUi(Ui::NGImageForReviewPropertyClass *ui){ m_propertyUi = ui; };
	Ui::NGImageForReviewPropertyClass *getPropertyUi(void) const { return m_propertyUi; };
	void setPropertyDialog(QDialog *dialog){ m_propertyDialog = dialog; };
	QDialog *getPropertyDialog(void){ return m_propertyDialog; };
	
// �v���p�e�B�_�C�A���O�̃V�O�i��accepted()�ɑΉ������X���b�g
private slots:
	void slot_propertyModified();

// �v���p�e�B�̃R�s�[��Ui�t�@�C���Ƃ̘A�g
public:
	void setProperty(const NGImageForReviewProperty &property);
private:
	void setPropertyToUi(const NGImageForReviewProperty &property);
	void setPropertyToUi();
	void setPropertyFromUi(NGImageForReviewProperty &property);
	void setPropertyFromUi();

// �R���X�g���N�^�Ŏg�p�����v���p�e�B�̏�����
private:
	void initProperty();

private:
	void updateProperty(){ setProperty(getProperty()); };
	
/*------------------------------------------------------------------------------------------------*/
/*----------------------------�v���p�e�B�֘A - �I��-----------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/
};

#endif // NGIMAGEFORREVIEW_H