#include "qtaikobotasync.h"

QTaikoBotAsync::QTaikoBotAsync(QString process, QObject *parent) : QTaikoBot(process, parent)
{
}

void QTaikoBotAsync::start()
{

    QTaikoBotWorker *wCheck = new QTaikoBotWorker(this->h, 1670, 87, QTaiko::RUNNING, this);
    QTaikoBotWorker *wColor = new QTaikoBotWorker(this->h, 390, 412, QTaiko::BLUE | QTaiko::RED, this);

    this->w.push_back(wCheck);
    this->w.push_back(wColor);

    connect(wCheck,SIGNAL(validated(int,QTaikoBotWorker*)),this,SLOT(processed(int,QTaikoBotWorker*)));
    connect(wColor,SIGNAL(validated(int,QTaikoBotWorker*)),this,SLOT(processed(int,QTaikoBotWorker*)));

    wCheck->start();
    wColor->start();
}

void QTaikoBotAsync::processed(int state, QTaikoBotWorker* sender)
{
    int id = this->w.indexOf(sender);

    emit pixelRead(id, sender->getLastPixmap());

    //If Running
    if(sender->hasStateCheck(QTaiko::Validate::RUNNING))
    {
        if(state & QTaiko::Validate::RUNNING)
        {
            this->isRunning = true;
            emit running(true);
        }
        else
        {
            this->isRunning = false;
            emit running(false);
        }
    }

    if(this->isRunning && compensation.timerId() == -1)
    {
        //If Red
        if(sender->hasStateCheck(QTaiko::Validate::RED))
        {
            if(state & QTaiko::Validate::RED)
            {
                if(!s->isPressed(r_keys[i_r]))
                {
                    emit press(r_keys[i_r], 20, 20);
                    i_r++;
                    if(i_r >= r_keys.size())
                        i_r = 0;
                }
            }
        }

        //If Blue
        if(sender->hasStateCheck(QTaiko::Validate::BLUE))
        {
            if(state & QTaiko::Validate::BLUE)
            {
                for(int i=0;i<b_keys.size();i++)
                {
                    if(!s->isPressed(b_keys[i_b]))
                    {
                        emit press(b_keys[i_b], 20, 20);
                        break;
                    }
                }
            }
        }

        /*
        //If Spinner
        if(sender->hasStateCheck(QTaiko::Validate::SPINNER))
        {

        }

        //If Slider
        if(sender->hasStateCheck(QTaiko::Validate::SLIDER))
        {

        }
        */
    }
}
