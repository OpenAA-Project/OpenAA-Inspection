/*
 * Copyright (C) 2025
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

#if	!defined(XGENERALSTOCKERFORDLL_H)
#define	XGENERALSTOCKERFORDLL_H

#include <QtGui>
#include <QVariant>
#include <QIODevice>

#include "XTypeDef.h"
#include "XDLLType.h"
#include "XDataInLayer.h"
#include "XGUIFormBase.h"

#ifdef _MSC_VER
#define	DEFFUNCEX		__declspec(dllexport)
#else
#define	DEFFUNCEX
#endif


class	LanguagePackage;
class	GeneralStockerItemBase;
class	ListPhasePageLayerPack;

extern	"C"{

DEFFUNCEX	bool			DLL_GetName(QString &str);
/*
	���̂c�k�k�̖��̂��Ԃ�
	str:	�Ԃ����̂��ݒ肷��
	�����V�X�e�������c�k�k���I�[�v���������A
		�uDLL_Initial�v���Ă΂��钼�O�ɂ��̊֐����Ă΂���
	����Export�֐��͕K���K�v
*/
DEFFUNCEX	bool			DLL_GetOrganization(QString &str);
/*
	���̂c�k�k�̑g�D�����Ԃ�
	str:	�Ԃ��g�D�����ݒ肷��
	�����V�X�e�������c�k�k���I�[�v���������A
		�uDLL_Initial�v���Ă΂��钼�O�ɂ��̊֐����Ă΂���
	����Export�֐��͕K�������K�v�Ȃ�
*/
DEFFUNCEX	bool	DLL_CheckCopyright(QString &CopyrightString);

DEFFUNCEX	WORD		DLL_GetDLLType(void);
/*
	�K���uDLLGeneralStockerMode�v���Ԃ��ׂ�
	�����V�X�e�������c�k�k���I�[�v�������Ƃ��ɂ��̒l���`�F�b�N������
	����Export�֐��͕K���K�v
*/
DEFFUNCEX	WORD		DLL_GetVersion(void);
/*
	���̂c�k�k�̃o�[�W�����ԍ����Ԃ��B
	�����̓V�X�e���ł͎g�p���Ă��Ȃ�
	����Export�֐��͕K�������K�v�Ȃ�
*/
DEFFUNCEX	const char	*DLL_GetSystemVersion(VersionType vtype);

DEFFUNCEX	void		DLL_AssociateComponent(LayersBase *Base,ComponentListContainer &List);

DEFFUNCEX	void		DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode);
/*
	�c�k�k�������ɑΉ������K�v�����鎞���̈������g���Č������ݒ肷��
	DLL_Initial�v���Ă΂ꂽ���ł��̊֐����Ă΂���
	����Export�֐��͕K�������K�v�Ȃ�
*/
DEFFUNCEX	GeneralStockerItemBase		*DLL_Initial(LayersBase *base);
/*
	�c�k�k������������
	���������͂c�k�k�ɂ���
	����Export�֐��͕K�������K�v�Ȃ�
	�n���h�����Ԃ��Ȃ����΂Ȃ��Ȃ�
*/

DEFFUNCEX	void			DLL_Release(GeneralStockerItemBase *handle);
/*
	�c�k�k���I�����钼�O�ɌĂ΂���
	���������͂c�k�k�ɂ���
	����Export�֐��͕K�������K�v�Ȃ�
*/

DEFFUNCEX	void			DLL_ReturnProperty(struct	PropertyGeneralStocker &Prop);
/*
	�c�k�k���I�����钼�O�ɌĂ΂���
	���������͂c�k�k�ɂ���
	����Export�֐��͕K�������K�v�Ȃ�
*/

DEFFUNCEX	void			DLL_EnumKeyword(GeneralStockerItemBase *handle ,QStringList &List);
/*
	�L�[���[�h���X�g���Ԃ�
	����Export�֐��͕K���K�v
*/

DEFFUNCEX	QVariant::Type	DLL_GetType(GeneralStockerItemBase *handle ,QString Keyword);
/*
	�L�[���[�h�̌^���Ԃ�	
	����Export�֐��͕K���K�v
*/
DEFFUNCEX	bool			DLL_GetData(GeneralStockerItemBase *handle ,QString Keyword 
										,QVariantList &ReturnValues,QVariantList &ArgValues);
/*
	�L�[���[�h�ɂЂ��t�����ꂽ�f�[�^���Ԃ�
	ArgValues�ɕK�v�������Έ�����������
	ReturnValues�Ƀf�[�^�������ă��^�[������

	�����ɏI�������Ƃ��Atrue���Ԃ��Ȃ����΂Ȃ��Ȃ�
	����Export�֐��͕K���K�v
*/

