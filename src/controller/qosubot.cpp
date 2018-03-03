#include "qosubot.h"

QOsuBot::QOsuBot(long pid, QObject *parent) : QObject(parent)
{
    w = new WindowHandler(pid,this);
    s = new KeySender(this);
}

void QOsuBot::setup(QVector<Coord> coords)
{

}

void QOsuBot::setCoords(QVector<Coord> coords)
{
    this->coords = coords;
}

QColor QOsuBot::getPixel(int x, int y, int id)
{
    QPixmap p = w->getPixel(x,y);
    emit pixelRead(id,p);
    return QColor(p.toImage().pixel(0,0));
}

void QOsuBot::hardRun()
{
    qreal r,g,b;
    QTime t;

    int i_r = 0;
    int i_b = 0;

    this->scan_time.clear();
    this->process_time.clear();

    this->scan_time.resize(20);
    this->process_time.resize(20);

    QVector<int> r_keys = {0x44, 0x4C};
    QVector<int> b_keys = {0x53, 0x4D};

    qDebug() << r_keys.size() << b_keys.size();

    connect(this,SIGNAL(press(int,int,int)),s,SLOT(sendKey(int,int,int)));

    while(true)
    {
        bool runState;

        //Monitoring
        t.restart();

        //State
        getPixel(1670, 87, 0).getRgbF(&r,&g,&b);

        if(r > 0.95 && g > 0.95 && b > 0.95)
        {
            runState = true;
            //Color Scan
            getPixel(390, 412, 1).getRgbF(&r,&g,&b);

            //Monitoring
            this->scan_time.pop_front();
            this->scan_time.push_back(t.elapsed());
            t.restart();

            if(isBlue(r,b,g))
            {
                if(!s->isPressed(b_keys[i_b]))
                {
                    emit press(b_keys[i_b], 20, 20);
                    i_b++;
                    if(i_b >= b_keys.size())
                        i_b = 0;
                }
            }
            else if(isRed(r,b,g))
            {
                if(!s->isPressed(r_keys[i_r]))
                {
                    emit press(r_keys[i_r], 20, 20);
                    i_r++;
                    if(i_r >= r_keys.size())
                        i_r = 0;
                }
            }

            //Monitoring
            this->process_time.pop_front();
            this->process_time.push_back(t.elapsed());
        }
        else
        {
            runState = false;
        }

        if(runState != isRunning)
        {
            emit running(runState);
            isRunning = runState;
        }

        emit scanTime(getMeanScan());
        emit processTime(getMeanProcess());

        if(t.elapsed() > 10)
            QThread::msleep(10);
        QThread::msleep(20);
    }
}

int QOsuBot::getMeanScan()
{
    int t = 0;

    for(int i=0;i<this->scan_time.size();i++)
        t += this->scan_time[i];

    return t / this->scan_time.size();
}

int QOsuBot::getMeanProcess()
{
    int t = 0;

    for(int i=0;i<this->process_time.size();i++)
        t += this->process_time[i];

    return t / this->process_time.size();
}

bool QOsuBot::isRed(qreal r, qreal b, qreal g)
{
    return (r > 0.5 && r > b);
}

bool QOsuBot::isBlue(qreal r, qreal b, qreal g)
{
    return (b > 0.5 && b > r);
}

void QOsuBot::run()
{
    QPixmap p;
    QRgb c;
    qreal r,g,b;
    QTime t;

    while(true)
    {
        t.restart();
        for(int i=0;i<this->coords.size();i++)
        {
            p = w->getPixel(this->coords[i].x,this->coords[i].y);
            c = p.toImage().pixel(0,0);

            QColor(c).getRgbF(&r,&g,&b);
            emit pixelRead(i,p);

            if(r > 0.5 && b < 0.5)
            {

            }
            else if(r < 0.5 && b > 0.5)
            {

            }
        }
        emit scanTime(t.elapsed());
        QThread::msleep(10);
    }
}
