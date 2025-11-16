#ifndef MTIMAGETOOLBUTTONCOLORED_H
#define MTIMAGETOOLBUTTONCOLORED_H

#include <QImage>
#include "mtImageToolButton.h"
#include "mtPushButtonWithBalloon.h"

class mtImageToolButtonColored : public mtImageToolButton, public mtButtonWithBalloonBase
{
	Q_OBJECT

public:
	explicit	mtImageToolButtonColored(QWidget *parent ,bool checked = true);
	explicit	mtImageToolButtonColored(const QImage &_img, const QColor &_col, QWidget *parent ,bool checked = true);
	explicit	mtImageToolButtonColored(const QImage &_img, QWidget *parent ,bool checked = true);
	~mtImageToolButtonColored();

	void setImageBmpColored(const QImage &_img);

	QColor color()	const;
	void setColor(const QColor &col);
	void setColor(const QString &ColString);
	void setPressedColor(const QColor &col);
	void setPressedColor(const QString &ColString);

	void DrawNormalColor();
	void DrawPressedColor();

protected:
	QImage img2;
	QColor Col;
	float nBlend_Alfa;

protected:
	virtual void mouseMoveEvent(QMouseEvent *event)		override;
	virtual void enterEvent(QEnterEvent *event)				override;
	virtual void closeEvent(QCloseEvent *event)			override;
	virtual void mousePressEvent(QMouseEvent *event)	override;
signals:
	void	RClick(QMouseEvent * event );
private:
	void setImageCombine(QImage &image);

private slots:
	void SlotMessageMouseMove(int x, int y);
};

#endif // MTIMAGETOOLBUTTONCOLORED_H
