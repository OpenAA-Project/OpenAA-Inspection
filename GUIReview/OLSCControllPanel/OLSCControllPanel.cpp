#include "OLSCControllPanelResource.h"
#include "OLSCControllPanel.h"
#include "../XGUIReviewGlobal.h"
#include "XReviewStructure.h"
#include "ReviewStructurePacket.h"
#include "../XGUIReviewCommonPacket.h"
#include "XSequenceRepairLocal.h"
#include "XAutofocusControl.h"



static	char	*sRoot=/**/"Review";
static	char	*sName=/**/"OLSCControllPanel";


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Export Functions
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"OLSC Crontroll panel.");
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	OLSCControllPanel *form = new OLSCControllPanel(Base,parent);
	return form;
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);

	return true;
}

DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<1)
		return(-1);

	Data[0].Type				 =/**/"QString";
	Data[0].VariableNameWithRoute=/**/"CommPortName";
	Data[0].Pointer				 =&((OLSCControllPanel *)Instance)->COMMName;
	
	Data[1].Type				 =/**/"QString";
	Data[1].VariableNameWithRoute=/**/"Port1Name";
	Data[1].Pointer				 =&((OLSCControllPanel *)Instance)->Port1Name;
	
	Data[2].Type				 =/**/"QString";
	Data[2].VariableNameWithRoute=/**/"Port2Name";
	Data[2].Pointer				 =&((OLSCControllPanel *)Instance)->Port2Name;
	
	Data[3].Type				 =/**/"QString";
	Data[3].VariableNameWithRoute=/**/"Port3Name";
	Data[3].Pointer				 =&((OLSCControllPanel *)Instance)->Port3Name;
	
	Data[4].Type				 =/**/"QString";
	Data[4].VariableNameWithRoute=/**/"Port4Name";
	Data[4].Pointer				 =&((OLSCControllPanel *)Instance)->Port4Name;
	
	Data[5].Type				 =/**/"bool";
	Data[5].VariableNameWithRoute=/**/"ShowCOMInfo";
	Data[5].Pointer				 =&((OLSCControllPanel *)Instance)->ShowCOMInfo;

	Data[6].Type				 =/**/"bool";
	Data[6].VariableNameWithRoute=/**/"ShowGetState";
	Data[6].Pointer				 =&((OLSCControllPanel *)Instance)->ShowGetState;

	Data[7].Type				 =/**/"bool";
	Data[7].VariableNameWithRoute=/**/"ShowStopAndPulseMove";
	Data[7].Pointer				 =&((OLSCControllPanel *)Instance)->ShowStopAndPulseMove;

	Data[8].Type				 =/**/"bool";
	Data[8].VariableNameWithRoute=/**/"ShowJogMove";
	Data[8].Pointer				 =&((OLSCControllPanel *)Instance)->ShowJogMove;
	
	Data[9].Type				 =/**/"bool";
	Data[9].VariableNameWithRoute=/**/"ShowHomeAndPortMove";
	Data[9].Pointer				 =&((OLSCControllPanel *)Instance)->ShowHomeAndPortMove;

	Data[10].Type				 =/**/"int32";
	Data[10].VariableNameWithRoute=/**/"SysSHomeNo";
	Data[10].Pointer				 =&((OLSCControllPanel *)Instance)->SysSHomeNo;
	
	Data[11].Type				 =/**/"int32";
	Data[11].VariableNameWithRoute=/**/"SysSMovePortNo";
	Data[11].Pointer				 =&((OLSCControllPanel *)Instance)->SysSMovePortNo;
	
	Data[12].Type				 =/**/"int32";
	Data[12].VariableNameWithRoute=/**/"SysPStopNo";
	Data[12].Pointer				 =&((OLSCControllPanel *)Instance)->SysPStopNo;

	return(13);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/OLSCControllPanel.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ButtonToShowTotalNGMap
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

