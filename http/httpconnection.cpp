#include "httpconnection.h"


HttpConnection::HttpConnection(QObject *parent) : TcpConnection(parent)
{
    m_mime.insert("txt", "text/plain");
    m_mime.insert("htm", "text/html");
    m_mime.insert("html", "text/html");
    m_mime.insert("js", "text/javascript");
    m_mime.insert("rtf", "text/rtf");
    m_mime.insert("jpg", "image/jpg");
}

HttpConnection::~HttpConnection() { }



QString HttpConnection::root()
{

}



void HttpConnection::setRoot(QString path)
{

}



int HttpConnection::rate()
{

}



void HttpConnection::setRate(int value)
{

}



void HttpConnection::processGet(QByteArray data)
{

}



void HttpConnection::handleRequest()
{

}



void HttpConnection::sendFile(QString file)
{

}



QString HttpConnection::getMimeType(QString path)
{

}



void HttpConnection::connected()
{

}

void HttpConnection::disconnected()
{

}

void HttpConnection::readyRead()
{

}



void HttpConnection::bytesWritten(qint64 bytes)
{

}

void HttpConnection::stateChanged(QAbstractSocket::SocketState socketState)
{

}

void HttpConnection::error(QAbstractSocket::SocketError socketError)
{

}

void HttpConnection::started()
{

}

void HttpConnection::transfered(int bytes)
{

}

void HttpConnection::finished()
{

}

void HttpConnection::transferError()
{

}
