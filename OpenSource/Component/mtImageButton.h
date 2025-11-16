#ifndef MTIMAGEBUTTON_H
#define MTIMAGEBUTTON_H

#include "mtImageButtonBase.h"
#include <QAbstractButton>
#include <QImage>
#include <QTimer>
#include <QPushButton>

class mtImageButton : public QPushButton, public mtImageButtonBase
{
	Q_OBJECT
	QTimer	TM;
public:
	explicit	mtImageButton(const QImage &_img, QWidget *parent);
	~mtImageButton();

protected:
	int nDrawX;
	int nDrawY;

	virtual void paintEvent(QPaintEvent *evt)			override;
	virtual void mousePressEvent(QMouseEvent *evt)		override;
	virtual void mouseReleaseEvent(QMouseEvent *evt)	override;

signals:
	void SignalClicked();

public slots:
	void	click ();
	virtual	void SlotClicked(bool checked);
	void	TimeOutOneShot();
};

#endif // MTIMAGEBUTTON_H