OLSCControllPanel::OLSCControllPanel(LayersBase *Base,QWidget *parent)
	:GUIFormBase(Base, parent),sio(NULL),derimita(QString(/**/"%1%2").arg(QChar(0x0D)).arg(QChar(0x0A)))
{
	
	COMMName = QString();
	Port1Name = QString();
	Port2Name = QString();
	Port3Name = QString();
	Port4Name = QString();

	ShowCOMInfo = true;
	ShowGetState = true;
	ShowStopAndPulseMove = true;
	ShowJogMove = true;
	ShowHomeAndPortMove = true;
	ZoomRate	=5;

	m_initializedPortValue = false;
	m_port1 = 0;
	m_port2 = 0;
	m_port3 = 0;
	m_port4 = 0;

	ZoomRate1=5;
	ZoomRate2=20;
	ZoomRate3=50;
	ZoomRate4=100;

	ui.setupUi(this);

	SysSHomeNo = -1;
	SysSMovePortNo = -1;
	SysPStopNo = -1;

	ioHome = NULL;
	ioMovePort = NULL;
	ioStopNo = NULL;
}

OLSCControllPanel::~OLSCControllPanel()
{

}

void hiddenLayerChild(QLayout *layout, bool hidden){
	for(int i=0; i<layout->count(); i++){
		if(layout->itemAt(i)->widget()!=NULL){
			layout->itemAt(i)->widget()->setHidden(hidden);
		}
	}
}

void OLSCControllPanel::Prepare()
{
	if(GetEditMode()==false && COMMName.isEmpty()==false){
		ui.leCOMName->setText(COMMName);
		update();
		on_pbCOMOpen_clicked();
	}

	QString name;
	if(Port1Name.isEmpty()==true){
		name = /**/"Port1";
	}else{
		name = Port1Name;
	}
	ui.pbMoveToPort1->setText(name);

	if(Port2Name.isEmpty()==true){
		name = /**/"Port2";
	}else{
		name = Port2Name;
	}
	ui.pbMoveToPort2->setText(name);

	if(Port3Name.isEmpty()==true){
		name = /**/"Port3";
	}else{
		name = Port3Name;
	}
	ui.pbMoveToPort3->setText(name);

	if(Port4Name.isEmpty()==true){
		name = /**/"Port4";
	}else{
		name = Port4Name;
	}
	ui.pbMoveToPort4->setText(name);

	ui.frmCOMInfo->setShown(ShowCOMInfo);
	ui.frmGetState->setShown(ShowGetState);
	ui.frmStopAndPulseMove->setShown(ShowStopAndPulseMove);
	ui.frmJogMove->setShown(ShowJogMove);
	ui.frmHomeAndPortMove->setShown(ShowHomeAndPortMove);

	if(GetEditMode()==false){
		if(GetLayersBase()->GetInsideLearningEditor()==false 
		&& GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL){
			SeqControlParam	*Param=(SeqControlParam *)GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetSeqParam();
			if(Param!=NULL){
				if(SysSHomeNo>0){
					ioHome		=new SignalOperandInt(this,SysSHomeNo,/**/"OLSCControllPanel:ioHome");
					connect(ioHome			,SIGNAL(changed())	,this	,SLOT(OperandChangedHome()));
					Param->SetSpecialOperand(ioHome);
				}
				if(SysSMovePortNo>0){
					ioMovePort		=new SignalOperandInt(this,SysSMovePortNo,/**/"OLSCControllPanel:ioMovePort");
					connect(ioMovePort			,SIGNAL(changed())	,this	,SLOT(OperandChangedMovePort()));
					Param->SetSpecialOperand(ioMovePort);
				}
				if(SysPStopNo>0){
					ioStopNo		=new SignalOperandBit(this,SysPStopNo,/**/"OLSCControllPanel:ioStopNo");
					connect(ioStopNo			,SIGNAL(changed())	,this	,SLOT(OperandChangedStop()));
					Param->SetSpecialOperand(ioStopNo);
				}
			}
		}
	}
}

