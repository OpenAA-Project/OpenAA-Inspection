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

#ifndef NGIMAGELISTFORREVIEW_H
#define NGIMAGELISTFORREVIEW_H

#include "NGImageListForReview_global.h"
#include <QTextStream.h>
#include "ui_NGImageListForm.h"
//#include "SettingDialog.h"

#include "XDLLOnly.h"

#include "ReviewStructureItems.h"
#include "../ControlInfoDialog.h"
#include "XReviewPropertyBase.h"

// �v���p�e�B�錾�J�n

class NGImageListForReview;

template<>
class PropertyBase<NGImageListForReview>;

typedef PropertyBase<NGImageListForReview> NGImageListForReviewProperty;

namespace Ui{
class NGImageListForReviewPropertyClass;
}
class	SignalOperandInt;
// �v���p�e�B�錾�I��

////
// NG�摜�P�ʂł̃��X�g���\�������R���|�[�l���g
// �p�P�b�g���M�ɂ����X�V�v������ReviewStructure�̃��X�g���Q�Ƃ��Ď��g�̃��X�g���X�V����
class NGIMAGELISTFORREVIEW_EXPORT NGImageListForReview : public GUIFormBase
{
	Q_OBJECT

private:
	struct _reqData{
		int32 NextListDelay;
		bool WaitProgressVisible;
	};
	int FrontCount;
	int BackCount;
public:
	NGImageListForReview(LayersBase *Base,QWidget *parent);
	~NGImageListForReview();

	bool	SameWidth;
	int32	WidthXYMatrix;
	int32	WidthLibrary;
	int32	WidthCause;
	int32	WidthCount;
	int32	WidthArea;
	bool	SkipSamePiece;
	int32	WaitMilisecToChangeSurface;

public:
	// �X�V�v���p�P�b�g���󂯎��������AReviewStructure��NG�̃��X�g���v�����A�\�����X�g���X�V����
	virtual	void TransmitDirectly(GUIDirectMessage *packet)	override;
	void updateGUI();
	void refleshTableRow(int row);
	void setCurrentRow(int row);
	int currentRow();
	virtual	bool eventFilter(QObject *target, QEvent *event)	override;
	virtual	void Prepare()	override;
	int	getNextListDelay();
	int getNextListDelay(const NGNailItem &item) const;
	bool isKeyMoveEnable() const { return ui.progKeyWait->value()==ui.progKeyWait->maximum(); };
	virtual void	Terminated(void)		override;

private:
	// �\�����Ă��郊�X�g�̓��e���X�V����
	void setNGList(const OrganizedHistoryItem &history);
	// �\�����Ă����E�B���h�E�F���ύX����
	void setViewColor(const OrganizedHistoryItem &history);
	void addNGList(const HistoryItem &historyPtr, const InsLibraryHash &InsLibHashPtr=InsLibraryHash(), int InsertRow=0);
	void updateVerticalHeader(int FrontCount, int BackCount);
	// F�L�[�̗v�f��XML�ɋL�q����.�߂��l�̓L�[�ɑΉ������F
	QColor setFKey(Review::FKey key);
	// F�L�[�̗v�f���폜����
	bool removeFKey(QColor &afterColor);
	void fillBackgraundColorOnTableAtRow(int row, QColor color);
	void setKeyPressedState(bool pressed){ keyPressed = pressed; };
	bool isKeyPressed() const { return keyPressed; };
	QColor getResultColor(const QStringList &resultList, const QColor &defaultColor=QColor(Qt::red));

	// ���݂�NG���I���ς݂ɂ���
	bool setCheckedCurrentNG();
	QColor getCurrentNGColor();

	void inputKeyUPArrow();
	void inputKeyDownArrow(bool Skip);
	void inputKeyRightArrow();
	void inputKeyLeftArrow();
	void inputKeyFunction(Review::FKey key);
	void inputKeyDelete();
	void inputKeyExchangeNGVisible();
	void inputKeyEnter();

	void moveHistory(Review::Direction direction);

	void startKeyWaitTimeLine(int interval);

