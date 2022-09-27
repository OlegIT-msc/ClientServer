#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "../../CommonClient/clienttcp.h"
#include "../../CommonClient/service.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    qmlRegisterType<ClientTCP>("tcp", 1, 0, "ClientTCP");

    ClientTCP C_TCP;
    Service Serv;

    QQmlApplicationEngine engine;
    QQmlContext *context = engine.rootContext();

    /* We load the object into the context to establish the connection,
     * and also define the name "appCore" by which the connection will occur
     * */
    context->setContextProperty("C_TCP", &C_TCP);
    context->setContextProperty("Serv", &Serv);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