void OLSCControllPanel::TransmitDirectly(GUIDirectMessage *packet)
{
	GUICmdReviewUpdateLocal *GUICmdReviewUpdateLocalVar = dynamic_cast<GUICmdReviewUpdateLocal *>(packet);
	if(GUICmdReviewUpdateLocalVar!=NULL){
		updateGUI();
		GUICmdReviewUpdateLocalVar->Ret = true;
		return;
	}
	CmdReqLensRange	*CmdReqLensRangeVar=dynamic_cast<CmdReqLensRange *>(packet);
	if(CmdReqLensRangeVar!=NULL){
		CmdReqLensRangeVar->ZoomRate=ZoomRate;
		return;
		/*
		CmdReqLensRangeVar->Number=searchCurrentPortPosition();
		switch(CmdReqLensRangeVar->Number){
		case 1:
			CmdReqLensRangeVar->ZoomRate=ZoomRate1;
			break;
		case 2:
			CmdReqLensRangeVar->ZoomRate=ZoomRate2;
			break;
		case 3:
			CmdReqLensRangeVar->ZoomRate=ZoomRate3;
			break;
		case 4:
			CmdReqLensRangeVar->ZoomRate=ZoomRate4;
			break;
		default:
			CmdReqLensRangeVar->ZoomRate=-1;
		}
		return;
		*/
	}
}

void OLSCControllPanel::updateGUI()
{
	GUIFormBase::update();
}

void OLSCControllPanel::paintEvent(QPaintEvent *event)
{
	GUIFormBase::paintEvent(event);

	if(GetEditMode()==false)return;

	QPainter painter(this);

	QPen pen;
	pen.setColor(QColor(Qt::black));
	pen.setWidth(1);

	QPen oldPen = painter.pen();

	painter.setPen(pen);

	QRect frect(0, 0, width(), height() );
	int w = lineWidth();
	frect.setTopLeft( QPoint(0, 0) );
	frect.setBottomRight( frect.bottomRight() - QPoint(w, w) );

	painter.drawRect( frect );

	painter.setPen(oldPen);
}

void OLSCControllPanel::ResizeAction()
{
}

void OLSCControllPanel::on_pbCOMOpen_clicked()
{
	if(ui.leCOMName->isEnabled()==false){
		if(sio!=NULL){
			delete sio;
			sio = NULL;
		}
		ui.leCOMName->setEnabled(true);
		ui.pbCOMOpen->setText(/**/"Open");
		return;
	}

	if(ui.leCOMName->text().isEmpty()==true){
		return;
	}

	QString comname = ui.leCOMName->text();

	if(sio==NULL){
		int	Character=8;
		int	Parity=2;
		int	Stopbit=1;
		int	BPS	=19200;
		char *portName;
		PortSettings portSet;

		switch(Character){
			case 5:
				portSet.DataBits=DATA_5;
				break;
			case 6:
				portSet.DataBits=DATA_6;
				break;
			case 7:
				portSet.DataBits=DATA_7;
				break;
			case 8:
				portSet.DataBits=DATA_8;
				break;
		}
		switch(Parity){
			case 0:
				portSet.Parity=PAR_NONE;
				break;
			case 1:
				portSet.Parity=PAR_ODD;
				break;
			case 2:
				portSet.Parity=PAR_EVEN;
				break;
		}
		switch(Stopbit){
			case 1:
				portSet.StopBits=STOP_1;
				break;
			case 2:
				portSet.StopBits=STOP_2;
				break;
			case 3:
				portSet.StopBits=STOP_1_5;
				break;
		}
		switch(BPS){
			case 110:
				portSet.BaudRate=BAUD110;
				break;
			case 300:
				portSet.BaudRate=BAUD300;
				break;
			case 600:
				portSet.BaudRate=BAUD600;
				break;
			case 1200:
				portSet.BaudRate=BAUD1200;
				break;
			case 2400:
				portSet.BaudRate=BAUD2400;
				break;
			case 4800:
				portSet.BaudRate=BAUD4800;
				break;
			case 9600:
				portSet.BaudRate=BAUD9600;
				break;
			case 14400:
				portSet.BaudRate=BAUD14400;
				break;
			case 19200:
				portSet.BaudRate=BAUD19200;
				break;
			case 38400:
				portSet.BaudRate=BAUD38400;
				break;
			case 56000:
				portSet.BaudRate=BAUD56000;
				break;
			case 57600:
				portSet.BaudRate=BAUD57600;
				break;
			case 115200:
				portSet.BaudRate=BAUD115200;
				break;
		}
		portSet.FlowControl=FLOW_OFF;
		portSet.Timeout_Sec=0;
		portSet.Timeout_Millisec=1;
		sio=new QextSerialPort(comname, portSet);
		sio->setDtr(true);
		sio->setRts(true);

		if(sio->open(QIODevice::ReadWrite)==false){
			QMessageBox::critical(this
								, LangSolver.GetString(OLSCControllPanel_LS,LID_0)/*"COM Open Error"*/
								, comname + LangSolver.GetString(OLSCControllPanel_LS,LID_1)/*" is not opend."*/);
			delete sio;
			sio = NULL;
			return;
		}

		sio->flush();

		QByteArray ary = (QString(/**/"?:") + QChar(0x0D) + QChar(0x0A)).toLocal8Bit().data();
		sio->write(ary);

		QElapsedTimer timer;
		timer.start();

		QString recieve;
		if(waitForDerimita(recieve)==false){
			QMessageBox::critical(this
								, LangSolver.GetString(OLSCControllPanel_LS,LID_2)/*"COM Response Error"*/
								,  LangSolver.GetString(OLSCControllPanel_LS,LID_3)/*"No response from "*/ + comname + /**/".");
			delete sio;
			sio = NULL;
			return;
		}
		
		ui.leCOMName->setEnabled(false);
		ui.pbCOMOpen->setText(LangSolver.GetString(OLSCControllPanel_LS,LID_4)/*"Close"*/);
	}
}

