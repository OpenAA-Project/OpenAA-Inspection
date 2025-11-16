#include "PIOViewer.h"
#include "XSequence.h"
#include <QFileDialog>
#include "XDataInLayer.h"
#include "XCriticalFunc.h"
#include "ShowSignalForm.h"
#include "XPIOInterface.h"
#include "XPIOButton.h"

extern	PIOClassPack		*PIOPack;

int	MaxSignalCount=1000000;

PIOViewer::PIOViewer(LayersBase *Base ,bool StartOnDLL,const QString &StartDLL
					,QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags),ServiceForLayers(Base)
{
	ui.setupUi(this);

	OpenedPIO=NULL;
	PIOThreadPointer	=new PIOThread(this);
	ui.comboBoxPIODLL->clear();
	for(PIOClass *I=PIOPack->GetFirst();I!=NULL;I=I->GetNext()){
		ui.comboBoxPIODLL->addItem(I->GetFileName());
	}
	int	Index=-1;
	if(PIOPack->GetCount()>0){
		Index=0;
		ui.comboBoxPIODLL->setCurrentIndex(0);
	}
	ui.lineEditIODef->setText(GetLayersBase()->GetUserPath()+QDir::separator()+QString("IODef.dat"));

	connect(PIOThreadPointer,SIGNAL(SignalShowIO()),this,SLOT(SlotShowIO()),Qt::QueuedConnection);
	PIOThreadPointer->start();
	InBitStock	=NULL;
	OutBitStock	=NULL;
	if(StartOnDLL==true){
		if(StartDLL.isEmpty()==false){
			QString	LStartDLL=StartDLL.toLower();
			int	row=0;
			for(PIOClass *I=PIOPack->GetFirst();I!=NULL;I=I->GetNext(),row++){
				QString	LDriverDLL=I->GetFileName().toLower();
				if(LDriverDLL.contains(LStartDLL)==true){
					ui.comboBoxPIODLL->setCurrentIndex(row);
					Index=row;
				}
			}
		}
		if(Index>=0){
			on_pushButtonOpenPIO_clicked();
		}
	}
}

PIOViewer::~PIOViewer()
{
	if(InBitStock!=NULL){
		delete	[]InBitStock;
		InBitStock=NULL;
	}
	if(OutBitStock!=NULL){
		delete	[]OutBitStock;
		OutBitStock=NULL;
	}
}

void PIOViewer::on_pbClose_clicked()
{
	close();
}

void	PIOViewer::closeEvent(QCloseEvent *ev)
{
	if(PIOThreadPointer!=NULL){
		PIOThreadPointer->terminate();
		PIOThreadPointer->ShouldFinish=true;
		PIOThreadPointer->wait(1000);
		PIOThreadPointer->deleteLater();
	}
	if(OpenedPIO!=NULL){
		delete	OpenedPIO;
		OpenedPIO=NULL;
	}
}

void PIOViewer::on_pushButtonSelectIODefineFile_clicked()
{
	QString FileName=QFileDialog::getOpenFileName ( 0, "Select IODef file", QString(), "Dat file (*.dat);;All files (*.*)");
	if(FileName.isEmpty()==false){
		ui.lineEditIODef->setText(FileName);
	}
}

void PIOViewer::on_pushButtonOpenPIO_clicked()
{
	int	Row=ui.comboBoxPIODLL->currentIndex();
	if(Row<0)
		return;
	PIOClass *I=PIOPack->GetItem(Row);
	if(I==NULL)
		return;

	OpenedPIO=I;
	while((I=PIOPack->GetFirst())!=NULL){
		PIOPack->RemoveList(I);
		if(OpenedPIO!=I){
			delete	I;
		}
	}
	PIOPack->AppendList(OpenedPIO);

	QString	IODefFileName=ui.lineEditIODef->text();
	OpenedPIO->ReadDefFileOfBoardName(IODefFileName);
	QString	Something=ui.lineEditParameter->text();
	OpenedPIO->Initialize(this,/**/"",false,Something);
	OpenedPIO->ReadDefFile(IODefFileName,false);

	ui.comboBoxBoardNumber->clear();
	int	N=OpenedPIO->GetBoardCount();
	for(int i=0;i<N;i++){
		ui.comboBoxBoardNumber->addItem(QString::number(i));
	}

	ui.comboBoxPIODLL	->setEnabled(false);
	ui.lineEditIODef	->setEnabled(false);
	ui.pushButtonOpenPIO->setEnabled(false);

	ui.pushButtonSelectIODefineFile	->setEnabled(false);
	on_chkEchoBack_clicked();
}

