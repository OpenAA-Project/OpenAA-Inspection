/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\Sequence\XSimulateTimingParameter.h
** Author : YYYYYYYYYY
****************************************************************************-**/


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
