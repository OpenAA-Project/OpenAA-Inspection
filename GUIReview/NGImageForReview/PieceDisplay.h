#pragma once

#include "mtGraphicUnit.h"
#include "XReviewCommon.h"
#include "ReviewStructureItems.h"

class PieceDisplay : public mtGraphicUnit
{
	Q_OBJECT

public:
	PieceDisplay(QWidget *parent=0);
	~PieceDisplay(){};

public:
	void setImage(QImage image,int RotateAngle=0);
	void setTopLeftPos(int x, int y){ TopLeftPos = QPoint(x, y); updateImage(); };
	void setTopLeftPos(QPoint p){ TopLeftPos = p; updateImage(); };
	virtual void updateImage(int RotateAngle=0);
	bool hasImage(){ return !Image.isNull(); };
	void	Clear(int RotateAngle);

public slots:
	void SlotWheel(int delta, int x, int y);
	void SlotMouseRDown(int,int);
	void SlotSetImageState(int zoomStage, int movx, int movy);
	void SlotShiftedImage();

signals:
	void SignalImageStateChanged(int zoomRate, int movx, int movy);

protected:
	QImage	Image;
	QImage	ImageOrg;
	QPoint TopLeftPos;
	int zoomStage;
};

class NGNailDisplay : public PieceDisplay
{
	Q_OBJECT

public:
	NGNailDisplay(QWidget *parent=0):PieceDisplay(parent),NGPoints(),NGPSelect(),NGSingSize(20),NGSingColor(Qt::red),NGSelectColor(Qt::cyan),NGVisible(true),NGSingColorForce(false)
	{
		connect(this, SIGNAL(SignalMouseMove(int,int)), SLOT(SlotMouseMove(int,int)));
	};

public:
	void setNGPoints(QList<ReviewNGPoint> list);
	//void setNGPoints(QList<ReviewNGPointWithShape> list){ NGPoints = list; NGPSelect = QVector<bool>(list.count(), false).toList(); updateImage(); };
	void setNGSingSize(int size){ NGSingSize = size; updateImage(); };
	void setNGSingColor(QColor color, bool forceColor=false){ NGSingColor = color; NGSingColorForce=forceColor; updateImage(); };
	void setNGVisible(bool enable){ if(NGVisible!=enable){NGVisible = enable; updateImage(); } };
	void setNGSelectColor(QColor color){ if(NGSelectColor==color)return; NGSelectColor = color; updateImage(); };
	bool getNGVisible(){ return NGVisible; };
	void exhangeNGVisible(){ NGVisible = !NGVisible; updateImage(); };
	void updateImage(int RotateAngle=0);

public slots:
	void SlotMouseMove(int x, int y);

private:
	QList<ReviewNGPoint>	NGPoints;
	QList<bool>		NGPSelect;
	int				NGSingSize;
	QColor			NGSingColor;
	QColor			NGSelectColor;
	bool			NGVisible;
	bool			NGSingColorForce;
};

class MasterPieceDisplay : public PieceDisplay
{
public:
	MasterPieceDisplay(QWidget *parent=0):PieceDisplay(parent){};
};