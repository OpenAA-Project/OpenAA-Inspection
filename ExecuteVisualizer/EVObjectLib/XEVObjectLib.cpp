#include "XExecuteVisualizer.h"
#include "XExecuteVisualizerForLib.h"
#include "XGeneralFunc.h"
#include "swap.h"
#include "XExecuteVisualizerInterface.h"

RunnerConnector::RunnerConnector(RunnerObject *parent)
	:Parent(parent)
{	
	ID=0;
	RelX=0;
	RelY=0;
}

const	int	ELen=3;
void	RunnerConnector::Draw(QPainter &Pnt)
{
	QPoint	XY[3];
	int	Px=GetParent()->geometry().left();
	int	Py=GetParent()->geometry().top();

	if(GetTypeOfInOut()==__In){
		Pnt.setBrush(Qt::yellow);
		Pnt.setPen(Qt::red);
		if(GetParent()->GetPosInput()==RunnerObject::IOPos_Left){
			XY[0].setX(Px+RelX-ELen);
			XY[0].setY(Py+RelY-ELen);
			XY[1].setX(Px+RelX+ELen);
			XY[1].setY(Py+RelY  );
			XY[2].setX(Px+RelX-ELen);
			XY[2].setY(Py+RelY+ELen);
		}
		else if(GetParent()->GetPosInput()==RunnerObject::IOPos_Top){
			XY[0].setX(Px+RelX-ELen);
			XY[0].setY(Py+RelY-ELen);
			XY[1].setX(Px+RelX     );
			XY[1].setY(Py+RelY+ELen);
			XY[2].setX(Px+RelX+ELen);
			XY[2].setY(Py+RelY-ELen);
		}
		else if(GetParent()->GetPosInput()==RunnerObject::IOPos_Right){
			XY[0].setX(Px+RelX+ELen);
			XY[0].setY(Py+RelY-ELen);
			XY[1].setX(Px+RelX-ELen);
			XY[1].setY(Py+RelY  );
			XY[2].setX(Px+RelX+ELen);
			XY[2].setY(Py+RelY+ELen);
		}
		else if(GetParent()->GetPosInput()==RunnerObject::IOPos_Bottom){
			XY[0].setX(Px+RelX-ELen);
			XY[0].setY(Py+RelY+ELen);
			XY[1].setX(Px+RelX  );
			XY[1].setY(Py+RelY-ELen);
			XY[2].setX(Px+RelX+ELen);
			XY[2].setY(Py+RelY+ELen);
		}
	}
	else{
		Pnt.setBrush(Qt::green);
		Pnt.setPen(Qt::red);
		if(GetParent()->GetPosOutput()==RunnerObject::IOPos_Left){
			XY[0].setX(Px+RelX+ELen);
			XY[0].setY(Py+RelY-ELen);
			XY[1].setX(Px+RelX-ELen);
			XY[1].setY(Py+RelY  );
			XY[2].setX(Px+RelX+ELen);
			XY[2].setY(Py+RelY+ELen);
		}
		else if(GetParent()->GetPosOutput()==RunnerObject::IOPos_Top){
			XY[0].setX(Px+RelX-ELen);
			XY[0].setY(Py+RelY+ELen);
			XY[1].setX(Px+RelX     );
			XY[1].setY(Py+RelY-ELen);
			XY[2].setX(Px+RelX+ELen);
			XY[2].setY(Py+RelY+ELen);
		}
		else if(GetParent()->GetPosOutput()==RunnerObject::IOPos_Right){
			XY[0].setX(Px+RelX-ELen);
			XY[0].setY(Py+RelY-ELen);
			XY[1].setX(Px+RelX+ELen);
			XY[1].setY(Py+RelY  );
			XY[2].setX(Px+RelX-ELen);
			XY[2].setY(Py+RelY+ELen);
		}
		else if(GetParent()->GetPosOutput()==RunnerObject::IOPos_Bottom){
			XY[0].setX(Px+RelX-ELen);
			XY[0].setY(Py+RelY-ELen);
			XY[1].setX(Px+RelX  );
			XY[1].setY(Py+RelY+ELen);
			XY[2].setX(Px+RelX+ELen);
			XY[2].setY(Py+RelY-ELen);
		}
	}
	Pnt.drawPolygon (XY,3);

	Pnt.setPen(Qt::black);
	if(GetTypeOfInOut()==__In){
		if(GetParent()->GetPosInput()==RunnerObject::IOPos_Left){
			QRect	Rect(Px+RelX-200,Py+RelY-10,200-ELen,20);
			Pnt.drawText(Rect, Qt::AlignRight | Qt::AlignVCenter ,GetName());
		}
		else if(GetParent()->GetPosInput()==RunnerObject::IOPos_Top){
			Pnt.save();
			Pnt.translate((Px+RelX),(Py+RelY-ELen));
			Pnt.rotate(-90);
			Pnt.drawText(0,0,GetName());
			Pnt.restore();
		}
		else if(GetParent()->GetPosInput()==RunnerObject::IOPos_Right){
			QRect	Rect(Px+RelX+ELen,Py+RelY-10,200-ELen,20);
			Pnt.drawText(Rect, Qt::AlignLeft | Qt::AlignVCenter ,GetName());
		}
		else if(GetParent()->GetPosInput()==RunnerObject::IOPos_Bottom){
			Pnt.save();
			Pnt.translate((Px+RelX),(Py+RelY+ELen));
			Pnt.rotate(90);
			Pnt.drawText(0,0,GetName());
			Pnt.restore();
		}
	}
	else{
		if(GetParent()->GetPosOutput()==RunnerObject::IOPos_Left){
			QRect	Rect(Px+RelX-200,Py+RelY-10,200-ELen,20);
			Pnt.drawText(Rect, Qt::AlignRight | Qt::AlignVCenter ,GetName());
		}
		else if(GetParent()->GetPosOutput()==RunnerObject::IOPos_Top){
			Pnt.save();
			Pnt.translate((Px+RelX),(Py+RelY-ELen));
			Pnt.rotate(-90);
			Pnt.drawText(0,0,GetName());
			Pnt.restore();
		}
		else if(GetParent()->GetPosOutput()==RunnerObject::IOPos_Right){
			QRect	Rect(Px+RelX+ELen,Py+RelY-10,200-ELen,20);
			Pnt.drawText(Rect, Qt::AlignLeft | Qt::AlignVCenter ,GetName());
		}
		else if(GetParent()->GetPosOutput()==RunnerObject::IOPos_Bottom){
			Pnt.save();
			Pnt.translate((Px+RelX),(Py+RelY+ELen));
			Pnt.rotate(90);
			Pnt.drawText(0,0,GetName());
			Pnt.restore();
		}
	}
}

