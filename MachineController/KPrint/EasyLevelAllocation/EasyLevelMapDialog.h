/*
 * Copyright (C) 2021
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

#ifndef EASYLEVELMAPDIALOG_H
#define EASYLEVELMAPDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
#include"XParamCustomized.h"
#include "XAlgorithmLibrary.h"
#include "XDataAlgorithm.h"
#include <QTableWidget>

namespace Ui {
class EasyLevelMapDialog;
}
class	GeneralLibFolderForm;
class	DotColorMatchingBase;
class	DentBase			;

class EasyLevelMapDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

	int		LastLevel;

	class	SelectLibrary :public ServiceForLayers
	{
	public:
		GeneralLibFolderForm	*pLibFolderForm;
		int		LibFolderID;
		QTableWidget	*Table;

		AlgorithmLibrary	*TempLib;
		int		LibType;
		AlgorithmLibraryListContainer	LibList;

		SelectLibrary(LayersBase *Base);
		~SelectLibrary(void);

		void	SetInitial(AlgorithmBase *ABase ,QWidget *LibFolderParent);
	};
	SelectLibrary	LibraryListDotColorMatching;
	SelectLibrary	LibraryListDentInspection;

public:
	ParamLevel	LevelData[10];

	explicit EasyLevelMapDialog(LayersBase *Base ,QWidget *parent = 0);
    ~EasyLevelMapDialog();
    
private slots:
    void on_horizontalSliderLevel_valueChanged(int value);
    void on_toolButtonDotColorMatchLibPattern_clicked();
    void on_toolButtonDotColorMatchLibFlat_clicked();
    void on_toolButtonDotColorMatchCADLib_clicked();
    void on_toolButtonDotColorMatchBladeLib_clicked();
    void on_toolButtonDentLib_clicked();
    void on_pushButtonSettingLibIDDotColorMatching_clicked();
    void on_pushButtonSettingLibIDDentInspection_clicked();
	void	SlotSelectLibFolderDotColorMatching	(int LibFolderID ,QString FolderName);
	void	SlotSelectLibFolderDentInspction	(int LibFolderID ,QString FolderName);
    void on_pushButtonOK_clicked();

private:
    Ui::EasyLevelMapDialog *ui;
	void FromWindow(int Level);
	void ToWindow(int Level);

	DotColorMatchingBase	*GetDotColorMatchingBase(void);
	DentBase				*GetDentBase(void);

	void	ShowID(int LibType, int LibID,SelectLibrary &SLib);
};

#endif // EASYLEVELMAPDIALOG_H