/****************************************************************************
** Meta object code from reading C++ file 'genericobjecttreemodel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "genericobjecttreemodel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'genericobjecttreemodel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_omnetpp__qtenv__GenericObjectTreeModel_t {
    QByteArrayData data[5];
    char stringdata0[69];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_omnetpp__qtenv__GenericObjectTreeModel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_omnetpp__qtenv__GenericObjectTreeModel_t qt_meta_stringdata_omnetpp__qtenv__GenericObjectTreeModel = {
    {
QT_MOC_LITERAL(0, 0, 38), // "omnetpp::qtenv::GenericObject..."
QT_MOC_LITERAL(1, 39, 10), // "dataEdited"
QT_MOC_LITERAL(2, 50, 0), // ""
QT_MOC_LITERAL(3, 51, 11), // "QModelIndex"
QT_MOC_LITERAL(4, 63, 5) // "index"

    },
    "omnetpp::qtenv::GenericObjectTreeModel\0"
    "dataEdited\0\0QModelIndex\0index"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_omnetpp__qtenv__GenericObjectTreeModel[] = {

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
       1,    1,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

       0        // eod
};

void omnetpp::qtenv::GenericObjectTreeModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GenericObjectTreeModel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->dataEdited((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (GenericObjectTreeModel::*)(const QModelIndex & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GenericObjectTreeModel::dataEdited)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject omnetpp::qtenv::GenericObjectTreeModel::staticMetaObject = { {
    &QAbstractItemModel::staticMetaObject,
    qt_meta_stringdata_omnetpp__qtenv__GenericObjectTreeModel.data,
    qt_meta_data_omnetpp__qtenv__GenericObjectTreeModel,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *omnetpp::qtenv::GenericObjectTreeModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *omnetpp::qtenv::GenericObjectTreeModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_omnetpp__qtenv__GenericObjectTreeModel.stringdata0))
        return static_cast<void*>(this);
    return QAbstractItemModel::qt_metacast(_clname);
}

int omnetpp::qtenv::GenericObjectTreeModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractItemModel::qt_metacall(_c, _id, _a);
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
void omnetpp::qtenv::GenericObjectTreeModel::dataEdited(const QModelIndex & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