bool	RunnerConnector::IsInclude(int x ,int y)
{
	if(abs(x-RelX)<=ELen && abs(y-RelY)<=ELen){
		return true;
	}
	return false;
}

//=================================================================================
RunnerObject::RunnerObject(LayersBase *Base ,RunnerMap *rmap)
	:QFrame(rmap)
	,ServiceForLayers(Base)
	,RMap(rmap)
{
	CurrentImage		=NULL;
	StatesDim			=NULL;
	AllocStateDimCount	=0;
	CurrentStateNumber	=0;
	DataVersion			=1;

	setFrameShape(QFrame::StyledPanel);
	setFrameShadow(QFrame::Raised);
	setLineWidth(2);
	setMidLineWidth(2);

	AccessDLL=NULL;
	resize(64,64);
	PosInput	=IOPos_Left;
	PosOutput	=IOPos_Right;
}
RunnerObject::~RunnerObject(void)
{
	if(StatesDim!=NULL){
		delete	[]StatesDim;
		StatesDim=NULL;
	}
	AllocStateDimCount=0;
}

void	RunnerObject::AllocateState(void)
{
	if(StatesDim!=NULL){
		delete	[]StatesDim;
		StatesDim=NULL;
	}
	struct RunnerState pState[1000];
	AllocStateDimCount=EnumStates(pState);
	if(AllocStateDimCount>0){
		StatesDim=new struct RunnerState[AllocStateDimCount];
		for(int i=0;i<AllocStateDimCount;i++){
			StatesDim[i]=pState[i];
		}
	}
}
struct RunnerState	*RunnerObject::GetCurrentState(void)
{
	if(AllocStateDimCount>CurrentStateNumber){
		return &StatesDim[CurrentStateNumber];
	}
	return NULL;
}

