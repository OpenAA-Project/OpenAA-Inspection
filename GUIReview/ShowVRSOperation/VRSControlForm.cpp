#include "ShowVRSOperationResource.h"
#include "VRSControlForm.h"
#include "XAlgorithmBase.h"
#include "ReviewStructurePacket.h"

VRSControlForm::VRSControlForm(AlgorithmBase *RBase, int MoveDistance, int ZDistanceStep, bool reverse_x, bool reverse_y, QWidget *parent)
	:QDialog(parent),m_joyForm(this)
{
	m_RBase = RBase;
	m_ui.setupUi(this);
	setWindowFlags((windowFlags() & ~(Qt::WindowCloseButtonHint | Qt::WindowMinMaxButtonsHint | Qt::WindowTitleHint)) | Qt::CustomizeWindowHint);
	if(_reviewAlgorithm()!=NULL){
		CmdReqVRSMotorState reqMotorState(_reviewAlgorithm()->GetLayersBase());
		_reviewAlgorithm()->TransmitDirectly( &reqMotorState );
		if(reqMotorState.ret==true){
			m_ui.sbZDistanceValue->setValue( reqMotorState.z );
			m_ui.sbZDistanceValueStep->setValue(ZDistanceStep);
			m_ui.sbMoveLength->setValue(MoveDistance);
		}

		seqenceUpdateTimer().setInterval(500);
		seqenceUpdateTimer().setSingleShot(true);

		connect(&seqenceUpdateTimer(), SIGNAL(timeout()), this, SLOT(updateSequencePosition()));

		updateSequencePosition();
	}
	m_ui.cbXReverse->setChecked(reverse_x);
	m_ui.cbYReverse->setChecked(reverse_y);
	
	// joy
	m_joyForm.setWindowFlags((m_joyForm.windowFlags() & ~(Qt::WindowCloseButtonHint | Qt::WindowMinMaxButtonsHint | Qt::WindowTitleHint)) | Qt::CustomizeWindowHint | Qt::Window);
	m_joyForm.setXReverse(reverse_x);
	m_joyForm.setYReverse(reverse_y);
	m_joyForm.setMaxValue(MoveDistance);
	m_joyForm.show();
	connect(&m_joyForm, SIGNAL(joyout(qreal, qreal)), this, SLOT(joyin(qreal,qreal)));
}

void VRSControlForm::on_pbUp_clicked()
{
	if(m_ui.cbYReverse->isChecked()==false){
		moveVRS(0, -m_ui.sbMoveLength->value());
	}else{
		moveVRS(0, m_ui.sbMoveLength->value());
	}
}

void VRSControlForm::on_pbDown_clicked()
{
	if(m_ui.cbYReverse->isChecked()==false){
		moveVRS(0, m_ui.sbMoveLength->value());
	}else{
		moveVRS(0, -m_ui.sbMoveLength->value());
	}
}

void VRSControlForm::on_pbRight_clicked()
{
	if(m_ui.cbXReverse->isChecked()==false){
		moveVRS(m_ui.sbMoveLength->value());
	}else{
		moveVRS(-m_ui.sbMoveLength->value());
	}
}

void VRSControlForm::on_pbLeft_clicked()
{
	if(m_ui.cbXReverse->isChecked()==false){
		moveVRS(-m_ui.sbMoveLength->value());
	}else{
		moveVRS(m_ui.sbMoveLength->value());
	}
}

void VRSControlForm::moveVRS(int movex, int movey, int movez)
{
	AlgorithmBase *RBase = _reviewAlgorithm();
	if(RBase==NULL)return;

	CmdReqVRSMotorState reqVRSPosition(_reviewAlgorithm()->GetLayersBase());
	RBase->TransmitDirectly(&reqVRSPosition);

	CmdSetVRSMotorState setVRSPosition(_reviewAlgorithm()->GetLayersBase());
	setVRSPosition.setX(reqVRSPosition.x + movex, movex!=0);
	setVRSPosition.setY(reqVRSPosition.y + movey, movey!=0);
	setVRSPosition.setZ(reqVRSPosition.z + movez, movez!=0);

	RBase->TransmitDirectly( &setVRSPosition );
}

AlgorithmBase *VRSControlForm::_reviewAlgorithm()
{
	return m_RBase;
}

void VRSControlForm::showEvent(QShowEvent *event)
{
	QDialog::showEvent(event);

	if(parent()!=NULL){
		move(parentWidget()->geometry().topRight());
	}
}

void VRSControlForm::on_sbMoveLength_valueChanged(int value)
{
	m_joyForm.setMaxValue(value);
}

void VRSControlForm::on_pbReflesh_clicked()
{
	CmdReqVRSMotorState state(_reviewAlgorithm()->GetLayersBase());

	_reviewAlgorithm()->TransmitDirectly( &state );

	m_ui.sbZDistanceValue->setValue( state.z );
}

void VRSControlForm::on_pbSetZDistance_clicked()
{
	CmdSetVRSMotorState state(_reviewAlgorithm()->GetLayersBase());

	state.setZ( m_ui.sbZDistanceValue->value() );
	
	_reviewAlgorithm()->TransmitDirectly( &state );
}

void VRSControlForm::on_sbMoveDistanceStep_valueChanged(int value)
{
	m_ui.sbMoveLength->setSingleStep( value );
}

void VRSControlForm::on_sbZDistanceValueStep_valueChanged(int value)
{
	m_ui.sbZDistanceValue->setSingleStep( value );
}

void VRSControlForm::on_cbXReverse_toggled(bool reverse)
{
	m_joyForm.setXReverse(reverse);
}

void VRSControlForm::on_cbYReverse_toggled(bool reverse)
{
	m_joyForm.setYReverse(reverse);
}

void VRSControlForm::joyin(qreal x, qreal y)
{
	int moveDistance = m_ui.sbMoveLength->value();
	if(moveDistance==0)return;

	int movx = moveDistance * x;
	int movy = moveDistance * y;

	if(m_ui.cbXReverse->isChecked()==true){
		movx = -movx;
	}
	if(m_ui.cbYReverse->isChecked()==true){
		movy = -movy;
	}

	moveVRS(movx, movy);
}

void VRSControlForm::updateSequencePosition()
{
	CmdReqVRSMotorState reqMotorState(_reviewAlgorithm()->GetLayersBase());

	_reviewAlgorithm()->TransmitDirectly( &reqMotorState );

	if(reqMotorState.ret==true){
		m_ui.lbXPos->setText(QString::number(reqMotorState.x));
		m_ui.lbYPos->setText(QString::number(reqMotorState.y));
		m_ui.lbZPos->setText(QString::number(reqMotorState.z));
	}else{
		m_ui.lbXPos->setText(LangSolver.GetString(VRSControlForm_LS,LID_23)/*"UnKnown"*/);
		m_ui.lbYPos->setText(LangSolver.GetString(VRSControlForm_LS,LID_24)/*"UnKnown"*/);
		m_ui.lbZPos->setText(LangSolver.GetString(VRSControlForm_LS,LID_25)/*"UnKnown"*/);
	}

	seqenceUpdateTimer().start();
}

void VRSControlForm::moveEvent(QMoveEvent *event)
{
	QDialog::moveEvent(event);

	m_joyForm.move(frameGeometry().bottomLeft());
}
