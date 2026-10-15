//
// Created by Piotr Suwara on 15/10/2026.
//

#ifndef BLE_HEART_RATE_DEMO_APPSTATE_H
#define BLE_HEART_RATE_DEMO_APPSTATE_H

#include "Service/HeartRateDevice.h"
#include <QList>

struct AppState {
    QList<HeartRateDevice> devices;
    HeartRateDevice* connectDevice;
    int connectedDeviceBpm = 0;


    bool scanning = false;
};



#endif //BLE_HEART_RATE_DEMO_APPSTATE_H
