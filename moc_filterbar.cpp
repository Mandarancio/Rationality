/****************************************************************************
** Meta object code from reading C++ file 'filterbar.h'
**
** Created: Tue Jun 22 23:46:02 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "filterbar.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'filterbar.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FilterBar[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      22,   11,   10,   10, 0x05,
      49,   47,   10,   10, 0x05,
      62,   47,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
      76,   10,   10,   10, 0x0a,
      93,   89,   10,   10, 0x0a,
     107,   10,   10,   10, 0x0a,
     114,   10,   10,   10, 0x0a,
     131,  124,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_FilterBar[] = {
    "FilterBar\0\0tag,signal\0currentDir(QString,bool)\0"
    "E\0isLast(bool)\0isFirst(bool)\0setHistory()\0"
    "tag\0open(QString)\0back()\0forward()\0"
    "filter\0filter(QString)\0"
};

const QMetaObject FilterBar::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_FilterBar,
      qt_meta_data_FilterBar, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &FilterBar::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *FilterBar::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *FilterBar::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FilterBar))
        return static_cast<void*>(const_cast< FilterBar*>(this));
    return QWidget::qt_metacast(_clname);
}

int FilterBar::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: currentDir((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 1: isLast((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: isFirst((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: setHistory(); break;
        case 4: open((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: back(); break;
        case 6: forward(); break;
        case 7: filter((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void FilterBar::currentDir(QString _t1, bool _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void FilterBar::isLast(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void FilterBar::isFirst(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
