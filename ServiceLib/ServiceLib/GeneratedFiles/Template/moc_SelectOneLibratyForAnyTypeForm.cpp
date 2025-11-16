/****************************************************************************
** Meta object code from reading C++ file 'SelectOneLibratyForAnyTypeForm.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.13)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../SelectOneLibratyForAnyTypeForm.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SelectOneLibratyForAnyTypeForm.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.13. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SelectOneLibratyForAnyTypeForm_t {
    QByteArrayData data[11];
    char stringdata0[212];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SelectOneLibratyForAnyTypeForm_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SelectOneLibratyForAnyTypeForm_t qt_meta_stringdata_SelectOneLibratyForAnyTypeForm = {
    {
QT_MOC_LITERAL(0, 0, 30), // "SelectOneLibratyForAnyTypeForm"
QT_MOC_LITERAL(1, 31, 36), // "on_comboBLibType_currentIndex..."
QT_MOC_LITERAL(2, 68, 0), // ""
QT_MOC_LITERAL(3, 69, 5), // "index"
QT_MOC_LITERAL(4, 75, 29), // "on_tableWidgetLibList_clicked"
QT_MOC_LITERAL(5, 105, 11), // "QModelIndex"
QT_MOC_LITERAL(6, 117, 23), // "on_pushButtonOK_clicked"
QT_MOC_LITERAL(7, 141, 27), // "on_pushButtonCancel_clicked"
QT_MOC_LITERAL(8, 169, 19), // "SlotSelectLibFolder"
QT_MOC_LITERAL(9, 189, 11), // "LibFolderID"
QT_MOC_LITERAL(10, 201, 10) // "FolderName"

    },
    "SelectOneLibratyForAnyTypeForm\0"
    "on_comboBLibType_currentIndexChanged\0"
    "\0index\0on_tableWidgetLibList_clicked\0"
    "QModelIndex\0on_pushButtonOK_clicked\0"
    "on_pushButtonCancel_clicked\0"
    "SlotSelectLibFolder\0LibFolderID\0"
    "FolderName"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SelectOneLibratyForAnyTypeForm[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x08 /* Private */,
       4,    1,   42,    2, 0x08 /* Private */,
       6,    0,   45,    2, 0x08 /* Private */,
       7,    0,   46,    2, 0x08 /* Private */,
       8,    2,   47,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, 0x80000000 | 5,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    9,   10,

       0        // eod
};

void SelectOneLibratyForAnyTypeForm::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SelectOneLibratyForAnyTypeForm *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_comboBLibType_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->on_tableWidgetLibList_clicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 2: _t->on_pushButtonOK_clicked(); break;
        case 3: _t->on_pushButtonCancel_clicked(); break;
        case 4: _t->SlotSelectLibFolder((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SelectOneLibratyForAnyTypeForm::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_SelectOneLibratyForAnyTypeForm.data,
    qt_meta_data_SelectOneLibratyForAnyTypeForm,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SelectOneLibratyForAnyTypeForm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SelectOneLibratyForAnyTypeForm::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SelectOneLibratyForAnyTypeForm.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "ServiceForLayers"))
        return static_cast< ServiceForLayers*>(this);
    return QWidget::qt_metacast(_clname);
}

int SelectOneLibratyForAnyTypeForm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
