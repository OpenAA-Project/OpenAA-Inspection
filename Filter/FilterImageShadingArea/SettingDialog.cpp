#include "SettingDialog.h"
#include "ui_SettingDialog.h"
#include "FilterImageShadingArea.h"
#include <QFileDialog>
#include "XIntClass.h"
#include "swap.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"

SettingDialog::SettingDialog(LayersBase *base,FilterImageShadingArea *parent ,QWidget *p) :
    QDialog(p)
	,ServiceForLayers(base)
    ,ui(new Ui::SettingDialog)
{
    ui->setupUi(this);
	Parent=parent;

	MagR	=1.0;
	MagG	=1.0;
	MagB	=1.0;
	UsagePhaseNumber=0;
	UsagePageNumber	=0;
	int	LayerNumb=GetLayersBase()->GetMaxLayerNumb();
	if(LayerNumb==1){
		ui->labelMagR			->setVisible(true);
		ui->doubleSpinBoxMagR	->setVisible(true);
		ui->labelMagG			->setVisible(false);
		ui->doubleSpinBoxMagG	->setVisible(false);
		ui->labelMagB			->setVisible(false);
		ui->doubleSpinBoxMagB	->setVisible(false);
	}
	else if(LayerNumb==2){
		ui->labelMagR			->setVisible(true);
		ui->doubleSpinBoxMagR	->setVisible(true);
		ui->labelMagG			->setVisible(true);
		ui->doubleSpinBoxMagG	->setVisible(true);
		ui->labelMagB			->setVisible(false);
		ui->doubleSpinBoxMagB	->setVisible(false);
	}
	else if(LayerNumb>=3){
		ui->labelMagR			->setVisible(true);
		ui->doubleSpinBoxMagR	->setVisible(true);
		ui->labelMagG			->setVisible(true);
		ui->doubleSpinBoxMagG	->setVisible(true);
		ui->labelMagB			->setVisible(true);
		ui->doubleSpinBoxMagB	->setVisible(true);
	}
}

SettingDialog::~SettingDialog()
{
    delete ui;
}

void SettingDialog::Reflect(void)
{
	ui->doubleSpinBoxMagR	->setValue(MagR);
	ui->doubleSpinBoxMagG	->setValue(MagG);
	ui->doubleSpinBoxMagB	->setValue(MagB);
	ui->spinBoxUsePhaseNumber	->setValue(UsagePhaseNumber);
	ui->spinBoxUsePageNumber	->setValue(UsagePageNumber);

	ui->listWidgetFileList->addItems(FileList);
}

void SettingDialog::on_pushButtonAddFiles_clicked()
{
	QStringList	FileList=QFileDialog::getOpenFileNames (NULL, "Select Pix files"
															, QString()
															, /**/"Pix(*.pix);;All files(*.*)");
	if(FileList.count()>0){
		ui->listWidgetFileList->addItems(FileList);
	}
}

void SettingDialog::on_pushButtonDelFiles_clicked()
{
	IntList		Rows;
	::GetSelectedRows(ui->listWidgetFileList,Rows);
	for(IntClass *v=Rows.GetLast();v!=NULL;v=v->GetPrev()){
		int	R=v->GetValue();
		QListWidgetItem *L=ui->listWidgetFileList->item(R);
		if(L!=NULL){
			ui->listWidgetFileList->removeItemWidget(L);
		}
	}
}

void SettingDialog::on_pushButtonCalculate_clicked()
{
	Parent->Initial();
	FileList=GetDataFromListWidget(ui->listWidgetFileList);
	int	Count=FileList.count();
	int	UsePhaseNumber	=ui->spinBoxUsePhaseNumber	->value();
	int	UsePageNumber	=ui->spinBoxUsePageNumber	->value();


	for(int i=0;i<Count;i++){
		AddPix(UsePhaseNumber,UsePageNumber,FileList[i],Parent->MultiplePerDot,Parent->XLen,Parent->YLen);
	}
	int	LayerNumb=GetLayersBase()->GetMaxLayerNumb();
	double	Mag[10];
	if(LayerNumb==1){
		Mag[0]=ui->doubleSpinBoxMagR	->value();
	}
	else if(LayerNumb==2){
		Mag[0]=ui->doubleSpinBoxMagR	->value();
		Mag[1]=ui->doubleSpinBoxMagG	->value();
	}
	else if(LayerNumb>=3){
		Mag[0]=ui->doubleSpinBoxMagR	->value();
		Mag[1]=ui->doubleSpinBoxMagG	->value();
		Mag[2]=ui->doubleSpinBoxMagB	->value();
	}
	
	for(int L=0;L<LayerNumb;L++){
		short	**DBuff=Parent->MultiplePerDot[L];
		short	MaxD=0;
		for(int y=0;y<Parent->YLen;y++){
			for(int x=0;x<Parent->XLen;x++){
				short	d=DBuff[y][x];
				MaxD=max(MaxD,d);
			}
		}
		for(int y=0;y<Parent->YLen;y++){
			for(int x=0;x<Parent->XLen;x++){
				short	d=DBuff[y][x];
				if(d==0)
					DBuff[y][x]=256;
				else{
					DBuff[y][x]=Mag[0]*256*255*MaxD/(d*Count);
				}
			}
		}
	}
}

