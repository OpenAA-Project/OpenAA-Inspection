#include "CopyAnyPhasePageLayerDialog.h"
#include "ui_CopyAnyPhasePageLayerDialog.h"
#include "ButtonCopyAnyPhasePageLayer.h"
#include "XAlgorithmBase.h"
#include "XDataAlgorithm.h"
#include "XFFT1d.h" 

extern	const	char	*sRoot;
extern	const	char	*sName;

CopyAnyPhasePageLayerDialog::CopyAnyPhasePageLayerDialog(LayersBase *Base ,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(Base)
    ,ui(new Ui::CopyAnyPhasePageLayerDialog)
{
    ui->setupUi(this);

	for(int phase=0;phase<GetPhaseNumb();phase++){
		ui->listWidgetSrcPhase->addItem(QString("Phase ")+QString::number(phase));
		ui->listWidgetDstPhase->addItem(QString("Phase ")+QString::number(phase));
	}
	for(int page=0;page<GetPageNumb();page++){
		ui->listWidgetSrcPage->addItem(QString("Page ")+QString::number(page));
		ui->listWidgetDstPage->addItem(QString("Page ")+QString::number(page));
	}
	int	LayerNumb=GetLayersBase()->GetMaxLayerNumb();
	for(int layer=0;layer<LayerNumb;layer++){
		ui->listWidgetSrcLayer->addItem(QString("Layer ")+QString::number(layer));
		ui->listWidgetDstLayer->addItem(QString("Layer ")+QString::number(layer));
	}
}

CopyAnyPhasePageLayerDialog::~CopyAnyPhasePageLayerDialog()
{
    delete ui;
}

void CopyAnyPhasePageLayerDialog::on_pushButtonExecuteCopy_clicked()
{
	int	SrcPhase=ui->listWidgetSrcPhase	->currentRow();
	int	SrcPage	=ui->listWidgetSrcPage	->currentRow();
	int	SrcLayer=ui->listWidgetSrcLayer	->currentRow();
	int	DstPhase=ui->listWidgetDstPhase	->currentRow();
	int	DstPage	=ui->listWidgetDstPage	->currentRow();
	int	DstLayer=ui->listWidgetDstLayer	->currentRow();
	if(SrcPhase	<0)	return;
	if(SrcPage	<0)	return;
	if(SrcLayer	<0)	return;
	if(DstPhase	<0)	return;
	if(DstPage	<0)	return;
	if(DstLayer	<0)	return;

	int	SGlobalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),SrcPage);
	GUICmdReqAnyData	RCmd(GetLayersBase(),sRoot,sName,SGlobalPage);
	GUICmdAckAnyData	ACmd(GetLayersBase(),sRoot,sName,SGlobalPage);
	RCmd.Phase	=SrcPhase;
	RCmd.Layer	=SrcLayer;
	RCmd.ReqMasterImage	=ui->checkBoxMasterImage->isChecked();
	RCmd.ReqTargetImage	=ui->checkBoxTargetImage->isChecked();
	RCmd.ReqAlgorithm	=ui->checkBoxAlgorithm	->isChecked();
	if(RCmd.Send(SGlobalPage,0,ACmd)==true){
		if(ACmd.Success==true){
			int	DGlobalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),DstPage);
			GUICmdSendAnyData	SCmd(GetLayersBase(),sRoot,sName,DGlobalPage);
			SCmd.Phase			=DstPhase;	//ACmd.Phase;
			SCmd.Layer			=DstLayer;	//ACmd.Layer;
			SCmd.ReqMasterImage	=ui->checkBoxDestMasterImage->isChecked();	//ACmd.ReqMasterImage	;
			SCmd.ReqTargetImage	=ui->checkBoxDestTargetImage->isChecked();	//ACmd.ReqTargetImage	;
			SCmd.ReqAlgorithm	=ACmd.ReqAlgorithm;
			SCmd.Data			=ACmd.Data;
			SCmd.Send(NULL,DGlobalPage,0);
		}
	}
}

void CopyAnyPhasePageLayerDialog::on_pushButtonClose_clicked()
{
	close();
}



//----------------------------------------------------------------------------------

GUICmdReqAnyData::GUICmdReqAnyData(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqAnyData::Load(QIODevice *f)
{
	if(::Load(f,Phase)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,ReqMasterImage)==false)
		return false;
	if(::Load(f,ReqTargetImage)==false)
		return false;
	if(::Load(f,ReqAlgorithm)==false)
		return false;
	return true;
}
bool	GUICmdReqAnyData::Save(QIODevice *f)
{
	if(::Save(f,Phase)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,ReqMasterImage)==false)
		return false;
	if(::Save(f,ReqTargetImage)==false)
		return false;
	if(::Save(f,ReqAlgorithm)==false)
		return false;
	return true;
}

