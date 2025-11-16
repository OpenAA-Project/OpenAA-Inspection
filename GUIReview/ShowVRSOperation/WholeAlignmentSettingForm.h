#pragma once

#include <QWidget>

class ReviewPIBase;

class WholeAlignmentSettingForm : public QWidget
{
	Q_OBJECT

public:
	WholeAlignmentSettingForm(ReviewPIBase *RBase, QWidget *parent=NULL);

public slots:
	void updateCameraImage(const QImage &image);

public:
	ReviewPIBase *m_RBase;
	QImage m_cameraImage;
};
