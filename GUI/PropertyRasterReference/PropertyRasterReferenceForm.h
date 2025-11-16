#ifndef PROPERTYRASTERREFERENCEFORM_H
#define PROPERTYRASTERREFERENCEFORM_H

#include <QWidget>
#include <QModelIndex>
#include "XGUIFormBase.h"
#include <QDialog>
#include <QScrollArea>
#include <QCheckBox>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>

#include "XGUIPacketForDLL.h"
#include "mtPushButtonColored.h"
#include "mtToolButtonColored.h"
#include "XServiceForLayers.h"
#include "XRaster.h"
#include "XRasterPacket.h"
#include "XGUIRasterPacket.h"
#include "XColorConvert.h"

namespace Ui {
class PropertyRasterReferenceForm;
}

class PropertyRasterReferenceForm : public GUIFormBase
{
    Q_OBJECT

    ColorProfileContainer   ColorProfiler;
public:
    explicit PropertyRasterReferenceForm(LayersBase *Base,QWidget *parent = nullptr);
    ~PropertyRasterReferenceForm();

    RasterBase	    *GetRasterBase(void);
    virtual void	BuildForShow(void)	override;
	virtual void	StartPage	(void)	override;
    virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

private slots:
    void on_toolButtonModeShowPDF_clicked();
    void on_toolButtonModeShowReference_clicked();
    void on_pushButtonAutoPickUp_clicked();
    void on_pushButtonSaveColorProfile_clicked();

    void	SlotImageClicked(int Line);
    void	SlotRasterClicked(int Line);


    void on_pushButtonSaveDefaultColorProfile_clicked();

private:
    Ui::PropertyRasterReferenceForm *ui;

    DisplayImageWithAlgorithm	*GetImagePanel(void);
    void	RepaintImage(void);
    void	ShowGrid(void);
};

//----------------------------------------------------------------------
class	ColorProfileColorButton : public mtPushButtonColored
{
    Q_OBJECT

    int Line;
public:
    ColorProfileColorButton(int Line);
private slots:
	void	SlotClicked();
signals:
	void	SignalClicked(int Line);
};

#endif // PROPERTYRASTERREFERENCEFORM_H
