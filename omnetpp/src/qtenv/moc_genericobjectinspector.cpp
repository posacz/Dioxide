/****************************************************************************
** Meta object code from reading C++ file 'genericobjectinspector.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "genericobjectinspector.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'genericobjectinspector.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_omnetpp__qtenv__GenericObjectInspector_t {
    QByteArrayData data[17];
    char stringdata0[226];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_omnetpp__qtenv__GenericObjectInspector_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_omnetpp__qtenv__GenericObjectInspector_t qt_meta_stringdata_omnetpp__qtenv__GenericObjectInspector = {
    {
QT_MOC_LITERAL(0, 0, 38), // "omnetpp::qtenv::GenericObject..."
QT_MOC_LITERAL(1, 39, 19), // "onTreeViewActivated"
QT_MOC_LITERAL(2, 59, 0), // ""
QT_MOC_LITERAL(3, 60, 11), // "QModelIndex"
QT_MOC_LITERAL(4, 72, 5), // "index"
QT_MOC_LITERAL(5, 78, 12), // "onDataEdited"
QT_MOC_LITERAL(6, 91, 23), // "gatherVisibleDataIfSafe"
QT_MOC_LITERAL(7, 115, 17), // "createContextMenu"
QT_MOC_LITERAL(8, 133, 3), // "pos"
QT_MOC_LITERAL(9, 137, 7), // "setMode"
QT_MOC_LITERAL(10, 145, 4), // "Mode"
QT_MOC_LITERAL(11, 150, 4), // "mode"
QT_MOC_LITERAL(12, 155, 13), // "toGroupedMode"
QT_MOC_LITERAL(13, 169, 10), // "toFlatMode"
QT_MOC_LITERAL(14, 180, 17), // "toInheritanceMode"
QT_MOC_LITERAL(15, 198, 14), // "toChildrenMode"
QT_MOC_LITERAL(16, 213, 12) // "toPacketMode"

    },
    "omnetpp::qtenv::GenericObjectInspector\0"
    "onTreeViewActivated\0\0QModelIndex\0index\0"
    "onDataEdited\0gatherVisibleDataIfSafe\0"
    "createContextMenu\0pos\0setMode\0Mode\0"
    "mode\0toGroupedMode\0toFlatMode\0"
    "toInheritanceMode\0toChildrenMode\0"
    "toPacketMode"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_omnetpp__qtenv__GenericObjectInspector[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x09 /* Protected */,
       5,    0,   67,    2, 0x09 /* Protected */,
       6,    0,   68,    2, 0x09 /* Protected */,
       7,    1,   69,    2, 0x09 /* Protected */,
       9,    1,   72,    2, 0x09 /* Protected */,
      12,    0,   75,    2, 0x09 /* Protected */,
      13,    0,   76,    2, 0x09 /* Protected */,
      14,    0,   77,    2, 0x09 /* Protected */,
      15,    0,   78,    2, 0x09 /* Protected */,
      16,    0,   79,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPoint,    8,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void omnetpp::qtenv::GenericObjectInspector::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GenericObjectInspector *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onTreeViewActivated((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 1: _t->onDataEdited(); break;
        case 2: _t->gatherVisibleDataIfSafe(); break;
        case 3: _t->createContextMenu((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 4: _t->setMode((*reinterpret_cast< Mode(*)>(_a[1]))); break;
        case 5: _t->toGroupedMode(); break;
        case 6: _t->toFlatMode(); break;
        case 7: _t->toInheritanceMode(); break;
        case 8: _t->toChildrenMode(); break;
        case 9: _t->toPacketMode(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject omnetpp::qtenv::GenericObjectInspector::staticMetaObject = { {
    &Inspector::staticMetaObject,
    qt_meta_stringdata_omnetpp__qtenv__GenericObjectInspector.data,
    qt_meta_data_omnetpp__qtenv__GenericObjectInspector,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *omnetpp::qtenv::GenericObjectInspector::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *omnetpp::qtenv::GenericObjectInspector::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_omnetpp__qtenv__GenericObjectInspector.stringdata0))
        return static_cast<void*>(this);
    return Inspector::qt_metacast(_clname);
}

int omnetpp::qtenv::GenericObjectInspector::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Inspector::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
