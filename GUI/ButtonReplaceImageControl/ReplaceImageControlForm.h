#ifndef REPLACEIMAGECONTROLFORM_H
#define REPLACEIMAGECONTROLFORM_H

#include <QWidget>
#include "XServiceForLayers.h"
#include "XFlexArea.h"
#include "XIntClass.h"
#include "mtFrameDraw.h"

namespace Ui {
class ReplaceImageControlForm;
}

class DisplayImage;
class GUIFormBase;
class ButtonReplaceImageControl;

class ReplaceImageControlForm : public QWidget,public ServiceForLayers
{
    Q_OBJECT

    ButtonReplaceImageControl   *Parent;
    IntList                     CompPageList;
    mtFrameDraw::DrawingMode    LastDrawingMode;
    QColor	LastDrawingColor;
public:
    explicit ReplaceImageControlForm(LayersBase *base 
                                    ,ButtonReplaceImageControl *p
                                    ,QWidget *parent = nullptr);
    ~ReplaceImageControlForm();

    void    SetDrawEnd(FlexArea &Area);
    void    ExeMouseLDown(int X, int Y);
    void	DrawPanel(QPainter &pnt,int movx ,int movy,double ZoomRate,int CanvasWidth ,int CanvasHeight);
	bool	IsAvailableShowMask(void);
	bool	IsAvailableDrawAreaForMask(void);
    bool    IsAvailableMouseLDouble(void);

private slots:
    void on_toolButtonIsolateByColor_clicked();
    void on_radioButtonIsolateByColor_clicked();
    void on_radioButtonIsolateByMask_clicked();
    void on_radioButtonIsolateByOutline_clicked();
    void on_radioButtonIsolateByDrawing_clicked();
    void on_pushButtonLoadMaskImage_clicked();
    void on_checkBoxCompositeInside_clicked();
    void on_radioButtonCompositeNone_clicked();
    void on_radioButtonCompositeColor_clicked();
    void on_radioButtonTransparent_clicked();
    void on_radioButtonCompositeImage_clicked();
    void on_radioButtonCompositePage_clicked();
    void on_radioButtonViewMask_clicked();
    void on_pushButtonCompositeColor_clicked();
    void on_pushButtonLoadCompositeImage_clicked();
    void on_comboBoxCompositePage_currentIndexChanged(int index);

    void    SlotClose();

private:
    Ui::ReplaceImageControlForm *ui;

    DisplayImage *GetImagePanel(void);
    virtual	void    showEvent(QShowEvent *event)    override;
    virtual	void	closeEvent(QCloseEvent *event)	override;
    void    SetMaskMode(void);
    void    SetProcessMode(void);
};

#endif // REPLACEIMAGECONTROLFORM_H
