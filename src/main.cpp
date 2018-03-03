#include "widget.h"
#include <QApplication>
#include "ui/qosubotwidget.h"
#include "ai/neural/neuralnet.h"

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);


    QVector<Coord> coordinates;
    coordinates.push_back(Coord(390,412,48));
    coordinates.push_back(Coord(380,412,49));

    QOsuBotWidget w(coordinates);
    w.show();

    return a.exec();

    /*
    NeuralNet n(std::vector<int> {2,4,4,1});
    return 0;
    */

}
