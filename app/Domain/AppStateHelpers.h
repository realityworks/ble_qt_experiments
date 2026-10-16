//
// Created by Piotr Suwara on 16/10/2026.
//

#ifndef BLE_HEART_RATE_DEMO_APPSTATEHELPERS_H
#define BLE_HEART_RATE_DEMO_APPSTATEHELPERS_H

#include "AppState.h"
#include "../Service/HeartRateDevice.h"

inline const HeartRateDevice* findDevice(const AppState &state, const QUuid &id)
{
    for (const HeartRateDevice &device : state.devices)
        if (device.id == id) return &device;
    return nullptr;
}

inline HeartRateDevice* findDevice(AppState &state, const QUuid &id)
{
    for (HeartRateDevice &device : state.devices)
        if (device.id == id) return &device;
    return nullptr;
}

// Adds newly discovered devices; keeps readings/state of ones we already know.
inline void mergeDevices(AppState &state, const QList<HeartRateDevice> &found)
{
    for (const HeartRateDevice &device : found) {
        if (HeartRateDevice *existing = findDevice(state, device.id))
            existing->name = device.name;
        else
            state.devices.append(device);
    }
}

#endif //BLE_HEART_RATE_DEMO_APPSTATEHELPERS_H
