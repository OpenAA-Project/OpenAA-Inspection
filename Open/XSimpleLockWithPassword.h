#if	!defined(XSIMPLELOCKWITHPASSWORD_H)
#define	XSIMPLELOCKWITHPASSWORD_H

class	SimpleLockWIthPassword
{
	QString		LoadedPassword;
	QString		CurrentPassword;

public:
	SimpleLockWIthPassword(void){}

	bool	Load(void);
	bool	CheckPassword(void);
	bool	CheckPasswordEverytime(void);
};

#endif