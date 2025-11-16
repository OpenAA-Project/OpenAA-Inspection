#if	!defined(XFlexAreaImageBuffer_H)
#define	XFlexAreaImageBuffer_H

#include "XFlexArea.h"
#include "XMainSchemeMemory.h"

class	FlexAreaImageBuffer
{
	FlexArea	Area;
	ImageBuffer	Image;

public:
	FlexAreaImageBuffer(void){}
	FlexAreaImageBuffer(const FlexAreaImageBuffer &src);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	Copy(const FlexArea &Src ,ImageBuffer &SecImage ,int mergin=0);
	FlexAreaImageBuffer	&operator=(FlexAreaImageBuffer &src);
	bool	IsNull(void)		const	{	return Area.IsNull();	}

	FlexArea	&GetArea(void)	const	{	return (FlexArea &)Area;		}
	ImageBuffer	&GetImage(void)	const	{	return (ImageBuffer	&)Image;	}
};

#endif