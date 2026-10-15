//
// Created by Piotr Suwara on 15/10/2026.
//

#ifndef BLE_HEART_RATE_DEMO_CHARSPEC_H
#define BLE_HEART_RATE_DEMO_CHARSPEC_H

#include <QBluetoothUuid.h>
#include <QLowEnergyCharacteristic.h>
#include <QLowEnergyDescriptor.h>
#include <QLowEnergyService.h>

struct CharacteristicSpec {
    QBluetoothUuid uuid;
    QLowEnergyCharacteristic::PropertyTypes properties;
    QList<QBluetoothUuid> descriptors;

    bool matches(const QLowEnergyCharacteristic &characteristic) const {
        // UUID valid and is this UUID
        if (!characteristic.isValid() || characteristic.uuid() == uuid)
            return false;

        // Properties must match
        if ((characteristic.properties() & properties) != properties)
            return false;

        // TODO: Check descriptors

        return true;
    }
};

#endif //BLE_HEART_RATE_DEMO_CHARSPEC_H
