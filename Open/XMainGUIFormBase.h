#pragma once

#include "NList.h"
#include <QString>
#include <QStringList>
#include <QIODevice>
#include "XTypeDef.h"
#include "XGUIDLL.h"
#include <QtGui>
#include <QVariant>
#include "XDataInLayer.h"
#include "XServiceForLayers.h"
#include "XMacroFunction.h"
#include "XGUIFormBase.h"
#include "XSingleExecuteBySocket.h"
#include "XDataComponent.h"
#include "XEntryPoint.h"
#include "XGUI.h"


class	MainGUIFormBase : public GUIFormBase
{
    Q_OBJECT

	friend	class	SocketForMainGUI;

	CheckSingleExecution	*Execution;
	QLocalServer			IdentificationServer;
	NPListPack<SocketForMainGUI>	IdentificationSocket;
	QSize					BaseSize;
	bool					ScaleFirst;	
	double					ScaleX;
	double					ScaleY;
	bool					ReEntrant;
public:
	bool	CloseCompletely;
	GUIInstancePack::_FormPosition	FormPosition;

	explicit	MainGUIFormBase(LayersBase	*_LayersBasePoint,QWidget *parent=NULL);

	virtual	void closeEvent ( QCloseEvent * event )	override;
	void	OutputPosition(void);
	virtual	void	ReflectAlignment(void)	override;

	void	SetSingleExecution(const QString &IdentifiedName);
	bool	CheckDoubleBoot(void);
	bool	RequirePrebootedSoftwareToTerminate(void);
	void	StartIdentificationServer(const QString &IdentificationName);
	virtual	void	GetGUIScale(double &XScale ,double &YScale)	override;
			void	SetGUIScale(double  XScale ,double  YScale);

protected:
	virtual	void	moveEvent ( QMoveEvent * event )	override;
	virtual	void	resizeEvent ( QResizeEvent * event )override;
private:
	QString	GetPositionFileName(void);
signals:
	void	QuitFromMenu();
	void	QuitUnconditionally();
	void	SignalMoveWindow(int PosX ,int PosY);
	void	SignalCloseEvent();
private slots:
	void	SlotTerminateFromOther();
	void	SlotNewConnection ();
};

inline	void	MainGUIFormBase::SetGUIScale(double  XScale ,double  YScale)
{
	ScaleX=XScale;
	ScaleY=YScale;
}

