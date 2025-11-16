#include "EditRemainTimeFormResource.h"
#include "ShowSumTimerForm.h"
#include "ui_ShowSumTimerForm.h"
#include "ThreadSequence.h"
#include "XSequenceLocal.h"
#include "XExecuteInspectBase.h"
#include "EditRemainTimeForm.h"
#include <QMenu>
#include <QMessageBox>
#include "XEntryPoint.h"

LongTime::LongTime(quint32 _hour, quint32 _minuite, quint32 _second, quint32 _miliSecond, bool minus)
	:m_isMinus(minus)
	,m_hour(_hour)
	,m_minuite(_minuite)
	,m_second(_second)
	,m_milisecond(_miliSecond)
{
}

void LongTime::addHour(quint64 h)
{
	//setHour( hour() + h );
	
	qint64 curMS = toMiliSecond();

	curMS += h * 60 * 60 * 1000;

	*this = fromMiliSecond(curMS);
}

void LongTime::addMinuite(quint64 min)
{
	qint64 curMS = toMiliSecond();

	curMS += min * 60 * 1000;

	*this = fromMiliSecond(curMS);

	//qint32 newMin = miliSecond() + min;
	//qint32 addH = 0;

	//if(newMin>59){
	//	qint64 sec = newMin / 60;
	//	newMin = newMin % 60;
	//	addH += sec;
	//}else if(newMin<0){
	//	qint64 sec = newMin / 60;
	//	newMin = newMin % 60;
	//	addH += sec;
	//	newMin += 60;
	//	addH -= 1;
	//}

	//addHour(addH);

	//setMinuite(newMin);
}

void LongTime::addSecond(quint64 sec)
{
	qint64 curMS = toMiliSecond();

	curMS += sec * 1000;

	*this = fromMiliSecond(curMS);
	//qint32 newSec = miliSecond() + sec;
	//qint32 addMin = 0;

	//if(newSec>59){
	//	qint64 sec = newSec / 60;
	//	newSec = newSec % 60;
	//	addMin += sec;
	//}else if(newSec<0){
	//	qint64 sec = newSec / 60;
	//	newSec = newSec % 60;
	//	addMin += sec;
	//	newSec += 60;
	//	addMin -= 1;
	//}

	//addMinuite(addMin);

	//setSecond(newSec);
}

void LongTime::addMiliSecond(quint64 msec)
{
	qint64 curMS = toMiliSecond();

	curMS += msec;

	*this = fromMiliSecond(curMS);
	//qint32 newMSec = miliSecond() + msec;
	//qint32 addSec = 0;

	//if(newMSec>999){
	//	qint64 sec = newMSec / 1000;
	//	newMSec = newMSec % 1000;
	//	addSec += sec;
	//}else if(newMSec<0){
	//	qint64 sec = newMSec / 1000;
	//	newMSec = newMSec % 1000;
	//	addSec += sec;
	//	newMSec += 1000;
	//	addSec -= 1;
	//}

	//addSecond(addSec);

	//setMiliSecond(newMSec);
}

qint64 LongTime::toMiliSecond() const
{
	qint64 res = 0;
	quint64 rate = 1;
	res += miliSecond() * rate;
	
	rate *= 1000;

	res += second() * rate;

	rate *= 60;

	res += minuite() * rate;

	rate *= 60;

	res += hour() * rate;

	if(isMinus()==false){
		return res;
	}else{
		return -res;
	}
}

LongTime LongTime::fromMiliSecond(quint64 msec)
{
	bool minus;
	if(msec<0){
		minus = true;
	}else{
		minus = false;
	}

	qint64 ms = msec % 1000;
	msec /= 1000;
	qint64 s = msec % 60;
	msec /= 60;
	qint64 m = msec % 60;
	msec /= 60;
	qint64 h = msec;

	return LongTime(h, m, s, ms, minus);
};

ShowSumTimerForm::ShowSumTimerForm(LayersBase *Base,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::ShowSumTimerForm)
{
    ui->setupUi(this);

	setFrameShape(QFrame::Shape::Panel);
	setFrameShadow(QFrame::Shadow::Raised);

	TitleName = /**/"MyTimer";
	
	TimerControlIONumber = 400;
	TimerProgressIONumber = 401;
	TimerFuncEndIONumber = 400;

	MaxTime_Hour = 0;
	MaxTime_Minuite = 0;
	MaxTime_Second = 0;
	MaxTime_MiliSec = 0;

	isIncreaseProgress = true;
	isIncreaseTime = true;
	isViewResetButton = true;
	isViewTimeLabel = true;
	isViewProgressBar = true;
	isSaveToFile = true;
	isTimeEditEnable = true;

	ioTimerEnable = NULL;
	ioTimerProgress = NULL;
	ioTimerFuncEnd = NULL;

	UpdateDuration = 60000;

	TitleFont = ui->lbTitle->font();
	TimeFont = ui->lbTime->font();

	//m_timer.invalidate(); // isValid()でfalseを返す。start()でisValid()はtrueを返すようになる。(初期化チェックに)
	m_sumTime.clear();
	m_timer.invalidate();


	if(GetEditMode()==false){
		m_contextMenu = new QMenu(this);
		m_showEditTimeAction = new QAction(LangSolver.GetString(ShowSumTimerForm_LS,LID_0)/*"EditTime"*/, this);

		m_contextMenu->addAction(m_showEditTimeAction);
		
		connect(m_showEditTimeAction, SIGNAL(triggered(bool)), this, SLOT(showEditTimeForm()));
		connect(&m_tline, SIGNAL(finished()), this, SLOT(timeLineFinished()));
	}else{
		m_contextMenu = NULL;
		m_showEditTimeAction = NULL;
	}
}

