#include "XExecuteVisualizer.h"
#include "XExecuteVisualizerForLib.h"
#include <QDir>
#include "XGeneralFunc.h"
#include "RunnerObjSettingForm.h"
#include "ShowConnectionInfoForm.h"
#include "XExecuteVisualizerInterface.h"

RunnerObjDLL::RunnerObjDLL(LayersBase *Base)
	:ServiceForLayers(Base)
{
	DLL_GetName				=NULL;
	DLL_GetVersion			=NULL;
	DLL_GetUsageFiles		=NULL;
	DLL_GetExplain			=NULL;
	DLL_SetLanguageCommon	=NULL;
	DLL_SetLanguage			=NULL;
	DLL_CheckCopyright		=NULL;
	DLL_Initial				=NULL;
	DLL_Close				=NULL;
	DLL_InitialQt			=NULL;

	DLL_CreateInstance		=NULL;
	DLL_DeleteInstance		=NULL;

	DLL_ShowSettingDialog	=NULL;
}
RunnerObjDLL::~RunnerObjDLL(void)
{
	if(ReEntrantDLL==true)
		return;
	ReEntrantDLL=true;

	if(DllLib.isLoaded()==true){
		DllLib.unload();
	}
	ReEntrantDLL=false;
}
bool	RunnerObjDLL::LoadDLL(const QString &filename)
{
	DllLib.setFileName(filename);
	if(DllLib.load()==false)
		return false;
	FileName	=filename;

	DLL_GetName				=(bool (*)(QString &Root ,QString &Name))DllLib.resolve("DLL_GetName");
	DLL_GetVersion			=(WORD (*)(void))DllLib.resolve("DLL_GetVersion");
	if(DLLManager::LoadDLL(DllLib)==false){
		return false;
	}
	DLL_GetUsageFiles		=(void (*)(QStringList &))DllLib.resolve("DLL_GetUsageFiles");

	DLL_GetExplain			=(const char *(*)(void))DllLib.resolve("DLL_GetExplain");
	DLL_SetLanguageCommon	=(void (*)(LanguagePackage &Pkg ,int LanguageCode))DllLib.resolve("DLL_SetLanguageCommon");
	DLL_SetLanguage			=(void (*)(LanguagePackage &Pkg ,int LanguageCode))DllLib.resolve("DLL_SetLanguage");
	DLL_CheckCopyright		=(bool (*)(QString &CopyrightString))DllLib.resolve("DLL_CheckCopyright");
	DLL_Initial				=(bool (*)(LayersBase *Base))DllLib.resolve("DLL_Initial");
	DLL_Close				=(void (*)(void))DllLib.resolve("DLL_Close");
	DLL_InitialQt			=(void (*)(QApplication *AppBase))DllLib.resolve("DLL_InitialQt");

	DLL_CreateInstance		=(RunnerObject *(*)(LayersBase *Base,RunnerMap *rmap))DllLib.resolve("DLL_CreateInstance");
	DLL_DeleteInstance		=(void (*)(RunnerObject *Instance))DllLib.resolve("DLL_DeleteInstance");

	DLL_ShowSettingDialog	=(bool (*)(RunnerObject *handle))DllLib.resolve("DLL_ShowSettingDialog");

	if(DLL_GetName!=NULL){
		DLL_GetName(DLLRoot,DLLName);
	}

	return true;
}
RunnerObject	*RunnerObjDLL::CreateInstance(RunnerMap *rmap)
{
	if(DLL_CreateInstance!=NULL){
		RunnerObject	*p=DLL_CreateInstance(GetLayersBase(),rmap);
		return p;
	}
	return NULL;
}
void	RunnerObjDLL::DeleteInstance(RunnerObject *Instance)
{
	if(DLL_DeleteInstance!=NULL){
		DLL_DeleteInstance(Instance);
	}
}

const QString	RunnerObjDLL::GetExplain(void)
{
	if(DLL_GetExplain!=NULL){
		const char	*c=DLL_GetExplain();
		if(c!=NULL){
			return QString::fromLocal8Bit(c);
		}
	}
	return /**/"";
}
WORD	RunnerObjDLL::GetVersion(void)
{
	if(DLL_GetVersion!=NULL){
		return DLL_GetVersion();
	}
	return 0;
}