QString	RunnerObject::GetCurrentStateStr(void)
{
	if(AllocStateDimCount>CurrentStateNumber){
		return QString(StatesDim[CurrentStateNumber].Str);
	}
	return "";
}

int				RunnerObject::GetCurrentStateCode(void)
{
	if(AllocStateDimCount>CurrentStateNumber){
		return StatesDim[CurrentStateNumber].Code;
	}
	return -1;
}

bool			RunnerObject::SetCurrentState(int StateCode)
{
	for(int i=0;i<AllocStateDimCount;i++){
		if(StatesDim[i].Code==StateCode){
			CurrentStateNumber=i;
			return true;
		}
	}
	return false;
}

void			RunnerObject::AppendInputConnector(RunnerConnector *a)
{
	InputConnectors.AppendList(a);
	a->SetID(InputConnectors.GetCount());
}

int				RunnerObject::GetInputCount(void)
{
	return InputConnectors.GetCount();
}
RunnerConnector	&RunnerObject::GetInputConnector(int n)
{
	return *InputConnectors.GetItem(n);
}
RunnerConnector	*RunnerObject::FindInputConnector(int id)
{
	for(RunnerConnector *a=InputConnectors.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetID()==id){
			return a;
		}
	}
	return NULL;
}
bool			RunnerObject::GetInputBool(const QString &ConnName)
{
	for(RunnerConnector *a=InputConnectors.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetName()==ConnName){
			for(GlueRunner *g=RMap->Glues.GetFirst();g!=NULL;g=g->GetNext()){
				if(g->To()==a){
					if(g->From()!=NULL){
						RunnerConnectorOut	*p=dynamic_cast<RunnerConnectorOut *>(g->From());
						if(p!=NULL){
							return p->GetOutputBool();
						}
					}
				}
			}
		}
	}
	return false;		
}
int				RunnerObject::GetInputInt(const QString &ConnName)
{
	for(RunnerConnector *a=InputConnectors.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetName()==ConnName){
			for(GlueRunner *g=RMap->Glues.GetFirst();g!=NULL;g=g->GetNext()){
				if(g->To()==a){
					if(g->From()!=NULL){
						RunnerConnectorOut	*p=dynamic_cast<RunnerConnectorOut *>(g->From());
						if(p!=NULL){
							return p->GetOutputInt();
						}
					}
				}
			}
		}
	}
	return 0;		
}

bool	RunnerObject::GetInputBool(int n)
{
	RunnerConnector *a=InputConnectors.GetItem(n);
	for(GlueRunner *g=RMap->Glues.GetFirst();g!=NULL;g=g->GetNext()){
		if(g->To()==a){
			if(g->From()!=NULL){
				RunnerConnectorOut	*p=dynamic_cast<RunnerConnectorOut *>(g->From());
				if(p!=NULL){
					return p->GetOutputBool();
				}
			}
		}
	}
	return false;		
}
int		RunnerObject::GetInputInt(int n)
{
	RunnerConnector *a=InputConnectors.GetItem(n);
	for(GlueRunner *g=RMap->Glues.GetFirst();g!=NULL;g=g->GetNext()){
		if(g->To()==a){
			if(g->From()!=NULL){
				RunnerConnectorOut	*p=dynamic_cast<RunnerConnectorOut *>(g->From());
				if(p!=NULL){
					return p->GetOutputInt();
				}
			}
		}
	}
	return 0;		
}


void			RunnerObject::AppendOutputConnector(RunnerConnector *a)
{
	OutputConnectors.AppendList(a);
	a->SetID(OutputConnectors.GetCount());
}
int				RunnerObject::GetOutputCount(void)
{
	return OutputConnectors.GetCount();
}
RunnerConnector	&RunnerObject::GetOutputConnector(int n)
{
	return *OutputConnectors.GetItem(n);
}
RunnerConnector	*RunnerObject::FindOutputConnector(int id)
{
	for(RunnerConnector *a=OutputConnectors.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetID()==id){
			return a;
		}
	}
	return NULL;
}

void	RunnerObject::Draw(QPainter &Pnt)
{
}

