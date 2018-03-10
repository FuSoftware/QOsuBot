#include "qscreenscanner.h"

QScreenScanner::QScreenScanner(WindowHandler *handler, int x, int y, QObject *parent) : QObject(parent)
{
    this->handler = handler;
    this->x = x;
    this->y = y;

    this->mode = ScreenScanMode::PIXEL;
}

QScreenScanner::QScreenScanner(WindowHandler *handler, int x, int y, int w, int h, QObject *parent) : QObject(parent)
{
    this->handler = handler;
    this->x = x;
    this->y = y;
    this->h = h;
    this->w = w;

    this->mode = ScreenScanMode::AREA;
}

QScreenScanner::QScreenScanner(WindowHandler *handler, QObject *parent) : QObject(parent)
{
    this->handler = handler;
    this->mode = ScreenScanMode::WINDOW;
}

void QScreenScanner::process()
{
    run = true;

    while(run)
    {
        if(this->handler->handleLoaded())
        {
            QPixmap p;

            switch (this->mode) {
            case ScreenScanMode::AREA:
                p = this->handler->getArea(this->x,this->y, this->w, this->h);
                break;
            case ScreenScanMode::PIXEL:
                p = this->handler->getPixel(this->x,this->y);
                break;
            case ScreenScanMode::WINDOW:
                p = this->handler->getWindow();
                break;
            default:
                break;
            }

            if(!p.isNull())
                emit scanned(p);
        }

        QThread::msleep(1); //Used to ease off the CPU
    }

    emit finished();
}

void QScreenScanner::stop()
{
    this->run = false;
}