bool	RunnerObjDLL::IsSettingDialog(void)
{
	if(DLL_ShowSettingDialog!=NULL){
		return true;
	}
	return false;
}
	
bool	RunnerObjDLL::ShowSettingDialog(RunnerObject *handle)
{
	if(DLL_ShowSettingDialog!=NULL){
		return DLL_ShowSettingDialog(handle);
	}
	return false;
}

void	RunnerObjDLL::GetExportFunctions(QStringList &Str)
{
	if(DLL_GetName!=NULL){
		Str.append("DLL_GetName");
	}
	if(DLL_GetVersion!=NULL){
		Str.append("DLL_GetVersion");
	}
	if(DLL_GetExplain!=NULL){
		Str.append("DLL_GetExplain");
	}
	if(DLL_SetLanguageCommon!=NULL){
		Str.append("DLL_SetLanguageCommon");
	}
	if(DLL_SetLanguage!=NULL){
		Str.append("DLL_SetLanguage");
	}
	if(DLL_CheckCopyright!=NULL){
		Str.append("DLL_CheckCopyright");
	}
	if(DLL_Initial!=NULL){
		Str.append("DLL_Initial");
	}
	if(DLL_Close!=NULL){
		Str.append("DLL_Close");
	}
	if(DLL_InitialQt!=NULL){
		Str.append("DLL_InitialQt");
	}
	if(DLL_CreateInstance!=NULL){
		Str.append("DLL_CreateInstance");
	}
	if(DLL_DeleteInstance!=NULL){
		Str.append("DLL_DeleteInstance");
	}
	if(DLL_ShowSettingDialog!=NULL){
		Str.append("DLL_ShowSettingDialog");
	}
	DLLManager::GetExportFunctions(Str);
}

//=================================================================
RunerDLLContainer::RunerDLLContainer(LayersBase *base)
	:ServiceForLayers(base)
{
}
RunerDLLContainer::~RunerDLLContainer(void)
{
}

void	RunerDLLContainer::LoadDLL(const QString &DllPath)
{
	QDir	Dir;

	RemoveAll();
	if(Dir.cd(DllPath)==true){
		QString	SearchFile=QString("*.")+GetDynamicFileExt();
		QStringList nameFilters(SearchFile);
		QStringList List=Dir.entryList ( nameFilters, QDir::Files, QDir::NoSort );

		for(int i=0;i<List.size();i++){
			QString	FileName=DllPath+GetSeparator()+List[i];
			if(QLibrary::isLibrary(FileName)==true){
				RunnerObjDLL	*DLL=new RunnerObjDLL(GetLayersBase());
				if(DLL->LoadDLL(FileName)==true){
					AppendList(DLL);
				}
				else{
					delete	DLL;
				}
			}
		}
	}
}

RunnerObjDLL	*RunerDLLContainer::FindDLL(const QString &DLLRoot ,const QString &DLLName)
{
	for(RunnerObjDLL *DLL=GetFirst();DLL!=NULL;DLL=DLL->GetNext()){
		if(DLL->DLLRoot==DLLRoot && DLL->DLLName==DLLName){
			return DLL;
		}
	}
	return NULL;
}