bool OLSCControllPanel::waitForDerimita(QString &recieve)
{
	if(sio==NULL)return false;

	QElapsedTimer timer;
	timer.start();

	QByteArray dump;

	while(timer.elapsed()<3000){
		QByteArray str = sio->readAll();

		dump += str;

		if(dump.contains(derimita.toLocal8Bit().data())==true){
			recieve = dump;
			return true;
		}
	}

	return false;
}

bool OLSCControllPanel::writeCommand(const QString &sendStr, QString &recieve)
{
	if(sio==NULL)return false;

	QString str = sendStr;
	str += derimita;

	sio->write(str.toLocal8Bit().data());
	qApp->processEvents(QEventLoop::ExcludeUserInputEvents);

	if(waitForDerimita(recieve)==false){
		QMessageBox::warning(this
							, LangSolver.GetString(OLSCControllPanel_LS,LID_5)/*"Command Error"*/
							, LangSolver.GetString(OLSCControllPanel_LS,LID_6)/*"No Response"*/);
		return false;
	}

	recieve.remove(derimita);

	return true;
}

void OLSCControllPanel::on_pbSensorStatus_clicked()
{
	if(sio==NULL)return;
	
	QString recieve;
	if(writeCommand(/**/"I:", recieve)==false){
		return;
	}

	ui.lbSensorStatus->setText(recieve);
}
void OLSCControllPanel::on_pbMotorStatus_clicked()
{
	if(sio==NULL)return;
	
	QString recieve;
	if(writeCommand(/**/"Q:0", recieve)==false){
		return;
	}

	if(recieve.count()!=10){
		ui.lbCurrentPosition->setText(LangSolver.GetString(OLSCControllPanel_LS,LID_7)/*"Error"*/);
		ui.lbCurrentMotorState->setText(LangSolver.GetString(OLSCControllPanel_LS,LID_8)/*"Error"*/);
		return;
	}

	QString pos = recieve.mid(0, 9);
	QString sta = recieve.at(9);

	ui.lbCurrentPosition->setText(pos);
	ui.lbCurrentMotorState->setText(sta);
}
void OLSCControllPanel::on_pbHome_clicked()
{
	if(sio==NULL)return;
	
	QString recieve;
	if(writeCommand(/**/"H:", recieve)==false){
		return;
	}
}
void OLSCControllPanel::on_pbMotorStop_clicked()
{
	if(sio==NULL)return;
	
	QString recieve;
	if(writeCommand(/**/"L:", recieve)==false){
		return;
	}
}
void OLSCControllPanel::on_pbMoveToPulse_clicked()
{
	int num = ui.sbMoveToPulse->value();
	
	QString recieve;
	if(writeCommand(QString(/**/"M:%1").arg(num), recieve)==false){
		return;
	}
}
void OLSCControllPanel::on_pbJog_clicked()
{
	int speed;
	if(ui.rbJogSlow->isChecked()==true){
		speed = 0;
	}else if(ui.rbJogFast->isChecked()==true){
		speed = 1;
	}else{
		speed = 2;
	}

	QChar c;
	if(ui.rbJogToPlus->isChecked()==true){
		c = QChar('+');
	}else{
		c = QChar('-');
	}
	
	QString recieve;
	if(writeCommand(QString(/**/"J:%1%2").arg(speed).arg(c), recieve)==false){
		return;
	}
}
void OLSCControllPanel::on_pbMoveToPort1_clicked()
{
	int num = ui.sbMoveToPulse->value();
	
	QString recieve;
	if(writeCommand(QString(/**/"Z:1").arg(num), recieve)==false){
		return;
	}
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Review" ,/**/"AutofocusChuo" ,/**/"");
	if(GProp!=NULL){
		CmdSetLensRange	Cmd(GetLayersBase());
		Cmd.Number=1;
		GProp->TransmitDirectly(&Cmd);
	}
	ZoomRate=5;
}
void OLSCControllPanel::on_pbMoveToPort2_clicked()
{
	int num = ui.sbMoveToPulse->value();
	
	QString recieve;
	if(writeCommand(QString(/**/"Z:2").arg(num), recieve)==false){
		return;
	}
		
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Review" ,/**/"AutofocusChuo" ,/**/"");
	if(GProp!=NULL){
		CmdSetLensRange	Cmd(GetLayersBase());
		Cmd.Number=2;
		GProp->TransmitDirectly(&Cmd);
	}
	ZoomRate=20;
}
void OLSCControllPanel::on_pbMoveToPort3_clicked()
{
	int num = ui.sbMoveToPulse->value();
	
	QString recieve;
	if(writeCommand(QString(/**/"Z:3").arg(num), recieve)==false){
		return;
	}
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Review" ,/**/"AutofocusChuo" ,/**/"");
	if(GProp!=NULL){
		CmdSetLensRange	Cmd(GetLayersBase());
		Cmd.Number=3;
		GProp->TransmitDirectly(&Cmd);
	}
	ZoomRate=50;
}
void OLSCControllPanel::on_pbMoveToPort4_clicked()
{
	int num = ui.sbMoveToPulse->value();
	
	QString recieve;
	if(writeCommand(QString(/**/"Z:4").arg(num), recieve)==false){
		return;
	}
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Review" ,/**/"AutofocusChuo" ,/**/"");
	if(GProp!=NULL){
		CmdSetLensRange	Cmd(GetLayersBase());
		Cmd.Number=4;
		GProp->TransmitDirectly(&Cmd);
	}
	ZoomRate=100;
}

