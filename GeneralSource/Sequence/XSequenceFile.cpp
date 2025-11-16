/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\Sequence\XSequenceFile.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


//---------------------------------------------------------------------------

#include <vcl.h>
#include <values.h>
#define	_USE_MATH_DEFINES
#include <math.h>
#pragma hdrstop

#include "XSequenceFile.h"
#include "XSequence.h"
#include "XBsearch.h"
#include "XSimulateTimingParameter.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)


LoadedTimingSlice::LoadedTimingSlice(void)
{
    TDHeader.DType=0;
    Data=NULL;
}

LoadedTimingSlice::~LoadedTimingSlice(void)
{
    if(TDHeader.DType==3){
        if(Data!=NULL)
            delete  []Data;
        Data=NULL;
        }
}

AnsiString  LoadedTimingSlice::GetString(void)
{
    return(AnsiString((char *)Data));
}


LoadedTimingFile::LoadedTimingFile(void)
{
    SeqData=NULL;
}
LoadedTimingFile::~LoadedTimingFile(void)
{
    if(SeqData!=NULL)
        delete  []SeqData;
    SeqData=NULL;
}

int    LoadedTimingFile::Initial(void)
{
    int LNumb=0;
    LBase.RemoveAll();

    for(IOOperand *i=SeqControl::IOOpe.GetFirst();i!=NULL;i=i->GetNext()){
        SSTimingList    *p=new SSTimingList();
        p->Point=i;
        LBase.AppendList(p);
        LNumb++;
        }

    for(CommOperand *i=SeqControl::CommOpe.GetFirst();i!=NULL;i=i->GetNext()){
        SSTimingList    *p=new SSTimingList();
        p->Point=i;
        LNumb++;
        LBase.AppendList(p);
        }
    for(BitOperand *i=SeqControl::BitOpe.GetFirst();i!=NULL;i=i->GetNext()){
        SSTimingList    *p=new SSTimingList();
        p->Point=i;
        LNumb++;
        LBase.AppendList(p);
        }
    for(WordOperand *i=SeqControl::WordOpe.GetFirst();i!=NULL;i=i->GetNext()){
        SSTimingList    *p=new SSTimingList();
        p->Point=i;
        LNumb++;
        LBase.AppendList(p);
        }
    for(StringOperand *i=SeqControl::StringOpe.GetFirst();i!=NULL;i=i->GetNext()){
        SSTimingList    *p=new SSTimingList();
        p->Point=i;
        LNumb++;
        LBase.AppendList(p);
        }
    for(SpecialOperand *i=SeqControl::SpecialOpe.GetFirst();i!=NULL;i=i->GetNext()){
        SSTimingList    *p=new SSTimingList();
        p->Point=i;
        LNumb++;
        LBase.AppendList(p);
        }
    for(SpecialBitOperand *i=SeqControl::SpecialBitOpe.GetFirst();i!=NULL;i=i->GetNext()){
        SSTimingList    *p=new SSTimingList();
        p->Point=i;
        LNumb++;
        LBase.AppendList(p);
        }
    for(GroupOperand *i=SeqControl::GroupOpe.GetFirst();i!=NULL;i=i->GetNext()){
        SSTimingList    *p=new SSTimingList();
        p->Point=i;
        LNumb++;
        LBase.AppendList(p);
        }
    for(LanvarOperand *i=SeqControl::LanvarOpe.GetFirst();i!=NULL;i=i->GetNext()){
        SSTimingList    *p=new SSTimingList();
        p->Point=i;
        LNumb++;
        LBase.AppendList(p);
        }
    FlowList.RemoveAll();
    AddedVector.RemoveAll();
    return(LNumb);
}

bool    LoadedTimingSlice::Read(TFileStream *rfile)
{
    if(TDHeader.DType==1){
        if(rfile->Read(&D,sizeof(D))!=sizeof(D))
            return(false);
        }
    if(TDHeader.DType==2){
        ByteLen=TDHeader.DataSize-sizeof(TDHeader);
        Data=new BYTE[ByteLen];
        if(rfile->Read(Data,ByteLen)!=ByteLen)
            return(false);
        }
    if(TDHeader.DType==3){
        ByteLen=TDHeader.DataSize-sizeof(TDHeader);
        Data=new BYTE[ByteLen];
        if(rfile->Read(Data,ByteLen)!=ByteLen)
            return(false);
        }
    return(true);
}

