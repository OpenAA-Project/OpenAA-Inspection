#ifndef SYNCDATABASE_H
#define SYNCDATABASE_H

#include <QMainWindow>
#include "ui_SyncDatabase.h"

#include "XSyncDatabase.h"
#include "XParamGlobal.h"
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QComboBox>
#include <QTranslator>
#include <QThread>
#include "XServiceForLayers.h"
#include <QTimer>

class	ParamGlobal;
class	LayersBase;
class	SyncDatabase;

class	ThreadProcessDatabase : public QThread,public ServiceForLayers
{
	Q_OBJECT
	SyncDatabase	*SBase;
public:
	volatile	bool	TerminationFlag;
	volatile	bool3	Halt;

	ThreadProcessDatabase(LayersBase *base,SyncDatabase *pbase ,QObject *parent);

	virtual	void	run(void);

signals:
	void	SignalCopyed();
	void	SignalUpdated();
	void	SignalRemoved();
	void	SignalStep();
};

class	SyncDBError : public NPList<SyncDBError>
{
	QString		TableName;
	QString		IDCode;
	QString		Message;
public:
	SyncDBError(void){}
	SyncDBError(const QString &_TableName ,const QString &_IDCode ,const QString &_Message)
		:TableName(_TableName),IDCode(_IDCode),Message(_Message){}
};


class	SyncErrorContainer : public NPListPack<SyncDBError>
{
public:
	SyncErrorContainer(void){}
};


class SyncDatabase : public QMainWindow,public ServiceForLayers
{
	Q_OBJECT

	QTimer			TM;
public:
	SyncAccess	SyncDB;
	ThreadProcessDatabase	ProcessDataBase;
	QStringList		ExcludedTables;

public:
	SyncDatabase(LayersBase *base
				,ParamGlobal*ParamCommData
				,QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~SyncDatabase();

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	ForceUpdateInsert(SyncErrorContainer &Errors,const QString &TableName,const QString &LastUpdateStr="LASTUPDATED");
	bool	CompareUpdate(SyncErrorContainer &Errors ,const QString &TableName);

private slots:
    void on_pushButtonRegister_clicked();
    void on_pushButtonTestCOnnectionDst_clicked();
    void on_toolButtonRun_clicked();
    void on_pushButtonForceUpdate_clicked();

signals:
	void	SignalSuccess(const QString &_TableName ,const QString &_IDCode ,const QString &_Message);
	void	SignalError  (const QString &_TableName ,const QString &_IDCode ,const QString &_Message);
	void	SignalProcessTable(const QString &_TableName);
private slots:
	void	SlotSuccess(const QString &_TableName ,const QString &_IDCode ,const QString &_Message);
	void	SlotError  (const QString &_TableName ,const QString &_IDCode ,const QString &_Message);
	void	SlotProcessTable(const QString &_TableName);
	void	SlotTimeOut();
    void on_pushButtonAddExcluded_clicked();

    void on_pushButtonDelExcluded_clicked();

private:
	Ui::SyncDatabaseClass ui;
	
	QStringList	TableList;
	SyncErrorContainer CompErrors;
	XTable *STablePointer;
	int		Step;

};



#endif // SYNCDATABASE_H