//=================================================================
GlueRunner::GlueRunner(RunnerMap *rmap)
	:RMap(rmap)
{
	ObjFrom	=NULL;
	ObjTo	=NULL;
	DrawingPosLen=0;
}
GlueRunner::~GlueRunner(void)
{
}
void	GlueRunner::Draw(QPainter &Pnt)
{
	const	int		ELen=5;

	QPen	SavedPen=Pnt.pen();
	QPen	Pen=SavedPen;
	Pen.setColor(Qt::green);
	Pen.setWidth(3);
	Pnt.setPen(Pen);

	for(XYClass *a=Lines.NPListPack<XYClass>::GetFirst();a!=NULL;a=a->GetNext()){
		XYClass *b=a->GetNext();
		if(b==NULL){
			break;
		}
		Pnt.drawLine(a->x,a->y,b->x ,b->y);
	}

	Pnt.setPen(SavedPen);

	Pnt.setPen(Qt::red);
	Pnt.setBrush(Qt::green);

	for(XYClass *a=Lines.NPListPack<XYClass>::GetFirst();a!=NULL;a=a->GetNext()){
		XYClass *b=a->GetNext();
		if(b==NULL){
			break;
		}
		Pnt.drawEllipse(b->x-ELen, b->y-ELen ,ELen+ELen ,ELen+ELen);
	}

	Pnt.setPen(Qt::green);
	Pnt.setBrush(Qt::green);

	double	TotalLen=0;
	bool	flag=false;
	for(XYClass *a=Lines.NPListPack<XYClass>::GetFirst();a!=NULL;a=a->GetNext()){
		XYClass *b=a->GetNext();
		if(b==NULL){
			break;
		}
		double	Len=hypot(a->x - b->x ,a->y - b->y);
		if(Len>0 && TotalLen<=DrawingPosLen && DrawingPosLen<(TotalLen+Len)){
			double	M=(DrawingPosLen-TotalLen)/Len;
			double	x=a->x+(b->x - a->x)*M;
			double	y=a->y+(b->y - a->y)*M;
			Pnt.drawEllipse(x-4,y-4,8,8);
			DrawingPosLen+=3;
			flag=true;
			break;
		}
		TotalLen+=Len;
	}
	if(flag==false){
		DrawingPosLen=0;
	}
}

XYClass	*GlueRunner::GetFirstPoint(void)
{
	return Lines.NPListPack<XYClass>::GetFirst();
}
XYClass	*GlueRunner::GetLastPoint(void)
{
	return Lines.NPListPack<XYClass>::GetLast();
}
void	GlueRunner::AddPoint(int x ,int y)
{
	Lines.AppendList(new XYClass(x,y));
}
void	GlueRunner::RemoveLast(void)
{
	XYClass	*a=GetLastPoint();
	if(a!=NULL){
		Lines.NPListPack<XYClass>::RemoveList(a);
		delete	a;
	}
}
bool	GlueRunner::IsInclude(int x ,int y)
{
	return Lines.IsInclude(x ,y);
}

void	GlueRunner::AddXYInFirstPoint(int dx,int dy)
{
	XYClass	*a=GetFirstPoint();
	if(a!=NULL){
		a->x+=dx;
		a->y+=dy;
	}
}

void	GlueRunner::AddXYInLastPoint (int dx,int dy)
{
	XYClass	*a=GetLastPoint();
	if(a!=NULL){
		a->x+=dx;
		a->y+=dy;
	}
}
XYClass	*GlueRunner::GetClosedPoint(int x ,int y ,double Area)
{
	for(XYClass	*a=Lines.NPListPack<XYClass>::GetFirst();a!=NULL;a=a->GetNext()){
		if(hypot(a->x-x,a->y-y)<=Area){
			return a;
		}
	}
	return NULL;
}