void OLSCControllPanel::updatePortShowByButton()
{
	if(m_initializedPortValue==false)return;

	QString recieve;
	if(writeCommand(/**/"Q:1", recieve)==false){
		return;
	}

	bool ok;
	int pos = recieve.toInt(&ok);

	if(ok==false)return;

	int pnum = -1;
	if(pos==m_port1){
		pnum = 0;
	}else if(pos==m_port2){
		pnum = 1;
	}else if(pos==m_port3){
		pnum = 2;
	}else if(pos==m_port4){
		pnum = 3;
	}else{
		pnum = -1;
	}

	if(pnum==-1){
		ui.pbMoveToPort1->setAutoFillBackground(true);
		ui.pbMoveToPort1->setStyleSheet(/**/"background-color: rgb(240, 240, 240)");
		ui.pbMoveToPort2->setAutoFillBackground(true);
		ui.pbMoveToPort2->setStyleSheet(/**/"background-color: rgb(240, 240, 240)");
		ui.pbMoveToPort3->setAutoFillBackground(true);
		ui.pbMoveToPort3->setStyleSheet(/**/"background-color: rgb(240, 240, 240)");
		ui.pbMoveToPort4->setAutoFillBackground(true);
		ui.pbMoveToPort4->setStyleSheet(/**/"background-color: rgb(240, 240, 240)");
	}else if(pnum==0){
		ui.pbMoveToPort1->setAutoFillBackground(true);
		ui.pbMoveToPort1->setStyleSheet(/**/"background-color: rgb(230, 150, 150)");
		ui.pbMoveToPort2->setAutoFillBackground(true);
		ui.pbMoveToPort2->setStyleSheet(/**/"background-color: rgb(240, 240, 240)");
		ui.pbMoveToPort3->setAutoFillBackground(true);
		ui.pbMoveToPort3->setStyleSheet(/**/"background-color: rgb(240, 240, 240)");
		ui.pbMoveToPort4->setAutoFillBackground(true);
		ui.pbMoveToPort4->setStyleSheet(/**/"background-color: rgb(240, 240, 240)");
	}else if(pnum==1){
		ui.pbMoveToPort1->setAutoFillBackground(true);
		ui.pbMoveToPort1->setStyleSheet(/**/"background-color: rgb(240, 240, 240)");
		ui.pbMoveToPort2->setAutoFillBackground(true);
		ui.pbMoveToPort2->setStyleSheet(/**/"background-color: rgb(230, 150, 150)");
		ui.pbMoveToPort3->setAutoFillBackground(true);
		ui.pbMoveToPort3->setStyleSheet(/**/"background-color: rgb(240, 240, 240)");
		ui.pbMoveToPort4->setAutoFillBackground(true);
		ui.pbMoveToPort4->setStyleSheet(/**/"background-color: rgb(240, 240, 240)");
	}else if(pnum==2){
		ui.pbMoveToPort1->setAutoFillBackground(true);
		ui.pbMoveToPort1->setStyleSheet(/**/"background-color: rgb(240, 240, 240)");
		ui.pbMoveToPort2->setAutoFillBackground(true);
		ui.pbMoveToPort2->setStyleSheet(/**/"background-color: rgb(240, 240, 240)");
		ui.pbMoveToPort3->setAutoFillBackground(true);
		ui.pbMoveToPort3->setStyleSheet(/**/"background-color: rgb(230, 150, 150)");
		ui.pbMoveToPort4->setAutoFillBackground(true);
		ui.pbMoveToPort4->setStyleSheet(/**/"background-color: rgb(240, 240, 240)");
	}else if(pnum==3){
		ui.pbMoveToPort1->setAutoFillBackground(true);
		ui.pbMoveToPort1->setStyleSheet(/**/"background-color: rgb(240, 240, 240)");
		ui.pbMoveToPort2->setAutoFillBackground(true);
		ui.pbMoveToPort2->setStyleSheet(/**/"background-color: rgb(240, 240, 240)");
		ui.pbMoveToPort3->setAutoFillBackground(true);
		ui.pbMoveToPort3->setStyleSheet(/**/"background-color: rgb(240, 240, 240)");
		ui.pbMoveToPort4->setAutoFillBackground(true);
		ui.pbMoveToPort4->setStyleSheet(/**/"background-color: rgb(230, 150, 150)");
	}else{
		ui.pbMoveToPort1->setAutoFillBackground(true);
		ui.pbMoveToPort1->setStyleSheet(/**/"background-color: rgb(240, 240, 240)");
		ui.pbMoveToPort2->setAutoFillBackground(true);
		ui.pbMoveToPort2->setStyleSheet(/**/"background-color: rgb(240, 240, 240)");
		ui.pbMoveToPort3->setAutoFillBackground(true);
		ui.pbMoveToPort3->setStyleSheet(/**/"background-color: rgb(240, 240, 240)");
		ui.pbMoveToPort4->setAutoFillBackground(true);
		ui.pbMoveToPort4->setStyleSheet(/**/"background-color: rgb(240, 240, 240)");
	}
}

