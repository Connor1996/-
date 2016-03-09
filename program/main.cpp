#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Travel Query System");
    w.setFixedSize(1280, 720);
    w.show();
	//show the window 
    return a.exec();
}