bool	GlueRunner::Save(QIODevice *f)
{
	int32	Ver=1;

	if(::Save(f,Ver)==false)
		return false;

	if(::Save(f,ID)==false)
		return false;
	bool	ExistObjFrom;
	if(ObjFrom!=NULL)
		ExistObjFrom=true;
	else
		ExistObjFrom=false;
	if(::Save(f,ExistObjFrom)==false)
		return false;
	if(ExistObjFrom==true){
		if(::Save(f,ObjFrom->GetParent()->GetID())==false)
			return false;
		if(::Save(f,ObjFrom->GetID())==false)
			return false;
	}

	bool	ExistObjTo;
	if(ObjTo!=NULL)
		ExistObjTo=true;
	else
		ExistObjTo=false;
	if(::Save(f,ExistObjTo)==false)
		return false;
	if(ExistObjTo==true){
		if(::Save(f,ObjTo->GetParent()->GetID())==false)
			return false;
		if(::Save(f,ObjTo->GetID())==false)
			return false;
	}
	if(Lines.Write(f)==false)
		return false;
	return true;
}
bool	GlueRunner::Load(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false)
		return false;

	if(::Load(f,ID)==false)
		return false;
	bool	ExistObjFrom;
	if(::Load(f,ExistObjFrom)==false)
		return false;
	if(ExistObjFrom==true){
		int32	ObjParentFromID;
		int32	ObjFromID;
		if(::Load(f,ObjParentFromID)==false)
			return false;
		RunnerObject	*Obj=RMap->FindRunnerObject(ObjParentFromID);
		if(Obj==NULL)
			return false;
		if(::Load(f,ObjFromID)==false)
			return false;
		ObjFrom=Obj->FindOutputConnector(ObjFromID);
		if(ObjFrom==NULL)
			return false;
	}

	bool	ExistObjTo;
	if(::Load(f,ExistObjTo)==false)
		return false;
	if(ExistObjTo==true){
		int32	ObjParentToID;
		int32	ObjToID;
		if(::Load(f,ObjParentToID)==false)
			return false;
		RunnerObject	*Obj=RMap->FindRunnerObject(ObjParentToID);
		if(Obj==NULL)
			return false;
		if(::Load(f,ObjToID)==false)
			return false;
		ObjTo=Obj->FindInputConnector(ObjToID);
		if(ObjTo==NULL)
			return false;
	}
	if(Lines.Read(f)==false)
		return false;
	return true;
}
//=================================================================

RunnerMap::RunnerMap(LayersBase *base ,bool _EditMode ,QWidget *parent)
	:ServiceForLayers(base)
	,QWidget(parent)
	,RunerDLLContainer(base)
{
	EditMode=_EditMode;
	DrawMode=Mode_None;
	if(EditMode==true){
		//grabMouse ();
		setMouseTracking(true);
	}
	MovingObj			=NULL;
	MovingObj			=NULL;
	ConnectingPoint		=NULL;
	ConnectingGlue		=NULL;
	ConnectionConnector	=NULL;
	CurrentPosX			=0;
	CurrentPosY			=0;
	PaintCount			=0;

	Tm.setInterval(10);
	Tm.setSingleShot(false);
	connect(&Tm,SIGNAL(timeout()),this,SLOT(SlotTimeOut()));
	Tm.start();
}
RunnerMap::~RunnerMap(void)
{
}
void	RunnerMap::Draw(QPainter &Pnt)
{
	for(RunnerObject *a=Objects.GetFirst();a!=NULL;a=a->GetNext()){
		a->Draw(Pnt);
	}
	for(GlueRunner *b=Glues.GetFirst();b!=NULL;b=b->GetNext()){
		b->Draw(Pnt);
	}
}

bool	RunnerMap::Save(QIODevice *f)
{
	int32	Ver=1;

	if(::Save(f,Ver)==false)
		return false;

	int32	CountObjects=Objects.GetCount();
	if(::Save(f,CountObjects)==false){
		return false;
	}
	for(RunnerObject *a=Objects.GetFirst();a!=NULL;a=a->GetNext()){
		QString	DLLRoot;
		QString	DLLName;
		a->GetRootName(DLLRoot,DLLName);
		if(::Save(f,DLLRoot)==false){
			return false;
		}
		if(::Save(f,DLLName)==false){
			return false;
		}
		if(a->Save(f)==false){
			return false;
		}
	}
	int32	CountGlues=Glues.GetCount();
	if(::Save(f,CountGlues)==false){
		return false;
	}
	for(GlueRunner *b=Glues.GetFirst();b!=NULL;b=b->GetNext()){
		if(b->Save(f)==false){
			return false;
		}
	}
	return true;
}
bool	RunnerMap::Load(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false)
		return false;

	int32	CountObjects;
	if(::Load(f,CountObjects)==false){
		return false;
	}
	Objects.RemoveAll();
	for(int i=0;i<CountObjects;i++){
		QString	DLLRoot;
		QString	DLLName;
		if(::Load(f,DLLRoot)==false){
			return false;
		}
		if(::Load(f,DLLName)==false){
			return false;
		}
		RunnerObjDLL	*DLL=FindDLL(DLLRoot ,DLLName);
		if(DLL==NULL){
			return false;
		}
		RunnerObject	*a=DLL->CreateInstance(this);
		if(a!=NULL){
			if(a->Load(f)==false){
				DLL->DeleteInstance(a);
				return false;
			}
			int	ID=a->GetID();
			AppendRunnerObject(a,DLL);
			a->SetID(ID);
			a->show();
		}
		else{
			return false;
		}
	}
	int32	CountGlues;
	if(::Load(f,CountGlues)==false){
		return false;
	}
	Glues.RemoveAll();
	for(int j=0;j<CountGlues;j++){
		GlueRunner	*b=new GlueRunner(this);
		if(b->Load(f)==false){
			return false;
		}
		Glues.AppendList(b);
	}
	return true;
}

