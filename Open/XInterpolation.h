#if	!defined(XINTERPOLATION_H)
#define	XINTERPOLATION_H

class ImageBuffer;
class FlexArea;
#include "XTypeDef.h"

void	InterpolateEllipse(ImageBuffer &Img , FlexArea &CircleArea
							,double &Cx,double &Cy
							,double &Rx,double &Ry
							,double Precision=0.001);
/*
	‘È‰~‚É•âŠÔ‚·‚é
	‚¨‚æ‚»‚Ì‘È‰~Œ`ó‚ğCircleArea‚É“ü‚ê‚Ä‚¨‚­
*/

bool	MakeInterpolatedLine(double x[] ,double y[] ,int N
							 ,double &A,double &B,double &C);
/*
	Å¬‚Qæ–@‚Å
	Ax+By+C=0
	‚ğ‹‚ß‚é
*/

bool	AnalizeInterpolatedLine(double x[] ,double y[] ,int N
								 ,double A,double B,double C
								,double &RetMaxSeparation
								,double &RetVarietySeparatedDistanceFromLine
								,double RetStartPointOnLine[2]
								,double RetEndPointOnLine[2]);

#endif