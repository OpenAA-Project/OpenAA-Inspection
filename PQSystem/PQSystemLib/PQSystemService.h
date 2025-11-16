#pragma once

#include <QAbstractButton>
#include <QString>
#include <QIODevice>
#include <QScrollArea>
#include <QWidget>
#include <QPainter>
#include <QColor>
#include "XDataInLayer.h"
#include "XServiceForLayers.h"
#include "XPQSystemFunc.h"
#include "XIntegrationBase.h"
#include "XPQSystemParam.h"

#include "libxl.h"
using namespace libxl;

class	LayersBase;
class	QWidget;
class	PQRunnerControllerContainer;

class LayersBasePQSystem : public LayersBase
{
	ParamPQSystem	*ParamPQSystemInst;
	PQRunnerControllerContainer	*RefRunners;

public:
    LayersBasePQSystem(EntryPointBase *pEntryPoint);
	LayersBasePQSystem(const QString &TypeName ,LayersBase *ParentLayer);
	LayersBasePQSystem(const LayersBase *Parent);

	void	SetPQRunnerControllerContainer(PQRunnerControllerContainer *p)		{	RefRunners=p;	}
	PQRunnerControllerContainer	*GetPQRunnerControllerContainer(void)	const	{	return RefRunners;	}

	ParamPQSystem	*GetParamPQSystem(void){	return ParamPQSystemInst;	}
private:

};


class PQSystemRunner : public QWidget,public ServiceForLayers,public ParamBase
{
	QString	SRoot;
	QString	SName;

protected:
	Book	*XLSXBook;
	Sheet	*XLSXSheet[100];
	int		SheetCount;
	Format	*Lang;
	Font	*Fnt;
	QString	ReferredExcelFileName;
public:
	PQSystemRunner(LayersBase *base ,const QString &root ,const QString &name
					,QWidget *parent);
	~PQSystemRunner();

	virtual	bool	Initial(void)	=0;

	virtual	const QString	GetPath(void)	=0;
	bool	SetLanguage(int LanguageCode);

	bool	GetMasterRelation(int RelationCode
							,QString &RetRelationNumber
							,QString &RetRelationName
							,QString &RetRemark
							,int &RetRelationType
							,QByteArray &CommonData
							,int32 &ThresholdLevelID);
	bool	LoadMasterImage(int RelationCode);
	QImage	LoadDataFromMaster(int masterCode);

	void	GetAllAlgorithmPointers(AlgorithmBasePointerContainer &Container);
	
	bool	LoadNGImageFile(const QString &FileName,NPListPack<IntegNGImage> NGImages[] ,int PhaseCount);
	bool	LoadNGImageFile(QIODevice *f ,NPListPack<IntegNGImage> NGImages[],int PhaseCount
							,int ShadowLevel,int ShadowNumber);

	bool	DrawMasterImage(EachMaster *M ,QImage &Image,int Phase 
							,int MovX,int MovY ,double ZoomRate);

	void	InitialExcel(void);
	void	ReleaseExcel(void);
	void	SetCellHeight(int height ,int SheetNo=0);
	void	WriteCell(int Row, int Col ,const QString &Str ,int SheetNo=0);
	void	WriteCellV(int Row, int Col ,const QVariant &Data ,int SheetNo=0);
	void	WriteCell(int Row, int Col ,int N	,int SheetNo=0);
	void	WriteCell(int Row, int Col ,int64 N	,int SheetNo=0);
	void	WriteCell(int Row, int Col ,double N,int SheetNo=0);
	void	WriteCell(int Row, int Col ,const QString &Str ,const QColor &Color ,int SheetNo=0);

	bool	SaveExcel(const QString &ExcelFileName);

	void	AddSheet(const QString &SheetName);

	void	SetRowHeight(int row,int height,int SheetNo);

};

//===========================================================================

class InspectionListByMaster : public NPListPack<InspectionList> ,public NPList<InspectionListByMaster>
{
public:
	LotList	LotListData;
	int		MachineID;
	InspectionListByMaster(void);
	~InspectionListByMaster();

	InspectionListByMaster	&operator=(const InspectionListByMaster &src);

	void	Move(InspectionListContainer &src);
};

class	LotListWithResult : public NPList<LotListWithResult>
{
public:
	bool	Effective;
	NPListPack<InspectionListByMaster>	CurrentInspection;

	LotListWithResult(void){}

	bool	LoadResult(IntegrationBase *Base);

	LotListWithResult	&operator=(const LotListWithResult &src);
};

class LotListContainerWithRelationCode : public NPList<LotListContainerWithRelationCode>
{
public:
	bool	Effective;
	NPListPack<LotListWithResult>	Container;
	int	RelationCode;

	LotListContainerWithRelationCode(){}
	~LotListContainerWithRelationCode(){}

};

//===========================================================================
class ScrollPanel;

class ImagePanel : public QWidget , public NPList<ImagePanel>
{
	ScrollPanel	*Parent;
protected:
	QImage	Image;
public:

	ImagePanel(ScrollPanel *p);
	~ImagePanel();

	void	Add(const QImage &s);
protected:
	virtual	void	paintEvent(QPaintEvent *event)	override;
	virtual	void	paint(QPainter &Pnt);
};

class ScrollPanel : public QScrollArea
{
public:
	QWidget	*W;
	NPListPack<ImagePanel>	Panels;

	ScrollPanel(QWidget *parent = nullptr);
	~ScrollPanel();

	virtual	ImagePanel	*CreatePanel(void);
	void		Clear(void);
	ImagePanel	*Add(const QImage &s);
	void		Assign(void);
};

