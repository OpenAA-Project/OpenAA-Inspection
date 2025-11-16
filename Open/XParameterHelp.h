#if	!defined(XParameterHelp_h)
#define	XParameterHelp_h

#include "XTypeDef.h"

struct	ParameterHelpStruct
{
	char	*Param;
	char	*Explain;
};


class	ParameterHelp
{
	const	ParameterHelpStruct *Dim;
	int		DimNumb;
public:
	ParameterHelp(const ParameterHelpStruct dim[] ,int DimNumb);

	void	PrintHelp(void);
	void	ShowDialog(void);
};



#endif