#include "ShowResultDialog.h"
#include "ui_ShowResultDialog.h"
#include "DustReducerAI.h"

#include "swap.h"
#include "XGeneralFunc.h"
#include <QFileDialog>
#include "XResultAnalizer.h"
#include "XDataInLayer.h"
#include <QFile>
#include "XDataAlgorithm.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

ShowResultDialog::ShowResultDialog(LayersBase *base ,DustReducerAI *P,QWidget *parent) :
    QDialog(parent),ServiceForLayers(base),Parent(P),
    ui(new Ui::ShowResultDialog)
{
    ui->setupUi(this);

	Current	=NULL;
	RegImage=NULL;
	CurrentImage=new QImage(Parent->XLen,Parent->YLen,QImage::Format_ARGB32);
	MakeImage(CurrentImage,Parent->CurrentPattern,GetLayersBase()->GetMaxLayerNumb(),Parent->XLen,Parent->YLen);
	ui->labelCurrentPanel->setPixmap(QPixmap::fromImage(*CurrentImage));

	ui->tableWidgetResult->setColumnWidth(0,54);
	ui->tableWidgetResult->setColumnWidth(1,130);
	ui->tableWidgetResult->setColumnWidth(2,54);
	ui->tableWidgetResult->setColumnWidth(3,48);

	ShowList();
}

ShowResultDialog::~ShowResultDialog()
{
    delete ui;

	if(CurrentImage!=NULL)
		delete	CurrentImage;
	CurrentImage=NULL;

	if(RegImage!=NULL)
		delete	RegImage;
	RegImage=NULL;
}
void	ShowResultDialog::MakeImage(QImage *Img,BYTE *Pattern[3],int LayerNumb,int XLen,int YLen)
{
	int	NXLen=min(XLen,Img->width());
	int	NYLen=min(YLen,Img->height());
	if(LayerNumb>=3){
		for(int y=0;y<NYLen;y++){
			QRgb	*d=(QRgb *)Img->scanLine(y);
			BYTE	*s0=Pattern[0]+y*XLen;
			BYTE	*s1=Pattern[1]+y*XLen;
			BYTE	*s2=Pattern[2]+y*XLen;
			for(int x=0;x<NXLen;x++){
				*d=qRgb(*s0,*s1,*s2);
				d++;
				s0++;
				s1++;
				s2++;
			}
		}
	}
	else
	if(LayerNumb==2){
		for(int y=0;y<NYLen;y++){
			QRgb	*d=(QRgb *)Img->scanLine(y);
			BYTE	*s0=Pattern[0]+y*XLen;
			BYTE	*s1=Pattern[1]+y*XLen;
			for(int x=0;x<NXLen;x++){
				*d=qRgb(*s0,*s0,*s1);
				d++;
				s0++;
				s1++;
			}
		}
	}
	else
	if(LayerNumb==1){
		for(int y=0;y<NYLen;y++){
			QRgb	*d=(QRgb *)Img->scanLine(y);
			BYTE	*s0=Pattern[0]+y*XLen;
			for(int x=0;x<NXLen;x++){
				*d=qRgb(*s0,*s0,*s0);
				d++;
				s0++;
			}
		}
	}
}

void ShowResultDialog::ShowList(void)
{
	int	Count=min(100,(int)Parent->RegLib.DustRegListPointerContainer.GetCount());
	ui->tableWidgetResult->setRowCount(Count);
	int	Row=0;
	for(DustRegListPointer *a=Parent->RegLib.DustRegListPointerContainer.GetFirst();a!=NULL && Row<Count;a=a->GetNext(),Row++){
		::SetDataToTable(ui->tableWidgetResult ,0 ,Row ,QString::number(a->Point->ID));
		::SetDataToTable(ui->tableWidgetResult ,1 ,Row ,a->Point->Comment);
		::SetDataToTable(ui->tableWidgetResult ,2 ,Row ,QString::number(a->Result,'f',3));
		if(a->Point->JudgeDustValue==_Judge_OK)
			::SetDataToTable(ui->tableWidgetResult ,3 ,Row ,QString(/**/"OK"));
		else
			::SetDataToTable(ui->tableWidgetResult ,3 ,Row ,QString(/**/"NG"));
	}
}

void ShowResultDialog::on_pushButtonRegOK_clicked()
{
	QString	Comment=ui->lineEditCurrentComment->text();

	for(int page=0;page<GetPageNumb();page++){
		GUICmdReqRADustReducerAIAddCurrent	RCmd(GetLayersBase(),sRoot,sName,page);
		RCmd.ResultAnalizerItemBaseID	=Parent->GetID();
		RCmd.Comment	=Comment;
		RCmd.OkNg		=_Judge_OK;
		RCmd.Send(NULL,page,0);
	}
	Parent->SaveLib();
	ShowList();
}

