#if	!defined(XGUIPacketGeneral_h)
#define	XGUIPacketGeneral_h

#include "XGUIPacketForDLL.h"

class	GUICmdReleaseSelectImagePanel : public GUICmdPacketBase
{
public:
	QString		AlgoRoot;
	QString		AlgoName;

	GUICmdReleaseSelectImagePanel(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


class	GUICmdSelectByLibs : public GUICmdPacketBase	//ライブラリによるアイテム選択要求コマンド
{
public:
	QString		AlgoRoot;
	QString		AlgoName;
	SelectLibListContainer	SelectedList;

	GUICmdSelectByLibs(AlgorithmBase	*base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif