/****************************************************************************
** Meta object code from reading C++ file 'SetThresholdLevelForm.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.13)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../SetThresholdLevelForm.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SetThresholdLevelForm.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.13. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SetThresholdLevelForm_t {
    QByteArrayData data[11];
    char stringdata0[206];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SetThresholdLevelForm_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SetThresholdLevelForm_t qt_meta_stringdata_SetThresholdLevelForm = {
    {
QT_MOC_LITERAL(0, 0, 21), // "SetThresholdLevelForm"
QT_MOC_LITERAL(1, 22, 26), // "SignalReqChangeLevelParent"
QT_MOC_LITERAL(2, 49, 0), // ""
QT_MOC_LITERAL(3, 50, 28), // "SignalChangeThresholdLevelID"
QT_MOC_LITERAL(4, 79, 16), // "ThresholdLevelID"
QT_MOC_LITERAL(5, 96, 32), // "on_horizontalSlider_valueChanged"
QT_MOC_LITERAL(6, 129, 5), // "value"
QT_MOC_LITERAL(7, 135, 24), // "SlotChangeThresholdLevel"
QT_MOC_LITERAL(8, 160, 8), // "OldLevel"
QT_MOC_LITERAL(9, 169, 8), // "NewLevel"
QT_MOC_LITERAL(10, 178, 27) // "on_pushButtonParent_clicked"

    },
    "SetThresholdLevelForm\0SignalReqChangeLevelParent\0"
    "\0SignalChangeThresholdLevelID\0"
    "ThresholdLevelID\0on_horizontalSlider_valueChanged\0"
    "value\0SlotChangeThresholdLevel\0OldLevel\0"
    "NewLevel\0on_pushButtonParent_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SetThresholdLevelForm[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x06 /* Public */,
       3,    1,   40,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   43,    2, 0x08 /* Private */,
       7,    2,   46,    2, 0x08 /* Private */,
      10,    0,   51,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    4,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    8,    9,
    QMetaType::Void,

       0        // eod
};

void SetThresholdLevelForm::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SetThresholdLevelForm *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->SignalReqChangeLevelParent(); break;
        case 1: _t->SignalChangeThresholdLevelID((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->on_horizontalSlider_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->SlotChangeThresholdLevel((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->on_pushButtonParent_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SetThresholdLevelForm::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SetThresholdLevelForm::SignalReqChangeLevelParent)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SetThresholdLevelForm::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SetThresholdLevelForm::SignalChangeThresholdLevelID)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SetThresholdLevelForm::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_SetThresholdLevelForm.data,
    qt_meta_data_SetThresholdLevelForm,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SetThresholdLevelForm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SetThresholdLevelForm::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SetThresholdLevelForm.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "ServiceForLayers"))
        return static_cast< ServiceForLayers*>(this);
    return QWidget::qt_metacast(_clname);
}

int SetThresholdLevelForm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void SetThresholdLevelForm::SignalReqChangeLevelParent()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void SetThresholdLevelForm::SignalChangeThresholdLevelID(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
