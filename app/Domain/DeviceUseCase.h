//
// Created by Piotr Suwara on 15/10/2026.
//

#ifndef BLE_HEART_RATE_DEMO_DEVICEUSECASE_H
#define BLE_HEART_RATE_DEMO_DEVICEUSECASE_H

#include <QObject>
#include "../Service/IDeviceService.h"
#include "GlobalDataStore.h"

class DeviceUseCase : public QObject {
    Q_OBJECT
public:
    using ServicePtr = std::shared_ptr<IDeviceService>;

    // Owning: hand over any IBleService (MockBleService, a QtBluetooth-backed one, ...).
    // `alert` replaces the default message box (handy for tests).
    DeviceUseCase(
        GlobalDataStore &store,
        ServicePtr ble,
        QObject *parent = nullptr
    ) : QObject(parent),
        m_store(store),
        m_ble(std::move(ble)) {
        Q_ASSERT_X(m_ble, "DeviceUseCase", "a BLE service is required");
    }

private:
    GlobalDataStore &m_store;
    ServicePtr m_ble;   // declared before m_subscriptions, so it is destroyed after them
};
#endif //BLE_HEART_RATE_DEMO_DEVICEUSECASE_H
