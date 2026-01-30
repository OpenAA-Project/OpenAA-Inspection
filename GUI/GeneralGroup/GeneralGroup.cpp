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

#include "GeneralGroupResource.h"

#include "GeneralGroup.h"
#include "XDataInLayer.h"
#include "XDLLOnly.h"
#include <QMessageBox>

#include "GeneralGroupSelfPasswordForm.h"

static	const	char	*sRoot=/**/"General";
static	const	char	*sName=/**/"GeneralGroup";


DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Add General group");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new GeneralGroup(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<3)
		return(-1);
	Data[0].Type					=/**/"QString";
	Data[0].VariableNameWithRoute	=/**/"GroupTitle";
	Data[0].Pointer					=&((GeneralGroup *)Instance)->m_text;
	Data[1].Type					=/**/"bool";
	Data[1].VariableNameWithRoute	=/**/"InitialCheckState";
	Data[1].Pointer					=&((GeneralGroup *)Instance)->m_initState;
	Data[2].Type					=/**/"QString";
	Data[2].VariableNameWithRoute	=/**/"SelfPassword";
	Data[2].Pointer					=&((GeneralGroup *)Instance)->m_selfPassword;
	return(3);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/GeneralGroup.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

//==================================================================================================
GeneralGroup::GeneralGroup(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	// �J�{�^���쐬
	m_button = new QPushButton(this);
	m_button->setCheckable(true);
	m_button->move(0,0);

	// �f�t�H���g�l
	m_text = /**/"Group";
	m_initState = false;
	
	// �O�g�쐬
	setLineWidth(1);
	setMidLineWidth(1);
	setFrameStyle(Shape::Box | Shadow::Sunken);
	if(GetEditMode()==true){
		resize(200,200);
	}else{
		// �C�x���g�t�B���^�g�ݍ���
		m_button->installEventFilter(this);
		connect(m_button, SIGNAL(toggled(bool)), this, SLOT(buttonToggled(bool)));
	}
}


GeneralGroup::~GeneralGroup()
{
	delete m_button;
}

void GeneralGroup::resizeEvent(QResizeEvent *event)
{
	GUIFormBase::resizeEvent(event);
	
	if(GetEditMode()==true){
		setLineWidth(1);
		setMidLineWidth(1);
		setFrameStyle(Shape::Box | Shadow::Sunken);
	}
}

void GeneralGroup::updateButtonText(void)
{
	// �{�^���̃`�F�b�N���ԂɑΉ������J���������ǋL
	QString str = m_text;
	if(GetEditMode()==true){
		str += /**/" <<";
	}else{
		if(m_button->isChecked()==true){
			str += /**/" <<";
		}else{
			str += /**/" >>";
		}
	}
	m_button->setText(str);
}

bool GeneralGroup::eventFilter(QObject *obj, QEvent *event)
{
	// �C�x���g�����J�{�^���ł����A�N���b�N�C�x���g�̏ꍇ
	if(obj==m_button && event->type()==QEvent::MouseButtonPress){
		QMouseEvent *me = static_cast<QMouseEvent*>(event);// �}�E�X�C�x���g�̒���
		if(me->button()==Qt::MouseButton::LeftButton){// ���N���b�N�������ꍇ
			if(m_passwordLock==false){// �p�X���[�h�������Ԃł����ꍇ
				return QObject::eventFilter(obj, event);
			}
			GeneralGroupSelfPasswordForm form(GetLayersBase());// �p�X���[�h���̓_�C�A���O
			if(form.exec()==QDialog::Accepted && m_selfPassword==form.password()){// �I�����󂯎����ŁA�p�X���[�h�Ɉ��v���Ă����ꍇ
				m_passwordLock = false;// �p�X���[�h�������Ԃ�
				QPushButton *btn = dynamic_cast<QPushButton*>(obj);
				if(btn!=NULL){
					btn->setChecked( !btn->isChecked() );// �ʏ��̃{�^���N���b�N�������}�j���A�����s
				}
			}else{
				return true;
			}
		}
	}
	return QObject::eventFilter(obj, event);
}

void GeneralGroup::buttonToggled(bool on)
{
	if(GetEditMode()==true){// GUI�쐬���͕����K�v������
		on = true;
	}
	const QObjectList &list = children();// �����Ɋi�[���Ă����qGUI�̃��X�g���擾
	for(int i=0; i<list.count(); i++){// �e�qGUI�ɑ΂��ĕ\����ONOFF���{�^���̉������Ԃ����ݒ肷��
		QObject *o = list[i];
		if(o==NULL || o==m_button){
			continue;
		}
		GUIFormBase *c = dynamic_cast<GUIFormBase*>(o);
		if(c==NULL){
			continue;
		}
		c->setVisible(on);
	}

	QRect r;
	if(GetEditMode()==false){
		if(on==false){
			r = m_button->rect();
		}else{
			r = rect();
		}
	}else{
		r = rect();
	}
	setFrameRect(r);
	
	updateButtonText();
}

void GeneralGroup::showEvent(QShowEvent *event)
{
	buttonToggled(m_button->isChecked());
	GUIFormBase::showEvent(event);
}

void GeneralGroup::paintEvent(QPaintEvent *event)
{
	buttonToggled(m_button->isChecked());
	GUIFormBase::paintEvent(event);
}

void	GeneralGroup::BuildForShow(void)
{
	buttonToggled(m_button->isChecked());
	GUIFormBase::BuildForShow();
}

void	GeneralGroup::ShowInPlayer(int64 shownInspectionID)
{
	buttonToggled(m_button->isChecked());
	GUIFormBase::ShowInPlayer(shownInspectionID);
}

void	GeneralGroup::StartPage(void)
{
	buttonToggled(m_button->isChecked());
	GUIFormBase::StartPage();
}

void	GeneralGroup::Prepare(void)
{
	// �{�^���ɂ������Ă��閼�O�����K�v�Ȓ������v�Z���ă{�^���̉����𒲐�����
	QFontMetrics fm(m_button->font());

	QString str = m_text;
	if(m_button->isChecked()==true){
		str += /**/" <<";
	}else{
		str += /**/" >>";
	}

	int len = fm.boundingRect(str).width();

	QRect r = m_button->geometry();

	if(len<50){// �ŏ�����
		len = 50;
	}

	r.setWidth(len+20);

	m_button->setGeometry(r);
	m_button->setChecked(m_initState);
	if(m_selfPassword.isEmpty()==true){
		m_passwordLock = false;
	}else{
		m_passwordLock = true;
	}
	
	updateButtonText();
	
	buttonToggled(m_button->isChecked());
}
