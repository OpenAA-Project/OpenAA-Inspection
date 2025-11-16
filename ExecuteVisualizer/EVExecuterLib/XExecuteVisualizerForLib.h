#if	!defined(XEXECUTEVISUALIZERFORLIB_H)
#define	XEXECUTEVISUALIZERFORLIB_H

#include "NList.h"
#include "XTypeDef.h"
#include <QString>
#include <QPainter>
#include <QIODevice>
#include <QLabel>
#include <QWidget>
#include <QTimer>
#include "XServiceForLayers.h"
#include <QLibrary>
#include "XExecuteVisualizer.h"
#include "XYCross.h"

class	RunnerMap;
class	RunnerConnector;
class	RunnerObject;
class	LanguagePackage;


class	GlueRunner : public NPList<GlueRunner>
{
	int32				ID;
	RunnerMap			*RMap;
	RunnerConnector		*ObjFrom;
	RunnerConnector		*ObjTo;
	XYLines				Lines;

	int					DrawingPosLen;

public:
	GlueRunner(RunnerMap *rmap);
	~GlueRunner(void);

	RunnerMap	*GetRMap(void)	{	return RMap;	}

	int32	GetID(void)		{	return ID;	}
	void	SetID(int32 id)	{	ID=id;		}

	RunnerConnector	*From(void)	{	return ObjFrom;	}
	RunnerConnector	*To(void)	{	return ObjTo;	}
	void	SetFrom(RunnerConnector	*a)	{	ObjFrom=a;	}
	void	SetTo(RunnerConnector	*a)	{	ObjTo=a;	}

	XYClass	*GetFirstPoint(void);
	XYClass	*GetLastPoint(void);
	void	AddPoint(int x ,int y);
	void	RemoveLast(void);
	bool	IsInclude(int x ,int y);
	void	AddXYInFirstPoint(int dx,int dy);
	void	AddXYInLastPoint (int dx,int dy);
	XYClass	*GetClosedPoint(int x ,int y ,double Area=5);

	virtual	void	Draw(QPainter &Pnt);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

//-----------------------------------------------------------------

class	RunerDLLContainer : public NPListPack<RunnerObjDLL>,virtual public ServiceForLayers
{
	friend	class	RunnerObjDLL;
public:
	RunerDLLContainer(LayersBase *base);
	~RunerDLLContainer(void);

	void	LoadDLL(const QString &DllPath);

	RunnerObjDLL	*FindDLL(const QString &DLLRoot ,const QString &DLLName);
};

class	RunnerMap : public QWidget, virtual public ServiceForLayers ,public RunerDLLContainer
{
	Q_OBJECT

	friend	class	RunnerObject;
	friend	class	RunnerConnector;

	int				StartPosX ,StartPosY;
	RunnerObject	*MovingObj;
	XYClass			*ConnectingPoint;
	XYClass			SavedPoint;
	GlueRunner		*ConnectingGlue;
	RunnerConnector *ConnectionConnector;
	int				CurrentPosX,CurrentPosY;
	int				PaintCount;

	enum	__DrawMode
	{
		 Mode_None
		,Mode_MoveObj
		,Mode_Connecting
		,Mode_MoveGlueControl
	}DrawMode;

	QTimer			Tm;
public:
	NPListPack<RunnerObject>	Objects;
	NPListPack<GlueRunner>		Glues;
	bool						EditMode;

	RunnerMap(LayersBase *base ,bool _EditMode ,QWidget *parent=NULL);
	~RunnerMap(void);

	void	Draw(QPainter &Pnt);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	FitToParent(void);

	void			AppendRunnerObject(RunnerObject *obj,RunnerObjDLL *accessDLL);
	void			DeleteRunnerObj(RunnerObject *obj);
	RunnerObject	*FindRunnerObject(int ID);

	void			AppendGlue(GlueRunner *a);
	void			RemoveGlue(GlueRunner *a);

protected:
	
	virtual void mouseDoubleClickEvent ( QMouseEvent * event )	override;
	virtual void showEvent ( QShowEvent * event )				override;
	virtual	void paintEvent ( QPaintEvent * event )				override;

	virtual	void mouseMoveEvent ( QMouseEvent * event )			override;
	virtual	void mousePressEvent ( QMouseEvent * event )		override; 
	virtual	void mouseReleaseEvent ( QMouseEvent * event )		override; 

	RunnerConnector *GetConnector(int X ,int Y);
	GlueRunner	*GetGlueControlPoint(int x ,int y ,XYClass **XY);

private slots:
	void	SlotObjLMouseUp(int ID,int x ,int y);
	void	SlotObjLMouseDown(int ID,int x ,int y);
	void	SlotObjRMouseUp(int ID,int x ,int y);
	void	SlotObjRMouseDown(int ID,int x ,int y);
	void	SlotTimeOut();
signals:
	void	SignalLDoubleClick(int x ,int y);
};

#endif