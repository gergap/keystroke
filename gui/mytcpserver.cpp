#include "mytcpserver.h"

MyTcpServer::MyTcpServer(QObject *parent) : QObject(parent)
{
    server = new QTcpServer(this);

    connect(server, SIGNAL(newConnection()), this, SLOT(newConnection()));

    if(!server->listen(QHostAddress::Any, 9999))
    {
        qDebug() << "Server could not start";
    }
    else
    {
        qDebug() << "Server started!";
    }

    m_enabled = true;
}


void MyTcpServer::newConnection()
{
    // need to grab the socket
    QTcpSocket *socket = server->nextPendingConnection();

    socket->write("Hello client\r\n");
    socket->flush();
    socket->waitForBytesWritten(3000);
    socket->waitForReadyRead(3000);
    QByteArray data = socket->readAll();
    QString command = QString::fromUtf8(data);

    if (command == "enable\n") {
        m_enabled = true;
        emit enabledChanged(m_enabled);
    } else if (command == "disable\n") {
        m_enabled = false;
        emit enabledChanged(m_enabled);
    }

    qDebug() << command;

    socket->close();
}

void MyTcpServer::setEnabled(bool enabled)
{
    if (enabled != m_enabled) {
        m_enabled = enabled;
        emit enabledChanged(m_enabled);
    }
}

bool MyTcpServer::enabled() const
{
    return m_enabled;
}

