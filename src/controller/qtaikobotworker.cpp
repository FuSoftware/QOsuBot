#include "qtaikobotworker.h"

QTaikoBotWorker::QTaikoBotWorker(WindowHandler *handler, int x, int y, int stateCheck, QObject *parent) : QObject(parent)
{
    this->s = new QScreenScanner(handler, x, y);
    this->stateCheck = stateCheck;
    setProcessFunc(pixelValidator);
}

QTaikoBotWorker::QTaikoBotWorker(WindowHandler *handler, int x, int y, int w, int h, int stateCheck, QObject *parent) : QObject(parent)
{
    this->s = new QScreenScanner(handler, x, y, w, h);
    this->stateCheck = stateCheck;
}

void QTaikoBotWorker::setProcessFunc(FValidator v)
{
    this->v = v;
}

QPixmap QTaikoBotWorker::getLastPixmap()
{
    return this->p;
}

void QTaikoBotWorker::start()
{
    QThread *t = new QThread(this);
    s->moveToThread(t);

    connect(t, SIGNAL(started()),  s, SLOT(process()));
    connect(s, SIGNAL(finished()), t, SLOT(quit()));
    connect(s, SIGNAL(finished()), s, SLOT(deleteLater()));
    connect(t, SIGNAL(finished()), t, SLOT(deleteLater()));

    connect(s,SIGNAL(scanned(QPixmap)),this,SLOT(process(QPixmap)));

    t->start();
}

void QTaikoBotWorker::stop()
{
    s->stop();
}

int QTaikoBotWorker::getStateCheck()
{
    return this->stateCheck;
}

bool QTaikoBotWorker::hasStateCheck(int state)
{
    return this->getStateCheck() & state;
}

void QTaikoBotWorker::process(QPixmap p)
{
    this->p = p;
    int state = this->v(this->p, this);
    emit validated(state,this);
}

bool QTaikoBotWorker::isRed(qreal r, qreal g, qreal b)
{
    return (r > 0.5 && r > b);
}

bool QTaikoBotWorker::isBlue(qreal r, qreal g, qreal b)
{
    return (b > 0.5 && b > r);
}

int QTaikoBotWorker::screenValidator(QPixmap p)
{
    int result = 0;
    return result;
}

int QTaikoBotWorker::pixelValidator(QPixmap p, QTaikoBotWorker *worker)
{
    int result = 0;

    qreal r,g,b;
    QColor(p.toImage().pixel(0,0)).getRgbF(&r,&g,&b);

    //If Red
    if(worker->hasStateCheck(QTaiko::RED))
        if(isRed(r,g,b))
            result += QTaiko::RED;

    //If Blue
    if(worker->hasStateCheck(QTaiko::BLUE))
        if(isBlue(r,g,b))
            result += QTaiko::BLUE;

    //If Running
    if(worker->hasStateCheck(QTaiko::RUNNING))
        if(r > 0.95 && g > 0.95 && b > 0.95)
            result += QTaiko::RUNNING;

    //If Spinner
    if(worker->hasStateCheck(QTaiko::SPINNER))
    {

    }

    //If Slider
    if(worker->hasStateCheck(QTaiko::SLIDER))
    {

    }


    return result;
}
