#ifndef PROPERTYLINEENHANCERFORM_H
#define PROPERTYLINEENHANCERFORM_H

#include "XGUIFormBase.h"
#include "ui_PropertyLineEnhancerForm.h"
#include "XLineEnhancer.h"
#include "XStandardPropertyForm.h"

class PropertyLineEnhancerForm : public GUIFormBase,public StandardPropertyForm
{
	Q_OBJECT

public:
	PropertyLineEnhancerForm(LayersBase *Base,QWidget *parent = 0);
	~PropertyLineEnhancerForm();

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

private:
	Ui::PropertyLineEnhancerFormClass ui;
	LineEnhancerBase	*GetLineEnhancerBase(void);

	void	ShowLibList(void);
	void	ShowSelectedLibList(void);
	virtual void	BuildForShow(void)	override;

	//LineEnhancerLibrary	*TempLib;
	AlgorithmLibraryLevelContainer* TempLib;
	int						LibType;

	AlgorithmLibraryListContainer	LibList;
	AlgorithmLibraryListContainer	SelectedLibList;
	int		LibFolderID;

	void	ShowLibrary(AlgorithmLibraryLevelContainer &data);
	void	GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data);
	virtual	void	SetLibFolder(int LibFolderID ,const QString &LinFolderName)	override;

	virtual	bool	SaveContent(QIODevice *f)	override;
	virtual	bool	LoadContent(QIODevice *f)	override;

private slots:
	void on_tableWidgetLibList_clicked(const QModelIndex &);
	void on_ButtonLibSave_clicked();
	void on_radioButtonMatching_toggled(bool);
	void on_radioButtonCalc_toggled(bool);
	void on_radioButtonBlock_toggled(bool);
	void on_radioButtonPickupArea_toggled(bool);
	void on_tableWidgetGeneratedLibList_clicked(const QModelIndex &);
	void on_ButtonPickupClearTest_clicked();
	void on_ButtonPickupTest_clicked();
	void on_pushButtonGetBackAll_clicked();
	void on_pushButtonSetFromAll_clicked();
	void on_ButtonGenerateLibs_clicked();
	void on_pushButtonGetBack_clicked();
	void on_pushButtonSetFrom_clicked();
	void on_tableWidgetGeneratedLibList_doubleClicked(QModelIndex);
	void on_tableWidgetLibList_doubleClicked(QModelIndex);
	void on_pushButtonEditLibFolder_clicked();
	void on_pushButtonEditLibrary_clicked();
};


class	GUICmdCreateLineEnhancer : public GUICmdPacketBase
{
public:
	AlgorithmLibraryListContainer	SelectedLibList;

	GUICmdCreateLineEnhancer(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdPickupTestList : public GUICmdPacketBase
{
public:
	//LineEnhancerLibrary	*LibPoint;
	AlgorithmLibraryLevelContainer	*LibPoint;
	bool	CreatedInside;

	GUICmdPickupTestList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);
	~GUICmdPickupTestList(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdTestClear : public GUICmdPacketBase
{
public:
	GUICmdTestClear(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSetDrawing : public GUICmdPacketBase
{
public:
	LineEnhancerDrawAttr::_DrawingArea	DrawingArea;
	QString	InstName;

	GUICmdSetDrawing(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif // PROPERTYLINEENHANCERFORM_H
