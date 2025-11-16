/****************************************************************************
** Meta object code from reading C++ file 'LibFolderForm.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.13)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../LibFolderForm.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'LibFolderForm.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.13. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_LibFolderForm_t {
    QByteArrayData data[20];
    char stringdata0[298];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_LibFolderForm_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_LibFolderForm_t qt_meta_stringdata_LibFolderForm = {
    {
QT_MOC_LITERAL(0, 0, 13), // "LibFolderForm"
QT_MOC_LITERAL(1, 14, 15), // "SelectLibFolder"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 11), // "LibFolderID"
QT_MOC_LITERAL(4, 43, 10), // "FolderName"
QT_MOC_LITERAL(5, 54, 10), // "SignalDrop"
QT_MOC_LITERAL(6, 65, 14), // "FolderParentID"
QT_MOC_LITERAL(7, 80, 8), // "QWidget*"
QT_MOC_LITERAL(8, 89, 1), // "w"
QT_MOC_LITERAL(9, 91, 27), // "on_pushButtonUpdate_clicked"
QT_MOC_LITERAL(10, 119, 21), // "on_treeWidget_clicked"
QT_MOC_LITERAL(11, 141, 11), // "QModelIndex"
QT_MOC_LITERAL(12, 153, 31), // "on_treeWidget_itemDoubleClicked"
QT_MOC_LITERAL(13, 185, 16), // "QTreeWidgetItem*"
QT_MOC_LITERAL(14, 202, 24), // "SlotItemSelectionChanged"
QT_MOC_LITERAL(15, 227, 22), // "SlotCurrentItemChanged"
QT_MOC_LITERAL(16, 250, 7), // "current"
QT_MOC_LITERAL(17, 258, 8), // "previous"
QT_MOC_LITERAL(18, 267, 14), // "SlotCopyFolder"
QT_MOC_LITERAL(19, 282, 15) // "SlotPasteFolder"

    },
    "LibFolderForm\0SelectLibFolder\0\0"
    "LibFolderID\0FolderName\0SignalDrop\0"
    "FolderParentID\0QWidget*\0w\0"
    "on_pushButtonUpdate_clicked\0"
    "on_treeWidget_clicked\0QModelIndex\0"
    "on_treeWidget_itemDoubleClicked\0"
    "QTreeWidgetItem*\0SlotItemSelectionChanged\0"
    "SlotCurrentItemChanged\0current\0previous\0"
    "SlotCopyFolder\0SlotPasteFolder"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LibFolderForm[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   59,    2, 0x06 /* Public */,
       5,    3,   64,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    0,   71,    2, 0x08 /* Private */,
      10,    1,   72,    2, 0x08 /* Private */,
      12,    2,   75,    2, 0x08 /* Private */,
      14,    0,   80,    2, 0x08 /* Private */,
      15,    2,   81,    2, 0x08 /* Private */,
      18,    0,   86,    2, 0x08 /* Private */,
      19,    0,   87,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    3,    4,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, 0x80000000 | 7,    6,    3,    8,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 11,    2,
    QMetaType::Void, 0x80000000 | 13, QMetaType::Int,    2,    2,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 13, 0x80000000 | 13,   16,   17,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void LibFolderForm::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<LibFolderForm *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->SelectLibFolder((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: _t->SignalDrop((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QWidget*(*)>(_a[3]))); break;
        case 2: _t->on_pushButtonUpdate_clicked(); break;
        case 3: _t->on_treeWidget_clicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 4: _t->on_treeWidget_itemDoubleClicked((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: _t->SlotItemSelectionChanged(); break;
        case 6: _t->SlotCurrentItemChanged((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< QTreeWidgetItem*(*)>(_a[2]))); break;
        case 7: _t->SlotCopyFolder(); break;
        case 8: _t->SlotPasteFolder(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (LibFolderForm::*)(int , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LibFolderForm::SelectLibFolder)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (LibFolderForm::*)(int , int , QWidget * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LibFolderForm::SignalDrop)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject LibFolderForm::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_LibFolderForm.data,
    qt_meta_data_LibFolderForm,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *LibFolderForm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LibFolderForm::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_LibFolderForm.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "ServiceForLayers"))
        return static_cast< ServiceForLayers*>(this);
    return QWidget::qt_metacast(_clname);
}

int LibFolderForm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void LibFolderForm::SelectLibFolder(int _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void LibFolderForm::SignalDrop(int _t1, int _t2, QWidget * _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
