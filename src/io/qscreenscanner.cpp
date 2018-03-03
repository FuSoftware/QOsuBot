#include "qscreenscanner.h"

QScreenScanner::QScreenScanner(WindowHandler *handler, int x, int y, QObject *parent) : QObject(parent)
{
    this->handler = handler;
    this->x = x;
    this->y = y;

    this->mode = ScanMode::PIXEL;
}

QScreenScanner::QScreenScanner(WindowHandler *handler, int x, int y, int w, int h, QObject *parent) : QObject(parent)
{
    this->handler = handler;
    this->x = x;
    this->y = y;
    this->h = h;
    this->w = w;

    this->mode = ScanMode::AREA;
}

QScreenScanner::QScreenScanner(WindowHandler *handler, int x, int y, QObject *parent) : QObject(parent)
{
    this->handler = handler;
    this->x = x;
    this->y = y;

    this->mode = ScanMode::WINDOW;
}

void QScreenScanner::process()
{
    while(run)
    {
        QPixmap p;

        switch (this->mode) {
        case ScanMode::AREA:
            p = w->getArea(this->x,this->y, this->w, this->h);
            break;
        case ScanMode::PIXEL:
            p = w->getPixel(this->x,this->y);
            break;
        case ScanMode::WINDOW:
            p = w->getWindow();
            break;
        default:
            break;
        }
        emit scanned(p);
        QThread::msleep(1); //Used to ease off the CPU
    }

    emit finished();
}

void QScreenScanner::stop()
{
    this->run = false;
}
