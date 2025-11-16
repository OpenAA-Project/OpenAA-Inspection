#ifndef SAVEMASTERIMAGEININSPECTION_H
#define SAVEMASTERIMAGEININSPECTION_H

#include "savemasterimageininspection_global.h"
#include "XServiceForLayers.h"
#include <QTcpSocket>
#include <QThread>
#include "XDataInLayer.h"
#include "XGUIFormBase.h"

class SaveMasterImageInInspection : public GUIFormBase
{
	Q_OBJECT

public:
	double	ZoomRate;

	SaveMasterImageInInspection(LayersBase *Base ,QWidget *parent);
	~SaveMasterImageInInspection(void);

	virtual	void	Prepare(void)	override;
	virtual void	ShowInPlayer(int64 shownInspectionID=-1)	override;

private slots:

};

class	GUICmdReqImageInInspection  : public GUICmdPacketBase
{
public:
	double	ZoomRate;
	int		MasterCode;
	int		MachineID;
	QString		ImagePath;

	GUICmdReqImageInInspection(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


#endif // SAVEMASTERIMAGEININSPECTION_H
