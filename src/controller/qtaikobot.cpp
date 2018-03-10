#include "qtaikobot.h"

QTaikoBot::QTaikoBot(QString process, QObject *parent) : QObject(parent)
{
    this->s = new KeySender(this);
    this->h = new WindowHandler(process,this);

    this->r_keys = {0x44, 0x4C};
    this->b_keys = {0x53, 0x4D};

    connect(this,SIGNAL(press(int,int,int)),s,SLOT(sendKey(int,int,int)));
}

bool QTaikoBot::isRed(qreal r, qreal b, qreal g)
{
    return (r > 0.5 && r > b);
}

bool QTaikoBot::isBlue(qreal r, qreal b, qreal g)
{
    return (b > 0.5 && b > r);
}