bool    LoadedTimingSlice::Write(TFileStream *wfile)
{
    if(TDHeader.DType==1){
        if(wfile->Write(&D,sizeof(D))!=sizeof(D))
            return(false);
        }
    if(TDHeader.DType==2){
        if(wfile->Write(Data,ByteLen)!=ByteLen)
            return(false);
        }
    if(TDHeader.DType==3){
        if(wfile->Write(Data,ByteLen)!=ByteLen)
            return(false);
        }
    return(true);
}

__TimingOperandHeader::__TimingOperandHeader(void)
{
    memset(Explain,0,sizeof(Explain));
    OpeExtendByte=0;
    OType        =200;
}

SSOperandClass::SSOperandClass(void)
{
    GroupDetail=NULL;
    LanvarDetail=NULL;
}
SSOperandClass::~SSOperandClass(void)
{
    if(GroupDetail!=NULL)
        delete  []GroupDetail;
    GroupDetail=NULL;

    if(LanvarDetail!=NULL)
        delete  []LanvarDetail;
    LanvarDetail=NULL;
}
SSOperandClass  &SSOperandClass::operator=(Operand &src)
{
    Data.OType  = src.GetKindCode();
    Data.ONumber= src.GetID();

    Data.OpeExtendByte=0;
    if(Data.OType==KindCodeIO){
        IOOperand   *c=dynamic_cast<IOOperand *>(&src);
        if(c!=NULL){
            Data.ForIO.BoardNumb    =c->BoardNumber;
            Data.ForIO.PortNumb     =c->PortNumber;
            Data.ForIO.BitNumb      =c->BitNumber;
            }
        }
    else
    if(Data.OType==KindCodeComm){
        CommOperand   *c=dynamic_cast<CommOperand *>(&src);
        if(c!=NULL){
            Data.ForComm.CommPort  = c->CommPort;
            Data.ForComm.BPS       = c->BPS;
            Data.ForComm.Parity    = c->Parity;
            Data.ForComm.Stopbit   = c->Stopbit;
            Data.ForComm.Character = c->Character;
            }
        }
    else
    if(Data.OType==KindCodeGroup){
        GroupOperand   *c=dynamic_cast<GroupOperand *>(&src);
        for(int i=0;i<GroupBitCount;i++){
            if(c->EachBitPoint[i]!=NULL)
                Data.OpeExtendByte+=sizeof(struct __TimingOperandGroup);
            }
        DetailNumb=Data.OpeExtendByte/sizeof(struct __TimingOperandGroup);
        GroupDetail=new struct  __TimingOperandGroup[DetailNumb];

        int N=0;
        for(int i=0;i<GroupBitCount;i++){
            if(c->EachBitPoint[i]!=NULL){
                GroupDetail[N].OType  =(BYTE)c->EachBitPoint[i]->GetKindCode();
                GroupDetail[N].ONumber=(BYTE)c->EachBitPoint[i]->GetID();
                N++;
                }
            }
        }
    else
    if(Data.OType==KindCodeLanvar){
        LanvarOperand   *c=dynamic_cast<LanvarOperand *>(&src);
        DetailNumb=c->IP.GetNumber();
        Data.OpeExtendByte=DetailNumb*sizeof(struct __TimingOperandLanvar);
        LanvarDetail=new struct __TimingOperandLanvar[DetailNumb];

        int N=0;
        for(IPList *ip=c->IP.GetFirst();ip!=NULL;ip=ip->GetNext(),N++){
            struct  __TimingOperandLanvar   dummy;
            LanvarDetail[N].IP[sizeof(dummy.IP)-1]=0;
            strncpy(LanvarDetail[N].IP,ip->IPAddress.c_str(),sizeof(dummy.IP));
            }
        }

    Data.NameLen=strlen(src.GetName());
    memset(Data.Explain,0,sizeof(Data.Explain));
    strncpy(Data.Explain,src.GetComment().c_str(),sizeof(Data.Explain)-1);

    Name=src.GetName();

    return(*this);
}

