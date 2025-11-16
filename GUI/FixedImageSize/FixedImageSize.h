#ifndef FIXEDIMAGESIZE_H
#define FIXEDIMAGESIZE_H

#include "fixedimagesize_global.h"
#include "XServiceForLayers.h"
#include "XDataInLayer.h"
#include "XGUIFormBase.h"


class	FixedImageSize : public GUIFormBase
{
	Q_OBJECT

public:

	int32	PosLeft;
	int32	PosTop;
	int32	PosRight;
	int32	PosBottom;
	QString	DisplayImageName;

	FixedImageSize(LayersBase *Base ,QWidget *parent);
	~FixedImageSize(void);

	virtual void	BuildForShow(void)	override;
	virtual void	ShowInPlayer(int64 shownInspectionID=-1)	override;

private slots:

};
#endif // FIXEDIMAGESIZE_H
