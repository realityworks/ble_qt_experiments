//
// Created by Piotr Suwara on 15/10/2026.
//

#ifndef BLE_HEART_RATE_DEMO_HEARTRATEDEVICE_H
#define BLE_HEART_RATE_DEMO_HEARTRATEDEVICE_H

#include <QUuid>
#include <QString>
#include "ConnectionState.h"

struct HeartRateDevice {
    QUuid id;                   // Device UUID
    QString name = QString("");                 // Device name
    int bpm = 0;
    int batteryLevel = 0;
    ConnectionState state = ConnectionState::Disconnected;
    bool operator==(const HeartRateDevice &) const = default;
};

#endif //BLE_HEART_RATE_DEMO_HEARTRATEDEVICE_H
