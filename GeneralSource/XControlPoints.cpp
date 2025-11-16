#include "XControlPoints.h"
#include "XGeneralFunc.h"

//====================================================================================================
XYPointWithName::XYPointWithName(const XYPointWithName &src)
{
	X=src.X;
	Y=src.Y;
	Name=src.Name;
}
XYPointWithName::XYPointWithName(int x ,int y,const QString &name)
{
	X=x;
	Y=y;
	Name=name;
}
bool	XYPointWithName::Save(QIODevice *f)
{
	if(::Save(f,X)==false)		return false;
	if(::Save(f,Y)==false)		return false;
	if(::Save(f,Name)==false)	return false;
	return true;
}

bool	XYPointWithName::Load(QIODevice *f)
{
	if(::Load(f,X)==false)		return false;
	if(::Load(f,Y)==false)		return false;
	if(::Load(f,Name)==false)	return false;
	return true;
}

XYPointWithName	&XYPointWithName::operator=(const XYPointWithName &src)
{
	X=src.X;
	Y=src.Y;
	Name=src.Name;
	return *this;
}

XYPointContainerWithName::XYPointContainerWithName(const XYPointContainerWithName &src)
{
	for(XYPointWithName *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		XYPointWithName	*d=new XYPointWithName();
		*d=*s;
		AppendList(d);
	}
}

XYPointWithName	*XYPointContainerWithName::Create(void)
{
	return new XYPointWithName();
}

XYPointContainerWithName	&XYPointContainerWithName::operator=(const XYPointContainerWithName &src)
{
	RemoveAll();
	for(XYPointWithName *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		XYPointWithName	*d=new XYPointWithName();
		*d=*s;
		AppendList(d);
	}
	return *this;
}
XYPointWithName	*XYPointContainerWithName::Add(int x ,int y,const QString &name)
{
	XYPointWithName	*d=new XYPointWithName(x,y,name);
	AppendList(d);
	return d;
}

//==================================================================

bool	AlgoListArray::Save(QIODevice *f)
{
	if(::Save(f,DLLRoot)==false)	return false;
	if(::Save(f,DLLName)==false)	return false;
	if(::Save(f,Array	)==false)	return false;
	return true;
}
bool	AlgoListArray::Load(QIODevice *f)
{
	if(::Load(f,DLLRoot)==false)	return false;
	if(::Load(f,DLLName)==false)	return false;
	if(::Load(f,Array	)==false)	return false;
	return true;
}
AlgoListArray	&AlgoListArray::operator=(const AlgoListArray &src)
{
	DLLRoot	=src.DLLRoot;
	DLLName	=src.DLLName;
	Array	=src.Array	;
	return *this;
}

AlgoListArrayContainer	&AlgoListArrayContainer::operator=(const AlgoListArrayContainer &src)
{
	RemoveAll();
	for(AlgoListArray *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		AlgoListArray	*d=new AlgoListArray();
		*d=*s;
		AppendList(d);
	}
	return *this;
}

//=====================================================================================

bool	AlgoListInPage::Save(QIODevice *f)
{
	if(::Save(f,Phase)==false)	return false;
	if(::Save(f,Page)==false)	return false;
	if(ControlPointsForPages.Save(f)==false)
		return false;
	if(AlgoList.Save(f)==false)
		return false;
	return true;
}
bool	AlgoListInPage::Load(QIODevice *f)
{
	if(::Load(f,Phase)==false)	return false;
	if(::Load(f,Page)==false)	return false;
	if(ControlPointsForPages.Load(f)==false)
		return false;
	if(AlgoList.Load(f)==false)
		return false;
	return true;
}
