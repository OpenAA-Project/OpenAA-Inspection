#pragma once

#include <QString>
#include <QIODevice>
#include "XIntClass.h"

class FromToClass
{
public:
	enum FromToClassType
	{
		Info_AllPages	=0
		,Info_File		=1
		,Info_Page		=2
		,Info_Shadow	=3
	};

	FromToClassType		SrcType;
	QString				SrcFileName;
	IntList				SrcPage;
	int					SrcShadowLevel;
	int					SrcShadowNumber;

	FromToClassType		DstType;
	QString				DstFileName;
	IntList				DstPage;
	int					DstShadowLevel;
	int					DstShadowNumber;

	FromToClass(void);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};
