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

// プロパティ宣言開始
#include "XReviewPropertyBase.h"

class WholeImageForReview;
class WholeDisplay_impl;

template<>
class PropertyBase<WholeImageForReview>;

typedef PropertyBase<WholeImageForReview> WholeImageForReviewProperty;

namespace Ui{
class WholeImageForReviewPropertyClass;
}

// プロパティ宣言終了

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
	QList<WholeDisplay *> FrontImageList;// フェイズ対応
	QList<WholeDisplay *> BackImageList;// フェイズ対応

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
/*----------------------------プロパティ関連 - 開始-----------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/
	
// プロパティのメインバッファ(GUIに使用する情報とUiからの入出力に使用)
private:
	WholeImageForReviewProperty *m_property;

// プロパティ設定ダイアログ(外部から(*主にプロパティ設定GUI)の要求で呼び出される)
private:
	Ui::WholeImageForReviewPropertyClass *m_propertyUi;
	QDialog *m_propertyDialog;

// プロパティへのアクセス
public:
	inline const WholeImageForReviewProperty &getProperty() const { return *m_property; };
	WholeImageForReviewProperty *getPropertyPtr() { return m_property; }

private:// 編集可能は内部からのみ
	inline WholeImageForReviewProperty &getProperty() { return *m_property; };

// プロパティのバッファとプロパティ設定ダイアログへのアクセス関数
private:
	void setPropertyUi(Ui::WholeImageForReviewPropertyClass *ui){ m_propertyUi = ui; };
	Ui::WholeImageForReviewPropertyClass *getPropertyUi(void) const { return m_propertyUi; };
	void setPropertyDialog(QDialog *dialog){ m_propertyDialog = dialog; };
	QDialog *getPropertyDialog(void){ return m_propertyDialog; };
	
// プロパティダイアログのシグナルaccepted()に対応するスロット
private slots:
	void slot_propertyModified();

// プロパティのコピーとUiファイルとの連携
public:
	void setProperty(const WholeImageForReviewProperty &property);
private:
	void setProperty(WholeImageForReviewProperty *property){ m_property = property; };
	void setPropertyToUi(const WholeImageForReviewProperty &property);
	void setPropertyToUi();
	void setPropertyFromUi(WholeImageForReviewProperty &property);
	void setPropertyFromUi();

// コンストラクタで使用するプロパティの初期化
private:
	void initProperty();

private:
	void updateProperty(){ setProperty(getProperty()); };
	
/*------------------------------------------------------------------------------------------------*/
/*----------------------------プロパティ関連 - 終了-----------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

private:
	void setPropertyToDisplay(WholeDisplay *display, Review::SideType side);
	void setPropertyToDisplay();
};

#endif // WHOLEIMAGEFORREVIEW_H
