#ifndef SHOWSELECTLAYERFORM_H
#define SHOWSELECTLAYERFORM_H

#include "XGUIFormBase.h"
#include <QPushButton>
#include <QStringList>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XDisplayImageHook.h"
#include "XDisplayImage.h"
#include "XMultiLayerColor.h"

namespace Ui {
class ShowSelectLayerForm;
}

class ShowSelectLayerForm : public GUIFormBase,public FunctionServerClass
{
    Q_OBJECT

    DisplayImage    **DisplayImagePointDim;
    MultiLayerColor Color;
public:
    QStringList DisplayImageInst;

    explicit ShowSelectLayerForm(LayersBase *Base ,QWidget *parent = nullptr);
    ~ShowSelectLayerForm();

    virtual void	ReadyParam(void)    override;
    void    ShowXY(DisplayImage *DImage,int GlobalPosX,int GlobalPosY);
private:
    Ui::ShowSelectLayerForm *ui;

    virtual void paintEvent(QPaintEvent *event) override;
};

class GUICmdReqMultiLayerColor : public GUICmdPacketBase
{
public:
	DisplayImage::DisplayType	DType;
	int							LocalX,LocalY;

	GUICmdReqMultiLayerColor(LayersBase *Base, const QString &EmitterRoot, const QString &EmitterName, int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd, QString &EmitterRoot, QString &EmitterName);
};

class GUICmdAckMultiLayerColor : public GUICmdPacketBase
{
public:
	MultiLayerColor Color;

	GUICmdAckMultiLayerColor(LayersBase *Base, const QString &EmitterRoot, const QString &EmitterName, int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd, QString &EmitterRoot, QString &EmitterName){}
};

#endif // SHOWSELECTLAYERFORM_H
