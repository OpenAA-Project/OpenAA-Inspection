#if	!defined(XSLAVEINDICATOR_H)
#define	XSLAVEINDICATOR_H


#define	SlaveIndicatorPort		16214
#define	SlaveIndicatorInterval	5000

struct	SlaveInfo
{
	int32	GlobalPage;
	int32	MachineID;
};

#endif