bool    LoadedTimingFile::Read(TFileStream *rfile)
{
    char    buff[1024];

    if(rfile->Read(&FileHeader,sizeof(FileHeader))!=sizeof(FileHeader))
        return(false);
    if(SeqData!=NULL)
        delete  []SeqData;
    SeqData=new struct __TimingSeq[FileHeader.SeqNumb];
    for(int i=0;i<FileHeader.SeqNumb;i++){
        if(rfile->Read(&SeqData[i].Header,sizeof(SeqData[i].Header))!=sizeof(SeqData[i].Header))
            return(false);
        if(rfile->Read(buff,SeqData[i].Header.NameLen)!=SeqData[i].Header.NameLen)
            return(false);
        SeqData[i].Name=buff;
        }

    for(int i=0;i<FileHeader.NamedOperandNumb;i++){
        SSOperandClass  *d=new SSOperandClass();
        if(rfile->Read(&d->Data,sizeof(d->Data))!=sizeof(d->Data))
            return(false);
        if(rfile->Read(buff,d->Data.NameLen)!=d->Data.NameLen)
            return(false);
        d->Name=buff;
        if(d->Data.OType==KindCodeGroup){
            d->DetailNumb=d->Data.OpeExtendByte/sizeof(struct __TimingOperandGroup);
            d->GroupDetail=new struct  __TimingOperandGroup[d->DetailNumb];
            for(int j=0;j<d->DetailNumb;j++){
                if(rfile->Read(&d->GroupDetail[j],sizeof(struct __TimingOperandGroup))!=sizeof(struct __TimingOperandGroup))
                    return(false);
                }
            }
        else
        if(d->Data.OType==KindCodeLanvar){
            d->DetailNumb=d->Data.OpeExtendByte/sizeof(struct __TimingOperandLanvar);
            d->LanvarDetail=new struct __TimingOperandLanvar[d->DetailNumb];
            for(int j=0;j<d->DetailNumb;j++){
                if(rfile->Read(&d->LanvarDetail[j],sizeof(struct __TimingOperandLanvar))!=sizeof(struct __TimingOperandLanvar))
                    return(false);
                }
            }
        OpeData.AppendList(d);

        if(d->Data.OType>=200){
            SSTimingList    *m=new SSTimingList();
            m->UserOpe=d;
            switch(d->Data.Kind){
                case __TOK_IO:
                    m->Kind=SSTimingList::__STL_Binary;
                    break;
                case __TOK_Bit:
                    m->Kind=SSTimingList::__STL_Binary;
                    break;
                case __TOK_Word:
                    m->Kind=SSTimingList::__STL_Word;
                    break;
                case __TOK_String:
                    m->Kind=SSTimingList::__STL_String;
                    break;
                case __TOK_Comm:
                    m->Kind=SSTimingList::__STL_String;
                    break;
                case __TOK_Lanvar:
                    m->Kind=SSTimingList::__STL_String;
                    break;
                case __TOK_Fifo:
                    m->Kind=SSTimingList::__STL_String;
                    break;
                }
            LBase.AppendList(m);
            }
        }

    //インデックステンポラリファイルの作成
    SSTimingList    **InPoint[256];
    for(int i=0;i<256;i++){
        InPoint[i]=new SSTimingList *[2048];
        for(int j=0;j<2048;j++){
            InPoint[i][j]=NULL;
            }
        }
    for(SSTimingList *k=LBase.GetFirst();k!=NULL;k=k->GetNext()){
        InPoint[k->Point->GetKindCode()][k->Point->GetID()]=k;
        }

    AddedVector.RemoveAll();
    for(;;){
        struct  __TimingDataHeader  TDHeader;
        if(rfile->Read(&TDHeader,sizeof(TDHeader))!=sizeof(TDHeader)){
            break;
            }
        if(TDHeader.DType==1 || TDHeader.DType==2 || TDHeader.DType==3){
            LoadedTimingSlice   *s=new LoadedTimingSlice();

            s->TDHeader=TDHeader;
            if(s->Read(rfile)==false){
                delete  s;
                break;
                }
            SSTimingList *k=InPoint[(s->TDHeader.OType)&255][(s->TDHeader.ONumber)&2047];
            if(k==NULL){
                delete  s;
                continue;
                }
            k->TimingData.AppendList(s);
            SSTimingFlowList    *h=new SSTimingFlowList();
            h->List =k;
            h->Point=s;
            FlowList.AppendList(h);
            }
        else
        if(TDHeader.DType==4){
            if(ReadParam(rfile)==false)
                break;
            }
        else
        if(TDHeader.DType==5){
            if(TDHeader.ONumber==1){
                AddedVectorSingleArrow  *v=new AddedVectorSingleArrow();
                if(v->Read(rfile)==false)
                    break;
                AddedVector.AppendList(v);
                }
            else
            if(TDHeader.ONumber==2){
                AddedVectorBothArrow  *v=new AddedVectorBothArrow();
                if(v->Read(rfile)==false)
                    break;
                AddedVector.AppendList(v);
                }
            else
            if(TDHeader.ONumber==3){
                AddedVectorFontChar  *v=new AddedVectorFontChar();
                if(v->Read(rfile)==false)
                    break;
                AddedVector.AppendList(v);
                }
            }
        }
    for(int i=0;i<256;i++){
        delete  []InPoint[i];
        }
    for(SSTimingList *r=LBase.GetFirst();r!=NULL;r=r->GetNext()){
        r->BuildTimingTable();

        LoadedTimingSlice *c=r->TimingData.GetFirst();
        if(c==NULL){
            r->Kind=SSTimingList::__STL_UnKnown;
            continue;
            }
        if(c->TDHeader.DType==1 || c->TDHeader.DType==2 ){
            r->MaxData=-MAXDOUBLE;
            r->MinData=MAXDOUBLE;
            for(LoadedTimingSlice *c=r->TimingData.GetFirst();c!=NULL;c=c->GetNext()){
                if(r->MaxData<c->GetInt())
                    r->MaxData=c->GetInt();
                if(r->MinData>c->GetInt())
                    r->MinData=c->GetInt();
                }
            if((fabs(r->MaxData-1.0)<0.00001 && fabs(r->MinData)<0.00001)
            || (fabs(r->MaxData)<0.00001 && fabs(r->MinData)<0.00001)
            || (fabs(r->MaxData-1.0)<0.00001 && fabs(r->MinData-1.0)<0.00001)){
                r->Kind=SSTimingList::__STL_Binary;
                }
            else{
                r->Kind=SSTimingList::__STL_Word;
                }
            }
        else
        if(c->TDHeader.DType==3){
            r->Kind=SSTimingList::__STL_String;
            }
        }

    return(true);
}

