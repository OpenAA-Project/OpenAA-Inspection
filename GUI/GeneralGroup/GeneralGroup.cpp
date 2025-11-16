#include "GeneralGroupResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\GeneralGroup\GeneralGroup.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

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
	// 開閉ボタン作成
	m_button = new QPushButton(this);
	m_button->setCheckable(true);
	m_button->move(0,0);

	// デフォルト値
	m_text = /**/"Group";
	m_initState = false;
	
	// 外枠作成
	setLineWidth(1);
	setMidLineWidth(1);
	setFrameStyle(Shape::Box | Shadow::Sunken);
	if(GetEditMode()==true){
		resize(200,200);
	}else{
		// イベントフィルタ組み込み
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
	// ボタンのチェック状態に対応した開閉文字列を追記
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
	// イベント元が開閉ボタンであり、クリックイベントの場合
	if(obj==m_button && event->type()==QEvent::MouseButtonPress){
		QMouseEvent *me = static_cast<QMouseEvent*>(event);// マウスイベントの調査
		if(me->button()==Qt::MouseButton::LeftButton){// 左クリックだった場合
			if(m_passwordLock==false){// パスワード解除状態である場合
				return QObject::eventFilter(obj, event);
			}
			GeneralGroupSelfPasswordForm form(GetLayersBase());// パスワード入力ダイアログ
			if(form.exec()==QDialog::Accepted && m_selfPassword==form.password()){// 終了が受け取りで、パスワードに一致している場合
				m_passwordLock = false;// パスワード解除状態へ
				QPushButton *btn = dynamic_cast<QPushButton*>(obj);
				if(btn!=NULL){
					btn->setChecked( !btn->isChecked() );// 通常のボタンクリック動作をマニュアル実行
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
	if(GetEditMode()==true){// GUI作成中は閉じる必要が無い
		on = true;
	}
	const QObjectList &list = children();// 内部に格納している子GUIのリストを取得
	for(int i=0; i<list.count(); i++){// 各子GUIに対して表示のONOFFをボタンの押下状態から設定する
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
	// ボタンにつけられている名前から必要な長さを計算してボタンの横幅を調整する
	QFontMetrics fm(m_button->font());

	QString str = m_text;
	if(m_button->isChecked()==true){
		str += /**/" <<";
	}else{
		str += /**/" >>";
	}

	int len = fm.boundingRect(str).width();

	QRect r = m_button->geometry();

	if(len<50){// 最小長さ
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

