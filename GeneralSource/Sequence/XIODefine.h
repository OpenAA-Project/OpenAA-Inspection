/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\Sequence\XIODefine.h
** Author : YYYYYYYYYY
****************************************************************************-**/


//---------------------------------------------------------------------------

#ifndef XIODefineH
#define XIODefineH
//---------------------------------------------------------------------------

#include <QString>
#include "XTypeDef.h"

class   IODefineClass
{
  public:
    QString  FileName;

    IODefineClass(void);
    ~IODefineClass(void);
    void    Release(void);

    int         BoardNumb;
    int         *INumb;
    int         *ONumb;

    bool    GetIName(int brdnum,int port ,int bit ,QString &ret)    const;
    bool    GetOName(int brdnum,int port ,int bit ,QString &ret)    const;

    char    ***DefInName;
    char    ***DefOutName;
    bool    ReadDefFile(char *DefFileName);
};


#endif
 