void    SSTimingList::BuildMinMaxRange(void)
{
    LoadedTimingSlice *e=TimingData.GetFirst();
    if(e==NULL)
        return;
    if(e->TDHeader.DType==1   || e->TDHeader.DType==2
    || e->TDHeader.DType==201 || e->TDHeader.DType==202){
        MaxData=-MAXDOUBLE;
        MinData=MAXDOUBLE;
        for(LoadedTimingSlice *c=TimingData.GetFirst();c!=NULL;c=c->GetNext()){
            if(MaxData<c->GetInt())
                MaxData=c->GetInt();
            if(MinData>c->GetInt())
                MinData=c->GetInt();
            }
        }
}

bool    LoadedTimingFile::Write(TFileStream *wfile)
{
    FileHeader.NamedOperandNumb=OpeData.GetNumber();
    if(wfile->Write(&FileHeader,sizeof(FileHeader))!=sizeof(FileHeader))
        return(false);

    for(int i=0;i<FileHeader.SeqNumb;i++){
        if(wfile->Write(&SeqData[i].Header,sizeof(SeqData[i].Header))!=sizeof(SeqData[i].Header))
            return(false);
        if(wfile->Write(SeqData[i].Name.c_str(),SeqData[i].Header.NameLen)!=SeqData[i].Header.NameLen)
            return(false);
        }

    for(SSOperandClass *c=OpeData.GetFirst();c!=NULL;c=c->GetNext()){
        c->Data.NameLen      =c->Name.Length();
        if(c->GroupDetail!=NULL)
            c->Data.OpeExtendByte=c->DetailNumb*sizeof(struct __TimingOperandGroup);
        if(c->LanvarDetail!=NULL)
            c->Data.OpeExtendByte=c->DetailNumb*sizeof(struct __TimingOperandLanvar);
        if(wfile->Write(&c->Data,sizeof(c->Data))!=sizeof(c->Data))
            return(false);
        if(wfile->Write(c->Name.c_str(),c->Data.NameLen)!=c->Data.NameLen)
            return(false);
        if(c->GroupDetail!=NULL){
            if(wfile->Write(c->GroupDetail,c->Data.OpeExtendByte)!=c->Data.OpeExtendByte)
                return(false);
            }
        else
        if(c->LanvarDetail!=NULL){
            if(wfile->Write(c->LanvarDetail,c->Data.OpeExtendByte)!=c->Data.OpeExtendByte)
                return(false);
            }
        }
    if(Write(wfile,NowParam)==false)
        return(false);

    for(AddedVectorBase *a=AddedVector.GetFirst();a!=NULL;a=a->GetNext()){
        if(Write(wfile,a)==false)
            return(false);
        }

    for(LoadedTimingSlice *s=new LoadedTimingSlice();s!=NULL;s=s->GetNext()){
        if(s->Write(wfile)==false){
            return(false);
            }
        }
    return(true);
}