void	RunnerMap::FitToParent(void)
{
	if(parentWidget()!=NULL){
		resize(parentWidget()->width(),parentWidget()->height());
	}
}

RunnerObject	*RunnerMap::FindRunnerObject(int ID)
{
	for(RunnerObject *a=Objects.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetID()==ID){
			return a;
		}
	}
	return NULL;
}

void RunnerMap::mouseDoubleClickEvent ( QMouseEvent * event )
{
	if(EditMode==true){
		emit	SignalLDoubleClick(event->x(),event->y());
	}
}
void	RunnerMap::AppendRunnerObject(RunnerObject *obj,RunnerObjDLL *accessDLL)
{
	int	MaxID=0;
	for(RunnerObject *a=Objects.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetID()>MaxID){
			MaxID=a->GetID();
		}
	}
	obj->SetID(MaxID+1);
	obj->SetAccessDLL(accessDLL);
	const QString	s=accessDLL->GetExplain();
	if(s.isEmpty()==false){
		obj->SetExplain(s);
	}
	obj->AllocateState();
	obj->MakeConnectorPos();
	Objects.AppendList(obj);

	connect(obj,SIGNAL(SignalLMouseUp(int,int,int)),this,SLOT(SlotObjLMouseUp(int,int,int)));
	connect(obj,SIGNAL(SignalLMouseDown(int,int,int)),this,SLOT(SlotObjLMouseDown(int,int,int)));
	connect(obj,SIGNAL(SignalRMouseUp(int,int,int)),this,SLOT(SlotObjRMouseUp(int,int,int)));
	connect(obj,SIGNAL(SignalRMouseDown(int,int,int)),this,SLOT(SlotObjRMouseDown(int,int,int)));

	repaint();
}
void	RunnerMap::DeleteRunnerObj(RunnerObject *obj)
{
	Objects.RemoveList(obj);
	ReStart:;
	for(GlueRunner *a=Glues.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->From()!=NULL){
			if(a->From()->GetParent()==obj){
				Glues.RemoveList(a);
				goto	ReStart;
			}
		}
		if(a->To()!=NULL){
			if(a->To()->GetParent()==obj){
				Glues.RemoveList(a);
				goto	ReStart;
			}
		}
	}
	obj->deleteLater();
}
void	RunnerMap::AppendGlue(GlueRunner *G)
{
	int	MaxID=0;
	for(GlueRunner *a=Glues.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetID()>MaxID){
			MaxID=a->GetID();
		}
	}
	G->SetID(MaxID+1);
	Glues.AppendList(G);
}

void	RunnerMap::RemoveGlue(GlueRunner *a)
{
	Glues.RemoveList(a);
	delete	a;
}

void RunnerMap::mouseMoveEvent ( QMouseEvent * event )
{
	if(EditMode==true){
		if(DrawMode==Mode_MoveObj){
			if(MovingObj!=NULL){
				int	dx=event->x()-StartPosX;
				int	dy=event->y()-StartPosY;
				StartPosX=event->x();
				StartPosY=event->y();
				MovingObj->move( MovingObj->geometry().left()+dx
								,MovingObj->geometry().top() +dy);
				for(GlueRunner *g=Glues.GetFirst();g!=NULL;g=g->GetNext()){
					if(g->From()!=NULL && g->From()->GetParent()==MovingObj){
						g->AddXYInFirstPoint(dx,dy);
					}
					if(g->To()!=NULL && g->To()->GetParent()==MovingObj){
						g->AddXYInLastPoint(dx,dy);
					}
				}
				repaint();
			}
		}
		else if(DrawMode==Mode_Connecting){
			CurrentPosX=event->x();
			CurrentPosY=event->y();
		}
		else if(DrawMode==Mode_MoveGlueControl){
			if(ConnectingPoint!=NULL){
				ConnectingPoint->x=event->x();
				ConnectingPoint->y=event->y();
			}
		}
	}
}

