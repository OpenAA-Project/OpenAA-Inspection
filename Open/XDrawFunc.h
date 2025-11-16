#if	!defined(XDRAWFUNC_H)
#define	XDRAWFUNC_H

#include <QPainter>
#include "XTypeDef.h"

void	DrawArrow(double StartX ,double StartY ,double EndX ,double EndY
				 ,QPainter &Pnt ,int movx ,int movy ,double ZoomRate ,int SizeOfArrowMark=10);

void	DrawArrow(double StartX ,double StartY ,double EndX ,double EndY
				 ,QPainter &Pnt ,int movx ,int movy ,double ZoomRate
				 ,int x1,int y1 ,int x2 ,int y2
				 ,int SizeOfArrowMark=10);

#endif

