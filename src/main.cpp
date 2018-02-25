#include "widget.h"
#include <QApplication>
#include "qosubotwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QVector<Coord> coordinates;
    coordinates.push_back(Coord(390,412,48));
    coordinates.push_back(Coord(380,412,49));

    QOsuBotWidget w(coordinates);
    w.show();

    return a.exec();
}
