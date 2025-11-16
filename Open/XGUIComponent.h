#pragma once

#include "XTypeDef.h"
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QLineEdit>
#include <QCheckBox>
#include <QComboBox>
#include <QSpinBox>
#include <QMouseEvent>
#include <QVariant>
#include "NList.h"
#include "XIntClass.h"
#include "XLearningRegist.h"

class LogicDLL;

class MemberComponentList : public NPList<MemberComponentList>
{
	int32		MemberID;
	QWidget		*Comp;
	bool		Editted;
	QVariant	Value;
public:
	MemberComponentList (void);
	MemberComponentList (int MemberID ,QWidget *e);
	~MemberComponentList(void);

	QWidget	*GetComponent(void)	{	return Comp;		}
	int		GetMemberID(void)	{	return MemberID;	}
	void	SetEditted(bool b);
	bool	IsEditted(void)		{	return Editted;		}

	void		SetValue(const QVariant &c);
	QVariant	GetValue(void);

	void	Restore(void);
};


class AlgorithmComponentWindow : public QWidget
{
    Q_OBJECT

	NPListPack<MemberComponentList>	MemberComponentContainer;
	bool	EnableChangeMode;
	bool	InnerEnabled;
	LogicDLL	*OpenedLogicDLL;
public:
	AlgorithmComponentWindow(QWidget *p);
	~AlgorithmComponentWindow();

	void	RegisterComponent(int MemberID ,QSpinBox *e);
	void	RegisterComponent(int MemberID ,QDoubleSpinBox *e);
	void	RegisterComponent(int MemberID ,QLineEdit *e);
	void	RegisterComponent(int MemberID ,QCheckBox *e);
	void	RegisterComponent(int MemberID ,QComboBox *e);

	void	GetEdittedList(IntList &EdittedMemberID);
	void	SetEnableChangeMode(bool b)	{	EnableChangeMode=b;	}

	void	mouseRelease(QObject *obj);

	void	EmitChangeValue(void);
	virtual	QByteArray	RequiteItemDataInWindow(void)	{	return QByteArray();	}
	void	SetLogicDLL(LogicDLL *v);
signals:
	void	SignalChangeValue();
	//void	SignalClosed();
private slots:
	void	SlotValueChangedInt(int n);
	void	SlotValueChangedDouble(double n);
	void	SlotTextChanged(const QString &text);
	void	SlotStateChanged(int state);
	void	SlotCurrentIndexChanged(int index);
protected:
	void	closeEvent(QCloseEvent *event);
};

