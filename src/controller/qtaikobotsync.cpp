#include "qtaikobotsync.h"

QTaikoBotSync::QTaikoBotSync(QString process, QObject *parent) : QTaikoBot(process, parent)
{

}

QColor QTaikoBotSync::getPixel(int x, int y, int id)
{
    QPixmap p = h->getPixel(x,y);
    emit pixelRead(id,p);
    return QColor(p.toImage().pixel(0,0));
}

void QTaikoBotSync::start()
{
    qreal r,g,b;
    QTime t;

    int i_r = 0;
    int i_b = 0;

    this->scan_time.clear();
    this->process_time.clear();

    this->scan_time.resize(20);
    this->process_time.resize(20);

    while(true)
    {
        bool runState;

        //Monitoring
        t.restart();

        //State
        getPixel(1670, 87, 0).getRgbF(&r,&g,&b);

        if(r > 0.95 && g > 0.95 && b > 0.95)
        {
            if(!runState) runState = true;
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

    emit finished();
}

int QTaikoBotSync::getMeanScan()
{
    int t = 0;

    for(int i=0;i<this->scan_time.size();i++)
        t += this->scan_time[i];

    return t / this->scan_time.size();
}

int QTaikoBotSync::getMeanProcess()
{
    int t = 0;

    for(int i=0;i<this->process_time.size();i++)
        t += this->process_time[i];

    return t / this->process_time.size();
}
