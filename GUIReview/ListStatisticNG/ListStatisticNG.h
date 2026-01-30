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

#ifndef LISTSTATISTICNG_H
#define LISTSTATISTICNG_H

#include "liststatisticng_global.h"

#include "ui_StatisticNGForm.h"

#include "XDLLOnly.h"

// �v���p�e�B�錾�J�n
#include "XReviewPropertyBase.h"

class ListStatisticNG;

template<>
class PropertyBase<ListStatisticNG>;

typedef PropertyBase<ListStatisticNG> ListStatisticNGProperty;

namespace Ui{
class ListStatisticNGPropertyClass;
}
// �v���p�e�B�錾�I��

// �ǂݍ����ł��郍�b�g�̊������ꂼ���m�F���ANG�ł��邩�ǂ����𒲂ׁANG�Ȃ��΁A�����Ɋ֘A�t�������Ă���F�L�[�������擾���č��v�l���o��
// OK�Ȃ��Ί���:OK�ɒǉ�����
// 
// ______|_NG_|_F1_|_F2_|_F3_|_�`_|_F12_|_OK_|
// ���\|____|____|____|____|____|_____|____|
// ����|____|____|____|____|____|_____|____|
// _NG��_|____|____|____|____|____|_____|__0_|
// 
class LISTSTATISTICNG_EXPORT ListStatisticNG : public GUIFormBase
{
	Q_OBJECT

public:
	ListStatisticNG(LayersBase *Base,QWidget *parent);
	~ListStatisticNG();

public:
	// �X�V�v�����󂯎����A���X�g���X�V����.
	virtual	void TransmitDirectly(GUIDirectMessage *packet)	override;
	void updateGUI();

public slots:
	void ResizeAction();

	void on_pbShowDetail_clicked();
	void on_pbSaveToFile_clicked();

public:
	QTableWidget *createDetailTableWidget(QString *errMsg=NULL);

private:
	//// �\�֌W
	//QList<int> FrontBoardWithFKeyList;	// F[i-1]�L�[�̊��� + F�L�[�Ȃ�
	//int FrontOKBoard;					// OK�ɑ���������

	//QList<int> FrontNGWithFKeyList;		// F[i-1]�L�[�ɑ�����NG���̍��v�l + F�L�[�Ȃ�


	//// ���֌W
	//QList<int> BackBoardWithFKeyList;	// F[i-1]�L�[�̊��� + F�L�[�Ȃ�
	//int BackOKBoard;					// OK�ɑ���������

	//QList<int> BackNGWithFKeyList;		// F[i-1]�L�[�ɑ�����NG���̍��v�l + F�L�[�Ȃ�

	Ui::StatisticNGClass ui;

private:
	QStringList m_FKeyDefinedNames;// F1~F12 & NoFKey

protected:
	void initFKeyDefinedNames();

public:
	inline QStringList getFKeyDefinedNames(bool fkeyOnly=false) const {
		if(fkeyOnly==false){
			return m_FKeyDefinedNames;
		}else{
			return m_FKeyDefinedNames.mid(0, m_FKeyDefinedNames.count()-2);
		}
	};
	inline QString *getFKeyDefinedNamesPtr(int index){ return &m_FKeyDefinedNames[index]; };
	QString getFKeyDefinedName(int index) const { return m_FKeyDefinedNames[index]; };

	int columnCount() const { return 14; };
	int rowCount() const { return 4; };

public:
	virtual	void Prepare(void)	override;
	
/*------------------------------------------------------------------------------------------------*/
/*----------------------------�v���p�e�B�֘A - �J�n-----------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/
	
// �v���p�e�B�̃��C���o�b�t�@(GUI�Ɏg�p����������Ui�����̓��o�͂Ɏg�p)
private:
	ListStatisticNGProperty *m_property;

// �v���p�e�B�ݒ��_�C�A���O(�O������(*���Ƀv���p�e�B�ݒ�GUI)�̗v���ŌĂяo������)
private:
	Ui::ListStatisticNGPropertyClass *m_propertyUi;
	QDialog *m_propertyDialog;

// �v���p�e�B�ւ̃A�N�Z�X
public:
	inline const ListStatisticNGProperty &getProperty() const { return *m_property; };
	ListStatisticNGProperty *getPropertyPtr() { return m_property; }

private:// �ҏW�\�͓��������̂�
	inline ListStatisticNGProperty &getProperty() { return *m_property; };

// �v���p�e�B�̃o�b�t�@�ƃv���p�e�B�ݒ��_�C�A���O�ւ̃A�N�Z�X�֐�
private:
	void setProperty(ListStatisticNGProperty *property){ m_property = property; };
	void setPropertyUi(Ui::ListStatisticNGPropertyClass *ui){ m_propertyUi = ui; };
	Ui::ListStatisticNGPropertyClass *getPropertyUi(void) const { return m_propertyUi; };
	void setPropertyDialog(QDialog *dialog){ m_propertyDialog = dialog; };
	QDialog *getPropertyDialog(void){ return m_propertyDialog; };
	
// �v���p�e�B�_�C�A���O�̃V�O�i��accepted()�ɑΉ������X���b�g
private slots:
	void slot_propertyModified();

// �v���p�e�B�̃R�s�[��Ui�t�@�C���Ƃ̘A�g
public:
	void setProperty(const ListStatisticNGProperty &property);
private:
	void setPropertyToUi(const ListStatisticNGProperty &property);
	void setPropertyToUi();
	void setPropertyFromUi(ListStatisticNGProperty &property);
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

#endif // LISTSTATISTICNG_H