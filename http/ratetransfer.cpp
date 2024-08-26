#include "ratetransfer.h"

RateTransfer::RateTransfer(QObject *parent) : QObject{parent}
{
    qDebug() << this << "Created";
    setDefaults();
}

RateTransfer::~RateTransfer()
{
    qDebug() << this << "Destroyed";
}



int RateTransfer::rate()
{
    return m_rate;
}



void RateTransfer::setRate(int value)
{
    m_rate = value;
    qDebug() << this << "Rate set to " << value;
}



int RateTransfer::size()
{
    return m_size;
}



void RateTransfer::setSize(int size)
{
    m_size = size;
    qDebug() << this << "Size set to " << size;
}



qint64 RateTransfer::maximum()
{
    return m_maximum;
}



void RateTransfer::setMaximum(qint64 value)
{
    m_maximum = value;
    qDebug() << this << "Maximum set to " << value;
}



QIODevice *RateTransfer::source()
{
    return m_source;
}



void RateTransfer::setSource(QIODevice *device)
{
    m_source = device;
    qDebug() << this << "Source set to " << device;

    if (m_source->isSequential())
        connect(m_source, &QIODevice::readyRead, this,&RateTransfer::readyRead);
}



QIODevice *RateTransfer::destination()
{
    return m_destination;
}



void RateTransfer::setDestination(QIODevice *device)
{
    m_destination= device;
    qDebug() << this << "Destination set to " << device;

    if (m_destination->isSequential())
        connect(m_source, &QIODevice::bytesWritten, this,&RateTransfer::bytesWritten);
}



bool RateTransfer::isTransfering()
{
    return m_transfering;
}



QString RateTransfer::errorString()
{
    return m_error;
}



void RateTransfer::setDefaults()
{
    qDebug() << this << "Setting the defaults";
    m_rate = 0;
    m_size = 0;
    m_maximum = 0;
    m_transfering = false;
    m_transfered = 0;
    m_source = 0;
    m_destination = 0;
    m_error = "";
    m_scheduled = false;
    m_timer.setInterval(5);
}



bool RateTransfer::checkDevices()
{
    if (!m_source)
    {
        m_transfering = false;
        m_error = "No source device!";
        qDebug() << this << m_error;
        emit error();
        return false;
    }

    if (!m_destination)
    {
        m_transfering = false;
        m_error = "No destination device!";
        qDebug() << this << m_error;
        emit error();
        return false;
    }

    if (!m_source->isOpen() || !m_source->isReadable())
    {
        m_transfering = false;
        m_error = "Source device is not open or is not readable!";
        qDebug() << this << m_error;
        emit error();
        return false;
    }

    if (!m_destination->isOpen() || !m_destination->isWritable())
    {
        m_transfering = false;
        m_error = "Destination device is not open or is not writable!";
        qDebug() << this << m_error;
        emit error();
        return false;
    }

    return true;
}



bool RateTransfer::checkTransfer()
{
    if (!m_transfering)
    {
        m_error = "Not transfering, aborting!";
        qDebug() << this << m_error;
        emit error();
        return false;
    }

    if (m_transfered >= m_rate)
    {
        m_error = "Rate exeeded, not allowed to transfer!";
        qDebug() << this << m_error;
        emit error();
        return false;
    }

    return true;
}



void RateTransfer::scheduleTransfer()
{

}



void RateTransfer::start()
{
    qDebug() << this << "Start called";

    if(m_transfering)
    {
        qDebug() << this << "Already Transfering!";
        return;
    }

    m_error = "";
    m_transfering = true;
    m_transfered = 0;
    emit started();

    if (!m_source->isSequential() && m_source->bytesAvailable() >0)
    {
        qDebug() << this << "Starting transfer by calling scheduleTransfer";
        scheduleTransfer();
    }
}



void RateTransfer::stop()
{
    qDebug() << this << "Stopping the transfer";
    m_timer.stop();
    m_transfering = false;

}



void RateTransfer::transfer()
{

}



void RateTransfer::readyRead()
{
    qDebug() << this << "readyRead() signaled";
    scheduleTransfer();
}



void RateTransfer::bytesWritten(qint64 bytes)
{
    qDebug() << this << "bytesWritten() signaled";
    scheduleTransfer();
}