SSTimingFlowList    *LoadedTimingFile::GetTopFlow(VInt64 &startTime)
{
    int k=0;
    VInt64  v;
    for(SSTimingFlowList *L=FlowList.GetFirst();L!=NULL;L=L->GetNext(),k++){
        if(k==0){
            v=L->Point->TDHeader.Clocks;
            if(v>=startTime)
                return(L);
            continue;
            }
        if(L->Point->TDHeader.Clocks>=startTime){
            return(L);
            }
        }
    return(NULL);
}

SSTimingList::SSTimingList(void)
{
    Point=NULL;
    UserOpe=NULL;
    
    Kind=__STL_UnKnown;
    TimingPointer=NULL;
    TimingNumb=0;
    ItemLineWidth=1;
    ItemLineColor=clRed;
}
SSTimingList::~SSTimingList(void)
{
    if(TimingPointer!=NULL)
        delete  []TimingPointer;
    TimingPointer=NULL;
    TimingNumb=0;
}

LoadedTimingSlice   *SSTimingList::GetTopSlice(VInt64 &startTime)
//  startTime以上のデータを返す
{
    int k=0;
    VInt64  v;
    for(LoadedTimingSlice *c=TimingData.GetFirst();c!=NULL;c=c->GetNext(),k++){
        if(k==0){
            v=c->TDHeader.Clocks;
            if(v>=startTime)
                return(c);
            continue;
            }
        if(c->TDHeader.Clocks>=startTime){
            return(c);
            }
        }
    return(NULL);
}

int cdecl SSTimingListsortFunc(const void *e1, const void *e2)
{
    LoadedTimingSlice   **p1=(LoadedTimingSlice **)e1;
    LoadedTimingSlice   **p2=(LoadedTimingSlice **)e2;

    if( (*p1)->TDHeader.Clocks>(*p2)->TDHeader.Clocks )
        return(1);
    if( (*p1)->TDHeader.Clocks<(*p2)->TDHeader.Clocks )
        return(-1);
    return(0);
}
LoadedTimingSlice   *SSTimingList::GetTopSliceLess(VInt64 &startTime)
//  startTime以下の最大のデータを返す
{
    LoadedTimingSlice   Key;
    LoadedTimingSlice   *KeyPoint=&Key;
    Key.TDHeader.Clocks=startTime;

    LoadedTimingSlice   **p=(LoadedTimingSlice **)LessSearch(&KeyPoint , TimingPointer , TimingNumb , sizeof(LoadedTimingSlice *) , SSTimingListsortFunc);

    if(p==NULL)
        return(NULL);
    return(*p);
}

LoadedTimingSlice   *SSTimingList::GetPrevSlice(VInt64 &startTime)
//  startTime以下のデータを返す
{
    int k=0;
    VInt64  v;
    for(LoadedTimingSlice *c=TimingData.GetLast();c!=NULL;c=c->GetPrev(),k++){
        if(k==0){
            v=c->TDHeader.Clocks;
            if(v<=startTime)
                return(c);
            continue;
            }
        if(c->TDHeader.Clocks<=startTime){
            return(c);
            }
        }
    return(NULL);
}

void    SSTimingList::BuildTimingTable(void)
{
    TimingNumb=TimingData.GetNumber();
    if(TimingPointer!=NULL)
        delete  []TimingPointer;
    TimingPointer=new LoadedTimingSlice *[TimingNumb];
    int n=0;
    for(LoadedTimingSlice *s=TimingData.GetFirst();s!=NULL;s=s->GetNext(),n++){
        TimingPointer[n]=s;
        }
}

bool    LoadedTimingFile::ReadParam(TFileStream *rfile)
{
    return NowParam.Read(rfile);
}


bool    LoadedTimingFile::Write(TFileStream *wfile ,SeqTimingParameter &param)
{
    struct  __TimingDataHeader  Header;

    Header.DataSize=sizeof(Header)+param.GetDataLength();
    Header.Clocks=0;         // 変更されたときのCPUクロック値
    Header.TickCount=0;		// 変更されたときのミリセカンド
    Header.SeqCode=0;
    Header.MLine=0;			// 変更されたときのシーケンス行
    Header.OType=0;
    Header.ONumber=0;
    Header.Flag=0;
    Header.Cause=0;
    Header.DType=4;        //データの種類 1:int , 2:AnsiString , 3:BYTE block

    if(wfile->Write(&Header,sizeof(Header))!=sizeof(Header))
            return(false);
    if(param.Write(wfile)==false)
        return(false);
    return(true);
}

