//
// Created by Piotr Suwara on 15/10/2026.
//

#ifndef BLE_HEART_RATE_DEMO_MOCKDEVICESERVICE_H
#define BLE_HEART_RATE_DEMO_MOCKDEVICESERVICE_H

#include "../IDeviceService.h"
#include "../../Utilities/ConcurrencyHelpers.h"
#include <QHash>
#include <QObject>
#include <QPromise>
#include <QRandomGenerator>
#include <QSet>
#include <QTimer>
#include <algorithm>
#include <memory>
#include <stdexcept>

class MockDeviceService : public IDeviceService {
public:
    explicit MockDeviceService(
        QList<HeartRateDevice> devices = defaultDevices(),
        int scanDelayMs = 5000,
        int connectDelayMs = 1500,
        int indicationIntervalMs = 1000
    )
        : m_devices(std::move(devices)), m_scanDelayMs(scanDelayMs),
          m_connectDelayMs(connectDelayMs), m_indicationIntervalMs(indicationIntervalMs) {
    }

    QFuture<QList<HeartRateDevice>> findDevices(const QUuid &) override {
        return after<QList<HeartRateDevice>>(m_scanDelayMs, [this] { return QList<HeartRateDevice>(); });
    }

    QFuture<HeartRateDevice> connectDevice(const QUuid& deviceId) override {
        return after<HeartRateDevice>(m_connectDelayMs, [this] { return HeartRateDevice(); });
    }

    bool disconnectDevice(const QUuid& deviceId) override {

    }

    Subscription heartRateConnect(const QUuid& deviceId, std::function<void(int)> sink) override {

    }

    static QList<HeartRateDevice> defaultDevices() {
        return {
            makeDevice("11111111-1111-1111-1111-111111111111", "Polar H10"),
            makeDevice("22222222-2222-2222-2222-222222222222", "Wahoo TICKR"),
            makeDevice("33333333-3333-3333-3333-333333333333", "Garmin HRM-Pro"),
        };
    }

private:
    QList<HeartRateDevice> m_devices;
    int m_scanDelayMs;
    int m_connectDelayMs;
    int m_indicationIntervalMs;

    QSet<QUuid> m_connected;
    QHash<QUuid, std::weak_ptr<QTimer>> m_indications;

    static HeartRateDevice makeDevice(const char *uuid, const char *name)
    {
        HeartRateDevice d;
        d.id = QUuid::fromString(QLatin1String(uuid));
        d.name = QString::fromLatin1(name);
        return d;
    }
};


#endif //BLE_HEART_RATE_DEMO_MOCKDEVICESERVICE_H
