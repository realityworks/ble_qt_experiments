//
// Created by Piotr Suwara on 15/10/2026.
//

#ifndef BLE_HEART_RATE_DEMO_IDEVICESERVICE_H
#define BLE_HEART_RATE_DEMO_IDEVICESERVICE_H

struct IDeviceService {
    virtual ~IDeviceService() = default;

    virtual void findDevices() = 0;
    virtual void connectDevice() = 0;
    virtual void listenToHeartRate() = 0;

protected:

    // Prevent copy by value, on allow reference of the service implementation
    IDeviceService() = default;
    IDeviceService(const IDeviceService&) = default;
    IDeviceService(IDeviceService&&) = default;
};

#endif //BLE_HEART_RATE_DEMO_IDEVICESERVICE_H
