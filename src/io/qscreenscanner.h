#ifndef WINDOWHANDLERWORKER_H
#define WINDOWHANDLERWORKER_H

#include <QObject>
#include <QSharedPointer>

#include "windowhandler.h"

enum ScreenScanMode{
    PIXEL = 0,
    AREA,
    WINDOW
};

class QScreenScanner : public QObject
{
    Q_OBJECT
public:
    QScreenScanner(WindowHandler *handler, QObject *parent = nullptr);
    QScreenScanner(WindowHandler *handler, int x, int y, QObject *parent = nullptr);
    QScreenScanner(WindowHandler *handler, int x, int y, int w, int h, QObject *parent = nullptr);

signals:
    void scanned(QPixmap p);
    void finished();

public slots:
    void process();
    void stop();

private:
    int mode = 0;

    bool run = true;
    int x;
    int y;
    int h;
    int w;

    WindowHandler *handler = 0;
};

#endif // WINDOWHANDLERWORKER_H
