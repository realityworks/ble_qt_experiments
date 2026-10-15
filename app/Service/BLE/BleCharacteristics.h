//
// Created by Piotr Suwara on 15/10/2026.
//

#ifndef BLE_HEART_RATE_DEMO_BLECHARACTERISTICS_H
#define BLE_HEART_RATE_DEMO_BLECHARACTERISTICS_H

#include <QBluetoothUuid.h>
#include <QLowEnergyCharacteristic.h>
#include <QLowEnergyDescriptor.h>
#include <QLowEnergyService.h>

#include "CharSpec.h"

inline const CharacteristicSpec kBatteryLevel {
    QBluetoothUuid("00002A37-0000-1000-8000-00805F9B34FB"),
    QLowEnergyCharacteristic::Read | QLowEnergyCharacteristic::Notify,           // <property READ/NOTIFY>
    { QBluetoothUuid(QBluetoothUuid::DescriptorType::ClientCharacteristicConfiguration) }
};

inline const CharacteristicSpec kHeartRateMeasure {
    QBluetoothUuid("00002A19-0000-1000-8000-00805F9B34FB"),
    QLowEnergyCharacteristic::Read | QLowEnergyCharacteristic::Notify,           // <property READ/NOTIFY>
    { QBluetoothUuid(QBluetoothUuid::DescriptorType::ClientCharacteristicConfiguration) }
};



#endif //BLE_HEART_RATE_DEMO_BLECHARACTERISTICS_H
