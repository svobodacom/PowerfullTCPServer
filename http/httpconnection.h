#ifndef HTTPCONNECTION_H
#define HTTPCONNECTION_H

#include <QObject>
#include <QFile>
#include <QFileInfo>
#include <QUrl>
#include <QMap>
#include <QStringList>
#include <QCoreApplication>
#include "tcpconnection.h"



class HttpConnection : public TcpConnection
{
public:
    explicit HttpConnection(QObject *parent = 0);
    ~HttpConnection();

    QString root();
    void setRoot(QString path);
    int rate();
    void setRate(int value);

protected:
    QFile *m_file;
    QString m_root;
    int m_rate;

    QMap<QString, QString> m_request;
    QMap<QString, QString> m_response;
    QMap<QString, QString> m_mime;
    // To Do - make a rate controller!

    void processGet(QByteArray data);
    void handleRequest();
    void sendFile(QString file);
    QString getMimeType(QString path);

public slots:
    virtual void connected();
    virtual void disconnected();
    virtual void readyRead();
    virtual void bytesWritten(qint64 bytes);
    virtual void stateChanged(QAbstractSocket::SocketState socketState);
    virtual void error(QAbstractSocket::SocketError socketError);

    void started();
    void transfered(int bytes);
    void finished();
    void transferError();
};

#endif // HTTPCONNECTION_H
