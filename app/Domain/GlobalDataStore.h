//
// Created by Piotr Suwara on 15/10/2026.
//

#ifndef BLE_HEART_RATE_DEMO_GLOBALDATASTORE_H
#define BLE_HEART_RATE_DEMO_GLOBALDATASTORE_H

#include <QObject>

class GlobalDataStore : public QObject {
    Q_OBJECT
public:
    explicit GlobalDataStore(QObject *parent = nullptr)
    : QObject(parent) {
        //qRegisterMetaType<GlobalDataStorePtr>();
    }

    void update() {

    }

    // Setup some type of connector to observe data
//signals:

private:
    void apply() {

    }
};

#endif //BLE_HEART_RATE_DEMO_GLOBALDATASTORE_H
