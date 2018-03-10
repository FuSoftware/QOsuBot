#ifndef QTAIKOBOTASYNC_H
#define QTAIKOBOTASYNC_H

#include <QObject>

class QTaikoBotAsync : public QObject
{
    Q_OBJECT
public:
    explicit QTaikoBotAsync(QObject *parent = nullptr);

signals:

public slots:
};

#endif // QTAIKOBOTASYNC_H