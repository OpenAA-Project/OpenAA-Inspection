#include "RepairStationResource.h"
#include "InspectionDataForm.h"

extern LangSolverClass LangSolver;

#include "PasswordEventOperator.h"

InspectionDataForm::InspectionDataForm()
{
	ui.setupUi(this);
	connect(ui.pbEnter,SIGNAL(clicked()),this,SLOT(pbEnterClicked()));
	LangSolver.SetUI(this);

	PasswordEventOperator *peo = new PasswordEventOperator(this);
	peo->addButton(ui.pbEnter);

	//?F?I?Y?e
	QPalette P;
	P.setColor(QPalette::Base,QColor(Qt::cyan));
	ui.leSumInsDataF->setPalette(P);
	ui.leOKInsDataF	->setPalette(P);
	ui.leNGInsDataF	->setPalette(P);
	ui.leSumInsDataB->setPalette(P);
	ui.leOKInsDataB	->setPalette(P);
	ui.leNGInsDataB	->setPalette(P);

	//?a?E?I?Y?e
	PaletteDefault=palette();
	PaletteAlarm[0].setColor(QPalette::Window,QColor(Qt::red));
	PaletteAlarm[1].setColor(QPalette::Window,QColor(Qt::yellow));
	setWindowTitle(LangSolver.GetString(InspectionDataForm_LS,LID_891)/*"???C?f?[?^?\?|"*/);

	//Timer
	Index=0;
	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(update()));
//	timer->start(500);
}

InspectionDataForm::~InspectionDataForm()
{
}

void InspectionDataForm::SetDialog(int Type,QList<QByteArray> *XMLFData,QList<QByteArray> *XMLBData,int MCount,int Flg)
{
	if(Flg!=1){
		SetRetXMLDataList(0,XMLFData);
	}
	if(Flg==0){
		return;
	}
	SetRetXMLDataList(1,XMLBData);

	for(int Cnt=0;Cnt<=Type;Cnt++){
		if(GetRetXMLDataList(Cnt)==NULL){
			continue;
		}
		int XMLDataListSum=GetRetXMLDataList(Cnt)->count();	//????
		int XMLDataListOK=0;	//OK
		int XMLDataListNG=0;	//NG
		for(int i=0;i<XMLDataListSum;i++){
///			if(GetRetXMLDataList(Cnt)->at(i).contains(LangSolver.GetString(InspectionDataForm_LS,LID_451)/*"<RES>OK</RES>"*/)){
///				XMLDataListOK++;
///			}
///			else if(GetRetXMLDataList(Cnt)->at(i).contains(LangSolver.GetString(InspectionDataForm_LS,LID_452)/*"<RES>NG</RES>"*/)){
				if(GetRetXMLDataList(Cnt)->at(i).contains(LangSolver.GetString(InspectionDataForm_LS,LID_453)/*"<NGP"*/)==false){
					XMLDataListOK++;
					continue;
				}
				XMLDataListNG++;
///			}
		}
		if(Cnt==0){
			ui.leSumInsDataF->setText(QString::number(XMLDataListSum));
			ui.leOKInsDataF	->setText(QString::number(XMLDataListOK));
			ui.leNGInsDataF	->setText(QString::number(XMLDataListNG));
		}
		else{
			ui.leSumInsDataB->setText(QString::number(XMLDataListSum));
			ui.leOKInsDataB	->setText(QString::number(XMLDataListOK));
			ui.leNGInsDataB	->setText(QString::number(XMLDataListNG));
		}
	}

	//???b?Z?[?W?o?I
	setPalette(PaletteDefault);
	ui.teMessage->clear();
	if(ui.leOKInsDataF->text().toInt()+ui.leNGInsDataF->text().toInt()!=ui.leSumInsDataF->text().toInt()){
		ui.teMessage->append(LangSolver.GetString(InspectionDataForm_LS,LID_454)/*"?a?Ê???I?????a?}?b?`?ƒÊ?U?1?n?I"*/);
		timer->start(500);
	}
	if(ui.leOKInsDataB->text().toInt()+ui.leNGInsDataB->text().toInt()!=ui.leSumInsDataB->text().toInt()){
		ui.teMessage->append(LangSolver.GetString(InspectionDataForm_LS,LID_455)/*"?o?Ê???I?????a?}?b?`?ƒÊ?U?1?n?I"*/);
		timer->start(500);
	}
	if(MCount==2 && ui.leSumInsDataF->text().toInt()!=ui.leSumInsDataB->text().toInt()){
		ui.teMessage->append(LangSolver.GetString(InspectionDataForm_LS,LID_456)/*"?a?Ê???A?o?Ê???I?????a?}?b?`?ƒÊ?U?1?n?I"*/);
		timer->start(500);
	}
	if(ui.teMessage->toPlainText().isEmpty()==true){
		timer->stop();
	}
}

void InspectionDataForm::closeEvent(QCloseEvent *event)
{
	timer->stop();
}

void InspectionDataForm::pbEnterClicked()
{
	accept();
	close();
}

void InspectionDataForm::update()
{
	Index^=1;
	setPalette(PaletteAlarm[Index]);
}
