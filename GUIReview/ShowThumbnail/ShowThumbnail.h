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

#ifndef SHOWTHUMBNAIL_H
#define SHOWTHUMBNAIL_H

#include "showthumbnail_global.h"
#include "XDLLOnly.h"

#include "XReviewStructure.h"

#include "Thumbnail.h"
#include "ThumbnailPage.h"
#include "ExpandThumbnailForm.h"
#include "SettingDialog.h"
#include "XReviewCommon.h"
#include "../XGUIReviewGlobal.h"

#include "../ControlInfoDialog.h"

#include <QStackedWidget>
#include <QProgressBar>
#include <QAction>
#include <QMenu>
#include <QLabel>
#include <QTimeLine>
#include <QLabel>

#include "XReviewPropertyBase.h"

class	ShowThumbnail;
class	ControlInfoDialog;

template<>
class PropertyBase<ShowThumbnail>;

typedef PropertyBase<ShowThumbnail> ShowThumbnailProperty;

namespace Ui{
class ShowThumbnailPropertyClass;
}

class SHOWTHUMBNAIL_EXPORT ShowThumbnail : public GUIFormBase
{
	Q_OBJECT

public:
	ShowThumbnail(LayersBase *Base,QWidget *parent);
	~ShowThumbnail();

public:
	enum _moveMode{
		PerThumbnail,
		PerPage
	};
	bool	SkipSamePiece;
	//bool	ModeShowPageByPiece;
public:
	virtual void	Prepare(void)	override;
	
	// �ENGList�̍X�V
	virtual	void TransmitDirectly(GUIDirectMessage *packet)	override;
	void updateGUI();
	void updateInfoLabel();
	//void updateHelpLabel();

protected:
	// �㉺���E�C�x���g
	virtual	void keyPressEvent(QKeyEvent *event)	override;
	virtual	void keyReleaseEvent(QKeyEvent *event)	override;

private:
	void updateThumbnailList();
	void setThumbnailList(OrganizedHistoryIndex orgHistoryPtr);
	void clearThumbnailList();
	void showThumbnail();
	void createThumbnailBook();
	void createThumbnailPageList();
	void createThumbnailPageListByPiece();
	void createEditerThumbnail();
	QImage createEditerImage(int width, int height, QColor backgroundColor, Review::FKey key);
	void updateFKeyColorList();
	// �y�[�W�ԍ�[page]��locate�Ɉړ��Alocate==Review::Manual�̏ꍇ��row,column���g�p
	void showPage(Review::SideType side, int page, Review::ListLocate, int row=-1, int column=-1);// �S�w��
	void showPage(Review::SideType side, Review::ListLocate locate);// �\���Ɛ擪�����w��
	void showPage(Review::ListLocate locate, int GlobalIndex=-1);// �SNG���X�g�̃C���f�b�N�X�w��
	int getLocalIndex(int page, int row, int column, Review::SideType side) const;
	int getGlobalIndex(int page, int row, int column, Review::SideType side) const;

	int calcPage(int localIndex) const;

	// �����L�[�ɂ����ړ��̕ύX
	void inputKeyMoveModeChange();

	// �����L�[�ɂ����ړ�
	void inputKeyUpArrow();
	void inputKeyDownArrow(bool Skip);
	void inputKeyRightArrow(bool Skip);
	void inputKeyLeftArrow();
	void inputKeyFunction(Review::FKey key);
	void inputKeyDelete();
	bool	GetAreaNameAndChecked(int GlobalIndex ,QString &AreaName);

	// F�L�[�̗v�f��XML�ɋL�q����.�߂��l�̓L�[�ɑΉ������F
public:
	QColor setFKey(Review::FKey key);
	// F�L�[�̗v�f���폜����
	bool removeFKey(QColor &afterColor);
private:
	bool isMoveHistoryEnable();
	bool moveHistory(Review::Direction direction/*�ړ���������:�O�E����*/, Review::ListLocate NGLocate/* NGNail�̈ʒu */, bool *historyExisted=NULL);

