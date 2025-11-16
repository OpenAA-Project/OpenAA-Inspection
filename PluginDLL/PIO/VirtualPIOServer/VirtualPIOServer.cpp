#include "VirtualPIOServer.h"
#include "XGeneralFunc.h"

VirtualPIOServer::VirtualPIOServer(int PortNumber ,QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags)
	,Server(this),DirectAccessServer(&Server)
{
	ui.setupUi(this);

	Server.StartServer(PortNumber);
	connect(&Server,SIGNAL(SignalStructureChanged()),this,SLOT(SlotStructureChanged()),Qt::QueuedConnection);

	DirectAccessServer.InitialServer();

	Timer.setSingleShot(false);
	Timer.setInterval(100);
	connect(&Timer,SIGNAL(timeout()),this,SLOT(SlotTimeout()));
	Timer.start();

	DirectAccessTimer.setSingleShot(false);
	DirectAccessTimer.setInterval(2);
	connect(&DirectAccessTimer,SIGNAL(timeout()),this,SLOT(SlotDirectAccessTimeout()));
	DirectAccessTimer.start();

	ui.tableWidgetIntegrated->setColumnWidth(0,140);
	ui.tableWidgetIntegrated->setColumnWidth(1,200);
	ui.tableWidgetIntegrated->setColumnWidth(2,48);

	ui.tableWidgetOut->setColumnWidth(0,48);
	ui.tableWidgetOut->setColumnWidth(1,160);
	ui.tableWidgetIn->setColumnWidth(0,48);
	ui.tableWidgetIn->setColumnWidth(1,160);
}

VirtualPIOServer::~VirtualPIOServer()
{

}



void	VirtualPIOServer::SlotTimeout()
{
	if(ui.tableWidgetIntegrated	->rowCount()!=Server.IOBitsToShow.GetCount()){
		SlotStructureChanged();
	}
	int	Row=0;
	for(BindedIOBit *a=Server.IOBitsToShow.GetFirst();a!=NULL;a=a->GetNext(),Row++){
		if(a->BitOut!=NULL)
			::SetDataToTable(ui.tableWidgetIntegrated,2 ,Row ,QString::number(a->BitOut->BitPoint->CurrentOutput));
		else
			::SetDataToTable(ui.tableWidgetIntegrated,2 ,Row ,QString("-"));
	}
	int	R=ui.listWidgetClientList->currentRow();
	if(R>=0){
		AllocatedClient *c=Server[R];
		if(c!=NULL){
			if(ui.tableWidgetOut->rowCount()==c->GetBitCountOut()){
				Row=0;
				for(ClientBitPort *m=c->BitPorts.GetFirst();m!=NULL;m=m->GetNext()){
					if(m->Output==true){
						::SetDataToTable(ui.tableWidgetOut,0 ,Row ,QString::number(m->BitNumber));
						::SetDataToTable(ui.tableWidgetOut,1 ,Row ,m->BitName);
						::SetDataToTable(ui.tableWidgetOut,2 ,Row ,QString::number(m->CurrentOutput));
						Row++;
					}
				}
			}
			if(ui.tableWidgetIn->rowCount()==c->GetBitCountIn()){
				Row=0;
				for(ClientBitPort *m=c->BitPorts.GetFirst();m!=NULL;m=m->GetNext()){
					if(m->Output==false){
						::SetDataToTable(ui.tableWidgetIn,0 ,Row ,QString::number(m->BitNumber));
						::SetDataToTable(ui.tableWidgetIn,1 ,Row ,m->BitName);
						ClientBitPort	*h=Server.SearchOutputBit(m->BitName);
						if(h!=NULL)
							::SetDataToTable(ui.tableWidgetIn,2 ,Row ,QString::number(h->CurrentOutput));
						else
							::SetDataToTable(ui.tableWidgetIn,2 ,Row ,QString("--"));
						Row++;
					}
				}
			}
		}
	}
}
void	VirtualPIOServer::SlotDirectAccessTimeout()
{
	DirectAccessServer.PollingInServer();
}
void	VirtualPIOServer::SlotStructureChanged()
{
	ui.tableWidgetIntegrated	->setRowCount(Server.IOBitsToShow.GetCount());
	int	Row=0;
	for(BindedIOBit *a=Server.IOBitsToShow.GetFirst();a!=NULL;a=a->GetNext(),Row++){
		if(a->BitOut!=NULL)
			::SetDataToTable(ui.tableWidgetIntegrated,0 ,Row ,a->BitOut->ClientPoint->ClientID + QString(":")+QString::number(a->BitOut->ClientPoint->ClientPortNumber));
		else
			::SetDataToTable(ui.tableWidgetIntegrated,0 ,Row ,QString("No output data"));

		if(a->BitOut!=NULL)
			::SetDataToTable(ui.tableWidgetIntegrated,1 ,Row ,a->BitOut->BitPoint->BitName);
		else if(a->BitIn.GetFirst()!=NULL)
			::SetDataToTable(ui.tableWidgetIntegrated,1 ,Row ,a->BitIn.GetFirst()->BitPoint->BitName);
	}

	ui.listWidgetClientList->clear();
	for(AllocatedClient *c=Server.GetFirst();c!=NULL;c=c->GetNext()){
		ui.listWidgetClientList->addItem(c->ClientIP);
	}
}

void VirtualPIOServer::on_listWidgetClientList_clicked(const QModelIndex &index)
{
	int	R=ui.listWidgetClientList->currentRow();
	if(R>=0){
		AllocatedClient *c=Server[R];
		if(c!=NULL){
			ui.tableWidgetOut	->setRowCount(c->GetBitCountOut());
			ui.tableWidgetIn	->setRowCount(c->GetBitCountIn());
		}
	}
}
