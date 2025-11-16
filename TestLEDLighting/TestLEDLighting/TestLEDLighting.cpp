/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\TestLEDLighting\TestLEDLighting\TestLEDLighting.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "TestLEDLighting.h"
#include "QCloseEvent"
#include <QHeaderView>
#include <QKeyEvent>

#if KindOfLight==1
	#include "LightDLL1Form.h"
    static  LightDLL1Form	*LightForm=NULL;
#elif   KindOfLight==2
	#include "LightDLL2Form.h"
    static  LightDLL2Form	*LightForm=NULL;
#endif

/* Error messages display */
#define WD_REGISTER_ERR printf
#define ACTIVE_ADDR_SPACE_NEEDS_INIT 0xFF

static bool ContinueMode;

TestLEDLighting::TestLEDLighting(QWidget *parent, Qt::WindowFlags flags)
	: QWidget(parent, flags)
{
	ui.setupUi(this);

	//初期化処理
	Init();

	#if KindOfLight==1
		hLighDLLtBase=new LightDLL1();
	#elif	KindOfLight==2
		hLighDLLtBase=new LightDLL2();
	#endif

	//connect
	connect(ui.pbAllOn,							SIGNAL(clicked()),									this,SLOT(pbAllOnClicked()));
	connect(ui.pbAllOff,						SIGNAL(clicked()),									this,SLOT(pbAllOffClicked()));
	connect(ui.pbOneOn,							SIGNAL(clicked()),									this,SLOT(pbOneOnClicked()));
	connect(ui.pbNextOn,						SIGNAL(clicked()),									this,SLOT(pbNextOnClicked()));
	connect(ui.pbStartPosClear,					SIGNAL(clicked()),									this,SLOT(pbStartPosClearClicked()));
	connect(ui.pbStart,							SIGNAL(clicked()),									this,SLOT(pbStartClicked()));
	connect(ui.pbClose,							SIGNAL(clicked()),									this,SLOT(pbCloseClicked()));
	connect(ui.pbDetails,						SIGNAL(clicked()),									this,SLOT(pbDetailsClicked()));
	connect(ui.twBar->selectionModel(),			SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),	this,SLOT(twBarRowChanged(QModelIndex)));
	connect(ui.twLED->selectionModel(),			SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),	this,SLOT(twLEDRowChanged(QModelIndex)));
	connect(ui.twBrightness->selectionModel(),	SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),	this,SLOT(twBrightnessRowChanged(QModelIndex)));
	connect(&tContinue,							SIGNAL(SignalOneOn()),								this,SLOT(pbOneOnClicked()));
	connect(&tContinue,							SIGNAL(SignalNextOn()),								this,SLOT(pbNextOnClicked()));

	//初期配置
	ui.twBar->setCurrentIndex(ui.twBar->model()->index(0,0));
	ui.twLED->setCurrentIndex(ui.twLED->model()->index(0,0));
	ui.twBrightness->setCurrentIndex(ui.twBrightness->model()->index(0,0));

	//WinDriver
	hDev = NULL;
/*
	// Initialize the WD_REGISTER library
	dwStatus = WD_REGISTER_LibInit();
	if (WD_STATUS_SUCCESS != dwStatus){
		WD_REGISTER_ERR("wd_register_diag: Failed to initialize the WD_REGISTER library: %s",
			WD_REGISTER_GetLastErr());
		return;
	}
*/
	// Open a handle to the device
	hDev = WD_REGISTER_DeviceOpen();
	if (!hDev){
		WD_REGISTER_ERR("wd_register_diag: Failed opening a handle to the device: %s",
			WD_REGISTER_GetLastErr());
		return;
	}

	/* Find the first active address space */
	dwAddrSpace = ACTIVE_ADDR_SPACE_NEEDS_INIT;
	mode = WDC_MODE_8;
	for (dwAddrSpace = 0; dwAddrSpace < WD_REGISTER_ADDR_SPACES_NUM; dwAddrSpace++){
		if (WDC_AddrSpaceIsActive(hDev, dwAddrSpace))
			break;
	}

	for(int i=0;i<LEDBARNUMB;i++){
		CLED[i].SetDevice(hDev);
		CLED[i].SetID((short)i);
		CLED[i].SetAddress(dwAddrSpace);
		CLED[i].Initial(LEDsNumb);
		for(int j=0;j<LEDsNumb;j++){
			Gain[i][j]=1.0;
			ChangeTransferLED[i][j]=false;
		}
	}
}

