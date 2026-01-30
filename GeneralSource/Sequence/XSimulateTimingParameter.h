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

#ifndef XSimulateTimingParameterH
#define XSimulateTimingParameterH
//---------------------------------------------------------------------------
#include <QColor>
#include <QString>
#include <QIODevice>

//#include "XUniversalDefinition.h"

#define TimingParamVersion  1


class   SeqTimingParameter
{
  public:
    int         ItemHeight;
    long double MaxTimsMS;

    QColor      BKColor1;
    QColor      BKColor2;
    QColor      MeasureColor;

    int         DefaultLineWidth;
    QColor      DefaultLineColor;

    QString  DefaultFontName;	//D-20051026
    int         DefaultFontSize;
    QColor      DefaultFontColor;	//D-20051026
    int         DefaultArrowSize;

    static  char    *ParamFileName;

    SeqTimingParameter(void){}

    void    ToDefault(void);
    bool    Write(QIODevice *os);
    bool    Read(QIODevice *is);
    int     GetDataLength(void);

    SeqTimingParameter &operator=(SeqTimingParameter &src);
};


#endif