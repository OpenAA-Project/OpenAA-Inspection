#if	!defined(XMLGeneralFunc_h)
#define	XMLGeneralFunc_h

#include <QString>
#include "XUnicodeGeneralFunc.h"
#include "XTypeDef.h"

wchar_t	*SkipSpace(wchar_t *fp);
QString	WChat2QString(wchar_t *src);
wchar_t	*CutWord(wchar_t *fp ,wchar_t *dest,int MaxDestLen);
wchar_t	*CutWordContent(wchar_t *fp ,wchar_t *dest,int MaxDestLen);
bool	IsDigit(wchar_t *fp ,double &RetNumber);

bool	GetXMLAttrStr (const QString &XMLSentense ,const QString &AttrName ,QString &RetAttrValue);
bool	GetXMLAttrInt (const QString &XMLSentense ,const QString &AttrName ,int &RetValue);
bool	GetXMLValueStr(const QString &XMLSentense ,const QString &TagName ,QString &RetTagValue);
bool	GetXMLCountValue(const QString &XMLSentense ,const QString &TagName ,int &RetCount);
	//<COUNT="90"/> ‚Ì‚æ‚¤‚È’l‚ðŽæ“¾

#endif
