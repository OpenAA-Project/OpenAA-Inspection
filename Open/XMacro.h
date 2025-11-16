#if	!defined(XMACRO_H)
#define	XMACRO_H

#ifdef __GNUC__
#include<string.h>
#define	strcmp	strcasecmp
#define	stricmp	strncasecmp
#endif

#endif