void PIOViewer::on_pushButtonShowSignal_clicked()
{
	ShowSignalForm	SigForm(this);
	SigForm.exec();
}

void PIOViewer::on_chkEchoBack_clicked()
{
	if(OpenedPIO==NULL){
		return;
	}
	int	BoardNumber=ui.comboBoxBoardNumber->currentIndex();
	if(BoardNumber<0){
		return;
	}
	int	OutBitCount	=OpenedPIO->GetPIOBrd(BoardNumber)->GetIOOutBitCount();

	if(ui.chkEchoBack->isChecked()==true){
		QPalette palette=ui.twOUT->palette();
		palette.setColor(QPalette::Base,QColor(Qt::cyan));
		ui.twOUT->setPalette(palette);

		for(int i=0;i<OutBitCount;i++){
			QTableWidgetItem *itemOUT=ui.twOUT->item(i,0);
			if(itemOUT!=NULL){
				itemOUT->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			}
		}
	}
	else{
		QPalette palette=ui.twOUT->palette();
		palette.setColor(QPalette::Base,QColor(Qt::white));
		ui.twOUT->setPalette(palette);

		for(int i=0;i<OutBitCount;i++){
			QTableWidgetItem *itemOUT=ui.twOUT->item(i,0);
			if(itemOUT!=NULL){
				itemOUT->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
			}
		}
	}
}

void PIOViewer::on_comboBoxBoardNumber_currentIndexChanged(int index)
{
	if(OpenedPIO==NULL){
		return;
	}
	int	BoardNumber=ui.comboBoxBoardNumber->currentIndex();
	if(BoardNumber<0){
		return;
	}

	int	InBitCount	=OpenedPIO->GetPIOBrd(BoardNumber)->GetIOInBitCount();
	int	OutBitCount	=OpenedPIO->GetPIOBrd(BoardNumber)->GetIOOutBitCount();
	ui.twIN		->setRowCount(InBitCount);
	ui.twIN		->setColumnCount(1);
	ui.twIN		->setColumnWidth(0,200);

	ui.twOUT	->setRowCount(OutBitCount);
	ui.twOUT	->setColumnCount(1);
	ui.twOUT	->setColumnWidth(0,200);

	if(InBitStock!=NULL){
		delete	[]InBitStock;
		InBitStock=NULL;
	}
	if(OutBitStock!=NULL){
		delete	[]OutBitStock;
		OutBitStock=NULL;
	}
	StartMilisec	=GetComputerMiliSec();
	InBitStock	=new SignalData[InBitCount];
	OutBitStock	=new SignalData[OutBitCount];
	for(int i=0;i<InBitCount;i++){
		InBitStock[i].Alloc(MaxSignalCount);
	}
	for(int i=0;i<OutBitCount;i++){
		OutBitStock[i].Alloc(MaxSignalCount);
	}

	for(int i=0;i<InBitCount;i++){
		QTableWidgetItem *itemIN=new QTableWidgetItem(OpenedPIO->GetInBitName(BoardNumber,i));
		itemIN->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		ui.twIN->setItem(i,0,itemIN);
		itemIN->setCheckState(Qt::Unchecked);
		ui.twIN->verticalHeader()->resizeSection(i,19);
	}

	for(int i=0;i<OutBitCount;i++){
		QTableWidgetItem *itemOUT=new QTableWidgetItem(OpenedPIO->GetOutBitName(BoardNumber,i));
		itemOUT->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
		ui.twOUT->setItem(i,0,itemOUT);
		itemOUT->setCheckState(Qt::Unchecked);
		ui.twOUT->verticalHeader()->resizeSection(i,19);
	}
	ui.twIN	->setHorizontalHeaderLabels(QStringList("Input bit"));
	ui.twOUT->setHorizontalHeaderLabels(QStringList("Output bit"));

	QStringList	VInStr;
	QStringList	VOutStr;
	for(int i=0;i<InBitCount;i++){
		VInStr	+=QString("IN ")+QString::number(i);
	}
	for(int i=0;i<OutBitCount;i++){
		VOutStr	+=QString("OUT ")+QString::number(i);
	}
	ui.twIN	->setVerticalHeaderLabels(VInStr);
	ui.twOUT	->setVerticalHeaderLabels(VOutStr);	

	int		InByteCount=(InBitCount+7)/8;
	for(int i=0;i<InByteCount;i++){
		LastInByte[i]=OpenedPIO->GetByte(BoardNumber,i);
	}
	int		OutByteCount=(OutBitCount+7)/8;
	for(int i=0;i<OutByteCount;i++){
		LastOutByte[i]=OpenedPIO->GetOutByte(BoardNumber,i);
	}
	SetSignalsInData();
}

