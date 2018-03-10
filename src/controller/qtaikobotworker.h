#ifndef QOSUBOTASYNC_H
#define QOSUBOTASYNC_H

#include <QObject>

class QOsuBotAsync : public QObject
{
    Q_OBJECT
public:
    explicit QOsuBotAsync(QObject *parent = nullptr);

signals:

public slots:
};

#endif // QOSUBOTASYNC_H