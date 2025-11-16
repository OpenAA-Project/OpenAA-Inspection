#pragma once

#include <QDialog>
#include <QTimer>

#include "ui_VRSControlForm.h"

#include "VRSJoyForm.h"

class AlgorithmBase;

class VRSControlForm : public QDialog
{
	Q_OBJECT

public:
	VRSControlForm(AlgorithmBase *RBase, int MoveDistance, int ZDistanceStep, bool reverse_x=false, bool reverse_y=false, QWidget *parent=NULL);

public slots:
	void on_pbUp_clicked();
	void on_pbDown_clicked();
	void on_pbRight_clicked();
	void on_pbLeft_clicked();

	void on_pbReflesh_clicked();
	void on_pbSetZDistance_clicked();

	void on_sbMoveLength_valueChanged(int);
	void on_sbMoveDistanceStep_valueChanged(int);
	void on_sbZDistanceValueStep_valueChanged(int);

	void on_cbXReverse_toggled(bool);
	void on_cbYReverse_toggled(bool);

private slots:
	void joyin(qreal x, qreal y);
	void updateSequencePosition();

protected:
	virtual	void	showEvent (QShowEvent * event)	override;
	virtual	void 	moveEvent(QMoveEvent *)			override;

private:
	void moveVRS(int movex, int movey=0, int movez=0);// move VRS machine. If value is 0, VRS machine don't move.

private:
	AlgorithmBase *_reviewAlgorithm();

private:
	AlgorithmBase *m_RBase;
	Ui::VRSControlClass m_ui;
	VRSJoyForm		m_joyForm;
	QTimer m_updateSequenceUpdateTimer;

private:
	QTimer &seqenceUpdateTimer() { return m_updateSequenceUpdateTimer; };
};
