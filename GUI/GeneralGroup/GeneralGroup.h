#ifndef GENERALPANEL_H
#define GENERALPANEL_H

#include "GeneralGroup_global.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include <QThread>
#include "XServiceForLayers.h"

class	GeneralGroup : public GUIFormBase
{
	Q_OBJECT

public:
	GeneralGroup(LayersBase *Base ,QWidget *parent);
	~GeneralGroup(void);

	virtual	void	Prepare(void)	override;

protected:
	virtual	void	resizeEvent(QResizeEvent *event)	override;
	virtual	void	showEvent(QShowEvent *event)		override;
	virtual	void	paintEvent(QPaintEvent *event)		override;
	
	virtual	void	BuildForShow(void)	override;
	virtual	void	ShowInPlayer(int64 shownInspectionID=-1)	override;
	virtual	void	StartPage	(void)	override;

private slots:
	void buttonToggled(bool on);

private:
	void updateButtonText(void);

protected:
	virtual	bool eventFilter(QObject *obj, QEvent *event)	override;

public:
	QString m_text;
	bool m_initState;
	QString m_selfPassword;
	bool	m_passwordLock;

private:
	QPushButton *m_button;
	QRect m_expandGeometry;
};


#endif // GENERALPANEL_H
