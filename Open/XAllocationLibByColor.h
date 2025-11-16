#if	!defined(XAllocationLibByColor_h)
#define	XAllocationLibByColor_h

#include "XIntClass.h"
#include "NListComp.h"
#include "XAlgorithmLibrary.h"
#include "XTypeDef.h"
#include "XGeneralFunc.h"
#include <QBuffer>

//------------------------------------------------------------------------------------

class	AllocationLibByColor : public NPListSaveLoad<AllocationLibByColor>
{
public:
	IntList	ColorCode;
	QColor	Color;	//This is available in ColorCode==-1
	AlgorithmLibraryListContainer	LibList;

	AllocationLibByColor(void){}
	AllocationLibByColor(int colorcode ,const QColor &col):Color(col)	{	ColorCode.Add(colorcode);	}
	AllocationLibByColor(IntList &colorcode ,const QColor &col):ColorCode(colorcode),Color(col){}

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);

	
	AllocationLibByColor	&operator=(AllocationLibByColor &src);
	QColor	GetColor(void);
};

class	AllocationLibByColorContainer : public NPListPackSaveLoad<AllocationLibByColor>
{
public:
	int	CommonID;
	AllocationLibByColorContainer(int commonid){	CommonID=commonid;	}

	virtual	AllocationLibByColor	*Create(void)	override {	return new AllocationLibByColor();	}
	bool	IsExist(const QColor &Col);
	AllocationLibByColor	*Find(const QColor &Col);

	virtual	bool	Save(QIODevice* f) override;
	virtual	bool	Load(QIODevice* f) override;

	AllocationLibByColorContainer	&operator=(const AllocationLibByColorContainer &src);
};

inline	bool	AllocationLibByColor::Save(QIODevice *f)
{
	int32	Ver=1;
	if(::Save(f,Ver			)==false)	return false;
	if(ColorCode.Save(f)==false)		return false;
	if(::Save(f,Color		)==false)	return false;
	if(LibList.Save(f)==false)			return false;
	return true;
}
inline	bool	AllocationLibByColor::Load(QIODevice *f)
{
	int32	Ver;
	if(::Load(f,Ver			)==false)	return false;
	if(ColorCode.Load(f)==false)		return false;
	if(::Load(f,Color		)==false)	return false;
	if(LibList.Load(f)==false)			return false;
	return true;
}
inline	AllocationLibByColor	&AllocationLibByColor::operator=(AllocationLibByColor &src)
{
	ColorCode	=src.ColorCode	;
	Color		=src.Color		;
	LibList		=src.LibList	;
	return *this;

}
inline	QColor	AllocationLibByColor::GetColor(void)
{
	if(ColorCode.GetFirst()!=NULL){
		switch(ColorCode.GetFirst()->GetValue()){
			case 1:	return Qt::red;
			case 2:	return Qt::yellow;
			case 3:	return Qt::green;
			case 4:	return Qt::cyan;
			case 5:	return Qt::blue;
			case 6:	return Qt::magenta;
			case 7:	return Qt::white;
			default:	break;	
		}
	}
	return Color;
}
inline	bool	AllocationLibByColorContainer::IsExist(const QColor &Col)
{
	for(AllocationLibByColor *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Color==Col)
			return true;
	}
	return false;
}
inline	AllocationLibByColor	*AllocationLibByColorContainer::Find(const QColor &Col)
{
	for(AllocationLibByColor *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Color==Col)
			return a;
	}
	return NULL;
}

inline	bool	AllocationLibByColorContainer::Save(QIODevice* f)
{
	if (::Save(f, CommonID) == false)	return false;
	return NPListPackSaveLoad<AllocationLibByColor>::Save(f);
}
inline	bool	AllocationLibByColorContainer::Load(QIODevice* f)
{
	if (::Load(f, CommonID) == false)	return false;
	return NPListPackSaveLoad<AllocationLibByColor>::Load(f);
}

inline	AllocationLibByColorContainer	&AllocationLibByColorContainer::operator=(const AllocationLibByColorContainer &src)
{
	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	((AllocationLibByColorContainer *)&src)->Save(&Buff);
	Buff.seek(0);
	Load(&Buff);
	return *this;
}

#endif