QString	PIOViewer::GetSignalInName(int BitNumber)
{
	if(OpenedPIO==NULL){
		return /**/"";
	}
	int	BoardNumber=ui.comboBoxBoardNumber->currentIndex();
	return OpenedPIO->GetInBitName(BoardNumber,BitNumber);
}

QString	PIOViewer::GetSignalOutName(int BitNumber)
{
	if(OpenedPIO==NULL){
		return /**/"";
	}
	int	BoardNumber=ui.comboBoxBoardNumber->currentIndex();
	return OpenedPIO->GetOutBitName(BoardNumber,BitNumber);
}

int		PIOViewer::GetSignalInBitCount(void)
{
	if(OpenedPIO==NULL){
		return 0;
	}
	int	BoardNumber=ui.comboBoxBoardNumber->currentIndex();
	if(BoardNumber<0){
		return 0;
	}
	int	InBitCount	=OpenedPIO->GetPIOBrd(BoardNumber)->GetIOInBitCount();
	return InBitCount;
}

int		PIOViewer::GetSignalOutBitCount(void)
{
	if(OpenedPIO==NULL){
		return 0;
	}
	int	BoardNumber=ui.comboBoxBoardNumber->currentIndex();
	if(BoardNumber<0){
		return 0;
	}
	int	OutBitCount	=OpenedPIO->GetPIOBrd(BoardNumber)->GetIOOutBitCount();
	return OutBitCount;
}
DWORD	PIOViewer::GetTotalSignalMilisec(void)
{
	if(OpenedPIO==NULL){
		return 0;
	}
	int	BoardNumber=ui.comboBoxBoardNumber->currentIndex();
	if(BoardNumber<0){
		return 0;
	}
	int	InBitCount	=OpenedPIO->GetPIOBrd(BoardNumber)->GetIOInBitCount();
	int	OutBitCount	=OpenedPIO->GetPIOBrd(BoardNumber)->GetIOOutBitCount();

	DWORD	Ret=0;
	for(int i=0;i<InBitCount;i++){
		if(InBitStock[i].GetLastMilisec()>Ret){
			Ret=InBitStock[i].GetLastMilisec();
		}
	}
	for(int i=0;i<OutBitCount;i++){
		if(OutBitStock[i].GetLastMilisec()>Ret){
			Ret=OutBitStock[i].GetLastMilisec();
		}
	}
	return Ret;
}

