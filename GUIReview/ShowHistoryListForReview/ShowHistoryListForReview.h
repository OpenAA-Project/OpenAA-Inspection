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

#ifndef SHOWHIERARCHYFORREVIEW_H
#define SHOWHIERARCHYFORREVIEW_H

#include "ShowHistoryListForReview_global.h"

#include "ui_HistoryListForm.h"
#include "ui_SettingDialog.h"
#include "HistoryListErrorDialog.h"
#include "XReviewStructure.h"

#include "XDLLOnly.h"

// �v���p�e�B�錾�J�n

class ShowHistoryListForReview;

template<>
class PropertyBase<ShowHistoryListForReview>;

typedef PropertyBase<ShowHistoryListForReview> ShowHistoryListForReviewProperty;

namespace Ui{
class ShowHistoryListForReviewPropertyClass;
}

// �v���p�e�B�錾�I��

class SHOWHISTORYLISTFORREVIEW_EXPORT ShowHistoryListForReview : public GUIFormBase
{
	Q_OBJECT

public:
	ShowHistoryListForReview(LayersBase *Base,QWidget *parent);
	~ShowHistoryListForReview();

	int		Width1;
	int		Width2;
	int		Width3;
	int		Width4;
	bool	SameWidth;
	
	virtual	void	Prepare(void)	override;

public:
	class TableData{
	public:
		TableData():EID(-1),InspectedTime(XDateTime()),isAllChecked(false),FrontNGCount(-1),BackNGCount(-1),FrontHalt(false),BackHalt(false){};
	public:
		bool isOK() const {
			bool front_ok;
			bool back_ok;

			if(hasFront()==false){
				front_ok = true;
			}else{
				if(FrontNGCount==0){
					front_ok = true;
				}else{
					front_ok = false;
				}
			}
			if(hasBack()==false){
				back_ok = true;
			}else{
				if(BackNGCount==0){
					back_ok = true;
				}else{
					back_ok = false;
				}
			}

			return ((front_ok==true) && (back_ok==true)); 
		};
		bool hasFront() const { return FrontNGCount>=0; };
		bool hasBack() const { return BackNGCount>=0; };

	public:
		int EID;
		int		InspectedMachine;
		XDateTime InspectedTime;
		bool isAllChecked;
		int		FrontNGNailCount;
		int		FrontNGCount;
		bool	FrontHalt;
		int		BackNGNailCount;
		int		BackNGCount;
		bool	BackHalt;
		bool existFront;
		bool existBack;
	};
public:
	// ShowHistoryListForReview�̑����M
	// [Send]
	// �ENGImageListForReview��NG���X�g�̍X�V�v��
	// 
	// [Recive]
	// �E�������X�g�̍X�V
	// �E�������X�g�̈ړ�
	virtual	void TransmitDirectly(GUIDirectMessage *packet)	override;
	
	void ShowHistoryList(OrganizedHistoryListPtr orgHistryListPtr);
	void updateGUI();
	void setGUIEnale(bool enable);
	bool isOKBoardVisible(){ return OKBoardVisible; };

protected:
	void contextMenuEvent(QContextMenuEvent *event);

private:
	void setTableRowItem(int row, TableData data,int &TopNGCount ,int &BackNGCount ,XDateTime &InspectionTime);
	int getTableIndex(int GlobalIndex);
	void createErrorDialog();

public slots:
	void ResizeAction();
	void relativeCellClicked(int currentRow, int currentColumn, int previousRow, int previousColumn);	// ���X�g���N���b�N�����Ƃ��̓���
								// �N���b�N�����s�ԍ����󂯎����ANGImageListForReview�ɑ���
	void setOKBoardVisible(bool v){ if(ui.cbOKVisible->isChecked()==v)return; ui.cbOKVisible->setChecked(v); updateTable(); };
	void updateTable();
	void reloadData();
	void stateOKViewChanged(int state);

	void showSettingDialog();
	void showErrorDialog();

	void sliderChanged(int value);

private:
	QAction *settingAction;
	QMenu *contextMenu;

private:
	Ui::HistoryListClass ui;
	HistoryListErrorDialog errorDialog;

	QStringList twHorizontalHeaderLabels;
	QString hhlInspectID;
	QString hhlInspectedTime;
	QString hhlFrontInfo;
	QString hhlBackInfo;

	bool OKBoardVisible;// OK���Ղ�?�����郂?�h
	QList<int> NGIndexAtTableRow;//	?�������Ă����e?�u����NG�s��ReviewStrucrure���ɂ������ǂ̗����C���f�b�N�X�����������X�g
								//	NGIndexAtTableRow[�e?�u���̍s�C���f�b�N�X] == OrgDataList�̃C���f�b�N�X

	QList<TableData> OrgDataList;


/*------------------------------------------------------------------------------------------------*/
/*----------------------------�v���p�e�B�֘A - �J�n-----------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/
	
// �v���p�e�B�̃��C���o�b�t?(GUI�Ɏg�p����������Ui�����̓��o�͂Ɏg�p)
private:
	ShowHistoryListForReviewProperty *m_property;

// �v���p�e�B�ݒ�?�C�A���O(�O������(*���Ƀv���p�e�B�ݒ�GUI)�̗v���ŌĂяo������)
private:
	Ui::ShowHistoryListForReviewPropertyClass *m_propertyUi;
	QDialog *m_propertyDialog;

// �v���p�e�B�ւ̃A�N�Z�X
public:
	inline const ShowHistoryListForReviewProperty &getProperty() const { return *m_property; };
	ShowHistoryListForReviewProperty *getPropertyPtr() { return m_property; }

private:// �ҏW��?�͓��������̂�
	inline ShowHistoryListForReviewProperty &getProperty() { return *m_property; };

// �v���p�e�B�̃o�b�t?�ƃv���p�e�B�ݒ�?�C�A���O�ւ̃A�N�Z�X�֐�
private:
	void setProperty(ShowHistoryListForReviewProperty *property){ m_property = property; };
	void setPropertyUi(Ui::ShowHistoryListForReviewPropertyClass *ui){ m_propertyUi = ui; };
	Ui::ShowHistoryListForReviewPropertyClass *getPropertyUi(void) const { return m_propertyUi; };
	void setPropertyDialog(QDialog *dialog){ m_propertyDialog = dialog; };
	QDialog *getPropertyDialog(void){ return m_propertyDialog; };
	
// �v���p�e�B?�C�A���O�̃V�O�i��accepted()�ɑΉ������X���b�g
private slots:
	void slot_propertyModified();

// �v���p�e�B�̃R�s?��Ui�t?�C���Ƃ̘A�g
public:
	void setProperty(const ShowHistoryListForReviewProperty &property);
private:
	void setPropertyToUi(const ShowHistoryListForReviewProperty &property);
	void setPropertyToUi();
	void setPropertyFromUi(ShowHistoryListForReviewProperty &property);
	void setPropertyFromUi();

// �R���X�g���N?�Ŏg�p�����v���p�e�B�̏�����
private:
	void initProperty();

private:
	void updateProperty(){ setProperty(getProperty()); };
	
/*------------------------------------------------------------------------------------------------*/
/*----------------------------�v���p�e�B�֘A - �I��-----------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/
};

#endif // SHOWHIERARCHYFORREVIEW_H