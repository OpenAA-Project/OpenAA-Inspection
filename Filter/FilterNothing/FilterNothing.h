#ifndef FILTERNOTHING_H
#define FILTERNOTHING_H

#include "filternothing_global.h"
#include "XFilterClass.h"
#include "XDLLType.h"
#include "XMainSchemeMemory.h"

class	ImageBuffer;

class	FilterNothing : public FilterClassBase
{
public:

	FilterNothing(LayersBase *base);

	virtual	bool	Save(QIODevice *f)	override{	return true;	}
	virtual	bool	Load(QIODevice *f)	override{	return true;	}
	virtual	bool	Execute(ImageBuffer *Buff[],int BufferDimCounts)	override{	return true;	}
	virtual	bool	Initial(void)		override{	return true;	}
	virtual	bool	Release(void)		override{	return true;	}

	virtual	QString	GetDataText(void)		override{	return "Nothing";			}
	virtual	QString	GetDefaultFileName(void)override{	return "FilterNothing.dat";	}
};

#endif // FILTERNOTHING_H
