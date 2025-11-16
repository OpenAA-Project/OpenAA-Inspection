/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XGeneralDialog.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "XTypeDef.h"
#include "XGeneralDialog.h"
#include<QWidget>
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "LibFolderForm.h"
#include "SelectLibFolderDialog.h"
#include "SelectLibraryForm.h"
#include "SelectPhasePageLayerDialog.h"
#include "XGeneralDialog.h"

GeneralDialog::GeneralDialog(LayersBase *Base,QWidget *cli ,QWidget * parent, bool _DeleteCliInClose)
:QDialog(parent),ServiceForLayers(Base)
{
	DeleteCliInClose=_DeleteCliInClose;
	resize(cli->width()+2,cli->height()+2);
	Client=cli;
	ClientParent=Client->parent();
	Client->setParent(this);
	Client->move(0,0);
	connect(Client,SIGNAL(SignalClose()),this ,SLOT(SlotClose()));
	SetWidgetCenter(this);
	if(GetLayersBase()!=NULL){
		GetLayersBase()->TmpHideProcessingForm();
	}
}

GeneralDialog::~GeneralDialog(void)
{
	//delete	Client;
	//Client=NULL;
	if(GetLayersBase()!=NULL){
		GetLayersBase()->TmpRercoverProcessingForm();
	}
	if(DeleteCliInClose==false){
		QWidget	*w=dynamic_cast<QWidget	*>(ClientParent);
		Client->setParent(w);
	}
}
void GeneralDialog::closeEvent ( QCloseEvent * event )
{
	QDialog::closeEvent (event);
	deleteLater ();
}

void GeneralDialog::resizeEvent(QResizeEvent * event )
{
	Client->resize(width()-1,height()-1);
}

void GeneralDialog::SlotClose()
{
	//Client->setParent(NULL);
	close();
}

//=======================================================================
GeneralLibFolderForm::GeneralLibFolderForm(int LibType,LayersBase *base,QWidget *parent)
	:QObject(parent)
{
	pLibFolderForm=new LibFolderForm(LibType,base,parent);
	connect(pLibFolderForm,SIGNAL(SelectLibFolder(int,QString)),this,SLOT(SlotSelectLibFolder(int,QString)));
	connect(pLibFolderForm,SIGNAL(SignalDrop(int ,int , QWidget *)),this,SLOT(SlotDrop(int ,int , QWidget *)));
}
GeneralLibFolderForm::~GeneralLibFolderForm()
{
	delete	pLibFolderForm;
	pLibFolderForm=NULL;
}

int		GeneralLibFolderForm::CreateNewFolder(void)
{
	return pLibFolderForm->CreateNewFolder();
}
int		GeneralLibFolderForm::SetLibType(int libType)
{
	return pLibFolderForm->SetLibType(libType);
}

void	GeneralLibFolderForm::Show(void)
{
	pLibFolderForm->Show();
}

void	GeneralLibFolderForm::Drop(int FolderParentID ,int LibFolderID , QWidget *w)
{
	pLibFolderForm->Drop(FolderParentID ,LibFolderID , w);
}

void	GeneralLibFolderForm::FitToFrame(QWidget *ParentFrame)
{
	pLibFolderForm->FitToFrame(ParentFrame);
}


void	GeneralLibFolderForm::SetCurrentLibFolder(int LibFolderID)
{
	pLibFolderForm->SetCurrentLibFolder(LibFolderID);
}
void	GeneralLibFolderForm::SlotSelectLibFolder(int libid,QString s)
{
	emit	SelectLibFolder(libid,s);
}
void	GeneralLibFolderForm::SlotDrop(int FolderParentID ,int LibFolderID , QWidget *w)
{
	emit	SignalDrop(FolderParentID ,LibFolderID ,w);
}

void	GeneralLibFolderForm::move(int x,int y)
{
	pLibFolderForm->move(x,y);
}
void	GeneralLibFolderForm::resize(int w ,int h)
{
	pLibFolderForm->resize(w ,h);
}
//=======================================================================

bool	ExeSelectLibFolderDialog(int LibType ,LayersBase * base, QWidget *parent
								 ,int	&RetSelectedLibFolderID
								 ,QString &RetSelectedFolderName)
{
	SelectLibFolderDialog	D(LibType,base,parent);
	if(D.exec()==(int)true){
		RetSelectedLibFolderID	=D.SelectedLibFolderID;
		RetSelectedFolderName	=D.SelectedFolderName;
		return true;
	}
	return false;
}
bool	ExeSelectLibraryForm(int LibType ,LayersBase * base, QWidget *parent
								 ,int	&RetSelectedLibID
								 ,QString &RetSelectedLibName)
{
	SelectLibraryForm	*s=new SelectLibraryForm(LibType,base,NULL);
	GeneralDialog	D(base,s,parent);
	D.exec();
	RetSelectedLibID	=s->SelectedLibID;
	RetSelectedLibName	=s->SelectedLibName;
	if(RetSelectedLibID>=0){
		return true;
	}
	return false;
}

bool	ExeSelectPhasePageLayerDialog(LayersBase *base
									,int &RetSelectPhase
									,int &RetSelectPage
									,int &RetSelectLayer)
{
	SelectPhasePageLayerDialog	D(base,NULL);
	if(D.exec()==(int)true){
		RetSelectPhase	=D.SelectPhase;
		RetSelectPage	=D.SelectPage;
		RetSelectLayer	=D.SelectLayer;
		return true;
	}
	return false;
}