void ShowSumTimerForm::contextMenuEvent(QContextMenuEvent *event)
{
	if(GetEditMode()==false && isTimeEditEnable==true){
		showEditTimeForm();

		//QPoint p = event->pos() + geometry().topLeft();
		//if(parentWidget()!=NULL){
		//	p += parentWidget()->geometry().topLeft();
		//}
		//m_contextMenu->exec(p/*event->pos() + geometry().topLeft() + parentWidget()->geometry().topLeft()*/);
	}
}

void ShowSumTimerForm::showEditTimeForm()
{
	EditRemainTimeForm form(GetLayersBase(),this);

	form.fromMiliSecond( sumTimeMSec() );

	if(form.exec()==QDialog::Accepted){
		setSumTime( form.time().toMiliSecond() );
		updateView();
		save();
	}
}

void ShowSumTimerForm::updateDuration()
{
	LongTime mt(MaxTime_Hour, MaxTime_Minuite, MaxTime_Second, MaxTime_MiliSec);
	if(mt.toMiliSecond()<UpdateDuration){
		m_tline.setDuration(mt.toMiliSecond());
	}else{
		m_tline.setDuration(UpdateDuration);
	}
}

ShowSumTimerForm::~ShowSumTimerForm()
{
	save();
    delete ui;
}

void ShowSumTimerForm::resizeEvent(QResizeEvent *event)
{
	//QSize newSize = QSize(event->size().width() + 10, event->size().height() + 10);
	//if(size()!=newSize){
	//	resize(newSize);
	//}
	
	setFrameShape(QFrame::Shape::Panel);
	setFrameShadow(QFrame::Shadow::Raised);
}

void	ShowSumTimerForm::Prepare(void)
{
	if(GetLayersBase()->GetInsideLearningEditor()==false 
	&& GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL
	&& GetLayersBase()->GetShadowLevel()==0){
		SeqControlParam	*Param=(SeqControlParam *)GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetSeqParam();
		if(Param!=NULL){
			ioTimerEnable		=new SignalOperandInt(this,TimerControlIONumber,/**/"ShowSumTimer:ioTimerEnable");
			ioTimerEnable->Set(0);

			ioTimerProgress		=new SignalOperandInt(this,TimerProgressIONumber,/**/"ShowSumTimer:ioTimerProgress");
			ioTimerProgress->Set(0);

			ioTimerFuncEnd		=new SignalOperandBit(this,TimerFuncEndIONumber,/**/"ShowSumTimer:ioTimerFuncEnd");
			ioTimerFuncEnd->Set(false);

			connect(ioTimerEnable	,SIGNAL(changed())	,this	,SLOT(OperandEnableChanged()));
			SeqErrorInfo	Error;
			if(Param->SetSpecialOperand(ioTimerEnable	,&Error)==false){
				ioTimerEnable->ShowErrorMessage(Error);
			}
			if(Param->SetSpecialOperand(ioTimerProgress	,&Error)==false){
				ioTimerProgress->ShowErrorMessage(Error);
			}
			if(Param->SetSpecialOperand(ioTimerFuncEnd	,&Error)==false){
				ioTimerFuncEnd->ShowErrorMessage(Error);
			}
		}
	}

	ui->lbTitle->setText(TitleName);
	ui->lbTitle->setVisible(isViewTitleLabel);
	ui->lbTime->setVisible(isViewTimeLabel);
	ui->pbReset->setVisible(isViewResetButton);
	ui->progressBar->setVisible(isViewProgressBar);
	ui->lbTitle->setFont(TitleFont);
	ui->lbTime->setFont(TimeFont);

	if(GetEditMode()==false){
		load();
		updateDuration();
	}
	updateView();
}

void	ShowSumTimerForm::BuildForShow(void)
{
	updateView();
}

void	ShowSumTimerForm::OperandEnableChanged()
{
	ioTimerFuncEnd->Set(false);
	int value = ioTimerEnable->Get();
	
	if(value==0){
		if(m_tline.state()==QTimeLine::State::Running){
			m_tline.stop();
			m_tline.setCurrentTime(0);
			updateSumTime();

			save();
			
			m_timer = QElapsedTimer();
			m_timer.invalidate();
			updateView();

			ioTimerProgress->Set((int)(progressRate()*1000));
		}else{
			// none
		}
	}else if(value==1){
		if(sumTimeMSec()<=maxTime()){
			m_tline.setCurrentTime(0);
			m_tline.start();
			m_timer.start();
		}
	}else if(value==2){
		setSumTime(0);
		updateView();
		ioTimerProgress->Set(0);
	}
	ioTimerFuncEnd->Set(true);
}

