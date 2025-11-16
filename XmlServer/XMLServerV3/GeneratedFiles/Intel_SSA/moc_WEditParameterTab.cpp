/****************************************************************************
** Meta object code from reading C++ file 'WEditParameterTab.h'
**
** Created: Thu Sep 10 11:41:23 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../GeneralSource/WEditParameterTab.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'WEditParameterTab.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_WEditParameterTab[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      18,   32,   32,   32, 0x05,

 // slots: signature, parameters, type, tag, flags
      33,   86,   32,   32, 0x08,
      90,   86,   32,   32, 0x08,
     143,   86,   32,   32, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_WEditParameterTab[] = {
    "WEditParameterTab\0SignalClose()\0\0"
    "FileButtonClicked(WEditParameterTab::EditParamLine*)\0"
    "Src\0PathButtonClicked(WEditParameterTab::EditParamLine*)\0"
    "ColorLogicButtonClicked(WEditParameterTab::EditParamLine*)\0"
};

void WEditParameterTab::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        WEditParameterTab *_t = static_cast<WEditParameterTab *>(_o);
        switch (_id) {
        case 0: _t->SignalClose(); break;
        case 1: _t->FileButtonClicked((*reinterpret_cast< WEditParameterTab::EditParamLine*(*)>(_a[1]))); break;
        case 2: _t->PathButtonClicked((*reinterpret_cast< WEditParameterTab::EditParamLine*(*)>(_a[1]))); break;
        case 3: _t->ColorLogicButtonClicked((*reinterpret_cast< WEditParameterTab::EditParamLine*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData WEditParameterTab::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject WEditParameterTab::staticMetaObject = {
    { &QTabWidget::staticMetaObject, qt_meta_stringdata_WEditParameterTab,
      qt_meta_data_WEditParameterTab, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &WEditParameterTab::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *WEditParameterTab::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *WEditParameterTab::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_WEditParameterTab))
        return static_cast<void*>(const_cast< WEditParameterTab*>(this));
    return QTabWidget::qt_metacast(_clname);
}

int WEditParameterTab::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTabWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void WEditParameterTab::SignalClose()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
static const uint qt_meta_data_ParamFilePathButton[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      20,   69,   73,   73, 0x05,

 // slots: signature, parameters, type, tag, flags
      74,   73,   73,   73, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ParamFilePathButton[] = {
    "ParamFilePathButton\0"
    "ClickedButton(WEditParameterTab::EditParamLine*)\0"
    "Src\0\0SlotClicked()\0"
};

void ParamFilePathButton::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ParamFilePathButton *_t = static_cast<ParamFilePathButton *>(_o);
        switch (_id) {
        case 0: _t->ClickedButton((*reinterpret_cast< WEditParameterTab::EditParamLine*(*)>(_a[1]))); break;
        case 1: _t->SlotClicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ParamFilePathButton::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ParamFilePathButton::staticMetaObject = {
    { &QPushButton::staticMetaObject, qt_meta_stringdata_ParamFilePathButton,
      qt_meta_data_ParamFilePathButton, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ParamFilePathButton::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ParamFilePathButton::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ParamFilePathButton::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ParamFilePathButton))
        return static_cast<void*>(const_cast< ParamFilePathButton*>(this));
    return QPushButton::qt_metacast(_clname);
}

int ParamFilePathButton::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QPushButton::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void ParamFilePathButton::ClickedButton(WEditParameterTab::EditParamLine * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
static const uint qt_meta_data_ParamColorLogicButton[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      22,   71,   75,   75, 0x05,

 // slots: signature, parameters, type, tag, flags
      76,   75,   75,   75, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ParamColorLogicButton[] = {
    "ParamColorLogicButton\0"
    "ClickedButton(WEditParameterTab::EditParamLine*)\0"
    "Src\0\0SlotClicked()\0"
};

void ParamColorLogicButton::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ParamColorLogicButton *_t = static_cast<ParamColorLogicButton *>(_o);
        switch (_id) {
        case 0: _t->ClickedButton((*reinterpret_cast< WEditParameterTab::EditParamLine*(*)>(_a[1]))); break;
        case 1: _t->SlotClicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ParamColorLogicButton::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ParamColorLogicButton::staticMetaObject = {
    { &QPushButton::staticMetaObject, qt_meta_stringdata_ParamColorLogicButton,
      qt_meta_data_ParamColorLogicButton, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ParamColorLogicButton::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ParamColorLogicButton::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ParamColorLogicButton::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ParamColorLogicButton))
        return static_cast<void*>(const_cast< ParamColorLogicButton*>(this));
    return QPushButton::qt_metacast(_clname);
}

int ParamColorLogicButton::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QPushButton::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void ParamColorLogicButton::ClickedButton(WEditParameterTab::EditParamLine * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
