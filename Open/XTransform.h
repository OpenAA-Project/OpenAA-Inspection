/*
 * Copyright (C) 2023
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

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