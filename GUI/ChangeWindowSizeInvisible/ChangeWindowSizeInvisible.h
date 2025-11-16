#ifndef CHANGEWINDOWSIZEINVISIBLE_H
#define CHANGEWINDOWSIZEINVISIBLE_H

#include "changewindowsizeinvisible_global.h"
#include "XServiceForLayers.h"
#include "XDataInLayer.h"
#include "XGUIFormBase.h"

class	ChangeWindowSizeInvisible : public GUIFormBase
{
	Q_OBJECT

	int		CurrentMaxSizeW;
	int		CurrentMaxSizeH;
public:

	bool	MaximizeWindowOnStartPage;
	bool	ReturnWindowSizewOnStartPage;
	bool	MaximizeWindowOnLeavePage;
	bool	ReturnWindowSizewOnLeavePage;

	ChangeWindowSizeInvisible(LayersBase *Base ,QWidget *parent);
	~ChangeWindowSizeInvisible(void);

	virtual void	Prepare(void)	override;

	virtual void	StartPage	(void)	override;
	virtual void	LeavePage	(void)	override;


private slots:

};
#endif // CHANGEWINDOWSIZEINVISIBLE_H