bool OLSCControllPanel::waitForStop(QString &stopInfo)
{
	bool ret = false;
	for(;;){
		QString recieve;
		if(writeCommand(/**/"Q:2", recieve)==false){
			stopInfo = LangSolver.GetString(OLSCControllPanel_LS,LID_9)/*"Communication error"*/;
			break;
		}

		if(recieve==/**/"K"){
			stopInfo = LangSolver.GetString(OLSCControllPanel_LS,LID_10)/*"Normal"*/;
			ret = true;
			break;
		}else if(recieve==/**/"L"){
			stopInfo = LangSolver.GetString(OLSCControllPanel_LS,LID_11)/*"Hardware or software limit"*/;
			break;
		}else if(recieve==/**/"H"){
			stopInfo = LangSolver.GetString(OLSCControllPanel_LS,LID_12)/*"Error on Homing"*/;
			break;
		}else if(recieve==/**/"C"){
			stopInfo = LangSolver.GetString(OLSCControllPanel_LS,LID_13)/*"Overflow pulse input"*/;
			break;
		}

		QElapsedTimer timer;
		timer.start();
		while(timer.elapsed()<100)
			;

		qApp->processEvents();
	}

	return ret;
}

void OLSCControllPanel::OperandChangedHome()
{
	int val = ioHome->Get();
	if(val!=1)return;

	on_pbHome_clicked();

	if(waitForStop()==true){
		ioHome->Set(2);
	}else{
		ioHome->Set(3);
	}
}

