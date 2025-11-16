#include "XTypeDef.h"
#include "PasswordEventOperator.h"

PasswordFileOperator PasswordEventOperator::m_pfo;
QVector<bool> PasswordEventOperator::m_unsealItems(0);
bool PasswordEventOperator::m_isLoaded = false;
bool PasswordEventOperator::m_forceUnseal = false;

PasswordEventOperator::PasswordEventOperator(QWidget *parent)
:QWidget(parent)
{
	if(m_isLoaded==false){
		update();
		m_isLoaded = true;
	}
}

void PasswordEventOperator::addButton(QPushButton **btn)
{
	PasswordPushButton *_btn = new PasswordPushButton((QWidget*)((*btn)->parent()));
	_btn->setObjectName( (*btn)->objectName() );
	_btn->installEventFilter(this);

	delete (*btn);
	(*btn) = _btn;
}

void PasswordEventOperator::addButton(PasswordPushButton *btn)
{
	btn->installEventFilter(this);
}

void PasswordEventOperator::update()
{
	m_pfo.load( PasswordFilePath() );
	m_unsealItems.resize(m_pfo.getNumItem());
	for(int i=0; i<m_pfo.getNumItem(); i++)
		m_unsealItems[i] = false;
}

bool PasswordEventOperator::tryAccess(QAbstractButton *btn, QEvent *event)
{
	QString itemName = btn->text() + QString("@") +  CreatePasswordObjectName(btn);
				
	int itemIndex = m_pfo.hasItem( itemName );// オブジェクト名からパスワードが付けられているか確認
	if(m_forceUnseal ||// 強制パスワード解除状態
		itemIndex==-1 ||// パスワード設定無し
		m_unsealItems[itemIndex]//開放済み
	)return QObject::eventFilter(btn, event);//受付
	
	// パスワード入力フォーム表示
	InputPasswordFormDialog dialog(this);
	if(dialog.exec()){
		QString pass = dialog.GetLiedPassword();
		int classIndex = m_pfo.hasPassword(pass);
		if(classIndex==-1){
			QMessageBox::warning(this, "!!!拒否!!!", "パスワードが一致しません!");
			return false;
		} else {
			QMessageBox::about(this, "---受付---", QString("クラス[%1]を解放します").arg(m_pfo.getClassName(classIndex)));
			for(int i=0; i<m_pfo.getNumItem(); i++){
				if(m_pfo.getItemFlag(classIndex, i)==true){
					m_unsealItems[i] = true;
				}
			}
			return QObject::eventFilter(btn, event);
		}
	}else{
		btn->setDown(false);
		return false;
	}
	return false;
}

bool PasswordEventOperator::eventFilter(QObject *obj, QEvent *event)
{
	QEvent::Type type = event->type();
	QKeyEvent *key = NULL;
	QMouseEvent *mouse = NULL;
	QString itemName(/**/"");

	QAbstractButton *btn = static_cast<QAbstractButton*>(obj);
	if(!btn)return false;// ボタンのみ対応
	
	switch(type){
	case QEvent::MouseButtonDblClick:
		return false;
		break;
		
	case QEvent::KeyPress:
		key = static_cast<QKeyEvent*>(event);
		if(!key)return false;
		switch(key->key()){
			// 対応キー
			case Qt::Key_Space://スペースキー
			case Qt::Key_Enter://エンターキー
				return tryAccess(btn, event);
				break;
			// その他のキーには対応しない
			default:
				return false;
				break;
		}
		break;
	case QEvent::MouseButtonRelease:// マウスクリックイベント
		// パスワード入力処理
		mouse = static_cast<QMouseEvent*>(event);
		if(mouse==NULL)return false;// キャスト失敗で終了
		if(mouse->button() == Qt::LeftButton){// 右クリックに対応
			return tryAccess(btn, event);
		}
		return false;
		break;
	default:
		return false;//基本的に受け付けない
		break;
	}
	return false;//基本的に受け付けない
}

