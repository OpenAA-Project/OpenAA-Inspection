#ifndef PROPERTYLINEENHANCER1LFORM_H
#define PROPERTYLINEENHANCER1LFORM_H

#include <QDialog>
#include "XGUIFormBase.h"
#include "ui_PropertyLineEnhancer1LForm.h"
#include "XLineEnhancer1L.h"
#include "XStandardPropertyForm.h"

namespace Ui {
    class PropertyLineEnhancer1LForm;
}

class PropertyLineEnhancer1LForm : public GUIFormBase,public StandardPropertyForm
{
    Q_OBJECT

public:
    explicit PropertyLineEnhancer1LForm(LayersBase *Base,QWidget *parent = 0);
    ~PropertyLineEnhancer1LForm();

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

private slots:
    void on_pushButtonEditLibFolder_clicked();
    void on_tableWidgetLibList_clicked(const QModelIndex &index);
    void on_tableWidgetLibList_doubleClicked(const QModelIndex &index);
    void on_tableWidgetGeneratedLibList_clicked(const QModelIndex &index);
    void on_tableWidgetGeneratedLibList_doubleClicked(const QModelIndex &index);
    void on_pushButtonSetFrom_clicked();
    void on_pushButtonGetBack_clicked();
    void on_pushButtonSetFromAll_clicked();
    void on_pushButtonGetBackAll_clicked();
    void on_ButtonPickupTest_clicked();
    void on_ButtonPickupClearTest_clicked();
    void on_ButtonGenerateLibs_clicked();
    void on_radioButtonPickupArea_clicked();
    void on_radioButtonBlock_clicked();
    void on_radioButtonCalc_clicked();
    void on_radioButtonMatching_clicked();
    void on_ButtonLibSave_clicked();

    void on_pushButtonEditLibrary_clicked();

private:
    Ui::PropertyLineEnhancer1LForm *ui;
	LineEnhancer1LBase	*GetLineEnhancer1LBase(void);

	void	ShowLibList(void);
	void	ShowSelectedLibList(void);
	virtual void	BuildForShow(void)	override;

	//LineEnhancer1LLibrary	*TempLib;
	AlgorithmLibraryLevelContainer* TempLib;
	int						LibType;

	AlgorithmLibraryListContainer	LibList;
	AlgorithmLibraryListContainer	SelectedLibList;
	int		LibFolderID;

	void	ShowLibrary(AlgorithmLibraryLevelContainer &data);
	void	GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data);
	virtual	void	SetLibFolder(int LibFolderID ,const QString &LinFolderName)	override;
	void	SetLayersFromLib(IntList &Layers);
};


class	GUICmdCreateLineEnhancer1L : public GUICmdPacketBase
{
public:
	AlgorithmLibraryListContainer	SelectedLibList;
	IntList							LayerList;

	GUICmdCreateLineEnhancer1L(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdPickupTestList : public GUICmdPacketBase
{
public:
	IntList					LayerList;
	//LineEnhancer1LLibrary	*LibPoint;
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
	LineEnhancer1LDrawAttr::_DrawingArea	DrawingArea;
	QString	InstName;

	GUICmdSetDrawing(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
#endif // PROPERTYLINEENHANCER1LFORM_H
