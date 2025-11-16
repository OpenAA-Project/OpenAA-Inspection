#ifndef MTIMAGEBUTTONCOLORED_H
#define MTIMAGEBUTTONCOLORED_H

#include "mtImageButton.h"
#include <QImage>

class mtImageButtonColored : public mtImageButton
{
	Q_OBJECT

public:
	explicit	mtImageButtonColored(const QImage &_img, const QColor &_col, QWidget *parent);
	explicit	mtImageButtonColored(const QImage &_img, QWidget *parent);
	~mtImageButtonColored();

	QColor color()	const;
	void setColor(const QColor &col);
	void setColor(const QString &ColString);

protected:
	QImage img2;
	QColor Col;
	float nBlend_Alfa;

private:
	void setImageCombine();
};

#endif // MTIMAGEBUTTONCOLORED_H
