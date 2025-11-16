#if	!defined(XIntegrationSimpleImagePanelPacket_h)
#define	XIntegrationSimpleImagePanelPacket_h

#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XDataInLayer.h"
#include "mtGraphicUnit.h"
#include "XIntegrationPacketComm.h"
#include <QToolButton>
#include "XIntegrationSimpleImagePanelCommon.h"

class	IntegrationAlgoSimpleImagePanel;
//====================================================================================================

class	IntegrationReqPanelImage : public IntegrationCmdPacketBase
{
public:
	struct _PanelImageInfo
	{
		int		Phase;
		double	ZoomRate;
		int		Movx,Movy;
		int		CanvasWidth,CanvasHeight;
		int		CountOfLayer;

		_PanelImageInfo(void){	Phase=0;	CanvasWidth=0;	CanvasHeight=0;	CountOfLayer=0;	}
	}PanelImageInfo;

	IntegrationReqPanelImage(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	

private:
	void	MakeImage(BYTE *ImageBuff);

};

class	IntegrationAckPanelImage : public IntegrationCmdPacketBase
{
public:
	//QImage	*Image;
	struct _PanelImageInfo
	{
		int	XLen,YLen;
		int	CountOfLayer;
		_PanelImageInfo(void){	XLen=0;	YLen=0;	CountOfLayer=0;	}
	}PanelImageInfo;
	BYTE	*ImageBuff;

	IntegrationAckPanelImage(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);
	virtual	~IntegrationAckPanelImage(void);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	void	Allocate(int CanvasWidth,int CanvasHeight,int CountOfLayer);
	void	CopyToImage(QImage &Img);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName){}
};

class	IntegrationCmdUndo : public IntegrationCmdPacketBase
{
public:
	IntegrationCmdUndo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	IntegrationCmdRedo : public IntegrationCmdPacketBase
{
public:
	IntegrationCmdRedo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);
};


//====================================================================================================

class	IntegrationReqAlgorithmPanelImage : public IntegrationCmdPacketBase
{
	friend	class	IntegrationAlgoSimpleImagePanel;

public:
	struct _ReqAlgorithmPanelInfo
	{
		int		Phase;
		double	ZoomRate;
		int		Movx,Movy;
		int		CanvasWidth,CanvasHeight;
		int		CountOfLayer;
		bool	OnSelection;
		bool	OnMoving;
		int		SelectionDx;
		int		SelectionDy;
		_ReqAlgorithmPanelInfo(void){	Phase=0;	CanvasWidth=0;	CanvasHeight=0;	}
	}ReqAlgorithmPanelInfo;
	IntList		LayerList;
	QByteArray	DrawAtterData;
	QString		AlgoDLLRoot;
	QString		AlgoDLLName;

	IntegrationReqAlgorithmPanelImage(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	

private:

};

class	IntegrationAckAlgorithmPanelImage : public IntegrationCmdPacketBase
{
	friend	class	IntegrationAlgoSimpleImagePanel;

public:
	struct _AckAlgorithmPanelInfo
	{
		int		CanvasWidth,CanvasHeight;
		int		CountOfLayer;

		_AckAlgorithmPanelInfo(void){	CanvasWidth=0;	CanvasHeight=0;	CountOfLayer=0;	}
	}AckAlgorithmPanelInfo;
	//QImage	*Image;
	BYTE		*ImageBuff;

	IntegrationAckAlgorithmPanelImage(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);
	virtual	~IntegrationAckAlgorithmPanelImage(void);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName){}

	void	ConvertToImage(QImage &CurrentImage);
};

//====================================================================================================

class	IntegrationCmdAlgorithmPanelAddItem : public IntegrationCmdPacketBase
{
public:
	int			Phase;
	IntList		LayerList;
	FlexArea	Area;
	QString		AlgoDLLRoot;
	QString		AlgoDLLName;
	QByteArray	Data;
	QByteArray	SomethingData;

	IntegrationCmdAlgorithmPanelAddItem(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	

private:
};

//====================================================================================================

class	IntegrationCmdAlgorithmPanelReleaseSelection : public IntegrationCmdPacketBase
{
public:
	QString		AlgoDLLRoot;
	QString		AlgoDLLName;

