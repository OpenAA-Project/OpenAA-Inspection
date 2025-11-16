#ifndef INTEGRATIONSTACKNGTHUMBNAILFORM_H
#define INTEGRATIONSTACKNGTHUMBNAILFORM_H

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
class IntegrationStackNGThumbnailForm;
}

class IntegrationStackNGThumbnailForm;
class LargeWindowForm;
class LargeMeasureWindowForm;
class LargeColorDifferenceForm;

class	ThumbnailPanel : public QWidget ,public NPList<ThumbnailPanel>
{
    Q_OBJECT

	friend	class IntegrationStackNGThumbnailForm;
	friend	class LargeWindowForm;
	friend	class LargeMeasureWindowForm;
	friend	class LargeColorDifferenceForm;
	friend	class LargeFlatInspectionForm;

	IntegrationStackNGThumbnailForm	*Parent;
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
	int			MessageRowCount;
public:
	int	Row,Column;
	int	Index;

	ThumbnailPanel(InspectionList *L,IntegrationStackNGThumbnailForm *p ,EachMaster *m,int phase,NGPointInPage *page,IntegNGImage *ImagePoint);
	~ThumbnailPanel(void);

	void	MakeImage(void);
	LayersBase	*GetLayersBase(void);
	EachMaster	*GetMaster(void)	{	return Master;	}
	virtual	int	Compare(ThumbnailPanel &src)	override;

	void	SendLearning(int LearningMenuID, bool AllItems);
private:
	virtual	void paintEvent ( QPaintEvent * event )				override;
	virtual	void mousePressEvent ( QMouseEvent * event )		override;
	virtual	void mouseDoubleClickEvent ( QMouseEvent * event )	override;

private slots:
	void	SlotShowDetail();
};

class IntegrationStackNGThumbnailForm : public GUIFormBase,public IntegratorRelation
{
    Q_OBJECT
	friend	class	ThumbnailPanel;

	NPListPack<ThumbnailPanel>	Panels;
	QTimer	FlipTimer;
	int	CurrentIndex;
	bool	EnableUpdate;
public:
	int32	SlaveNo;	//-1:All sides
	int32	MachineID;	//-1: Depend on SlaveNo
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
	LargeFlatInspectionForm		*LargeFlatInspectionWindow;
	DWORD	LastPressedTime;
	bool	ShowRemarkData;

    explicit IntegrationStackNGThumbnailForm(LayersBase *Base ,QWidget *parent = 0);
    ~IntegrationStackNGThumbnailForm();

	virtual void	StartLot(void)	override;
	virtual void	Prepare(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	int	GetCurrentIndex(void)	{	return CurrentIndex;	}
	void	DetailFromThumbnail(ThumbnailPanel *p);
	void	GetInformation(InspectionList *L,NGPoint *Rp
							,QString &StrLibID ,QString &StrLibName ,QString &StrResult);
	void	PressPanel(int index);
signals:
	void	SignalReqDetail(EachMaster *m ,InspectionList *Result, InspectionList *CurrentInspection, NGPoint *RepresentativePoint
							,int Phase ,int Page ,IntList &ItemID);

private slots:
	void	ResizeAction(); 
	void	SlotFlipTimer();
	void	SlotScrollerChanged(int value);
private:
    Ui::IntegrationStackNGThumbnailForm *ui;

	virtual	void	SpecifiedDirectly(SpecifiedBroadcaster *v) override;
	bool	ExistsInPanel(InspectionList *L);
	void	AddNGImagesAll(void);
	bool	AddNGImagesAll(int SlaveNo);

	QWidget	*GetParentWidget(void);
	ThumbnailPanel	*GetPanel(int index);

	QStringList	GetInformation(InspectionList *L,NGPoint *p);

	void	RepaintPanel(void);
	void	BroadcastNGPoint(void);
	void	ArrangePanelPosition(void);
	void	SetInvisibleAll(void);

	bool	LoadNGImageFile(const QString &FileName,NPListPack<IntegNGImage> NGImages[] ,int PhaseCount);
	bool	LoadNGImageFile(QIODevice *f,NPListPack<IntegNGImage> NGImages[] ,int PhaseCount
							,int ShadowLevel,int ShadowNumber);
	bool	IsShownPanelCompletely(int Index);
	void	SetToShowPanel(int Index);
	void	SendLearning(IntegNGImage	*ImagePoint ,NGPoint *RepresentativePoint
						,int Phase ,int Page
						,int LearningMenuID, bool AllItems);
};


#endif // INTEGRATIONSTACKNGTHUMBNAILFORM_H
