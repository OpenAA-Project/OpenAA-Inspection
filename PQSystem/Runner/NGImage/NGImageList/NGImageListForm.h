#ifndef NGIMAGELISTFORM_H
#define NGIMAGELISTFORM_H

#include <QWidget>
#include <QImage>
#include <QModelIndex>
#include <QDateTime>
#include "PQSystemService.h"
#include "XDataInLayer.h"
#include "SelectLotForm.h"
#include "XAlgorithmLibrary.h"
#include "XPQSystemFunc.h"
#include "libxl.h"
using namespace libxl;

namespace Ui {
class NGImageListForm;
}
class IntegNGImage;
class InspectionList;
class NGPoint;

class NGListByMaster: public NPList<NGListByMaster>
{
public:
	PointerListContainer<IntegNGImage>	NGImages;
	int							MachineID;

	NGListByMaster(void){}
};

class NGListWithImages : public NPList<NGListWithImages>
{
public:
	NPListPack<NGListByMaster>	NGImageBYMaster;
	XDateTime					InspectionTime;
	int64						InspectionID;
	LotListWithResult			*LotPointer;
	int							RelationCode;

	NGListWithImages()	{	LotPointer=NULL;	}
	~NGListWithImages(){}
};

class LibTypeIDList : public NPList<LibTypeIDList>
{
public:
	int32	LibType;
	int32	LibID;
	int32	Index;
	int32	UniqueID;

	int		NGCount;
	DoubleList	ResultValueList;

	LibTypeIDList(void)	{	NGCount=0;	}
};

class NGLibTypeIDList : public NPList<NGLibTypeIDList>
{
public:
	int32	LibType;
	int32	LibID;
	int32	NGType;
	_ResultType	ResultType;

	NGLibTypeIDList(void)	{	NGType=0;	}
};

class NGInfoList : public NPList<NGInfoList>
{
public:
	NGLibTypeIDList	*GType;
	EachMaster		*Master;
	int64	InspectionID;
	int32	Cause[2];
	double	DoubleCause;

	NGInfoList(void){}
};

class NGInfoListInLot : public NPList<NGInfoListInLot>
{
public:
	int32	LotAutoCount;
	NPListPack<NGInfoList>		NGInfoListData[100];

	NGInfoListInLot(void){}
};

class Sheet1ByImage;


class NGImageListForm : public PQSystemRunner
{
    Q_OBJECT
    AlgorithmBasePointerContainer 	AlgorithmContainer;
	AlgorithmBase					*CurrentAlgorithm;
	AlgorithmLibraryListContainer	LibIDList;
	AlgorithmLibraryList			*CurrentLibrary;
	AlgorithmLibraryListContainer	CheckedLibIDList;
	SelectLotForm					LotForm;
	NPListPack<LotListContainerWithRelationCode>	AllLotList;

	IntList		RemationMasterCodeList;
public:
	NPListPack<NGListWithImages>	ResultList;
	int	ResultRelationCode;
	ScrollPanel		TestPanel	;
	QDateTime		StartTime	;
	QDateTime		EndTime		;

    explicit NGImageListForm(LayersBase *base ,const QString &root ,const QString &name
							,QWidget *parent = 0);
    ~NGImageListForm();
    
	virtual	bool	Initial(void)   override;
	virtual	const QString	GetPath(void)		override;
	virtual	QString	GetDataText(void)			override    {   return /**/"PQSystemNGImageList";      }
	virtual	QString	GetDefaultFileName(void)	override    {   return /**/"PQSystemNGImageList.dat";  }

protected:
	virtual	void showEvent(QShowEvent *event)	override;

private slots:
    void on_pushButtonSelectMaster_clicked();
    void on_pushButtonStartSearch_clicked();
    void on_pushButtonView_clicked();
    void on_pushButtonExcel_clicked();
    void on_listWidgetAlgorithm_clicked(const QModelIndex &index);
    void on_tableWidgetLibrary_clicked(const QModelIndex &index);
    void on_listWidgetThreshold_clicked(const QModelIndex &index);
    void on_listWidgetSpecial_clicked(const QModelIndex &index);

private:
    Ui::NGImageListForm *ui;

	bool	CheckByLib(NGPoint *NG);
	bool	WriteExcel(const QString &ExcelFileName);
	void	SetNGImage (EachMaster *m ,int64 InspectionID ,IntegNGImage *r,int Row,int Col,int SheetNo);
	void	SetNGImage2(EachMaster *m ,int64 InspectionID ,IntegNGImage *r,int Row,int Col,int SheetNo);
	Sheet1ByImage	*SetNGImage3(EachMaster *m ,int64 InspectionID ,IntegNGImage *g);

	QStringList	GetInformation(InspectionList *L,NGPoint *Rp);

	bool	MakeExcelSheet1(void);
	bool	MakeExcelSheet2(void);
	bool	MakeExcelSheet3(void);
	bool	MakeExcelSheet4(void);
	bool	MakeExcelSheet5(void);

	bool	LibraryExist(int LibType,int LibID);
};

#endif // NGIMAGELISTFORM_H
