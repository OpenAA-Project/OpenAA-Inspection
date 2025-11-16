#ifndef GENERALMENU_H
#define GENERALMENU_H

#include "generalmenu_global.h"
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include <QThread>
#include "XServiceForLayers.h"
#include <QMenuBar>

class	GeneralMenu : public GUIFormBase
{
	Q_OBJECT

	QMenuBar	MenuBar;
	NPListPack<MenuInfoContainer>	AllMenus;
public:
	GeneralMenu(LayersBase *Base ,QWidget *parent);
	~GeneralMenu(void);

	virtual	void	Prepare(void)		override;
	virtual void	BuildForShow(void)	override;
	virtual void	TabChanged(void)	override;

	virtual void	StartPage	(void)	override;
};


#endif // GENERALMENU_H