void ShowResultDialog::on_pushButtonRegNG_clicked()
{
	QString	Comment=ui->lineEditCurrentComment->text();

	for(int page=0;page<GetPageNumb();page++){
		GUICmdReqRADustReducerAIAddCurrent	RCmd(GetLayersBase(),sRoot,sName,page);
		RCmd.ResultAnalizerItemBaseID	=Parent->GetID();
		RCmd.Comment	=Comment;
		RCmd.OkNg		=_Judge_NG;
		RCmd.Send(NULL,page,0);
	}
	Parent->SaveLib();
	ShowList();
}

void ShowResultDialog::on_tableWidgetResult_clicked(const QModelIndex &index)
{
	int	Row=ui->tableWidgetResult->currentRow();
	if(Row<0)
		return;
	DustRegListPointer *a=Parent->RegLib.DustRegListPointerContainer.GetItem(Row);
	if(a!=NULL){
		Current=a;
		if(RegImage!=NULL){
			delete	RegImage;
		}
		RegImage=new QImage(Current->Point->XLen,Current->Point->YLen,QImage::Format_ARGB32);
		MakeImage(RegImage,Current->Point->Pattern,Current->Point->LayerNumb,Current->Point->XLen,Current->Point->YLen);
		ui->labelRegPanel->setPixmap(QPixmap::fromImage(*RegImage));
		ui->lineEditRegComment	->setText(Current->Point->Comment);
		ui->comboBoxJudge	->setCurrentIndex((Current->Point->JudgeDustValue==_Judge_OK)?0:1);
	}
}

void ShowResultDialog::on_pushButtonChangeReg_clicked()
{
	int	Row=ui->tableWidgetResult->currentRow();
	if(Row<0)
		return;
	if(Current!=NULL){
		QString	Comment=ui->lineEditRegComment	->text();

		Current->Point->Comment	=Comment;
		Current->Point->JudgeDustValue	=(ui->comboBoxJudge	->currentIndex()==0)?_Judge_OK:_Judge_NG;
		Parent->SaveLib();
		ShowList();
		::SetCurrentRow(ui->tableWidgetResult,Row);

		for(int page=0;page<GetPageNumb();page++){
			GUICmdReqRADustReducerAIUpdateRegLib	RCmd(GetLayersBase(),sRoot,sName,page);
			RCmd.ResultAnalizerItemBaseID	=Parent->GetID();
			RCmd.DustRegListID				=Current->Point->ID;
			RCmd.Comment	=Comment;
			RCmd.OkNg		=Current->Point->JudgeDustValue;
			RCmd.Send(NULL,page,0);
		}
	}
}

void ShowResultDialog::on_pushButtonDeleteReg_clicked()
{
	if(Current!=NULL){
		DustRegList	*p=Current->Point;
		Parent->RegLib.DustRegListPointerContainer.RemoveList(Current);
		int	ResultAnalizerItemBaseID=Parent->GetID();
		int	DustRegListID			=Current->Point->ID;
		delete	Current;
		Parent->RegLib.RemoveList(p);
		delete	p;
		Parent->SaveLib();

		for(int page=0;page<GetPageNumb();page++){
			GUICmdReqRADustReducerAIDeleteRegLib	RCmd(GetLayersBase(),sRoot,sName,page);
			RCmd.ResultAnalizerItemBaseID	=ResultAnalizerItemBaseID;
			RCmd.DustRegListID				=DustRegListID;
			RCmd.Send(NULL,page,0);
		}

		Current=NULL;
		ShowList();

	}

}

void ShowResultDialog::on_pushButtonLoadRegPack_clicked()
{
	QString	FileName=QFileDialog::getOpenFileName(NULL,"Select Registration library file"
														,QString()
														,/**/"Dat file(*.dat);;All files(*.*)");
	if(FileName.isEmpty()==false){
		QFile	File(FileName);
		if(File.open(QIODevice::ReadOnly)==true){
			Parent->RegLib.Load(&File);
			Current=NULL;
			Parent->Calc();
			ShowList();
		}
	}
}

void ShowResultDialog::on_pushButtonSaveRegPack_clicked()
{
	QString	FileName=QFileDialog::getSaveFileName(NULL,"Save Registration library file"
														,QString()
														,/**/"Dat file(*.dat);;All files(*.*)");
	if(FileName.isEmpty()==false){
		QFile	File(FileName);
		if(File.open(QIODevice::WriteOnly)==true){
			Parent->RegLib.Save(&File);
		}
	}

}

void ShowResultDialog::on_pushButtonClearRegPack_clicked()
{
	Parent->RegLib.RemoveAll();
	Parent->RegLib.DustRegListPointerContainer.RemoveAll();
	Current=NULL;
	ShowList();
}

