#pragma once

#include "NListComp.h"
#include <QColor>
#include "XServiceForLayers.h"

class LayersBase;

class ReferencePDF : public NPListSaveLoad<ReferencePDF>
{
public:
	int		ID;
	QString	ReferenceName;
	QColor	PDFColor;
	double	*ColorDim;
	int		CountOfColorDim;

	ReferencePDF(void);
	ReferencePDF(const ReferencePDF &src);
	virtual	~ReferencePDF(void);

	double			GetColorDistance(const QColor &Col);
	ReferencePDF	&operator=(const ReferencePDF &src);
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

class ReferencePDFContainer : public NPListPackSaveLoad<ReferencePDF>,public ServiceForLayers
{
public:
	ReferencePDFContainer(LayersBase *Base);
	ReferencePDFContainer(const ReferencePDFContainer &src);

	virtual	ReferencePDF	*Create(void)	override;
	ReferencePDFContainer	&operator=(const ReferencePDFContainer &src);
	virtual	void	AppendListItem(ReferencePDF *additem)	override;
	void	ReGenerateID(void);

	QString	GetDefaultFileName(void)	{	return /**/ "ReferencePDF.dat";	}
	ReferencePDF	*FindClosed(const QColor &Col ,double ColerDistance);
	ReferencePDF	*FindClosed(const QColor &Col);
	int	FindClosed(const QColor &Col ,ReferencePDF **R1 ,ReferencePDF **R2 ,ReferencePDF **R3);

	bool	LoadDefault(void);
	bool	SaveDefault(void);
};
