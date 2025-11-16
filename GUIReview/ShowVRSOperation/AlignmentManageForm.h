#pragma once

#include "ui_AlignmentManageForm.h"
#include "XReviewCommon.h"

class ReviewPIBase;
class LayersBase;

class AlignmentManageForm : public QDialog
{
	Q_OBJECT

public:
	AlignmentManageForm(ReviewPIBase *RBase, int MoveLength, int ZDistance, bool reverse_x=false, bool reverse_y=false, QWidget *parent=NULL);

// 全体画像上で1組の3?アライメントを使用する
public slots:
	void on_pbSetWholeAlignmentPoint1_clicked();
	void on_pbSetWholeAlignmentPoint2_clicked();
	void on_pbSetWholeAlignmentPoint3_clicked();
	void on_pbSetCameraWholeAlignment1_clicked();
	void on_pbSetCameraWholeAlignment2_clicked();
	void on_pbSetCameraWholeAlignment3_clicked();

	void on_pbClearWholeAlignment1_clicked();
	void on_pbClearWholeAlignmentOfImage1_clicked();
	void on_pbClearWholeAlignmentOfCamera1_clicked();
	void on_pbClearWholeAlignment2_clicked();
	void on_pbClearWholeAlignmentOfImage2_clicked();
	void on_pbClearWholeAlignmentOfCamera2_clicked();
	void on_pbClearWholeAlignment3_clicked();
	void on_pbClearWholeAlignmentOfImage3_clicked();
	void on_pbClearWholeAlignmentOfCamera3_clicked();
	void on_pbClearWholeAlignmentAll_clicked();
	
	void on_pbClearEachPageAlignment1_clicked();
	void on_pbClearEachPageAlignmentOfImage1_clicked();
	void on_pbClearEachPageAlignmentOfCamera1_clicked();
	void on_pbClearEachPageAlignment2_clicked();
	void on_pbClearEachPageAlignmentOfImage2_clicked();
	void on_pbClearEachPageAlignmentOfCamera2_clicked();
	void on_pbClearEachPageAlignment3_clicked();
	void on_pbClearEachPageAlignmentOfImage3_clicked();
	void on_pbClearEachPageAlignmentOfCamera3_clicked();
	void on_pbClearEachPageAlignmentAll_clicked();

	void on_cbEachAlignmentSettingPage_currentIndexChanged(int);
	void on_cbSideType_currentIndexChanged(int);

	void on_rbWholeAlignment_toggled(bool);
	void on_rbEachPageAlignment_toggled(bool);
	
	void on_pbSetEachPageAlignmentPoint1_clicked();
	void on_pbSetEachPageAlignmentPoint2_clicked();
	void on_pbSetEachPageAlignmentPoint3_clicked();
	void on_pbSetCameraEachPageAlignment1_clicked();
	void on_pbSetCameraEachPageAlignment2_clicked();
	void on_pbSetCameraEachPageAlignment3_clicked();

	void on_pbDebugGo_clicked();

	void changeData();

	void updateRotate(int index);
	void updateEnableLabel();
	void updateClearButtonEnable();
	void updatePhaseComboBox();
	void updateImage(bool redraw=false){ setUpdateImageRequire(true); if(redraw==true)update(); };
	void updateDrawRects();

protected:
	virtual	void 	paintEvent(QPaintEvent *)	override;
	virtual	void	resizeEvent ( QResizeEvent * event )	override;

private:
	void clearWholeAlignment(Review::SideType side, int phase, Review::AlignmentSide align_side, Review::AlignmentNo align_no);
	void clearEachPageAlignment(Review::SideType side, int phase, int page, Review::AlignmentSide align_side, Review::AlignmentNo align_no);

public:
	void getWholeAlignmentRect(QRect &first, QRect &second, QRect &third);

	//void setAlignmentWhole(const QRect &first, const QRect &second, const QRect &third);
	void moveVRS(int movex, int movey, int movez);

	void setUpdateImageRequire(bool req){ m_updateImageRequire = req; };
	bool isUpdateImageRequire() const { return m_updateImageRequire; };

	void setInitMoveLength(int length){ m_initMoveLength = length; };
	void setInitZDistance(int distance){ m_initZDistance = distance; };

	int initMoveLength() const { return m_initMoveLength; };
	int initZDistance() const { return m_initZDistance; };

	bool initXReverse() const { return m_initXReverse; };
	bool initYReverse() const { return m_initYReverse; };

	void setInitXReverse(bool reverse) { m_initXReverse = reverse; };
	void setInitYReverse(bool reverse) { m_initYReverse = reverse; };

private:
	Ui::AlignmentManageClass ui;

	ReviewPIBase *m_RBase;

	bool m_updateImageRequire;

