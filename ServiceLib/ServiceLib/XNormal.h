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

#if	!defined(XNORMAL_H)
#define	XNORMAL_H

#include "XTypeDef.h"
class NormalDistribution
{
  double _mu;  // ����
  double _var; // ���U

public:

  /*
    �R���X�g���N�^

    double mu : ����
    double sigma : �W���΍�
  */
  NormalDistribution( double mu, double sigma );

  // �m���ϐ� a �ɂ������m�����x���Ԃ�
  double operator[]( double x ) const;

  // ���� (-��,a] �ɂ������m�����Ԃ�
  double lower_p( double a ) const;

  // ���� [a,b] �ɂ������m�����Ԃ�
  double p( double a, double b ) const;

  double average() const { return( _mu ); }   // ���ϒl
  double variance() const { return( _var ); } // ���U
};

double qnorm(double u);
double pnorm(double qn);


#endif