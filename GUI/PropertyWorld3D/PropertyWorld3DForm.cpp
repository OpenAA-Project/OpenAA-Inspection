#include "PropertyWorld3DForm.h"
#include "ui_PropertyWorld3DForm.h"
#include "XPropertyWorld3DPacket.h"

extern	const	char	*sRoot;
extern	const	char	*sName;


PropertyWorld3DForm::PropertyWorld3DForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::PropertyWorld3DForm)
{
    ui->setupUi(this);
}

PropertyWorld3DForm::~PropertyWorld3DForm()
{
    delete ui;
}

World3DBase	*PropertyWorld3DForm::GetWorld3DBase(void)
{
	return (World3DBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"World3D");
}

void PropertyWorld3DForm::on_pushButtonAddStepFile_clicked()
{
    QString FileName=QFileDialog::getSaveFileName(NULL
                                                ,"Load step file"
                                                ,QString()
                                                ,/**/"Step file(*.step *.stp;;All files(*.*)");
    if(FileName.isEmpty()==false){
        QFile   File(FileName);
        if(File.open(QIODevice::ReadWrite)==true){
            QByteArray  FArray=File.readAll();
            for(int page=0;page<GetPageNumb();page++){
                int GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
                GUICmdLoadStepFile  RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
                RCmd.FArray=FArray;
                RCmd.Send(NULL,GlobalPage,0);
            }
        }
    }
}

