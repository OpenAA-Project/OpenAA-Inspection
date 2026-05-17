#ifndef DISPLAYTHUMBNAILIMAGE_H
#define DISPLAYTHUMBNAILIMAGE_H

#include "displaythumbnailimage_global.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XGUIFormBase.h"
#include "XDisplayImage.h"
#include "XGeneralFunc.h"
#include <QTimer>
#include <QImage>
#include <QGridLayout>
#include <QKeyEvent>
#include <QWheelEvent>

class	ThumbnailForm;
class	ErrorGroup;

class DisplayThumbnailImage : public GUIFormBase,public DisplayImageHooked
{
	Q_OBJECT

	ThumbnailForm	***ThumForm;
	QTimer			TM;
	QImage			*MasterImage;
	QImage			*TargetImage;

public:
	DisplayThumbnailImage(LayersBase *Base ,QWidget *parent);
	~DisplayThumbnailImage(void);
	
	virtual void	Prepare(void)	override;
	virtual void	ShowInPlayer(int64 shownInspectionID)	override;

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	bool	Mastered;
	int32	ColumnCount,wColumnCount;
	int32	RowCount,wRowCount;
	double	ZoomInRate;
	bool	EnableThumbnail;
	bool	EnableThumbnailMaster;
	bool	NGTopToBottom;
	bool	ShowNG;
	bool	BlinkNG;
	bool	BlinkOn;
	int32	ShowFixedPhase;

	ThumbnailForm	*GetThumForm(int Row,int Column)	{	return ThumForm[Row][Column];	}

protected:
	virtual	void	keyPressEvent(QKeyEvent *event)	override;
	virtual	void	wheelEvent(QWheelEvent *event)	override;

private slots:

private:
	LayersBase	*LBase;
    QGridLayout	*gridLayout;

	int ErrorGroupTableCount;
	ErrorGroup	**ErrorGroupTable;

///	void	SetThumFormData(int FirstIndex,double ZoomR=0);
	void	SetThumFormData(int FirstIndex=0,int CurrentRow=0);
	double	GetZoomRate(void);
};

#include "ThumbnailForm.h"

#endif // DISPLAYTHUMBNAILIMAGE_H
