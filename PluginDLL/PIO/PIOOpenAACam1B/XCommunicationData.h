#ifndef XCOMMUNICATIONDATA_H
#define XCOMMUNICATIONDATA_H

#pragma pack(push, 1)

struct CommDataCam1BMoSi
{
    bool     Out0:1;
    bool     Out1:1;
    bool     Out2:1;
    bool     Out3:1;

    bool     CamLine0:1; //To Camera

    bool     Light0Enable:1;
    bool     Light1Enable:1;

    short   CamTriggerMode;

    unsigned short  Light0Value;
    unsigned short  Light1Value;
};

struct CommDataCam1BMiSo
{
    bool     Inp0:1;
    bool     Inp1:1;
    bool     Inp2:1;
    bool     Inp3:1;

    bool     CamLine1:1; //From Camera

    bool     SW0:1;
    bool     SW1:1;
    bool     SW2:1;

    unsigned short  AD0Light;
    unsigned short  AD1Light;
};

#pragma pack(pop)


#endif // XCOMMUNICATIONDATA_H
