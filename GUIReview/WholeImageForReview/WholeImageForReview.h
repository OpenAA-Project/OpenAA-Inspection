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

#ifndef WHOLEIMAGEFORREVIEW_H
#define WHOLEIMAGEFORREVIEW_H

#include "wholeimageforreview_global.h"

#include <QDebug>
#include <QGridLayout>
//#include "WholeDisplay.h"

class WholeDisplay;

#include "XDLLOnly.h"
#include "XReviewCommon.h"
#include "ReviewStructureItems.h"

// �v���p�e�B�錾�J�n
#include "XReviewPropertyBase.h"

class WholeImageForReview;
class WholeDisplay_impl;

template<>
class PropertyBase<WholeImageForReview>;

typedef PropertyBase<WholeImageForReview> WholeImageForReviewProperty;

namespace Ui{
class WholeImageForReviewPropertyClass;
}

// �v���p�e�B�錾�I��

class WHOLEIMAGEFORREVIEW_EXPORT WholeImageForReview : public GUIFormBase
{
	Q_OBJECT

public:
	WholeImageForReview(LayersBase *Base,QWidget *parent);
	~WholeImageForReview();

	double ZoomImageFromFile;
public:
	bool loadImage(Review::SideType side);
	bool loadImage(Review::SideType side, int phase);
	bool loadImage(QString filename, unsigned int nPhase, unsigned int nPage);
	void updateGUI(void);
	void setDrawZoomLock(bool lock){ drawZoomLock = lock; };
	bool isDrawZoomLock(void){ return drawZoomLock; };

	virtual void	Prepare(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	
	virtual	bool eventFilter(QObject *target, QEvent *event)	override;
	void connectDisplay(Review::SideType side, int phase);
	void disconnectDisplay(Review::SideType side, int phase);
	void updatePCEArea();
	void updateImages();

protected:
	virtual	void paintEvent(QPaintEvent *)	override;

private:
	//void checkData();
	void setOrientation(Qt::Orientation orientationFrontBack, Qt::Orientation orientationPhase);
	void setOrientation();
	void setNGCrossView(bool view);
	void setNGPointView(bool view);
	void setOnlyCurrentNGNailRectView(bool view);
	void clearCurrent();
	void clear();

public slots:
	void SlotFrontNGSelect(int phase, int index);
	void SlotBackNGSelect(int phase, int index);
	void loadImageFront(void){ loadImage(Review::Front); };
	void loadImageBack(void){ loadImage(Review::Back); };
	void SlotSetDragRectImage(Review::SideType side, int phase, QRect rect);
	void SlotSetOrgImage(Review::SideType side,int phase);

public:
	QList<WholeDisplay *> getImageList(Review::SideType side);
	WholeDisplay *getWholeDisplay(Review::SideType side, int phase);
	WholeDisplay_impl *getWholeDisplayCanvas(Review::SideType side, int phase);

private:
	QList<WholeDisplay *> FrontImageList;// �t�F�C�Y�Ή�
	QList<WholeDisplay *> BackImageList;// �t�F�C�Y�Ή�

	QWidget *FrontWidget;
	QWidget *BackWidget;

	int FrontMasterCode;
	int BackMasterCode;

	bool drawZoomLock;

	int currentIndex;
	Review::SideType currentSide;
	int currentPhase;
	int currentEID;

	QGridLayout *mainLayout;
	QGridLayout *frontLayout;
	QGridLayout *backLayout;

	//Qt::Orientation viewFrontBackMode;
	//Qt::Orientation viewPhaseMode;
	//bool viewNGNailCross;
	//bool viewNGPoint;
	//bool viewOnlyCurrentNail;
	
/*------------------------------------------------------------------------------------------------*/
/*----------------------------�v���p�e�B�֘A - �J�n-----------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/
	
// �v���p�e�B�̃��C���o�b�t�@(GUI�Ɏg�p����������Ui�����̓��o�͂Ɏg�p)
private:
	WholeImageForReviewProperty *m_property;

// �v���p�e�B�ݒ��_�C�A���O(�O������(*���Ƀv���p�e�B�ݒ�GUI)�̗v���ŌĂяo������)
private:
	Ui::WholeImageForReviewPropertyClass *m_propertyUi;
	QDialog *m_propertyDialog;

// �v���p�e�B�ւ̃A�N�Z�X
public:
	inline const WholeImageForReviewProperty &getProperty() const { return *m_property; };
	WholeImageForReviewProperty *getPropertyPtr() { return m_property; }

private:// �ҏW�\�͓��������̂�
	inline WholeImageForReviewProperty &getProperty() { return *m_property; };

// �v���p�e�B�̃o�b�t�@�ƃv���p�e�B�ݒ��_�C�A���O�ւ̃A�N�Z�X�֐�
private:
	void setPropertyUi(Ui::WholeImageForReviewPropertyClass *ui){ m_propertyUi = ui; };
	Ui::WholeImageForReviewPropertyClass *getPropertyUi(void) const { return m_propertyUi; };
	void setPropertyDialog(QDialog *dialog){ m_propertyDialog = dialog; };
	QDialog *getPropertyDialog(void){ return m_propertyDialog; };
	
// �v���p�e�B�_�C�A���O�̃V�O�i��accepted()�ɑΉ������X���b�g
private slots:
	void slot_propertyModified();

// �v���p�e�B�̃R�s�[��Ui�t�@�C���Ƃ̘A�g
public:
	void setProperty(const WholeImageForReviewProperty &property);
private:
	void setProperty(WholeImageForReviewProperty *property){ m_property = property; };
	void setPropertyToUi(const WholeImageForReviewProperty &property);
	void setPropertyToUi();
	void setPropertyFromUi(WholeImageForReviewProperty &property);
	void setPropertyFromUi();

// �R���X�g���N�^�Ŏg�p�����v���p�e�B�̏�����
private:
	void initProperty();

private:
	void updateProperty(){ setProperty(getProperty()); };
	
/*------------------------------------------------------------------------------------------------*/
/*----------------------------�v���p�e�B�֘A - �I��-----------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

private:
	void setPropertyToDisplay(WholeDisplay *display, Review::SideType side);
	void setPropertyToDisplay();
};

#endif // WHOLEIMAGEFORREVIEW_H