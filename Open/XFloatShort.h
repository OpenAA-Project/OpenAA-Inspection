#if	!defined(XFloatShort_h)
#define	XFloatShort_h

#include "XTypeDef.h"
#include <QIODevice>
#define	_USE_MATH_DEFINES
#include <math.h>

class	UFloatShort
{
#pragma	pack(push,1)
	BYTE	Integer;
	BYTE	Decimal;
#pragma	pack(pop)

public:
	UFloatShort(void)								{	Integer=0;	Decimal=0;	}
	explicit	UFloatShort(int n)					{	Integer=n;	Decimal=0;	}
	explicit	UFloatShort(double n)				{	Integer=(BYTE)n;	Decimal=(n-floor(n))*256.0;	}
	UFloatShort(const UFloatShort &src)	{	Integer=src.Integer;	Decimal=src.Decimal;	}

	UFloatShort	&operator=(int n);
	UFloatShort	&operator=(double n);
	UFloatShort	&operator=(const UFloatShort &src);
	UFloatShort	&operator+=(const UFloatShort &src);
	UFloatShort	&operator-=(const UFloatShort &src);
	friend	UFloatShort	operator+(const UFloatShort &src1 ,const UFloatShort &src2);
	friend	UFloatShort	operator-(const UFloatShort &src1 ,const UFloatShort &src2);
	friend	UFloatShort	operator*(const UFloatShort &src1 ,const UFloatShort &src2);
	friend	UFloatShort	operator/(const UFloatShort &src1 ,const UFloatShort &src2);

	UFloatShort	&operator++(void);
	UFloatShort	&operator--(void);

	bool	operator==(const UFloatShort &src)	const;
	bool	operator!=(const UFloatShort &src)	const;

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	int		GetInt(void)	const	{	return Integer;	}
	int		GetCeil(void)	const	{	return (Decimal==0)?Integer:Integer+1;	}
	float	GetFloat(void) const	{	return Integer+(Decimal/256.0);		}
};

#endif