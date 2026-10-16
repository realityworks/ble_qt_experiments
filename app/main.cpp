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

#include "Presentation/DetailView/DetailView.h"
#include "Presentation/DetailView/DetailViewModel.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Global singletons
    GlobalDataStore store;
    std::shared_ptr<IDeviceService> deviceService = std::make_shared<MockDeviceService>();
    DeviceUseCase useCase(store, deviceService);

    // Setup the views
    ListViewModel listViewModel(useCase);
    std::unique_ptr<DetailViewModel> detailViewModel;

    QStackedWidget stack;
    auto *listView = new ListView(listViewModel);       // owned by the stack
    stack.addWidget(listView);

    // Connect the list to the detail view
    QObject::connect(
        &listViewModel,
        &ListViewModel::deviceSelected,
        &stack,
        [&](const QUuid &id) {
            detailViewModel = std::make_unique<DetailViewModel>(useCase, id);
            auto *detailView = new DetailView(*detailViewModel);

            stack.addWidget(detailView);
            stack.setCurrentWidget(detailView);

            // Move from detail back to list
            QObject::connect(
                detailView,
                &DetailView::backRequested,
                &stack,
                [&stack, &detailViewModel, listView, detailView] {
                    stack.setCurrentWidget(listView);
                    stack.removeWidget(detailView);
                    detailView->deleteLater();
                    detailViewModel.reset();
                }
            );

        }
    );

    stack.setWindowTitle(QObject::tr("BLE Heart Rate"));
    stack.resize(420, 520);
    stack.show();
    return app.exec();
}
