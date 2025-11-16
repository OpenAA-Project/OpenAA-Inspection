#if	!defined(XPASSWORDQWIDGET_H)
#define	XPASSWORDQWIDGET_H

#include <QObject>
#include "NList.h"
#include "XServiceForLayers.h"

class	PasswordFilterPointerList;
class	PasswordFilter;
class	PasswordInControl;


class	PasswordInQWodget
{
	QWidget	*ParentWidget;
	LayersBase	*Base;
public:
	PasswordInQWodget(LayersBase *base ,QWidget *parent);

	void	SetupPassword(void);

public:
	void	InstallEventHandler(PasswordFilter *f,NPListPack<PasswordFilterPointerList> &PasswordFilterPointerData);
	void	InstallEventHandlerOnlyPassword(PasswordFilter *f,PasswordInControl *c);

};


#endif