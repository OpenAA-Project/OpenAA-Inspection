#if	!defined(XCOMPLEX_H)
#define	XCOMPLEX_H

#include "XTypeDef.h"

class	DoubleComplex
{
	double	Real,Imag;
public:
	DoubleComplex(void){}
	DoubleComplex(double r, double i):Real(r),Imag(i){}
	DoubleComplex(const DoubleComplex &src);

	DoubleComplex	&operator=(const DoubleComplex &src);
	DoubleComplex	&operator+=(const DoubleComplex &src);
	DoubleComplex	&operator-=(const DoubleComplex &src);
	DoubleComplex	&operator*=(const DoubleComplex &src);
	DoubleComplex	&operator/=(const DoubleComplex &src);
	DoubleComplex	&operator*=(const double src);
	DoubleComplex	&operator/=(const double src);

	bool	operator==(const DoubleComplex &src)	const;
	bool	operator!=(const DoubleComplex &src)	const;

	DoubleComplex	operator+(const DoubleComplex &src1);
	DoubleComplex	operator-(const DoubleComplex &src1);
	DoubleComplex	operator*(const DoubleComplex &src1);
	DoubleComplex	operator/(const DoubleComplex &src1);

	double	imag()	const	{		return Imag;	}
	double	real()	const	{		return Real;	}
	void	set(double re ,double img)	{	Real=re;	Imag=img;	}

	inline	double	norm()	const
	{
		return real()*real()+imag()*imag();
	}
};


inline	DoubleComplex	&DoubleComplex::operator=(const DoubleComplex &src)
{
	Real=src.Real;	Imag=src.Imag;
	return *this;
}
inline	DoubleComplex	&DoubleComplex::operator+=(const DoubleComplex &src)
{
	Real+=src.Real;	Imag+=src.Imag;
	return *this;
}
inline	DoubleComplex	&DoubleComplex::operator-=(const DoubleComplex &src)
{
	Real-=src.Real;	Imag-=src.Imag;
	return *this;
}
inline	DoubleComplex	&DoubleComplex::operator*=(const DoubleComplex &src)
{
	double	tReal=src.Real*Real-src.Imag*Imag;
	double	tImag=src.Real*Imag+src.Imag*Real;
	Real=tReal;
	Imag=tImag;
	return *this;
}
inline	DoubleComplex	&DoubleComplex::operator/=(const DoubleComplex &src)
{
	double	D=src.Real*src.Real+src.Imag*src.Imag;
	if(D!=0.0){
		double	tReal=(src.Real*Real+src.Imag*Imag)/D;
		double	tImag=(src.Real*Imag-src.Imag*Real)/D;
		Real=tReal;
		Imag=tImag;
	}
	else{
	}
	return *this;
}

inline	DoubleComplex	&DoubleComplex::operator*=(const double src)
{
	set(Real*src,Imag*src);
	return *this;
}
inline	DoubleComplex	&DoubleComplex::operator/=(const double src)
{
	set(Real/src,Imag/src);
	return *this;
}

inline	bool	DoubleComplex::operator==(const DoubleComplex &src)	const
{
	if(Real==src.Real && Imag==src.Imag){
		return true;
	}
	return false;
}
inline	bool	DoubleComplex::operator!=(const DoubleComplex &src)	const
{
	if(Real!=src.Real || Imag!=src.Imag){
		return true;
	}
	return false;
}

inline	DoubleComplex	DoubleComplex::operator+(const DoubleComplex &src)
{
	DoubleComplex	Ret(Real+src.Real,	Imag+src.Imag);
	return Ret;
}
inline	DoubleComplex	DoubleComplex::operator-(const DoubleComplex &src)
{
	DoubleComplex	Ret(Real-src.Real,	Imag-src.Imag);
	return Ret;
}
inline	DoubleComplex	DoubleComplex::operator*(const DoubleComplex &src)
{
	DoubleComplex	Ret(src.Real*Real-src.Imag*Imag,src.Real*Imag+src.Imag*Real);
	return Ret;
}
inline	DoubleComplex	DoubleComplex::operator/(const DoubleComplex &src)
{
	double	D=src.Real*src.Real+src.Imag*src.Imag;
	if(D!=0.0){
		double	tReal=(src.Real*Real+src.Imag*Imag)/D;
		double	tImag=(src.Real*Imag-src.Imag*Real)/D;
		DoubleComplex	Ret(tReal,	tImag);
		return Ret;
	}
	else{
		DoubleComplex	Ret;
		return Ret;
	}
}
#endif