GlueRunner	*RunnerMap::GetGlueControlPoint(int x ,int y ,XYClass **XY)
{
	for(GlueRunner *g=Glues.GetFirst();g!=NULL;g=g->GetNext()){
		XYClass	*a=g->GetClosedPoint(x,y);
		if(a!=NULL){
			*XY=a;
			return g;
		}
	}
	return NULL;
}


void RunnerMap::mousePressEvent ( QMouseEvent * event )
{
	if(EditMode==true){
		int	X=event->x();
		int	Y=event->y();
		if(event->button()==Qt::LeftButton){
			if(DrawMode==Mode_None){
				RunnerConnector *C=GetConnector(X ,Y);
				XYClass *XY;
				GlueRunner	*G=GetGlueControlPoint(X ,Y ,&XY);
				if(C!=NULL){
					DrawMode=Mode_Connecting;
					ConnectingGlue	=new GlueRunner(this);
					ConnectingGlue->AddPoint(X,Y);
					ConnectingPoint=ConnectingGlue->GetFirstPoint();
					ConnectionConnector=C;
					CurrentPosX=event->x();
					CurrentPosY=event->y();
				}
				else if(G!=NULL){
					ConnectingGlue=G;
					ConnectingPoint=XY;
					SavedPoint.x=ConnectingPoint->x;
					SavedPoint.y=ConnectingPoint->y;
					DrawMode=Mode_MoveGlueControl;
				}
			}
			else if(DrawMode==Mode_Connecting){
				RunnerConnector *C=GetConnector(X ,Y);
				if(C==NULL){
					if(ConnectingGlue!=NULL){
						ConnectingGlue->AddPoint(X,Y);
						ConnectingPoint=ConnectingGlue->GetLastPoint();
						CurrentPosX=event->x();
						CurrentPosY=event->y();
					}
				}
				else{
					if(ConnectionConnector->GetTypeOfInOut()==RunnerConnector::__Out && C->GetTypeOfInOut()==RunnerConnector::__In){
						DrawMode=Mode_None;
						ConnectingGlue->AddPoint(X,Y);
						ConnectingGlue->SetFrom(ConnectionConnector);
						ConnectingGlue->SetTo(C);
						AppendGlue(ConnectingGlue);
						ConnectingGlue=NULL;
						ConnectingPoint=NULL;
						ConnectionConnector=NULL;
					}
					else if(ConnectionConnector->GetTypeOfInOut()==RunnerConnector::__In && C->GetTypeOfInOut()==RunnerConnector::__Out){
						DrawMode=Mode_None;
						ConnectingGlue->AddPoint(X,Y);
						ConnectingGlue->SetFrom(C);
						ConnectingGlue->SetTo(ConnectionConnector);
						AppendGlue(ConnectingGlue);
						ConnectingGlue=NULL;
						ConnectingPoint=NULL;
						ConnectionConnector=NULL;
					}
				}
			}
			else if(DrawMode==Mode_MoveGlueControl){
				DrawMode=Mode_None;
				ConnectingGlue=NULL;
				ConnectingPoint=NULL;
				ConnectionConnector=NULL;
			}
		}
		else if(event->button()==Qt::RightButton){
			if(DrawMode==Mode_Connecting){
				if(ConnectingGlue!=NULL){
					ConnectingGlue->RemoveLast();
					ConnectingPoint=ConnectingGlue->GetLastPoint();
					if(ConnectingPoint==NULL){
						delete	ConnectingGlue;
						ConnectingPoint		=NULL;
						ConnectingGlue		=NULL;
						ConnectionConnector	=NULL;
						DrawMode=Mode_None;
					}
				}
			}
			else if(DrawMode==Mode_None){
				for(GlueRunner *g=Glues.GetFirst();g!=NULL;g=g->GetNext()){
					if(g->IsInclude(X,Y)==true){
						ShowConnectionInfoForm	Q(g ,NULL);
						Q.exec();
						break;
					}
				}
			}
			else if(DrawMode==Mode_MoveGlueControl){
				if(ConnectingPoint!=NULL){
					ConnectingPoint->x	=SavedPoint.x;
					ConnectingPoint->y	=SavedPoint.y;
				}
				DrawMode=Mode_None;
				ConnectingGlue=NULL;
				ConnectingPoint=NULL;
				ConnectionConnector=NULL;
			}
		}
	}
}
RunnerConnector *RunnerMap::GetConnector(int X ,int Y)
{
	for(RunnerObject *a=Objects.GetFirst();a!=NULL;a=a->GetNext()){
		int	Px=a->geometry().left();
		int	Py=a->geometry().top();
		for(RunnerConnector *c=a->InputConnectors.GetFirst();c!=NULL;c=c->GetNext()){
			if(c->IsInclude(X-Px,Y-Py)==true){
				return c;
			}
		}
		for(RunnerConnector *c=a->OutputConnectors.GetFirst();c!=NULL;c=c->GetNext()){
			if(c->IsInclude(X-Px,Y-Py)==true){
				return c;
			}
		}
	}
	return NULL;
}