bool    LoadedTimingFile::Write(TFileStream *wfile ,AddedVectorBase *v)
{
    struct  __TimingDataHeader  Header;

    Header.DataSize=sizeof(Header)+v->GetDataLength();
    Header.Clocks=0;         // 変更されたときのCPUクロック値
    Header.TickCount=0;		// 変更されたときのミリセカンド
    Header.SeqCode=0;
    Header.MLine=0;			// 変更されたときのシーケンス行
    Header.OType=0;
    Header.ONumber=v->GetID();
    Header.Flag=0;
    Header.Cause=0;
    Header.DType=5;        //データの種類 1:int , 2:AnsiString , 3:BYTE block

    if(wfile->Write(&Header,sizeof(Header))!=sizeof(Header))
            return(false);
    if(v->Write(wfile)==false)
        return(false);
    return(true);
}

//===================================================================
int     AddedVectorBase::GetDataLength(void)
{
    TMemoryStream   *d=new TMemoryStream();

    Write(d);
    int Len=d->Size;
    delete  d;
    return(Len);
}

void    AddedVectorBase::DrawArrow(TCanvas *canvas ,int startx,int starty,int endx, int endy
                , int ArrowSize)
{
    int dx=endx-startx;
    int dy=endy-starty;
    double Len=hypot(dx,dy);

    Windows::TPoint P[5];

    int px=-dx*ArrowSize/Len;
    int py=-dy*ArrowSize/Len;

    double  coss=cos(22.0/360.0*2.0*M_PI);
    double  sins=sin(22.0/360.0*2.0*M_PI);

    P[0].x =endx;
    P[0].y =endy;
    P[1].x = px*coss+py*sins+endx;
    P[1].y =-px*sins+py*coss+endy;
    P[2].x = px*0.8+endx;
    P[2].y = py*0.8+endy;
    P[3].x = px*coss-py*sins+endx;
    P[3].y = px*sins+py*coss+endy;
    P[4]=P[0];
    canvas->Polygon(P,3);
}



AddedVectorSingleArrow::AddedVectorSingleArrow(void)
{
    StartX  =0;
    StartY  =0;
    ArrowedX=0;
    ArrowedY=0;
    LineWidth=1;
    LineColor=clBlack;
    ArrowSize=10;
}

void    AddedVectorSingleArrow::Draw(double ZoomRate
                                    ,VInt64 &topx, int topy, TCanvas *canvas)
{
    VInt64  rx1;
    int     ry1;
    VInt64  rx2;
    int     ry2;
    int     qx1,qy1;
    int     qx2,qy2;

    rx1=StartX;
    rx1-=topx;
    ry1=StartY-topy;

    rx2=ArrowedX;
    rx2-=topx;
    ry2=ArrowedY-topy;
    qx1=rx1.GetDouble()*ZoomRate;
    qy1=ry1*ZoomRate;
    qx2=rx2.GetDouble()*ZoomRate;
    qy2=ry2*ZoomRate;

    canvas->Pen->Color=LineColor    ;
    canvas->Pen->Style=psSolid      ;
    canvas->Pen->Width=1            ;
    canvas->Pen->Mode =pmCopy;
    canvas->Brush->Color=LineColor  ;
    canvas->Brush->Style=bsSolid    ;
    DrawArrow(canvas ,qx1,qy1,qx2,qy2 ,ArrowSize);

    int dx=qx2-qx1;
    int dy=qy2-qy1;
    double  Len=hypot(dx,dy);
    int ex=dx*ArrowSize*0.8/Len;
    int ey=dy*ArrowSize*0.8/Len;
    int pex=qx1+dx-ex;
    int pey=qy1+dy-ey;

    canvas->Pen->Width=LineWidth    ;
    canvas->MoveTo(qx1,qy1);
    canvas->LineTo(pex,pey);
}

bool    AddedVectorSingleArrow::Read(TStream *is)
{
    if(StartX.Read(is)  ==false)
        return(false);
    if(is->Read(&StartY,sizeof(StartY))!=sizeof(StartY))
        return(false);
    if(ArrowedX.Read(is)==false)
        return(false);
    if(is->Read(&ArrowedY,sizeof(ArrowedY))!=sizeof(ArrowedY))
        return(false);
    if(is->Read(&LineWidth,sizeof(LineWidth))!=sizeof(LineWidth))
        return(false);
    if(is->Read(&LineColor,sizeof(LineColor))!=sizeof(LineColor))
        return(false);
    if(is->Read(&ArrowSize,sizeof(ArrowSize))!=sizeof(ArrowSize))
        return(false);
    return(true);
}
bool    AddedVectorSingleArrow::Write(TStream *os)
{
    if(StartX.Write(os)  ==false)
        return(false);
    if(os->Write(&StartY,sizeof(StartY))!=sizeof(StartY))
        return(false);
    if(ArrowedX.Write(os)==false)
        return(false);
    if(os->Write(&ArrowedY,sizeof(ArrowedY))!=sizeof(ArrowedY))
        return(false);
    if(os->Write(&LineWidth,sizeof(LineWidth))!=sizeof(LineWidth))
        return(false);
    if(os->Write(&LineColor,sizeof(LineColor))!=sizeof(LineColor))
        return(false);
    if(os->Write(&ArrowSize,sizeof(ArrowSize))!=sizeof(ArrowSize))
        return(false);
    return(true);
}

