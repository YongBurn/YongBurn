#include "contactmodel.h"
#include <QDebug>

ContactModel::ContactModel(QObject *parent)
    : QAbstractListModel(parent)
    , m_isFiltered(false)
{
}

int ContactModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_isFiltered ? m_filteredContacts.count() : m_contacts.count();
}

QVariant ContactModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= rowCount())
        return QVariant();

    const Contact &contact = m_isFiltered ? m_filteredContacts.at(index.row()) : m_contacts.at(index.row());

    switch (role) {
    case NameRole:
        return contact.name;
    case NicknameRole:
        return contact.nickname;
    case GroupRole:
        return contact.group;
    case IsOnlineRole:
        return contact.isOnline;
    case UnreadCountRole:
        return contact.unreadCount;
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> ContactModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[NicknameRole] = "nickname";
    roles[GroupRole] = "group";
    roles[IsOnlineRole] = "isOnline";
    roles[UnreadCountRole] = "unreadCount";
    return roles;
}

void ContactModel::addContact(const Contact &contact)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_contacts.append(contact);
    if (m_isFiltered && (m_currentFilter.isEmpty() || contact.group == m_currentFilter)) {
        m_filteredContacts.append(contact);
    }
    endInsertRows();
}

void ContactModel::removeContact(const QString &name)
{
    int index = findContactIndex(name);
    if (index == -1) return;

    beginRemoveRows(QModelIndex(), index, index);
    m_contacts.removeAt(index);
    
    // 同时从筛选列表中移除
    for (int i = 0; i < m_filteredContacts.count(); ++i) {
        if (m_filteredContacts[i].name == name) {
            m_filteredContacts.removeAt(i);
            break;
        }
    }
    endRemoveRows();
}

void ContactModel::updateContact(const QString &name, const Contact &contact)
{
    int index = findContactIndex(name);
    if (index == -1) return;

    m_contacts[index] = contact;

    // 更新筛选列表
    if (m_isFiltered) {
        for (int i = 0; i < m_filteredContacts.count(); ++i) {
            if (m_filteredContacts[i].name == name) {
                if (m_currentFilter.isEmpty() || contact.group == m_currentFilter) {
                    m_filteredContacts[i] = contact;
                } else {
                    // 如果更新后不符合筛选条件，则移除
                    beginRemoveRows(QModelIndex(), i, i);
                    m_filteredContacts.removeAt(i);
                    endRemoveRows();
                }
                break;
            }
        }
    }

    emit dataChanged(createIndex(index, 0), createIndex(index, 0));
}

Contact ContactModel::getContact(const QString &name) const
{
    int index = findContactIndex(name);
    if (index != -1) {
        return m_contacts.at(index);
    }
    return Contact();
}

void ContactModel::setContacts(const QList<Contact> &contacts)
{
    beginResetModel();
    m_contacts = contacts;
    if (m_isFiltered) {
        m_filteredContacts.clear();
        for (const Contact &contact : contacts) {
            if (m_currentFilter.isEmpty() || contact.group == m_currentFilter) {
                m_filteredContacts.append(contact);
            }
        }
    }
    endResetModel();
}

void ContactModel::clearContacts()
{
    beginResetModel();
    m_contacts.clear();
    m_filteredContacts.clear();
    endResetModel();
}

void ContactModel::filterByGroup(const QString &groupName)
{
    beginResetModel();
    m_currentFilter = groupName;
    m_isFiltered = true;
    m_filteredContacts.clear();

    for (const Contact &contact : m_contacts) {
        if (groupName.isEmpty() || contact.group == groupName) {
            m_filteredContacts.append(contact);
        }
    }
    endResetModel();
}

void ContactModel::showAllContacts()
{
    beginResetModel();
    m_isFiltered = false;
    m_currentFilter.clear();
    endResetModel();
}

QStringList ContactModel::getGroups() const
{
    QStringList groups;
    for (const Contact &contact : m_contacts) {
        if (!groups.contains(contact.group)) {
            groups.append(contact.group);
        }
    }
    groups.sort();
    return groups;
}

void ContactModel::setContactOnline(const QString &name, bool online)
{
    int index = findContactIndex(name);
    if (index == -1) return;

    m_contacts[index].isOnline = online;

    // 更新筛选列表
    if (m_isFiltered) {
        for (int i = 0; i < m_filteredContacts.count(); ++i) {
            if (m_filteredContacts[i].name == name) {
                m_filteredContacts[i].isOnline = online;
                emit dataChanged(createIndex(i, 0), createIndex(i, 0));
                break;
            }
        }
    }

    emit dataChanged(createIndex(index, 0), createIndex(index, 0));
}

void ContactModel::updateUnreadCount(const QString &name, int count)
{
    int index = findContactIndex(name);
    if (index == -1) return;

    m_contacts[index].unreadCount = count;

    // 更新筛选列表
    if (m_isFiltered) {
        for (int i = 0; i < m_filteredContacts.count(); ++i) {
            if (m_filteredContacts[i].name == name) {
                m_filteredContacts[i].unreadCount = count;
                emit dataChanged(createIndex(i, 0), createIndex(i, 0));
                break;
            }
        }
    }

    emit dataChanged(createIndex(index, 0), createIndex(index, 0));
}

int ContactModel::findContactIndex(const QString &name) const
{
    for (int i = 0; i < m_contacts.count(); ++i) {
        if (m_contacts[i].name == name) {
            return i;
        }
    }
    return -1;
}