void RunnerMap::mouseReleaseEvent ( QMouseEvent * event )
{
	if(EditMode==true){
	}
}

void	RunnerMap::SlotObjLMouseUp(int ID,int x ,int y)
{
	if(DrawMode==Mode_MoveObj){
		if(MovingObj!=NULL){
			MovingObj=NULL;
			DrawMode=Mode_None;
		}
	}
}
void	RunnerMap::SlotObjLMouseDown(int ID,int x ,int y)
{
	if(DrawMode==Mode_None){
		MovingObj=FindRunnerObject(ID);
		if(MovingObj!=NULL){
			StartPosX=x+MovingObj->geometry().left();
			StartPosY=y+MovingObj->geometry().top();
			DrawMode=Mode_MoveObj;
		}
	}
}
void	RunnerMap::SlotObjRMouseUp(int ID,int x ,int y)
{
	RunnerObject	*Obj=FindRunnerObject(ID);
	if(Obj!=NULL){
		QPoint LPos(Obj->geometry().left()+x,Obj->geometry().top()+y);
		QPoint GPos=QWidget::mapToGlobal ( LPos);

		RunnerObjSettingForm	SettingDialog(Obj,NULL);
		SettingDialog.move(GPos);
		SettingDialog.exec();
		Obj->MakeConnectorPos();
		repaint();
	}
}
void	RunnerMap::SlotObjRMouseDown(int ID,int x ,int y)
{
}
void RunnerMap::SlotTimeOut()
{
	PaintCount++;
	for(RunnerObject *a=Objects.GetFirst();a!=NULL;a=a->GetNext()){
		a->IntervalExecute();
	}
	if(PaintCount>20){
		for(RunnerObject *a=Objects.GetFirst();a!=NULL;a=a->GetNext()){
			a->repaint();
		}
		repaint();
		PaintCount=0;
	}
}
void RunnerMap::paintEvent ( QPaintEvent * event )
{
	QPainter	Pnt(this);
	for(RunnerObject *a=Objects.GetFirst();a!=NULL;a=a->GetNext()){
		a->DrawConnector(Pnt);
		a->DrawStatus(Pnt);
	}
	for(GlueRunner *g=Glues.GetFirst();g!=NULL;g=g->GetNext()){
		g->Draw(Pnt);
	}
	if(DrawMode==Mode_Connecting){
		ConnectingGlue->Draw(Pnt);
		Pnt.setPen(Qt::red);
		if(ConnectingPoint!=NULL){
			Pnt.drawLine(ConnectingPoint->x,ConnectingPoint->y,CurrentPosX,CurrentPosY);
		}
	}
}

void RunnerMap::showEvent ( QShowEvent * event )
{

}