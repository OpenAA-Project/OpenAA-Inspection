#ifndef SHORTCUTKEYINVISIBLE_H
#define SHORTCUTKEYINVISIBLE_H

#include "shortcutkeyinvisible_global.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include <QThread>
#include "XServiceForLayers.h"
#include <QShortcut>

class	SignalOperandInt;

struct	ShortcutKeyInfoList: public QObject
{
    Q_OBJECT
public:
enum	AdditionalKey
	{
		_None		=0
		,_Ctrl		=1
		,_Shift		=2
		,_Alt		=3
		,_CtrlShift	=4
		,_AltShift	=5
		,_AltCtrl	=6
	};

	int				ID;			//This is added in Prepare function
	AdditionalKey	AddedKey;
	class	_KeyCode
	{
	public:
		DWORD			QtKeyCode;
		DWORD			WinKeyCode;

		_KeyCode(DWORD qtkey, DWORD winkey){	QtKeyCode=qtkey;	WinKeyCode=winkey;	}
		_KeyCode(void)	{	QtKeyCode=0;	WinKeyCode=0;	}
	}KeyCode;
	char			*DLLRoot;
	char			*DLLName;
	char			*DLLInst;
	char			*ObjPath;
	char			*ObjName;
	
	enum	ActionType
	{
		 _NoAction				=0
		,_PushButton			=1
		,_DoubleClickList		=2
		,_SelectComboboxList	=3
		,_Check					=4
		,_Uncheck				=5
		,_ToggleCheck			=6
		,_InputInEdit			=7
		,_OutSequenceSystemWord	=8
	};

	ActionType		Action;

	union{
		char			ExtraData[32];
		DWORD			Numb;
	};
	QShortcut	*Shortcut;

	ShortcutKeyInfoList(void);
	~ShortcutKeyInfoList(void);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	CopyFrom(struct ShortcutKeyInfoList &Src);
	void	Execute(GUIFormBase *w);

signals:
	void	SignalActivateKey(int ID);
private slots:
	void	SlotActivateKey();

private:
	QWidget	*GetControl(LayersBase *Base,QWidget *MainWidget);
};


class	ShortcutKeyInvisible: public GUIFormBase
{
    Q_OBJECT
public:
	static	struct	ShortcutKeyInfoList		ShortcutKeyDim[1000];
	static	int								CountOfShortcut;

	int					RegSysShortcutKey;
	SignalOperandInt	*oSysShortcutKey;

	QByteArray	KeyArray;

	ShortcutKeyInvisible(LayersBase *Base ,QWidget *parent);
	~ShortcutKeyInvisible();

	virtual	void	Prepare(void)	override;


private:
	static	int	MakeDefaultKey(ShortcutKeyInfoList::AdditionalKey AddedKey,int StartIndex);

private slots:
	void	SlotExecuteForByteArray(const QString &Category ,const QString &KeyName ,QByteArray &data);
	void	SlotActivateKey(int ID);
};

#endif // SHORTCUTKEYINVISIBLE_H