void	GUICmdReqAnyData::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckAnyData	*SendBack=GetSendBack(GUICmdAckAnyData,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	
	QBuffer	Buff;
	
	bool	TotalSuccess=true;
	Buff.open(QIODevice::ReadWrite);
	if(ReqMasterImage==true){
		bool	Success=false;
		PageDataInOnePhase	*Ph=GetLayersBase()->GetPageDataPhase(Phase);
		if(Ph!=NULL){
			DataInPage	*Dp=Ph->GetPageData(localPage);
			if(Dp!=NULL){
				DataInLayer	*Lp=Dp->GetLayerData(Layer);
				if(Lp!=NULL){
					if(Lp->GetMasterBuff().Save(&Buff)==true){
						Success=true;
					}
				}
			}
		}
		if(Success==false){
			TotalSuccess=false;
		}
	}

	if(ReqTargetImage==true){
		bool	Success=false;
		PageDataInOnePhase	*Ph=GetLayersBase()->GetPageDataPhase(Phase);
		if(Ph!=NULL){
			DataInPage	*Dp=Ph->GetPageData(localPage);
			if(Dp!=NULL){
				DataInLayer	*Lp=Dp->GetLayerData(Layer);
				if(Lp!=NULL){
					if(Lp->GetTargetBuff().Save(&Buff)==true){
						Success=true;
					}
				}
			}
		}
		if(Success==false){
			TotalSuccess=false;
		}
	}
	
	if(ReqAlgorithm==true){
		int	N=GetLayersBase()->GetLogicDLLBase()->GetCount();
		if(::Save(&Buff,N)==false){
			TotalSuccess=false;
		}
		else{
			for(LogicDLL *L=GetLayersBase()->GetLogicDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
				bool	Success=false;
				AlgorithmInPageInOnePhase	*Ah=L->GetInstance()->GetPageDataPhase(Phase);
				if(Ah!=NULL){
					AlgorithmInPageRoot		*Ap=Ah->GetPageData(localPage);
					if(Ap!=NULL){
						if(::Save(&Buff,L->GetDLLRoot())==false)
							break;
						if(::Save(&Buff,L->GetDLLName())==false)
							break;
						if(Ap->Save(&Buff)==true){
							Success=true;
						}
					}
				}
				if(Success==false){
					TotalSuccess=false;
				}
			}
		}
	}
	SendBack->ReqMasterImage=ReqMasterImage;
	SendBack->ReqTargetImage=ReqTargetImage;
	SendBack->ReqAlgorithm	=ReqAlgorithm;
	SendBack->Data=Buff.buffer();
	SendBack->Success	=TotalSuccess;

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

//----------------------------------------------------------------------------------

GUICmdAckAnyData::GUICmdAckAnyData(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdAckAnyData::Load(QIODevice *f)
{
	if(::Load(f,Phase)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,ReqMasterImage)==false)
		return false;
	if(::Load(f,ReqTargetImage)==false)
		return false;
	if(::Load(f,ReqAlgorithm)==false)
		return false;
	if(::Load(f,Data)==false)
		return false;
	if(::Load(f,Success)==false)
		return false;
	return true;
}
bool	GUICmdAckAnyData::Save(QIODevice *f)
{
	if(::Save(f,Phase)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,ReqMasterImage)==false)
		return false;
	if(::Save(f,ReqTargetImage)==false)
		return false;
	if(::Save(f,ReqAlgorithm)==false)
		return false;
	if(::Save(f,Data)==false)
		return false;
	if(::Save(f,Success)==false)
		return false;
	return true;

}

//----------------------------------------------------------------------------------

GUICmdSendAnyData::GUICmdSendAnyData(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendAnyData::Load(QIODevice *f)
{
	if(::Load(f,Phase)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,ReqMasterImage)==false)
		return false;
	if(::Load(f,ReqTargetImage)==false)
		return false;
	if(::Load(f,ReqAlgorithm)==false)
		return false;
	if(::Load(f,Data)==false)
		return false;
	return true;
}
bool	GUICmdSendAnyData::Save(QIODevice *f)
{
	if(::Save(f,Phase)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,ReqMasterImage)==false)
		return false;
	if(::Save(f,ReqTargetImage)==false)
		return false;
	if(::Save(f,ReqAlgorithm)==false)
		return false;
	if(::Save(f,Data)==false)
		return false;
	return true;
}