	IntegrationCmdAlgorithmPanelReleaseSelection(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	

private:
};
//====================================================================================================

class	IntegrationCmdAlgorithmPanelMoveSelection : public IntegrationCmdPacketBase
{
public:
	int			Dx,Dy;
	QString		AlgoDLLRoot;
	QString		AlgoDLLName;

	IntegrationCmdAlgorithmPanelMoveSelection(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	

private:
};
//====================================================================================================

class	IntegrationCmdAlgorithmPanelDeleteSelectItems : public IntegrationCmdPacketBase
{
public:
	int			Phase;
	QString		AlgoDLLRoot;
	QString		AlgoDLLName;
	QByteArray	SomethingData;

	IntegrationCmdAlgorithmPanelDeleteSelectItems(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	

private:
};

//====================================================================================================

class	IntegrationCmdAlgorithmPanelCutItem : public IntegrationCmdPacketBase
{
public:
	int			Phase;
	IntList		LayerList;
	FlexArea	Area;
	QString		AlgoDLLRoot;
	QString		AlgoDLLName;
	QByteArray	SomethingData;

	IntegrationCmdAlgorithmPanelCutItem(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	

private:
};

//====================================================================================================

class	IntegrationCmdAlgorithmPanelSelectArea : public IntegrationCmdPacketBase
{
public:
	int			Phase;
	IntList		LayerList;
	FlexArea	Area;
	QString		AlgoDLLRoot;
	QString		AlgoDLLName;
	bool		UseSelectionDialog;
	QByteArray	SomethingData;

	IntegrationCmdAlgorithmPanelSelectArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	

private:
};

class	IntegrationCmdAckAlgorithmPanelSelectArea : public IntegrationCmdPacketBase
{
public:
	SelectedItemsInfoContainer	SelectedContainer;

	IntegrationCmdAckAlgorithmPanelSelectArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName){}

private:
};

class	IntegrationCmdAlgorithmPanelSelectItems : public IntegrationCmdPacketBase
{
public:
	SelectedItemsInfoContainer	SelectedContainer;

	IntegrationCmdAlgorithmPanelSelectItems(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	IntegrationCmdReqHasSelectedItem : public IntegrationCmdPacketBase
{
public:
	int			Phase;
	QString		AlgoDLLRoot;
	QString		AlgoDLLName;

	IntegrationCmdReqHasSelectedItem(LayersBase *Base 
									,const QString &EmitterRoot,const QString &EmitterName 
									,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);
};
class	IntegrationCmdAckHasSelectedItem : public IntegrationCmdPacketBase
{
public:
	int32	SelectedItemCount;

	IntegrationCmdAckHasSelectedItem(LayersBase *Base 
									,const QString &EmitterRoot,const QString &EmitterName 
									,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo,int cmd ,QString &EmitterRoot,QString &EmitterName){}
};

//==================================================================

class	IntegrationCmdReqAlgoDataWithControlPoints: public IntegrationCmdPacketBase
{
public:
	int	Phase;
	int	ShadowLevel;
	int	ShadowNumber;
	RootNameListContainer	AlgorithmList;
	QByteArray	CopyToSlaveInfo;
	QString		DLLRoot;
	QString		DLLName;

	IntegrationCmdReqAlgoDataWithControlPoints(LayersBase *Base 
									,const QString &EmitterRoot,const QString &EmitterName 
									,int SlaveNo=-1);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	IntegrationCmdAckAlgoDataWithControlPoints: public IntegrationCmdPacketBase
{
public:
	XYPointContainerWithName	ControlPointsForPages;
	AlgoListArrayContainer	AlgoList;

	IntegrationCmdAckAlgoDataWithControlPoints(LayersBase *Base 
									,const QString &EmitterRoot,const QString &EmitterName 
									,int SlaveNo=-1);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName){}	
};

class	IntegrationCmdSetAlgoDataWithControlPoints: public IntegrationCmdPacketBase
{
public:
	int	Phase;
	int	ShadowLevel;
	int	ShadowNumber;
	XYPointContainerWithName	ControlPointsForPages;
	AlgoListArrayContainer	AlgoList;
	QString	GUIRoot;
	QString	GUIName;
	bool	ClearBeforeCopy;

	IntegrationCmdSetAlgoDataWithControlPoints(LayersBase *Base 
									,const QString &EmitterRoot,const QString &EmitterName 
									,int SlaveNo=-1);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);
};

#endif