bool	RunnerObject::Save(QIODevice *f)
{
	if(::Save(f,DataVersion)==false)
		return false;

	if(::Save(f,ID)==false)
		return false;

	QRect	r=geometry();
	int32	x=r.left();
	int32	y=r.top();
	if(::Save(f,x)==false)
		return false;
	if(::Save(f,y)==false)
		return false;

	if(::Save(f,Comment)==false)
		return false;
	if(::Save(f,UniqueName)==false)
		return false;

	BYTE	dPosInput=(BYTE)PosInput;
	if(::Save(f,dPosInput)==false)
		return false;
	BYTE	dPosOutput=(BYTE)PosOutput;
	if(::Save(f,dPosOutput)==false)
		return false;

	return true;
}
bool	RunnerObject::Load(QIODevice *f)
{
	if(::Load(f,DataVersion)==false)
		return false;

	if(::Load(f,ID)==false)
		return false;

	int32	x;
	int32	y;
	if(::Load(f,x)==false)
		return false;
	if(::Load(f,y)==false)
		return false;
	move(x,y);

	if(::Load(f,Comment)==false)
		return false;
	if(::Load(f,UniqueName)==false)
		return false;

	BYTE	dPosInput;
	if(::Load(f,dPosInput)==false)
		return false;
	PosInput=(IOPosition)dPosInput;

	BYTE	dPosOutput;
	if(::Load(f,dPosOutput)==false)
		return false;
	PosOutput=(IOPosition)dPosOutput;

	MakeConnectorPos();

	return true;
}

bool	RunnerObject::GetRootName(QString &DLLRoot, QString &DLLName)
{
	if(AccessDLL!=NULL){
		AccessDLL->GetRootName(DLLRoot, DLLName);
		return true;
	}
	return false;
}

void	RunnerObject::SetImage(QImage *img)
{
	CurrentImage=img;
	//repaint();
}
void RunnerObject::mousePressEvent ( QMouseEvent * event )
{
	if(event->button()==Qt::LeftButton){
		emit	SignalLMouseDown(GetID(),event->x(),event->y());
	}
	else if(event->button()==Qt::RightButton){
		emit	SignalRMouseDown(GetID(),event->x(),event->y());
	}
}

void RunnerObject::mouseReleaseEvent ( QMouseEvent * event )
{
	if(event->button()==Qt::LeftButton){
		emit	SignalLMouseUp(GetID(),event->x(),event->y());
	}
	else if(event->button()==Qt::RightButton){
		emit	SignalRMouseUp(GetID(),event->x(),event->y());
	}
}

void	RunnerObject::MakeConnectorPos(void)
{
	const int	VSep=6;
	const int	HSep=6;
	int	LeftNumb=GetCountOfPosConnector(IOPos_Left);
	if(LeftNumb!=0){
		int	sp=height()/(LeftNumb+1);
		if(sp<VSep){
			sp=VSep;
		}
		int	L=sp*LeftNumb;
		int	D=(height()-L)/2;

		int	Pos=D;
		if(GetPosInput()==IOPos_Left){
			for(RunnerConnector *a=InputConnectors.GetFirst();a!=NULL;a=a->GetNext()){
				a->RelX=-HSep;
				a->RelY=Pos;
				Pos+=sp;
			}
		}
		if(GetPosOutput()==IOPos_Left){
			for(RunnerConnector *a=OutputConnectors.GetFirst();a!=NULL;a=a->GetNext()){
				a->RelX=-HSep;
				a->RelY=Pos;
				Pos+=sp;
			}
		}
	}
	int	TopNumb=GetCountOfPosConnector(IOPos_Top);
	if(TopNumb!=0){
		int	sp=width()/(TopNumb+1);
		if(sp<HSep){
			sp=HSep;
		}
		int	L=sp*TopNumb;
		int	D=(width()-L)/2;

		int	Pos=D;
		if(GetPosInput()==IOPos_Top){
			for(RunnerConnector *a=InputConnectors.GetFirst();a!=NULL;a=a->GetNext()){
				a->RelX=Pos;
				a->RelY=-VSep;
				Pos+=sp;
			}
		}
		if(GetPosOutput()==IOPos_Top){
			for(RunnerConnector *a=OutputConnectors.GetFirst();a!=NULL;a=a->GetNext()){
				a->RelX=Pos;
				a->RelY=-VSep;
				Pos+=sp;
			}
		}
	}
	int	RightNumb=GetCountOfPosConnector(IOPos_Right);
	if(RightNumb!=0){
		int	sp=height()/(RightNumb+1);
		if(sp<VSep){
			sp=VSep;
		}
		int	L=sp*RightNumb;
		int	D=(height()-L)/2;

		int	Pos=D;
		if(GetPosInput()==IOPos_Right){
			for(RunnerConnector *a=InputConnectors.GetFirst();a!=NULL;a=a->GetNext()){
				a->RelX=width()+HSep;
				a->RelY=Pos;
				Pos+=sp;
			}
		}
		if(GetPosOutput()==IOPos_Right){
			for(RunnerConnector *a=OutputConnectors.GetFirst();a!=NULL;a=a->GetNext()){
				a->RelX=width()+HSep;
				a->RelY=Pos;
				Pos+=sp;
			}
		}
	}
	int	BottomNumb=GetCountOfPosConnector(IOPos_Bottom);
	if(BottomNumb!=0){
		int	sp=width()/(BottomNumb+1);
		if(sp<HSep){
			sp=HSep;
		}
		int	L=sp*BottomNumb;
		int	D=(width()-L)/2;

		int	Pos=D;
		if(GetPosInput()==IOPos_Bottom){
			for(RunnerConnector *a=InputConnectors.GetFirst();a!=NULL;a=a->GetNext()){
				a->RelX=Pos;
				a->RelY=height()+VSep;
				Pos+=sp;
			}
		}
		if(GetPosOutput()==IOPos_Bottom){
			for(RunnerConnector *a=OutputConnectors.GetFirst();a!=NULL;a=a->GetNext()){
				a->RelX=Pos;
				a->RelY=height()+VSep;
				Pos+=sp;
			}
		}
	}
}

