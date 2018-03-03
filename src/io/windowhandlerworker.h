#ifndef WINDOWHANDLERWORKER_H
#define WINDOWHANDLERWORKER_H

#include <QObject>
#include "windowhandler.h"

class WindowHandlerWorker : public QObject
{
    Q_OBJECT
public:
    WindowHandlerWorker(WindowHandler *w, int x, int y, QObject *parent = nullptr);

signals:
    void pixelScanned(QPixmap);
    void finished();

public slots:
    void process();
    void stop();

private:
    bool run = true;
    int x;
    int y;
    WindowHandler *w = 0;
};

#endif // WINDOWHANDLERWORKER_H