	ThumbnailList *currentThumbnailList();
	ThumbnailPageList *currentThumbnailPageList();

	bool isCurrentPageAllChecked();
	bool isPageAllChecked(int GlobalPage);
	bool isPageAllChecked(Review::SideType side, int LocalPage);
	bool isCurrentHistoryAllChecked();

private:// currentXXX�𒼐ڕύX�����֐�
	bool setCurrentNG(Review::SideType side, int page, int row, int column);

protected:
	virtual	void paintEvent(QPaintEvent *event)				override;
	virtual	void contextMenuEvent(QContextMenuEvent *event)	override;
	virtual	void mousePressEvent(QMouseEvent *event)		override;

private:
	void setRowCount(int size);
	void setColumnCount(int size);
	void setNGSignSize(int size);
	void setViewMaster(bool view);
	void setCurrentSide(Review::SideType side);
	void setCurrentPage(int page);
	void setCurrentRow(int row);
	void setCurrentColumn(int column);
	void setCurrentThumbnail(Thumbnail *thumbnail);
	void setMoveMode(_moveMode mode);
	void setExpandThumbnail(Thumbnail *thumbnail);
	void setExpandThumbnailVisible(bool v);
	void setMoveDelay(int miliSec);
	void setKeyPressedState(bool pressed);
	void setEnableExpandThumbnal(bool enable);
	void setModeShowPageByPiece (bool enable);
	void setFKeyList(const QList<QColor> &list);
	void setCurrentEID(int id);

public:
	int getRowCount() const;
	int getColumnCount() const;
	int getNGSignSize() const;
	bool isViewMaster() const;
	Review::SideType getCurrentSide() const;
	int getCurrentPage() const;
	int getCurrentRow() const;
	int getCurrentColumn() const;

	Thumbnail *getCurrentThumbnail() const;
	Thumbnail *getThumbnail(Review::SideType side, int page, int row, int column);
	Thumbnail *getThumbnail(Review::SideType side, int LocalIndex);
	Thumbnail *getThumbnail(int GlobalIndex);
private:
	int getThumbnailCount(Review::SideType side) const;
	int getThumbnailCountAll() const;
	int getCurrentThumbnailCount() const;
	int getCurrentThumbnailTotalNumb() const;
	_moveMode getMoveMode() const;
	int getThumbnailCountInPage() const;
	Thumbnail *getExpandThumbnail() const;
	bool getExpandThumbnailVisible() const;
	bool isEnableExpandThumbnal() const;
	bool isModeShowPageByPiece () const;
	int getCurrentEID() const;

	ThumbnailList &getThumbnailList(Review::SideType side);
	const ThumbnailList &getThumbnailList(Review::SideType side) const;
	ThumbnailPageList &getThumbnailPageList(Review::SideType side);
	const ThumbnailPageList &getThumbnailPageList(Review::SideType side) const;
	ThumbnailList &getCurrentThumbnailList();
	const ThumbnailList &getCurrentThumbnailList() const;
	ThumbnailPageList &getCurrentThumbnailPageList();
	const ThumbnailPageList &getCurrentThumbnailPageList() const;

