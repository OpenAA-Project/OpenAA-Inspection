#ifndef MTIMAGEBUTTONWITHBALLOON_H
#define MTIMAGEBUTTONWITHBALLOON_H

#include <QImage>
#include "mtImageButton.h"
#include "mtPushButtonWithBalloon.h"

class mtImageButtonWithBalloon : public mtImageButton ,public mtButtonWithBalloonBase
{
	Q_OBJECT

public:
	explicit	mtImageButtonWithBalloon(const QImage &_img, QWidget *parent);
	~mtImageButtonWithBalloon();

protected:
	virtual void mouseMoveEvent(QMouseEvent *event)	override;
	virtual void enterEvent(QEnterEvent *event)			override;
	virtual void closeEvent(QCloseEvent *event)		override;
	virtual void mousePressEvent(QMouseEvent *event)override;

signals:
	void SignalEnter();

private slots:
	void SlotMessageMouseMove(int x, int y);

private:
	
};

#endif // MTIMAGEBUTTONWITHBALLOON_H
