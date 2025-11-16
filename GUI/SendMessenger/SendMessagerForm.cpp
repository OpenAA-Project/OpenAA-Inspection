#include "sendmessagerResource.h"
#include "SendMessagerForm.h"
#include "XDataInLayer.h"

SendMessagerForm::SendMessagerForm(LayersBase *Base ,QWidget *parent)
	: GUIFormBase(Base,parent),MClient(this)
{
	ui.setupUi(this);
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		QVariant	v(GlobalPage);
		ui.comboBoxPage->addItem(QString(/**/"Page ")+QString::number(GlobalPage),v);
	}
	IPAddress=/**/"localhost";
	GetParamGUI()->SetParam(&IPAddress, /**/"SendMessager",/**/"IPAddress"		,LangSolver.GetString(SendMessagerForm_LS,LID_0)/*"Messager\'s IP Address"*/		);
}

SendMessagerForm::~SendMessagerForm()
{
}

void	SendMessagerForm::Prepare(void)
{
	MClient.Start();
	MClient.Initial(IPAddress);
}
void SendMessagerForm::on_pushButtonSend_clicked()
{
	int	r=ui.comboBoxPage->currentIndex();
	if(r>=0){
		int	GlobalPage=ui.comboBoxPage->itemData(r).toInt();
		QString	Message=ui.lineEditMessage->text();
		MClient.Send(1,GlobalPage,Message);
	}
}