bool	PIOViewer::IsChangedPIO(void)
{
	if(OpenedPIO==NULL){
		return false;
	}
	int	BoardNumber=ui.comboBoxBoardNumber->currentIndex();
	if(BoardNumber<0){
		return false;
	}
	int	InBitCount	=OpenedPIO->GetPIOBrd(BoardNumber)->GetIOInBitCount();
	int	OutBitCount	=OpenedPIO->GetPIOBrd(BoardNumber)->GetIOOutBitCount();

	BYTE	tmpLastInByte[64];
	BYTE	tmpLastOutByte[64];

	int		InByteCount=(InBitCount+7)/8;
	for(int i=0;i<InByteCount;i++){
		tmpLastInByte[i]=OpenedPIO->GetByte(BoardNumber,i);
	}
	int		OutByteCount=(OutBitCount+7)/8;
	for(int i=0;i<OutByteCount;i++){
		tmpLastOutByte[i]=OpenedPIO->GetEchobackOutByte(BoardNumber,i);
	}
	bool	Changed=false;
	for(int i=0;i<InByteCount;i++){
		if(tmpLastInByte[i]!=LastInByte[i]){
			Changed=true;
			break;
		}
	}
	if(Changed==false){
		for(int i=0;i<OutByteCount;i++){
			if(tmpLastOutByte[i]!=LastOutByte[i]){
				Changed=true;
				break;
			}
		}
	}
	SetSignalsInData();

	if(Changed==true){
		for(int i=0;i<InByteCount;i++){
			LastInByte[i]=tmpLastInByte[i];
		}
		for(int i=0;i<OutByteCount;i++){
			LastOutByte[i]=tmpLastOutByte[i];
		}
		return true;
	}
	return false;
}
void	PIOViewer::SetSignalsInData(void)
{
	if(OpenedPIO==NULL){
		return;
	}
	if(InBitStock==NULL)
		return;
	int	BoardNumber=ui.comboBoxBoardNumber->currentIndex();
	if(BoardNumber<0){
		return;
	}
	int	InBitCount	=OpenedPIO->GetPIOBrd(BoardNumber)->GetIOInBitCount();
	int	OutBitCount	=OpenedPIO->GetPIOBrd(BoardNumber)->GetIOOutBitCount();

	BYTE	tmpLastInByte[64];
	BYTE	tmpLastOutByte[64];

	int		InByteCount=(InBitCount+7)/8;
	for(int i=0;i<InByteCount;i++){
		tmpLastInByte[i]=OpenedPIO->GetByte(BoardNumber,i);
	}
	int		OutByteCount=(OutBitCount+7)/8;
	for(int i=0;i<OutByteCount;i++){
		tmpLastOutByte[i]=OpenedPIO->GetEchobackOutByte(BoardNumber,i);
	}

	DWORD	CurrentMilisec=GetComputerMiliSec();
	for(int i=0;i<InBitCount;i++){
		int	BIndex=i>>3;
		int	BMask=1<<(i&7);
		if((tmpLastInByte[BIndex] & BMask)!=(LastInByte[BIndex] & BMask)){
			if((tmpLastInByte[BIndex] & BMask)!=0){
				InBitStock[i].Set(CurrentMilisec-StartMilisec,true);
			}
			else{
				InBitStock[i].Set(CurrentMilisec-StartMilisec,false);
			}
		}
	}
	for(int i=0;i<OutBitCount;i++){
		int	BIndex=i>>3;
		int	BMask=1<<(i&7);
		if((tmpLastOutByte[BIndex] & BMask)!=(LastOutByte[BIndex] & BMask)){
			if((tmpLastOutByte[BIndex] & BMask)!=0){
				OutBitStock[i].Set(CurrentMilisec-StartMilisec,true);
			}
			else{
				OutBitStock[i].Set(CurrentMilisec-StartMilisec,false);
			}
		}
	}
}

SignalData	*PIOViewer::GetSignal(bool InData,int BitNumber)
{
	if(InData==true){
		return &InBitStock[BitNumber];
	}
	else{
		return &OutBitStock[BitNumber];
	}
}

void	PIOViewer::SlotShowIO()
{
	if(OpenedPIO==NULL){
		return;
	}
	int	BoardNumber=ui.comboBoxBoardNumber->currentIndex();
	if(BoardNumber<0){
		return;
	}
	int	InBitCount	=OpenedPIO->GetPIOBrd(BoardNumber)->GetIOInBitCount();

	for(int i=0;i<InBitCount;i++){
		QTableWidgetItem *itemIN=ui.twIN->item(i,0);
		if(OpenedPIO->GetBit(BoardNumber,i>>3,i&7)==0){
			itemIN->setCheckState(Qt::Unchecked);
		}
		else{
			itemIN->setCheckState(Qt::Checked);
		}
	}
	if(ui.chkEchoBack->isChecked()==true){
		int	OutBitCount	=OpenedPIO->GetPIOBrd(BoardNumber)->GetIOOutBitCount();
		for(int i=0;i<OutBitCount;i++){
			QTableWidgetItem *itemOUT=ui.twOUT->item(i,0);
			if(OpenedPIO->GetEchobackOutBit(BoardNumber,i)==0){
				itemOUT->setCheckState(Qt::Unchecked);
			}
			else{
				itemOUT->setCheckState(Qt::Checked);
			}
		}
	}
}
void PIOViewer::on_twOUT_itemChanged(QTableWidgetItem *item)
{
	if(OpenedPIO==NULL){
		return;
	}
	if(ui.chkEchoBack->isChecked()==false){
		int	BoardNumber=ui.comboBoxBoardNumber->currentIndex();
		if(BoardNumber<0){
			return;
		}
		int	OutBitCount	=OpenedPIO->GetPIOBrd(BoardNumber)->GetIOOutBitCount();
		for(int i=0;i<OutBitCount;i++){
			QTableWidgetItem	*d=ui.twOUT->item(i,0);
			if(d!=NULL){
				if(d->checkState ()==Qt::Checked){
					OpenedPIO->SetBit(BoardNumber,i>>3,i&7,1);
				}
				else{
					OpenedPIO->SetBit(BoardNumber,i>>3,i&7,0);
				}
			}
		}
	}
}
void PIOViewer::on_pushButtonSaveSignal_clicked()
{
	if(OpenedPIO==NULL){
		return;
	}
	QString FileName=QFileDialog::getSaveFileName ( 0, "Save signal datas", QString(), "Signal file (*.sgn);;All files (*.*)");
	if(FileName.isEmpty()==false){
		QFile	File(FileName);
		if(File.open(QIODevice::WriteOnly)==true){
			SaveSignal(&File);
		}
	}
}