AddedVectorBothArrow::AddedVectorBothArrow(void)
{
    StartX  =0;
    StartY  =0;
    EndX    =0;
    EndY    =0;
    LineWidth=1;
    LineColor=clBlack;
    ArrowSize=10;
}

bool    AddedVectorBothArrow::Read(TStream *is)
{
    if(StartX.Read(is)  ==false)
        return(false);
    if(is->Read(&StartY,sizeof(StartY))!=sizeof(StartY))
        return(false);
    if(EndX.Read(is)    ==false)
        return(false);
    if(is->Read(&EndY,sizeof(EndY))!=sizeof(EndY))
        return(false);
    if(is->Read(&LineWidth,sizeof(LineWidth))!=sizeof(LineWidth))
        return(false);
    if(is->Read(&LineColor,sizeof(LineColor))!=sizeof(LineColor))
        return(false);
    if(is->Read(&ArrowSize,sizeof(ArrowSize))!=sizeof(ArrowSize))
        return(false);
    return(true);
}
bool    AddedVectorBothArrow::Write(TStream *os)
{
    if(StartX.Write(os) ==false)
        return(false);
    if(os->Write(&StartY,sizeof(StartY))!=sizeof(StartY))
        return(false);
    if(EndX.Write(os)   ==false)
        return(false);
    if(os->Write(&EndY,sizeof(EndY))!=sizeof(EndY))
        return(false);
    if(os->Write(&LineWidth,sizeof(LineWidth))!=sizeof(LineWidth))
        return(false);
    if(os->Write(&LineColor,sizeof(LineColor))!=sizeof(LineColor))
        return(false);
    if(os->Write(&ArrowSize,sizeof(ArrowSize))!=sizeof(ArrowSize))
        return(false);
    return(true);
}

void    AddedVectorBothArrow::Draw(double ZoomRate ,VInt64 &topx, int topy, TCanvas *canvas)
{
    VInt64  rx1;
    int     ry1;
    VInt64  rx2;
    int     ry2;
    int     qx1,qy1;
    int     qx2,qy2;

    rx1=StartX;
    rx1-=topx;
    ry1=StartY-topy;

    rx2=EndX;
    rx2-=topx;
    ry2=EndY-topy;
    qx1=rx1.GetDouble()*ZoomRate;
    qy1=ry1*ZoomRate;
    qx2=rx2.GetDouble()*ZoomRate;
    qy2=ry2*ZoomRate;

    canvas->Pen->Color=LineColor    ;
    canvas->Pen->Style=psSolid      ;
    canvas->Pen->Width=1            ;
    canvas->Pen->Mode =pmCopy;
    canvas->Brush->Color=LineColor  ;
    canvas->Brush->Style=bsSolid    ;
    DrawArrow(canvas ,qx1,qy1,qx2,qy2 ,ArrowSize);
    DrawArrow(canvas ,qx2,qy2,qx1,qy1 ,ArrowSize);

    int dx=qx2-qx1;
    int dy=qy2-qy1;
    double  Len=hypot(dx,dy);
    int ex=dx*ArrowSize*0.8/Len;
    int ey=dy*ArrowSize*0.8/Len;
    int pex2=qx1+dx-ex;
    int pey2=qy1+dy-ey;
    int pex1=qx1+ex;
    int pey1=qy1+ey;

    canvas->Pen->Width=LineWidth    ;
    canvas->MoveTo(pex1,pey1);
    canvas->LineTo(pex2,pey2);
}

AddedVectorFontChar::AddedVectorFontChar(void)
{
    StartX  =0;
    StartY  =0;
    Character="";
    FontColor=clBlack;
    FontName    ="System";
    FontCharSet =0;
    FontSize    =9;
    FontStyle   =TFontStyles();
    Angle       =0.0;
}

