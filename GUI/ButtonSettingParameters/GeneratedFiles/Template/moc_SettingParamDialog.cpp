/****************************************************************************
** Meta object code from reading C++ file 'SettingParamDialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.13)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../SettingParamDialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SettingParamDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.13. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SettingParamDialog_t {
    QByteArrayData data[10];
    char stringdata0[244];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SettingParamDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SettingParamDialog_t qt_meta_stringdata_SettingParamDialog = {
    {
QT_MOC_LITERAL(0, 0, 18), // "SettingParamDialog"
QT_MOC_LITERAL(1, 19, 35), // "on_tabWidgetAllParam_currentC..."
QT_MOC_LITERAL(2, 55, 0), // ""
QT_MOC_LITERAL(3, 56, 23), // "on_ButtonCancel_clicked"
QT_MOC_LITERAL(4, 80, 19), // "on_ButtonOK_clicked"
QT_MOC_LITERAL(5, 100, 11), // "SlotRefrect"
QT_MOC_LITERAL(6, 112, 30), // "on_ButtonOutlineOffset_clicked"
QT_MOC_LITERAL(7, 143, 34), // "on_pushButtonRowImageTable_cl..."
QT_MOC_LITERAL(8, 178, 35), // "on_pushButtonLoadImageTable_c..."
QT_MOC_LITERAL(9, 214, 29) // "on_pushButtonEachPage_clicked"

    },
    "SettingParamDialog\0"
    "on_tabWidgetAllParam_currentChanged\0"
    "\0on_ButtonCancel_clicked\0on_ButtonOK_clicked\0"
    "SlotRefrect\0on_ButtonOutlineOffset_clicked\0"
    "on_pushButtonRowImageTable_clicked\0"
    "on_pushButtonLoadImageTable_clicked\0"
    "on_pushButtonEachPage_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SettingParamDialog[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x08 /* Private */,
       3,    0,   57,    2, 0x08 /* Private */,
       4,    0,   58,    2, 0x08 /* Private */,
       5,    0,   59,    2, 0x08 /* Private */,
       6,    0,   60,    2, 0x08 /* Private */,
       7,    0,   61,    2, 0x08 /* Private */,
       8,    0,   62,    2, 0x08 /* Private */,
       9,    0,   63,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void SettingParamDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SettingParamDialog *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_tabWidgetAllParam_currentChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->on_ButtonCancel_clicked(); break;
        case 2: _t->on_ButtonOK_clicked(); break;
        case 3: _t->SlotRefrect(); break;
        case 4: _t->on_ButtonOutlineOffset_clicked(); break;
        case 5: _t->on_pushButtonRowImageTable_clicked(); break;
        case 6: _t->on_pushButtonLoadImageTable_clicked(); break;
        case 7: _t->on_pushButtonEachPage_clicked(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SettingParamDialog::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_SettingParamDialog.data,
    qt_meta_data_SettingParamDialog,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SettingParamDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SettingParamDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SettingParamDialog.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "ServiceForLayers"))
        return static_cast< ServiceForLayers*>(this);
    return QDialog::qt_metacast(_clname);
}

int SettingParamDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