void PIOViewer::on_pushButtonLoadSignal_clicked()
{
	QString FileName=QFileDialog::getOpenFileName ( 0, "Load signal datas", QString(), "Signal file (*.sgn);;All files (*.*)");
	if(FileName.isEmpty()==false){
		QFile	File(FileName);
		if(File.open(QIODevice::ReadOnly)==true){
			LoadSignal(&File);
		}
	}
}
void PIOViewer::on_pushButtonClear_clicked()
{
	if(OpenedPIO==NULL){
		return;
	}
	int	BoardNumber=ui.comboBoxBoardNumber->currentIndex();
	if(BoardNumber<0){
		return;
	}

	int	InBitCount	=OpenedPIO->GetPIOBrd(BoardNumber)->GetIOInBitCount();
	int	OutBitCount	=OpenedPIO->GetPIOBrd(BoardNumber)->GetIOOutBitCount();

	PIOThreadPointer->HaltOn=true;
	GSleep(100);
	for(int i=0;i<InBitCount;i++){
		InBitStock[i].Reset();
	}
	for(int i=0;i<OutBitCount;i++){
		OutBitStock[i].Reset();
	}
	PIOThreadPointer->HaltOn=false;
}

bool	PIOViewer::SaveSignal(QIODevice *f)
{
	if(OpenedPIO==NULL){
		return false;
	}
	int	BoardNumber=ui.comboBoxBoardNumber->currentIndex();
	if(BoardNumber<0){
		return false;
	}

	int	InBitCount	=OpenedPIO->GetPIOBrd(BoardNumber)->GetIOInBitCount();
	int	OutBitCount	=OpenedPIO->GetPIOBrd(BoardNumber)->GetIOOutBitCount();

	if(::Save(f,BoardNumber)==false)
		return false;
	if(::Save(f,InBitCount)==false)
		return false;
	if(::Save(f,OutBitCount)==false)
		return false;
	for(int i=0;i<InBitCount;i++){
		if(InBitStock[i].Save(f)==false)
			return false;
	}
	for(int i=0;i<OutBitCount;i++){
		if(OutBitStock[i].Save(f)==false)
			return false;
	}
	return true;
}

bool	PIOViewer::LoadSignal(QIODevice *f)
{
	if(OpenedPIO==NULL){
		return false;
	}
	int	BoardNumber=ui.comboBoxBoardNumber->currentIndex();
	if(BoardNumber<0){
		return false;
	}

	int	InBitCount	=OpenedPIO->GetPIOBrd(BoardNumber)->GetIOInBitCount();
	int	OutBitCount	=OpenedPIO->GetPIOBrd(BoardNumber)->GetIOOutBitCount();

	int	iInBitCount;
	int	iOutBitCount;
	if(::Load(f,BoardNumber)==false)
		return false;
	if(::Load(f,iInBitCount)==false)
		return false;
	if(::Load(f,iOutBitCount)==false)
		return false;

	for(int i=0;i<InBitCount && i<iInBitCount;i++){
		if(InBitStock[i].Load(f)==false)
			return false;
	}
	for(int i=0;i<OutBitCount && i<iOutBitCount;i++){
		if(OutBitStock[i].Load(f)==false)
			return false;
	}
	return true;
}

//=========================================================================================
PIOThread::PIOThread(PIOViewer *parent)
{
	Parent=parent;
	ShouldFinish=false;
	HaltOn	=false;
}

void PIOThread::run()
{
	GSleep(2000);
	emit	SignalShowIO();
	while(ShouldFinish==false){
		if(Parent->IsChangedPIO()==true){
			emit	SignalShowIO();
		}
		msleep(1);
		while(HaltOn==true){
			msleep(100);
		}
	}
}