void SettingDialog::on_pushButtonClose_clicked()
{
	MagR	=ui->doubleSpinBoxMagR	->value();
	MagG	=ui->doubleSpinBoxMagG	->value();
	MagB	=ui->doubleSpinBoxMagB	->value();
	UsagePhaseNumber	=ui->spinBoxUsePhaseNumber	->value();
	UsagePageNumber		=ui->spinBoxUsePageNumber	->value();
	FileList=GetDataFromListWidget(ui->listWidgetFileList);
	done(true);
}

bool SettingDialog::AddPix(int UsePhaseNumber,int UsePageNumber,const QString &FileName,short ***MultiplePerDot ,int XLen ,int YLen)
{
	QFile	RFile(FileName);
	if(RFile.open(QIODevice::ReadOnly)==false)
		return false;

	int	Ver;
	if(::Load(&RFile,Ver)==false)
		return false;
	int	iDotPerLine;
	int	iMaxLines;
	int	iPageNumb;
	int	iLayerNumb;
	int	iYCountBase;
	int	iPhaseNumb=1;
	if(Ver>=2){
		if(::Load(&RFile,iPhaseNumb)==false)
			return false;
	}
	if(::Load(&RFile,iPageNumb)==false)
		return false;
	if(::Load(&RFile,iLayerNumb)==false)
		return false;
	if(::Load(&RFile,iDotPerLine)==false)
		return false;
	if(::Load(&RFile,iMaxLines)==false)
		return false;
	if(::Load(&RFile,iYCountBase)==false)
		return false;

	BYTE	Buff[200000];
	for(int phase=0;phase<iPhaseNumb;phase++){
		if(phase==UsePhaseNumber){
			for(int page=0;page<iPageNumb;page++){
				if(page==UsePageNumber){
					int	YCount=iYCountBase;
					int	TopY;
					for(TopY=0;TopY<GetMaxLines(-1) && TopY<iMaxLines;TopY+=YCount){
						if(TopY+YCount>iMaxLines)
							YCount=iMaxLines-TopY;
						int	Layer;
						for(Layer=0;Layer<GetLayerNumb(page) && Layer<iLayerNumb;Layer++){
							for(int i=0;i<YCount;i++){
								if(RFile.read((char *)Buff,iDotPerLine)!=iDotPerLine)
									return false;
								short	**d=MultiplePerDot[Layer];
								for(int x=0;x<XLen && x<iDotPerLine;x++){
									d[TopY+i][x]+=Buff[x];
								}
							}
						}
						if(Layer<iLayerNumb){
							for(;Layer<iLayerNumb;Layer++){
								QByteArray	D=RFile.read(YCount*iDotPerLine);
								if(D.count()!=YCount*iDotPerLine){
									return false;
								}
							}
						}
					}
					if(TopY<iMaxLines){
						for(;TopY<iMaxLines;TopY+=YCount){
							if(TopY+YCount>iMaxLines)
								YCount=iMaxLines-TopY;
							int	Layer;
							for(Layer=0;Layer<iLayerNumb;Layer++){
								QByteArray	D=RFile.read(YCount*iDotPerLine);
								if(D.count()!=YCount*iDotPerLine){
									return false;
								}
							}
						}			
					}
				}
				else{
					int	YCount=iYCountBase;
					int	TopY;
					for(TopY=0;TopY<iMaxLines;TopY+=YCount){
						if(TopY+YCount>iMaxLines)
							YCount=iMaxLines-TopY;
						int	Layer;
						for(Layer=0;Layer<iLayerNumb;Layer++){
							for(int i=0;i<YCount;i++){
								if(RFile.read((char *)Buff,iDotPerLine)!=iDotPerLine)
									return false;
							}
						}
					}
				}
			}
		}
		else{
			for(int page=0;page<iPageNumb;page++){
				int	YCount=iYCountBase;
				int	TopY;
				for(TopY=0;TopY<iMaxLines;TopY+=YCount){
					if(TopY+YCount>iMaxLines)
						YCount=iMaxLines-TopY;
					int	Layer;
					for(Layer=0;Layer<iLayerNumb;Layer++){
						for(int i=0;i<YCount;i++){
							if(RFile.read((char *)Buff,iDotPerLine)!=iDotPerLine)
								return false;
						}
					}
				}
			}
		}
	}
	return true;
}
void SettingDialog::on_pushButtonCancel_clicked()
{
	done(false);
}
