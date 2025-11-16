#include "XTypeDef.h"
#include <cmath>
#include "XImageStocker.h"

ListOfQImage::ListOfQImage(QImage &img)
{
	Img=new QImage();
	*Img=img;
}
ListOfQImage::ListOfQImage(const QString &resourcename)
{
	ResourceName	=resourcename;
	Img				=new QImage(resourcename);
}
ListOfQImage::~ListOfQImage(void)
{
	delete	Img;
	Img=NULL;
}

ListOfQImage	&ListOfQImage::operator=(const ListOfQImage &src)
{
	ResourceName=src.ResourceName;
	*Img=*src.Img;
	return *this;
}

const QImage	&ListOfQImageStocker::GetImage(const QString &resourcename)
{
	for(ListOfQImage *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetResourceName()==resourcename){
			return a->GetImage();
		}
	}
	ListOfQImage *b=new ListOfQImage(resourcename);
	AppendList(b);
	return b->GetImage();
}