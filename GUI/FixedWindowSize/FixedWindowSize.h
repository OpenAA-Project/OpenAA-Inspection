#ifndef FIXEDWINDOWSIZE_H
#define FIXEDWINDOWSIZE_H

#include "fixedwindowsize_global.h"
#include "XServiceForLayers.h"
#include "XDataInLayer.h"
#include "XGUIFormBase.h"


class	FixedWindowSize : public GUIFormBase
{
	Q_OBJECT

public:
	int32	PosLeft;
	int32	PosTop;
	int32	PosRight;
	int32	PosBottom;

	FixedWindowSize(LayersBase *Base ,QWidget *parent);
	~FixedWindowSize(void);

	virtual void	Prepare(void)	override;

private slots:

};
#endif // FIXEDWINDOWSIZE_H
