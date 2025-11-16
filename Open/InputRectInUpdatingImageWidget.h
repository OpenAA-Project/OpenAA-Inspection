#pragma once

#include "InputRectInMultiImageWidget.h"

class InputRectInUpdatingImageWidget : public InputRectInMultiImageWidget
{
	Q_OBJECT

public:
	InputRectInUpdatingImageWidget(QWidget *parent=NULL):InputRectInMultiImageWidget(parent){};

public slots:
	void setImage(QImage image){
		QList<QImage> list;
		list << image;
		setImageList(list, outlineList());
	};
};
