//
// Created by Piotr Suwara on 15/10/2026.
//

#ifndef BLE_HEART_RATE_DEMO_DEVICEUSECASE_H
#define BLE_HEART_RATE_DEMO_DEVICEUSECASE_H

#include <QObject>
#include "../Service/IDeviceService.h"
#include "GlobalDataStore.h"
#include "AppStateHelpers.h"

class DeviceUseCase : public QObject {
    Q_OBJECT
public:
    using ServicePtr = std::shared_ptr<IDeviceService>;

    // Owning: hand over any IBleService (MockBleService, a QtBluetooth-backed one, ...).
    // `alert` replaces the default message box (handy for tests).
    DeviceUseCase(
        GlobalDataStore &store,
        ServicePtr ble,
        QObject *parent = nullptr
    ) : QObject(parent),
        m_store(store),
        m_deviceService(std::move(ble)) {
        Q_ASSERT_X(m_deviceService, "DeviceUseCase", "a BLE service is required");
    }

    std::optional<HeartRateDevice> device(const QUuid &id) const {
        const auto snap = m_store.currentState();
        if (const HeartRateDevice *device = findDevice(*snap, id))
            return *device;

        return std::nullopt;
    }

    template <typename Handler>
    void observeScanning(const QObject *context, Handler handler) {
        m_store.observe(context, &AppState::scanning, handler);
    }

    template <typename Handler>
    void observeDevices(
        const QObject *context,
        Handler handler
    ) {
        m_store.observe(context, &AppState::devices, handler);
    }

    template <typename Handler>
    void observeConnectionState(const QObject *context, Handler handler) {
        m_store.observe(context, &AppState::connectionState, handler);
    }

    template <typename Handler>
    void observeBpm(const QObject *context, Handler handler) {
        m_store.observe(context, &AppState::connectedDeviceBpm, handler);
    }

    // Core usecase functions :

    QList<HeartRateDevice> devices() const { return m_store.currentState()->devices; }
    bool isScanning() const { return m_store.currentState()->scanning; }

    void scan() {
        if (isScanning()) return;
            setScanning(true);

        // TODO: Set correct service UUID
        m_deviceService->findDevices(QUuid()).then(
            this,
            [this](const QList<HeartRateDevice> &found) {
                m_store.update([found](AppState &state) {
                    mergeDevices(state, found);
                    state.scanning = false;
                });
            }
        );
    }

    // KeyPath-style: observe one member of the device with `id`.
    template <typename T, typename Handler>
    void observeDeviceField(
        const QUuid &id,
        T HeartRateDevice::*field,
        const QObject *context,
        Handler handler
    ) {
        m_store.observe(
            context,
            [id, field](const AppState &state) -> T {
                const HeartRateDevice *device = findDevice(state, id);
                return device ? device->*field : T{};
            },
            handler
        );
    }

    void connectDevice(const QUuid &id) {
        m_store.update([](AppState &state) {
            state.connectionState = ConnectionState::Connecting;
        });

        m_deviceService->connectDevice(id).then(
            this,
            [this, id](const std::optional<HeartRateDevice> &connectedDevice) {
                if (connectedDevice == std::nullopt)
                    return;

                startHeartRateListener(id);

                m_store.update([connectedDevice](AppState &state) {
                    state.connectedDevice = connectedDevice.value().id;
                    state.connectionState = ConnectionState::Connected;
                });
            }
        );
    }

    void disconnectDevice(const QUuid &id) {
        m_subscriptions.remove(id); // dropping the subscription stops indications
        resetDevice(id);
    }

private:
    void startHeartRateListener(const QUuid &id)
    {
        GlobalDataStore *store = &m_store;
        // The sink is the "int variable": each BPM lands in this device's slot in the store.
        auto sub = m_deviceService->heartRateConnect(
            id,
            [store, id](int bpm) {
                store->update([id, bpm](AppState &state) {
                    if (HeartRateDevice *device = findDevice(state, id))
                        device->bpm = bpm;
                    state.connectedDeviceBpm = bpm;
                });
            }
        );

        if (!sub) {
            resetDevice(id);
            return;
        }
        m_subscriptions.insert(id, sub);
    }

    void setScanning(bool v) {
        m_store.update([v](AppState &s) { s.scanning = v; });
    }

    void resetDevice(const QUuid &id) {
        updateDevice(id, [](HeartRateDevice &d) {
            d.state = ConnectionState::Disconnected;
            d.bpm = 0;
        });
    }

    template <typename F>
    void updateDevice(const QUuid &id, F updateFunction) {
        m_store.update(
            [id, updateFunction](AppState &state){
                if (HeartRateDevice *device = findDevice(state, id))
                    updateFunction(*device);
            }
        );
    }

    GlobalDataStore &m_store;
    ServicePtr m_deviceService;   // declared before m_subscriptions, so it is destroyed after them
    QHash<QUuid, IDeviceService::Subscription> m_subscriptions;
};
#endif //BLE_HEART_RATE_DEMO_DEVICEUSECASE_H