int	RunnerObject::GetCountOfPosConnector(RunnerObject::IOPosition Pos)
{
	int	Ret=0;
	if(GetPosInput()==Pos){
		Ret+=InputConnectors.GetCount();
	}
	if(GetPosOutput()==Pos){
		Ret+=OutputConnectors.GetCount();
	}
	return Ret;
}
void	RunnerObject::DrawConnector(QPainter &Pnt)
{
	for(RunnerConnector *a=InputConnectors.GetFirst();a!=NULL;a=a->GetNext()){
		a->Draw(Pnt);
	}
	for(RunnerConnector *b=OutputConnectors.GetFirst();b!=NULL;b=b->GetNext()){
		b->Draw(Pnt);
	}
}
void RunnerObject::paintEvent ( QPaintEvent * event )
{
	QPainter	Pnt(this);

	if(CurrentImage!=NULL){
		Pnt.drawImage(0,0,*CurrentImage);
	}
}
void	RunnerObject::DrawStatus(QPainter &Pnt)
{
	int	Px=geometry().left();
	int	Py=geometry().top();
	int	H=geometry().height();
	int	W=geometry().width();

	Pnt.setBrush(Qt::white);
	Pnt.setPen(Qt::white);
	if(GetPosInput()!=RunnerObject::IOPos_Bottom
	&& GetPosOutput()!=RunnerObject::IOPos_Bottom){
		QRect	Rect(Px,Py+H,W,20);
		Pnt.drawText(Rect, Qt::AlignRight | Qt::AlignVCenter ,GetCurrentStateStr());
	}
	else if(GetPosInput()!=RunnerObject::IOPos_Top
	&& GetPosOutput()!=RunnerObject::IOPos_Top){
		QRect	Rect(Px,Py-20,W,20);
		Pnt.drawText(Rect, Qt::AlignRight | Qt::AlignVCenter ,GetCurrentStateStr());
	}
	if(GetPosInput()!=RunnerObject::IOPos_Left
	&& GetPosOutput()!=RunnerObject::IOPos_Left){
		QRect	Rect(0,0,W,20);
		Pnt.save();
		Pnt.translate(Px-20,Py);
		Pnt.rotate(-90);
		Pnt.drawText(Rect, Qt::AlignRight | Qt::AlignVCenter ,GetCurrentStateStr());
		Pnt.restore();
	}
	if(GetPosInput()!=RunnerObject::IOPos_Right
	&& GetPosOutput()!=RunnerObject::IOPos_Right){
		QRect	Rect(0,0,W,20);
		Pnt.save();
		Pnt.translate(Px+W,Py);
		Pnt.rotate(-90);
		Pnt.drawText(Rect, Qt::AlignRight | Qt::AlignVCenter ,GetCurrentStateStr());
		Pnt.restore();
	}
}
//=================================================================================