//
// Created by Piotr Suwara on 15/10/2026.
//

#ifndef BLE_HEART_RATE_DEMO_DEVICESERVICEFACTORY_H
#define BLE_HEART_RATE_DEMO_DEVICESERVICEFACTORY_H

#include "IBleService.h"
#include "MockBleService.h"

#include <QCoreApplication>
#include <QStringList>
#include <memory>

enum class DeviceServiceType { Mock, Bluetooth };

// The one place that knows the concrete service types.
inline std::shared_ptr<IDeviceService> makeDeviceService(DeviceServiceType backend)
{
    switch (backend) {
        case DeviceServiceType::Mock:
            //return std::make_shared<MockDeviceService>();
            qFatal("Not implemented");
        case DeviceServiceType::Bluetooth:
            // return std::make_shared<BleDeviceService>();   // add once the QtBluetooth implementation exists
            qFatal("Not implemented");
    }
    return nullptr;
}

inline DeviceServiceType serviceFromArguments(const QStringList &args) {
    return args.contains(QLatin1String("bluetooth")) ? DeviceServiceType::Bluetooth : DeviceServiceType::Mock;
}

#endif //BLE_HEART_RATE_DEMO_DEVICESERVICEFACTORY_H
