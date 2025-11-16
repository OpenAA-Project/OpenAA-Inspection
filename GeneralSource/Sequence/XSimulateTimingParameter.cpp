/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\Sequence\XSimulateTimingParameter.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


//---------------------------------------------------------------------------

#include "XSimulateTimingParameter.h"
#include "XSequenceFile.h"
#include "XTypeDef.h"

//---------------------------------------------------------------------------

char    *SeqTimingParameter::ParamFileName="TmParam.dat";


void    SeqTimingParameter::ToDefault(void)
{
    ItemHeight=24;
    MaxTimsMS =5*60*1000;   //デフォルト5分

    BKColor1=clWhite;
    BKColor2=clYellow;
    MeasureColor=clBlack;

    DefaultLineWidth=1;
    DefaultLineColor=clRed;

    DefaultFontName=/**/"";
    DefaultCharset=ANSI_CHARSET;
    DefaultFontSize=9;
    //DefaultFontStyle;
    DefaultFontColor=clBlack;
    DefaultArrowSize=10;
}
bool    SeqTimingParameter::Write(QIODevice *os)
{
    int Ver=TimingParamVersion;

    if(os->write((const char *)&Ver,sizeof(Ver))!=sizeof(Ver))
        return(false);
    if(os->write((const char *)&ItemHeight,sizeof(ItemHeight))!=sizeof(ItemHeight))
        return(false);
    if(os->write((const char *)&MaxTimsMS,sizeof(MaxTimsMS))!=sizeof(MaxTimsMS))
        return(false);
    if(os->write((const char *)&BKColor1,sizeof(BKColor1))!=sizeof(BKColor1))
        return(false);
    if(os->write((const char *)&BKColor2,sizeof(BKColor2))!=sizeof(BKColor2))
        return(false);
    if(os->write((const char *)&MeasureColor,sizeof(MeasureColor))!=sizeof(MeasureColor))
        return(false);
    if(os->write((const char *)&DefaultLineWidth,sizeof(DefaultLineWidth))!=sizeof(DefaultLineWidth))
        return(false);
    if(os->write((const char *)&DefaultLineColor,sizeof(DefaultLineColor))!=sizeof(DefaultLineColor))
        return(false);

    if(Save(os,DefaultFontName)!=true)
        return(false);
    if(os->write((const char *)&DefaultCharset,sizeof(DefaultCharset))!=sizeof(DefaultCharset))
        return(false);
    if(os->write((const char *)&DefaultFontSize,sizeof(DefaultFontSize))!=sizeof(DefaultFontSize))
        return(false);
    if(os->write((const char *)&DefaultFontStyle,sizeof(DefaultFontStyle))!=sizeof(DefaultFontStyle))
        return(false);
    if(os->write((const char *)&DefaultFontColor,sizeof(DefaultFontColor))!=sizeof(DefaultFontColor))
        return(false);
    if(os->write((const char *)&DefaultArrowSize,sizeof(DefaultArrowSize))!=sizeof(DefaultArrowSize))
        return(false);

    return(true);
}
bool    SeqTimingParameter::Read(QIODevice *is)
{
    int Ver;
    if(is->read((char *)&Ver,sizeof(Ver))!=sizeof(Ver))
        return(false);
    if(is->read((char *)&ItemHeight,sizeof(ItemHeight))!=sizeof(ItemHeight))
        return(false);
    if(is->read((char *)&MaxTimsMS,sizeof(MaxTimsMS))!=sizeof(MaxTimsMS))
        return(false);
    if(is->read((char *)&BKColor1,sizeof(BKColor1))!=sizeof(BKColor1))
        return(false);
    if(is->read((char *)&BKColor2,sizeof(BKColor2))!=sizeof(BKColor2))
        return(false);
    if(is->read((char *)&MeasureColor,sizeof(MeasureColor))!=sizeof(MeasureColor))
        return(false);
    if(is->read((char *)&DefaultLineWidth,sizeof(DefaultLineWidth))!=sizeof(DefaultLineWidth))
        return(false);
    if(is->read((char *)&DefaultLineColor,sizeof(DefaultLineColor))!=sizeof(DefaultLineColor))
        return(false);

    if(Load(is,DefaultFontName)!=true)
        return(false);
    if(is->read((char *)&DefaultCharset,sizeof(DefaultCharset))!=sizeof(DefaultCharset))
        return(false);
    if(is->read((char *)&DefaultFontSize,sizeof(DefaultFontSize))!=sizeof(DefaultFontSize))
        return(false);
    if(is->read((char *)&DefaultFontStyle,sizeof(DefaultFontStyle))!=sizeof(DefaultFontStyle))
        return(false);
    if(is->read((char *)&DefaultFontColor,sizeof(DefaultFontColor))!=sizeof(DefaultFontColor))
        return(false);
    if(is->read((char *)&DefaultArrowSize,sizeof(DefaultArrowSize))!=sizeof(DefaultArrowSize))
        return(false);
    return(true);
}

SeqTimingParameter &SeqTimingParameter::operator=(SeqTimingParameter &src)
{
    ItemHeight      =src.ItemHeight;
    MaxTimsMS       =src.MaxTimsMS;

    BKColor1        =src.BKColor1;
    BKColor2        =src.BKColor2;
    MeasureColor    =src.MeasureColor;

    DefaultLineWidth=src.DefaultLineWidth;
    DefaultLineColor=src.DefaultLineColor;

    DefaultFontName =src.DefaultFontName ;
    DefaultCharset  =src.DefaultCharset  ;
    DefaultFontSize =src.DefaultFontSize ;
    DefaultFontStyle=src.DefaultFontStyle;
    DefaultFontColor=src.DefaultFontColor;
    DefaultArrowSize=src.DefaultArrowSize;
    return(*this);
}

int     SeqTimingParameter::GetDataLength(void)
{
    TMemoryStream   *d=new TMemoryStream();

    Write(d);
    int Len=d->Size;
    delete  d;
    return(Len);
}

