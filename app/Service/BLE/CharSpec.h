//
// Created by Piotr Suwara on 15/10/2026.
//

#include <QBluetoothUuid.h>
#include <QLowEnergyCharacteristic.h>
#include <QLowEnergyDescriptor.h>
#include <QLowEnergyService.h>

#ifndef BLE_HEART_RATE_DEMO_CHARSPEC_H
#define BLE_HEART_RATE_DEMO_CHARSPEC_H

struct CharacteristicSpect {
    QBluetoothUuid uuid;
};

#endif //BLE_HEART_RATE_DEMO_CHARSPEC_H
