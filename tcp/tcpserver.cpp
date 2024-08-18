#include "tcpserver.h"

TcpServer::TcpServer(QObject *parent)
    : QTcpServer(parent)
{
    qDebug() << this << "created";
}

TcpServer::~TcpServer()
{
    qDebug() << this << "destroyed";
}



bool TcpServer::listen(const QHostAddress &address, quint16 port)
{
    if (!QTcpServer::listen(address, port)) return false;

    m_thread = new QThread(this);
    m_connections = new TcpConnections();

    connect(m_thread, &QThread::started, m_connections, &TcpConnections::start, Qt::QueuedConnection);
    connect(this, &TcpServer::accepting, m_connections, &TcpConnections::accept, Qt::QueuedConnection);
    connect(this, &TcpServer::finished, m_connections, &TcpConnections::quit, Qt::QueuedConnection);
    connect(m_connections, &TcpConnections::finished, this, &TcpServer::complete, Qt::QueuedConnection);

    m_connections->moveToThread(m_thread);
    m_thread->start();
}



void TcpServer::close()
{

}



qint64 TcpServer::port()
{

}



void TcpServer::incomingConnection(qintptr descriptor)
{

}



void TcpServer::accept(qintptr descriptor, TcpConnection *connection)
{

}



void TcpServer::complete()
{

}
