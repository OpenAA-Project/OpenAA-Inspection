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

//---------------------------------------------------------------------------

#ifndef XFFT1dH
#define XFFT1dH
//---------------------------------------------------------------------------
#define	_COMPLEX_DEFINED
#include "XComplex.h"
#include <iostream>

#include "XTypeDef.h"

#define  maxPrimeFactor        37
#define  maxPrimeFactorDiv2    (maxPrimeFactor+1)/2
#define  maxFactorCount        20

class	FFTClass
{
	int      groupOffset,dataOffset,adr;
	int      groupNo,dataNo,blockNo,twNo;
	double   omega, tw_re,tw_im;
	double   twiddleRe[maxPrimeFactor], twiddleIm[maxPrimeFactor];
    double   trigRe[maxPrimeFactor], trigIm[maxPrimeFactor];
    double   zRe[maxPrimeFactor], zIm[maxPrimeFactor];
	double   vRe[maxPrimeFactorDiv2], vIm[maxPrimeFactorDiv2];
	double   wRe[maxPrimeFactorDiv2], wIm[maxPrimeFactorDiv2];
public:

	bool fft(int n, DoubleComplex x[] ,DoubleComplex y[]);
	bool fftPower(int n, BYTE   x[] ,double y[]);
	bool fftPower(int n, int    x[] ,double y[]);
	bool fftPower(int n, double x[] ,double y[]);
	bool reversefft(int n, DoubleComplex InpData[] ,DoubleComplex ResultOut[]);
private:
	void factorize(int n, int *nFact, int fact[]);
	bool transTableSetup(int sofar[], int actual[], int remain[],
                     int *nFact,
                     int *nPoints);
	void permute(int nPoint, int nFact,
             int fact[], int remain[],
             DoubleComplex x[], DoubleComplex y[] );
	void initTrig(int radix);
	void fft_4(double aRe[], double aIm[]);
	void fft_5(double aRe[], double aIm[]);
	void fft_8();
	void fft_10();
	void fft_odd(int radix);
	void twiddleTransf(int sofarRadix, int radix, int remainRadix,
                    DoubleComplex y[]);

};

#endif