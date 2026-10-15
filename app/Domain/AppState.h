//
// Created by Piotr Suwara on 15/10/2026.
//

#ifndef BLE_HEART_RATE_DEMO_APPSTATE_H
#define BLE_HEART_RATE_DEMO_APPSTATE_H

// TODO: Move this to services
struct Device {

};

struct AppState {
    QList<Device> devices;
    bool scanning = false;
};



#endif //BLE_HEART_RATE_DEMO_APPSTATE_H
