#ifndef INTEGRATIONSTACKMULTINGTHUMBNAILFORM_H
#define INTEGRATIONSTACKMULTINGTHUMBNAILFORM_H

#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QPushButton>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XIntegrationBase.h"
#include "XDataInLayer.h"
#include "IntegrationLib.h"
#include "XIntegrationPacketComm.h"
#include "XLearningRegist.h"

namespace Ui {
class IntegrationStackMultiNGThumbnailForm;
}

class IntegrationStackMultiNGThumbnailForm;
class LargeWindowForm;
class LargeMeasureWindowForm;
class LargeColorDifferenceForm;

class	ThumbnailPanel : public QWidget ,public NPList<ThumbnailPanel>
{
    Q_OBJECT

	friend	class IntegrationStackMultiNGThumbnailForm;
	friend	class LargeWindowForm;
	friend	class LargeMeasureWindowForm;
	friend	class LargeColorDifferenceForm;

protected:
	IntegrationStackMultiNGThumbnailForm	*Parent;
	EachMaster	*Master;
	QImage	NGImage;
	QImage	*NGMarkImage;
	QImage	*MasterImage;
	int		Phase;
	InspectionList	*Result;
	NGPointInPage	*RPage;
	IntegNGImage	*ImagePoint;
	NGPoint			*RepresentativePoint;	
	InspectionList	*CurrentInspection;
	bool	ShowingNGOnFlip;
	QStringList		Messages;
	bool		Visible;

public:
	int	Row,Column;
	//int	Index;

	ThumbnailPanel(InspectionList *L,IntegrationStackMultiNGThumbnailForm *p ,EachMaster *m,int phase,NGPointInPage *page,IntegNGImage *ImagePoint);
	~ThumbnailPanel(void);

	virtual	void	MakeImage(void);
	LayersBase	*GetLayersBase(void);
	EachMaster	*GetMaster(void)	{	return Master;	}
	virtual	int	Compare(ThumbnailPanel &src)	override;

	virtual	void	SendLearning(int LearningMenuID, bool AllItems);
private:
	virtual	void paintEvent ( QPaintEvent * event )				override;
	virtual	void mousePressEvent ( QMouseEvent * event )		override;
	virtual	void mouseDoubleClickEvent ( QMouseEvent * event )	override;

private slots:
	void	SlotShowDetail();
};

class	ThumbnailColumHeaderPanel : public ThumbnailPanel
{
    Q_OBJECT

	friend	class IntegrationStackMultiNGThumbnailForm;
	friend	class LargeWindowForm;
	friend	class LargeMeasureWindowForm;
	friend	class LargeColorDifferenceForm;

public:

	ThumbnailColumHeaderPanel(InspectionList *L,IntegrationStackMultiNGThumbnailForm *p ,EachMaster *m,int phase,NGPointInPage *page,IntegNGImage *ImagePoint);
	~ThumbnailColumHeaderPanel(void);

	virtual	void	MakeImage(void)	override;
	virtual	int	Compare(ThumbnailPanel &src)	override;

	virtual	void	SendLearning(int LearningMenuID, bool AllItems)	override;
private:
	virtual	void paintEvent ( QPaintEvent * event )				override;
	virtual	void mousePressEvent ( QMouseEvent * event )		override;
	virtual	void mouseDoubleClickEvent ( QMouseEvent * event )	override;
};


class NGLineList : public QWidget ,public NPList<NGLineList>
{
public:
	IntegrationStackMultiNGThumbnailForm	*Parent;
	NPListPack<ThumbnailPanel>	Panels;
	int64						InspectionID;

	NGLineList(IntegrationStackMultiNGThumbnailForm *p);
	~NGLineList(void);

	virtual	int	Compare(NGLineList &src);
};


class IntegrationStackMultiNGThumbnailForm : public GUIFormBase,public IntegratorRelation
{
    Q_OBJECT
	friend	class	ThumbnailPanel;

	NPListPack<NGLineList>	NGLineListPack;

	QTimer	FlipTimer;
	int		CurrentIndex;
	int		CurrentPanelNo;
	bool	EnableUpdate;
public:
	int32	ThumbnailWidth;
	int32	ThumbnailHeight;
	int32	ThumbnailMergin;
	double	ZoomRate;
	bool	ShowInformation;
	bool	ShowInformationTime;
	bool	ShowInformationNumber;
	int		MaxXCount;
	int		MaxYCount;
	int32	ScrollerWidth;
	LargeWindowForm				*LargeWindow;
	LargeMeasureWindowForm		*LargeMeasureWindow;
	LargeColorDifferenceForm	*LargeColorDifferenceWindow;
	DWORD	LastPressedTime;
public:
    explicit IntegrationStackMultiNGThumbnailForm(LayersBase *Base ,QWidget *parent = nullptr);
    ~IntegrationStackMultiNGThumbnailForm();

	virtual	void	Prepare(void)	override;

	virtual void	StartLot(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	int	GetCurrentIndex(void)	{	return CurrentIndex;	}
	void	DetailFromThumbnail(ThumbnailPanel *p);
	void	GetInformation(int SlaveNo
							,InspectionList *L,NGPoint *Rp
							,QString &StrLibID ,QString &StrLibName ,QString &StrResult);
	void	PressPanel(void);
signals:
	void	SignalReqDetail(EachMaster *m ,InspectionList *Result, InspectionList *CurrentInspection, NGPoint *RepresentativePoint
							,int Phase ,int Page ,IntList &ItemID);

private slots:
	void	ResizeAction(); 
	void	SlotScrollerChanged(int value);
	void	SlotFlipTimer();
private:
    Ui::IntegrationStackMultiNGThumbnailForm *ui;

	virtual	void	SpecifiedDirectly(SpecifiedBroadcaster *v) override;
	bool	ExistsInPanel(InspectionList *L);
	void	AddNGImagesAll(void);
	bool	AddNGImagesAll(int SlaveNo);

	QWidget	*GetParentWidget(void);
	ThumbnailPanel	*GetPanel(int index,int PanelNo);

	QStringList	GetInformation(int SlaveNo
							,InspectionList *L,NGPoint *p);

	void	RepaintPanel(void);
	void	BroadcastNGPoint(void);
	void	ArrangePanelPosition(void);
	void	SetInvisibleAll(void);

	bool	LoadNGImageFile(const QString &FileName,NPListPack<IntegNGImage> NGImages[] ,int PhaseCount);
	bool	LoadNGImageFile(QIODevice *f,NPListPack<IntegNGImage> NGImages[] ,int PhaseCount
							,int ShadowLevel,int ShadowNumber);
	void	SetToShowPanel(int Index ,int PanelNo);
	void	SendLearning(IntegNGImage	*ImagePoint ,NGPoint *RepresentativePoint
						,int Phase ,int Page
						,int LearningMenuID, bool AllItems);
};

#endif // INTEGRATIONSTACKMULTINGTHUMBNAILFORM_H
