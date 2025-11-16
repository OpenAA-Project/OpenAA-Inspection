/****************************************************************************
** Meta object code from reading C++ file 'XGUIFormBase.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.13)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../Open/XGUIFormBase.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'XGUIFormBase.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.13. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MenuInfoList_t {
    QByteArrayData data[5];
    char stringdata0[53];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MenuInfoList_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MenuInfoList_t qt_meta_stringdata_MenuInfoList = {
    {
QT_MOC_LITERAL(0, 0, 12), // "MenuInfoList"
QT_MOC_LITERAL(1, 13, 23), // "SignalTriggeredFromMenu"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 2), // "id"
QT_MOC_LITERAL(4, 41, 11) // "SlotTrigger"

    },
    "MenuInfoList\0SignalTriggeredFromMenu\0"
    "\0id\0SlotTrigger"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MenuInfoList[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   27,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void MenuInfoList::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MenuInfoList *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->SignalTriggeredFromMenu((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->SlotTrigger(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MenuInfoList::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MenuInfoList::SignalTriggeredFromMenu)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MenuInfoList::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_MenuInfoList.data,
    qt_meta_data_MenuInfoList,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MenuInfoList::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MenuInfoList::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MenuInfoList.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "NPList<MenuInfoList>"))
        return static_cast< NPList<MenuInfoList>*>(this);
    return QObject::qt_metacast(_clname);
}

int MenuInfoList::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
void MenuInfoList::SignalTriggeredFromMenu(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_ButtonRightClickEnabler_t {
    QByteArrayData data[6];
    char stringdata0[73];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ButtonRightClickEnabler_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ButtonRightClickEnabler_t qt_meta_stringdata_ButtonRightClickEnabler = {
    {
QT_MOC_LITERAL(0, 0, 23), // "ButtonRightClickEnabler"
QT_MOC_LITERAL(1, 24, 12), // "RightClicked"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 16), // "QAbstractButton*"
QT_MOC_LITERAL(4, 55, 3), // "obj"
QT_MOC_LITERAL(5, 59, 13) // "DoubleClicked"

    },
    "ButtonRightClickEnabler\0RightClicked\0"
    "\0QAbstractButton*\0obj\0DoubleClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ButtonRightClickEnabler[] = {

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
       1,    1,   24,    2, 0x06 /* Public */,
       5,    1,   27,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,

       0        // eod
};

void ButtonRightClickEnabler::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ButtonRightClickEnabler *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->RightClicked((*reinterpret_cast< QAbstractButton*(*)>(_a[1]))); break;
        case 1: _t->DoubleClicked((*reinterpret_cast< QAbstractButton*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ButtonRightClickEnabler::*)(QAbstractButton * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ButtonRightClickEnabler::RightClicked)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ButtonRightClickEnabler::*)(QAbstractButton * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ButtonRightClickEnabler::DoubleClicked)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ButtonRightClickEnabler::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_ButtonRightClickEnabler.data,
    qt_meta_data_ButtonRightClickEnabler,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ButtonRightClickEnabler::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ButtonRightClickEnabler::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ButtonRightClickEnabler.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ButtonRightClickEnabler::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
