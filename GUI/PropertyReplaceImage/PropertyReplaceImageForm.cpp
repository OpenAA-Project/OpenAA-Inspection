#include "PropertyReplaceImageForm.h"
#include "ui_PropertyReplaceImageForm.h"
#include "XPropertyReplaceImagePacket.h"
#include "XDataInLayer.h"

extern  const	char	*sRoot;
extern  const	char	*sName;

PropertyReplaceImageForm::PropertyReplaceImageForm(LayersBase *Base,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::PropertyReplaceImageForm)
{
    ui->setupUi(this);
}

PropertyReplaceImageForm::~PropertyReplaceImageForm()
{
    delete ui;
}

void PropertyReplaceImageForm::on_toolButtonViewMask_clicked()
{

}

void	PropertyReplaceImageForm::TransmitDirectly(GUIDirectMessage *packet)
{
    CmdReplaceImageDrawAttr *CmdReplaceImageDrawAttrVar=dynamic_cast<CmdReplaceImageDrawAttr *>(packet);
    if(CmdReplaceImageDrawAttrVar!=NULL){
        CmdReplaceImageDrawAttrVar->ShowIsoMask=ui->toolButtonViewMask->isChecked();
        return;
    }


}
void	PropertyReplaceImageForm::BuildForShow(void)
{
}
void	PropertyReplaceImageForm::StartPage	(void)
{
}
