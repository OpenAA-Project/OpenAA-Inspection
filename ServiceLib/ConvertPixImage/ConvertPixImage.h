#ifndef CONVERTPIXIMAGE_H
#define CONVERTPIXIMAGE_H

#include <QMainWindow>
#include "ui_ConvertPixImage.h"
#include "NList.h"

class	PixFileList : public NPList<PixFileList>
{
public:
	QString	Path;
	QString	FileName;
};



class ConvertPixImage : public QMainWindow
{
	Q_OBJECT

	NPListPack<PixFileList>	PixFileContainer;
	QString		LastDir;

public:
	ConvertPixImage(QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~ConvertPixImage();

private slots:
    void on_pushButtonAddPixFile_clicked();
    void on_pushButtonAddPixFolder_clicked();
    void on_pushButtonFindPath_clicked();
    void on_pushButtonExecuteConvert_clicked();
    void on_pushButtonClose_clicked();
    void on_pushButtonDeleteList_clicked();

private:
	Ui::ConvertPixImageClass ui;

	void	ShowList(void);
	bool	ConvertToImage(PixFileList	*PixFile,const QString &OutPath,const QString &ImgFormat);

};

#endif // CONVERTPIXIMAGE_H
