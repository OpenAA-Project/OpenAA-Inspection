#include "VirtualPIOClient.h"
#include "XGeneralFunc.h"

VirtualPIOClient::VirtualPIOClient(const QString &IPAddress,int PortNumber
								 , const QString &AccessMemoryName ,QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags)
	,Adapter(this,IPAddress,PortNumber,AccessMemoryName)
{
	ui.setupUi(this);

	ui.tableWidgetPortBitsIn	->setColumnWidth(0,32);
	ui.tableWidgetPortBitsIn	->setColumnWidth(1,100);
	ui.tableWidgetPortBitsIn	->setColumnWidth(2,32);

	ui.tableWidgetPortBitsOut	->setColumnWidth(0,32);
	ui.tableWidgetPortBitsOut	->setColumnWidth(1,100);
	ui.tableWidgetPortBitsOut	->setColumnWidth(2,32);

	setWindowTitle(AccessMemoryName);
	minimizeAction	=new QAction(/**/"Minimize",this);
	connect(minimizeAction	,SIGNAL(triggered()),this,SLOT(hide()));
	showAction		=new QAction(/**/"Normalize VirtualPIOClient",this);
	connect(showAction		,SIGNAL(triggered()),this,SLOT(showNormal()));
	quitAction		=new QAction(/**/"quit",this);
	connect(quitAction		,SIGNAL(triggered()),qApp,SLOT(quit()));

	TrayIconMenu=new QMenu(this);
	TrayIconMenu->addAction(minimizeAction);
	TrayIconMenu->addAction(showAction);
	TrayIconMenu->addAction(quitAction);

	TrayIcon	=new QSystemTrayIcon(this);
	TrayIcon->setContextMenu(TrayIconMenu);
	TrayIcon->setIcon(QIcon(QPixmap(/**/":Resources/VirtualPIOClient.png")));
	TrayIcon->show();

	TM.setInterval(2000);
	TM.setSingleShot(false);
	connect(&TM,SIGNAL(timeout()),this,SLOT(SlotTimeOut()));
	FirstTimeOut	=false;
	TM.start();

	CommOpe.setInterval(100);
	CommOpe.setSingleShot(false);
	connect(&CommOpe,SIGNAL(timeout()),this,SLOT(SlotTimeOutComm()));
	CommOpe.start();

}

VirtualPIOClient::~VirtualPIOClient()
{
}


void	VirtualPIOClient::ShowGrid(void)
{
	int	AdapterNumb=1;
	ui.tableWidget->setRowCount(AdapterNumb);
	for(int row=0;row<AdapterNumb;row++){
		::SetDataToTable(ui.tableWidget ,0,row ,Adapter.ServerIPAddress);
		::SetDataToTable(ui.tableWidget ,1,row ,QString::number(Adapter.ServerPortNumber));
	}
}
void	VirtualPIOClient::SlotTimeOut()
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true)
		return;
	ReEntrant=true;

	if(FirstTimeOut==false){
		hide();
		FirstTimeOut=true;
		TM.setInterval(1);
	}
	Adapter.MemMapOperator();

	ShowGrid();
	ReEntrant=false;
}

void	VirtualPIOClient::closeEvent(QCloseEvent *ev)
{
	if(TrayIcon->isVisible()==true){
		hide();
		ev->ignore();
	}
}

void	VirtualPIOClient::SlotTimeOutComm()
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true)
		return;
	ReEntrant=true;

	bool	Ret1=Adapter.CommGetBitInDataStream();
	bool	Ret2=Adapter.CommSetBitOutDataStream();

	if(Ret1==true && Ret2==true){
		QPalette	P=palette();
		P.setColor(QPalette::Window,Qt::green);
		setPalette(P);
	}
	else{
		QPalette	P=palette();
		P.setColor(QPalette::Window,Qt::red);
		setPalette(P);
	}

	int	CountIn	=Adapter.PortBitsIn.GetCount();
	int	CountOut=Adapter.PortBitsOut.GetCount();
	ui.tableWidgetPortBitsIn	->setRowCount(CountIn);
	ui.tableWidgetPortBitsOut	->setRowCount(CountOut);

	int	n=0;
	for(PortBit *p=Adapter.PortBitsIn.GetFirst();p!=NULL;p=p->GetNext()){
		::SetDataToTable(ui.tableWidgetPortBitsIn ,0 ,n ,QString::number(p->BitNumber));
		::SetDataToTable(ui.tableWidgetPortBitsIn ,1 ,n ,p->BitName);
		::SetDataToTable(ui.tableWidgetPortBitsIn ,2 ,n ,QString::number(p->CurrentData));
		n++;
	}
	n=0;
	for(PortBit *p=Adapter.PortBitsOut.GetFirst();p!=NULL;p=p->GetNext()){
		::SetDataToTable(ui.tableWidgetPortBitsOut ,0 ,n ,QString::number(p->BitNumber));
		::SetDataToTable(ui.tableWidgetPortBitsOut ,1 ,n ,p->BitName);
		int	d=Adapter.GetBitOutData(p->BitNumber);
		::SetDataToTable(ui.tableWidgetPortBitsOut ,2 ,n ,QString::number(d));
		n++;
	}
	int	v=ui.progressBar->value();
	v++;
	if(ui.progressBar->maximum()<=v)
		v=0;
	ui.progressBar->setValue(v);

	ReEntrant=false;
}