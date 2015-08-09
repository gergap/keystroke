#ifndef MYTCPSERVER_H_K2HPZQGD
#define MYTCPSERVER_H_K2HPZQGD

#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>
#include <QDebug>

class MyTcpServer : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool enabled READ enabled WRITE setEnabled NOTIFY enabledChanged)
public:
    explicit MyTcpServer(QObject *parent = 0);

    void setEnabled(bool enabled);
    bool enabled() const;

signals:
    void enabledChanged(bool);

public slots:
    void newConnection();

private:
    QTcpServer *server;
    bool m_enabled;
};

#endif /* end of include guard: MYTCPSERVER_H_K2HPZQGD */

