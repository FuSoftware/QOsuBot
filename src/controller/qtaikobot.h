#ifndef QTAIKOBOT_H
#define QTAIKOBOT_H

#include <QObject>

class QTaikoBot : public QObject
{
    Q_OBJECT
public:
    explicit QTaikoBot(QObject *parent = nullptr);

signals:

public slots:
};

#endif // QTAIKOBOT_H