void OLSCControllPanel::OperandChangedMovePort()
{
	int val = ioMovePort->Get();
	if(val!=qBound(1, val, 4))return;

	switch(val){
	case 1:
		on_pbMoveToPort1_clicked();
		break;
	case 2:
		on_pbMoveToPort2_clicked();
		break;
	case 3:
		on_pbMoveToPort3_clicked();
		break;
	case 4:
		on_pbMoveToPort4_clicked();
		break;
	default:
		break;
	}

	QString info;
	if(waitForStop(info)==false){
		ioMovePort->Set(6);
	}else{
		ioMovePort->Set(5);
	}
}

void OLSCControllPanel::OperandChangedStop()
{
	if(ioStopNo->Get()==true)return;

	on_pbMotorStop_clicked();

	QString info;
	waitForStop(info);

	ioStopNo->Set(false);
}

bool OLSCControllPanel::readParameter(int number, int &value)
{
	QString recieve;
	if(writeCommand(QString(/**/"P:%1R").arg(number), recieve)==false){
		return false;
	}

	bool ok;
	int v = recieve.toInt(&ok);

	if(ok==false){
		return false;
	}

	value = v;
	return true;
}

void OLSCControllPanel::updatePortPosition()
{
	m_initializedPortValue = false;

	int value;
	if(readParameter(41, value)==false){
		return;
	}

	m_port1 = value;
	
	if(readParameter(42, value)==false){
		return;
	}

	m_port2 = value;
	
	if(readParameter(43, value)==false){
		return;
	}

	m_port3 = value;
	
	if(readParameter(44, value)==false){
		return;
	}

	m_port4 = value;

	m_initializedPortValue = true;
}

int OLSCControllPanel::searchCurrentPortPosition()
{
	if(sio==NULL)return -1;

	QString recieve;
	if(writeCommand(/**/"Q:1", recieve)==false){
		return -1;
	}

	bool ok;
	int pos = recieve.toInt(&ok);
	if(ok==false){
		return -1;
	}

	if(pos==m_port1){
		return 0;
	}else if(pos==m_port2){
		return 1;
	}else if(pos==m_port3){
		return 2;
	}else if(pos==m_port4){
		return 3;
	}else{
		return -1;
	}

	return -1;
}

int OLSCControllPanel::portPosition(int i) const
{
	switch(i){
	case 0:
		return m_port1;
	case 1:
		return m_port2;
	case 2:
		return m_port3;
	case 3:
		return m_port4;
	default:
		return -1;
	}

	return -1;
}