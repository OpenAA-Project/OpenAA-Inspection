#ifndef REALTIMEIMAGEPANEL_H
#define REALTIMEIMAGEPANEL_H

#include "realtimeimagepanel_global.h"
#include "XDisplayImage.h"
#include <QTimer>


class ImageBufferDimClass
{
public:
	ImageBuffer	*IBuff[3];

	ImageBufferDimClass(void);
	~ImageBufferDimClass(void);

	void	Alloc(int XLen ,int YLen);
};


class	RealtimeImagePanel : public DisplayImage
{
	Q_OBJECT

	ImageBufferDimClass	*IBuff;
	CameraClass			**Cam;
	int					CountCamera;
	QTimer				Timer;
	QImage				Image;
public:
	QString		ImageType;
	int32		IntervalMilisec;

	RealtimeImagePanel(LayersBase *Base ,QWidget *parent);
	~RealtimeImagePanel(void);

	virtual	void	Prepare(void) override;
	virtual void	ReadyParam(void)							override;
	virtual	void	ShowInPlayer(int64 shownInspectionID=-1)	override;
	virtual void	ShowInScanning(int64 shownInspectionID=-1)	override;

	virtual	bool	ReallocXYPixels(int NewDotPerLine ,int NewMaxLines);

private slots:
	void	ResizeAction();
	void	SlotTimeout();
	virtual	void	CanvasSlotOnPaint(QPainter &pnt);
};
#endif // REALTIMEIMAGEPANEL_H
