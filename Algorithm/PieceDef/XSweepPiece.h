#if	!defined(XSweepPiece_h)
#define	XSweepPiece_h

#include "NList.h"

class	FlexAreaImageBuffer;
class	ImageBuffer;

class	SweepResult : public NPList<SweepResult>
{
public:
	int	X,Y;
	double	MatchingRate;

	SweepResult(int x, int y ,double rate):X(x),Y(y),MatchingRate(rate){}
};

class	SweepResultContainer : public NPListPack<SweepResult>
{
public:
	SweepResultContainer(void){}
};

int		SweepPiece(ImageBuffer &Img ,FlexAreaImageBuffer &Seed ,SweepResultContainer &Found 
				,BYTE **BitBuff,int XByte ,int YLen
				,double CoEfficient=0.8);


#endif