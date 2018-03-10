#include "widget.h"
#include <QApplication>
#include "ui/QTaikoBotWidget.h"
#include "ai/neural/neuralnet.h"
#include "io/windowhandler.h"

#include <QSharedPointer>
#include <QPixmap>

#include "controller/qtaikobotworker.h"

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);


    QTaikoBotWidget w("osu!.exe");
    w.show();


    /*
    QTaikoBotWorker *wCheck = new QTaikoBotWorker(0, 1670, 87, QTaiko::RUNNING);
    QTaikoBotWorker *wColor = new QTaikoBotWorker(0, 390, 412, QTaiko::BLUE | QTaiko::RED);

    std::cout << wCheck->getStateCheck() << std::endl
              << wCheck->hasStateCheck(QTaiko::RED) << " "
              << wCheck->hasStateCheck(QTaiko::BLUE) << " "
              << wCheck->hasStateCheck(QTaiko::RUNNING) << std::endl;

    std::cout << wColor->getStateCheck() << std::endl
              << wColor->hasStateCheck(QTaiko::RED) << " "
              << wColor->hasStateCheck(QTaiko::BLUE) << " "
              << wColor->hasStateCheck(QTaiko::RUNNING) << std::endl;
    */

    return a.exec();

    /*
    NeuralNet n(std::vector<int> {2,4,4,1});
    return 0;
    */

}
