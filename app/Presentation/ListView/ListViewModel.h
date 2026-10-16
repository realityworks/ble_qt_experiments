//
// Created by Piotr Suwara on 15/10/2026.
//

#ifndef BLE_HEART_RATE_DEMO_LISTVIEWMODEL_H
#define BLE_HEART_RATE_DEMO_LISTVIEWMODEL_H

#include <QObject>
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
        //m_scanning = useCase.isScanning();
        // useCase.observeDevices(this, [this](const QList<Device> &d) { m_model->setDevices(d); });
        // useCase.observeScanning(this, [this](bool v) {
        //     m_scanning = v;
        //     emit scanningChanged();
        // });
    }

    QStringList devices() const { return m_items; }
    // bool scanning() const { return m_scanning; }
    //
    // Q_INVOKABLE void scan() { m_useCase.scan(); }
    //
    // Q_INVOKABLE void select(int row)
    // {
    //     const QUuid id = m_model->idAt(row);
    //     if (!id.isNull()) emit deviceActivated(id);   // navigation intent
    // }

    // signals:
    //     void scanningChanged();
    //void deviceActivated(const QUuid &id);

private:
    DeviceUseCase &m_useCase;
    QStringList m_items;
    bool m_scanning = false;
};

#endif //BLE_HEART_RATE_DEMO_LISTVIEWMODEL_H