void ShowResultDialog::on_pushButtonClose_clicked()
{
	done(true);
}

//============================================================================
GUICmdReqRADustReducerAIAddCurrent::GUICmdReqRADustReducerAIAddCurrent(LayersBase *base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdReqRADustReducerAIAddCurrent::Load(QIODevice *f)
{
	if(::Load(f,ResultAnalizerItemBaseID)==false)	return false;
	if(::Load(f,Comment)==false)					return false;
	BYTE	d;
	if(::Load(f,d)==false)							return false;
	OkNg	=(JudgeDust)d;
	return true;
}
bool	GUICmdReqRADustReducerAIAddCurrent::Save(QIODevice *f)
{
	if(::Save(f,ResultAnalizerItemBaseID)==false)	return false;
	if(::Save(f,Comment)==false)					return false;
	BYTE	d=(BYTE)OkNg;
	if(::Save(f,Comment)==false)					return false;
	return true;
}

void	GUICmdReqRADustReducerAIAddCurrent::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	if(localPage==0){
		ResultAnalizerItemBase	*R=GetLayersBase()->GetResultAnalizerItemBaseContainer()->FindByID(ResultAnalizerItemBaseID);
		if(R!=NULL){
			DustReducerAI	*DustReducerAIItem=dynamic_cast<DustReducerAI *>(R);
			if(DustReducerAIItem!=NULL){
				DustReducerAIItem->AddToLib(Comment,OkNg);
				DustReducerAIItem->SaveLib();
			}
		}
	}
}

GUICmdReqRADustReducerAIUpdateRegLib::GUICmdReqRADustReducerAIUpdateRegLib(LayersBase *base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdReqRADustReducerAIUpdateRegLib::Load(QIODevice *f)
{
	if(::Load(f,ResultAnalizerItemBaseID)==false)	return false;
	if(::Load(f,DustRegListID)==false)				return false;
	if(::Load(f,Comment)==false)					return false;
	BYTE	d;
	if(::Load(f,d)==false)							return false;
	OkNg	=(JudgeDust)d;
	return true;
}
bool	GUICmdReqRADustReducerAIUpdateRegLib::Save(QIODevice *f)
{
	if(::Save(f,ResultAnalizerItemBaseID)==false)	return false;
	if(::Save(f,DustRegListID)==false)				return false;
	if(::Save(f,Comment)==false)					return false;
	BYTE	d=(BYTE)OkNg;
	if(::Save(f,Comment)==false)					return false;
	return true;
}

void	GUICmdReqRADustReducerAIUpdateRegLib::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	ResultAnalizerItemBase	*R=GetLayersBase()->GetResultAnalizerItemBaseContainer()->FindByID(ResultAnalizerItemBaseID);
	if(R!=NULL){
		DustReducerAI	*DustReducerAIItem=dynamic_cast<DustReducerAI *>(R);
		if(DustReducerAIItem!=NULL){
			DustRegList	*r=DustReducerAIItem->RegLib.FindByID(DustRegListID);
			if(r!=NULL){
				r->Comment			=Comment;
				r->JudgeDustValue	=OkNg;
				DustReducerAIItem->SaveLib();
			}
		}
	}
}

GUICmdReqRADustReducerAIDeleteRegLib::GUICmdReqRADustReducerAIDeleteRegLib(LayersBase *base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdReqRADustReducerAIDeleteRegLib::Load(QIODevice *f)
{
	if(::Load(f,ResultAnalizerItemBaseID)==false)	return false;
	if(::Load(f,DustRegListID)==false)				return false;
	return true;
}
bool	GUICmdReqRADustReducerAIDeleteRegLib::Save(QIODevice *f)
{
	if(::Save(f,ResultAnalizerItemBaseID)==false)	return false;
	if(::Save(f,DustRegListID)==false)				return false;
	return true;
}

void	GUICmdReqRADustReducerAIDeleteRegLib::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	ResultAnalizerItemBase	*R=GetLayersBase()->GetResultAnalizerItemBaseContainer()->FindByID(ResultAnalizerItemBaseID);
	if(R!=NULL){
		DustReducerAI	*DustReducerAIItem=dynamic_cast<DustReducerAI *>(R);
		if(DustReducerAIItem!=NULL){
			DustRegListPointer	*p=DustReducerAIItem->RegLib.FindPointer(DustRegListID);
			if(p!=NULL){
				DustReducerAIItem->RegLib.DustRegListPointerContainer.RemoveList(p);
				delete	p;
			}
			DustRegList	*r=DustReducerAIItem->RegLib.FindByID(DustRegListID);
			if(r!=NULL){
				DustReducerAIItem->RegLib.RemoveList(r);
				delete	r;
			}
			DustReducerAIItem->SaveLib();
		}
	}
}
