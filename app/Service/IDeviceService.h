//
// Created by Piotr Suwara on 15/10/2026.
//

#ifndef BLE_HEART_RATE_DEMO_IDEVICESERVICE_H
#define BLE_HEART_RATE_DEMO_IDEVICESERVICE_H

#include <QFuture>
#include <QList>
#include <QUuid>
#include <functional>
#include <memory>
#include "HeartRateDevice.h"

struct IDeviceService {
    virtual ~IDeviceService() = default;

    // Scan for and list the devices which match our requirements
    virtual QFuture<QList<HeartRateDevice>> findDevices(const QUuid &serviceUuid) = 0;

    // Connect the device completely and get
    virtual QFuture<HeartRateDevice> connectDevice(const QUuid &deviceId) = 0;

    virtual bool disconnectDevice(const QUuid &deviceId) = 0;

    // Subscribes to heart rate indications: every new BPM value is written to `sink`
    // (the write side of an int variable). The sink may be called from any thread.
    virtual Subscription heartRateConnect(
        const QUuid &deviceId,
        std::function<void(int)> sink
    ) = 0;

protected:

    // Prevent copy by value, on allow reference of the service implementation
    IDeviceService() = default;
    IDeviceService(const IDeviceService&) = default;
    IDeviceService(IDeviceService&&) = default;
};

#endif //BLE_HEART_RATE_DEMO_IDEVICESERVICE_H
