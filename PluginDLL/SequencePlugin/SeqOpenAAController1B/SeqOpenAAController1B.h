#pragma once

#include "seqopenaacontroller1b_global.h"
#include "XServiceForLayers.h"
#include <QTcpSocket>

#define OpenAAController1BSeqPort   43501

class SeqOpenAAController1B :public QObject ,public ServiceForLayers
{
    QTcpSocket  *Sock;
    QString     IPAddress;
public:

    SeqOpenAAController1B(LayersBase *base,const QString &Param);
    ~SeqOpenAAController1B(void);

    bool    ConnectToHost();
    bool    SendOK();
    bool    SendNG();

};
