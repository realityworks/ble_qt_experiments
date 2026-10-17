//
// Created by Piotr Suwara on 15/10/2026.
//

#ifndef BLE_HEART_RATE_DEMO_APPSTATE_H
#define BLE_HEART_RATE_DEMO_APPSTATE_H

#include "../Service/HeartRateDevice.h"
#include <QList>
#include <QUuid>
#include <memory>

struct AppState {
    QList<HeartRateDevice> devices;
    std::optional<QUuid> connectedDevice;

    int connectedDeviceBpm = 0;
    ConnectionState connectionState = ConnectionState::Disconnected;
    QString connectedDeviceName = "";
    bool scanning = false;
};

using AppStatePtr = std::shared_ptr<const AppState>;
Q_DECLARE_METATYPE(AppStatePtr);

#endif //BLE_HEART_RATE_DEMO_APPSTATE_H
