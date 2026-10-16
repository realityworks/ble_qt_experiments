#include <QApplication>
#include <QQmlContext>
#include <QQmlApplicationEngine>
#include "Domain/GlobalDataStore.h"
#include "Domain/AppState.h"
#include "Service/IDeviceService.h"
#include "Service/HeartRateDevice.h"
#include "Service/MOCK/MockDeviceService.h"
#include "Service/BLE/BleDeviceService.h"
#include "Domain/DeviceUseCase.h"
#include "Domain/GlobalDataStore.h"
#include "Presentation/ListView/ListViewModel.h"
#include "Presentation/ListView/ListView.h"
#include <QStackedWidget>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    GlobalDataStore store;
    std::shared_ptr<IDeviceService> deviceService = std::make_shared<MockDeviceService>();

    DeviceUseCase useCase(store, deviceService);
    ListViewModel listVm(useCase);

    QStackedWidget stack;
    auto *listView = new ListView(listVm);       // owned by the stack
    stack.addWidget(listView);

    stack.resize(420, 520);
    stack.show();
    return app.exec();
}