void	GUICmdSendAnyData::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	bool	TotalSuccess=true;
	QBuffer	Buff(&Data);
	Buff.open(QIODevice::ReadOnly);
	if(ReqMasterImage==true){
		bool	Success=false;
		PageDataInOnePhase	*Ph=GetLayersBase()->GetPageDataPhase(Phase);
		if(Ph!=NULL){
			DataInPage	*Dp=Ph->GetPageData(localPage);
			if(Dp!=NULL){
				DataInLayer	*Lp=Dp->GetLayerData(Layer);
				if(Lp!=NULL){
					if(Lp->GetMasterBuff().Load(&Buff)==true){
						Success=true;
					}
				}
			}
		}
		if(Success==false){
			return;
		}
	}

	if(ReqTargetImage==true){
		bool	Success=false;
		PageDataInOnePhase	*Ph=GetLayersBase()->GetPageDataPhase(Phase);
		if(Ph!=NULL){
			DataInPage	*Dp=Ph->GetPageData(localPage);
			if(Dp!=NULL){
				DataInLayer	*Lp=Dp->GetLayerData(Layer);
				if(Lp!=NULL){
					if(Lp->GetTargetBuff().Load(&Buff)==true){
						Success=true;
					}
				}
			}
		}
		if(Success==false){
			return;
		}
	}
	
	if(ReqAlgorithm==true){
		int	N;
		if(::Load(&Buff,N)==true){
			for(int i=0;i<N;i++){
				QString	DLLRoot,DLLName;
				if(::Load(&Buff,DLLRoot)==false)
					break;
				if(::Load(&Buff,DLLName)==false)
					break;
				AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(DLLRoot,DLLName);
				if(Ab==NULL)
					break;
				AlgorithmInPageInOnePhase	*Ah=Ab->GetPageDataPhase(Phase);
				if(Ah!=NULL){
					AlgorithmInPageRoot		*Ap=Ah->GetPageData(localPage);
					if(Ap!=NULL){
						if(Ap->Load(&Buff)==false){
							break;
						}
					}
				}
			}
		}
	}
}

void CopyAnyPhasePageLayerDialog::on_pushButtonTest_clicked()
{
	ImagePointerContainer Images;
	PageDataInOnePhase	*Ph=GetLayersBase()->GetPageDataPhase(0);
	if(Ph!=NULL){
		DataInPage	*Dp=Ph->GetPageData(0);
		if(Dp!=NULL){
			Dp->GetTargetImages(Images);
		}
	}

	for(int L=85*2;L<256;L++){
		*Images[L]=*Images[2];
	}
	for(int L=85;L<85*2;L++){
		*Images[L]=*Images[1];
	}
	for(int L=1;L<85;L++){
		*Images[L]=*Images[0];
	}
	for(int L=0;L<256;L++){
		for(int y=0;y<GetMaxLines(0);y++){
			BYTE	*s=Images[L]->GetY(y);
			for(int x=0;x<GetDotPerLine(0);x++,s++){
				*s=*s/2;
			}
		}
	}
	for(int y=0;y<GetMaxLines(0);y++){
		for(int x=0;x<GetDotPerLine(0);x++){
			DoubleComplex	LDim[257];
			for(int L=0;L<256;L++){
				LDim[L]=DoubleComplex(Images[L]->GetY(y)[x],0);
			}
			LDim[256].set(0,0);
			FFTClass	fft;
			DoubleComplex	ResultDim[257];
			fft.fft(256, LDim ,ResultDim);
			for(int L=3;L<256;L++){
				ResultDim[L].set(0,0);
			}
			fft.reversefft(256, ResultDim ,LDim);
			for(int L=0;L<256;L++){
				Images[L]->GetY(y)[x]=(int)LDim[L].norm();
			}
		}
	}

	for(int L=0;L<256;L++){
		for(int y=0;y<GetMaxLines(0);y+=16){
			for(int x=0;x<GetDotPerLine(0);x+=16){
				double	h=rand()/(double)RAND_MAX;
				h=h*0.4+0.6;
				double	f=rand()/(double)RAND_MAX;
				f=f*15;
				for(int ky=0;ky<16;ky++){
					if(y+ky<GetMaxLines(0)){
						for(int kx=0;kx<16;kx++){
							if(x+kx<GetDotPerLine(0)){
								BYTE	*s=Images[L]->GetY(y+ky);
								*(s+kx)=*(s+kx)*h+f;
							}
						}
					}
				}
			}
		}
	}
	for(int L=0;L<256;L++){
		for(int y=0;y<GetMaxLines(0);y+=4){
			for(int x=0;x<GetDotPerLine(0);x+=4){
				double	h=rand()/(double)RAND_MAX;
				h=h*0.4+0.6;
				double	f=rand()/(double)RAND_MAX;
				f=f*15;
				for(int ky=0;ky<4;ky++){
					if(y+ky<GetMaxLines(0)){
						for(int kx=0;kx<4;kx++){
							if(x+kx<GetDotPerLine(0)){
								BYTE	*s=Images[L]->GetY(y+ky);
								*(s+kx)=*(s+kx)*h+f;
							}
						}
					}
				}
			}
		}
	}
	for(int L=0;L<256;L++){
		for(int y=0;y<GetMaxLines(0);y++){
			BYTE	*s=Images[L]->GetY(y);
			for(int x=0;x<GetDotPerLine(0);x++,s++){
				double	h=rand()/(double)RAND_MAX;
				h=h*0.4+0.6;
				double	f=rand()/(double)RAND_MAX;
				f=f*15;
				*s=*s*h+f;
			}
		}
	}

}

