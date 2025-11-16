#if	!defined(XLEARNINGINPAGE_H)
#define	XLEARNINGINPAGE_H

#include "XServiceForLayers.h"
#include "XGUIPacketForDLL.h"
#include "NList.h"
#include <QIODevice>
#include <QString>
#include "XTypeDef.h"
#include "XDateTime.h"
#include "XBoolList.h"

class	ImageBuffer;
class	LayersBase;
class	AlignmentPacket2D;
class	FlexArea;
class	LearningImage;
class	LearningImagePointerContainer;
class	ResultInspection;
class	ExecuteInitialAfterEditInfo;

class	LearningInPage : public ServiceForLayers
{
public:
	int		LocalPage;
	NPListPack<LearningImage>	LearningImageStocker;

	LearningInPage(int _Page ,LayersBase *Base);

	bool	LoadLearning(QIODevice *f);
	bool	SaveLearning(QIODevice *f);

	bool	LoadLearningDefault(void);
	bool	SaveLearningDefault(const QString &ImagePath);

	bool	SaveAlgorithm(const QString &ImagePath);
	bool	LoadAlgorithm(void);

	LearningImage *SetAllocImage(const XDateTime &_CreatedTime ,int GlobalPage
						, int LocalX1 ,int LocalY1 ,int LocalX2 ,int LocalY2
						, AlignmentPacket2D *Align);

	LearningImage	*Find(const XDateTime &CreatedTime)	const;
	bool	DeleteLearning(LearningImage *f);

	void	ClearResultMark(int layer);
	void	ClearAllMarkToProceed(int layer);
	void	SetResultMarkForLearning(int layer ,int x ,int y);

	void	RestoreAllLearningImageTarget(void);
	void	AddShowingLearningImageTarget(LearningImage *f);

	void	RestoreAllLearningImageMaster(void);
	void	AddShowingLearningImageMaster(LearningImage *f);

	void	MakeLearningImagePointerContainer(LearningImagePointerContainer &Container);

	void	EditLearning(void);

	void	ExecuteInitialAfterEdit	(ExecuteInitialAfterEditInfo &EInfo,bool ProgressStep=true);
	void	ExecuteStartByScanOnly	(bool ProgressStep=true);
	void	ExecuteStartByInspection(bool ProgressStep=true);
	void	ExecuteCaptured			(ListPhasePageLayerPack &CapturedList ,bool ProgressStep=true);
	void	ExecutePreAlignment		(bool ProgressStep=true);
	void	ExecuteAlignment		(bool ProgressStep=true);
	void	ExecutePreProcessing	(bool ProgressStep=true);
	void	ExecuteProcessing		(ResultInspection *Res ,bool ProgressStep=true);
	void	ExecuteProcessingRevived(bool ProgressStep=true);
	void	ExecutePostProcessing	(bool ProgressStep=true);
	void	ExecutePreScanning		(bool ProgressStep=true);
	void	ExecuteScanning			(bool ProgressStep=true);
	void	ExecutePostScanning		(bool ProgressStep=true);

private:
	QString	MakeFileName(void);
	QString	MakeAlgorithmFileName(const QString &AlgoBlobName);

};

#endif