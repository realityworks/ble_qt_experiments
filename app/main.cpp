#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "Domain/GlobalDataStore.h"
#include "Domain/AppState.h"
#include "Service/IDeviceService.h"
#include "Service/HeartRateDevice.h"
#include "Service/BLE/BleDeviceService.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);






    QQmlApplicationEngine engine;
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
                     &app, []() { QCoreApplication::exit(-1); },
                     Qt::QueuedConnection);
    engine.loadFromModule("bleheartratedemo", "Main");

    return app.exec();
}
