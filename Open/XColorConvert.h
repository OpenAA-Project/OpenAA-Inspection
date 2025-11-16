#pragma once

#include "NListComp.h"
#include <QColor>
#include <QIODevice>

double	GetColorDistancce(const QColor &col1,const QColor &col2);
double	GetColorDistancce(const QRgb &col1,const QRgb &col2);
//--------------------------------------------------------------------------------------------------------
class	ColorProfile : public NPListSaveLoad<ColorProfile>
{
public:
	int32	ID;
	QColor	SrcColor;
	QColor	DstColor;
	QString	Name;
	
	ColorProfile(void){		ID=-1;	}
	ColorProfile(const ColorProfile &Src);
	ColorProfile(const QColor &SrcColor,const QColor &DstColor);

	ColorProfile	&operator=(const ColorProfile &src);

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
};

class	ColorProfileContainer : public NPListPackSaveLoad<ColorProfile>
{
public:
	ColorProfileContainer(void){}
	ColorProfileContainer(const ColorProfileContainer &src);

	virtual	ColorProfile	*Create(void);

	ColorProfile	*GetClosedSrcColor(const QColor &col)	const;
	ColorProfile	*GetClosedDstColor(const QColor &col)	const;

	ColorProfileContainer	&operator=(const ColorProfileContainer &src);
	void	MergeBySource(const ColorProfileContainer &src);
	void	MergeBySource(const QColor &PDFColor ,const QColor &ImgColor);

	QColor	AssignToSrcBy4(const QColor &dCol)	const;
	QColor	AssignToSrcBy1(const QColor &dCol)	const;
};

class	ColorProfileContainerWithTable : public ColorProfileContainer
{
	QRgb	*ColTable;

public:
	ColorProfileContainerWithTable(void);
	ColorProfileContainerWithTable(const ColorProfileContainerWithTable &src);
	~ColorProfileContainerWithTable(void);

	ColorProfileContainerWithTable	&operator=(const ColorProfileContainerWithTable &src);
	ColorProfileContainerWithTable	&operator=(const ColorProfileContainer &src);

	void	MakeTable(void);

	QRgb	GetColor(const QRgb &dCol)	const;

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
};

inline	QRgb	ColorProfileContainerWithTable::GetColor(const QRgb &dCol)	const
{
	return ColTable[(qRed(dCol)<<16) + (qGreen(dCol)<<8) + qBlue(dCol)];
}

//--------------------------------------------------------------------------------------------------------
//class	ColorCount : public NPList<ColorCount>
//{
//public:
//	QColor	Color;
//	int32	Count;
//
//	ColorCount(void)	{	Count=0;	}
//	ColorCount(const ColorCount &src);
//
//	ColorCount	&operator=(const ColorCount &src);
//};

class	ColorCountContainer// : public NPListPack<ColorCount>
{
public:
	int	BListR[256];
	int	BListG[256];
	int	BListB[256];

	ColorCountContainer(void);
	ColorCountContainer(const ColorCountContainer &src);

	ColorCountContainer	&operator=(const ColorCountContainer &src);
	void	IncreaseCount(const QRgb &col);
};

class ColorCountList : public NPList<ColorCountList>
{
public:
	QRgb	IndexColor;
	ColorCountContainer	ColorContainer;
	QRgb	DestColor;

	ColorCountList(const QRgb &col);
	ColorCountList(const ColorCountList &src);

	ColorCountList	&operator=(const ColorCountList &src);

	void	IncreaseCount(const QRgb &col);
	void	MakeDestColor(void);
private:
	int		MakeCenterBrightness(int BList[256],double OmitL, double OmitH);
};
class	ColorCountListContainer : public NPListPack<ColorCountList>
{
	ColorCountList	*Point[256][256][256];

public:
	ColorCountListContainer(void);
	ColorCountListContainer(const ColorCountListContainer &src);

	ColorCountListContainer	&operator=(const ColorCountListContainer &src);

	void	Append(ColorCountList *s);
	ColorCountList	*FindIndexColor(const QRgb &indexcol);
};