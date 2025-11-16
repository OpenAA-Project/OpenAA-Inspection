#include "ShortcutKeyInvisible.h"
#include "XDataInLayer.h"

struct	ShortcutKeyInfoList		ShortcutKeyInvisible::ShortcutKeyDim[1000];
int								ShortcutKeyInvisible::CountOfShortcut;

#ifdef _MSC_VER
#include <windows.h>


int	ShortcutKeyInvisible::MakeDefaultKey(ShortcutKeyInfoList::AdditionalKey AddedKey,int StartIndex)
{
	int	Ret=StartIndex;

	ShortcutKeyDim[Ret++].KeyCode=	ShortcutKeyInfoList::_KeyCode(	Qt::Key_Escape		,VK_ESCAPE	);
	ShortcutKeyDim[Ret++].KeyCode=	ShortcutKeyInfoList::_KeyCode(	Qt::Key_Tab			,VK_TAB		);
	ShortcutKeyDim[Ret++].KeyCode=	ShortcutKeyInfoList::_KeyCode(	Qt::Key_Backspace	,VK_BACK	);
	ShortcutKeyDim[Ret++].KeyCode=	ShortcutKeyInfoList::_KeyCode(	Qt::Key_Enter		,VK_RETURN	);
	ShortcutKeyDim[Ret++].KeyCode=	ShortcutKeyInfoList::_KeyCode(	Qt::Key_Insert		,VK_INSERT	);
	ShortcutKeyDim[Ret++].KeyCode=	ShortcutKeyInfoList::_KeyCode(	Qt::Key_Delete		,VK_DELETE	);
	ShortcutKeyDim[Ret++].KeyCode=	ShortcutKeyInfoList::_KeyCode(	Qt::Key_Pause		,VK_PAUSE	);
	ShortcutKeyDim[Ret++].KeyCode=	ShortcutKeyInfoList::_KeyCode(	Qt::Key_Print		,VK_PRINT	);
	ShortcutKeyDim[Ret++].KeyCode=	ShortcutKeyInfoList::_KeyCode(	Qt::Key_Home		,VK_HOME	);
	ShortcutKeyDim[Ret++].KeyCode=	ShortcutKeyInfoList::_KeyCode(	Qt::Key_End			,VK_END	);
	ShortcutKeyDim[Ret++].KeyCode=	ShortcutKeyInfoList::_KeyCode(	Qt::Key_Left		,VK_LEFT	);
	ShortcutKeyDim[Ret++].KeyCode=	ShortcutKeyInfoList::_KeyCode(	Qt::Key_Up			,VK_UP	);
	ShortcutKeyDim[Ret++].KeyCode=	ShortcutKeyInfoList::_KeyCode(	Qt::Key_Right		,VK_RIGHT	);
	ShortcutKeyDim[Ret++].KeyCode=	ShortcutKeyInfoList::_KeyCode(	Qt::Key_Down		,VK_DOWN	);
	ShortcutKeyDim[Ret++].KeyCode=	ShortcutKeyInfoList::_KeyCode(	Qt::Key_PageUp		,VK_PRIOR	);
	ShortcutKeyDim[Ret++].KeyCode=	ShortcutKeyInfoList::_KeyCode(	Qt::Key_PageDown	,VK_NEXT	);
	ShortcutKeyDim[Ret++].KeyCode=	ShortcutKeyInfoList::_KeyCode(	Qt::Key_ScrollLock	,VK_SCROLL	);
	ShortcutKeyDim[Ret++].KeyCode=	ShortcutKeyInfoList::_KeyCode(	Qt::Key_F1			,VK_F1	);
	ShortcutKeyDim[Ret++].KeyCode=	ShortcutKeyInfoList::_KeyCode(	Qt::Key_F2			,VK_F2	);
	ShortcutKeyDim[Ret++].KeyCode=	ShortcutKeyInfoList::_KeyCode(	Qt::Key_F3			,VK_F3	);
	ShortcutKeyDim[Ret++].KeyCode=	ShortcutKeyInfoList::_KeyCode(	Qt::Key_F4			,VK_F4	);
	ShortcutKeyDim[Ret++].KeyCode=	ShortcutKeyInfoList::_KeyCode(	Qt::Key_F5			,VK_F5	);
	ShortcutKeyDim[Ret++].KeyCode=	ShortcutKeyInfoList::_KeyCode(	Qt::Key_F6			,VK_F6	);
	ShortcutKeyDim[Ret++].KeyCode=	ShortcutKeyInfoList::_KeyCode(	Qt::Key_F7			,VK_F7	);
	ShortcutKeyDim[Ret++].KeyCode=	ShortcutKeyInfoList::_KeyCode(	Qt::Key_F8			,VK_F8	);
	ShortcutKeyDim[Ret++].KeyCode=	ShortcutKeyInfoList::_KeyCode(	Qt::Key_F9			,VK_F9	);
	ShortcutKeyDim[Ret++].KeyCode=	ShortcutKeyInfoList::_KeyCode(	Qt::Key_F10			,VK_F10	);
	ShortcutKeyDim[Ret++].KeyCode=	ShortcutKeyInfoList::_KeyCode(	Qt::Key_F11			,VK_F11	);
	ShortcutKeyDim[Ret++].KeyCode=	ShortcutKeyInfoList::_KeyCode(	Qt::Key_F12			,VK_F12	);
	ShortcutKeyDim[Ret++].KeyCode=	ShortcutKeyInfoList::_KeyCode(	Qt::Key_Space		,VK_SPACE	);
	//ShortcutKeyDim[Ret++].KeyCode=	ShortcutKeyInfoList::_KeyCode(	Qt::Key_Percent	,	);
	//ShortcutKeyDim[Ret++].KeyCode=	ShortcutKeyInfoList::_KeyCode(	Qt::Key_Ampersand	,	);
	//ShortcutKeyDim[Ret++].KeyCode=	ShortcutKeyInfoList::_KeyCode(	Qt::Key_Apostrophe	,	);
	ShortcutKeyDim[Ret++].KeyCode=	ShortcutKeyInfoList::_KeyCode(	Qt::Key_Asterisk	,VK_MULTIPLY	);
	ShortcutKeyDim[Ret++].KeyCode=	ShortcutKeyInfoList::_KeyCode(	Qt::Key_Plus		,VK_ADD	);
	ShortcutKeyDim[Ret++].KeyCode=	ShortcutKeyInfoList::_KeyCode(	Qt::Key_Comma		,VK_SEPARATOR	);
	ShortcutKeyDim[Ret++].KeyCode=	ShortcutKeyInfoList::_KeyCode(	Qt::Key_Minus		,VK_SUBTRACT	);
	ShortcutKeyDim[Ret++].KeyCode=	ShortcutKeyInfoList::_KeyCode(	Qt::Key_Period		,VK_DECIMAL	);
	ShortcutKeyDim[Ret++].KeyCode=	ShortcutKeyInfoList::_KeyCode(	Qt::Key_Slash		,VK_DIVIDE	);
	ShortcutKeyDim[Ret++].KeyCode=	ShortcutKeyInfoList::_KeyCode(	Qt::Key_0			,VK_NUMPAD0	);
	ShortcutKeyDim[Ret++].KeyCode=	ShortcutKeyInfoList::_KeyCode(	Qt::Key_1			,VK_NUMPAD1	);
	ShortcutKeyDim[Ret++].KeyCode=	ShortcutKeyInfoList::_KeyCode(	Qt::Key_2			,VK_NUMPAD2	);
	ShortcutKeyDim[Ret++].KeyCode=	ShortcutKeyInfoList::_KeyCode(	Qt::Key_3			,VK_NUMPAD3	);
	ShortcutKeyDim[Ret++].KeyCode=	ShortcutKeyInfoList::_KeyCode(	Qt::Key_4			,VK_NUMPAD4	);
	ShortcutKeyDim[Ret++].KeyCode=	ShortcutKeyInfoList::_KeyCode(	Qt::Key_5			,VK_NUMPAD5	);
	ShortcutKeyDim[Ret++].KeyCode=	ShortcutKeyInfoList::_KeyCode(	Qt::Key_6			,VK_NUMPAD6	);
	ShortcutKeyDim[Ret++].KeyCode=	ShortcutKeyInfoList::_KeyCode(	Qt::Key_7			,VK_NUMPAD7	);
	ShortcutKeyDim[Ret++].KeyCode=	ShortcutKeyInfoList::_KeyCode(	Qt::Key_8			,VK_NUMPAD8	);
	ShortcutKeyDim[Ret++].KeyCode=	ShortcutKeyInfoList::_KeyCode(	Qt::Key_9			,VK_NUMPAD9	);
	//ShortcutKeyDim[Ret++].KeyCode=	ShortcutKeyInfoList::_KeyCode(	Qt::Key_Colon		,	);
	//ShortcutKeyDim[Ret++].KeyCode=	ShortcutKeyInfoList::_KeyCode(	Qt::Key_Semicolon		,	);
	//ShortcutKeyDim[Ret++].KeyCode=	ShortcutKeyInfoList::_KeyCode(	Qt::Key_Less		,	);
	//ShortcutKeyDim[Ret++].KeyCode=	ShortcutKeyInfoList::_KeyCode(	Qt::Key_Equal		,	);
	//ShortcutKeyDim[Ret++].KeyCode=	ShortcutKeyInfoList::_KeyCode(	Qt::Key_Greater		,	);
	//ShortcutKeyDim[Ret++].KeyCode=	ShortcutKeyInfoList::_KeyCode(	Qt::Key_Question		,	);
	//ShortcutKeyDim[Ret++].KeyCode=	ShortcutKeyInfoList::_KeyCode(	Qt::Key_At		,	);
	/*
	ShortcutKeyDim[Ret++].KeyCode=	ShortcutKeyInfoList::_KeyCode(	Qt::Key_A			,VK_A	);
	ShortcutKeyDim[Ret++].KeyCode=	ShortcutKeyInfoList::_KeyCode(	Qt::Key_B			,VK_B	);
	ShortcutKeyDim[Ret++].KeyCode=	ShortcutKeyInfoList::_KeyCode(	Qt::Key_C			,VK_C	);
	ShortcutKeyDim[Ret++].KeyCode=	ShortcutKeyInfoList::_KeyCode(	Qt::Key_D			,VK_D	);
	ShortcutKeyDim[Ret++].KeyCode=	ShortcutKeyInfoList::_KeyCode(	Qt::Key_E			,VK_E	);
	ShortcutKeyDim[Ret++].KeyCode=	ShortcutKeyInfoList::_KeyCode(	Qt::Key_F			,VK_F	);
	ShortcutKeyDim[Ret++].KeyCode=	ShortcutKeyInfoList::_KeyCode(	Qt::Key_G			,VK_G	);
	ShortcutKeyDim[Ret++].KeyCode=	ShortcutKeyInfoList::_KeyCode(	Qt::Key_H			,VK_H	);
	ShortcutKeyDim[Ret++].KeyCode=	ShortcutKeyInfoList::_KeyCode(	Qt::Key_I			,VK_I	);
	ShortcutKeyDim[Ret++].KeyCode=	ShortcutKeyInfoList::_KeyCode(	Qt::Key_J			,VK_J	);
	ShortcutKeyDim[Ret++].KeyCode=	ShortcutKeyInfoList::_KeyCode(	Qt::Key_K			,VK_K	);
	ShortcutKeyDim[Ret++].KeyCode=	ShortcutKeyInfoList::_KeyCode(	Qt::Key_L			,VK_L	);
	ShortcutKeyDim[Ret++].KeyCode=	ShortcutKeyInfoList::_KeyCode(	Qt::Key_M			,VK_M	);
	ShortcutKeyDim[Ret++].KeyCode=	ShortcutKeyInfoList::_KeyCode(	Qt::Key_N			,VK_N	);
	ShortcutKeyDim[Ret++].KeyCode=	ShortcutKeyInfoList::_KeyCode(	Qt::Key_O			,VK_O	);
	ShortcutKeyDim[Ret++].KeyCode=	ShortcutKeyInfoList::_KeyCode(	Qt::Key_P			,VK_P	);
	ShortcutKeyDim[Ret++].KeyCode=	ShortcutKeyInfoList::_KeyCode(	Qt::Key_Q			,VK_Q	);
	ShortcutKeyDim[Ret++].KeyCode=	ShortcutKeyInfoList::_KeyCode(	Qt::Key_R			,VK_R	);
	ShortcutKeyDim[Ret++].KeyCode=	ShortcutKeyInfoList::_KeyCode(	Qt::Key_S			,VK_S	);
	ShortcutKeyDim[Ret++].KeyCode=	ShortcutKeyInfoList::_KeyCode(	Qt::Key_T			,VK_T	);
	ShortcutKeyDim[Ret++].KeyCode=	ShortcutKeyInfoList::_KeyCode(	Qt::Key_U			,VK_U	);
	ShortcutKeyDim[Ret++].KeyCode=	ShortcutKeyInfoList::_KeyCode(	Qt::Key_V			,VK_V	);
	ShortcutKeyDim[Ret++].KeyCode=	ShortcutKeyInfoList::_KeyCode(	Qt::Key_W			,VK_W	);
	ShortcutKeyDim[Ret++].KeyCode=	ShortcutKeyInfoList::_KeyCode(	Qt::Key_X			,VK_X	);
	ShortcutKeyDim[Ret++].KeyCode=	ShortcutKeyInfoList::_KeyCode(	Qt::Key_Y			,VK_Y	);
	ShortcutKeyDim[Ret++].KeyCode=	ShortcutKeyInfoList::_KeyCode(	Qt::Key_Z			,VK_Z	);
	*/
	//ShortcutKeyDim[Ret++].KeyCode=	ShortcutKeyInfoList::_KeyCode(	Qt::Key_BracketLeft		,	);
	//ShortcutKeyDim[Ret++].KeyCode=	ShortcutKeyInfoList::_KeyCode(	Qt::Key_Backslash		,	);
	//ShortcutKeyDim[Ret++].KeyCode=	ShortcutKeyInfoList::_KeyCode(	Qt::Key_BracketRight		,	);
	//ShortcutKeyDim[Ret++].KeyCode=	ShortcutKeyInfoList::_KeyCode(	Qt::Key_AsciiCircum		,	);
	//ShortcutKeyDim[Ret++].KeyCode=	ShortcutKeyInfoList::_KeyCode(	Qt::Key_Underscore		,	);
	//ShortcutKeyDim[Ret++].KeyCode=	ShortcutKeyInfoList::_KeyCode(	Qt::Key_QuoteLeft		,	);
	//ShortcutKeyDim[Ret++].KeyCode=	ShortcutKeyInfoList::_KeyCode(	Qt::Key_BraceLeft		,	);

	for(int i=StartIndex;i<Ret;i++){
		ShortcutKeyDim[i].AddedKey	=AddedKey;
	}
	return Ret;
}

#else

int	ShortcutKeyInvisible::MakeDefaultKey(ShortcutKeyInfoList::AdditionalKey AddedKey,int StartIndex)
{
	return 0;
}

#endif