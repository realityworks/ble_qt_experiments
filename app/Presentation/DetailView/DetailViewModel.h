//
// Created by Piotr Suwara on 15/10/2026.
//

#ifndef BLE_HEART_RATE_DEMO_DETAILVIEWMODEL_H
#define BLE_HEART_RATE_DEMO_DETAILVIEWMODEL_H

#include "../../Domain/DeviceUseCase.h"

#include <QObject>
#include <QString>

#include <QObject>
#include <QStringList>

class DetailViewModel : public QObject {
    Q_OBJECT
public:
    DetailViewModel(
        DeviceUseCase &useCase,
        const QUuid &deviceId,
        QObject *parent = nullptr
    ) : QObject(parent), m_useCase(useCase), m_id(deviceId) {
        if (const auto d = useCase.device(m_id)) {
            m_name = d->name;
            m_bpm = d->bpm;
            m_state = d->state;
        }

        connectBindings();
    }

    ~DetailViewModel() override { m_useCase.disconnectDevice(m_id); }

    QString name() const { return m_name; }
    int bpm() const { return m_bpm; }
    ConnectionState state() const { return m_state; }
    QString status() const { return toString(m_state); }
    bool connected() const { return m_state == ConnectionState::Connected; }
    bool connecting() const { return m_state == ConnectionState::Connecting; }

    Q_INVOKABLE void connectToDevice() { m_useCase.connectDevice(m_id); }
    Q_INVOKABLE void disconnectFromDevice() { m_useCase.disconnectDevice(m_id); }

signals:
    void nameChanged();
    void bpmChanged();
    void stateChanged();

private:
    DeviceUseCase &m_useCase;
    QUuid m_id;
    QString m_name;
    int m_bpm = 0;

    // TODO: Move this into the AppState
    ConnectionState m_state = ConnectionState::Disconnected;

    void connectBindings() {
        m_useCase.observeDeviceField(
            m_id,
            &HeartRateDevice::name,
            this,
            [this](const QString &v){
                m_name = v;
                emit nameChanged();
            }
        );

        m_useCase.observeDeviceField(
            m_id,
            &HeartRateDevice::bpm,
            this,
            [this](int v){
                m_bpm = v;
                emit bpmChanged();
            });

        m_useCase.observeDeviceField(
            m_id,
            &HeartRateDevice::state,
            this,
            [this](ConnectionState v){
                m_state = v;
                emit stateChanged();
            }
        );
    }
};

#endif //BLE_HEART_RATE_DEMO_DETAILVIEWMODEL_H