bool    AddedVectorFontChar::Read(TStream *is)
{
    if(StartX.Read(is)  ==false)
        return(false);
    if(is->Read(&StartY,sizeof(StartY))!=sizeof(StartY))
        return(false);
    if(ReadString(Character,is)==false)
        return(false);
    if(is->Read(&FontColor,sizeof(FontColor))!=sizeof(FontColor))
        return(false);
    if(ReadString(FontName,is)==false)
        return(false);
    if(is->Read(&FontCharSet,sizeof(FontCharSet))!=sizeof(FontCharSet))
        return(false);
    if(is->Read(&FontSize   ,sizeof(FontSize))   !=sizeof(FontSize))
        return(false);
    if(is->Read(&FontStyle  ,sizeof(FontStyle))  !=sizeof(FontStyle))
        return(false);
    if(is->Read(&Angle      ,sizeof(Angle))      !=sizeof(Angle))
        return(false);
    return(true);
}
bool    AddedVectorFontChar::Write(TStream *os)
{
    if(StartX.Write(os)  ==false)
        return(false);
    if(os->Write(&StartY,sizeof(StartY))!=sizeof(StartY))
        return(false);
    if(WriteString(Character,os)==false)
        return(false);
    if(os->Write(&FontColor,sizeof(FontColor))!=sizeof(FontColor))
        return(false);
    if(WriteString(FontName,os)==false)
        return(false);
    if(os->Write(&FontCharSet,sizeof(FontCharSet))!=sizeof(FontCharSet))
        return(false);
    if(os->Write(&FontSize   ,sizeof(FontSize))   !=sizeof(FontSize))
        return(false);
    if(os->Write(&FontStyle  ,sizeof(FontStyle))  !=sizeof(FontStyle))
        return(false);
    if(os->Write(&Angle      ,sizeof(Angle))      !=sizeof(Angle))
        return(false);
    return(true);
}
void    AddedVectorFontChar::Draw(double ZoomRate ,VInt64 &topx, int topy, TCanvas *canvas)
{
    VInt64  rx1;
    int     ry1;
    int     qx1,qy1;

    rx1=StartX;
    rx1-=topx;
    ry1=StartY-topy;

    qx1=rx1.GetDouble()*ZoomRate;
    qy1=ry1*ZoomRate;

    TFont   *L=new TFont();
    L->Charset  =FontCharSet;
    L->Color    =FontColor;
    L->Name     =FontName;
    L->Size     =FontSize;
    L->Style    =FontStyle;
    canvas->Font->Assign(L);
    TStringList *r=new TStringList();
    r->Text=Character;
    canvas->Brush->Style=bsClear;
    for(int y=0;y<r->Count;y++){
        int py=canvas->TextHeight("Wg");
        canvas->TextOut(qx1,qy1+y*py,r->Strings[y]);
        }
}

bool    WriteString(AnsiString data , TStream *os)
{
    int Len=data.Length();
    if(os->Write(data.c_str(),Len+1)!=(Len+1))
        return(false);
    return(true);
}
bool    ReadString(AnsiString &data , TStream *is)
{
    char    Buff[1000];
    BYTE    d=1;
    int     N=0;
    char *fp;
    for(fp=Buff;d!=0;fp++,N++){
        if(is->Read(&d,sizeof(d))!=sizeof(d))
            return(false);
        if(N>=1000)
            return(false);
        *fp=d;
        }
    *fp=0;
    data=Buff;
    return(true);
}

bool    WriteStrings(TStrings *data , TStream *os)
{
    int Len=data->Count;
    if(os->Write(&Len,sizeof(Len))!=sizeof(Len))
        return(false);
    for(int i=0;i<Len;i++){
        if(WriteString(data->Strings[i] , os)==false)
            return(false);
        }
    return(true);
}
bool    ReadStrings(TStrings *data, TStream *is)
{
    data->Clear();
    int Len;
    if(is->Read(&Len,sizeof(Len))!=sizeof(Len))
        return(false);
    for(int i=0;i<Len;i++){
        AnsiString  A;
        if(ReadString(A , is)==false)
            return(false);
        data->Add(A);
        }
    return(true);
}

int     LoadedTimingFile::GetUserSignalNumb(void)
{
    int LNumb=0;
    for(SSOperandClass *s=OpeData.GetFirst();s!=NULL;s=s->GetNext()){
        if(s->Data.OType>=200)
            LNumb++;
        }
    return(LNumb);
}

AnsiString  SSOperandClass::GetKindName(void)
{
    switch(Data.OType){
        case 201:
            return("Binary");
        case 202:
            return("Word");
        case 203:
            return("String");
        }
    return("");
}
AnsiString  SSOperandClass::GetName(void)
{
    return(Name);
}


