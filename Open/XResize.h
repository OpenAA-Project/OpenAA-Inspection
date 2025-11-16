#if	!defined(XResize_h)
#define	XResize_h

#include<QWidget>
#include<QStringList>
#include<QRect>
#include "NList.h"
#include "XTypeDef.h"

class	WidgetGeometry;

class	WidgetGeometry : public NPList<WidgetGeometry>
{
public:
	QWidget		*WPoint;
	double	ChangedRate;
	QRect	Rect;
	NPListPack<WidgetGeometry>	Children;

	WidgetGeometry(void){	WPoint=NULL;	}

	void	SetWidget(QWidget *w);
	void	SetObject(QObject *w);

	void	Resize(void);
	void	Resize(double Rate);
};



#endif