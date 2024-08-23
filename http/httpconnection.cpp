#include "httpconnection.h"


HttpConnection::HttpConnection(QObject *parent) : TcpConnection(parent)
{
    m_mime.insert("txt", "text/plain");
    m_mime.insert("htm", "text/html");
    m_mime.insert("html", "text/html");
    m_mime.insert("js", "text/javascript");
    m_mime.insert("rtf", "text/rtf");
    m_mime.insert("jpg", "image/jpg");
    m_mime.insert("jpeg", "image/jpeg");
    m_mime.insert("gif", "image/gif");
    m_mime.insert("png", "image/png");
    m_mime.insert("avi", "video/avi");
    m_mime.insert("mpg", "video/mpg");
    m_mime.insert("mpeg", "video/mpeg");
    m_mime.insert("mp4", "video/mp4");
    m_mime.insert("mkv", "video/x-matroska");
    m_mime.insert("qt", "video/quicktime");
    m_mime.insert("webm", "video/webm");
    m_mime.insert("wmv", "video/x-ms-wmv");
    m_mime.insert("flv", "video/x-flv");
    m_mime.insert("mp3", "audio/mp3");
    m_mime.insert("wav", "audio/wav");
    m_mime.insert("tar", "application/x-tar");
    m_mime.insert("zip", "application/zip");
    m_mime.insert("pdf", "application/pdf");
    m_mime.insert("xml", "text/xml");
}


HttpConnection::~HttpConnection()
{
    qDebug() << this << "Destroyed";
}



QString HttpConnection::root()
{
    return m_root;
}



void HttpConnection::setRoot(QString path)
{
    qDebug() << this << "Root set to: " << path;
    m_root = path;
}



int HttpConnection::rate()
{
    return m_rate;
}



void HttpConnection::setRate(int value)
{
    qDebug() << this << "Rate set to: " << value;
    m_rate = value;
}



void HttpConnection::processGet(QByteArray data)
{
    qDebug() << this << "Processing GET";

    QByteArray eoh;
    eoh.append("\r\n\r\n");

    QString header = m_request.value("svr_header","");
    header.append(data);
    m_request.insert("svr_header", header);

    if (header.contains(eoh))
    {
        // end of header found, parse the header
        QStringList lines = header.split("\r\n");
        for (int i = 0; i < lines.count(); i++)
        {
            QString line = lines.at(i);

            if (i == 0)
            {
                // first line has 3 values: METHOD PATH VERSION
                QStringList items = line.split(" ");
                if (items.count() >=1)
                    m_request.insert("http_method", items.at(0).trimmed());

                if (items.count() >=2)
                {
                    QString path = items.at(1).trimmed();
                    path = QUrl::fromPercentEncoding(path.toLatin1());
                    m_request.insert("http_path", path);
                }

                if (items.count() >=3)
                    m_request.insert("http_version", items.at(2).trimmed());
            }
            else
            {
                // all other lines are key value pairs
                if (!line.contains(":") && !line.isEmpty())
                {
                    qWarning() << this << "Skipping line due to missing ':' " << line;
                    continue;
                }
                int pos = line.indexOf(":");
                QString key = line.mid(0,pos);
                QString value = line.mid(pos +1);
                m_request.insert(key.trimmed(), value.trimmed());
            }
        }

        // attempt to handle the request
        handleRequest();
    }
}



void HttpConnection::handleRequest()
{
    qDebug() << this << "Handle the Request";

    QString file = m_request.value("http_path","");

    // strip out any directory jumps
    file = file.replace("..","");

    // /mydir/something/something + /test.jpg
    QString actualFile = m_root + file;
    QFileInfo fi(actualFile);
    QByteArray response;

    // if it is a directory, check for index.html
    if (fi.isDir())
    {
        qDebug() << this << "client is requesting a directory...";
        QString indexFile = actualFile + "index.html";
        QFileInfo fIndex(indexFile);

        if (fIndex.exists())
        {
            qDebug() << this << "setting / to /index.html";
            fi.setFile(indexFile);
        }
    }

    // send the file if it exists
    if (fi.exists() && fi.isFile())
    {
        // YES it exists
        QString mime = getMimeType(fi.fileName());
        qDebug() << this << "Sending file:" << fi.path();
        m_response.insert("code", "200");
        m_response.insert("path", fi.filePath());

        response.append("HTTP/1.1 200 OK\r\n");
        response.append(("Content-Type: " + mime + "\r\n").toLatin1());
        response.append(("Content-Length: " + QString::number(fi.size()) + "\r\n").toLatin1());
        response.append("Connection: close\r\n");
        response.append("\r\n");

    }
    else
    {
        // NO it does not exist
        response.append("HTTP/1.1 404 NOT FOUND\r\n");
        response.append("Connection: close\r\n");
        response.append("\r\n");
    }

    m_socket->write(response);
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
