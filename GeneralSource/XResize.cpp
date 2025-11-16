#include "XTypeDef.h"
#include "XResize.h"
#include "swap.h"

void	WidgetGeometry::SetWidget(QWidget *w)
{
	WPoint=w;
	Rect=w->geometry();

	const QObjectList	&Obj=w->children();
	int	N=Obj.count();
	for(int i=0;i<N;i++){
		QObject	*o=Obj[i];
		QWidget	*c=dynamic_cast<QWidget *>(o);
		if(c!=NULL){
			WidgetGeometry	*g=new WidgetGeometry();
			g->SetWidget(c);
			Children.AppendList(g);
		}
		else{
			SetObject(o);
		}
	}
}

void	WidgetGeometry::SetObject(QObject *w)
{
	const QObjectList	&Obj=w->children();
	int	N=Obj.count();
	for(int i=0;i<N;i++){
		QObject	*o=Obj[i];
		QWidget	*c=dynamic_cast<QWidget *>(o);
		if(c!=NULL){
			WidgetGeometry	*g=new WidgetGeometry();
			g->SetWidget(c);
			Children.AppendList(g);
		}
		else{
			SetObject(o);
		}
	}
}

void	WidgetGeometry::Resize(void)
{
	if(WPoint==NULL)
		return;
	QRect	R=WPoint->geometry();
	double	RateX=((double)R.width())/((double)Rect.width());
	double	RateY=((double)R.height())/((double)Rect.height());
	Resize(min(RateX,RateY));
}
void	WidgetGeometry::Resize(double Rate)
{
	if(WPoint==NULL)
		return;
	ChangedRate=Rate;
	QFont	font=WPoint->font();
	font.setPointSize(font.pointSize()*Rate);
	WPoint->setFont(font);
	WPoint->setGeometry(Rect.left()*Rate,Rect.top()*Rate,Rect.width()*Rate,Rect.height()*Rate);
	for(WidgetGeometry *a=Children.GetFirst();a!=NULL;a=a->GetNext()){
		a->Resize(Rate);
	}
}
