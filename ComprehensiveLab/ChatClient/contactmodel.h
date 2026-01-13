#ifndef CONTACTMODEL_H
#define CONTACTMODEL_H

#include <QAbstractListModel>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

struct Contact {
    QString name;
    QString nickname;
    QString group;
    bool isOnline;
    int unreadCount;
    QJsonObject toJson() const {
        QJsonObject obj;
        obj["name"] = name;
        obj["nickname"] = nickname;
        obj["group"] = group;
        obj["isOnline"] = isOnline;
        obj["unreadCount"] = unreadCount;
        return obj;
    }
    static Contact fromJson(const QJsonObject &obj) {
        Contact contact;
        contact.name = obj["name"].toString();
        contact.nickname = obj["nickname"].toString();
        contact.group = obj["group"].toString();
        contact.isOnline = obj["isOnline"].toBool();
        contact.unreadCount = obj["unreadCount"].toInt();
        return contact;
    }
};

class ContactModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum ContactRoles {
        NameRole = Qt::UserRole + 1,
        NicknameRole,
        GroupRole,
        IsOnlineRole,
        UnreadCountRole
    };

    explicit ContactModel(QObject *parent = nullptr);

    // QAbstractListModel interface
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    // 自定义方法
    void addContact(const Contact &contact);
    void removeContact(const QString &name);
    void updateContact(const QString &name, const Contact &contact);
    Contact getContact(const QString &name) const;
    void setContacts(const QList<Contact> &contacts);
    void clearContacts();

    // 分组筛选
    void filterByGroup(const QString &groupName);
    void showAllContacts();
    QStringList getGroups() const;

    // 在线状态
    void setContactOnline(const QString &name, bool online);
    void updateUnreadCount(const QString &name, int count);

private:
    QList<Contact> m_contacts;
    QList<Contact> m_filteredContacts;
    QString m_currentFilter;
    bool m_isFiltered;

    int findContactIndex(const QString &name) const;
};

#endif // CONTACTMODEL_H