#include "WindUpImageResource.h"
#include "WindUpImageForm.h"
#include "ui_WindUpImageForm.h"
#include "XDataInLayer.h"
#include "XGeneralFunc.h"
#include "XRememberer.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

WindUpImageForm::WindUpImageForm(LayersBase *Base,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::WindUpImageForm)
{
    ui->setupUi(this);

	ui->spinBoxShiftDown	->setValue(ControlRememberer::GetInt(ui->spinBoxShiftDown	,2000));
	ui->spinBoxWindUp		->setValue(ControlRememberer::GetInt(ui->spinBoxWindUp		,3000));
	ui->spinBoxBrightness	->setValue(ControlRememberer::GetInt(ui->spinBoxBrightness	,20));
}

WindUpImageForm::~WindUpImageForm()
{
    delete ui;
}

void WindUpImageForm::on_pushButtonExecuteWindup_clicked()
{
	int	ShiftDown	=ui->spinBoxShiftDown->value();
	int	WindUp		=ui->spinBoxWindUp	->value();
	int	Brightness	=ui->spinBoxBrightness->value();

	ControlRememberer::SetValue(ui->spinBoxShiftDown	,ui->spinBoxShiftDown->value()	);
	ControlRememberer::SetValue(ui->spinBoxWindUp		,ui->spinBoxWindUp->value()		);
	ControlRememberer::SetValue(ui->spinBoxBrightness	,ui->spinBoxBrightness->value()	);

	for(int page=0;page<GetPageNumb();page++){
		int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdExecuteWindUp	RCmd(GetLayersBase(),sRoot,sName,globalPage);
		RCmd.ShiftDown	=ShiftDown;
		RCmd.WindUp		=WindUp;
		RCmd.Brightness	=Brightness;
		RCmd.SendOnly(globalPage,0,10000);
	}
}


//===========================================================================================

GUICmdExecuteWindUp::GUICmdExecuteWindUp(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	ShiftDown	=0;
	WindUp		=0;
	Brightness	=0;
}
bool	GUICmdExecuteWindUp::Load(QIODevice *f)
{
	if(::Load(f,ShiftDown)==false){
		return false;
	}
	if(::Load(f,WindUp)==false){
		return false;
	}
	if(::Load(f,Brightness)==false){
		return false;
	}
	return true;
}

bool	GUICmdExecuteWindUp::Save(QIODevice *f)
{
	if(::Save(f,ShiftDown)==false){
		return false;
	}
	if(::Save(f,WindUp)==false){
		return false;
	}
	if(::Save(f,Brightness)==false){
		return false;
	}
	return true;
}


void	GUICmdExecuteWindUp::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	DataInPage	*Dp=GetLayersBase()->GetPageData(localPage);
	for(int layer=0;layer<GetLayerNumb(localPage);layer++){
		DataInLayer	*Lp=Dp->GetLayerData(layer);
		ImageBuffer	&IBuff=Lp->GetMasterBuff();

		ImageBuffer	Buff(0,Dp->GetDotPerLine(),Dp->GetMaxLines());
		//元画像をバッファへコピー
		Buff=IBuff;

		//画像移動
		IBuff.MoveImage(0,ShiftDown);
		if(ShiftDown>0){
			//全体を下に移動するとき、上の空き領域を塗りつぶす
			for(int y=0;y<Dp->GetMaxLines() && y<ShiftDown;y++){
				BYTE	*d=IBuff.GetY(y);
				memset(d,Brightness,Dp->GetDotPerLine());
			}
		}
		else{
			//全体を上に移動するとき、下の空き領域を塗りつぶす
			for(int y=Dp->GetMaxLines()+ShiftDown;y<Dp->GetMaxLines();y++){
				BYTE	*d=IBuff.GetY(y);
				memset(d,Brightness,Dp->GetDotPerLine());
			}
		}
		if(WindUp>=Dp->GetMaxLines()){
			WindUp=Dp->GetMaxLines();
		}
		if(ShiftDown>0){
			//画像を下に移動するとき、巻き上げは下からWindUpライン分を上へコピー
			for(int n=0;n<WindUp;n++){
				BYTE	*d=IBuff.GetY(n);
				BYTE	*s=Buff.GetY(Dp->GetMaxLines()-WindUp+n);
				memcpy(d,s,Dp->GetDotPerLine());
			}
		}
		else{
			//画像を上に移動するとき、巻き上げは上からWindUpライン分を下へコピー
			for(int n=0;n<WindUp;n++){
				BYTE	*d=IBuff.GetY(Dp->GetMaxLines()-WindUp+n);
				BYTE	*s=Buff.GetY(n);
				memcpy(d,s,Dp->GetDotPerLine());
			}
		}
	}
	SendAck(localPage);
}