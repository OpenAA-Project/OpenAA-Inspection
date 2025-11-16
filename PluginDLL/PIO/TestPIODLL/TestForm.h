#ifndef TESTFORM_H
#define TESTFORM_H

#include <QWidget>
#include <QTimer>
#include <QCheckBox>
#include <QToolButton>
#include <QMutex>
#include "XTypeDef.h"

namespace Ui {
    class TestForm;
}

class TestForm : public QWidget
{
    Q_OBJECT

	QTimer	TM;
	int		BitCountIn;
	int		BitCountOut;

	QCheckBox	*OutputBit[128];
	QCheckBox	*InputBit[128];
	QToolButton	*InputEnabled[128];
	bool		InputEnabledMode[128];

	volatile	BYTE		InputedData[128];


	DWORD		LastAccessTime;
public:
	short	BoardID;

public:
    explicit TestForm(short	_BoardID ,QWidget *parent = 0);
    ~TestForm();

	static	QMutex		IOAccess;

	BYTE	GetBufferedInBit(BYTE bitIndex);
	BYTE	GetBufferedInByte(BYTE byteIndex);

	BYTE	PIOGetBit(BYTE bitIndex);
	BYTE	PIOGetByte(BYTE byteIndex);

private slots:
	void	on_toolButtonInputEnabled_clicked();
	void	on_checkBoxInput_clicked();
	
	void	SlotTimeout ();

private:
    Ui::TestForm *ui;

	void	SetupForm(void);
};

#endif // TESTFORM_H
