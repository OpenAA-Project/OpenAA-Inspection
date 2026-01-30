/*
 * Copyright (C) 2025
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

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

	//�{�^���̃X�e�[�^�X
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