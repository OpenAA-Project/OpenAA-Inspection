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

#ifndef LISTMASTERDATAANDLOAD_H
#define LISTMASTERDATAANDLOAD_H

#include "listmasterdataandload_global.h"

#include "XDLLOnly.h"

#include "ListMaster.h"

// �v���p�e�B�錾�J�n
#include "XReviewPropertyBase.h"

class ListMasterDataAndLoad;

template<>
class PropertyBase<ListMasterDataAndLoad>;

typedef PropertyBase<ListMasterDataAndLoad> ListMasterDataAndLoadProperty;

namespace Ui{
class ListMasterDataAndLoadPropertyClass;
}
// �v���p�e�B�錾�I��

class LISTMASTERDATAANDLOAD_EXPORT ListMasterDataAndLoad : public GUIFormBase
{
	Q_OBJECT

public:
	ListMasterDataAndLoad(LayersBase *Base,QWidget *parent);
	~ListMasterDataAndLoad();

	virtual	void	Prepare(void)	override;
public:
	virtual	void TransmitDirectly(GUIDirectMessage *packet)	override;

public:
	ListMasterForm m_ListMasterForm;// ���C���t�H�[��

public slots:
	void ResizeAction();//�E�B���h�E�T�C�Y�ύX���̓���
	void updateTable();
	
/*------------------------------------------------------------------------------------------------*/
/*----------------------------�v���p�e�B�֘A - �J�n-----------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/
	
// �v���p�e�B�̃��C���o�b�t�@(GUI�Ɏg�p����������Ui�����̓��o�͂Ɏg�p)
private:
	ListMasterDataAndLoadProperty *m_property;

// �v���p�e�B�ݒ��_�C�A���O(�O������(*���Ƀv���p�e�B�ݒ�GUI)�̗v���ŌĂяo������)
private:
	Ui::ListMasterDataAndLoadPropertyClass *m_propertyUi;
	QDialog *m_propertyDialog;

// �v���p�e�B�ւ̃A�N�Z�X
public:
	inline const ListMasterDataAndLoadProperty &getProperty() const { return *m_property; };
	ListMasterDataAndLoadProperty *getPropertyPtr() { return m_property; }

private:// �ҏW�\�͓��������̂�
	inline ListMasterDataAndLoadProperty &getProperty() { return *m_property; };

// �v���p�e�B�̃o�b�t�@�ƃv���p�e�B�ݒ��_�C�A���O�ւ̃A�N�Z�X�֐�
private:
	void setProperty(ListMasterDataAndLoadProperty *property){ m_property = property; };
	void setPropertyUi(Ui::ListMasterDataAndLoadPropertyClass *ui){ m_propertyUi = ui; };
	Ui::ListMasterDataAndLoadPropertyClass *getPropertyUi(void) const { return m_propertyUi; };
	void setPropertyDialog(QDialog *dialog){ m_propertyDialog = dialog; };
	QDialog *getPropertyDialog(void){ return m_propertyDialog; };
	
// �v���p�e�B�_�C�A���O�̃V�O�i��accepted()�ɑΉ������X���b�g
private slots:
	void slot_propertyModified();
	void showMachineIDFilterDialog();

// �v���p�e�B�̃R�s�[��Ui�t�@�C���Ƃ̘A�g
public:
	void setProperty(const ListMasterDataAndLoadProperty &property);
private:
	void setPropertyToUi(const ListMasterDataAndLoadProperty &property);
	void setPropertyToUi();
	void setPropertyFromUi(ListMasterDataAndLoadProperty &property);
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

#endif // LISTMASTERDATAANDLOAD_H