	void setGUIEnable(bool enable);
	bool	GetAreaNameAndChecked(int row ,QString &AreaName);
	int		GetListCount(void);


private slots:
	void endKeyWaitTimeLine(int value);

protected:
	// �J�[�\���L�[���AF�L�[�AF�L�[�̃N���A�L�[�������ꂽ���̓���
	// �J�[�\���L�[�̏ꍇ���E�̓��삪ShowHistoryListForReview�̈ړ��R�}���h���M�ɂȂ��B
	// setFKey() �� clearFKey() �����s������
	// �܂��ANGImageForReview��WholeImageForReview�ɍX�V�v�����s������
	virtual	void keyPressEvent(QKeyEvent *event)			override;
	virtual	void keyReleaseEvent(QKeyEvent *event)			override;
	virtual	void contextMenuEvent(QContextMenuEvent *event)	override;

private slots:
	// UI�̃��X�g���N���b�N���ꂽ���̃X���b�g
	// �N���b�N���ꂽ�s�����I������NGNailItem�����肵�AReviewStructure�֑I�����Ԃɂ����悤�ɗv������
	// ���̂��ƁANGImageForReview��WholeImageForReview�ɍX�V���v������
	void cellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);
	//void SlotSetSortOrder();
	void SlotShowKeyAssignInfoDialog();

private:
	Ui::NGImageListClass ui;	// �\���pUI
								// �\���pQTableWidget�ANG���\��QLineEdit
	QStringList mainHHeader;
	int32 NextListDelay;
	bool keyPressed;
	QPalette defPalette;

public:
	_reqData reqData;

private:
	//QAction *settingAction;
	QAction *showControlAction;
	QMenu *contextMenu;
	//SettingDialog *settingDialog;
	ControlInfoDialog *controlInfoDialog;

private:
	QString hhlNGPoint;
	QString hhlLibrary;
	QString hhlNGCause;
	QString hhlNGCount;
	QString hhlNGArea;

private:
	QTimeLine *keyWaitTimeLine;
	
/*------------------------------------------------------------------------------------------------*/
/*----------------------------�v���p�e�B�֘A - �J�n-----------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/
	
// �v���p�e�B�̃��C���o�b�t�@(GUI�Ɏg�p����������Ui�����̓��o�͂Ɏg�p)
private:
	NGImageListForReviewProperty *m_property;

// �v���p�e�B�ݒ��_�C�A���O(�O������(*���Ƀv���p�e�B�ݒ�GUI)�̗v���ŌĂяo������)
private:
	Ui::NGImageListForReviewPropertyClass *m_propertyUi;
	QDialog *m_propertyDialog;

// �v���p�e�B�ւ̃A�N�Z�X
public:
	inline const NGImageListForReviewProperty &getProperty() const { return *m_property; };
	NGImageListForReviewProperty *getPropertyPtr() { return m_property; }

private:// �ҏW�\�͓��������̂�
	inline NGImageListForReviewProperty &getProperty() { return *m_property; };

// �v���p�e�B�̃o�b�t�@�ƃv���p�e�B�ݒ��_�C�A���O�ւ̃A�N�Z�X�֐�
private:
	void setProperty(NGImageListForReviewProperty *property){ m_property = property; };
	void setPropertyUi(Ui::NGImageListForReviewPropertyClass *ui){ m_propertyUi = ui; };
	Ui::NGImageListForReviewPropertyClass *getPropertyUi(void) const { return m_propertyUi; };
	void setPropertyDialog(QDialog *dialog){ m_propertyDialog = dialog; };
	QDialog *getPropertyDialog(void){ return m_propertyDialog; };
	
// �v���p�e�B�_�C�A���O�̃V�O�i��accepted()�ɑΉ������X���b�g
private slots:
	void slot_propertyModified();

// �v���p�e�B�̃R�s�[��Ui�t�@�C���Ƃ̘A�g
public:
	void setProperty(const NGImageListForReviewProperty &property);
private:
	void setPropertyToUi(const NGImageListForReviewProperty &property);
	void setPropertyToUi();
	void setPropertyFromUi(NGImageListForReviewProperty &property);
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



#endif // NGIMAGELISTFORREVIEW_H