void ShowSumTimerForm::updateTimerLabel()
{
	QString str;
	if(ViewStringFormat.isEmpty()==false){
		str = ViewStringFormat;
	}else{
		str = /**/"h:m:s";
	}

	if(GetEditMode()==false){
		LongTime st = sumTime();

		if(isIncreaseTime==false){	// 残り時間表示の場合
			LongTime mt(MaxTime_Hour, MaxTime_Minuite, MaxTime_Second, MaxTime_MiliSec);

			st = mt - st;
		}
		str.replace(/**/"h", QString(/**/"%1").arg(st.hour(), 2, 10, QChar('0')));
		str.replace(/**/"m", QString(/**/"%1").arg(st.minuite(), 2, 10, QChar('0')));
		str.replace(/**/"s", QString(/**/"%1").arg(st.second(), 2, 10, QChar('0')));
		str.replace(/**/"z", QString(/**/"%1").arg(st.miliSecond(), 3, 10, QChar('0')));
		if(st.isMinus()==true){
			str.push_front(QChar('-'));
		}
	}else{
		str.replace(/**/"h", QString(/**/"%1").arg(11, 2, 10, QChar('0')));
		str.replace(/**/"m", QString(/**/"%1").arg(22, 2, 10, QChar('0')));
		str.replace(/**/"s", QString(/**/"%1").arg(33, 2, 10, QChar('0')));
		str.replace(/**/"z", QString(/**/"%1").arg(444, 3, 10, QChar('0')));
	}


	ui->lbTime->setText(str);
}

void ShowSumTimerForm::updateProgressBar()
{
	int value = progressRate() * ui->progressBar->maximum();

	if(isIncreaseProgress==true){
		ui->progressBar->setValue(value);
	}else{
		ui->progressBar->setValue(ui->progressBar->maximum() - value);
	}
}

void ShowSumTimerForm::updateView()
{
	if(isViewTimeLabel==true){
		updateTimerLabel();
	}
	if(isViewProgressBar==true){
		updateProgressBar();
	}
}

void ShowSumTimerForm::updateSumTime()
{
	if(m_timer.isValid()==true){
		m_sumTime.addMiliSecond(m_timer.elapsed());
		m_timer = QElapsedTimer();
		m_timer.start();
	}
}

void ShowSumTimerForm::save()
{
	if(isSaveToFile==true){
		QMutexLocker locker(&m_fileMutex);
		QString filename = QString(/**/"SumTime_%1.dat").arg(TimerControlIONumber);
		QFile file(filename);
		if(file.open(QIODevice::WriteOnly)==true){
			QDataStream stream(&file);
			stream << sumTimeMSec();
		}
	}
}

void ShowSumTimerForm::load()
{
	if(isSaveToFile==true){
		QMutexLocker locker(&m_fileMutex);
		QString filename = QString(/**/"SumTime_%1.dat").arg(TimerControlIONumber);
		QFile file(filename);
		if(file.open(QIODevice::ReadOnly)==true){
			QDataStream stream(&file);
			quint64 buff;
			stream >> buff;
			setSumTime(buff);
		}
		updateView();
	}
}

void ShowSumTimerForm::on_pbReset_clicked()
{
	QMessageBox mbox(this);

	mbox.setModal(false);
	mbox.setText(LangSolver.GetString(ShowSumTimerForm_LS,LID_1)/*"Do you clear this timer?"*/);
	mbox.setInformativeText(LangSolver.GetString(ShowSumTimerForm_LS,LID_2)/*"This action can not undo."*/);
	mbox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
	mbox.setDefaultButton(QMessageBox::Cancel);

	int ret = mbox.exec();

	if(ret==QMessageBox::Ok){
		setSumTime(0);
		updateView();
	}
}

int ShowSumTimerForm::nextDuration() const
{
	quint64 ct = sumTimeMSec();
	quint64 mt = maxTime();

	quint64 st;
	if(mt<ct){
		st = 0;
	}else{
		st = mt - ct;
	}

	if(UpdateDuration<st){
		return UpdateDuration;
	}else{
		if(st<=0){
			return 0;
		}else{
			return st;
		}
	}
}

void ShowSumTimerForm::timeLineFinished()
{
	const LongTime temp = m_sumTime;
	//updateSumTime();
	m_tline.setCurrentTime(0);

	int nd = nextDuration();

	qDebug() << /**/"old:" << temp.toMiliSecond();
	qDebug() << /**/"new:" << m_sumTime.toMiliSecond();

	if(nd==0){
		m_tline.setDuration(UpdateDuration);
		m_tline.setCurrentTime(0);
		m_tline.stop();
		setSumTime(maxTime());
		updateView();
		m_timer = QElapsedTimer();
		m_timer.invalidate();
		save();
	}else{
		m_tline.setDuration(nd);
		m_tline.setCurrentTime(0);
		m_tline.start();
		updateView();
	}

	ioTimerProgress->Set((int)(progressRate()*1000));
}