TestLEDLighting::~TestLEDLighting()
{
}

void TestLEDLighting::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()){
		case Qt::Key_Left:
			if(ui.twBrightness->hasFocus())
				ui.twLED->setFocus();
			else if(ui.twLED->hasFocus())
				ui.twBar->setFocus();
			break;
		case Qt::Key_Right:
			if(ui.twBar->hasFocus())
				ui.twLED->setFocus();
			else if(ui.twLED->hasFocus())
				ui.twBrightness->setFocus();
			break;
		default:
			QWidget::keyPressEvent(event);
			break;
	}
}

void TestLEDLighting::closeEvent(QCloseEvent *event)
{
/*	// Perform necessary cleanup before exiting the program
	if (hDev && !WD_REGISTER_DeviceClose(hDev)){
		WD_REGISTER_ERR("wd_register_diag: Failed closing WD_REGISTER device: %s",
			WD_REGISTER_GetLastErr());
	}
 
	dwStatus = WD_REGISTER_LibUninit();
	if (WD_STATUS_SUCCESS != dwStatus)
		WD_REGISTER_ERR("wd_register_diag: Failed to uninit the WD_REGISTER library: %s", WD_REGISTER_GetLastErr());
*/
	ContinueMode=false;
	event->accept();
}

void TestLEDLighting::pbAllOnClicked()
{
	//全部点灯
	ui.pgbLight->setValue(0);
	for(int i=0;i<LEDBarNumb;i++){
		for(int j=0;j<LEDNumbPerLine;j++)
			LEDBright[i/2][j+(i&1)*LEDNumbPerLine]=(short)ui.sbBrightness->value();
	}

	for(int i=0;i<LEDBARNUMB;i++){
		for(int j=0;j<LEDsNumb;j++){
			CLED[i].Change(j,LEDBright[i][j]);
			CLED[i].OutData(j,Gain[i][j]);
		}
		ui.pgbLight->setValue(100*(i+1)/LEDBARNUMB);
	}
}

void TestLEDLighting::pbAllOffClicked()
{
	//全部消灯
	ui.pgbLight->setValue(0);
	for(int i=0;i<LEDBarNumb;i++){
		for(int j=0;j<LEDNumbPerLine;j++)
			LEDBright[i/2][j+(i&1)*LEDNumbPerLine]=0;
	}

	for(int i=0;i<LEDBARNUMB;i++){
		for(int j=0;j<LEDsNumb;j++){
			CLED[i].Change(j,LEDBright[i][j]);
			CLED[i].OutData(j,Gain[i][j]);
		}
		ui.pgbLight->setValue(100*(i+1)/LEDBARNUMB);
	}
}

void TestLEDLighting::pbOneOnClicked()
{
	ui.pgbLight->setValue(0);
	LEDBright[ui.twBar->currentIndex().row()/2][ui.twLED->currentIndex().row()+(ui.twBar->currentIndex().row()&1)*LEDNumbPerLine]=(short)ui.sbBrightness->value();

	if(ui.chkMultiple->isChecked()==false){
		for(int i=0;i<LEDBarNumb;i++){
			for(int j=0;j<LEDNumbPerLine;j++){
				if(i!=ui.twBar->currentIndex().row() || j!=ui.twLED->currentIndex().row()){
					if(LEDBright[i/2][j+(i&1)*LEDNumbPerLine]!=0){
						LEDBright[i/2][j+(i&1)*LEDNumbPerLine]=0;
						ChangeTransferLED[i/2][j+(i&1)*LEDNumbPerLine]=true;
					}
					else
						ChangeTransferLED[i/2][j+(i&1)*LEDNumbPerLine]=false;
				}
				else
					ChangeTransferLED[i/2][j+(i&1)*LEDNumbPerLine]=true;
			}
		}
	}

	for(int i=0;i<LEDBARNUMB;i++){
		for(int j=0;j<LEDsNumb;j++){
			if(ChangeTransferLED[i][j]){
				CLED[i].Change(j,LEDBright[i][j]);
				CLED[i].OutData(j,Gain[i][j]);
			}
		}
		ui.pgbLight->setValue(100*(i+1)/LEDBARNUMB);
	}
}