void ButtonRightClickEnabler::RightClicked(QAbstractButton * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ButtonRightClickEnabler::DoubleClicked(QAbstractButton * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
struct qt_meta_stringdata_GUIFormBase_t {
    QByteArrayData data[48];
    char stringdata0[711];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GUIFormBase_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GUIFormBase_t qt_meta_stringdata_GUIFormBase = {
    {
QT_MOC_LITERAL(0, 0, 11), // "GUIFormBase"
QT_MOC_LITERAL(1, 12, 21), // "SignalRefreshInPlayer"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 5), // "int64"
QT_MOC_LITERAL(4, 41, 17), // "shownInspectionID"
QT_MOC_LITERAL(5, 59, 22), // "SignalOnTheWayInPlayer"
QT_MOC_LITERAL(6, 82, 30), // "SignalRefreshByEveryInspection"
QT_MOC_LITERAL(7, 113, 19), // "SignalRefreshInEdit"
QT_MOC_LITERAL(8, 133, 23), // "SignalRefreshInScanning"
QT_MOC_LITERAL(9, 157, 17), // "SignalDoneExecute"
QT_MOC_LITERAL(10, 175, 30), // "ExecuteInspectBase::MotionMode"
QT_MOC_LITERAL(11, 206, 4), // "mode"
QT_MOC_LITERAL(12, 211, 12), // "SignalResize"
QT_MOC_LITERAL(13, 224, 10), // "SignalMove"
QT_MOC_LITERAL(14, 235, 13), // "SignalRelease"
QT_MOC_LITERAL(15, 249, 11), // "SignalClose"
QT_MOC_LITERAL(16, 261, 12), // "GUIFormBase*"
QT_MOC_LITERAL(17, 274, 4), // "form"
QT_MOC_LITERAL(18, 279, 16), // "SignalPushButton"
QT_MOC_LITERAL(19, 296, 13), // "SignalRaiseUp"
QT_MOC_LITERAL(20, 310, 13), // "SignalRepaint"
QT_MOC_LITERAL(21, 324, 19), // "SlotRefreshInPlayer"
QT_MOC_LITERAL(22, 344, 20), // "SlotOnTheWayInPlayer"
QT_MOC_LITERAL(23, 365, 28), // "SlotRefreshByEveryInspection"
QT_MOC_LITERAL(24, 394, 17), // "SlotRefreshInEdit"
QT_MOC_LITERAL(25, 412, 21), // "SlotRefreshInScanning"
QT_MOC_LITERAL(26, 434, 15), // "SlotDoneExecute"
QT_MOC_LITERAL(27, 450, 11), // "SlotCommand"
QT_MOC_LITERAL(28, 462, 3), // "cmd"
QT_MOC_LITERAL(29, 466, 14), // "SlotWroteSlave"
QT_MOC_LITERAL(30, 481, 9), // "XDateTime"
QT_MOC_LITERAL(31, 491, 2), // "tm"
QT_MOC_LITERAL(32, 494, 17), // "SlotChangeLotInfo"
QT_MOC_LITERAL(33, 512, 10), // "DeliveryNo"
QT_MOC_LITERAL(34, 523, 12), // "SlotZOrderUp"
QT_MOC_LITERAL(35, 536, 12), // "RemoveAction"
QT_MOC_LITERAL(36, 549, 14), // "ForcusProperty"
QT_MOC_LITERAL(37, 564, 28), // "ReleaseAllSelectedInEditMode"
QT_MOC_LITERAL(38, 593, 12), // "ChangeTabTop"
QT_MOC_LITERAL(39, 606, 10), // "TurnUpDown"
QT_MOC_LITERAL(40, 617, 13), // "DeleteTabPage"
QT_MOC_LITERAL(41, 631, 16), // "ChangeTextAction"
QT_MOC_LITERAL(42, 648, 14), // "SlotPushButton"
QT_MOC_LITERAL(43, 663, 11), // "SlotRepaint"
QT_MOC_LITERAL(44, 675, 14), // "MessageOutFunc"
QT_MOC_LITERAL(45, 690, 1), // "N"
QT_MOC_LITERAL(46, 692, 15), // "SlotTriggerMenu"
QT_MOC_LITERAL(47, 708, 2) // "id"

    },
    "GUIFormBase\0SignalRefreshInPlayer\0\0"
    "int64\0shownInspectionID\0SignalOnTheWayInPlayer\0"
    "SignalRefreshByEveryInspection\0"
    "SignalRefreshInEdit\0SignalRefreshInScanning\0"
    "SignalDoneExecute\0ExecuteInspectBase::MotionMode\0"
    "mode\0SignalResize\0SignalMove\0SignalRelease\0"
    "SignalClose\0GUIFormBase*\0form\0"
    "SignalPushButton\0SignalRaiseUp\0"
    "SignalRepaint\0SlotRefreshInPlayer\0"
    "SlotOnTheWayInPlayer\0SlotRefreshByEveryInspection\0"
    "SlotRefreshInEdit\0SlotRefreshInScanning\0"
    "SlotDoneExecute\0SlotCommand\0cmd\0"
    "SlotWroteSlave\0XDateTime\0tm\0"
    "SlotChangeLotInfo\0DeliveryNo\0SlotZOrderUp\0"
    "RemoveAction\0ForcusProperty\0"
    "ReleaseAllSelectedInEditMode\0ChangeTabTop\0"
    "TurnUpDown\0DeleteTabPage\0ChangeTextAction\0"
    "SlotPushButton\0SlotRepaint\0MessageOutFunc\0"
    "N\0SlotTriggerMenu\0id"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GUIFormBase[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      34,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      13,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  184,    2, 0x06 /* Public */,
       5,    1,  187,    2, 0x06 /* Public */,
       6,    1,  190,    2, 0x06 /* Public */,
       7,    0,  193,    2, 0x06 /* Public */,
       8,    1,  194,    2, 0x06 /* Public */,
       9,    2,  197,    2, 0x06 /* Public */,
      12,    0,  202,    2, 0x06 /* Public */,
      13,    0,  203,    2, 0x06 /* Public */,
      14,    0,  204,    2, 0x06 /* Public */,
      15,    1,  205,    2, 0x06 /* Public */,
      18,    0,  208,    2, 0x06 /* Public */,
      19,    0,  209,    2, 0x06 /* Public */,
      20,    0,  210,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      21,    1,  211,    2, 0x0a /* Public */,
      22,    1,  214,    2, 0x0a /* Public */,
      23,    1,  217,    2, 0x0a /* Public */,
      24,    0,  220,    2, 0x0a /* Public */,
      25,    1,  221,    2, 0x0a /* Public */,
      26,    2,  224,    2, 0x0a /* Public */,
      27,    1,  229,    2, 0x0a /* Public */,
      29,    1,  232,    2, 0x0a /* Public */,
      32,    1,  235,    2, 0x0a /* Public */,
      34,    0,  238,    2, 0x0a /* Public */,
      35,    0,  239,    2, 0x0a /* Public */,
      36,    0,  240,    2, 0x0a /* Public */,
      37,    0,  241,    2, 0x0a /* Public */,
      38,    0,  242,    2, 0x0a /* Public */,
      39,    0,  243,    2, 0x0a /* Public */,
      40,    0,  244,    2, 0x0a /* Public */,
      41,    0,  245,    2, 0x0a /* Public */,
      42,    0,  246,    2, 0x0a /* Public */,
      43,    0,  247,    2, 0x0a /* Public */,
      44,    1,  248,    2, 0x08 /* Private */,
      46,    1,  251,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 10,    4,   11,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 16,   17,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 10,    4,   11,
    QMetaType::Void, QMetaType::Int,   28,
    QMetaType::Void, 0x80000000 | 30,   31,
    QMetaType::Void, QMetaType::Int,   33,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   45,
    QMetaType::Void, QMetaType::Int,   47,

       0        // eod
};

void GUIFormBase::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GUIFormBase *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->SignalRefreshInPlayer((*reinterpret_cast< int64(*)>(_a[1]))); break;
        case 1: _t->SignalOnTheWayInPlayer((*reinterpret_cast< int64(*)>(_a[1]))); break;
        case 2: _t->SignalRefreshByEveryInspection((*reinterpret_cast< int64(*)>(_a[1]))); break;
        case 3: _t->SignalRefreshInEdit(); break;
        case 4: _t->SignalRefreshInScanning((*reinterpret_cast< int64(*)>(_a[1]))); break;
        case 5: _t->SignalDoneExecute((*reinterpret_cast< int64(*)>(_a[1])),(*reinterpret_cast< ExecuteInspectBase::MotionMode(*)>(_a[2]))); break;
        case 6: _t->SignalResize(); break;
        case 7: _t->SignalMove(); break;
        case 8: _t->SignalRelease(); break;
        case 9: _t->SignalClose((*reinterpret_cast< GUIFormBase*(*)>(_a[1]))); break;
        case 10: _t->SignalPushButton(); break;
        case 11: _t->SignalRaiseUp(); break;
        case 12: _t->SignalRepaint(); break;
        case 13: _t->SlotRefreshInPlayer((*reinterpret_cast< int64(*)>(_a[1]))); break;
        case 14: _t->SlotOnTheWayInPlayer((*reinterpret_cast< int64(*)>(_a[1]))); break;
        case 15: _t->SlotRefreshByEveryInspection((*reinterpret_cast< int64(*)>(_a[1]))); break;
        case 16: _t->SlotRefreshInEdit(); break;
        case 17: _t->SlotRefreshInScanning((*reinterpret_cast< int64(*)>(_a[1]))); break;
        case 18: _t->SlotDoneExecute((*reinterpret_cast< int64(*)>(_a[1])),(*reinterpret_cast< ExecuteInspectBase::MotionMode(*)>(_a[2]))); break;
        case 19: _t->SlotCommand((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 20: _t->SlotWroteSlave((*reinterpret_cast< XDateTime(*)>(_a[1]))); break;
        case 21: _t->SlotChangeLotInfo((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 22: _t->SlotZOrderUp(); break;
        case 23: _t->RemoveAction(); break;
        case 24: _t->ForcusProperty(); break;
        case 25: _t->ReleaseAllSelectedInEditMode(); break;
        case 26: _t->ChangeTabTop(); break;
        case 27: _t->TurnUpDown(); break;
        case 28: _t->DeleteTabPage(); break;
        case 29: _t->ChangeTextAction(); break;
        case 30: _t->SlotPushButton(); break;
        case 31: _t->SlotRepaint(); break;
        case 32: _t->MessageOutFunc((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 33: _t->SlotTriggerMenu((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 9:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< GUIFormBase* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (GUIFormBase::*)(int64 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GUIFormBase::SignalRefreshInPlayer)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (GUIFormBase::*)(int64 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GUIFormBase::SignalOnTheWayInPlayer)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (GUIFormBase::*)(int64 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GUIFormBase::SignalRefreshByEveryInspection)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (GUIFormBase::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GUIFormBase::SignalRefreshInEdit)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (GUIFormBase::*)(int64 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GUIFormBase::SignalRefreshInScanning)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (GUIFormBase::*)(int64 , ExecuteInspectBase::MotionMode );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GUIFormBase::SignalDoneExecute)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (GUIFormBase::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GUIFormBase::SignalResize)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (GUIFormBase::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GUIFormBase::SignalMove)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (GUIFormBase::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GUIFormBase::SignalRelease)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (GUIFormBase::*)(GUIFormBase * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GUIFormBase::SignalClose)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (GUIFormBase::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GUIFormBase::SignalPushButton)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (GUIFormBase::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GUIFormBase::SignalRaiseUp)) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (GUIFormBase::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GUIFormBase::SignalRepaint)) {
                *result = 12;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject GUIFormBase::staticMetaObject = { {
    QMetaObject::SuperData::link<QFrame::staticMetaObject>(),
    qt_meta_stringdata_GUIFormBase.data,
    qt_meta_data_GUIFormBase,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *GUIFormBase::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GUIFormBase::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GUIFormBase.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "IdentifiedClass"))
        return static_cast< IdentifiedClass*>(this);
    return QFrame::qt_metacast(_clname);
}

int GUIFormBase::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 34)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 34;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 34)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 34;
    }
    return _id;
}

// SIGNAL 0
void GUIFormBase::SignalRefreshInPlayer(int64 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void GUIFormBase::SignalOnTheWayInPlayer(int64 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void GUIFormBase::SignalRefreshByEveryInspection(int64 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void GUIFormBase::SignalRefreshInEdit()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void GUIFormBase::SignalRefreshInScanning(int64 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void GUIFormBase::SignalDoneExecute(int64 _t1, ExecuteInspectBase::MotionMode _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void GUIFormBase::SignalResize()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void GUIFormBase::SignalMove()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void GUIFormBase::SignalRelease()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}

// SIGNAL 9
void GUIFormBase::SignalClose(GUIFormBase * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void GUIFormBase::SignalPushButton()
{
    QMetaObject::activate(this, &staticMetaObject, 10, nullptr);
}

// SIGNAL 11
void GUIFormBase::SignalRaiseUp()
{
    QMetaObject::activate(this, &staticMetaObject, 11, nullptr);
}

// SIGNAL 12
void GUIFormBase::SignalRepaint()
{
    QMetaObject::activate(this, &staticMetaObject, 12, nullptr);
}
struct qt_meta_stringdata_ParamGUI_t {
    QByteArrayData data[7];
    char stringdata0[70];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ParamGUI_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ParamGUI_t qt_meta_stringdata_ParamGUI = {
    {
QT_MOC_LITERAL(0, 0, 8), // "ParamGUI"
QT_MOC_LITERAL(1, 9, 25), // "SignalExecuteForByteArray"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 8), // "Category"
QT_MOC_LITERAL(4, 45, 7), // "KeyName"
QT_MOC_LITERAL(5, 53, 11), // "QByteArray&"
QT_MOC_LITERAL(6, 65, 4) // "data"

    },
    "ParamGUI\0SignalExecuteForByteArray\0\0"
    "Category\0KeyName\0QByteArray&\0data"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ParamGUI[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString, 0x80000000 | 5,    3,    4,    6,

       0        // eod
};

void ParamGUI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ParamGUI *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->SignalExecuteForByteArray((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< QByteArray(*)>(_a[3]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ParamGUI::*)(const QString & , const QString & , QByteArray & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ParamGUI::SignalExecuteForByteArray)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ParamGUI::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_ParamGUI.data,
    qt_meta_data_ParamGUI,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ParamGUI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ParamGUI::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ParamGUI.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "ParamBase"))
        return static_cast< ParamBase*>(this);
    return QObject::qt_metacast(_clname);
}

int ParamGUI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void ParamGUI::SignalExecuteForByteArray(const QString & _t1, const QString & _t2, QByteArray & _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_KeyPressIgnorer_t {
    QByteArrayData data[1];
    char stringdata0[16];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_KeyPressIgnorer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_KeyPressIgnorer_t qt_meta_stringdata_KeyPressIgnorer = {
    {
QT_MOC_LITERAL(0, 0, 15) // "KeyPressIgnorer"

    },
    "KeyPressIgnorer"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_KeyPressIgnorer[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void KeyPressIgnorer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject KeyPressIgnorer::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_KeyPressIgnorer.data,
    qt_meta_data_KeyPressIgnorer,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *KeyPressIgnorer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *KeyPressIgnorer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_KeyPressIgnorer.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int KeyPressIgnorer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
