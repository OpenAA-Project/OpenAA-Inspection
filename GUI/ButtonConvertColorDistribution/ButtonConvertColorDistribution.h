#pragma once

#include "buttonconvertcolordistribution_global.h"
#include <QPushButton>
#include <QBuffer>
#include "XGUIFormBase.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include <QString>
#include <QColor>
#include <QFont>
#include <QImage>
#include "XDoubleClass.h"

class	ButtonConvertColorDistribution : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;

public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	bool	ChangeMasterImage;

	ButtonConvertColorDistribution(LayersBase *Base ,QWidget *parent);
	~ButtonConvertColorDistribution(void);
	virtual void	Prepare(void)	override;

public slots:
	void SlotClicked (bool checked);

private slots:
	void	ResizeAction();
};

//============================================================================================

class	GUICmdConvertColorDistribution : public GUICmdPacketBase
{
public:
	bool	ChangeMasterImage;

	GUICmdConvertColorDistribution(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
private:
	void	MakeAvrV(const ImagePointerContainer &Images ,const BYTE **MaskBitmap,DoubleList &Avr,DoubleList &V
					,int X1,int Y1,int X2,int Y2,bool SmoothMode);
	void	Convert(const ImagePointerContainer &Images ,const BYTE	**MaskBitmap,DoubleList &SrcAvr,DoubleList &DstAvr,DoubleList &DifV
					,int X1,int Y1,int X2,int Y2);

};
