#pragma once

#include <QDialog>

#include "ui_CameraAlignmentSettingForm.h"
#include "VRSControlForm.h"

class AlgorithmBase;

class CameraAlignmentSettingForm : public QDialog
{
	Q_OBJECT

public:
	CameraAlignmentSettingForm(AlgorithmBase *Base, int InitMoveDistance, int InitZDistanceStep, bool reverse_x=false, bool reverse_y=false, QWidget *parent=NULL);

public:
	QLabel *cameraLabel();
	InputRectInConstImageLabel *cameraLabelForm();
	QRectF resultNormalizationRect() const;

public:
	void setImageData(const QList<QImage> &imageList, const QList<QPoint> &outlineList, const QRect &alignment, bool firstExpand=false);

protected:
	virtual	void moveEvent(QMoveEvent *)			override;
	virtual	void	showEvent (QShowEvent * event)	override;

private slots:
    void on_pushButtonMove_clicked();

private:
	Ui::CameraAlignmentSettingClass ui;
	VRSControlForm	m_controlForm;
};

