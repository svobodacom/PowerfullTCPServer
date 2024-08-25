#include "ratetransfer.h"

RateTransfer::RateTransfer(QObject *parent) : QObject{parent}
{
    setDefaults();
}

RateTransfer::~RateTransfer()
{

}



int RateTransfer::rate()
{

}



void RateTransfer::setRate(int value)
{

}



qint64 RateTransfer::maximum()
{
    return m_maximum;
}



void RateTransfer::setMaximum(qint64 value)
{

}



QIODevice *RateTransfer::source()
{

}



void RateTransfer::setSource(QIODevice *device)
{

}



QIODevice *RateTransfer::destination()
{

}



void RateTransfer::setDestination(QIODevice *device)
{

}



bool RateTransfer::isTransfering()
{

}



QString RateTransfer::errorString()
{

}



void RateTransfer::setDefaults()
{

}



bool RateTransfer::checkDevices()
{

}



bool RateTransfer::checkTransfer()
{

}



void RateTransfer::scheduleTransfer()
{

}



void RateTransfer::start()
{

}



void RateTransfer::stop()
{

}



void RateTransfer::transfer()
{

}



void RateTransfer::readyRead()
{

}



void RateTransfer::bytesWritten(qint64 bytes)
{

}



