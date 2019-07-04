/****************************************************************************
** Meta object code from reading C++ file 'screen.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../screen.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'screen.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Screen_t {
    QByteArrayData data[18];
    char stringdata0[211];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Screen_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Screen_t qt_meta_stringdata_Screen = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Screen"
QT_MOC_LITERAL(1, 7, 7), // "sendpic"
QT_MOC_LITERAL(2, 15, 0), // ""
QT_MOC_LITERAL(3, 16, 8), // "QPixmap*"
QT_MOC_LITERAL(4, 25, 1), // "p"
QT_MOC_LITERAL(5, 27, 17), // "on_btn_ok_clicked"
QT_MOC_LITERAL(6, 45, 21), // "on_btn_cancel_clicked"
QT_MOC_LITERAL(7, 67, 19), // "on_btn_save_clicked"
QT_MOC_LITERAL(8, 87, 19), // "on_btn_line_clicked"
QT_MOC_LITERAL(9, 107, 19), // "on_btn_text_clicked"
QT_MOC_LITERAL(10, 127, 21), // "on_btn_return_clicked"
QT_MOC_LITERAL(11, 149, 20), // "on_btn_arrow_clicked"
QT_MOC_LITERAL(12, 170, 9), // "showColor"
QT_MOC_LITERAL(13, 180, 9), // "showStyle"
QT_MOC_LITERAL(14, 190, 8), // "setWidth"
QT_MOC_LITERAL(15, 199, 1), // "w"
QT_MOC_LITERAL(16, 201, 7), // "setSize"
QT_MOC_LITERAL(17, 209, 1) // "s"

    },
    "Screen\0sendpic\0\0QPixmap*\0p\0on_btn_ok_clicked\0"
    "on_btn_cancel_clicked\0on_btn_save_clicked\0"
    "on_btn_line_clicked\0on_btn_text_clicked\0"
    "on_btn_return_clicked\0on_btn_arrow_clicked\0"
    "showColor\0showStyle\0setWidth\0w\0setSize\0"
    "s"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Screen[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   74,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   77,    2, 0x0a /* Public */,
       6,    0,   78,    2, 0x0a /* Public */,
       7,    0,   79,    2, 0x0a /* Public */,
       8,    0,   80,    2, 0x0a /* Public */,
       9,    0,   81,    2, 0x0a /* Public */,
      10,    0,   82,    2, 0x0a /* Public */,
      11,    0,   83,    2, 0x0a /* Public */,
      12,    0,   84,    2, 0x0a /* Public */,
      13,    0,   85,    2, 0x0a /* Public */,
      14,    1,   86,    2, 0x0a /* Public */,
      16,    1,   89,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   15,
    QMetaType::Void, QMetaType::Int,   17,

       0        // eod
};

void Screen::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Screen *_t = static_cast<Screen *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendpic((*reinterpret_cast< QPixmap*(*)>(_a[1]))); break;
        case 1: _t->on_btn_ok_clicked(); break;
        case 2: _t->on_btn_cancel_clicked(); break;
        case 3: _t->on_btn_save_clicked(); break;
        case 4: _t->on_btn_line_clicked(); break;
        case 5: _t->on_btn_text_clicked(); break;
        case 6: _t->on_btn_return_clicked(); break;
        case 7: _t->on_btn_arrow_clicked(); break;
        case 8: _t->showColor(); break;
        case 9: _t->showStyle(); break;
        case 10: _t->setWidth((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->setSize((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (Screen::*_t)(QPixmap * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Screen::sendpic)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Screen::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Screen.data,
      qt_meta_data_Screen,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Screen::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Screen::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Screen.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Screen::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void Screen::sendpic(QPixmap * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
