#ifndef SERVERWORKER_H
#define SERVERWORKER_H

#include <QObject>
#include <QTcpSocket>
#include <QJsonObject>

class ServerWorker : public QObject
{
    Q_OBJECT
public:
    explicit ServerWorker(QObject *parent = nullptr);
    bool setSocketDescriptor(qintptr socketDescriptor);
    QString userName() const { return m_userName; }
    void setUserName(const QString &name) { m_userName = name; }
    void sendJson(const QJsonObject &json); // 补充sendJson声明

signals:
    void logMessage(const QString &msg);
    void jsonReceived(ServerWorker *sender, const QJsonObject &docObj);
    void disconnectedFromClient();

private slots:
    void onReadyRead();
    void onDisconnected();

private:
    QTcpSocket *m_socket = nullptr;
    QString m_userName;
    QByteArray m_buffer;
};

#endif // SERVERWORKER_H
