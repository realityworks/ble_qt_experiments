//
// Created by Piotr Suwara on 15/10/2026.
//

#ifndef BLE_HEART_RATE_DEMO_SERVICESPEC_H
#define BLE_HEART_RATE_DEMO_SERVICESPEC_H



struct ServiceSpec {
    QBluetoothUuid uuid;
    QList<CharacteristicSpec> characteristics;

    // TODO: Implement once MOCK done
};

#endif //BLE_HEART_RATE_DEMO_SERVICESPEC_H
