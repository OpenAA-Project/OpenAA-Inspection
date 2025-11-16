#include "PQSystemExecutor.h"
#include "PQSystemService.h"

LayersBasePQSystem::LayersBasePQSystem(EntryPointBase *pEntryPoint)
	:LayersBase(pEntryPoint)
{
	ParamPQSystemInst=new ParamPQSystem(this);
}
LayersBasePQSystem::LayersBasePQSystem(const QString &TypeName ,LayersBase *ParentLayer)
	:LayersBase(TypeName ,ParentLayer)
{
	ParamPQSystemInst=new ParamPQSystem(this);
}

LayersBasePQSystem::LayersBasePQSystem(const LayersBase *Parent)
	:LayersBase(Parent)
{
	ParamPQSystemInst=new ParamPQSystem(this);
}
//=========================================

MenuButton::MenuButton(PQSystemExecutor *p)
	:Parent(p),Controller(NULL)
{
	connect(this,SIGNAL(clicked()),this,SLOT(SlotClicked()));
	setCheckable(true);
}

void	MenuButton::SlotClicked()
{
	if(isChecked()==false){
		setChecked(true);
	}
	if(Controller!=NULL){
		Parent->ShowController(Controller);
	}
}


PQSystemExecutor::PQSystemExecutor(LayersBase *base,QWidget *parent)
    : QMainWindow(parent),ServiceForLayers(base),Runners(base)
{
    ui.setupUi(this);
	TabCount	=0;
	CurrentRunner	=NULL;

	LayersBasePQSystem	*PQLBase=(LayersBasePQSystem *)base;
	PQLBase->SetPQRunnerControllerContainer(&Runners);
}
bool	PQSystemExecutor::LoadDLL(const QString &DLLPath)
{
	if(Runners.LoadDLL(DLLPath)==false){
		return false;
	}
	while(ui.toolBoxMenu->count()>0){
		ui.toolBoxMenu->removeItem(0);
	}
	Runners.SetLanguage(GetLayersBase()->GetLanguageCode());
	for(PQRunnerController *a=Runners.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Create()==false){
			return false;
		}
		PQSystemRunner	*r=a->GetRunner();
		const	QString	s=r->GetPath();
		QStringList	List=s.split('/');
		if(List.count()<2){
			return false;
		}
		QString	Str1=List[0];
		bool	Found=false;
		for(int i=0;i<TabCount;i++){
			if(Str1==Tabs[i].GetFirst()->TabName){
				MenuButton	*m=new MenuButton(this);
				m->TabName=Str1;
				m->ButtonName=List[1];
				m->Controller	=a;
				Tabs[i].AppendList(m);
				Found=true;
				break;
			}
		}
		if(Found==false){
			if(TabCount<100){
				MenuButton	*m=new MenuButton(this);
				m->TabName=Str1;
				m->ButtonName=List[1];
				m->Controller	=a;
				Tabs[TabCount].AppendList(m);
				TabCount++;
			}
		}
	}
	for(PQRunnerController *a=Runners.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->InitialRunner()==false){
			return false;
		}
	}
	int	ButtonHeight=32;
	for(int i=0;i<TabCount;i++){
		QWidget *w=new QWidget();
		ui.toolBoxMenu->addItem(w, Tabs[i].GetFirst()->TabName);
		int	Row=0;
		for(MenuButton *m=Tabs[i].GetFirst();m!=NULL;m=m->GetNext(),Row++){
			m->setParent(w);
			m->setGeometry(32,Row*ButtonHeight,ui.toolBoxMenu->width()-32,ButtonHeight);
			m->setText(m->ButtonName);
		}
	}
}

void PQSystemExecutor::resizeEvent(QResizeEvent *event)
{
	ui.toolBoxMenu->resize(ui.toolBoxMenu->width(),height());
}

void	PQSystemExecutor::ShowController(PQRunnerController *Controller)
{
	PQSystemRunner	*r=Controller->GetRunner();

	for(int i=0;i<TabCount;i++){
		for(MenuButton *m=Tabs[i].GetFirst();m!=NULL;m=m->GetNext()){
			if(m->Controller->GetRunner()!=r){
				m->setChecked(false);
			}
		}
	}

	if(CurrentRunner!=r && CurrentRunner!=NULL){
		CurrentRunner->close();
	}

	int	W=r->width();
	int	H=r->height();
	ui.frame->setGeometry(ui.toolBoxMenu->width(),0,W,H);
	r->setParent(ui.frame);
	r->show();
	CurrentRunner=r;
	resize(ui.toolBoxMenu->width()+W,H);
}
