#include <QApplication>
#include "HomePage.h"



int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    HomePage homePage;
    homePage.setWindowTitle("Home Page - Employee Management System");
    homePage.resize(1280, 720);
    homePage.show();

    return app.exec();
}
