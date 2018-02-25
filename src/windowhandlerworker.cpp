#include "windowhandlerworker.h"

WindowHandlerWorker::WindowHandlerWorker(WindowHandler *w, int x, int y, QObject *parent) : QObject(parent)
{
    this->w = w;
    this->x = x;
    this->y = y;
}

void WindowHandlerWorker::process()
{
    while(run)
    {
        QPixmap p = w->getPixel(this->x,this->y);
        emit pixelScanned(p);
        QThread::msleep(1);
    }

    emit finished();
}

void WindowHandlerWorker::stop()
{
    this->run = false;
}
