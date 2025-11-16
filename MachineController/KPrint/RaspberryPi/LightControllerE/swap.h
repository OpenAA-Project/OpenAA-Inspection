/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\swap.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef SWAP
#define SWAP
#include <qglobal.h>
inline	void swap(qint64 &x,qint64 &y)
{
	qint64	k;

	k=x;
	x=y;
	y=k;

}
inline	void swap(int &x,int &y)
{
	int	k;

	k=x;
	x=y;
	y=k;

}
inline	void swap(unsigned int &x,unsigned int &y)
{
	unsigned int	k;

	k=x;
	x=y;
	y=k;

}

inline	void swap(long &x,long &y)
{
	long	k;

	k=x;
	x=y;
	y=k;

}

inline	void swap(unsigned long &x,unsigned long &y)
{
	unsigned long	k;

	k=x;
	x=y;
	y=k;

}

inline	void swap(short &x,short &y)
{
	short	k;

	k=x;
	x=y;
	y=k;

}
inline	void swap(unsigned short &x,unsigned short &y)
{
	unsigned short	k;

	k=x;
	x=y;
	y=k;

}

inline	void swap(char &x,char &y)
{
	char	k;

	k=x;
	x=y;
	y=k;

}
inline	void swap(unsigned char &x,unsigned char &y)
{
	unsigned char	k;

	k=x;
	x=y;
	y=k;

}

inline	void swap(float &x,float &y)
{
	float	k;

	k=x;
	x=y;
	y=k;

}

inline	void swap(double &x,double &y)
{
	double	k;

	k=x;
	x=y;
	y=k;

}

inline	int	max(qint64 x,qint64 y)
{
	if(x>y) return(x);
	return(y);
}
inline	int	max(int x,int y)
{
	if(x>y) return(x);
	return(y);
}
inline	int	max(short int x,int y)
{
	if(x>y) return(x);
	return(y);
}
inline	int	max(int x,short int y)
{
	if(x>y) return(x);
	return(y);
}
inline	int	max(unsigned short int x,int y)
{
	if((unsigned int)x>(unsigned int)y) return(x);
	return(y);
}
inline	int	max(int x,unsigned short int y)
{
	if((unsigned int)x>(unsigned int)y) return(x);
	return(y);
}
inline	int	max(short int x,unsigned int y)
{
	if((unsigned int)x>(unsigned int)y) return(x);
	return(y);
}
inline	int	max(unsigned int x,short int y)
{
	if((unsigned int)x>(unsigned int)y) return(x);
	return(y);
}
inline	unsigned int	 max(unsigned int x,unsigned int y)
{
	if(x>y) return(x);
	return(y);
}
inline	short	max(short x,short y)
{
	if(x>y) return(x);
	return(y);
}
inline	unsigned short	max(unsigned short x,unsigned short y)
{
	if(x>y) return(x);
	return(y);
}
inline	long	max(long x,long y)
{
	if(x>y) return(x);
	return(y);
}
inline	unsigned long	 max(unsigned long x,unsigned long y)
{
	if(x>y) return(x);
	return(y);
}

inline	double	max(double x,double y)
{
	if(x>y) return(x);
	return(y);
}

inline	int	min(qint64 x,qint64 y)
{
	if(x<y) return(x);
	return(y);
}
inline	int	min(int x,int y)
{
	if(x<y) return(x);
	return(y);
}

inline	int	min(short int x,int y)
{
	if(x<y) return(x);
	return(y);
}

inline	int	min(int x,short int y)
{
	if(x<y) return(x);
	return(y);
}

inline	int	min(unsigned short int x,int y)
{
	if((unsigned int)x<(unsigned int)y) return(x);
	return(y);
}

inline	int	min(int x,unsigned short int y)
{
	if((unsigned int)x<(unsigned int)y) return(x);
	return(y);
}

inline	int	min(short int x,unsigned int y)
{
	if((unsigned int)x<(unsigned int)y) return(x);
	return(y);
}

inline	int	min(unsigned int x,short int y)
{
	if((unsigned int)x<(unsigned int)y) return(x);
	return(y);
}
inline	unsigned int	 min(unsigned int x,unsigned int y)
{
	if(x<y) return(x);
	return(y);
}
inline	short	min(short x,short y)
{
	if(x<y) return(x);
	return(y);
}
inline	unsigned short	min(unsigned short x,unsigned short y)
{
	if(x<y) return(x);
	return(y);
}
inline	long	min(long x,long y)
{
	if(x<y) return(x);
	return(y);
}
inline	unsigned long	 min(unsigned long x,unsigned long y)
{
	if(x<y) return(x);
	return(y);
}

inline	double	min(double x,double y)
{
	if(x<y) return(x);
	return(y);
}

/*
inline long abs(long x)
{
	if(x>=0)	return(x);
	return(-x);
}
*/
inline short abs(short	x)
{
	if(x>=0)	return(x);
	return((short)-x);
}
inline char abs(char x)
{
	if(x>=0)	return(x);
	return((char)-x);
}

inline	int	diff(int x,int y)
{
	return((x>=y)?x-y:y-x);
}

inline	unsigned short SwapHL(unsigned short c)
{
	return((*((unsigned char *)&c)<<8)+ *(((unsigned char *)&c)+1));
}


inline	int	Clipping(int d ,int LMin ,int LMax)
{
    if(d<LMin)
		return LMin;
	if(d>LMax)
		return LMax;
	return d;
}

inline	unsigned char	ClipByte(int d)
{
	if(d<0)
		return 0;
	if(d>255)
		return 255;
	return	d;
}

inline	short	Clipping(short d ,short LMin ,short LMax)
{
    if(d<LMin)
		return LMin;
	if(d>LMax)
		return LMax;
	return d;
}

inline	double	Clipping(double d ,double LMin ,double LMax)
{
    if(d<LMin)
		return LMin;
	if(d>LMax)
		return LMax;
	return d;
}

inline	short SwapByte(short x)
{
	return ((*((unsigned char*)&x))<<8) + *(((unsigned char*)&x)+1);
}


#endif
