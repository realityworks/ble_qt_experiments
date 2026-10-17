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

    Q_INVOKABLE void select(const QModelIndex &index) {
        // TODO: Need to update model to be a device list first maybe
        //emit deviceSelected(m_items[index].uuid);
        QUuid selectedUUID = QUuid("11111111-1111-1111-1111-111111111111");
        emit deviceSelected(selectedUUID);
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

            // TODO: Configure with more complex model
            //configureListView(devices);

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

// Configure list view sample code
// enum { SubtitleRole = Qt::UserRole + 1 };
//
// auto *view  = new QListView;
// auto *model = new QStandardItemModel(view);
// view->setModel(model);
//
// auto add = [&](const QString &title, const QString &subtitle) {
//     auto *item = new QStandardItem(title + "\n" + subtitle);  // what's displayed
//     item->setData(title, Qt::UserRole);                       // optional: raw title
//     item->setData(subtitle, SubtitleRole);                    // raw subtitle
//     model->appendRow(item);
// };
//
// add("First item",  "This is the first subtitle");
// add("Second item", "Another descriptive line");
//
// QObject::connect(view, &QListView::activated, view, [](const QModelIndex &index) {
//     QString subtitle = index.data(SubtitleRole).toString();
//     QString title    = index.data(Qt::UserRole).toString();
//     qDebug() << title << subtitle;
// });