void TestLEDLighting::pbNextOnClicked()
{
	if(ui.twLED->currentIndex().row()>=ui.twLED->rowCount()-1){
		if(ui.twBar->currentIndex().row()>=ui.twBar->rowCount()-1)
			return;
		ui.twBar->setCurrentIndex(ui.twBar->model()->index(ui.twBar->currentIndex().row()+1,0));
		ui.twLED->setCurrentIndex(ui.twLED->model()->index(0,0));
	}
	else
		ui.twLED->setCurrentIndex(ui.twLED->model()->index(ui.twLED->currentIndex().row()+1,0));

	pbOneOnClicked();
}

void TestLEDLighting::pbStartPosClearClicked()
{
	ui.twBar->setCurrentIndex(ui.twBar->model()->index(0,0));
	ui.twLED->setCurrentIndex(ui.twLED->model()->index(0,0));
}

void TestLEDLighting::pbStartClicked()
{
	if(ContinueMode==false){
		ContinueMode=true;
		tContinue.SetSwitchTime(ui.sbSwitchTime->value());
		ui.pbStart->setText(tr("Continuous lighting. Stop"));
		tContinue.start();
	}
    else{
		ContinueMode=false;
		ui.pbStart->setText(tr("Start"));
	}
}

void TestLEDLighting::pbCloseClicked()
{
	close();
}

void TestLEDLighting::pbDetailsClicked()
{
	//詳細画面の表示
	#if KindOfLight==1
		LightDLL1	*p=dynamic_cast<LightDLL1 *>(hLighDLLtBase);
	#elif	KindOfLight==2
		LightDLL2	*p=dynamic_cast<LightDLL2 *>(hLighDLLtBase);
	#endif

	if(LightForm==NULL){
		#if KindOfLight==1
			LightForm=new LightDLL1Form(p);
		#elif	KindOfLight==2
			LightForm=new LightDLL2Form(p);
		#endif
	}

    LightForm->InspectionLight=hLighDLLtBase;
    if(p==NULL)
        return;
    LightForm->BLight=*p;
	if(LightForm->exec()){
        *p=LightForm->BLight;
        return;
	}
}

void TestLEDLighting::twBarRowChanged(const QModelIndex &CIndex)
{
	ui.leBar->setText(ui.twBar->currentItem()->text());
}

void TestLEDLighting::twLEDRowChanged(const QModelIndex &CIndex)
{
	ui.leLED->setText(ui.twLED->currentItem()->text());
}

void TestLEDLighting::twBrightnessRowChanged(const QModelIndex &CIndex)
{
	ui.sbBrightness->setValue(ui.twBrightness->currentItem()->text().toInt());
}

