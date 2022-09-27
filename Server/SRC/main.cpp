#include "mainwindow.h"

#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
//    QTextCodec codecText = QTextCodec::codecForName("UTF-8");
// //   QTextCodec *codecText = Qt::codecForHtml(data);
//    QTextCodec::setCodecForLocale(codecText);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
