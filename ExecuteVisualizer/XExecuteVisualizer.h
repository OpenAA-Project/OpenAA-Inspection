#if	!defined(XEXECUTEVISUALIZER_H)
#define	XEXECUTEVISUALIZER_H

#include "NList.h"
#include "XTypeDef.h"
#include <QString>
#include <QPainter>
#include <QIODevice>
#include <QLabel>
#include <QWidget>
#include "XServiceForLayers.h"
#include <QLibrary>

class	RunnerConnecter;
class	RunnerObject;
class	RunnerObjDLL;
class	RunnerMap;


class	RunnerConnector : public NPList<RunnerConnector>
{
	friend	class	RunnerObject;
	friend	class	RunnerMap;

	int				ID;
	RunnerObject	*Parent;
	int				RelX,RelY;
public:
	RunnerConnector(RunnerObject *parent);

	enum	TypeOfRunnerConnector
	{
		__ValueInt
		,__ValueBool
	};
	enum	__TypeOfInOut
	{
		__In
		,__Out
	};

	virtual	TypeOfRunnerConnector	GetType(void)	=0;
	virtual	QString					GetName(void)	=0;

	int32	GetID(void)					{	return ID;	}
	void	SetID(int32 id)				{	ID=id;		}
	RunnerObject	*GetParent(void)	{	return Parent;	}

	virtual	void	Draw(QPainter &Pnt);
	bool	IsInclude(int x ,int y);

private:
	virtual	__TypeOfInOut		GetTypeOfInOut(void)	=0;
};

class	RunnerConnectorIn : public RunnerConnector
{
public:
	RunnerConnectorIn(RunnerObject *parent):RunnerConnector(parent){}

	virtual	void	SetInputBool(bool b){}
	virtual	void	SetInputInt(int d)	{}

	virtual	__TypeOfInOut		GetTypeOfInOut(void)	{	return RunnerConnector::__In;	}
};

class	RunnerConnectorOut : public RunnerConnector
{
public:
	RunnerConnectorOut(RunnerObject *parent):RunnerConnector(parent){}

	virtual	bool	GetOutputBool(void)	{	return false;	}
	virtual	int		GetOutputInt(void)	{	return 0;		}

	virtual	__TypeOfInOut		GetTypeOfInOut(void)	{	return RunnerConnector::__Out;	}
};

struct	RunnerState
{
	int32		Code;
	char		*Str;
};

class	RunnerObject : public QFrame ,public NPList<RunnerObject> , public ServiceForLayers
{
	Q_OBJECT

	friend	class	RunnerConnector;
	friend	class	RunnerMap;

	int32			ID;
	RunnerObjDLL	*AccessDLL;
	RunnerMap		*RMap;
	QString			Explain;
	int32			DataVersion;

protected:
	QImage		*CurrentImage;

	QString		Comment;
	QString		UniqueName;
	struct	RunnerState		*StatesDim;
	int						AllocStateDimCount;
	int						CurrentStateNumber;

	NPListPack<RunnerConnector>		InputConnectors;
	NPListPack<RunnerConnector>		OutputConnectors;

public:
	enum	IOPosition
	{
		 IOPos_Left		=1
		,IOPos_Top		=2
		,IOPos_Right	=3
		,IOPos_Bottom	=4
	};
private:
	IOPosition	PosInput;
	IOPosition	PosOutput;

public:
	RunnerObject(LayersBase *Base ,RunnerMap *rMap);
	virtual	~RunnerObject(void);

	int32	GetID(void)		{	return ID;	}
	void	SetID(int32 id)	{	ID=id;		}

	QString	GetExplain(void)				{	return Explain;	}
	void	SetExplain(const QString &str)	{	Explain=str;	}

	virtual	void	ShowSettingDialog(void){}
	virtual	int		EnumStates(struct RunnerState pState[1000])	=0;
	virtual	void	IntervalExecute(void)						=0;

	void			AllocateState(void);
	struct RunnerState	*GetCurrentState(void);
	QString			GetCurrentStateStr(void);
	int				GetCurrentStateCode(void);
	bool			SetCurrentState(int StateCode);

	QString	GetUniqueName(void)					{	return UniqueName;	}
	void	SetUniqueName(const QString &str)	{	UniqueName=str;		}
	QString	GetComment(void)					{	return Comment;		}
	void	SetComment(const QString &str)		{	Comment=str;		}

	RunnerObjDLL	*GetAccessDLL(void)				{	return AccessDLL;	}
	void			SetAccessDLL(RunnerObjDLL *dll)	{	AccessDLL=dll;		}

	void			AppendInputConnector(RunnerConnector *a);
	int				GetInputCount(void);
	RunnerConnector	&GetInputConnector(int n);
	RunnerConnector	*FindInputConnector(int id);
	bool			GetInputBool(const QString &ConnName);
	int				GetInputInt(const QString &ConnName);
	bool			GetInputBool(int n);
	int				GetInputInt(int n);

	void			AppendOutputConnector(RunnerConnector *a);
	int				GetOutputCount(void);
	RunnerConnector	&GetOutputConnector(int n);
	RunnerConnector	*FindOutputConnector(int id);

	virtual	void	Draw(QPainter &Pnt);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);

	void			SetDataVersion(int ver)	{	DataVersion=ver;	}
	int				GetDataVersion(void)	{	return DataVersion;	}

	bool	GetRootName(QString &DLLRoot, QString &DLLName);

	void	SetImage(QImage *img);

	IOPosition	GetPosInput(void)		{	return PosInput;	}
	IOPosition	GetPosOutput(void)		{	return PosOutput;	}
	void	SetPosInput(IOPosition pos)	{	PosInput=pos;		}
	void	SetPosOutput(IOPosition	pos){	PosOutput=pos;		}
	void	DrawConnector(QPainter &Pnt);

protected:
	virtual	void paintEvent ( QPaintEvent * event )	override;
	void	DrawStatus(QPainter &Pnt);

	virtual	void mousePressEvent ( QMouseEvent * event )	override; 
	virtual	void mouseReleaseEvent ( QMouseEvent * event )	override; 

public:
	void	MakeConnectorPos(void);
private:
	int		GetCountOfPosConnector(IOPosition Pos);

signals:
	void	SignalLMouseUp(int ID,int x ,int y);
	void	SignalLMouseDown(int ID,int x ,int y);
	void	SignalRMouseUp(int ID,int x ,int y);
	void	SignalRMouseDown(int ID,int x ,int y);
};


#endif