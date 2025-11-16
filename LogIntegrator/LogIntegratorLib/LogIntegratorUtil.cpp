#include "LogIntegratorUtil.h"

QString ForceDirectories( QString path )
{
	char delim = '/';
	QStringList dirs = (path).split(delim, QString::SkipEmptyParts);
	QDir dir(dirs[0] + delim);
	for(int i=1; i<dirs.count(); i++){
		if(!dir.exists(dirs[i])){
			if(!dir.mkdir(dirs[i])){
				return dir.path();
			}
		}
		if(!dir.cd(dirs[i])){
			return dir.path();
		}
	}
	return dir.path();
}
