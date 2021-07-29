/* Program author
* Name: Khoa Pham Dinh
* Student number: 050359620
* UserID: gmkhph
* E-Mail: khoa.phamdinh@tuni.fi
*
*
*/
#include "mainwindow.hh"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
