#include "mainwindow.h"

#include <QApplication>
#include <ctime>

int main(int argc, char *argv[])
{
    time_t now = time(0);
    tm* tm_now = localtime(&now);
    int thisYear = (tm_now->tm_year + 1900);

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);  // Enable high DPI scaling
    QGuiApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