void TestLEDLighting::Init()
{
	//Bar
	int BarRowCnt=20;
	ui.twBar->setColumnCount(1);
	ui.twBar->setRowCount(BarRowCnt);
	ui.twBar->horizontalHeader()->hide();
	ui.twBar->verticalHeader()->hide();
	ui.twBar->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ui.twBar->setShowGrid(false);
	ui.twBar->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui.twBar->setSelectionMode(QAbstractItemView::SingleSelection);
	ui.twBar->setSelectionBehavior(QAbstractItemView::SelectRows);
	for(int Row=0;Row<BarRowCnt;Row++){
		QTableWidgetItem *Item=new QTableWidgetItem(QString::number(Row+1));
		Item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		ui.twBar->setItem(Row,0,Item);
		ui.twBar->verticalHeader()->resizeSection(Row,13);
	}

	//LED
	int LEDRowCnt=32;
	ui.twLED->setColumnCount(1);
	ui.twLED->setRowCount(LEDRowCnt);
	ui.twLED->horizontalHeader()->hide();
	ui.twLED->verticalHeader()->hide();
	ui.twLED->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ui.twLED->setShowGrid(false);
	ui.twLED->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui.twLED->setSelectionMode(QAbstractItemView::SingleSelection);
	ui.twLED->setSelectionBehavior(QAbstractItemView::SelectRows);
	for(int Row=0;Row<LEDRowCnt;Row++){
		QTableWidgetItem *Item=new QTableWidgetItem(QString::number(Row+1));
		Item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		ui.twLED->setItem(Row,0,Item);
		ui.twLED->verticalHeader()->resizeSection(Row,13);
	}

	//Brightness
	const int BrightnessRowCnt=11;
	int BrightnessRowList[BrightnessRowCnt]={0,5,6,7,8,9,10,15,20,30,40};
	ui.twBrightness->setColumnCount(1);
	ui.twBrightness->setRowCount(BrightnessRowCnt);
	ui.twBrightness->horizontalHeader()->hide();
	ui.twBrightness->verticalHeader()->hide();
	ui.twBrightness->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ui.twBrightness->setShowGrid(false);
	ui.twBrightness->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui.twBrightness->setSelectionMode(QAbstractItemView::SingleSelection);
	ui.twBrightness->setSelectionBehavior(QAbstractItemView::SelectRows);
	for(int Row=0;Row<BrightnessRowCnt;Row++){
		QTableWidgetItem *Item=new QTableWidgetItem(QString::number(BrightnessRowList[Row]));
		Item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		ui.twBrightness->setItem(Row,0,Item);
		ui.twBrightness->verticalHeader()->resizeSection(Row,13);
	}

	//表示部
	QPalette palette;
	palette.setColor(QPalette::Base,QColor(Qt::cyan));
	ui.leBar->setPalette(palette);
	ui.leLED->setPalette(palette);
	palette.setColor(QPalette::Base,QColor(Qt::green));
	ui.lbBar->setPalette(palette);
	ui.lbLED->setPalette(palette);
	ui.lbBrightness->setPalette(palette);
	palette.setColor(QPalette::Base,QColor(Qt::magenta));
	ui.leSwitchTime->setPalette(palette);

	palette.setColor(QPalette::Base,QColor(Qt::red));
	QLineEdit *leTestInputTitle=new QLineEdit(tr("Test Input"));
	leTestInputTitle->setReadOnly(true);
	leTestInputTitle->setAlignment(Qt::AlignCenter);
	leTestInputTitle->setPalette(palette);
	ui.dwTestInput->setTitleBarWidget(leTestInputTitle);

	QLineEdit *leContinueTesstTitle=new QLineEdit(tr("Continue Test"));
	leContinueTesstTitle->setReadOnly(true);
	leContinueTesstTitle->setAlignment(Qt::AlignCenter);
	leContinueTesstTitle->setPalette(palette);
	ui.dwContinueTest->setTitleBarWidget(leContinueTesstTitle);
/*
	QPalette BackPalette;
	BackPalette.setColor(QPalette::Background,QColor(Qt::lightGray));
	ui.fmBar->setPalette(BackPalette);
	ui.fmLED->setPalette(BackPalette);
	ui.fmBrightness->setPalette(BackPalette);
	BackPalette.setColor(QPalette::Background,QColor(Qt::blue));
	ui.dwTestInput->setPalette(BackPalette);
*/
}

ContinueThread::ContinueThread()
{
	ContinueMode=false;
}

void ContinueThread::run()
{
	DWORD   NowTime=::GetTickCount();
	DWORD   LastTime=NowTime;

	while(ContinueMode){
		if(NowTime==LastTime){
			::Beep(3000,200);
//			MessageBeep( 0xFFFFFFFF );
			emit SignalOneOn();
		}
		else if(NowTime-LastTime>=SwitchTime){
			::Beep(3000,200);
//			MessageBeep( 0xFFFFFFFF );
			emit SignalNextOn();
			LastTime=NowTime;
		}
		NowTime=::GetTickCount();
	}
}
