#if	!defined(XCheckEverydayCommon_h)
#define	XCheckEverydayCommon_h

#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class	CheckEverydayLightInfo : public NPListSaveLoad<CheckEverydayLightInfo>
{
public:
	int32	Page;
	int32	Layer;
	int32	ID;
	int		BrightnessLow;
	int		BrightnessHigh;
	double	CurrentValue;
	bool	Result;
	int		x1,y1,x2,y2;
	QString		ItemName;

	CheckEverydayLightInfo(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);
};

class	CheckEverydayLightInfoContainer : public NPListPackSaveLoad<CheckEverydayLightInfo>	
{
public:
	CheckEverydayLightInfoContainer(void){}

	CheckEverydayLightInfo	*Create(void){	return new CheckEverydayLightInfo();	}
};

class	CheckEverydayFocusInfo : public NPListSaveLoad<CheckEverydayFocusInfo>
{
public:
	int32	Page;
	int32	Layer;
	int32	ID;
	double	FocusLow;
	double	CurrentValue;
	bool	Result;
	int		x1,y1,x2,y2;
	QString		ItemName;

	CheckEverydayFocusInfo(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);
};

class	CheckEverydayFocusInfoContainer : public NPListPackSaveLoad<CheckEverydayFocusInfo>	
{
public:
	CheckEverydayFocusInfoContainer(void){}

	CheckEverydayFocusInfo	*Create(void){	return new CheckEverydayFocusInfo();	}
};



#endif