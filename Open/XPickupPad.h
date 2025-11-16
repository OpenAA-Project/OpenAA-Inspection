#if	!defined(XPICKUPPAD_H)
#define	XPICKUPPAD_H

class	ImageBuffer;
class	FlexArea;

int	MakeColorCenter(int BrList[256]);
//	輝度リストの２つのピークの中央値を求める

bool	GetPadFromImage(ImageBuffer &Img
						,FlexArea &SurroundArea
						,FlexArea &PadArea);
//	画像からパッドを抽出する


#endif