DEFFUNCEX	bool				DLL_ShowDialog(GeneralStockerItemBase *handle ,QString Keyword, QWidget *parent);
/*
	�L�[���[�h�Ɋ֘A�����_�C�A���O���J��
	���ꂪ�Ă΂����̂́A�����̏����n�Ɉˑ�����
	����Export�֐��͕K�������K�v�Ȃ�
*/

DEFFUNCEX	void	DLL_TransmitDirectly(GeneralStockerItemBase *handle ,GUIDirectMessage *packet);

DEFFUNCEX	bool			DLL_Save(QIODevice *f,GeneralStockerItemBase *handle);
/*
	�ݒ��������ۑ�����
	����Export�֐��͕K�������K�v�Ȃ�
*/
DEFFUNCEX	bool			DLL_Load(QIODevice *f,GeneralStockerItemBase *handle);
/*
	�ݒ��������ǂ݂����A���̂c�k�k�ɐݒ肷��
	����Export�֐��͕K�������K�v�Ȃ�
*/

DEFFUNCEX	void	DLL_GetGuiAdditionalDatabase(NPListPack<GuiAdditionalDatabase> &Data);

DEFFUNCEX	ExeResult	DLL_ExecuteInitialAfterEditPrev	(int ExeID ,GeneralStockerItemBase *handle ,ResultInspection *Res);
DEFFUNCEX	ExeResult	DLL_ExecuteInitialAfterEditPost	(int ExeID ,GeneralStockerItemBase *handle ,ResultInspection *Res);
DEFFUNCEX	ExeResult	DLL_ExecuteStartByInspectionPrev(int ExeID ,GeneralStockerItemBase *handle ,ResultInspection *Res);
DEFFUNCEX	ExeResult	DLL_ExecuteStartByInspectionPost(int ExeID ,GeneralStockerItemBase *handle ,ResultInspection *Res);
DEFFUNCEX	ExeResult	DLL_ExecuteCapturedPrev			(int ExeID ,GeneralStockerItemBase *handle ,ResultInspection *Res,ListPhasePageLayerPack &CapturedList);
DEFFUNCEX	ExeResult	DLL_ExecuteCapturedPost			(int ExeID ,GeneralStockerItemBase *handle ,ResultInspection *Res,ListPhasePageLayerPack &CapturedList);
DEFFUNCEX	ExeResult	DLL_ExecutePreAlignmentPrev		(int ExeID ,GeneralStockerItemBase *handle ,ResultInspection *Res);
DEFFUNCEX	ExeResult	DLL_ExecutePreAlignmentPost		(int ExeID ,GeneralStockerItemBase *handle ,ResultInspection *Res);
DEFFUNCEX	ExeResult	DLL_ExecuteAlignmentPrev		(int ExeID ,GeneralStockerItemBase *handle ,ResultInspection *Res);
DEFFUNCEX	ExeResult	DLL_ExecuteAlignmentPost		(int ExeID ,GeneralStockerItemBase *handle ,ResultInspection *Res);
DEFFUNCEX	ExeResult	DLL_ExecutePreProcessingPrev	(int ExeID ,GeneralStockerItemBase *handle ,ResultInspection *Res);
DEFFUNCEX	ExeResult	DLL_ExecutePreProcessingPost	(int ExeID ,GeneralStockerItemBase *handle ,ResultInspection *Res);
DEFFUNCEX	ExeResult	DLL_ExecuteProcessingPrev		(int ExeID ,GeneralStockerItemBase *handle ,ResultInspection *Res);
DEFFUNCEX	ExeResult	DLL_ExecuteProcessingPost		(int ExeID ,GeneralStockerItemBase *handle ,ResultInspection *Res);
DEFFUNCEX	ExeResult	DLL_ExecuteProcessingRevivedPrev(int ExeID ,GeneralStockerItemBase *handle ,ResultInspection *Res);
DEFFUNCEX	ExeResult	DLL_ExecuteProcessingRevivedPost(int ExeID ,GeneralStockerItemBase *handle ,ResultInspection *Res);
DEFFUNCEX	ExeResult	DLL_ExecutePostProcessingPrev	(int ExeID ,GeneralStockerItemBase *handle ,ResultInspection *Res);
DEFFUNCEX	ExeResult	DLL_ExecutePostProcessingPost	(int ExeID ,GeneralStockerItemBase *handle ,ResultInspection *Res);

};


#endif