	int getPageCount(Review::SideType side);
	int getCurrentPageCount();
	int getCurrentPageLastIndex();
	int getCurrentThumbnailCountInLastPage();
	int getLastRow(Review::SideType side);
	int getLastColumn(Review::SideType side);
	int getCurrentLastRow();
	int getCurrentLastColumn();
	int getCurrentThumbnailLastGlobalIndex();
	int getMoveDelay();
	int getPageDelay(const ThumbnailPage *pageWidget);
	bool isKeyPressed() const;
	bool existCurrentThumbnail() const;
	void startPageWaitTimeLine(int interval);

public slots:
	void ResizeAction();
	void slotSetCurrentThumbnail(Thumbnail *thumbnail);

private:
	//struct _reqData{
	//	int32 rowCount;
	//	int32 columnCount;
	//	int32 NGSignSize;
	//	int32 viewMaster;
	//	int32 delayMSec;
	//	int32 moveMode;
	//	bool enableExpandDialog;
	//};

private:
	// EditGUI�Ŏw�肷�邱�Ƃ��o�����c���̕\�����̍ő��l
	//int rowCount;		// �c���ő��l
	//int columnCount;	// �����ő��l
	//int NGSignSize; // NG�`���T�C�Y
	//bool viewMaster;// �}�X�^�[�摜���\�����邩�ǂ���
	//bool enableExpandThumbnal;// �g���T���l�C���L������

	QList<QColor> m_FKeyColorList;

	Review::SideType m_currentSide;// ���ݕ\�����̃T�C�h Front or Back
	int m_currentPage;// ���ݕ\�����̃y�[�W�B�P�y�[�W���ɍő� rowMax * columnMax ��NG�摜���\��������
	int m_currentRow;		// ���I�����Ԃł�-1(NG�摜�����Ȃ�)
	int m_currentColumn;	// ���I�����Ԃł�-1(NG�摜�����Ȃ�)
	Thumbnail *m_currentThumbnail;// ���ݑI�𒆂�NG�摜

	int m_delayMSec;

	ThumbnailList m_FrontThumbnailList;	// �S�T���l�C���A�C�e���̃��X�g�o�b�t�@(�\)
	ThumbnailList m_BackThumbnailList;		// �S�T���l�C���A�C�e���̃��X�g�o�b�t�@(��)

	ThumbnailPageList m_FrontThumbnailPageList;	// �\���y�[�W���X�g
	ThumbnailPageList m_BackThumbnailPageList;	// �����y�[�W���X�g

	_moveMode m_moveMode;

	//QVector<QGridLayout*> pageLayouts;
	//QGridLayout *mainLayout;
	
	//QWidget		*layoutWidget;

	QStackedWidget *m_ThumbnailBook;
	QLabel *m_InfoLabel;
	//QLabel *HelpLabel;
	QVBoxLayout *m_mainLayout;

	int m_currentEID;
	bool m_keyPressed;
	bool m_drawNGSingEnable;

protected:
	void setFKeyColorList(const QList<QColor> &list){ m_FKeyColorList = list; Review::resize(13, m_FKeyColorList); };

	QList<QColor> getFKeyColorList() const { return m_FKeyColorList; };
	//Review::SideType currentSide() const { return m_currentSide; };
	//int currentPage() const { return m_currentPage; };
	//int currentRow() const { return m_currentRow; };
	//int currentColumn() const { return m_currentColumn; };
	//Thumbnail *currentThumbnail() const { return m_currentThumbnail; };
	int delayMSec() const { return m_delayMSec; };

protected:
	void setThumbnailBook(QStackedWidget *book){ m_ThumbnailBook = book; };
	void clearThumbnailBook(){ if(m_ThumbnailBook!=NULL)delete m_ThumbnailBook; m_ThumbnailBook = NULL; };

	QStackedWidget *thumbnailBook() const { return m_ThumbnailBook; };
	QLabel *infoLabel() const { return m_InfoLabel; };
	QVBoxLayout *mainLayout() const { return m_mainLayout; };

private:
	QAction *m_settingAction;
	QMenu *m_contextMenu;
	SettingDialog *m_settingDialog;
	ControlInfoDialog *m_controlInfoDialog;
	QAction *m_controlInfoAction;
	QProgressBar *m_pageWaitProgressBar;
	QLabel		*LabelInfo;
	QTimeLine *m_pageWaitTimeLine;