	int m_initMoveLength;
	int m_initZDistance;
	bool m_initXReverse;
	bool m_initYReverse;

private:
	//Review::ThreeValue<QRect> m_wholeAlignmentList;
	//QList<Review::ThreeValue<QRect> > m_pageAlignmentList;
	QList<Review::ThreeValue<QRect> > m_drawAlignmentList;
	QPixmap m_pixEnable;
	QPixmap m_pixDisable;

public:
	QPixmap enablePixmap(bool enable){ return enable ? m_pixEnable : m_pixDisable; };

private:
	ReviewPIBase *_reviewAlgorithm(){ return m_RBase; };
	LayersBase *GetLayersBase();

	QRect getRect(const QRect &beforeRect);
	QRectF getCameraRect(const QRect &imageAlignment);

	QRect getRect(int page, const QRect &beforeRect);

	int rotate(void) const;
	Review::Rotate rotateEnum(void) const;

	static void rotateImageData(Review::Rotate rotation, const QList<QImage> &imageList, const QList<QPoint> &outlineOffsetList, const QRect &beforeRect,
		 QList<QImage> &rotatedImageList, QList<QPoint> &rotatedOutlineOffsetList, QRect &rotatedBeforeRect,
		 const QList<QSize> &imageSizeList=QList<QSize>(), QList<QSize> *rotatedImageSizeList=NULL);
	static void rotateImageData(Review::Rotate rotation, const QImage &image, const QPoint &outlineOffset, const QRect &beforeRect,
		QImage &rotatedImage, QPoint rotatedOutlineOffset, QRect &rotatedBeforeRect);
	static QRect makeWholeRect(const QList<QSize> &sizeList, const QList<QPoint> &offsetList, Review::Rotate rotation);
	static QRect makeWholeRect(const QSize &s, const QPoint &offset, Review::Rotate rotation);

	inline Review::SideType currentSide() const { return static_cast<Review::SideType>(ui.cbSideType->currentIndex()); };
	inline Review::VRSAlignmentType currentAlignemntType() const { return ((ui.rbWholeAlignment->isChecked()==true) ? Review::VRSAlignmentType::VRSAlingmentWholeImage : Review::VRSAlignmentType::VRSAlingmentEachPage); };
	inline int currentPage() const { return ui.cbEachAlignmentSettingPage->currentIndex(); };
	inline int currentPhase() const { return ui.cbPhase->currentIndex(); };
	
public:
	//void setWholeAlignmentRect(const Review::ThreeValue<QRect> &rects){ m_wholeAlignmentList = rects; };
	//void setWholeAlignmentRectList(const QList<QRect> &list){ if(list.count()<3)return; m_wholeAlignmentList.setValue(list[0], list[1], list[2]); };
	//void setWholeAlignmentRect(int index, const QRect &rect){ if(Review::isBetween(0, index, 2)==false)return; m_wholeAlignmentList.setValue(static_cast<Review::THREE_INDEX>(index), rect); };
	//void setWholeAlignmentRectList(const QRect &first, const QRect &second, const QRect &third){
	//	setWholeAlignmentRect(0, first);
	//	setWholeAlignmentRect(1, second);
	//	setWholeAlignmentRect(2, third);
	//};
	
	Review::ThreeValue<QRect> getWholeAlignmentRectList();
	QRect getWholeAlignmentRect(int index);

	//void setEachPageAlignmentRectList(const QList<Review::ThreeValue<QRect> > &list){ m_pageAlignmentList = list; Review::increase(ui.cbEachAlignmentSettingPage->count(), m_pageAlignmentList); };
	//void setEachPageAlignmentRect(int page, Review::ThreeValue<QRect> &rects){ m_pageAlignmentList[page] = rects; };

	QList<Review::ThreeValue<QRect> > getEachPageAlignmentRectList();
	Review::ThreeValue<QRect> getEachPageAlignmentRect(int page);

	void setDrawAlignmentList(const QList<Review::ThreeValue<QRect> > &list){ m_drawAlignmentList = list; };
	void setDrawAlignmentList(const Review::ThreeValue<QRect> &align){ m_drawAlignmentList.clear(); m_drawAlignmentList.append(align); };

	QList<Review::ThreeValue<QRect> > getDrawAlignmentRectList() const { return m_drawAlignmentList; };
	Review::ThreeValue<QRect> getDrawAlignmentRect(int index) const { return m_drawAlignmentList[index]; };

private:
	void setWholeAlignmentData(int index, const QRect &beforeRect);
	void setEachPageAlignmentData(Review::SideType side, int page, int index, const QRect &beforeRect);
	void setEachPageCameraAlignmentData(Review::SideType side, int page, int index, const QRect &beforeRect);
};
