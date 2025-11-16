#include "ShowVRSOperationResource.h"
#include "WholeAlignmentSettingForm.h"



WholeAlignmentSettingForm::WholeAlignmentSettingForm(ReviewPIBase *RBase, QWidget *parent)
	:QWidget(parent),m_RBase(RBase),m_cameraImage()
{
}

void WholeAlignmentSettingForm::updateCameraImage(const QImage &image)
{
	if(m_cameraImage!=image){
		m_cameraImage = image;
	}
}
