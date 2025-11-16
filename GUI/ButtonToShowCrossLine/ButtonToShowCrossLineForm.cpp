#include "ButtonToShowCrossLineForm.h"
#include "ui_ButtonToShowCrossLineForm.h"
#include "XDisplayImage.h"
#include <QColorDialog>

CrossLineButton::CrossLineButton ( QWidget * parent)
	:QToolButton(parent)
{
}

void	CrossLineButton::mouseReleaseEvent ( QMouseEvent * e )
{
	if(e->button()==Qt::RightButton){
		emit	SignalRightButton();
	}
	QToolButton::mouseReleaseEvent(e);
}


ButtonToShowCrossLineForm::ButtonToShowCrossLineForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent)
	,Button(this)
    ,ui(new Ui::ButtonToShowCrossLineForm)
{
    ui->setupUi(this);
	LineColor	=Qt::yellow;
	CrossLine	=true;
	MatrixLine	=true;

	GetParamGUI()->SetParam(&LineColor	, /**/"ButtonToShowCrossLine",/**/"LineColor"	,/**/"Color for CrossLine"	);

	Button.setText(ui->toolButtonCrossLine->text());
	Button.setGeometry(ui->toolButtonCrossLine->geometry());
	Button.setCheckable(true);
	Button.setChecked(ui->toolButtonCrossLine->isChecked());

	bool	Ret=(connect(&Button ,SIGNAL(clicked(bool)),this,SLOT(on_toolButtonCrossLine_clicked(bool))))?true:false;
			Ret=(connect(&Button ,SIGNAL(SignalRightButton()),SLOT(on_toolButtonCrossLine_pressed())))?true:false;

	delete	ui->toolButtonCrossLine;
	ui->toolButtonCrossLine=NULL;

	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ButtonToShowCrossLineForm::~ButtonToShowCrossLineForm()
{
    delete ui;
}

void	ButtonToShowCrossLineForm::AfterPrepare(void)
{
	on_toolButtonCrossLine_clicked(true);
}

void ButtonToShowCrossLineForm::on_toolButtonCrossLine_clicked(bool b)
{
	for(int i=0;i<ImagePanelInst.count();i++){
		GUIFormBase	*f=GetLayersBase()->FindByName(ImagePanelInst[i]);
		if(f!=NULL){
			DisplayImage	*Img=dynamic_cast<DisplayImage *>(f);
			if(Img!=NULL){
				Img->SetCrossLineMode(Button.isChecked(),LineColor);
				Img->Repaint();
			}
		}
	}
}

void	ButtonToShowCrossLineForm::ResizeAction()
{
	Button.move(0,0);
	Button.resize(width(),height());
}

void ButtonToShowCrossLineForm::on_toolButtonCrossLine_pressed()
{
	QColor	Col=QColorDialog::getColor ( LineColor, NULL
									, "クロスラインの色");
	if(Col.isValid()==true){
		LineColor=Col;
		on_toolButtonCrossLine_clicked(true);
	}
}

