#include "XGeneralFunc.h"
#include "X6AxisCommon.h"
#include "ControlRobotCommon.h"

SplinePointList::SplinePointList(const SplinePointList &src)
{
    JPos        =src.JPos        ;
    CapturePoint=src.CapturePoint;
}

SplinePointList	&SplinePointList::operator=(const SplinePointList &src)
{
    JPos        =src.JPos        ;
    CapturePoint=src.CapturePoint;
    return *this;
}

bool	SplinePointList::Save(QIODevice *f)
{
    if(f->write((const char *)&JPos,sizeof(JPos))!=sizeof(JPos))
        return false;
    if(::Save(f,CapturePoint)==false)
        return false;
    return true;
}

bool	SplinePointList::Load(QIODevice *f)
{
    if(f->read((char *)&JPos,sizeof(JPos))!=sizeof(JPos))
        return false;
    if(::Load(f,CapturePoint)==false)
        return false;
    return true;
}

SplinePointListContainer::SplinePointListContainer(const SplinePointListContainer &src)
{
    for(SplinePointList *s=src.GetFirst();s!=NULL;s=s->GetNext()){
        SplinePointList *d=new SplinePointList(*s);
        AppendList(d);
    }
}

SplinePointListContainer	&SplinePointListContainer::operator=(const SplinePointListContainer &src)
{
    RemoveAll();
    for(SplinePointList *s=src.GetFirst();s!=NULL;s=s->GetNext()){
        SplinePointList *d=new SplinePointList(*s);
        AppendList(d);
    }
    return *this;
}

double	GetDistanceXYZ(JointPos &s1,JointPos &s2)
{
    double  dx=s1.jPos[0]-s2.jPos[0];
    double  dy=s1.jPos[1]-s2.jPos[1];
    double  dz=s1.jPos[2]-s2.jPos[2];

    return sqrt(dx*dx+dy*dy+dz*dz);
}
double	GetDistancePQR(JointPos &s1,JointPos &s2)
{
    double  dp=s1.jPos[3]-s2.jPos[3];
    double  dq=s1.jPos[4]-s2.jPos[4];
    double  dr=s1.jPos[5]-s2.jPos[5];

    return sqrt(dp*dp+dq*dq+dr*dr);
}
/*
bool	Save(QIODevice *f,const DescPose &a)
{
    if(f->write((const char *)&a,sizeof(DescPose))!=sizeof(DescPose))
        return false;
    return true;
}

bool	Load(QIODevice *f,DescPose &a)
{
    if(f->read((char *)&a,sizeof(DescPose))!=sizeof(DescPose))
        return false;
    return true;
}
*/
bool	Save(QIODevice *f,const JointPos &a)
{
    if(f->write((const char *)&a,sizeof(JointPos))!=sizeof(JointPos))
        return false;
    return true;
}

bool	Load(QIODevice *f,JointPos &a)
{
    if(f->read((char *)&a,sizeof(JointPos))!=sizeof(JointPos))
        return false;
    return true;
}
