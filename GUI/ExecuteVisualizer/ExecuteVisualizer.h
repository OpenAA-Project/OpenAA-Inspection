#ifndef EXECUTEVISUALIZER_H
#define EXECUTEVISUALIZER_H

#include <QLabel>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XExecuteVisualizer.h"
#include "XExecuteVisualizerForLib.h"

class	ExecuteVisualizer : public GUIFormBase
{
	Q_OBJECT

	RunnerMap	*RMap;
public:
	QString	RunnerFileName;

	ExecuteVisualizer(LayersBase *Base ,QWidget *parent);
	~ExecuteVisualizer(void);

	virtual void	Prepare(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

private:


private slots:
};

#endif // EXECUTEVISUALIZER_H
