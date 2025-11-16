/****************************************************************************
** Meta object code from reading C++ file 'XLightClass.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.13)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../Open/XLightClass.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'XLightClass.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.13. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_LightDLLBaseClass_t {
    QByteArrayData data[5];
    char stringdata0[80];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_LightDLLBaseClass_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_LightDLLBaseClass_t qt_meta_stringdata_LightDLLBaseClass = {
    {
QT_MOC_LITERAL(0, 0, 17), // "LightDLLBaseClass"
QT_MOC_LITERAL(1, 18, 25), // "SignalReflectDataInDialog"
QT_MOC_LITERAL(2, 44, 0), // ""
QT_MOC_LITERAL(3, 45, 26), // "SignalReflectOnOffInDialog"
QT_MOC_LITERAL(4, 72, 7) // "LightOn"

    },
    "LightDLLBaseClass\0SignalReflectDataInDialog\0"
    "\0SignalReflectOnOffInDialog\0LightOn"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LightDLLBaseClass[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x06 /* Public */,
       3,    1,   25,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    4,

       0        // eod
};

void LightDLLBaseClass::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<LightDLLBaseClass *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->SignalReflectDataInDialog(); break;
        case 1: _t->SignalReflectOnOffInDialog((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (LightDLLBaseClass::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LightDLLBaseClass::SignalReflectDataInDialog)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (LightDLLBaseClass::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LightDLLBaseClass::SignalReflectOnOffInDialog)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject LightDLLBaseClass::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_LightDLLBaseClass.data,
    qt_meta_data_LightDLLBaseClass,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *LightDLLBaseClass::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LightDLLBaseClass::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_LightDLLBaseClass.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "IdentifiedClass"))
        return static_cast< IdentifiedClass*>(this);
    if (!strcmp(_clname, "ServiceForLayers"))
        return static_cast< ServiceForLayers*>(this);
    return QWidget::qt_metacast(_clname);
}

int LightDLLBaseClass::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void LightDLLBaseClass::SignalReflectDataInDialog()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void LightDLLBaseClass::SignalReflectOnOffInDialog(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
