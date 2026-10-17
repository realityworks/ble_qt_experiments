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
        int scanDelayMs = 1000,
        int connectDelayMs = 1500,
        int indicationIntervalMs = 1000
    )
        : m_devices(std::move(devices)), m_scanDelayMs(scanDelayMs),
          m_connectDelayMs(connectDelayMs), m_indicationIntervalMs(indicationIntervalMs) {
    }

    QFuture<QList<HeartRateDevice>> findDevices(const QUuid &) override {
        return after<QList<HeartRateDevice>>(
            m_scanDelayMs,
            [this] {
                return m_devices;
            }
        );
    }

    QFuture<std::optional<HeartRateDevice>> connectDevice(const QUuid& deviceId) override {
        return after<std::optional<HeartRateDevice>>(
            m_connectDelayMs,
            [this, deviceId] -> std::optional<HeartRateDevice> {
                auto it = std::find_if(
                    m_devices.begin(),
                    m_devices.end(),
                    [&deviceId](const HeartRateDevice& checkDevice) {
                        return checkDevice.id == deviceId; // Your predicate condition
                    }
                );
                it->state = ConnectionState::Connected;
                if (it != m_devices.end()) {
                    m_connected.insert((*it).id);
                    return *it;
                }
                return std::nullopt;
            }
        );
    }

    bool disconnectDevice(const QUuid& deviceId) override {
        auto it = std::find_if(
            m_devices.begin(),
            m_devices.end(),
            [&deviceId](const HeartRateDevice& checkDevice) {
                return checkDevice.id == deviceId; // Your predicate condition
            }
        );

        it->state = ConnectionState::Disconnected;
        if (it != m_devices.end()) {
            m_connected.remove((*it).id);
        }
    }

    Subscription heartRateConnect(
        const QUuid& deviceId,
        std::function<void(int)> sink
    ) override {
        // TODO: Just do an update with sleeps
        Q_UNUSED(deviceId);
        std::shared_ptr<QTimer> timer = std::make_shared<QTimer>();
        timer->setInterval(1000);
        QObject::connect(
            timer.get(),
            &QTimer::timeout,
            timer.get(),
            [sink = std::move(sink)] {
                sink(QRandomGenerator::global()->bounded(80, 121));
            }
        );
        timer->start();
        return timer;
    }

    static QList<HeartRateDevice> defaultDevices() {
        return {
            makeDevice("11111111-1111-1111-1111-111111111111", "DEVICE 001"),
            makeDevice("22222222-2222-2222-2222-222222222222", "DEVICE 002"),
            makeDevice("33333333-3333-3333-3333-333333333333", "DEVICE 003"),
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
