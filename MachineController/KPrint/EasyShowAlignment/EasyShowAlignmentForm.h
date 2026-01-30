/*
 * Copyright (C) 2025
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef EASYSHOWALIGNMENTFORM_H
#define EASYSHOWALIGNMENTFORM_H

#include <QWidget>
#include "XServiceForLayers.h"
#include "NList.h"
#include "XTypeDef.h"
#include "PropertyAlignmentLargePacket.h"
#include "XIntegrationBase.h"
#include "XIntegrationPacketComm.h"

namespace Ui {
class EasyShowAlignmentForm;
}
class EasyShowAlignment;
class EasyShowAlignmentForm;

class AlignmentMarkPanel : public QWidget ,public NPList<AlignmentMarkPanel>
{
    friend  class EasyShowAlignmentForm;

    EasyShowAlignmentForm   *Parent;
    AlignmentLargePointList Data;
    int     movx,movy;
    double  ZoomRate;
    QImage  AlignmentImage;
    int     LastX,LastY;
public:
    bool    Selected;
	AlignmentMarkPanel(AlignmentLargePointList *L,EasyShowAlignmentForm *p);

    void    MakeData(void);

private:
    virtual void    paintEvent(QPaintEvent *event)          override;
    virtual void    mousePressEvent(QMouseEvent *event)     override;
    virtual void    mouseReleaseEvent(QMouseEvent *event)   override;
    virtual void    mouseMoveEvent(QMouseEvent *event)      override;
    virtual void    wheelEvent(QWheelEvent *event)          override;
};

class EasyShowAlignmentForm : public QWidget,public ServiceForLayers
{
    Q_OBJECT

    friend  class AlignmentMarkPanel;

    EasyShowAlignment   *Parent;
    NPListPack<AlignmentMarkPanel>  Panels;
    //QWidget BasePanel;
    QImage  AlignmentImage;
    double  ZoomRate;
public:
    explicit EasyShowAlignmentForm(LayersBase *Base,EasyShowAlignment *p,QWidget *parent = nullptr);
    ~EasyShowAlignmentForm();

    void    ShowStart(void);
    void    SetSelect(AlignmentMarkPanel *s);
    void	ShowInPlayer		(int64 shownInspectionID=-1);
private:
    Ui::EasyShowAlignmentForm *ui;

    virtual void    paintEvent(QPaintEvent *event)     override;
    virtual void    resizeEvent(QResizeEvent *event)   override;

private slots:
    void    SlotScrollerChanged(int);
};


class	IntegrationCmdReqAlignmentImage : public IntegrationCmdPacketBase
{
public:
    struct
    {
	    int32	Phase;
	    int32   movx,movy;
        double  ZoomRate;
        int32   ImageWidth,ImageHeight;
        int32   Layer;
        int32   ItemID;
    }Data;

	IntegrationCmdReqAlignmentImage(LayersBase *Base 
									,const QString &EmitterRoot,const QString &EmitterName 
									,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	IntegrationCmdAckAlignmentImage : public IntegrationCmdPacketBase
{
public:
    int32   ImageWidth,ImageHeight;
	QImage  *Image;

	IntegrationCmdAckAlignmentImage(LayersBase *Base 
									,const QString &EmitterRoot,const QString &EmitterName 
									,int SlaveNo=-1);
    ~IntegrationCmdAckAlignmentImage(void);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

    virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName){}
};


#endif // EASYSHOWALIGNMENTFORM_H