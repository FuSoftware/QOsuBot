#include "qosubotwidget.h"

QOsuBotWidget::QOsuBotWidget(QVector<Coord> coordinates, QWidget *parent) : QWidget(parent)
{
    this->bot = new QOsuBot(328);
    scan = new QLabel("Time", this);
    running = new QLabel("Run State", this);
    QPushButton *pb = new QPushButton("Start",this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(running);
    layout->addWidget(scan);
    layout->addWidget(pb);

    QHBoxLayout *pixelLayout = new QHBoxLayout;
    layout->addLayout(pixelLayout);

    for(int i=0;i<coordinates.size();i++)
    {
        QLabel *l = new QLabel(this);
        this->pixels.push_back(l);
        pixelLayout->addWidget(l);
    }

    this->coordinates = coordinates;

    connect(pb,SIGNAL(clicked(bool)),this,SLOT(start()));

    connect(bot,SIGNAL(scanTime(long)),this,SLOT(onScan(long)));
    connect(bot,SIGNAL(pixelRead(int,QPixmap)),this,SLOT(onPixel(int,QPixmap)));
    connect(bot,SIGNAL(running(bool)),this,SLOT(onRunning(bool)));
}

void QOsuBotWidget::onScan(long elapsed)
{
    this->scan->setText(QString::number(elapsed) + QString("ms"));
}

void QOsuBotWidget::onRunning(bool running)
{
    if(running)
        this->running->setText("Running");
    else
        this->running->setText("Not Running");

}

void QOsuBotWidget::onPixel(int id, QPixmap value)
{
    this->pixels[id]->setPixmap(value.scaled(50,50));
}

void QOsuBotWidget::start()
{
    QThread *t = new QThread(this);
    this->bot->setCoords(this->coordinates);
    this->bot->moveToThread(t);

    //Thread Management
    connect(t, SIGNAL(started()),  this->bot, SLOT(hardRun()));
    connect(this->bot, SIGNAL(finished()), t, SLOT(quit()));
    connect(this->bot, SIGNAL(finished()), this->bot, SLOT(deleteLater()));
    connect(t, SIGNAL(finished()), t, SLOT(deleteLater()));

    t->start();

}
