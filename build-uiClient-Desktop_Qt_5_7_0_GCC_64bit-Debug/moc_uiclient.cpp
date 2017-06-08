/****************************************************************************
** Meta object code from reading C++ file 'uiclient.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../uiClient/uiclient.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'uiclient.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_UiClient_t {
    QByteArrayData data[7];
    char stringdata0[101];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_UiClient_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_UiClient_t qt_meta_stringdata_UiClient = {
    {
QT_MOC_LITERAL(0, 0, 8), // "UiClient"
QT_MOC_LITERAL(1, 9, 11), // "clearSignal"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 24), // "std::vector<std::string>"
QT_MOC_LITERAL(4, 47, 5), // "users"
QT_MOC_LITERAL(5, 53, 13), // "display_users"
QT_MOC_LITERAL(6, 67, 33) // "on_lineEdit_message_returnPre..."

    },
    "UiClient\0clearSignal\0\0std::vector<std::string>\0"
    "users\0display_users\0"
    "on_lineEdit_message_returnPressed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UiClient[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   32,    2, 0x0a /* Public */,
       6,    0,   35,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,

       0        // eod
};

void UiClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        UiClient *_t = static_cast<UiClient *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->clearSignal((*reinterpret_cast< std::vector<std::string>(*)>(_a[1]))); break;
        case 1: _t->display_users((*reinterpret_cast< std::vector<std::string>(*)>(_a[1]))); break;
        case 2: _t->on_lineEdit_message_returnPressed(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (UiClient::*_t)(std::vector<std::string> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&UiClient::clearSignal)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject UiClient::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_UiClient.data,
      qt_meta_data_UiClient,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *UiClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UiClient::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_UiClient.stringdata0))
        return static_cast<void*>(const_cast< UiClient*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int UiClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void UiClient::clearSignal(std::vector<std::string> _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
