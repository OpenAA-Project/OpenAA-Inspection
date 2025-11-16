#if	!defined(XReviewCameraCommon_h)
#define	XReviewCameraCommon_h

#include <QIODevice>
#include <QWidget>
#include "XTypeDef.h"
#include "XGUIPacketForDLL.h"
#include <QImage>


class	CmdReqImageFromReviewCamera : public GUIDirectMessage
{
public:
	int		ImageWidth;
	int		ImageHeight;
	QImage	Image;
	bool	Result;

	CmdReqImageFromReviewCamera(LayersBase *base)
		:GUIDirectMessage(base){	ImageWidth=0;	ImageHeight=0;	}
};


#endif