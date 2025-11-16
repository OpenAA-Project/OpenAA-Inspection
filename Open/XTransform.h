#pragma once

#include <QIODevice>
class XYPointContainerWithName;

class TransformBase
{
public:
	TransformBase(void);
	virtual	~TransformBase(void);

	virtual	bool	Save(QIODevice *f)	=0;
	virtual	bool	Load(QIODevice *f)	=0;

	virtual	TransformBase	*clone(void)=0;

	virtual	TransformBase &operator*=(const TransformBase &src)	=0;
	virtual	bool	Reverse(void)						=0;

	virtual	bool	Transform		(double X,double Y,double &RetX ,double &RetY)	=0;
	virtual	bool	ReverseTransform(double X,double Y,double &RetX ,double &RetY)	=0;
	static	TransformBase	*MakeTransformParamControlPoints(const XYPointContainerWithName &Dst ,const XYPointContainerWithName &Src);
};

class TransformAffin : public TransformBase
{
public:
	double	Param[6];

	TransformAffin(void);
	TransformAffin(const TransformAffin &src);
	TransformAffin(double Param[6]);
	TransformAffin(double a ,double b ,double c ,double d ,double e ,double f);

	virtual	TransformBase	*clone(void)	override;
	TransformAffin	&operator=(const TransformAffin &src);
	virtual	TransformBase &operator*=(const TransformBase &src)	override;
	virtual	bool	Reverse(void)	override;

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;

	virtual	bool	Transform		(double X,double Y,double &RetX ,double &RetY)	override;
	virtual	bool	ReverseTransform(double X,double Y,double &RetX ,double &RetY)	override;
};