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

#ifndef SELECTLOTFORREVIEW_H
#define SELECTLOTFORREVIEW_H

#include "selectlotforreview_global.h"
#include "ui_SelectLotForm.h"

#include "XDLLOnly.h"

#include "../XGUICmdReviewCommon.h"

// �v���p�e�B�錾�J�n

class SelectLotForReview;

template<>
class PropertyBase<SelectLotForReview>;

typedef PropertyBase<SelectLotForReview> SelectLotForReviewProperty;

namespace Ui{
class SelectLotForReviewPropertyClass;
}

// �v���p�e�B�錾�I��

// ���b�g�̑I���\��GUI
// ���{�I�ɂ̓R���p�C�����ɐ������ꂽDLL�𑼂�GUI�Ȃǂł��݂��݁ACreateInstance�Ő��������C���X�^���X��GeneralDialog�ŕ\������
class SELECTLOTFORREVIEW_EXPORT SelectLotForReview : public GUIFormBase
{
	Q_OBJECT

public:
	SelectLotForReview(LayersBase *Base,QWidget *parent);
	~SelectLotForReview();

	int	WidthFileName;
	int	WidthLotName;
	bool	SameWidth;
	
	virtual	void	Prepare(void)	override;

public:
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	//void	SetSide(Review::SideType side){ m_Side = side; };
	void	updateGUI(bool onlySelf=true);
	void	setGUIEnable(bool enable);
	
private:
	//void	ShowLotList(Review::SideType side, const QStringList &LotList, const QStringList &LotNameList);
	void	ShowLotList(Review::SideType side, const LotInfoList &lotList);

	class SelectLotForReviewLocker;
public slots:
	void	doubleClicked(int row, int column);
	void	okButtonClicked();
	void	cancelButtonClicked();
	void	updateLotList();

signals:
	void	SignalClose();// GeneralDialog�p�I���V�O�i��

private:
	Ui::SelectLotFormClass ui;
	//Review::SideType m_Side;

	int m_FrontMasterCode;
	int m_FrontMachineID;
	int m_BackMasterCode;
	int m_BackMachineID;
	QString m_FolderName;
	
/*------------------------------------------------------------------------------------------------*/
/*----------------------------�v���p�e�B�֘A - �J�n-----------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/
	
// �v���p�e�B�̃��C���o�b�t�@(GUI�Ɏg�p����������Ui�����̓��o�͂Ɏg�p)
private:
	SelectLotForReviewProperty *m_property;

// �v���p�e�B�ݒ��_�C�A���O(�O������(*���Ƀv���p�e�B�ݒ�GUI)�̗v���ŌĂяo������)
private:
	Ui::SelectLotForReviewPropertyClass *m_propertyUi;
	QDialog *m_propertyDialog;

// �v���p�e�B�ւ̃A�N�Z�X
public:
	inline const SelectLotForReviewProperty &getProperty() const { return *m_property; };
	SelectLotForReviewProperty *getPropertyPtr() { return m_property; }

private:// �ҏW�\�͓��������̂�
	inline SelectLotForReviewProperty &getProperty() { return *m_property; };

// �v���p�e�B�̃o�b�t�@�ƃv���p�e�B�ݒ��_�C�A���O�ւ̃A�N�Z�X�֐�
private:
	void setProperty(SelectLotForReviewProperty *property){ m_property = property; };
	void setPropertyUi(Ui::SelectLotForReviewPropertyClass *ui){ m_propertyUi = ui; };
	Ui::SelectLotForReviewPropertyClass *getPropertyUi(void) const { return m_propertyUi; };
	void setPropertyDialog(QDialog *dialog){ m_propertyDialog = dialog; };
	QDialog *getPropertyDialog(void){ return m_propertyDialog; };
	
// �v���p�e�B�_�C�A���O�̃V�O�i��accepted()�ɑΉ������X���b�g
private slots:
	void slot_propertyModified();
	void slot_propertyRejected();

// �v���p�e�B�̃R�s�[��Ui�t�@�C���Ƃ̘A�g
public:
	void setProperty(const SelectLotForReviewProperty &property);
private:
	void setPropertyToUi(const SelectLotForReviewProperty &property);
	void setPropertyToUi();
	void setPropertyFromUi(SelectLotForReviewProperty &property);
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

#endif // SELECTLOTFORREVIEW_H