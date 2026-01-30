/*
 * Copyright (C) 2023
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef PROPERTYRASTERINSPECTIONFORM_H
#define PROPERTYRASTERINSPECTIONFORM_H

#include "XGUIFormBase.h"
#include "XRasterInspection.h"
#include "XStandardPropertyForm.h"
#include <QString>

namespace Ui {
class PropertyRasterInspectionForm;
}

class PropertyRasterInspectionForm : public GUIFormBase,public StandardPropertyForm
{
    Q_OBJECT

    int     ModeShowPDF;    //0:No PDF  1:ShowPDF   2:Show Item PDF
public:
    explicit PropertyRasterInspectionForm(LayersBase *Base ,QWidget *parent = nullptr);
    ~PropertyRasterInspectionForm();

 	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual void	ShowInEdit(void)	override;
	virtual void	BuildForShow(void)	override;
	virtual void	StartPage	(void)	override;

	void	ClearLibList(void);
	void	SetLib(int LibID);

	virtual	bool	SaveContent(QIODevice *f)	override;
	virtual	bool	LoadContent(QIODevice *f)	override;
private slots:
    void on_pushButtonEditLibrary_clicked();
    void on_pushButtonReferencePDF_clicked();
    void on_pushButtonEditLibFolder_clicked();
    void on_pushButtonSetFrom_clicked();
    void on_pushButtonGetBack_clicked();
    void on_pushButtonSetFromAll_clicked();
    void on_pushButtonGetBackAll_clicked();
    void on_toolButtonDrawMode_clicked();
    void on_toolButtonShowPDF_clicked();
    void on_pushButtonGenerate_clicked();
    void on_tableWidgetLibList_doubleClicked(const QModelIndex &index);
    void on_tableWidgetGeneratedLibList_doubleClicked(const QModelIndex &index);

private:
    Ui::PropertyRasterInspectionForm *ui;

    RasterInspectionBase	*GetRasterInspectionBase(void);
	AlgorithmLibraryLevelContainer		*LLib;
	int				LibType;

	void	ShowLibList(void);
	void	ShowSelectedLibList(void);
	virtual	void	SetLibFolder(int LibFolderID ,const QString &LinFolderName)	override;

	AlgorithmLibraryListContainer	LibList;
	AlgorithmLibraryListContainer	SelectedLibList;
	int		LibFolderID;

	void	ShowList(void);
};

#endif // PROPERTYRASTERINSPECTIONFORM_H