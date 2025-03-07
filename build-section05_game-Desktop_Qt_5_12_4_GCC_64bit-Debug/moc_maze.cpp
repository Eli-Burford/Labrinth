/****************************************************************************
** Meta object code from reading C++ file 'maze.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../section05_game/maze.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'maze.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_maze_t {
    QByteArrayData data[9];
    char stringdata0[88];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_maze_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_maze_t qt_meta_stringdata_maze = {
    {
QT_MOC_LITERAL(0, 0, 4), // "maze"
QT_MOC_LITERAL(1, 5, 13), // "endGameSignal"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 1), // "m"
QT_MOC_LITERAL(4, 22, 15), // "playerCollision"
QT_MOC_LITERAL(5, 38, 7), // "Player*"
QT_MOC_LITERAL(6, 46, 17), // "spawnSpeedPowerUp"
QT_MOC_LITERAL(7, 64, 14), // "speedCountDown"
QT_MOC_LITERAL(8, 79, 8) // "testSlot"

    },
    "maze\0endGameSignal\0\0m\0playerCollision\0"
    "Player*\0spawnSpeedPowerUp\0speedCountDown\0"
    "testSlot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_maze[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   42,    2, 0x08 /* Private */,
       6,    0,   45,    2, 0x08 /* Private */,
       7,    0,   46,    2, 0x08 /* Private */,
       8,    0,   47,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Char,    3,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void maze::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<maze *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->endGameSignal((*reinterpret_cast< char(*)>(_a[1]))); break;
        case 1: _t->playerCollision((*reinterpret_cast< Player*(*)>(_a[1]))); break;
        case 2: _t->spawnSpeedPowerUp(); break;
        case 3: _t->speedCountDown(); break;
        case 4: _t->testSlot(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (maze::*)(char );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&maze::endGameSignal)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject maze::staticMetaObject = { {
    &QDialog::staticMetaObject,
    qt_meta_stringdata_maze.data,
    qt_meta_data_maze,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *maze::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *maze::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_maze.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int maze::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
void maze::endGameSignal(char _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