	ExpandThumbnailDialog *m_ExpandDialog;

protected:
	QAction *settingAction() const { return m_settingAction; };
	QMenu *contextMenu() const { return m_contextMenu; };
	SettingDialog *settingDialog() const { return m_settingDialog; };
	ControlInfoDialog *controlInfoDialog() const { return m_controlInfoDialog; };
	QAction *controlInfoAction() const { return m_controlInfoAction; };
	QProgressBar *pageWaitProgressBar() const { return m_pageWaitProgressBar; };
	QTimeLine *pageWaitTimeLine() const { return m_pageWaitTimeLine; };
	ExpandThumbnailDialog *expandDialog() const { return m_ExpandDialog; };

	void setSettingDialog(SettingDialog *dialog){ m_settingDialog = dialog; };

private slots:
	void showSettingDialog();
	void changedRowColumnCount(int rowCount, int columnCount);
	void changedNGSignSize(int size);
	void slotSetMasterVisible(int state);
	void slotSortOrderChanged(int index);
	
// �v���p�e�B�̃��C���o�b�t�@(GUI�Ɏg�p����������Ui�����̓��o�͂Ɏg�p)
private:
	ShowThumbnailProperty *m_property;

// �v���p�e�B�ݒ��_�C�A���O(�O������(*���Ƀv���p�e�B�ݒ�GUI)�̗v���ŌĂяo������)
private:
	Ui::ShowThumbnailPropertyClass *m_propertyUi;
	QDialog *m_propertyDialog;

// �v���p�e�B�ւ̃A�N�Z�X
public:
	inline const ShowThumbnailProperty &getProperty() const { return *m_property; };
	ShowThumbnailProperty *getPropertyPtr() { return m_property; }

	ReviewPIBase *GetReviewBase(void);
	void	ShowLabelInfo(const QString &Message);
	void	SetFKeyIndex(int GlobalIndex ,Review::FKey key);
private:// �ҏW�\�͓��������̂�
	inline ShowThumbnailProperty &getProperty() { return *m_property; };

// �v���p�e�B�̃o�b�t�@�ƃv���p�e�B�ݒ��_�C�A���O�ւ̃A�N�Z�X�֐�
private:
	void setProperty(ShowThumbnailProperty *property){ m_property = property; };
	void setPropertyUi(Ui::ShowThumbnailPropertyClass *ui){ m_propertyUi = ui; };
	Ui::ShowThumbnailPropertyClass *getPropertyUi(void) const { return m_propertyUi; };
	void setPropertyDialog(QDialog *dialog){ m_propertyDialog = dialog; };
	QDialog *getPropertyDialog(void){ return m_propertyDialog; };
	
// �v���p�e�B�_�C�A���O�̃V�O�i��accepted()�ɑΉ������X���b�g
private slots:
	void slot_propertyModified();
    void on_pushButtonColorNoChecked_clicked();
    void on_pushButtonColorChecked_clicked();
    void on_pushButtonColorF1_clicked();
    void on_pushButtonColorF2_clicked();
    void on_pushButtonColorF3_clicked();
    void on_pushButtonColorF4_clicked();
    void on_pushButtonColorF5_clicked();
    void on_pushButtonColorF6_clicked();
    void on_pushButtonColorF7_clicked();
    void on_pushButtonColorF8_clicked();
    void on_pushButtonColorF9_clicked();
    void on_pushButtonColorF10_clicked();
    void on_pushButtonColorF11_clicked();
    void on_pushButtonColorF12_clicked();
// �v���p�e�B�̃R�s�[��Ui�t�@�C���Ƃ̘A�g
public:
	void setProperty(const ShowThumbnailProperty &property);
private:
	void setPropertyToUi(const ShowThumbnailProperty &property);
	void setPropertyToUi();
	void setPropertyFromUi(ShowThumbnailProperty &property);
	void setPropertyFromUi();

// �R���X�g���N�^�Ŏg�p�����v���p�e�B�̏�����
private:
	void initProperty();

private:
	void updateProperty(){ setProperty(getProperty()); };
};

#endif // SHOWTHUMBNAIL_H