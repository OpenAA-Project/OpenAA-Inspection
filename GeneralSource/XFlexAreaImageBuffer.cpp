#include "XTypeDef.h"
#include"XFlexAreaImageBuffer.h"

FlexAreaImageBuffer::FlexAreaImageBuffer(const FlexAreaImageBuffer &src)
{
	Area=src.Area;
	Image=src.Image;
}

bool	FlexAreaImageBuffer::Save(QIODevice *f)
{
	if(Area.Save(f)==false)
		return false;
	if(Image.Save(f)==false)
		return false;
	return true;
}

bool	FlexAreaImageBuffer::Load(QIODevice *f)
{
	if(Area.Load(f)==false)
		return false;
	if(Image.Load(f)==false)
		return false;
	return true;
}

void	FlexAreaImageBuffer::Copy(const FlexArea &Src ,ImageBuffer &SrcImage ,int mergin)
{
	int	X=Src.GetMinX();
	int	Y=Src.GetMinY();
	Area=Src;
	Area.MoveToNoClip(-X+mergin,-Y+mergin);
	int	W=Src.GetWidth();
	int	H=Src.GetHeight();
	Image.Set(0,0,W+mergin*2,H+mergin*2);
	Image.PartialCopy(SrcImage,X-mergin,Y-mergin);

}

FlexAreaImageBuffer	&FlexAreaImageBuffer::operator=(FlexAreaImageBuffer &src)
{
	Area=src.Area;
	Image.Set(0,0,src.GetImage().GetWidth(), src.GetImage().GetHeight());
	Image=src.Image;
	return *this;
}