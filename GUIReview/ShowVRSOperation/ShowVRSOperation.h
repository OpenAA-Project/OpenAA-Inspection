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

#ifndef SHOWVRSOPERATION_H
#define SHOWVRSOPERATION_H

#include "showvrsoperation_global.h"

#include "XDLLOnly.h"

#include "ui_ShowVRSOperationForm.h"

// �v���p�e�B�錾�J�n
#include "XReviewPropertyBase.h"

class ShowVRSOperation;

template<>
class PropertyBase<ShowVRSOperation>;

typedef PropertyBase<ShowVRSOperation> ShowVRSOperationProperty;

namespace Ui{
class ShowVRSOperationPropertyClass;
}

// �v���p�e�B�錾�I��

// VRS�̎蓮�ɂ����ړ��v�����s���R���|�[�l���g
// ���܂ł͉��ʂ��N���b�N���邱�Ƃɂ����ړ������蓮�ł̈ړ����@�������������߁A�A���C�����g�Ɏ��Ԃ��������܂���
// �������g�p���邱�Ƃɂ����A���̎��Ԃ��啝�Ɍy�������܂�
class SHOWVRSOPERATION_EXPORT ShowVRSOperation : public GUIFormBase
{
	Q_OBJECT

public:
	ShowVRSOperation(LayersBase *Base,QWidget *parent);
	~ShowVRSOperation();

private:
	Ui::ShowVRSOperationClass ui;

public:
	bool showVRSSettingButton;
	QString passwordForSettingButton;

private:
	bool	settingButtonIsFree;

public:
	virtual	void TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	void Prepare(void)	override;

public slots:
	void on_pbVRSSetting_clicked();
	void on_pbAlignmentManager_clicked();
	void on_pbSetZDiastance_clicked();
	void on_pbOrigin_clicked();
	void on_pbEscape_clicked();
	void on_pbMoveUp_clicked();
	void on_pbMoveDown_clicked();
	void on_pbMoveLeft_clicked();
	void on_pbMoveRight_clicked();
	void on_cbYReverse_toggled(bool);
	void on_cbXReverse_toggled(bool);
	void on_sbZDistanceStep_valueChanged(int);

	//void on_pbTest_clicked();
	
/*------------------------------------------------------------------------------------------------*/
/*----------------------------�v���p�e�B�֘A - �J�n-----------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/
	
// �v���p�e�B�̃��C���o�b�t�@(GUI�Ɏg�p����������Ui�����̓��o�͂Ɏg�p)
private:
	ShowVRSOperationProperty *m_property;

// �v���p�e�B�ݒ��_�C�A���O(�O������(*���Ƀv���p�e�B�ݒ�GUI)�̗v���ŌĂяo������)
private:
	Ui::ShowVRSOperationPropertyClass *m_propertyUi;
	QDialog *m_propertyDialog;

// �v���p�e�B�ւ̃A�N�Z�X
public:
	inline const ShowVRSOperationProperty &getProperty() const { return *m_property; };
	ShowVRSOperationProperty *getPropertyPtr() { return m_property; }

private:// �ҏW�\�͓��������̂�
	inline ShowVRSOperationProperty &getProperty() { return *m_property; };

// �v���p�e�B�̃o�b�t�@�ƃv���p�e�B�ݒ��_�C�A���O�ւ̃A�N�Z�X�֐�
private:
	void setProperty(ShowVRSOperationProperty *property){ m_property = property; };
	void setPropertyUi(Ui::ShowVRSOperationPropertyClass *ui){ m_propertyUi = ui; };
	Ui::ShowVRSOperationPropertyClass *getPropertyUi(void) const { return m_propertyUi; };
	void setPropertyDialog(QDialog *dialog){ m_propertyDialog = dialog; };
	QDialog *getPropertyDialog(void){ return m_propertyDialog; };
	
// �v���p�e�B�_�C�A���O�̃V�O�i��accepted()�ɑΉ������X���b�g
private slots:
	void slot_propertyModified();

// �v���p�e�B�̃R�s�[��Ui�t�@�C���Ƃ̘A�g
public:
	void setProperty(const ShowVRSOperationProperty &property);
private:
	void setPropertyToUi(const ShowVRSOperationProperty &property);
	void setPropertyToUi();
	void setPropertyFromUi(ShowVRSOperationProperty &property);
	void setPropertyFromUi();

// �R���X�g���N�^�Ŏg�p�����v���p�e�B�̏�����
private:
	void initProperty();

private:
	void updateProperty(){ setProperty(getProperty()); };
	
/*------------------------------------------------------------------------------------------------*/
/*----------------------------�v���p�e�B�֘A - �I��-----------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

private slots:
	void updateMoveLength(int value);
	void updateZDistanceStep(int value);
	void updateSequencePosition();

private:
	QTimer m_seqenceUpdateTime;

private:
	QTimer &sequenceUpdateTime(){ return m_seqenceUpdateTime; };
};

#endif // SHOWVRSOPERATION_H