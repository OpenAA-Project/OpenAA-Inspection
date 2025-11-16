#ifndef MTIMAGETOOLBUTTONWITHBALLOON_H
#define MTIMAGETOOLBUTTONWITHBALLOON_H

#include <QToolButton>
#include "mtPushButtonWithBalloon.h"
#include "mtImageToolButton.h"

class mtImageToolButtonWithBalloon : public mtImageToolButton, public mtButtonWithBalloonBase
{
	Q_OBJECT

public:
	explicit	mtImageToolButtonWithBalloon(const QImage &_img, QWidget *parent);
	~mtImageToolButtonWithBalloon();

protected:
	virtual void mouseMoveEvent(QMouseEvent *event)	override;
	virtual void enterEvent(QEnterEvent *event)			override;
	virtual void closeEvent(QCloseEvent *event)		override;
	virtual void mousePressEvent(QMouseEvent *event)override;
	virtual	void mouseDoubleClickEvent(QMouseEvent *event)	override;
signals:
	void SignalEnter();
	void	RClick(QMouseEvent * event );
	void	LDoubleClick(QMouseEvent * event );
private slots:
	void SlotMessageMouseMove(int x, int y);

private:
	
};
#endif // MTIMAGETOOLBUTTONWITHBALLOON_H
