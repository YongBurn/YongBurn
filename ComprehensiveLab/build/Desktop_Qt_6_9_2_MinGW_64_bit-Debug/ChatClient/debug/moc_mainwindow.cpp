/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../ChatClient/mainwindow.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.9.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN10MainWindowE_t {};
} // unnamed namespace

template <> constexpr inline auto MainWindow::qt_create_metaobjectdata<qt_meta_tag_ZN10MainWindowE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "MainWindow",
        "on_loginButton_clicked",
        "",
        "on_registerButton_clicked",
        "on_returnButton_clicked",
        "on_Register_clicked",
        "on_logoutBtn_clicked",
        "on_sayBtn_clicked",
        "on_SendprivateChat_clicked",
        "on_PrivateChatreturn_clicked",
        "on_contacts_clicked",
        "on_AddGroup_clicked",
        "on_Addcontact_clicked",
        "on_Return_clicked",
        "on_userListWidget_itemDoubleClicked",
        "QListWidgetItem*",
        "item",
        "on_userListWidget_2_itemDoubleClicked",
        "on_userListWidget_4_itemDoubleClicked",
        "on_Grouping_itemClicked",
        "connectedToServer",
        "disconnectedFromServer",
        "messageReceived",
        "sender",
        "text",
        "jsonReceived",
        "docObj",
        "userJoined",
        "user",
        "userLeft",
        "userListReceived",
        "list",
        "displayPrivateMessage",
        "timestamp",
        "isSentByMe",
        "onNetworkConnected",
        "onNetworkDisconnected",
        "onNetworkError",
        "error",
        "onNetworkMessageReceived",
        "message",
        "onReconnectionAttempt",
        "attempt",
        "loadLocalData",
        "saveMessageToLocal",
        "receiver",
        "content",
        "type",
        "loadChatHistory",
        "contact",
        "updateConnectionStatus",
        "updateContactList",
        "updateGroupList",
        "syncPrivateChatUserList"
    };

    QtMocHelpers::UintData qt_methods {
        // Slot 'on_loginButton_clicked'
        QtMocHelpers::SlotData<void()>(1, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_registerButton_clicked'
        QtMocHelpers::SlotData<void()>(3, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_returnButton_clicked'
        QtMocHelpers::SlotData<void()>(4, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_Register_clicked'
        QtMocHelpers::SlotData<void()>(5, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_logoutBtn_clicked'
        QtMocHelpers::SlotData<void()>(6, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_sayBtn_clicked'
        QtMocHelpers::SlotData<void()>(7, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_SendprivateChat_clicked'
        QtMocHelpers::SlotData<void()>(8, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_PrivateChatreturn_clicked'
        QtMocHelpers::SlotData<void()>(9, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_contacts_clicked'
        QtMocHelpers::SlotData<void()>(10, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_AddGroup_clicked'
        QtMocHelpers::SlotData<void()>(11, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_Addcontact_clicked'
        QtMocHelpers::SlotData<void()>(12, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_Return_clicked'
        QtMocHelpers::SlotData<void()>(13, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_userListWidget_itemDoubleClicked'
        QtMocHelpers::SlotData<void(QListWidgetItem *)>(14, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 15, 16 },
        }}),
        // Slot 'on_userListWidget_2_itemDoubleClicked'
        QtMocHelpers::SlotData<void(QListWidgetItem *)>(17, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 15, 16 },
        }}),
        // Slot 'on_userListWidget_4_itemDoubleClicked'
        QtMocHelpers::SlotData<void(QListWidgetItem *)>(18, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 15, 16 },
        }}),
        // Slot 'on_Grouping_itemClicked'
        QtMocHelpers::SlotData<void(QListWidgetItem *)>(19, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 15, 16 },
        }}),
        // Slot 'connectedToServer'
        QtMocHelpers::SlotData<void()>(20, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'disconnectedFromServer'
        QtMocHelpers::SlotData<void()>(21, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'messageReceived'
        QtMocHelpers::SlotData<void(const QString &, const QString &)>(22, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 23 }, { QMetaType::QString, 24 },
        }}),
        // Slot 'jsonReceived'
        QtMocHelpers::SlotData<void(const QJsonObject &)>(25, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QJsonObject, 26 },
        }}),
        // Slot 'userJoined'
        QtMocHelpers::SlotData<void(const QString &)>(27, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 28 },
        }}),
        // Slot 'userLeft'
        QtMocHelpers::SlotData<void(const QString &)>(29, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 28 },
        }}),
        // Slot 'userListReceived'
        QtMocHelpers::SlotData<void(const QStringList &)>(30, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QStringList, 31 },
        }}),
        // Slot 'displayPrivateMessage'
        QtMocHelpers::SlotData<void(const QString &, const QString &, const QString &, bool)>(32, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 23 }, { QMetaType::QString, 24 }, { QMetaType::QString, 33 }, { QMetaType::Bool, 34 },
        }}),
        // Slot 'onNetworkConnected'
        QtMocHelpers::SlotData<void()>(35, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onNetworkDisconnected'
        QtMocHelpers::SlotData<void()>(36, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onNetworkError'
        QtMocHelpers::SlotData<void(const QString &)>(37, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 38 },
        }}),
        // Slot 'onNetworkMessageReceived'
        QtMocHelpers::SlotData<void(const QJsonObject &)>(39, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QJsonObject, 40 },
        }}),
        // Slot 'onReconnectionAttempt'
        QtMocHelpers::SlotData<void(int)>(41, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 42 },
        }}),
        // Slot 'loadLocalData'
        QtMocHelpers::SlotData<void()>(43, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'saveMessageToLocal'
        QtMocHelpers::SlotData<void(const QString &, const QString &, const QString &, const QString &)>(44, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 23 }, { QMetaType::QString, 45 }, { QMetaType::QString, 46 }, { QMetaType::QString, 47 },
        }}),
        // Slot 'loadChatHistory'
        QtMocHelpers::SlotData<void(const QString &)>(48, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 49 },
        }}),
        // Slot 'updateConnectionStatus'
        QtMocHelpers::SlotData<void()>(50, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'updateContactList'
        QtMocHelpers::SlotData<void()>(51, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'updateGroupList'
        QtMocHelpers::SlotData<void()>(52, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'syncPrivateChatUserList'
        QtMocHelpers::SlotData<void()>(53, 2, QMC::AccessPrivate, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<MainWindow, qt_meta_tag_ZN10MainWindowE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10MainWindowE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10MainWindowE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN10MainWindowE_t>.metaTypes,
    nullptr
} };

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<MainWindow *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->on_loginButton_clicked(); break;
        case 1: _t->on_registerButton_clicked(); break;
        case 2: _t->on_returnButton_clicked(); break;
        case 3: _t->on_Register_clicked(); break;
        case 4: _t->on_logoutBtn_clicked(); break;
        case 5: _t->on_sayBtn_clicked(); break;
        case 6: _t->on_SendprivateChat_clicked(); break;
        case 7: _t->on_PrivateChatreturn_clicked(); break;
        case 8: _t->on_contacts_clicked(); break;
        case 9: _t->on_AddGroup_clicked(); break;
        case 10: _t->on_Addcontact_clicked(); break;
        case 11: _t->on_Return_clicked(); break;
        case 12: _t->on_userListWidget_itemDoubleClicked((*reinterpret_cast< std::add_pointer_t<QListWidgetItem*>>(_a[1]))); break;
        case 13: _t->on_userListWidget_2_itemDoubleClicked((*reinterpret_cast< std::add_pointer_t<QListWidgetItem*>>(_a[1]))); break;
        case 14: _t->on_userListWidget_4_itemDoubleClicked((*reinterpret_cast< std::add_pointer_t<QListWidgetItem*>>(_a[1]))); break;
        case 15: _t->on_Grouping_itemClicked((*reinterpret_cast< std::add_pointer_t<QListWidgetItem*>>(_a[1]))); break;
        case 16: _t->connectedToServer(); break;
        case 17: _t->disconnectedFromServer(); break;
        case 18: _t->messageReceived((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 19: _t->jsonReceived((*reinterpret_cast< std::add_pointer_t<QJsonObject>>(_a[1]))); break;
        case 20: _t->userJoined((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 21: _t->userLeft((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 22: _t->userListReceived((*reinterpret_cast< std::add_pointer_t<QStringList>>(_a[1]))); break;
        case 23: _t->displayPrivateMessage((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[4]))); break;
        case 24: _t->onNetworkConnected(); break;
        case 25: _t->onNetworkDisconnected(); break;
        case 26: _t->onNetworkError((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 27: _t->onNetworkMessageReceived((*reinterpret_cast< std::add_pointer_t<QJsonObject>>(_a[1]))); break;
        case 28: _t->onReconnectionAttempt((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 29: _t->loadLocalData(); break;
        case 30: _t->saveMessageToLocal((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[4]))); break;
        case 31: _t->loadChatHistory((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 32: _t->updateConnectionStatus(); break;
        case 33: _t->updateContactList(); break;
        case 34: _t->updateGroupList(); break;
        case 35: _t->syncPrivateChatUserList(); break;
        default: ;
        }
    }
}

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10MainWindowE_t>.strings))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 36)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 36;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 36)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 36;
    }
    return _id;
}
QT_WARNING_POP
