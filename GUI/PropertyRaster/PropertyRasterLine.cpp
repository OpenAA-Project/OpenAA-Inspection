#include "PropertyRasterForm.h"


RasterFileLayerLine::RasterFileLayerLine(void)
{
	ShownBox=new QCheckBox();
	FileLayerID=-1;
}
RasterFileLayerLine::RasterFileLayerLine(const RasterFileLayerLine &src)
{
	ShownBox=new QCheckBox()	;

	FileLayerID	=-1				;
	FileName	=src.FileName	;
	Color		=src.Color		;
}


void	RasterFileLayerLine::SetShown(bool b)
{
	ShownBox->setChecked(b);

}
bool	RasterFileLayerLine::GetShown(void)
{
	return ShownBox->isChecked();
}

void	RasterFileLayerLine::StoreFromWindow(void)
{
}
void	RasterFileLayerLine::ReflectToWindow(void)
{
}
bool	RasterFileLayerLine::SaveContent(QIODevice *f)
{
	if(::Save(f,FileLayerID)==false)
		return false;
	if(::Save(f,FileName)==false)
		return false;
	if(::Save(f,Color)==false)
		return false;
	return true;
}
bool	RasterFileLayerLine::LoadContent(QIODevice *f)
{
	if(::Load(f,FileLayerID)==false)
		return false;
	if(::Load(f,FileName)==false)
		return false;
	if(::Load(f,Color)==false)
		return false;
	return true;
}
