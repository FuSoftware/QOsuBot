#include "widget.h"

Widget::Widget(QWidget *parent): QWidget(parent)
{
    QVBoxLayout *l = new QVBoxLayout(this);
    le = new QLineEdit(this);
    label = new QLabel("Placeholder",this);
    labelTime = new QLabel(this);
    le->setValidator(new QIntValidator(0,100000,this));

    l->addWidget(le);
    l->addWidget(labelTime);
    l->addWidget(label);

    w = new WindowHandler("osu.exe");

    connect(le,SIGNAL(returnPressed()),this,SLOT(setPid()));

    QTimer *t = new QTimer(this);
    t->setInterval(50);
    connect(t,SIGNAL(timeout()),this,SLOT(refreshScreen()));
    t->start();

}

Widget::~Widget()
{

}

void Widget::setPid()
{
    w->setPid(le->text().toLong());
}

void Widget::refreshScreen()
{
    QTime t;
    t.start();
    QPixmap p = w->getProcessScreen();
    labelTime->setText(QString::number(t.elapsed()) + QString("ms"));
    label->setPixmap(p.scaled(600,600,Qt::KeepAspectRatio));
}
