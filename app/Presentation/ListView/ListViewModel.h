//
// Created by Piotr Suwara on 15/10/2026.
//

#ifndef BLE_HEART_RATE_DEMO_LISTVIEWMODEL_H
#define BLE_HEART_RATE_DEMO_LISTVIEWMODEL_H

#include <QObject>
#include <QStringList>
#include "../../Domain/DeviceUseCase.h"

class ListViewModel : public QObject {
    Q_OBJECT
    //Q_PROPERTY(bool scanning READ scanning NOTIFY scanningChanged)
public:
    explicit ListViewModel(
        DeviceUseCase &useCase,
        QObject *parent = nullptr
    )
        : QObject(parent), m_useCase(useCase)
    {
        m_items = QStringList {
            "Test1",
            "Test2",
        };

        connectToUseCase();
    }

    QStringList devices() const { return m_items; }
    bool scanning() const { return m_scanning; }

    // View model functions
    Q_INVOKABLE void scan() {
        m_useCase.scan();
    }

    Q_INVOKABLE void select() {
        // TODO: Need to update model to be a device list first maybe
    }

signals:
    void scanningChanged();
    void devicesFound();
    void deviceSelected(const QUuid &id);

private:
    void connectToUseCase() {
        m_scanning = m_useCase.isScanning();
        m_useCase.observeDevices(this, [this](const QList<HeartRateDevice> &devices){
            QStringList deviceNames;
            deviceNames.reserve(devices.size()); // Optimization to prevent reallocation

            for (const auto &device : devices) {
                deviceNames.append(device.name);
            }

            m_items = deviceNames;
            emit devicesFound();
        });
        m_useCase.observeScanning(this, [this](bool value) {
             m_scanning = value;
             emit scanningChanged();
        });
    }

    DeviceUseCase &m_useCase;
    QStringList m_items;
    bool m_scanning = false;
};

#endif //BLE_HEART_RATE_DEMO_LISTVIEWMODEL_H
