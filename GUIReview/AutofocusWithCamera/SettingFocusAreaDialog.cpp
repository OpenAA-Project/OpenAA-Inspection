#include "AutofocusWithCameraResource.h"
#include "SettingFocusAreaDialog.h"
#include "ui_SettingFocusAreaDialog.h"
#include "swap.h"
#include "AutofocusWithCameraForm.h"

SettingFocusAreaDialog::SettingFocusAreaDialog(AutofocusWithCameraForm *p,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingFocusAreaDialog)
{
    ui->setupUi(this);
	Parent=p;

	ImagePanel.setParent(ui->frame);
	ImagePanel.move(0,0);
	ImagePanel.resize(ui->frame->width(),ui->frame->height());
	bool	Ret=(connect(&ImagePanel,SIGNAL(SignalOnPaint(QPainter &)),this,SLOT(SlotOnPaint(QPainter &))))?true:false;
			Ret=(connect(&ImagePanel,SIGNAL(SignalDrawEnd(void)),this,SLOT(SlotDrawEnd(void))))?true:false;
	ImagePanel.SetMode(mtFrameDraw::fdRectangle);
	ImagePanel.SetFrameColor(Qt::red);

	p->GetLayersBase()->InstallOperationLog(this);
}

SettingFocusAreaDialog::~SettingFocusAreaDialog()
{
    delete ui;
}

void	SettingFocusAreaDialog::Initial(QImage &Image ,int x1, int y1 ,int x2, int y2)
{
	SampleImage	=Image;
	FocusAreaX1=x1;
	FocusAreaY1=y1;
	FocusAreaX2=x2;
	FocusAreaY2=y2;

	double	Zx=((double)ui->frame->width ())/(double)Image.width();
	double	Zy=((double)ui->frame->height())/(double)Image.height();
	double	Z=min(Zx,Zy);
	ImagePanel.SetZoomRate(Z);
	ImagePanel.SetMovXY(0,0);
	ImagePanel.SetAreaSize(Image.width(),Image.height());
	ImagePanel.show();
}

void SettingFocusAreaDialog::on_pushButtonOK_clicked()
{
	done(true);
}

void SettingFocusAreaDialog::on_pushButtonCancel_clicked()
{
	done(false);
}

void	SettingFocusAreaDialog::SlotOnPaint(QPainter &pnt)
{
	pnt.drawImage(0,0,SampleImage.scaled(ImagePanel.width(),ImagePanel.height(),Qt::KeepAspectRatio));
}

void	SettingFocusAreaDialog::SlotDrawEnd(void)
{
	double	Zx=(double)SampleImage.width()/(double)ImagePanel.width();
	double	Zy=(double)SampleImage.height()/(double)ImagePanel.height();
	double	Z=max(Zx,Zy);
	FocusAreaX1	=ImagePanel.GetCanvas()->SData.UData.RectangleData.x1;
	FocusAreaY1	=ImagePanel.GetCanvas()->SData.UData.RectangleData.y1;
	FocusAreaX2	=ImagePanel.GetCanvas()->SData.UData.RectangleData.x2;
	FocusAreaY2	=ImagePanel.GetCanvas()->SData.UData.RectangleData.y2;
}
void SettingFocusAreaDialog::on_pushButtonSetDarkLightSetting_clicked()
{
	Parent->SaveDarkLightData();
}
