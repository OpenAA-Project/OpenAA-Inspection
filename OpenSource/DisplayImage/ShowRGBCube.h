#ifndef SHOWRGBCUBE_H
#define SHOWRGBCUBE_H

#include <QWidget>
#include <QPaintEvent>
#include <QCloseEvent>
#include <QMouseEvent>
#include <QResizeEvent>
#include "XColorSpace.h"

namespace Ui {
class ShowRGBCube;
}

class	ShowRGBCube;
class	ShowRGBSpace;

class	ShowRGBColorPanel : public QWidget
{
    friend class	ShowRGBSpace;
    Q_OBJECT

    ShowRGBSpace	*ParentPanel;
public:
    explicit	ShowRGBColorPanel(ShowRGBSpace *parentPanel,QWidget * parent = 0, Qt::WindowFlags f = Qt::Widget );
    virtual	void paintEvent ( QPaintEvent * event )			override;
    virtual	void mouseMoveEvent ( QMouseEvent * event ) 	override;
    virtual	void mousePressEvent ( QMouseEvent * event )	override;
    virtual	void closeEvent ( QCloseEvent * event ) 		override;

signals:
    void	AddEliminated(void);
    void	DelEliminated(void);
};

class ShowRGBSpace : public QWidget
{
    friend class	ShowRGBColorPanel;
    Q_OBJECT

    ShowRGBColorPanel	CPanel;
    int	BaseSizeW;
    int	BaseSizeH;
    int	frameZoneW;
    int	frameZoneH;
    double	ZxPanel;
    double	ZyPanel;
public:
    explicit ShowRGBSpace(QWidget *parent = 0);
    ~ShowRGBSpace();

    ColorLogic	Cube;

    int		GetCurrentBrightness(void);
    void	SetColorMsg(int r ,int g ,int b);
    void	InitializedDoneCube(void);
    void	Repaint(void);
    void	Fit(QWidget *f);
    void	Set(RGBStock &data);

    virtual	void closeEvent ( QCloseEvent * event )	override;

signals:
    void	AddEliminated(void);
    void	DelEliminated(void);
private:
    Ui::ShowRGBCube *ui;

    virtual	void	resizeEvent ( QResizeEvent * event )	override;
private slots:
    void on_VSliderBrightness_valueChanged(int);
    void	SlotAddEliminated(void);
    void	SlotDelEliminated(void);
};

#endif // SHOWRGBCUBE_H
