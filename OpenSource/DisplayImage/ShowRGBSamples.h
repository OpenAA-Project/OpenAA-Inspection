#ifndef SHOWRGBSAMPLES_H
#define SHOWRGBSAMPLES_H

#include <QWidget>
#include "XColorSpace.h"

namespace Ui {
class ShowRGBSamples;
}

class ShowRGBSamples;

class	ShowRGBSamplesPanel : public QWidget
{
    friend class	ShowRGBSamples;
    Q_OBJECT

    ShowRGBSamples	*ParentPanel;
public:
    explicit	ShowRGBSamplesPanel(ShowRGBSamples *parentPanel,QWidget * parent = 0, Qt::WindowFlags f = Qt::Widget );
    
    virtual	void paintEvent ( QPaintEvent * event )			override;
    virtual	void mouseMoveEvent ( QMouseEvent * event ) 	override;
    virtual	void mousePressEvent ( QMouseEvent * event )	override;
    virtual	void closeEvent ( QCloseEvent * event ) 		override;

signals:
    void	AddEliminated(void);
    void	DelEliminated(void);
};

class ShowRGBSamples : public QWidget
{
    friend class	ShowRGBSamplesPanel;
    Q_OBJECT

    ShowRGBSamplesPanel	CPanel;
    int	BaseSizeW;
    int	BaseSizeH;
    int	frameZoneW;
    int	frameZoneH;
    double	ZxPanel;
    double	ZyPanel;

public:
    explicit ShowRGBSamples(QWidget *parent = 0);
    ~ShowRGBSamples();

    RGBStock	Cube;
    int			Ext;

    int		GetExtended(void);
    int		GetCurrentBrightness(void);
    void	SetColorMsg(int r ,int g ,int b);
    void	InitializedDoneCube(void);
    void	Repaint(void);
    void	Fit(QWidget *f);

signals:
    void	AddEliminated(void);
    void	DelEliminated(void);

private slots:
    void on_VSliderBrightness_valueChanged(int value);
    void on_spinBoxExtend_valueChanged(int arg1);
    void	SlotAddEliminated(void);
    void	SlotDelEliminated(void);

private:
    Ui::ShowRGBSamples *ui;

    virtual	void closeEvent ( QCloseEvent * event ) override;
};

#endif // SHOWRGBSAMPLES_H
