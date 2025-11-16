#include "PropertyMultiFileMapFormResource.h"
#include "PropertyMultiFileMapForm.h"
#include "ui_PropertyMultiFileMapForm.h"
#include "XMultiFileMap.h"
#include "XDatabaseLoader.h"
#include "XDisplayImagePacket.h"
#include "XGeneralFunc.h"
#include "XGUIMultiFileMapPacket.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

PropertyMultiFileMapForm::PropertyMultiFileMapForm(LayersBase *Base,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::PropertyMultiFileMapForm)
{
    ui->setupUi(this);
}

PropertyMultiFileMapForm::~PropertyMultiFileMapForm()
{
    delete ui;
}


MultiFileMapBase	*PropertyMultiFileMapForm::GetMultiFileMapBase(void)
{
	return (MultiFileMapBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"MultiFileMap");
}

void	PropertyMultiFileMapForm::BuildForShow(void)
{
}
void	PropertyMultiFileMapForm::TransmitDirectly(GUIDirectMessage *packet)
{
	GUICmdAckMultiFileMapInfo *GUICmdAckMultiFileMapInfoVar=dynamic_cast<GUICmdAckMultiFileMapInfo *>(packet);
	if(GUICmdAckMultiFileMapInfoVar!=NULL){
		if(GUICmdAckMultiFileMapInfoVar->PosX>=0 && GUICmdAckMultiFileMapInfoVar->PosY>=0){
			ui->lineEditPosX	->setText(QString::number(GUICmdAckMultiFileMapInfoVar->PosX));
			ui->lineEditPosY	->setText(QString::number(GUICmdAckMultiFileMapInfoVar->PosY));
			ui->lineEditFileName->setText(GUICmdAckMultiFileMapInfoVar->FileName);
		}
		return;
	}
	GUICmdSetMultiFileMapHeader	*GUICmdSetMultiFileMapHeaderVar=dynamic_cast<GUICmdSetMultiFileMapHeader *>(packet);
	if(GUICmdSetMultiFileMapHeaderVar!=NULL){
		ui->lineEditProduct	->setText(GUICmdSetMultiFileMapHeaderVar->ProductName);
		ui->lineEditInspName->setText(GUICmdSetMultiFileMapHeaderVar->PathName);
		ui->lineEditImgNum_X->setText(QString::number(GUICmdSetMultiFileMapHeaderVar->NumbX));
		ui->lineEditImgNum_Y->setText(QString::number(GUICmdSetMultiFileMapHeaderVar->NumbY));
		return;
	}
}

bool	PropertyMultiFileMapForm::SaveContent(QIODevice *f)
{
	WORD	Ver=1;
	if(::Save(f,Ver)==false)
		return false;

	if(::Save(f,LibType)==false)
		return false;
	if(LibList.Save(f)==false)
		return false;
	if(SelectedLibList.Save(f)==false)
		return false;
	if(::Save(f,LibFolderID)==false)
		return false;
	return true;
}
bool	PropertyMultiFileMapForm::LoadContent(QIODevice *f)
{
	WORD	Ver;
	if(::Load(f,Ver)==false)
		return false;

	if(::Load(f,LibType)==false)
		return false;
	if(LibList.Load(f)==false)
		return false;
	if(SelectedLibList.Load(f)==false)
		return false;
	if(::Load(f,LibFolderID)==false)
		return false;

	return true;
}
