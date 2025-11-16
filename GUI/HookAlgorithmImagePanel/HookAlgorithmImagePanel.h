#ifndef HOOKALGORITHMIMAGEPANEL_H
#define HOOKALGORITHMIMAGEPANEL_H

#include "hookalgorithmimagepanel_global.h"
#include "XServiceForLayers.h"
#include <QTcpSocket>
#include <QThread>
#include "XDataInLayer.h"
#include "XGUIFormBase.h"
#include "XDisplayImageHook.h"
#include "XDisplayImage.h"

class	HookAlgorithmImagePanel : public GUIFormBase,public FunctionServerClass
{
	Q_OBJECT
	
	DisplayImage	*SrcImg;
	DisplayImage	*TargetImg;
	QImage			*IData;
	double			LastZoomRate;
	int				LastMovX;
	int				LastMovY;
	int				LastWidth;
	int				LastHeight;
public:
	QString		SrcAlgoImagePanelRoot;
	QString		SrcAlgoImagePanelName;
	QString		SrcAlgoImagePanelInst;

	QString		TargetImagePanelRoot;
	QString		TargetImagePanelName;
	QString		TargetImagePanelInst;


	HookAlgorithmImagePanel(LayersBase *Base ,QWidget *parent);
	~HookAlgorithmImagePanel(void);

	virtual	void	ReadyParam(void)	override;
	void	Draw(QPainter &pnt ,double ZoomRate ,int movx ,int movy);

signals:
	void	SignalOnPaint(QPainter &);
private slots:

};


#endif // HOOKALGORITHMIMAGEPANEL_H
