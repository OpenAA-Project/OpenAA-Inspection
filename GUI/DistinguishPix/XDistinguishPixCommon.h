#if	!defined(XDistinguishPixCommon_H)
#define	XDistinguishPixCommon_H

#include "XGUIFormBase.h"
#include "XGUIPacketForDLL.h"

class	FileListContainer;
class	FileListLeaf;

class	JudgeTargetBroadcaster : public SpecifiedBroadcaster
{
public:
	QString	FolderName;
	QString	FileName;
	int		Judgement;
	QString	JudgeStr;

	JudgeTargetBroadcaster(void){}
};

class	CmdReqFileListContainer: public GUIDirectMessage
{
public:
	FileListContainer	*Container;

	CmdReqFileListContainer(LayersBase *base):GUIDirectMessage(base){}
	CmdReqFileListContainer(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdReqLoadImageIntoTarget: public GUIDirectMessage
{
public:
	FileListLeaf	*Pointer;
	bool			Success;

	CmdReqLoadImageIntoTarget(LayersBase *base):GUIDirectMessage(base){}
	CmdReqLoadImageIntoTarget(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};


//--------------------------------------------------------------------------------

class	FileListLeaf : public NPList<FileListLeaf>
{
public:
	QString		UFolderName;
	QString		FileName;
	int32		Judgement;	//0:Undefined	1:OK	2:NG
	QString		JudgeStr;	//This is not saved. This is from Button text

	FileListLeaf(void);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	FileListContainer : public NPListPack<FileListLeaf>
{
public:
	FileListContainer(void){}

	FileListLeaf	*Find(const QString &UFolderName,const QString &FileName);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

#endif