void PasswordEventOperator::copyPropaty(QPushButton *dest, QPushButton *source)
{
	//dest->setAcceptDrops( true );// 必須
	//dest->setAccessibleDescription( source->accessibleDescription() );
	//dest->setAccessibleName( source->accessibleName() );
	//dest->setAutoDefault( source->autoDefault() );
	//dest->setAutoExclusive( source->autoExclusive() );
	//dest->setAutoFillBackground( source->autoFillBackground() );
	//dest->setAutoRepeat( source->autoRepeat() );
	//dest->setAutoRepeatDelay( source->autoRepeatDelay() );
	//dest->setAutoRepeatInterval( source->autoRepeatInterval() );
	//dest->setBackgroundRole( source->backgroundRole() );
	//dest->setBaseSize( source->baseSize() );
	//dest->setCheckable( source->isCheckable() );
	//dest->setChecked( source->isChecked() );

	//{
	//	int l,t,r,b;
	//	source->getContentsMargins(&l, &t, &r, &b);
	//	dest->setContentsMargins(l, t, r, b);
	//}
	//
	//dest->setContextMenuPolicy( source->contextMenuPolicy() );
	//dest->setCursor( source->cursor() );
	//dest->setDefault( source->isDefault() );
	//dest->setEnabled( source->isEnabled() );
	//dest->setDown( source->isDown() );
	//dest->setFlat( source->isFlat() );
	//dest->setFocusPolicy( source->focusPolicy() );
	//dest->setFocusProxy( source->focusProxy() );
	//dest->setFont( source->font() );
	//dest->setForegroundRole( source->foregroundRole() );
	//dest->setGeometry( source->geometry() );
	//dest->setHidden( source->isHidden() );
	//dest->setIcon( source->icon() );
	//dest->setInputContext( source->inputContext() );
	//QLayout *layout = source->layout();
	//dest->setLayout( layout );
	//dest->setLayoutDirection( source->layoutDirection() );

	//{
	//	QLocale locale = source->locale();
	//	dest->setLocale( locale );
	//}
	//
	//dest->setMask( source->mask() );
	//dest->setMaximumSize( source->maximumSize() );
	//dest->setMenu( source->menu() );
	//dest->setMinimumSize( source->minimumSize() );
	//dest->setMouseTracking( source->hasMouseTracking() );
	//dest->setObjectName( source->objectName() );
	//dest->setPalette( source->palette() );
	//dest->setParent( (QWidget*)source->parent() );
	//dest->setShortcut( source->shortcut() );
	//dest->setSizeIncrement( source->sizeIncrement() );
	//dest->setSizePolicy( source->sizePolicy() );
	//dest->setStatusTip( source->statusTip() );
	//dest->setStyle( source->style() );
	//dest->setStyleSheet( source->styleSheet() );
	//dest->setText( source->text() );
	//dest->setToolTip( source->toolTip() );
	//dest->setUpdatesEnabled( source->updatesEnabled() );
	//dest->setWhatsThis( source->whatsThis() );

	//dest->setWindowFilePath( source->windowFilePath() );
	//dest->setWindowFlags( source->windowFlags() );
	//dest->setWindowIcon( source->windowIcon() );
	//dest->setWindowIconText( source->windowIconText() );
	//dest->setWindowModality( source->windowModality() );
	//dest->setWindowModified( source->isWindowModified() );

	//dest->setWindowOpacity( source->windowOpacity() );
	//dest->setWindowRole( source->windowRole() );
	//dest->setWindowState( source->windowState() );
	//dest->setWindowSurface( source->windowSurface() );
	//dest->setWindowTitle( source->windowTitle() );
}

QString PasswordEventOperator::PasswordFilePath()
{
	QString passFileName = qApp->applicationFilePath();
	passFileName = passFileName.left(passFileName.lastIndexOf('.')) + ".pwd";
	return passFileName;
}

QString PasswordEventOperator::CreatePasswordObjectName(QObject *obj)
{
	return PasswordFileOperator::createItemName(obj) + " - " + obj->objectName();
}