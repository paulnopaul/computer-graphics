/****************************************************************************
** Meta object code from reading C++ file 'polygonwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../lab_06/polygonwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'polygonwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PolygonWidget_t {
    QByteArrayData data[7];
    char stringdata0[82];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PolygonWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PolygonWidget_t qt_meta_stringdata_PolygonWidget = {
    {
QT_MOC_LITERAL(0, 0, 13), // "PolygonWidget"
QT_MOC_LITERAL(1, 14, 12), // "newEdgeAdded"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 12), // "edgesCleared"
QT_MOC_LITERAL(4, 41, 18), // "newFillPointCoords"
QT_MOC_LITERAL(5, 60, 8), // "newPoint"
QT_MOC_LITERAL(6, 69, 12) // "figureFilled"

    },
    "PolygonWidget\0newEdgeAdded\0\0edgesCleared\0"
    "newFillPointCoords\0newPoint\0figureFilled"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PolygonWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,
       3,    0,   37,    2, 0x06 /* Public */,
       4,    1,   38,    2, 0x06 /* Public */,
       6,    0,   41,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QLine,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPoint,    5,
    QMetaType::Void,

       0        // eod
};

void PolygonWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PolygonWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->newEdgeAdded((*reinterpret_cast< const QLine(*)>(_a[1]))); break;
        case 1: _t->edgesCleared(); break;
        case 2: _t->newFillPointCoords((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 3: _t->figureFilled(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (PolygonWidget::*)(const QLine & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PolygonWidget::newEdgeAdded)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (PolygonWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PolygonWidget::edgesCleared)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (PolygonWidget::*)(QPoint );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PolygonWidget::newFillPointCoords)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (PolygonWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PolygonWidget::figureFilled)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject PolygonWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_PolygonWidget.data,
    qt_meta_data_PolygonWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *PolygonWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PolygonWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PolygonWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int PolygonWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void PolygonWidget::newEdgeAdded(const QLine & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PolygonWidget::edgesCleared()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void PolygonWidget::newFillPointCoords(QPoint _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void PolygonWidget::figureFilled()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE