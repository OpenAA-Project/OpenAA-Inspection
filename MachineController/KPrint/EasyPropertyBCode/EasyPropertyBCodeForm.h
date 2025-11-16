#ifndef EASYPROPERTYBCODEFORM_H
#define EASYPROPERTYBCODEFORM_H

#include <QModelIndex>
#include "XGUIFormBase.h"
#include "XIntegrationPacketComm.h"
#include "XServiceForLayers.h"
#include "XBCRInspection.h"

namespace Ui {
class EasyPropertyBCodeForm;
}

class EasyPropertyBCodeForm : public GUIFormBase
{
    Q_OBJECT

    int		CheckType;		//0:Read	1:Quality Check
    double	QuilityGrade;
    BCRGradeListContainer	GradeList;
	BCRContainer			GridList;
public:
	int32	SlaveNo;
	
	explicit EasyPropertyBCodeForm(LayersBase *Base ,QWidget *parent = 0);
    ~EasyPropertyBCodeForm();

    virtual void	Prepare(void)		override;
	virtual	void	BuildForShow(void)  override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet) override;
	virtual	void	StartInitial(void)	override;
private slots:
    void on_pushButtonQualityLoad_clicked();
    void on_pushButtonQualitySave_clicked();
    void on_tableWidgetItemList_itemSelectionChanged();
    void on_pushButtonSetQuality_clicked();
    void on_tableWidgetItemList_clicked(const QModelIndex &index);

private:
    Ui::EasyPropertyBCodeForm *ui;

	void	ShowGrid(void);
	void    LoadGradeListFromWindow(BCRGradeListContainer &List);
    void    ShowGradeList(BCRGradeListContainer &List);
};

class	CmdReqBCodeInfo : public GUIDirectMessage
{
public:
	enum _BCodeType
	{
		_ReadBCode			=1
		,_QualityBCode		=2
	}BCodeType;
    double	QuilityGrade;
    BCRGradeListContainer	GradeList;

	CmdReqBCodeInfo(LayersBase *base):GUIDirectMessage(base){}
	CmdReqBCodeInfo(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdShowBCodeGrid : public GUIDirectMessage
{
public:
	CmdShowBCodeGrid(LayersBase *base):GUIDirectMessage(base){}
	CmdShowBCodeGrid(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	IntegrationCmdReqBCodeList : public IntegrationCmdPacketBase
{
public:
	int	Page;
	int	ItemID;

	IntegrationCmdReqBCodeList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	

private:
};

class	IntegrationCmdAckBCodeList : public IntegrationCmdPacketBase
{
public:
	int						CheckType;		//0:Read	1:Quality Check
    double					QuilityGrade;
    BCRGradeListContainer	GradeList;

	IntegrationCmdAckBCodeList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName){}

private:
};

class	IntegrationCmdReqBCodeItems : public IntegrationCmdPacketBase
{
public:
	IntegrationCmdReqBCodeItems(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f){	return true;	}
	virtual	bool	Save(QIODevice *f){	return true;	}

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	

private:
};

class	IntegrationCmdAckBCodeItems : public IntegrationCmdPacketBase
{
public:
	BCRContainer			GridList;

	IntegrationCmdAckBCodeItems(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName){}

private:
};


class	IntegrationCmdSetBCodeItem : public IntegrationCmdPacketBase
{
public:
	int						Page;
	int						ItemID;
	int						CheckType;		//0:Read	1:Quality Check
    double					QuilityGrade;
    BCRGradeListContainer	GradeList;

	IntegrationCmdSetBCodeItem(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	

private:
};

#endif // EASYPROPERTYBCODEFORM_H
