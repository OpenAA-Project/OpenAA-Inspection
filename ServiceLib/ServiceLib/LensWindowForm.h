#ifndef LENSWINDOWFORM_H
#define LENSWINDOWFORM_H

#include <QWidget>
#include <QImage>
#include <QTimer>
#include "XServiceForLayers.h"
#include "XDisplayImage.h"

namespace Ui {
class LensWindowForm;
}
class	LayersBase;

class LensWindowForm : public QWidget,public ServiceForLayers
{
    Q_OBJECT

	GUICmdSendBmp	**BmpReceiver;
	GUICmdReqBmp	**BmpRequester;
	int				AllocedBmp;
	DisplayImage::DisplayType	DType;
	int				CurrentGlobalX,CurrentGlobalY;
	double			ZoomRate;
	DisplayImage	*TargetPanel;
	QTimer			TM;
public:
    explicit LensWindowForm(LayersBase *base,QWidget *parent = 0);
    ~LensWindowForm();

	void	AllocInnerBuff(void);
	void	ShowLens(DisplayImage *_TargetPanel ,int GlobalX ,int GlobalY , DisplayImage::DisplayType dtype);
private:
    Ui::LensWindowForm *ui;

	virtual	void paintEvent ( QPaintEvent * event ) override;
	void	ChangeDxy2Gxy(int Dx,int Dy ,int &Gx ,int &Gy);
	void	ChangeGxy2Dxy(int Gx,int Gy ,int &Dx ,int &Dy);
	
	virtual	void hideEvent ( QHideEvent * event )	override;
	virtual	void closeEvent ( QCloseEvent * event )	override;
	virtual	void resizeEvent ( QResizeEvent * event ) override;
signals:
	void	SignalClose();
private slots:
	void	SlotTimeout();
	void	SlotCloseEvent();
};

#endif // LENSWINDOWFORM_H
