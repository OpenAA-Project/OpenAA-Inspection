#ifndef MTPUSHBUTTONIMAGE_H
#define MTPUSHBUTTONIMAGE_H

#include <QWidget>
#include <QImage>

#include "XFlexArea.h"
#include "XYCross.h"
#include "XDataInLayer.h"
#include "NList.h"

class mtImageButtonBase 
{
	bool	InvertMode;
public:
	mtImageButtonBase();
	~mtImageButtonBase();

	//ボタンのステータス
	enum	ButtonState{
				 Default	=0
				,Pressed	=1
				,Released	=2
				,Clicked	=3
				,RePressed	=4
	};
	ButtonState	BtnState;

	void setImage();
	void setInvertMode(bool b);
	void setFaceImage(const QImage &_img);

protected:
	QImage img;
	QImage PressedImg;
	QImage *wImg;

	PureFlexAreaListContainer fAreaList;
	XYClassCluster xyArea;

private:
	bool calcThreshold();
	bool chkBit(int x, int y);
};
#endif // MTPUSHBUTTONIMAGE_H
